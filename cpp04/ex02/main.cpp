#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
    const int count = 4;
    Animal* animals[count];

    std::cout << "--- 1. DIZIYI DOLDURMA (Half Dogs, Half Cats) ---" << std::endl;
    for (int i = 0; i < count; i++) {
        if (i < count / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n--- 2. SES TESTI ---" << std::endl;
    for (int i = 0; i < count; i++) {
        std::cout << i << ". " << animals[i]->getType() << " says: ";
        animals[i]->makeSound();
    }

    std::cout << "\n--- 3. DEEP COPY TESTI ---" << std::endl;
    Dog basic;
    {
        Dog tmp = basic; // Copy constructor çağrılır
        // Burada tmp kapsam dışına çıktığında destructor'ı çalışacak.
        // Eğer Deep Copy yoksa, basic'in beyni de silinecek (Double Free hatası).
    }
    std::cout << "Basic hala hayatta ve sesi: ";
    basic.makeSound();

    std::cout << "\n--- 4. DIZIYI TEMIZLEME ---" << std::endl;
    for (int i = 0; i < count; i++) {
        delete animals[i];
    }

    return 0;
}