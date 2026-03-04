#include <iostream>
#include <string>

int main(int ac, char **av)
{
    if (ac == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (0);
    }
    for (int i = 1; i < ac; i++)
    {
        std::string current_arg = av[i];
        for (size_t j = 0; j < current_arg.length(); j++)
        {
            std::cout << (char)std::toupper((unsigned char)current_arg[j]);
        }
    }
    std::cout << std::endl;
    return (0);
}
// :: (Scope resolution) Kapsama Erismek orn: std::cout (standart kutuphanenin cout fonksiyonu)
// << (Stream insertion) Ekleme operatoru, Sağındaki veriyi solundaki akışa(stream) gönderir.