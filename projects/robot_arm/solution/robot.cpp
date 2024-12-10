#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numbers>

#include "debug.h"
#include "segment/tip.h"
#include "segment/straight.h"
#include "segment/bend.h"
#include "segment/rotate.h"
#include "segment/root.h"

// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  Segment::Tip tip (10.0);
  Segment::Bend bend (tip, 6.0);
  Segment::Straight straight (bend, 15.0);
  Segment::Rotate rotate (straight, 5.0);
  Segment::Root root (rotate);

  bend.set_angle (1.3);
  rotate.set_angle (std::numbers::pi/2.0);

  std::cout << "tip position: " << root.tip_position() << "\n";
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
