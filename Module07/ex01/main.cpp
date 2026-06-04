#include "iter.hpp"
#include <iostream>

template<typename T>
void print(T &x){
    std::cout << x;
}

template<>
void print<int>(int &x) {
	std::cout << ++x;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int	len = 5;


    iter(arr, len, print<int const>);
	std::cout << std::endl;
    iter(arr, len, print<int>);

    return 0;
}
