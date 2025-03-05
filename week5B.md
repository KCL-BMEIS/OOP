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
  - nonetheless, pointers are very widely used in C & C++

--

To understand iterators, we need to start with pointers

---
class: section

# Pointers

---

# Memory addresses


Consider a regular variable of type `int`, initialised to 10:
```
int x = 10;
```
--

Our `int` variable `x` takes up 32 bits at some location in memory.
```


... d641b172e0747349e94e6fbd`000a`6915ca4990b2f8cbc1e205813aba0ead50ec761b ...
                            x=10
```
Computer memory contains a very long list of 8-bit bytes &ndash; we can think
of it as an *array*


---

# Memory addresses

Consider a regular variable of type `int`, initialised to 10:
```
int x = 10;
```
Our `int` variable `x` takes up 32 bits at some location in memory.
```
                 address of x = 13487234
                            ↓
... d641b172e0747349e94e6fbd`000a`6915ca4990b2f8cbc1e205813aba0ead50ec761b ...
                            x=10
```
Computer memory contains a very long list of 8-bit bytes &ndash; we can think
of it as an *array*

The *address* of our variable `x` is the byte offset to the first byte of
its memory location
- the actual value of the address is difficult to interpret &ndash; it's just a (very) large
  number
- on modern systems, this is a 64-bit unsigned integer
- ... regardless of which type of variable it points to!

---

# Pointers and addresses

A *pointer* is a special data type to store *memory addresses*
- storing the memory location of a variable allows a pointer to *point* to that variable

--

We can declare a variable `p` as a *pointer* to an `int` like so:
```
int* p;
```

--

We can then assign to `p` the *address* of our regular variable `x` using the
[*address-of*
operator](https://www.geeksforgeeks.org/cpp-pointer-operators/):
```
p = &x;
```

--

The pointer `p` now contains the *address* of `x` &ndash; we can say that `p` *points to* `x`
```
                            p = 13487234
                            ↓
... d641b172e0747349e94e6fbd`000a`6915ca4990b2f8cbc1e205813aba0ead50ec761b ...
                            x=10
```

---

# Pointers and addresses

To read the value that the pointer refers to, we need to use the [dereferencing
operator](https://www.w3schools.com/cpp/cpp_pointers_dereference.asp):
```
int y = *p;
```

--

Note that to be able to correctly interpret the contents at the memory location
pointed to by `p`, we need to know what *type* of data is stored at that
location

&rArr; This is why we need to declare a pointer to a *type*
```
`int`* p;
```

--

The value stored at that addess would be very different if we
think it is a `float` instead of an `int`!
```yaml
pointer value: 0x7ffc2cf013a4, value pointed to if int:   10
pointer value: 0x7ffc2cf013a4, value pointed to if float: 1.4013e-44
```

... even though both pointers store the same address!


---

# Pointers and addresses

To illustrate:
```
int x = 10;
int* p = &x;
std::cerr << "pointer value: " << p << ", value pointed to: " << *p << "\n";
```
gives:
```
pointer value: 0x7ffffcc34, value pointed to: 10
```


---

# Multple pointers, same address

We can have multiple pointers all point to the same memory location:
```
int x = 10;
int* p = &x;

int* q = p;
```

--

This is equivalent to the following:

```
                            p = 13487234
                            ↓
... d641b172e0747349e94e6fbd`000a`6915ca4990b2f8cbc1e205813aba0ead50ec761b ...
                            ↑ 
                            q = 13487234
```


---

# Multiple pointers, same address

This means assigning a different value to the memory location pointed to by
one of them will change the value for *all* of them:
```
 int x = 10;
 int* p = &x;

 int* q = p;

 *q = 20;

 std::cerr << "x: " << x << "\n";
 std::cerr << "pointer value: " << p << ", value pointed to: " << *p << "\n";
 std::cerr << "pointer value: " << q << ", value pointed to: " << *q << "\n";
```

This will produce:
```
x: 20
pointer value: 0x7ffe65e51724, value pointed to: 20
pointer value: 0x7ffe65e51724, value pointed to: 20
```

---

# Pointers as references

Pointers can therefore act as *references* to other data
- they can be passed around and copied, and still refer to the same original
  variable
- in C, this is the only way to hold references to other variables

--

This can be used to allow functions to modify their arguments:
```
void increment (int* val) { *p += 2; }
```

--

Compare this to the same operation using C++ references (the recommended way!):
```
void increment (int& val) { p += 2; }
```

--

As you can appreciate, there is a very tight relationship between *pointers* and *references*
- references act as another name (an alias) for the same variable
  - no need to use the address-of operator, or the dereferencing operator
- pointers store the address of the variable

---

# C-style arrays

Pointers are often used to access C-style *arrays*:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };
```
The above declares an array of 5 `floats` initialised with the values provided. 

--

This array is stored in memory as 5 consecutive 32-bit entries:
```
                v[0]    v[2]    v[4]
                ----    ----    ----
... d641b172e074`7349`e94e`6fbd`6915`ca49`90b2f8cbc1e205813aba0ead50ec761b ...
                    ----    ----
                    v[1]    v[3]
```
--

The variable `v` is *also* a pointer: it stores the memory location of the first
entry in the array
- the compiler also knows that it refers to an array of 5 `float` values

---

# C-style arrays

To demonstrate that a C-style array is also a pointer:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };

float* pv = v;

std::cerr << "Value in v at offset 2:  " << v[2] << "\n";
std::cerr << "Value in pv at offset 2: " << pv[2] << "\n";

```
produces:
```yaml
Value in v at offset 2:  1.9
Value in pv at offset 2: 1.9
```

How does this work?

---

# Pointer arithmetic

We can *increment* a pointer:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };
float* pv = v;
std::cerr << "address of pv: " << pv << ", value pointed to: " << *pv << "\n";

