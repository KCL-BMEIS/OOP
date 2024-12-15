---
layout: presentation
title: "Week 1, session 2: starting our first project"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 1, session 2
## Starting our first project

---

# Project: DNA shotgun sequencing

We will use a selection of short projects to illustrate the use of C++ in
various practical situations. 

The first of these projects will focus on sequencing DNA using the shotgun
sequencing approach. 

- [Please take a look at the project description by following this
link](https://github.com/KCL-BMEIS/OOP/blob/main/projects/DNA_shotgun_sequencing/assignment.md)

--
<br>

As you can see, there is a lot to do! Let's get started one step at a time...

When writing code, it's best to start from a simple working solution, and build
up from there. 

--
<br>

We'll begin by writing a simple `main()` function, make sure that compiles,
then add some basic command-line argument handling to make sure we have the
filename of the input file

---

# First step: set up a simple skeleton

**shotgun.cpp:**

```
#include <iostream>
#include <vector>
#include <string>
int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);
  if (args.size() < 2) {
    std::cerr << "ERROR: expected filename as first argument\n";
    return 1;
  }
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";
  return 0;
}
```

--

Compile with:
```
$ g++ shotgun.cpp -o shotgun
```

---

# `std::cout` or `std::cerr`?

When printing to the terminal, should be we print to `std::cout` or
`std::cerr`? 

- after all, both print to the terminal - what's the difference?

--

The reason there are two output streams is that these can be used as
independent inputs for other processes. 

One example of this is [shell
redirection](https://linuxcommand.org/lc3_lts0070.phpP):
 
- we will learn more about this later in the course

--

It is therefore common to reserve _standard output_ (`std::cout`) for the
expected result of the program, and _standard error_ (`std::cerr`) for error
and progress reporting.

- In our skeleton code, we therefore use `std::cerr` for now, since all of the
  output we've produced so far are simple progress updates, rather than usable
  output as such.

---

# Next step: load data from file

The next logical thing to do is add code to load some data. 

- We could work on other aspects of the code, but without data to apply them
  to, it will be difficult to test them

--

In C++, files are typically handled using the **streams input/output library**

--

There are two main classes that we can use:
- `std::ifstream` for inputs: this provides functionality to _read_ from a file
- `std::ofstream` for outputs: this provides functionality to _write_ to a file
--
- there is also the `std::fstream` class which provides both input and output
  functionality
  - rarely needed, most of the time, we need to read _or_ write, not both. 
--

These are declared in the `<fstream>` header. 

---

# Next step: load data from file


```
#include <iostream>
#include <vector>
#include <string>
*#include <fstream>

int main (int argc, char* argv[])
{
```

```
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";

* std::ifstream infile (args[1]);
* if (!infile) {
*   std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
*   return 1;
* }

  return 0;
}
```

---

# Next step: load data from file


```
#include <iostream>
#include <vector>
#include <string>
*#include <fstream>

int main (int argc, char* argv[])
{
```

```
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  return 0;
}
```

.explain-top[
To use the functionality, we first need to `#include` the header where it is declared
]


---

# Next step: load data from file


```
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main (int argc, char* argv[])
{
```

```
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";

* std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  return 0;
}
```

.explain-top[
To read a file, we need to create a variable of type `std::ifstream`
- this is an instance of an _input file stream_

We call this variable `infile` 
- a name that will hopefully provide some insight into what its purpose will be. 

We immediately _construct_ this instance by giving it the name of the file
to open (`args[1]`). 
]


---

# Next step: load data from file


```
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main (int argc, char* argv[])
{
```
```
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";

  std::ifstream infile (args[1]);
* if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  return 0;
}
```

.explain-top[
It is _always_ a good idea to check for errors when opening a file
- maybe the file doesn't exist, or the name is mis-spelled, or we do not have
  permissions to access the file

The simplest way to check for errors is to use the `std::ifstream` class' _not_ (`!`) operator 
- this is an example of _operator overloading_ (to be covered later in the
  course)
]


---

# Next step: load data from file


```
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main (int argc, char* argv[])
{
```
```
  std::cerr << "reading fragments from file \"" << args[1] << "\"...\n";

  std::ifstream infile (args[1]);
  if (!infile) {
*   std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
*   return 1;
  }

  return 0;
}
```

.explain-top[
If an error is detected, it is good practice to:
- report as much information about the error as we can 
  - this will help anyone using our program (including ourselves!) figure out
    what went wrong
- interrupt execution of the program in some appropriate way 
  - unless there is some reasonable way to deal with the error
  - Here, the cleanest strategy is to return from `main()` with a non-zero exit
    code
]


---

# Exit code

In computing, programs will always provide an _exit code_ when they terminate.

--

The exit code is used to report success or failure to other programs
- and sometimes (though rarely) the _reason_ for the failure 

--

We can query the exit code of the last command in the terminal using the
special shell variable `$?` - for example:
```
$ g++ shotgun.cpp -o shotgun
$ ./shotgun bogus.txt
ERROR: failed to open file "bogus.txt" - aborting
$ echo $?
1
```

---

# Using exit code with the shell `&&` operator

We can already use these exit codes to make our lives a little bit easier:

We can instruct the shell to compile our code, and _if successful_, also run
the program we've just compiled. 

--

We can do this very easily using [the `&&` operator](https://medium.frnn.dev/understanding-and-in-linux-bash-navigating-command-sequences-like-a-pro-fe5e72489da1):
```
$ g++ shotgun.cpp -o shotgun && ./shotgun bogus.txt
```

--

In the above, the `&&` operator means: run the command on the left, and if its exit
code is zero (success), run the command on the right

- since `g++` is a regular program, its exit code should also reflect
  successful execution

--
<br>

We can also use the `||` operator, with the opposite meaning:
- only run the second command if the first reports failure (non-zero exit code)

---

# Next step: load data from file

Now we have a `std::ifstream` open and ready to read from, we can use the same
interface as we have already used with `std::cout` and `std::cerr`:
- this time, we use the _extraction operator_, `>>`

--

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

* std::string frag;
* infile >> frag;

  return 0;
}
```

---

# Next step: load data from file

Now we have a `std::ifstream` open and ready to read from, we can use the same
interface as we have already used with `std::cout` and `std::cerr`:
- this time, we use the _extraction operator_, `>>`

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

* std::string frag;
  infile >> frag;

  return 0;
}
```

.explain-top[
Here, we create an _instance_ of `std::string`, and call this variable `frag`
- this will hold the value of the string we are about to read from file
]

---

# Next step: load data from file

Now we have a `std::ifstream` open and ready to read from, we can use the same
interface as we have already used with `std::cout` and `std::cerr`:
- this time, we use the _extraction operator_, `>>`

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  std::string frag;
* infile >> frag;

  return 0;
}
```

.explain-top[
Next, we use the extraction operator (`>>`) to read the first string from the
file into our variable `frag`
]

---

# Next step: load data from file

But we need to read more than one string from the file. To do this, we are
going to read the data into a vector strings

--

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  std::string frag;
* std::vector<std::string> fragments;
* while (infile >> frag)
*  fragments.push_back (frag);

  return 0;
}
```

---

# Next step: load data from file

But we need to read more than one string from the file. To do this, we are
going to read the data into a vector strings

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  std::string frag;
* std::vector<std::string> fragments;
  while (infile >> frag)
   fragments.push_back (frag);

  return 0;
}
```

.explain-middle[
We start by defining a new variable of type `std::vector<std::string>`, called
`fragments`
]

---

# Next step: load data from file

But we need to read more than one string from the file. To do this, we are
going to read the data into a vector strings

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  std::string frag;
  std::vector<std::string> fragments;
* while (infile >> frag)
   fragments.push_back (frag);

  return 0;
}
```

