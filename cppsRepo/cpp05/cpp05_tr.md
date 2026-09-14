# C++ - Modül 05

## Tekrar ve İstisnalar

_Özet:
Bu belge C++ modüllerinden Modül 05'in alıştırmalarını içerir._

```
Sürüm: 11.
```

## İçindekiler

- I Giriş
- II Genel Kurallar
- III Yapay Zeka Talimatları
- IV Alıştırma 00: Anne, büyüyünce bürokrat olmak istiyorum!
- V Alıştırma 01: Hepsi, işte başa dönüş!
- VI Alıştırma 02: Hayır, form 28C değil 28B'ye ihtiyacın var...
- VII Alıştırma 03: En azından bu kahve yapmaktan daha iyidir
- VIII Gönderme ve Eş Değerlendirme


# Bölüm I

# Giriş

_C++ Bjarne Stroustrup tarafından C programlama dilinin bir uzantısı olarak veya "Sınıflı B ilişkili C" (kaynak: Wikipedia) olarak oluşturulan genel amaçlı bir programlama dilidir._

Bu modüllerin amacı sizi **Nesne Yönelimli Programlama** ile tanıştırmaktır.
Bu C++ yolculuğunuzun başlangıç noktası olacaktır. OOP öğrenilmesi için birçok dil önerilir.
Biz C++'ı seçtik çünkü eski arkadaşınız C'den türemiştir.
Bu karmaşık bir dil olduğundan ve işleri basit tutmak için kodunuz **C++98** standardına uygun olacaktır.
Modern C++'ın birçok açıdan önemli ölçüde farklı olduğunun farkındayız. Yani, proficient bir C++ geliştirici olmak istiyorsanız,
42 Ortak Çekirdeği tamamladıktan sonra ilerlemeniz size kalmış!


# Bölüm II

# Genel Kurallar

**Derleme**

- Kodunuzu c++ ve -Wall -Wextra -Werror bayraklarıyla derleyin
- Kodunuz -std=c++ bayrağını eklerseniz yine derlenmesi gerekir

```
Biçimlendirme ve Adlandırma Kuralları
```
- Alıştırma dizinleri şu şekilde adlandırılacaktır: ex00, ex01, ... , exn
- Dosyalarınızı, sınıflarınızı, işlevlerinizi, üye işlevlerinizi ve özniteliklerinizi yönergelerde gerektiği şekilde adlandırın.
- Sınıf adlarını **UpperCamelCase** biçiminde yazın. Sınıf kodunu içeren dosyalar her zaman sınıf adına göre adlandırılacaktır. Örneğin:
    ClassName.hpp/ClassName.h, ClassName.cpp, veya ClassName.tpp. Daha sonra, bir tuğla duvarı için "BrickWall" adında bir sınıf tanımı içeren bir başlık dosyanız varsa,
    adı BrickWall.hpp olacaktır.
- Aksi belirtilmedikçe, her çıkış mesajı yeni satır karakteriyle bitmelidir
    ve standart çıkışa gösterilmelidir.
- _Norminette'ye Hoşça Kalın!_ C++ modüllerinde kodlama stili zorunlu değildir. Favori stilinizi takip edebilirsiniz. Ancak
    eş değerlendiricilerinizin anlayamadığı kodu puanlandıramayacaklarını unutmayın. Temiz ve okunabilir kod yazmanız için elinizden geleni yapın.

```
İzin Verilen/Yasaklı
```
```
Artık C'de kod yazmıyorsunuz. C++ zamanı! Bu nedenle:
```
- Standart kütüphaneden neredeyse her şeyi kullanmanıza izin verilir. Bu nedenle, bildiğiniz şeye sadık kalmak yerine,
    alışkın olduğunuz C işlevlerinin C++ sürümlerini mümkün olduğunca kullanmak akıllıca olur.
