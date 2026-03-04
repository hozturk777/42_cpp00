# C++ - Modül 02

## Ad-hoc çok biçimlilik, operatör aşırı yükleme

## ve Ortodoks Kanonik sınıf formu

_Özet: Bu belge, C++ modüllerinden Modül 02'nin alıştırmalarını içerir._

```
Versiyon: 9.
```

## İçindekiler

- I Giriş
- II Genel kurallar
- III Yeni kurallar
- IV Yapay Zeka Talimatları
- V Alıştırma 00: Ortodoks Kanonik Formda İlk Sınıfım
- VI Alıştırma 01: Daha kullanışlı bir sabit noktalı sayı sınıfına doğru
- VII Alıştırma 02: Şimdi konuşuyoruz
- VIII Alıştırma 03: BSP
- IX Teslim ve Akran Değerlendirmesi


# Bölüm I

# Giriş

_C++, Bjarne Stroustrup tarafından C programlama dilinin bir uzantısı olarak veya "Sınıflarla C" olarak oluşturulmuş genel amaçlı bir programlama dilidir (kaynak: Wikipedia)._

Bu modüllerin amacı, sizi **Nesne Yönelimli Programlama**'ya tanıştırmaktır.
Bu, C++ yolculuğunuzun başlangıç noktası olacaktır. OOP öğrenmek için birçok dil önerilir, ancak eski dostunuz C'den türetildiği için C++ seçmeye karar verdik. Bu karmaşık bir dil olduğundan ve işleri basit tutmak için, kodunuz C++98 standardına uygun olacaktır.
Modern C++'ın birçok açıdan oldukça farklı olduğunun farkındayız. Bu nedenle, yetenekli bir C++ geliştiricisi olmak istiyorsanız, 42 Common Core'dan sonra daha ileri gitmeniz size kalmıştır!


# Bölüm II

# Genel kurallar

**Derleme**

- Kodunuzu c++ ve -Wall -Wextra -Werror bayraklarıyla derleyin
- -std=c++98 bayrağını eklerseniz kodunuz yine de derlenmeli

```
Biçimlendirme ve adlandırma kuralları
```
- Alıştırma dizinleri şu şekilde adlandırılacaktır: ex00, ex01, ... , exn
- Dosyalarınızı, sınıflarınızı, fonksiyonlarınızı, üye fonksiyonlarınızı ve özelliklerinizi
    yönergelerde belirtildiği gibi adlandırın.
- Sınıf isimlerini **UpperCamelCase** formatında yazın. Sınıf kodu içeren dosyalar
    her zaman sınıf adına göre adlandırılacaktır. Örneğin:
    ClassName.hpp/ClassName.h, ClassName.cpp veya ClassName.tpp. Yani, bir
    tuğla duvarı temsil eden "BrickWall" sınıfının tanımını içeren bir başlık dosyanız varsa,
    adı BrickWall.hpp olacaktır.
- Aksi belirtilmedikçe, her çıktı mesajı yeni satır karakteriyle bitmeli
    ve standart çıktıya gösterilmelidir.
- _Güle güle Norminette!_ C++ modüllerinde kodlama stili zorunlu değildir.
    Favori stilinizi takip edebilirsiniz. Ancak akran değerlendiricilerinizin anlayamadığı
    kodun notlandıramayacakları kod olduğunu unutmayın. Temiz ve okunabilir kod yazmak için
    elinizden gelenin en iyisini yapın.

```
İzin Verilen/Yasak
```
```
Artık C'de kodlama yapmıyorsunuz. C++ zamanı! Bu nedenle:
```
- Standart kütüphaneden neredeyse her şeyi kullanmanıza izin verilir. Bu nedenle,
    zaten bildiğiniz şeylere bağlı kalmak yerine, mümkün olduğunca alışkın olduğunuz C
    fonksiyonlarının C++'a özgü versiyonlarını kullanmak akıllıca olacaktır.
