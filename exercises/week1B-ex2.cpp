#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <format>

std::string RLE(const std::string &input) {
    if (input.empty()) {
        return "";
    }

    char c = input[0];
    int count = 1;
    std::string output;
    output.push_back(c);
    for (int i = 1; i < input.size(); i++) {
        if (input[i] != c) {
            output += std::format("{}{}", count, input[i]);
            count = 1;
            c = input[i];
        } else {
            count++;
        }
    }
    output += std::format("{}", count);
    return output;
}

int main(int argc, char **argv)
{
    std::vector<std::string> args(argv, argv + argc);

    if (args.size() != 3) {
        std::cerr << "Requires input and output filename\n";
        return 1;
    }

    std::ifstream infile(args[1]);
    std::string input;
    infile >> input;

    std::string const output = RLE(input);

    std::ofstream outfile(args[2]);
    outfile << output << '\n';
}