# Bureaucrat.hpp — Satır Satır Sistemsel Açıklama

Bu doküman `Bureaucrat.hpp` dosyasındaki her satırı; derleyici (compiler), bellek (RAM),
ve çalışma zamanı (runtime) düzeyinde ne yaptığını açıklar.

---

## 1-2. Include Guard

```cpp
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP
```

- Bu bir **preprocessor** (önişlemci) direktifidir. Derleme, kaynak kodun derlenmesinden
  ÖNCE, saf metin düzeyinde çalışan bir "find & replace" aşamasından geçer.
- `#ifndef` = "eğer bu isimde bir macro tanımlı değilse". `BUREAUCRAT_HPP` henüz
  tanımlanmadıysa içeri gir, tanımlıysa (yani bu header daha önce include edildiyse)
  dosyanın geri kalanını tamamen atla.
- **Neden var:** Aynı header birden fazla `.cpp` dosyasından zincirleme include
  edilirse (örn. A.hpp -> B.hpp -> Bureaucrat.hpp, ve A.hpp de direkt
  Bureaucrat.hpp içeriyorsa), sınıf tanımı iki kez derleyiciye görünür ve
  "redefinition of class Bureaucrat" hatası alırsınız. Include guard bunu RAM'de
  veya diskte değil, **derleme zamanında (compile-time)** preprocessor seviyesinde engeller.
- Sistemsel not: Bu satırların çalışma zamanında (runtime) hiçbir karşılığı yoktur.
  Program çalışırken CPU bu satırları hiç görmez; onlar sadece derleyiciye "hangi
  metni dahil et/etme" talimatı verir. `#endif` (satır 44) bu bloğu kapatır.

---

## 4-8. Renk Kodları (Macro Tanımları)

```cpp
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
...
```

- Yine preprocessor seviyesinde çalışır. `GREEN` kelimesi, derleyici görmeden önce
  preprocessor tarafından `"\033[1;32m"` string literaline **metinsel olarak**
  değiştirilir (substitution). Derleyici hiçbir zaman "GREEN" kelimesini görmez.
- `\033` = ESC karakteri (ASCII 27, oktal). Terminal bu ESC dizisini gördüğünde
  metni renklendirir. Bu bir **ANSI escape code**'dur; RAM'de sıradan bir char
  dizisi olarak durur, terminal emülatörü bunu yorumlayıp ekran çıktısını
  renklendirir. C++ dilinin veya derleyicinin bu konuda bir bilgisi yoktur —
  sadece bir string literal.
- Bu string'ler programın **binary'sinin read-only data segmentinde (.rodata)**
  saklanır (aşağıda detaylandırılıyor).

---

## 10-11. Include'lar

```cpp
#include <string>
#include <exception>
```

- Preprocessor bu satırları görünce, o başlık dosyalarının **tüm içeriğini**
  kelimesi kelimesine bu noktaya yapıştırır (metinsel kopyalama). Derleyici
  aslında binlerce satırlık genişletilmiş kodu görür.
- `<string>` → `std::string` sınıfının tanımını getirir (dinamik bellek yöneten
  bir sarmalayıcı/wrapper sınıf, içeride bir `char*` heap pointer'ı tutar).
- `<exception>` → `std::exception` base class'ını getirir; `what()` virtual
  metodunu tanımlar.

---

## 13-14. Sınıf Tanımı

```cpp
class Bureaucrat
{
```

- Derleyiciye yeni bir **tür (type)** tanımlandığını söyler. Bu satır henüz RAM'de
  hiçbir şey oluşturmaz — sadece bir "kalıp/şablon" (blueprint) tanımlanır.
  Bellek ayrımı yalnızca bu tipten bir **nesne (object)** oluşturulduğunda olur
  (örn. `Bureaucrat b;` satırında, stack üzerinde).

---

## 15-17. Private Üyeler

```cpp
private:
    const std::string _name;
    int _grade;
```

- `private:` — **erişim kontrolü (access control)**. Bu tamamen derleme zamanı
  (compile-time) bir kavramdır; RAM'de "private" diye bir bit/flag yoktur.
  Derleyici, class dışından `_name`'e erişmeye çalışan kodu görürse derlemeyi
  hata ile durdurur. Çalışma zamanında (runtime) hiçbir koruma yoktur — bellek
  düzeyinde private/public üyeler arasında fark yoktur, ikisi de aynı nesnenin
  bellek bloğu içinde art arda dizilir.

### `const std::string _name;`

- **`const`**: Bu üye, nesne bir kez constructor ile inşa edildikten sonra
  **bir daha değiştirilemez** demektir. Derleyici, `_name = "x";` gibi bir
  atama görürse compile-time hatası verir.
- Sistemsel etkisi: `const` olmayan bir üyeden farklı olarak, `const` üye
  sadece **member initializer list** ile ilklendirilebilir (constructor
  gövdesinde `this->_name = ...` yazamazsınız çünkü bu bir atama, ilklendirme
  değildir). `Bureaucrat.cpp:9` satırında görüldüğü gibi:
  `Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name)`
- **Önemli sonuç:** Bir sınıfta `const` üye varsa, o sınıfın
  **copy assignment operator'ü (`operator=`)** derleyici tarafından
  otomatik/implicit olarak **üretilemez** çünkü atama `_name`'i yeniden
  yazmayı gerektirir ama `_name` const'tur. Bu yüzden bu sınıfta
  `operator=` elle (manuel) yazılmıştır (satır 22) — ama dikkat: o da
  gerçekte `_name`'i değiştirmez (cpp dosyasına bakınca sadece `_grade`
  kopyalanıyor), çünkü `_name` const olduğu için zaten değiştirilemez.
