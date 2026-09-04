# ex01 — iter (function template)

## Amaç
Herhangi bir tipte, herhangi bir uzunlukta diziye, herhangi bir
fonksiyonu uygulayan tek bir `iter` template'i yazmak. Uygulanacak
fonksiyon elemanı **const referans** ya da **non-const referans**
alabilmeli — `iter`'ın kendisi buna karışmamalı.

## Neden fonksiyon tipi de template parametresi (`F`)?
- 3. parametreyi sabit bir imza ile (`void (*f)(T &)`) yazsaydık,
  `iter` yalnızca *tam o imzaya* sahip fonksiyonlarla çalışırdı.
  C++'ta fonksiyon pointer tipleri **implicit convert olmaz**: `T
  const &` alan bir fonksiyon, `T &` bekleyen bir pointer değişkenine
  atanamaz. Yani sabit imza seçseydik, const-ref alan fonksiyonlar
  (örn. sadece `std::cout` ile yazdıran) reddedilirdi.
- `F`'yi de template yaparak bu kararı **çağırana** bırakıyoruz: `f`
  ister fonksiyon pointer'ı ister functor olsun, `iter` içinde tek
  yaptığımız `f(array[i])` çağrısı — hangi imzaya sahip olduğunu
  derleyici çağrı anında (instantiation sırasında) çözer.

## Sistem seviyesinde bilinmesi gerekenler
1. **Template argüman çıkarımı (deduction) fonksiyon pointer'larında
   sınırlı çalışır**: `iter(arr, len, printElem<int>)` çağrısında
   `printElem<int>` diye **açıkça** T'yi belirtmek zorundayız.
   `printElem` kendisi de bir template olduğu için, derleyici onu
   `iter`'ın `F` parametresine bakarak "geriye doğru" çözemez —
   deduction tek yönlü çalışır (kullanım yerinden imzaya, imzadan
   kullanım yerine değil).
2. **`len`'in `const` olması ne anlama gelir**: `iter` fonksiyonu
   kendi içinde `len`'i değiştiremez; bu, "bu parametre sadece okunur,
   fonksiyonun iç mantığı yanlışlıkla onu değiştiremez" garantisini
   derleyiciye verir. Çağıran taraftaki `len` değişkenini etkilemez
   (zaten value ile geçiyor), sadece `iter`'ın gövdesi için bir
   sözleşmedir.
3. **const-correctness dizide de zincirleme çalışır**: `T *array`
   parametresine `int const carr[]` verildiğinde, derleyici `T`'yi
   `int const` olarak çözer. Bu durumda `array[i]` de `int const &`
   tipinde olur — `doubleElem` gibi non-const referans isteyen bir
   fonksiyonla çağırmaya çalışırsan **derleme hatası** alırsın. Bu,
   runtime'da değil derleme zamanında yakalanan bir güvenlik: const
   bir diziyi yanlışlıkla değiştirmeye çalışan kod hiç binary'ye
   girmez.
4. **`f(array[i])` çağrısının maliyeti**: `f` bir fonksiyon
   pointer'ıysa runtime'da bir indirect call (pointer üzerinden
   çağrı) olur; ama `f` bir functor/lambda-benzeri obje olsaydı ve
   `operator()` inline edilebiliyorsa, derleyici genelde bunu tamamen
   optimize edip normal bir fonksiyon çağrısı gibi (hatta bazen daha
   hızlı) üretebilir. Template'in "generic ama sıfır maliyetli
   olma" felsefesi burada da geçerli.
