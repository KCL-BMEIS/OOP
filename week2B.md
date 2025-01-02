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
No! If we carry on, we'll find a larger overlap


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

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) 
      return overlap;
  }

  return 0;
}
```

---

# Computing the overlap

```
  ...

* for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) 
      return overlap;
* }

  return 0;
}
```
.explain-bottom[
We then iterate over the range of valid overlaps. 

<br>As discussed in the previous slides, we start with the largest overlap, and
gradually reduce the size of the overlap.
]


---

# Computing the overlap

```
  ...

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
*   const auto seq_start = sequence.substr(0, overlap);
*   const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) 
      return overlap;
  }

  return 0;
}

```
.explain-bottom[
Within the loop, we extract the portion of the main `sequence` and candidate
`fragment` that are being checked for overlap
]


---

# Computing the overlap

```
  ...

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
*   if (seq_start == frag_end) 
*     return overlap;
  }

  return 0;
}

```
.explain-bottom[
We can then compare the extracted portions using the `==` 
*comparison operator*

<br>
If they match, we can immediately return the value of the overlap
]


---

# Computing the overlap

```
  ...

  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) 
      return overlap;
  }

* return 0;
}

```
.explain-bottom[
If we make through to the last iteration, there is no match, so we simply
`return 0;`
]



---

# Exercises


Have a go at making these changes, and try out your function with different
fragments from the data

Modify the function to also check for overlap at the *end* of the current
sequence
- hint: you can use a *negative* overlap to represent this case

Modify your code to iterate over all candidate fragments and identity the
fragment with the largest overap

Add a function to merge a candidate fragment into the current sequence, given
the value of the overlap









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

The purpose of a command-line option is typically to *alter the behaviour* of the
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

Have a go at implementing this simple approach to detect the `-v` option:
- start by checking whether the option has been provided in the arguments list
- if it has, then:
  - take whatever action is appropriate (e.g. set a `verbose` variable `true`)
  - remove that option from the argument list
- process your arguments as previously

--

.explain-bottom[
Hint: there are many ways of doing this, but you may find the new C++20
[`std::erase()`](https://en.cppreference.com/w/cpp/container/vector/erase2)
function very useful here (if you can work out how to use it from the
documentation...)
]

---

# Detecting the `-v` option

Possible solution:

```
...

void run (std::vector<std::string>& args)
{
* bool verbose = std::erase (args, "-v");

  if (args.size() < 3)
    throw std::runtime_error ("expected 2 arguments: input_fragments output_sequence");

  ...
}
```

--

`std::erase()` will erase any occurence of the value (`"-v"`) from the
container (`args`), and return the *number* of occurences removed. 
- if no `-v` in the argument list, the return value is zero, which equates to
  `false` when assigned to a `bool`
- if there were *any* occurences of `-v`, a non-zero value will be returned,
  which equates to `true`

---

# Global variables

One problem with the previous solution is that `verbose` is a *local* variable
- it is only accessible within the `run()` function

--

If we call other functions, the code in these functions will have no knowledge
or access to our `verbose` variable

--

We could pass our `verbose` variable as an argument to all relevant functions
- but this *very* rapidly becomes cumbersome and impractical

--

A better option in this particular case is to use a *global* variable


---

# Global variables

A global variable is declared outside of any function and is accessible
from anywhere in the code
- provided its *declaration* is encountered before the point of use within each
  translation unit

--

 
In general, global variables are *strongly* discouraged
- they introduce scope for state changes that may affect how different part of
  the program operate, and make it difficult to ensure predictable behaviour
(see e.g. [this
article](https://embeddedartistry.com/fieldatlas/the-problems-with-global-variables/)
for details)

--

There are however cases where they make sense: 
- for constants (in which case they would also be declared `const`)
--
- when they represent a truly unique entity
  - examples include `std::cout`, `std::cerr`: there can only be one of each in
    any program
  - in our case, there can only ever be one setting representing verbose mode!

---

# Global variables

We could declare our global variable like this:

```
...

*bool verbose = false;

...

