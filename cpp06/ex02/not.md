# dynamic_cast — Detaylı Sistemsel Not

## Ne yapar (ve ne YAPMAZ)
`dynamic_cast<T>(expr)`, `static_cast`'in aksine, dönüşümü **derleme
zamanında değil çalışma zamanında** doğrular. Sadece **polymorphic**
sınıflarda (en az bir `virtual` fonksiyonu olan) çalışır.

**Ne DEĞİLDİR:**
- **Ücretsiz değildir.** `static_cast`'in tersine, gerçek bir çalışma
  zamanı maliyeti var (RTTI tablosunda arama/lookup).
- **Her sınıfta çalışmaz.** Polymorphic olmayan (hiç virtual fonksiyonu
  olmayan) bir sınıfta `dynamic_cast` denemek **derleme hatası** verir.
- **Garanti değildir.** Pointer'da başarısızlıkta sessizce `NULL` döner,
  reference'ta ise **exception fırlatır** — `static_cast`'in aksine "her
  zaman bir şekilde çalışır" değildir.

## RTTI (Run-Time Type Information) — bunu mümkün kılan mekanizma
Bir sınıfın **en az bir virtual fonksiyonu** (`Base::~Base()` gibi) olması,
derleyicinin her nesneye **gizli bir vtable pointer** (vptr) eklemesini
sağlar. Bu vptr, sadece fonksiyon adreslerini değil, aynı zamanda **o
sınıfın RTTI bilgisini** (tip adı, hiyerarşi bilgisi) de işaret eder.

`dynamic_cast<A*>(p)` çalıştığında, donanım/kütüphane:
1. `p`'nin vptr'ından gerçek nesnenin **RTTI type_info** kaydına ulaşır.
2. Bu kaydı, hedef tipin (`A`) RTTI kaydıyla **karşılaştırır** (hiyerarşi
   boyunca yukarı/aşağı gezinerek, çoklu kalıtım varsa daha karmaşık bir
   algoritma çalışır).
3. Eşleşme varsa doğru pointer'ı (gerekirse adres düzeltmesiyle, çoklu
   kalıtımda "this pointer adjustment") döndürür, yoksa `NULL`.

Bu, `static_cast`'in aksine **gerçek bir çalışma zamanı algoritması** —
sıfır maliyetli değil, vtable lookup + tip karşılaştırma içerir.

## `ex02`'de tam olarak ne oluyor
```cpp
void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    ...
}
```
`generate()` çalışma zamanında rastgele `A`, `B` ya da `C` üretiyor,
`Base*` olarak döndürüyor — **derleme zamanında hangi tip olduğunu
bilmiyoruz**. `dynamic_cast`, tam da bu belirsizliği çözen araç: her
tip için sırayla dener, hangisi başarılı olursa gerçek tip odur.

## Pointer vs reference — iki farklı hata modeli
```cpp
dynamic_cast<A*>(p)   // başarısızsa: NULL döner (kontrol edilebilir)
dynamic_cast<A&>(p)   // başarısızsa: std::bad_cast FIRLATIR (NULL referans olamaz!)
```
Reference hiçbir zaman "geçersiz/boş" bir değer tutamaz — dil bunu garanti
eder. Bu yüzden `dynamic_cast<A&>` başarısız olduğunda dönecek "geçersiz"
bir referans **yoktur**, standardın tek çaresi exception fırlatmak.
`ex02`'de bunu `catch (...)` ile (tip adını `<typeinfo>`'dan almadan)
yakalıyoruz.

## static_cast'ten fark — neden burada dynamic_cast şart
```cpp
static_cast<A*>(basePtr);   // DERLENİR ama kontrolsüz — basePtr gerçekten
                             // bir A değilse, davranış UNDEFINED (UB)
dynamic_cast<A*>(basePtr);  // ÇALIŞMA ZAMANINDA kontrol eder, yanlışsa NULL
```
`static_cast`, base→derived downcast'e **izin verir ama doğrulamaz** —
derleyici "sen biliyorsundur" der. `generate()`'in döndürdüğü nesnenin
gerçek tipi **rastgele** olduğundan, `static_cast` kullanmak UB riski
taşırdı; `dynamic_cast` bu riski, RTTI kontrolüyle ortadan kaldırıyor.

## `<typeinfo>` yasağıyla ilişkisi
`dynamic_cast` bir **dil anahtar kelimesi** — RTTI verisini derleyici
zaten üretir, biz `<typeinfo>` header'ını **elle include etmeden** de
`dynamic_cast` kullanabiliriz. Yasak olan, `std::bad_cast`'i isimle
yakalamak ya da `typeid` kullanmak gibi, header'ı **açıkça** gerektiren
şeyler — biz bunları `catch (...)` ile (isimsiz yakalama) atlıyoruz.

## dynamic_cast vs diğer cast'ler
| Cast | Kontrol zamanı | Maliyet | Gereksinim |
|---|---|---|---|
| `static_cast` | derleme | sıfır (ya da gerçek dönüşüm maliyeti) | tanımlı ilişki |
| `dynamic_cast` | **çalışma zamanı** | vtable lookup + RTTI karşılaştırma | polymorphic sınıf (virtual fonksiyon şart) |
| `reinterpret_cast` | yok | sıfır | integral/pointer arası, kontrolsüz |
| `const_cast` | derleme | sıfır | sadece const/volatile |

## Neden `Base`'in destructor'ı `virtual` olmak ZORUNDA
`virtual` fonksiyon olmadan RTTI/vptr **hiç oluşmaz**, `dynamic_cast`
derleme hatası verir. Ayrıca `delete p` (bir `Base*` üzerinden) çağrıldığında,
`virtual` destructor olmazsa sadece `Base`'in yıkıcısı çalışır, türetilmiş
sınıfa ait kaynaklar (varsa) sızabilir — `ex02`'de bu ikisi (RTTI + doğru
destructor zinciri) aynı `virtual` anahtar kelimesine bağlı.
