## CPP00

## Kullanılan kütüphaneler ve amaçları

<iostream>	I/O Streams. Giriş/Çıkış işlemleri.	std::cout, std::cin, std::endl
<string>	String Class. C'deki char * dizilerinin modern, güvenli ve esnek hali.	std::string, .length(), .substr()
<iomanip>	I/O Manipulation. Çıktıyı formatlamak için kullanılır.	std::setw(10) (Sütun genişliği ayarlama)
<cctype>	C Character Type. Karakter analizi ve dönüşümü.	std::toupper (büyük harf), std::isdigit (rakam mı?)
<cstdlib>	C Standard Library. Genel amaçlı fonksiyonlar.	std::atoi (string'i int'e çevirme)

## Syntax ve Kritik Yapılar 

## Namespace (İsim Uzayı) kavramı: <std::>

    Nedir? std, "Standard"ın kısaltmasıdır. C++ standart kütüphanesindeki her şey bu soyadını taşır. Fonksiyonları, sınıfları ve değişkenleri bir arada gruplayan bir kapsam. Aynı isim farklı namespacelerde bulunabilir.

    Neden? Kütüphanedeki cout ile karışmasın diye std::cout deriz. (isim çakışmalarını önlemek için). 

## std::string
char * mantığında manuel bellek yönetimi(malloc-free) gerektirmeyen kendi boyutunu bilen dinamik metin nesneleri.
## class
veri(değişkenler) ve bu veriyi işleyen fonksiyonların bir arada tanımlandığı şablon.
## Stream (Akış) Mantığı: cout ve cin
C'deki printf ve scanf fonksiyonlarının yerini "Stream" objeleri alır.

    std::cout << "Merhaba": "Merhaba" verisini çıktı akışına (ekrana) itmek (<<). charakter output standart çıktı akışı. (terminal ekranı)

    std::cin >> veri: Giriş akışından (klavye) veriyi değişkene çekmek (>>).

    Farkı: printf("%d", i) tip belirtmeni ister. cout << i tipi otomatik anlar (Type Safety).

## std::getline vs std::cin >>
Sen kodunda std::getline(std::cin, tmp) 

    std::cin >> tmp;: Boşluğu (space) gördüğü an okumayı durdurur. "Ahmet Mehmet" yazarsan sadece "Ahmet"i alır, "Mehmet" sonraki değişkene kayar.

    std::getline(std::cin, tmp);: \n (Enter) görene kadar tüm satırı okur.

   	Dikkat: Eğer kodunda bir yerde cin >> bir yerde getline karıştırırsan, cin arkasında bir \n karakteri bırakır ve sonraki getline boş satır okur.

## ex00 amacı
stdout (standart çıktı), döngü ve karakter manipülasyonunu c++ tarzıyla öğrenmek.

<cstring> C tarzında string işlemleri için kullanılan kütüphane.

this->_name = o anki nesneye işaret eder. örneğin name bir sınıfın private üyesi. bu üyeye erişmek için kullanılır. kod içerisinde kullanmak zorunlu değil ancak aynı isimde iki nesne var ise hangi nesnenin classın üyesi olduğunu işaretlemek için kullanılır.( karışmaması için ).

:: = scope resolution operator / kapsam çözünürlük operatörü.
örneğin std::cout std namespaceinin cout nesnesi demek.

<< = inseraction operator. veriyi akışa ittirme operatoru. örneğin sağdaki veriyi al soldaki couta gönder.

std::endl = endline iki iş yapar. '\n' yeni satır karakteri basar. tamponu (buffer) temizler (flash), yani yazının o an ekranda görünmesini sağlar, yeni satıra geçer ve ayırdığı buffer belleği işlem sonunda temizler. 

## ex01 amacı
class yapılarını öğrendiğimiz proje. sabit boyutlu dizileri öğreniyoruz.

contact sınıfının iç yapısını tanımlar. bu klass bir kişinin bilgilerini tutar. 
ifendef - define - endif birdenfazla kez dahil edilmesini engeller.

class içerisinde private ve public sınıfları tanımlı. (bir de bizim kullanmadığımız protected classlar var)

public classlar her yerden erişilebilir classlardır. dışarıdaki fonksiyonlar tarafından class nesneleri tarafından türetiilmiş classlar ve friendler tarafından erişilebilir.

private classlar gizli verileri tutarlar. yalnızca aynı sınıf nesneleri ya da friend class nesneleri tarafından erişilebilirler. 

protected classlar ise private classlardan farklı olarak, sınıfın içerisinde friend class, aynı  sınıf ve türerilmiş sınıflar tarafından erişilebilirler. sınıf dışından (nesne üzerinden) erişilemezler. ( bun kadar bilmek bence yeterli çünkü henüz bu classları işlemiyoruz. ek bilgi)

_firstName, _lastName, _nickname... her biri std::string tipindedir. kişilerin özel bilgilerini tutarlar. 