- Ancak başka hiçbir harici kütüphane kullanamazsınız. Bu, C++11 (ve türetilmiş biçimleri) ile Boost kütüphanelerinin
    yasaklı olduğu anlamına gelir. Aşağıdaki işlevler de yasaklıdır: *printf(), *alloc() ve free(). Bunları kullanırsanız,
    notunuz 0 olacak ve bu kadar.


C++ - Modül 05 Tekrar ve İstisnalar

- C++'ın özelliklerinden birini kullandığınızda, asla yasaklanmadığı sürece
    using namespace <ns_name> ve friend anahtar kelimeleri yasaklanmıştır. Aksi takdirde notunuz -42 olacak.
- **STL'yi yalnızca Modüller 08 ve 09'da kullanmanıza izin verilir.** Bu şu anlama gelir:
    **Konteyner** (vector/list/map vb.) ve **Algoritmalar** (<algorithm> başlığını içeren her şey) yoktur.
    Aksi takdirde notunuz -42 olacak.

```
Bazı Tasarım Gereksinimleri
```
- Bellek sızıntısı C++'da da meydana gelir. Bellek ayırdığınızda (new anahtar sözcüğünü kullanarak),
    **bellek sızıntılarından** kaçınmalısınız.
- Modül 02'den Modül 09'a kadar, sınıflarınız **Ortodoks****Kurallı Form**'da tasarlanmalıdır,
    açık olarak başka türlü belirtilmedikçe.
- Bir başlık dosyasına yerleştirilen herhangi bir işlev uygulaması (işlev şablonları hariç)
    alıştırmaya 0 anlamına gelir.
- Her başlık dosyasını diğerlerinden bağımsız olarak kullanabilmeniz gerekir. Bu nedenle,
    ihtiyaç duydukları tüm bağımlılıkları dahil etmelidirler. Ancak, başlık koruma ekleyerek
    **çift dahil** sorununu önlemeniz gerekir. Aksi takdirde notunuz 0 olacak.

```
Oku Beni
```
- Key gerekliyse ek dosyalar ekleyebilirsiniz (örneğin, kodunuzu bölmek için). Bu görevler bir program tarafından doğrulanmadığından,
    zorunlu dosyaları teslim ettiğiniz sürece bunu yapmakta özgürsünüz.
- Bazen bir alıştırmanın yönergeleri kısa görünebilir ancak örnekler açıkça yazılı olmayan gereksinimleri gösterebilir.
- Başlamadan önce her modülü tamamen okuyun! Gerçekten, bunu yapın.
- Odin'in ve Thor'un adıyla! Zihninizi kullanın!!!

```
C++ projeleri için Makefile'ye ilişkin olarak, C'deki kurallar
aynı şekilde geçerlidir (Norm bölümündeki Makefile'ye bakın).
```
```
Birçok sınıf uygulamanız gerekecektir. Bu sıkıcı görünebilir,
ancak sevdiğiniz metin editörünü kodlayabiliyorsanız değil.
```

C++ - Modül 05 Tekrar ve İstisnalar

```
Alıştırmaları tamamlamak için belirli bir özgürlüğe sahipsiniz.
Ancak zorunlu kuralları takip edin ve tembellik etmeyin. İtişe gerekli
yararlı bilgiler kaçırırdınız! Teorik kavramları okumaktan çekinmeyin.
```

# Bölüm III

# Yapay Zeka Talimatları

## ● Bağlam

Bu proje, 42 eğitiminin temel yapı taşlarını keşfetmenize yardımcı olmak için tasarlanmıştır.

Anahtar bilgi ve becerileri uygun şekilde yerleştirmek için yapay zeka araçlarını ve desteğini kullanan
düşünceli bir yaklaşım benimsemeliyiz.

Gerçek temel öğrenme, başarısız olalıp, tekrar edip ve eş-öğrenme değişimi yoluyla gerçek zihni zahmetini gerektirir.

42'nin yapay zeka hakkındaki duruşunun daha tam bir açıklaması için — bir öğrenme aracı olarak, 42 eğitiminin bir parçası
olarak ve iş piyasasında bir beklenti olarak — lütfen intranet üzerinde adanmış SSS'ye bakın.

