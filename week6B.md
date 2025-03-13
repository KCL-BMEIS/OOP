---
layout: presentation
title: "Week 6, session 2: abstract classes, class destructor, finalise robot arm project"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 6, session 2
## Abstract classes, class destructor<br>finalise robot arm project

---

# Picking up where we left off

We continue working on our [robot arm
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/robot_arm/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/robot_solution/projects/robot_arm/solution)

.explain-bottom[
Make sure your code is up to date now!
]

---

# Exercise from last session

Implement the other segment types: `bend`, `rotate`

Use these to set up the full robot arm as specified in the instructions

---
**In `segment/rotate.h`:**
```
#pragma once

#include "segment/base.h"
namespace Segment {

  class Rotate : public Base {
    public:
      Rotate (Base& next, double length) :
        Base (next, "rotate"),
        m_length (length),
        m_angle (0.0) { }

      Point tip_position () const override;

      void set_angle (double angle) { m_angle = angle; }

    private:
      const double m_length;
      double m_angle;
  };

}
```

--

.explain-topright[
We only need two addtional data members: length and angle

<br>
The length will not need to change once initialised
- we can declared it `const`
]

--

.explain-bottomright[
... but the angle needs to be adjustable at run-time
- we do *not* declare it `const`
- we provide a 'setter' method to allow it to be specified
]

---

**In `segment/rotate.cpp`:**
```
#include <cmath>

#include "segment/rotate.h"

namespace Segment {

  Point Rotate::tip_position () const
  {
    auto p = m_next.tip_position();
    const double s = std::sin (m_angle);
    const double c = std::cos (m_angle);
    return {
      c*p[0] - s*p[1],
      s*p[0] + c*p[1],
      m_length + p[2]
    };

  }
}
```

--

