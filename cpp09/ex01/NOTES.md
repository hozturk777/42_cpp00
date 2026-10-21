# cpp09 ex01 — RPN

## RPN ne demek?
- **R**everse **P**olish **N**otation = Ters Leh Gösterimi.
- **Polish (Leh):** Polonyalı mantıkçı Jan Łukasiewicz 1924'te operatörü **başa** yazan bir gösterim buldu → `+ 3 4`
- **Reverse (ters):** operatör **sona** yazılır → `3 4 +`
- 1950'lerde bilgisayarlar için geliştirildi; 1970'lerde HP hesap makineleriyle yaygınlaştı.

| Gösterim | Operatör nerede | Örnek |
|---|---|---|
| Infix (normal) | ortada | `3 + 4` |
| Prefix (Polish) | başta | `+ 3 4` |
| Postfix (RPN) | sonda | `3 4 +` |

## Neden RPN?
- Normal yazımda öncelik kuralları ve parantez gerekir:
  - `3 + 4 * 2` → önce çarpma: 11
  - `(3 + 4) * 2` → önce parantez: 14
- RPN'de ikisi farklı yazılır, parantez ve öncelik gerekmez:
  - `3 4 2 * +` → 11
  - `3 4 + 2 *` → 14
- İşlem sırası doğrudan yazılış sırasıdır.
- Bilgisayar için okuması çok kolaydır: soldan sağa tek geçiş yeter.

## RPN ile stack ilişkisi
- RPN stack için icat edilmedi; parantezsiz yazım için icat edildi.
- Ama RPN'i hesaplamanın en doğal yolu stack'tir.
- Sebep: operatör her zaman **en son gelen iki sayıya** uygulanır.
- "En son gelen" = stack'in üstü (LIFO: son giren ilk çıkar).
- Bu yüzden subject "container kullan" deyince doğru seçim `std::stack`.

## Stack ile hesaplama
İfade soldan sağa okunur:
- **Sayı** → stack'in üstüne koy (push).
- **Operatör** → üstten iki sayı al (pop), işlemi yap, sonucu geri koy.
- İfade bitince stack'te **tek sayı** kalmalı. Cevap odur.

Örnek: `"7 7 * 7 -"`

| Token | İşlem | Stack (alt → üst) |
|---|---|---|
| `7` | push | 7 |
| `7` | push | 7 7 |
| `*` | 7 × 7 = 49 | 49 |
| `7` | push | 49 7 |
| `-` | 49 − 7 = 42 | 42 |

Sonuç: `42`

## Sıra önemli
- Stack'ten ilk çıkan sayı **sağdaki** operand'dır.
- Yukarıdaki `-` adımında önce 7, sonra 49 çıktı.
- İşlem `49 - 7` olmalı, `7 - 49` değil.

```cpp
int b = top; pop;   // önce çıkan → sağdaki
int a = top; pop;   // sonra çıkan → soldaki
push(a - b);
```

## Container seçimi
- `std::map` ex00'da kullanıldı, artık yasak.
- RPN son giren ilk çıkar (LIFO) mantığıyla çalışır → `std::stack`.
- **Tuzak:** `std::stack` varsayılan olarak içeride `std::deque` kullanır.
- ex02'de deque kullanılacak, bu yüzden stack'e içeride `std::list` verilir:

```cpp
std::stack<int, std::list<int> > _stack;
```

- C++98'de `> >` arasında boşluk şart.

## Hata durumları
Hepsi stderr'e `Error` basar (subject bunu istiyor):

| Durum | Örnek |
|---|---|
| Argüman sayısı 1 değil | `./RPN` |
| Rakam ya da `+ - / *` dışı token | `"(1 + 1)"`, `"1 a +"`, `"1.5 2 +"` |
| 10 ya da daha büyük sayı | `"10 2 +"` |
| Operatörde 2'den az sayı | `"1 +"` |
| Sıfıra bölme | `"1 0 /"` |
| Sonda 1'den fazla sayı | `"1 2"` |

## Subject örnekleri
```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
```

## Kontrol sorusu
- `"8 2 /"` için stack'ten önce hangi sayı çıkar?
- İşlem `8 / 2` mi olmalı, `2 / 8` mi?
