#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon{
	private:
		std::string _type;
	public:
		Weapon(std::string _type);
		~Weapon();

		const std::string& getType() const; // Dönen referans'da const olacak // const std::string& dönersen, sadece o verinin "takma adını" (adresini) vermiş olursun; bu da özellikle uzun metinlerde belleği ve işlemciyi yormaz.
		void setType(std::string _type);
};

#endif