---
layout: presentation
title: "Week 2, session 2: more string handling, basic debugging"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 2, session 2
## More string handling<br>Basic debugging

---

# Picking up where we left off

We continue working on our [DNA shotgun sequencing
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/DNA_shotgun_sequencing/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/main/projects/DNA_shotgun_sequencing/solution)

.explain-bottom[
Make sure your code is up to date now!
]


---
layout: true

# Computing the overlap

Let's imagine that this is the current estimate of the sequence:
```
CTGAATGCTTGGGCTGAAAGGGCGCGAGACGTATTCCCCGGTTGCAGACG
```
and this is a candidate fragment:
```
CCCTCATCACAACTGAATGCTTGGGCTGAA
```

We could compute the overlap by comparing the overlapping region, starting from
the smallest overlap:

---

---

```
                             `C`TGAATGCTTGGGCTGAAAGGGCGCGAGACGTATTCCCCGGTTGC
CCCTCATCACAACTGAATGCTTGGGCTGA`A`
```

---

```
                             `CT`GAATGCTTGGGCTGAAAGGGCGCGAGACGTATTCCCCGGTTGC
 CCCTCATCACAACTGAATGCTTGGGCTG`AA`
```
---

```
                             `CTG`AATGCTTGGGCTGAAAGGGCGCGAGACGTATTCCCCGGTTGC
  CCCTCATCACAACTGAATGCTTGGGCT`GAA`
```
---

```
                             `CTGA`ATGCTTGGGCTGAAAGGGCGCGAGACGTATTCCCCGGTTGC
   CCCTCATCACAACTGAATGCTTGGGC`TGAA`
```
---

```
                             `CTGAA`TGCTTGGGCTGAAAGGGCGCGAGACGTATTCCCCGGTTGC
    CCCTCATCACAACTGAATGCTTGGG`CTGAA`
```
We have a match with an overlap of 5 bases!
- should we stop now?

---

```
                             `CTGAATGCTTGGGCTGAA`AGGGCGCGAGACGTATTCCCCGGTTGC
                 CCCTCATCACAA`CTGAATGCTTGGGCTGAA`
```
No! If we carry on, we'll find a larger overlap


---
layout: true

# Computing the overlap

A better strategy is to start with the biggest overlap first, and gradually
reduce it
- that way, if we do find a match, we can stop immediately

---

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCGCGAGAC`GTATTCCCCGGTTGC
                             `CCCTCATCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCGCGAGA`CGTATTCCCCGGTTGC
                            C`CCTCATCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCGCGAG`ACGTATTCCCCGGTTGC
                           CC`CTCATCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCGCGA`GACGTATTCCCCGGTTGC
                          CCC`TCATCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCGCG`AGACGTATTCCCCGGTTGC
                         CCCT`CATCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCGC`GAGACGTATTCCCCGGTTGC
                        CCCTC`ATCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGCG`CGAGACGTATTCCCCGGTTGC
                       CCCTCA`TCACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGGC`GCGAGACGTATTCCCCGGTTGC
                      CCCTCAT`CACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGGG`CGCGAGACGTATTCCCCGGTTGC
                     CCCTCATC`ACAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAGG`GCGCGAGACGTATTCCCCGGTTGC
                    CCCTCATCA`CAACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAAG`GGCGCGAGACGTATTCCCCGGTTGC
                   CCCTCATCAC`AACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAAA`GGGCGCGAGACGTATTCCCCGGTTGC
                  CCCTCATCACA`ACTGAATGCTTGGGCTGAA`
```

---

```
                             `CTGAATGCTTGGGCTGAA`AGGGCGCGAGACGTATTCCCCGGTTGC
                 CCCTCATCACAA`CTGAATGCTTGGGCTGAA`
```
Now as soon as we find an overlap, it is guaranteed to be the largest


---
layout: false

# Exercises

- Add a function to compute the overlap between the current sequence and a
  candidate fragment
  - make sure it works for both ends of the string
  - ignore the possibility that fragments might be reversed for now

- Use this function to identify the candidate fragment with the largest overlap
with current sequence

- Add a function to merge this candidate fragment with the current sequence,
given the computed overlap

- Use these functions to iteratively merge candidates fragments until no
overlapping fragments remain

- Check that all unmerged fragments are already contained within the sequence

--

.explain-bottom[
Have a go at implementing code to do this
]


---

# Computing the overlap

We create a header file `overlap.h` to hold our function *declaration*
```
#pragma once

#include <string>

int compute_overlap (const std::string& sequence, const std::string& fragment);
```

---

# Computing the overlap

We create a header file `overlap.h` to hold our function *declaration*
```
#pragma once

#include <string>

`int` compute_overlap (const std::string& sequence, const std::string& fragment);
```
- we return an integer representing the number of bases in the overlap

---

# Computing the overlap

We create a header file `overlap.h` to hold our function *declaration*
```
#pragma once

#include <string>

int `compute_overlap` (const std::string& sequence, const std::string& fragment);
```
- we return an integer representing the number of bases in the overlap
- we chose a suitable name for our function that clearly states its purpose

---

# Computing the overlap

We create a header file `overlap.h` to hold our function *declaration*
```
#pragma once

#include <string>

int compute_overlap (`const std::string& sequence, const std::string& fragment`);
```
- we return an integer representing the number of bases in the overlap
- we chose a suitable name for our function that clearly states its purpose
- we pass both the sequence and candidate fragment as const references to
  strings

---

# Computing the overlap

