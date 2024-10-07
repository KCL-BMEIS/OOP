#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (int n = 0; n < args.size(); n++)
    std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