- Ancak, başka bir harici kütüphane kullanamazsınız. Bu, C++11 (ve türetilmiş
    formlar) ve Boost kütüphanelerinin yasak olduğu anlamına gelir. Aşağıdaki fonksiyonlar
    da yasaktır: *printf(), *alloc() ve free(). Bunları kullanırsanız, notunuz 0 olacak
    ve o kadar.


C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
- Aksi açıkça belirtilmedikçe, using namespace <ns_name> ve
    friend anahtar kelimelerinin yasak olduğunu unutmayın. Aksi takdirde, notunuz -42 olacaktır.
- **STL'yi yalnızca Modül 08 ve 09'da kullanmanıza izin verilir.** Bu şu anlama gelir:
    **Konteyner** yok (vector/list/map ve benzeri) ve **Algoritma** yok (o zamana kadar <algorithm>
    başlığını içeren herhangi bir şey) yok. Aksi takdirde, notunuz -42 olacaktır.

```
Birkaç tasarım gereksinimi
```
- Bellek sızıntısı C++'da da oluşur. Bellek tahsis ettiğinizde (new
    anahtar kelimesini kullanarak), **bellek sızıntılarından** kaçınmalısınız.
- Modül 02'den Modül 09'a kadar, sınıflarınız **Ortodoks**
    **Kanonik Formda** tasarlanmalıdır, aksi açıkça belirtilmedikçe.
- Bir başlık dosyasına konulan herhangi bir fonksiyon uygulaması (fonksiyon şablonları hariç)
    alıştırma için 0 anlamına gelir.
- Her başlığınızı diğerlerinden bağımsız olarak kullanabilmelisiniz. Bu nedenle,
    ihtiyaç duydukları tüm bağımlılıkları içermeleri gerekir. Ancak, **include guard'ları**
    ekleyerek çift dahil etme sorununu önlemelisiniz. Aksi takdirde, notunuz 0 olacaktır.

```
Beni oku
```
- İhtiyacınız varsa bazı ek dosyalar ekleyebilirsiniz (örneğin, kodunuzu bölmek için).
    Bu ödevler bir program tarafından doğrulanmadığından, zorunlu dosyaları teslim ettiğiniz
    sürece bunu yapmaktan çekinmeyin.
- Bazen, bir alıştırmanın yönergeleri kısa görünür ancak örnekler
    talimatlarda açıkça yazılmayan gereksinimleri gösterebilir.
- Başlamadan önce her modülü tamamen okuyun! Gerçekten, yapın.
- Odin'e, Thor'a yemin olsun! Beyninizi kullanın!!!

```
C++ projeleri için Makefile ile ilgili olarak, C'deki kurallar geçerlidir
(Makefile hakkındaki Norm bölümüne bakın).
```
```
Birçok sınıf uygulamanız gerekecek. Bu sıkıcı görünebilir,
favori metin düzenleyicinizi komut dosyası haline getirebilirseniz.
```

C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
```
Alıştırmaları tamamlamak için size belirli bir özgürlük verilir.
Ancak, zorunlu kuralları izleyin ve tembel olmayın. Birçok
yararlı bilgiyi kaçırırsınız! Teorik kavramlar hakkında
okumaktan çekinmeyin.
```

# Bölüm III

# Yeni kurallar

Şu andan itibaren, tüm sınıflarınız **Ortodoks Kanonik Formda** tasarlanmalıdır,
aksi açıkça belirtilmedikçe. Daha sonra aşağıdaki dört gerekli üye fonksiyonu uygulayacaklardır:

- Varsayılan yapıcı
- Kopya yapıcı
- Kopya atama operatörü
- Yıkıcı

Sınıf kodunuzu iki dosyaya bölün. Başlık dosyası (.hpp/.h) sınıf
tanımını içerirken, kaynak dosyası (.cpp) uygulamayı içerir.


# Bölüm IV

# Yapay Zeka Talimatları

## ● Bağlam

Bu proje, 42 eğitiminizin temel yapı taşlarını keşfetmenize yardımcı olmak için tasarlanmıştır.

Temel bilgi ve becerileri düzgün bir şekilde yerleştirmek için, yapay zeka araçlarını ve desteğini
kullanırken düşünceli bir yaklaşım benimsemek önemlidir.

