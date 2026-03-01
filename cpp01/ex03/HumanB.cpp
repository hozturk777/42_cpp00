#include "HumanB.hpp"
#include <iostream>
#include <string>

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{
}
HumanB::~HumanB(){

}

void HumanB::attack(){
	if (this->_weapon != NULL)
        std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
    else
        std::cout << this->_name << " has no weapon" << std::endl;
}

void HumanB::setWeapon(Weapon& _weapon){
	this->_weapon = &_weapon;
}