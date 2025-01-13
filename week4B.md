---
layout: presentation
title: "Week 4, session 2: using external libraries, operator overloading"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 4, session 2
## using external libraries<br>operator overloading

---

# Picking up where we left off

We continue working on our [fMRI analysis
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/fMRI/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/main/projects/fMRI/solution)

.explain-bottom[
Make sure your code is up to date now!
]

---

# Exercise

Implement a class called `Dataset` to represent a *time series* of image slices

This class should:
- store a vector of `Image`s
- provide methods to:
  - load the images
  - query the size of the data set (the number of time points / slices)
  - get one of the image slices given its index
  - get the full timecourse for a pixel of interest, given its *x* & *y*
    coordinates
- have a default constructor
- have a non-default constructor that will also load the data from the
  relevant file(s)
  
Modify your own code to use this new class

---

**`dataset.h`:**
```
#pragma once

#include <vector>
#include <string>

#include "image.h"

class Dataset
{
  public:
    Dataset () = default;
    Dataset (const std::vector<std::string>& filenames) { load (filenames); }

    void load (const std::vector<std::string>& filenames);

    unsigned int size () const { return m_slices.size(); }
    const Image& get (int n) const { return m_slices[n]; }
    std::vector<int> get_timecourse (int x, int y) const;

  private:
    std::vector<Image> m_slices;
};
```

---

**`dataset.cpp`:**
```
#include <vector>
#include <string>
#include <format>
#include <stdexcept>

#include "debug.h"
#include "pgm.h"
#include "dataset.h"

std::vector<int> Dataset::get_timecourse (int x, int y) const
{
  std::vector<int> vals (size());
  for (unsigned int n = 0; n < size(); ++n)
    vals[n] = m_slices[n].get(x,y);
  return vals;
}

...
```

---

**`dataset.cpp`:** *(continued)*
```
...

void Dataset::load (const std::vector<std::string>& filenames)
{
  m_slices.clear();
  if (filenames.empty())
    throw std::runtime_error ("no filenames supplied when loading dataset");

  for (const auto& fname : filenames)
    m_slices.push_back (load_pgm (fname));

  // check that dimensions all match up:
  for (unsigned int n = 1; n < m_slices.size(); ++n) {
    if ( (m_slices[n].width() != m_slices[n-1].width()) ||
         (m_slices[n].height() != m_slices[n-1].height()) )
      throw std::runtime_error ("dimensions do not match across slices");
  }

  debug::log (std::format (
      "loaded {} slices of size {}x{}\n",
      m_slices.size(), m_slices[0].width(), m_slices[0].height()));
}
```

---
class: section

# Command-line handling

## handling options with extra arguments

---

# Selecting the pixel of interest

Currently, our code can print the intensity at a pixel of interest
- but the location of that pixel is hard-coded

It would be better to provide a mechanism to allow us (and our users) to select
different pixels

--

&rArr; we can do this using a command-line option, for example:
```
$ ./fmri ../data/fmri-*.pgm `-p 30 48`
```

--

.explain-bottom[
Exercise: implement code to handle such an option, and use it to print out the
timecourse of the intensity at various locations

<br>
Hint: you will most likely find the following methods useful:
- [`std::ranges::find()`](https://en.cppreference.com/w/cpp/algorithm/ranges/find), [`std::distance()`](https://www.geeksforgeeks.org/stddistance-in-c/), [`std::vector::erase()`](https://www.geeksforgeeks.org/vector-erase-in-cpp-stl/), [`std::stoi()`](https://www.geeksforgeeks.org/stdstoi-function-in-cpp/)
]

---

**In `fmri.cpp`:**
```
...

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

* int x = -1, y = -1;
* auto pixel_option = std::ranges::find (args, "-p");
* if (pixel_option != args.end()) {
*   if (std::distance (pixel_option, args.end()) < 3)
*     throw std::runtime_error (
*            "not enough arguments to '-p' option (expected '-p x y')");
*   x = std::stoi (*(pixel_option+1));
*   y = std::stoi (*(pixel_option+2));
*   args.erase (pixel_option, pixel_option+3);
* }

  ...
```

---
class: section

# Using external libraries

---

# Why use external libraries?

We could write code to do everything ourselves
- but that is often not possible, or at best not a good use of our time

--

For example, we may wish to perform matrix multiplications
- but it is [incredibly difficult to write efficient
  code](https://gist.github.com/nadavrot/5b35d44e8ba3dd718e595e40184d03f0) to do this!
- what if we need to solve more complex matrix problems, involving matrix
  inversions, etc?

--

As another example, we may wish to perform Fourier transforms
- but this is not trivial to code up, particularly if performance matters

--

&rArr; much better to use an external, well-maintained library, written by experts
- it saves us time 
- it means (a lot) fewer bugs
- less code for us to maintain, document, etc
- other developpers will likely already be familiar with well-known libraries
--
- ... and it often means we can do something that we simply wouldn't be able to
  do otherwise!
