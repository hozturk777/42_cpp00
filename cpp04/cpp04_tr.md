# C++ - Modül 04

## Alt Tür Çok Biçimliliği, Soyut Sınıflar ve

## Arayüzler

_Özet: Bu belge, C++ modüllerinin Modül 04 alıştırmalarını içerir._

```
Versiyon: 13.
```

## İçindekiler

- I Giriş
- II Genel kurallar
- III Yapay Zeka Talimatları
- IV Alıştırma 00: Çok Biçimlilik
- V Alıştırma 01: Dünyayı ateşe vermek istemiyorum
- VI Alıştırma 02: Soyut sınıf
- VII Alıştırma 03: Arayüz ve özet
- VIII Teslim ve Akran Değerlendirmesi


# Bölüm I

# Giriş

_C++, Bjarne Stroustrup tarafından C programlama dilinin bir uzantısı olarak veya "Sınıflarla C" olarak oluşturulan genel amaçlı bir programlama dilidir (kaynak: Wikipedia)._

Bu modüllerin amacı sizi **Nesne Yönelimli Programlama** ile tanıştırmaktır.
Bu, C++ yolculuğunuzun başlangıç noktası olacaktır. OOP öğrenmek için birçok dil önerilir,
ancak eski dostunuz C'den türediği için C++'ı seçtik.
C++ karmaşık bir dil olduğundan ve işleri basit tutmak için, kodunuz C++98 standardına
uyacaktır.
Modern C++'ın birçok açıdan önemli ölçüde farklı olduğunun farkındayız. Bu nedenle,
yetkin bir C++ geliştiricisi olmak istiyorsanız, 42 Common Core'un ötesinde yolculuğunuza
devam etmek size kalmıştır!


# Bölüm II

# Genel kurallar

**Derleme**

- Kodunuzu c++ ve -Wall -Wextra -Werror bayraklarıyla derleyin
- -std=c++98 bayrağını eklerseniz kodunuz yine de derlenmeli

```
Biçimlendirme ve adlandırma kuralları
```
- Alıştırma dizinleri şu şekilde adlandırılacaktır: ex00, ex01, ... , exn
- Dosyalarınızı, sınıflarınızı, fonksiyonlarınızı, üye fonksiyonlarınızı ve özniteliklerinizi
    yönergelerde istendiği şekilde adlandırın.
- Sınıf isimlerini **UpperCamelCase** biçiminde yazın. Sınıf kodu içeren dosyalar
    her zaman sınıf adına göre adlandırılacaktır. Örneğin:
    ClassName.hpp/ClassName.h, ClassName.cpp veya ClassName.tpp. Eğer
    bir tuğla duvarı temsil eden "BrickWall" sınıfının tanımını içeren bir başlık dosyanız varsa,
    adının BrickWall.hpp olması gerekir.
- Aksi belirtilmedikçe, her çıktı mesajı yeni satır karakteriyle bitmeli
    ve standart çıktıya yazdırılmalıdır.
- _Güle güle Norminette!_ C++ modüllerinde zorunlu bir kodlama stili yoktur.
    Favori stilinizi takip edebilirsiniz. Ancak akran değerlendiricilerinizin anlayamadığı
    kodu notlandıramayacaklarını unutmayın. Temiz ve okunabilir kod yazmak için
    elinizden geleni yapın.

```
İzinli/Yasak
```
```
Artık C'de kod yazmıyorsunuz. C++ zamanı! Bu nedenle:
```
- Standart kütüphanedeki neredeyse her şeyi kullanmanıza izin verilir. Bu yüzden,
    bildiklerinize bağlı kalmak yerine, alışık olduğunuz C fonksiyonlarının
    C++ tarzı sürümlerini mümkün olduğunca kullanmak akıllıca olacaktır.
- Ancak başka hiçbir harici kütüphaneyi kullanamazsınız. Bu, C++11'in (ve türevlerinin)
    ve Boost kütüphanelerinin yasak olduğu anlamına gelir. Aşağıdaki fonksiyonlar da
    yasaktır: *printf(), *alloc() ve free(). Bunları kullanırsanız notunuz 0 olur,
    hepsi bu.


