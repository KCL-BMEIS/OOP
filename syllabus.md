---
layout: default
title: Syllabus - Object-Oriented Programming (5CCYB041)
---

# Syllabus for Object-Oriented Programming (5CCYB041)

## The Unix command-line
- What is the command-line, the terminal, and the shell
- The filesystem, absolute & relative paths
- Basic commands: `ls`, `pwd`, `cd`, `cp`, `mv`, `rm`, ...
- Command structure, arguments & options

## Compiling a C++ program
- difference between *compiled* and *interpreted* languages
- invoking the compiler
- useful compiler flags: `-o`, `-O2`, `-Wall`, `-c`, `-I`, `-g`
- different stages of compilation: preprocessor, compiler, linker
- compiling and linking programs split over multiple files
- using build systems to simplify building complex programs
- using the `oop_build` script supplied as part of this course

## Basic structure of a program
- the `main()` function
- preprocessor directives, particularly `#include`
- difference between using inverted commas `""` and angled brackets `<>` in `#include` directive
- handling command-line arguments
- return value / exit code

## Data types & variables
- Basic data types: `int`, `short`, `char`, and their `unsigned` versions, `float`, `double`, ...
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
- function overloading
- `inline` keyword
- lambda functions
- lambda capture
- use of lambda functions in STL algorithms

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

## Inheritance


## OOP design
- SOLID principles and others
- prefer composition over inheritance
- Resource acquisition is initialisation (RAII)

## Templates

## The Standard Template Library
- useful containers: `std::vector`, `std::array`, `std::string`
- the `std::ranges` library
- useful algorithms: `std::ranges::sort()`, `std::ranges::max()`, `std::ranges::min()`, `std::ranges::find()`, ...

## Memory management (for information only - not assessed, and *not* to be used in course)
- pointers
- C-style arrays
- memory allocation & deallocation using `new` & `delete`
- array allocation & deallocation using `new[]` & `delete[]`
- why use of raw pointers and manual memory management is to be avoided unless absolutely necessary
