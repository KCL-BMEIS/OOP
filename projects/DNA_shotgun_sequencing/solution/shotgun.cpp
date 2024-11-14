#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  if (args.size() < 3) {
    std::cerr << "ERROR: missing arguments - expected 2 arguments: input_fragments output_sequence\n";
    return 1;
  }
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  std::vector<std::string> fragments;
  std::string frag;
  while (infile >> frag)
    fragments.push_back (frag);

  if (fragments.empty()) {
    std::cerr << "ERROR: file \"" << args[1] << "\" contains no fragments - aborting\n";
    return 1;
  }

  std::cerr << "read " << fragments.size() << " fragments\n";

  double sum = 0.0;
  std::string::size_type min = fragments[0].size();
  std::string::size_type max = fragments[0].size();
  for (const auto& f : fragments) {
    sum += f.size();
    min = std::min (min, f.size());
    max = std::max (max, f.size());
  }
  std::cerr << "mean fragment length: " << sum/fragments.size() << ", range [ " << min << " " << max << " ]\n";


  unsigned int size_of_longest = 0;
  unsigned int index_of_longest = 0;
  for (unsigned int n = 0; n < fragments.size(); ++n) {
    if (fragments[n].size() > size_of_longest) {
      index_of_longest = n;
      size_of_longest = fragments[n].size();
    }
  }
  std::string sequence = fragments[index_of_longest];
  std::cerr << "initial sequence has size " << sequence.size() << "\n";


  std::cerr << "writing sequence to file \"" << args[2] << "\"...\n";
  std::ofstream outfile (args[2]);
  if (!outfile) {
    std::cerr << "ERROR: failed to open output file \"" << args[2] << "\" - aborting\n";
    return 1;
  }
  outfile << sequence << "\n";
  if (!outfile) {
    std::cerr << "ERROR: error occurred while writing to output file \"" << args[2] << "\" - aborting\n";
    return 1;
  }

  return 0;
}