We create a header file `overlap.h` to hold our function *declaration*
```
#pragma once

*#include <string>

int compute_overlap (const std::string& sequence, const std::string& fragment);
```
- we return an integer representing the number of bases in the overlap
- we chose a suitable name for our function that clearly states its purpose
- we pass both the sequence and candidate fragment as const references to
  strings
- we need to `#include` the `<string>` header since we are using `std::string`

---

# Computing the overlap

We create a header file `overlap.h` to hold our function *declaration*
```
*#pragma once

#include <string>

int compute_overlap (const std::string& sequence, const std::string& fragment);
```
- we return an integer representing the number of bases in the overlap
- we chose a suitable name for our function that clearly states its purpose
- we pass both the sequence and candidate fragment as const references to
  strings
- we need to `#include` the `<string>` header since we are using `std::string`
- we use the `#pragma once` directive to avoid double-inclusion 

---

# Computing the overlap

Next, we create the `overlap.cpp` file to hold our function *definition*
```
#include <iostream>
#include <stdexcept>
#include <string>

#include "overlap.h"

int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  // this is where our code will go
}
```

---

# Computing the overlap

Next, we create the `overlap.cpp` file to hold our function *definition*
```
#include <iostream>
#include <stdexcept>
#include <string>

#include "overlap.h"

*int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  // this is where our code will go
}
```

- we need to replicate the function declaration, making sure it matches exactly

---

# Computing the overlap

Next, we create the `overlap.cpp` file to hold our function *definition*
```
#include <iostream>
#include <stdexcept>
#include <string>

*#include "overlap.h"

int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  // this is where our code will go
}
```

- we need to replicate the function declaration, making sure it matches exactly
- we need to `#include` the matching header file

---

# Computing the overlap

Next, we create the `overlap.cpp` file to hold our function *definition*
```
*#include <iostream>
*#include <stdexcept>
*#include <string>

#include "overlap.h"

int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  // this is where our code will go
}
```

- we need to replicate the function declaration, making sure it matches exactly
- we need to `#include` the matching header file
- we need to `#include` the system headers for the functionality we will be
  using

---

# Computing the overlap

Next, we create the `overlap.cpp` file to hold our function *definition*
```
#include <iostream>
#include <stdexcept>
#include <string>

#include "overlap.h"

int compute_overlap (const std::string& sequence, const std::string& fragment)
{
* // this is where our code will go
}
```

- we need to replicate the function declaration, making sure it matches exactly
- we need to `#include` the matching header file
- we need to `#include` the system headers for the functionality we will be
  using
- now we can worry about what will go in the body of our function

---

# Computing the overlap

Now we fill out the body of our `compute_overlap()` function
```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  ...

  return 0;
}
```

---

# Computing the overlap

Now we fill out the body of our `compute_overlap()` function
```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
* if (fragment.size() > sequence.size())
*   throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  ...

  return 0;
}
```
- always check any assumptions and expectations upfront &ndash;
  this can save you a lot of frustration later...

---

# Computing the overlap

Now we fill out the body of our `compute_overlap()` function
```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

* std::cerr << "sequence is \"" << sequence << "\"\n";
* std::cerr << "trying fragment \"" << fragment << "\"\n";

  ...

  return 0;
}
```
- always check any assumptions and expectations upfront &ndash;
  this can save you a lot of frustration later...
- when in development mode, don't hesitate to display lots of information, it
  will often alert you to where things might be going wrong.


---

# Computing the overlap

Now we fill out the body of our `compute_overlap()` function
```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  ...

* return 0;
}
```
- always check any assumptions and expectations upfront &ndash;
  this can save you a lot of frustration later...
- when in development mode, don't hesitate to display lots of information, it
  will often alert you to where things might be going wrong.
- we need to return an integer, so let's return a value of zero (no overlap) by
  default

---

# Computing the overlap

Now we fill out the body of our `compute_overlap()` function
```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

* ...

  return 0;
}
```
- always check any assumptions and expectations upfront &ndash;
  this can save you a lot of frustration later...
- when in development mode, don't hesitate to display lots of information, it
  will often alert you to where things might be going wrong.
- we need to return an integer, so let's return a value of zero (no overlap) by
  default

.explain-bottom[
Now we can focus on what happens here...
]

---

# Computing the overlap

```
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
      return overlap;
  }
```

---

# Computing the overlap

```
* for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
      return overlap;
* }
```
We iterate over the range of valid overlaps:
- starting from the *largest* possible overlap (the size of the candidate
  fragment)
- *reducing* the size of the overlap at each iteration
- until the overlap is zero

---

# Computing the overlap

```
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
*   const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
      return overlap;
  }
```
We iterate over the range of valid overlaps:
- starting from the *largest* possible overlap (the size of the candidate
  fragment)
- *reducing* the size of the overlap at each iteration
- until the overlap is zero

