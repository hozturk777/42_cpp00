# Intern.hpp / Intern.cpp 

Bu doküman ex03'teki `Intern` sınıfını; derleyici (compiler), bellek (RAM),
ve çalışma zamanı (runtime) düzeyinde ne yaptığını açıklar. Önceki
exercise'lardan (AForm, concrete form'lar) farklı olarak burada asıl konu
**fonksiyon pointer'ları**, **static member fonksiyonlar** ve **factory
pattern**'dir.

---

## Neden bu sınıf var (subject bağlamı)

`Intern::makeForm(formName, target)` bir string alıp, o isme karşılık gelen
`AForm` alt sınıfından bir nesne üretip `AForm*` olarak döndürmeli. Subject
açıkça yasaklıyor: **uzun if/elseif/else zincirleri kullanılamaz**. Aynı
zamanda `std::map` gibi bir STL container da kullanılamaz (Module 08'e kadar
yasak). Çözüm: elle yazılmış, **isim → fabrika fonksiyonu** eşlemesi tutan
sabit boyutlu bir `struct` dizisi.

---

## Intern.hpp

```cpp
class AForm;
```

- **Forward declaration**. `Intern.hpp`, `AForm`'un tam tanımına (üyelerine,
  boyutuna) ihtiyaç duymaz — sadece `AForm*` (pointer) kullanıyor, ve bir
  pointer'ın boyutu (8 byte, 64-bit sistemde) tipin içeriğinden bağımsız
  sabittir. Bu yüzden derleyici tam tanımı görmeden de `AForm*` içeren bir
  imza derleyebilir. **Neden önemli:** Eğer burada `#include "AForm.hpp"`
  yapsaydık, `Intern.hpp`'yi include eden her dosya gereksiz yere
  `AForm.hpp`'nin tüm içeriğini de (transitively) almış olurdu — derleme
  süresini uzatır ve gereksiz bağımlılık yaratır.

```cpp
class Intern
{
	public:
		Intern();
		Intern(const Intern& copy);
		Intern& operator=(const Intern& copy);
		~Intern();

		AForm*	makeForm(const std::string& formName, const std::string& target) const;

	private:
		static AForm*	createShrubbery(const std::string& target);
		static AForm*	createRobotomy(const std::string& target);
		static AForm*	createPardon(const std::string& target);
};
```

- **Orthodox Canonical Form** (default ctor, copy ctor, copy assignment,
  destructor) burada da uygulanıyor, ama `Intern`'in hiç attribute'u yok —
  subject'in dediği gibi "no name, no grade, no unique characteristics".
  Bu yüzden `.cpp` içinde bu dört fonksiyon neredeyse boş gövdelidir; RAM'de
  bir `Intern` nesnesi **0 byte'lık boş bir sınıf** olur (C++ kuralı gereği
  gerçekte minimum 1 byte tutulur — iki farklı nesnenin aynı adrese sahip
  olmaması için — ama içinde hiçbir veri yoktur).

### `static AForm* createShrubbery(const std::string& target);` — `static` member fonksiyon

- Normal (non-static) bir üye fonksiyon çağrıldığında, derleyici gizlice bir
  `this` pointer'ı iletir (`obj.method()` aslında `method(&obj)` gibi
  çalışır — `this`, fonksiyonun gizli ilk parametresidir). **`static`** bir
  üye fonksiyonda bu `this` parametresi **yoktur**. Bu, fonksiyonun imzasını
  sıradan bir global fonksiyonla (serbest fonksiyonla) **aynı** yapar —
  farkı sadece `Intern::` scope'u içinde yaşaması ve `Intern`'in `private`
  bölümünde tanımlıysa sınıf dışından çağrılamamasıdır.
- **Neden static olmak zorunda burada:** Birazdan göreceğimiz fonksiyon
  pointer'ı dizisinde (`FormEntry::create`), pointer'ın tipi
  `AForm* (*)(const std::string&)` — yani "bir `const std::string&` alıp
  `AForm*` dönen fonksiyon" tipidir. Normal (non-static) bir üye fonksiyonun
  gerçek imzası gizli `this` parametresi yüzünden bu tipe **uymaz**
  (üye fonksiyon pointer'ları `AForm* (Intern::*)(const std::string&)` gibi
  tamamen farklı, daha karmaşık bir tiptir — çağırmak için bir `Intern`
  nesnesi gerektirir). `static` yaparak bu üç fonksiyonu "sıradan fonksiyon
  pointer'ı" tipine uygun hale getiriyoruz.
- `private` olmaları: Bunlar sadece `makeForm()`'un iç uygulama detayı,
  sınıf dışından çağrılmasına gerek yok — **encapsulation** (kapsülleme).

---

## Intern.cpp

### Orthodox Canonical Form gövdeleri

```cpp
Intern::Intern() {
}

Intern::Intern(const Intern& copy) {
	(void)copy;
}

Intern& Intern::operator=(const Intern& copy) {
	(void)copy;
	return (*this);
}

Intern::~Intern() {
}
```

