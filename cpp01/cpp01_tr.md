# C++ - Modül 01

## Bellek tahsisi, üyelere işaretçiler,

## referanslar ve switch ifadeleri

_Özet:
Bu belge C++ modüllerinden Modül 01'in egzersizlerini içerir._

```
Versiyon: 11.
```

## İçindekiler

- I Giriş
- II Genel kurallar
- III YZ Talimatları
- IV Egzersiz 00: BraiiiiiiinnnzzzZ
- V Egzersiz 01: Daha fazla beyin!
- VI Egzersiz 02: MERHABA BU BEYİN
- VII Egzersiz 03: Gereksiz şiddet
- VIII Egzersiz 04: Sed kaybedenler içindir
- IX Egzersiz 05: Harl 2.0
- X Egzersiz 06: Harl filtresi
- XI Teslim ve akran değerlendirmesi


# Bölüm I

# Giriş

_C++, Bjarne Stroustrup tarafından C programlama dilinin bir uzantısı veya "Sınıflarla C" olarak oluşturulmuş genel amaçlı bir programlama dilidir (kaynak: Wikipedia)._

Bu modüllerin amacı sizi **Nesne Yönelimli Programlama** ile tanıştırmaktır.
Bu, C++ yolculuğunuzun başlangıç noktası olacaktır. OOP öğrenmek için birçok dil önerilir.
C++'ı seçtik çünkü eski dostunuz C'den türetilmiştir.
Bu karmaşık bir dil olduğundan ve işleri basit tutmak için, kodunuz
C++98 standardına uygun olacaktır.
Modern C++'ın birçok açıdan çok farklı olduğunun farkındayız. Bu yüzden eğer
yetkin bir C++ geliştiricisi olmak istiyorsanız, 42 Common
Core'dan sonra daha ileri gitmeniz size kalmıştır!


# Bölüm II

# Genel kurallar

**Derleme**

- Kodunuzu c++ ile ve -Wall -Wextra -Werror bayraklarıyla derleyin
- -std=c++ bayrağını eklerseniz kodunuz yine de derlenmeli

```
Biçimlendirme ve adlandırma kuralları
```
- Egzersiz dizinleri şu şekilde adlandırılacaktır: ex00, ex01, ... , exn
- Dosyalarınızı, sınıflarınızı, fonksiyonlarınızı, üye fonksiyonlarınızı ve özniteliklerinizi
    kılavuzlarda gerektiği gibi adlandırın.
- Sınıf isimlerini **UpperCamelCase** formatında yazın. Sınıf kodunu içeren dosyalar
    her zaman sınıf adına göre adlandırılacaktır. Örneğin:
    ClassName.hpp/ClassName.h, ClassName.cpp, veya ClassName.tpp. O halde, eğer
    bir tuğla duvarı temsil eden "BrickWall" sınıfının tanımını içeren bir başlık dosyanız varsa,
    adı BrickWall.hpp olacaktır.
- Aksi belirtilmedikçe, her çıktı mesajı yeni satır karakteri ile bitmelidir
    ve standart çıktıya gösterilmelidir.
- _Hoşçakal Norminette!_ C++ modüllerinde kodlama stili zorunlu değildir.
    Favori stilinizi takip edebilirsiniz. Ancak akran değerlendiricilerinizin anlayamadığı
    kodun not verilemeyeceğini unutmayın. Temiz ve okunabilir kod yazmak için elinizden geleni yapın.

```
İzin verilen/Yasak
```
```
Artık C'de kodlama yapmıyorsunuz. C++ zamanı! Bu nedenle:
```
- Standart kütüphaneden neredeyse her şeyi kullanmanıza izin verilir. Bu nedenle,
    zaten bildiklerinize bağlı kalmak yerine, mümkün olduğunca alıştığınız C fonksiyonlarının
    C++-ça versiyonlarını kullanmak akıllıca olacaktır.
- Ancak, başka bir harici kütüphane kullanamazsınız. Bu, C++11 (ve türevleri)
    ve Boost kütüphanelerinin yasak olduğu anlamına gelir. Aşağıdaki fonksiyonlar da
    yasaktır: *printf(), *alloc() ve free(). Bunları kullanırsanız, notunuz 0 olacaktır
    ve hepsi bu.


