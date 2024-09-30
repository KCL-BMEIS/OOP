#include <iostream>
#include <vector>
#include <string>

int main (int argc, char** argv)
{
  std::vector<std::string> args (argv, argv+argc);

  for (auto a : args)
    std::cout << "argument: " << a << "\n";

  return 0;
}
