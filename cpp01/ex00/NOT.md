🔍 Kodun Teknik Analizi
Kodun, C++ bellek yönetiminin temelini çok iyi özetliyor:

1. Stack Allocation (Yığın Bellek)
main içindeki Zombie z("Huso"); ve randomChump içindeki Zombie zombie(name); kullanımları Stack üzerinde yer açar.

Ömür: Bu zombiler bulundukları { } (scope) dışına çıktıkları an otomatik olarak yok edilirler.

Kanıt: randomChump fonksiyonu bittiği an, senin yazdığın (veya yazacağın) destructor mesajı ekranda belirir.

2. Heap Allocation (Öbek Bellek)
newZombie içindeki new Zombie(_name); kullanımı belleğin Heap bölgesinde yer ayırır.

Ömür: Bu zombi, sen delete(news); diyene kadar hayatta kalır.

Neden newZombie? Eğer newZombie içinde stack kullansaydın, fonksiyon bittiği an zombi ölürdü ve main'e geçersiz bir adres dönerdi. new kullanarak zombiyi fonksiyonun dışına sağ salim çıkarmış oldun.