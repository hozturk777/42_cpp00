#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- 1. Konstruktor Zinciri Testi ---" << std::endl;
    // ScavTrap olusturuldugunda once ClapTrap'in olustugu gorulmeli
    ScavTrap scav("SC4V-TP");
    std::cout << std::endl;

    std::cout << "--- 2. Temel Istatistik ve Saldiri Testi ---" << std::endl;
    // ScavTrap'in kendine has saldiri mesaji ve hasari (20) olmali
    scav.attack("Vahsi Skag");
    scav.takeDamage(30);
    scav.beRepaired(20);
    std::cout << std::endl;

    std::cout << "--- 3. Ozel Yetenek Testi ---" << std::endl;
    // ScavTrap'in ozel Gatekeeper modu
    scav.guardGate();
    std::cout << std::endl;

    std::cout << "--- 4. Enerji ve Can Tukenme Testi ---" << std::endl;
    // Enerjisi veya cani biten robot aksiyon alamaz
    ScavTrap weakBot("YorgunRobot");
    for (int i = 0; i < 51; i++) {
        weakBot.attack("Hedef Tahtasi");
    }
    weakBot.beRepaired(10); // Enerji bittigi icin calismamali
    std::cout << std::endl;

    std::cout << "--- 5. Destruktor Zinciri Testi ---" << std::endl;
    // Yok edilme sirasi olusmanin tam tersi olmali
    return 0;
}