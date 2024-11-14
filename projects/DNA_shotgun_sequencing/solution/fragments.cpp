#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "fragments.h"

std::vector<std::string> load_fragments (const std::string& filename)
{
  std::cerr << "reading fragments from file \"" << filename << "\"...\n";

  std::ifstream infile (filename);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << filename << "\" - aborting\n";
    std::exit (1);
  }

  std::vector<std::string> fragments;
  std::string frag;
  while (infile >> frag)
    fragments.push_back (frag);

  if (fragments.empty()) {
    std::cerr << "ERROR: file \"" << filename << "\" contains no fragments - aborting\n";
    std::exit (1);
  }

  std::cerr << "read " << fragments.size() << " fragments\n";

  return fragments;
}




void fragment_statistics (const std::vector<std::string>& fragments)
{
  double sum = 0.0;
  std::string::size_type min = fragments[0].size();
  std::string::size_type max = fragments[0].size();
  for (const auto& f : fragments) {
    sum += f.size();
    min = std::min (min, f.size());
    max = std::max (max, f.size());
  }
  std::cerr << "mean fragment length: " << sum/fragments.size() << ", range [ " << min << " " << max << " ]\n";
}




void write_sequence (const std::string& filename, const std::string& sequence)
{
  std::cerr << "writing sequence to file \"" << filename << "\"...\n";
  std::ofstream outfile (filename);
  if (!outfile) {
    std::cerr << "ERROR: failed to open output file \"" << filename << "\" - aborting\n";
    std::exit (1);
  }
  outfile << sequence << "\n";
  if (!outfile) {
    std::cerr << "ERROR: error occurred while writing to output file \"" << filename << "\" - aborting\n";
    std::exit (1);
  }
}