C++ - Modül 01

```
Bellek tahsisi, üyelere işaretçiler,
referanslar ve switch ifadeleri
```
- Aksi açıkça belirtilmedikçe, using namespace <ns_name> ve
    friend anahtar kelimeleri yasaktır. Aksi takdirde, notunuz -42 olacaktır.
- **STL'yi yalnızca Modül 08 ve 09'da kullanmanıza izin verilir.** Bu demektir ki:
    o zamana kadar **Konteyner** (vector/list/map ve benzeri) ve **Algoritma** (
    <algorithm> başlığını dahil etmeyi gerektiren herhangi bir şey) yok. Aksi takdirde, notunuz
    -42 olacaktır.

```
Birkaç tasarım gereksinimi
```
- C++'da da bellek sızıntısı olur. Bellek tahsis ettiğinizde (new
    anahtar kelimesini kullanarak), **bellek sızıntılarından** kaçınmalısınız.
- Modül 02'den Modül 09'a kadar, sınıflarınız **Ortodoks**
    **Kanonik Form**da tasarlanmalıdır, aksi açıkça belirtilmedikçe.
- Bir başlık dosyasına konulan herhangi bir fonksiyon uygulaması (fonksiyon şablonları hariç)
    egzersiz için 0 anlamına gelir.
- Her bir başlığınızı diğerlerinden bağımsız olarak kullanabilmelisiniz. Bu nedenle,
    ihtiyaç duydukları tüm bağımlılıkları içermeleri gerekir. Ancak, **include guard** ekleyerek
    çift dahil etme sorununu önlemelisiniz. Aksi takdirde, notunuz
    0 olacaktır.

```
Beni oku
```
- İhtiyacınız olursa bazı ek dosyalar ekleyebilirsiniz (örneğin, kodunuzu bölmek için).
    Bu ödevler bir program tarafından doğrulanmadığından, zorunlu dosyaları teslim ettiğiniz sürece
    bunu yapmaktan çekinmeyin.
- Bazen, bir egzersizin kılavuzları kısa görünür ancak örnekler
    talimatlarda açıkça yazılmamış gereksinimleri gösterebilir.
- Başlamadan önce her modülü tamamen okuyun! Gerçekten, yapın.
- Odin adına, Thor adına! Beyninizi kullanın!!!

```
C++ projeleri için Makefile ile ilgili olarak, C'dekilerle aynı kurallar geçerlidir
(Makefile hakkındaki Norm bölümüne bakın).
```
```
Bir sürü sınıf uygulamanız gerekecek. Bu sıkıcı görünebilir,
favori metin düzenleyicinizi betikleyebiliyorsanız olmadıkça.
```

C++ - Modül 01

```
Bellek tahsisi, üyelere işaretçiler,
referanslar ve switch ifadeleri
```
```
Egzersizleri tamamlamak için size belirli bir özgürlük verilmiştir.
Ancak, zorunlu kurallara uyun ve tembel olmayın. Bir sürü
yararlı bilgiyi kaçırırsınız! Teorik kavramlar hakkında okumaktan
çekinmeyin.
```

# Bölüm III

# YZ Talimatları

## ● Bağlam

Bu proje, 42 eğitiminizin temel yapı taşlarını keşfetmenize yardımcı olmak için tasarlanmıştır.

Temel bilgi ve becerileri düzgün bir şekilde yerleştirmek için, YZ araçlarını ve desteğini
kullanırken düşünceli bir yaklaşım benimsemek önemlidir.

Gerçek temel öğrenme, gerçek entelektüel çaba gerektirir — zorluk, tekrar
ve akran öğrenimi alışverişi yoluyla.

YZ hakkındaki duruşumuzun daha eksiksiz bir genel görünümü için — bir öğrenme aracı olarak,
42 eğitiminin bir parçası olarak ve iş piyasasında bir beklenti olarak — lütfen
intranetteki özel SSS'ye bakın.

## ● Ana mesaj