- `std::string` bir **sınıf**tır, ilkel (primitive) tip değildir. Bellekte
  şöyle durur: nesnenin kendisi (genelde 32 byte civarı, implementasyona
  bağlı: bir pointer + boyut + kapasite alanları) **stack'te veya nesnenin
  içine gömülü** olarak durur; ama string'in gerçek karakter verisi
  (`"Default"` gibi) genelde **heap** üzerinde ayrı bir yerde tutulur
  (kısa string optimizasyonu -SSO- yoksa; kısa stringler bazı
  implementasyonlarda doğrudan nesnenin içinde/stackte tutulabilir).

### `int _grade;`

- İlkel (primitive) tip. Bellekte tipik olarak 4 byte yer kaplar, doğrudan
  nesnenin bellek bloğunun içine gömülüdür (heap'e ayrı bir ayırma
  gerektirmez). CPU seviyesinde bir `int` okuma/yazma tek bir mov
  instruction'ı ile RAM'den register'a/register'dan RAM'e taşınır.

---

## 18. `public:`

- Erişim belirleyicisi değişir. Bundan sonraki üyeler class dışından
  erişilebilir olur. Yine tamamen derleme zamanı bir kavram.

---

## 19-23. Constructor'lar, Assignment, Destructor

```cpp
Bureaucrat();
Bureaucrat(const std::string name, int grade);
Bureaucrat(const Bureaucrat& copy);
Bureaucrat& operator=(const Bureaucrat& copy);
~Bureaucrat();
```

Bunlar sadece **bildirim (declaration)**'dır; gövdeleri `.cpp` dosyasındadır
(tanım/definition orada). Header'da sadece "böyle bir fonksiyon var, imzası
bu" denir; linker daha sonra çağrıyı gerçek koda bağlar.

- **Default constructor** `Bureaucrat()`: Argümansız nesne oluşturmayı sağlar.
  RAM'de: nesne için ayrılan bellek bloğu (stack ya da heap, `new` ile mi
  oluşturuluyor ona bağlı) bu fonksiyon çağrılarak ilklendirilir.
