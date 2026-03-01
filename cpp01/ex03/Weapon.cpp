#include "Weapon.hpp"


Weapon::Weapon(std::string _type){
	this->_type = _type;
}
Weapon::~Weapon(){

}

const std::string& Weapon::getType() const {
	return (this->_type);
}

void Weapon::setType(std::string _type) {
	this->_type = _type;
}