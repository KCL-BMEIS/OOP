---
layout: presentation
title: "Week 5, session 2: pointers, iterators and lambda functions"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 5, session 2
## pointers, iterators<br>and lambda functions

---

# Picking up where we left off

We continue working on our [fMRI analysis
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/fMRI/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/fmri_solution/projects/fMRI/solution)

.explain-bottom[
Make sure your code is up to date now!
]

---

# Pointers and iterators


Many algorithms in the standard template library require an
understanding of [iterators](https://www.geeksforgeeks.org/iterators-c-stl/)
- we have already come across a few places where we needed to interact with
  them

--

Iterators are inspired from the concept of *pointers*
- pointers are an old concept, predating C++
- pointers are a powerful tool, but difficult to understand
  - and very difficult to use safely!

--

To understand iterators, we need to start with pointers

---

# Pointers

A pointer is a special data type for variables that *point to* other variables.

Consider a regular variable of type `int`, initialised to 10:
```
int x = 10;
```

--

We can declare a variable `p` as a *pointer* to an `int` like so:
```
int* p;
```

--

We can then assign the *address* of the regular `x` variable using the
[*address-of*
operator](https://www.geeksforgeeks.org/cpp-pointer-operators/) to `p`:
```
p = &x;
```

--

The pointer `p` now contains the *address* of `x`
- we can say that `p` *points to* `x`


---

# Pointers and addresses

Pointers contain the *memory location* of the variable they point to
- on modern systems, this is a 64-bit unsigned integer

--

The *value* held by a pointer variable is always an integer &ndash; an address
- regardless of which type of variable it points to

--

To read the value that the pointer refers to, we need to use the [dereferencing
operator](https://www.w3schools.com/cpp/cpp_pointers_dereference.asp):
```
int y = *p;
```

---

# Pointers and addresses

To illustrate:
```
int x = 10;
int*p = &x;
std::cerr << "pointer value: " << p << ", value pointed to: " << *p << "\n";
```
gives:
```
pointer value: 0x7ffffcc34, value pointed to: 10
```
