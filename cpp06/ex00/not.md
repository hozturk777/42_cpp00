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



# static_cast — Detaylı Sistemsel Not

## Ne yapar
`static_cast<T>(expr)`, derleyicinin **derleme zamanında** bildiği, tipler
arasında tanımlı bir dönüşüm ilişkisi olduğunda kullanılan cast'tir. Standart
(`[expr.static.cast]`) hangi dönüşümlere izin verildiğini net olarak listeler:
sayısal tipler arası (int↔float↔double↔char), enum↔int, `void*`↔`T*`, base↔derived
pointer/reference (ilişkili sınıflar), ve explicit constructor/conversion
operator çağrıları.

## Derleme zamanında ne olur (sayısal dönüşümler için)
`static_cast` bir "yorumlama" değil, gerçek bir **değer dönüşümüdür** — bit
kalıbı değişir, çünkü int ve float tamamen farklı ikili temsillere sahiptir
(int: two's complement; float/double: IEEE 754).

Derleyici, hedef makine mimarisine göre gerçek CPU talimatları üretir:
- `int → float/double`: FPU/SSE talimatı (x86-64'te `cvtsi2sd`) — tamsayı,
  IEEE 754 kayan nokta formatına çevrilir.
- `float/double → int`: `cvttsd2si` gibi bir "truncate" talimatı — ondalık kısım
  **atılır** (yuvarlama değil, sıfıra doğru kesme).
- `double → float`: mantissa 52 bitten 23 bite düşürülür, **hassasiyet kaybı**
  olur (rounding). `float → double` ise kayıpsızdır (genişleme).
- `char → int`: **sign extension** (`movsx`, işaretli ise) ya da **zero
  extension** (`movzx`, unsigned ise) — üst bitler işarete göre doldurulur.

Bunların hepsi **compile-time'da karar verilir**, çalışma zamanında hiçbir
kontrol/lookup yapılmaz — bu yüzden `static_cast` sıfır runtime maliyetli bir
cast'tir (tam tersine `dynamic_cast`, aşağıda).

## Undefined Behavior riski
`static_cast` **aralık kontrolü yapmaz**. `static_cast<int>(1e20)` gibi, hedef
tipin temsil edemeyeceği bir değeri cast etmek **UB**'dir — bu yüzden
`ScalarConverter.cpp`'de cast etmeden önce `INT_MIN`/`INT_MAX` ile manuel
karşılaştırma yapıyoruz (`printInt`, `printChar`).

Sınıf hiyerarşisinde de aynı tehlike var: `static_cast<Derived*>(basePtr)`
derleyici tarafından **izin verilir** ama `basePtr` gerçekten bir `Derived`
nesnesine işaret etmiyorsa UB'dir — çünkü hiçbir runtime kontrolü yoktur
(bu tam olarak ex02'de `dynamic_cast`'in çözdüğü problem).

## static_cast vs C-style cast `(T)expr`
C-style cast, aslında "sırayla dene" mantığıyla çalışan bir **kara kutudur**:
önce `const_cast` dener, olmazsa `static_cast`, o da olmazsa sessizce
`reinterpret_cast`'e (gerekirse `const_cast` ile birleştirerek) düşer. Yani:
- Niyetini kodda belli etmez — okuyan biri "bu sayısal bir dönüşüm mü, yoksa
  tehlikeli bir pointer reinterpretation mı?" ayrımını göremez.
- Yanlışlıkla `const`'u kırabilir veya alakasız pointer tiplerini
  reinterpret edebilir, derleyici hiç uyarmaz.
- `grep`lemesi bile zordur (`(int)x` ile normal parantez ayırt edilemez),
  `static_cast<int>(x)` ise kod tabanında aranabilir/görünürdür.

`static_cast`, sadece **tanımlı ilişkili** dönüşümlere izin vererek bunu
derleme zamanında sınırlar — geçersiz bir `static_cast<T>(x)` **derleme
hatası** verir, C-style cast ise neredeyse hiçbir şeyi reddetmez.

## static_cast vs reinterpret_cast
- `static_cast`: tipler arasında **anlamlı/tanımlı** bir dönüşüm ilişkisi
  olmalı (int→float gibi, ya da ilişkili class hiyerarşisi).
- `reinterpret_cast`: hiçbir dönüşüm mantığı yoktur, **bit kalıbı olduğu gibi**
  başka bir tipmiş gibi yeniden yorumlanır (ör. pointer↔integer — tam olarak
  ex01'deki `Serializer`). Alakasız pointer tipleri arasında da kullanılabilir,
  bu da strict aliasing kurallarını çiğneyip UB üretebilir.

## static_cast vs dynamic_cast
- `static_cast` derleme zamanı kontrolü yapar, **runtime kontrolü yapmaz** —
  yanlış varsayımda UB.
- `dynamic_cast`, polymorphic (virtual fonksiyonlu) sınıflarda, **RTTI**
  (vtable üzerinden gerçek tip bilgisi) kullanarak **çalışma zamanında**
  kontrol eder; pointer'da başarısızlıkta `NULL`, reference'ta `std::bad_cast`
  fırlatır. Bu güvenlik, ekstra runtime maliyeti (vtable lookup) ile gelir.

## static_cast vs const_cast
`const_cast` tamamen farklı bir amaca hizmet eder: tip değişmez, sadece
`const`/`volatile` niteleyicisi eklenir/kaldırılır. `static_cast` ile
const'u kırmaya çalışmak derleme hatası verir — bu ikisi kesişmez.

## Özet tablo
| Cast              | Kontrol zamanı | Amaç                                   |
|-------------------|----------------|------------------------------------------|
| static_cast       | derleme        | ilişkili/tanımlı tip dönüşümleri         |
| dynamic_cast      | çalışma zamanı | polymorphic hiyerarşide gerçek tip       |
| reinterpret_cast  | yok            | bit kalıbını olduğu gibi yeniden yorumla |
| const_cast        | derleme        | sadece const/volatile ekle/çıkar         |
| C-style cast      | belirsiz       | yukarıdakilerin hepsini sessizce dener   |
