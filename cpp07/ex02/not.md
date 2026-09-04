# ex02 — Array (class template)

## Amaç
`T` tipinden bağımsız, kendi belleğini yöneten bir `Array<T>` sınıfı
yazmak: default/parametreli constructor, derin kopyalayan copy
ctor/assignment, sınır kontrollü `operator[]`, `size()`. STL
`std::vector` yasak (Module 08'e kadar) — aynı işlevi elle,
`new[]`/`delete[]` ile kurmak zorundayız.

## Neden derin kopya (deep copy) şart?
- `_data` bir `T*` yani ham bir bellek adresi. Derleyicinin ürettiği
  **varsayılan** copy ctor/assignment sadece bu pointer'ı kopyalar
  (shallow copy) — iki `Array` nesnesi aynı belleği paylaşır.
- Sonuç: biri `delete[]` çağırdığında (destructor) diğeri artık
  **serbest bırakılmış belleğe** işaret eder → **dangling pointer**,
  ardından ona erişmek **undefined behavior** (use-after-free).
  İkinci kez `delete[]` çağrılırsa da **double free** olur.
- Bu yüzden copy ctor ve `operator=`'ı **elle** yazıp, her seferinde
  `new[]` ile taze bellek ayırıp elemanları tek tek kopyalamak
  zorundayız — subject'in "orijinali değiştirmek kopyayı etkilemesin"
  şartı tam olarak bunu test ediyor.

## Sistem seviyesinde bilinmesi gerekenler
1. **Preventive allocation yasağı ne demek**: "n eleman iste, n eleman
   ayır" — `new T[n]` çağrısı tam olarak `n * sizeof(T)` kadar bellek
   ayırır, fazladan kapasite/buffer tutmayız (örn. `std::vector`'ın
   growth stratejisinin aksine). Bu yüzden `_size` her zaman gerçek
   ayrılmış eleman sayısıyla birebir eşleşmeli.
2. **`new T[0]` geçerlidir**: Sıfır boyutlu diziler C++'ta yasal, geçerli
   bir pointer döner (dereference edilemez ama `delete[]` edilebilir).
   Bu sayede default ctor için `_data`'yı NULL bırakıp destructor'da
   özel durum kontrolü yazmamıza gerek kalmadı — kod tek bir yoldan
   geçiyor (NULL-check dallanması yok), daha az hata yüzeyi.
3. **`operator=`'da self-assignment kontrolü (`this != &src`)**: Eğer
   `c = c;` gibi bir çağrı olursa ve bu kontrol olmasaydı, önce
   `delete[] _data` çalışır (kendi verimizi sileriz), sonra
   `src._data`'dan (artık silinmiş bellekten) okumaya çalışırız →
   UB. Kontrolün yokluğu sessizce çalışıp nadir durumda çöken bir bug
   üretir — bu yüzden Orthodox Canonical Form'da assignment operator
   yazarken bu kontrol neredeyse her zaman gerekli.
4. **`operator=`'da "önce yeni ayır, sonra eskiyi sil" sırası (strong
   exception safety)**: Kodda `tmp` adında geçici bir dizi ayırıp
   dolduruyoruz, ancak her şey başarılıysa `_data`'yı `tmp`'ye
   çeviriyoruz. Eğer `new T[src._size]` bellek yetersizliğinden
   (`std::bad_alloc`) patlarsa, `_data` hâlâ eski, geçerli veriyi
   tutuyor — nesne **tutarsız bir yarı-silinmiş durumda kalmıyor**.
   Önce `delete[] _data` yapıp sonra `new` çağırsaydık, `new`
   başarısız olduğunda nesne kalıcı olarak boş/geçersiz kalırdı.
5. **`operator[]`'ın const/non-const olarak iki kez tanımlanması**:
   `T const &operator[](size_t) const` olmadan, `void print(Array<int>
   const &a)` gibi bir fonksiyon içinde `a[i]` çağrısı derlenmez —
   çünkü const bir nesne üzerinde yalnızca const üye fonksiyonlar
   çağrılabilir. İki overload birlikte, hem "oku" hem "yaz" senaryosunu
   const-doğru şekilde kapsıyor.
6. **`std::out_of_range` neden uygun**: `<stdexcept>` içindeki bu sınıf
   `std::exception`'dan türer, `what()` ile açıklayıcı mesaj taşır.
   STL container/algorithm yasağı burada geçerli değil — yasaklanan
   `<vector>`, `<algorithm>` gibi *veri yapıları/algoritmalar*;
   `<stdexcept>` sadece exception sınıfları tanımlıyor, container
   değil.
