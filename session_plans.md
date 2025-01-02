# Week 1

## Introduction to the command-line, first steps

- [what is C++, relationship with C](https://www.geeksforgeeks.org/history-of-c/)
- [the command-line](https://command-line-tutorial.readthedocs.io/)
- [navigating the filesystem](https://command-line-tutorial.readthedocs.io/commands.html)
- [invoking the compiler](https://www.geeksforgeeks.org/compiling-with-g-plus-plus/)
- using an editor: [micro](https://micro-editor.github.io/) (or [notepad++](https://notepad-plus-plus.org/))
- writing our first `hello_world.cpp`
- [including standard headers](https://www.geeksforgeeks.org/header-files-in-c-c-with-examples/)
- [Basic data types](https://www.tutorialspoint.com/cplusplus/cpp_data_types.htm): `bool`, `int`, `float`, `double`
- [the `std::string` class](https://www.w3schools.com/cpp/cpp_strings.asp)
- [command-line arguments](https://medium.com/@mostsignificant/3-ways-to-parse-command-line-arguments-in-c-quick-do-it-yourself-or-comprehensive-36913284460f)
- [the `std::vector` class](https://www.geeksforgeeks.org/vector-in-cpp-stl/)
- [range-based `for` loop](https://www.geeksforgeeks.org/range-based-loop-c/)
- [regular `for` loop](https://www.geeksforgeeks.org/cpp-for-loop/)
- [the `while` loop](https://www.geeksforgeeks.org/cpp-while-loop/)
- [`do`-`while` loop](https://www.geeksforgeeks.org/cpp-do-while-loop/)
- [type inference](https://www.geeksforgeeks.org/type-inference-in-c-auto-and-decltype/): the `auto` keyword
- conditional execution: [the `if` statement](https://www.w3schools.com/cpp/cpp_conditions.asp)
- [statements and compound statements](https://cplusplus.com/doc/tutorial/control/)
- basic error handling


## First project: DNA shotgun sequencing, input/output, functions

- Introduce [DNA shotgun sequencing](https://github.com/KCL-BMEIS/OOP_coursework/tree/main/DNA_shotgun_sequencing) project
- [std::cin, std::cout, std::cerr and their use](https://www.tutorialspoint.com/what-are-cin-cout-and-cerr-streams-in-cplusplus)
- reading data from file: [std::ifstream](https://cplusplus.com/doc/tutorial/files/)
- [(const) references](https://www.geeksforgeeks.org/references-in-cpp/)
- Using algorithms from the C++ [Standard Template Library](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/): [`std::min()`](https://en.cppreference.com/w/cpp/algorithm/min), [`std::max()`](https://en.cppreference.com/w/cpp/algorithm/max)
- writing data to file: [std::ofstream](https://cplusplus.com/doc/tutorial/files)
- [Using and defining functions](https://www.geeksforgeeks.org/functions-in-cpp/)
- [returning values from functions](https://www.geeksforgeeks.org/return-statement-in-cpp-with-examples/)


---

# Week 2

## Multi-file project, error handling

- [type aliasing](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)
- [defining separate header and cpp files](https://www.codeproject.com/Articles/5341253/C-Cplusplus-Headers-and-Source-Files-How-Do-They-W)
  - [compiling and linking](https://www.learncpp.com/cpp-tutorial/introduction-to-the-compiler-linker-and-libraries/)
  - what is a [translation (compilation) unit](https://en.wikipedia.org/wiki/Translation_unit_(programming))
  - [header guards](https://www.geeksforgeeks.org/header-guard-in-c/) and [`#pragma once`](https://includeguardian.io/article/pragma-once-vs-ifndef)
  - [difference between using inverted commas `""` and angled brackets `<>` in `#include` directive](https://www.geeksforgeeks.org/difference-between-include-and-include-in-c-c-with-examples/)
- [the role of the preprocessor](https://www.geeksforgeeks.org/cpp-preprocessors-and-directives/)
- automated build systems 
  - [what they are and why we need one](https://blog.feabhas.com/2021/06/why-we-need-build-systems/)
  - Make, CMake, Ninja, ...
  - introduce [our custom `oop_build` script](https://github.com/jdtournier/simple_build)
- Error handling using [C++ exceptions](https://learn.microsoft.com/en-us/cpp/cpp/errors-and-exception-handling-modern-cpp)
- More practice with functions and string handling
- More on using STL algorithms: [iterators](https://www.geeksforgeeks.org/iterators-c-stl/)


## More string handling, basic debugging

- adding functions to perform required operations to our project
- [variable scope](https://www.geeksforgeeks.org/scope-of-variables-in-c/): global, block, function
- [namespaces](https://www.geeksforgeeks.org/namespace-in-c/)
- [the `inline` keyword](https://www.accu.org/journals/overload/29/166/collyer/) and the [One Definition Rule](https://ryonaldteofilo.medium.com/inline-and-one-definition-rule-in-c-db760ec81fb2)
- adding debugging functionality to our project
  - More command-line handling: [options](https://command-line-tutorial.readthedocs.io/introduction.html#command-line-options)

---

# Week 3

## Advanced string formatting, grouping data

- advanced string formatting using [`std::format()`](https://www.accu.org/journals/overload/29/166/collyer/)
- [grouping data into a `struct`](https://www.geeksforgeeks.org/structures-in-cpp/)
- returning multiple values from functions using [C++17 structured binding](https://www.cppstories.com/2022/structured-bindings/)
- [using `std::string_view` to avoid copies](https://www.geeksforgeeks.org/class-stdstring_view-in-cpp-17/)
- Introducing classes
  - [methods](https://www.geeksforgeeks.org/cpp-class-methods/)
  - [access specifiers](https://www.geeksforgeeks.org/constructors-c/)
- OOP design features:
  - [encapsulation](https://www.geeksforgeeks.org/encapsulation-in-cpp/)
  - [abstraction](https://www.geeksforgeeks.org/abstraction-in-cpp/)

## Classes in C++

- More on classes
  - [class constructor](https://www.geeksforgeeks.org/constructors-c/)
  - [initialiser list](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/)
- [Default function arguments](https://www.geeksforgeeks.org/default-arguments-c/)
- [Constructor delegation](https://www.geeksforgeeks.org/constructor-delegation-c/) (aka constructor chaining)
- [the `const` keyword](https://www.geeksforgeeks.org/const-keyword-in-cpp/):
 - for variables
 - for function arguments
 - [for methods](https://www.geeksforgeeks.org/const-member-functions-c/)
 - [why pass by `const` reference](https://www.geeksforgeeks.org/const-reference-vs-normal-parameter-passing-in-cpp/)

---

# Week 4

## fMRI project

- more practice with:
  - basic program structure and command-line argument handling
  - file handling and loading data
  - error handling and debugging
  - creating a class
- handling multidimensional data arrays
- new concepts: 
  - [list (uniform) initialisation](https://www.geeksforgeeks.org/uniform-initialization-in-c/)
  - [casting operators](https://www.geeksforgeeks.org/casting-operators-in-cpp/)
  - [getters and setters](https://www.geeksforgeeks.org/cpp-getters-and-setters/)
  - [command-line globbing and wildcards](https://www.shell-tips.com/bash/wildcards-globbing/)


## Using external libraries, operator overloading

- more practice with: 
  - handling command-line arguments and options
  - file handling
  - writing functions
- using external libraries
  - simple example of using an external header-only library: Donald's [terminal_graphics](https://github.com/jdtournier/terminal_graphics) project
- [function overloading](https://www.geeksforgeeks.org/function-overloading-c/)
- [overloading the subscript or array indexing operator](https://www.geeksforgeeks.org/overloading-subscript-or-array-index-operator-in-c/)
- [overloading the function call operator](https://www.geeksforgeeks.org/overload-function-call-operator-in-cpp/)
- [overloading the stream insertion operator](https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/)


---

# Week 5

## Lambda expressions & template programming

- [class templates](https://www.geeksforgeeks.org/templates-cpp/)
- [the `<cmath>` header](https://www.w3schools.com/cpp/cpp_ref_math.asp) and associated functions
- [lambda expressions](https://www.geeksforgeeks.org/lambda-expression-in-c/)
- [use of lambda expressions with the C++ Standard Template Library (STL)](https://medium.com/@m4xshen/the-beauty-of-c-stl-algorithm-and-lambda-205e6f0d8335)
- [the C++20 `std::ranges` library](https://www.geeksforgeeks.org/cpp-20-ranges-library/)
- [function templates](https://www.geeksforgeeks.org/templates-cpp/)
- finishing touches to fMRI project


## Robot arm project & inheritance

- introduce the modular robot arm project
- [inheritance](https://www.geeksforgeeks.org/inheritance-in-c/)
- [virtual functions](https://www.geeksforgeeks.org/virtual-function-cpp/)
  - difference between virtual and overridden functions
  - static / dynamic binding 
- [pure virtual functions](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
  - abstract and concrete classes
- [class vs. object vs. instance](https://www.codementor.io/@stevedonovan/class-vs-object-vs-instance-14i2s2lu6r)


---

# Week 6

## Object-oriented design

- aggregation, composition, inheritance
- object lifetime & ownership
- [OOP design principles](https://hackernoon.com/10-oop-design-principles-every-programmer-should-know-f187436caf65) ([SOLID](https://www.digitalocean.com/community/conceptual-articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design)): 
  - DRY (Don’t repeat yourself)
  - Encapsulate What Changes
  - Open Closed Design Principle
  - Single Responsibility Principle
  - Dependency Injection or Inversion principle
  - Favor Composition over Inheritance
  - Liskoff substitution principle
  - Interface Segregation Principle
  - Programming for Interface not implementation
  - Delegation principles
- UML overview
- UML class diagrams
- typical workflow for the OOP design
  - [blog abour OOP design process](https://www.mdfaisal.com/blog/first-5-steps-of-object-oriented-design)

## Peer marking

- Peer marking
- go through solution and marking scheme
- ...?

---

# Week 7


## stringstream, finalise robot arm project

- more practise with `for` loops, functions, and file I/O
- Introduce [std::istringstream](https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/)
- finalise robot arm project

## TBC

---

# Week 8

## Practice session: design and initial implementation

## Practice session: finalise project

---

# Week 9

## TBC

## TBC


---


# Week 10

## pointers and manual memory management

- pointers
- C-style arrays
- C-style string handling
- `new` / `delete`
- memory leaks
- double free
- array `new[]` & `delete[]`


## Pointers and manual memory management

- using constructor / destructor / copy constructor / assignment operator to manage memory
- smart pointers? 
- RAII?

---

# Topics not yet covered:

- [`switch` statement](https://www.geeksforgeeks.org/switch-statement-in-cpp/)
- jump statements: [`break` and `continue`](https://www.w3schools.com/cpp/cpp_break.asp)
- [conditional (ternary) operator (`?:`)](https://www.geeksforgeeks.org/cpp-ternary-or-conditional-operator/)
- [Resource Acquisition Is Initialization (RAII)](https://www.geeksforgeeks.org/resource-acquisition-is-initialization/)
- [the function stack](https://www.geeksforgeeks.org/function-call-stack-in-c/)
- [recursion](https://www.geeksforgeeks.org/cpp-recursion/)
- categories using [enumerated types (`enums`)](https://www.geeksforgeeks.org/enumeration-in-cpp/)
- [class destructor](https://www.geeksforgeeks.org/destructors-c/)
- multi-line comments and why they're usually best avoided
- dynamic vs. static type checking
- `std::array`
- difference between `std::vector::operator[]` and `std::vector::at()` in terms of bounds checking
- expressions with mixed types, implicit type casting, integer promotion, ...
- destructors
- static data members
- copy constructor
- virtual functions
- pure virtual functions
- abstract and concrete classes
- inheritance vs. composition
- member function overloading
- difference between virtual and overloaded functions
- static / dynamic binding 
- OOP design - REQUIRES A LOT OF THOUGHT!
- UML
- composition / aggregation / inheritance
- operator overloading
- friend functions
- operator overloading: global or member?
- `this` pointer
- overloading the assignment operator
- runtime vs. compile-time/static polymorphism
- object lifetime & ownership
  - relationship to composition & aggregation, etc.
- OOP principles: encapsulation, polymorphism, inheritance, abstraction
- [OOP design principles](https://hackernoon.com/10-oop-design-principles-every-programmer-should-know-f187436caf65) ([SOLID](https://www.digitalocean.com/community/conceptual-articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design)): 
  - DRY (Don’t repeat yourself)
  - Encapsulate What Changes
  - Open Closed Design Principle
  - Single Responsibility Principle
  - Dependency Injection or Inversion principle
  - Favor Composition over Inheritance
  - Liskoff substitution principle
  - Interface Segregation Principle
  - Programming for Interface not implementation
  - Delegation principles




---
  
# Open questions:

- how use inheritance in a meaningful way without pointers?
  - should be fine using *references* instead
- how to demonstrate aggregation without pointers?
  - can demonstrate construction of member (const) reference 
  - note that [non-const references are not recommended in the C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-constref)
    - but only because this makes the class copy-constructable, but not copy-assignable
    - if anything, highlights issues of ownership and lifetime, which are a serious problem with aggregation
- [blog abour OOP design process](https://www.mdfaisal.com/blog/first-5-steps-of-object-oriented-design)
  - how to teach design?
  - how to *assess* design?

---

# NOT covered in course:

- Why not use pointers and manual memory management? See recommendations in this video:
  - [Kate Gregory: Stop Teaching C](https://www.youtube.com/watch?v=YnWhqhNdYyk)
  - and these blog posts:
      - [C++ Will No Longer Have Pointers](https://www.fluentcpp.com/2018/04/01/cpp-will-no-longer-have-pointers/)
      - [Raw Pointers Are Gone!](https://arne-mertz.de/2018/04/raw-pointers-are-gone/)
      - [No New New: Raw Pointers Removed from C++](https://www.modernescpp.com/index.php/no-new-new/)
      - [Deprecating Raw Pointers in C++20](https://www.cppstories.com/2018/04/deprecating-pointers/)
      - [No more pointers](https://blog.tartanllama.xyz/no-pointers/)


