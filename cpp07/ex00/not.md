# ex00 — swap / min / max (function templates)

## Amaç
Tip bağımsız çalışan `swap`, `min`, `max` fonksiyonlarını **fonksiyon
template**'i olarak yazmak. Aynı kod hem `int` hem `std::string` hem
de karşılaştırma operatörlerine sahip herhangi bir tip için tekrar
yazılmadan çalışmalı.

## Neden template?
- C'de (ya da template'siz C++'ta) her tip için ayrı `swapInt`,
  `swapString` fonksiyonu yazman gerekirdi — kod tekrarı ve bakım
  yükü.
- Template, derleyiciye "bu fonksiyonun şablonunu tut, hangi tiple
  çağrılırsa o tip için gerçek fonksiyonu **sen üret**" der. Bu işleme
  **template instantiation** denir ve **derleme zamanında** olur —
  runtime'da hiçbir maliyeti yoktur (generic'lik "bedava").
- Şablon sadece `<`, `=` gibi operatörlerin var olduğunu varsayar;
  tip güvenliği yine derleme zamanında kontrol edilir (`std::string`
  `<` operatörünü desteklediği için `min`/`max` onunla da çalışır).

## Sistem seviyesinde bilinmesi gerekenler
1. **Template'ler header'da tanımlanmak zorunda**: Derleyici, bir
   template fonksiyonunu ancak *kullanıldığı* yerde, hangi tiple
   çağrıldığını görünce somutlaştırabilir (instantiate). Eğer
   implementasyon bir `.cpp` dosyasında olsaydı, o `.cpp` ayrı
   derlendiğinde (translation unit) hangi tiplerle kullanılacağını
   bilemezdi → linker "tanımsız referans" hatası verirdi. Bu yüzden
   normal fonksiyonlarda header'a implementasyon koymak yasakken,
   template'lerde bu bir istisna değil, bir **zorunluluk**.
2. **Reference parametre şart**: `swap(T &a, T &b)` referans
   almazsa fonksiyon içindeki `a`, `b` çağıranın değişkenlerinin
   kopyası olur; orijinal değişmez. `min`/`max`'ta `T const &`
   dönmek de gereksiz kopyalamayı (özellikle `std::string` gibi
   pahalı tiplerde) önler — sadece bir adres/referans döner.
3. **Eşitlik durumunda "ikinciyi döndür" kuralı**: `min` için
   `b < a ? b : a`, `max` için `a < b ? b : a` yazımı, `a == b`
   olduğunda otomatik olarak ikinci parametreyi seçer — ayrı bir
   `if (a == b)` dalına gerek kalmadan, tek bir karşılaştırma
   operatörüyle (`<`) hem min hem max hem de eşitlik davranışı elde
   edilir. Bu da subject'in "sadece `<` operatörü desteklensin
   yeter" kısıtına uyar (`==` gerektirmez).
4. **`::` ile çağırmanın anlamı**: `::swap(a, b)` global namespace'e
   ait `swap`'ı çağırır. Bu, ileride `std::swap` gibi başka bir
   `swap` ile isim çakışması (overload resolution belirsizliği)
   olmasın diye önemli — subject'in test kodunda bilinçli olarak
   kullanılıyor.