.explain-middle[
We then use a `while` loop to keep reading from the input file stream until the
stream reports `false`
- this should signify the end-of-file
]

---

# Next step: load data from file

But we need to read more than one string from the file. To do this, we are
going to read the data into a vector strings

```
  ...

  std::ifstream infile (args[1]);
  if (!infile) {
    std::cerr << "ERROR: failed to open file \"" << args[1] << "\" - aborting\n";
    return 1;
  }

  std::string frag;
  std::vector<std::string> fragments;
  while (infile >> frag)
*  fragments.push_back (frag);

  return 0;
}
```

.explain-middle[
Every time we successfully read a string from the input file, we append it to
our vector of string (`fragments`) using the `.push_back()` method.
]

---

# More about `std::ifstream`

The `std::ifstream` class provides a lot more functionality, most of which we
will not cover in this course. However, the methods below are commonly used:

- `.open(const std::string& filename)`: open the file given the `filename`.
  This is useful when declaring a `std::ifstream` variable with no filename,
  e.g.:
  ```
  std::ifstream infile;
  ...
  infile.open (filename);
  ```

- `.close()`: close the file once we are done reading. Note that we rarely need
  to invoke this method explicitly since it will be invoked automatically when
  the `infile` variable is destroyed (goes out of scope).


---

