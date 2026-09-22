# C++ - Modül 06

## C++ cast'leri

_Özet:
Bu belge, C++ modüllerinin 06. Modülüne ait alıştırmaları içerir._

```
Versiyon: 8.1
```

## İçindekiler

- I Giriş
- II Genel kurallar
- III Ek Kural
- IV AI Talimatları
- V Alıştırma 00: Skaler tiplerin dönüşümü
- VI Alıştırma 01: Serileştirme
- VII Alıştırma 02: Gerçek tipi belirleme
- VIII Teslim ve Akran Değerlendirmesi


# Bölüm I

# Giriş

_C++, Bjarne Stroustrup tarafından C programlama dilinin bir uzantısı olarak
yaratılmış, genel amaçlı bir programlama dilidir; çoğu zaman "Sınıflarla C" olarak
anılır (kaynak: Wikipedia)._

Bu modüllerin amacı sizi **Nesne Yönelimli Programlama**'yla tanıştırmaktır.
Bu, C++ yolculuğunuzun başlangıç noktası olacak. OOP öğrenmek için birçok dil
önerilir, ama biz C++'ı seçtik çünkü eski dostunuz C'den türemiştir. C++ karmaşık
bir dil olduğu için, kodunuz işleri basit tutmak amacıyla C++98 standardına
uyacak.
Modern C++'ın birçok açıdan önemli ölçüde farklılaştığını kabul ediyoruz. Yetkin
bir C++ geliştiricisi olmak istiyorsanız, 42 Ortak Çekirdeğin ötesine geçip
araştırmak size kalacak!


# Bölüm II

# Genel kurallar

**Derleme**

- Kodunuzu c++ ile ve -Wall -Wextra -Werror bayraklarıyla derleyin
- Kodunuz -std=c++98 bayrağı eklendiğinde de derlenebilmeli

```
Biçimlendirme ve isimlendirme kuralları
```
- Alıştırma dizinleri şu şekilde adlandırılacak: ex00, ex01, ... , exn
- Dosyalarınızı, sınıflarınızı, fonksiyonlarınızı, üye fonksiyonlarınızı ve
    özniteliklerinizi rehberde istenildiği şekilde adlandırın.
- Sınıf isimlerini **UpperCamelCase** formatında yazın. Sınıf kodunu içeren
    dosyalar her zaman sınıf adına göre adlandırılacak. Örneğin:
    ClassName.hpp/ClassName.h, ClassName.cpp veya ClassName.tpp. Yani, bir tuğla
    duvarı temsil eden "BrickWall" sınıfının tanımını içeren bir header dosyanız
    varsa, adı BrickWall.hpp olacaktır.
- Aksi belirtilmedikçe, her çıktı mesajı bir yeni satır karakteriyle bitmeli ve
    standart çıktıya (stdout) yazdırılmalıdır.
- _Norminette'e elveda!_ C++ modüllerinde herhangi bir kodlama stili
    zorunluluğu yoktur. En sevdiğiniz stili takip edebilirsiniz. Ama akran
    değerlendiricilerinizin anlayamadığı kodu değerlendiremeyeceklerini unutmayın.
    Temiz ve okunabilir kod yazmak için elinizden geleni yapın.

```
İzin verilen/Yasak olan
```
```
Artık C ile kod yazmıyorsunuz. C++ zamanı! Bu nedenle:
```
- Standart kütüphaneden neredeyse her şeyi kullanmanıza izin verilir. Yani,
    bildiğiniz şeylere sıkı sıkıya bağlı kalmak yerine, alışık olduğunuz C
    fonksiyonlarının C++'a özgü versiyonlarını olabildiğince kullanmak akıllıca
    olur.
- Ancak başka bir harici kütüphane kullanamazsınız. Bu, C++11'in (ve türevi
    formların) ve Boost kütüphanelerinin yasak olduğu anlamına gelir. Şu
    fonksiyonlar da yasaktır: *printf(), *alloc() ve free(). Bunları
    kullanırsanız notunuz 0 olur, hepsi bu.


C++ - Modül 06 C++ cast'leri

- Aksi açıkça belirtilmedikçe, using namespace <ns_name> ve friend anahtar
    kelimeleri yasaktır. Aksi halde notunuz -42 olacaktır.
- **STL'i sadece Modül 08 ve 09'da kullanmanıza izin verilir.** Bu şu anlama
    gelir: o zamana kadar **Container**'lar (vector/list/map ve benzerleri) ve
    **Algorithm**'lar (<algorithm> header'ını include etmeyi gerektiren her şey)
    yasaktır. Aksi halde notunuz -42 olacaktır.

