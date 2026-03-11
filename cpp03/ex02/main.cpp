#include "FragTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- 1. FragTrap Constructor Chain Test ---" << std::endl;
    FragTrap frag("FR4G-TP");
    std::cout << std::endl;

    std::cout << "--- 2. FragTrap Statistics and Attack Test ---" << std::endl;
    frag.attack("Handsome Jack");
    frag.takeDamage(50);
    frag.beRepaired(25);
    std::cout << std::endl;

    std::cout << "--- 3.  FragTrap Special Ability (High Five) Test ---" << std::endl;
    frag.highFivesGuys();
    std::cout << std::endl;

    std::cout << "--- 4. FragTrap Energy Depletion Test ---" << std::endl;
    FragTrap staminaBot("StaminaBot");
    for (int i = 0; i < 101; i++) {
        staminaBot.attack("Kum Torbasi");
    }
    staminaBot.highFivesGuys();
    std::cout << std::endl;

    std::cout << "--- 5. FragTrap Death and Action Test ---" << std::endl;
    FragTrap deadBot("GuleGule");
    deadBot.takeDamage(150); 
    deadBot.attack("Hayalet"); 
    deadBot.highFivesGuys(); 
    std::cout << std::endl;

    std::cout << "--- 6. FragTrap Destructor Chain Test ---" << std::endl;
    return 0;
}