*pv++;

std::cerr << "address of pv: " << pv << ", value pointed to: " << *pv << "\n";
```

produces:
```
address of pv: 0x7ffed3dc9640, value pointed to: 2.3
address of pv: 0x7ffed3dc9644, value pointed to: 6.3
```
&rArr; address has increased by 4 bytes: the size of a `float` (32 bits, which equates to 4 bytes)
- the pointer now points to the next element along in memory
- ... based on the knowledge that the memory points to elements of type `float`

---

# Pointer arithmetic

We can *add an integer* to a pointer:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };
float* pv = v;
std::cerr << "address of pv: " << pv << ", value pointed to: " << *pv << "\n";

*pv += 3;

std::cerr << "address of pv: " << pv << ", value pointed to: " << *pv << "\n";
```

produces:
```
address of pv: 0x7ffed3dc9640, value pointed to: 2.3
address of pv: 0x7ffed3dc964c, value pointed to: -3.12
```
&rArr; address has increased by 12 bytes: 3 &times; the size of a `float`!

---

# Pointer arithmetic

We can *take the difference* between two pointers of the same type:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };
float* pv = v;

pv += 3;

*int diff = pv - v;
std::cerr << "difference is " << diff << "\n";
```

produces:
```
difference is 3
```
&rArr; even though difference in actual memory location is 12 bytes, the difference between pointers is expressed in units of the type pointed to

---

# Pointer arithmetic

We can request the element at some offset relative to the pointer:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };

std::cerr << "Value in v at offset 4:  " << v[4] << "\n";
std::cerr << "Value in v at offset 4:  " << *(v+4) << "\n";
```

produces:
```
Value in v at offset 4:  5.356
Value in v at offset 4:  5.356
```
--

You can see that the subscript operator `[]` is equivalent to dereferencing the
address at the specified offset relative to the pointer:
- `v[4]` is equivalent to `*(v+4)`



---

# C-style arrays &ndash; recap

- Old-school arrays can be declared as `type name[size];`
- they can be initialised at that point: `type name[size] = { a, b, c, ... };`
  - `size` is optional in this case
- their size is static &ndash; we cannot dynamically resize these arrays at
  runtime
  - they are only useful when the required size is known at compile-time
- they can be indexed using the subscript operator just like `std::vector`
- they are technically implemented by storing the address of the first element
  - a C-style array is a pointer
- there is no bounds checking! If we try to access an item outside the
array, anything can happen...
  - this is referred to as [undefined behaviour](https://www.geeksforgeeks.org/undefined-behavior-c-cpp/)

--

**Why did we not introduce them earlier?**

- the main reason is that `std::vector` is much more useful and much safer
- C-style arrays are inherited from the older C language
- their use is not recommended in modern C++
  - we should use `std::array` instead if we need a fixed-size array
- ... but we will sometimes encounter them, and so we need to understand them


---

# C-style strings

In the older C language, strings are stored as a C-style array of `char` items
```
char* text = "some text";
```
This declares a pointer to `char`, with the address set to the first element of
the array `some text`

```
                            text = 3459874102
                            ↓
... d641b172e0747349e94e6fbd`some text0`6915ca4990b2f8cbc1e205813aba0ead50ec761b ...
```
Each character is stored according to its [ASCII code](https://en.wikipedia.org/wiki/ASCII)

--

Because the pointer has no knowledge of the size of the array it points to,
C-style strings need to be
[null-terminated](https://en.wikipedia.org/wiki/Null-terminated%5fstring)
- the last character must be the integer value `0` &ndash; the null character
 - note: this is different from the [ASCII code](https://en.wikipedia.org/wiki/ASCII) for the character `0` !

---

# C-style strings

What is the issue with C-style strings?
- they are unsafe!
  - what if the final null character is missing?
- they can be less efficient
  - to determine the size of the string, we have to go through the entire
    array to find the terminating null character
- they are statically-sized
- manipulating C-style strings requires careful handling and memory management
  &ndash; which introduce scope for serious errors!

For these any many other reasons besides, modern C++ provides the much safer
and more convenient `std::string` class

--

Nonetheless, we will sometimes encounter C-style strings, so we need to
understand them

---

# A C-style array of C-style strings

It is possible to declare a C-style array of *pointers*:
```
int x[5] = { 4, 1, 6, 12, 3 };
int y[3] = { 7, 9, 2 };

int* ap[2] = { x, y };

std::cerr << "item 3 of first entry: " << ap[0][3] << "\n";
```
this produces:
```
item 3 of first entry: 12
```




