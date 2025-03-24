---
layout: presentation
title: "Week 7, session 2: Resource and memory management"
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

[Memory safety](https://www.memorysafety.org/docs/memory-safety/) is arguably
the biggest source of errors, bugs and security issues with C / C++
- &rArr; we need to understand memory, how to manage it, and the various kinds of
issues that we may encounter. 

--

There are two broad categories of issues that we need to consider:
.columns[
.col[
- accessing invalid memory locations
  - [buffer overflow](https://en.wikipedia.org/wiki/Buffer_overflow)
  - using [stale references or pointers](https://en.wikipedia.org/wiki/Stale_pointer_bug) 
  - ...
]
.col[
- manual memory management
  - [memory leaks](https://www.geeksforgeeks.org/memory-leak-in-c-and-how-to-avoid-it/)
  - [double free](https://isab.run/paste/5aece618)
  - [dangling pointers](https://www.geeksforgeeks.org/dangling-pointers-in-cpp/)
  - ...
]
]

--

Modern C++ makes it is possible to produce code that is relatively safe
- without performing any manual memory management
- this is the approach taken on this course

But we are now at the stage where we need to cover this topic

---

# Memory management

On modern computers, every running process has access to its own region of
memory
- this is its [address space](https://en.wikipedia.org/wiki/Virtual_address_space)
- this region is isolated from other processes using [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory)

--

[Memory can be allocated from two regions](https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/) of this address space:
- the stack
- the heap

---
name: stack_memory
class: section

# The stack

---

# The stack

Stack allocation takes place in the [function call stack](https://en.wikipedia.org/wiki/Call_stack)

The call stack is a data structure that holds the information about the
functions currently running in our process

--

.columns[
.col[
a [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type%29) is a
  generic data structure widely used in computing

It is a way of storing items in a last-in first-out (LIFO) manner

Items are *pushed* on top of the stack, and then *popped* off the stack
]
.col[
![:scale 90%](images/stack.png)
]
]

--

This structure matches the way functions work

---

## The function stack and stack frames


.columns[
.col[
- `main()` calls `run()`
  - the program *pushes* a new [stack frame](https://www.geeksforgeeks.org/stack-frame-in-computer-organization/) for `run()` onto the function call stack
  - the program then executes the code for `run()`
]
.col[
```
               &#9474;             &#9474;
               &#9474;             &#9474;
      run() &rarr; &#9474;             &#9474;
               &#9474; main()      &#9474;
```
]
]

--

.columns[
.col[
- `run()` calls `load_pgm()`
  - the program *pushes* a new [stack frame](https://www.geeksforgeeks.org/stack-frame-in-computer-organization/) for `load_pgm()` onto the function call stack
  - the program then executes the code for `load_pgm()`
]
.col[
```
               &#9474;             &#9474;
 load_pgm() &rarr; &#9474;             &#9474;
               &#9474; run()       &#9474;
               &#9474; main()      &#9474;
```
]
]

--

.columns[
.col[
- `load_pgm()` completes and returns
  - the program *pops* the [stack frame](https://www.geeksforgeeks.org/stack-frame-in-computer-organization/) for `load_pgm()`
  - the program then resumes execution of the remaining code for `run()`
]
.col[
```
               &#9474;             &#9474;
               &#9474; load_pgm()  &#9474; &rarr; 
               &#9474; run()       &#9474;
               &#9474; main()      &#9474;
```
]
]

---

# The function stack and stack frames

Each item in the [function call stack](https://en.wikipedia.org/wiki/Call_stack) 
is called a [stack frame](https://www.geeksforgeeks.org/stack-frame-in-computer-organization/) 

Every time a function is invoked, a new stack frame is pushed onto the call stack

--

The arguments and local variables needed for the function to run are stored in the stack frame
<br>&emsp;*&rArr; this is what is meant by 'stack allocation'*

--

The lifetime of the stack frame is tied to the lifetime of the function call
- as soon as the function returns, the stack frame is popped and its contents *destroyed*
- all local (function-scope) variables immediately go out of scope 
- &rArr; the compiler will insert code to ensure all their destructors are invoked at that point

--

Stack allocations are therefore very predictable and easy to manage
- memory is allocated on the stack when a local variable is declared
- memory is released when the function returns

&rArr; on this course, we have so far *only* used stack allocations 

---
name: recursion
class: section

# Recursive functions

---

# Recursive functions

It is important to understand that a stack frame is specific to an *invocation* of the function
- *not* the function itself

--

If that function is called again, that specific call will get its *own* fresh stack frame
- this allows functions to call themselves &ndash; these are called [recursive functions](https://www.geeksforgeeks.org/recursive-functions/)

--
<br>
This is best illustrated with a classic example: the [Fibonacci sequence](https://en.wikipedia.org/wiki/Fibonacci_sequence)
- In the [Fibonacci sequence](https://en.wikipedia.org/wiki/Fibonacci_sequence),
  each number is the sum of the two preceding numbers
  (starting with 0, 1):
- 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...

--

This can be written as a recursive function:
$$
f(n) = f(n-1) + f(n-2)
$$

---

# Recursive functions: the Fibonacci sequence

We can therefore write this as:
```
int fib (int n) {
* return fib(n-1) + fib(n-2);
}
```
The part of a recursive function where the function calls itself is called the
*inductive step*

--

But what happens when the function eventually calls `fib(1)` or `fib(0)`?
- we need some condition that will prevent further recursion

--

```
int fib (int n) {
* if (n <= 1)
*   return n;
  return fib(n-1) + fib(n-2);
}
```
- this is called the *anchor condition*


---
layout: true

## Recursive functions: the Fibonacci sequence

Let's track the state of the call stack when we call `fib(5)` to get the 
5th element:

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]


---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]


---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack5[
in `fib(1)`: &emsp; `n = 1` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack5[
in `fib(1)`: &emsp; `n = 1` &emsp; `a = ?` &emsp; `b = ?` &emsp; **`return 1`**

```
int fib (int n) {
* if (n <= 1)
*   return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; **`a = 1`** &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = 1` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
* int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = 1` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
* int b = fib(n-2);
  return a + b;
}
```
]

.stack5[
in `fib(0)`: &emsp; `n = 0` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = 1` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
* int b = fib(n-2);
  return a + b;
}
```
]

.stack5[
in `fib(0)`: &emsp; `n = 0` &emsp; `a = ?` &emsp; `b = ?` &emsp; **`return 0`**

```
int fib (int n) {
* if (n <= 1)
*   return n;
  int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = 1` &emsp; **`b = 0`** &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
* int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack4[
in `fib(2)`: &emsp; `n = 2` &emsp; `a = 1` &emsp; `b = 0` &emsp; **`return 1`**

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
  int b = fib(n-2);
* return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; **`a = 1`** &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

---

.stack1[
in `fib(5)`: &emsp; `n = 5` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack2[
in `fib(4)`: &emsp; `n = 4` &emsp; `a = ?` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
* int a = fib(n-1);
  int b = fib(n-2);
  return a + b;
}
```
]

.stack3[
in `fib(3)`: &emsp; `n = 3` &emsp; `a = 1` &emsp; `b = ?` &emsp; `return ?`

```
int fib (int n) {
  if (n <= 1)
    return n;
  int a = fib(n-1);
* int b = fib(n-2);
  return a + b;
}
```
]

--

.explain-bottomright[
... and so on!
]


---
layout: false

# Fibonacci sequence without recursion

In many cases, recursion is not necessary
- the problem can be written differently, for example:

```
int fib (int n) {
  if (n < 2)
    return n;
  int f_2 = 0, f_1 = 1, f_0;
  for (int i = 2; i <= n; i++) {
    f_0 = f_1 + f_2;
    f_2 = f_1;
    f_1 = f_0;
  }
  return f_0;
}
```

--

This is often preferable, since recursive functions require additional storage
on the stack for every nested function call
- the program can run out of stack memory for large numbers!


---
name: heap_memory
class: section

# The heap

---

# The heap

We can also allocate memory manually, outside the stack
- this type of memory is allocated on the [heap](https://www.geeksforgeeks.org/what-is-a-memory-heap/)

--

We can request a chunk of heap memory at any time, and release it back when
we're done
- the lifetime of data stored on the heap is not bound to function scope
- we can allocate memory in one function call, use it elsewhere, and release
  back from a different function

--

This provides a lot of flexibility, but requires careful management
- if our program allocates memory, we need to make sure that memory is released
  when no longer needed
- we need to keep track of all the chunks of memory we have allocated
- there are many ways this can go wrong...

---
layout: true
name: new_delete

# New & delete

---

The following allocates a single integer on the heap:

```
int* p = new int;
```

--

In C++, heap memory is allocated using the `new` and `delete` operators
- in C, the corresponding functions are `malloc()` and `free()`

--

It returns a [pointer](https://www.geeksforgeeks.org/cpp-pointers/) to the newly allocated integer
- this pointer stores the *memory address* to the first byte of the memory region holding the data for our `int`

--

We need to specify the *type* of the data that will be held at the new memory
location
- the compiler needs to know how much memory to allocate to hold a variable of
  that type

---

Since we have to provide the type to the `new` operator, we can often use the
`auto` keyword:

```
`auto`* p = new int;
```
---

We can allocate any type of object this way:
```
auto* p = new `std::vector<int>`;
```

The default constructor will be invoked as soon as the memory chunk is
allocated
- this is the other reason why need to specify the *type*


---

We can also provide arguments to the constructor if required:
```
auto* p = new std::vector<int> `(5, 0)`;
```


---

When dealing with inherited types, we can assign the returned pointer to a
pointer-to-base-class:
```
`Segment::Base`* p = new `Segment::Tip` (20.0);
```

This means we can declare *pointers* to a base class and pass them to other
functions
- even for an *abstract* base class!
- this is widely used for runtime polymorphism

---

When we're done, we need to release the memory back to the system using the
`delete` operator:
```
Segment::Base* p = new Segment::Tip (20.0);

...

*delete p;
```

--

The `delete` operator needs to know which bit of memory to release
- this is the address stored in the pointer
- we therefore need to hold onto that address for the lifetime of that memory
  region!

--

The `delete` operator is responsible for invoking the *destructor* of the
object
- this is guaranteed to happen *before* the memory is released

---
layout: false

# New & delete for arrays

There is a special syntax to allocate memory to hold a C-style array of some
type:
```
double* p = new double `[10]`;
```

This allocates a memory region to hold 10 `double`s

For regular built-in types ([plain old data (POD)
types](https://www.geeksforgeeks.org/pod-type-in-cpp/)), this leaves the
values in the array uninitialised
- each element could contain anything


---

# New & delete for arrays

It is possible to *default-initialise* such POD values using this syntax:

```
double* p = new double [10]`()`;
double* p = new double [10]`{}`;
```

Both lines are equivalent, and both will zero-initialise the array.


---

# New & delete for arrays

It is also possible to *value-initialise* an array using a brace-enclosed list:

```
double* p = new double [10] `{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }`;
```

---

# New & delete for arrays

For class types, the default constructor will be invoked on each element:

```
auto* p = new `std::string` [10];
```
This constructs a C-style array of 10 `std::string`s, each default-constructed
- the strings will all be empty

---

# New & delete for arrays

It is also possible to use value initialisation with a brace-enclosed list:

```
auto* p = new std::string [5] `{ "a", "ab", "abc", "abcd", "abdce" }`;
```

---

# New & delete for arrays

As before, we need to release the memory back to the system

```
auto* p = new std::string [5] { "a", "ab", "abc", "abcd", "abdce" };

...

*delete [] p;
```

However, note that in this case we need use the *array* `delete` operator:
`delete []`

We need to make sure that:
- every memory region allocated using *regular* `new` is released using *regular* `delete`
- every memory region allocated using *array* `new` is released using *array* `delete`

This is a common source of error!

---
name: null_pointer

# The null pointer

It is possible to declare a pointer that does not point to a valid memory
region
- we may want to declare the variable to hold the memory address, but actually
  allocate later (e.g. once we know how much memory to allocate)
- when we release the memory, there is a chance the remaining code could try to
  use the pointer
- ...

--

In this case, we can assign it the special value `nullptr`
- this is an alias for a literal zero
- this allows the code to *check* whether the pointer is valid before accessing
  the memory it points to:

```
Segment::Base* p = nullptr;

...

if (p)
  std::cout << p->tip_position() << "\n";
```

---

# The null pointer

When releasing memory, we can also assign it the value `nullptr` to ensure it
is marked as invalid:
```
delete p;
p = nullptr;

...

if (p)
  std::cout << "value held is " << *p << "\n";
```

--

We therefore need to be very careful when handling pointers
- they may not point to valid locations!
- but setting the pointer to `nullptr` means we can at least check for validity

--

An attempt to *dereference* a `nullptr` will lead to an immediate crash
- the error message is rarely very informative however, and indicates a generic
  memory access violation
  - typically: `segmentation fault`

---
name: memory_problems
class: section

# What can go wrong with memory management?

---
name: memory_leak

# Memory leaks

When we fail to `delete` memory previously allocated with `new`, that memory
chunk remains marked as in use
- it will not be available for subsequent allocations

Eventually, the system will run out of memory, leading to a crash

```
double compute (int n, ...) {
  double* values = new double [n];
  ...
  // perform computation
  return result;
} // &larr; values is not deleted! The address is lost - no scope for subsequent deletion

...

for (auto data : image_data) {
  auto val = compute (nmeasurements, data); 
  ...
}
```

--

.explain-bottomright[
Every call to `compute()` will allocate memory that will never be released

<br>
This is a memory leak &ndash; eventually the program will run out of memory and
crash
]

---

# Memory leaks

It is not easy to guarantee deletion always happens:
```
double compute (int n, ...) {
* double* values = new double [n];

  ...

  if (some_error)
    throw std::runtime_error ("computation failed");

  ...

  if (early_termination_condition)
    return result;

  ...

* delete [] values;
  return result;
}
```

--

.explain-bottomright[
Our function allocates memory for `values`, and releases it before returning
]

---

# Memory leaks

It is not easy to guarantee deletion always happens:
```
double compute (int n, ...) {
  double* values = new double [n];

  ...

* if (some_error)
*   throw std::runtime_error ("computation failed");

  ...

  if (early_termination_condition)
    return result;

  ...

  delete [] values;
  return result;
}
```

.explain-bottomright[
But if an exception is thrown, the memory will not be released!
]

---

# Memory leaks

It is not easy to guarantee deletion always happens:
```
double compute (int n, ...) {
  double* values = new double [n];

  ...

  if (some_error)
    throw std::runtime_error ("computation failed");

  ...

* if (early_termination_condition)
*   return result;

  ...

  delete [] values;
  return result;
}
```

.explain-bottomright[
We may return from the function at multiple points 

<br>We need to make sure any
previously allocated memory is released for *every* return statement!
]

---
name: dangling_pointers

# Dangling pointers and references

[Dangling pointers](https://www.geeksforgeeks.org/dangling-pointers-in-cpp/)
occur when the memory they point to has already been deleted
- subsequent attempts to dereference this pointer are invalid!
- this is *undefined behaviour* &ndash; anything can happen
  - crash with a segmentation fault
  - unexpected results
  - data corruption
  - ...

--

This can happen for different reasons
- returning the address of a function scope variable
- deleting memory without setting the pointer to `nullptr`
- having multiple pointers to the same memory
- ...

---

# Dangling pointers and references

```
Segment::Base* create_segment() {
  Segment::Tip tip (20.0);
  return &tip;
}


int main() {
  ...

  auto* segment = create_segment();
* std::cout << segment->tip_position() << "\n";
  return 0;
}
```

Here, `create_segment()` returns the address of a local function-scope variable

This variable will no longer exist as soon as `create_segment()` returns
- the stack frame containing its memory location will have been popped!

The address stored in `segment` no longer points to a valid instance!


---
name: double_free

# Double free

```
void finalise (Data* d) {
  // process data in d
  ...
* delete d;
};

int main () {
  Data* data_item = new Data;
  ...
  finalise (data_item);
* delete data_item;
}
```

Here, the memory address pointed to by `data_item` is deleted twice
- once in `finalise()`, once in `main()`

Trying to delete an already released memory location will cause a program crash!

---
name: memory_solutions
class: section

# Memory management<br>in modern C++

---

# First line of defence: don't do it!

As you can see, there are many ways things can go wrong when managing memory
manually. 
- we have only covered a few simple cases here. 

--

Thankfully, modern C++ provides a number of approaches and techniques to avoid
the most common pitfalls

--

The most obvious way to avoid these issues is to avoid manual memory
management!
- you can handle most projects using well-behaved standard types
- e.g. `std::string`, `std::array`, `std::vector`, ...
- we have completed 3 projects on this course without *any* manual memory
  management!

---
name: ownership_lifetime

# Object ownership and lifetime

When we allocate memory from the heap, we need to keep track of:
- the memory address 
- whether this was allocated using regular or array `new`

So that we can release that memory when it is no longer needed

--

When we release the memory, we need to:
- make sure it is only released *once*
- using the matching version of `delete` (regular or array)
- make sure the pointer is set to `nullptr` afterwards &ndash; unless we can guarantee it
  won't be used any more

--

It may be possible to handle this within a single function
- or a simple collection of functions that are designed to work together

--

But most of the time, we want to use objects allocated on the heap in many
different places!

---

# Object ownership and lifetime

Many languages rely on [garbage
collection](https://en.wikipedia.org/wiki/Garbage_collection_(computer_science%29)
- the program releases any previously allocated memory that is no longer
  referenced
- every so often, the program needs to halt execution and perform garbage collection
- this can impact performance, particularly in applications where timing needs
  to be predictable
- this will also typically require more memory, since memory is not immediately
  released

--

C++ does not perform garbage collection
- we need to handle our own memory...

To properly track the memory allocations, we need to think about [ownership and
lifetime](https://www.ditsing.com/object-lifetime-and-ownership/)
- which bit of the code 'owns' that memory?
- this code is then responsible for managing it

--

One way to do this is to set up a class to manage the memory
- objects of this class can then be considered to have ownership of that memory
- the lifetime of that memory is tied to the lifetime of the object


---
name: raii
class: section

# RAII: Resource Acquisition Is Initialisation

---

# RAII: Resource Acquisition Is Initialisation

[RAII](https://www.geeksforgeeks.org/resource-acquisition-is-initialization/) stand for "Resource Acquisition Is Initialisation"

It is an idiomatic programming technique widely used in C++ to manage *resources*
- in RAII, the class constructor *acquires* the resource, while the destructor
  *releases* the resource
- this means ownership and lifetime of the resource are tied to the object

--

A 'resource' in this context is anything that must be acquired before use, and
has a limited supply
- memory
- file handles
- network connections
- database connections
- mutexes (mutual exclusion locks)
- ...

--

This is how many of the standard classes manage their resources:
- `std::vector` (can) allocate memory at construction, and the
  memory is released in the destructor
- `std::ifstream` & `std::ofstream` (can) open a file at construction, and
  close the file in the destructor




---

# Implementing RAII for memory management

For example, this is how we might implement our own version of a vector:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }
    ~MyVector () { delete [] m_data; }

    int size () const { return m_size; }
    int&       operator[] (int n)       { return m_data[n]; }
    const int& operator[] (int n) const { return m_data[n]; }

  private:
    int* m_data;
    int  m_size;
};
```

---

# Implementing RAII for memory management

For example, this is how we might implement our own version of a vector:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }
    ~MyVector () { delete [] m_data; }

    int size () const { return m_size; }
    int&       operator[] (int n)       { return m_data[n]; }
    const int& operator[] (int n) const { return m_data[n]; }

  private:
*   int* m_data;
*   int  m_size;
};
```

.explain-bottomright[
The class has two data members: 
- the size of the vector
- a pointer to the memory region storing the elements in the vector 

<br>Note our class is designed to hold data of type `int` 
]

---

# Implementing RAII for memory management

For example, this is how we might implement our own version of a vector:

```
class MyVector {
  public:
*   MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }
    ~MyVector () { delete [] m_data; }

    int size () const { return m_size; }
    int&       operator[] (int n)       { return m_data[n]; }
    const int& operator[] (int n) const { return m_data[n]; }

  private:
    int* m_data;
    int  m_size;
};
```

.explain-bottomright[
The default constructor ensures the pointer is set to `nullptr` and the size to
zero
]

---

# Implementing RAII for memory management

For example, this is how we might implement our own version of a vector:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
*   MyVector (int size) : m_data (new int[size]), m_size (size) { }
    ~MyVector () { delete [] m_data; }

    int size () const { return m_size; }
    int&       operator[] (int n)       { return m_data[n]; }
    const int& operator[] (int n) const { return m_data[n]; }

  private:
    int* m_data;
    int  m_size;
};
```

.explain-bottomright[
The other constructor allows the user to specify the size of the vector. 

<br>The `m_data` pointer is then set to the address of a new memory region of
the right size. 
]

---

# Implementing RAII for memory management

For example, this is how we might implement our own version of a vector:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }
*   ~MyVector () { delete [] m_data; }

    int size () const { return m_size; }
    int&       operator[] (int n)       { return m_data[n]; }
    const int& operator[] (int n) const { return m_data[n]; }

  private:
    int* m_data;
    int  m_size;
};
```

.explain-bottomright[
The destructor will delete the memory region pointed to by `m_data`

<br>Note that it is not an error to call `delete` on a `nullptr`: the standard states that
nothing will happen in this case
]

---

# Implementing RAII for memory management

For example, this is how we might implement our own version of a vector:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }
    ~MyVector () { delete [] m_data; }

*   int size () const { return m_size; }
*   int&       operator[] (int n)       { return m_data[n]; }
*   const int& operator[] (int n) const { return m_data[n]; }

  private:
    int* m_data;
    int  m_size;
};
```

.explain-bottomright[
The other methods provide access to the data. We have already seen these
operators in use with our `Image` class in the fMRI project. 
]

---

# Implementing RAII for memory management

This class can be used like this:

```
double compute (int n, double rate) {
  MyVector vec (10);  // &larr; the constructor allocates a memory region to hold 10 ints

  if (rate < 0.0) 
    throw std::runtime_error ("invalid value for rate");
  // &uarr; even if we throw an exception, the destructor will be invoked,
  // releasing the memory

  for (int n = 0; n < vec.size(); n++)
    vec[n] = std::exp (-n*rate);

  double result = 0.0;
  for (int n = 0; n < vec.size(); n++)
    result += vec[n];

  return result;
}  // &larr; the destructor is invoked as vec goes out of scope, releasing the memory 

```

---

# Implementing RAII for memory management

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }
    ~MyVector () { delete [] m_data; }

*   void clear () {
*     delete [] m_data;
*     m_data = nullptr;
*     m_size = 0;
*   }

*   void resize (int new_size) {
*     delete [] m_data;
*     m_data = new int [new_size];
*     m_size = new_size;
*   }

    int size () const { return m_size; }
    ...
```

.explain-bottomright[
In practice, we would have other methods, such as `clear()` and `resize()`, and
these also need to properly manage the memory 

<br>
Here, `resize` reallocates a new region of the desired size. But it does not
preserve the previous contents
- a more mature implementation may handle this more gracefully
]

---
name: copy_and_assignment

# The copy constructor and assignment operator

When handling resource such as memory manually, we typically also need to worry
about what happens when our object is *copied*

--

## Copy construction

```
MyVector vec (10);
...
MyVector vec2 (vec);   // &larr; this is copy construction
MyVector vec3 = vec;   // &larr; ... and so is this!
```

--

## Assignment
```
MyVector vec (10);
MyVector vec2;
...
vec2 = vec;    // &larr; this is assignment
```

--

.explain-bottomright[
**Copy-construction** refers to constructing a new variable by copying an
existing one of the same type. This occurs if the variable is being declared at
the same time.

<br>**Assignment** refers to copying an existing variable of the same type into
an existing variable. This occurs if the variable had already been declared
previously.
]

---

# The copy constructor and assignment operator

These operations are handled by two dedicated methods:
- the [copy constructor](https://www.geeksforgeeks.org/copy-constructor-in-cpp/)
- the [assignment operator](https://www.geeksforgeeks.org/cpp-assignment-operators/)

```
class MyVector {
  public:
    ...
*   MyVector (const MyVector& other);                 // &larr; copy constructor
*   MyVector& operator= (const MyVector& other);      // &larr; assignment operator
    ...
```

If unspecified, the compiler will implicitly provide default versions of these methods.
- these simply copy class member one by one using their own copy constructor
or assignment operator.

--

If we need to declare our own destructor, we will typically also need to
declare our own copy constructor and assignment operator
- the implicit default versions will typically do the wrong thing!

---

# The Rule of Five

The [Rule of Five](https://www.geeksforgeeks.org/rule-of-five-in-cpp/) states
that if we need to define any of the following, we should define all of them:
- destructor
- copy constructor
- assignment operator
- *move constructor*<sup>1</sup>
- *move assignment operator*<sup>1</sup>

.note[
<sup>1</sup>*these methods relate to [move
semantics](https://cbarrete.com/move-from-scratch.html), which are beyond the
scope of this course.*
]

--

The reason for this is that when we need to define one of them, it is typically
because we are managing some resource that will require careful management
- if we need to handle destruction in a non-default way, we most likely also
  need to handle copying in a non-default way, and vice-versa

--

Let's see why using our `MyVector` class as an example

---

# Why is the default copy constructor not appropriate?


There are only 2 data members in our `MyVector` class:

```
class MyVector {
  ...
  private:
*   int* m_data;
*   int  m_size;
};
```

--

If we create a copy of this object by copying each member, we will end up with
another object with a `m_data` pointer referencing the *same memory address* as
the first:

```
void run_computation () { 
  MyVector vec1 (10);   // &larr; memory allocated here
  MyVector vec2 = vec1; // &larr; vec2 now refers to the same memory address
  ...
}  // &larr; both destructors will try to delete the same memory address!
```

--

.explain-bottomright[
What happens when they go out of scope? 

- the destructor for `vec2` will release the memory
- the destructor for `vec1` will *also* try to
  release the same memory address!

&rArr; the program will crash due to a double deletion
]

---

# The copy constructor

Here is a possible implementation for a more appropriate copy constructor:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }

*   MyVector (const MyVector& other) : 
*     m_data (new int [other.size()]),
*     m_size (other.size()) {
*       for (int n = 0; n < m_size; n++)
*         m_data[n] = other.m_data[n];
*     }

    ...
```

---

# The copy constructor

Here is a possible implementation for a more appropriate copy constructor:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }

*   MyVector (const MyVector& other) : 
      m_data (new int [other.size()]),
      m_size (other.size()) {
        for (int n = 0; n < m_size; n++)
          m_data[n] = other.m_data[n];
      }

    ...
```

.explain-bottomright[
This is the expected declaration for the copy constructor:

<br>It is a constructor with a single argument: a const reference to another
  instance of the same type
]

---

# The copy constructor

Here is a possible implementation for a more appropriate copy constructor:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }

    MyVector (const MyVector& other) : 
*     m_data (new int [other.size()]),
*     m_size (other.size()) {
        for (int n = 0; n < m_size; n++)
          m_data[n] = other.m_data[n];
      }

    ...
```

.explain-bottomright[
We initialise the data members in the [member initialise
list](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/). In
particular, we allocate enough memory to match the contents of the vector we
are copying from. 
]

---

# The copy constructor

Here is a possible implementation for a more appropriate copy constructor:

```
class MyVector {
  public:
    MyVector () : m_data(nullptr), m_size (0) { }
    MyVector (int size) : m_data (new int[size]), m_size (size) { }

    MyVector (const MyVector& other) : 
      m_data (new int [other.size()]),
      m_size (other.size()) {
*       for (int n = 0; n < m_size; n++)
*         m_data[n] = other.m_data[n];
      }

    ...
```

.explain-bottomright[
We can now perform a manual copy the contents of the array across to our own
freshly-allocated memory region. 

<br>This type of operation is referred to as a [deep
copy](https://www.geeksforgeeks.org/shallow-copy-and-deep-copy-in-c/)
]


---

# The assignment operator

Here is a possible implementation for a more appropriate assignment operator:

```
class MyVector {
  public:
    ....

*   MyVector& operator= (const MyVector& other) {
*     delete [] m_data;
*     m_size = other.size();
*     m_data = new int [m_size];
*     for (int n = 0; n < m_size; n++)
*       m_data[n] = other.m_data[n];
*     return *this;
*   }

    ...
```

---

# The assignment operator

Here is a possible implementation for a more appropriate assignment operator:

```
class MyVector {
  public:
    ....

*   MyVector& operator= (const MyVector& other) {
      delete [] m_data;
      m_size = other.size();
      m_data = new int [m_size];
      for (int n = 0; n < m_size; n++)
        m_data[n] = other.m_data[n];
      return *this;
    }

    ...
```

.explain-bottomright[
This is the expected declaration for the assignment operator: 

- it has the special name `operator=`
- it takes a single argument: a const reference to another instance of the same
  type
- it returns a non-const reference to *itself*
]

---

# The assignment operator

Here is a possible implementation for a more appropriate assignment operator:

```
class MyVector {
  public:
    ....

    MyVector& operator= (const MyVector& other) {
*     delete [] m_data;
      m_size = other.size();
      m_data = new int [m_size];
      for (int n = 0; n < m_size; n++)
        m_data[n] = other.m_data[n];
      return *this;
    }

    ...
```

.explain-bottomright[
This time, we need to release any memory we may have previously been holding. 

<br>The assignment operator will be invoked on a fully-constructed instance:
it is possible (indeed likely) that it may already contain some data!
]
---

# The assignment operator

Here is a possible implementation for a more appropriate assignment operator:

```
class MyVector {
  public:
    ....

    MyVector& operator= (const MyVector& other) {
      delete [] m_data;
*     m_size = other.size();
*     m_data = new int [m_size];
      for (int n = 0; n < m_size; n++)
        m_data[n] = other.m_data[n];
      return *this;
    }

    ...
```

.explain-bottomright[
As for the copy constructor, we can now allocate enough memory to hold the data
we are about to copy over. 

<br>This time, we cannot use the member initializer list, as this is not a
constructor. We assign the appropriate values to the data members within the
body of the function. 
]


---

# The assignment operator

Here is a possible implementation for a more appropriate assignment operator:

```
class MyVector {
  public:
    ....

    MyVector& operator= (const MyVector& other) {
      delete [] m_data;
      m_size = other.size();
      m_data = new int [m_size];
*     for (int n = 0; n < m_size; n++)
*       m_data[n] = other.m_data[n];
      return *this;
    }

    ...
```

.explain-bottomright[
We copy the data across as we did in the copy constructor
]

---

# The assignment operator

Here is a possible implementation for a more appropriate assignment operator:

```
class MyVector {
  public:
    ....

    MyVector& operator= (const MyVector& other) {
      delete [] m_data;
      m_size = other.size();
      m_data = new int [m_size];
      for (int n = 0; n < m_size; n++)
        m_data[n] = other.m_data[n];
*     return *this;
    }

    ...
```

.explain-bottomright[
Finally, we return a reference to the current instance of `MyVector`, by
dereferencing the [`this`
pointer](https://www.geeksforgeeks.org/this-pointer-in-c/)

<br>This allows follow-on operations to be performed, for example:
```
MyVector vec1 (10);
MyVector vec2, vec3;

...

vec2 = vec3 = vec1;
```
]


---

# Case 1: deep copy

What we implemented for `MyVector` ensures that when we create a copy of our
class, the entire contents are carried over: a [deep copy](https://www.geeksforgeeks.org/shallow-copy-and-deep-copy-in-c/)
- this is default behaviour in many standard objects, e.g. `std::string`, `std::vector`

--

This ensures that all instances remain entirely independent:
- making changes to the data of one copy will not influence the data in another
- this matches what most people would expect

--

It also avoids problems with memory management, such as 
[memory leaks](https://www.geeksforgeeks.org/memory-leak-in-c-and-how-to-avoid-it/),
[double free](https://isab.run/paste/5aece618), or
[dangling pointers](https://www.geeksforgeeks.org/dangling-pointers-in-cpp/)

--

But there are other strategies that may make sense in different situations!

---

# Case 2: unique copy

Some resources cannot or should not be copied over
- e.g. file streams / file handles
- connection handlers to e.g. web services or databases
- a pointer to memory where a unique resource is stored
- ...

--

In this case, it may be safer to *disable* copy constructor and assignment
altogether

This can be done as follows:
```
class MyVector { 
  public: 
    ...
    MyVector (const MyVector& other) `= delete`;
    MyVector& operator= (const MyVector& other) `= delete`;
    ...
```

---

# Case 2: unique copy

For example, file streams have no copy constructors or assignment operators
- these have been explicitly deleted
- such objects are said to be *non-copyable*

--

This means it is not possible to write, for example:
```
  ... 
  std::ifstream infile (filename);

  ...

  std::ifstream infile_copy (infile);  // &larr; error: use of deleted function
  ...
```

--

<br>
.note[
Note: non-copyable object can often still be *movable*, allowing them to be stored in e.g.
  `std::vector`
  - this relies on [move semantics](https://cbarrete.com/move-from-scratch.html), 
    which is beyond the scope of this course
]


---

# Case 3: shared copy

In other situations, it may be appropriate for each instances of the class to
own a *shared reference* or pointer to the resource

--

In such cases, we need some mechanism in place to ensure:

- the resource remains available as long as it might be needed 
  - often, this might be as long as any other object holds a reference to it

- the resource is appropriate deleted, closed or otherwise disposed of when no
  longer required

- the resource is only deleted / closed once

--

There a variety of ways of dealing with such situations:
- having one object that owns and manages the lifetime of the resource, and
  using *non-owning* references or pointers throughout the rest of the code
  - we then only need to ensure the manager object maintains the resource
    active as long as it is needed
- we could also use [reference counting](https://mortoray.com/what-is-reference-counting/): track the number
  of active users of the resource, and automatically delete or close it when that number reaches zero

---
name: smart_pointers
class: section

# Smart pointers

---
class: info

# Smart pointers

Since managing pointers is such a common task, and such a rich source of
errors, the C++ standard now provides lightweight template classes purely to
manage pointers

--

These [smart pointers](https://www.geeksforgeeks.org/smart-pointers-cpp/) are
designed to be used with a similar syntax as regular pointers
- but provide *safe* implementations of the destructor, copy constructors,
  and assignment operators

--

There are different variants, but two of them are very widely used:
- `std::unique_ptr`
- `std::shared_ptr`

---
class: info

# When holding a unique instance

The [`std::unique_ptr`](https://www.geeksforgeeks.org/unique_ptr-in-cpp/) 
template class automatically manages a single pointer. 
- it will `delete` the memory in its destructor
- using the appropriate version of `delete` (regular or array)
- and ensures there is only one owner at any point in time

--

To ensure single ownership, its copy constructor and assignment operator have
been *deleted*
- it is *non-copyable*

---
class: info

# When holding a unique instance

For example:

```
void some_function () {
  // construct a unique_ptr to manage a pointer to Segment::Base, 
  // and immediately assign a freshly allocated pointer to it:
  std::unique_ptr<Segment::Base> seg_root (new Segment::Tip (20.0));

  // this can be used like a regular pointer:
  std::cout << seg_root->tip_position() << "\n";

} // &larr; but will be automatically deleted when unique_ptr is destroyed
```

---
class: info

# When holding a unique instance

This can be useful if we need to store a pointer as a class member:

```
namespace Segment {
  class Base {
  public:
      Base (Base* next_segment, const std::string& type) :
        m_next (next_segment), 
        m_type (type) { }

      // no need for special handling in the destructor!
      virtual ~Base () { };

      ...

    protected:
      std::unique_ptr<Base> m_next;
      const std::string     m_type;
  };
}
```

--

.explain-bottomright[
Note that because `std::unique_ptr` is *non-copyable*, our class will also be
*non-copyable*: one of its member cannot be copied!

<br>Only use this approach if you're confident you will not need to support
copy operations! 
]

---
class: info

# When holding a shareable instance

The [`std::shared_ptr`](https://www.geeksforgeeks.org/shared_ptr-in-cpp/)
template class *also* automatically manages a single pointer. 
- it will `delete` the memory in its destructor
- using the appropriate version of `delete` (regular or array)
--
- ... but allows for shared ownership across multiple owners!

--

It uses [reference counting](https://mortoray.com/what-is-reference-counting/)
to ensure deletion only happens when the number of 'owners' drops to zero

--

It is therefore *copyable* &ndash; but all copies refer to the same instance
- this is *not* a deep copy!

---
class: info

# When holding a shareable instance

For example:

```
std::shared_ptr<Segment::Base> some_function () {
  // construct a shared_ptr to manage a pointer to Segment::Base, 
  // and immediately assign a freshly allocated pointer to it:
  std::shared_ptr<Segment::Base> seg_root (new Segment::Tip (20.0));

  // this can be used like a regular pointer:
  std::cout << seg_root->tip_position() << "\n";

  return seg_root;
} // &larr; the new segment will only be deleted if the reference count drops to zero
```

This function returns a shared pointer, which can be passed around if required.
- we can make copies, or pass it to other function by copy
- the memory it points to will only be deleted once all active references have
  been destroyed

---
class: info

# When holding a shareable instance

This can be useful if we need to store a pointer as a class member:

```
namespace Segment {
  class Base {
  public:
      Base (Base* next_segment, const std::string& type) :
        m_next (next_segment), 
        m_type (type) { }

      // no need for special handling in the destructor!
      virtual ~Base () { };

      ...

    protected:
      `std::shared_ptr<Base>` m_next;
      const std::string     m_type;
  };
}
```

--

.explain-bottomright[
Note that our class will now be *copyable* (in contrast to `std::unique_ptr`).

<br>But all instances will be accessing the same memory location!
]


---
class: section
name: inherited_object_storage

# Storing objects in the context of inheritance

---
name: object_slicing

# Object slicing

In our robot arm project, each segment stores a reference to the next segment
- why can we not store an *instance* of the next segment?

--

This is because of [object
slicing](https://www.geeksforgeeks.org/object-slicing-in-c/)
- derived classes will typically be larger than their base class
- if we store the next segment as an *instance* of type `Segment::Base`, the
  memory allocated to store this segment will be just enough to store a
`Segment::Base`
  - but this is typically smaller than any *derived* class!

--

&rArr; the next segment will only contain the members
expected in the base class
- we will preserve the next segment and the type
- ... but lose any information specific to derived classes (e.g. length or angle)

--

By storing a *reference* or *pointer* to a fully-formed instance of the right
type, this is no longer an issue
- but we then need to worry about object lifetime and ownership
- and potentially memory management!

---
name: vector_of_base

# Vector of base class objects

The issue of [object
slicing](https://www.geeksforgeeks.org/object-slicing-in-c/) is most obvious
when trying to store a *vector* of classes.

--

Consider the following code, using the classes defined in our robot arm project:
```
std::vector<Segment::Base> segments;
segments.push_back (Segment::Tip (20.0));
```

How does a `std::vector` store its contents? 
- it allocates enough memory to store the number of elements required
- ... assuming they are all of the same size!
- ... and the size of each element is taken to be that of the type specified
  (`Segment::Base` in our case)

--

The size of `Segment::Base` is 40 bytes, but the size of `Segment::Tip` is
*48 bytes*
- `Segment::Tip` contains one additional `double` to store the length (of size 64 bits / 8
  bytes)

--

&rArr; the next segment that we insert into the vector will overwrite the end of our tip
segment!

---

# Vector of base class objects

How do we store a vector of objects, when the size of the objects is variable
and unpredictable?

--

We can instead store a vector of pointers:
```
std::vector<Segment::Base*> segments;
segments.push_back (new Segment::Tip (20.0));
```
But who is then responsible for deleting all these pointers?

--

Again, we need to consider ownership and lifetime

One approach is to allocate the segments first, then store their addresses in a
vector
- the implicit understanding is that the vector *does not own* the segments

```
Segment::Tip tip (20.0);                // &larr; allocated on the stack
std::vector<Segment::Base*> segments;
segments.push_back (&tip);              // &larr; 'segments' *only* stores the addresses
```

---
name: reference_wrapper

# The `std::reference_wrapper` class

A cleaner way to achieve the same outcome is to use [the
`std::reference_wrapper` class](https://www.geeksforgeeks.org/reference_wrapper-in-cpp/)
- this class template provides a reference-like object, but allows copying,
  moving, and reasssignment

--

This allows us to have a vector of these `reference_wrapper`s:
```
Segment::Tip tip (20.0);                // &larr; allocated on the stack

std::vector<std::reference_wrapper<Segment::Base>> segments;
segments.push_back (tip);               // &larr; 'segments' *only* stores references
```

This is very similar to the previous case (storing a vector of pointers)
- but by storing *references*, it is more explicit that the `segments` vector
  does not *own* the segments
- we also do not need to `push_back` the *address* of the objects &ndash; they are
  passed by reference

---
name: vector_smart_ptr
class: info

# A vector of smart pointers

In cases where the vector should have ownership of its contents, we can
instead use a vector of smart pointers

For example:
```
std::vector<std::unique_ptr<Segment::Base>> segments;
segments.push_back (new Segment::Tip (20.0));
```
Because each element in the vector is a `std::unique_ptr`, its destructor will
also delete the memory it points to
- the vector will clear its contents and any associated memory when it is
  destroyed
- this effectively *transfers ownership* of the pointers to the `segments` vector

--

It is also possible to have a vector of `std::shared_ptr`
- this depends on exactly what the code is intended to do... 

---

# Exercise

Update robot arm project to use manual memory management

- start by using pointers to store the next segment, instead of references

- provide functionality to allow the next segment to be set outside of the
  constructor, using a new `set_next()` method

- make sure the `Segment::Base` class deletes its next segment
  - this means we can only provide segments allocated on the heap
  - it will require changes to the way the segments are set up in `run()`

- now try using a smart pointer to `Segment::Base` to manage the next segment 


