1. Zincirleme Kullanım (Chaining)
operator<< overloading yaptığında, nesneni tıpkı bir int veya string gibi std::cout ile zincirleme şekilde kullanabilirsin. Eğer sadece string dönsen, her seferinde o fonksiyonu çağırman gerekir.

Overloading ile: std::cout << obj1 << " " << obj2 << std::endl;

String Dönerek: std::cout << obj1.toString() << " " << obj2.toString() << std::endl;

2. Akış (Stream) Mantığına Uyumluluk
C++'ta nesnelerin kendilerini bir "akışa" (ostream) yazması, dilin felsefesine (idiomatic C++) daha uygundur. Bu sayede nesneni sadece ekrana basmakla kalmaz, hiçbir kod değişikliği yapmadan bir dosyaya (ofstream) veya bir string akışına (stringstream) da gönderebilirsin.

3. Bellek ve Performans
Bir std::string döndüğünde, fonksiyon içinde yeni bir string nesnesi oluşturulur, veriler oraya kopyalanır ve sonra bu nesne geri döndürülür. Operatör overload ettiğinde ise veriyi doğrudan akışa (buffer) yazarsın, böylece gereksiz kopyalama ve geçici nesne oluşturma maliyetinden kurtulursun.

4. 42 "Ad-hoc" Polimorfizm Hedefi
Yorum satırına yazdığın gibi, bu egzersizlerin amacı sana Ad-hoc Polimorfizm (function/operator overloading) kavramını öğretmektir. C++ Module 02'ye geçtiğinde, neredeyse her sınıfın (Fixed, Point vb.) kendi operator<< aşırı yüklemesine sahip olduğunu göreceksin.

Teknik Not:
Yazdığın koddaki şu kısım oldukça profesyonel bir dokunuş:
os << (char)std::toupper((unsigned char)temp[i]);
unsigned char cast işlemi, ASCII dışı karakterlerde std::toupper fonksiyonunun tanımsız davranış sergilemesini (undefined behavior) engeller; bu yüzden doğru bir yaklaşımdır.