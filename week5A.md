---
layout: presentation
title: "Week 5, session 1: template programming"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 5, session 1
## template programming

---

# Picking up where we left off

We continue working on our [fMRI analysis
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/fMRI/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/fmri_solution/projects/fMRI/solution)

.explain-bottom[
Make sure your code is up to date now!
]

---

# Limitations of utility functions

Our rescale function is currently declared in `task.h` as:
```
std::vector<float> rescale (const std::vector<int>& task, int min, int max);
```
--

Currently, this can only be used to rescale a vector of `int`
- what if we wanted to use the same functionality to rescale a vector of
  `float`?

--
We could use function overloading:
```
std::vector<float> rescale (const std::vector<`int`>& task, `int` min, `int` max);
std::vector<float> rescale (const std::vector<`float`>& task, `float` min, `float` max);
```
--

... but then we would have to duplicate the function *definition* too!

---

# Using function overloading

```
std::vector<float> rescale (const std::vector<int>& task, int min, int max)
{
  std::vector<float> out (task.size());
  for (unsigned int n = 0; n < task.size(); ++n)
    out[n] = min + task[n] * (max-min);
  return out;
}

std::vector<float> rescale (const std::vector<float>& task, float min, float max)
{
  std::vector<float> out (task.size());
  for (unsigned int n = 0; n < task.size(); ++n)
    out[n] = min + task[n] * (max-min);
  return out;
}
```

--

.explain-bottom[
**Note that the functions are *identical* other than their declaration!**
<br>
Function overloading is useful, but may not be the best tool here
- what if at some later stage, we need to do the same thing with a vector of `double`?
- what if we find a subtle bug in the code? We would need to correct the error
  in all the different versions
]

---
class: section

# C++ template functions

## Generic programming in C++

---

# Template functions

C++ provides a way to define a function for one or more *generic* types
- this allows us to provide a *blueprint* for what the function should do
- when we need to use the function, the compiler will work out what the type
  is, substitute it into our code, and compile that
