#include <iostream>
#include <vector>
#include <string>

#include "fragments.h"
#include "overlap.h"

// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  if (args.size() < 3)
    throw std::runtime_error ("missing arguments - expected 2 arguments: input_fragments output_sequence");

  auto fragments = load_fragments (args[1]);
  fragment_statistics (fragments);

  auto sequence = extract_longest_fragment (fragments);
  std::cerr << "initial sequence has size " << sequence.size() << "\n";

  auto overlap = compute_overlap (sequence, fragments[12]);
  std::cerr << "computed overlap = " << overlap << "\n";

  write_sequence (args[2], sequence);
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
