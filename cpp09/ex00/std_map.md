# std::map

## Nedir?
- Anahtar → değer sözlüğü.
- Anahtarlar benzersizdir ve her zaman **sıralı** durur.
- Her eleman bir `pair`: `first` anahtar, `second` değer.

```cpp
std::map<std::string, double> m;
m["2012-01-11"] = 7.1;
m["2011-01-01"] = 0.3;   // içeride yine sıralı: 2011..., 2012...
```

## İçeride nasıl çalışır?
- İçeride bir **red-black tree** (kendini dengeleyen ikili arama ağacı) vardır.
- Her eleman heap'te ayrı bir düğümdür. `new`/`delete` işini map kendisi yapar.
- Soldaki düğümler küçük, sağdakiler büyüktür.
- Arama her adımda ağacın yarısını eler → **O(log n)**.
- Ağaç her eklemede kendini dengeler; zincire dönüşmez.
- Sıralama yalnızca `operator<` ile yapılır.
- `++it` bir sonraki büyük elemana gider; bu yüzden dolaşma sıralıdır.

```
           2011-01-07
          /          \
   2011-01-01      2012-01-11
```

## Komutlar
| Komut | Ne yapar |
|---|---|
| `m[k] = v` | Ekler ya da üzerine yazar |
| `m.insert(std::make_pair(k, v))` | Ekler; anahtar varsa dokunmaz |
| `m.find(k)` | Iterator döner; yoksa `end()` |
| `m.count(k)` | 0 ya da 1 |
| `m.lower_bound(k)` | ≥ k olan ilk eleman |
| `m.upper_bound(k)` | > k olan ilk eleman |
| `m.erase(k)` | Siler |
| `m.size()` / `m.empty()` | Boyut / boş mu |
| `m.begin()` / `m.end()` | İlk eleman / sonun bir ötesi |

```cpp
for (std::map<std::string, double>::const_iterator it = m.begin(); it != m.end(); ++it)
    std::cout << it->first << " " << it->second << std::endl;
```

## Tuzaklar
- `m[k]` ile **okumak**, anahtar yoksa onu ekler. Okumak için `find` kullan.
- `const` map'te `[]` çalışmaz.
- `begin()`'den `--it` yapmak ve `end()`'i okumak tanımsız davranıştır.
- `at()` ve `unordered_map` C++11'dir; 42'de yasak.

## Diğer container'lardan farkı
| | vector | list | map |
|---|---|---|---|
| Yapı | Ardışık dizi | Bağlı liste | Ağaç |
| İndeksle erişim | O(1) | Yok | Yok |
| Değer / anahtar arama | O(n) | O(n) | **O(log n)** |
| Her zaman sıralı | Hayır | Hayır | **Evet** |

- `set`: map gibi ama yalnızca anahtar tutar.
- `multimap`: aynı anahtar birden çok kez olabilir.

## ex00'da neden map?
- Tarih → kur eşlemesi = anahtar → değer.
- Tarihler sıralı olmalı.
- En yakın alt tarih: `upper_bound(date)` ve ardından `--it`.