We extract the part of the current sequence that corresponds to that overlap
- to do this, we use the string [`substr()` method](https://www.geeksforgeeks.org/substring-in-cpp/)

---

# Computing the overlap

```
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
*   const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
      return overlap;
  }
```
We iterate over the range of valid overlaps:
- starting from the *largest* possible overlap (the size of the candidate
  fragment)
- *reducing* the size of the overlap at each iteration
- until the overlap is zero

We extract the part of the current sequence that corresponds to that overlap
- to do this, we use the string [`substr()` method](https://www.geeksforgeeks.org/substring-in-cpp/)
- and likewise for the candidate sequence &ndash; though it is now the *end* of
  the string

---

# Computing the overlap

```
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
*   if (seq_start == frag_end)
*     return overlap;
  }
```
We iterate over the range of valid overlaps:
- starting from the *largest* possible overlap (the size of the candidate
  fragment)
- *reducing* the size of the overlap at each iteration
- until the overlap is zero

We extract the part of the current sequence that corresponds to that overlap
- to do this, we use the string [`substr()` method](https://www.geeksforgeeks.org/substring-in-cpp/)
- and likewise for the candidate sequence &ndash; though it is now the *end* of
  the string

Finally, we check whether both substrings match
- If so, we can immediately return the size of the current overlap


---

# Computing the overlap

```
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = `fragment.substr(fragment.size()-overlap)`;
    if (seq_start == frag_end)
      return overlap;
  }
```
We iterate over the range of valid overlaps:
- starting from the *largest* possible overlap (the size of the candidate
  fragment)
- *reducing* the size of the overlap at each iteration
- until the overlap is zero

We extract the part of the current sequence that corresponds to that overlap
- to do this, we use the string [`substr()` method](https://www.geeksforgeeks.org/substring-in-cpp/)
- and likewise for the candidate sequence &ndash; though it is now the *end* of
  the string

Finally, we check whether both substrings match
- If so, we can immediately return the size of the current overlap

.explain-bottom[
Note that in this call to `substr()`, we only provided one argument, whereas we
had provided two arguments in the previous call (position and length of the
substring).

<br>
This is because the arguments for this call have been given *default values*:
- if unspecified, the position is zero, and the length is the maximum value
possible.
- we will cover [default arguments in
  C++](https://www.geeksforgeeks.org/default-arguments-c/) later in the course.
]





---

# Computing the overlap

Here is our function definition in full:

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
      return overlap;
  }

  return 0;
}
```

---

# Exercises

- Add a function to compute the overlap between the current sequence and a
  candidate fragment
  - **make sure it works for both ends of the string**
  - ignore the possibility that fragments might be reversed for now

- Use this function to identify the candidate fragment with the largest overlap
with current sequence

- Add a function to merge this candidate fragment with the current sequence,
given the computed overlap

- Use these functions to iteratively merge candidates fragments until no
overlapping fragments remain

- Check that all unmerged fragments are already contained within the sequence


---

# Computing the overlap

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
      return overlap;
  }

  return 0;
}
```

.explain-bottom[
We need to modify our code to also check for overlap at the other end of the
sequence
]

---

# Computing the overlap

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end)
*     return overlap;
  }

  return 0;
}
```
.explain-bottom[
We can no longer return the overlap here, since there may be a larger overlap
at the other end. 

<br>
We need to check both ends, and return the larger of the two.
]

---

# Computing the overlap

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

* int largest_overlap = 0;
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  ...
```
.explain-top[
To do this, we declare an integer variable to hold the value of the largest
overlap detected so far
]

---

# Computing the overlap

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_overlap = 0;
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
*   if (seq_start == frag_end) {
*     largest_overlap = overlap;
*     break;
*   }
  }

  ...
```
.explain-top[
Now, instead of returning the value of the current overlap, we record this
value, and use the `break` statement to stop the enclosing loop and
proceed with the following code.
]

---

# Computing the overlap

```
    ...
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  for (int overlap = fragment.size(); overlap > largest_overlap; --overlap) {
    const auto seq_end = sequence.substr(sequence.size() - overlap);
    const auto frag_start = fragment.substr(0, overlap);
    if (seq_end == frag_start) {
      largest_overlap = -overlap;
      break;
    }
  }

  return largest_overlap;
}
```

--

.explain-top[
We now check the other end of the string, using the same idea as before
&ndash; with a few differences
]

---

# Computing the overlap

```
    ...
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  for (int overlap = fragment.size(); overlap > largest_overlap; --overlap) {
*   const auto seq_end = sequence.substr(sequence.size() - overlap);
*   const auto frag_start = fragment.substr(0, overlap);
    if (seq_end == frag_start) {
      largest_overlap = -overlap;
      break;
    }
  }

  return largest_overlap;
}
```

.explain-top[
This time, we extract the substrings from the *opposite* ends of both the current
sequence and the candidate fragment
]

---

# Computing the overlap

```
    ...
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  for (int overlap = fragment.size(); overlap > `largest_overlap`; --overlap) {
    const auto seq_end = sequence.substr(sequence.size() - overlap);
    const auto frag_start = fragment.substr(0, overlap);
    if (seq_end == frag_start) {
      largest_overlap = -overlap;
      break;
    }
  }

  return largest_overlap;
}
```

.explain-top[
There is no point iterating all the way to zero, since we already know the size
of the largest overlap from the previous loop
- there is no point checking smaller overlaps!
]

---

# Computing the overlap

```
    ...
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  for (int overlap = fragment.size(); overlap > largest_overlap; --overlap) {
    const auto seq_end = sequence.substr(sequence.size() - overlap);
    const auto frag_start = fragment.substr(0, overlap);
    if (seq_end == frag_start) {
*     largest_overlap = -overlap;
      break;
    }
  }

  return largest_overlap;
}
```

.explain-top[
... and we record the overlap as a *negative* value.
- this will be our way of representing an overlap at the tail end of the
  sequence
- this is already guaranteed to be the largest overlap, since we are only
  considering overlaps larger than the previous check in this `for` loop
]

---

# Computing the overlap

```
    ...
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  for (int overlap = fragment.size(); overlap > largest_overlap; --overlap) {
    const auto seq_end = sequence.substr(sequence.size() - overlap);
    const auto frag_start = fragment.substr(0, overlap);
    if (seq_end == frag_start) {
      largest_overlap = -overlap;
      break;
    }
  }