## ● Ana İleti

```
☛ Kısayollar olmadan güçlü temeller oluşturun.
```
```
☛ Gerçekten teknik ve güç becerilerini geliştirin.
```
```
☛ Gerçek eş-öğrenme deneyimi yaşayın, öğrenme ve yeni sorunları çözme şeklini öğrenmeye başlayın.
```
```
☛ Öğrenme yolculuğu sonuçtan daha önemlidir.
```
```
☛ Yapay zeka ile ilişkili riskleri öğrenin ve genel tuzaklardan kaçınmak için etkili
kontrol uygulamaları ve karşı önlemler geliştirin.
```
## ● Öğrenen Kuralları:

- Özellikle yapay zekaya başvurmadan önce atanan görevlere akıl yürütme uygulamalısınız.


C++ - Modül 05 Tekrar ve İstisnalar

- Yapay zekadan doğrudan yanıt istememelissiniz.
- 42'nin yapay zeka hakkındaki küresel yaklaşımını öğrenmelisiniz.

● **Faz Çıktıları:**

Bu temel faz içinde aşağıdaki çıktıları elde edeceksiniz:

- Uygun teknik ve kodlama temelleri edinin.
- Yapay zekanın bu faz sırasında neden ve nasıl tehlikeli olabileceğini bilin.

● **Açıklamalar ve Örnek:**

- Evet, yapay zekanın var olduğunu biliyoruz — ve evet, projelerinizi çözebilir. Ancak burada
    öğrenmek için varsınız, yapay zekanın öğrendiğini kanıtlamak için değil. Sadece
    yapay zekanın verilen problemi çözebildemini göstermek için zamanınızı (veya bizimkini) boşa harcamayın.
- 42'de öğrenme cevabı bilmekle ilgili değildir — kendiniz bulma becerisini geliştirmekle ilgilidir.
    Yapay zeka cevabı doğrudan verir, ancak bu kendi akıl yürütmenizi oluşturmanızı engeller.
    Ve akıl yürütmenin zamanı, çabası ve başarısızlık gerekir. Başarının yolu kolay olacak değildir.
- Sınavlar sırasında yapay zekanın kullanılamayacağını bilin — internet yok, akıllı telefonlar yok, vb.
    Öğrenme sürecinizde yapay zekaya çok fazla güvendiyseniz bunu çabucak fark edeceksiniz.
- Eş-öğrenme sizi farklı fikirler ve yaklaşımlara maruz bırakarak kişilerarası becerilerinizi
    ve ıraklaştırılmış düşünme yeteneğinizi iyileştirir. Bu, sadece bir botla sohbet etmekten çok daha değerli.
    Yani utanmayın — konuşun, soru sorun ve birlikte öğrenin!
- Evet, yapay zeka müfredatın bir parçası olacak — hem bir öğrenme aracı olarak hem de
    kendisi bir konu olarak. Hatta, kendi yapay zeka yazılımını oluşturma şansınız olacak.
    Intranette mevcut olan belgelerde 42'nin sizin üzerinden geçeceğiniz kresen yaklaşımı hakkında
    daha fazla bilgi edinebilirsiniz.

```
✓ İyi Uygulamaa:
```
```
Yeni bir konsept üzerine takılıp kaldım. Yakınımdaki birinden nasıl yaklaştığını sorarım. 10 dakika konuşuruz
— ve aniden anlamaya başlıyorum. Bunu anlıyorum.
```
```
✗ Kötü Uygulamaa:
```
```
Yapay zekayı gizlice kullanıyorum, doğru görünen kodunu kopyalıyorum. Eş değerlendirmesi sırasında, hiçbir şey açıklayamıyorum. Başarısız oldum.
Sınav sırasında — yapay zeka yok — takılıp kaldım. Tekrar başarısız oldum.
```

