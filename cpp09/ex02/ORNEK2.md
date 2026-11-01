# Kod izi: `./PmergeMe 5 3 1 4 7 8 6`

Gösterim: `indeks(değer)` → `0(5)` = values[0] = 5

```
values:  [0]=5  [1]=3  [2]=1  [3]=4  [4]=7  [5]=8  [6]=6
```

---

## sortByIndex

```
idx = [0 1 2 3 4 5 6]
→ fordJohnson(idx, values)      // LEVEL 0
```

---

## LEVEL 0 — giriş

```
idx = [0 1 2 3 4 5 6]   değerler: [5 3 1 4 7 8 6]
n   = 7
n < 2 ? hayır
```

### Eşleştirme döngüsü (`for i += 2`)

| i | a = idx[i] | b = idx[i+1] | values[a] < values[b] ? | swap | bigs | partner |
|---|---|---|---|---|---|---|
| 0 | 0(5) | 1(3) | 5 < 3 hayır | yok | [0] | partner[0] = 1 |
| 2 | 2(1) | 3(4) | 1 < 4 evet | a=3, b=2 | [0 3] | partner[3] = 2 |
| 4 | 4(7) | 5(8) | 7 < 8 evet | a=5, b=4 | [0 3 5] | partner[5] = 4 |
| 6 | — | — | 6+1 < 7 hayır → döngü biter | | | |

```
bigs         = [0 3 5]        değerler: [5 4 8]
partner      : 0→1   3→2   5→4      (5→3, 4→1, 8→7)
hasStraggler = true   (7 % 2 == 1)
straggler    = idx[6] = 6(6)
→ fordJohnson(bigs, values)     // LEVEL 1
```

---

## LEVEL 1 — giriş

```
idx = [0 3 5]   değerler: [5 4 8]      (LEVEL 0'ın bigs'i)
n   = 3
n < 2 ? hayır
```

### Eşleştirme döngüsü

| i | a | b | values[a] < values[b] ? | swap | bigs | partner |
|---|---|---|---|---|---|---|
| 0 | 0(5) | 3(4) | 5 < 4 hayır | yok | [0] | partner[0] = 3 |
| 2 | — | — | 2+1 < 3 hayır → döngü biter | | | |

```
bigs         = [0]            değerler: [5]
partner      : 0→3            (5→4)
hasStraggler = true   (3 % 2 == 1)
straggler    = idx[2] = 5(8)
→ fordJohnson(bigs, values)     // LEVEL 2
```

---

## LEVEL 2

```
idx = [0]   değerler: [5]
n   = 1
n < 2 ? evet → return       (idx değişmedi: [0])
```

---

## LEVEL 1 — dönüş

```
bigs = [0]   değerler: [5]
```

### Ana zincir

```
chain.push_back(partner[bigs[0]])  → partner[0] = 3   → chain = [3]
chain.insert(end, bigs)                               → chain = [3 0]
chain = [3 0]   değerler: [4 5]
```

```
pairCount  = 1
smallCount = 2
prev = 1   curr = 3
```

### while — tur 1

```
prev < smallCount ? 1 < 2 evet
start = (3 < 2) ? 3 : 2 → 2
for i = 2 .. (i > 1)
```

**i = 2**

```
i == pairCount + 1 ? 2 == 2 evet → straggler
b  = 5(8)
hi = chain.size() = 2
lo = 0
```

| lo | hi | mid | chain[mid] | values[b] < ? | sonuç |
|---|---|---|---|---|---|
| 0 | 2 | 1 | 0(5) | 8 < 5 hayır | lo = 2 |
| 2 | 2 | — | — | lo < hi hayır → biter | |

```
chain.insert(begin + 2, 5)
chain = [3 0 5]   değerler: [4 5 8]
```

```
next = 3 + 2*1 = 5
prev = 3   curr = 5
prev < smallCount ? 3 < 2 hayır → while biter
```

```
idx = chain → [3 0 5]
→ LEVEL 0'ın bigs'i artık [3 0 5]   değerler: [4 5 8]
```

---

## LEVEL 0 — dönüş

```
bigs = [3 0 5]   değerler: [4 5 8]
partner (LEVEL 0'ınki): 3→2   0→1   5→4
straggler = 6(6)
```

### Ana zincir

```
chain.push_back(partner[bigs[0]])  → partner[3] = 2   → chain = [2]
chain.insert(end, bigs)                               → chain = [2 3 0 5]
chain = [2 3 0 5]   değerler: [1 4 5 8]
```

