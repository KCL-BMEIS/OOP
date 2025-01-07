---
layout: presentation
title: "Week 6, session 1: object-oriented design"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 6, session 1
## object-oriented design

---

# What we have learned so far

**By now, you should be able to:**
.columns[
.col[
- use the terminal and navigate around the filesystem
- write, compile and run a small C++ program
- use `for` loops and `if` statements
- use standard data types, including `std::string` and `std::vector`
]
.col[
- write and use your own functions **and classes**
- read and write basic information to & from file
- handle command-line arguments and options
- split your code across multiple `cpp` and header files
]
]

**You should also have a good understanding of:**
.columns[
.col[
- error handling using C++ exceptions
- (const) references
- variable scope
- **the `const` keyword in various contexts**
]
.col[
- the `inline` keyword
- namespaces
- the compile & link process
- **OOP design principles: abstraction and encapsulation**
]
]

**If you struggle with any of these aspects, please ask for help!**

---

# Abstraction and encapsulation

The [difference between abstraction and encapsulation is far from
obvious](https://www.tonymarston.co.uk/php-mysql/abstraction.txt)!
 
[According to Bjarne Stroustrup](https://www.stroustrup.com/glossary.html), the original developer of C++:
- **abstraction** is the act of specifying a general interface hiding implementation details. 
- **encapsulation** is the enforcement of abstraction by mechanisms that prevent access to implementation details of an object or a group of objects except through a well-defined interface. 

--

*Abstraction* relates to the *process* by which we decide which methods to make
available to users, and which aspects of the implementation (data members, etc)
should be hidden from users
- this is more about the *design* process

--

*encapsulation* relates the *means* by which abstraction is enforced. 
- C++ classes provides a mechanism to achieve encapsulation
- this is more about the *implementation* process

--

In practice, the two concepts go hand in hand: abstraction relies on
encapsulation, and vice-versa

---


