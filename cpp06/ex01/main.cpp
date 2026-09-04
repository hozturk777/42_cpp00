#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data original;
	original.id = 42;
	original.name = "test";
	original.value = 3.14;

	uintptr_t raw = Serializer::serialize(&original);
	Data *restored = Serializer::deserialize(raw);

	std::cout << "Original address:     " << &original << std::endl;
	std::cout << "Serialized value:     " << raw << std::endl;
	std::cout << "Deserialized address: " << restored << std::endl;
	std::cout << ((&original == restored) ? "Pointers match!" : "Pointers do NOT match!") << std::endl;
	std::cout << "restored->id = " << restored->id << std::endl;
	std::cout << "restored->name = " << restored->name << std::endl;
	std::cout << "restored->value = " << restored->value << std::endl;
	return 0;
}