* return largest_overlap;
}
```

.explain-top[
Finally, we end by returning the largest overlap recorded in both loops
]

---

# Exercises

- Add a function to compute the overlap between the current sequence and a
  candidate fragment
  - make sure it works for both ends of the string
  - ignore the possibility that fragments might be reversed for now

- **Use this function to identify the candidate fragment with the largest overlap
with current sequence**

- Add a function to merge this candidate fragment with the current sequence,
given the computed overlap

- Use these functions to iteratively merge candidates fragments until no
overlapping fragments remain

- Check that all unmerged fragments are already contained within the sequence


---

# Identifying fragment with the largest overlap

```
  ...

  int biggest_overlap = 0;
  int fragment_with_biggest_overlap = -1;
  for (int n = 0; n < fragments.size(); ++n) {
    const auto overlap = compute_overlap (sequence, fragments[n]);
    if (std::abs (biggest_overlap) < std::abs (overlap)) {
      biggest_overlap = overlap;
      fragment_with_biggest_overlap = n;
    }
  }

  if (fragment_with_biggest_overlap >= 0)
    std::cerr << "fragment with biggest overlap is at index " 
      << fragment_with_biggest_overlap
      << ", overlap = " << biggest_overlap << "\n";

  write_sequence (args[2], sequence);
}

```

---

# Identifying fragment with the largest overlap

```
  ...

  int biggest_overlap = 0;
  int fragment_with_biggest_overlap = -1;
* for (int n = 0; n < fragments.size(); ++n) {
    const auto overlap = compute_overlap (sequence, fragments[n]);
    if (std::abs (biggest_overlap) < std::abs (overlap)) {
      biggest_overlap = overlap;
      fragment_with_biggest_overlap = n;
    }
* }

  if (fragment_with_biggest_overlap >= 0)
    std::cerr << "fragment with biggest overlap is at index " 
      << fragment_with_biggest_overlap
      << ", overlap = " << biggest_overlap << "\n";

  write_sequence (args[2], sequence);
}

```
.explain-bottom[
We iterate over all candidate fragments
- we use a regular `for` loop (rather than a range-based `for` loop) since we
  want to keep track of the *index* of the fragment
]

---

# Identifying fragment with the largest overlap

```
  ...

  int biggest_overlap = 0;
  int fragment_with_biggest_overlap = -1;
  for (int n = 0; n < fragments.size(); ++n) {
*   const auto overlap = compute_overlap (sequence, fragments[n]);
    if (std::abs (biggest_overlap) < std::abs (overlap)) {
      biggest_overlap = overlap;
      fragment_with_biggest_overlap = n;
    }
  }

  if (fragment_with_biggest_overlap >= 0)
    std::cerr << "fragment with biggest overlap is at index " 
      << fragment_with_biggest_overlap
      << ", overlap = " << biggest_overlap << "\n";

  write_sequence (args[2], sequence);
}

```

.explain-bottom[
We use our new function to compute the overlap for the current candidate
fragment
- we store the result in a *block scope* variable
- we declare this variable `const` since we have no intention of modifying it
  any further 
  - this is good practice as we can rely on the compiler to check that we do
    not trip ourselves up!
- we allow the compiler to deduce the type using the `auto` keyword
  - the compiler will assume we want to use the type returned by
    `compute_overlap()`
  - we could just easily have declared it as `int`...
]

---

# Identifying fragment with the largest overlap

```
  ...

* int biggest_overlap = 0;
  int fragment_with_biggest_overlap = -1;
  for (int n = 0; n < fragments.size(); ++n) {
    const auto overlap = compute_overlap (sequence, fragments[n]);
*   if (std::abs (biggest_overlap) < std::abs (overlap)) {
      biggest_overlap = overlap;
      fragment_with_biggest_overlap = n;
    }
  }

  if (fragment_with_biggest_overlap >= 0)
    std::cerr << "fragment with biggest overlap is at index " 
      << fragment_with_biggest_overlap
      << ", overlap = " << biggest_overlap << "\n";

  write_sequence (args[2], sequence);
}

```
.explain-bottom[
We can then compare the extracted portions using the `==` 
*comparison operator*

<br>
If they match, we can immediately return the value of the overlap
]


.explain-bottom[
We check whether the overlap for the current fragment exceeds the biggest
overlap we have detected so far
- since we have allowed overlaps to be negative, we need to take the *absolute*
  value of the overlaps prior to comparison
- we also need to make sure we have declared a variable to hold the value of
  the biggest overlap detected so far, and initialise it with the smallest
value possible
]

---

# Identifying fragment with the largest overlap

```
  ...

  int biggest_overlap = 0;
* int fragment_with_biggest_overlap = -1;
  for (int n = 0; n < fragments.size(); ++n) {
    const auto overlap = compute_overlap (sequence, fragments[n]);
    if (std::abs (biggest_overlap) < std::abs (overlap)) {
*     biggest_overlap = overlap;
*     fragment_with_biggest_overlap = n;
    }
  }

  if (fragment_with_biggest_overlap >= 0)
    std::cerr << "fragment with biggest overlap is at index " 
      << fragment_with_biggest_overlap
      << ", overlap = " << biggest_overlap << "\n";

  write_sequence (args[2], sequence);
}

