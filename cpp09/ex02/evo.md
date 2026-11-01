# Jacobsthal — evo notu

Örnek girdi: `5 7 3 4 6 1 2`

---

## Kim ne yapıyor?

| iş | kim yapıyor | kodda |
|---|---|---|
| Eşleştirme | `for (i += 2)` döngüsü | `partner[a] = b` |
| Büyükleri sıralama | recursive | `fordJohnson(bigs, values)` |
| Küçükleri **hangi sırayla** sokacağız | **Jacobsthal** | `prev` / `curr` / `start` |
| Küçüğü **nereye** sokacağız | binary search | `lo` / `hi` / `mid` |
| Arama yerini kısaltma | eş kuralı | `while (chain[hi] != a)` |

Jacobsthal kimseyi eşlemez ve sıralamaz. **Sadece sıra söyler.**

---

## Deneme ne demek?

Bir deneme = bir karşılaştırma:
```cpp
if (values[b] < values[chain[mid]])
```

| arama yerindeki sayı | en fazla deneme |
|---|---|
| 1 | 1 |
| 2–3 | 2 |
| 4–7 | 3 |
| 8–15 | 4 |

3'ten 4'e çıkınca 1 deneme fazla gider.
Hedef: arama yerini **3, 7, 15** sınırında tutmak.

---

## Örnekte durum

Zincir hazır:
```
3  4  6  7
```

Büyüklere numara ver, eşlerini yaz:
```
bigs (sıralı):  4    6    7
numara:         1.   2.   3.
eşi:            3    1    5     + straggler 2 → 4.
```

- 1. eş (3) zaten en başta, karşılaştırmasız.
- Sokulacaklar: 1, 5, 2

---

## İki kural

### 1. Eş kuralı — kendi eşinin soluna bak
```
5'in eşi 7 → 5 < 7 kesin → sadece 7'nin solu
1'in eşi 6 → 1 < 6 kesin → sadece 6'nın solu
2 straggler → eşi yok   → tüm zincir
```

### 2. Jacobsthal — hangi sırayla?
Sayılar: `1  3  5  11  21  43 ...`  (`next = curr + 2 * prev`)

Her grupta **büyük sayıdan geri say**, öncekine gelince dur:

| prev | curr | sıra |
|---|---|---|
| 1 | 3 | 3. 2. |
| 3 | 5 | 5. 4. |
| 5 | 11 | 11. 10. … 6. |
| 11 | 21 | 21. … 12. |

Olmayan numara atlanır.

Örnekte 4 küçük var → sıra `3. 2. 4.` → **5, 1, 2**

---

## Neden önce 5?

**Önce 1 sokulsaydı:**
```
1 → 6'nın solu:  3 4           → 2 deneme
zincir: 1 3 4 6 7
5 → 7'nin solu:  1 3 4 6       → 4 sayı → 3 deneme  ❌
```

**Önce 5 (Jacobsthal):**
```
5 → 7'nin solu:  3 4 6         → 3 sayı → 2 deneme  ✅
zincir: 3 4 5 6 7
1 → 6'nın solu:  3 4 5         → 3 sayı → 2 deneme  ✅
zincir: 1 3 4 5 6 7
2 → tüm zincir:  1 3 4 5 6 7   → 6 sayı → 3 deneme
zincir: 1 2 3 4 5 6 7
```

Sağdaki önce girince soldakinin arama yerini uzatmaz.

---

## Neden sadece "en sağdan başla" değil?

11 küçük olsa:
```
sadece sağdan:  11 10 9 8 7 6 5 4 3 2
Jacobsthal:     3 2 | 5 4 | 11 10 9 8 7 6
```

Her grupta deneme 1 artar, ama sınır aşılmaz:

| grup | sıra | her biri en fazla |
|---|---|---|
| 1 | 3. 2. | 2 deneme |
| 2 | 5. 4. | 3 deneme |
| 3 | 11. … 6. | 4 deneme |
| 4 | 21. … 12. | 5 deneme |

---

## Kodda

```cpp
size_t prev = 1;
size_t curr = 3;
while (prev < smallCount)
{
    size_t start = (curr < smallCount) ? curr : smallCount; // olmayan numarayı atla
    for (size_t i = start; i > prev; --i)                    // grubun sağından sola
    {
        if (i == pairCount + 1)        // straggler
            hi = chain.size();         // tüm zincir
        else
            while (chain[hi] != a)     // eş kuralı: a'nın soluna kadar
                ++hi;
        // binary search → insert
    }
    size_t next = curr + 2 * prev;     // 3 → 5 → 11 → 21
    prev = curr;
    curr = next;
}
```

---

## Evo cümlesi

> Jacobsthal, küçük elemanların zincire **ekleme sırasını** belirler.
> Grupları 3, 5, 11, 21… sınırlarına göre ayırır, her grubu sağdan sola ekler.
> Böylece her binary search aralığı 3, 7, 15… uzunluğunu geçmez ve
> karşılaştırma sayısı en aza iner.
> Ayrıca her küçük, sadece kendi eşinin soluna kadar aranır.