C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

- Aksi açıkça belirtilmedikçe, using namespace <ns_name> ve
    friend anahtar sözcüklerinin yasak olduğunu unutmayın. Aksi halde notunuz -42 olur.
- **STL'yi sadece Modül 08 ve 09'da kullanabilirsiniz.** Bu şu anlama gelir:
    o zamana kadar **Container** yok (vector/list/map vb.) ve **Algorithm** yok (<algorithm>
    başlığını gerektiren her şey). Aksi halde notunuz -42 olur.

```
Birkaç tasarım gereksinimi
```
- C++'ta da bellek sızıntısı olur. Bellek ayırdığınızda (new
    anahtar sözcüğünü kullanarak), **bellek sızıntılarından** kaçınmalısınız.
- Modül 02'den Modül 09'a kadar sınıflarınız, **aksi açıkça belirtilmedikçe**
    **Ortodoks Kanonik Formda** tasarlanmalıdır.
- Bir başlık dosyasına konulan herhangi bir fonksiyon uygulaması (fonksiyon şablonları hariç)
    alıştırma için 0 anlamına gelir.
- Her başlığınızı diğerlerinden bağımsız kullanabiliyor olmalısınız. Bu nedenle,
    ihtiyaç duydukları tüm bağımlılıkları içermelidirler. Ancak **include guard** ekleyerek
    çift dahil etme sorunundan kaçınmalısınız. Aksi halde notunuz 0 olur.

```
Beni oku
```
- İhtiyacınız varsa bazı ek dosyalar ekleyebilirsiniz (örneğin kodunuzu bölmek için).
    Bu ödevler bir program tarafından doğrulanmadığı için, zorunlu dosyaları teslim ettiğiniz
    sürece bunu yapmaktan çekinmeyin.
- Bazen bir alıştırmanın yönergeleri kısa görünebilir ancak örnekler,
    talimatlarda açıkça yazılmayan gereksinimleri gösterebilir.
- Başlamadan önce her modülü tamamen okuyun! Gerçekten, okuyun.
- Odin aşkına, Thor aşkına! Beyninizi kullanın!!!

```
C++ projeleri için Makefile konusunda, C ile aynı kurallar geçerlidir
(Makefile hakkındaki Norm bölümüne bakın).
```
```
Birçok sınıf uygulamanız gerekecek. Bu sıkıcı görünebilir,
tercih ettiğiniz metin düzenleyiciyi betikleyemiyorsanız.
```

C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

```
Alıştırmaları tamamlamanız için size belli bir özgürlük verilir.
Ancak zorunlu kuralları takip edin ve tembel olmayın. Birçok
faydalı bilgiyi kaçırırsınız! Teorik kavramlar hakkında
okumaktan çekinmeyin.
```

# Bölüm III

# Yapay Zeka Talimatları

## ● Bağlam

Bu proje, 42 eğitiminizin temel yapı taşlarını keşfetmenize yardımcı olmak için tasarlanmıştır.

Temel bilgi ve becerileri doğru şekilde yerleştirmek için, yapay zeka araçlarını ve desteğini
kullanırken düşünceli bir yaklaşım benimsemek çok önemlidir.

Gerçek temel öğrenme; zorlanma, tekrar
ve akran öğrenimi alışverişleri yoluyla gerçek zihinsel çaba gerektirir.

Yapay zekaya bakış açımızın daha kapsamlı bir özeti için (bir öğrenme aracı olarak,
42 eğitiminin bir parçası olarak ve iş piyasasında bir beklenti olarak) intranetteki
özel SSS'ye bakın.

## ● Ana mesaj

