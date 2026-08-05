# 42 C++ Modülleri — Claude Kuralları

## Rol: Manuel mod — kod yazılabilir ama dosyaya dokunmadan önce izin şart

Bu bir 42 okulu projesi. Amaç öğrenmek, ödevi bitirmek değil.

- Kod yazmak serbest (açıklama isterse kod göster, örnek ver, tam implementasyon da
  yazabilirsin).
- **Ama dosyayı (Edit/Write) değiştirmeden önce mutlaka sor ve onay al.** Kullanıcı
  "evet yaz/uygula" demeden Edit/Write çağırma. Sohbette kod gösterip "bunu uygulayayım
  mı?" diye sormak yeterli.
- Kullanıcı bir şeyi yanlış yapıyorsa neden yanlış olduğunu açıkla, doğru yöne it.
- Kısa ve öz cevap ver. Uzun ders anlatma, madde madde gereksiz genişletme yok.

## 42 C++ Modül Kuralları (Module 00–09 boyunca geçerli)

- **Standart:** C++98. `-std=c++98` ile derlenmeli; `-std=c++11`+ ile de derlenebilmeli
  ama 98 dışı hiçbir özellik (auto, nullptr, range-for, lambda, vs.) kullanılmamalı.
- **Derleme bayrakları:** `-Wall -Wextra -Werror`, hatasız derlenmeli.
- **Yasak (Module 00–07):** STL container/algorithm yok (`<vector>`, `<map>`, `<list>`,
  `<algorithm>` vb.) — **Module 08–09'a kadar** yasak.
- **Yasak (her zaman):** `using namespace ...`, `friend`, `*printf()`, `*alloc()`, `free()`.
  Boost ve C++11+ kütüphaneleri yasak.
- **Orthodox Canonical Form:** Module 02'den itibaren her sınıf (exception sınıfları hariç)
  default constructor, copy constructor, copy assignment operator, destructor içermeli.
- **Header kuralı:** Fonksiyon implementasyonu header'da olamaz (template fonksiyonlar
  hariç) — olursa o exercise 0 alır. Include guard zorunlu.
- **Attribute/erişim kuralları exercise'a göre değişir** (örn. Form'da attribute'lar
  private olmalı, protected değil) — her exercise'ın metnini dikkatlice oku, örtük
  gereksinimler var.
- **İsimlendirme:** Sınıflar UpperCamelCase, dosya adı sınıf adıyla birebir aynı
  (ClassName.hpp/.cpp).
- **Çıktı:** Her mesaj `\n` ile bitmeli, stdout'a yazılmalı.
- Norm/norminette yok ama okunabilir kod bekleniyor (peer evaluation var).

## Bu repo bağlamı

- cpp05 üzerinde çalışılıyor, sırayla ex00 → ex03.
- Şu an konu: **ex02** — `Form` → `AForm` (abstract) refactor'ü ve 3 concrete form sınıfı
  (`ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm`).
- `Bureaucrat::executeForm()` eklenecek.

## Token ekonomisi

- Gereksiz dosya okuma/arama yapma; kullanıcı hangi dosyadan bahsediyorsa ona odaklan.
- Uzun kod bloğu üretme (zaten yazmıyorsun); kısa, hedefe yönelik açıklamalar tercih et.
