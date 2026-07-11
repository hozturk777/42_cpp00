# vptr, vtable, override, overload — Sistemsel Açıklama

Bu doküman C++'ta polymorphism'in temelini oluşturan `vptr` / `vtable`
mekanizmasını ve sık karıştırılan `override` / `overload` kavramlarını,
somut derleme çıktıları ve bellek adresleriyle açıklar.

---

## 1. Sorun: Derleyici hangi fonksiyonu çağıracağını NASIL bilir?

Normal (virtual olmayan) bir fonksiyon çağrısında, derleyici hangi kodun
çalışacağını **derleme zamanında (compile-time)** bilir ve makine kodunda
doğrudan o adrese `call` üretir:

```cpp
void foo() { ... }
foo();   // Derleyici: "call 0x4012a0" gibi sabit bir adrese zıpla
```

Ama polymorphism'de (bir base class pointer'ı/referansı üzerinden
türetilmiş sınıfın override ettiği fonksiyonu çağırmak) derleyici, hangi
fonksiyonun çalışacağını **derleme zamanında bilemez** — çünkü hangi
gerçek/dinamik tipin nesnesiyle karşılaşacağı çalışma zamanında (runtime)
belli olur:

```cpp
std::exception* p = ...;  // Aslında GradeTooHighException mi, yoksa
                           // başka bir exception türü mü, derleme
                           // sırasında bilinmiyor.
p->what();                 // Hangi what() çalışacak?
```

Bu sorunu çözmek için derleyici, **vtable** ve **vptr** mekanizmasını kurar.

---

## 2. vtable (Virtual Method Table) nedir?

- vtable, bir sınıfın **tüm `virtual` fonksiyonlarının adreslerini** tutan,
  fonksiyon pointer'larından oluşmuş **statik bir dizi**dir.
- Her sınıf (en az bir `virtual` fonksiyonu varsa) için derleyici **tek bir**
  vtable üretir — nesne sayısından bağımsız! 1000 tane `GradeTooHighException`
  nesnesi yaratsanız bile, vtable'dan sadece **1 tane** vardır, tüm nesneler
  onu paylaşır.
- Bu tablo, programın binary'sinde **read-only bir bellek bölgesinde**
  (genelde `.rodata` ya da `.data.rel.ro` section'ı — ELF/Mach-O formatında)
  durur. Program diskten RAM'e yüklenirken (`exec`/loader aşamasında) bu
  bölge de belleğe haritalanır ve program çalıştığı sürece sabit kalır.

Örnek:

```cpp
class std::exception {
    virtual const char* what() const throw();
    virtual ~exception();
};

class GradeTooHighException : public std::exception {
    virtual const char* what() const throw();  // override
};
```

Bellekte (kavramsal olarak) şöyle iki ayrı tablo oluşur:

```
vtable for std::exception:
+---+----------------------------------------+
| 0 | &std::exception::~exception             |
| 1 | &std::exception::what                   |
+---+----------------------------------------+

vtable for GradeTooHighException:
+---+----------------------------------------+
| 0 | &GradeTooHighException::~exception (miras alınmış ya da override) |
| 1 | &GradeTooHighException::what              | <-- FARKLI adres!
+---+----------------------------------------+
```

`GradeTooHighException` sadece `what()`'i override ettiği için, kendi
vtable'ında SADECE `what()` slotu değişir; diğer slotlar (override
edilmemiş fonksiyonlar) base class'ınkiyle aynı adresi gösterir.

---

## 3. vptr (Virtual Table Pointer) nedir?

- vptr, **her nesnenin içinde** duran, o nesnenin sınıfına ait vtable'ın
  adresini tutan **gizli bir pointer alanı**dır.
- Derleyici bunu sizin haberiniz olmadan, sınıfın ilk `virtual` fonksiyonu
  tanımlandığı anda otomatik olarak nesnenin bellek düzenine ekler (genelde
  nesnenin en başına, offset 0'a).
- Nesne `construct` edilirken (constructor çalışırken), derleyici sizin
  yazdığınız kod çalışmadan ÖNCE, gizlice şu işlemi yapar:
  `this->vptr = &ClassName_vtable;`
  Bu yüzden constructor içinde bile `virtual` çağrılar doğru şekilde
  o anki sınıfın vtable'ına gider (ama base class constructor'ı çalışırken
  vptr henüz base class'ın vtable'ına işaret eder — bilinen bir C++
  detayıdır: constructor içinde virtual dispatch tam olarak türetilmiş
  sınıfa gitmez).

### Somut kanıt: gerçek bellek adreslerini okuma

