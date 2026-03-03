#include <iostream>
#include <fstream>

std::string replaceLine(const std::string& line, const std::string& s1, const std::string& s2) {
    if (s1.empty())
		return line;
    
    std::string result;
    size_t pos = 0;
    size_t foundPos;

    // Bulabildiğin sürece s1'i aramaya devam et
    while ((foundPos = line.find(s1, pos)) != std::string::npos) {
        // Bulunan yere kadar olan kısmı sonuca ekle
        result += line.substr(pos, foundPos - pos);
        // s1 yerine s2'yi ekle
        result += s2;
        // Bir sonraki arama için başlangıç noktasını s1'in sonuna kaydır
        pos = foundPos + s1.length();
    }
    // Satırın geri kalan kısmını (son eşleşmeden sonrasını) ekle
    result += line.substr(pos);
    return result;
}


int main(int ac, char **av)
{
	if (ac != 4) {
        std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
        return 1;
    }

	std::string fname = av[1];
	std::string s1 = av[2];
	std::string s2 = av[3];

	std::ifstream ifs(fname.c_str()); // c.str nedir ?
	if (!ifs.is_open())
	{
		std::cout << "Error: Could not open file:" << fname << std::endl;
		return 1;
	}
	
	std::ofstream ofs((fname + ".replace").c_str());
	if (!ifs.is_open())
	{
		std::cout << "Error: Could not create output file:" << std::endl;
		ifs.close();
		return 1;
	}
	
	std::string line;
	while (std::getline(ifs, line))
	{
		ofs << replaceLine(line, s1, s2);
		if (!ifs.eof())
			ofs << "\n";
		
	}
	
	ifs.close();
	ofs.close();

}