```
Birkaç tasarım gerekliliği
```
- Bellek sızıntısı C++'ta da olur. Bellek ayırdığınızda (new anahtar kelimesini
    kullanarak), **bellek sızıntılarından** kaçınmalısınız.
- Modül 02'den Modül 09'a kadar, sınıflarınız **açıkça belirtilmediği sürece
    Orthodox Canonical Form** ile tasarlanmalıdır.
- Bir header dosyasına konan herhangi bir fonksiyon implementasyonu (fonksiyon
    template'leri hariç) o alıştırmaya 0 almak demektir.
- Header'larınızın her birini diğerlerinden bağımsız olarak kullanabilmelisiniz.
    Bu nedenle, ihtiyaç duydukları tüm bağımlılıkları include etmelidirler. Ancak,
    çift include (double inclusion) sorunundan **include guard** ekleyerek
    kaçınmalısınız. Aksi halde notunuz 0 olacaktır.

```
Beni oku
```
- İhtiyacınız olursa bazı ek dosyalar ekleyebilirsiniz (yani, kodunuzu bölmek
    için). Bu ödevler bir program tarafından doğrulanmadığından, zorunlu
    dosyaları teslim ettiğiniz sürece bunu yapmakta özgürsünüz.
- Bazen bir alıştırmanın yönergeleri kısa görünür ama örnekler, talimatlarda
    açıkça yazılmamış gereksinimleri gösterebilir.
- Başlamadan önce her modülü tamamen okuyun! Gerçekten yapın.
- Odin adına, Thor adına! Beyninizi kullanın!!!

```
C++ projeleri için Makefile ile ilgili olarak, C'deki aynı kurallar
geçerlidir (Makefile ile ilgili Norm bölümüne bakın).
```
```
Bir dizi sınıf implemente etmeniz gerekecek. Favori metin editörünüzü
script'leyebiliyorsanız bu can sıkıcı olmaktan çıkabilir.
```

C++ - Modül 06 C++ cast'leri

```
Alıştırmaları tamamlamak için size belirli bir özgürlük tanınıyor.
Ancak, zorunlu kurallara uyun ve tembel olmayın. Aksi halde birçok
faydalı bilgiyi kaçırırsınız! Teorik kavramlar hakkında okumaktan
çekinmeyin.
```

# Bölüm III

# Ek Kural

Aşağıdaki kural modülün tamamına uygulanır ve zorunludur.

Her alıştırma için, tip dönüşümü belirli bir cast türü kullanılarak yapılmalıdır.
Seçiminiz defans sırasında incelenecektir.


# Bölüm IV

# AI Talimatları

## ● Bağlam

Bu proje, 42 eğitiminizin temel yapı taşlarını keşfetmenize yardımcı olmak için
tasarlanmıştır.

Temel bilgi ve becerileri düzgünce yerleştirmek için, AI araçlarını ve desteğini
kullanırken düşünceli bir yaklaşım benimsemek şarttır.

Gerçek temel öğrenme, gerçek entelektüel çaba gerektirir — zorlanma, tekrar ve
akran öğrenme değişimleri yoluyla.

AI'ya dair duruşumuz hakkında daha kapsamlı bir bakış için — bir öğrenme aracı
olarak, 42 eğitiminin bir parçası olarak ve iş piyasasında bir beklenti olarak —
lütfen intranette bulunan özel SSS'ye bakın.

## ● Ana mesaj

```
☛ Kısayol kullanmadan güçlü temeller inşa edin.
```
```
☛ Gerçekten teknik ve güç becerileri geliştirin.
```
```
☛ Gerçek akran öğrenmeyi deneyimleyin, nasıl öğrenileceğini ve yeni problemlerin
nasıl çözüleceğini öğrenmeye başlayın.
```
```
☛ Öğrenme yolculuğu sonuçtan daha önemlidir.
```
```
☛ AI ile ilişkili riskler hakkında öğrenin ve yaygın tuzaklardan kaçınmak için
etkili kontrol pratikleri ve karşı tedbirler geliştirin.
```
## ● Öğrenci kuralları:

- Görevlerinize, özellikle AI'ya başvurmadan önce, akıl yürütme uygulamalısınız.


C++ - Modül 06 C++ cast'leri

- AI'dan doğrudan cevaplar istememelisiniz.
- 42'nin AI konusundaki genel yaklaşımını öğrenmelisiniz.

● **Aşama çıktıları:**

Bu temel aşama içinde, şu çıktıları alacaksınız:

- Düzgün teknik ve kodlama temelleri edinmek.
- AI'nın bu aşamada neden ve nasıl tehlikeli olabileceğini bilmek.

● **Yorumlar ve örnek:**

- Evet, AI'nın var olduğunu biliyoruz — ve evet, projelerinizi çözebilir. Ama
    siz burada öğrenmek için varsınız, AI'nın öğrendiğini kanıtlamak için değil.
    AI'nın verilen problemi çözebildiğini göstermek için zamanınızı (veya bizimkini)
    harcamayın.
- 42'de öğrenmek cevabı bilmekle ilgili değildir — bir cevap bulma yeteneği
    geliştirmekle ilgilidir. AI size cevabı direkt verir, ama bu sizin kendi akıl
    yürütmenizi inşa etmenizi engeller. Ve akıl yürütme zaman, çaba gerektirir ve
    başarısızlığı içerir. Başarıya giden yol kolay olmak üzere tasarlanmamıştır.
- Sınavlar sırasında AI'nın mevcut olmadığını unutmayın — internet yok, akıllı
    telefon yok, vb. Öğrenme sürecinizde AI'ya ne kadar aşırı güvendiğinizi çok
    çabuk fark edeceksiniz.
- Akran öğrenme sizi farklı fikirlere ve yaklaşımlara maruz bırakır, kişilerarası
    becerilerinizi ve farklı düşünme yeteneğinizi geliştirir. Bu, sadece bir botla
    sohbet etmekten çok daha değerlidir. O yüzden çekinmeyin — konuşun, sorular
    sorun ve birlikte öğrenin!
- Evet, AI müfredatın bir parçası olacak — hem bir öğrenme aracı hem de kendi
    başına bir konu olarak. Kendi AI yazılımınızı bile inşa etme şansınız olacak.
    İntranette bulunan dokümantasyonda göreceğiniz crescendo yaklaşımımız hakkında
    daha fazla bilgi edinmek için.

```
✓ İyi pratik:
```
```
Yeni bir kavramda tıkandım. Yakınımdaki birine bu konuya nasıl yaklaştığını
soruyorum. 10 dakika konuşuyoruz — ve birden kafamda oturuyor. Anlıyorum.
```
```
✗ Kötü pratik:
```
```
Gizlice AI kullanıyorum, doğru görünen bir kod kopyalıyorum. Akran
değerlendirmesi sırasında hiçbir şeyi açıklayamıyorum. Başarısız oluyorum.
Sınavda — AI yok — yine tıkanıyorum. Başarısız oluyorum.
```

# Bölüm V

# Alıştırma 00: Skaler tiplerin

# dönüşümü

```
Alıştırma00
```
```
Skaler tiplerin dönüşümü
Dizin: ex 00 /
Teslim Edilecek Dosyalar: Makefile, *.cpp, *.{h, hpp}
İzin Verilen: String'den bir int, float veya double'a dönüşüm yapan
herhangi bir fonksiyon. Bu yardımcı olacak, ama işin tamamını yapmayacak.
```
Yalnızca bir static "convert" metodu içerecek bir ScalarConverter sınıfı yazın; bu
metot, parametre olarak en yaygın haliyle bir C++ literalinin string temsilini
alacak ve değerini şu skaler tip serisinde çıktı olarak verecek:

- char
- int
- float
- double

Bu sınıfın hiçbir şeyi depolamasına gerek olmadığından, kullanıcılar tarafından
instantiate edilememelidir. char parametreleri hariç, yalnızca ondalık (decimal)
gösterim kullanılacaktır.

char literal örnekleri: 'c', 'a', ...
İşleri basit tutmak için, görüntülenemeyen (non-displayable) karakterlerin girdi
olarak kullanılmaması gerektiğini not edin. Bir char dönüşümü görüntülenemiyorsa,
bilgilendirici bir mesaj yazdırın.

int literal örnekleri: 0, -42, 42...

float literal örnekleri: 0.0f, -4.2f, 4.2f...
Şu sözde-literalleri (pseudo-literal) de işlemeniz gerekiyor (bilim adına, bilirsiniz):
-inff, +inff ve nanf.


C++ - Modül 06 C++ cast'leri

double literal örnekleri: 0.0, -4.2, 4.2...
Şu sözde-literalleri de işlemeniz gerekiyor (eğlence adına, bilirsiniz): -inf,
+inf ve nan.


C++ - Modül 06 C++ cast'leri

Sınıfınızın beklendiği gibi çalıştığını test edecek bir program yazın.

Önce parametre olarak geçirilen literalin tipini tespit etmeniz, onu string'den
gerçek tipine dönüştürmeniz, ardından **açıkça** (explicitly) diğer üç veri tipine
dönüştürmeniz gerekiyor. Son olarak, sonuçları aşağıda gösterildiği gibi
görüntüleyin.

Bir dönüşüm mantıklı değilse veya taşma (overflow) yapıyorsa, kullanıcıyı tip
dönüşümünün mümkün olmadığı konusunda bilgilendiren bir mesaj görüntüleyin.
Sayısal limitleri ve özel değerleri işlemek için ihtiyacınız olan her header'ı
include edin.

```
./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0
./convert nan
char: impossible
int: impossible
float: nanf
double: nan
./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
```

# Bölüm VI

# Alıştırma 01: Serileştirme

```
Alıştırma: 01
```
```
Serileştirme
Dizin: ex 01 /
Teslim Edilecek Dosyalar: Makefile, *.cpp, *.{h, hpp}
Yasak: Yok
```
Kullanıcı tarafından hiçbir şekilde initialize edilemeyecek bir Serializer sınıfı
implemente edin; bu sınıf şu static metotlara sahip olacak:

```
uintptr_t serialize(Data* ptr);
```
Bir pointer alır ve onu unsigned integer tipi uintptr_t'ye dönüştürür.

```
Data* deserialize(uintptr_t raw);
```
Bir unsigned integer parametresi alır ve onu Data'ya bir pointer'a dönüştürür.

Sınıfınızın beklendiği gibi çalıştığını test edecek bir program yazın.

Boş olmayan (yani veri üyeleri olan) bir Data yapısı (structure) oluşturmalısınız.

serialize()'ı Data nesnesinin adresi üzerinde kullanın ve dönüş değerini
deserialize()'a geçirin. Ardından, deserialize()'ın dönüş değerinin orijinal
pointer'a eşit olduğundan emin olun.

Data yapınızın dosyalarını teslim etmeyi unutmayın.


# Bölüm VII

# Alıştırma 02: Gerçek tipi belirleme

```
Alıştırma: 02
```
```
Gerçek tipi belirleme
Dizin: ex 02 /
Teslim Edilecek Dosyalar: Makefile, *.cpp, *.{h, hpp}
Yasak: std::typeinfo
```
Yalnızca public bir virtual destructor'a sahip bir **Base** sınıfı implemente edin.
Base'den public olarak inherit eden üç boş sınıf oluşturun: **A** , **B** ve **C**.

```
Bu dört sınıfın Orthodox Canonical Form ile tasarlanması gerekmez.
```
Şu fonksiyonları implemente edin:

```
Base * generate(void);
```
Rastgele olarak A, B veya C'yi instantiate eder ve örneği bir Base pointer'ı
olarak döndürür. Rastgele seçim implementasyonu için istediğiniz her şeyi
kullanmakta özgürsünüz.

```
void identify(Base* p);
```
p'nin işaret ettiği nesnenin gerçek tipini yazdırır: "A", "B" veya "C".

```
void identify(Base& p);
```
p'nin referans verdiği nesnenin gerçek tipini yazdırır: "A", "B" veya "C". Bu
fonksiyonun içinde bir pointer kullanmak yasaktır.

typeinfo header'ını include etmek yasaktır.

Her şeyin beklendiği gibi çalıştığını test edecek bir program yazın.


# Bölüm VIII

# Teslim ve Akran Değerlendirmesi

Ödevinizi her zamanki gibi Git deponuza teslim edin. Defans sırasında yalnızca
deponuzun içindeki çalışma değerlendirilecektir. Klasörlerinizin ve
dosyalarınızın adlarının doğru olduğundan emin olmak için kontrol etmekten
çekinmeyin.

Değerlendirme sırasında, ara sıra projenin **kısa bir değişikliği** talep
edilebilir. Bu, küçük bir davranış değişikliği, yazılacak veya yeniden
yazılacak birkaç satır kod veya eklenmesi kolay bir özellik içerebilir.

Bu adım **her proje için geçerli olmasa da** , değerlendirme yönergelerinde
belirtilmişse buna hazırlıklı olmalısınız.

Bu adım, projenin belirli bir bölümünü gerçekten anlayıp anlamadığınızı
doğrulamak içindir. Değişiklik, seçtiğiniz herhangi bir geliştirme ortamında
(örneğin, alışık olduğunuz kurulum) yapılabilir ve değerlendirmenin bir parçası
olarak belirli bir zaman aralığı tanımlanmadığı sürece birkaç dakika içinde
gerçekleştirilebilir olmalıdır.
Örneğin, bir fonksiyonu veya script'i küçük bir şekilde güncellemeniz, bir
görünümü değiştirmeniz veya yeni bilgi depolamak için bir veri yapısını
ayarlamanız istenebilir, vb.

Detaylar (kapsam, hedef vb.) **değerlendirme yönergelerinde** belirtilecek ve
aynı proje için bir değerlendirmeden diğerine farklılık gösterebilir.
