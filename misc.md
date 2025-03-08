---
layout: presentation
title: "Miscellaneous slides"
---

# Error handling

The previous example is a simple way to handle errors.
- we'll learn a better way when we cover *exceptions* later in the course

--

Some general rules about error handling:

- If your code is making assumptions about its inputs, check them!
  - for example, if your code assumes a parameter is positive, check and alert the user if this is not the case (and exit if appropriate)
  - *this will save you time later on!*

--

- If you can reasonably handle the error, do so, but warn the user about it

--

- Most of the time, the error will be *fatal* (not recoverable), in which case your program should *not* proceed
  - issue an informative message about the problem, and exit with a non-zero exit code

--

- try to detect errors as early as possible 
  - for example: don't start a long batch of processing without first checking that you can create the output file



---
name: type_alias

# Type Aliasing

We have already started using a vector of strings to store the fragments
&ndash; and it does seem to provide all the functionality we need at this point

--

We could type `std::vector<std::string>` as the type for the fragment list
wherever this is needed
- but it is a bit long...
- it is not obvious what its purpose is to outside observers
- what if we decide to use a different type to store the fragments at a later
  stage? We'd need to modify our code in lots of different places

--

This is an example where defining a [*type
alias*](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/) might be a good idea:
```
using Fragments = std::vector<std::string>;
```

Now we can use `Fragments` as the type for our list of fragments, and the
compiler will understand that to mean `std::vector<std::string>`
- note this is *not* a new type - merely an *alias* for an existing type


---

# Type Aliasing

What does this look like in our project?
```
... 

*using Fragments = std::vector<std::string>;

`Fragments` load_fragments (const std::string& filename)
{
  ...
```


```
... 

void fragment_statistics (const `Fragments`& fragments)
{
  ...
```

--

.explain-bottom[
Exercise: modify your code as shown here
]

---
name: structured_binding

class: section

# Structured binding

## Splitting up grouped data

---

# Structured binding

