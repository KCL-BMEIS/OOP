#pragma once

#include <iostream>
#include <string>

namespace debug {
  inline bool verbose = false;

    inline void log (const std::string& message) {
    if (verbose)
      std::cerr << "[DEBUG] " << message << "\n";
  }

}

