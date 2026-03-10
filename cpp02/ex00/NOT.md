### const static int _bits = 8;
> static olduğu için bu değişken her nesne için ayrı ayrı bellekte yer kaplamaz sınıfın tüm nesneleri için tek bellek adresi kullanılır.

### ---------

### int getRawBits( void ) const;
> const olması bu sınıftaki hiç bir değişkeni değiştiremeyeceğini(read-only) gösterir.

### ---------

> C++'ta bir sınıf yazdığında, sen yazmasan bile derleyici senin yerine varsayılan bir kopyalama yapıcısı ve atama operatörü oluşturur. Ancak derleyicinin otomatik oluşturduğu bu fonksiyonlar, sadece yüzeysel kopyalama (shallow copy) yapar.
> Eğer sınıfın içinde dinamik bellek (pointer) veya özel kaynak yönetimi varsa, iki farklı nesne aynı bellek adresini göstermeye başlar.
> Nesnelerden biri yok edildiğinde (destructor), diğeri çöp bir adresi göstermeye devam eder; bu da segmentation fault veya memory leak (bellek sızıntısı) ile sonuçlanır.

### ---------

> Özellikle Fixed sınıfı (Modül 02) bir sayı tipini temsil eder. Bir tam sayı (int) değişkenini başka bir değişkene kopyalayabildiğin gibi (a = b), kendi yazdığın Fixed sınıfını da güvenle kopyalayabilmelisin.
> Copy Constructor: Bir nesneyi başka bir nesneden "doğurmanı" sağlar (Fixed a(b);).
> Copy Assignment Operator: Mevcut bir nesnenin içeriğini başka bir nesneyle "güncellemeni" sağlar (a = b;).