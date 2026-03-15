#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

class Animal {
protected:
    std::string _type;

public:
    Animal();
    Animal(const Animal& copy);
    Animal& operator=(const Animal& copy);
    virtual ~Animal();

    virtual void makeSound() const;
    std::string getType() const;
};

#endif