Gerçek temel öğrenme, gerçek entelektüel çaba gerektirir - meydan okuma, tekrar
ve akran öğrenme alışverişleri yoluyla.

Yapay zeka hakkındaki tutumumuzun daha eksiksiz bir genel bakışı için - bir öğrenme aracı olarak,
42 eğitiminin bir parçası olarak ve iş piyasasında bir beklenti olarak - lütfen intranetteki
özel SSS'ye bakın.

## ● Ana mesaj

```
☛ Kestirme yollar olmadan güçlü temeller oluşturun.
```
```
☛ Gerçekten teknik ve güç becerileri geliştirin.
```
```
☛ Gerçek akran öğrenimini deneyimleyin, nasıl öğreneceğinizi ve yeni sorunları nasıl çözeceğinizi öğrenmeye başlayın.
```
```
☛ Öğrenme yolculuğu sonuçtan daha önemlidir.
```
```
☛ Yapay zeka ile ilişkili riskler hakkında bilgi edinin ve yaygın tuzaklardan kaçınmak için etkili
kontrol uygulamaları ve karşı önlemler geliştirin.
```
## ● Öğrenci kuralları:

- Size verilen görevlere akıl yürütmeyi uygulamalısınız, özellikle yapay zekaya başvurmadan önce.


C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
- Yapay zekadan doğrudan cevaplar istememeli siniz.
- Yapay zeka konusunda 42'nin genel yaklaşımını öğrenmelisiniz.

● **Faz sonuçları:**

Bu temel aşamada aşağıdaki sonuçları elde edeceksiniz:

- Uygun teknik ve kodlama temelleri edinin.
- Yapay zekanın bu aşamada neden ve nasıl tehlikeli olabileceğini bilin.

● **Yorumlar ve örnek:**

- Evet, yapay zekanın var olduğunu biliyoruz - ve evet, projelerinizi çözebilir. Ancak buraya
    öğrenmek için geldiniz, yapay zekanın öğrendiğini kanıtlamak için değil. Sadece yapay zekanın
    verilen sorunu çözebileceğini göstermek için zamanınızı (veya bizimkini) boşa harcamayın.
- 42'de öğrenmek cevabı bilmekle ilgili değildir - birini bulma yeteneği geliştirmekle ilgilidir.
    Yapay zeka size doğrudan cevabı verir, ancak bu kendi akıl yürütmenizi oluşturmanızı engeller.
    Ve akıl yürütme zaman, çaba alır ve başarısızlığı içerir. Başarıya giden yolun kolay olması
    beklenmez.
- Sınavlarda yapay zekanın mevcut olmadığını unutmayın - internet yok, akıllı telefon yok,
    vb. Öğrenme sürecinizde yapay zekaya çok fazla güvendiyseniz bunu hızlıca fark edeceksiniz.
- Akran öğrenimi sizi farklı fikirlere ve yaklaşımlara maruz bırakır, kişilerarası becerilerinizi
    ve farklı düşünme yeteneğinizi geliştirir. Bu, sadece bir bot ile sohbet etmekten çok daha
    değerlidir. Bu yüzden utanmayın - konuşun, sorular sorun ve birlikte öğrenin!
- Evet, yapay zeka müfredatın bir parçası olacak - hem bir öğrenme aracı olarak hem de kendi
    başına bir konu olarak. Hatta kendi yapay zeka yazılımınızı oluşturma şansınız olacak.
    İnranette mevcut dokümantasyonda geçeceğiniz crescendo yaklaşımımız hakkında daha fazla
    bilgi edinmek için.

```
✓ İyi uygulama:
```
```
Yeni bir kavramda takıldım. Yakındaki birine nasıl yaklaştıklarını soruyorum. 10 dakika konuşuyoruz
- ve aniden anlıyorum. Anladım.
```
```
✗ Kötü uygulama:
```
```
Gizlice yapay zeka kullanıyorum, doğru görünen bir kod kopyalıyorum. Akran değerlendirmesi
sırasında hiçbir şeyi açıklayamıyorum. Başarısız oluyorum. Sınav sırasında - yapay zeka yok -
tekrar takılıyorum. Başarısız oluyorum.
```

