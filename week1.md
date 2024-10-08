---
layout: presentation
title: "Week 1: Introduction"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
## Week 1: Introduction

---

# Teaching team

## Module leads

.center[.teamcols[
.col[ 
[J-Donald Tournier](mailto:jacques-donald.tournier@kcl.ac.uk) ]
.col[ 
![:scale 100%](images/donald.jpg)] 
.col[ 
![:scale 100%](images/michela.jpg)]
.col[
[Michela Antonelli](mailto:michela.antonelli@kcl.ac.uk) ]
] ]

## Lecturers

.center[.teamcols[
.col[
[Tobias Wood](mailto:tobias.wood@kcl.ac.uk) ]
.col[ 
![:scale 100%](images/toby.jpg) ] 
.col[ 
![:scale 100%](images/marc.jpg) ]
.col[ [Marc Modat](marc.modat@kcl.ac.uk) ] 
] ]

---

# Course overview

## Structure

- 10 week course, with 2-hour tutorials twice a week
- on week 6, peer-assessed exercise (formative only)

--

## Assessment
.columns[
.col[
- first coursework (10%)
  - instructions available 6 February
  - submission due 25 February

- second coursework (30%)
  - instructions available 13 March
  - submission due 3 April
]

.col[
- final exam (60%)
  - this is a _written_ exam
  - please look through example questions provided
]
]

---

# Course overview

## Objectives

This course is an introduction to object-oriented programming using C++.

--

It will provide you with an understanding of:

- the Unix command-line

--
- how to handle and manage files and commands in a Unix environments

--
- the basics of programming using C++

--
- the basics of the object-oriented programming paradigm

--
- how to manage and process complex data structures

--

Where possible, the course aims to provide with transferable skills that can be
applied in other situations

--

- for many of you, these skills will prove valuable for your final project
- _even if you don't use C++!_

---

# Course overview

## It is _not_ intended as a full C++ course

--

We will _not_ cover concepts that many other C++ courses would consider
fundamental, including:

--
- C-style arrays
- memory management
- pointers or smart pointers
- ...

--

Why are we avoiding these topics?

- They cause too much confusion too early. You can learn about these topics
  when you have become sufficiently familiar with the basics

--
- Many of these features are discouraged in modern C++, and are best avoided
  altogether where possible

--

Many other C++ topics will also not be covered as they are too advanced

---

# How to make the most of this course

Learning to program can only be done through experience
- please make every effort to attend all the tutorials!

--
- don't hesitate to ask if anything is unclear or you need any help

--
- go through all the examples

--
- search online for examples and explanations!
  - but bear in mind that online sources may use concepts we have
    deliberately left out of the course!

--

Good online resources include:

- [cplusplus.com](http://www.cplusplus.com/) C++ tutorial and reference, recommended
- [Bucky's C++ programming tutorials](https://www.youtube.com/playlist?embed=no&list=PLAE85DE8440AA6B83): collection of helpful videos on different C++ concepts
- [cprogramming.com](http://www.cprogramming.com/tutorial/c++-tutorial.html): C++ tutorials and discussion forum for questions and answers
- [cppreference.com](http://en.cppreference.com/w/cpp): very thorough C++ reference, recommended
- [Hackerrank](https://www.hackerrank.com/): interactive code exercises
- [C++ FAQ](https://isocpp.org/faq): great resource with answers to general or specific questions

---

# The command-line

![:right 40%](images/MSYS.png)

In this course, we will be using a Unix-like terminal environment 
and running all of our code within the terminal. 

- This means we need to understand the Unix command-line.

--

On the KCL-managed Windows systems, we will rely on the [MSYS2
project](https://www.msys2.org/). 

- Use the **`MSYS2 MSYS` terminal** (ignore the other variants)
- This provides a Unix-like environment, preloaded with all the necessary software.
- Start it from the _Start_ Menu (search for "MSYS")

--

To install this on your own Windows computer, follow the instructions on KEATS.<br>
On macOS, you can immediately use the [Terminal
application](https://support.apple.com/en-gb/guide/terminal/welcome/mac).

---

# The command-line

To get started, click on the _Start_ menu and search for the `MSYS2 MSYS`
application

.note[
ignore the other options, you need to use the `MSYS` variant!]


--

<br>

The terminal is an application that allows you to enter _commands_ and view
their output

--

The commands are _interpreted_ by another program called the _command
intrepreter_ 
- typically referred to as 'the shell'

--
- here, we are using the [Bourne-again shell (`bash`)](https://en.wikipedia.org/wiki/Bash_(Unix_shell%29)

--

.note[
On Windows, the standard shell used to be the DOS shell, though MicroSoft
has since introduced the more modern PowerShell &ndash; we won't be using either of
them on this course!]

---

# The command prompt

When started, the shell will show a _prompt_, and wait for you to enter
commands.

--

The prompt will (typically) take the form:
```
user@hostname:folder $
```

--
where:

- `user` is your current username

--
- `hostname` is the name of the computer this session is currently running on

--
- `folder` is the folder you are currently operating in (the _current working
  directory_)

.note[
The `~` symbol is used as a shorthand for your home folder]

---

# Navigating using the command-line

Try the following commands:

- `ls` &emsp; list the files & folders in the current folder
  - `ls -l` &emsp; list in long format (permissions, ownership, file sizes, ...)
  - `ls Desktop` &emsp; list the files in the `Desktop` folder 

- `pwd` &emsp; print the current working directory 

- `cd` &emsp; change directory
  - `cd` &emsp; change to your _home folder_
  - `cd ..` &emsp; change to the _parent directory_ relative to the current folder
  - `cd Documents` &emsp; change to the `Documents` folder 
  - `cd ../Desktop` &emsp; change to the `Desktop` folder in the current folder's parent directory


.note[
In computing, the terms _folder_ and _directory_ are often used interchangeably]

---

# Navigating using the command-line

You can see that the commands in the previous slide allow you to move around
and inspect the _filesystem_, in much the same way as you would using your file
manager. 

<br>
<br>
Try using the Windows Explorer to verify that the listings provided on the
command-line correspond to the folders on your account.

.note[
on macOS, you can use the _finder_ application instead]


---

# Command-line tips & tricks

Typing long commands over and over again can quickly get tiresome.
Thankfully, modern command interpreters provide handy shortcuts to make life
easier
- please get used to them as early as you can!

--

The **up/down arrows** allow you recall previously typed commands, which you can
then edit and modify as required (using the left/right arrows)
- very useful when you've made a simple typo on a long command!

--

The **TAB key** asks the shell to complete the current word if it has enough
information to do so. For example, typing `cd Doc`, then pressing the `TAB` will complete the
  command to `cd Documents` 
  - *provided* there is a `Documents` folder at that location
  - *and* there are no other folders that start with `Doc`

--

.note[To learn more about how to use the shell, please take a look through any
of the many tutorials available online, in particular our own [Introduction to the
Unix command-line](https://command-line-tutorial.readthedocs.io/)]

---

# Writing our first C++ program

![:right 40%](images/micro.png)
We need to create and edit a text file to hold our code. 
To do this, we need to use a **text editor**
- There are many good editors available, but some are better suited for writing C++

--

- On KCL-managed systems, you can use a simple terminal-based editor called
  [micro](https://micro-editor.github.io/)

--

- other options include [Notepad++](https://notepad-plus-plus.org/) (Windows
  only), [Sublime Text](https://www.sublimetext.com/), 
  [VS Code](https://code.visualstudio.com/), [BBEdit](https://www.barebones.com/products/bbedit/) 
  (macOS only), ...

--

.note[
We do not recommend the use of full-blown _integrated development environments_
(IDE) early on. While convenient, these obscure the processes involved, making
it difficult for newcomers to understand where things might go wrong.
<br>
<br>
It is also very difficult to find an IDE that is both easy to install and works
flawlessly across all relevant platforms. We have
therefore decided to avoid the use of IDEs on this course.]



---

# Writing our first C++ program

![:right 60%](images/new_folder.png)

We need to start by creating a folder to store our code
- We can use the Windows File Explorer (or Finder on macOS), then navigate to
  this folder using the command-line


--

<br>
<br>
- ... or we can use the command-line straight away!

---

# Create a folder on the command-line

- navigate to the location where you want to create the folder, for example:
  ```bash
  $ cd ~/"OneDrive - King's College London/Documents/"
  ```

--
- use the `mkdir` command to create the desired folder:
  ```bash
  $ mkdir OOP
  ```

--
- navigate to this folder, and create a subfolder for this first example:
  ```bash
  $ cd OOP/
  $ mkdir hello_world
  ```

--
- finally, change directory into this folder:
  ```
  $ cd hello_world
  ```


---

# Our first C++ program: Hello World

Once we are in the right folder, we need to create a new text file called
`main.cpp` with these contents:

```C++
#include <iostream>

int main ()
{
  std::cout << "Hello World\n";
  return 0;
}
```

--

<br>
Create a new text file called `main.cpp` using `micro` (or whichever editor you
have decided to use), type in the contents, and save the file.
```
$ micro main.cpp
```

---

# Useful shortcuts for 'micro' text editor


.columns[
.col[
- `Ctrl+Q` &emsp; close current file
- `Ctrl+S` &emsp; save curent file
- `Ctrl+O` &emsp; open file


- `Crtl+C` &emsp; copy currently selected text
- `Crtl+X` &emsp; cut currently selected text
- `Crtl+K` &emsp; cut current line
- `Ctrl+V` &emsp; paste previously copied text
- `Crtl+D` &emsp; duplicate current line


- `Crtl+Z` &emsp; undo
- `Crtl+Y` &emsp; redo
]

.col[
- `Ctrl+T` &emsp; new tab
- `Ctrl+Alt+>` &emsp; Next Tab
- `Ctrl+Alt+<` &emsp; Prev Tab


- `Ctrl+F` &emsp; search
- `Ctrl+N` &emsp; next match
- `Ctrl+P` &emsp; previous match


- `Tab` &emsp; autocomplete / indent selection
- `Alt+Tab` &emsp; un-indent selection


- `Ctrl+G` &emsp; help
- `Ctrl+b` &emsp; shell prompt
]
]

See the [online documentation](https://github.com/zyedidia/micro/blob/master/runtime/help/keybindings.md#default-keybinding-configuration)
for the complete listing.


---

# Compiling our program

The code we have written in the file `main.cpp` cannot be executed as it is.
- it is _human readable_ code, designed for us to more conveniently express
  what the program should do

--

To use the program, we need to _compile_ it
- in simple terms, we need to translate our code into _machine instructions_ that
  the computer can execute directly

--

We do this by running the _compiler_ on our code:
```
$ g++ main.cpp
```

--

This should produce a new _executable_ file in the current working directory:
```
$ ls
a.exe  main.cpp
```

---

# Running our program

Now that we produced an executable, we can run it.

--

By default, the shell looks for commands to run in a predefined set of folders,
as listed in the system `PATH`.
- simply typing `a.exe` will not (normally) work &ndash; *unless* `a.exe` is
  in one of these folders.

--

However, we can provide the explicit location of our executable when typing the
command &ndash; *without* modifying the system `PATH`

--

Our command is in the current folder, which we can refer to using the `.` symbol. <br>
We can therefore type:
```
$ ./a.exe
Hello, world!
```

--

.note[If necessary, search online for more information about the `PATH`, e.g.
[wikipedia](https://en.wikipedia.org/wiki/PATH_(variable%29)]


---

# Controlling the output of the compiler

By default, the compiler will produce an executable called `a.exe`
- this is true for MSYS2 &ndash; on many other platforms, this will be `a.out`

--

We can control the name of the executable using the `-o` [command-line
option](https://command-line-tutorial.readthedocs.io/introduction.html#command-line-options):
```
g++ main.cpp -o main
```

--

And invoke the resulting executable as before:
```
$ ./main
Hello, world!
```

---

# Understanding our 'hello world' example

```C++
#include <iostream>

int main ()
{
  std::cout << "Hello World\n";
  return 0;
}
```
Let's look through our example code again and go through each line

---

# Understanding our 'hello world' example

```C++
*#include <iostream>

int main ()
{
  std::cout << "Hello World\n";
  return 0;
}
```

Lines that start with a `#` symbol are so-called _preprocessor directives_

--

The `#include` directive requests inclusion of the contents of the `iostream` _header _

--

Header files are normal C++ files that declare functionality that we might need to use

--

The `iostream` header declares the input/output stream functionality for
printing to the terminal via `std::cout` &ndash; which is why we need to include it


---

# Understanding our 'hello world' example

```C++
#include <iostream>

*int main ()
{
  std::cout << "Hello World\n";
  return 0;
}
```

This is the declaration of the `main()` function

--

The `main()` function is the *entry point* for any program

--

By convention, we declare it as returning an integer (`int`)

--

We'll see more about this when we cover functions

---

# Understanding our 'hello world' example

```C++
#include <iostream>

int main ()
{
* std::cout << "Hello World\n";
  return 0;
}
```

Next, we feed the *string* "Hello World" to the *standard output*
stream, `std::cout`

--

Note the use of the *insertion operator*, `<<`
- This line reads as: insert the string "Hello World" into the `std::cout` IO
  stream

--

Note also the trailing `\n` *escape sequence* at the end of the string
- The backslash `\` character can be used to *escape* the normal interpretation
  of the next character
- Here, the sequence `\n` translates into the *newline* character

---

# Understanding our 'hello world' example

```C++
#include <iostream>

int main ()
{
  std::cout << "Hello World\n";
* return 0;
}
```

Finally, we return from `main()`, which marks the end of our program

--

We return the value 0 to indicate success (no errors)

--

This value is the *exit code* of our program. It can be used by other programs, or
by the shell, to detect any errors during execution
- by convention, any non-zero value signals that an error occurred
- different error codes can sometimes be used to signal different types of errors

---

# Understanding our 'hello world' example

```C++
#include <iostream>

int main ()
{
* std::cout << "Hello World\n";
* return 0;
}
```

Note the use of semicolons `;` to mark the end of each of these lines

--

These lines are individual *statements*
- in C++, the semicolon marks the end of the statement
- technically, these statements could both be on the same line &ndash; only the
  semicolon matters

---

# Understanding our 'hello world' example

```C++
#include <iostream>

int main ()
*{
  std::cout << "Hello World\n";
  return 0;
*}
```

Note also the use of curly brackets (or *braces*, or *curly braces*) to enclose
the code for the main function

--

In C++, braces are used to group statements together. We will see more about
this later



---

# Exercises

- Modify `main.cpp` to remove the newline character, then compile and run the
  executable. What effect does this have?

- Modify `main.cpp` to remove the `#include` line, then compile. What effect
  does this have?

- Modify `main.cpp` to remove the semicolon after `return 0;`, then compile.
  What effect does this have?

---

# Command-line arguments

To interact with our program, we need some way to pass information to it
- for example, the name of a file to process, or the value of some parameter

--

We can use [command-line arguments](https://command-line-tutorial.readthedocs.io/introduction.html#command-line-arguments) 
to do this. This requires a minor modification to the declaration of our `main()` function:
```
int main (int argc, char* argv[])
```

--

Unfortunately, the arguments are provided as a C-style array of pointers &ndash; features that we are trying hard to avoid on this course!

For this reason, we recommend immediately converting these arguments into a more modern form: a vector of strings

---

# Command-line arguments

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  // now we can access the command-line arguments:
  std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

This is the way we recommend handling command-line arguments on this course
- Please use this structure for your own programs

--

Let's step through the program to understand each step

---

# Command-line arguments

```
#include <iostream>
*#include <vector>
*#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  // now we can access the command-line arguments:
  std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

We need to include two additional headers: `<vector>` and `<string>`
- these provide the functionality required to form a vector of strings

---

# Command-line arguments

```
#include <iostream>
#include <vector>
#include <string>

*int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  // now we can access the command-line arguments:
  std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

We need to modify the declaration of the `main()` function to accept additional arguments
- these provide the information required to access the command-line arguments

---

# Command-line arguments

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
* std::vector<std::string> args (argv, argv+argc);

  // now we can access the command-line arguments:
  std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

This line declares a new variable called `args`, of type `std::vector<std::string>` (a vector of strings)

--
- It is initialised from the arguments passed to `main()`

--
- Don't worry about the syntax for now &ndash; we will fill in the blanks in due course

---

# Command-line arguments

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  // now we can access the command-line arguments:
* std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

Here, we simply display the value of the first argument by feeding it to standard output
- each argument can be accessed using the subscript operator `[]`

---

# Command-line arguments

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

* // now we can access the command-line arguments:
  std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

A line starting with `//` denotes a *comment*
- The compiler will ignore any text after this until the end of the line

--
- You are strongly encouraged to use comments to explain anything that isn't immediately obvious in your own code!


---

# Command-line arguments

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  // now we can access the command-line arguments:
  std::cout << "first argument is " << argv[1] << "\n";
  
  return 0;
}
```

Now modify your own code as shown above, compile it, and run it.
- What happens if you *don't* provide at least one command-line argument?


---

# Iterating over a vector

In your own code, you will often need to iterate over the contents of a vector

--

The easiest and safest way to do this is to use a [range-based for loop](https://www.geeksforgeeks.org/range-based-loop-c/):

```
for (auto item : vec) 
  statement;
```

---

# Iterating over a vector

In your own code, you will often need to iterate over the contents of a vector

The easiest and safest way to do this is to use a [range-based for loop](https://www.geeksforgeeks.org/range-based-loop-c/):

```
`for` (auto item : vec) 
  statement;
```

- the `for` keyword declares the start of the loop


---

# Iterating over a vector

In your own code, you will often need to iterate over the contents of a vector

The easiest and safest way to do this is to use a [range-based for loop](https://www.geeksforgeeks.org/range-based-loop-c/):

```
for (auto item : `vec`) 
  statement;
```

- the `for` keyword declares the start of the loop

- `vec` is the *container* (e.g. a `std::vector`) whose elements we wish to iterate over


---

# Iterating over a vector

In your own code, you will often need to iterate over the contents of a vector

The easiest and safest way to do this is to use a [range-based for loop](https://www.geeksforgeeks.org/range-based-loop-c/):

```
for (auto `item` : vec) 
  statement;
```

- the `for` keyword declares the start of the loop

- `vec` is the *container* (e.g. a `std::vector`) whose elements we wish to iterate over

- `item` is the variable that will contain a *copy* of each element for processing within the loop


---

# Iterating over a vector

In your own code, you will often need to iterate over the contents of a vector

The easiest and safest way to do this is to use a [range-based for loop](https://www.geeksforgeeks.org/range-based-loop-c/):

```
for (`auto` item : vec) 
  statement;
```

- the `for` keyword declares the start of the loop

- `vec` is the *container* (e.g. a `std::vector`) whose elements we wish to iterate over

- `item` is the variable that will contain a *copy* of each element for processing within the loop

- `auto` is a special keyword, requesting that the compiler *deduce* the type of `item` from the context


---

# Iterating over a vector

In your own code, you will often need to iterate over the contents of a vector

The easiest and safest way to do this is to use a [range-based for loop](https://www.geeksforgeeks.org/range-based-loop-c/):

```
for (auto item : vec) 
  `statement;`
```

- the `for` keyword declares the start of the loop

- `vec` is the *container* (e.g. a `std::vector`) whose elements we wish to iterate over

- `item` is the variable that will contain a *copy* of each element for processing within the loop

- `auto` is a special keyword, requesting that the compiler *deduce* the type of `item` from the context

- `statement` is the code to execute for each iteration (for each element in `vec`)


---

# Iterating over command-line arguments

Let's try using the range-based for loop to iterate over the command-line arguments:

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (auto a : args)
    std::cout << "argument: " << a << "\n";
  
  return 0;
}
```

Modify your own code to match and try it out. 


---

# The original for loop

The range-based for loop is a special case of the `for` loop
- more convenient and safer when iterating over *containers*

--
- it is also more modern (introduced in [C++11](https://en.cppreference.com/w/cpp/11))

--

The original `for` loop takes this form:
```
for (init-statement ; condition ; expression)
  statement;
```

---

# The original for loop

The range-based for loop is a special case of the `for` loop
- more convenient and safer when iterating over *containers*
- it is also more modern (introduced in [C++11](https://en.cppreference.com/w/cpp/11))

The original `for` loop takes this form:
```
for (`init-statement` ; condition ; expression)
  statement;
```

- `init-statement`: *(optional)* a declaration and/or expression to be evaluated before the first iteration. 


---

# The original for loop

The range-based for loop is a special case of the `for` loop
- more convenient and safer when iterating over *containers*
- it is also more modern (introduced in [C++11](https://en.cppreference.com/w/cpp/11))

The original `for` loop takes this form:
```
for (init-statement ; `condition` ; expression)
  statement;
```

- `init-statement`: *(optional)* a declaration and/or expression to be evaluated before the first iteration. 

- `condition`: a test to determine whether to perform the next iteration. If `false`, the loop will terminate.


---

# The original for loop

The range-based for loop is a special case of the `for` loop
- more convenient and safer when iterating over *containers*
- it is also more modern (introduced in [C++11](https://en.cppreference.com/w/cpp/11))

The original `for` loop takes this form:
```
for (init-statement ; condition ; `expression`)
  statement;
```

- `init-statement`: *(optional)* a declaration and/or expression to be evaluated before the first iteration. 

- `condition`: a test to determine whether to perform the next iteration. If `false`, the loop will terminate.

- `expression`: an action to perform after completion of each iteration


---

# The original for loop

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (int n = 0; n < args.size(); n++)
    std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
```

Let's modify our program to use a regular for loop.


---

# The original for loop

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (`int n = 0`; n < args.size(); n++)
    std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
```

For the `init-statement`: declare a variable of type `int` (an integer) and initialise it to zero
- this will serve as our *counter* for the loop

---

# The original for loop

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (int n = 0; `n < args.size()`; n++)
    std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
```

For the `condition`: keep iterating while the counter is less than the size of our container

---

# The original for loop

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (int n = 0; n < args.size(); `n++`)
    std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
```

For the `expression`: increment the counter by one

--
- note the use of the *postfix increment operator*
--
- this is equivalent to `n = n + 1`, or `n += 1` (more on that later)

---

# The original for loop

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (int n = 0; n < args.size(); n++)
*   std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
```

For the `statement`, we display the argument along with its position (`n`) on
standard output
- with a regular `for` loop, we can also keep track of the *index* of the
  argument


---

# The original for loop

```
#include <iostream>
#include <vector>
#include <string>

int main (int argc, char* argv[])
{
  std::vector<std::string> args (argv, argv+argc);

  for (int n = 0; n < args.size(); n++)
    std::cout << "argument " << n << ": " << args[n] << "\n";

  return 0;
}
```

Modify your own code to match, compile it, and run your program with different
arguments to verify that everything works as expected.


---

# Data types

We have already come across a number of different *data types*:
- `int`
- `std::string`
- `std::vector<std::string>`

C++ is a *statically-typed* language
- every variable needs to have its type defined before use
- once defined, a variable cannot change its type


--

Let's go over the main types available in C++

---

# Basic data types (Plain Old Data)

| type name | description | bits | range |
|:----:|:-----:|:---:|:----:|
| `bool` | true/false | ? | `true` or `false` |
| `char` | signed integer | 8 | -127 to 128 |
| `unsigned char` | unsigned integer | 8 | 0 to 256 |
| `short int` | signed integer | 16 | -(2<sup>15</sup>-1) to 2<sup>15</sup> |
| `short unsigned int` | unsigned integer | 16 | 0 to 2<sup>16</sup> |
| `int` | *signed* integer | 32 | -(2<sup>31</sup>-1) to 2<sup>31</sup> |
| `unsigned int` | *unsigned* integer | 32 | 0 to 2<sup>32</sup> |
| `long int` | higher precision signed integer | 64 | -(2<sup>63</sup>-1) to 2<sup>63</sup> |
| `long unsigned int` | higher precision unsigned integer | 64 | 0 to 2<sup>64</sup> |
| `float` | floating-point value | 32 |  &pm;3.4<sup>-38</sup> to &pm;3.4<sup>38</sup> |
| `double` | higher precision floating-point value | 64 |  &pm;1.7<sup>-308</sup> to &pm;1.7<sup>308</sup> |