```
☛ Kestirme yollara kaçmadan güçlü temeller kurun.
```
```
☛ Gerçekten teknik ve güç becerilerini geliştirin.
```
```
☛ Gerçek akran öğrenimini deneyimleyin, öğrenmeyi ve yeni problemleri çözmeyi öğrenmeye başlayın.
```
```
☛ Öğrenme yolculuğu sonuçtan daha önemlidir.
```
```
☛ Yapay zeka ile ilişkili riskleri öğrenin ve yaygın tuzaklardan kaçınmak için etkili
kontrol pratikleri ve karşı önlemler geliştirin.
```
## ● Öğrenci kuralları:

- Size verilen görevlerde, özellikle yapay zekaya başvurmadan önce, akıl yürütme uygulamalısınız.


C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

- Yapay zekadan doğrudan cevap istememelisiniz.
- Yapay zekaya dair 42'nin genel yaklaşımını öğrenmelisiniz.

● **Aşama çıktıları:**

Bu temel aşamada şu çıktıları elde edeceksiniz:

- Sağlam teknik ve kodlama temelleri edinmek.
- Bu aşamada yapay zekanın neden ve nasıl tehlikeli olabileceğini bilmek.

● **Yorumlar ve örnek:**

- Evet, yapay zekanın var olduğunu biliyoruz ve evet, projelerinizi çözebilir. Ancak siz buraya
    yapay zekanın öğrendiğini kanıtlamak için değil, öğrenmek için geldiniz. Sadece yapay zekanın
    verilen problemi çözebildiğini göstermek için zamanınızı (ve bizim zamanımızı) boşa harcamayın.
- 42'de öğrenmek cevabı bilmekle ilgili değildir; bir cevabı bulma becerisini geliştirmekle ilgilidir.
    Yapay zeka size cevabı doğrudan verir, fakat bu da kendi akıl yürütmenizi kurmanızı engeller.
    Akıl yürütme ise zaman ve emek ister, ayrıca başarısızlığı da içerir. Başarı yolu
    kolay olmak zorunda değildir.
- Sınavlarda yapay zekanın erişilebilir olmadığını unutmayın: internet yok, akıllı telefon yok,
    vb. Öğrenme sürecinizde yapay zekaya fazla güvendiyseniz bunu hızlıca fark edersiniz.
- Akran öğrenimi sizi farklı fikir ve yaklaşımlarla buluşturur; kişilerarası becerilerinizi
    ve farklı düşünebilme yeteneğinizi geliştirir. Bu, bir botla sohbet etmekten çok daha
    değerlidir. Bu yüzden çekinmeyin: konuşun, soru sorun ve birlikte öğrenin!
- Evet, yapay zeka müfredatın bir parçası olacak; hem bir öğrenme aracı olarak hem de
    başlı başına bir konu olarak. Hatta kendi yapay zeka yazılımınızı geliştirme şansınız da olacak.
    Bu süreçte geçeceğiniz artan yaklaşımımız hakkında daha fazla bilgi için intranetteki
    dokümantasyona göz atın.

```
✓ İyi uygulama:
```
```
Yeni bir kavramda takıldım. Yakınımdaki birine nasıl yaklaştıklarını soruyorum. 10 dakika konuşuyoruz
ve bir anda kafamda oturuyor. Anlıyorum.
```
```
✗ Kötü uygulama:
```
```
Gizlice yapay zeka kullanıyorum, doğru gibi görünen bir kodu kopyalıyorum. Akran değerlendirmesinde
hiçbir şeyi açıklayamıyorum. Kalıyorum. Sınavda, yapay zeka yokken, yine takılıyorum. Yine kalıyorum.
```

# Bölüm IV

# Alıştırma 00: Çok Biçimlilik

```
Alıştırma: 00
```
```
Çok Biçimlilik
Dizin: ex 00 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, *.cpp, *.{h, hpp}
Yasak: Yok
```
Her alıştırma için, verebildiğiniz **en kapsamlı testleri** sunmalısınız.
Her sınıfın yapıcıları ve yıkıcıları belirli mesajlar göstermelidir. Tüm sınıflar için
aynı mesajı kullanmayın.