- this allows us to write a generic function once and re-use it in different
  contexts
  - this is a great tool to maximise [code re-use](https://www.lambdatest.com/learning-hub/code-reusability)

--

We have already been using template functions throughout this course:
- `std::min()`, `std::max()`, `std::ranges::min()`, `std::ranges::max()`,
  `std::distance()`, `std::format()`, ...

--

Let's illustrate the concept by modifying our task `rescale()` function

---

# Template functions

Writing a template function avoids the need for multiple overloaded functions
by allowing us to provide a single generic definition:
```
`template <typename T>`
std::vector<float> rescale (const std::vector<`T`>& task, `T` min, `T` max)
{
  std::vector<float> out (task.size());
  for (unsigned int n = 0; n < task.size(); ++n)
    out[n] = min + task[n] * (max-min);
  return out;
}
```

--

We can then use the function as before, for *any type* (within reason...):
```
std::vector<`double`> task; 
...
auto task_rescaled = rescale (task, 0.0, 1000.0); 
```

---

# Template functions - how does this work?

When the compiler encounters this line:
```
auto task_rescaled = rescale (task, 0.0, 1000.0);
```
It will look up the *types* of all the arguments, and note that they are:
- `task`: `std::vector<double>`
- `0.0`: `double`
- `1000.0`: `double`

--

This matches the previously-declared template function, since `T` can be
substituted for `double`:
```
template <typename T>
std::vector<float> rescale (const std::vector<`T`>& task, `T` min, `T` max);
```

--

The compiler can now actually compile the function:
```
std::vector<float> rescale (const std::vector<`double`>& task, `double` min, `double` max);
```

---

# Template functions

When using templates, there are a few issues to watch out for:

The compiler won't actually produce any code until the type is known
- all it can do when encountering the definition is make sure the syntax is
    correct

--

The type will only be known at the point where the function is used
- this is normally in a different file from the declaration
- for example, `rescale()` is declated in `task.h`, but used in `fmri.cpp`

--

The compiler can only produce the required code if it has access
to the full *definition*

--

&rArr; the definition must be available in the same translation unit

--

We have to place the full definition *in the header file*, alongside the declaration
- there is no point including it in the corresponding `.cpp` file
  - the compiler won't generate any code until the type is specified
  - this is different from regular functions


---

To illustrate the problem, imagine we declare our template function in `task.h`:
```
template <typename T>
std::vector<float> rescale (const std::vector<T>& task, T min, T max);
```

--

... define it in `task.cpp`:
```
template <typename T>
std::vector<float> rescale (const std::vector<`T`>& task, `T` min, `T` max)
{
  std::vector<float> out (task.size());
  for (unsigned int n = 0; n < task.size(); ++n)
    out[n] = min + task[n] * (max-min);
  return out;
}
```

--

... and use it in `fmri.cpp`:
```
std::vector<int> task; 
...
auto task_rescaled = rescale (task, 0, 1000); 
```

---

Then when compiling `task.cpp`:
- no code would be produced for *any* version of `rescale()`
  - the compiler doesn't know which type might be requested

--

When compiling `fmri.cpp`:
- no definition would be available for the desired `rescale<int>()` version 
- the compiler would nonetheless assume that a version of `rescale<int>()`
  must have been produced elsewhere
- the output file `task.o` would mention that he function `rescale<int>()` is
  being used

--

When linking `fmri.o`, `task.o`, etc:
- we will have an *unresolved symbol* error: there is no function `rescale<int>()`
  

--

<br>
For this reason, **the definition of a template function must be included in the header file**!
- *not* in the `.cpp` file
- the function will implicitly be marked `inline` to prevent the multiple
  symbol problem when linking 

--

.explain-bottom[
Exercise: convert the `rescale()` function to a template function
]

---

# Template functions

There can be more than a single template argument

--

For example, this function allows one vector to be added to another, with the
results stored in-place in the first vector &ndash; even if
the types differ:
```
template <`typename A, typename B`>
void add_in_place (std::vector<`A`>& vecA, const std::vector<`B`>&  vecB)
{
  if (vecA.size() != vecB.size())
   throw std::runtime_error ("vector size must be the same");

  for (unsigned int n = 0; n < vecA.size(); ++n)
    vecA[n] += vecB[n];
}
```

---

# Template argument deduction

Note that issues can occur due to template argument deduction, when the types
provided don't match where they should. 

For example, there can be issue with our `rescale()` function when the type deduced
by the compiler for the `min` & `max` limits doesn't match the type for the
elements of the vector.

Consider this example:
```
std::vector<short unsigned int> task; 
...
auto task_rescaled = rescale (task, 0, 1000);
```
This will produced an error because the arguments `0` & `1000` are deduced as being
of type `int`, but the type of the vector elements is declared as `short
unsigned int`
- according to our declaration, these should all be the same type (`T`)
- the compiler can't work out which type to use for `T`!

The full compiler error is shown on the next slide

---

# Compiler error due to template argument 

```
fmri.cpp: In function ‘void run(std::vector<std::__cxx11::basic_string<char> >&)’:
fmri.cpp:67:23: error: no matching function for call to ‘rescale(std::vector<short unsigned int>&, int, int)’
   67 |   auto task_rescaled = rescale (task, 0, 1000);
      |               ~~~~~~~~^~~~~~~~~~~~~~
In file included from fmri.cpp:13:
task.h:9:20: note: candidate: ‘template<class ValueType> std::vector<float> rescale(const std::vector<ValueType>&, ValueType, ValueType)’
    9 | std::vector<float> rescale (const std::vector<ValueType>& task, ValueType min, ValueType max)
      |                    ^~~~~~~
task.h:9:20: note:   template argument deduction/substitution failed:
fmri.cpp:67:23: note:   deduced conflicting types for parameter ‘ValueType’ (‘short unsigned int’ and ‘int’)
   67 |   auto task_rescaled = rescale (task, 0, 1000);
      |                            ~~~~~~~~^~~~~~~~~~~~~~
```

---

# Exercise

A simple solution to this problem is to allow the types for the `min` & `max`
arguments to differ from the type of the vector elements. 
- modify the `rescale()` function by adding at least one more template
  parameter to its declaration, to avoid the issue mentioned in the previous
  slides.


---

# Solution

```
template <typename T`, typename C`>
std::vector<float> rescale (const std::vector<T>& task, `C` min, `C` max)
{
  std::vector<float> out (task.size());
  for (unsigned int n = 0; n < task.size(); ++n)
    out[n] = min + task[n] * (max-min);
  return out;
}
```

---
class: section

# Class templates in C++

---

# Limitations of our Image class

Over the last few sessions, we have come up with a useful `Image` class
- but it has its limitations

--

As written, our `Image` class is hard-coded to use `int` to store the intensity
of each pixel
- what if we wanted to use a smaller type (e.g. a 16-bit `short unsigned int`) to
  limit memory usage?
- what if we needed to store floating-point values?

--

We could:
- copy/paste our whole `Image` class
- call it `ImageFloat` instead
- change `int` to `float` where relevant

--

... but that is a *lot* of code duplication!

&rArr; let's use C++ templates instead


---

**In `image.h`:**
```

class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<int>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<int> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }

    const int& operator() (int x, int y) const { return m_data[x + m_xdim*y]; }
    int& operator() (int x, int y) { return m_data[x + m_xdim*y]; }

  private:
    int m_xdim, m_ydim;
    std::vector<int> m_data;
};
```
---

**In `image.h`:**
```

class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<`int`>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<int> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }

    const `int`& operator() (int x, int y) const { return m_data[x + m_xdim*y]; }
    `int`& operator() (int x, int y) { return m_data[x + m_xdim*y]; }

  private:
    int m_xdim, m_ydim;
    std::vector<`int`> m_data;
};
```

.explain-topright[
Currently, our `Image` class is hard-coded to store `int` values
]

---

**In `image.h`:**
```

class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<`float`>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<int> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }

    const `float`& operator() (int x, int y) const { return m_data[x + m_xdim*y]; }
    `float`& operator() (int x, int y) { return m_data[x + m_xdim*y]; }

  private:
    int m_xdim, m_ydim;
    std::vector<`float`> m_data;
};
```

.explain-topright[
... but if we changed the *type* from `int` to `float` at the locations
highlighted, this class would work just as well for `float`!
]

---

**In `image.h`:**
```
`template <typename T>`
class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<T>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<int> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }

    const T& operator() (int x, int y) const { return m_data[x + m_xdim*y]; }
    T& operator() (int x, int y) { return m_data[x + m_xdim*y]; }

  private:
    int m_xdim, m_ydim;
    std::vector<T> m_data;
};
```

.explain-topright[
Our `Image` class can readily be converted into a `template` class

<br>As with template functions, we need to use the `template` keyword to denote
the class as a *template*, and list the *arguments* this template will take
- our template accepts a single *type* argument, which will be referred to as
  `T` in our definition
]


---

**In `image.h`:**
```
template <typename T>
class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<`T`>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<int> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }

    const `T`& operator() (int x, int y) const { return m_data[x + m_xdim*y]; }
    `T`& operator() (int x, int y) { return m_data[x + m_xdim*y]; }

  private:
    int m_xdim, m_ydim;
    std::vector<`T`> m_data;
};
```

.explain-topright[
We can now use the (as  yet unknown) type `T` where required instead of `int`
]


---

**In `image.h`:**
```
template <typename T>
class Image {
  public:
    Image (`int` xdim, `int` ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (`int` xdim, `int` ydim, const std::vector<T>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<`int`> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    `int` width () const { return m_xdim; }
    `int` height () const { return m_ydim; }

    const T& operator() (`int` x, `int` y) const { return m_data[x + m_xdim*y]; }
    T& operator() (`int` x, `int` y) { return m_data[x + m_xdim*y]; }

  private:
    `int` m_xdim, m_ydim;
    std::vector<T> m_data;
};
```

.explain-topright[
Note: we don't blindly replace every mention of `int` from the class!

<br>We only replace it where it relates to its use as the pixel intensity
]


---

# Using class templates

We can now declare instances of our class template for any desired type like this:
```
  Image<int> image (256, 256);
```
or from an existing vector of data (of matching type):
```
  std::vector<float> data;
  ...

  Image<float> image (512, 512, data);
```

--

The compiler will then substitute the desired type (`int` or `float`) instead
of `T` in the class definition, and compile the result
- as if we had manually substituted the type ourselves!

--

You'll note that we have already been using class templates since the
beginning!
- `std::vector` is a class template

---

# Where to define class templates

As with template functions, the compiler will not produce any code when
encountering a template class definition 
- it can only check our definition for correctness

--

The compiler will only generate code when the data type is known: at the point of use

--

&rArr; the full class declaration and all method definitions must be available
in the header! 
- as before, all methods are implicitly marked `inline` to prevent the multiple
  symbol problem when linking 


---

# Exercises

- Convert the `Image` class to a template class, where the template parameter
  determines the type to use for the image intensities. Modify the rest of the
  code to make use of it

- Convert the `Dataset` class to a template class, where the template parameter
  determines the type to use for the image intensities. Modify the rest of the
  code to make use of it

---

**In `image.h`:**
```
`template <typename T>`
class Image {
  public:
    Image (int xdim, int ydim) :
      m_xdim (xdim), m_ydim (ydim), m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<`T`>& data) :
      m_xdim (xdim), m_ydim (ydim), m_data (data) {
        if (static_cast<int> (m_data.size()) != m_xdim * m_ydim)
          throw std::runtime_error ("dimensions don't match");
      }

    int width () const { return m_xdim; }
    int height () const { return m_ydim; }

    const `T`& operator() (int x, int y) const { return m_data[x + m_xdim*y]; }
    `T`& operator() (int x, int y) { return m_data[x + m_xdim*y]; }

  private:
    int m_xdim, m_ydim;
    std::vector<`T`> m_data;
};
```

---

**Also in `image.h`:** 
- note that the insertion operator must now also be a template

```
`template <class ValueType>`
inline std::ostream& operator<< (std::ostream& out, const `Image<ValueType>`& im)
```


**In `load_pgm.h/cpp`:**

```
`Image<int>` load_pgm (const std::string& filename);
```

**In `dataset.h`:**
```
class Dataset
{
    ...
    const `Image<int>`& operator[] (int n) const { return m_slices[n]; }
    ...

  private:
    std::vector<`Image<int>`> m_slices;
};
```

---

# Polymorphism

[Polymorphism](https://www.geeksforgeeks.org/cpp-polymorphism/) is one of the
key feature of Object-Oriented Programming

It refers to ability to define a single *interface* with multiple
implementations
- For example, the `std::vector` class has a well-defined interface, but
  different implementations for different types

--

C++ provides several mechanisms to implement *polymorphism*:

- Compile-time polymorphim
  - function overloading
  - templates

--

- Run-time polymorphism
  - inheritance (to be covered later)

--

Our template `Image` class is an example of *compile-time polymorphism*
- and so were our overloaded `rescale()` functions
- ... and so is our *templated* `rescale()` function

---

# Exercises

- Convert the `Image` class to a template class, where the template parameter
  determines the type to use for the image intensities. Modify the rest of the
  code to make use of it

- Convert the `Dataset` class to a template class, where the template parameter
  determines the type to use for the image intensities. Modify the rest of the
  code to make use of it

