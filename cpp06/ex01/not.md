# ex01 — Serializer

## Amaç
Bir `Data*` pointer'ını `uintptr_t` (bir tamsayı) tipine çevirip geri
pointer'a döndürmek. Amaç, bellek adresinin sadece bir sayı olduğunu ve
tip sisteminin derleyici tarafından dayatılan bir soyutlama olduğunu
göstermek.

## Neden reinterpret_cast?
- `static_cast` burada **kullanılamaz**: pointer ile integer arasında
  "mantıklı"/ilişkili bir dönüşüm yoktur (int↔float gibi örtük bir
  ilişki yok), derleyici bu ikisini birbirine static_cast ile
  çeviremez.
- `reinterpret_cast` tam olarak bunun için var: bir bit kalıbını
  **hiç değiştirmeden**, sadece "bundan böyle bu tipmiş gibi davran"
  der. Pointer↔integer, pointer↔alakasız pointer tipi gibi düşük
  seviyeli, platforma bağlı dönüşümlerde kullanılır.
- `dynamic_cast`: sadece polymorphic (virtual fonksiyonlu) sınıf
  hiyerarşilerinde RTTI ile çalışır, burada uygulanamaz (ex02'de
  kullanılacak).
- `const_cast`: sadece const/volatile eklemek/kaldırmak için, tip
  değişikliğiyle ilgisi yok.

## Sistem seviyesinde bilinmesi gerekenler
1. **uintptr_t nedir**: bir pointer'ı bilgi kaybı olmadan tutabilecek
   büyüklükte, implementation-defined bir unsigned integer tipidir.
   `<stdint.h>` içinde tanımlıdır (C99 kökenli; C++98'de standart
   değildir ama fiilen tüm derleyiciler/libc'ler sağlar — bu yüzden
   subject'te "Forbidden: None" deniyor, harici kütüphane sayılmıyor).
   64-bit sistemde genelde `unsigned long` büyüklüğündedir.
2. **Pointer sadece bir adres**: `serialize()` pointer'ın gösterdiği
   bellek adresini bir sayıya çevirir; `deserialize()` aynı sayıyı
   tekrar pointer olarak yorumlar. Aradaki `Data` nesnesinin kendisi
   hiç kopyalanmaz/taşınmaz — round-trip sonunda aynı adrese işaret
   ettiğimiz için `restored->id`, `->name`, `->value` hâlâ orijinal
   nesnenin verileridir.
3. **Round-trip garantisi (C++98 standardına göre)**: bir pointer'ı
   `uintptr_t`'ye çevirip tekrar aynı pointer tipine geri çevirmek,
   orijinal pointer ile eşit bir değer üretir — standart bunu garanti
   eder. Ama araya giren integer değeri aritmetik olarak
   değiştirirseniz (`raw + 1` gibi) bu garanti biter, UB'ye girersiniz.
4. **Neden Data non-empty olmalı**: struct'ın en az bir üyesi olmazsa
   (boş struct), derleme geçse de "gerçek bir nesneyi serialize
   ediyoruz" fikri anlamsızlaşır — subject bilinçli olarak veri
   taşınan gerçek bir nesne üzerinde test yaptırıyor.
5. **Neden sınıf instantiate edilemez**: `Serializer`'ın hiç state'i
   yok; constructor/copy/operator= `private` yapılarak sadece
   "static fonksiyon grubu" (utility class) olarak kullanılması
   zorlanıyor — ex00'daki `ScalarConverter` ile aynı pattern.