```cpp
#include <exception>
#include <iostream>
#include <cstdio>

class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw() { return "Grade is too high"; }
};

class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw() { return "Grade is too low"; }
};

int main() {
    GradeTooHighException e1;
    GradeTooLowException  e2;

    void** vptr1 = reinterpret_cast<void**>(&e1);
    void** vptr2 = reinterpret_cast<void**>(&e2);

    std::printf("e1'in vptr'si (vtable adresi) = %p\n", vptr1[0]);
    std::printf("e2'nin vptr'si (vtable adresi) = %p\n", vptr2[0]);
    // Bu iki adres FARKLIDIR, çünkü iki farklı sınıfın iki farklı
    // vtable'ı var.
}
```

Çalıştırdığımızda (gerçek terminal çıktısı):

```
e1'in vptr'si (vtable adresi) = 0x1048940d0
e2'nin vptr'si (vtable adresi) = 0x104894100
```

İki adres birbirinden farklı — çünkü `GradeTooHighException` ve
`GradeTooLowException` ayrı sınıflar, ayrı vtable'lara sahipler.

### `obj.what()` çağrıldığında CPU seviyesinde olan tam adımlar:

```cpp
std::exception* p = &e1;
p->what();
```

1. CPU, `p`'nin tuttuğu adresi register'a yükler (`p`'nin kendisi bir
   pointer, 8 byte, stack'te ya da register'da durur).
