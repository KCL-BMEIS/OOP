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
filename, then get our `run()` method to invoke it on the input file.
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

We are now at the point where we need to understand how the data are actually
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
   - this is the [file
     signature](https://en.wikipedia.org/wiki/List_of_file_signatures) (also called the *magic number* or *magic bytes*))
   - if it doesn't match, this is an error!
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

  if (data.size() != xdim * ydim)
    throw std::runtime_error (std::format (
          "amount of data in PGM file \"{}\" ({}) does not match dimensions ({}x{})",
          filename, data.size(), xdim, ydim));

  return 0;
}
```

---
name: signedness

# Compiler warnings: signedness

When compiling your code, you may have noticed a warning issued by the
compiler:
```
$ g++ -Wall -O2 -DNDEBUG -std=c++20 -I. -c pgm.cpp -o pgm.o
pgm.cpp: In function ‘int load_pgm(const std::string&)’:
*pgm.cpp:35:19: warning: comparison of integer expressions of different signedness: 
‘std::vector<int>::size_type’ {aka ‘long unsigned int’} and ‘int’ [-Wsign-compare]
   35 |   if (data.size() != xdim * ydim)
      |       ~~~~~~~~~~~~^~~~~~~~~~~~~~
```

--

This warning only occurs when compiling with `-Wall`
- this compiler option instructs the compiler to issue all (common) warnings
- it is good practice to heed these warnings, and ensure your code compiles
  without any such warnings

--
This warning means that we have compared a `signed` variable with an `unsigned`
variable
- [`std::vector` `size()` returns an `unsigned`
  quantity](https://www.geeksforgeeks.org/iteration-over-vector-unsigned-vs-signed-index-variable-cpp/), but we are using `int` for our image dimensions
- `unsigned` types cannot take negative values, but can represent larger quantities
- one of these variables has to be converted to the other's type before the
  comparison
  - otherwise, this can lead to [unexpected
    results](https://subethasoftware.com/2017/12/01/c-warning-comparison-between-signed-and-unsigned-integer-expressions-wsign-compare/)

---
name: casting

# Type conversion

To avoid these warnings, we need to ensure both types have the same signedness
before comparing
- we need to perform an explicit [type
  conversion](https://www.geeksforgeeks.org/type-conversion-in-c/)
  - this is also called *type casting*

--

There are several ways to do this, but some are considered outdated:
```
// C-style type casting [outdated]: 
  if (`(int) data.size()` != xdim * ydim)

// C++ functional notation [not recommended]: 
  if (`int (data.size())` != xdim * ydim)

// C++ casting operators [recommended]: 
  if (`static_cast<int> (data.size())` != xdim * ydim)
```

The recommended way is to use the explicit C++ [casting
  operators](https://www.geeksforgeeks.org/casting-operators-in-cpp/)
- there are 4 such operators &ndash; with `static_cast` being the most common


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

* if (static_cast<int>(data.size()) != xdim * ydim)
    throw std::runtime_error (std::format (
          "amount of data in PGM file \"{}\" ({}) does not match dimensions ({}x{})",
          filename, data.size(), xdim, ydim));

  return 0;
}
```

---

# Representing image data

We can already see that we need multiple pieces of information to represent an
image:
- the dimensions of the image
- the pixel intensities

--

It therefore makes sense to *encapsulate* this information into a single
object, and provide an *abstract* interface to interact with it. 

--

&rArr; let's create a class to represent an image

---

# Representing image data