- **Parametreli constructor**: `name` ve `grade` alır. Dikkat: `name`
  değer olarak (by value) alınıyor — çağrı sırasında string'in bir **kopyası**
  stack'e (fonksiyonun parametre alanına) kopyalanır. Bu, referans (`const
  std::string&`) kullanılsaydı önlenebilecek gereksiz bir kopyalama
  maliyetidir (performans notu, ödevin gereksinimlerine bağlı).
- **Copy constructor** `Bureaucrat(const Bureaucrat& copy)`: Var olan bir
  nesneden yeni bir nesne üretirken çağrılır (örn. `Bureaucrat b2(b1);` ya da
  `Bureaucrat b2 = b1;`). `const Bureaucrat&` — referans olduğu için hiçbir
  kopya yapılmaz, sadece `copy`'nin bellek adresi fonksiyona geçirilir (CPU
  seviyesinde bu bir pointer/register üzerinden adres taşımadır, tüm nesneyi
  kopyalamaz). `const` sayesinde fonksiyon içinde `copy` nesnesi değiştirilemez.
- **Copy assignment operator** `operator=`: Zaten var olan iki nesne arasında
  `b1 = b2;` yazıldığında çağrılır (yeni nesne yaratmaz, var olanın içeriğini
  değiştirir). Kendi kendine atamaya karşı (`this != &copy`) kontrol
  cpp dosyasında var — bu, `b1 = b1;` gibi durumlarda gereksiz/zararlı
  işlemleri önlemek için klasik bir C++ idiyomudur (self-assignment check).
- **Destructor** `~Bureaucrat()`: Nesne kapsam (scope) dışına çıktığında ya da
  `delete` ile silindiğinde otomatik çağrılır. Sistemsel olarak: stack'teki bir
  nesne fonksiyon `return` olduğunda, stack pointer geri alınmadan HEMEN ÖNCE
  derleyicinin eklediği gizli bir çağrı ile destructor tetiklenir. Burada özel
  bir "temizlik" yapılmıyor (sadece log basıyor), ama `_name` (bir
  `std::string`) kendi destructor'ı üzerinden **heap'te ayırdığı belleği
  otomatik olarak serbest bırakır** (RAII prensibi).

---

## 25-26. Const Member Fonksiyonlar

```cpp
std::string getName() const;
int getGrade() const;
```

- Fonksiyon imzasının sonundaki `const`, `_name` veya `_grade`'i alan `const`
  değildir — bu, **`this` pointer'ının const olduğu** anlamına gelir. Yani bu
  metod içinde `this->_grade = 5;` gibi bir değişiklik yapılamaz; derleyici
  compile-time'da engeller.
- **Neden önemli:** `const Bureaucrat& b` gibi bir referans/parametre
  üzerinden sadece `const` işaretli metodlar çağrılabilir. `operator<<`
  (satır 42) parametresi `const Bureaucrat&` olduğu için, içeride `b.getName()`
  çağırabilmek adına `getName()`'in const olması **zorunludur** — const
  olmasaydı derleme hatası alırdınız.
- Sistemsel düzeyde: `const` metod ile normal metod arasında derlenen
  makine kodu (assembly) düzeyinde HİÇBİR fark yoktur. `const` tamamen bir
  derleyici disiplinidir (compile-time type checking); CPU çalışırken "bu
  const bir çağrıydı" diye bir bilgiye sahip değildir, bu bilgi binary'ye
  gömülmez.

## 27-28. Diğer Metodlar

```cpp
void incGrade();
void decGrade();
```

`const` değiller çünkü `_grade`'i değiştiriyorlar (cpp'de görüldüğü gibi).

---

## 30-33. İç İçe Sınıf: GradeTooHighException

```cpp
class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
};
```

- Bu, `Bureaucrat` sınıfının içinde tanımlanmış bir **nested class**'tır.
  Tamamen ismi kapsamlama (scoping) amaçlıdır: dışarıdan
  `Bureaucrat::GradeTooHighException` şeklinde erişilir. RAM'de veya
  runtime'da bir "içe gömülü olma" etkisi yoktur, sadece isimlendirme/scope
  kuralıdır.
- **`: public std::exception`** — public inheritance (kalıtım). Bu sınıf
  `std::exception`'ın TÜM (public/protected) üyelerini devralır ve
  `is-a` ilişkisi kurar: bir `GradeTooHighException` nesnesi, aynı zamanda
  bir `std::exception` nesnesidir ve `std::exception&` veya
  `std::exception*` türünden bir referans/pointer ile yakalanabilir
  (`catch (std::exception& e)` gibi genel handler'lar bunu yakalayabilir).
  - Bellek düzeyinde: `GradeTooHighException` nesnesi, içinde bir
    `std::exception` alt-nesnesi barındırır (base subobject). Bellek
    düzeni tipik olarak: [vtable pointer][std::exception'ın kendi
    alanları][varsa GradeTooHighException'a özgü ek alanlar — burada yok].

### `virtual`

- **`virtual`**, C++'ın **dinamik/geç bağlama (dynamic/late binding)**
  mekanizmasını tetikler. Normalde (virtual olmayan) bir fonksiyon çağrısı
  derleme zamanında hangi fonksiyonun çağrılacağına karar verir (static
  binding) — CPU direkt o fonksiyonun adresine `call` yapar.
- `virtual` işaretli bir fonksiyon için derleyici **her sınıf için bir
  vtable (virtual method table)** oluşturur — bu, fonksiyon pointer'larından
  oluşan, programın **read-only data / text segmentinde** (genelde
  `.rodata` ya da `.data.rel.ro`) duran statik bir dizidir.
- Her nesne, bu sınıfın vtable'ına işaret eden gizli bir **vptr (virtual
  table pointer)** alanı taşır — bu vptr, nesnenin bellek bloğunun
  (genelde) en başına derleyici tarafından otomatik eklenir (nesne
  boyutunu +8 byte, 64-bit sistemde, artırır).
- Çalışma zamanında `obj.what()` çağrıldığında CPU şunları yapar:
  1. Nesnenin bellek adresinden vptr'yi oku (RAM'den bir pointer oku, 8 byte).
  2. vptr'nin gösterdiği vtable'dan, `what()`'in bu sınıftaki override'ının
     adresini bulacak offset'i oku (yine bir RAM okuması).
  3. O adrese `call` yap (indirect call — CPU'nun dallanma tahmin
     (branch prediction) birimi için, direct call'a göre biraz daha
     maliyetli, çünkü hedef adres önceden bilinemez, register üzerinden
     dolaylı olarak gelir).
  - Bu yüzden `virtual` çağrı, virtual olmayan bir çağrıya göre 1-2 ekstra
    bellek erişimi + bir indirect jump içerir (performans notu — genelde
    ihmal edilebilir ama sistemsel olarak fark budur).
- **Neden burada `virtual` gerekli:** `std::exception::what()` zaten
  `virtual` olarak tanımlıdır. Eğer siz bir `std::exception*` pointer'ı
  üzerinden `what()` çağırırsanız (örn. genel bir `catch (std::exception&
  e) { e.what(); }` bloğunda), hangi `what()`'in çalışacağına derleme
  zamanında değil, **çalışma zamanında, nesnenin gerçek/dinamik tipine
  bakılarak** karar verilir (polymorphism). `virtual` olmasaydı, her zaman
  `std::exception::what()` çağrılırdı (statik tip neyse o), sizin
  override'ınız asla çalışmazdı.

### `const` (fonksiyonun sonunda)

- Yukarıda açıklandığı gibi, `this`'in const olduğunu belirtir.
  `std::exception::what()`'in imzası da `const` olduğu için, override eden
  fonksiyonun da birebir aynı imzaya (const dahil) sahip olması **zorunludur**
  — aksi halde bu bir override değil, tamamen farklı/yeni bir fonksiyon
  (overload/gizleme) olurdu ve polymorphism çalışmazdı.

### `throw()` — Exception Specification (C++98/03 stili)

```cpp
virtual const char* what() const throw();
```

- Bu, fonksiyonun **hiçbir exception fırlatmayacağını (fırlatmamalı)**
  taahhüt eden eski (C++98/03, C++11'de deprecated, C++17'de kaldırıldı)
  bir sözdizimidir: **dynamic exception specification**.
- `throw()` boş parantez = "bu fonksiyon exception fırlatmaz" demektir.
  (`throw(int)` yazsaydınız "sadece int tipinde exception fırlatabilir"
  anlamına gelirdi — burada boş, yani hiç fırlatmaz.)
- Sistemsel/runtime etkisi: Eğer bu fonksiyon `throw()` dediği halde
  gerçekten bir exception fırlatırsa, runtime `std::unexpected()` çağrılır
  ve genelde program `std::terminate()` ile sonlanır — bu kontrol derleme
  zamanında DEĞİL, **çalışma zamanında** (bir exception fırlatılma anında)
  yapılır; derleyici bunu garanti edemez, sadece bir runtime sözleşmesi
  (contract) sunar.
- 42 okulu ödevlerinde bu satır genelde `std::exception::what()`'in orijinal
  imzasıyla **birebir eşleşmek** için zorunlu tutulur (override kuralları
  gereği base class imzasıyla aynı olmalı). Modern C++'ta bunun yerine
  `noexcept` kullanılır (C++11+), ama bu ödev muhtemelen C++98 standardında
  yazıldığı için eski sözdizimi kullanılmış.

### `const char* what() const throw();` — Fonksiyonun Dönüş Değeri

- `const char*` — değiştirilemez bir C-stili string'e (null-terminated
  char dizisi) işaret eden bir pointer döner. Bellekte bu genelde bir
  **string literal**'e işaret eder (örn. cpp'de `return ("Grade is too
  high");`), ki bu literal binary'nin **.rodata (read-only data)**
  segmentinde durur — program ömrü boyunca sabittir, heap/stack'te değil.
  Bu yüzden pointer'ı döndürmek güvenlidir (dangling pointer riski yoktur,
  çünkü .rodata segmenti program çalıştığı sürece bellekte kalır).