void run (std::vector<std::string>& args)
{
* verbose = std::erase (args, "-v");

  ...
```

But there are still issues with this:
- this is declared within our `shotgun.cpp` file &ndash; it won't be accessible
  in our other `cpp` files
  - they won't be in the same *translation unit*
--
- what happens if another function declares their own local variable called
  `verbose`?

---

# Variable scope and shadowing

The scope of a variable determines its lifetime and where it can be accessed
from. 

**Global scope**

- Variables are *instantiated* (created) before `main()` starts, and destroyed
  after `main()` returns
- they are accessible from any part of the code
  - provided their declaration occurs before their point of use in the current
    translation unit

--

**Function scope**

- Variables are instantiated when declared, and
  destroyed when the function returns
- They are only accessible within their enclosing function, after their
  declaration
- Each invocation of a given function will have its own version of its local
  variables

--

**Block scope**
- Block scope means within a compound statement (e.g. within a `for` loop or `if` statement)
- Variables are instantiated when declared, and destroyed at the end of the
  block
- They are only accessible within their block, after their declaration


---

# Variable scope and shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <- global scope

...

void compute ()
{
  int count = 10;   // <- function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <- block scope
    std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

--

This is perfectly legal in C++!

---

# Variable scope and shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
*int count = 0;   // <- global scope

...

void compute ()
{
* int count = 10;   // <- function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <- block scope
    std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-bottom[
The variable at function scope *hides* the variable of the same name at
global scope
- at this point, any reference to `count` is assumed to refer to the *function scope* variable
- the global scope version of `count` still exists, but is no longer accessible
  by that name
]

---

# Variable scope and shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <- global scope

...

void compute ()
{
* int count = 10;   // <- function scope
  ...

* for (int count = 0; count < 20; ++count) {    // <- block scope
    std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-top[
Similarly, the variable at block scope *hides* the variable of the same name at
function scope
- at this point, any reference to `count` is assumed to refer to the *block scope* variable
- the function and global scope versions of `count` still exist, but are no longer accessible
  by that name
]

---

# Variable scope and shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <- global scope

...

void compute ()
{
  int count = 10;   // <- function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <- block scope
*   std::cout << count << "\n";
    ...
  }
  std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-top[
This line will print the *block scope* version of `count`
]

---

# Variable scope and shadowing

*Variable shadowing* (also called *name hiding*) occurs when two variables of
the same name co-exist in different scopes

```
int count = 0;   // <- global scope

...

void compute ()
{
  int count = 10;   // <- function scope
  ...

  for (int count = 0; count < 20; ++count) {    // <- block scope
    std::cout << count << "\n";
    ...
  }
* std::cout << count << "\n";
}
```

This is perfectly legal in C++!

.explain-top[
... but this line will print the *function scope* version of `count`, since it
is outside the block
- the block scope version has been destroyed by that point
]


---

# Variable scope and shadowing


Variable shadowing allows a function to use local variables without worrying about
whether some other global variable exists elsewhere with the same name

--

... but it can also lead to subtle errors
- especially in the case of block scope variables hiding function scope
  variables

--

[Name collisions](https://en.wikipedia.org/wiki/Name_collision) are a general
problem in computing
- many projects will rely on functionality provided by other projects
- difficult to avoid using the same names across different projects!

--

Most of these problems can be avoided by:
- not using global variables in the first place!
--
- using a dedicated *C++ namespace*


---

class: section

# C++ namespaces

---

# What is a namespace?

A namespace is essentially a *named scope* for your function and variable
declarations

--

We have been using a namespace from the start: the `std` namespace
- this namespace is where all the functionality provided by the C++ standard is
  declared

--

.columns[
.col[
```
std::vector
```
- the vector class (a *type*) declared within the `std` namespace
]
.col[
```
std::cout
```
- a variable (actually of type `std::ostream`) called `cout`
  declared within the `std` namespace
]
]

---

# What is a namespace?

A namespace is essentially a *named scope* for your function and variable
declarations

We have been using a namespace from the start: the `std` namespace
- this namespace is where all the functionality provided by the C++ standard is
  declared

.columns[
.col[
```
`std`::vector
```
- the vector class (a *type*) declared within the `std` namespace
]
.col[
```
`std`::cout
```
- a variable (actually of type `std::ostream`) called `cout`
  declared within the `std` namespace
]
]

- these are both declared within the `std` namespace
---

# What is a namespace?

A namespace is essentially a *named scope* for your function and variable
declarations

We have been using a namespace from the start: the `std` namespace
- this namespace is where all the functionality provided by the C++ standard is
  declared

.columns[
.col[
```
std`::`vector
```
- the vector class (a *type*) declared within the `std` namespace
]
.col[
```
std`::`cout
```
- a variable (actually of type `std::ostream`) called `cout`
  declared within the `std` namespace
]
]

- these are both declared within the `std` namespace
- accessing members of a namespace is done with the [*scope resolution
  operator*](https://www.geeksforgeeks.org/scope-resolution-operator-in-c/)
