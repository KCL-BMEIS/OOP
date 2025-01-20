#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int main(int argc, char **argv)
{
    // Convert arguments from C to C++
    std::vector<std::string> args(argv, argv + argc);

    // Check arguments are valid.
    if (args.size() != 4)
    { // Remember args[0] is the program name
        std::cerr << "Requires 3 inputs: a b c\n";
        return 1; // Exit early
    }

    // Convert arguments from strings to floating point numbers
    float const a = std::stof(args[1]);
    float const b = std::stof(args[2]);
    float const c = std::stof(args[3]);

    // Check that answer will be real-valued
    if (b * b < 4.0 * a * c)
    {
        std::cerr << "Roots will be complex\n";
        return 1;
    }

    // Perform the calculation
    float const x1 = -b - std::sqrt(b * b - 4.0 * a * c) / (2.0 * a);
    float const x2 = -b + std::sqrt(b * b - 4.0 * a * c) / (2.0 * a);

    // Output the results and exit
    std::cout << "The roots are " << x1 << " and " << x2 << '\n';
    return 0;
}