---

## 35-38. GradeTooLowException

Yukarıdakiyle birebir aynı yapı/mantık, sadece farklı bir mesaj döner
(`"Grade is too low"`). Ayrı bir sınıf olmasının nedeni: `catch` bloklarında
"çok yüksek" ile "çok düşük" hatasını **tip bazlı olarak** ayırt edebilmek
(`catch (Bureaucrat::GradeTooHighException&)` vs
`catch (Bureaucrat::GradeTooLowException&)`).

---

## `throw` (exception fırlatma) — cpp dosyasında kullanımı

Header'daki `throw()` ile karıştırılmaması gereken, cpp dosyasındaki asıl
`throw` ifadesi:

```cpp
if (grade > 150)
    throw Bureaucrat::GradeTooHighException();
```

Sistemsel olarak `throw` çalıştığında CPU/runtime şunları yapar:
1. `Bureaucrat::GradeTooHighException()` geçici bir nesne olarak
   oluşturulur (genelde exception nesnesi için ayrılmış özel bir bellek
   alanında — bu, normal stack/heap'ten farklı, C++ runtime'ının (libstdc++,
   libc++ gibi) kendi ayırdığı bir **exception bölgesi**dir).
2. Runtime, çağrı yığınında (call stack) **geriye doğru tarama (stack
   unwinding)** yapmaya başlar: mevcut fonksiyondan başlayarak, her bir üst
   çağırana doğru çıkar, bu sırada scope'tan çıkan her yerel nesnenin
   destructor'ı otomatik çağrılır (RAII temizliği).
