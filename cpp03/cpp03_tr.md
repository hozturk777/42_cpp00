# C++ - Modül 03

## Kalıtım

_Özet:
Bu belge, C++ modüllerinden Modül 03'ün alıştırmalarını içerir._

```
Versiyon: 8.
```

## İçindekiler

- I Giriş
- II Genel kurallar
- III Yapay Zeka Talimatları
- IV Alıştırma 00: Veeee... AÇ!
- V Alıştırma 01: Serena, aşkım!
- VI Alıştırma 02: Tekrarlayan iş
- VII Alıştırma 03: Şimdi garip!
- VIII Teslim ve Akran Değerlendirmesi


# Bölüm I

# Giriş

_C++, Bjarne Stroustrup tarafından C programlama dilinin bir uzantısı olarak veya "Sınıflarla C" olarak oluşturulmuş genel amaçlı bir programlama dilidir (kaynak: Wikipedia)._

Bu modüllerin amacı, sizi **Nesne Yönelimli Programlama**'ya tanıştırmaktır.
Bu, C++ yolculuğunuzun başlangıç noktası olacaktır. OOP öğrenmek için birçok dil önerilir,
ancak eski dostunuz C'den türetildiği için C++ seçmeye karar verdik.
Bu karmaşık bir dil olduğundan ve işleri basit tutmak için, kodunuz C++98 standardına
uygun olacaktır.
Modern C++'ın birçok açıdan çok farklı olduğunun farkındayız. Bu nedenle, yetenekli
bir C++ geliştiricisi olmak istiyorsanız, 42 Common Core'dan sonra daha ileri gitmeniz
size kalmıştır!


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


C++ - Modül 03 Kalıtım

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

C++ - Modül 03 Kalıtım

```
Alıştırmaları tamamlamak için size belirli bir özgürlük verilir.
Ancak, zorunlu kuralları izleyin ve tembel olmayın. Birçok
yararlı bilgiyi kaçırırsınız! Teorik kavramlar hakkında
okumaktan çekinmeyin.
```

# Bölüm III

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


C++ - Modül 03 Kalıtım

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

# Bölüm IV

# Alıştırma 00: Veeee... AÇ!

```
Alıştırma: 00
```
```
Veeee... AÇ!
Dizin: ex 00 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, ClapTrap.{h, hpp}, ClapTrap.cpp
Yasak: Hiçbiri
```
```
Öncelikle, bir sınıf uygulamanız gerekiyor! Ne kadar orijinal!
```
**ClapTrap** olarak adlandırılacak ve parantez içinde belirtilen değerlere
başlatılan aşağıdaki özel özniteliklere sahip olacaktır:

- Yapıcıya parametre olarak geçirilen Name (İsim)
- ClapTrap'in sağlığını temsil eden Hit points (Can puanları) (10)
- Energy points (Enerji puanları) (10)
- Attack damage (Saldırı hasarı) (0)

ClapTrap'in daha gerçekçi davranması için aşağıdaki genel üye fonksiyonlarını ekleyin:

- void attack(const std::string& target);
- void takeDamage(unsigned int amount);
- void beRepaired(unsigned int amount);

ClapTrap saldırdığında, hedefinin <saldırı hasarı> kadar can puanı kaybetmesine neden olur.
ClapTrap kendini onarırken, <miktar> kadar can puanı kazanır. Saldırmak ve onarım
yapmak her biri 1 enerji puanı harcar. Elbette, ClapTrap'in can puanı veya
enerji puanı kalmamışsa hiçbir şey yapamaz. Ancak, bu alıştırmalar bir giriş niteliğinde olduğundan,
ClapTrap örnekleri birbirleriyle doğrudan etkileşimde bulunmamalı ve parametreler
başka bir ClapTrap örneğine atıfta bulunmamalıdır.


C++ - Modül 03 Kalıtım

Tüm bu üye fonksiyonlarında, ne olduğunu açıklamak için bir mesaj yazdırmanız gerekir.
Örneğin, attack() fonksiyonu şuna benzer bir şey gösterebilir (elbette, açılı
parantezler olmadan):

```
ClapTrap <isim> <hedefe> saldırıyor, <hasar> puan hasar veriyor!
```
Yapıcılar ve yıkıcı da bir mesaj görüntülemelidir, böylece akran değerlendirici leriniz
çağrıldıklarını kolayca görebilirler.

```
Kodunuzun beklendiği gibi çalıştığından emin olmak için kendi testlerinizi uygulayın ve teslim edin.
```

# Bölüm V

# Alıştırma 01: Serena, aşkım!

```
Alıştırma: 01
```
```
Serena, aşkım!
Dizin: ex 01 /
Teslim Edilecek Dosyalar: Önceki alıştırmadaki dosyalar + ScavTrap.{h, hpp},
ScavTrap.cpp
Yasak: Hiçbiri
```
ClapTrap'lerden hiçbir zaman yeterince olamayacağınız için, şimdi türetilmiş bir robot
oluşturacaksınız. **ScavTrap** olarak adlandırılacak ve yapıcıları ile yıkıcıyı ClapTrap'ten
miras alacaktır. Ancak, yapıcıları, yıkıcısı ve attack() fonksiyonu farklı mesajlar
yazdıracaktır. Sonuçta, ClapTrap'ler bireyselliklerinin farkındadır.

