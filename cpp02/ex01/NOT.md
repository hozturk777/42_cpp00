> float değerini saklarken doğrudan bit kaydıramayız çünkü float tipi bellekte IEEE 754 standardıyla (sign, exponent, mantissa) saklanır. Bu yüzden çarparak tam sayıya çevirip öyle saklıyoruz. roundf kullanmamızın sebebi ise hassasiyet kaybını minimuma indirmektir

> Bilgisayar işlemcileri (CPU) tam sayılarla (int) işlem yaparken çok hızlıdır. Ancak ondalıklı sayılarla (float) işlem yapmak için FPU (Floating Point Unit) denilen özel bir birime ihtiyaç duyarlar.
 >> Eski veya Küçük Sistemler: GameBoy, eski hesap makineleri veya bugün kullandığımız küçük mikrokontrolcülerde (çamaşır makinesi kartı gibi) gelişmiş bir FPU yoktur.

>> Sorun: Eğer bu cihazlarda standart float kullanırsan, işlemci o sayıyı toplamak için yüzlerce takla atar ve sistem çok yavaşlar.

>> Çözüm (Fixed Point): Biz bu projede, bir tam sayının (int) içine sanal bir virgül koyuyoruz. İşlemciye "Bu aslında bir tam sayı, sen öyle davran" diyoruz ama biz kendi kafamızda son 8 bitini ondalık kabul ediyoruz. Böylece float hızında değil, int hızında ondalıklı işlem yapıyoruz.

>> Hız: Tam sayı toplama işlemi, float toplama işleminden kat kat daha hızlıdır.

>> Determinizm (Aynı Sonuç): float sayıları farklı işlemcilerde (Intel vs ARM) bazen çok küçük farklarla hesaplanabilir. Ancak Fixed Point tamamen tam sayı matematiği kullandığı için her işlemcide bitine kadar aynı sonucu verir. Bu, çok oyunculu (multiplayer) oyunların senkronizasyonu için hayati önem taşır.

>> Donanım Uyumu: FPU ünitesi olmayan çiplerde ondalıklı hesap yapabilmenin tek yolu budur.

### ---------

> Fixed-point (sabit noktalı) aritmetik, özellikle düşük güçlü işlemcilerde veya yüksek performans gereken grafik işlemlerinde floating-point (kayan noktalı) birimlerine ihtiyaç duymadan ondalıklı sayıları temsil etmek için kullanılır.

>> Normalde C++'taki float tipi IEEE 754 standardını kullanır. Bu standartta bir sayı üç parçaya bölünür: İşaret (1 bit), Üstel (8 bit) ve Mantissa (23 bit).

>> Bu yapı çok geniş bir aralığı temsil edebilir ancak bit düzeyinde toplama/çıkarma yapmak zordur.

>> Fixed-point aritmetiğinde ise biz bu karmaşık yapıyı terk edip, sayının belirli bir kısmını tam sayı, geri kalan sabit kısmını ise kesir olarak kabul ederiz.

### ---------

> Roundf örn:10859.52 sayısını en yakın tarafa yuvarlar: yuvarlamadığında .52 kaybederken roundf sayesinde kayıp daha minimize ediliyor.

### ---------
> IEEE 754 (Elektrik elektronik mühendislik enstitüsü)
>>Value actually stored in float: Bilgisayarın belleğinde "gerçekten" duran değerdir. Gördüğün gibi upuzun bir sayı: $1.17549435... \times 10^{-38}$.
>>Error due to conversion: İşte burası çok kritik! Sen bir sayı girmek istersin ama bilgisayar o sayıyı bitlerle tam ifade edemez. Aradaki o devasa küsuratlı fark (hata), işte bizim az önce konuştuğumuz yuvarlama zorunluluğunun nedenidir.
>>Hexadecimal Representation (00800000): Bu 32 bitin onaltılık sistemdeki karşılığıdır. Bellekte bu sayı tam olarak bu şekilde kodlanmıştır.