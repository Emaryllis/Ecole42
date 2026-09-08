#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
	Data data;
	data.id = 42;
	data.name = "Test Data";
	data.value = 3.14159;

	Data *originalPtr = &data;
	const uintptr_t serialized = Serializer::serialize(originalPtr);
	const Data *deserializedPtr = Serializer::deserialize(serialized);

	std::cout << "Original Pointer:     " << originalPtr << std::endl;
	std::cout << "Serialized Value:     " << serialized << std::endl;
	std::cout << "Deserialized Pointer: " << deserializedPtr << std::endl;

	if (deserializedPtr == originalPtr)
		std::cout << "Success: Deserialized pointer matches original pointer." << std::endl;
	else
		std::cout << "Error: Pointers do not match!" << std::endl;

	std::cout << "Data ID:    " << deserializedPtr->id << std::endl;
	std::cout << "Data Name:  " << deserializedPtr->name << std::endl;
	std::cout << "Data Value: " << deserializedPtr->value << std::endl;

	return 0;
}