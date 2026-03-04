#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon{
	private:
		std::string _type;
	public:
		Weapon(std::string _type);
		~Weapon();

		const std::string& getType() const;
		void setType(std::string _type);
};

#endif