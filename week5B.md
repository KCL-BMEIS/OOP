---
layout: presentation
title: "Week 5, session 2: pointers, iterators and lambda expressions"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 5, session 2
## pointers, iterators<br>and lambda expressions

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

# Multiple pointers, same address

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
void increment (int* pval) { *pval += 2; }
```
--

which can then be used as
```
int x = 10;
increment (&x);   // <-- we need to pass the address of x!
std::cout << "value of x is now " << x << "\n";
```

--

this produces:
```
value of x is now 12
```
---

# Pointers compared to references

Compare this to the same operation using C++ references (the recommended way!):
```
void increment (int& val) { val += 2; }
```
--

which can then be used as
```
int x = 10;
increment (x);   // <-- no need to take the address of x
std::cout << "value of x is now " << x << "\n";
```

--

to produce:
```
value of x is now 12
```

--

As you can appreciate, there is a very tight relationship between *pointers* and *references*
- references act as another name (an alias) for the same variable
- pointers store the address of the variable

---

# Pointers to classes

Pointers can also be used to point to a class or struct:
```
class MyClass {
  public:
    int x;
    float f;
    std::string text;
};

MyClass var = { 5, 3.14, "hello!" };
MyClass* pvar = &var;

std::cerr << "pvar points to x = " << (*pvar).x
          << ", f = " << (*pvar).f
          << ", text = \"" << (*pvar).text << "\"\n";
```
this produces:
```
pvar points to x = 5, f = 3.14, text = "hello!"
```

---

# Pointers to classes

Referring to a member of a class from a pointer is so common it has its own
operator:
```
class MyClass {
  public:
    int x;
    float f;
    std::string text;
};

MyClass var = { 5, 3.14, "hello!" };
MyClass* pvar = &var;

std::cerr << "pvar points to x = " << `pvar->x`
          << ", f = " << `pvar->f`
          << ", text = \"" << `pvar->text` << "\"\n";
```
this produces:
```
pvar points to x = 5, f = 3.14, text = "hello!"
```

---

# The problem with pointers

Pointers are an incredibly powerful tool, but also provide multiple ways of
introducing errors

--

What if the object that an pointer refers to is no longer in scope?

```
int* get_pointer_to_value () {
  int value = complicated_calculation();
  return &value;  // points to local variable!
}
```

--

What if the address in the pointer is modified so that it points to an
  invalid location?

```
int x = 10;
int* p = &x;
...
p++;
...
process_value (&p); // what value does p refer to now?
```

---
class: section

# C-style arrays

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

&rArr; let's look at the operations that we can perform with pointers

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
&rArr; even though difference in actual memory location is 12 bytes, the
difference between pointers is expressed in units of the type pointed to:
`float`

---

# Pointer arithmetic

We can request the element at some offset relative to the pointer:
```
float v[5] = { 2.3, 6.3, 1.9, -3.12, 5.356 };

std::cerr << "Value in v at offset 4:  " << `v[4]` << "\n";
std::cerr << "Value in v at offset 4:  " << `*(v+4)` << "\n";
```

produces:
```
Value in v at offset 4:  5.356
Value in v at offset 4:  5.356
```
--

You can see that the subscript operator `[]` is equivalent to dereferencing the
address at the specified offset from the pointer:
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
class: section

# C-style strings

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
- e.g. the character `A` is stored as the integer value 65.

--

A pointer does not 'know' the size of the array it points to
&rArr; C-style strings are [null-terminated](https://en.wikipedia.org/wiki/Null-terminated%5fstring)
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
  - this introduces scope for serious errors!

For these and many other reasons besides, modern C++ provides the much safer
and more convenient `std::string` class

--

Nonetheless, we will sometimes encounter C-style strings, so we need to
understand them

---

# C-style array of pointers

It is possible to declare a C-style array of *pointers*:
```
int x[5] = { 4, 1, 6, 12, 3 };
int y[3] = { 7, 9, 2 };

