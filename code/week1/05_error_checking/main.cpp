#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  if (args.size() < 3)
    throw std::runtime_error ("expected min & max to be provided as arguments");

  int from = std::stoi (args[1]);
  int to = std::stoi (args[2]);

  if (from >= to)
    throw std::runtime_error ("max must be greater than min");

  std::vector<int> vec;
  for (int n = from; n < to; n++)
    vec.push_back (n);

  for (auto x : vec)
    std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