The C++17 standard introduced the ability to use [*structured binding*](https://www.geeksforgeeks.org/structured-binding-c/)
- this allows us to declare and initialise multiple variables from the
  individual members of a larger composite variable

--


This is best illustrated by example, using our `find_biggest_overlap()`
function:
```
`auto overlap` = find_biggest_overlap (sequence, fragments);
std::cerr << std::format ("overlap of size {} at index {}\n", 
                          `overlap.size`, `overlap.fragment`);
```

--

Using *structured binding*, we can declare independent variables for each
member of the `Overlap` structure returned:
```
auto [ overlap, index ] = find_biggest_overlap (sequence, fragments);
std::cerr << std::format ("overlap of size {} at index {}\n", `overlap`, `index`);
```
--

.explain-bottom[
Exercise: modify your own code to use structured binding as shown here
]

---
class: info

# Structured binding using `std::tuple`

The C++ STL provides a convenience template class that can be used as a
lightweight replacement for a dedicated `struct` in a variety
of contexts: [`std::tuple`](https://www.geeksforgeeks.org/tuples-in-c/)

One use for `std::tuple` is for structured binding:
```
#include <tuple>

std::tuple<int,int> find_biggest_overlap (const std::string& sequence, 
                                          Fragments& fragments)
{
  ...
  return { biggest_overlap, fragment_with_biggest_overlap };
}

...

auto [ overlap, index ] = find_biggest_overlap (sequence, fragments);
```

---
class: info

# Why don't we use `std::tuple`?

While appealing in its simplicity, `std::tuple` does not provide any indication
about the *interpretation* or *meaning* of each member
- in our case, all we know is that we get 2 `int`s 
- which one represents the overlap size, and which the index?
- We have to rely on additional documentation to work this out 
  - this could be described in a comment, or some other external document

--

On the other hand, using a `struct` provides *named* members, whose interpretation is
immediately much clearer. 

&rArr; Better to use a `struct` with named members rather than a `std::tuple`
where possible

--

The `std::tuple` class is very useful in other contexts, especially when
working with generic functions and containers 
- a generic function or container will not know ahead of time what it
  is to contain
- `std::tuple` provides a simple container for an arbitrary number of variables
  of arbitrary types
- `std::tuple` is therefore used in many places throughout the C++ STL

---

# Structured binding

Structured binding offers another way to return multiple values from a function
- this can sometimes be more convenient or more legible

--

There are many other uses for structured binding
- many of these are too advanced for this course 
  - indeed, arguably some of the most useful were [only introduced in
    C++23](https://www.cppstories.com/2023/view-zip/)!
- if interested, [have a look online for examples](https://www.cppstories.com/2022/structured-bindings/)


---
name: string_view

class: section

# `std::string_view`

## avoiding needless copies

---

# Performance issues

Let's take a look at our code so far, and try to reason about where most of the
time is spent

--

The bulk of our algorithm consists of a series of nested loops:

&ensp; &bull; loop while there are fragments left to merge
<br>&ensp; &emsp; &bull; &ensp; loop over all candidate fragments
<br>&ensp; &emsp; &emsp; &bull; &ensp; loop over all overlap sizes 
<br>&ensp; &emsp; &emsp; &emsp; &bull; &ensp; extract the corresponding substrings and compare
<br>&ensp; &emsp; &bull; &ensp; merge the fragment with the largest overlap 
<br>&ensp; &emsp; &bull; &ensp; remove it from the list of candidate fragments

--

When looking for opportunities to improve performance, we should focus our
attention on the *innermost loop*
- this is the portion of code that will be executed most often

--

&rArr; what is going on in the innermost loop?

---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
--
We actually have three loops, although we did not write them up ourselves!


---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = `sequence.substr(0, overlap)`;
    const auto frag_end = `fragment.substr(fragment.size()-overlap)`;
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We actually have three loops, although we did not write them up ourselves!
- one for extracting each substring

---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (`seq_start == frag_end`) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We actually have three loops, although we did not write them up ourselves!
- one for extracting each substring
- one for the comparison itself


---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    `const auto seq_start` = sequence.substr(0, overlap);
    `const auto frag_end` = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We actually have three loops, although we did not write them up ourselves!
- one for extracting each substring
- one for the comparison itself

We also have some implicit memory allocation & deallocation for each substring
- we will cover this much later in the course


---

# The innermost loop

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
Can we avoid any of these overheads?
--
- there is not much that can be done about the comparison itself
  - thankfully, it will tend to terminate early (as soon as any character
    doesn't match)
--
- but can we avoid copying each substring into a whole new `std::string` to
  perform the comparison?

---

# Avoiding needless copying

```
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    bool match = true;
    for (int n = 0; n < overlap; ++n) {
      if (sequence[n] != fragment[fragment.size()-overlap+n]) {
        match = false;
        break;
      }
    }
    if (match) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```

We can perform the comparison manually character-by-character, ensuring we
compare the characters at the correct positions


---

# The `std::string_view` class

```


int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = sequence.substr(0, overlap);
    const auto frag_end = fragment.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
... or we can use the `std::string_view` class to achieve the same effect!

---

# The `std::string_view` class

```
#include <string_view>
...
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = `std::string_view (sequence)`.substr(0, overlap);
    const auto frag_end = `std::string_view (fragment)`.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
... or we can use the `std::string_view` class to achieve the same effect!


---

# The `std::string_view` class

How does this work?

Each `std::string` holds information consisting of:
- the size of the string
- a handle to the *memory location* corresponding to the start of the text
  - this is actually a [pointer](https://www.geeksforgeeks.org/cpp-pointers/) &ndash; which we are trying to avoid as much as
    possible on this course!


```xml
                         ↓
(*#&\:;*'¬|\^$(&*^$%("()!`this is the text that our string contains`@~@:~#*(£';~"£*(£|#@
```

--
Memory is essentially a very long list of 8-bit *bytes*
- most of these are going to contain data in machine representation (binary)
  - none of that will make sense as text
- the text for our string will occupy some contiguous section of memory
  - the `std::string` class only needs to know *where it starts* and *how long it
    is*

--

The `std::string_view` class holds *exactly the same information*

---

# The `std::string_view` class

The `std::string_view` class provides a *non-owning (and non-modifiable) view*
of a string

Notably, it provides its own `substr()` method, which also returns a
`std::string_view`
- with a different start and size for the substring
- no copying is performed!

--

Original `std::string`: 
- start at position 1000, size 41 bytes

```xml
                         ↓
(*#&\:;*'¬|\^$(&*^$%("()!`this is the text that our string contains`@~@:~#*(£';~"£*(£|#@
⁣
```

---

# The `std::string_view` class

The `std::string_view` class provides a *non-owning (and non-modifiable) view*
of a string

Notably, it provides its own `substr()` method, which also returns a
`std::string_view`
- with a different start and size for the substring
- no copying is performed!

Original `std::string`: 
- start at position 1000, size 41 bytes

```xml
                         ↓
(*#&\:;*'¬|\^$(&*^$%("()!this is the text that `our string` contains@~@:~#*(£';~"£*(£|#@
                                               ↑
```

`std::string_view` for `"our string"`: 
- start at position 1022, size 10 bytes


---
class: section

# Ownership and lifetime

---

# Ownership and lifetime

The main difference between `std::string` and `std::string_view` is one of
*ownership*

--

Each `std::string` 'owns' the memory where its text is
stored, and is responsible for its management
- it needs to *allocate* the memory when some text needs to be stored
- it needs to *free* or *deallocate* that memory when no longer in use, so
  that the memory can be used for other purposes

--

Each `std::string_view` only provides a *view* into some existing text in
memory
- it does not *own* that memory, and is not responsible for managing it

--

Consequently, `std::string_view` instances are very cheap to create and destroy
- no memory management!
- no copying!

--

But we need to be very careful with the *lifetime* of that memory location...

---

# Ownership and lifetime

When extracting a substring using the original `std::string`, we got a new
`std::string`
- this new `std::string` contained a fully self-contained *copy*
  of the corresponding text 
- its *lifetime* was not tied to the lifetime of the original `std::string`

--

But when we extract a substring using the new `std::string_view`, we
get a non-owning *view*
- the text in that view is completely dependent on the original `std::string`
- its *lifetime* is intrisincally tied to that of the original `std::string`

--

There is nothing to prevent the use of a `std::string_view` that is no longer
valid!
- no mechanism exists in C++ to prevent this
- if the original `std::string` no longer exists, or points to new
  location, we will get [undefined behaviour](https://en.wikipedia.org/wiki/Undefined_behavior)
  - the code may crash, we could get nonsense back, etc.

--
It is up to the developer (you!) to ensure the lifetime of the text exceeds
the lifetime of the view
- this is a very common source of bugs and security vulnerabilities

---

# Ownership and lifetime &ndash; examples

```
std::string text ("this is the text that our string contains");
std::cout << text << "\n";

auto view = std::string_view (text).substr (22, 10);
std::cout << view << "\n";

text.clear();     // ⇐ original string is no longer valid!
std::cout << view << "\n";
```
--

If you try this, you may find that the code works just fine
- this is because the memory where the text was stored hasn't been modified
- that memory location has been marked as unused and is available for other uses
- ... but we haven't needed to store anything else there &ndash; yet!

--

This is why the result of the last line of code is [undefined behaviour](https://en.wikipedia.org/wiki/Undefined_behavior)
- it may work as expected sometimes, or it may crash other times
- it may depend on what compiler is used, or what settings were used for the
  compiler, etc.

---

# Ownership and lifetime &ndash; examples

```
std::string text ("this is the text that our string contains");
std::cout << text << "\n";

auto view = std::string_view (text).substr (22, 10);
std::cout << view << "\n";

text = "a longer piece of text that won't fit in the original memory location");
// ⇑ forces re-allocation: original string is no longer valid!
std::cout << view << "\n";
```
--

Assigning a different string to our variable can also force a re-allocation
- particularly if the new string is longer than the original
- there is no guarantee that the new string will be allocated at the same
  location!

---

# Ownership and lifetime &ndash; examples

```
std::string_view get_substr () 
{
  std::string original = read_from_file();
  return std::string_view (original);
}

// ⇓ original string has gone out of scope and no longer exists!
std::cout << get_substr() << "\n";
```
--

Returning a non-owning view or reference to a function scope, local variable is a common mistake!
- this applies to any non-owning reference or similar construct

---

# Ownership and lifetime &ndash; examples

```
// a vector of 16 integers:
std::vector<int> v = (16, 0); 

// we take an iterator to the first element:
auto iter = v.begin();

// we take a reference to the second element:
int& ref (v[1]);

// we append another element to the vector:
v.push_back (1);
// ⇑ this may cause a re-allocation of the contents of the vector
// to a different memory location!
```

This issue is much broader than just `std::string_view`
- it affects any constructs that refers to data owned or managed by some other construct
- it can affect references and STL iterators too!


---

# Ownership and lifetime &ndash; examples

These are examples of a more general class of problems, generally referred to as
[dangling references](https://abseil.io/tips/180)
- you will also come across 'dangling pointers', which is essentially the same
  problem 

This applies to references, iterators, pointers and any non-owning construct

--

It is not always obvious when such references become invalidated
- the original owner has been destroyed or gone out of scope
- the original owner has been cleared of its contents
- the original owner has moved its contents to a different location

--

For these reasons, use non-owning constructs with caution!
- in general, they are safe as function *arguments* 
  - the owning object lives in a broader scope with a longer lifetime, and
    will not change while the function runs
- they are *not* safe as return values
  - especially when referring to function scope variables!
- they are *not* safe when there is a possibility of modification of the original
  container

---

# Back to our own code...

```
`#include <string_view>`
...
int compute_overlap (const std::string& sequence, const std::string& fragment)
{
  ...
  for (int overlap = fragment.size(); overlap > 0; --overlap) {
    const auto seq_start = `std::string_view (sequence)`.substr(0, overlap);
    const auto frag_end = `std::string_view (fragment)`.substr(fragment.size()-overlap);
    if (seq_start == frag_end) {
      largest_overlap = overlap;
      break;
    }
  }
  ...
```
--

In our case, we can see that:
- the lifetime of both `std::string_view`s is shorter than the original
  `sequence` & `fragments`
- there is no scope for our code to modify either `sequence` or `fragment`
  while our views are live
  - indeed, we enforced this by providing these to `compute_overlap()` as `const` references!


---

# Impact of using `std::string_view` on performance

We can measure the impact of this simple change using the [`time`
command](https://www.geeksforgeeks.org/time-command-in-linux-with-examples/):

Before the change:
```
$ time ./shotgun ../data/fragments-1.txt out
initial sequence has size 1000
final sequence has length 20108

`real    0m0.359s`
user    0m0.359s
sys     0m0.000s
```
---

# Impact of using `std::string_view` on performance

We can measure the impact of this simple change using the [`time`
command](https://www.geeksforgeeks.org/time-command-in-linux-with-examples/):


After the change:
```
$ time ./shotgun ../data/fragments-1.txt out
initial sequence has size 1000
final sequence has length 20108

`real    0m0.041s`
user    0m0.037s
sys     0m0.004s
```
--

This is almost 10× faster!

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

