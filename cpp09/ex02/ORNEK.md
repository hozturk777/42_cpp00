# Örnek: `./PmergeMe 5 7 3 4 6 1 2`

Bu dosya, algoritmanın bu girdi üzerinde **katman katman** ne yaptığını gösterir.
Tüm adımlar gerçek kod çalıştırılarak doğrulandı.

> Kod aslında sayıların **indekslerini** tutar. Burada okunması kolay olsun diye
> hep **değerleri** yazıyoruz.

---

## Büyük resim
Algoritma kendini çağırır. Her çağrı bir **kat** gibi düşünülebilir:

```
KAT 0:  5 7 3 4 6 1 2     (7 sayı)
          │  büyükleri aşağı gönder
          ▼
KAT 1:  7 4 6             (3 sayı)
          │  büyükleri aşağı gönder
          ▼
KAT 2:  7                 (1 sayı → zaten sıralı, geri dön)
```

Her kat iki iş yapar:
1. **İnerken:** sayıları ikişerli eşle, büyükleri bir alt kata gönder.
2. **Çıkarken:** alt kattan sıralı gelen büyüklerin arasına küçükleri yerleştir.

---

## KAT 0 — iniş (7 sayı)

**İkişerli eşle:**
```
5 7   3 4   6 1   2
───   ───   ───   ─
7>5   4>3   6>1   eşi yok
```

| Çift | Büyük | Küçük |
|---|---|---|
| 5, 7 | 7 | 5 |
| 3, 4 | 4 | 3 |
| 6, 1 | 6 | 1 |
| 2 | — | — (straggler) |

```
bigs      = 7 4 6
partner   : 7 → 5,  4 → 3,  6 → 1
straggler = 2
```
→ `7 4 6` sıralanmak üzere **KAT 1'e** gönderilir.

---

## KAT 1 — iniş (3 sayı: `7 4 6`)

**İkişerli eşle:**
```
7 4   6
───   ─
7>4   eşi yok
```
```
bigs      = 7
partner   : 7 → 4
straggler = 6
```
→ `7` **KAT 2'ye** gönderilir.

---

## KAT 2 (1 sayı: `7`)
Tek sayı zaten sıralıdır. Hiçbir şey yapmadan **geri döner**: `7`

---

## KAT 1 — çıkış

**Ana zinciri kur:** sıralı büyüklerin en küçüğünün eşini başa koy, arkasına büyükleri diz.
```
sıralı bigs = 7
7'nin eşi   = 4
chain       = 4 7
```

**Kimler eklenecek?**
```
pairCount  = 1   (1 çift vardı)
smallCount = 2   (4 + straggler 6)
```
4 zaten zincirde. Geriye sadece **straggler 6** kaldı.

**6'yı ekle:** büyüğü yok, tüm zincirde aranır: `4 7`
```
6 < 7 ?  evet  → sola git
6 < 4 ?  hayır → 4 ile 7 arasına
chain = 4 6 7
```

→ KAT 0'a **`4 6 7`** olarak döner.

---

## KAT 0 — çıkış

**Ana zinciri kur:**
```
sıralı bigs = 4 6 7
4'ün eşi    = 3
chain       = 3 4 6 7
```

**Kimler eklenecek?**
```
pairCount  = 3   (3 çift vardı)
smallCount = 4   (3, 5, 1 + straggler 2)
```

Küçükleri numaralayalım (sıralı büyüklere göre):

| Numara | Küçük | Büyüğü | Durum |
|---|---|---|---|
| 1. | 3 | 4 | zaten zincirde |
| 2. | 1 | 6 | eklenecek |
| 3. | 5 | 7 | eklenecek |
| 4. | 2 | yok (straggler) | eklenecek |

**Ekleme sırası (Jacobsthal):** önce **3, 2**, sonra **4**.

### 1. tur: 3. ve 2. küçük

**3. küçük = 5** → büyüğü 7, yalnızca 7'nin **soluna** bak: `3 4 6`
```
5 < 4 ?  hayır → sağa
5 < 6 ?  evet  → 4 ile 6 arasına
chain = 3 4 5 6 7
```

**2. küçük = 1** → büyüğü 6, yalnızca 6'nın **soluna** bak: `3 4 5`
```
1 < 4 ?  evet → sola
1 < 3 ?  evet → en başa
chain = 1 3 4 5 6 7
```

### 2. tur: 4. küçük

**4. küçük = 2 (straggler)** → büyüğü yok, **tüm zincire** bak: `1 3 4 5 6 7`
```
2 < 5 ?  evet  → sola
2 < 3 ?  evet  → sola
2 < 1 ?  hayır → 1 ile 3 arasına
chain = 1 2 3 4 5 6 7
```

---

## Sonuç
```
Before: 5 7 3 4 6 1 2
After:  1 2 3 4 5 6 7
```

## Kaç karşılaştırma yapıldı?
| Nerede | Sayı |
|---|---|
| KAT 0 eşleştirme (3 çift) | 3 |
| KAT 1 eşleştirme (1 çift) | 1 |
| KAT 1: 6'yı ekleme | 2 |
| KAT 0: 5'i ekleme | 2 |
| KAT 0: 1'i ekleme | 2 |
| KAT 0: 2'yi ekleme | 3 |
| **Toplam** | **13** |

7 sayı için Ford-Johnson'ın en kötü durumda yaptığı karşılaştırma sayısı da 13.
Yani bu girdi tam sınırda sıralandı.

---

## Kodda karşılıkları
| Burada | Kodda |
|---|---|
| büyükler | `bigs` |
| "7 → 5" (büyüğün eşi) | `partner[7] = 5` |
| eşi olmayan | `straggler` |
| ana zincir | `chain` |
| kaç çift | `pairCount` |
| kaç küçük (straggler dahil) | `smallCount` |
| "7'nin soluna bak" | `hi` = 7'nin zincirdeki yeri |
| "tüm zincire bak" | `hi = chain.size()` |
| "önce 3, 2 sonra 4" | `prev` / `curr` / `start` döngüsü |
