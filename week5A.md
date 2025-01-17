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


