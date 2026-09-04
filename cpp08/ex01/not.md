# ex01 — Span

## Amaç
En fazla N int tutabilen bir `Span` sınıfı yazmak: tekli ekleme
(`addNumber`), iterator-range ile toplu ekleme (`addRange`), ve
elemanlar arası en kısa/en uzun mesafeyi bulan `shortestSpan` /
`longestSpan`. İçte kendi diziyi elle yönetmek yerine `std::vector`
kullanmak — Module 08'in "artık STL serbest, kullan" kuralının ilk
gerçek uygulaması.

## Neden `std::vector<int>` ve elle `new[]`/`delete[]` değil?
- Module 07'ye kadar container yasaktı, kendi belleğini yönetmek
  (deep copy, destructor'da `delete[]`) zorunluydu. Burada artık
  `std::vector` kullanılıyor — copy ctor/assignment `_numbers(src._numbers)`
  ile otomatik derin kopyalanıyor, elle bellek yönetimi kodu tamamen
  ortadan kalkıyor.
- Bu, subject'in "STL'i kullanmazsan kötü not alırsın" uyarısının
  karşılığı: aynı işi elle yazmak burada artık **kötü pratik**, çünkü
  hazır ve test edilmiş bir araç varken tekrar icat etmek anlamsız.

## Sistem seviyesinde bilinmesi gerekenler
1. **`addRange` neden header'da (template member function)**: Template
   fonksiyonlar/member'lar derleme anında somutlaştığı için (compile-time
   instantiation) implementasyonları `.cpp`'de olamaz — linker somut
   tipi göremez. Bu yüzden `addRange`, sınıfın diğer üyelerinin aksine
   `Span.hpp` içinde tanımlı; "implementasyon header'da olamaz" kuralının
   template'ler için istisnası tam burada devreye giriyor.
2. **`InputIterator` generic tasarımı**: `addRange(first, last)` belirli
   bir container'a değil, herhangi bir iterator çiftine bağlı —
   `main.cpp`'de `std::vector<int>::iterator` ile çağrılıyor ama aynı
   şekilde bir array pointer'ı veya `std::list::iterator` ile de
   çalışır. Bu, `std::vector`'ün kendi range-constructor'ının
   (`vector(first, last)`) taklit edilmesi; subject'in "Containers'ı
   incele" ipucu tam bunu işaret ediyor.
3. **Kapasite kontrolü `std::distance` ile önden yapılıyor**:
   `_maxSize - _numbers.size() < distance(first, last)` satırı, elemanları
   eklemeden önce sığıp sığmayacağını hesaplıyor. Böylece ya hepsi
   eklenir ya da hiçbiri eklenmez (**all-or-nothing**) — yarım kalan bir
   `insert` sonrası tutarsız/taşmış bir Span'de kalma riski yok.
4. **`_maxSize` unsigned, çıkarma işlemi güvenli çünkü invariant
   korunuyor**: `_maxSize - _numbers.size()` unsigned çıkarma; eğer
   `_numbers.size()` hiçbir zaman `_maxSize`'ı geçemiyorsa (bunu
   `addNumber`'daki `>=` kontrolü garanti ediyor) bu satır asla negatife
   taşıp dev bir sayıya sarmıyor (**unsigned underflow**). Bu tür bir
   kontrolü kaldırırsan sessizce yanlış sonuç üreten bir bug'a dönüşür.
5. **`shortestSpan` neden önce `sort` istiyor**: En kısa mesafe, sıralı
   dizide **ancak ardışık elemanlar arasında** olabilir (sıralı değilken
   uzak iki eleman rastgele yakın çıkabilir ama bu genel çözüm değildir).
   `std::sort` sonrası tek geçişte ardışık farkların minimumunu almak
   O(n log n) ile çözüyor; sort olmadan tüm çiftleri karşılaştırmak
   O(n²) olurdu — 10.000 elemanda bu fark performansta hissedilir.
6. **`longestSpan` için `sort` gerekmiyor**: En uzun mesafe her zaman
   `max - min`'dir, dizinin sırasından bağımsız. Bu yüzden
   `std::min_element`/`std::max_element` ile O(n)'de çözülüyor — burada
   sort yapmak gereksiz bir maliyet olurdu, iki fonksiyonun farklı
   algoritma stratejisi izlemesinin sebebi bu.
7. **Private default constructor ile OCF çelişkisi nasıl çözülüyor**:
   Orthodox Canonical Form default ctor ister, ama subject "constructor'a
   tek parametre (N) geçilecek" diyor — ikisi çelişir gibi görünür.
   Çözüm: default ctor'u yazıp `private` yapmak. Böylece sınıf hâlâ OCF'yi
   sağlıyor (fonksiyon var) ama dışarıdan `Span sp;` gibi parametresiz
   kullanım derleme hatası veriyor — subject'in niyeti korunuyor.
8. **`reserve(n)` neden parametreli constructor'da çağrılıyor**:
   `std::vector` eleman eklerken kapasitesi dolunca kendini büyütür ve
   bu büyüme sırasında **tüm elemanları yeni belleğe kopyalar**. `N`
   önceden bilindiği için `reserve(n)` ile tüm bellek baştan ayrılıyor,
   `addNumber` çağrıları sırasında gereksiz yeniden ayırma/kopyalama
   olmuyor — 10.000 elemanlık testte bu performans farkını yaratan şey.