Önce **Animal** adında basit bir temel sınıf uygulayarak başlayın. Bir korumalı
özniteliği vardır:

- std::string type;

```
Animal'dan türeyen bir Dog sınıfı uygulayın.
Animal'dan türeyen bir Cat sınıfı uygulayın.
```
Bu iki türetilmiş sınıf, type alanını adlarına göre ayarlamalıdır.
Dolayısıyla Dog'un type değeri "Dog", Cat'in type değeri "Cat" olacaktır.
Animal sınıfının type değeri boş bırakılabilir veya seçtiğiniz bir değere ayarlanabilir.

```
Her hayvan şu üye fonksiyonu kullanabilmelidir:
makeSound()
Uygun bir ses yazdıracaktır (kediler havlamaz).
```

C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

Bu kod çalıştırıldığında Animal'ın değil, Dog ve Cat sınıflarının kendine özgü
seslerini yazdırmalıdır.

```
int main()
{
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();
std::cout << j->getType() << " " << std::endl;
std::cout << i->getType() << " " << std::endl;
i->makeSound(); //kedi sesi verecek!
j->makeSound();
meta->makeSound();
...
return 0;
}
```
Nasıl çalıştığını anladığınızdan emin olmak için, **WrongAnimal** sınıfından türeyen
bir **WrongCat** sınıfı uygulayın. Yukarıdaki kodda Animal ve Cat yerine yanlış olanları
koyarsanız, WrongCat, WrongAnimal sesini çıkarmalıdır.

```
Yukarıda verilenlerden daha fazla test uygulayın ve teslim edin.
```

# Bölüm V

# Alıştırma 01: Dünyayı ateşe vermek istemiyorum

```
Alıştırma: 01
```
```
Dünyayı ateşe vermek istemiyorum
Dizin: ex 01 /
Teslim Edilecek Dosyalar: Önceki alıştırmadaki dosyalar + *.cpp, *.{h, hpp}
Yasak: Yok
```
```
Her sınıfın yapıcıları ve yıkıcıları belirli mesajlar göstermelidir.
```
Bir **Brain** sınıfı uygulayın. ideas adında 100 elemanlı bir std::string dizisi içerir.
Bu şekilde Dog ve Cat sınıfları özel bir Brain* özniteliğine sahip olacaktır.
Kurulum sırasında Dog ve Cat, Brain'lerini new Brain(); ile oluşturacaktır.
Yıkım sırasında Dog ve Cat, Brain'lerini silecektir.

main fonksiyonunuzda bir **Animal** nesne dizisi oluşturup doldurun. Yarısı
**Dog**, diğer yarısı **Cat** nesneleri olacaktır. Program çalışmasının sonunda
bu dizi üzerinde dönüp her Animal'ı silin. Köpekleri ve kedileri doğrudan Animal olarak
silmelisiniz. Uygun yıkıcılar beklenen sırada çağrılmalıdır.

```
Bellek sızıntısı kontrolünü unutmayın.
```
Bir Dog veya Cat kopyası yüzeysel (shallow) olmamalıdır. Bu nedenle, kopyalarınızın
derin kopya (deep copy) olduğunu test etmelisiniz!


C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

```
int main()
{
const Animal* j = new Dog();
const Animal* i = new Cat();
```
```
delete j; //sızıntı oluşturmamalı
delete i;
...
return 0;
}
```
```
Yukarıda verilenlerden daha fazla test uygulayın ve teslim edin.
```

# Bölüm VI

# Alıştırma 02: Soyut sınıf

```
Alıştırma: 02
```
```
Soyut sınıf
Dizin: ex 02 /
Teslim Edilecek Dosyalar: Önceki alıştırmadaki dosyalar + *.cpp, *.{h, hpp}
Yasak: Yok
```
```
Aslında Animal nesneleri oluşturmak anlamlı değil. Doğru, ses çıkarmıyorlar!
```
Olası hataları önlemek için varsayılan Animal sınıfı örneklenebilir olmamalıdır.
Kimsenin Animal örneği oluşturamaması için Animal sınıfını düzeltin. Her şey eskisi gibi çalışmalıdır.

