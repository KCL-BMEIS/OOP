#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
#include "debug.h"

// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 3)
    throw std::runtime_error ("missing arguments - expected 2 arguments: input_fragments output_sequence");

  auto fragments = load_fragments (args[1]);
  if (debug::verbose)
    fragment_statistics (fragments);

  auto sequence = extract_longest_fragment (fragments);
  std::cerr << "initial sequence has size " << sequence.size() << "\n";

  while (fragments.size()) {
    debug::log ("---------------------------------------------------");
    debug::log (std::to_string (fragments.size()) + " fragments left");

    auto overlap = find_biggest_overlap (sequence, fragments);

    if (overlap.fragment < 0)
      break;

    if (std::abs (overlap.size) < 10)
      break;

    debug::log (std::format ("fragment with biggest overlap is at index {}, overlap = {}",
         overlap.fragment, overlap.size));

    merge (sequence, fragments[overlap.fragment], overlap.size);
    fragments.erase (fragments.begin() + overlap.fragment);
  }

  debug::log (std::format ("{} fragments remaining unmatched - checking whether already contained in sequence...",
        fragments.size()));

  int num_unmatched = 0;
  for (const auto& frag : fragments) {
    if (sequence.find (frag) == std::string::npos)
      ++num_unmatched;
  }

  if (num_unmatched)
    std::cerr << "WARNING: " << num_unmatched << " fragments remain unmatched!\n";

  std::cerr << "final sequence has length " << sequence.size() << "\n";

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
