# C++ Exception Mekanizması — Öğretim Notları

## 1. `virtual` — Late Binding / Dynamic Dispatch

- **Early binding (static dispatch):** `virtual` yokken, hangi fonksiyonun çalışacağı **compile-time**'da sabitlenir.
- **Late binding (dynamic dispatch):** `virtual` varken, hangi fonksiyonun çalışacağı nesnenin **gerçek (runtime) tipine** göre belirlenir.

### Vtable / Vptr Mekanizması
- **Vtable (Virtual Table):** Sınıfa özel, fonksiyon pointer'larından oluşan statik dizi.
  - GCC/Clang'da genelde **`.data.rel.ro`** segmentinde durur (relocation gerektiği için `.rodata` değil — ASLR/PIE nedeniyle load-time'da güncellenir, sonra read-only'e çevrilir).
- **Vptr (Virtual Pointer):** Her nesnenin içinde gizli bir pointer, o nesnenin vtable'ını gösterir (tek inheritance'ta genelde offset 0).

### Çağrı Anı (Assembly Seviyesi)
```asm
mov rax, [rdi]        ; vptr'ı yükle
mov rax, [rax + 16]   ; vtable'dan fonksiyon adresini al
call rax               ; indirect call
```

| | Direct Call | Indirect Call (Virtual) |
|---|---|---|
| Hedef adres | Compile-time sabit | Runtime, register üzerinden |
| Bellek erişimi | 0 ekstra | 2 ekstra (vptr + vtable slot) |
| Branch prediction | Gerekmez | BTB (Branch Target Buffer) tahmini gerekir |
| Terim | **Static dispatch** | **Dynamic dispatch** |

**Neden kullanılır?** Base class pointer/reference (`std::exception&`) üzerinden çağrı yapılsa bile, gerçek türetilmiş sınıfın implementasyonunun çalışmasını garanti eder → **polimorfizm**.

---

## 2. `what()` İmzasının Anatomisi

```cpp
virtual const char* what() const throw();
```

| Parça | Terim | Amaç |
|---|---|---|
| `virtual` | Dynamic dispatch | Runtime'da doğru override'ın çalışmasını sağlar |
| `const char*` | — | `std::string`'e bağımlı olmamak için (allocation riski taşımaz) |
| `const` (sonda) | Const member function | `const std::exception&` ile uyumlu olması için zorunlu |
| `throw()` | No-throw guarantee | `what()`'ın exception fırlatmayacağı garantisi |

**Signature uyumu kritik:** Override eden fonksiyon, base class'takiyle **birebir aynı imzayı** taşımalı. Aksi halde bu bir override değil, **name hiding** olur ve vtable'a hiç girmez — sessiz bug.

---

## 3. `throw()` Neden Var — "Çift Exception" Riski

`what()`'ın kendi içinde throw yoktur (base class ve türetilmiş sınıflarda genelde sadece `return`). Risk, **`what()`'ın çağrıldığı bağlamın** zaten kırılgan olmasından gelir:

```
throw "Hata 1" → stack unwinding başlar
   → unwinding sırasında bir destructor içinde e.what() çağrılıyor
      → what() içeride bir şey daha fırlatırsa ("Hata 2")
         → AYNI ANDA İKİ AKTİF EXCEPTION
            → std::terminate() ANINDA çağrılır
```

`throw()` / `noexcept`, `what()`'ın bu hassas anlarda bile ikinci bir exception eklemeyeceği garantisidir.

---

## 4. `throw` — Ne, Ne Zaman, Neden

- **Ne yapar:** Normal akışı keser, exception nesnesini fırlatır. Fonksiyonun kalan kodu **hiç çalışmaz**.
- **Ne zaman:** Fonksiyon normal şekilde devam edemeyeceği bir kural ihlali olduğunda (örn. grade sınır dışı).
- **Neden `return` değil:** Hata, oluştuğu yerden çok uzakta (üst seviyede) ele alınmak istendiğinde — ara fonksiyonların hata kodunu manuel taşımasına gerek kalmaz.

