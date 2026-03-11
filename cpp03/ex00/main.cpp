#include "ClapTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- 1. Constructor and Name Test ---" << std::endl;
    ClapTrap clap("CL4P-TP");
    std::cout << std::endl;

    std::cout << "--- 2. Attack and Energy Test ---" << std::endl;
    clap.attack("Hedef Kuklasi");
    std::cout << std::endl;

    std::cout << "--- 3. Damage and Repair Test ---" << std::endl;
    clap.takeDamage(5);
    clap.beRepaired(3);
    std::cout << std::endl;

    std::cout << "--- 4. Energy Depletion Test ---" << std::endl;
    ClapTrap weakling("BitikRobot");
    for (int i = 0; i < 11; i++) {
        weakling.attack("Duvar");
    }
    weakling.beRepaired(5);
    std::cout << std::endl;

    std::cout << "--- 5. Death Test ---" << std::endl;
    ClapTrap ghost("Hayalet");
    ghost.takeDamage(10);
    ghost.attack("Intikam");
    ghost.beRepaired(1);
    std::cout << std::endl;

    std::cout << "--- 6. Destructor Test ---" << std::endl;
    return 0;
}