---
layout: presentation
title: "Week 3, session 1: advanced string formatting, structs & classes"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 3, session 1
## advanced string formatting<br>structs & classes

---

# What we have learned so far

### By now, you should be able to:
.columns[
.col[
- use the terminal and navigate around the filesystem
- write, compile and run a small C++ program
- use `for` loops and `if` statements
- use standard data types, including `std::string` and `std::vector`
]
.col[
- write and use your own functions
- read and write basic information to & from file
- handle command-line arguments and options
- split your code across multiple `cpp` and header files
]
]

### Ideally, you should also have a basic understanding of:
.columns[
.col[
- error handling using C++ exceptions
- (const) references
- variable scope
]
.col[
- the `inline` keyword
- namespaces
- the compile & link process
]
]

**If you struggle with any of these aspects, please ask for help!**

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
name: format

# Advanced string formatting

We've already seen how to concatenate strings to form more complex strings, and
how to convert numeric values to strings using `std::to_string()`
- but this isn't always very convenient or easy to follow

--

The C++20 standard introduces a new function to help with string formatting:
[`std::format()`](https://www.geeksforgeeks.org/cpp-20-std-format/)

--

Its use is best illustrated with an example. Instead of writing:
```
  debug::log ("read " + std::to_string (fragments.size()) + " fragments");
```

--

we can write:
```
#include <format>

...

  debug::log (std::format ("read {} fragments", fragments.size()));
```

---

# The `std::format()` function

The `std::format()` *template* function has the following (highly simplified) declaration:
```
namespace std { 
  string format (format_string fmt, ArgType1 arg1, ArgType2 arg2, ...);
}
```

---

# The `std::format()` function

The `std::format()` *template* function has the following (highly simplified) declaration:
```
*namespace std { 
  string format (format_string fmt, ArgType1 arg1, ArgType2 arg2, ...);
*}
```

- it is declared within the `std` namespace


---

# The `std::format()` function

The `std::format()` *template* function has the following (highly simplified) declaration:
```
namespace std { 
  `string` format (format_string fmt, ArgType1 arg1, ArgType2 arg2, ...);
}
```

- it is declared within the `std` namespace
- it returns a `std::string`


---

# The `std::format()` function

The `std::format()` *template* function has the following (highly simplified) declaration:
```
namespace std { 
  string format (`format_string fmt`, ArgType1 arg1, ArgType2 arg2, ...);
}
```

- it is declared within the `std` namespace
- it returns a `std::string`
- the first argument is the *format string*, of type `std::format_string`
  - it contains the text for the output string, with braces `{}` where substitutions are to be inserted


---

# The `std::format()` function

The `std::format()` *template* function has the following (highly simplified) declaration:
```
namespace std { 
  string format (format_string fmt, `ArgType1 arg1`, ArgType2 arg2, ...);
}
```

- it is declared within the `std` namespace
- it returns a `std::string`
- the first argument is the *format string*, of type `std::format_string`
  - it contains the text for the output string, with braces `{}` where substitutions are to be inserted
- each subsequent argument is a variable to be converted to text and inserted
  into the format string instead of the matching `{}`

---

# The `std::format()` function

For example:
```
std::string name = "Joe";
std::string colour = "orange";

std::cout << std::format ("My name is {}, my favorite colour is {}\n", name, colour);
```
would produce:
```
My name is Joe, my favorite colour is orange
```

---

# The `std::format()` function

But the arguments to be substituted don't need to be strings:
```
int num_iter = 101;
double func_value = 0.023859;

std::cout << std::format ("after {} iterations, function value = {}\n", 
                          num_iter, func_value);
```
would produce:
```
after 101 iterations, function value = 0.023859
```

---

# The `std::format()` function

For numeric arguments, the conversion to text can be carefully controlled:
```
int num_iter = 101;
double func_value = 0.023859;

std::cout << std::format ("after {} iterations, function value = `{:.3f}`\n", 
                          num_iter, func_value);
```
would produce the second argument to 3 decimal places:
```
after 101 iterations, function value = 0.024
```

---

# The `std::format()` function


There are many more formatting options &ndash; too many to cover in this
course!

For details, please refer to the [relevant documentation](https://en.cppreference.com/w/cpp/utility/format/spec)

.explain-bottom[
Have a go at using the `std::format()` function where relevant in your own code
]


---
name: struct

class: section

# Composite data types

## grouping data into *structures*

---

# Returning multiple values from a function

Looking at our project, we would like to add a `find_biggest_overlap()` function to:
- identify the fragment that has the biggest overlap with the current sequence
- remove it from the list of candidate fragments 
- *and* return the size of the overlap

We need to return *two* pieces of information from that function!

--

One approach to this problem relies on *references*:
- one of the arguments to our function is a reference to an existing variable,
  and the function will assign the correct value to that variable before
  returning:

```
int find_biggest_overlap (const std::string& sequence, Fragments& fragments, 
                          `int& index`)
```
- The `index` variable is passed by non-const reference, allowing the function to
  assign a value to it that will also update the original variable.
- the function would then be free to use the return value to provide the
  size of the corresponding overlap


---

# Returning multiple values from a function

We would then be able to use this function as follows:

```
int index_of_fragment;
int overlap_size = find_biggest_overlap (sequence, fragments, index_of_fragment);
```
Since `index_of_fragment` is passed by reference, the function can update its value
- we can now rely on both `overlap_size` and `index_of_fragment` being set correctly.

--

However, this is a cumbersome approach
- we need to declare a variable before invoking the function
- the intent is not immediately clear

--

A better solution would be to return a single variable of a type capable of
holding multiple values
- for example, we could return a `std::vector<int>` here 
- but what if the two values to be returned were of a different type?

---

# Structures in C++

A cleaner solution would be to declare our own *compound data type*, composed
of the two variables we need. 

This can be done using *structures* 
- structures are an old concept: they predate C++ and were already present in C

--

Structures allow us to define a new compound data type, composed of other data types,
grouped together into a single entity.
- each *member variable* is named, and can therefore be assigned a clear interpretation
- the struct can then be treated as any other variable, passed to & from
  function calls, etc.

--

This is best illustrated with an example

---

# Structures in C++


Structures are declared using the `struct` keyword, followed by the list of
members (along with their types) enclosed in braces:
```
struct Overlap {
  int size;
  int fragment;
};
```
--

This can then be used as a regular data type in our function declaration:
```
`Overlap` find_biggest_overlap (const std::string& sequence, Fragments& fragments);
```
--

We can use our function as follows, and access the member variables using 
[dot-notation](https://www.geeksforgeeks.org/dot-operator-in-cpp/):
```
`auto overlap` = find_biggest_overlap (sequence, fragments);
std::cerr << std::format ("overlap of size {} at index {}\n", 
                          `overlap.size`, `overlap.fragment`);
```


---

# Returning multiple values from a function

Declaring our own custom `struct` allows us to return multiple pieces of
information as a single variable
- this is a cleaner way to solve our problem

.explain-bottom[
Have a go at adding the `find_biggest_overlap()` function to your own code
]


---
name: structured_binding

class: section

# Structured binding

## Splitting up grouped data

---

# Structured binding

The C++17 standard introduced the ability to use [*structured binding*](https://www.geeksforgeeks.org/structured-binding-c/)
- this allows up to declare and initialise multiple variables from the
  individual members of a larger composite variable

--


This is best illustrated by example, using our `find_biggest_overlap()`
function:
```
`auto overlap` = find_biggest_overlap (sequence, fragments);
std::cerr << std::format ("overlap of size {} at index {}\n", 
                          `overlap.size`, `overlap.fragment`);
```

--

Using *structured binding*, we can declare independent variables for each
member of the `Overlap` structure returned:
```
auto [ overlap, index ] = find_biggest_overlap (sequence, fragments);
std::cerr << std::format ("overlap of size {} at index {}\n", `overlap`, `index`);
```
--

.explain-bottom[
Have a go at modifying your own code to use structured binding as shown here
]

---
class: info

# Structured binding using `std::tuple`

The C++ STL provides a convenience template class that can be used as a
lightweight replacement for a dedicated `struct` in a variety
of contexts: [`std::tuple`](https://www.geeksforgeeks.org/tuples-in-c/)

One use for `std::tuple` is for structured binding:
```
#include <tuple>

std::tuple<int,int> find_biggest_overlap (const std::string& sequence, 
                                          Fragments& fragments)
{
  ...
  return { biggest_overlap, fragment_with_biggest_overlap };
}

...

auto [ overlap, index ] = find_biggest_overlap (sequence, fragments);
```

---
class: info

# Why don't we use `std::tuple`?

While appealing in its simplicity, `std::tuple` does not provide any indication
about the *interpretation* or *meaning* of each member
- in our case, all we know is that we get 2 `int`s 
- which one represents the overlap size, and which the index?
- We have to rely on additional documentation to work this out 
  - this could be described in a comment, or some other external document

--

On the other hand, using a `struct` provides *named* members, whose interpretation is
immediately much clearer. 

&rArr; Better to use a `struct` with named members rather than a `std::tuple`
where possible

--

The `std::tuple` class is very useful in other contexts, especially when
working with generic functions and containers 
- a generic function or container will not know ahead of time what it
  is to contain
- `std::tuple` provides a simple container for an arbitrary number of variables
  of arbitrary types
- `std::tuple` is therefore used in many places throughout the C++ STL

---

# Structured binding

Structured binding offers another way to return multiple values from a function
- this can sometimes be more convenient or more legible

--

There are many other uses for structured binding
- many of these are too advanced for this course 
  - indeed, arguably some of the most useful were [only introduced in
    C++23](https://www.cppstories.com/2023/view-zip/)!
- if interested, [have a look online for examples](https://www.cppstories.com/2022/structured-bindings/)


---
name: string_view

class: section

# `std::string_view`

## avoiding needless copies

---

# Performance issues


---

# The `std::string_view` class

---

# Ownership and lifetime




---
name: classes

class: section

# Classes

## A cornerstone of Object-Oriented Programming

---

# Extending structures with methods


---

# Access specifiers


---

# OOP design principles

- encapsulation

- abstraction


---

# Using classes in our project

We already use plenty of classes in our project:
- `std::string`
- `std::vector`
- `std::vector<std:string>` (aliased to `Fragments`)

These already provide all the functionality we need for our program to function

--

But what if we need to use our DNA shotgun sequencing algorithm as part of a
broader project?
- it would be better to *encapsulate* the algorithm into a distinct, discrete
  module of some form

&rArr; use a class to represent our algorithm!

---

# Representing our shotgun sequencing algorithm as a class

Let's set up a class called `ShotgunSequencer` to encapsulate our algorithm



---

# Solutions



---

# Exercises

