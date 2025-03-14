---
layout: presentation
title: "Week 7, session 1: Resource and memory management"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 7, session 2
## Resource and memory management

---
name: memory_management
class: section

# Memory management

---

# Memory management

---
name: stack_memory
class: section

# The stack

---

# The stack

---

# The function stack and stack frames

---
name: recursion
class: section

# Recursive functions

---

# Recursive functions

---
name: heap_memory
class: section

# The heap

---

# The heap

---
name: new_delete

# New & delete

---

# New & delete for arrays

---
name: null_pointer

# The null pointer

---
name: memory_problems
class: section

# What can go wrong with memory management?

---
name: memory_leak

# Memory leaks

---
name: dangling_pointers

# Dangling pointers and references

---
name: double_free

# Double free

---
name: ownership

# Object ownership



---
name: memory_solutions
class: section

# Memory management<br>in modern C++

---

# First line of defence: don't do it!

---
name: raii
class: section

# RAII: Resource Acquisition Is Initialisation

---

# RAII: Resource Acquisition Is Initialisation

---

# Implementing RAII for memory management

---
name: copy_and_assignment

# The copy constructor and assignment operator

---

# Case 1: deep copy

e.g. `std::string`, `std::vector`

---

# Case 2: unique copy

e.g. file streams

---
name: smart_pointers

# Smart pointers

---

# Smart pointers

---

# When holding a unique instance

`std::unique_ptr` and `std::make_unique`

---

# When holding a shareable instance

`std::shared_ptr` and `std::make_shared`

---
name: robot_arm_pointers
class: section

# The robot arm project<br>revisited using pointers

---
name: object_slicing

# Object slicing

---

# Exercise

Update robot arm project using smart pointers




