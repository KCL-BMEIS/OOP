---
layout: presentation
title: "Week 6, session 1: robot arm project, inheritance"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 6, session 1
## next project: robot arm project<br>inheritance

---

# Our next project: fMRI analysis

This week, we start off on a new project: a simple system to control a modular
robot arm
- Have a look at the [assignment instructions](https://github.com/KCL-BMEIS/OOP/blob/main/projects/robot_arm/assignment.md)

You will find the most up to date version of the project in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/robot_solution/projects/robot_arm/solution)

<br>
Let's take a look at the assignment to figure out what needs to be done

--

.explain-bottom[
You will find some code to start from in the solution folder

<br>
&rArr; [Make sure your code is up to date
now!](https://github.com/KCL-BMEIS/OOP/blob/main/projects/code_updater.md)
]

---

# Designing the project

The problem calls for defining:
- a *base class* for a generic 'segment'
- *derived classes* for each segment sub-type

--

This is exactly the kind of problem that Object-Oriented Programming is
designed to address

This kind of design can be implemented through
[inheritance](https://www.learncpp.com/cpp-tutorial/introduction-to-inheritance/)
- this is one of the four core features of OOP

---

# Inheritance

Inheritance refers to the ability to define a *derived* class that extends a *base* class
- the derived class *inherits* all the properties of the base class
- the derived class can provide its own implementation of some methods
- the derived class can store additional data members in addition to those
  inherited from its base class

--

This is used to address a broad range of problems, where:
- there is generic type of object, with defined interactions (the base class)
- there are one or more syb-types of this object, with their own implementation
  of these interactions (derived classes)
  - these can also provide additional functionality specific to the derived
    class

---
layout: true

# Example of inheritance

There are many examples of inheritance relationships

Consider a computer mouse (pointing device):
.center[
![:scale 11%](images/wired_mouse.png) ![:scale 10%](images/wireless_mouse.png) &ensp; ![:scale 8%](images/touchpad.png) &emsp; ![:scale 10%](images/touchscreen.png) &emsp; ![:scale 10%](images/tablet.png)
]

---

<br>
- there are different types of pointing devices:
  - connected via PS/2, USB, bluetooth, ...
  - with/without scroll wheel, middle button, extra buttons, ...
  - sometimes users use a touchscreen or tablet
- the software on the computer shouldn't need to know what *type* of pointing
  device is connected
  - it just needs to know how to *interact* with these devices in a consistent
    manner

---

We can design a *base class* to represent a pointing device
- this provide the basic information and the *interface* required for *any*
  pointing device

We can then create *derived classes* that *inherit* from this base class
- each derived class can provide specific *implementations* of the interface

The software application can then be provided with an instance of the
appropriate derived class
- the application only needs to know how to interact with the base class


---
layout: false

# How inheritance applies to our problem

For our robot arm project:
- we can set up a base class to represent (and interact with) a *segment*
- we can set up a derived class for each type of segment that inherits the base
  class

--

The task requires us to track the position of the surgical tip
- each segment should be able to report on the position of the tip *relative to
  its base connector*
- ... given the position of the tip *relative to the previous segment's base
  connector*

---

# Tracking the tip position &ndash; tip

tip position relative to base:
$$
\begin{bmatrix}
0 \\\\
0 \\\\
\textrm{length}
\end{bmatrix}
$$
.center[
![:scale 8%](images/robot_tip.png)
]

---

# Tracking the tip position &ndash; bend

tip position relative to base:
$$
\begin{bmatrix}
0 \\\\
0 \\\\
\textrm{length}/2
\end{bmatrix} + \begin{bmatrix}
\cos(\textrm{angle}) & 0 & \sin(\textrm{angle}) \\\\
0 & 0 & 0 \\\\
-\sin(\textrm{angle}) & 0 & \cos(\textrm{angle}) \\\\
\end{bmatrix} \times \left( \begin{bmatrix}
0 \\\\
0 \\\\
\textrm{length}/2
\end{bmatrix} + \textrm{previous tip position}
\right)
$$

.center[
![:scale 27%](images/robot_tip2.png)
]

---

# Tracking the tip position &ndash; bend

tip position relative to base:
$$
\begin{bmatrix}
0 \\\\
0 \\\\
\textrm{length}
\end{bmatrix} + \textrm{previous tip position}
$$

.center[
![:scale 27%](images/robot_tip3.png)
]

---

# Designing the Segment base class

Each segment needs functionality to:
- report its type
- compute and report the position of the tip relative to its own base connector
- hold a *reference* to the next segment

--

```
Segment (rotate)
├── type
└── next_segment → Segment (straight)
                     ├── type
                     └── next_segment → Segment (bend)
                                          ├── type
                                          └── next_segment → Segment (tip)
                                                               ├── type
                                                               └── next_segment → `?`
```
--

Need a way to terminate the chain
- not too important since tip segment has no need to refer to next segment

---

## Designing the Segment base class

```
namespace Segment {
  class Base {











  };
}
```
We start by defining a class called `Segment`, as we normally would
- since we anticipate many different types of segments, it makes sense to set
  them up within their own `Segment` namespace

---

## Designing the Segment base class

```
namespace Segment {
  class Base {








    private:
      const std::string m_type;
      Segment& m_next_segment;
  };
}
```

We only need to 2 data members: 
- a string to hold the type
  - this will not need to be modified after construction &rArr; declare it `const`
--
- a *reference* to the next segment
  - *note:* this cannot be a *copy* &ndash; we will see why later

---

## Designing the Segment base class

```
namespace Segment {
  class Base {
    public:
      Segment (const std::string& type, Segment& next_segment) :
         m_type (type),
         m_segment (segment) { }
  
  
  
  
    private:
      const std::string m_type;
      Segment& m_next_segment;
  };
}
```

Both data members are *immutable*:
- [references](https://www.geeksforgeeks.org/references-in-cpp/) cannot be made to refer to a different variable after construction
- the `m_type` member is `const`

&rArr; they must both be initialised in the constructor, using the [member initialiser list](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/)


---

## Designing the Segment base class

```
namespace Segment {
  class Base {
    public:
      Segment (const std::string& type, Segment& next_segment) :
         m_type (type),
         m_segment (segment) { }
  
      const std::string& type () const { return m_type; }
  
  
    private:
      const std::string m_type;
      Segment& m_next_segment;
  };
}
```

Add a getter / accessor method for the type
- technically, we could make the `m_type` member public, since it is `const`
  anyway
  - there is no risk of it being modified unexpectedly
  - but it is considered good practice to provide a getter method

---

## Designing the Segment base class

```
namespace Segment {
  class Base {
    public:
      Segment (const std::string& type, Segment& next_segment) :
         m_type (type),
         m_segment (segment) { }
  
      const std::string& type () const { return m_type; }
      std::array<double,3> tip_position () const;
  
    private:
      const std::string m_type;
      Segment& m_next_segment;
  };
}
```

We need a method to compute and report the position of the tip relative to the
base of the current segment
- the *implementation* needs to be type-dependent
- but the *interface* needs to be well-defined and identical for all segment
  types
  - *interface* in this context means the method signature / declaration

---

## Designing the Segment base class

```
namespace Segment {
  class Base {
    public:
      Segment (const std::string& type, Segment& next_segment) :
         m_type (type),
         m_segment (segment) { }
  
      const std::string& type () const { return m_type; }
      `virtual` std::array<double,3> tip_position () const;
  
    private:
      const std::string m_type;
      Segment& m_next_segment;
  };
}
```

If the implementation of a method depends on the sub-type, it must be declared
[virtual](https://www.geeksforgeeks.org/virtual-function-cpp/)
- this means that *derived* classes are allowed to *override* the
  implementation
- this is what allows [runtime polymorphism](https://www.geeksforgeeks.org/cpp-polymorphism/) (more on that later)

---

## Designing the Segment base class

```
namespace Segment {
  class Base {
    public:
      Segment (const std::string& type, Segment& next_segment) :
         m_type (type),
         m_segment (segment) { }
  
      const std::string& type () const { return m_type; }
      virtual std::array<double,3> tip_position () const { `return { };` }
  
    private:
      const std::string m_type;
      Segment& m_next_segment;
  };
}
```

For now, we can provide a default implementation for the `tip_position()`
method
- this just returns a default-initialised `std::array` using a braced initialiser list
- technically, there is no way to provide a reasonable implementation for the base
  class
- we will see how to deal with this later

---

# Writing our first derived class

We now have a functional base class
- but we can't do anything with it yet
- it is designed to be derived, and the derived classes will provide meaningful
  implementations

--


Let's start with the simplest one: the straight segment


---

## Designing the Straight segment class

```
namespace Segment {
  class Straight `:` `public Base` { 











  };
}
```
We define our `Straight` class as a regular class, with one key difference:
- we specify that it inherits from `Base` using the syntax shown
- `public` here means that public methods of the base class will also be
  public in the derived class
  - it is the most common mode of inheritance (`private` and `protected` are
    also possible, but rarely used)

---

## Designing the Straight segment class

```
namespace Segment {
  class Straight : public Base { 









*   private:
*     const double m_length;
  };
}
```

Note that the `Straight` class only not needs one additional data member: its
length
- it will already have the `m_type` and `m_next_segment` data members from the base class!


---

## Designing the Straight segment class

```
namespace Segment {
  class Straight : public Base { 
*   Straight (const Base& next, double length);
 







    private:
      const double m_length;
  };
}
```

The constructor for the Straight segment needs two pieces of information: 
- a reference to the next segment
- its own length


---

## Designing the Straight segment class

```
namespace Segment {
  class Straight : public Base { 
    Straight (const Base& next, double length) :
*     Base (next, "straight"),
      m_length (length) { }






    private:
      const double m_length;
  };
}
```

Note that the constructor of the derived class must invoke the constructor for
its base class first
- if not explicitly stated, the base class default constructor will
  implicitly be invoked (if one exists)
- this ensures the base class is fully initialised in case the derived class depends on any of its functionality 
- this must be done within the [member initialiser list](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/)

---

## Designing the Straight segment class

```
namespace Segment {
  class Straight : public Base { 
    Straight (const Base& next, double length) :
      Base (next, "straight"),
      m_length (length) { }

*   std::array<double,3> tip_position () const {
      auto p = m_next.tip_position();
      return { p[0], p[1], m_length+p[2] };
    }

    private:
      const double m_length;
  };
}
```

Finally, we can provide our implementation for the *virtual* `tip_position()`
method
- its declaration must match that from the base class exactly


---

## Designing the Straight segment class

```
namespace Segment {
  class Straight : public Base { 
    Straight (const Base& next, double length) :
      Base (next, "straight"),
      m_length (length) { }

    std::array<double,3> tip_position () const {
*     auto p = m_next.tip_position();
*     return { p[0], p[1], m_length+p[2] };
    }

    private:
      const double m_length;
  };
}
```

For the `Straight` segment, the implementation is relatively straightforward:
- we retrieve the tip position from the next segment
  - remember we've inherited the `m_next_segment` member from the `Base` class!
- add its length to the *z*-component
- and return a `std::array` with that position


---

## Designing the Straight segment class

```
namespace Segment {
  class Straight : public Base { 
    Straight (const Base& next, double length) :
      Base (next, "straight"),
      m_length (length) { }

    std::array<double,3> tip_position () const `override` {
      auto p = m_next.tip_position();
      return { p[0], p[1], m_length+p[2] };
    }

    private:
      const double m_length;
  };
}
```

When overriding a virtual method, it is good practice to add the `override`
keyword
- this ensures that a matching virtual method really does exist in the base class
- this alerts users of our class that we intend this method to override the
  base class implementation
- this helps to avoid a number of subtle errors 


---

# The next derived class: the tip

We now have:
- a Base class for our segments
- one derived class for segments of 'straight' type

--

But we can't use any of this code yet:
- we need an instance of the next segment to construct a `Straight` segment
- but the only type of segment we can currently instantiate is a `Straight`
  segment!

--

We need at least one derived class that can be instantiated *without* a next
segment!

&rArr; the tip segment


---

## The next derived class: the tip

```
namespace Segment {
  class Tip : public Base {









    private:
      const double m_length;
  };
}
```

As for the `Straight` segment, we need only one additional data member: the tip
length


---

## The next derived class: the tip

```
namespace Segment {
  class Tip : public Base {
    public:
      Tip (double length) :
        Base (*this, "tip"),
        m_length (length) { }

      std::array<double,3> Tip::tip_position () const override {
        return { 0.0, 0.0, m_length };
      }

    private:
      const double m_length;
  };
}
```


