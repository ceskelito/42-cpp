#include "Array.class.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Test 1: Array with no parameter ===" << std::endl;
	Array<int> a;
	std::cout << "Size of empty array: " << a.size() << std::endl;
	std::cout << "Value at a[0]: " << a[0] << std::endl;

	std::cout << "\n=== Test 2: Array with n parameter ===" << std::endl;
	Array<int> b(5);
	std::cout << "Size of b: " << b.size() << std::endl;
	std::cout << "Default value at b[0]: " << b[0] << std::endl;
	std::cout << "Default value at b[4]: " << b[4] << std::endl;

	std::cout << "\n=== Test 3: Setting values ===" << std::endl;
	Array<int> c(3);
	c[0] = 42;
	c[1] = 100;
	c[2] = 200;
	std::cout << "c[0]: " << c[0] << std::endl;
	std::cout << "c[1]: " << c[1] << std::endl;
	std::cout << "c[2]: " << c[2] << std::endl;

	std::cout << "\n=== Test 4: Copy constructor ===" << std::endl;
	Array<int> d = c;
	std::cout << "d[0]: " << d[0] << std::endl;
	std::cout << "d[1]: " << d[1] << std::endl;
	d[0] = 999;
	std::cout << "After modifying d[0] to 999:" << std::endl;
	std::cout << "c[0]: " << c[0] << " (should be 42)" << std::endl;
	std::cout << "d[0]: " << d[0] << " (should be 999)" << std::endl;

	std::cout << "\n=== Test 5: Assignment operator ===" << std::endl;
	Array<int> e(2);
	e[0] = 11;
	e[1] = 22;
	Array<int> f(4);
	f = e;
	std::cout << "f.size() after assignment: " << f.size() << std::endl;
	std::cout << "f[0]: " << f[0] << std::endl;
	std::cout << "f[1]: " << f[1] << std::endl;
	f[0] = 777;
	std::cout << "After modifying f[0] to 777:" << std::endl;
	std::cout << "e[0]: " << e[0] << " (should be 11)" << std::endl;
	std::cout << "f[0]: " << f[0] << " (should be 777)" << std::endl;

	std::cout << "\n=== Test 6: Self assignment ===" << std::endl;
	Array<int> g(3);
	g[0] = 5;
	g[1] = 10;
	g[2] = 15;
	g = g;
	std::cout << "g[0] after self assignment: " << g[0] << std::endl;
	std::cout << "g[1] after self assignment: " << g[1] << std::endl;

	std::cout << "\n=== Test 7: Out of range exception ===" << std::endl;
	Array<int> h(2);
	h[0] = 55;
	h[1] = 66;
	try {
		std::cout << "Trying to access h[2] (out of bounds)..." << std::endl;
		std::cout << h[2] << std::endl;
		std::cout << "ERROR: Exception was not thrown!" << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 8: Array of strings ===" << std::endl;
	Array<std::string> strings(3);
	strings[0] = "Hello";
	strings[1] = "World";
	strings[2] = "C++";
	std::cout << "strings[0]: " << strings[0] << std::endl;
	std::cout << "strings[1]: " << strings[1] << std::endl;
	std::cout << "strings[2]: " << strings[2] << std::endl;

	std::cout << "\n=== Test 9: Array of floats ===" << std::endl;
	Array<float> floats(3);
	floats[0] = 3.14f;
	floats[1] = 2.71f;
	floats[2] = 1.41f;
	std::cout << "floats[0]: " << floats[0] << std::endl;
	std::cout << "floats[1]: " << floats[1] << std::endl;
	std::cout << "floats[2]: " << floats[2] << std::endl;

	std::cout << "\n=== All tests completed ===" << std::endl;
	return 0;
}