```
.explain-bottom[
If we make through to the last iteration, there is no match, so we simply
`return 0;`
]



.explain-bottom[
If the overlap is the biggest so far, record its value, and the index of the
corresponding fragment
- to do this, we also need to declare a variable to hold the index of the
  corresponding fragment
- we also need to initialise the value of this index. In this case, it's best
  to assign it an *invalid* value (for example, a negative index)
]

---

# Exercises

- Add a function to compute the overlap between the current sequence and a
  candidate fragment
  - make sure it works for both ends of the string
  - ignore the possibility that fragments might be reversed for now

- Use this function to identify the candidate fragment with the largest overlap
with current sequence

- **Add a function to merge this candidate fragment with the current sequence,
given the computed overlap**

- Use these functions to iteratively merge candidates fragments until no
overlapping fragments remain

- Check that all unmerged fragments are already contained within the sequence


---

# Merge fragment with current sequence

Add our function *declaration* to `overlap.h`:
```
void merge (std::string& sequence, const std::string& fragment, const int overlap);
```

Add our function *definition* to `overlap.cpp`:
```
void merge (std::string& sequence, const std::string& fragment, const int overlap)
{
  if (overlap < 0) {
    sequence += fragment.substr (-overlap);
  }
  else if (overlap > 0) {
    sequence = fragment.substr (0, fragment.size()-overlap) + sequence;
  }
}
```

--
.explain-bottom[
- we *concatenate* the non-overlapping portion of the fragment with the
  sequence
- the *sign* of overlap indicates which end the overlap corresponds to
  - hence whether to *append* or *prepend* the fragment to the sequence
]

---

# Merge fragment with current sequence

Use `merge()` function in `main()`:

```
  ...

  if (fragment_with_biggest_overlap >= 0) {
    std::cerr << "fragment with biggest overlap is at index " 
      << fragment_with_biggest_overlap
      << ", overlap = " << biggest_overlap << "\n";

*   merge (sequence, fragments[fragment_with_biggest_overlap], biggest_overlap);
  }

  std::cerr << "final sequence has length " << sequence.size() << "\n";
  write_sequence (args[2], sequence);
}
```

---

# Exercises

- Add a function to compute the overlap between the current sequence and a
  candidate fragment
  - make sure it works for both ends of the string
  - ignore the possibility that fragments might be reversed for now

- Use this function to identify the candidate fragment with the largest overlap
with current sequence

- Add a function to merge this candidate fragment with the current sequence,
given the computed overlap

- **Use these functions to iteratively merge candidates fragments until no
overlapping fragments remain**

- Check that all unmerged fragments are already contained within the sequence

---

# Iteratively merge fragments into sequence

**TODO**

---

# Exercises

- Add a function to compute the overlap between the current sequence and a
  candidate fragment
  - make sure it works for both ends of the string
  - ignore the possibility that fragments might be reversed for now

- Use this function to identify the candidate fragment with the largest overlap
with current sequence

- Add a function to merge this candidate fragment with the current sequence,
given the computed overlap

- Use these functions to iteratively merge candidates fragments until no
overlapping fragments remain

- **Check that all unmerged fragments are already contained within the sequence**

---

# Check all unmerged fragments are already in sequence

**TODO**

---
name: cmdline_options

class: section

# Command-line options

## Requesting additional debugging information

---

# Command-line options

We've already seen examples of command-line options in other commands:
```
$ ls `-l`
$ g++ `-std=c++20` shotgun.cpp `-o` shotgun
```

--

The purpose of a command-line option is typically to *alter the behaviour* of the
command in some way

--

Can we use that to request additional debugging information?
- it is a common practice for commands to provide an option to enable *verbose
  mode*
- this is really useful to figure out exactly what is going wrong when running
  your program!

--

A typical option to enable verbose mode is `-v`
- let's try to implement this in our project

---

# Command-line options

There are many ways to handle command-line options
- indeed, there are [many *libraries* dedicated to command-line
  parsing](https://hackingcpp.com/cpp/libs/cmdline_args_parsing.html)...

--

Have a go at implementing this simple approach to detect the `-v` option:
- start by checking whether the option has been provided in the arguments list
- if it has, then:
  - take whatever action is appropriate (e.g. set a `verbose` variable `true`)
  - remove that option from the argument list
- process your arguments as previously

--

.explain-bottom[
Hint: there are many ways of doing this, but you may find the new C++20
[`std::erase()`](https://en.cppreference.com/w/cpp/container/vector/erase2)
function very useful here (if you can work out how to use it from the
documentation...)
]

---

# Detecting the `-v` option

Possible solution:

```
...

void run (std::vector<std::string>& args)
{
* bool verbose = std::erase (args, "-v");

  if (args.size() < 3)
    throw std::runtime_error ("expected 2 arguments: input_fragments output_sequence");

  ...
}
```

--

`std::erase()` will erase any occurence of the value (`"-v"`) from the
container (`args`), and return the *number* of occurences removed. 
- if no `-v` in the argument list, the return value is zero, which equates to
  `false` when assigned to a `bool`
- if there were *any* occurences of `-v`, a non-zero value will be returned,
  which equates to `true`

---

# Global variables

One problem with the previous solution is that `verbose` is a *local* variable
- it is only accessible within the `run()` function

--

If we call other functions, the code in these functions will have no knowledge
or access to our `verbose` variable

--

We could pass our `verbose` variable as an argument to all relevant functions
- but this *very* rapidly becomes cumbersome and impractical

--

A better option in this particular case is to use a *global* variable


---

# Global variables

A global variable is declared outside of any function and is accessible
from anywhere in the code
- provided its *declaration* is encountered before the point of use within each
  translation unit

--

 
In general, global variables are *strongly* discouraged
- they introduce scope for state changes that may affect how different part of
  the program operate, and make it difficult to ensure predictable behaviour
(see e.g. [this
article](https://embeddedartistry.com/fieldatlas/the-problems-with-global-variables/)
for details)

--

There are however cases where they make sense: 
- for constants (in which case they would also be declared `const`)
--
- when they represent a truly unique entity
  - examples include `std::cout`, `std::cerr`: there can only be one of each in
    any program
  - in our case, there can only ever be one setting representing verbose mode!

---

# Global variables

We could declare our global variable like this:

```
...

