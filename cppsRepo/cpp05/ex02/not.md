# ex02 — Akış Notu (main'den sona kadar)

## Amaç

`Form`, abstract `AForm`'a dönüştürüldü. 3 concrete form eklendi
(`ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm`).
Her formun imzalanması **ve** execute edilebilmesi için ayrı grade eşiği var.
`Bureaucrat::executeForm()` bu execute girişimini yönetiyor.

## main.cpp akışı

1. `srand(time(NULL))` — Robotomy'nin %50 şansı için rastgelelik tohumu.
2. İki bürokrat: `lowGrade` (150, en düşük yetki) ve `highGrade` (1, en yüksek yetki).
3. **ShrubberyCreationForm("home")** oluşturulur (constructor, sign=145/exec=137).
   - `lowGrade.signForm(shrub)` → grade 150 > 145, yetersiz → imzalanamaz, hata basılır.
   - `highGrade.signForm(shrub)` → grade 1 ≤ 145, imzalanır.
   - `lowGrade.executeForm(shrub)` → imzalı ama execute grade'i (137) için 150 yetersiz → hata.
   - `highGrade.executeForm(shrub)` → başarılı, `executeAction()` çalışır, `home_shrubbery` dosyası oluşur.
4. **RobotomyRequestForm("Bender")**: `highGrade` imzalar ve execute eder → drilling noise + %50 başarı/başarısızlık mesajı.
5. **PresidentialPardonForm("Zaphod")**: `highGrade` imzalar ve execute eder → sabit pardon mesajı.
6. **İmzasız form execute denemesi**: yeni bir `PresidentialPardonForm("Nobody")` hiç imzalanmadan direkt execute edilmeye çalışılır → `FormNotSignedException` yakalanır.
7. Son try/catch: `ShrubberyCreationForm badForm;` default constructor'ı çağrılır (burada hata bekleniyorsa constructor içinde bir grade validasyonu olmalı — yoksa bu blok sadece OCF default ctor'unu test eder).

## Kod içindeki mekanizma (execute zinciri)

```
Bureaucrat::executeForm(form)
  -> form.execute(*this)              // AForm::execute (public, non-virtual)
       -> imzalı mı? değilse throw FormNotSignedException
       -> executor grade yeterli mi? değilse throw GradeTooLowException
       -> executeAction()             // protected pure virtual, concrete class'ta override
```

Bu **NVI (Non-Virtual Interface)** deseni: ortak kontrol tek yerde (`AForm::execute`),
her concrete class sadece kendi `executeAction()`'ını yazıyor — kod tekrarı yok.

## Neden çalışıyor / neyi kanıtlıyor

- Yetersiz grade'le imza/execute reddediliyor → grade kontrolü doğru.
- İmzasız form execute edilemiyor → sign kontrolü doğru.
- Shrubbery dosyası gerçekten diske yazılıyor → `executeAction()` polymorphic dispatch ile doğru override'a gidiyor.
- Robotomy'nin çıktısı çalıştırma çalıştırma değişiyor → `rand()` doğru kullanılmış.
- Program sonunda tüm nesneler scope'tan çıkarken destructor zinciri (AForm → concrete class) sorunsuz tetikleniyor, `-Wall -Wextra -Werror` ile temiz derleniyor.
