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

# Picking up where we left off

We continue working on our [DNA shotgun sequencing
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/DNA_shotgun_sequencing/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/shotgun_sequencing_solution/projects/DNA_shotgun_sequencing/solution)

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
Exercise: use the `std::format()` function where relevant in your own code
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
int find_biggest_overlap (const std::string& sequence, 
                          std::vector<std::string>& fragments, `int& index`)
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
`Overlap` find_biggest_overlap (const std::string& sequence, std::vector<std::string>& fragments);
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
layout:true

# Aggregate initialisation

In the implementation of our function (the function definition), we need to
return a variable of type `Overlap`. We can do that like this:

---

```
   ...
   Overlap retval;
   retval.size = biggest_overlap;
   retval.fragment = fragment_with_biggest_overlap;
   return retval;
}
```

---

```
   ...


   Overlap retval = { biggest_overlap, fragment_with_biggest_overlap };
   return retval;
}
```
A much cleaner solution is to use [aggregate
initialisation](https://www.geeksforgeeks.org/aggregate-initialization-in-cpp-20/)
in the `return` statement 
- each member of the struct is then initialised with the matching variable in
  the brace-delimited list 

---

```
   ...



   return { biggest_overlap, fragment_with_biggest_overlap };
}
```

A much cleaner solution is to use [aggregate
initialisation](https://www.geeksforgeeks.org/aggregate-initialization-in-cpp-20/)
in the `return` statement 
- each member of the struct is then initialised with the matching variable in
  the brace-delimited list 

And this can be further simplified by returning the initialiser list directly
- the compiler already knows that this function returns an object of type `Overlap`
- the compiler will instantiate a *temporary* (unnamed) instance of `Overlap`
  for us
- ... and use aggregate initialisation as before

---
layout:false

# Returning multiple values from a function

Declaring our own custom `struct` allows us to return multiple pieces of
information as a single variable
- this is a cleaner way to solve our problem

--

.explain-bottom[
Exercise: add the `find_biggest_overlap()` function to your own code
]



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
- `std::string`, `std::vector`, `std::ifstream`, ...


---

# Class member functions or methods

*Methods* or *member functions* are functions that are accessed via an existing
*instance* of a class using the [dot
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

# Difference between `struct` and `class`

In C++, there is actually very little *practical* difference between `struct` and `class`
- there is however a big *conceptual* difference!

--

As far as the compiler is concerned, `struct` & `class` are essentially the
same thing
- the only *actual* difference between the two is that *unless otherwise
  specified*:
  - members of a `struct` are *public* by default
  - members of a `class` are *private* by default

--

Nonetheless, you are encouraged to reserve the use of `struct` for small, lightweight containers with public data members only
- for example, as a way of grouping variables into a single entity that can be
  returned from a function
- do not use a `struct` for anything that should provide an abstract interface, and/or
  where maintaining consistency between member variables is important

--

&rArr; In general, prefer to define a `class`

---

# Using classes in our project

We already use plenty of classes in our project:
- `std::string`
- `std::vector`
- `std::vector<std:string>`

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
    std::vector<std::string> m_fragments;
};
```

---

```
class ShotgunSequencer {

  `private:`
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
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
*   std::vector<std::string> m_fragments;
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
    std::vector<std::string> m_fragments;
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
  - we need to initialise `m_minimum_overlap` since we have declared it
    `const` &ndash; we won't be able to modify it later!
  - note: this type of [in-class member
    initialisation](https://isocpp.org/wiki/faq/cpp11-language-classes#member-init)
    was introduced in C++11 

---
layout: true

# The shotgun sequencing algorithm as a class

We now need to add *methods* to allow users of our class to interact with it:

---

```
class ShotgunSequencer {
  public:
    void init (const std::vector<std::string>& fragments);
    bool iterate ();
    void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```

---

```
class ShotgunSequencer {
  `public`:
    void init (const std::vector<std::string>& fragments);
    bool iterate ();
    void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```
- this time, our methods will need to be **public**
  - this is done using the `public` keyword, in much the same way as with
    `private`

---

```
class ShotgunSequencer {
  public:
*   void init (const std::vector<std::string>& fragments);
*   bool iterate ();
*   void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```
- this time, our methods will need to be **public**
  - this is done using the `public` keyword, in much the same way as with
    `private`
- we can now add our *method declarations*
  - the names of these methods should mirror the actions performed in the algorithm
  - these look like regular function declarations &ndash;
    but are declared *within the scope* of our `ShotgunSequencer` class

---

```
class ShotgunSequencer {
  public:
*   void init (const std::vector<std::string>& fragments);
    bool iterate ();
    void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```
- `.init()` is used to provide the list of fragments to initialise the
    algorithm
  - it does not need to return anything (return type is therefore `void`)


---

```
class ShotgunSequencer {
  public:
    void init (const std::vector<std::string>& fragments);
*   bool iterate ();
    void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```
- `.iterate()` performs a single iteration of the algorithm 
  - it will identify the fragment with the largest overlap, and if found, merge
    it
  - we return a `bool` to indicate the status of the iteration:
    <br>&rArr; if `false`, no fragment was found, and the algorithm should stop

---

```
class ShotgunSequencer {
  public:
    void init (const std::vector<std::string>& fragments);
    bool iterate ();
*   void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```
- `.check_remaining_fragments()` performs the final check
  - the remaining fragments should all already be contained within the estimated sequence
  - we *could* have decided to return `bool` to indicate the status of the check &ndash; this is a design decision!
  - ... but if any fragments remain, we consider this to be unexpected, but not fatal &rArr; we issue a warning
  - there is therefore to need for a return value &ndash; the return type is
    also `void`
 

---

```
class ShotgunSequencer {
  public:
    void init (const std::vector<std::string>& fragments);
*   bool iterate ();
*   void check_remaining_fragments ();

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    std::vector<std::string> m_fragments;
};
```
- note that we don't need to provide any arguments to these methods
  - this is because the class members will all be available within the scope of
    these methods
  - they will already have full access to the private `m_minimum_overlap`, `m_sequence` and `m_fragments`
    variables!
 


---
layout: true

# The shotgun sequencing algorithm as a class

How do we use our class elsewhere in our code? In `shotgun.cpp`:

---

---

```
*#include "shotgun_sequencer.h"

  ...
  auto fragments = load_fragments (args[1]);

* ShotgunSequencer solver;
* solver.init (fragments);
* while (solver.iterate());
* solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";
  write_sequence (args[2], solver.sequence());
}
```


---

```
*#include "shotgun_sequencer.h"

  ...
  auto fragments = load_fragments (args[1]);

  ShotgunSequencer solver;
  solver.init (fragments);
  while (solver.iterate());
  solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";
  write_sequence (args[2], solver.sequence());
}
```

- we need to `#include` our new header to ensure the declarations are
  accessible in this file


---

```
#include "shotgun_sequencer.h"

  ...
  auto fragments = load_fragments (args[1]);

* ShotgunSequencer solver;
  solver.init (fragments);
  while (solver.iterate());
  solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";
  write_sequence (args[2], solver.sequence());
}
```

- we need to `#include` our new header to ensure the declarations are
  accessible in this file
- at the apppropriate point, we can create an *instance* of our new
  `ShotgunSequencer` class



---

```
#include "shotgun_sequencer.h"

  ...
  auto fragments = load_fragments (args[1]);

  ShotgunSequencer solver;
* solver.init (fragments);
  while (solver.iterate());
  solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";
  write_sequence (args[2], solver.sequence());
}
```

- we need to `#include` our new header to ensure the declarations are
  accessible in this file
- at the apppropriate point, we can create an *instance* of our new
  `ShotgunSequencer` class
- we use the `.init()` method to supply the list of fragments and initialise
  the algorithm


---

```
#include "shotgun_sequencer.h"

  ...
  auto fragments = load_fragments (args[1]);

  ShotgunSequencer solver;
  solver.init (fragments);
* while (solver.iterate());
  solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";
  write_sequence (args[2], solver.sequence());
}
```

- we can now iterate through the algorithm
  - the simplest approach is to use a `while` loop here: we keep going while `iterate()` returns `true`
  - as everything is done within the `.iterate()` method, we can leave the
    loop empty

---

```
#include "shotgun_sequencer.h"

  ...
  auto fragments = load_fragments (args[1]);

  ShotgunSequencer solver;
  solver.init (fragments);
  while (solver.iterate());
* solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";
  write_sequence (args[2], solver.sequence());
}
```

Finally, we can perform the final check to ensure all the remaining fragments
are indeed already contained in the final sequence


---
layout: false

# The shotgun sequencing algorithm as a class

Note that *we cannot access private members* outside the class:

```
int run (std::vector<std::string>& args)
{
  ...
* std::cout << "final sequence is: " << solver.m_sequence << "\n";
  write_sequence (args[2], solver.sequence());
}
```

- this line will result in a compiler error, similar to:
  ```
  shotgun.cpp: In function ‘void run(std::vector<std::__cxx11::basic_string<char> >&)’:
  shotgun.cpp:35:48: error: ‘std::string ShotgunSequencer::m_sequence’ is private within this context
     35 |   std::cout << "final sequence is: " << solver.m_sequence << "\n";
        |                                                ^~~~~~~~~~
  In file included from shotgun.cpp:8:
  shotgun_sequencer.h:16:17: note: declared private here
     16 |     std::string m_sequence;
        |                 ^~~~~~~~~~
  ```



---
layout: true

# The shotgun sequencing algorithm as a class

We have *declared* our methods, but we have not *defined* them! 
<br>Let's create a `shotgun_sequencer.cpp` file to match the corresponding
header:

---

---

```c++
#include <iostream>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
#include "shotgun_sequencer.h"
#include "debug.h"

void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{ ... }

bool ShotgunSequencer::iterate ()
{ ... }

void ShotgunSequencer::check_remaining_fragments ()
{ ... }
```

---

```c++
#include <iostream>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
*#include "shotgun_sequencer.h"
#include "debug.h"

void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{ ... }

bool ShotgunSequencer::iterate ()
{ ... }

void ShotgunSequencer::check_remaining_fragments ()
{ ... }
```

.explain-bottom[
As before, we need to `#include` all the necessary headers that declare the
functionality we are going to use &ndash; including our new header!
]

---

```c++
#include <iostream>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
#include "shotgun_sequencer.h"
#include "debug.h"

*void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{ ... }

*bool ShotgunSequencer::iterate ()
{ ... }

*void ShotgunSequencer::check_remaining_fragments ()
{ ... }
```

.explain-top[
We can now provide the definitions for our methods. As before, we need to
start each *definition* by replicating the *declaration*, so that the compiler
can match it with the original declaration in the header

<br>
But there are some clear differences!
]


---

```c++
#include <iostream>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
#include "shotgun_sequencer.h"
#include "debug.h"

void `ShotgunSequencer::`init (const std::vector<std::string>& fragments)
{ ... }

bool `ShotgunSequencer::`iterate ()
{ ... }

void `ShotgunSequencer::`check_remaining_fragments ()
{ ... }
```

.explain-top[
The name of each method is now prefixed with the *class name* and the [scope
resolution
operator](https://www.geeksforgeeks.org/scope-resolution-operator-in-c/)

<br>
This is because these definitions are now *outside* the scope of the class
declaration (outside the braces within which we declared our member variables
and functions).

<br>
This is how we can refer to member functions of a class. This essentially
means: the `init()` method that was declared within the scope of the
`ShotgunSequencer` class ]


---

```c++
#include <iostream>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
#include "shotgun_sequencer.h"
#include "debug.h"

*void init (const std::vector<std::string>& fragments)
{ ... }

*bool iterate ()
{ ... }

*void check_remaining_fragments ()
{ ... }
```

.explain-top[
If we tried to define our methods *without* this scope resolution, the compiler
would (rightly) assume that we are defining completely different, *global* functions,
that are entirely independent of our `ShotgunSequencer` class!

<br>For example, we would end up with:
- an unexpected `iterate()` function
  - potentially with *compiler* errors as we try to access member variables
- no *definition* for our `ShotgunSequencer::iterate()` method 
  - leading to *linker* errors at a later stage in the build process (unresolved symbol)
]

---

```c++
#include <iostream>
#include <algorithm>
#include <format>

#include "fragments.h"
#include "overlap.h"
#include "shotgun_sequencer.h"
#include "debug.h"

void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{ `...` }

bool ShotgunSequencer::iterate ()
{ `...` }

void ShotgunSequencer::check_remaining_fragments ()
{ `...` }
```

.explain-top[
Let's now focus on what will go in the *body* of our functions
]

---
layout: true

# Function definitions

---

```
void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{
  m_fragments = fragments;
  if (debug::verbose)
    fragment_statistics (m_fragments);
  m_sequence = extract_longest_fragment (m_fragments);
}
```

---

```
void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{
  `m_fragments` = fragments;
  if (debug::verbose)
    fragment_statistics (`m_fragments`);
  `m_sequence` = extract_longest_fragment (`m_fragments`);
}
```

Note that we can access the *members* of our class directly within the body of
our method
- technically, these are the members of the *current instance* of our class
- each instance will have its own independent version of these variables


---

```
void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{
* m_fragments = fragments;
  if (debug::verbose)
    fragment_statistics (m_fragments);
  m_sequence = extract_longest_fragment (m_fragments);
}
```

Note that we can access the *members* of our class directly within the body of
our method
- technically, these are the members of the *current instance* of our class
- each instance will have its own independent version of these variables


We start by copying the list of fragments over from the argument provided
  (`fragments`) into the corresponding member variable (`m_fragments`)
- note how using a clear naming strategy for class members helps to avoid
    confusion!

---

```
void ShotgunSequencer::init (const std::vector<std::string>& fragments)
{
  m_fragments = fragments;
* if (debug::verbose)
*   fragment_statistics (m_fragments);
* m_sequence = extract_longest_fragment (m_fragments);
}
```

Note that we can access the *members* of our class directly within the body of
our method
- technically, these are the members of the *current instance* of our class
- each instance will have its own independent version of these variables


We start by copying the list of fragments over from the argument provided
  (`fragments`) into the corresponding member variable (`m_fragments`)
- note how using a clear naming strategy for class members helps to avoid
    confusion!

The rest of the function mirrors what was done in `shotgun.cpp` previously

---

```
bool ShotgunSequencer::iterate ()
{
  debug::log ("---------------------------------------------------");
  debug::log (std::format ("{} fragments left", m_fragments.size()));

  auto [ overlap, index ] = find_biggest_overlap (m_sequence, m_fragments);

  if (index < 0)
    return false;
  if (std::abs (overlap) < m_minimum_overlap)
    return false;

  debug::log (
      std::format ("fragment with biggest overlap is at index {}, overlap = {}",
      index, overlap));

  merge (m_sequence, m_fragments[index], overlap);
  m_fragments.erase (m_fragments.begin() + index);
  return true;
}
```
.explain-topright[
This mirrors almost exactly what was previously performed in `shotgun.cpp`
&ndash; this time using the member variables (`m_minimum_overlap`,
`m_fragments`, `m_sequence`)
]

---

```
bool ShotgunSequencer::iterate ()
{
  debug::log ("---------------------------------------------------");
  debug::log (std::format ("{} fragments left", m_fragments.size()));

  auto [ overlap, index ] = find_biggest_overlap (m_sequence, m_fragments);

  if (index < 0)
    `return false`;
  if (std::abs (overlap) < m_minimum_overlap)
    `return false`;

  debug::log (
      std::format ("fragment with biggest overlap is at index {}, overlap = {}",
      index, overlap));

  merge (m_sequence, m_fragments[index], overlap);
  m_fragments.erase (m_fragments.begin() + index);
  `return true`;
}
```
.explain-topright[
The main difference is that we now `return` to indicate success or failure. 
]

---

```
void ShotgunSequencer::check_remaining_fragments ()
{
  debug::log (std::format (
        "{} fragments remaining unmatched"
        m_fragments.size()));
  int num_unmatched = 0;
  for (auto& frag : m_fragments) {
    if (m_sequence.find (frag) == std::string::npos)
      ++num_unmatched;
  }

  if (num_unmatched)
    std::cerr << "WARNING: " << num_unmatched << " fragments remain unmatched!\n";
  else
    debug::log ("all remaining fragments matched OK");
}
```
Likewise, the code in `ShotgunSequencer::check_remaining_fragments()` works exactly as it
did previously in `shotgun.cpp`



---
layout: false
name: getset

# Getters & setters

There is one final piece required for us to be able to use our
`ShotgunSequencer` class:
- a way to retrieve the resulting sequence

--

For this, we can use a [*getter*
method](https://www.geeksforgeeks.org/cpp-getters-and-setters/)

```
class ShotgunSequencer {
  public:
    ...
*   const std::string& sequence () const { return m_sequence; }
  private:
    ...
};
```

--

Let's unpack what is going on here...

---

# Getters & setters

```
class ShotgunSequencer {
  public:
    ...
    `const std::string& sequence () const` { return m_sequence; }
  private:
    ...
};
```
This is the *declaration* of our method

---

# Getters & setters

```
class ShotgunSequencer {
  public:
    ...
    const std::string& `sequence` () const { return m_sequence; }
  private:
    ...
};
```
We have given our getter method a simple name: `sequence()` 
- note that many style guides would recommend a name such as `get_sequence()`
  or `getSequence()`
- use whichever [coding
  standards](https://isocpp.org/wiki/faq/coding-standards) are in use on
  whichever project you may be contributing to!


---

# Getters & setters

```
class ShotgunSequencer {
  public:
    ...
    `const std::string&` sequence () const { return m_sequence; }
  private:
    ...
};
```

Our getter returns a *const reference* to our member variable
- this is a common construct: returning a full-blown copy could rapidly become
  prohibitive
- returning a `const` reference guarantees our *private* variable remains
  read-only
  - it cannot be modified from outside the code


---

# Getters & setters

```
class ShotgunSequencer {
  public:
    ...
    const std::string& sequence `()` const { return m_sequence; }
  private:
    ...
};
```

Note that our getter method does not take any arguments
- we can simply invoke it as `solver.sequence()`
- this is often the case with getters: they only need to return the
  corresponding value

---
name: const_method


# Getters & setters - const methods

```
class ShotgunSequencer {
  public:
    ...
    const std::string& sequence () `const` { return m_sequence; }
  private:
    ...
};
```
The `const` keyword has a special meaning when placed at the end of our method
declaration, after the argument list:
- it states that this method cannot modify any of the class members
- calling this method is therefore guaranteed to leave the class itself
  completely unmodified
- the compiler is responsible for enforcing this

---

# Getters & setters

```
class ShotgunSequencer {
  public:
    ...
    const std::string& sequence () const { `return m_sequence;` }
  private:
    ...
};
```

In this case, we have decided to insert the method *definition* right in
the class declaration
- this differs from our previous methods, which were defined separately in the
  corresponding `.cpp` file

--

This declares the member function implicitly as `inline`
- remember: `inline` means the definition is allowed to appear
  across multiple *translation units*
- this makes sense for small functions such as getters & setters
- it provides opportunities for the compiler to optimise away the function call 
  - it can simply substitute the *body* of the function where it might
    otherwise have called the function
- there is now no need to supply the corresponding function definition in a
  separate `.cpp` file

---

# Getters & setters

```
class ShotgunSequencer {
  public:
*   void init (const std::vector<std::string>& fragments);
    ...
    const std::string& sequence () const { return m_sequence; }
  private:
    ...
};
```

*Setters* perform the opposite action from getters
- they allow users to *set* class parameters
- they typically do not need to return anything, so usually have a `void` return type
- since they modify class members, they cannot be declared `const`

--

Our `init()` method is in many ways a setter method:
- it sets the (initial) list of fragments
- we could have called this method `set_fragments()` or similar
  - here, we have chosen to call it `init()` since setting the fragment list
    implicitly (re-)initialises the algorithm


---

# Getters & setters

Getters and setters are an important tool to implement *encapsulation*

- the getter can ensure the member variable cannot be modified directly from
  outside the class

- the setter can perform any additional actions that may be required when
  modifying member variables
  - for example, our `init()` method (if viewed as a setter method) needs to
    re-initialise the whole algorithm, including resetting the current estimate
    of the sequence to the longest fragment in the list
  - simply setting the list of fragments without reinitialising the algorithm
    would leave the class in an inconsistent state &ndash; breaking
    encapsulation


---
class: section
name: exercises

# Exercises

---

# Exercises

Have a go at implementing the changes necessary to create the
`ShotgunSequencer` class.

Move the functionality previously in `shotgun.cpp`
(currently within the `run()` function) into dedicated methods.




