#include "FragTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- 1. FragTrap Konstruktor Zinciri Testi ---" << std::endl;
    FragTrap frag("FR4G-TP");
    std::cout << std::endl;

    std::cout << "--- 2. FragTrap Istatistik ve Saldiri Testi ---" << std::endl;
    frag.attack("Handsome Jack");
    frag.takeDamage(50);
    frag.beRepaired(25);
    std::cout << std::endl;

    std::cout << "--- 3. FragTrap Ozel Yetenek (High Five) Testi ---" << std::endl;
    frag.highFivesGuys();
    std::cout << std::endl;

    std::cout << "--- 4. FragTrap Enerji Tukenme Testi ---" << std::endl;
    FragTrap staminaBot("StaminaBot");
    for (int i = 0; i < 101; i++) {
        staminaBot.attack("Kum Torbasi");
    }
    staminaBot.highFivesGuys();
    std::cout << std::endl;

    std::cout << "--- 5. FragTrap Olum ve Aksiyon Testi ---" << std::endl;
    FragTrap deadBot("GuleGule");
    deadBot.takeDamage(150); 
    deadBot.attack("Hayalet"); 
    deadBot.highFivesGuys(); 
    std::cout << std::endl;

    std::cout << "--- 6. FragTrap Destruktor Zinciri Testi ---" << std::endl;
    return 0;
}