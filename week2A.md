---
layout: presentation
title: "Week 2, session 1: multi-file projects, error handling"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 2, session 1
## Multi-file projects, error handling

---

# What we covered so far

- The Unix command-line
- Writing C++ code using a simple text editor
- Compiling our first C++ program
- The `#include` preprocessor directive
- Basic data type, `std::string` and `std::vector`
- Iteration and conditional execution
- Statements and compound statements
- Type inference using the `auto` keyword
- Basic error handling
- Handling command-line arguments
- File input/output
- (const) references
- Defining and using functions

---

# Picking up where we left off

Last week, we had started working on our [DNA shotgun sequencing
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/DNA_shotgun_sequencing/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/main/projects/DNA_shotgun_sequencing/solution)

.explain-bottom[
Make sure your code is up to date now!
]

---

# Type Aliasing

We have already started using a vector of strings to store the fragments
&ndash; and it does seem to provide all the functionality we need at this point

--

We could type `std::vector<std::string>` as the type for the fragment list
wherever this is needed
- but it is a bit long...
- it is not obvious what its purpose is to outside observers
- what if we decide to use a different type to store the fragments at a later
  stage? We'd need to modify our code in lots of different places

--

This is an example where defining a *type alias* might be a good idea:
```
using Fragments = std::vector<std::string>;
```

Now we can use `Fragments` as the type for our list of fragments, and the
compiler will understand that to mean `std::vector<std::string>`
- note this is *not* a new type - merely an *alias* for an existing type


---

# Type Aliasing

What does this look like in our project?
```
... 

*using Fragments = std::vector<std::string>;

`Fragments` load_fragments (const std::string& filename)
{
  ...
```


```
... 

void fragment_statistics (const `Fragments`& fragments)
{
  ...
```

--

.explain-bottom[
Have a go at modifying your code as shown here

]

---

# Splitting projects over multiple files

We've barely started on our project, and our `.cpp` file is already ~100 lines
- it will grow and eventually become difficult to manage

--

In practice, projects are spread over multiple files
- it helps to keep our code logically organised
- it keeps each individual file small enough to manage
- it allows for incremental and/or parallel compilation
- it allows for code re-use

--

Of these, the last two points are probably the most important!

---

# Splitting projects over multiple files

In C & C++, we can use the `#include` directive to import another file into our
current code

--

Files designed to be `#include`d in this way are called *header files*
- they typically have extension `.h` (though `.hpp`, `.H` are also sometimes
  used)

--

We have already imported such header files in our project:
- `<iostream>`
- `<fstream>`
- `<string>`
- `<vector>`
- ...

--

These are *system headers*, provided as part of the standard C++ library
- C++ standard system headers do not have the `.h` extension
- They should be `#include`d within *angled brackets*, e.g.: 
  ```
  #include <iostream>
  ```

---

# Splitting projects over multiple files

We can write our own header files, and request they be included in some other
file in the same way. 

--

To illustrate how this works, we create a new *header file* called
`fragments.h`
- this will contain the *declarations* of our functions

--
We will also need a corresponding `fragments.cpp` file
- this will contain the matching *definitions* for our functions

--
We will then `#include` our header in our main `shotgun.cpp` file, but this
time using *inverted commas*, and with the `.h` extension:
```
#include "fragments.h"
```

---

# Splitting projects over multiple files

This is what our `fragments.h` file should look like:

```
#pragma once

#include <vector>
#include <string>

using Fragments = std::vector<std::string>;

Fragments load_fragments (const std::string& filename);

void fragment_statistics (const Fragments& fragments);

void write_sequence (const std::string& filename, const std::string& sequence);
```


---

# Splitting projects over multiple files

This is what our `fragments.h` file should look like:

```
*#pragma once

#include <vector>
#include <string>

using Fragments = std::vector<std::string>;

Fragments load_fragments (const std::string& filename);

void fragment_statistics (const Fragments& fragments);

void write_sequence (const std::string& filename, const std::string& sequence);
```


