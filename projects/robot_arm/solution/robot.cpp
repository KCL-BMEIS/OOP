#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numbers>
#include <chrono>
#include <thread>

#include "debug.h"
#include "load_parameters.h"
#include "segment/tip.h"
#include "segment/straight.h"
#include "segment/bend.h"
#include "segment/rotate.h"
#include "segment/root.h"


// This function contains our program's core functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 2)
    throw std::runtime_error ("expected parameter file as first argument");

  // set up robot arm:

  Segment::Tip tip (10.0);
  Segment::Bend bend3 (tip, 6.0);
  Segment::Straight straight3 (bend3, 15.0);
  Segment::Rotate rotate3 (straight3, 5.0);
  Segment::Bend bend2 (rotate3, 8.0);
  Segment::Straight straight2 (bend2, 20.0);
  Segment::Rotate rotate2 (straight2, 5.0);
  Segment::Bend bend1 (rotate2, 10.0);
  Segment::Straight straight1 (bend1, 30.0);
  Segment::Rotate rotate1 (straight1, 5.0);
  Segment::Root root (rotate1);

  // read parameter list:
  auto params = load_parameters (args[1]);

  std::vector<Point> positions;

  for (const auto& p : params) {

    rotate1.set_angle (p[0]);
    bend1.set_angle (p[1]);
    rotate2.set_angle (p[2]);
    bend2.set_angle (p[3]);
    rotate3.set_angle (p[4]);
    bend3.set_angle (p[5]);

    positions.push_back (root.tip_position());
    std::cout << positions.back() << "\n";
  }

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