2. O adresten (nesnenin offset 0'ından) **8 byte okur** → bu, vptr'nin
   DEĞERİ, yani vtable'ın adresi.
3. O vtable adresinden, `what()`'in vtable içindeki **sabit offset'ine**
   (örn. offset 8, ikinci slot) giderek **8 byte daha okur** → bu da
   gerçek `what()` fonksiyonunun makine kodu adresi.
4. CPU o adrese **indirect call** yapar (hedefi register'dan alan bir
   `call` — direkt/sabit adresli bir `call`'dan farklı olarak, CPU'nun
   dallanma tahmin (branch prediction) birimi hedefi önceden kestiremez,
   bu yüzden marjinal bir performans maliyeti vardır).

Yani tek bir `virtual` çağrı = **2 ekstra RAM okuması + 1 indirect jump**.
Virtual olmayan bir çağrı ise doğrudan sabit adrese `call` yapar (0 ekstra
RAM okuması, direct jump — dallanma hedefi derleme zamanında bilindiği
için CPU branch predictor'ı için de daha ucuzdur).

---

## 4. override nedir?

**Override**: Bir türetilmiş (derived) sınıfın, base class'tan miras aldığı
**`virtual`** bir fonksiyonu, **BİREBİR AYNI İMZAYLA** (aynı isim, aynı
parametre tipleri, aynı `const`/`volatile` niteleyicileri, uyumlu dönüş
tipi) yeniden tanımlamasıdır.

```cpp
class std::exception {
    virtual const char* what() const throw();
};

class GradeTooHighException : public std::exception {
    virtual const char* what() const throw();  // OVERRIDE
    //     ^^^^^^^^^^^^ ^^^^^ ^^^^^
    //     aynı isim    aynı const  aynı throw()
};
```

- Base class'ta fonksiyon `virtual` olmak ZORUNDADIR, aksi halde override
  değil, sadece **name hiding** (isim gizleme) olur — base class'taki
  fonksiyon bir daha erişilemez hale gelir ama dinamik dispatch çalışmaz.
- **Sistemsel etki:** Override olduğunda, derleyici türetilmiş sınıfın
  vtable'ındaki ilgili slotu, base class'ın fonksiyon adresi yerine
  **türetilmiş sınıfın kendi fonksiyonunun adresiyle** doldurur. Bellekte
  hiçbir yeni "override" bayrağı/flag'i yoktur — sadece vtable'daki bir
  pointer değeri değişir.
- C++11'den itibaren isteğe bağlı `override` anahtar kelimesi eklenebilir
  (`const throw()`'un yanına): `const override;`. Bu, derleyiciye "ben bu
  fonksiyonun gerçekten bir base class fonksiyonunu override ettiğini
  iddia ediyorum, eğer imza uyuşmuyorsa hata ver" der — yani **derleme
  zamanı güvenlik kontrolüdür**, çalışma zamanında hiçbir etkisi yoktur.
  (42 okulu ödevlerinde genelde C++98 kullanıldığı için bu anahtar kelime
  kullanılmaz, ama modern kodda çok önerilir.)

### Override olmazsa ne olur? (yanlış imza örneği)

```cpp
class Base {
    public:
        virtual const char* what() const throw() { return "Base"; }
};

class Derived : public Base {
    public:
        // const eksik! -> Bu bir OVERRIDE DEĞİL, tamamen yeni/ayrı bir fonksiyon
        virtual const char* what() throw() { return "Derived"; }
};

int main() {
    Base* p = new Derived();
    std::cout << p->what() << std::endl;  // "Base" YAZAR! (Derived'inki değil)
}
```

Somut kanıt için derleyip çalıştıralım:

---

## 5. overload nedir?

**Overload**: Aynı isimde, ama **farklı parametre listesine** (farklı
tip, farklı sayıda parametre) sahip birden fazla fonksiyon tanımlamaktır.
`virtual` ile hiçbir ilgisi yoktur — tamamen derleme zamanında (compile-time,
**static/early binding**) çözülür.

```cpp
class Bureaucrat {
    public:
        void setGrade(int g);          // overload #1
        void setGrade(std::string s);  // overload #2 (farklı parametre tipi)
};
```

- Derleyici, `setGrade(5)` çağrısını görünce, argümanın tipine
  (`int`) bakarak **derleme zamanında** hangi overload'un çağrılacağına
  karar verir. Buna **static binding** denir — `virtual`'daki gibi
  runtime'da vtable'a bakmaya gerek yoktur.
- Sistemsel etki: Overload'lar, derleyici tarafından **her biri için ayrı
  ayrı, farklı isimlere sahip** (name mangling ile, örn.
  `_ZN10Bureaucrat8setGradeEi` vs `_ZN10Bureaucrat8setGradeENSt7__cxx1112basic_stringIcEE`)
  makine koduna derlenir. Yani "overload" kavramı runtime'da HİÇ yoktur —
  linker'a göre bunlar zaten baştan beri tamamen ayrı, birbirinden
  bağımsız iki fonksiyondur. `virtual` çağrıdaki gibi bir "hangisini
  çalıştırayım" belirsizliği hiç oluşmaz; derleyici derleme anında hangi
  sembole `call` yapılacağını zaten bilir.

---

## 6. override vs overload — Karşılaştırma Tablosu

| | **Override** | **Overload** |
|---|---|---|
| İsim | Aynı | Aynı |
| Parametreler | Aynı (birebir) | Farklı |
| `virtual` gerekli mi? | Evet (base class'ta) | Hayır, ilgisiz |
| Ne zaman çözülür? | Çalışma zamanı (runtime, vtable üzerinden) | Derleme zamanı (compile-time) |
| Hangi sınıfta olur? | Base + Derived (kalıtım ilişkisi) | Aynı sınıf (veya scope) içinde |
| Bellek/CPU etkisi | vtable slotu değişir, indirect call | Ayrı ayrı sembollere derlenir, direct call |
| Binding türü | Dynamic / late binding | Static / early binding |
| Amaç | Polymorphism (farklı davranış, aynı arayüz) | Aynı işin farklı girişlerle yapılması (kolaylık) |

---

## 7. Kendi Bureaucrat.hpp'nizdeki somut örnek

```cpp
class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();  // <-- override
};

class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();  // <-- override (farklı sınıf, aynı imza)
};
```

- Her iki sınıf da `std::exception::what()`'i **override** ediyor — isim
  aynı (`what`), imza aynı (`const throw()`), her ikisi de `virtual`.
  Bu bir overload DEĞİL, çünkü aralarında kalıtım ilişkisi var ve imzalar
  birebir aynı.
- Eğer siz `Bureaucrat` sınıfı içine `what(int code)` gibi ekstra
  parametreli bir fonksiyon eklemiş olsaydınız, o bir **overload** olurdu
  (farklı parametre listesi, aynı isim, aynı sınıf içinde de olabilir).

### Neden bu iki exception ayrı sınıflar (overload değil, iki ayrı override)?

Çünkü `catch` bloklarında **tip bazlı** yakalama yapabilmek istiyoruz:

```cpp
try {
    Bureaucrat b("Test", 200);
} catch (Bureaucrat::GradeTooHighException& e) {
    std::cout << e.what() << std::endl;  // "Grade is too high" -> kendi vtable'ından
} catch (Bureaucrat::GradeTooLowException& e) {
    std::cout << e.what() << std::endl;  // "Grade is too low" -> kendi vtable'ından
}
```

Runtime, fırlatılan (`throw` edilen) nesnenin **gerçek/dinamik tipine**
bakarak hangi `catch` bloğunun eşleştiğine karar verir (bu da bir tür
runtime type bilgisi kullanımıdır — RTTI). Her `catch` bloğunda `e.what()`
çağrıldığında, o nesnenin KENDİ vtable'ındaki `what()` çalışır —
override mekanizması sayesinde doğru mesaj otomatik olarak seçilir, siz
hiçbir `if/else` ya da tip kontrolü yazmak zorunda kalmazsınız.
