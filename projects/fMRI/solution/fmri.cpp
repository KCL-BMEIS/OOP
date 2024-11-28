#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

#include "debug.h"
#include "pgm.h"

// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 2)
    throw std::runtime_error ("missing arguments - expected at least 1 argument");

  std::vector<Image> slices;
  for (unsigned int n = 1; n < args.size(); ++n)
    slices.push_back (load_pgm (args[n]));

  // check that dimensions all match up:
  for (unsigned int n = 1; n < slices.size(); ++n) {
    if ( (slices[n].width() != slices[n-1].width()) ||
         (slices[n].height() != slices[n-1].height()) )
      throw std::runtime_error ("dimensions do not match across slices");
  }

  std::cerr << std::format (
      "loaded {} slices of size {}x{}\n",
      slices.size(), slices[0].width(), slices[0].height());

  int x = slices[0].width()/2;
  int y = slices[0].height()/2;

  std::cerr << std::format ("image values at pixel ({},{}) = [ ", x, y);
  for (const auto& slice : slices)
    std::cerr << slice.get (x,y) << " ";
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
