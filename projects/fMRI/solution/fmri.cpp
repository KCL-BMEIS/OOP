#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

#include "terminal_graphics.h"

#include "debug.h"
#include "pgm.h"
#include "dataset.h"
#include "task.h"
#include "utils.h"

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

  if (args.size() < 3)
    throw std::runtime_error ("missing arguments - expected at least 2 arguments: taskfile followed by list of images");

  auto task = load_task (args[1]);

  Dataset data ({ args.begin()+2, args.end() });

  if (task.size() != data.size())
    throw std::runtime_error ("number of time points in task file does not match dataset");

  TG::imshow (TG::magnify (data[0], 4), 0, 4000);

  // default values if x & y not set (<0):
  if (x < 0 || y < 0) {
    x = data[0].width()/2;
    y = data[0].height()/2;
  }
  else {
    if (x >= data[0].width() || y >= data[0].height())
      throw std::runtime_error ("pixel position is out of bounds");
  }

  auto signal = data.get_timecourse (x,y);
  auto minval = std::ranges::min (signal);
  auto maxval = std::ranges::max (signal);
  TG::plot()
    .add_line (signal)
    .add_line (rescale (task, minval, maxval), 3);

  std::cerr << std::format ("correlation_coefficient at ({},{}) = {}\n",
     x, y, correlation_coefficient (signal, task));
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
