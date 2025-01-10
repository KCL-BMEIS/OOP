---
layout: presentation
title: "Week 4, session 1: functional MRI project"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 4, session 1
## next project: functional MRI

---

# What we have learned so far

**By now, you should be able to:**
.columns[
.col[
- use the terminal and navigate around the filesystem
- write, compile and run a small C++ program
- use `for` loops and `if` statements
- use standard data types, including `std::string` and `std::vector`
]
.col[
- write and use your own functions **and classes**
- read and write basic information to & from file
- handle command-line arguments and options
- split your code across multiple `cpp` and header files
]
]

**You should also have a good understanding of:**
.columns[
.col[
- error handling using C++ exceptions
- (const) references
- variable scope
- **the `const` keyword in various contexts**
- **ownership & lifetime**
]
.col[
- the `inline` keyword
- namespaces
- the compile & link process
- **OOP design principles: abstraction and encapsulation**
]
]

**If you struggle with any of these aspects, please ask for help!**

---

# Our next project: fMRI analysis

This week, we start off on a new project: a simple correlation analysis of function MRI data
- Have a look at the [assignment instructions](https://github.com/KCL-BMEIS/OOP/blob/main/projects/fMRI/assignment.md)

You will find the most up to date version of the project in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/main/projects/fMRI/solution)


---

# Getting started

Let's start from the structure we set up in the last project:
- we'll create a file to hold our `main()` function, called `fmri.cpp`
- we'll copy over the `debug.h` header and use that functionality in this
  project too
- we'll set up the `run()` function as before
- we'll start with simply checking that we have one command-line
  argument for the input data filename


--

.explain-bottom[
Have a go at setting up a new project and setting it up as described above
]

---

**`debug.h`**

```
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
```

---

**`fmri.cpp`**

```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "debug.h"


// This function contains our program's core functionality:
void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 2)
    throw std::runtime_error ("missing arguments - expected at least 1 argument");

  std::cerr << "reading file \"" << args[1] << "\"\n";
}

...
```

---

**`fmri.cpp`** *(continued)*

```
...

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
```

---

# Now what?

There are many aspects of the program we could start coding up!

--

But as before, the best place to start is (probably) data loading
- we can't run any processing without some data

--

This time however, data loading is more complicated
- the input data consist of *multiple* files
- the data in each file are stored in a more complex format than previously

--

Let's start by loading just one file for now

.explain-bottom[
Add a function called `load_pgm()` that will open the input file given its
filename, and get our `run()` method to invoke it on the input file.
- we won't worry about the return type for now, so just get it to return an
  `int`
]

---

New file **`pgm.h`**:
```
#pragma once

#include <string>

int load_pgm (const std::string& filename);
```

In **`fmri.cpp`**:
```
...
*#include "pgm.h"

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 2)
    throw std::runtime_error ("missing arguments - expected at least 1 argument");

*  auto slice = load_pgm (args[1]);
}
```

---

New file **`pgm.cpp`**:
```
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <format>
 
#include "debug.h"
#include "pgm.h"

int load_pgm (const std::string& filename)
{
  debug::log ("loading PGM file \"" + filename + "\"...");
  
  std::ifstream infile (filename);
  if (!infile)
    throw std::runtime_error ("unable to open file \"" + filename + "\"");

  return 0;
}
```


---

# The PGM format

We are not at the point where we need to understand how the data are actually
stored. 

--

We're told each data slice is stored in [plain PGM
format](https://netpbm.sourceforge.net/doc/pgm.html#plainpgm)
- this is a very simple, text-only format for 2D images

--

Let's take a look at the [online documentation](https://netpbm.sourceforge.net/doc/pgm.html#plainpgm) and figure out what we need to do


---

# The PGM format

The steps required to read a PGM file:
1. read the first string, and check that it matches `P2` exactly
   - if not, this is an error!
   - this is the [file
     signature](https://en.wikipedia.org/wiki/List_of_file_signatures) (also called the *magic number* or *magic bytes*))
2. read the next two integers: these will be the dimensions of the image
3. read the next integer: this is the maximum pixel value in the image
4. load the pixel intensities themselves

--

To keep things simple, we are going to assume these files contain no comments
- a more practical PGM reader should be able to deal with them

--

.explain-bottom[
Have a go at implementing steps 1-3
- if running in verbose mode, report the size and maximum intensity
]


---

In **`pgm.cpp`**:
```
int load_pgm (const std::string& filename)
{
  ...
  if (!infile)
    throw std::runtime_error ("unable to open file \"" + filename + "\"");

  std::string magic_number;
  infile >> magic_number;
  if (magic_number != "P2")
    throw std::runtime_error ("file \"" + filename + "\" is not in plain PGM format");

  int xdim, ydim, maxval;
  infile >> xdim >> ydim >> maxval;

  debug::log (std::format (
        "PGM file \"{}\" contains {}x{} image with maximum value {}",
        filename, xdim, ydim, maxval));

  return 0;
}
```

---

# Reading image data

We are now ready to read the image data

--

The simplest approach is to load the data into a vector.
- we can then verify that the number of pixel values matches the number we
  expected based on the dimensions

--

.explain-bottom[
Implement step 4 (reading the pixel intensities) as described above. 
- if the number of pixel values does not match the expected number, this is an
  error
]

---

In **`pgm.cpp`**:
```
int load_pgm (const std::string& filename)
{
  ...
  debug::log (std::format (
        "PGM file \"{}\" contains {}x{} image with maximum value {}",
        filename, xdim, ydim, maxval));

  int val;
  std::vector<int> data;
  while (infile >> val)
    data.push_back (val);

  if (static_cast<int>(data.size()) != xdim * ydim)
    throw std::runtime_error (std::format (
          "amount of data in PGM file \"{}\" ({}) does not match dimensions ({}x{})",
          filename, data.size(), xdim, ydim));

  return 0;
}
```

---

# Representing image data