```
☛ Kısayollar olmadan güçlü temeller oluşturun.
```
```
☛ Gerçekten teknik ve güç becerileri geliştirin.
```
```
☛ Gerçek akran öğrenimini deneyimleyin, nasıl öğrenileceğini ve yeni problemlerin nasıl çözüleceğini öğrenmeye başlayın.
```
```
☛ Öğrenme yolculuğu sonuçtan daha önemlidir.
```
```
☛ YZ ile ilişkili riskler hakkında bilgi edinin ve yaygın tuzaklardan kaçınmak için etkili kontrol uygulamaları
ve karşı önlemler geliştirin.
```
## ● Öğrenci kuralları:

- Özellikle YZ'ye başvurmadan önce, atanan görevlerinize mantık yürütmelisiniz.


C++ - Modül 01

```
Bellek tahsisi, üyelere işaretçiler,
referanslar ve switch ifadeleri
```
- YZ'den doğrudan cevaplar istemememelisiniz.
- 42'nin YZ hakkındaki genel yaklaşımını öğrenmelisiniz.

● **Aşama çıktıları:**

Bu temel aşamada, aşağıdaki çıktıları elde edeceksiniz:

- Uygun teknik ve kodlama temelleri edinin.
- YZ'nin bu aşamada neden ve nasıl tehlikeli olabileceğini bilin.

● **Yorumlar ve örnek:**

- Evet, YZ'nin var olduğunu biliyoruz — ve evet, projelerinizi çözebilir. Ama buraya
    öğrenmek için geldiniz, YZ'nin öğrendiğini kanıtlamak için değil. Sadece YZ'nin
    verilen problemi çözebileceğini göstermek için zamanınızı (veya bizimkini) boşa harcamayın.
- 42'de öğrenmek cevabı bilmek hakkında değildir — bir cevap bulma yeteneğini
    geliştirmek hakkındadır. YZ size doğrudan cevabı verir, ancak bu kendi mantığınızı
    oluşturmanızı engeller. Ve mantık yürütmek zaman, çaba ve başarısızlık gerektirir.
    Başarıya giden yol kolay olmamalıdır.
- Sınavlar sırasında YZ'nin mevcut olmadığını unutmayın — internet yok, akıllı telefonlar yok,
    vb. Öğrenme sürecinizde YZ'ye çok güvenip güvenmediğinizi çabucak anlayacaksınız.
- Akran öğrenimi sizi farklı fikirlere ve yaklaşımlara maruz bırakır, kişilerarası
    becerilerinizi ve farklı düşünme yeteneğinizi geliştirir. Bu bir botla sohbet etmekten
    çok daha değerlidir. Bu yüzden utangaç olmayın — konuşun, sorular sorun ve birlikte öğrenin!
- Evet, YZ müfredatın bir parçası olacak — hem bir öğrenme aracı olarak hem de
    başlı başına bir konu olarak. Hatta kendi YZ yazılımınızı oluşturma şansınız olacak.
    İnternette mevcut belgelerde geçeceğiniz kademeli yaklaşım hakkında daha fazla
    bilgi edinmek için.

```
✓ İyi uygulama:
```
```
Yeni bir kavramda takıldım. Yakındaki birine nasıl yaklaştıklarını soruyorum. 10 dakika
konuşuyoruz — ve aniden anlaşılıyor. Anladım.
```
```
✗ Kötü uygulama:
```
```
Gizlice YZ kullanıyorum, doğru görünen bir kod kopyalıyorum. Akran değerlendirmesi sırasında,
hiçbir şeyi açıklayamıyorum. Başarısız oluyorum. Sınav sırasında — YZ yok — yine takılıyorum. Başarısız oluyorum.
```

# Bölüm IV

# Egzersiz 00: BraiiiiiiinnnzzzZ

```
Egzersiz: 00
```
```
BraiiiiiiinnnzzzZ
Dizin: ex 00 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Zombie.{h, hpp}, Zombie.cpp,
newZombie.cpp, randomChump.cpp
Yasak: Yok
```
Önce, bir **Zombie** sınıfı uygulayın. Özel bir string özniteliği name'e sahiptir.
Zombie sınıfına bir void announce( void ); üye fonksiyonu ekleyin. Zombiler
kendilerini şu şekilde duyururlar:

```
<name>: BraiiiiiiinnnzzzZ...
```
Açılı parantezleri (< ve >) yazdırmayın. Foo adlı bir zombi için mesaj şöyle olacaktır:

