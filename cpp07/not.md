# CPP07 — C++ Templates

## Modülün amacı

**Generic programming** öğrenmek: bir algoritmayı ya da veri yapısını **tip bağımsız** yazmak.
Bu modül, cpp08/09'daki STL'e hazırlık — `std::vector<T>`, `std::swap`, `std::min` gibi
şeylerin nasıl yazıldığını kendin yazarak göreceksin.

## Sistem düzeyinde: template nedir, nasıl çalışır?

- Template **kod değildir, kod üreten bir kalıptır**. `swap<int>` kullandığın anda derleyici
  o kalıptan `int` için gerçek bir fonksiyon üretir → **instantiation**.
- Instantiation **derleme zamanında** olur (runtime maliyeti yok, virtual/vtable yok).
  Buna *static polymorphism* denir; cpp04'teki virtual ise *dynamic polymorphism*.
- **Neden header'da olmak zorunda?** Her `.cpp` ayrı derlenir (translation unit). Derleyici
  `min<std::string>` üretmek için template'in **gövdesini görmek** zorunda. Gövde başka
  bir `.cpp`'de olsaydı üretemezdi → linker hatası (`undefined reference`).
- Aynı instantiation birden çok `.cpp`'de üretilirse linker sorun çıkarmaz: template
  fonksiyonlar ODR açısından `inline` gibi davranır, kopyalardan biri tutulur.
- **İki aşamalı kontrol:** Template tanımı okunurken sadece tipe bağlı olmayan kısımlar
  kontrol edilir; `a < b` gibi T'ye bağlı ifadeler ancak instantiation'da kontrol edilir.
  Yani `min` yazıp `<` operatörü olmayan bir tiple çağırırsan hata **çağırdığın yerde** çıkar.
- **Template argument deduction:** `min(a, b)` → derleyici T'yi argümanlardan çıkarır.
  `min(1, 2.5)` → T hem `int` hem `double` olamaz → hata. `min<double>(1, 2.5)` ile açıkça verilir.
- **Code bloat:** Her farklı T için ayrı kopya üretilir → binary büyür. Hız karşılığı boyut.
- `.tpp` dosyası sadece bir **isimlendirme alışkanlığı**. Header'ın sonunda `#include "Array.tpp"`
  yapılır; teknik olarak hâlâ header'dadır ama sınıf tanımı ile implementasyon ayrı durur.

---

## ex00 — `swap`, `min`, `max`

**Amaç:** En basit fonksiyon template'leri. `typename T` + deduction mantığını oturtmak.

- `swap(T &a, T &b)` → referansla al, geçici değişkenle değiştir.
- `min/max` → `const T&` alıp `const T&` döndürmek mantıklı (gereksiz kopya yok).
- **Eşitse ikincisini döndür** kuralı: `a < b ? a : b` → eşitlikte `b` döner ✅.
  `max` için `a > b ? a : b` ✅. Sırayı ters yazarsan kural bozulur — değerlendirmede sorulur.
- **Neden `::swap`?** `::` global namespace'i zorlar. `std::string` argümanıyla çağırınca
  **ADL (Argument Dependent Lookup)** `std` namespace'ine de bakar ve `std::swap`/`std::min`
  bulunur → *ambiguous call*. `::` bunu engeller.
- "Tüm karşılaştırma operatörlerini desteklemeli" → T için `<` ve `>` tanımlı olmalı.
  Kendi sınıfınla test etmek güzel bir artı (Fixed gibi).

## ex01 — `iter`

**Amaç:** Fonksiyonu parametre olarak geçmek + template'in `const` ile etkileşimi.

- İmza fikri: `template <typename T, typename F> void iter(T *arr, const size_t len, F f)`
- `F` template parametresi olunca hem **function pointer** hem **functor** kabul eder.
- **const meselesi:** `const int arr[]` geçersen T otomatik `const int` olarak çıkarılır →
  `f` `const int&` alan bir fonksiyon olmalı. Non-const dizide hem `T&` hem `const T&` alan
  fonksiyon çalışır. İpucu bu yüzden verilmiş: deduction'ın const'ı nasıl taşıdığını düşün.
  (Alternatif: `T*` ve `const T*` için iki ayrı overload.)
- **Template fonksiyonu 3. parametre olarak geçmek:** `iter(arr, 3, print)` çalışmaz —
  `print` bir fonksiyon değil, bir kalıp; F çıkarılamaz. Açıkça instantiate et:
  `iter(arr, 3, print<int>)`.
- Test: int, string, const dizi, değer değiştiren fonksiyon (ör. `increment`), yazdıran fonksiyon.

## ex02 — `Array<T>` class template

**Amaç:** Class template + dinamik bellek + OCF + exception — önceki modüllerin birleşimi.
Aslında mini bir `std::vector`.

- **Üyeler:** `T *_data; unsigned int _size;`
- **Default ctor:** Boş dizi. `_data = NULL` veya `new T[0]` (ikisi de geçerli; `delete[] NULL` güvenli).
- **`Array(unsigned int n)`:** `new T[n]()` — sondaki `()` **value-initialization** yapar:
  `int` gibi primitive'ler 0 olur, `()` olmadan çöp değer kalır. Subject'teki
  `new int()` ipucu tam olarak bu.
- **Copy ctor / `operator=`:** **Deep copy** şart — yeni `new T[]`, elemanları tek tek kopyala.
  Shallow copy yaparsan iki nesne aynı belleği gösterir → biri değişince diğeri de değişir,
  sonunda **double free**. `operator=`'de: self-assignment kontrolü → eskiyi `delete[]` → yeni alloc → kopyala.
- **Destructor:** `delete[] _data;` (`delete` değil — `new[]` ile `delete[]` eşleşmeli).
- **`operator[]`:** İki versiyon yaz:
  - `T& operator[](unsigned int i)` → yazma için
  - `const T& operator[](unsigned int i) const` → const Array okuma için
  - `i >= _size` ise `throw` (std::exception ya da ondan türeyen bir sınıf, ör. `std::out_of_range`).
  - `unsigned` olduğu için negatif index (`-1`) çok büyük sayıya döner → yine yakalanır.
- **`size() const`:** "Instance'ı değiştirmemeli" = `const` member function.
- **Neden "preventive allocation" yasak?** Kapasiteyi önceden fazla ayırmak (vector'ün
  capacity mantığı) istenmiyor; tam `n` eleman ayır.
- Test: boş dizi, `int` default değerleri 0 mı, kopyayı değiştirip orijinale bak,
  out-of-bounds try/catch, `Array<std::string>`, const Array, valgrind/leaks ile leak kontrolü.

---

## Değerlendirmede muhtemel sorular

- Template neden header'da? → instantiation için gövde görünmeli (TU mantığı).
- `::min` yerine `min` yazsan ne olur? → ADL + `std::min` → ambiguous.
- `new T[n]` ile `new T[n]()` farkı?
- Deep copy vs shallow copy, self-assignment neden kontrol edilir?
- `operator[]`'ün const versiyonu neden gerekli?
- `iter`'e `print` yerine neden `print<int>` geçtin?
