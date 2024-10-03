#include <iostream>
#include <vector>
#include <string>

int main (int argc, char** argv)
{
  std::vector<std::string> args (argv, argv+argc);

  int from = std::stoi (args[1]);
  int to = std::stoi (args[2]);

  std::vector<int> vec;
  for (int n = from; n < to; n++)
    vec.push_back (n);

  for (auto x : vec)
    std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
