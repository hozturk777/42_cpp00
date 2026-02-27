#include <iostream> // I/O stream std::cout icin kutuphane
#include <string>

class ToUpper {
	private:
		std::string _argv;

	public:
		ToUpper(std::string p_argv) : _argv(p_argv) {}
		std::string getArgv() const { return _argv; }
};

std::ostream& operator<<(std::ostream& os, const ToUpper& str){
	std::string temp = str.getArgv();
    for (size_t i = 0; temp[i]; i++) {
        os << (char)std::toupper((unsigned char)temp[i]);
    }
	return os;
}

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	else
	{
		for (size_t i = 1; i < ac; i++)
		{
			ToUpper doit(av[i]);
			std::cout << doit;
		}
	}
	std::cout << std::endl;
	return 0;
}

// std::ostream&: cout aslında bir ostream (output stream) nesnesidir. Fonksiyonun bunu referans olarak döndürmesi gerekir ki cout << var << var; gibi zincirleme işlemler yapılabilsin.
// operator<<: Bu, C++'a "Ben << sembolünün davranışını değiştiriyorum" demenin yoludur
// :: (Scope resolution) Kapsama Erismek orn: std::cout (standart kutuphanenin cout fonksiyonu)
// << (Stream insertion) Ekleme operatoru, Sağındaki veriyi solundaki akışa(stream) gönderir.