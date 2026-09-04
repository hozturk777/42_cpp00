# ex02 — Identify real type

## Amaç
`Base` pointer/reference'ı arkasındaki **gerçek** (dynamic) tipin `A`,
`B` yoksa `C` olduğunu, `<typeinfo>` include etmeden, RTTI mekanizmasını
kullanarak tespit etmek.

## Neden dynamic_cast?
- `static_cast` **derleme zamanında** karar verir; base→derived cast'te
  "bu pointer gerçekten o türden mi" diye **çalışma zamanında kontrol
  etmez** — yanlış tahmin edersen UB. Burada gerçek tip elimizde değil
  (rastgele üretiliyor), yani çalışma zamanı kontrolü şart.
- `dynamic_cast` tam bunun için var: base↔derived arasında, **çalışma
  zamanında** RTTI bilgisine bakarak "bu obje gerçekten bu tipte mi"
  diye kontrol eder.
  - Pointer'da başarısız olursa **NULL** döner (exception atmaz).
  - Reference'ta başarısız olursa **`std::bad_cast` exception fırlatır**
    (çünkü referans hiçbir zaman NULL olamaz, dönecek "geçersiz" bir
    değer yok).
- `reinterpret_cast`/`static_cast` burada güvensiz olurdu: tip kontrolü
  yapmadan pointer'ı olduğu gibi yeniden yorumlarlar, yanlış tipte
  okuma/UB riski taşırlar.

## Sistem seviyesinde bilinmesi gerekenler
1. **RTTI (Run-Time Type Information)**: bir sınıfın en az bir `virtual`
   fonksiyonu (burada `~Base()`) olması, derleyicinin her nesneye gizli
   bir **vtable pointer** koymasını sağlar. `dynamic_cast` işte bu
   vtable üzerinden gerçek tipi çözer. Virtual fonksiyon olmasaydı
   `dynamic_cast` derleme hatası verirdi — polymorphic olmayan bir
   sınıfta "gerçek tip" kavramı yoktur.
2. **`<typeinfo>` dolaylı olarak hep vardır**: `dynamic_cast` ve
   `std::bad_cast` dil düzeyinde derleyici tarafından desteklenir,
   `<typeinfo>` header'ını **biz include etmesek de** derleyici RTTI
   verisini zaten üretir. Subject'in yasakladığı, bizim bu header'ı
   **elle** include edip `typeid` gibi araçları kullanmamız.
3. **`catch(...)` ile bad_cast'i "isimsiz" yakalamak**: `std::bad_cast`
   tipinin adını yazmak `<typeinfo>` include etmeyi gerektirir. Bunun
   yerine generic `catch (...)` kullanarak, hangi exception olduğunu
   hiç sormadan "başarısız oldu" bilgisini yakalıyoruz — header'a hiç
   dokunmadan.
4. **pointer vs reference farkı, tasarım kararı olarak öğretici**:
   pointer API'sinde "başarısız" durumu doğal bir NULL değeriyle
   ifade edilebiliyor. Reference'ta böyle bir "geçersiz referans"
   kavramı olmadığı için dil, exception mekanizmasına başvurmak
   zorunda kalıyor. Aynı RTTI sorgusunun iki farklı hata modeli
   (NULL dönüş vs exception) olması, C++'ın pointer/reference
   felsefesindeki temel farkı gösteriyor.
5. **`new`/`delete` dengesi**: `generate()` her çağrıda `new` ile bir
   nesne üretiyor; `main`'de her `delete p` ile serbest bırakılıyor.
   `Base`'in destructor'ının `virtual` olması burada kritik: `delete`
   bir `Base*` üzerinden çağrılsa bile, gerçek tipin (`A`/`B`/`C`)
   destructor'ı doğru çalışır. Virtual olmasaydı, sadece `Base`'in
   destructor'ı çalışır ve türetilmiş sınıfa ait kaynaklar (varsa)
   sızardı.
