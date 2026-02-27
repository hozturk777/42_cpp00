#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
	private:
		std::string _name;
		std::string _surName;
		std::string _nickName;
		std::string _phoneNumber;
		std::string _darkestSecret;

	public:
		Contact();
		~Contact();

		std::string getFirstName() const;
		std::string getSurName() const;
		std::string getNickName() const;
		std::string getPhoneNumber() const;
		std::string getDarkestSecret() const;

		void setFirstName(std::string _name);
		void setSurName(std::string _surName);
		void setNickName(std::string _nickName);
		void setPhoneNumber(std::string _phoneNumber);
		void setDarkestSecret(std::string _darkestSecret);
};

#endif