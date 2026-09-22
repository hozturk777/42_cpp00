# cpp06 — Amaç

cpp06'nın amacı: C++'ın dört farklı cast türünü (`static_cast`, `dynamic_cast`,
`reinterpret_cast`, `const_cast`) pratikte ne zaman/nasıl kullanacağını
öğretmek.

- **ex00**: aritmetik/skaler tipler arası güvenli dönüşüm → `static_cast`
- **ex01**: pointer↔integer gibi ilişkisiz tipler arası bit-seviyesi dönüşüm
  → `reinterpret_cast`
- **ex02**: polymorphic sınıf hiyerarşisinde çalışma zamanında gerçek tipi
  tespit etme → `dynamic_cast`

Kısacası: C-style cast'in (`(int)x`) her şeyi sessizce yapabildiği tehlikeli
esnekliğinden kurtulup, her cast'in niyetini kodda açıkça belli eden,
derleyicinin de hatalı kullanımı yakalayabildiği C++ cast sistemini
öğretiyor.
