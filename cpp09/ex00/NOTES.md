# cpp09 ex00 — Bitcoin Exchange

## Ne yapıyor?
- Program adı `btc`.
- Bir tarih ve bir bitcoin miktarı alır.
- O tarihteki kurla çarpar, sonucu basar.
- Kurlar `data.csv` içinde.
- Sorgular argüman olarak verilen dosyada.

## Dosya formatları
| Dosya | Format | Örnek |
|---|---|---|
| `data.csv` | `date,exchange_rate` | `2011-01-01,0.3` |
| input | `date \| value` | `2011-01-03 \| 3` |

## Çalıştırma
```bash
make
./btc input.txt
```
- `ex00` içinden çalıştır; `data.csv` orada aranır.

## Container: std::map
- `std::map<std::string, double> _db`
- Anahtar tarih, değer kur.
- Map anahtara göre sıralı tutar.
- `YYYY-MM-DD` string'leri alfabetik sıralanınca kronolojik de sıralanır.
- Bu yüzden tarihi int'e çevirmeye gerek yok.
- `double` seçildi: `float` büyük çarpımlarda yuvarlama hatası yapar.
- Kural: map artık ex01 ve ex02'de kullanılamaz.

## En yakın alt tarih
- Subject: tarih DB'de yoksa bir **alt** tarihi kullan.
- `upper_bound(date)` → tarihten **kesin büyük** ilk eleman.
- Bir geri (`--it`) → eşit ya da en yakın alt tarih.
- `begin()` dönerse geri gidilemez → hata.

```cpp
std::map<std::string, double>::const_iterator it = _db.upper_bound(date);
if (it == _db.begin())
    throw std::runtime_error("no data before => " + date);
--it;
return it->second;
```

Örnek (DB: 01-01, 01-04, 01-07):
| Aranan | upper_bound | --it | Sonuç |
|---|---|---|---|
| 2011-01-04 | 01-07 | 01-04 | kendisi |
| 2011-01-03 | 01-04 | 01-01 | alt tarih |
| 2030-01-01 | end() | son kayıt | son kur |
| 2008-01-01 | begin() | — | hata |

- `begin()` kontrolü olmadan `--it` → tanımsız davranış.

## Tarih doğrulama
1. Tam 10 karakter, 4. ve 7. indekste `-`, gerisi rakam.
2. Ay 1–12 arası.
3. Gün 1 ile ayın gün sayısı arası.
- Artık yıl: 4'e bölünür ve 100'e bölünmez, ya da 400'e bölünür.
- `2012-02-29` geçerli, `2011-02-29` değil.
- `2011-04-31` geçersiz; nisan 30 çeker.

## Değer doğrulama
- Yalnızca `[-]rakamlar[.rakamlar]` kabul edilir.
- `-` kabul edilir; negatif değer kendi hatasını alsın diye.
- `1e2`, `0x10`, `+5`, `inf`, `5.`, `.5` → bad input.
- Format doğruysa `strtod` ile çevrilir.
- `double` ile okunduğu için `2147483648` taşmaz.

## Bir satırın akışı (processLine)
1. Satırı trim et.
2. `" | "` yok → `Error: bad input => <satır>`
3. Tarih ya da değer geçersiz → `Error: bad input => <satır>`
4. Değer < 0 → `Error: not a positive number.`
5. Değer > 1000 → `Error: too large a number.`
6. Tarih DB'den önce → `Error: no data before => <tarih>`
7. Hepsi geçti → `date => value = value × rate`
- İlk takılan kontrol mesajını basar, satır biter.
- Değer input'taki string olarak basılır (`=> 1.2`).

## İki tür hata
- **Dosya hatası:** `throw` edilir, `main` yakalar, program biter.
  - Argüman yok / dosya açılmıyor → `Error: could not open file.`
- **Satır hatası:** basılır, sonraki satıra geçilir.
- Hepsi stdout'a gider; subject başka bir şey demiyor.

## Sınıf yapısı
| Fonksiyon | Görevi |
|---|---|
| `loadDatabase` | `data.csv`'yi map'e yükler |
| `processInput` | Input'u açar, başlığı atlar |
| `processLine` | Tek satırın kontrolü ve çıktısı |
| `isValidDate` | Tarih kontrolü |
| `parseValue` | Değer format kontrolü |
| `getRate` | En yakın alt tarihin kuru |

- OCF: copy constructor ve `operator=` yalnızca `_db`'yi kopyalar.
- `new` yok, destructor boş.
- `operator=` içinde `this != &other` kontrolü var.

## Evaluation soruları
1. **Neden map?** Sıralı, `upper_bound` ile O(log n) arama.
2. **lower_bound ile upper_bound farkı?** `lower_bound` ≥, `upper_bound` > döndürür.
3. **İlk tarihten önceki tarih?** `begin()` kontrolü; yoksa UB.
4. **2147483648 neden çökmüyor?** `double` ile okunuyor.
5. **Neden `4.71159e+07`?** `cout` varsayılan 6 anlamlı hane gösterir. `std::fixed` + `std::setprecision` ile değişir.

## Evaluation'da input oluşturma
```bash
cat > input.txt << EOF
date | value
2011-01-03 | 3
EOF
```
- `EOF` tek başına bir satırda olmalı.