# Bölüm V

# Alıştırma 00: Ortodoks Kanonik Formda

# İlk Sınıfım

```
Alıştırma: 00
```
```
Ortodoks Kanonik Formda İlk Sınıfım
Dizin: ex 00 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Yasak: Hiçbiri
```
```
Tamsayıları ve kayan noktalı sayıları bildiğinizi düşünüyorsunuz. Ne kadar sevimli.
```
```
Lütfen bilmediğinizi keşfetmek için bu 3 sayfalık makaleyi (1, 2, 3) okuyun. Devam edin, okuyun.
```
Bugüne kadar, kodunuzda kullandığınız her sayı temelde ya bir tamsayı ya da kayan noktalı
bir sayıydı veya bunların varyantlarından herhangi biriydi (short, char, long, double ve benzeri).
Yukarıdaki makaleyi okuduktan sonra, tamsayıların ve kayan noktalı sayıların zıt
özelliklere sahip olduğunu varsaymak güvenlidir.

Ancak bugün, işler değişecek. Yeni ve harika bir sayı
türünü keşfedeceksiniz: **sabit noktalı sayılar**! Çoğu dilin skaler türlerinde kalıcı olarak eksik olan
sabit noktalı sayılar, performans, doğruluk, aralık ve
hassasiyet arasında değerli bir denge sunar. Bu, sabit noktalı sayıların özellikle bilgisayar
grafiklerine, ses işlemeye veya bilimsel programlamaya uygulanabilir olmasını açıklar.

C++'da sabit noktalı sayılar eksik olduğundan, onları ekleyeceksiniz. Bu Berkeley'den
gelen makale iyi bir başlangıçtır. Berkeley Üniversitesi'nin ne olduğu hakkında hiçbir fikriniz
yoksa, Wikipedia sayfasının bu bölümünü okuyun.


C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
```
Sabit noktalı bir sayıyı temsil eden Ortodoks Kanonik Formda bir sınıf oluşturun:
```
- Özel üyeler:

```
◦ Sabit noktalı sayı değerini depolamak için bir tamsayı.
◦ Kesirli bit sayısını depolamak için statik bir sabit tamsayı. Değeri
her zaman 8 tamsayı literali olacaktır.
```
- Genel üyeler:

```
◦ Sabit noktalı sayı değerini 0'a başlatan varsayılan bir yapıcı.
◦ Bir kopya yapıcı.
◦ Bir kopya atama operatörü aşırı yüklemesi.
◦ Bir yıkıcı.
◦ int getRawBits( void ) const; üye fonksiyonu
sabit noktalı değerin ham değerini döndürür.
◦ void setRawBits( int const raw ); üye fonksiyonu
sabit noktalı sayının ham değerini ayarlar.
```
```
Bu kodu çalıştırmak:
#include <iostream>
int main( void ) {
Fixed a;
Fixed b( a );
Fixed c;
c = b;
std::cout << a.getRawBits() << std::endl;
std::cout << b.getRawBits() << std::endl;
std::cout << c.getRawBits() << std::endl;
return 0;
}
```
```
Şuna benzer bir şey çıkmalı:
$> ./a.out
Default constructor called
Copy constructor called
Copy assignment operator called // <-- Bu satır uygulamanıza bağlı olarak eksik olabilir
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
$>
```

# Bölüm VI

# Alıştırma 01: Daha kullanışlı bir

# sabit noktalı sayı sınıfına doğru

```
Alıştırma
```
```
Daha kullanışlı bir sabit noktalı sayı sınıfına doğru
Dizin: ex 01 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Yetkili: roundf (<cmath>'den)
```
Önceki alıştırma iyi bir başlangıçtı, ancak sınıfımız oldukça işe yaramaz. Yalnızca
0.0 değerini temsil edebiliyor.