Testlerinizde uygun yapım/yıkım zincirlemenin gösterilmesi gerektiğini unutmayın.
Bir ScavTrap oluşturulduğunda, program önce bir ClapTrap oluşturarak başlar. Yıkım
ters sırayla gerçekleşir. Neden?

**ScavTrap**, ClapTrap'in özelliklerini kullanacak (ClapTrap'i buna göre güncelleyin) ve
bunları şu değerlere başlatmalıdır:

- Yapıcıya parametre olarak geçirilen Name (İsim)
- ClapTrap'in sağlığını temsil eden Hit points (Can puanları) (100)
- Energy points (Enerji puanları) (50)
- Attack damage (Saldırı hasarı) (20)
    ScavTrap'in ayrıca kendi özel yeteneği olacaktır:
       void guardGate();

Bu üye fonksiyon, ScavTrap'in artık Kapı bekçisi
modunda olduğunu belirten bir mesaj gösterecektir.

```
Programınıza daha fazla test eklemeyi unutmayın.
```

# Bölüm VI

# Alıştırma 02: Tekrarlayan iş

```
Alıştırma: 02
```
```
Tekrarlayan iş
Dizin: ex 02 /
Teslim Edilecek Dosyalar: Önceki alıştırmalardaki dosyalar + FragTrap.{h, hpp},
FragTrap.cpp
Yasak: Hiçbiri
```
```
ClapTrap'ler yapmak muhtemelen sinirlerinizi bozmaya başlamıştır.
```
Şimdi, ClapTrap'ten miras alan bir **FragTrap** sınıfı uygulayın. ScavTrap'e çok benzer.
Ancak, yapım ve yıkım mesajları farklı olmalıdır. Testlerinizde uygun
yapım/yıkım zincirlemenin gösterilmesi gerekir. Bir FragTrap oluşturulduğunda,
program önce bir ClapTrap oluşturarak başlar. Yıkım ters sırayla gerçekleşir.

```
Özellikler için de aynı durum geçerlidir, ancak bu sefer farklı değerlerle:
```
- Yapıcıya parametre olarak geçirilen Name (İsim)
- ClapTrap'in sağlığını temsil eden Hit points (Can puanları) (100)
- Energy points (Enerji puanları) (100)
- Attack damage (Saldırı hasarı) (30)

```
FragTrap'in de özel bir yeteneği var:
```
```
void highFivesGuys(void);
```
Bu üye fonksiyon, standart çıktıda pozitif bir beşlik isteği görüntüler.

```
Yine, programınıza daha fazla test ekleyin.
```

# Bölüm VII

# Alıştırma 03: Şimdi garip!

```
Alıştırma: 03
```
```
Şimdi garip!
Dizin: ex 03 /
Teslim Edilecek Dosyalar: Önceki alıştırmalardaki dosyalar + DiamondTrap.{h, hpp},
DiamondTrap.cpp
Yasak: Hiçbiri
```
Bu alıştırmada, bir canavar yaratacaksınız: yarı FragTrap, yarı ScavTrap
olan bir ClapTrap. **DiamondTrap** olarak adlandırılacak ve hem FragTrap'ten HEM DE
ScavTrap'ten miras alacaktır. Bu çok riskli!

DiamondTrap sınıfı, name (isim) adlı özel bir özelliğe sahip olacaktır. Bu özellik,
ClapTrap temel sınıfındaki ile tam olarak aynı değişken adına sahip olmalıdır (robotun
adına atıfta bulunmadan).
Daha net olmak için, işte iki örnek:
ClapTrap'in değişkeni name ise, DiamondTrap'in değişkenine name adını verin.
ClapTrap'in değişkeni _name ise, DiamondTrap'in değişkenine _name adını verin.

```
Özellikleri ve üye fonksiyonları, üst sınıflarından miras alınacaktır:
```
- Bir yapıcıya parametre olarak geçirilen Name (İsim)
- ClapTrap::name (yapıcının parametresi + "_clap_name" soneki)
- Hit points (Can puanları) (FragTrap)
- Energy points (Enerji puanları) (ScavTrap)
- Attack damage (Saldırı hasarı) (FragTrap)
- attack() (ScavTrap)


C++ - Modül 03 Kalıtım

Her iki üst sınıfın özel fonksiyonlarına ek olarak, DiamondTrap'in
kendi özel yeteneği olacaktır:

```
void whoAmI();
```
Bu üye fonksiyon, hem kendi adını hem de ClapTrap adını gösterecektir.

Elbette, DiamondTrap'in ClapTrap örneği bir kez ve yalnızca bir kez oluşturulacaktır.
Evet, bir numara var.

```
Yine, programınıza daha fazla test ekleyin.
```
```
-Wshadow ve -Wno-shadow derleyici bayraklarını biliyor musunuz?
```
```
Alıştırma 03'ü tamamlamadan bu modülü geçebilirsiniz.
```

# Bölüm VIII

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