# Add more error checking and reporting

It is _always_ a good idea to check for errors where relevant. Here, we check
that the vector of fragments that we just loaded contains at least one entry,
and report the number of fragments loaded:

```
  std::string frag;
  std::vector<std::string> fragments;
  while (infile >> frag)
   fragments.push_back (frag);

* if (fragments.empty()) {
*   std::cerr << "ERROR: file \"" << args[1] 
*             << "\" contains no fragments - aborting\n";
*   return 1;
* }
*
* std::cerr << "read " << fragments.size() << " fragments\n";

  return 0;
}
```

---


# Report basic statistics about the data

Now that we have code to load the data, we can run it and check that it works:

```
$ g++ shotgun.cpp -o shotgun && ./shotgun ../data/fragments-no-reverse-1.txt
reading fragments from file "../data/fragments-no-reverse-1.txt"...
read 190 fragments
```

--

But how do we know we read the data correctly?

--

We can print out the first few fragments, and check they match what we see in
the file. 

--

We can also report basic statistics about the data, such as mean, minimum and
maximum fragment size

---

# Report basic statistics about the data

```
  ...

  std::cerr << "read " << fragments.size() << " fragments\n";

* double sum = 0.0;
* std::string::size_type min = fragments[0].size();
* std::string::size_type max = fragments[0].size();
* for (const auto& f : fragments) {
*   sum += f.size();
*   min = std::min (min, f.size());
*   max = std::max (max, f.size());
* }
* std::cerr << "mean fragment length: " << sum/fragments.size() 
*           << ", range [ " << min << " " << max << " ]\n";

  return 0;
}
```

---

# Report basic statistics about the data

```
  ...

  std::cerr << "read " << fragments.size() << " fragments\n";

  double sum = 0.0;
  std::string::size_type min = fragments[0].size();
  std::string::size_type max = fragments[0].size();
  for (const auto& f : fragments) {
    sum += f.size();
*   min = std::min (min, f.size());
*   max = std::max (max, f.size());
  }
  std::cerr << "mean fragment length: " << sum/fragments.size() 
            << ", range [ " << min << " " << max << " ]\n";

  return 0;
}
```

.explain-top[
Note the use of the `std::min()` and `std::max()` functions
- these return the minimum or maximum (respectively) value of the two arguments
  provided

These are part of the C++ Standard Template Library (STL)
- the STL provides a lot of functionality, but we can only cover
  a fraction of it in this course. 
]


---

# Report basic statistics about the data

```
  ...

  std::cerr << "read " << fragments.size() << " fragments\n";

  double sum = 0.0;
  std::string::size_type min = fragments[0].size();
  std::string::size_type max = fragments[0].size();
  for (`const auto& f` : fragments) {
    sum += f.size();
    min = std::min (min, f.size());
    max = std::max (max, f.size());
  }
  std::cerr << "mean fragment length: " << sum/fragments.size() 
            << ", range [ " << min << " " << max << " ]\n";

  return 0;
}
```

.explain-bottom[
Note also the use of a _const reference_ to an `auto` variable (whose type is
deduced by the compiler from the context). 
- a reference is essentially an _alias_ for an existing variable
- this avoids a needless copy of each element of the `fragments` vector for
  each iteration
- note the use of the ampersand (`&`) symbol in the declaration
]

---

# Report basic statistics about the data

```
  ...

  std::cerr << "read " << fragments.size() << " fragments\n";

  double sum = 0.0;
  std::string::size_type min = fragments[0].size();
  std::string::size_type max = fragments[0].size();
  for (const auto& f : fragments) {
    sum += f.size();
    min = std::min (min, f.size());
    max = std::max (max, f.size());
  }
  std::cerr << "mean fragment length: " << sum/fragments.size() 
            << ", range [ " << min << " " << max << " ]\n";

  return 0;
}
```

Try it out and check that the results match expectations
