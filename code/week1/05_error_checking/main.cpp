#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  if (args.size() < 3) {
    std::cerr << "ERROR: expected min & max to be provided as arguments\n";
    return 1;
  }

  int from = std::stoi (args[1]);
  int to = std::stoi (args[2]);

  if (from > to) {
    std::cerr << "ERROR: max must be greater than min\n";
    return 1;
  }

  std::vector<int> vec;
  for (int n = from; n <= to; n++)
    vec.push_back (n);

  for (auto x : vec)
    std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