*int* ap[2] = { x, y };

std::cerr << "item 3 of first entry: " << ap[0][3] << "\n";
```
this produces:
```
item 3 of first entry: 12
```
--

- `ap[0]` is the first entry in the `ap` array: `x`
- `ap[0][3]` is entry 3 of `ap[0]` &ndash; in other words, `x[3]`
- alternatively: `ap[0][3]` can be interpreted as `(ap[0])[3]`


---

# C-style array of C-style strings

One use case for a C-style array of pointers is to store an array of strings:
```
char* a = "one";
char* b = "two";
char* c = "three";

char* list[] = { a, b, c };

std::cout << "Entry 2 in list is \"" << list[2] << "\"\n";
```
which produces:
```
Entry 2 in list is "three"
```

--

You will recognise this from the definition of the `main()` function:
```
int main (int argc, `char* argv[]`)
```

---

# The command-line arguments

We are now finally in a position to explain how the arguments are provided to
our command!

```
int main (int argc, char* argv[])
```

- `argv` is a C-style array of C-style strings
- `argc` is the number of arguments
  - since the `argv` pointer can't provide information about the size of the array it
    points to

--

We can now make more direct use of these arguments:
```
int main (int argc, char* argv[]) 
{
  for (int n = 0; n < argc; n++)
    std::cout << "argument " << n << " is \"" << argv[n] << "\"\n";
  return 0;
}
```

--

However, we still recommend converting to a `std::vector<std::string>` on this
course!

---
class: section

# STL iterators

---

# The C++ Standard Template Library (STL)

The C++ STL provides many useful *containers* and *algorithms*

We have already made extensive use of the `std::vector` container
- but [there are many
  others](https://www.geeksforgeeks.org/containers-cpp-stl/)

We have already made use of many STL algorithms
- `std::min()`, `std::max()`, `std::find()`, ...

--

<br>
But much of this functionality requires the use of *iterators*

&rArr; what are they, and how do they work?

---

# Iterators

In essence, STL iterators are objects that behave just like pointers
- in fact, regular pointers can often be used as iterators!

--

They are designed to provide a lightweight object that can:
- *point* to an element of a container
- *provide the value* of the element it points to
- be *incremented* to point to the next element
- have an integer added to it to point to the element that many positions along
  in the container
- ...

--

STL containers all provide:
- a `begin()` method that returns an iterator to the first element in the
  container
- an `end()` method that return an iterator to one past the last element in the
  container 
  - the iterator returned by `end()` does not point to a valid element!


---

# How to use iterators

Iterators are designed to be used as if they were pointers
- this is achieved using [operator
  overloading](https://www.geeksforgeeks.org/iterators-operations-in-cpp/)

```
std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

auto it = x.begin();
std::cout << "iterator value is " << *it << "\n";

it++;
std::cout << "value at iterator is now " << *it << "\n";


it += 4;
std::cout << "value at iterator is now " << *it << "\n";

std::cout << "value at (iterator+2) is " << *(it+2) << "\n";

std::cout << "iterator is at offset " << it-x.begin() << "\n";
```

---

# How to use iterators

the code on the previous slide produces:
```
iterator value is 1
value at iterator is now 2
value at iterator is now 6
value at (iterator+2) is 8
iterator is at offset 5
```

--

But we could already do all this just as easily using the subscript `[]`
operator!

&rArr; why do we really need iterators?

---

# How to use iterators with STL algorithms

[STL algorithms](https://www.geeksforgeeks.org/algorithms-library-c-stl/) rely
on iterators, and are found in the `<algorithm>` header

**Example: `std::find()`:**
```
*std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

auto it = std::find (x.begin(), x.end(), 7);
std::cerr << "element with value 7 is at position " 
          << it - x.begin() << ", value = " << *it << "\n";