```
Sınıfınıza aşağıdaki genel yapıcıları ve genel üye fonksiyonlarını ekleyin:
```
- Parametre olarak **sabit bir tamsayı** alan bir yapıcı.
    Onu karşılık gelen sabit noktalı değere dönüştürür. Kesirli bit değeri
    alıştırma 00'daki gibi 8'e başlatılmalıdır.
- Parametre olarak **sabit bir kayan noktalı sayı** alan bir yapıcı.
    Onu karşılık gelen sabit noktalı değere dönüştürür. Kesirli bit değeri
    alıştırma 00'daki gibi 8'e başlatılmalıdır.
- float toFloat( void ) const; üye fonksiyonu
    sabit noktalı değeri kayan noktalı bir değere dönüştürür.
- int toInt( void ) const; üye fonksiyonu
    sabit noktalı değeri bir tamsayı değerine dönüştürür.

```
Ve Fixed sınıf dosyalarına aşağıdaki fonksiyonu ekleyin:
```
- Parametre olarak geçirilen çıktı akışı nesnesine sabit noktalı sayının kayan noktalı bir
    temsilini ekleyen ekleme («) operatörünün bir aşırı yüklemesi.


C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
```
Bu kodu çalıştırmak:
```
```
#include <iostream>
int main( void ) {
Fixed a;
Fixed const b( 10 );
Fixed const c( 42.42f );
Fixed const d( b );
a = Fixed( 1234.4321f );
std::cout << "a is " << a << std::endl;
std::cout << "b is " << b << std::endl;
std::cout << "c is " << c << std::endl;
std::cout << "d is " << d << std::endl;
std::cout << "a is " << a.toInt() << " as integer" << std::endl;
std::cout << "b is " << b.toInt() << " as integer" << std::endl;
std::cout << "c is " << c.toInt() << " as integer" << std::endl;
std::cout << "d is " << d.toInt() << " as integer" << std::endl;
return 0;
}
```
```
Şuna benzer bir şey çıkmalı:
$> ./a.out
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.
b is 10
c is 42.
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
$>
```

# Bölüm VII

# Alıştırma 02: Şimdi konuşuyoruz

```
Alıştırma
```
```
Şimdi konuşuyoruz
Dizin: ex 02 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Yetkili: roundf (<cmath>'den)
```
```
Aşağıdaki operatörleri aşırı yüklemek için sınıfınıza genel üye fonksiyonları ekleyin:
```
- 6 karşılaştırma operatörü: >, <, >=, <=, == ve !=.
- 4 aritmetik operatör: +, -, *, ve /.
- 4 artırma/azaltma (ön artırma ve son artırma, ön azaltma ve
    son azaltma) operatörü, sabit noktalı değeri temsil edilebilir en küçük _ε_ ile artıracak veya
    azaltacaktır, öyle ki 1 + _ε >_ 1.

```
Sınıfınıza bu dört genel aşırı yüklenmiş üye fonksiyonu ekleyin:
```
- Parametre olarak iki sabit noktalı sayı referansı alan ve en küçüğüne bir referans
    döndüren statik bir min üye fonksiyonu.
- Parametre olarak iki **sabit** sabit noktalı sayı referansı alan ve en küçüğüne bir referans
    döndüren statik bir min üye fonksiyonu.
- Parametre olarak iki sabit noktalı sayı referansı alan ve en büyüğüne bir referans
    döndüren statik bir max üye fonksiyonu.
- Parametre olarak iki **sabit** sabit noktalı sayı referansı alan ve en büyüğüne bir referans
    döndüren statik bir max üye fonksiyonu.


C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
```
Sınıfınızın her özelliğini test etmek size kalmıştır. Ancak, aşağıdaki kodu çalıştırmak:
```
```
#include <iostream>
int main( void ) {
Fixed a;
Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;
std::cout << b << std::endl;
std::cout << Fixed::max( a, b ) << std::endl;
return 0;
}
```
Şuna benzer bir şey çıkmalı (daha fazla okunabilirlik için, aşağıdaki örnekte yapıcı/yıkıcı mesajları
kaldırılmıştır):

