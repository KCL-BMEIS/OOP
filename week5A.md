---
layout: presentation
title: "Week 5, session 1: template programming, lambda expressions"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 5, session 1
## lambda expressions<br>template programming

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

# Picking up where we left off

We continue working on our [fMRI analysis
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/fMRI/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/main/projects/fMRI/solution)

.explain-bottom[
Make sure your code is up to date now!
]

---

# Limitations of our Image class

Over the last few sessions, we have come up with a useful `Image` class
- but it has its limitations

--

As written, our `Image` class is hard-coded to use `int` to store the intensity
of each pixel
- what if we wanted to use a smaller type (e.g. a 16-bit `unsigned int`) to
  limit memory usage?
- what if we needed to store floating-point values?

--

We could:
- copy/paste our whole `Image` class
- call it `ImageFloat` instead
- change `int` to `float` where relevant

--

... but we can do a lot better using a *generic programming* approach: 

&rArr; C++ templates

---
class: section

# C++ templates

---

# Template functions

C++ provides a way to define a function for one or more generic types
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

This is how our rescale function is currently declared in `task.h`:
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

**In `task.cpp`:**
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

Note that the functions are *identical* other than their declaration!

--

Function overloading is useful, but may not be the best tool here
- what if at some later stage, we need to do the same thing with a vector of `double`?
- what if we find a subtle bug in the code? We would need to correct the error
  in all the different versions

---

# Template functions

Writing a template function avoids these issues by allowing us to provide a
single definition:
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
std::vector<`unsigned short int`> task; 
...
auto task_rescaled = rescale (task, 0, 1000); 
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

To illustrate, if we were to declare our template function in `task.h`:
```
template <typename T>
std::vector<float> rescale (const std::vector<T>& task, T min, T max);
```
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
- no definition would be available for the desired version of `rescale()`
  (`rescale<int>()`)
- the compiler would nonetheless assume that a version of `rescale<int>()`
  must have been produced elsewhere
- the output file `task.o` would mention that the function `rescale<int>()` is
  in use

--

When linking `fmri.o`, `task.o`, etc:
- we will have an *unresolved symbol* error: there is no function `rescale<int>()`
  

--

For this reason, **the definition of a template function must be included in the header file**!
- *not* in the `.cpp` file

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
