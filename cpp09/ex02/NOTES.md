# cpp09 ex02 — PmergeMe (Ford-Johnson)

## Görev
- Program adı `PmergeMe`.
- Argüman olarak pozitif tam sayılar alır: `./PmergeMe 3 5 9 7 4`
- **Ford-Johnson** (merge-insertion) algoritmasıyla sıralar.
- İki farklı container kullanır, algoritmayı her biri için ayrı yazar.
- En az 3000 sayıyı işleyebilmeli; tekrar eden sayılar olabilir.
- Hata → stderr'e `Error`.

## Algoritmanın amacı
- Amaç **en az karşılaştırmayla** sıralamak.
- Hız (süre) değil, **karşılaştırma sayısı** optimize edilir.
- Knuth, *The Art of Computer Programming*, Vol. 3, s. 184.
- Teorik alt sınıra çok yakındır.
  - Örnek: 5 sayı için en az 7 karşılaştırma gerekir; Ford-Johnson 7'de bitirir.

## Ana fikir
1. Sayıları **ikişerli eşle**, her çiftte büyüğü ve küçüğü ayır.
2. **Büyükleri** aynı algoritmayla (recursive) sırala.
3. Sıralı büyükler bir **ana zincir** (main chain) oluşturur.
4. **Küçükleri** ana zincire **binary search** ile tek tek yerleştir.
5. Yerleştirme sırası **Jacobsthal sayılarına** göre belirlenir.

## Adım 1: Eşleştirme
- Sayılar ikişerli gruplanır, her çift bir kez karşılaştırılır.
- Büyük olana `a`, küçük olana `b` denir.
- Sayı adedi tekse son sayı eşsiz kalır (**straggler**); en sona saklanır.

```
8 2 | 6 4 | 7 1 | 5 3
(8,2) (6,4) (7,1) (5,3)     → a: 8 6 7 5   b: 2 4 1 3
```

## Adım 2: Büyükleri sırala (recursive)
- Yalnızca `a`'lar aynı algoritmayla sıralanır.
- Her `b` kendi `a`'sına bağlı kalır; `a` yer değiştirirse `b` de onunla gider.
- Burada `std::sort` kullanmak **yasak** sayılır; algoritma kendini çağırmalı.

```
a sıralı:  5   6   7   8
bağlı b:   3   4   1   2
isim:      a1  a2  a3  a4   /   b1  b2  b3  b4
```

## Adım 3: Ana zincir
- Sıralı `a`'lar ana zinciri oluşturur.
- `b1` < `a1` ve `a1` en küçük `a` → `b1` karşılaştırmasız en başa konur.

```
ana zincir: [b1 a1 a2 a3 a4] = [3 5 6 7 8]
bekleyenler (pend): b2=4, b3=1, b4=2
```

## Adım 4: Binary insertion
- Her `b` ana zincire binary search ile eklenir.
- **Kritik bilgi:** `bi` < `ai`. Yani `bi` yalnızca `ai`'nin **solunda** aranır.
- Arama aralığı küçük kaldığı için karşılaştırma az olur.

```
b3=1 → a3=7'nin solunda ara: [3 5 6]        → [1 3 5 6 7 8]
b2=4 → a2=6'nın solunda ara: [1 3 5]        → [1 3 4 5 6 7 8]
b4=2 → a4=8'in solunda ara:  [1 3 4 5 6 7]  → [1 2 3 4 5 6 7 8]
```

- En sonda straggler varsa tüm zincirde aranarak eklenir.

## Adım 5: Jacobsthal sırası
- `b`'ler 2, 3, 4… diye sırayla eklenmez.
- Jacobsthal sayıları: `J(n) = J(n-1) + 2·J(n-2)`
  - 0, 1, 1, **3, 5, 11, 21, 43, 85** …
- Ekleme sırası: her Jacobsthal sayısından **geriye** doğru, bir öncekine kadar.

| Grup | Eklenen sıra |
|---|---|
| 1 | b3, b2 |
| 2 | b5, b4 |
| 3 | b11, b10, … , b6 |
| 4 | b21, b20, … , b12 |

- Var olmayan indeksler atlanır (4 `b` varsa: b3, b2, b4).

## Neden Jacobsthal?
- Binary search `2^k − 1` elemanlı bir aralıkta en fazla `k` karşılaştırma yapar.
- Örnek: 3 eleman → 2 karşılaştırma, 7 eleman → 3 karşılaştırma.
- Jacobsthal sırası, her `b`'nin arama aralığını tam `2^k − 1`'in altında tutar.
- Örnek: `b3` eklenirken aralık `[b1 a1 a2]` = 3 eleman → 2 karşılaştırma.
- Sonra `b2` eklenir; aralık `[b1 a1]` + belki `b3` = en fazla 3 → yine 2 karşılaştırma.
- Ters sırayla eklenseydi aralıklar büyür, karşılaştırma artardı.

## Küçük örnek (subject): `3 5 9 7 4`
```
çiftler: (5,3) (9,7)   straggler: 4
a sıralı: 5 9   →   b1=3, b2=7
ana zincir: [3 5 9]
b2=7 → 9'un solunda ara [3 5]   → [3 5 7 9]
straggler 4 → tüm zincirde ara  → [3 4 5 7 9]
```

## Container seçimi
- `map`, `stack`, `list` önceki exercise'larda kullanıldı → yasak.
- `std::vector` ve `std::deque`:
  - İkisi de indeksle erişim verir (`v[i]`) → binary search için gerekli.
  - İkisi de ortaya eleman ekleyebilir (`insert`).
- Subject: algoritmayı her container için **ayrı** yaz, generic template kullanma.

## Çıktı formatı
```
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 12.00000 us
Time to process a range of 5 elements with std::deque  : 15.00000 us
```
- Süre: hem sıralama hem **veri yönetimi** (parse + container'a doldurma) dahil.
- Hassasiyet iki container arasındaki farkı göstermeli (mikrosaniye).

## Hata durumları
| Girdi | Sonuç |
|---|---|
| Argüman yok | `Error` |
| Negatif: `-1` | `Error` |
| Sayı değil: `abc`, `1.5`, `+` | `Error` |
| `int` sınırını aşan sayı | `Error` |
| Tekrar eden sayı: `3 3 1` | **Geçerli**, sıralanır |

## Sık yapılan hatalar
- Büyükleri `std::sort` ile sıralamak → Ford-Johnson değil.
- Jacobsthal sırası yerine `b`'leri sırayla eklemek.
- `bi`'yi tüm zincirde aramak (`ai` sınırını kullanmamak).
- Recursive sıralamadan sonra hangi `b`'nin hangi `a`'ya ait olduğunu kaybetmek.
- Süreyi yalnızca sıralama için ölçmek.
