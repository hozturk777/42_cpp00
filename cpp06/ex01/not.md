# reinterpret_cast — Detaylı Sistemsel Not

## Ne yapar (ve ne YAPMAZ)
`reinterpret_cast<T>(expr)`, bir bit kalıbını **hiç değiştirmeden**, sadece
derleyiciye "bu bit kalıbını bundan sonra `T` tipiymiş gibi ele al" der.

**Ne DEĞİLDİR — kritik ayrım:**
- **Değer dönüşümü yapmaz.** `static_cast<double>(int)` gibi gerçek bir
  hesaplama (FPU talimatı, IEEE 754'e çevirme) **yoktur**. `reinterpret_cast`
  sonrası bit kalıbı, öncesiyle **birebir aynıdır**.
- **Tip güvenliği sağlamaz.** Derleyici, hedef tipin kaynak tiple "mantıklı"
  bir ilişkisi olup olmadığını **kontrol etmez** — neredeyse her pointer/
  integer kombinasyonuna izin verir.
- **Taşınabilir (portable) değildir.** Sonucun davranışı **implementation-
  defined**'dır — standart, `reinterpret_cast`'in kesin sonucunu garanti
  etmez, sadece "derleyiciye göre tanımlı" der.

## `ex01`'de tam olarak ne oluyor
```cpp
uintptr_t Serializer::serialize(Data *ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}
```
`ptr`, bir bellek adresi tutan 8 bytelık (64-bit sistemde) bir pointer.
`reinterpret_cast`, bu adresin **bit kalıbını aynen kopyalayıp**,
`uintptr_t` (8 byte'lık unsigned integer) olarak yeniden etiketliyor —
hiçbir hesaplama, hiçbir dönüştürme yok. Adres `0x16f602ba0` ise, sonuç
`uintptr_t` değeri de tam olarak `0x16f602ba0` (ondalık: `6163540896`).

## static_cast'ten fark — neden orada değil burada kullanıyoruz
`static_cast`, derleyicinin **tanımlı bir dönüşüm ilişkisi bildiği** durumlar
için var (int↔float, base↔derived class). Pointer ile integer arasında böyle
"matematiksel" bir ilişki **yok** — 64-bit bir adres, 64-bit bir sayı gibi
görünse de, derleyici bunların "aynı kavramın iki temsili" olduğunu bilemez.
Bu yüzden `static_cast<uintptr_t>(ptr)` yazmaya çalışsan **derleme hatası**
alırsın — `reinterpret_cast` bu kısıtlamayı bilerek aşmak için var.

## Round-trip garantisi — standart NE ZAMAN güvence veriyor
C++ standardı şunu garanti eder: bir pointer'ı `reinterpret_cast` ile bir
integer'a çevirip, **hiç değiştirmeden**, aynı integer'ı tekrar **aynı
pointer tipine** `reinterpret_cast` edersen, orijinal pointer'la eşit bir
değer elde edersin.

```cpp
uintptr_t raw = serialize(&original);   // pointer → integer
Data *restored = deserialize(raw);       // integer → pointer (AYNI değer)
// restored == &original  garantili
```

**Garanti burada biter:** `raw + 1` gibi aritmetik yaparsan (integer'ı
değiştirirsen), sonucu tekrar pointer'a çevirmek **undefined behavior**
olur — çünkü artık "orijinal adresin bir kaydırılmışı" anlamlı bir pointer
olmayabilir (hizalama, geçerli bellek bölgesi garantisi yok).

## Donanım seviyesinde ne oluyor
`reinterpret_cast<uintptr_t>(ptr)`'in ürettiği makine kodu genelde
**hiçbir talimat üretmez** — pointer zaten bir register'da 64-bit bir sayı
olarak duruyor, `uintptr_t`'ye "cast" etmek sadece derleyicinin **tip
kontrolünü** o değişkeni artık integer aritmetiğiyle kullanmaya izin
vermesi anlamına gelir. Çalışma zamanında sıfır maliyetli (`static_cast`
gibi, ama onun aksine hiçbir dönüşüm hesaplaması da yok).

## reinterpret_cast vs diğer cast'ler
| Cast | Kontrol | Bit kalıbı değişir mi | Kullanım alanı |
|---|---|---|---|
| `static_cast` | derleme zamanı, tanımlı ilişki şart | **evet** (gerçek dönüşüm) | int↔float, ilişkili class hiyerarşisi |
| `reinterpret_cast` | yok, hemen hemen her şeye izin verir | **hayır** (aynen kopyalanır) | pointer↔integer, alakasız pointer tipleri |
| `dynamic_cast` | çalışma zamanı, RTTI | hayır (sadece kontrol eder) | polymorphic hiyerarşide gerçek tip |
| `const_cast` | derleme zamanı | hayır | sadece const/volatile ekle/çıkar |

## Tehlikesi — neden dikkatli kullanılmalı
`reinterpret_cast`, tip sisteminin **arka kapısı**. Alakasız iki pointer
tipi arasında (`int*` → `Data*` gibi) kullanılırsa, **strict aliasing**
kuralını çiğneyip derleyicinin optimizasyon varsayımlarını bozabilir, UB
üretebilir. Bizim `ex01`'deki kullanımımız güvenli çünkü:
1. Sadece pointer↔integer arası (aliasing sorunu yok, çünkü integer bir
   "tip" olarak bellek erişimi anlamına gelmiyor).
2. Round-trip'i standartça garantili tek yol (integer'ı **hiç
   değiştirmeden** geri pointer'a çeviriyoruz).
