# std::vector — Özet (C++98)

## Nedir?

`std::vector<T>`, **boyutu çalışma zamanında büyüyüp küçülebilen dinamik bir dizidir**. Bir class template'tir:
cpp07'de yazdığın `Array<T>`'nin standart ve gelişmiş hâli.

```cpp
#include <vector>

std::vector<int> v;      // boş, int tutan vector
v.push_back(10);         // [10]
v.push_back(20);         // [10, 20]
```

## Bellekte nasıl durur?

- Elemanlar **yan yana (contiguous)** durur, tıpkı normal bir dizi gibi → `v[i]` ile anında erişim (O(1)).
- İçeride 3 bilgi tutulur: başlangıç pointer'ı, **size** (kaç eleman var) ve **capacity** (kaç elemanlık yer ayrılmış).
- Yer dolunca vector **daha büyük yeni bir bellek ayırır** (genelde 2 katı), elemanları oraya kopyalar ve eskisini siler.

```
size = 3, capacity = 4:   [10][20][30][  ]
push_back(40)          →  [10][20][30][40]              (yer vardı)
push_back(50)          →  [10][20][30][40][50][  ][  ][  ]   (yeni bellek, kopyala, eskiyi sil)
```

> ⚠️ Yeniden ayırma olduğunda eski **pointer, referans ve iterator'ler geçersiz olur**.

## Oluşturma

```cpp
std::vector<int> a;              // boş
std::vector<int> b(5);           // 5 eleman, hepsi 0       → [0, 0, 0, 0, 0]
std::vector<int> c(3, 7);        // 3 eleman, hepsi 7       → [7, 7, 7]
std::vector<int> d(c);           // c'nin kopyası (deep copy)

int arr[] = {1, 2, 3};
std::vector<int> e(arr, arr + 3);   // diziden oluştur     → [1, 2, 3]
```

## Temel komutlar

| Komut | Ne yapar | Örnek (`v = [1, 2, 3]`) |
|---|---|---|
| `push_back(x)` | Sona ekler | `v.push_back(4)` → `[1, 2, 3, 4]` |
| `pop_back()` | Sondakini siler | `v.pop_back()` → `[1, 2]` |
| `size()` | Eleman sayısı | `3` |
| `empty()` | Boş mu? | `false` |
| `capacity()` | Ayrılmış yer | `≥ 3` |
| `v[i]` | Erişim, **sınır kontrolü yok** | `v[0]` → `1`, `v[10]` → UB ❌ |
| `at(i)` | Erişim, **sınır kontrolü var** | `v.at(10)` → `std::out_of_range` fırlatır |
| `front()` / `back()` | İlk / son eleman | `1` / `3` |
| `clear()` | Hepsini siler (size = 0) | `[]` |
| `resize(n)` | Boyutu n yapar | `v.resize(5)` → `[1, 2, 3, 0, 0]` |
| `reserve(n)` | Sadece capacity'yi büyütür, size değişmez | `v.reserve(100)` |

## Iterator ile gezme (C++98 usulü)

Iterator, container içinde gezmeye yarayan **akıllı pointer**'dır.

```cpp
std::vector<int> v(arr, arr + 3);

for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << " ";                // 1 2 3
```

```
 v.begin()                  v.end()
    ↓                          ↓
  [ 1 ][ 2 ][ 3 ]  (son elemandan SONRAKİ yer — içi boş, dereference edilmez)
```

- Const bir vector'de `std::vector<int>::const_iterator` kullanılır.
- `auto` ve range-for (`for (int x : v)`) C++11'dir, **kullanamazsın**.

## Ortaya ekleme / silme

```cpp
v.insert(v.begin() + 1, 99);   // [1, 99, 2, 3]  — araya ekler, sağdakiler kayar (yavaş, O(n))
v.erase(v.begin());            // [99, 2, 3]     — siler, sağdakiler sola kayar (yavaş, O(n))
```

## `<algorithm>` ile kullanım (cpp08'de lazım)

```cpp
#include <algorithm>

std::vector<int>::iterator it = std::find(v.begin(), v.end(), 2);
if (it != v.end())
    std::cout << "bulundu: " << *it << std::endl;
else
    std::cout << "yok" << std::endl;           // bulamazsa end() döner

std::sort(v.begin(), v.end());                  // küçükten büyüğe sıralar
```

## Hız özeti

| İşlem | Maliyet |
|---|---|
| `v[i]`, `at(i)` | O(1) — anında |
| `push_back` / `pop_back` | O(1) (ortalama; yeniden ayırmada O(n)) |
| `insert` / `erase` (ortada) | O(n) — elemanlar kayar |
| `std::find` | O(n) — tek tek arar |

## vector vs list (tek satırda)

- **vector:** Yan yana bellek → hızlı erişim (`v[i]`), ortaya ekleme yavaş.
- **list:** Bağlı liste → `l[i]` yok, ama ortaya ekleme/silme hızlı (O(1)).
