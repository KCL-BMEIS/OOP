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

    // Check that each side length is valid
    if ((a >= b + c) ||
        (b >= a + c) ||
        (c >= a + b))
    {
        std::cerr << "Invalid side length detected\n";
        return 1;
    }

    // Perform the calculation
    float const s = (a + b + c) / 2.0;
    float const A = std::sqrt(s * (s - a) * (s - b) * (s - c));

    // Output the result and exit
    std::cout << "The area is " << A << '\n';
    return 0;
}
