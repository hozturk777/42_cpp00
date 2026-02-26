#include <iostream> // I/O stream std::cout icin kutuphane
#include <string>

//int	main(int ac, char **av)
//{
//	if (ac == 1)
//	{
//		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
//		return (0);
//	}
//	else
//	{
//		av++;
//		for (size_t i = 0; av[i]; i++)
//		{
//			for (size_t j = 0; av[i][j]; j++)
//				std::cout << (char)std::toupper(av[i][j]);
//		}
//		std::cout << std::endl;
//	}
//	return (0);
//}

// :: (Scope resolution) Kapsama Erismek orn: std::cout (standart kutuphanenin cout fonksiyonu)
// << (Stream insertion) Ekleme operatoru, Sağındaki veriyi solundaki akışa(stream) gönderir.


class ToUpper {
	private:
		std::string argv;

	public:
		ToUpper(std::string p_argv) : argv(p_argv) {}

		friend std::ostream& operator<<(std::ostream& os, const ToUpper& str){
			std::string temp = str.argv;
			for (auto & c : temp) { // Reference-based range-for loop
				c = std::toupper(c);
			}
			os << temp;
			return os;
		}
};

int	main(int ac, char **av)
{
	ToUpper doit(av[1]);

	std::cout << doit << std::endl;
}

// auto temp'in elemanlarının type'ı neyse c'yi otomatik type cast ediyor, &(ref) alma sebebi ise direkt temp'den gelen karakterin adresinde işlem yapmak için
// 