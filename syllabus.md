---
layout: default
title: Syllabus - Object-Oriented Programming (5CCYB041)
---

# Syllabus for Object-Oriented Programming (5CCYB041)

This is a list of topics to be covered on this module. Note that during the course, topics will *not* necessarily be introduced in the order presented on this page.

## The Unix command-line
- what is the command-line, the terminal, and the shell
- the filesystem, absolute & relative paths
- basic commands: `ls`, `pwd`, `cd`, `cp`, `mv`, `rm`, ...
- command structure, arguments & options
- using an editor (whether terminal-based or external)

## Compiling a C++ program
- difference between *compiled* and *interpreted* languages
- invoking the compiler
- useful compiler flags: `-o`, `-O2`, `-Wall`, `-c`, `-I`, `-g`
- different stages of compilation: preprocessor, compiler, linker
- compiling and linking programs split over multiple files
- understand concept of build systems to simplify building complex programs (`Make`, `CMake`, ...)
- using the `oop_build` script supplied as part of this course

## Basic structure of a program
- the `main()` function
- preprocessor directives, particularly `#include`
- difference between using inverted commas `""` and angled brackets `<>` in `#include` directive
- handling command-line arguments
- return value / exit code

## Data types & variables
- basic data types: `int`, `short`, `char`, and their `unsigned` versions, `float`, `double`, ...
- declaring a variable
- defining a variable
- the `auto` keyword
- Compound data types: structs & classes
- Dynamic vs. static type handling
- Basic operators: `=`, `+`, `-`, `*`, `/`, `%`, `++`, `--`, `<<`, `>>`, `+=`, `-=`, `*=`, `/=`
- implicit type conversions

## Control flow
- the `if`/`else` statement
- statements & compound statements
- the standard `for` loop
- the range-based `for` loop
- the `while` loop
- the `do`/`while` loop
- conditional operators: `==`, `!=`, `<`, `>`, `<=`, `>=`
- compound conditional expressions using logical operators: `&&`, `||`, `!`
- the conditional (ternary) `?:` operator

## Functions
- purpose of functions (control flow, code re-use, code clarity, ...)
- function declaration vs. definition
- general syntax
- function arguments, default arguments
- return statement, return type
- returning _multiple_ values from functions using [C++17 structured binding](https://www.cppstories.com/2022/structured-bindings/)
- function overloading
- `inline` keyword
- lambda functions
- lambda capture
- use of lambda functions in STL algorithms

## File input/output
- [file streams](https://cplusplus.com/doc/tutorial/files/) (or alternatively, on [GeeksforGeeks](https://www.geeksforgeeks.org/file-handling-c-classes/))
- [`std::cin`, `std::cout`, `std::cerr` and their use](https://www.tutorialspoint.com/what-are-cin-cout-and-cerr-streams-in-cplusplus)
- interacting with files: `std::ifstream`, `std::ofstream`
- [converting between text & built-in data types](https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/) and [vice-versa](https://www.geeksforgeeks.org/converting-number-to-string-in-cpp/)
- using [insertion](https://learn.microsoft.com/en-us/cpp/standard-library/using-insertion-operators-and-controlling-format) and [extraction](https://learn.microsoft.com/en-us/cpp/standard-library/using-extraction-operators) operators (`<<`, `>>`)
- [checking for errors](https://www.edureka.co/blog/file-handling-in-cpp/#check-the-file-for-errors)

## Error handling using exceptions
- [throwing exceptions](https://www.geeksforgeeks.org/exception-handling-c/)
- catching exceptions
- catching exceptions by type
- using multiple `catch` statements
- [rethrowing exceptions](https://www.geeksforgeeks.org/rethrowing-an-exception-in-cpp/)
- what happens when exceptions are thrown: [stack unwinding](https://www.geeksforgeeks.org/stack-unwinding-in-c/)
- [why you should *not* throw exceptions from a destructor](https://www.experts-exchange.com/articles/18350/C-Throwing-exceptions-from-destructors.html)

## Namespaces
- what they are, and their purpose
- `using` declaration
- why indiscriminate use of `using namespace std;` is discouraged
- declaring your own namespace (not assessed)

## Classes
- simple `struct`, difference between `struct` & `class`
- declaration & definition
- general syntax
- `public`, `protected`, `private`
- methods / member functions
- special methods: constructor, copy-constructor, destructor
- implicit inline methods
- syntax for defining methods outside class, and where to place method definitions

## Inheritance
- purpose and syntax
- `public`, `protected` and `private` inheritance
- function hiding
- virtual functions
- pure virtual functions and abstract classes

## OOP design
- OOP principles: encapsulation, abstraction, inheritance, polymorphism
- UML, focussing on UML class diagrams
- aggregation, composition, inheritance
- SOLID principles and others
- prefer composition over inheritance
- object lifetime and ownership
- Resource acquisition is initialisation (RAII)

## Templates
- what they are, and why they're useful
- general syntax
- template type and non-type parameters
- `typename` & `class` keywords
- static / compile-time polymorphism
- template functions
- template classes
- template class methods
- why template functions & methods must all be defined in headers, not cpp files

## The Standard Template Library
- useful containers: `std::vector`, `std::array`, `std::string`
- algorithms & iterators
- the `std::ranges` library
- useful algorithms: `std::ranges::sort()`, `std::ranges::max()`, `std::ranges::min()`, `std::ranges::find()`, ...

## Memory management (for information only - not assessed, and *not* to be used on this course)
- pointers
- C-style arrays
- memory allocation & deallocation using `new` & `delete`
- array allocation & deallocation using `new[]` & `delete[]`
- allocating on the heap vs. allocating on the stack
- why use of raw pointers and manual memory management is to be avoided unless absolutely necessary
