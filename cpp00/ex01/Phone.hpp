#ifndef PHONE_HPP
#define PHONE_HPP

#include "Contact.hpp"

class Phone{
	private:
		Contact _person[8];
		int		_index;
		int		_totalPerson;

	public:
		Phone();
		~Phone();

		void getPhoneBook();
};

#endif