# Bölüm IV

# Alıştırma 00: Anne, büyüyünce

# bürokrat olmak istiyorum!

```
Alıştırma: 00
```
```
Anne, büyüyünce bürokrat olmak istiyorum!
Dizin: ex 00 /
Gönderilecek Dosyalar: Makefile, main.cpp, Bureaucrat.{h, hpp}, Bureaucrat.cpp
Yasaklı: Hiçbiri
```
```
Lütfen dikkat edin ki istisna sınıflarının Ortodoks Kurallı Forma uyması gerekmez.
Ancak diğer her sınıf ona uymalıdır.
```
Ofisler, koridorlar, formlar ve bekleme kuyrukları olan yapay bir kabusu tasarlayalım.
Eğlenceli geliyor? Hayır? Çok yazık.

```
Önce, bu geniş bürokrasya makinesindeki en küçük vidadan başlayalım: Bürokrat.
```
```
Bir Büroktrat'ın olması gerekir:
```
- Sabit bir ad.
- **1** (mümkün olan en yüksek derece) ile **150** (mümkün olan en düşük derece) arasında değişen bir derece.

Geçersiz bir derece ile Bürokrat'ı örneklemek için herhangi bir girişim bir istisna atmalıdır:
ya Bureaucrat::GradeTooHighException ya da Bureaucrat::GradeTooLowException.


C++ - Modül 05 Tekrar ve İstisnalar

Her iki öznitelik için de getter'lar sağlayacaksınız: getName() ve getGrade(). Ayrıca,
bürokratın derecesini artırmak veya azaltmak için iki üye işlevi uygulamalısınız.
Derece aralığın dışında çıkarsa, her iki işlev de yapıcı ile aynı istisnaları atmalıdır.

```
Unutmayın, derece 1 en yüksek ve 150 en düşük olduğundan,
derece 3'ü artırmak bürokrat için derece 2 ile sonuçlanmalıdır.
```
```
Atılan istisnalar try ve catch bloklarını kullanarak yakalanabilir olmalıdır:
```
```
try
{
/* bürokratlarla bazı şeyler yapın */
}
catch (std::exception & e)
{
/* istisnayı yönetin */
}
```
Ekleme («) operatörünün bir aşırı yüklemesini uygulamalısınız şu biçimde çıkış yazdırmak için
(açılı köşeli parantezler olmadan):

```
<name>, bureaucrat grade <grade>.
```
```
Her zamanki gibi, her şeyin beklendiği gibi çalıştığını kanıtlamak için bazı testler gönderin.
```

# Bölüm V

# Alıştırma 01: Hepsi, işte başa dönüş!

```
Alıştırma: 01
```
```
Hepsi, işte başa dönüş!
Dizin: ex 01 /
Gönderilecek Dosyalar: Önceki alıştırmadan gelen dosyalar + Form.{h, hpp}, Form.cpp
Yasaklı: Hiçbiri
```
Artık bürokratlarınız var, onlara yapacak bir şey verelim. Formları yığınla doldurmasından daha iyi bir aktivite ne olabilir?

```
Bir Form sınıfı oluşturalım. Bunun özellikleri:
```
- Sabit bir ad.
- İmzalanıp imzalanmadığını gösteren bir boole değeri (yapıda, imzalanmamıştır).
- İmzalamak için gerekli olan derece.
- Onu yürütmek için gerekli olan derece.

```
Tüm bu öznitelikler özel (private), korunmamış (protected) değildir.
```
Form'un **dereceleri** Bürokrat'ın dereceleri ile aynı kuralları izler. Bu nedenle,
aşağıdaki istisnalar bir formun derecesi sınırların dışındaysa atılacaktır:
Form::GradeTooHighException ve Form::GradeTooLowException.

Önceden olduğu gibi, tüm öznitelikler için getter'lar yazın ve ekleme («) operatörünü
aşırı yükleyin formu'un tüm bilgisini yazdırmak için.


