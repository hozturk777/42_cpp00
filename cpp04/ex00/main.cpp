#include <iostream>
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(){
	WrongAnimal animal;
	animal.makeSound();

	std::cout << "--------------------------------------" << std::endl;

	WrongAnimal* cat = new WrongCat(); // Upcasting

	cat->makeSound();
	delete cat;
	
	std::cout << "--------------------------------------" << std::endl;

	Animal a;
	a.makeSound();

	std::cout << "--------------------------------------" << std::endl;

	Animal* animalDog = new Dog();
	animalDog->makeSound();
	delete animalDog;
	
	std::cout << "--------------------------------------" << std::endl;

	Animal* animalCat = new Cat();
	animalCat->makeSound();
	delete animalCat;

	std::cout << "--------------------------------------" << std::endl;

}