```
produces:
```
element with value 7 is at position 6, value = 7
```

`x.begin()` and `x.end()` specify the *range* over which to perform the search:
- from `x.begin()` up to (but not including) `x.end()`

---

# How to use iterators with STL algorithms

Note: you can also use the `std::distance()` function instead of the
subtraction:

**Example: `std::find()`:**
```
std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

auto it = std::find (x.begin(), x.end(), 7);
std::cerr << "element with value 7 is at position " 
          << `std::distance (x.begin(), it)` << ", value = " << *it << "\n";
```
produces:
```
element with value 7 is at position 6, value = 7
```

---

# How to use iterators with STL algorithms

C++20 also introduces a slightly simpler version with the [ranges library](https://www.geeksforgeeks.org/cpp-20-ranges-library/)

**Example: `std::ranges::find()`:**
```
std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

auto it = `std::ranges::find (x, 7)`;
std::cerr << "element with value 7 is at position " 
          << std::distance (x.begin(), it) << ", value = " << *it << "\n";
```
produces:
```
element with value 7 is at position 6, value = 7
```

This version assumes we want to search from `begin()` to `end()` of the
container supplied as the first argument.

You need to `#include <ranges>` to use functions in the `std::ranges` namespace

---

# How to use iterators with STL algorithms

What happens when the container doesn't have the requested element?

**Example: `std::ranges::find()`:**
```
std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

auto it = std::ranges::find (x, `12`);
std::cerr << "element with value 12 is at position " 
          << std::distance (x.begin(), it) << ", value = " << *it << "\n";
```
produces:
```
element with value 12 is at position 10, value = `???`
```

When the item is not found, `std::find()` / `std::ranges::find()` return
`x.end()`
- this is one past the last element in the container
- &rArr; in this case, this is 10 elements from the beginning
- dereferencing the iterator may return nonsense, crash the program, ...

---

# How to use iterators with STL algorithms

What happens when the container doesn't have the requested element?

**Example: `std::ranges::find()`:**
```
std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

auto it = std::ranges::find (x, 12);
`if (it == x.end())`
  std::cerr << "element with value 12 not found!\n";
else 
  std::cerr << "element with value 12 is at position " 
            << std::distance (x.begin(), it) << ", value = " << *it << "\n";
```
produces:
```
element with value 12 not found!
```

We need to check whether the item has been found before dereferencing the
iterator!

---

# How to use iterators with STL algorithms

`std::max_element()` and `std::min_element()` return the
*iterator* to the relevant item:

**Example: `std::max_element()`**
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
auto it = `std::max_element (x.begin(), x.end())`;
std::cerr << "max value is " << *it << "\n";
```
produces
```
max value is 82
```


---

# How to use iterators with STL algorithms

There is a more convenient version in the [ranges library](https://www.geeksforgeeks.org/cpp-20-ranges-library/):

**Example: `std::ranges::max()`**
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
std::cerr << "max value is " << `std::ranges::max (x)` << "\n";
```
produces
```
max value is 82
```

---

# How to use iterators with STL algorithms

The `std::sort()` function sorts the items in-place:

**Example: `std::sort()`**
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
`std::sort (x.begin(), x.end())`;
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```
produces
```
-23 -2 1 5 9 13 18 21 42 82
```

This operation modifies the vector. If you need to preserve the original order,
make a copy before sorting!

---

# How to use iterators with STL algorithms

As before, there is a slightly more convenient version in the [ranges library](https://www.geeksforgeeks.org/cpp-20-ranges-library/):

**Example: `std::ranges::sort()`**
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
`std::ranges::sort (x)`;
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```
produces
```
-23 -2 1 5 9 13 18 21 42 82
```
---

# How to use iterators with STL algorithms

There are many more algorithms available in the STL

