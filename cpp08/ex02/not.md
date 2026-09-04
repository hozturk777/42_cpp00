# ex02 — MutantStack

## Amaç
`std::stack`'i **iterable** hale getiren bir `MutantStack<T>` yazmak.
`std::stack` bilinçli olarak iterator sunmaz (sadece LIFO erişim için
tasarlanmış); bu exercise, bir adapter container'ın gerçekte neyin
üstüne kurulu olduğunu ve o alttaki yapıya nasıl erişilebileceğini
göstermek için var.

## Neden `std::stack`'ten inherit etmek işe yarıyor?
- `std::stack` aslında kendi başına bir container değil, bir
  **container adapter**: içeride varsayılan olarak `std::deque<T>` tutar
  ve `push`/`pop`/`top` gibi fonksiyonları o alttaki container'a
  yönlendirir. Bu alttaki container, `std::stack` içinde `protected
  Container c;` olarak tanımlı — yani `private` değil, türeyen sınıflar
  ona erişebilir.
- `MutantStack`, `public std::stack<T, Container>`'dan inherit ederek
  `push`/`pop`/`top`/`size`/`empty` gibi tüm member fonksiyonları
  **bedavaya** kazanıyor (hiçbirini yeniden yazmadık). Tek eklediğimiz
  şey, korunan `c` üyesine `begin()`/`end()` üzerinden bir kapı açmak.

## Sistem seviyesinde bilinmesi gerekenler
1. **`this->c` neden `c` değil**: `MutantStack`, template bir sınıftan
   (`std::stack<T, Container>`) türediği için `c`, derleyicinin ilk
   geçişte bilemeyeceği bir **dependent name**'dir (base class template
   parametresine bağlı). `this->c` yazmak derleyiciye "bu isme lookup'ı
   template somutlaştığında yap" der; sadece `c` yazsan C++98'de
   derleyici bunu bulamayabilir/hata verebilir.
2. **`Container` neden ikinci bir template parametresi, sabit
   `std::deque` değil**: `std::stack<T, Container = std::deque<T> >`
   imzası, `std::stack`'in kendi imzasıyla birebir eşleşiyor — böylece
   `MutantStack<int>` varsayılan olarak `deque` kullanırken,
   `MutantStack<int, std::vector<int> >` gibi farklı bir alttaki
   container ile de kullanılabilir. Bu, subject'in "std::stack'in tüm
   davranışını sun" şartını tam karşılıyor.
3. **`iterator`/`const_iterator` neden `typename Container::iterator`
   üzerinden typedef'lendi**: `MutantStack`'in kendi iterator mantığını
   yazmaya gerek yok — alttaki `Container` (deque/vector/list) zaten
   kendi iterator'ını sağlıyor. `begin()`/`end()` de sadece `c.begin()`/
   `c.end()`'i olduğu gibi dışarı açıyor; iterator **implementasyonu**
   burada değil, `Container`'ın kendisinde.
4. **`main.cpp`'de `MutantStack` ile `std::list` testinin aynı çıktıyı
   vermesi tesadüf değil**: İkisi de aynı iterator arayüzünü
   (`begin`/`end`/`operator!=`/`operator++`) sağladığı için, aynı push
   sırası aynı gezinme sırasını üretiyor. Bu da ex00'daki `easyfind`
   ile aynı prensibi doğruluyor: **container-agnostic kod, doğru
   arayüz sağlandığı sürece hangi container olduğunu bilmeden çalışır**.
5. **Neden yeni bir `push`/`pop`/`top` yazılmadı**: `public` inheritance
   ile `std::stack`'in tüm public arayüzü zaten `MutantStack`'in bir
   parçası oluyor (override etmeden). Bunları elle yeniden yazmak hem
   gereksiz kod tekrarı hem de `std::stack`'in kendi optimize edilmiş
   implementasyonunu bozma riski taşırdı — inheritance burada "is-a"
   ilişkisini (MutantStack bir stack'tir, üstüne iterator eklenmiş)
   doğru şekilde kullanıyor.
6. **`std::stack<int> s(mstack);` satırının çalışması**: `std::stack`'in
   copy constructor'ı, kaynak nesnenin `Container`'ını kopyalar.
   `MutantStack` da `std::stack`'ten türediği için bu satır sorunsuz
   derlenir — `MutantStack`'in bir `std::stack`'e **implicit olarak
   dönüşebilmesi**, inheritance'ın "is-a" garantisinin somut kanıtı.
