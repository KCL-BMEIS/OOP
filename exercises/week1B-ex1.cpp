#include <vector>
#include <string>
#include <iostream>
#include <fstream>

bool isPrime(int const i)
{
    if (i < 4)
    {
        return true;
    }

    for (int j = 2; j < i / 2; j++)
    {
        if (i % j == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    std::vector<std::string> args(argv, argv + argc);

    int const maximum = std::stoi(args[1]);

    std::cout << "Finding primes up to " << maximum << '\n';

    if (args.size() == 3)
    {
        std::ofstream output(args[2]);
        for (int i = 1; i < maximum; i++)
        {
            if (isPrime(i))
            {
                output << i << '\n';
            }
        }
    }
    else if (args.size() == 2)
    {
        for (int i = 1; i < maximum; i++)
        {
            if (isPrime(i))
            {
                std::cout << i << '\n';
            }
        }
    }
    else
    {
        std::cout << "Wrong number of arguments" << '\n';
    }
}