Please [consult the documentation
online](https://www.geeksforgeeks.org/algorithms-library-c-stl/) if you need to use any others.


---

# Providing operations to STL algorithms

Some of the algorithms in the STL expect you to provide an *operation* to apply to
individual items

These include:
- `std::for_each()`
- `std::transform()`
- `std::generate()`
- ...

This can take the form of:
- a regular function
- a class with an overloaded `operator()`
- a *lambda expression*

There are also equivalent versions of these algorithms in the [ranges library](https://www.geeksforgeeks.org/cpp-20-ranges-library/)

---

# Providing operations to STL algorithms

For example, using a regular function:
```
int dist_from_12 (int v) { return std::abs(12-v); }
...

std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
std::transform (x.begin(), x.end(), x.begin(), dist_from_12);
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```
produces
```
11 9 1 70 14 3 30 7 35 6
```

---

# Providing operations to STL algorithms

For example, using a regular function:
```
int dist_from_12 (int v) { return std::abs(12-v); }
...

std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
std::transform (`x.begin(), x.end()`, x.begin(), dist_from_12);
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```
produces
```
11 9 1 70 14 3 30 7 35 6
```

`std::transform` applies the operation to each element in the *input range*

---

# Providing operations to STL algorithms

For example, using a regular function:
```
int dist_from_12 (int v) { return std::abs(12-v); }
...

std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
std::transform (x.begin(), x.end(), `x.begin()`, dist_from_12);
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```
produces
```
11 9 1 70 14 3 30 7 35 6
```

`std::transform` applies the operation to each element in the *input
range*,<br>
storing the transformed element in the *output range*, starting from the position
specified
- here, the output range is the same as the input range, to apply the operation
  in-place


---

# Providing operations to STL algorithms

This time, using a class with an overloaded `operator()` method:
```
class dist_from {
  public:
    dist_from (int value) : m_value (value) { }
*   int operator() (int v) const { return std::abs(m_value-v); }
  private:
    const int m_value;
};

std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
std::transform (x.begin(), x.end(), x.begin(), `dist_from (5)`);
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```

With a class, we can store other parameters in the class 
- here, we can specify a different value at the point of use

---

# Providing operations to STL algorithms

For simple operations, a struct can be used to the same effect:
```
struct dist_from {
    int operator() (int v) const { return std::abs(m_value-v); }
    const int m_value;
};




std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };
std::transform (x.begin(), x.end(), x.begin(), `dist_from { 5 }`);
for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```

- structs are `public` by default
- the `m_value` member doesn't need to be private &ndash; especially if
  `const`
- we can use aggregate initialisation and avoid the need to provide an explicit
  constructor



---
class: section

# Lambda expressions

---
layout:true

# Lambda expressions

These allow small functions to be declared in line with the code, near or at
the point of use

A simple lambda expression might look like this:

---
```
auto dist_from_12 = [](int v) { return std::abs(v-12); }
```
---
```
`auto` dist_from_12 = [](int v) { return std::abs(v-12); }
```
- The type of a lambda expression is obscure, and best left for the compiler to
work out.

---
```
auto `dist_from_12` = [](int v) { return std::abs(v-12); }
```
- The type of a lambda expression is obscure, and best left for the compiler to
work out.
- If needed, you can give a name to the lambda expression 

---
```
auto dist_from_12 = `[]`(int v) { return std::abs(v-12); }
```
- The type of a lambda expression is obscure, and best left for the compiler to
work out.
- If needed, you can give a name to the lambda expression 
- The *capture clause* can be used to give access to variables from the
  enclosing scope, if required
  - here, we leave it empty for now


---
```
auto dist_from_12 = []`(int v)` { return std::abs(v-12); }
```
- The type of a lambda expression is obscure, and best left for the compiler to
work out.
- If needed, you can give a name to the lambda expression 
- The *capture clause* can be used to give access to variables from the
  enclosing scope, if required
  - here, we leave it empty for now
- Next, we provide the arguments to the expression, as we would for normal
  functions


---
```
auto dist_from_12 = [](int v) `{ return std::abs(v-12); }`
```
- The type of a lambda expression is obscure, and best left for the compiler to
work out.
- If needed, you can give a name to the lambda expression 
- The *capture clause* can be used to give access to variables from the
  enclosing scope, if required
  - here, we leave it empty for now
- Next, we provide the arguments to the expression, as we would for normal
  functions
- Finally, we provide the *body* of expression, to define what the function
  should do


---
```
auto dist_from_12 = [](int v) `-> int` { return std::abs(v-12); }
```
- The type of a lambda expression is obscure, and best left for the compiler to
work out.
- If needed, you can give a name to the lambda expression 
- The *capture clause* can be used to give access to variables from the
  enclosing scope, if required
  - here, we leave it empty for now
- Next, we provide the arguments to the expression, as we would for normal
  functions
- Finally, we provide the *body* of expression, to define what the function
  should do
- (optional) If the compiler cannot deduce the type of the return value, this can also be
  specified as shown

---
layout: false

# Lambda expressions and STL algorithms

We can use these lambda expressions with our STL algorithms:
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };


*auto dist_from_12 = [](int v) { return std::abs(v-12); }

std::transform (x.begin(), x.end(), x.begin(), `dist_from_12`);

for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```

---

# Lambda expressions and STL algorithms

If we don't need to re-use our expression elsewhere, we can use an *anonymous
lambda*:
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };



std::transform (x.begin(), x.end(), x.begin(), 
                `[](int v) { return std::abs(v-12); }`);

for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```
The combination of STL algorithms with Lambda expressions provides a powerful
framework
- the operation can be specified in a concise way at the point of use
- the way the operation is applied to the container is implicit in the choice
  of algorithm

---

# Lambda capture

The capture clause can be used to provide access to variables from the current
scope:
```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };


`int ref = 5;`
std::transform (x.begin(), x.end(), x.begin(), 
                [`ref`](int v) { return std::abs(v-`ref`); });

for (auto i : x)
  std::cout << i << " ";
std::cout << "\n";
```

This can be useful if the operation depends on some other parameter(s)
- in this case, `ref` may not be known at compile-time, for example

---

# Lambda capture

Parameters can also be captured by reference, which allows modification of the
original variable:

```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };


`int sos = 0;`
`std::for_each` (x.begin(), x.end(), 
               `[&sos]`(int n) { `sos += n*n;` });

std::cout << "sum of squares is " << sos << "\n";
```
produces:
```
sum of squares is 10062
```

`std::for_each` performs an operation on each item, but does not expect a
return value
- it cannot be used to *transform* the items

---

# Lambda capture

It is possible to capture multiple parameters, by copy or by reference:

```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };

`int ref = 12;`
`int sos = 0;`
std::for_each (x.begin(), x.end(), 
               `[ref,&sos]`(int n) { sos += (n-ref)*(n-ref); });

std::cout << "sum of squared difference from " << ref << " is " << sos << "\n";
```
produces:
```
sum of squared difference from 12 is 7518
```

Here, `ref` can be passed by copy, since it does not need to be modified
- it is also small enough that passing by copy will not affect performance

On the other hand, `sos` needs to be passed by reference as it needs to be
modified in the lambda

---

# Lambda capture

Finally, it is also possible to capture *all* local variables by reference:

```
std::vector<int> x = { 1, 21, 13, 82, -2, 9, 42, 5, -23, 18 };

int ref = 12;
int sos = 0;
std::for_each (x.begin(), x.end(), 
               `[&]`(int n) { sos += (n-ref)*(n-ref); });

std::cout << "sum of squared difference from " << ref << " is " << sos << "\n";
```
produces:
```
sum of squared difference from 12 is 7518
```

---

# Exercises

Use a lambda function to perform the task rescaling in the fMRI project
- you can then remove the `rescale()` function in `task.h` / `task.cpp`