```
Foo: BraiiiiiiinnnzzzZ...
```
```
Ardından, aşağıdaki iki fonksiyonu uygulayın:
```
- Zombie* newZombie( std::string name );
    Bu fonksiyon bir zombi oluşturur, adlandırır ve onu fonksiyon kapsamı dışında
    kullanabilmeniz için döndürür.
- void randomChump( std::string name );
    Bu fonksiyon bir zombi oluşturur, adlandırır ve kendini duyurmasını sağlar.

Şimdi, egzersizin asıl amacı nedir? Zombileri yığın veya yığın üzerinde tahsis etmenin
hangi durumda daha iyi olduğunu belirlemelisiniz.

Zombiler artık ihtiyacınız olmadığında yok edilmelidir. Yıkıcı, hata ayıklama amacıyla
zombinin adını içeren bir mesaj yazdırmalıdır.


# Bölüm V

# Egzersiz 01: Daha fazla beyin!

```
Egzersiz: 01
```
```
Daha fazla beyin!
Dizin: ex 01 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Zombie.{h, hpp}, Zombie.cpp,
zombieHorde.cpp
Yasak: Yok
```
```
Bir Zombi sürüsü oluşturma zamanı!
```
```
Uygun dosyada aşağıdaki fonksiyonu uygulayın:
```
```
Zombie* zombieHorde( int N, std::string name );
```
Tek bir tahsiste N Zombie nesnesi tahsis etmelidir. Ardından, zombileri başlatmalı,
her birine parametre olarak geçirilen adı vermelidir. Fonksiyon, ilk zombiye bir
işaretçi döndürür.
zombieHorde() fonksiyonunuzun beklendiği gibi çalıştığından emin olmak için kendi testlerinizi uygulayın.
Her zombi için announce() çağırmayı deneyin.

Tüm zombileri serbest bırakmak için delete kullanmayı unutmayın ve **bellek
sızıntılarını** kontrol edin.


# Bölüm VI

# Egzersiz 02: MERHABA BU BEYİN

```
Egzersiz: 02
```
```
MERHABA BU BEYİN
Dizin: ex 02 /
Teslim Edilecek Dosyalar: Makefile, main.cpp
Yasak: Yok
```
```
Aşağıdakileri içeren bir program yazın:
```
- "HI THIS IS BRAIN" olarak başlatılan bir string değişkeni.
- stringPTR: string'e bir işaretçi.
- stringREF: string'e bir referans.

```
Programınız şunları yazdırmalıdır:
```
- String değişkeninin bellek adresi.
- stringPTR tarafından tutulan bellek adresi.
- stringREF tarafından tutulan bellek adresi.

```
Ve sonra:
```
- String değişkeninin değeri.
- stringPTR tarafından işaret edilen değer.
- stringREF tarafından işaret edilen değer.

Hepsi bu—hiç hile yok. Bu egzersizin amacı, tamamen yeni görünebilecek referansların
gizemini çözmektir. Bazı küçük farklılıklar olsa da, bu basitçe zaten yaptığınız bir şey için
başka bir sözdizimidir: adres manipülasyonu.


# Bölüm VII

# Egzersiz 03: Gereksiz şiddet

```
Egzersiz: 03
```
```
Gereksiz şiddet
Dizin: ex 03 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Weapon.{h, hpp}, Weapon.cpp, HumanA.{h,
hpp}, HumanA.cpp, HumanB.{h, hpp}, HumanB.cpp
Yasak: Yok
```
```
Aşağıdakilere sahip bir Weapon sınıfı uygulayın:
```
- Bir string olan özel bir type özniteliği.
- type'a sabit bir referans döndüren bir getType() üye fonksiyonu.
- Parametre olarak geçirilen yeni değeri kullanarak type'ı ayarlayan bir setType() üye fonksiyonu.

Şimdi, iki sınıf oluşturun: **HumanA** ve **HumanB**. Her ikisinin de bir Weapon ve
bir name'i var. Ayrıca (açılı parantezler olmadan) şunu görüntüleyen bir attack() üye fonksiyonları var:

```
<name> attacks with their <weapon type>
```
```
HumanA ve HumanB, bu iki küçük ayrıntı dışında neredeyse aynıdır:
```
- **HumanA** Weapon'ı yapıcısında alırken, **HumanB** almaz.
- **HumanB** **her zaman** silahı olmayabilir, oysa **HumanA** **her zaman**
    silahlı olacaktır.


C++ - Modül 01

```
Bellek tahsisi, üyelere işaretçiler,
referanslar ve switch ifadeleri
```
Uygulamanız doğruysa, aşağıdaki kodu çalıştırmak her iki test durumu için "crude spiked club"
ile bir saldırı ve ardından "some other type of club" ile ikinci bir saldırı yazdıracaktır:

```
int main()
{
{
Weapon club = Weapon("crude spiked club");
HumanA bob("Bob", club);
bob.attack();
club.setType("some other type of club");
bob.attack();
}
{
Weapon club = Weapon("crude spiked club");
HumanB jim("Jim");
jim.setWeapon(club);
jim.attack();
club.setType("some other type of club");
jim.attack();
}
return 0;
}
```
```
Bellek sızıntılarını kontrol etmeyi unutmayın.
```
```
Hangi durumda Weapon'a bir işaretçi kullanmanın en iyi olduğunu düşünüyorsunuz?
Ve Weapon'a bir referans? Neden? Bu egzersizi başlatmadan önce
düşünün.
```

# Bölüm VIII

# Egzersiz 04: Sed kaybedenler içindir

```
Egzersiz: 04
```
```
Sed kaybedenler içindir
Dizin: ex 04 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, *.cpp, *.{h, hpp}
Yasak: std::string::replace
```
Aşağıdaki sırayla üç parametre alan bir program oluşturun: bir dosya adı ve
iki string, s1 ve s2.
<filename> dosyasını açmalı ve içeriğini yeni bir
<filename>.replace dosyasına kopyalamalı, s1'in her oluşumunu s2 ile değiştirmelidir.

C dosya manipülasyon fonksiyonlarını kullanmak yasaktır ve hile olarak kabul edilecektir.
std::string sınıfının tüm üye fonksiyonlarına izin verilir, replace hariç. Onları
akıllıca kullanın!

Tabii ki, beklenmeyen girdileri ve hataları işleyin. Programınızın beklendiği gibi
çalıştığından emin olmak için kendi testlerinizi oluşturmalı ve teslim etmelisiniz.


# Bölüm IX

# Egzersiz 05: Harl 2.

```
Egzersiz: 05
```
```
Harl 2.
Dizin: ex 05 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Harl.{h, hpp}, Harl.cpp
Yasak: Yok
```
Harl'ı biliyor musunuz? Hepimiz biliyoruz, değil mi? Bilmiyorsanız, Harl'ın
yaptığı yorum türlerini aşağıda bulabilirsiniz. Seviyelere göre sınıflandırılmışlardır:

- " **DEBUG** " seviyesi: Hata ayıklama mesajları bağlamsal bilgi içerir. Genellikle
    problem teşhisi için kullanılırlar.
    Örnek: _"7XL-çift-peynirli-üçlü-turşulu-özel-_
    _ketçaplı burgerim için ekstra pastırma almayı seviyorum. Gerçekten seviyorum!"_
- " **INFO** " seviyesi: Bu mesajlar kapsamlı bilgi içerir. Program yürütmesini
    bir üretim ortamında izlemek için yardımcı olurlar.
    Örnek: _"Ekstra pastırmanın daha fazla paraya mal olduğuna inanamıyorum. Burgerime_
    _yeterli pastırma koymadınız! Koymuş olsaydınız, daha fazla istemezdim!"_
- " **WARNING** " seviyesi: Uyarı mesajları sistemde potansiyel bir sorunu gösterir.
    Ancak, ele alınabilir veya göz ardı edilebilir.
    Örnek: _"Bedava biraz ekstra pastırma almayı hak ettiğimi düşünüyorum. Yıllardır geliyorum,_
    _oysa sen burada çalışmaya sadece geçen ay başladın."_
- " **ERROR** " seviyesi: Bu mesajlar, kurtarılamaz bir hatanın oluştuğunu gösterir.
    Bu genellikle manuel müdahale gerektiren kritik bir sorundur.
    Örnek: _"Bu kabul edilemez! Şimdi müdürle konuşmak istiyorum."_


