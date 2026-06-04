#include "Serializer.class.hpp"
#include <iostream>

typedef struct s_data {
	int info;
} Data;

int main() {
	
	uintptr_t	serialized = 0;
	Data*		data = new Data;
	Data*		deserialized = 0;

	data->info = 42;

	std::cout << "data info: " << data->info << std::endl;
	serialized = Serializer::serialize(data);
	std::cout << "serialized: " << serialized << std::endl;	
	deserialized = Serializer::deserialize(serialized);
	std::cout << "deserialized info: " << deserialized->info << std::endl;

	delete data;
}
