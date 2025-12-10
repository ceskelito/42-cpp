#include <iostream>
#include <cstring>
#include <string>

int main(int argc, char *argv[])
{
	const std::string	noise = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	if (argc < 2)
		std::cout << noise;
	
	for (int i = 1; i < argc; i++)
		for (char *str = strtok(argv[i], " "); str; str = strtok(NULL, " "))
		{
			int len = strlen(str);
			for (int j = 0; j < len; j++)
				str[j] = toupper(str[j]);	
			std::cout << str << " ";
		}
	std::cout << std::endl;

	return 0;
}
