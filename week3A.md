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

Let's take a look at our code so far, and try to reason about where most of the
time is spent

--

The bulk of our algorithm consists of a series of nested loops:

&ensp; &bull; loop while there are fragments left to merge
<br>&ensp; &emsp; &bull; &ensp; loop over all candidate fragments
<br>&ensp; &emsp; &emsp; &bull; &ensp; loop over all overlap sizes 
<br>&ensp; &emsp; &emsp; &emsp; &bull; &ensp; extract the corresponding substrings and compare
<br>&ensp; &bull; &ensp; merge the fragment with the largest overlap 
<br>&ensp; &bull; &ensp; remove it from the list of candidate fragments

--

When looking for opportunities to improve performance, we should focus our
attention on the *innermost loop*
- this is the portion of code that will be executed most often

--

&rArr; what is going on in the innermost loop?

---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
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
--
We actually have three loops, although we did not write them up ourselves!


---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = `sequence.substr(0, overlap)`;
    const auto frag_end = `fragment.substr(fragment.size()-overlap)`;
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We actually have three loops, although we did not write them up ourselves!
- one for extracting each substring

---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (`seq_start == frag_end`) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We actually have three loops, although we did not write them up ourselves!
- one for extracting each substring
- one for the comparison itself


---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    `const auto seq_start` = sequence.substr(0, overlap);
    `const auto frag_end` = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We actually have three loops, although we did not write them up ourselves!
- one for extracting each substring
- one for the comparison itself

We also have some implicit memory allocation & deallocation for each substring
- we will cover this much later in the course