.explain-topright[
Note the syntax to define the method outside of the class:
- we need to enclose in within the `Segment` namespace
- we need to specify that it is a member of `Rotate` using the [scope resolution
  operator](https://www.geeksforgeeks.org/scope-resolution-operator-in-c/)
]

--

.explain-bottomright[
This performs the calculation as specified [in the instructions](https://github.com/KCL-BMEIS/OOP/blob/main/projects/robot_arm/assignment.md):
$$
p\_n = \begin{pmatrix} 0 \\\\
0 \\\\
l
\end{pmatrix} + \begin{pmatrix}
\cos(\theta) & -\sin(\theta) & 0 \\\\
\sin(\theta) & \cos(\theta) & 0 \\\\
0 & 0 & 1
\end{pmatrix} p_{n+1}
$$
]

---

**In `segment/rotate.cpp`:** (alternative syntax)
```
#include <cmath>

#include "segment/rotate.h"



* Point Segment::Rotate::tip_position () const
  {
    auto p = m_next.tip_position();
    const double s = std::sin (m_angle);
    const double c = std::cos (m_angle);
    return {
      c*p[0] - s*p[1],
      s*p[0] + c*p[1],
      m_length + p[2]
    };

  }
```

.explain-bottomright[
Instead of enclosing in `Segment` namespace, it is also possible to specify the
method using *nested* scope resolution:
- `tip_position()` is a member of `Rotate`
- ... which is a member of `Segment`
]

---

**In `segment/bend.h`:**
```
#pragma once

#include "segment/base.h"

namespace Segment {

  class Bend : public Base {
    public:
      Bend (Base& next, double length) :
        Base (next, "bend"),
        m_length (length),
        m_angle (0.0) { }

      Point tip_position () const override;

      void set_angle (double angle) { m_angle = angle; }

    private:
      const double m_length;
      double m_angle;
  };

}
```

.explain-bottomright[
This is almost identical to the `Rotate` segment
]

---

**In `segment/bend.cpp`:**
```
#include <cmath>

#include "segment/bend.h"

namespace Segment {

  Point Bend::tip_position () const
  {
    auto p = m_next.tip_position();
    const double s = std::sin (m_angle);
    const double c = std::cos (m_angle);
    return {
      s*(m_length/2.0 + p[2]) + c*p[0],
      p[1],
      m_length/2.0 + c*(m_length/2.0 + p[2]) - s*p[0]
    };

  }
}
```
--

.explain-topright[
This performs the calculation as specified [in the instructions](https://github.com/KCL-BMEIS/OOP/blob/main/projects/robot_arm/assignment.md):
$$
p\_n = \begin{pmatrix}
0 \\\\
0 \\\\
l/2
\end{pmatrix} + \begin{pmatrix}
\cos(\theta) & 0 & \sin(\theta) \\\\
0 & 1 & 0 \\\\
-\sin(\theta) & 0 & \cos(\theta)
\end{pmatrix} \left[ p_{n+1} + \begin{pmatrix} 
0 \\\\
0 \\\\
l/2
\end{pmatrix} \right] 
$$
]

---

**In `robot.cpp`:**
```
void run (std::vector<std::string>& args) 
{
  ...
  // set up robot arm:
  
  Segment::Tip tip (10.0);
  Segment::Bend bend3 (tip, 6.0);
  Segment::Straight straight3 (bend3, 15.0);
  Segment::Rotate rotate3 (straight3, 5.0);
  Segment::Bend bend2 (rotate3, 8.0);
  Segment::Straight straight2 (bend2, 20.0);
  Segment::Rotate rotate2 (straight2, 5.0);
  Segment::Bend bend1 (rotate2, 10.0);
  Segment::Straight straight1 (bend1, 30.0);
  Segment::Rotate rotate1 (straight1, 5.0);

  std::cout << "tip position: " << rotate1.tip_position() << "\n";
  return 0;
}
```

---

**In `root.h`:**
```
#pragma once

#include "segment/base.h"

namespace Segment {
  class Root : public Base {
    public:
      Root (Base& next) :
        Base (next, "root") { }

      Point tip_position () const override;
  };
}
```
**In `root.cpp`:**
```
#include "segment/root.h"

Point Segment::Root::tip_position () const
{
  return m_next.tip_position();
}
```

.explain-topright[
For clarity, we decide to also add a `Root` class, which will act as the
'anchor' for our robot arm

<br>
This simply reports the position of the tip of the next segment, without
modifying it any way.
]

---

**In `robot.cpp`:**
```
void run (std::vector<std::string>& args) 
{
  ...
  // set up robot arm:
  
  Segment::Tip tip (10.0);
  Segment::Bend bend3 (tip, 6.0);
  Segment::Straight straight3 (bend3, 15.0);
  Segment::Rotate rotate3 (straight3, 5.0);
  Segment::Bend bend2 (rotate3, 8.0);
  Segment::Straight straight2 (bend2, 20.0);
  Segment::Rotate rotate2 (straight2, 5.0);
  Segment::Bend bend1 (rotate2, 10.0);
  Segment::Straight straight1 (bend1, 30.0);
  Segment::Rotate rotate1 (straight1, 5.0);
* Segment::Root root (rotate1);

  std::cout << "tip position: " << `root`.tip_position() << "\n";
  return 0;
}
```

.explain-topright[
This makes it clearer as to which segment is at the start of the arm

<br>
The `Root` segment could eventually be extended to have additional controls
specific to its role.
]

---
name: abstract_class
class: section

# Pure virtual methods<br> and abstract classes

---

# Pure virtual methods and abstract classes

It makes no sense for objects of type
`Segment::Base` to be instantiated (created)
- but our design currently allows this to happen

C++ allows one or more methods of a base class to be declared [pure
virtual](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
- this means that we do not or cannot provide an implementation of these
  methods

--

In our case, we cannot provide a sensible implementation for the `tip_position()` method
- we can make that method *pure virtual*:
```
  class Base {
      ...
      virtual Point tip_position () const `= 0`;
      ...
  };
```
--

The `= 0` assignment effectively states that the *base* class only declares the *interface*
- it will *not* provide an implementation of this method
- but *derived* classes *must* provide an implementation of this method

---

# Pure virtual methods and abstract classes

A base class with one or more pure virtual methods is said to be
[abstract](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)

The compiler will refuse to instantiate an object of this type
- it is *incomplete*!
- if it were to create such an object, what happens if the code subsequently
  attempted to call the `tip_position()` method?

--

Abstract classes are therefore designed purely to specify the expected
*interface*
- they are designed to be inherited

---

# Exercise

Make the `Segment::Base` class abstract in your own code

Verify that this makes it impossible to create an object of type
`Segment::Base`!

Verify that derived classes must indeed implement their own version of the pure
virtual `tip_position()` method

---
name: runtime_polymorphism
class: section

# Runtime polymorphism

---

# Runtime polymorphism

Inheritance is useful to specify functionality that is common across sub-types
(derived classes)

However, by itself it not sufficient to achieve runtime polymorphism
- so far, all the instances we have created have a known, fixed type at the
  point of use

--

In the following example, the output is already clear since we already know the type of
`tip` and `straight`:

```
Segment::Tip tip (20.0);
Segment::Straight (tip, 30.0);

std::cout << tip.type() << "\n";
std::cout << straight.type() << "\n";
```

--

[Runtime polymorphism](https://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-cpp/) relies on the combination of virtual functions and
references (or pointers)



---

# Runtime polymorphism

[Runtime polymorphism](https://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-cpp/)
is also known as *dynamic polymorphism*. It relies on the concept of [dynamic
binding](https://www.geeksforgeeks.org/dynamic-binding-in-cpp/):
- the decision as to which version of the method to invoke is not made at
  compile time
- it is determined at runtime, based on the *type* of the object provided 

--

This works because we can declare *references* (or iterators or pointers) to
objects of the base class, and have them refer (or point) to objects of a type
derived from that base class:


```
Segment::Tip tip (20.0);

Segment::Base& ref = tip;                  // <= OK since Tip derives from Base

std::cout << ref.tip_position() << "\n";   // <= calls Tip::tip_position()!
```

Here, `ref` refers to an instance of `Segment::Base`
- yet calling `ref.tip_position()` will call the implementation provided by
  `Segment::Tip`!
- ... because the *actual* object referred to by `ref` is of type
  `Segment::Tip`

---

# Runtime polymorphism

[Runtime polymorphism](https://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-cpp/)
is also known as *dynamic polymorphism*. It relies on the concept of [dynamic
binding](https://www.geeksforgeeks.org/dynamic-binding-in-cpp/):
- the decision as to which version of the method to invoke is not made at
  compile time
- it is determined at runtime, based on the *type* of the class 

This works because we can declare *references* (or iterators or pointers) to
objects of the base class, and have them refer (or point) to objects of a type
derived from that base class:


```
Segment::Tip tip (20.0);

*Segment::Base* ptr = &tip;

std::cout << `ptr->tip_position()` << "\n";
```

Here, `ptr` refers to an instance of `Segment::Base`
- yet calling `ptr->tip_position()` will call the implementation provided by
  `Segment::Tip`!
- ... because the *actual* object pointed to by `ptr` is of type
  `Segment::Tip`

.explain-top[
Note that pointers are often used in this context
- they behave similarly to references, though with a slightly different syntax
]

---

# Runtime polymorphism

The fact that this is indeed runtime polymorphism is perhaps better illustrated
with a function:
```
void report (const Segment::Base& seg) 
{
  std::cout << "tip position is " << seg.tip_position() << "\n";
}
```

This function might be defined in one `cpp` file, and used in a totally separate `cpp` file
- when compiling the function, the compiler cannot know which type of class will be supplied
- only that it is of class `Segment::Base` &ndash; or a class *derived from it*

--

The decision as to which version of `tip_position()` to use cannot be made at compile-time
<br>
&rarr; it must be a runtime decision

--

A class derived from the base class should be usable anywhere the base class can be
used!
- this is sometimes referred to as the [Liskov substitution principle](https://dev.to/tkarropoulos/demystifying-the-liskov-substitution-principle-a-guide-for-developers-3gmm)

---

# Runtime polymorphism

This explains why our robot arm implementation relies on the use of
references:
```
namespace Segment {
  class Base {
    ...
    protected:
*     Base& m_next;
      const std::string m_type;
  };
}
```
We could not pass the next segment by copy, since that would only copy over the
parts of the segment that correspond to the base class!
- any interaction with `m_next` would assume it is *literally* of type
  `Segment::Base`
  - no dynamic binding!
- besides, we cannot have an actual instance of the base class, since it is now
  abstract
  - this would produce a compiler error

---
name: lifetime
class: section

# Object lifetime

---

# Object lifetime

Our design relies on:
- creating an instance of the tip segment
- creating an instance of the bend segment, which will hold a reference to
  the tip segment
- creating an instance of the straight segment, which will hold a reference to the
  bend segment
- ...

--

This design can only work if the tip segment is instantiated before the bend
segment, and is not destroyed before the bend segment
- the *lifetime* of the tip must exceed that of the bend segment
- the *lifetime* of the bend segment must exceed that of the straight segment
- ...

Otherwise, there is a risk of one segment attempting to access information that
is no longer valid!

--

.explain-bottom[
Poor handling of object lifetime is a major source of bugs and security
issues!
]

---

# Object lifetime and scope

The strategy we have used provides these guarantees, thanks to the rules around
[construction and
destruction](https://www.geeksforgeeks.org/order-constructor-destructor-call-c/)

```
{
  ...
  Segment::Tip tip (10.0);                       // <= tip is constructed
  Segment::Bend bend3 (tip, 6.0);                // <= bend3 is constructed
  Segment::Straight straight3 (bend3, 15.0);     // <= straight3 is constructed
  ...
}                         // <= straight3, bend3, tip are destroyed, in that order
```
When used as regular variables:
- object are constructed when declared
- destroyed when they go [out of scope](https://www.geeksforgeeks.org/scope-of-variables-in-c/) 
  - normally, this corresponds to the end of the enclosing block or function

--

**Importantly, objects will be destroyed in *reverse construction* order**
- in our case, `tip` was constructed first, so is guaranteed to be destroyed
  last

---
name: destructor
class: section

# The class destructor

---

# The class destructor

The [destructor](https://www.geeksforgeeks.org/destructors-c/) is the counterpart of the [constructor](https://www.geeksforgeeks.org/constructors-c/)
- it is invoked when the object is destroyed
- it can be used to perform any additional clean-up operations that might be required

--

If we don't provide an explicit destructor, the compiler will insert an
implicit default destructor
- just like it did for the constructor!
- the default destructor will invoke the destructor for each data member
  - in the reverse order that they appear in the class
  - this is also the reverse order of construction

--

So far, we have not needed to provide an explicit destructor
- we have been careful to use data members whose own destructors do the right
  thing
  - the `std::string` and `std::vector` destructors will release any memory they might have used
  - the `std::ifstream` destructor will close any open files it might have been
    holding

--

Using well-behaved data members means we can safely rely on the default implicit destructor
- this is by far the preferred strategy!

---

# Inheritance and virtual destructors

When a derived class is destroyed, the destructor for the derived class must
  be run *before* the destructor for the base class
- once again, destruction happens in *reverse construction* order

--

To ensure this, if any derived classes require a destructor, the base class should provide a
  *virtual* destructor
- by declaring it `virtual`, the derived class's destructor can be resolved
    and invoked when required

--

When designing the base class, we will not in general know whether any derived
class will need to provide their own destructor
- we should therefore *always* provide a virtual destructor, even if it is
  empty!

---

# The destructor

```
#include "point.h"
namespace Segment {
  class Base {
    public:
      Base (Base& next_segment, const std::string& type) :
         m_next (next_segment),
         m_type (type) { }

      `~Base();`
  
      const std::string& type () const { return m_type; }
      virtual Point tip_position () const { return { }; }
  
    protected:
      Base& m_next;
      const std::string m_type;
  };
}
```

.explain-bottom[
The destructor is specified as the name of the class, prefix with the
tilde (`~`) symbol
- destructors cannot take any arguments
- they also have no return value
]


---

# The destructor

```
#include "point.h"
namespace Segment {
  class Base {
    public:
      Base (Base& next_segment, const std::string& type) :
         m_next (next_segment),
         m_type (type) { }

      `virtual` ~Base();
  
      const std::string& type () const { return m_type; }
      virtual Point tip_position () const { return { }; }
  
    protected:
      Base& m_next;
      const std::string m_type;
  };
}
```

.explain-bottom[
If it is designed to be inherited, the destructor should be declared `virtual`
]


---

# The destructor

```
#include "point.h"
namespace Segment {
  class Base {
    public:
      Base (Base& next_segment, const std::string& type) :
         m_next (next_segment),
         m_type (type) { }

      virtual ~Base() `{ }`
  
      const std::string& type () const { return m_type; }
      virtual Point tip_position () const { return { }; }
  
    protected:
      Base& m_next;
      const std::string m_type;
  };
}
```

.explain-bottom[
In our case, the destructor does not need to do anything: all of our data
members are well-behaved

<br> &rArr; we can define it as an empty function
]

--

.explain-topright[
Note: destructors should not throw exceptions

<br>
This is to avoid issues that may arise if the destructor is invoked in the
process of handling a previous exception
]

---

# The destructor

```
#include "point.h"
namespace Segment {
  class Base {
    public:
      Base (Base& next_segment, const std::string& type) :
         m_next (next_segment),
         m_type (type) { }

*     virtual ~Base();

      ...
```
**In `segment/base.cpp`:**
```
...

* Base::~Base() { }

...
```

.explain-topright[
Instead of leaving the definition of the destructor inline in the class declaration, 
we can place it in the corresponding `cpp` file.
]

---

# Tracking object lifetimes

We can use constructors and destructors to track the lifetime of our objects

In our case, this can be done by inserting debugging statements:

**In `segment/base.h`:**
```
      Base (Base& next_segment, const std::string& type) :
         m_next (next_segment),
         m_type (type) { 
*          debug::log ("constructing segment of type " + m_type);
         }
```
**In `segment/base.h`:**
```
  Base::~Base() {
*   debug::log ("destroying segment of type " + m_type);
  }
```

---

# Exercise

Add a virtual destructor to the `Segment::Base` class

Add logging calls to the constructor and destructor to track object lifetimes

Verify that objects are destroyed in reverse order from their construction

Verify that the lifetime of the tip segment exceeds that of the next segment,
etc. 

---
class: section

# Finishing off <br>the robot arm project

---

# Finishing off the robot arm project

We have code to setup the robot arm, and we can use it to report the tip
position

The next steps are to:
1. load the parameter file
1. set the various angles to their corresponding values in the parameter file
  for each time frame
1. iterate over the time frames, compute the trajectory, and display on the
  terminal
1. compute the speed of the tip and display this as a function of time
1. compute the acceleration of the tip and display this alongside the speed
1. compute the maximum speed and acceleration and check whether they are within
  the specified safety margins

--

We have covered *almost* all the material necessary to implement the above
- let's look at step 1 in more detail

---
name: stringstream

# Reading text line-by-line

The parameter file consists of a some number of parameters per time point, all
on the same line, with each line corresponding to a different time point
```
 0.00000000e+00 0.00000000e+00 0.00000000e+00 0.00000000e+00 0.00000000e+00 0.00000000e+00
 1.20830487e-02 1.20830487e-02 1.20830487e-02 1.20830487e-02 0.00000000e+00 1.20830487e-02
 2.41660973e-02 2.41660973e-02 2.41660973e-02 2.41660973e-02 0.00000000e+00 2.41660973e-02
 3.62491460e-02 3.62491460e-02 3.62491460e-02 3.62491460e-02 0.00000000e+00 3.62491460e-02
 4.83321947e-02 4.83321947e-02 4.83321947e-02 4.83321947e-02 0.00000000e+00 4.83321947e-02
...
```

--

We could load all the parameters as one long vector of values, then 
to re-arrange the data into sets of 6 parameters
- or we could read the data 6 parameters at a time

--

Both approaches rely on *a priori* knowledge that there are 6 values per time point!
- we cannot handle files that may have different numbers of parameters
- we cannot detect errors in the file (maybe some lines have too many
  or too few parameters)

---

# Reading text line-by-line


Ideally, we would:
- read one line at a time
- read each value on that line into a parameter vector
- check that the size of that vector is as expected, and/or matches the size of
  the previous lines in the file

--

We can read text one line at a time using the [std::getline()
method](https://www.geeksforgeeks.org/getline-string-c/):
```
std::ifstream infile (filename); 
...
std::string line;
while (`std::getline (infile, line)`) {
  // process that line:
  ... 
}
```

--

But we then need to read the values from that line
- how can we do that?

---

# Treating a *string* as a *stream*

We can use the [std::stringstream](https://www.geeksforgeeks.org/stringstream-c-applications/) class to treat a string as if it were a stream
- It's like writing your string into a file, and then using a stream to read
  from that file
- This allows us to use the same interface that we've been using to read from
  streams, but this time reading from our string

--

As with file streams, there are 3 variants:
- `std::stringstream` for both read and write access
- `std::istringstream` if we only need to *read* from the string
- `std::ostringstream` if we only need to *write* to the string

---

# Illustration of string stream

```
// The std::stringstream classes are declared in the <sstream> header:
#include <sstream>

...
// the string we want to read from:
std::string line;
...
// maybe read line using std::getline(), etc.
...

// set up an input string stream, initialised with 
// the string we want to read from:
std::istringstream sstream (line);

// we can now read from our string stream using the same syntax as before!
// for example:
std::vector<double> param;
while (sstream >> val)
  param.push_back (val);
```

---

# Exercises

We have now covered all the material necessary to finish the project!

Modify your code to implement the remaining steps:
1. load the parameter file (including all relevant error checking)
1. set the various angles to their corresponding values in the parameter file
  for each time frame
1. iterate over the time frames, compute the trajectory, and display on the
  terminal
1. compute the speed of the tip and display this as a function of time
1. compute the acceleration of the tip and display this alongside the speed
1. compute the maximum speed and acceleration and check whether they are within
  the specified safety margins

