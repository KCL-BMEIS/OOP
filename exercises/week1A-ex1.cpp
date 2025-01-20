#include <iostream>

int main()
{
    std::cout << (7 * 3) / 5 << '\n';         // Outputs 4 as integer division
    std::cout << (7.0 * 3) / 5 << '\n';       // Outputs 4.2 as promoted to floating-point division
    std::cout << (7 * 3.0) / 5 << '\n';       // Outputs 4.2 as promoted to floating-point division
    std::cout << (7 * 3) / 5.0 << '\n';       // Outputs 4.2 as promoted to floating-point division
    std::cout << (7.0 * 3.0) / (5.0) << '\n'; // Outputs 4.2 as floating-point division
    std::cout << (7 * 3) % 5 << '\n';         // Outputs 1 (integer remainder)
    // std::cout << (7 * 3.0) % 5 << '\n';     // Does not compile as no floating-point remainder operator
}