---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
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
Can we avoid any of these overheads?
--
- there is not much that can be done about the comparison itself
  - thankfully, it will tend to terminate early (as soon as any character
    doesn't match)
--
- but can we avoid copying each substring into a whole new `std::string` to
  perform the comparison?

---

# Avoiding needless copying

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    bool match = true;
    for (int n = 0; n < overlap; ++n) {
      if (sequence[n] != fragment[fragment.size()-overlap+n]) {
        match = false;
        break;
      }
    }
    if (match) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We can perform the comparison manually character-by-character, ensuring we
compare the characters at the correct positions


---

# The `std::string_view` class

```


int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
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
... or we can use the `std::string_view` class to achieve the same effect!

---

# The `std::string_view` class

```
#include <string_view>
...
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = `std::string_view (sequence)`.substr(0, overlap);
    const auto frag_end = `std::string_view (fragment)`.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
... or we can use the `std::string_view` class to achieve the same effect!


---

# The `std::string_view` class

How does this work?

Each `std::string` holds information consisting of:
- the size of the string
- a handle to the *memory location* corresponding to the start of the text
  - this is actually a [pointer](https://www.geeksforgeeks.org/cpp-pointers/) &ndash; which we are trying to avoid as much as
    possible on this course!


```xml
                         ↓
(*#&\:;*'¬|\^$(&*^$%("()!`this is the text that our string contains`@~@:~#*(£';~"£*(£|#@
```

--
Memory is essentially a very long list of 8-bit *bytes*
- most of these are going to contain data in machine representation (binary)
  - none of that will make sense as text
- the text for our string will occupy some contiguous section of memory
  - the `std::string` class only needs to know *where it starts* and *how long it
    is*

--

The `std::string_view` class holds *exactly the same information*

---

# The `std::string_view` class

The `std::string_view` class provides a *non-owning (and non-modifiable) view*
of a string

Notably, it provides its own `substr()` method, which also returns a
`std::string_view`
- with a different start and size for the substring
- no copying is performed!

--

Original `std::string`: 
- start at position 1000, size 41 bytes

```xml
                         ↓
(*#&\:;*'¬|\^$(&*^$%("()!`this is the text that our string contains`@~@:~#*(£';~"£*(£|#@
⁣
```

---

# The `std::string_view` class

The `std::string_view` class provides a *non-owning (and non-modifiable) view*
of a string

Notably, it provides its own `substr()` method, which also returns a
`std::string_view`
- with a different start and size for the substring
- no copying is performed!

Original `std::string`: 
- start at position 1000, size 41 bytes

```xml
                         ↓
(*#&\:;*'¬|\^$(&*^$%("()!this is the text that `our string` contains@~@:~#*(£';~"£*(£|#@
                                               ↑
```

`std::string_view` for `"our string"`: 
- start at position 1022, size 10 bytes


---

# Ownership and lifetime

The main difference between `std::string` and `std::string_view` is one of
*ownership*

--

Each `std::string` 'owns' the memory where its text is
stored, and is responsible for its management
- it needs to *allocate* the memory when some text needs to be stored
- it needs to *free* or *deallocate* that memory when no longer in use, so
  that the memory can be used for other purposes

--

Each `std::string_view` only provides a *view* into some existing text in
memory
- it does not *own* that memory, and is not responsible for managing it

--

Consequently, `std::string_view` instances are very cheap to create and destroy
- no memory management!
- no copying!

--

But we need to be very careful with the *lifetime* of that memory location...

---

# Ownership and lifetime

When extracting a substring using the original `std::string`, we got a new
`std::string`
- this new `std::string` contained a fully self-contained *copy*
  of the corresponding text 
- its *lifetime* was not tied to the lifetime of the original `std::string`

--

In contrast, when we extract a substring using the new `std::string_view`, we
got a non-owning *view*
- the text in that view is completely dependent on the original `std::string`
- its *lifetime* is intrisincally tied to that of the original `std::string`

--

There is nothing to prevent the use of a `std::string_view` that is no longer
valid!
- no mechanism exists in C++ to prevent this
- if the original `std::string` no longer exists, or points to new
  location, we will get [undefined behaviour](https://en.wikipedia.org/wiki/Undefined_behavior)
  - the code may crash, we could get nonsense back, etc.

--
It is up to the developer (you!) to ensure the lifetime of the text exceeds
the lifetime of the view
- this is a very common source of bugs and security vulnerabilities

---

# Ownership and lifetime &ndash; examples

```
std::string text ("this is the text that our string contains");
std::cout << text << "\n";

auto view = std::string_view (text).substr (22, 10);
std::cout << view << "\n";

text.clear();     // ⇐ original string is no longer valid!
std::cout << view << "\n";
```
--

If you try this, you may find that the code works just fine
- this is because the memory where the text was stored hasn't been modified
- that memory location has been marked as unused and is available for other uses
- ... but we haven't needed to store anything else there &ndash; yet!

--

This is why the result of the last line of code is *undefined behaviour*
- it may work as expected sometimes, or it may crash other times
- it may depend on what compiler is used, or what settings were used for the
  compiler, etc.

---

# Ownership and lifetime &ndash; examples

```
std::string text ("this is the text that our string contains");
std::cout << text << "\n";

auto view = std::string_view (text).substr (22, 10);
std::cout << view << "\n";

text = "a longer piece of text that won't fit in the original memory location");
// ⇑ forces re-allocation: original string is no longer valid!
std::cout << view << "\n";
```
--

Assigning a different string to our variable can also force a re-allocation
- particularly if the new string is longer than the original
- there is no guarantee that the new string will be allocated at the same
  location!

---

# Ownership and lifetime &ndash; examples

```
std::string_view get_substr () 
{
  std::string original = read_from_file();
  return std::string_view (original);
}

// ⇓ original string has gone out of scope and no longer exists!
std::cout << get_substr() << "\n";
```
--

Returning a non-owning view or reference to a function scope, local variable is a common mistake!
- this applies to any non-owning reference or similar construct

---

# Ownership and lifetime &ndash; examples

```
// a vector of 16 integers:
std::vector<int> v = (16, 0); 

// we take an iterator to the first element:
auto iter = v.begin();

// we take a reference to the second element:
int& ref (v[1]);

// we append another element to the vector:
v.push_back (1);
// ⇑ this may cause a re-allocation of the contents of the vector
// to a different memory location!
```

This issue is much broader than just `std::string_view`
- it affects any constructs that provides a non-owning view of data held by
  some other construct
- it can affect references and STL iterators too!


---

# Ownership and lifetime &ndash; examples

These are examples of a more general class of problems, generally referred to as
[dangling references](https://abseil.io/tips/180)
- you will also come across 'dangling pointers', which is essentially the same
  problem 

This applies to references, iterators, pointers and any non-owning construct

--

It is not always obvious when such references become invalidated
- the original owner has been destroyed or gone out of scope
- the original owner has been cleared of its contents
- the original owner has moved its contents to a different location

--

For these reasons, use non-owning constructs with caution!
- in general, they are safe as function *arguments* 
  - the owning object lives in a broader scope with a longer lifetime, and
    will not change while the function runs
- they are *not* safe as return values
  - especially when referring to function scope variables!
- they are *not* safe when there is a possibility of modification of the original
  container

---

# Back to our own code...

```
`#include <string_view>`
...
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = `std::string_view (sequence)`.substr(0, overlap);
    const auto frag_end = `std::string_view (fragment)`.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
--

In our case, we can see that:
- the lifetime of both `std::string_view`s is shorter than the original
  `sequence` & `fragments`
- there is no scope for our code to modify either `sequence` or `fragment`
  while our views are live
  - indeed, we enforced this by providing these to `compute_overlap()` as `const` references!


---

# Impact of using `std::string_view` on performance

We can measure the impact of this simple change using the [`time`
command](https://www.geeksforgeeks.org/time-command-in-linux-with-examples/):

Before the change:
```
$ time ./shotgun ../data/fragments-1.txt out
initial sequence has size 1000
final sequence has length 20108

real    0m0.359s
user    0m0.359s
sys     0m0.000s
```
---

# Impact of using `std::string_view` on performance

We can measure the impact of this simple change using the [`time`
command](https://www.geeksforgeeks.org/time-command-in-linux-with-examples/):


After the change:
```
$ time ./shotgun ../data/fragments-1.txt out
initial sequence has size 1000
final sequence has length 20108

real    0m0.041s
user    0m0.037s
sys     0m0.004s
```
--

This is almost 10× faster!

---
name: classes

class: section

# Classes

## A cornerstone of Object-Oriented Programming

---

# C++ classes

Classes can be thought of an extension of structures
- indeed, in C++, `struct` are also classes!

--

Classes are user-defined data types that can be used to group data, but also:
- allow the class to provide *member functions* to interact with the data
- provide *access specifiers* to limit access to some or all member variables

--

Classes are central to Object-Oriented Programming
- a class is essentially a *blueprint* for objects of that type
- a class is used to represent a broadly independent aspect of our program 
- an instance of a class is also referred to as an *object*

--

We have already used a number of standard classes:
- `std::string`, `std::vector`, `std::string_view`, ...


---

# Class member functions or methods

*Methods* or *member functions* are functions that are accessed via an existing
*instance* using the [dot
operator]((https://www.geeksforgeeks.org/dot-operator-in-cpp/)

--

You have already been using methods throughout the course so far:
- `s.size();`
- `v.size();`
- `v.push_back();`
- `v.insert();`
- ...

--

These are a feature of C++ classes
- you can define your own methods for your own classes

---

# Access specifiers

Member variables or functions can be declared as *public* or *private*

--

When **public**, the corresponding variable or function can be used from outside
the class

When **private**, the variable or function can only be used within another member
function of the same class

--

The ability to protect members in this way supports
[*encapsulation*](https://www.geeksforgeeks.org/encapsulation-in-cpp/) and
[*abstraction*](https://www.geeksforgeeks.org/abstraction-in-cpp/)
- *private* data can only be modified using *public* methods:
  - the author of the class can then ensure the *consistency* of the
    internal state of their class (encapsulation)
  - users of the class only need to understand the *abstract*
    interface provided via the *public* methods (abstraction) 

--

Encapsulation and abstraction are [fundamental features of Object-Oriented
Programming](https://www.geeksforgeeks.org/object-oriented-programming-in-cpp/)
- we will cover them in more detail later in the course, when they will make
  more sense

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

--

&rArr; let's use a class to represent our algorithm!

---
layout: true

# The shotgun sequencing algorithm as a class

Let's set up a class called `ShotgunSequencer` to encapsulate our algorithm:

---

```
class ShotgunSequencer {

};
```

---

```
`class` ShotgunSequencer {

};
```
- a class is declared using the keyword `class` 
  - this is similar to declaring a `struct`

---

```
class `ShotgunSequencer` {

};
```
- a class is declared using the keyword `class` 
  - this is similar to declaring a `struct`
- we provide a suitable name for the class
  - this is the name of the *type* &ndash; not an instance
  - there are many conventions for naming &ndash; on this course, we recommend
    using
[PascalCase](https://www.freecodecamp.org/news/snake-case-vs-camel-case-vs-pascal-case-vs-kebab-case-whats-the-difference/)
  - it is important to chose a name that clearly expresses what kind of object
    this class represents


---

```
class ShotgunSequencer `{`

`};`
```
- a class is declared using the keyword `class` 
  - this is similar to declaring a `struct`
- we provide a suitable name for the class
  - this is the name of the *type* &ndash; not an instance
  - there are many conventions for naming &ndash; on this course, we recommend
    using
[PascalCase](https://www.freecodecamp.org/news/snake-case-vs-camel-case-vs-pascal-case-vs-kebab-case-whats-the-difference/)
  - it is important to chose a name that clearly expresses what kind of object
    this class represents
- the contents of the class are then declared between braces
  - don't forget the final semicolon!

---
layout: true

# The shotgun sequencing algorithm as a class

Now let's add some data members to our class:

---

```
class ShotgunSequencer {

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```

---

```
class ShotgunSequencer {

  `private:`
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```
- we are going to declare our member variables as **private**
  - this is done using the `private` keyword, followed by a colon (`:`)
  - all subsequent declarations will be private


---

```
class ShotgunSequencer {

  private:
*   const int m_minimum_overlap = 10;
*   std::string m_sequence;
*   Fragments m_fragments;
};
```
- we are going to declare our member variables as **private**
  - this is done using the `private` keyword, followed by a colon (`:`)
  - all subsequent declarations will be private
- we can now declare our member variables, in exactly the same way as we did
  with `struct`
  - there are many naming conventions &ndash; for member variables, we
    recommend `snake_case` with the `m_` prefix 

---

```
class ShotgunSequencer {

  private:
*   const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```
- we are going to declare our member variables as **private**
  - this is done using the `private` keyword, followed by a colon (`:`)
  - all subsequent declarations will be private
- we can now declare our member variables, in exactly the same way as we did
  with `struct`
  - there are many naming conventions &ndash; for member variables, we
    recommend `snake_case` with the `m_` prefix 
- note that member variables can be *default-initialised* as shown
  - this type of initialisation was introduced in C++11 
  - we need to initialise `m_minimum_overlap` since we have declared it
    `const` &ndash; we won't be able to modify it later!

---
layout: true

# The shotgun sequencing algorithm as a class

We now need to add *methods* to allow users of our class to interact with it:

---

```
class ShotgunSequencer {
  public:
    void init (const Fragments& fragments);
    bool iterate ();
    void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```

---

```
class ShotgunSequencer {
  `public`:
    void init (const Fragments& fragments);
    bool iterate ();
    void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```
- this time, our methods will need to be **public**
  - this is done using the `public` keyword, in much the same way as with
    `private`

---

```
class ShotgunSequencer {
  public:
*   void init (const Fragments& fragments);
*   bool iterate ();
*   void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```
- this time, our methods will need to be **public**
  - this is done using the `public` keyword, in much the same way as with
    `private`
- we can now add our *method declarations*
  - these look very similar to regular function declarations
  - ... but they are declared within the scope of our `ShotgunSequencer` class





---
layout: false

# Difference between `struct` and `class`

In C++, there is very little difference between `struct` and `class`


---

# Solutions



---

# Exercises

