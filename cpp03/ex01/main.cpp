#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- 1. Konstruktor Zinciri Testi ---" << std::endl;
    ScavTrap scav("SC4V-TP");
    std::cout << std::endl;

    std::cout << "--- 2. Temel Istatistik ve Saldiri Testi ---" << std::endl;
    scav.attack("Vahsi Skag");
    scav.takeDamage(30);
    scav.beRepaired(20);
    std::cout << std::endl;

    std::cout << "--- 3. Ozel Yetenek Testi ---" << std::endl;
    scav.guardGate();
    std::cout << std::endl;

    std::cout << "--- 4. Enerji ve Can Tukenme Testi ---" << std::endl;
    ScavTrap weakBot("YorgunRobot");
    for (int i = 0; i < 51; i++) {
        weakBot.attack("Hedef Tahtasi");
    }
    weakBot.beRepaired(10); 
    std::cout << std::endl;

    std::cout << "--- 5. Destruktor Zinciri Testi ---" << std::endl;
    return 0;
}