C++ - Modül 05 Tekrar ve İstisnalar

Ayrıca, Form'a bir Bürokrat alan beSigned() üye işlevi ekleyin. Bürokratın derecesi yeterince yüksekse
(gerekli olandan büyük veya eşit) formun durumunu imzalanmış olarak değiştirin. Unutmayın, derece 1 derece 2'den daha yüksektir.
Derece çok düşükse, Form::GradeTooLowException atın.

Daha sonra, Bürokrat sınıfında signForm() üye işlevi ekleyin. Bu işlev, Form::beSigned()'ı çağırmalıdır
formu imzalamaya çalışmak için. Form başarıyla imzalanırsa, şu şekilde bir şey yazdıracaktır:
<bureaucrat> signed <form>

```
Aksi takdirde, şu şekilde bir şey yazdıracaktır:
```
```
<bureaucrat> couldn't sign <form> because <reason>.
```
```
Her şeyin beklendiği gibi çalıştığını sağlamak için bazı testler uygulayın ve gönderin.
```

# Bölüm VI

# Alıştırma 02: Hayır, form 28C değil

# 28B'ye ihtiyacın var...

```
Alıştırma: 02
```
```
Hayır, form 28C değil 28B'ye ihtiyacın var...
Dizin: ex 02 /
Gönderilecek Dosyalar: Makefile, main.cpp, Bureaucrat.[{h, hpp},cpp], +
AForm.[{h, hpp},cpp], ShrubberyCreationForm.[{h, hpp},cpp], +
RobotomyRequestForm.[{h, hpp},cpp], PresidentialPardonForm.[{h, hpp},cpp]
Yasaklı: Hiçbiri
```
Artık temel formlara sahipsiniz, gerçekte işe yarayan birkaç tane daha oluşturmak zamanı geldi.

Her durumda, temel Form sınıfı soyut bir sınıf olmalı ve bu nedenle AForm olarak yeniden adlandırılmalıdır.
Formun özniteliklerinin özel kalması gerekeceğini ve bunların temel sınıfa ait olduğunu hatırlayın.

```
Aşağıdaki somut sınıfları ekleyin:
```
- **ShrubberyCreationForm** : Gerekli dereceler: imzala 145, yürüt 137
    Çalışma dizininde <target>_shrubbery adında bir dosya oluşturur ve
    içine ASCII ağaçları yazar.
- **RobotomyRequestForm** : Gerekli dereceler: imzala 72, yürüt 45
    Matkap gürültüleri çıkarır, ardından <target>'ın başarıyla robotomlaştırıldığını
    %50 oranında bildirir. Aksi takdirde, robotomun başarısız olduğunu bildirir.
- **PresidentialPardonForm** : Gerekli dereceler: imzala 25, yürüt 5
    <target>'ın Zaphod Beeblebrox tarafından affedildiğini bildirir.

Hepsi yapıcıda yalnızca bir parametre alırlar: formun hedefi. Örneğin,
evde çalı oluşturmak istiyorsanız "home".


C++ - Modül 05 Tekrar ve İstisnalar

Şimdi, temel forma execute(Bureaucrat const & executor) const üye işlevini ekleyin
ve somut sınıflarda formun eylemini yürütmek için bir işlev uygulayın. Formun imzalanıp
imzalanmadığını ve formu yürütmek için çalışan bürokratın derecesinin yeterince yüksek olup olmadığını kontrol etmelisiniz.
Aksi takdirde, uygun bir istisna atın.

Gereksinimleri her somut sınıfta mı yoksa temel sınıfta (ve daha sonra formu yürütmek için başka bir işlev çağırarak)
kontrol edip etmediğiniz size kalmıştır. Ancak, bir yol diğerinden daha zarif.

Son olarak, Bürokrat sınıfına executeForm(AForm const & form) const üye işlevini ekleyin. Formu yürütmeyi denemelidir.
Başarılı olursa, şu şekilde bir şey yazdıracaktır:

