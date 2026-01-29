#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <sys/stat.h>

static bool file_exists(const std::string& path) {
    struct stat sb;
    return stat(path.c_str(), &sb) == 0 && S_ISREG(sb.st_mode);
}

static std::string read_file(const std::string& path) {
    std::ifstream ifs(path.c_str());
    if (!ifs)
        throw std::runtime_error("Cannot open file: " + path);
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

static void write_file(const std::string& path, const std::string& content) {
    std::ofstream ofs(path.c_str());
    if (!ofs)
        throw std::runtime_error("Cannot write file: " + path);
    ofs << content;
}

static std::string sed_replace(
    const std::string& input,
    const std::string& old_str,
    const std::string& new_str
) {
    if (old_str.empty())
        return input;

    std::string result;
    std::size_t pos = 0, prev = 0;

    while ((pos = input.find(old_str, prev)) != std::string::npos) {
        result.append(input, prev, pos - prev);
        result += new_str;
        prev = pos + old_str.size();
    }
    result.append(input, prev, std::string::npos);
    return result;
}

static int compare(
    const std::string& output_file,
    const std::string& expected
) {
    std::string actual = read_file(output_file);

    if (actual == expected) {
        std::cout << "OK - Files match for `" << output_file << "'\n";
        return 0;
    }

    std::cout << "KO - Files differ for `" << output_file << "'\n\n";
    std::cout << "---- actual ----\n" << actual << "\n";
    std::cout << "---- expected ----\n" << expected << "\n";
    return 1;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <old_string> <new_string> [input-file]\n";
        return 1;
    }

    std::string old_str   = argv[1];
    std::string new_str   = argv[2];
    std::string input     = argv[3];
    std::string output    = input + ".replace";

    if (!file_exists(input)) {
        std::cerr << "Error: File '" << input << "' not found\n";
        return 1;
    }

    try {
        std::string content = read_file(input);

        // Simulazione run_cpp: produce <input>.replace
        std::string replaced = sed_replace(content, old_str, new_str);
        write_file(output, replaced);

        // Simulazione run_sed + compare
        std::string expected = sed_replace(content, old_str, new_str);
        return compare(output, expected);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