.explain-bottom[
The `#pragam once` preprocessor directive ensures that our header file will
only be included once. We will cover this in more detail shortly.
]


---

# Splitting projects over multiple files

This is what our `fragments.h` file should look like:

```
#pragma once

*#include <vector>
*#include <string>

using Fragments = std::vector<std::string>;

Fragments load_fragments (const std::string& filename);

void fragment_statistics (const Fragments& fragments);

void write_sequence (const std::string& filename, const std::string& sequence);
```

.explain-bottom[
Our header should `#include` any headers required to make sense of
the code in our header

<br>
Here, we need to make sure the compiler knows about `std::string` and
`std::vector` &ndash; so the corresponding system headers both need to be
`#include`d 
]

---

# Splitting projects over multiple files

This is what our `fragments.h` file should look like:

```
#pragma once

#include <vector>
#include <string>

*using Fragments = std::vector<std::string>;

Fragments load_fragments (const std::string& filename);

void fragment_statistics (const Fragments& fragments);

void write_sequence (const std::string& filename, const std::string& sequence);
```


.explain-bottom[
We also include our type alias &ndash; otherwise the compiler won't know what
we mean by `Fragments`
]

---

# Splitting projects over multiple files

This is what our `fragments.h` file should look like:

```
#pragma once

#include <vector>
#include <string>

using Fragments = std::vector<std::string>;

*Fragments load_fragments (const std::string& filename);
*
*void fragment_statistics (const Fragments& fragments);
*
*void write_sequence (const std::string& filename, const std::string& sequence);
```


.explain-bottom[
Next, we list our function *declarations*. Note that we do not include the full
*definitions* (function body) here &ndash; they will go in the corresponding
`.cpp` file
]


---

# Splitting projects over multiple files

This is what our `fragments.cpp` file should look like:
```
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "fragments.h"

Fragments load_fragments (const std::string& filename)
{ ...
}

void fragment_statistics (const Fragments& fragments)
{ ...
}

void write_sequence (const std::string& filename, const std::string& sequence)
{ ...
}
```

---

# Splitting projects over multiple files

This is what our `fragments.cpp` file should look like:
```
*#include <iostream>
*#include <fstream>
*#include <vector>
*#include <string>

#include "fragments.h"

Fragments load_fragments (const std::string& filename)
{ ...
}

void fragment_statistics (const Fragments& fragments)
{ ...
}

void write_sequence (const std::string& filename, const std::string& sequence)
{ ...
}
```

.explain-bottom[
As for the main `shotgun.cpp` file, we start by `#include`ing the system headers
needed for our code
]

---

# Splitting projects over multiple files

This is what our `fragments.cpp` file should look like:
```
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

*#include "fragments.h"

Fragments load_fragments (const std::string& filename)
{ ...
}

void fragment_statistics (const Fragments& fragments)
{ ...
}

void write_sequence (const std::string& filename, const std::string& sequence)
{ ...
}
```

.explain-bottom[
We can then `#include` the matching header for our code file &ndash; and indeed
any other header that we may have written that our code might need. 
]

---

# Splitting projects over multiple files

This is what our `fragments.cpp` file should look like:
```
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "fragments.h"

*Fragments load_fragments (const std::string& filename)
*{ ...
*}
*
*void fragment_statistics (const Fragments& fragments)
*{ ...
*}
*
*void write_sequence (const std::string& filename, const std::string& sequence)
*{ ...
*}
```

.explain-bottom[
We can then insert the full *definitions* for our functions (the actual
contents have been omitted here for brevity). 

<br>
The definitions need to match the declarations in the header file *exactly*
&ndash; otherwise the compiler may throw an error, or assume you are defining
a different function altogether.
]



---

# Splitting projects over multiple files

Finally, this is what our main `shotgun.cpp` file should look like:
```
#include <iostream>
#include <vector>
#include <string>

#include "fragments.h"

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  ...

  return 0;
}
```