```
<bureaucrat> executed <form>
```
```
Aksi takdirde, açık bir hata mesajı yazdıracaktır.
```
```
Her şeyin beklendiği gibi çalıştığını sağlamak için bazı testler uygulayın ve gönderin.
```

# Bölüm VII

# Alıştırma 03: En azından bu kahve

# yapmaktan daha iyidir

```
Alıştırma: 03
```
```
En azından bu kahve yapmaktan daha iyidir
Dizin: ex 03 /
Gönderilecek Dosyalar: Önceki alıştırmalardan gelen dosyalar + Intern.{h, hpp}, Intern.cpp
Yasaklı: Hiçbiri
```
Gün boyu formları doldurs çünkü bürokratlar için çok acı olacağından, praktisyenler bu sıkıcı görevi üstlenmek için vardır.
Bu alıştırmada **Intern** sınıfını uygulamalısınız. Stajyer'in adı, derecesi ve benzersiz özellikleri yoktur.
Bürokratların önem verdiği tek şey, işilerini yapıp yapmadığıdır.

Ancak, stajyer'in bir temel yeteneği vardır: makeForm() işlevi. Bu işlev, iki dize parametresi alır:
ilki bir formun adını temsil eder ve ikincisi formun hedefini temsil eder. Bir **AForm** nesnesine bir işaretçi döndürür
(parametre olarak geçirilen form adına karşılık gelen) ve hedefi ikinci parametreye başlatır.

```
Şu şekilde bir şey yazdırmalı:
```
```
Intern creates <form>
```
```
Eğer sağlanan form adı yoksa, açık bir hata mesajı yazdıracaktır.
```

C++ - Modül 05 Tekrar ve İstisnalar

Aşırı if/elseif/else yapısı kullanma gibi pis ve karmaşık çözümlerden kaçınmalısınız.
Bu tür bir yaklaşım değerlendirme işlemi sırasında kabul edilmeyecektir. Artık Piscine (havuz) içinde değilsiniz.
Her zamanki gibi, her şeyin beklendiği gibi çalıştığını sağlamak için test etmelisiniz.

Örneğin, aşağıdaki kod "Bender" hedefli bir **RobotomyRequestForm** oluşturur:

```
{
Intern someRandomIntern;
AForm* rrf;
rrf = someRandomIntern.makeForm("robotomy request", "Bender");
}
```

# Bölüm VIII

# Gönderme ve Eş Değerlendirme

Projenizi her zamanki gibi Git deponuza gönderin. Yalnızca deponuzun içindeki çalışma,
savunma sırasında değerlendirilecektir. Klasör ve dosya adlarınızın doğru olduğundan emin olmak için
iki kez kontrol edin.

Değerlendirme sırasında, projeye kısa bir **değişiklik** talep edilebilir. Bu,
küçük bir davranış değişikliği, yazılacak veya yeniden yazılacak birkaç kod satırı veya
kolayca eklenebilecek bir özellik içerebilir.

Bu adım her proje için **geçerli olmayabilir**, ancak değerlendirme yönergelerinde belirtilmişse
bunun için hazırlanmalısınız.

Bu adım, projenin belirli bir bölümü hakkında gerçek anlaşınızı doğrulamak için tasarlanmıştır.
Değişiklik, seçtiğiniz herhangi bir geliştirme ortamında (örneğin, olağan kurulumunuz) gerçekleştirilebilir
ve birkaç dakika içinde mümkün olmalıdır — aksi takdirde, değerlendirmenin bir parçası olarak tanımlanmış belirli bir zaman aralığı vardır.
Örneğin, bir işleve küçük bir güncelleme yapmanız, bir ekranı değiştirmeniz veya
yeni bilgileri depolamak için bir veri yapısını ayarlamanız istenebilir.

Ayrıntılar (**kapsam, hedef, vb.**) **değerlendirme yönergelerinde** belirtilecek ve aynı proje
için bir değerlendirmeden diğerine değişebilir.