C++ - Modül 01

```
Bellek tahsisi, üyelere işaretçiler,
referanslar ve switch ifadeleri
```
Harl'ı otomatikleştireceksiniz. Zor olmayacak çünkü her zaman aynı şeyleri söylüyor.
Aşağıdaki özel üye fonksiyonlarına sahip bir **Harl** sınıfı oluşturmalısınız:

- void debug( void );
- void info( void );
- void warning( void );
- void error( void );

**Harl** ayrıca parametre olarak geçirilen seviyeye bağlı olarak yukarıdaki dört üye fonksiyonunu
çağıran bir genel üye fonksiyonuna sahiptir:

```
void complain( std::string level );
```
Bu egzersizin amacı **üye fonksiyonlarına işaretçiler** kullanmaktır. Bu bir
öneri değildir. Harl, if/else if/else ormanı kullanmadan şikayet etmelidir. İki kez
düşünmez!

Harl'ın çok şikayet ettiğini göstermek için testler oluşturun ve teslim edin.
Yukarıda konuda listelenen yorum örneklerini kullanabilir veya kendi yorumlarınızı
kullanmayı seçebilirsiniz.


# Bölüm X

# Egzersiz 06: Harl filtresi

```
Egzersiz: 06
```
```
Harl filtresi
Dizin: ex 06 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, Harl.{h, hpp}, Harl.cpp
Yasak: Yok
```
Bazen Harl'ın söylediği her şeye dikkat etmek istemezsiniz. Dinlemek istediğiniz
günlük seviyelerine bağlı olarak Harl'ın söylediklerini filtrelemek için bir sistem uygulayın.

Parametre olarak dört seviyeden birini alan bir program oluşturun. Bu seviyeden
ve yukarıdaki tüm mesajları görüntüleyecektir. Örneğin:

$> ./harlFilter "WARNING"
[ WARNING ]
I think I deserve to have some extra bacon for free.
I've been coming for years, whereas you started working here just last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now.

$> ./harlFilter "I am not sure how tired I am today..."
[ Probably complaining about insignificant problems ]

Harl ile başa çıkmanın birkaç yolu olsa da, en etkili olanlardan biri
onu KAPATMAKTIR (SWITCH).

```
Yürütülebilir dosyanıza harlFilter adını verin.
```
```
Bu egzersizde switch ifadesini kullanmalı ve belki de keşfetmelisiniz.
```
```
Egzersiz 06'yı yapmadan bu modülü geçebilirsiniz.
```

# Bölüm XI

# Teslim ve akran değerlendirmesi

Ödevinizi her zamanki gibi Git deponuzda teslim edin. Savunma sırasında yalnızca
deponuzdaki çalışma değerlendirilecektir. Dosyalarınızın ve klasörlerinizin adlarını
doğru olduklarından emin olmak için iki kez kontrol etmekten çekinmeyin.

Değerlendirme sırasında, ara sıra projenin kısa bir **değişikliği** istenebilir.
Bu, küçük bir davranış değişikliği, yazılacak veya yeniden yazılacak birkaç satır kod veya
eklemesi kolay bir özellik içerebilir.

Bu adım **her proje için geçerli olmayabilir**, ancak değerlendirme kılavuzlarında
belirtilmişse bunun için hazırlıklı olmalısınız.

Bu adım, projenin belirli bir bölümünü gerçekten anladığınızı doğrulamak içindir.
Değişiklik istediğiniz herhangi bir geliştirme ortamında gerçekleştirilebilir (örneğin,
normal kurulumunuz) ve birkaç dakika içinde yapılabilir olmalıdır — belirli bir zaman
dilimi değerlendirmenin bir parçası olarak tanımlanmadıkça.
Örneğin, bir fonksiyona veya betiğe küçük bir güncelleme yapmanız, bir
görüntüyü değiştirmeniz veya yeni bilgileri depolamak için bir veri yapısını ayarlamanız istenebilir, vb.

Detaylar (kapsam, hedef, vb.) **değerlendirme kılavuzlarında** belirtilecektir ve aynı
proje için bir değerlendirmeden diğerine değişebilir.