---

# Splitting projects over multiple files

Finally, this is what our main `shotgun.cpp` file should look like:
```
#include <iostream>
#include <vector>
#include <string>

*#include "fragments.h"

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  ...

  return 0;
}
```

.explain-bottom[
We can replace all the function definitions we had previously with a single
`#include` statement!
]

---

# Splitting projects over multiple files

So we now have a project split over 3 files:

- `shotgun.cpp` 
  - `#include "fragments.h"`
  - contains our `main()` function
  - uses functions declared in `fragments.h`

- `fragments.h` 
  - contains the *declarations* for the functions used in `main()`

- `fragments.cpp` 
  - `#include "fragments.h"`
  - contains the *definitions* for the functions declared in
  `fragments.h`

--

How do we compile this project?


---

# Building a multi-file project

We could compile everything in one go:
```
$ g++ -std=c++20 shotgun.cpp fragments.cpp -o shotgun
```
--

That works, but it negates the benefits of incremental or parallel builds

--
What is normally done is:

- *compile* each `.cpp` file independently into an intermediate file format
  called an *object file*
  - these contain the functions and symbols defined in our `.cpp` file
    translated into machine (binary) code

- *link* the resulting object files together to generate the final *executable*
  - this resolves all the references to different functions, and makes sure
    they can all be found for inclusion into the final executable
  - at this stage, we may also link our code with external (static or
    dynamic) libraries (we will not cover this in great detail, interested
    readers can [read up on this 
online](https://www.geeksforgeeks.org/static-and-dynamic-linking-in-operating-systems/))


---

# The compile & link process

![:right 65%](images/compile_link.png)



---

# Commands to perform the compile & link process

Compile:
```
$ g++ -std=c++20 -c shotgun.cpp -o shotgun.o
$ g++ -std=c++20 -c fragments.cpp -o fragments.o
```

Link:
```
$ g++ shotgun.o fragments.o -o shotgun
```

---

# Commands to perform the compile & link process

Compile:
```
$ g++ -std=c++20 `-c` shotgun.cpp -o shotgun.o
$ g++ -std=c++20 `-c` fragments.cpp -o fragments.o
```

Link:
```
$ g++ shotgun.o fragments.o -o shotgun
```

.explain-bottom[
The `-c` option instructs `g++` to *compile* only

<br>
Normally it would both compile *and* link
]



---

# Commands to perform the compile & link process

Compile:
```
$ g++ -std=c++20 -c shotgun.cpp -o `shotgun.o`
$ g++ -std=c++20 -c fragments.cpp -o `fragments.o`
```

Link:
```
$ g++ shotgun.o fragments.o -o shotgun
```

.explain-bottom[
Note that the output files from these commands are now *object files*, with the
`.o` extension
]


---

# Commands to perform the compile & link process

Compile:
```
$ g++ -std=c++20 -c shotgun.cpp -o shotgun.o
$ g++ -std=c++20 -c fragments.cpp -o fragments.o
```

Link:
```
$ g++ `shotgun.o fragments.o` -o shotgun
```

.explain-bottom[
The final link stage takes the object files only to produce the final
executable
]


---

# Commands to perform the compile & link process

Compile:
```
$ g++ -std=c++20 -c shotgun.cpp -o shotgun.o
$ g++ -std=c++20 -c fragments.cpp -o fragments.o
```

Link:
```
$ g++ shotgun.o fragments.o -o shotgun
```

Why bother when this could all be done with one command?

--

Because each of these tasks can be performed independently, and therefore in
parallel
- faster builds for large projects

--
and each of these tasks only needs to be performed if there has been a change
in its inputs
- e.g. if we edit `shotgun.cpp`, we do not need to re-compile `fragments.cpp`
- allows for *incremental builds* &ndash; can save huge amounts of time when
  working on large projects


---

# Commands to perform the compile & link process

Compile:
```
$ g++ -std=c++20 -c shotgun.cpp -o shotgun.o
$ g++ -std=c++20 -c fragments.cpp -o fragments.o
```

Link:
```
$ g++ shotgun.o fragments.o -o shotgun
```

.explain-bottom[
Have a go at splitting up the code as shown previously, and compiling and
linking the different files using the commands above
]

---

# When do we need to recompile?

When we make changes to a file, it is not necessarily trivial to determine
which `.cpp` files need to be recompiled

--

If we edit `fragments.h`, we will need to recompile both `fragments.cpp` and
`shotgun.cpp`

--

If we edit `fragments.cpp`, we only need to recompile `fragments.cpp`
- `shotgun.cpp` does not include any part of `fragments.cpp`
- similarly for `shotgun.cpp`

--

The situation becomes much more complex for large projects
- a header file can `#include` other header files, which themselves can
  `#include` other header files, etc.

--

To manage this web of dependencies, we use *C++ build systems* &ndash; of which
there are many...
- most well-known tools include `GNU make`, `cmake`, `qmake`, `ninja`, `meson`, `scons`, ...
- these can be very complex to understand and manage well
- some of these tools handle different aspects as well as building
  - external dependencies, different operating systems, testing, packaging, ...

---

# How do C++ build systems work?

A comprehensive overview of C++ build systems is beyond the scope of this
course

--

At their most basic, build systems work by:
- knowing which *targets* depends on which inputs, e.g.:
  - `shotgun.o` depends on `shotgun.cpp` & `fragments.h`
  - `shotgun` depends on `shotgun.o` & `fragments.o`
--
- knowing which command to use to regenerate each *target* when necessary
  - this could be an explicit command for each target, or a more generic *rule*
    for each type of target
--
- establishing whether any of the dependencies have been modified more recently than
  the *target*
  - this is typically done via *timestamps*: the time of last modification
--
- if the *target* is older than any of its dependencies (or doesn't exist yet), then
  it need to be regenerated

--

This needs to be done *recursively*:
- all dependencies of a target must themselves be up to date before working out
  if the target needs to be regenerated
  - e.g. both `shotgun.o` and `fragments.o` must be up to date
    before deciding whether we need to relink them
- this can become quite messy in large projects...

---

# What build system is used in this course?


To keep things as simple as possible on this course, we will use a simple
script of our own design (the
[simple_build](https://github.com/jdtournier/simple_build) project)

On KCL systems, this script has already been made available as the command
`oop_build`

--

This script is capable of handling small projects, and does not require any
setting up or editing
- change directory (using `cd`) to your project folder, and run `oop_build`

--

The project must however follow some simple rules
- `cpp` files have the extension `.cpp`
- system headers are *all* `#include`d within angled brackets (`<>`)
- project headers are *all* `#include`d within inverted commas (`""`)
- any `cpp` file that contains a `main()` function will produce a matching
  executable of the same name (minus the `.cpp` extension)
- any `cpp` file that needs to be compiled and linked into other executables
  needs to have matching header of the same name, and this header needs to be
  `#include`d in at least one other `cpp` file 

--

If you follows the conventions taught on this course, the above rules
will always work for you

---

# Building our project using `oop_build`

Make sure your code has been split up as shown in this session
- or fetch the latest version from the website

The listing should show (at least) these files:
```
$ ls
fragments.cpp    fragments.h    shotgun.cpp
```

--

When ready, run the `oop_build` command and run the resulting executable:
```
$ oop_build
g++ -Wall -O2 -DNDEBUG -std=c++20 -I. -c shotgun.cpp -o shotgun.o
g++ -Wall -O2 -DNDEBUG -std=c++20 -I. -c fragments.cpp -o fragments.o
g++ shotgun.o fragments.o -o shotgun
```

--

You'll note there are more options in these commands than we've used so far
- you don't need to know about them &ndash; but if interested, feel free to look
  them up online!



