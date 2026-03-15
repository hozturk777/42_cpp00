#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    std::cout << "--- Testing Polymorphism with Abstract Class ---" << std::endl;
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    dog->makeSound();
    cat->makeSound();

    std::cout << "\n--- Testing Deep Copy for Dog ---" << std::endl;
    Dog originalDog;
    {
        Dog tmp = originalDog;
        tmp.makeSound();
    }
    
    originalDog.makeSound();

    std::cout << "\n--- Cleaning up ---" << std::endl;
    delete dog;
    delete cat;

    return 0;
}