3. Bu tarama, tipi eşleşen bir `catch` bloğu bulana kadar (ya da `main`'e
   kadar çıkıp `std::terminate()` çağrılana kadar) devam eder.
4. Bu mekanizma **normal fonksiyon `return`'ünden çok daha maliyetlidir**
   çünkü derleyici, hangi objelerin nerede destroy edileceğine dair önceden
   ürettiği "unwind tabloları" (genelde `.eh_frame` ELF section'ı, DWARF
   formatında) üzerinden RAM'den okuma yaparak yığını sarar — bu, normal bir
   fonksiyon dönüşü gibi tek bir stack pointer ayarlamasından çok daha
   karmaşık bir işlemdir.

---

## 42. Serbest (non-member) Fonksiyon

```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);
```

- Sınıfın üyesi değil, **global/serbest bir fonksiyon**dur (`operator<<`
  bir sınıf üyesi olarak tanımlansaydı, `std::cout << b` yerine
  `b << std::cout` yazmanız gerekirdi çünkü sol operand her zaman `this`
  olur — bu yüzden ikili operatörler C++'ta genelde free function olarak
  tanımlanır).
- `std::ostream&` dönüşü, **zincirleme (chaining)** yapılabilmesi içindir:
  `std::cout << b1 << b2;` gibi ifadeler, her `<<` çağrısının sonucu bir
  sonraki `<<`'ye sol operand olarak geçtiği için çalışır (`os` referansı
  aynı stream nesnesine işaret ederek geri döner).
- `const Bureaucrat& b` — referans olduğu için nesne kopyalanmaz (sadece
  adresi CPU register'ında taşınır), `const` olduğu için içeride `b`
  değiştirilemez ve bu sayede yalnızca `const` işaretli metodlar
  (`getName()`, `getGrade()`) çağrılabilir.

---

## Özet Tablo

| Anahtar Kelime | Ne zaman etkili | Sistemsel karşılığı |
|---|---|---|
| `#ifndef/#define/#endif` | Derleme öncesi (preprocessor) | Yalnızca metin düzeyinde; RAM'de karşılığı yok |
| `#define GREEN ...` | Preprocessor | Metinsel yer değiştirme; string `.rodata`'da durur |
| `private/public` | Derleme zamanı | Erişim denetimi; bellek düzeninde fark yaratmaz |
| `const` (üye değişken) | Derleme + ilklendirme | Sadece initializer list ile set edilir; implicit `operator=` üretimini engeller |
| `const` (metod sonunda) | Derleme zamanı | `this` pointer'ı const olur; compile-time kontrol |
| `virtual` | Derleme (vtable üretimi) + çalışma zamanı (dispatch) | Her nesneye vptr eklenir (+8 byte, 64-bit); çağrıda RAM'den vtable okunup indirect call yapılır |
| `throw()` (imzada) | Eski C++98 exception specification | Çalışma zamanı sözleşmesi; ihlalde `std::terminate()` |
| `throw expr;` (fırlatma) | Çalışma zamanı | Stack unwinding + RAII destructor zinciri + eh_frame tabloları üzerinden arama |
| `: public std::exception` | Derleme zamanı (kalıtım) + çalışma zamanı (polymorphism) | Base subobject bellekte gömülü durur; vptr üzerinden dinamik çözümleme |