```cpp
void Bureaucrat::incGrade() {
    if (this->_grade <= 1)
        throw Bureaucrat::GradeTooHighException();  // devam edilemez
    this->_grade--;                                   // normal durum
}
```

---

## 5. `catch` Nasıl Çalışır — Stack Unwinding

**Yanlış model:** "İlerleyip görmezden gelerek catch arama."
**Doğru model:** Her terk edilen fonksiyon seviyesinde **kalan kod tamamen çalışmaz**, call stack **yukarı doğru boşaltılır (unwind)**.

```cpp
void level3() { throw std::runtime_error("Hata!"); /* sonrası çalışmaz */ }
void level2() { level3(); /* level3 sonrası hiç çalışmaz */ }
void level1() {
    try { level2(); }
    catch (std::exception& e) { /* burada yakalanır */ }
}
```

### Adım Adım
1. `throw` → exception nesnesi özel bir runtime alanına kopyalanır (**`__cxa_allocate_exception`**, heap benzeri — **`.rodata` değil**, çünkü runtime'da oluşan bir nesne).
2. Şu anki frame terk edilir → local nesnelerin destructor'ları çağrılır (**RAII garantisi**) → frame stack'ten pop edilir.
3. Bir üst seviyeye çıkılır; orada `try/catch` yoksa aynı işlem tekrarlanır.
4. Uygun `try` bulunduğunda, exception'ın tipi `catch` bloklarıyla karşılaştırılır (**RTTI ile type matching**).
5. Uyum varsa `catch` çalışır, kontrol normal akışa döner.

**Not — string literal ile exception nesnesi farkı:**
| Ne | Nerede |
|---|---|
| `"Grade is too high"` (string literal) | `.rodata` — compile-time'da zaten var |
| Fırlatılan exception nesnesinin kendisi | Runtime'ın özel alanı — `throw` anında oluşur |

---

## 6. Catch Yoksa Ne Olur?

```
Unhandled exception → std::terminate() → std::abort() → SIGABRT → CRASH
```

- Stack unwinding'in yapılıp yapılmayacağı bu durumda **unspecified** (derleyiciye bağlı) — destructor çağrımı garanti değil.
- GCC'nin `__verbose_terminate_handler`'ı, çökmeden önce `what()`'ı otomatik çağırıp ekrana basar.

**42 projelerinde abort almamak için:** Her riskli çağrı (constructor, `incGrade`, `decGrade`, `beSigned` vb.) **çağrıldığı yerde** (`main.cpp`) `try/catch` ile sarılmalı. Sınıfın kendi fonksiyonları asla kendi `throw`'unu kendi `catch`'lemez — "throw eden yakalamaz, çağıran yakalar" prensibi.

---

## 7. Tasarım Deseni — Nested Exception Idiom

```cpp
class Bureaucrat {
    class GradeTooHighException : public std::exception {
        public: virtual const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
        public: virtual const char* what() const throw();
    };
};
```

- Exception sınıfı, ait olduğu sınıfın **içine** gömülür → scope izolasyonu + semantik bağ.
- 42 kuralı: Bu nested exception sınıfları **Orthodox Canonical Form'dan muaf** (diğer tüm sınıflar zorunlu).

---

## Terim Sözlüğü (Öğrencilere Aktarım İçin)

| Terim | Türkçe Karşılık |
|---|---|
| Early binding / Static dispatch | Derleme zamanı fonksiyon bağlama |
| Late binding / Dynamic dispatch | Çalışma zamanı fonksiyon bağlama |
| Vtable | Sanal fonksiyon tablosu |
| Vptr | Sanal fonksiyon pointer'ı |
| Stack unwinding | Yığın geri sarma |
| Exception propagation | İstisnanın yayılması |
| RTTI (Run-Time Type Information) | Çalışma zamanı tip bilgisi |
| No-throw guarantee | İstisna fırlatmama garantisi |
| Nested exception idiom | İç içe istisna sınıfı deseni |
| Unhandled exception | Yakalanmamış istisna |