```
İsterseniz, Animal sınıf adına A öneki ekleyerek sınıf adını güncelleyebilirsiniz.
```

# Bölüm VII

# Alıştırma 03: Arayüz ve özet

```
Alıştırma: 03
```
```
Arayüz ve özet
Dizin: ex 03 /
Teslim Edilecek Dosyalar: Makefile, main.cpp, *.cpp, *.{h, hpp}
Yasak: Yok
```
C++98'de arayüz kavramı yoktur (C++20'de bile yoktur). Ancak saf soyut sınıflar
yaygın olarak arayüz olarak adlandırılır. Bu yüzden bu son alıştırmada,
bu modülü anladığınızdan emin olmak için arayüzleri uygulamayı deneyelim.

Aşağıdaki **AMateria** sınıfının tanımını tamamlayın ve gerekli
üye fonksiyonları uygulayın.

```
class AMateria
{
protected:
[...]
```
```
public:
AMateria(std::string const & type);
[...]
```
```
std::string const & getType() const; //Materia türünü döndürür
```
```
virtual AMateria* clone() const = 0;
virtual void use(ICharacter& target);
};
```

C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

Materia'lar için somut sınıfları uygulayın: **Ice** ve **Cure**. Türlerini ayarlamak için
adlarının küçük harfli hallerini kullanın (Ice için "ice", Cure için "cure"). Elbette,
clone() üye fonksiyonu aynı türden yeni bir örnek döndürmelidir (yani bir Ice Materia'yı
klonlarsanız, yeni bir Ice Materia elde edersiniz).

```
use(ICharacter&) üye fonksiyonu şunu göstermelidir:
```
- Ice: "* <name> hedefine bir buz oku fırlatıyor *"
- Cure: "* <name>’in yaralarını iyileştiriyor *"

<name>, parametre olarak geçirilen Character'ın adıdır. Köşeli
parantezleri (< ve >) yazdırmayın.

```
Bir Materia'yı diğerine atarken, türü kopyalamak
anlamlı değildir.
```
```
Aşağıdaki arayüzü uygulayacak somut Character sınıfını yazın:
```
```
class ICharacter
{
public:
virtual ~ICharacter() {}
virtual std::string const & getName() const = 0;
virtual void equip(AMateria* m) = 0;
virtual void unequip(int idx) = 0;
virtual void use(int idx, ICharacter& target) = 0;
};
```
**Character**, 4 yuvadan oluşan bir envantere sahiptir; yani en fazla 4 Materia taşıyabilir.
Envanter yapım sırasında boştur. Materia'ları buldukları ilk boş
yuvaya şu sırayla takarlar: slot 0'dan slot 3'e. Dolu bir envantere Materia eklemeye
çalışırlarsa ya da var olmayan bir Materia'yı use/unequip etmeye çalışırlarsa hiçbir şey
olmamalıdır (ama hatalar yine de yasaktır). unequip() üye fonksiyonu Materia'yı
SİLMEMELİDİR!

```
Karakterinizin yere bıraktığı Materia'ları istediğiniz gibi yönetin.
unequip() çağırmadan önce adresleri kaydedin veya başka bir şey yapın,
ama bellek sızıntısından kaçınmanız gerektiğini unutmayın.
```
use(int, ICharacter&) üye fonksiyonu, slot[idx]'deki Materia'yı kullanmalı
ve hedef parametresini AMateria::use fonksiyonuna iletmelidir.


C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

```
Karakterinizin envanteri herhangi bir
AMateria türünü destekleyebilmelidir.
```
**Character** sınıfınız, adını parametre olarak alan bir yapıcıya sahip olmalıdır. Character'ın
herhangi bir kopyası (kopya yapıcı veya kopya atama operatörü kullanılarak) **derin** olmalıdır.
Kopyalama sırasında, Character'ın Materia'ları envantere yenileri eklenmeden önce
silinmelidir. Elbette Character yok edildiğinde Materia'lar da silinmelidir.

