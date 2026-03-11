#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- 1. Constructor Chain Test ---" << std::endl;
    ScavTrap scav("SC4V-TP");
    std::cout << std::endl;

    std::cout << "--- 2. Basic Statistics and Attack Testing ---" << std::endl;
    scav.attack("Vahsi Skag");
    scav.takeDamage(30);
    scav.beRepaired(20);
    std::cout << std::endl;

    std::cout << "--- 3. Special Talent Test ---" << std::endl;
    scav.guardGate();
    std::cout << std::endl;

    std::cout << "--- 4. Energy and Fatigue Test ---" << std::endl;
    ScavTrap weakBot("YorgunRobot");
    for (int i = 0; i < 51; i++) {
        weakBot.attack("Hedef Tahtasi");
    }
    weakBot.beRepaired(10); 
    std::cout << std::endl;

    std::cout << "--- 5. Destructor Chain Test ---" << std::endl;
    return 0;
}