---
layout: presentation
title: "Week 2, session 1: multi-file projects, error handling
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
$ g++ shotgun.cpp fragments.cpp -o shotgun
```
--

That works, but it negates the benefits of incremental or parallel builds

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