```
$> ./a.out
0
0.
0.
0.
0.
10.
10.
$>
```
```
0'a bölme yaparsanız, programın çökmesinin kabul edilebilir olduğu
```

# Bölüm VIII

# Alıştırma 03: BSP

```
Alıştırma
```
```
BSP
Dizin: ex 03 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp,
Point.{h, hpp}, Point.cpp, bsp.cpp
Yetkili: roundf (<cmath>'den)
```
```
Artık işlevsel bir Fixed sınıfınız olduğuna göre, onu kullanmak güzel olurdu.
```
Bir noktanın bir üçgenin içinde olup olmadığını gösteren bir fonksiyon uygulayın. Çok
kullanışlı, değil mi?

```
BSP, Binary Space Partitioning anlamına gelir. Rica ederiz. :)
```
```
Alıştırma 03'ü tamamlamadan bu modülü geçebilirsiniz.
```

C++ - Modül 02

```
Ad-hoc çok biçimlilik, operatör aşırı yükleme
ve Ortodoks Kanonik sınıf formu
```
2D bir noktayı temsil eden Ortodoks Kanonik Formda **Point** sınıfını oluşturarak
başlayalım:

- Özel üyeler:

```
◦ Fixed const özelliği x.
◦ Fixed const özelliği y.
◦ Yararlı olan başka bir şey.
```
- Genel üyeler:

```
◦ x ve y'yi 0'a başlatan varsayılan bir yapıcı.
◦ Parametre olarak iki sabit kayan noktalı sayı alan bir yapıcı.
x ve y'yi bu parametrelerle başlatır.
◦ Bir kopya yapıcı.
◦ Bir kopya atama operatörü aşırı yüklemesi.
◦ Bir yıkıcı.
◦ Yararlı olan başka bir şey.
```
```
Sonuç olarak, aşağıdaki fonksiyonu uygun dosyada uygulayın:
```
```
bool bsp( Point const a, Point const b, Point const c, Point const point);
```
- a, b, c: Sevgili üçgenimizin köşeleri.
- point: Kontrol edilecek nokta.
- Döndürür: Nokta üçgenin içindeyse True. Aksi takdirde False.
    Bu nedenle, nokta bir köşe veya bir kenar üzerindeyse, False döndürecektir.

```
Sınıfınızın beklendiği gibi davrandığından emin olmak için kendi testlerinizi uygulayın ve teslim edin.
```

# Bölüm IX

# Teslim ve Akran Değerlendirmesi

Ödevinizi her zamanki gibi Git deponuzda teslim edin. Savunma sırasında yalnızca deponuzdaki
çalışma değerlendirilecektir. Klasörlerinizin ve dosyalarınızın adlarının doğru olduğundan emin olmak
için iki kez kontrol etmekten çekinmeyin.

Değerlendirme sırasında, **projenin kısa bir modifikasyonu** ara sıra istenebilir. Bu,
küçük bir davranış değişikliği, yazılacak veya yeniden yazılacak birkaç satır kod veya
eklenmesi kolay bir özellik içerebilir.

Bu adım **her proje için geçerli olmayabilir**, ancak değerlendirme yönergelerinde belirtilmişse
buna hazırlıklı olmalısınız.

Bu adım, projenin belirli bir bölümü hakkındaki gerçek anlayışınızı doğrulamak içindir.
Değişiklik seçtiğiniz herhangi bir geliştirme ortamında (örneğin,
olağan kurulumunuz) gerçekleştirilebilir ve birkaç dakika içinde yapılabilmelidir - belirli
bir zaman dilimi değerlendirmenin bir parçası olarak tanımlanmadıkça.
Örneğinden, bir fonksiyona veya betiğe küçük bir güncelleme yapmak, bir ekranı değiştirmek veya
yeni bilgileri depolamak için bir veri yapısını ayarlamak vb. istenebilir.

Ayrıntılar (kapsam, hedef, vb.) **değerlendirme yönergelerinde** belirtilecektir ve aynı proje
için bir değerlendirmeden diğerine değişebilir.
