#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
    const int num_animals = 4;
    Animal* animals[num_animals];

    std::cout << "--- Creating Animals ---" << std::endl;
    for (int i = 0; i < num_animals; i++) {
        if (i < num_animals / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n--- Testing Deep Copy ---" << std::endl;
    Dog basic;
    {
        Dog tmp = basic; 
    } 
    basic.makeSound();

    std::cout << "\n--- Deleting Animals ---" << std::endl;
    for (int i = 0; i < num_animals; i++) {
        delete animals[i];
    }

    return 0;
}