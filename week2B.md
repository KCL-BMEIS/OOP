---
layout: presentation
title: "Week 2, session 2: debugging, advanced string formatting"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 2, session 2
## Debugging<br>Advanced string formatting


---

# Exercises

Add a function to compute the overlap between the current sequence and a
  candidate fragment
- make sure it works for both ends of the string
- ignore the possibility that fragments might be reversed for now

Use this function to identify the candidate fragment with the largest overlap
with current sequence

Add a function to merge this candidate fragment with the current sequence,
given the computed overlap

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
No! If we carry on, we'll find larger overlap


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

--

Let's implement code to do this

---
layout: false

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
```
- it's always a good to check any assumptions and expectations upfront &ndash;
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
```
- it's always a good to check any assumptions and expectations upfront &ndash;
  this can save you a lot of frustration later...
- when in development mode, don't hesitate to display lots of information, it
  will often alert you to where things might be going wrong.

---

# Computing the overlap

```
  ...

  int largest_overlap = 0;
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

  return largest_overlap;
}
```

---

# Computing the overlap

```
  ...

* int largest_overlap = 0;
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }

* return largest_overlap;
}

```
.explain-bottom[
We declare an integer to hold the value of the computed overlap. 
- we give this variable an initial value of zero
-  this is the value that will be returned 
- *unless* we find a valid overlap
]

---

# Computing the overlap

```
  ...

  int largest_overlap = 0;
* for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
* }

  return largest_offset;
}

```
.explain-bottom[
We then iterate over the range of valid overlaps. 

<br>At this point, we need to be clear about how we are going to represent the
overlap
]














---

Next, we create the `overlap.cpp` file to hold our function *definition*

```
*int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_offset = 0;
  for (int offset = fragment.size(); offset > 0; --offset) {
    const auto seq_start = sequence.substr(0, offset);
    const auto frag_end = fragment.substr(fragment.size()-offset);
    if (seq_start == frag_end) {
      largest_offset = offset;
      break;
    }
  }

  return largest_offset;
}

```

.explain-bottom[

]

---

Next, we create the `overlap.cpp` file to hold our function *definition*

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_offset = 0;

  for (int offset = fragment.size(); offset > 0; --offset) {
    const auto seq_start = sequence.substr(0, offset);
    const auto frag_end = fragment.substr(fragment.size()-offset);
    if (seq_start == frag_end) {
      largest_offset = offset;
      break;
    }
  }

  return largest_offset;
}

```

---

Next, we create the `overlap.cpp` file to hold our function *definition*

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_offset = 0;

  for (int offset = fragment.size(); offset > 0; --offset) {
    const auto seq_start = sequence.substr(0, offset);
    const auto frag_end = fragment.substr(fragment.size()-offset);
    if (seq_start == frag_end) {
      largest_offset = offset;
      break;
    }
  }

  return largest_offset;
}

```

---

Next, we create the `overlap.cpp` file to hold our function *definition*

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_offset = 0;

  for (int offset = fragment.size(); offset > 0; --offset) {
    const auto seq_start = sequence.substr(0, offset);
    const auto frag_end = fragment.substr(fragment.size()-offset);
    if (seq_start == frag_end) {
      largest_offset = offset;
      break;
    }
  }

  return largest_offset;
}

```

---

Next, we create the `overlap.cpp` file to hold our function *definition*

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_offset = 0;

  for (int offset = fragment.size(); offset > 0; --offset) {
    const auto seq_start = sequence.substr(0, offset);
    const auto frag_end = fragment.substr(fragment.size()-offset);
    if (seq_start == frag_end) {
      largest_offset = offset;
      break;
    }
  }

  return largest_offset;
}

```

---

Next, we create the `overlap.cpp` file to hold our function *definition*

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  if (fragment.size() > sequence.size())
    throw std::runtime_error ("fragment size larger than current sequence!");

  std::cerr << "sequence is \"" << sequence << "\"\n";
  std::cerr << "trying fragment \"" << fragment << "\"\n";

  int largest_offset = 0;

  for (int offset = fragment.size(); offset > 0; --offset) {
    const auto seq_start = sequence.substr(0, offset);
    const auto frag_end = fragment.substr(fragment.size()-offset);
    if (seq_start == frag_end) {
      largest_offset = offset;
      break;
    }
  }

  return largest_offset;
}

```



---

class: section

# Command-line options

## Requesting addtional debugging information

---

# Command-line options

We've already seen examples of command-line options in other commands:
```
$ ls `-l`
$ g++ `-std=c++20` shotgun.cpp `-o` shotgun
```

--

The purpose of command-line options is typically to *alter the behaviour* of the
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

Here, we are going to use a very simple approach:
- start by checking whether the option has been provided in the arguments list
- if it has, then:
  - take whatever action is appropriate (e.g. set a `verbose` variable `true`)
  - remove that option from the argument list
- process your arguments as previously

--

.explain-bottom[
Have a go at modifying your code to detect the `-v` option
]

---

# Detecting the `-v` option

```




