## OOP (Object-Oriented Programming) - Nesne Yönelimli Programlama

**Temel fikir:** Veriyi (özellikler) ve o veri üzerinde işlem yapan fonksiyonları (metodlar) tek bir birim (nesne/object) içinde birleştirmek.

### 4 Temel Prensip

**1. Encapsulation (Kapsülleme/Veri Gizleme)**
- Veriyi dışarıdan doğrudan erişime kapatıp, kontrollü erişim sağlama (getter/setter, private/public/protected)
- Amaç: veri bütünlüğünü korumak, iç implementasyonu gizlemek

**2. Inheritance (Kalıtım)**
- Bir sınıfın (child/derived class) başka bir sınıftan (parent/base class) özellik ve metod devralması
- Kod tekrarını azaltır, "is-a" ilişkisi kurar (örn: `Dog` bir `Animal`'dır)

**3. Polymorphism (Çok Biçimlilik)**
- Aynı arayüzün (interface) farklı sınıflarda farklı davranması
- İki türü: **compile-time (static)** — function overloading; **runtime (dynamic)** — virtual functions ile late binding

**4. Abstraction (Soyutlama)**
- Karmaşık implementasyon detaylarını gizleyip, sadece gerekli/temel özellikleri dışarıya sunma
- Abstract class / interface ile gerçekleştirilir

### Temel Kavramlar
- **Class:** Nesnenin şablonu/kalıbı (blueprint)
- **Object:** Class'ın somut örneği (instance)
- **Constructor/Destructor:** Nesne yaratılırken/yok edilirken çalışan özel metodlar

### Neden Kullanılır?
- Kod yeniden kullanılabilirliği (reusability)
- Bakımı kolay, modüler yapı
- Gerçek dünya modellemesine daha yakın (nesneler = varlıklar)

---

## Abstract Class

**Tanım:** Kendisinden doğrudan **nesne (instance) oluşturulamayan**, ama **inherit edilebilen** (miras alınabilen) sınıf.

### C++'ta bir class'ı abstract yapan şey
İçinde en az bir tane **pure virtual function** olması gerekir:

```cpp
class AbstractClass {
public:
    virtual void doSomething() = 0;  // pure virtual → = 0
};
```

- `= 0` ifadesi o fonksiyonu **pure virtual** yapar, bu da class'ı otomatik olarak abstract hale getirir

### Neden Kullanılır?
- **Interface/sözleşme (contract)** tanımlamak için: "Bu sınıftan türeyen her class, şu metodu mutlaka implement etmek zorunda"
- Ortak bir arayüz (polymorphism) sağlar ama implementasyon detayını türeyen sınıflara bırakır

### Örnek

```cpp
class Shape {  // abstract
public:
    virtual double area() const = 0;  // her şekil bunu implement etmeli
};

class Circle : public Shape {
public:
    double area() const override { return 3.14 * r * r; }  // artık concrete
};
```

- `Shape s;` → **hata**, obje oluşturulamaz
- `Circle c;` → **çalışır**, çünkü pure virtual metodu implement etti (artık concrete/somut class)

**Neden instance oluşturulamıyor?** Çünkü eksik/tanımsız bir davranış (implementasyonu olmayan bir fonksiyon) içeriyor, derleyici bu yüzden izin vermiyor.