We'll call our class `Image`
- remember that we recommend using [PascalCase](https://www.freecodecamp.org/news/snake-case-vs-camel-case-vs-pascal-case-vs-kebab-case-whats-the-difference/) for types

--

It will hold private data members:
- two `int` members, one for each dimension
- a `std::vector` of `int` for the pixel intensities
- remember that we recommend using the `m_` prefix to denote member variables

--

It will provide an abstract interface using public methods, including:
- a constructor to create an image of a given size with zero intensities
- a constructor to create an image of a given size with intensities supplied
  as an additional argument
- *getters* for the width and height of the image

--

.explain-bottom[
Exercise: have a go at creating the Image class as described above, and modify
your `load_pgm()` function to return an `Image` ]

---

**`image.h`:**
```
#pragma once

#include <vector>

class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<int>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (m_data.size() != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions do not match data vector");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }
    const std::vector<int>& data () const { return m_data; }

  private:
    int m_xdim, m_ydim;
    std::vector<int> m_data;
};
```
 
---

**`pgm.h`:**
```
#pragma once

#include <string>

*#include "image.h"

`Image` load_pgm (const std::string& filename);
```

**`pgm.cpp`:**
```
...
*#include "pgm.h"

`Image` load_pgm (const std::string& filename)
{
  ...

* Image image (xdim, ydim, data);
* return image;
}
```


---

**`pgm.h`:**
```
#pragma once

#include <string>

*#include "image.h"

`Image` load_pgm (const std::string& filename);
```

**`pgm.cpp`:**
```
...
*#include "pgm.h"

`Image` load_pgm (const std::string& filename)
{
  ...

* return Image (xdim, ydim, data);
}
```

.explain-middle[
... or alternatively, return a *temporary* object of type `Image` by invoking
its constructor:
]


---

**`pgm.h`:**
```
#pragma once

#include <string>

*#include "image.h"

`Image` load_pgm (const std::string& filename);
```

**`pgm.cpp`:**
```
...
*#include "pgm.h"

`Image` load_pgm (const std::string& filename)
{
  ...

* return { xdim, ydim, data };
}
```


.explain-middle[
... or even more succinctly, use [uniform
initialisation](https://ianyepan.github.io/posts/cpp-uniform-initialization/) to achieve the same effect:

<br>
If a matching constructor is available for the data type to be returned, the
compiler will use it with each argument substituted in the corresponding place
]

---
name: array_indexing

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0123
4567
89ab
cdef
```
]
]
]

--

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
`0123`
4567
89ab
cdef
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
`0123`456789abcdef
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0123
`4567`
89ab
cdef
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123`4567`89abcdef
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0123
4567
`89ab`
cdef
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
01234567`89ab`cdef
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0123
4567
89ab
`cdef`
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789ab`cdef`
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0123
4567
89ab
cdef
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]

--

But we could also store this one *column* at a time:

.center[
```text
048c159d26ae37bf
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
`0`123
`4`567
`8`9ab
`c`def
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]

But we could also store this one *column* at a time:

.center[
```text
`048c`159d26ae37bf
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0`1`23
4`5`67
8`9`ab
c`d`ef
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]

But we could also store this one *column* at a time:

.center[
```text
048c`159d`26ae37bf
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
01`2`3
45`6`7
89`a`b
cd`e`f
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]

But we could also store this one *column* at a time:

.center[
```text
048c159d`26ae`37bf
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
012`3`
456`7`
89a`b`
cde`f`
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]

But we could also store this one *column* at a time:

.center[
```text
048c159d26ae`37bf`
```
]


---

# Representing image data

.columns[
.col[
Let's assume we have a 4×4 image to hold in memory, with the following
intensities
]
.col[
.center[
```text
0123
4567
89ab
cdef
```
]
]
]

We could hold this data in memory one row at a time:

.center[
```text
0123456789abcdef
```
]

But we could also store this one *column* at a time:

.center[
```text
048c159d26ae37bf
```
]

These are called [*row-major* and *column-major*
ordering](https://en.wikipedia.org/wiki/Row-_and_column-major_order), respectively
- these are standard ways of storing 2D images and matrices
- the same principles can also be generalised to store multidimensional (>2D) arrays

---

# Representing image data

.columns[
.col[
Questions: 
- which order are we implicitly using in our code?
- how to we locate the intensity for the element (pixel) at index (*x*, *y*)?
]
.col[
.center[
```text
0123
4567
89ab
cdef
```
]
]
]

--

Looking through our code, we can see we've loaded the data in row-major order
.center[
```text
0123456789abcdef
```
]

--

To locate the pixel intensity at index (*x*, *y*), let's start simple and
build from there:

---

# Representing image data

.columns[
.col[
Questions: 
- which order are we implicitly using in our code?
- how to we locate the intensity for the element (pixel) at index (*x*, *y*)?
]
.col[
.center[
```text
`0`123
4567
89ab
cdef
```
]
]
]

Looking through our code, we can see we've loaded the data in row-major order
.center[
```text
`0`123456789abcdef
```
]

To locate the pixel intensity at index (*x*, *y*), let's start simple and
build from there:
- when *x*=*y*=0, the pixel intensity is at offset: 0

---

# Representing image data

.columns[
.col[
Questions: 
- which order are we implicitly using in our code?
- how to we locate the intensity for the element (pixel) at index (*x*, *y*)?
]
.col[
.center[
```text
01`2`3
4567
89ab
cdef
```
]
]
]

Looking through our code, we can see we've loaded the data in row-major order
.center[
```text
01`2`3456789abcdef
```
]

To locate the pixel intensity at index (*x*, *y*), let's start simple and
build from there:
- when *x*=*y*=0, the pixel intensity is at offset: 0
- when *y*=0, the pixel intensity is at offset: *x*

---

# Representing image data

.columns[
.col[
Questions: 
- which order are we implicitly using in our code?
- how to we locate the intensity for the element (pixel) at index (*x*, *y*)?
]
.col[
.center[
```text
0123
4567
`8`9ab
cdef
```
]
]
]

Looking through our code, we can see we've loaded the data in row-major order
.center[
```text
01234567`8`9abcdef
```
]

To locate the pixel intensity at index (*x*, *y*), let's start simple and
build from there:
- when *x*=*y*=0, the pixel intensity is at offset: 0
- when *y*=0, the pixel intensity is at offset: *x*
- when *x*=0, the pixel intensity is at offset: *y* &times; *N<sub>x</sub>*
  - *N<sub>x</sub>* is the size of the image along the *x*-axis (i.e. the width)

---

# Representing image data

.columns[
.col[
Questions: 
- which order are we implicitly using in our code?
- how to we locate the intensity for the element (pixel) at index (*x*, *y*)?
]
.col[
.center[
```text
0123
4567
89`a`b
cdef
```
]
]
]

Looking through our code, we can see we've loaded the data in row-major order
.center[
```text
0123456789`a`bcdef
```
]

To locate the pixel intensity at index (*x*, *y*), let's start simple and
build from there:
- when *x*=*y*=0, the pixel intensity is at offset: 0
- when *y*=0, the pixel intensity is at offset: *x*
- when *x*=0, the pixel intensity is at offset: *y* &times; *N<sub>x</sub>*
  - *N<sub>x</sub>* is the size of the image along the *x*-axis (i.e. the width)

&rArr; the pixel at index (*x*, *y*) is at offset: *x* + *y* &times; *N<sub>x</sub>*


--

.explain-top[
Exercise: add public getter & setter methods to get & set the pixel intensity at coordinate (*x*,
*y*)
]


---

**`image.h`:**
```
class Image {
  public:
    ...

    int get (int x, int y) const { return m_data[x + m_xdim*y]; }
    void set (int x, int y, int value)  { m_data[x + m_xdim*y] = value; }

  private: 
    ...
};
```

---

# Loading the full image series

We are now in a position where we can load each slice, given its filename
- how do we expand on that to load *all* the data slices?

--

There are several possible strategies for listing the relevant filenames for
each slice
- we could for example provide a *prefix* for the filename, and the number of files to load

--
&rArr; here, we are going to rely on the shell's [file
globbing](https://www.baeldung.com/linux/bash-globbing) feature to keep
things simple for us

---

# File globbing

When we invoke our command using the `*` wildcard:
```
$ ./fmri ../data/data/fmri-*.pgm
```
we are asking the *shell* to find all files that match this pattern, and insert
them as separate arguments to our command. 
- note this happens *before* our command is executed!

--

Our command will *actually* be invoked as:
```
$ ./fmri ../data/data/fmri-000.pgm ../data/data/fmri-001.pgm ../data/data/fmri-002.pgm
../data/data/fmri-003.pgm../data/data/fmri-004.pgm  ../data/data/fmri-005.pgm 
... 
../data/data/fmri-167.pgm ../data/data/fmri-168.pgm ../data/data/fmri-169.pgm
```

--

We can now iterate over our arguments, relying on the slices being
listed in alphabetical order
- note that this is a very weak assumption: in general, data will not always be
  so conveniently named!

---

# Loading the full image series

We can now load the full image series, storing the data as a vector of `Image`s

- use your verbose option (`-v`) to check which files are being loaded and in
  what order

- to verify that your code works as expected, print out the pixel intensities
  for all time-points at a specific position, for example at index (30, 48)

.explain-bottom[
Exercise: implement code to load the full data set using file globbing as described above
]


---

**In `fmri.cpp`:**
```
  ...
  std::vector<Image> slices;
  for (unsigned int n = 1; n < args.size(); ++n)
    slices.push_back (load_pgm (args[n]));

  // check that dimensions all match up:
  for (unsigned int n = 1; n < slices.size(); ++n) {
    if ( (slices[n].width() != slices[n-1].width()) ||
         (slices[n].height() != slices[n-1].height()) )
      throw std::runtime_error ("dimensions do not match across slices");
  }
  std::cerr << std::format (
      "loaded {} slices of size {}x{}\n",
      slices.size(), slices[0].width(), slices[0].height());

  int x = 30;
  int y = 48;
  std::cerr << std::format ("image values at pixel ({},{}) = [ ", x, y);
  for (const auto& slice : slices)
    std::cerr << slice.get (x,y) << " ";
  std::cerr << "]\n";
}
```

---
class: section

# Exercises


