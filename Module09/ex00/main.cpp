#include "BitcoinExchange.hpp"
#include <iostream>

#include <ctime>
#include <string>
#include <sstream>
#include <stdexcept>
#include <sstream>

std::time_t getTimeStamp(std::string timeString) {
    int		year, month, day;
    char	dash1, dash2;

	// Works beacuse istringstream save the data only if can fit the variable
    std::istringstream iss(timeString);
    iss >> year >> dash1 >> month >> dash2 >> day;

    if (timeString.length() != 10 || iss.fail() || dash1 != '-' || dash2 != '-' || !iss.eof()) {
        throw std::invalid_argument("Invalide date format: " + timeString + ". Expected YYYY-MM-DD.");
    }

    struct std::tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_isdst = -1;

	// Convert the struct in timestamp
    std::time_t timestamp = std::mktime(&timeStruct);

	// Obtain the normalized date string from the struct
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeStruct);
    std::string normalizedDate(buffer);

    // If the normalized differs from the original, means that the date was Invalid
    if (timestamp == -1 || normalizedDate != timeString) {
        throw std::invalid_argument("Invalid date: " + timeString);
    }

    return timestamp;
}

std::string timestampToString(time_t timestamp, const char* format = "%Y-%m-%d %H:%M:%S") {
    struct tm * timeinfo;
    char buffer[80];

    // Converte il timestamp in una struct tm locale
    timeinfo = localtime(&timestamp);

    // Formatta la data secondo il formato specificato
    strftime(buffer, sizeof(buffer), format, timeinfo);

    return std::string(buffer);
}

#include <exception>

int main(int ac, char **av) {
	if (ac != 2)
	{
		std::cerr << "Erroneus number of argument. Has to be 1." << std::endl;
		return 1;
	}

	// BitcoinExchange btc(av[1]);
	// btc.printInfo();
	
	std::time_t t;
	try {
		t = getTimeStamp("2025-12-3");
		t = getTimeStamp("2004-01-25");
		t = getTimeStamp("2026-02-30");
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	(void) t;
	(void) av;

}