- Hiçbir attribute olmadığı için gövdeler boş. `(void)copy;` — derleyicinin
  "kullanılmayan parametre" (`-Wunused-parameter`, `-Wextra` ile açılır)
  uyarısını susturmak için klasik bir C++ idiyomu: `copy` ifadesini
  **kullanmış gibi** gösterir ama hiçbir makine kodu üretmez (derleyici bu
  ifadeyi tamamen eler — "no-op").
- `-Werror` bayrağı yüzünden buradaki her uyarı derlemeyi durdurur; bu
  yüzden `(void)copy;` burada kozmetik değil, **zorunlu**.

### Fabrika (factory) fonksiyonları

```cpp
AForm*	Intern::createShrubbery(const std::string& target) {
	return (new ShrubberyCreationForm(target));
}
```

- `new ShrubberyCreationForm(target)`: **Heap** üzerinde bir
  `ShrubberyCreationForm` nesnesi için yer ayrılır (constructor çağrılır),
  ve dönen adres bir `ShrubberyCreationForm*` pointer'ıdır.
- Bu pointer, fonksiyonun dönüş tipi olan `AForm*`'a **implicit olarak**
  dönüştürülür (upcast) — çünkü `ShrubberyCreationForm`, `public AForm`'dan
  türediği için "is-a AForm" ilişkisi vardır. Bu dönüşüm bellekte hiçbir
  şeyi değiştirmez (adres aynı kalır); sadece derleyicinin pointer'ı hangi
  tipin "merceğinden" gördüğünü değiştirir (compile-time bir kavramdır).
- **Bellek sızıntısı riski burada YOK ama dikkat edilmesi gereken yer:**
  `new` ile ayrılan bu bellek, bir yerde `delete` edilmezse **heap leak**
  olur. Bu fonksiyon sorumluluğu çağırana (`makeForm`, ve zincirleme olarak
  `main`) devrediyor — **ownership transfer**. `main.cpp`'de her `forms[i]`
  için `delete forms[i];` çağrısı bu yüzden zorunlu.

### `makeForm` — asıl mekanizma

```cpp
AForm*	Intern::makeForm(const std::string& formName, const std::string& target) const {
	struct FormEntry {
		const char*		name;
		AForm*			(*create)(const std::string&);
	};
```

- `struct FormEntry`, `makeForm` fonksiyonunun **içinde** tanımlanmış yerel
  (local) bir tip — sadece bu fonksiyon içinde görünür, dışarıdan
  erişilemez. Bu, ihtiyaç sadece burada olduğu için kapsamı (scope)
  mümkün olduğunca dar tutma pratiğidir.
- `AForm* (*create)(const std::string&);` — bu bir **fonksiyon pointer'ı
  değişkeni tanımıdır**. Okuma şekli (C'nin klasik "spiral kural"ı ile):
  `create` isminde bir değişken, bu değişken bir **pointer**'dır (`*create`),
  bu pointer'ın işaret ettiği şey bir **fonksiyon**dur
  (`(const std::string&)` parametre listesi), ve o fonksiyon `AForm*` döner.
  RAM'de bu alan sadece **8 byte'lık bir adres** tutar (kod segmentindeki
  bir fonksiyonun başlangıç adresi — `.text` section'ı).

```cpp
	const FormEntry	forms[] = {
		{"shrubbery creation", &Intern::createShrubbery},
		{"robotomy request", &Intern::createRobotomy},
		{"presidential pardon", &Intern::createPardon}
	};
	const size_t		formsCount = sizeof(forms) / sizeof(forms[0]);
```

- `forms[]` — boyutu derleyici tarafından **initializer listesinden**
  otomatik hesaplanan sabit boyutlu bir dizi (burada 3 eleman). Bu dizi
  `makeForm` her çağrıldığında **stack üzerinde yeniden oluşturulur**
  (yani her çağrıda 3 elemanlık küçük bir kopyalama maliyeti vardır — çok
  ihmal edilebilir, ama sistemsel not olarak: bu dizi `static` yapılsaydı
  bir kez oluşturulup program ömrü boyunca saklanırdı; burada `const`
  olması sadece "bu diziye yazma yapılamaz" demektir, "bir kez oluşturulur"
  demek değildir).
- `&Intern::createShrubbery` — `static` bir üye fonksiyonun **adresini**
  alma sözdizimi. `static` olduğu için (normal üye fonksiyonlardan farklı
  olarak) bu adres sıradan bir `AForm* (*)(const std::string&)` pointer
  tipine **doğrudan** atanabilir — `Intern::` scope belirtici sadece ismin
  nerede arandığını gösterir, tip üzerinde bir etkisi yoktur.
- `sizeof(forms) / sizeof(forms[0])` — dizinin toplam byte boyutunu, tek bir
  elemanın byte boyutuna bölerek eleman sayısını (3) elde eden klasik C/C++
  idiyomu. Bu, **derleme zamanında** (compile-time) sabit bir değere
  (constant expression) indirgenir; runtime'da gerçek bir bölme işlemi
  CPU'da çalışmaz (derleyici optimizasyonuyla sabitlenir).

```cpp
	for (size_t i = 0; i < formsCount; i++) {
		if (formName == forms[i].name) {
			AForm* form = forms[i].create(target);
			std::cout << "Intern creates " << *form << std::endl;
			return (form);
		}
	}
	std::cout << "Intern couldn't find a form named \"" << formName << "\"" << std::endl;
	return (NULL);
}
```

- `formName == forms[i].name` — burada `formName` bir `std::string`,
  `forms[i].name` ise bir `const char*`. `std::string::operator==`'un
  `const char*` alan bir overload'u olduğu için, `forms[i].name`
  otomatik olarak geçici bir `std::string`'e dönüştürülüp karşılaştırılır
  (implicit conversion). Bu karşılaştırma **içerik bazlıdır** (karakter
  karakter), pointer adresi karşılaştırması değildir.
- `forms[i].create(target)` — burada `.create` bir fonksiyon pointer'ı
  değişkenidir; `create(target)` yazmak, C++'ta otomatik olarak
  `(*create)(target)`'a eşdeğerdir (fonksiyon pointer'ları için
  dereference etmek opsiyoneldir, dil bunu kolaylık olsun diye izin verir).
  CPU seviyesinde bu bir **indirect call**'dır: önce `create` değişkeninin
  RAM'deki değeri (bir adres) okunur, sonra o adrese `call` yapılır —
  normal `createShrubbery(target)` çağrısındaki gibi adres derleme
  zamanında sabit (direct call) değildir.
- Bu döngü + struct-dizisi yaklaşımı, subject'in yasakladığı
  "if/elseif/else zinciri"nin **yerine geçer**: yeni bir form türü eklemek
  istediğinizde tek yapmanız gereken `forms[]` dizisine bir satır eklemek,
  hiçbir dallanma (branch) mantığı değişmez. Bu aynı zamanda **Open/Closed
  Principle**'a bir örnektir (yeni davranış eklemek için var olan kodu
  değiştirmeye gerek yok).