contact(): yapıcı ~contact(): yıkıcı
constructor ve destructur fonksiyonlar. bu seviyede destructor öğrenmemize gerek yok. 
<Constructor> bir sınıftan yeni bir nesne üretildiği anda otomatik olarak çalışan ilk fonksiyondur. Amacı, nesnenin değişkenlerine ilk değerlerini atamak ve onu kullanıma hazırlamaktır. (Sınıf ismiyle aynı isme sahiptir). 
<Destructor> nesnenin ömrü bittiğinde (kod bloğundan çıkıldığında veya silindiğinde) otomatik olarak çalışan son fonksiyondur. Amacı, nesnenin kullandığı belleği temizlemek veya açık dosyaları kapatmak gibi "çöpü dışarı atma" işlemlerini yapmaktır. (Sınıf isminin başına ~ işareti alır).

## getter ve setter fonksiyonlar.
Setter (Yazma): Sınıfın gizli (private) değişkenlerine dışarıdan gelen yeni bir değeri atamak/yazmak için kullanılan fonksiyondur. En önemli özelliği, veriyi kaydetmeden önce kontrol (validation) yapabilmemizi sağlamasıdır (örn: yaş değişkenine eksi bir sayı girilmesini engellemek).

Getter (Okuyucu): Sınıfın gizli (private) değişkenlerinin değerini dışarıya okumak/döndürmek için kullanılan fonksiyondur. Veriyi sadece gösterir, değiştirmez (bu yüzden genellikle const olarak tanımlanır).

sınıfların private alanlara güvenli erişimini sağlayan metodlardır. setter - yazma / getter - okuma

<neden private> kullanıyoruz = çünkü nesnenin iç durumu kontrol altında tutulur. dışarıdan doğrudan erişim yoktur. c++ encapsulation ilkesi.

contact.cpp
contact sınıfının fonksiyon gövdelerini içerir. yani gerçek işleri yapan kod bu kısımda.

void contact::setFirstName(std:string str) { this->_firstName = str;}
this işaretçisiyle nesnenin firstName üyesine değer atar.
std::string contact getFirstName() const {return(this->firstName)}

firstName değerini geri döndürür. 'const'  fonksiyonu nesnenin durumunu değiştirmez.

phoneBook.hpp

telefon rehberinin tuttuğu veri ve fonksiyonlar.

contact contact[8] = sabit boyutlu dizi en fazla 8 kişi saklayabilir. (dinamik bellek bu projede yasak)

int count = geçerli kayıt sayısı için.
int oldest = taşma durumunda hangi index üzerine yazılacağını tutar.(sirküler davranış).

phoneBook(); =  constructor.

phoneBook.cpp

PhoneBook::PhoneBook() : _count(0), _oldest(0) {} = yapıcı fonksiyon count ve oldesti program başlarken 0dan başlatır.

static std::string formatfield(const std::string &s){...} 
Tablo sütununa yazılacak metni 10 karaktere göre düzenler.
eğer len 10dan büyükse proje gerekliliği sebebiyle 9 karakter alır sonuna nokta ekler tabloda kısaltılmış şekilde gösterir. (yazılar sağa yazlı olmalı eğer yaslı değilse bunun için de fonk. yazılabilir.)

addContact = yeni contact oluşturup kullanıcıdan bütün alanları alır.

<std::getline(std::cin, tmp)> = getline satır başında sonunda arasında gizli boşluk  içerebileceğinden ötürü satırn tamamnı almak için kullanılır.
boş giriş kontrolü yapılır. tmp içinde atılır satır kontrol edilir. 
eğer kullanıcı bilgiyi boş bırakır enter derse uyarı metni çıkar ve kullanıcıdan boşluğu doldurması istenir. (rehbere boş alan eklenmez)
telefon numarasına ben yalnızca sayısal karakter kontrolü ekledim.

eğer kayıtlı kişi sayısı 8e ulaşırsa yeni kiş en eski kayıdın üzerine yazılır. (cicular kayıt)

<search contact const> = kayıtları listeler kullanıcıdan bir index alıp detay gösterir.
eğer count = 0 ise 'phone book is empty' uyarısı verir.

## tablo oluşturma 
std::setw(10) tablonun sütun widthini 10 olarak ayarlar.
projeye göre 4 sürun olmalı ve '|' ile ayrılmalı
index gösterimi 1'den başlamalı.

index sorgulamada geçersiz index verildiğinde 'invalid index' uyarısı verilmelidir.
geçerli index numaraları = 1-8
geçersiz index numaraları =  negatif sayılar, 8'den büyük sayılar, harfler, işaretler, '1a' gibi geçersiz sorgular.

main.cpp

PhoneBook phoneBook = phonebook classından bir phonebook nesnesi oluşturur.
bu nesne program boyunca rehberi tutar.
std:string cmd = kullanıcından alınan komutu saklamak için bir std:string değişkeni.

while(true){...} = sonsuz döngü. kullanıcı exit yazana kadar veya c/d sinyalleriyle programı sonlandırana kadar devam eder.
ADD - SEARCH - EXIT komutları ile işlem yapılır.
<c_str> = bazı fonksiyonlarla birlikte kullanılır. örneğin atoi. std::string içindeki metni alır sonuna bir nul terminator karakter ekleyerek bunu C dilinin anlayacağı bir karakter dizisine (const char *) dönüştürür.

