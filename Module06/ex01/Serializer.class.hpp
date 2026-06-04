#pragma once

#include <inttypes.h>

typedef struct s_data Data;

class Serializer {

	private:
		// Required but not used
		Serializer ( void );
		Serializer ( Serializer & other);
		Serializer& operator= (Serializer & other);
		~Serializer ( void );

	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);
};