*bool verbose = false;

...

void run (std::vector<std::string>& args)
{
* verbose = std::erase (args, "-v");

  ...
```

But there are still issues with this:
- this is declared within our `shotgun.cpp` file &ndash; it won't be accessible
  in our other `cpp` files
  - they won't be in the same *translation unit*
--
- what happens if another function declares their own local variable called
  `verbose`?

---
name: scope

# Variable scope

The scope of a variable determines its lifetime and where it can be accessed
from. 

**Global scope**

- Variables are *instantiated* (created) before `main()` starts, and destroyed
  after `main()` returns
- they are accessible from any part of the code
  - provided their declaration occurs before their point of use in the current
    translation unit

--

**Function scope**

- Variables are instantiated when declared, and
  destroyed when the function returns
- They are only accessible within their enclosing function, after their
  declaration
- Each invocation of a given function will have its own version of its local
  variables

--

**Block scope**
- Block scope means within a compound statement (e.g. within a `for` loop or `if` statement)
- Variables are instantiated when declared, and destroyed at the end of the
  block
- They are only accessible within their block, after their declaration


---
name: shadowing

# Variable shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <= global scope

...

void compute ()
{
  int count = 10;   // <= function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <= block scope
    std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

--

This is perfectly legal in C++!

---

# Variable shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
*int count = 0;   // <= global scope

...

void compute ()
{
* int count = 10;   // <= function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <= block scope
    std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-bottom[
The variable at function scope *hides* the variable of the same name at
global scope
- at this point, any reference to `count` is assumed to refer to the *function scope* variable
- the global scope version of `count` still exists, but is no longer accessible
  by that name
]

---

# Variable shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <= global scope

...

void compute ()
{
* int count = 10;   // <= function scope
  ...

* for (int count = 0; count < 20; ++count) {    // <= block scope
    std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-top[
Similarly, the variable at block scope *hides* the variable of the same name at
function scope
- at this point, any reference to `count` is assumed to refer to the *block scope* variable
- the function and global scope versions of `count` still exist, but are no longer accessible
  by that name
]

---

# Variable shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <= global scope

...

void compute ()
{
  int count = 10;   // <= function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <= block scope
*   std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-top[
This line will print the *block scope* version of `count`
]

---

# Variable shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <= global scope

...

void compute ()
{
  int count = 10;   // <= function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <= block scope
    std::cout << count << "\n";
    ...
  }
* std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-top[
... but this line will print the *function scope* version of `count`, since it
is outside the block
- the block scope version has been destroyed by that point
]


---

# Variable shadowing


Variable shadowing allows a function to use local variables without worrying about
whether some other global variable exists elsewhere with the same name

--

... but it can also lead to subtle errors!

--

[Name collisions](https://en.wikipedia.org/wiki/Name_collision) are a general
problem in computing
- many projects will rely on functionality provided by other projects
- difficult to avoid using the same names across different projects!

--

Most of these problems can be avoided by:
- not using global variables in the first place!
--
- using a dedicated *C++ namespace*


---
name: namespace

class: section

# C++ namespaces

---

# What is a namespace?

A namespace is essentially a *named scope* for your function and variable
declarations

--

We have already been using a namespace from the start: the `std` namespace
- this namespace is where all the functionality provided by the C++ standard is
  declared

--

.columns[
.col[
```
std::vector
```
- the vector class (a *type*) declared within the `std` namespace
]
.col[
```
std::cout
```
- a variable (actually of type `std::ostream`) called `cout`
  declared within the `std` namespace
]
]

---

# What is a namespace?

A namespace is essentially a *named scope* for your function and variable
declarations

We have been using a namespace from the start: the `std` namespace
- this namespace is where all the functionality provided by the C++ standard is
  declared

.columns[
.col[
```
`std`::vector
```
- the vector class (a *type*) declared within the `std` namespace
]
.col[
```
`std`::cout
```
- a variable (actually of type `std::ostream`) called `cout`
  declared within the `std` namespace
]
]

- these are both declared within the `std` namespace
---

# What is a namespace?

A namespace is essentially a *named scope* for your function and variable
declarations

We have been using a namespace from the start: the `std` namespace
- this namespace is where all the functionality provided by the C++ standard is
  declared

.columns[
.col[
```
std`::`vector
```
- the vector class (a *type*) declared within the `std` namespace
]
.col[
```
std`::`cout
```
- a variable (actually of type `std::ostream`) called `cout`
  declared within the `std` namespace
]
]

- these are both declared within the `std` namespace
- accessing members of a namespace is done with the [*scope resolution
  operator*](https://www.geeksforgeeks.org/scope-resolution-operator-in-c/)
(`::`)

---

# Why would we want to use namespaces?

The main purpose of C++ namespace is:
- to organise your code into logical units
- to avoid name collisions

--

For example, we may very well want to declare a variable or function called
`count()` 
- but there is already a [C++ STL `count()`
  algorithm](https://www.geeksforgeeks.org/std-count-cpp-stl/)!

Thankfully, it is declared within the `std` namespace
- we can declare our variable or function `count` without the risk of name
  collisions with `std::count()`!

---

# Declaring namespaces

Declaring variables or functions within a namespace is simply a matter of
declaring them *within the scope of our namespace*. 

--

For example:
```
namespace debug {

  bool verbose = false;

}
```

This declares our variable `verbose` to be within the `debug` namespace
- this also implicitly declares the `debug` namespace if it hadn't already been
  encountered

---

# Working with namespaces

Any code also declared within our `debug` namespace can already access our
`verbose` variable directly.

--

When accessing our variable outside of the `debug` namespace, we can refer to
it using its *fully qualified name*:
```
if (debug::verbose)
  ...
```

--

Alternatively, we can selectively bring one identifier (variable or function)
into the current scope with the `using` declaration:
```
using debug::verbose;

...

if (verbose)
  ...
```

---

# Working with namespaces

We can also bring *all* identifiers declared in a namespace into the current scope with the `using namespace` declaration:
```
using namespace debug;

...

if (verbose)
  ...
```

--

The `using namespace` declaration can be problematic
- the general recommendation is to avoid its use
- especially at *global scope*

--

It is much better to use the fully qualified name, or if it really helps code
readability, use the selective `using` declaration for the specific identifiers you
  need
- and only use it at *function* or *block* scope


---

# The problem with `using namespace std;`

In spite of the general recommendation to avoid blanket `using namespace`
declarations, you will find that many (if not most) C++ tutorials make use of
this declaration from the very beginning, starting at 'hello world':
```
#include <iostream>

*using namespace std;

int main() {
  cout << "Hello World!\n";
  return 0;
}
```

--

This brings *everything* declared within the `std` namespace into the *global* scope
- this helps to keep the code cleaner by avoiding the need for
  `std::` as a prefix for `std::cerr`, `std::vector`, `std::string`, ...
- it makes it a bit easier when getting started with C++


---

# The problem with `using namespace std;`

So why do we not follow this convention on this course?
- because [its use is considered bad practice](https://www.geeksforgeeks.org/using-namespace-std-considered-bad-practice/)
--
- on this course, we try to teach best practice from the outset so you pick up
  the right habits

--

In general, the `using namespace` declaration is not recommended
- it bring *everything* from that namespace into the current scope
- *including* variables or functions you might not have known about!
- it negates the name collision benefits that C++ namespaces were meant to
  address!

--

It is particularly bad practice to make use of `using namespace` declarations
at global scope within header files
- it's acceptable to use `using namespace` within your own `cpp` files
  - it would still not be considered good practice!
  - but you can manage name collisions within your own project
--
- but header files are supposed to be used by other code!
  - any such global declaration will *pollute* the namespace of any code that
    `#include`s your header
  - it will affect the entire *translation unit* from the point your header is
    `#include`d

---

# Working with namespaces

For the reasons outlined in the previous slides, we recommend to always use the
*fully qualified name* to access members of a namespace

--

Coming back to our project, we can declare our `verbose` variable within a new
`debug` namespace to avoid name collisions
```
namespace debug {
  bool verbose = false;
}
```
and refer to this variable by its fully qualified name: `debug::verbose`

--

But we still need to work out *where* to declare this variable

---

# Working with global variables

As previously mentioned, our `debug::verbose` variable must be *declared* prior
to its point of use in any *translation unit* where it is needed
- this means it needs to be *declared* in a header file

--

Let's create a header file `debug.h` to hold this variable:
```
#pragma once

namespace debug {
  bool verbose = false;
}
```

--

We can now `#include` it in `shotgun.cpp`, `fragments.h` and `overlap.cpp`

--

.explain-bottom[
Have a go at implementing these changes in your code
]

---

# Working with global variables

When trying to do this, you will most likely have encountered errors of this nature:
```
/usr/bin/ld: fragments.o:(.bss+0x0): multiple definition of `debug::verbose'; 
    shotgun.o:(.bss+0x0): first defined here
/usr/bin/ld: overlap.o:(.bss+0x0): multiple definition of `debug::verbose'; 
    shotgun.o:(.bss+0x0): first defined here
collect2: error: ld returned 1 exit status
```

--

The issue is that we have declared and *implicitly defined* our
`debug::verbose` variable once per *translation unit*
- we now have 3 versions of the same *global* variable, each independently listed in the
  object files `shotgun.o`, `fragments.o` and `overlap.o`
--
- this causes an error at the *linker stage*, when the contents of all the
  compiled object files are brought together to form the final executable:
  which version is the right one to use?

--

There are 2 ways to get around this:
- ensure the variable is *only declared* in the header, and provide a *single*
  definition in a separate `cpp` file
- tell the compiler to allow multiple definitions of this variable

---

# Working with global variables

**First approach:**

Use the [`extern`
keyword](https://www.geeksforgeeks.org/understanding-extern-keyword-in-c/) in
`debug.h` to make it clear that we are *only declaring* our variable at this
point:
```
#pragma once

namespace debug {
  `extern` bool verbose;
}
```

--

and place the full definition and initialisation in a new file `debug.cpp`:
```
#include "debug.h"

namespace debug {
  bool verbose = false;
}
```

---
name: inline_variable

# Working with global variables

**Second approach (much simpler):**

Use the `inline` keyword in our `debug.h` header file to allow multiple definitions 
of the same variable to be provided across multiple translation units:
```
#pragma once

namespace debug {
  `inline` bool verbose = false;
}
```
We do not need an additional `cpp` file in this case, and the initial value can
now be specified at the same time

--

Note that [this use of the `inline` keyword was introduced in the C++17 version
of the standard](https://www.geeksforgeeks.org/cpp-17-inline-variables/)

--

.explain-bottom[
Let's go ahead and use the `inline` keyword in our project
]

---

# Enabling the verbose option

We now have all the pieces required to implement our verbose option
- we add the `debug.h` header file as per the previous slide
--
- in `main()`:
  - we use the `std::erase()` call to detect and handle the `-v` option
  - and set `debug::verbose` to `true` if detected
  - we do this *before* any attempt at using the command-line arguments
--
- everywhere else:
  - `#include "debug.h"` so the `debug::verbose` variable is declared at the
    point of use
  - check if `debug::verbose` is `true`, and if so print out appropriate information 

--

For example, in `fragments.cpp`:
```
...
Fragments load_fragments (const std::string& filename)
{
* if (debug::verbose)
    std::cerr << "reading fragments from file \"" << filename << "\"...\n";
  ...
```

--

.explain-bottom[
Have a go at implementing these changes to your own code
]

---

# Using the verbose option

We can now run our code as normal:
```
$ ./shotgun ../data/fragments-no-reverse-1.txt out
initial sequence has size 1000
final sequence has length 20108
```
which provides a clean output, showing just as much information as we might
expect when everything works correctly

---

# Using the verbose option

... or we can run it with the verbose option to see exactly what is going on:
```
$ ./shotgun ../data/fragments-no-reverse-1.txt out `-v`
reading fragments from file "../data/fragments-no-reverse-1.txt"...
read 190 fragments
190 fragments, mean fragment length: 529.158, range [ 51 1000 ]
initial sequence has size 1000
---------------------------------------------------
189 fragments left
fragment with biggest overlap is at index 41, overlap = -824
---------------------------------------------------

...

fragment with biggest overlap is at index 37, overlap = 51
---------------------------------------------------
104 fragments left
104 fragments remaining unmatched - checking whether already contained in sequence...
final sequence has length 20108
writing sequence to file "out"...
```

---

# Using the verbose option

The availability of a verbose option allows you and your users to quickly
narrow down problems

- the default output can be kept clean and minimal

- when issues occur, running in verbose mode provide useful information:
  - in the case of crashes, it provides a more precise indication of *when* the
    problem occurred (as indicated by the last message), and hence *where* to
    look in the code to figure out the problem
  - in the case of unexpected output, the information reported may point out
    issues with the input data, or provide clues as to where to look for errors in the
    code

- when there are performance issues, verbose mode can provide an indication of
  which stage is taking longer to complete than expected

- ...

--

In general, it is recommended to provide some mechanism to allow users
to get detailed information about the processing, whether using a verbose
option, or by way of a separate log file

---

# Adding convenience functions for debugging

Now that we have the option to provide debugging output, we can wrap up this
functionality more cleanly to avoid having lots of `if (debug::verbose)`
statements throughout our code

Let's implement a `debug::log()` function, which will take a `std::string` as
its argument, and print it to the standard error stream if in debug mode
- it can additionally format its output to more clearly label it as debugging
  information (for example, by prefixing each line with `[DEBUG]`)


--

.explain-bottom[
Have a go at implementing and using such a function in your own code
]

---

# Adding convenience functions for debugging

In `debug.h`:
```
#pragma once

*include <iostream>
*include <string>

namespace debug {
  inline bool verbose = false;

* inline void log (const std::string& message) {
*   if (verbose)
*     std::cerr << "[DEBUG] " << message << "\n";
* }
}
```

---
name: inline_function

# Adding convenience functions for debugging

In `debug.h`:
```
#pragma once

include <iostream>
include <string>

namespace debug {
  inline bool verbose = false;

  `inline` void log (const std::string& message) {
    if (verbose)
      std::cerr << "[DEBUG] " << message << "\n";
  }
}
```


Note the use of the `inline` keyword here, this time to allow multiple definitions of the same *function*

---

# A word about `inline`

Historically, the `inline` keyword was considered more as a performance
optimisation feature
- it was used for functions only, to indicate that a given function was
  suitable for *inlining*
- this would suggest to the compiler that the required code could be
  *substituted* directly at the point of use, rather than *calling* that function
  explicitly
- There is always a small overhead to calling a function, and for functions
  that perform small operations and are called very often, this can impact
  performance
- declaring such functions as `inline` can help avoid the overhead of dedicated
  function calls, and so improve performance
  - this is only possible if the function *definition* is available, which is
    why the `inline` mechanism was introduced to allow definitions to be
    included in header files without causing the *multiple definition* problem
- For further details, refer to other online sources (e.g.
  [GeeksForGeeks](https://www.geeksforgeeks.org/inline-functions-cpp/))

--

In modern C++ (particularly since C++17), the `inline` keyword is used to allow multiple definitions of
functions or variables across multiple translation units
- although it does allow the compiler to perform the kinds of optimisation
mentioned above, the compiler is free to treat this merely as a *hint*


---

# Adding convenience functions for debugging

We can now use our convenience function in our code, for example in `fragments.cpp`:
```
...
Fragments load_fragments (const std::string& filename)
{
* if (debug::verbose)
*   std::cerr << "reading fragments from file \"" << filename << "\"...\n";
  ...
```
becomes simply:
```
...
Fragments load_fragments (const std::string& filename)
{
* debug::log ("reading fragments from file \"" + filename + "\"...");
  ...
```

