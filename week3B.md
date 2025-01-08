---
layout: presentation
title: "Week 3, session 2: more on classes"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 3, session 2
## more on C++ classes

---

# Picking up where we left off

We continue working on our [DNA shotgun sequencing
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/DNA_shotgun_sequencing/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/main/projects/DNA_shotgun_sequencing/solution)

.explain-bottom[
Make sure your code is up to date now!
]


---
name: constructor

# Class construction and destruction

With classes, we can define actions to take when creating an instance, and when
destroying an instance
- using [*constructor(s)*](https://www.geeksforgeeks.org/constructors-c/)
  and a [*destructor*](https://www.geeksforgeeks.org/destructors-c/)

--

Constructors are used to ensure all members are initialised to sensible defaults
- for example, by default, `std::string` & `std::vector` both have size zero
- our `ShotgunSequencer` class has a default minimum overlap size of 10 bases

--

The constructor runs immediately after the memory to hold our instance has been
allocated
- but before any of our variables have been initialised 

--

In our previous example, we did not provide any constructors
- in this case, the compiler automatically generates an *implicit default
  constructor*

---

# The *implicit* default constructor

The [default
constructor](https://www.geeksforgeeks.org/default-constructors-in-cpp/) is
used to construct an instance when no additional arguments are provided:
```
std::string s;             // ⇐ invokes default constructor
ShotgunSequencer solver;   // ⇐ invokes (implicit) default constructor
```

--

If no constructor is provided, the compiler will automatically generate an *implicit* default
constructor for us
- this will invoke the default constructor for each of the member variables in turn
- in the same order as declared in the class

--

Our `m_sequence` and `m_fragments` variables have well-defined constructors
- but the `m_minimum_overlap` variable is an `int`, which has no default
  constructor
- the memory corresponding to our `int` is simply left as-is: uninitialised
  - whatever value was already present at that memory location simply remains
    there
--
- ... unless we have a provided a default value using [in-class member
  initialisation](https://isocpp.org/wiki/faq/cpp11-language-classes#member-init) &ndash; which we have!


---

# The *implicit* default constructor

```
#pragma once

#include "fragments.h"

class ShotgunSequencer {
  public:
    void init (const Fragments& fragments);
    bool iterate ();
    void check_remaining_fragments ();

    const Fragments& remaining_fragments () const { return m_fragments; }
    const std::string& sequence () const { return m_sequence; }

  private:
    const int m_minimum_overlap = 10;
    std::string m_sequence;
    Fragments m_fragments;
};
```

--
.explain-top[
The implicit default constructor will:
- set the value of `m_minimum_overlap` to 10
- initialise `m_sequence` using the default constructor for `std::string` (zero
  length)
- initialise `m_fragments` using the default constructor for `Fragments`, which
  is an alias for `std::vector<std::string>` (also zero length)

]

---

# Specifying the default constructor

If the implicit default constructor is sufficient for your needs, great!

But what if we wanted to allow different values for the minimum overlap?
- if `m_minimum_overlap` is to stay `const`, we need to do this in the constructor

--

⇒ Let's start by declaring an explicit default constructor:
- we'll add an argument to set the minimum overlap later

```
class ShotgunSequencer {
  public:
*   ShotgunSequencer () :
*      m_minimum_overlap (10) { }
    ...
  private:
*   const int m_minimum_overlap;
    ...
};
```

--

Let's unpack what is going on here...


---

# Specifying the default constructor

```
class ShotgunSequencer {
  public:
    `ShotgunSequencer` () :
       m_minimum_overlap (10) { }
    ...
  private:
    const int m_minimum_overlap;
    ...
};
```
Constructors are declared like regular methods, but:
- we use the name of the class
- with no return type

---

# Specifying the default constructor

```
class ShotgunSequencer {
  public:
    ShotgunSequencer `()` :
       m_minimum_overlap (10) { }
    ...
  private:
    const int m_minimum_overlap;
    ...
};
```
Since this is the *default* constructor, it takes no arguments
- we can also have constructors that accept arguments, but they are then no
  longer *default* constructors

---

# Specifying the default constructor

```
class ShotgunSequencer {
  public:
    ShotgunSequencer () `:`
       `m_minimum_overlap (10)` { }
    ...
  private:
    const int m_minimum_overlap;
    ...
};
```
We can then (optionally) initialise member variables using [list
initialisation](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/)
- this can be used to *construct* member variables with non-default values
- here, we only need to construct `m_minimum_overlap` &ndash; the other
  variables can be default-constructed

--

This is done before the body of the constructor
- using a colon followed by a comma-separated list
- any member that requires non-default construction is listed with
  its constructor arguments in brackets
- members should be initialised in the same order as listed in the class
  declaration

---

# Specifying the default constructor

```
class ShotgunSequencer {
  public:
    ShotgunSequencer () :
       m_minimum_overlap (10) `{ }`
    ...
  private:
    const int m_minimum_overlap;
    ...
};
```

This is followed by the body of the constructor, in braces
- in our case, we do not need to take any further action, so we leave the body
  empty
- note in this case, we have also defined our constructor within the class
  declaration
  - it will implicitly be `inline`

---

# Specifying the default constructor

```
class ShotgunSequencer {
  public:
*   ShotgunSequencer ();
    ...
  private:
    const int m_minimum_overlap;
    ...
};
```


In `shotgun_sequencer.cpp`:
```
*   ShotgunSequencer::ShotgunSequencer () : 
*       m_minimum_overlap (10 { }
```

If you need to define the constructor *outside* the class declaration, note
that:
- the fully-qualified name of the constructor is `ClassName::ClassName`
   - we declare the constructor (`ClassName`) method within the scope of
     the `ClassName` class
- the initialiser list goes with the *definition* &ndash; not the *declaration*

---

# Specifying the default constructor

```
class ShotgunSequencer {
  public:
    ShotgunSequencer () :
       m_minimum_overlap (10) { }
    ...
  private:
*   const int m_minimum_overlap;
    ...
};
```

Note that we no longer need to specify a default value for `m_minimum_overlap`
when declaring it
- there is no point since this variable will now be initialised in the
  constructor
- the value specified in the constructor will take precedence


---

# Initialiser list or body of constructor?

```
class ShotgunSequencer {
  public:
*   ShotgunSequencer () { m_minimum_overlap = 10; }
    ...
  private:
    const int m_minimum_overlap;
    ...
};
```
Rather than use an initialiser list, we might want to set the value of member variables
in the body of the constructor

--

This is not possible here, since `m_minimum_overlap` is already `const`
  within the body of the constructor!
  <br>&rArr; we *have* to use a list initialiser for `const` members


---

# Initialiser list or body of constructor?

```
class ShotgunSequencer {
  public:
*   ShotgunSequencer () { m_minimum_overlap = 10; }
    ...
  private:
    int m_minimum_overlap;
    ...
};
```

This would be possible if `m_minimum_overlap` was not `const`
- and for simple data types like `int`, this would make no difference

--

However, in many cases this is not so efficient
- all members need to be constructed *before* the body of the constructor is
  executed
- there will be cases where the default constructor performs operations that
  are then immediately negated by the subsequent assignment in the body of the
  constructor

&rArr; always prefer list initialisation where possible


---

# Specifying a non-default constructor

```
class ShotgunSequencer {
  public:
    ShotgunSequencer () :
       m_minimum_overlap (10) { }
*   ShotgunSequencer (int minimum_overlap) :
*      m_minimum_overlap (minimum_overlap) { }
    ...
};
```

We can define other constructors
- this relies on [function overloading](https://www.geeksforgeeks.org/function-overloading-c/)

--

Function overloading refers to the declaration of multiple functions with the same name, but with different arguments
- the *number* of arguments may be different
- the *type* of the arguments may be different
- the compiler must be able to unambiguously figure out which function overload
  to use based on the arguments provided

---

# Specifying a non-default constructor

```
class ShotgunSequencer {
  public:
*   ShotgunSequencer () :
       m_minimum_overlap (10) { }
*   ShotgunSequencer (int minimum_overlap) :
       m_minimum_overlap (minimum_overlap) { }
    ...
};
```

Here, we have:
- a (default) construct with no arguments 
  <br>&rArr; the default value of 10 will be used for the minimum overlap
- a constructor that takes a single `int` argument
  <br>&rArr;  the value provided will be used for the minimum overlap

⇒ no ambiguity

---

# Specifying a non-default constructor

```
class ShotgunSequencer {
  public:
*   ShotgunSequencer () :
       m_minimum_overlap (10) { }
*   ShotgunSequencer (int minimum_overlap) :
       m_minimum_overlap (minimum_overlap) { }
    ...
};
```

We can now use one constructor when we want to stick with the default value:
```
  ShotgunSequencer solver;
```
or we can use the other constructor when we want to specify this value:
```
  ShotgunSequencer solver (10);
```


---

# Handy trick: using default arguments

```
class ShotgunSequencer {
  public:
    ShotgunSequencer (`int minimum_overlap = 10`) :
       m_minimum_overlap (minimum_overlap) { }
    ...
};
```

In some case, we can use [default function
arguments](https://www.geeksforgeeks.org/default-arguments-c/) to avoid the
need for two separate constructors
- functions arguments can be provided with default values (as shown above)
  - as long as they are the last argument(s) in the list
- the compiler will substitute the value specified if it is not provided at the
  point of use

--

This means we only need to define a single constructor to achieve the same
functionality!

--

We will see more examples of default arguments later in the course


--

.explain-bottom[
Have a go at adding a constructor to your own code
]

---


# The class destructor

Mention only, will cover later (with inheritance)


---

# Constructor chaining

---

# Access specifiers for class methods


---

# Solutions


---

# Exercises