```
Aşağıdaki arayüzü uygulayacak somut MateriaSource sınıfını yazın:
```
```
class IMateriaSource
{
public:
virtual ~IMateriaSource() {}
virtual void learnMateria(AMateria*) = 0;
virtual AMateria* createMateria(std::string const & type) = 0;
};
```
- learnMateria(AMateria*)
    Parametre olarak verilen Materia'nın bir kopyasını alır ve daha sonra klonlanabilmesi için
    bellekte saklar. Character gibi **MateriaSource** da en fazla 4 Materia bilebilir.
    Bunlar benzersiz olmak zorunda değildir.
- createMateria(std::string const &)
    Yeni bir Materia döndürür. Bu Materia, daha önce **MateriaSource** tarafından öğrenilmiş,
    türü parametre olarak verilenle eşleşen Materia'nın bir kopyasıdır. Tür bilinmiyorsa
    0 döndürür.

Özetle, **MateriaSource** sınıfınız gerektiğinde oluşturabilmek için Materia "şablonlarını"
öğrenebilmelidir. Ardından, türünü tanımlayan bir string kullanarak
yeni bir Materia üretebilirsiniz.


C++ - Modül 04 Alt Tür Çok Biçimliliği, Soyut Sınıflar ve Arayüzler

```
Bu kodu çalıştırmak:
```
```
int main()
{
IMateriaSource* src = new MateriaSource();
src->learnMateria( new Ice());
src->learnMateria( new Cure());
ICharacter* me = new Character("me");
AMateria* tmp;
tmp = src->createMateria("ice");
me->equip(tmp);
tmp = src->createMateria("cure");
me->equip(tmp);
ICharacter* bob = new Character("bob");
me->use(0, *bob);
me->use(1, *bob);
delete bob;
delete me;
delete src;
return 0;
}
```
```
Şunu vermelidir:
```
```
$> clang++ -W -Wall -Werror *.cpp
$> ./a.out | cat -e
* shoots an ice bolt at bob *$
* heals bob's wounds *$
```
```
Her zamanki gibi, yukarıda verilenlerden daha fazla test uygulayın ve teslim edin.
```
```
Alıştırma 03'ü yapmadan da bu modülü geçebilirsiniz.
```

# Bölüm VIII

# Teslim ve Akran Değerlendirmesi

Ödevinizi her zamanki gibi Git deponuza teslim edin. Savunma sırasında yalnızca deponuzun
içindeki çalışmalar değerlendirilecektir. Klasör ve dosya adlarınızın doğru olduğundan
emin olmak için tekrar kontrol etmekten çekinmeyin.

Değerlendirme sırasında, **projenin kısa bir değişikliği** zaman zaman istenebilir.
Bu; küçük bir davranış değişikliği, yazılacak veya yeniden yazılacak birkaç satır kod
ya da kolay eklenebilir bir özellik içerebilir.

Bu adım **her proje için geçerli olmayabilir**, ancak değerlendirme yönergelerinde
belirtilmişse buna hazır olmalısınız.

Bu adım, projenin belirli bir kısmını gerçekten anlayıp anlamadığınızı doğrulamak için vardır.
Değişiklik, seçtiğiniz herhangi bir geliştirme ortamında (örneğin kendi düzeninizde)
yapılabilir ve değerlendirme kapsamında özel bir süre tanımlanmadıkça birkaç dakika
içinde uygulanabilir olmalıdır.
Örneğin, bir fonksiyona veya betiğe küçük bir güncelleme yapmanız, bir gösterimi
değiştirmeniz veya yeni bilgi saklamak için bir veri yapısını ayarlamanız istenebilir.

Ayrıntılar (kapsam, hedef vb.) **değerlendirme yönergelerinde** belirtilecek ve aynı proje için
bir değerlendirmeden diğerine değişebilecektir.
