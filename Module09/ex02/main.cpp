
#include "PmergeMe.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <set>

#include <cmath>
#include <vector>
#include <list>

static std::string validate_arg(std::string arg)
{
    if (arg[0] == '-')
        return "Negative numbers are not allowed";
    long nbr = strtol(arg.c_str(), NULL, 10);
    if (nbr == 0 && arg != "0")
        return "Non-number arguments not allowed";
    if (nbr > INT_MAX || errno == ERANGE)
        return "Too big arguments are not allowed";
    return "";
}

static std::string validate(int argc, char** argv)
{
    if (argc == 1)
        return "No arguments were provided";
    for (int i = 1; i < argc; i++)
    {
        std::string status = validate_arg(argv[i]);
        if (status != "")
            return status;
    }
    return "";
}

static std::vector<int> argv_to_vector(int argc, char** argv)
{
    std::vector<int> res;
    res.reserve(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        res.push_back(atoi(argv[i]));
    }
    return res;
}

static std::list<int> argv_to_list(int argc, char** argv)
{
    std::list<int> res;
    for (int i = 1; i < argc; i++)
    {
        res.push_back(atoi(argv[i]));
    }
    return res;
}

static std::multiset<int> argv_to_set(int argc, char** argv)
{
    std::multiset<int> res;
    for (int i = 1; i < argc; i++)
    {
        res.insert(atoi(argv[i]));
    }
    return res;
}

template <typename T> static bool is_sorted(const T& container)
{
    if (container.size() == 0 || container.size() == 1)
        return true;
    typename T::const_iterator end = container.end();
    std::advance(end, -1);
    for (typename T::const_iterator it = container.begin(); it != end; it++)
    {
        typename T::const_iterator next = it;
        std::advance(next, 1);
        if (*it > *next)
            return false;
    }
    return true;
}

static std::string argv_to_str(int argc, char** argv)
{
    std::string res("");
    res.reserve(argc + 1);
    res += "[";
    res += argv[1];
    for (int i = 2; argv[i]; i++)
    {
        res += " ";
        res += argv[i];
    }
    res += "]";
    return res;
}

static std::string vec_to_str(std::vector<int>& vec)
{
    std::stringstream ss;
    ss << "[" << vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        ss << " " << vec[i];
    }
    ss << "]";
    return ss.str();
}

static bool retained_original_values(std::multiset<int>& original_values, std::vector<int>& vec)
{
	for (int i = 0; i < (int)vec.size(); i++)
	{
        std::multiset<int>::iterator it = original_values.find(vec[i]);
        if (it == original_values.end())
            return false;
        original_values.erase(it);
	}
	return true;
}

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int main(int argc, char** argv)
{
	
    std::string status = validate(argc, argv);
    if (status != "")
    {
        std::cerr << "Error: " << status << "\n";
        return EXIT_FAILURE;
    }
    std::multiset<int> original_values = argv_to_set(argc, argv);

	int nbr_of_comps_vec = 0;
    clock_t start_vec = clock();
    std::vector<int> vec = argv_to_vector(argc, argv);
	nbr_of_comps_vec = PmergeMe::sort(vec);
    clock_t end_vec = clock();
    double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;

    int nbr_of_comps_list = 0;
    clock_t start_list = clock();
    std::list<int> lst = argv_to_list(argc, argv);
    nbr_of_comps_list = PmergeMe::sort(lst);
    clock_t end_list = clock();
    double time_elapsed_list = static_cast<double>(end_list - start_list) / CLOCKS_PER_SEC;

     if (!is_sorted(vec) || (int)vec.size() != (argc - 1) || !retained_original_values(original_values, vec))
     {
              std::cout << "Vector was not sorted properly.\n";
          return 1;
     }
         if (!is_sorted(lst) || (int)lst.size() != (argc - 1))
     {
              std::cout << "List was not sorted properly.\n";
          return 1;
     }

    std::cout << "\033[31mBefore\033[00m: " << argv_to_str(argc, argv) << "\n";
    std::cout << "\033[32mAfter\033[00m:  " << vec_to_str(vec) << "\n";
    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << std::fixed << std::setprecision(6)
              << time_elapsed_vec << "s\n";
    std::cout << "Time to process a range of " << lst.size()
              << " elements with std::list   : " << std::fixed << std::setprecision(6)
              << time_elapsed_list << "s\n";
    std::cout << "Maximum admitted comparisons    : " << F(argc - 1) << std::endl;
    std::cout << "Number of effective comparisons : " << nbr_of_comps_vec << '\n';
    (void) nbr_of_comps_list;
}