- Form bulunamazsa `NULL` döner. `main.cpp` bu durumda `if (forms[i])`
  kontrolüyle `NULL` pointer'ı `delete`'lememeye/kullanmamaya dikkat eder
  (`delete NULL` C++'ta güvenlidir/no-op'tur ama `*NULL` gibi bir
  dereference **undefined behavior**'dır, o yüzden kontrol şart).

---

## Polymorphism ve bellek yönetimi (main.cpp bağlamı)

```cpp
AForm* forms[4];
forms[0] = someRandomIntern.makeForm("shrubbery creation", "home");
...
delete forms[i];
```

- `forms[i]`'nin **statik tipi** `AForm*`'tur ama **dinamik (gerçek) tipi**
  `ShrubberyCreationForm`, `RobotomyRequestForm` veya
  `PresidentialPardonForm` olabilir — hangisi olduğu yalnızca runtime'da
  bellekteki vptr'ye bakılarak bilinir.
- `delete forms[i];` çağrıldığında, eğer `AForm::~AForm()` **virtual**
  olmasaydı, derleyici sadece `AForm`'un destructor'ını çağırırdı — türetilen
  sınıfın (`ShrubberyCreationForm` gibi) kendi üyelerinin (örn. `_target`
  string'inin heap belleği) temizlenmesi **atlanırdı** → bu bir bellek
  sızıntısıdır (partial destruction). `~AForm()`'un `virtual` işaretli
  olması (`AForm.hpp`), `delete`'in vtable üzerinden **doğru** (en türetilmiş)
  destructor'ı bulup çağırmasını garanti eder — bu yüzden ex02'de
  `~AForm()`'u virtual yapmak sadece "iyi pratik" değil, ex03'te
  `Intern`'in ürettiği nesnelerin `AForm*` üzerinden güvenle silinebilmesi
  için **zorunluluktu**.

---

## Özet Tablo

| Kavram | Ne işe yarıyor | Sistemsel karşılığı |
|---|---|---|
| `class AForm;` (forward decl) | Gereksiz include'u önler | Sadece pointer boyutu (8 byte) bilinmesi yeterli |
| `static` üye fonksiyon | Fonksiyon pointer tipine uygunluk | Gizli `this` parametresi yok, sıradan fonksiyon gibi çağrılır |
| `AForm* (*create)(const std::string&)` | if/else zincirini önleyen dispatch tablosu | RAM'de sadece bir kod-adresi (8 byte) tutan değişken |
| `struct FormEntry` (local) | İsim↔fabrika eşleşmesi | Stack üzerinde küçük sabit boyutlu dizi |
| `new Concrete(target)` → `AForm*` | Heap'te nesne oluşturup upcast | Ownership `main`'e devredilir, `delete` sorumluluğu çağıranındır |
| `virtual ~AForm()` | Doğru destructor zincirini garanti eder | `delete` vtable üzerinden en türetilmiş destructor'ı bulur |
| `NULL` dönüş (form bulunamazsa) | Hata durumunu işaretler | `main`'de dereference öncesi kontrol zorunlu |
