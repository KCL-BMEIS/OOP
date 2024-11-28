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

  int x = -1, y = -1;
  auto pixel_option = std::ranges::find (args, "-p");
  if (pixel_option != args.end()) {
    if (std::distance (pixel_option, args.end()) < 3)
      throw std::runtime_error ("not enough arguments to '-p' option (expected '-p x y')");
    x = std::stoi (*(pixel_option+1));
    y = std::stoi (*(pixel_option+2));
    args.erase (pixel_option, pixel_option+3);
  }

  if (args.size() < 2)
    throw std::runtime_error ("missing arguments - expected at least 1 argument");

  Dataset data ({ args.begin()+1, args.end() });

  // default values if x & y not set (<0):
  if (x < 0 || y < 0) {
    x = data.get(0).width()/2;
    y = data.get(0).height()/2;
  }
  else {
    if (x >= data.get(0).width() || y >= data.get(0).height())
      throw std::runtime_error ("pixel position is out of bounds");
  }

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