>> const = kopya oluşturulamaz içindeki veri değiştirilemez. fonksiyon değişken uyumu olmalı.

>> toupper = C standartında int alır. ama bu değer ya EOF ya da unsigned char olmalı. eğer değer negatifse tanımsız davranış olur. (istenirse cast işlemi yapılabilir)

## CPP01

## ex00
steak - heap yapılarını öğrenmek amaç.
zombi sınıfı üzerinden yığın stack ve heap üzerinde nesne oluşturmayı (new / delete) ve destructor davranışını görmek.

newZombie ve randomChump yardımcı fonksiyonlar. 
>>newZombie= nesne oluşturma davranışını 'new' işlemi ile heap üzerinde gerçekleştirir.
>>randonChump = constructor ile normal bir nesneyi stack üzerinde oluşturur. ömrü scope kadardır ve heapten daha hızlıdır.

announce ve setName class içerisinde çünkü nesnenin durumu (name üyesi) ile doğrudan çalışır.
üye fonksiyonlar private verilere erişebilir bu yüzden sınıf içinde tanımlı.

const std::string& name kullanımı = const bu fonksiyon içinde parametre değiştirilmeyecek sadece okunacak demek için.
& (referans işareti) = kopya oluşturmayı engeller. boşluğu işaret etmez pointer gibi. rvalue (geçici value - kısa ömürlü olarak oluşan nesneler) ve lvalue ile çalışır. sadece bunları kabul eder. null olamaz çağıran yanlışlıkla bile null işaret edemez. geçici değer ile bağlanabilir. * gibi doğrudan geçici işaret edilemez. fonksiyon içinde başka nesneye bağlanamaz. (referans-pointer farkı ileride işlenecek)
rvalue: 
std::string("hi") ya da "hi" literalinden geçici bir std::string oluşturulduğunda ortaya çıkan nesne.
setName(const std::string& name) ile setName("Bob) veya setName(std::string(Bob)) çağırılabilir.

Not: geçici const referansa bağlandığında yerel değişkende scope süresi boyunca veya fonk. çağırıldığında çağrı süresince geçiciyi kullanabilir. ama geçici değişken fonksiyondan dönen referans olarak saklanamaz. (dangling - geçersiz yasak)

>>announce(void) const = sondaki const metodun nesnenin durmununn değişmediğini bildirir. böylece const zombie üzerinden de çağırılabilir.
zombie nesnesinin name üyesini okur ekrana yazdırır.
>>setName = name üyesine yeni değer atar. this->name = name.
parametre  &const olduğu için kopyalanamaz.

>>Zombie::Zombie(const std::string& n): name(n) {}
Bu yapıya Member Initializer List (Üye Başlatma Listesi) denir.
name(n) name doğrudan n(copy sontructor) oluşturur. bu ifade üyenin copy constructor ile başlatılmasını sağlar. name doğrudan n'in içeriğiyle oluşturulur. önce boş oluşturulup sonra atamadn daha verimli.
var olan nesnein içeriğini n ile değiştiriyor.  
İki temel farkı vardır:

    Zamanlama: Atama işlemi, constructor'ın gövdesi (body) çalışmadan önce biter.

    Performans: name = n; yazmaktan daha performanslıdır çünkü değişkeni önce boş yaratıp sonra içini doldurmak yerine, yaratırken doldurur.
örnek: 
	Senin Yazdığın: name(n) -> "Kutuyu üretirken içine ismi koy." (Tek adım)

	Eski Usul: { name = n; } -> "Boş kutu üret, sonra içine ismi koy." (İki adım)

>>Zombie::Zombie(): name("") {}
Varsayılan Kurucudur (Default Constructor).

Yaptığı iş şudur: Eğer kodunda parantez içinde hiçbir isim vermeden bir Zombie oluşturursan (örneğin: Zombie z;), bu fonksiyon devreye girer.

İki temel görevi vardır:

    Zombiyi parametresiz (argümansız) yaratmana izin verir.

    Zombinin ismini (name) başlangıçta boş bir string ("") olarak ayarlar, yani zombiyi "isimsiz" başlatır.

~Zombie destructor nesnenin ömrü bittiğinde çağırılır. kaynak temizliği yapar.  
stack nesnelerinde scope bittiğinde otomatik çalışırken heap nesnelerinde [delete] çağırıldığında çalışır.

>>Zombie* newZombie(std::string name)
Zombie* tipinde değer döndüren bu fonksiyon heap'te (dinamik bellek) new bellek bloğu ayırır.
pointer kullanımı allocated nesnesinin adresini döndürmek için. delete ile temizlenir. var yok durumu gösterilebilir.
nesne fonk. sonrasında hala valid çünkü heapte.

## ex01 HORDE

heap üzerinde N adet zombie nesnesi oluşturur. dizileri öğrendiğimiz egzersiz.
döngüde her elemana setName ile isim verir. 
Zombie* döndürür bu dizinin ilk elemanının adresidir.
horde dizinin başlangıç elemanının adresini tutar. delete için <delete[]> kullanılmalı.

proje çok fazla nesne ve dizi oluşumunu anlatıyor.

## ex02 

* (Pointer) ve & (Referance) arasındaki farkı, adre ve değer çıktısını ve nasıl erişildiğini öğreniyoruz.

>>std::string* stringPTR = &s : stringPTR değişkeninin adresini tutan pointer adresini yazdırır. *stringPTR ile değere erişilir. null olabilir.

>> std::string& stringREF = s : stringREF s için bir takma adıdır. &stringREF ile elde edilen adres &s ile aynıdır. referans bir kez bağlanır. null olamaz. başka nesneye yeniden bağlanmaz.
&s, stringPTR ve stringREF aynı adresi gösterir.
ve s ile aynı değeri yazdırırlar.

fonksiyon parametreleri, alias, dinamik bellek yönetimi arasındaki farkları kavramak için temel. referanslar parametre geçirirken kopyayı önlemek ve null riskini kaldırmak için; pointerlar nullable veya dinamik veri yapıları için kullanılır.

## ex03 getType / setType

bu projede kısaca ex02de öğrendiklerimizi pekiştirmek için küçük bir uygulama yapıyoruz. Maini proje veriyor zaten.

>>getType weapon içindeki type stringinin sabit (const) referansını döndürüyor. Bu stringin kopyasını oluşturmadan doğrudan erişim sağlar, çağrının değişmesini engeller.

>>setType parametreyi const referans ile alır. gfereksiz kopyayı önler. weapon nesnesinin type üyesini verilen değerle değiştirir.

>>weapon& nesnenin her zaman var olacağını ve değiştirilemez bir bağlantı istendiğinde kllanılır. başka bir nesneye yeniden  bağlanmaz.

>>weapon* nesnenin opsiyonel olarak yok olabileceği ya da daha sonra atanabileceği durumlar için. null olaiblir. yeniden atanabilir.

>>örnek= void Weapon::setType(const std::string& t) { type = t; }
settype ile weapon nesnesinin type üyesini t ile güncellemek.

## ex04

>>eof= akışta son(EOF) ile karşılaşıp karşılaşmadığını bildirir.
getline son satır karakterini okumaz, çıkarır. döngü içinde her okunan satırdan sonra arasında '\n' koymak istiyorum. fazladan '\n' eklememek için eof kontrolü yapıyorum.

>>cerr= standart namespace'deki hata çıktısı ostream. hata uyarı mesajları için kullanılır. (cout normal program çıktısını bozmamak ve hata uyarılarını ayrı bir akışta tutmak için, hata mesajlarının hemen gözükmesi gerektiğinde tercih edilir.)

>>ifs= input file stream. dosyadan okuma yapar.  dosyayı açmak ve içeriğini okumak. fdnin gelişmiş hali. dosyanın nerede kaldığın, hata bayraklarına kadar tutuyor. <isopen> açılıp açılmadığını kontrol eder. getline ile satır satır okur. <c_str> const char * olarak dönüştürmesi için.

>>ofs= output file stream. çıktı, output, dosya akışı. bellekteki akışta veriyi dosyaya yazar.

>>clear neden kullanılır= tekrar çağırıldığında ya da dışarıdan gelen stringi yeniden kullanacağımızda önceki içeriğin kalmaması için boşaltır.

>>bad = dosyada açıldıktan sonra bir sıkıntı oldu mu? değişiklik oldu mu? dosya flagleri son açıldığında değiştirilmiş olabilir. file eof gibi flaglerle dosyanın bittiğini düşünebilir. tüm dosyanın kontrol edildiğinden emin olmak için. donanım arızası vb. durumları kontrol eder. Kritik/Sistem hatasıdır. Akışın kendisi bozulmuştur (örneğin; dosya okunurken aniden silinmiştir, bellek yetmemiştir). Veri akışı kopmuştur ve genellikle kurtarılamaz bir durumdur.

>>yeni oluşturulan dosyayı kontrol ederken bad yerine fail kullanmak daha mantıklı. <fail> bad'den daha dar kontrol. akışta bir hata gördüğünde programı durdurur. Format/Tür hatasıdır. Program senden int (sayı) beklerken kullanıcı string (harf) girerse failbit yanar. Akış (stream) fiziksel olarak sağlamdır; sadece o anki işlem başarısız olmuştur. Hatayı temizleyip (clear) yola devam edebilirsin.

## ex05 - Harl - dizi
Sınıfın iç detaylarını (özel fonksiyonları) dışarıya kapatarak soyutlamayı bozmuyoruz. Kullanıcıya complain üzerinden tek bir giriş noktası sunuyoruz. Böylece gelen seviye (level) bilgisini içeride doğrulayıp ilgili fonksiyonu çağırma işini, dışarıdan gizli bir şekilde yönetiyoruz

>>complain bir member fonksiyon pointer tanımlar. *fptr
aynı sıra ile iki dizi tutar. level[] string anahtarlar, func[] bu sevyelere karşılık gelen üye fonksiyonlar. 

this->*funcs[i] eşleşme bulursa ilgili private üye fonk. çağırır ve geri döner.
>>Member Function Pointers (Üye Fonksiyon İşaretçileri): if-else zinciri kurmak yerine, fonksiyonların adreslerini bir dizide tutup doğrudan çağırmak performans ve temiz kod sağlar. (if ormanına girmeden dispatch(seviye->işlem) yapar.)

## ex05 gemini özeti:
📝 Harl (Ex05) - Member Function Pointers Özeti

1. Temel Felsefe (Encapsulation & Abstraction)

    Amaç: Sınıfın iç detaylarını (private fonksiyonlar: debug, info vs.) dışarıya kapatarak soyutlamayı korumak.

    Yöntem: Kullanıcıya complain(level) üzerinden tek bir giriş noktası sunulur. Harl, gelen şikayet seviyesini içeride doğrular ve ilgili fonksiyonu kendisi çağırır. Dışarıdan kimse harl.debug() diyemez.

2. Mekanizma (Dispatch Table / Dağıtım Tablosu)

    Yapı: complain fonksiyonu, string anahtarlar (levels) ve bunlara karşılık gelen fonksiyon adreslerini (ptr) tutan iki paralel dizi (veya array of pairs) kullanır.

    İşleyiş: Döngü ile string eşleşmesi aranır. Eşleşme bulunduğunda, ilgili indexteki fonksiyon işaretçisi tetiklenir.

3. Kritik Syntax (Burası Çok Önemli!) C++'ta bir üye fonksiyonu işaret etmek, normal bir C fonksiyonunu işaret etmekten zordur çünkü bir nesneye (instance) ihtiyaç duyar.

    Tanımlama: void (Harl::*ptr)(void) = &Harl::debug;

    Çağırma: (this->*ptr)();

        this->: Hangi nesne üzerindeyiz?

        *ptr: Hangi fonksiyonu çağırıyoruz?

        (): Argümanlar (varsa).

4. Neden Yaptık? (Clean Code)

    If-Else Ormanından Kaçış: Uzayıp giden if (level == "DEBUG") ... else if ... zinciri yerine, veriye dayalı (data-driven) temiz bir yapı kurduk.

    Bakım Kolaylığı: Yeni bir seviye eklemek için koda yeni if blokları eklemek yerine, sadece diziye yeni bir eleman eklemek yeterlidir.

## ex06 switch/case

Bu proje, sınıf yapısı olarak Ex05 ile tamamen aynıdır; tek fark main içindeki switch-case filtresidir. Burada case bloklarına bilerek break koymayarak 'fall-through' (aşağı düşme) mantığını kullanırız.

Kod, argüman olarak verilen seviyeden giriş yapar ve bir break görene kadar (yani sona kadar) altındaki tüm işlemleri zincirleme çalıştırır.

    Örneğin: DEBUG ile başlarsak tüm mesajları,

    WARNING ile başlarsak sadece o ve üzerindeki (ERROR) seviyeleri görürüz.

Eğer girilen ifade hiçbir case ile eşleşmezse, default bloğu devreye girer ve istenen hata mesajını döner.

⚠️NOT: C++'ta switch yapısı String (metin) ile çalışmaz, sadece tamsayı (int/char/enum) ile çalışır. Bu yüzden Ex06'da önce gelen string'i (örn: "DEBUG") bir döngüyle kontrol edip sayısal bir index'e (0, 1, 2, 3) çevirmemiz, sonra bu index'i switch içine atmamız gerekir.

## CPP02 FIXED-POINT

Tam sayıları(int) kullanarak ondalıklı sayıları temsil etmenin çok zekice ve performanslı bir yolu.

Temel mantık = "noktayı sabitlemek"
bilgisayarlar tam sayıları çok hızlı işler ama ondalıklı sayıları(float, double) işlemek daha karmaşıktır.
>> sabit noktalı sayılarda, ondalıklı sayının yerini en baştan belirleriz ve bir daha değiştirmeyiz.

örneğin:
>>bir cetvelde milimetre cinsinden ölçüm yaptığımızda eğer 10.5cm ölçülürse bunu 105mm olarak tutarız.
saklanan değer= 105(tam sayı)
sabit kural= nokta her zaman sağdan bir basamak içeride
gerçek değer= 10.5

>>bankacılık sisteminde genellikle float kullanılmaz çünkü <floating-point(kayan noktalı)> sayılar hassas hesaplamalarda (0.1+0.2) küçük hatalar yapabilir. Bunun yerine sabit noktalı mantık kullanılır. 
cüzdanda 15.75tl varsa bilgisayar bunu float olarak değil int olarak 1575 şeklinde saklar.
ölçek(scaling factor) 100. Hesaplama yaparken her zaman son iki basamak kuruştur kuralı.

>>gerçek değer = saklanan tam sayı / 100

## Formül (Bitlik sistem)
                    saklanan tam sayı
elde etmek    =  ---------------------- = 47/4 = 11,75
istediğimiz sayı	   bit sayısı
				      2

saklanan değer -> bit karşılığı
bit sayısı -> fized point olarak belirlenen bit

<Tam sayıyı hafızada hazırlama>
sayımız 11.75 olsun.
11 sayısının 8 bitlik sistemde karşılığı 0000 1011
kuralımız son 2 bit ondalıktır olsun
11 tam sayısını tam sayı kısmına kaydırmak için 2 basamak sola iteliyoruz. (11<2) 
>ham 11 = 0000 1011 
sola kaymış hali = 0010 1100 (yani 44)
<ondalık kısmı ekleme>
sağda açılan 2 boşluğa (0.75)' in karşılığı olan 11' i ekleyeceğiz. bitlik gösterimi 0000 0011 
yani sayının tam sayı ile birleşmiş son hali = 0010 1111 (yani 47 olur)

formülde yerine koyalım

elde etmek istediğimiz sayı 11.75 = 47 / 4 
>>4 = 2 üreri 2 olduğu için 4 olur. çünkü biz son 2 bit ondalık olsun dedik.

>> neden ekleme değil kaydırma
çünkü 1011 yanına 11 eklemeye çalışsaydık 8biti aşardı. sola kaydırıp yer açıyoruz.
>> başka örnekler için 11=0.75 10=0.5 01=0.25 00=0
<CPP02>' de 32bitlik sistem var. (int)
2 bit ondalık değil 8 bit ondalık.
static const int _bits = 8 olacak.
bu da 8 bit kaydıracağız demek.

dolayısıyla sayı2 ile değil 256(2 üzeri 8) ile çarpılıp bölünürr.

fixed value: ham bitleri tutan değişken 
static const int fractional bits = 8 (sabit her zaman 8)

fixed() : default constructor.
fied(const fixed &other) : copy connstructor.
fixed &operator=(const fixed &other): copy assigment operator.
~fixed() : destructor.

getRawBits: değeri döndürür
setRawBits: değeri set eder.

<orthodox cannonical form nedir?>
c++'ta bir sınıfın "kendine yeten" ve "güveli kopyalanabilir" bir tip haline gelmesi için gereken standart iskelet.

>> 4 ana öğesi vardır.
 >default constructor: nesne ilk oluşturulduğunda güvenli bir başlangıç değeri(0) verir.
 >copy constructor: fixed a=b; dediğinde verilerin birbirine karışmamasını sağlar.
 >copy assigment operator(operator=): a=b dediğinde mavcut nesnenin değerini günceller.
 >destructor: nesne bellekten silinirken temizlik yapar.

pointer kullanımı başladığında bu form olmazsa bellek sııntısı veya double free hataları olabilir.

<accuracy vs. precision> (makalelere göre)

>integers (tam sayılar) tamamen accuracy (doğruluk) odaklıdır. 2+1 = 3'tür. ama hassasiyetleri yoktur.
>floats (kayan noktalılar) precision (hassasiyet) sunarlar ama doğruluk düşüktür. 'oyun hamuru' benzetmesi gibi esnektirler ama asla mükemmel bir kare(tam doğruluk) olamazlar.
>fixed point bu ikisi arasında bir denge "balance" kurar. Oyun motorları ve sinyal işleme(DSP) gibi hızın çok kritik olduğu yerlerde kullanılır.

makalede fixed <8,3> vermişti bizim örneğimizde <8,2>.
projede ise fixed <32,8> kullanıyoruz. ölçek faktörü 2 üzeri 8 yani 256.
hafızada 1 saklıyorsam gerçek değerim 1/256'dır.
hafızada 256 saklıyorsam gerçek değerim 1'dir.

## ex00 
 ortodox cannonical form öğreniyoruz.
## ex01
bu projede int/float <-> fixed dönüşümleri ve << operatörünü öğreniyoruz.

>> kaydırma operatorü yerine sabit kullanıl (1<<8)
(1<< _fractionalBits) doğru ama performans ve okunabilirlik için constructor içinde veya toFloat içinde kullanmak yerine makaledeki 'ölçekleme faktörü' (256) bir kez hesaplamak daha iyi. 

>> float dönüşümündeki hassasiyet (Rounding)
fixed::fixed(const float f) içinde roundf kullanımı
makaedeki gibi float oyun hamuru gibi tam karşılığı olmayabilir. 
-> roundf ile yakın bir bir değeri yakalanıyor. 
roundf binary olarak her zaman kesin ifade edilemediği için çarpma işlemi sonrası çıkan sonucun en yakın tam sayıya (bit karşılığına) yuvarlanması hassasiyet korumak için makalede önerilen bir yöntem.

>> toInt/ toFloat mantığı 
 toInt fonksiyonunda >>8 (bölme işlemi) çok mantıklı çünkü bu sayının ondalık kısmını çöpe atar ve sadece tam sayı kalır.

## neden (float)this->_fixed value / 256 
fixed point sisteminde virgül 8 bit sayıyı 2üzeri8'e bölmek o sanal virgülü gerçek yerine koyarak float olarak okumamızı sağlar.

## << operator overloading neden uye fonk. (member fonk) değil?
çünkü soldaki nesne std::ostream yani fixed değildir. bu yüzden sınıfın dışında (ama sınıfın verilene erişebilecek şekilde veya toFloat kullanarak) tanımlanmalıdır.

## ex02
bu projede artık sadece sayıları saklamayı değil onları birbirleriyle etkileşime sokmayı öğreniyoruz.

-> çarpma-bölme işlemlerindeki taşma (overflow) mantığını long long kullanarak çözebiliriz. 
	-en önemli kavram ϵ(epsilon) ve artırım
		"Increase or decrease the fixed-point value by the smallest representable ϵ such that 1+ϵ>1."
	>>makaledeki precision(hassasiyet) konususnun tam karşılığı bizim sistemimizde temsil edilen en küçük birim 2üzeri−8 yani 1/256=0.00390625'dir.
koddaki this->_fixedValue += 1 aslıdna sayıyı aslında sayıyı matematiksel olarak 0.00390625 (1/256) kadar artırır. çünkü tam sayılar dünyasında en küçük adım 1'dir. Fixed-point dünyasında bu 1 birim, ondalık kısmın en sağındaki bitin açılması demektir.

## Aritmetik Operatörler ve Ölçekleme Sorunu
Toplama ve çıkarmada sorun yok; ama çarpma ve bölme kısmında makalelerde bahsedilen "Shifting" mevzusu tekrar devreye giriyor. 

>>çarpma(*): İki fixed-point sayıyı çarptığında, aslında iki kez ölçeklenmiş bir sayı elde edilir. (2üzeri 8 × 2üzeri 8= 2üzeri 16)

ben projede tmp>>_fractionBits yaparak yani sonucu tekrar 2üzeri 8'e bölerek (sağa kaydırarak) orijinal ölçeğe (8bitli ondalık) geri getiriyorum.

>>long long-> makaledeki gibi iki 32 bit int çarpıldığında 64bit bir alana ihtiyaç duyulabilir. veri kaybını önlemek için.

>>bölme(/): Bölmede tam tersi bir durum var. Eğer direkt bölünürse paydaki 2üzeri 8 ve paydadaki 2üzeri 8 birbirini yok eder ve sonuç "tam sayı" gibi kalır.

->ben num<<_fractionBits ile bölme işleminden önce payı sola kaydırarak ölçeği koruyorum. 'makaledeki shift before divide'

>> static const kullanımı: 1<< _fractionalBits yerine 1 kez hesaplayıp sabit olarak kullanmak daha mantıklı

fixed(const int n) constructor'ı : fixed r; oluşturup değer atamak default constructor'ın gereksiz yere çalışmasına neden olur. setRawBits ya da private bir cunstroctor kullanışlı olabilir.

--------
## neden operaotor overloading?
a + b yazabilmek, kodu sadece okunabilir kılmaz; aynı zamanda karmaşık sayı sistemlerini (Fixed Point gibi) sanki yerleşik bir tipmiş (int, float) gibi kullanmamızı sağlar.

## Pre-increment vs Post-increment:
++a (önce artır, sonra döndür) ile a++ (mevcut hali kopyala, artır, eskiyi döndür) arasındaki fark nesen kopyalama maliyeti.
++a verimli. doğrudan mevcut nesnenin içindeki değeri değiştirir ve kendisini (*this) referans olarak döndürür. bellek harcamaz. a++ maliyetlidir. sayının eski halini hatırlamak zorundadır. önce tmp tutar sonra nesneyi arttırır ama çıktıda eskiyi döndürür. yani a++ ile hep fazladan nesne oluşturup yok ederiz.

>> fonk. kullanım
fixed& operator ++() : parametresiz pre 
fixed operator ++(int) : içindeki sahte int bunun post olduğunu derleyiciye anlatmak için kullanılan flag.

## chatten eksta not istemiştim bu kısımları ben de daha okumadım.

1. static Fonksiyon Nedir ve Neden min/max Statiktir?

Bunu anlamak için Nesne (Instance) ile Sınıf (Class) arasındaki farkı bilmelisin.

    Non-Static (Normal) Fonksiyon: "Benim değerimle çalış." der. Bir nesneye ihtiyaç duyar.

        Örn: a.toInt() -> Burada a nesnesinin içindeki değeri çeviririz. Gizli bir this işaretçisi vardır (this = &a).

    Static Fonksiyon: "Genel bir kural işlet." der. Nesneye ihtiyaç duymaz, sınıfın kendisine aittir.

        Örn: Fixed::max(a, b) -> Burada a veya b nesnesinin üzerinden işlem yapmıyoruz. İki nesneyi alıp kıyaslıyoruz.
Neden min ve max Static Yapılır? Eğer static yapmasaydın şöyle çağırmak zorunda kalırdın:
	Fixed a(10);
	Fixed b(20);
	Fixed c = a.max(b); // "a, sen b ile kendini kıyasla"
Bu sözdizimi asimetriktir ve gariptir. Sanki işi a yapıyormuş gibi durur.
Oysa static yaptığında:
	Fixed c = Fixed::max(a, b); // "Fixed sınıfı, şu iki elemana bak ve büyüğünü ver"
Bu, matematiksel fonksiyonlar (Math.max gibi) için standarttır. Static fonksiyonların içinde this pointer'ı yoktur çünkü belirli bir nesneye bağlı değildirler.

2. Notların İçin Düzenlemeler ve Teknik Eklemeler

Notların zaten çok güçlü, ama aşağıdaki teknik detayları aralara serpiştirirsen (veya ayrı bir başlık açarsan) proje savunmasında (defense) çok daha yetkin görünürsün.
A. Ex00 & Orthodox Canonical Form (OCF) Hakkında Ek

Senin notunda: "pointer kullanımı başladığında bu form olmazsa bellek sıkıntısı..." Ekleme: Özellikle operator= (Copy Assignment) içinde Self-Assignment Check (Kendine atama kontrolü) yapmak çok kritiktir.
	if (this != &other) // Bu kontrol

Neden? Eğer a = a; denirse ve biz içeride dinamik bellek yönetiyor olsaydık (bu projede yok ama genel kural), önce a'nın belleğini silip sonra a'dan kopyalamaya çalışırdık. Sildiğimiz şeyi kopyalamaya çalışacağımız için program çökerdi. Senin kodunda bu kontrol var, notlarına "Güvenlik Kontrolü" olarak ekleyebilirsin.
B. Ex01 & Bitwise Magic (Bit Kaydırma Büyüsü)

Senin notunda: "neden ekleme değil kaydırma" Teknik Detay Eklemesi: Bilgisayar dünyasında 2 ile çarpmak veya bölmek yerine Bit Shifting (Kaydırma) kullanmak işlemci (CPU) için çok daha ucuzdur.

    x << 8 demek x * 256 demektir.

    x >> 8 demek x / 256 demektir. CPU bunu tek bir "cycle"da yapar, ama çarpma işlemi daha fazla güç harcar. Fixed Point aritmetiğinin "hızlı" olmasının sebeplerinden biri budur.

C. Ex02 & Aritmetik İşlemlerdeki Hassas Denge

Senin notun: "long long kullanarak veri kaybını önlemek" Daha Teknik Açıklama:

    Çarpma: İki Q8.8 (Fixed Point) sayıyı çarptığında sonuç Q16.16 formatında olur (yani ondalık kısım 16 bite çıkar). Eğer bunu 32 bitlik int içine sığdırmaya çalışırsan taşma (overflow) olur.

        Bu yüzden long long (64 bit) ile işlem yapıp sonucu tekrar 8 bit sağa kaydırarak (>> 8) ondalık kısmı tekrar 8 bite düşürürüz (Rescaling).

    Bölme: a / b işleminde 5 / 2 tam sayı bölmesi yaparsan sonuç 2 olur (0.5 kaybolur).

        Bu yüzden Shift Before Divide: Payı (a) önce sola kaydırıp (<< 8) büyütürüz, sonra böleriz. Böylece kaybolacak ondalık kısmı kurtarmış oluruz.

D. Pre-increment vs Post-increment (Mülakat Sorusu)

Senin notun: "a++ maliyetlidir. sayının eski halini hatırlamak zorundadır." Ekleme: Koduna int parametresi eklememizin (operator++(int)) tek sebebi derleyiciye (compiler) "Hey, bu parametreli olan fonksiyon Post-Increment (a++) içindir, onu çağırırken diğerinden ayır" demektir. O int parametresi fonksiyonun içinde asla kullanılmaz (dummy parameter).

3. Kodun Üzerine Küçük Bir İpucu

Kodunda şu yorumu gördüm: // İYİLEŞTİRME: Değişkenlere doğrudan erişmek yerine setRawBits kullanmak encapsulation için daha iyidir.

Düzeltme/Bilgi: Aslında Fixed sınıfının içindeyken (operator+ fonksiyonu gibi), other._fixedValue diyerek private değişkene doğrudan erişmek Encapsulation'ı bozmaz. C++'ta erişim kısıtlamaları nesne bazlı değil, sınıf bazlıdır. Yani bir Fixed nesnesi, başka bir Fixed nesnesinin private üyelerine erişebilir.

    setRawBits kullanmak bir tercih meselesidir (function call overhead yaratabilir).

    Doğrudan erişim (this->_fixedValue + other._fixedValue) genelde operatörlerde daha performanslı kabul edilir. İkisi de doğru, ama doğrudan erişim yanlış değil.

Özetlenmiş Yeni Not Başlığı Önerisi: "Static ve This İlişkisi"

Not defterine şu kutuyu ekleyebilirsin:

    Neden Min/Max Statik?

        Bağımsızlık: Karşılaştırma işlemi a nesnesine veya b nesnesine ait değildir; genel bir matematik kuralıdır.

        Çağrım Kolaylığı: a.max(b) yerine Fixed::max(a, b) yazmak, işlemin simetrik olduğunu gösterir.

        Teknik Fark: Statik fonksiyonlar this pointer'ına sahip değildir. Bu yüzden sınıfın non-static değişkenlerine (yani _fixedValue) doğrudan erişemezler; sadece parametre olarak aldıkları nesneler üzerinden işlem yaparlar.
