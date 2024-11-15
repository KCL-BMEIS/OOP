#include <iostream>
#include <stdexcept>
#include <string>

#include "overlap.h"
#include "fragments.h"

int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence - this shouldn't happen!");

  std::cerr << "------------------------------------------------------\n";
  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_overlap = 0;

  // Start from the largest overlap, and decrease size of overlap at each
  // iteration. This guarantees we stop as soon as we find the largest overlap:
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    //std::cerr << "  overlap = " << overlap << ": seq " << seq_start << ", fragment " << frag_end << "\n";
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  // We are going to allow the overlap to be negative, in which case it would
  // be interpreted as corresponding to the overlap from the end of the
  // sequence:
  for (int overlap = fragment.size(); overlap > largest_overlap; --overlap) {
    const auto seq_end = sequence.substr(sequence.size() - overlap);
    const auto frag_start = fragment.substr(0, overlap);
    //std::cerr << "  overlap = " << overlap << ": seq " << seq_end << ", fragment " << frag_start << "\n";
    if (seq_end == frag_start) {
      largest_overlap = -overlap;
      break;
    }
  }

  return largest_overlap;
}





void merge (std::string& sequence, const std::string& fragment, const int overlap)
{
  if (overlap < 0) {
    sequence += fragment.substr (-overlap);
  }
  else if (overlap > 0) {
    sequence = fragment.substr (0, fragment.size()-overlap) + sequence;
  }
}

