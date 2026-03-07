> float değerini saklarken doğrudan bit kaydıramayız çünkü float tipi bellekte IEEE 754 standardıyla (sign, exponent, mantissa) saklanır. Bu yüzden çarparak tam sayıya çevirip öyle saklıyoruz. roundf kullanmamızın sebebi ise hassasiyet kaybını minimuma indirmektir

> Bilgisayar işlemcileri (CPU) tam sayılarla (int) işlem yaparken çok hızlıdır. Ancak ondalıklı sayılarla (float) işlem yapmak için FPU (Floating Point Unit) denilen özel bir birime ihtiyaç duyarlar.
 >> Eski veya Küçük Sistemler: GameBoy, eski hesap makineleri veya bugün kullandığımız küçük mikrokontrolcülerde (çamaşır makinesi kartı gibi) gelişmiş bir FPU yoktur.

>> Sorun: Eğer bu cihazlarda standart float kullanırsan, işlemci o sayıyı toplamak için yüzlerce takla atar ve sistem çok yavaşlar.

>> Çözüm (Fixed Point): Biz bu projede, bir tam sayının (int) içine sanal bir virgül koyuyoruz. İşlemciye "Bu aslında bir tam sayı, sen öyle davran" diyoruz ama biz kendi kafamızda son 8 bitini ondalık kabul ediyoruz. Böylece float hızında değil, int hızında ondalıklı işlem yapıyoruz.

>> Hız: Tam sayı toplama işlemi, float toplama işleminden kat kat daha hızlıdır.

>> Determinizm (Aynı Sonuç): float sayıları farklı işlemcilerde (Intel vs ARM) bazen çok küçük farklarla hesaplanabilir. Ancak Fixed Point tamamen tam sayı matematiği kullandığı için her işlemcide bitine kadar aynı sonucu verir. Bu, çok oyunculu (multiplayer) oyunların senkronizasyonu için hayati önem taşır.

>> Donanım Uyumu: FPU ünitesi olmayan çiplerde ondalıklı hesap yapabilmenin tek yolu budur.