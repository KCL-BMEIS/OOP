#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

#include "debug.h"
#include "pgm.h"
#include "dataset.h"

// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 2)
    throw std::runtime_error ("missing arguments - expected at least 1 argument");

  Dataset data ({ args.begin()+1, args.end() });

  int x = data.get(0).width()/2;
  int y = data.get(0).height()/2;

  std::cerr << std::format ("image values at pixel ({},{}) = [ ", x, y);
  for (const auto& val : data.get_timecourse (x,y))
    std::cerr << val << " ";
  std::cerr << "]\n";
}




// skeleton main() function, whose purpose is now to pass the arguments to
// run() in the expected format, and catch and handle any exceptions that may
// be thrown.

int main (int argc, char* argv[])
{
  try {
    std::vector<std::string> args (argv, argv+argc);
    run (args);
  }
  catch (std::exception& excp) {
    std::cerr << "ERROR: " << excp.what() << " - aborting\n";
    return 1;
  }
  catch (...) {
    std::cerr << "ERROR: unknown exception thrown - aborting\n";
    return 1;
  }

  return 0;
}
