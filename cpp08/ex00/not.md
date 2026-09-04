# ex00 — easyfind (function template)

## Amaç
`T` tipinden bağımsız, herhangi bir sequence container'da (vector,
list, deque...) int arayan tek bir `easyfind` fonksiyonu yazmak.
Container'a özel bir arama yazmak yerine, STL'in **iterator soyutlaması**
üzerinden container-agnostic bir algoritma kurmak — modülün asıl
öğrettiği şey bu.

## Neden container tipini şablonla, `std::find`'ı elle değil?
- `easyfind`, `T &container` alıyor ve içeride `container.begin()` /
  `container.end()` çağırıyor. `T` vector de olsa list de olsa bu
  ikisi her STL container'da tanımlı olduğu için fonksiyon **hiç
  değişmeden** ikisiyle de çalışıyor — `main.cpp`'de aynı `easyfind`
  çağrısının hem `vector<int>` hem `list<int>` üzerinde çalışması bunu
  ispatlıyor.
- `std::find`'ı kendin `for` döngüsüyle yazsaydın da çalışırdı, ama o
  zaman container'ın iç yapısına (index'lenebilir mi, random access
  mi) bağımlı kod yazma riski doğardı. `std::find` sadece `!=` ve
  `++it` operatörlerine ihtiyaç duyar — bu yüzden `list` gibi random
  access olmayan bir container'da da sorunsuz çalışır.

## Sistem seviyesinde bilinmesi gerekenler
1. **`typename T::iterator` neden gerekli**: `T` bir template
   parametresi olduğu için derleyici, `T::iterator`'ın bir tip mi yoksa
   bir static üye mi olduğunu template'in ilk geçişinde bilemez
   (**dependent name**). `typename` anahtar kelimesi derleyiciye "bu
   bir tip, static bir değişken değil" der. Bunu yazmazsan derleyici
   hata verir — bu C++98'de opsiyonel değil, template içinde container
   üyesine bu şekilde erişen her yerde zorunlu.
2. **`std::find` neden `<algorithm>`, arama mantığı neden burada
   yeniden yazılmadı**: `std::find(first, last, value)` iterator
   çiftiyle çalışan generic bir algoritma; hangi container'dan geldiği
   umurunda değil. Bu, Module 08'in temel fikri — algoritmayı veri
   yapısından ayırmak. `easyfind` aslında `std::find`'ın üstüne ince
   bir hata-yönetim katmanı (exception fırlatma) ekliyor, aramanın
   kendisini yeniden icat etmiyor.
3. **Bulunamama durumunda exception seçimi (`std::out_of_range`)**:
   `std::find` bulamazsa `container.end()` döner; `end()` **dereference
   edilemez**, bir sentinel'dir. Onu olduğu gibi döndürüp çağırana
   `== end()` kontrolünü bırakmak yerine, burada `end()`'i yakalayıp
   `std::out_of_range` fırlatmak tercih edilmiş — arayan taraf her
   çağrıda manuel kontrol yazmak zorunda kalmıyor, hata `try/catch` ile
   tek noktadan yönetiliyor. `<stdexcept>` include edilmesinin sebebi
   bu; STL container/algorithm yasağı burada geçerli değil çünkü bu
   sadece bir exception sınıfı, veri yapısı değil.
4. **Parametre neden `T &` (const değil)**: `container.begin()`'in
   const olmayan overload'u `iterator` döner, const overload'u ise
   `const_iterator` döner. Fonksiyon `T::iterator` dönmeyi taahhüt
   ettiği için parametre const alınamaz — const bir container
   verilseydi derleyici `const_iterator`'ı `iterator`'a çeviremeyeceği
   için hata verirdi. Bu, fonksiyonun neden salt-okunur değil de
   "container'ı değiştirebilecek bir iterator" döndürdüğünü de açıklar
   (örn. bulunan elemanı silmek için kullanılabilir).
5. **"Sadece integer container, associative container'ları handle
   etmene gerek yok" şartının kod üzerindeki etkisi**: `value`
   parametresi `int` olarak sabitlenmiş, `T` sadece container tipi için
   generic. `std::find` value-based (== karşılaştırması) çalıştığı
   için `map`/`set` gibi associative container'larda semantik olarak
   yanlış olurdu (onların kendi `O(log n)` `find()` member fonksiyonu
   var) — bu yüzden subject bilinçli olarak bunları kapsam dışı
   bırakıyor, `easyfind`'ın sequence container'lara özel bir araç
   olduğunu netleştiriyor.
