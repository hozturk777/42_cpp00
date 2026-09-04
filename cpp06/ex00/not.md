# ex00 — ScalarConverter

## Amaç
Bir komut satırı argümanını (string) alıp, hangi C++ literal tipi olduğunu
tespit edip (`char`, `int`, `float`, `double`), o değeri diğer üç tipe de
**explicit** (açık) cast ile dönüştürüp ekrana basmak. Asıl konu: C++'ın
farklı cast türlerini (`static_cast`, `dynamic_cast`, `reinterpret_cast`,
`const_cast`) tanımak ve doğru olanı doğru yerde kullanmak.

## Neden static_cast?
- `static_cast`: derleme zamanında bilinen, "mantıklı" tip dönüşümleri için
  (int↔float, char↔int, base↔derived pointer/reference — ilgili tipler
  birbiriyle ilişkiliyse). Burada hepsi aritmetik/skaler tipler olduğu için
  doğru seçim budur.
- `reinterpret_cast` bit kalıbını olduğu gibi başka bir tipe yeniden
  yorumlar (ör. pointer↔integer) — ex01'de (Serializer) kullanılacak.
- `dynamic_cast` sadece polymorphic sınıflarda (virtual fonksiyonu olan)
  RTTI ile çalışır — ex02'de kullanılacak.
- `const_cast` sadece const/volatile niteleyicisini kaldırıp eklemek için.
- C-style cast (`(int)x`) bunların hepsini sessizce yapabildiği için
  tehlikelidir; C++ cast'leri niyeti kodda görünür kılar, derleyici de
  yanlış kullanımı bazı durumlarda yakalar.

## Sistem seviyesinde bilinmesi gerekenler
1. **IEEE 754**: `float`/`double` NaN ve Infinity değerlerini standart
   olarak destekler. `std::isnan()`, `std::isinf()` bunları kontrol eder.
   NaN kendisiyle bile eşit değildir (`NaN != NaN`).
2. **Integer overflow ile static_cast**: `double`'dan `int`'e sınır dışı
   bir değeri `static_cast` etmek **undefined behavior**'dır. Bu yüzden
   cast etmeden önce `INT_MIN`/`INT_MAX` ile karşılaştırma şart
   (`printInt` fonksiyonundaki kontrol tam olarak bunun için var).
3. **char'ın işaretliliği platforma bağlıdır** (x86_64'te genelde signed,
   `-128..127`). Displayable aralık (`isprint`) bundan ayrı bir kavram:
   yazdırılabilir ASCII aralığı `32-126`'dır. "Non displayable" ile
   "impossible" farklı şeyler: biri geçerli ama görünmez karakter, diğeri
   char aralığının tamamen dışında.
4. **Literal tespiti string seviyesinde yapılıyor**: gerçek bir C++
   derleyicisi gibi, `'c'` (tek tırnak + 1 karakter), `42.0f` (f soneki),
   `4.2` (nokta içeren), `42` (salt rakam) formatlarını ayırt ediyoruz.
   `nan`/`inf` gibi pseudo-literaller derleyicinin anlayacağı literal
   değil, biz string eşleşmesiyle özel olarak yakalıyoruz.
5. **Neden sınıf instantiate edilemez?**: Constructor/copy
   constructor/operator= `private` yapılmış — sınıfın hiç state'i yok,
   sadece bir "namespace + static fonksiyon" gibi davranıyor
   (utility class pattern).

## Kritik uygulama detayı (bulduğumuz gerçek bug)
İlk versiyonda büyük sayılar (`2147483648` gibi) bilimsel gösterimle
(`2.14748e+09`) basılırken, "tam sayıysa `.0` ekle" mantığı bu string'in
sonuna körü körüne `.0` ekleyip `2.14748e+09.0f` gibi bozuk çıktı
üretiyordu. Çözüm: `.` veya `e`/`E` zaten string'de var mı diye kontrol
edip, yoksa `.0` eklemek. Ders: kayan noktalı sayıyı stringe çevirirken
formatın (normal mi, bilimsel mi) çıktığı biçimi asla varsaymayın.