```
pairCount  = 3
smallCount = 4
prev = 1   curr = 3
```

| küçük no | bigs[i-1] (a) | partner[a] (b) |
|---|---|---|
| 1 | 3(4) | 2(1) → zincirde zaten |
| 2 | 0(5) | 1(3) |
| 3 | 5(8) | 4(7) |
| 4 | — | straggler 6(6) |

### while — tur 1

```
prev < smallCount ? 1 < 4 evet
start = (3 < 4) ? 3 : 4 → 3
for i = 3, 2
```

**i = 3**

```
i == 4 ? hayır → else
a = bigs[2] = 5(8)
b = partner[5] = 4(7)
hi: chain[hi] != 5 → hi = 3      chain = [2 3 0 5]
lo = 0
```

| lo | hi | mid | chain[mid] | values[b] < ? | sonuç |
|---|---|---|---|---|---|
| 0 | 3 | 1 | 3(4) | 7 < 4 hayır | lo = 2 |
| 2 | 3 | 2 | 0(5) | 7 < 5 hayır | lo = 3 |
| 3 | 3 | — | — | biter | |

```
chain.insert(begin + 3, 4)
chain = [2 3 0 4 5]   değerler: [1 4 5 7 8]
```

**i = 2**

```
i == 4 ? hayır → else
a = bigs[1] = 0(5)
b = partner[0] = 1(3)
hi: chain[hi] != 0 → hi = 2      chain = [2 3 0 4 5]
lo = 0
```

| lo | hi | mid | chain[mid] | values[b] < ? | sonuç |
|---|---|---|---|---|---|
| 0 | 2 | 1 | 3(4) | 3 < 4 evet | hi = 1 |
| 0 | 1 | 0 | 2(1) | 3 < 1 hayır | lo = 1 |
| 1 | 1 | — | — | biter | |

```
chain.insert(begin + 1, 1)
chain = [2 1 3 0 4 5]   değerler: [1 3 4 5 7 8]
```

```
next = 3 + 2*1 = 5
prev = 3   curr = 5
```

### while — tur 2

```
prev < smallCount ? 3 < 4 evet
start = (5 < 4) ? 5 : 4 → 4
for i = 4 .. (i > 3)
```

**i = 4**

```
i == 4 ? evet → straggler
b  = 6(6)
hi = chain.size() = 6
lo = 0
```

| lo | hi | mid | chain[mid] | values[b] < ? | sonuç |
|---|---|---|---|---|---|
| 0 | 6 | 3 | 0(5) | 6 < 5 hayır | lo = 4 |
| 4 | 6 | 5 | 5(8) | 6 < 8 evet | hi = 5 |
| 4 | 5 | 4 | 4(7) | 6 < 7 evet | hi = 4 |
| 4 | 4 | — | — | biter | |

```
chain.insert(begin + 4, 6)
chain = [2 1 3 0 6 4 5]   değerler: [1 3 4 5 6 7 8]
```

```
next = 5 + 2*3 = 11
prev = 5   curr = 11
prev < smallCount ? 5 < 4 hayır → while biter
```

```
idx = chain → [2 1 3 0 6 4 5]
→ sortByIndex'in idx'i artık [2 1 3 0 6 4 5]
```

---

## sortByIndex — dönüş

| i | idx[i] | values[idx[i]] | sorted |
|---|---|---|---|
| 0 | 2 | 1 | [1] |
| 1 | 1 | 3 | [1 3] |
| 2 | 3 | 4 | [1 3 4] |
| 3 | 0 | 5 | [1 3 4 5] |
| 4 | 6 | 6 | [1 3 4 5 6] |
| 5 | 4 | 7 | [1 3 4 5 6 7] |
| 6 | 5 | 8 | [1 3 4 5 6 7 8] |

```
values = sorted → [1 3 4 5 6 7 8]
```

---

## Çıktı

```
Before: 5 3 1 4 7 8 6
After: 1 3 4 5 6 7 8
```

## Karşılaştırma sayısı

| yer | adet |
|---|---|
| LEVEL 0 eşleştirme | 3 |
| LEVEL 1 eşleştirme | 1 |
| LEVEL 1 straggler 8 | 1 |
| LEVEL 0 b=7 | 2 |
| LEVEL 0 b=3 | 2 |
| LEVEL 0 straggler 6 | 3 |
| **toplam** | **12** |
