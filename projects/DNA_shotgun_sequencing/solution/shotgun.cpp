#include <iostream>
#include <vector>
#include <string>

#include "fragments.h"
#include "overlap.h"
#include "debug.h"
#include "shotgun_sequencer.h"

// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 3)
    throw std::runtime_error ("missing arguments - expected 2 arguments: input_fragments output_sequence");

  ShotgunSequencer solver (args[1], 10);

  std::cerr << "initial sequence has size " << solver.sequence().size() << "\n";

  while (solver.iterate());

  solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";

  solver.save (args[2]);
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
