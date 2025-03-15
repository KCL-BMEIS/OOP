---
layout: presentation
title: "Week 7, session 1: OOP design and principles"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 7, session 1
## OOP design and principles


---

# Exercises

We have now covered all the material necessary to finish the [robot arm
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/robot_arm/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/robot_solution/projects/robot_arm/solution)

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


.explain-bottom[
Refer to [the online
solution](https://github.com/KCL-BMEIS/OOP/tree/robot_solution/projects/robot_arm/solution) for the final design
]

---
name: OOP_principles
class: section

# OOP core principles

---

# OOP core principles

Object-Oriented Programming is based on [4 core
principles](https://khalilstemmler.com/articles/object-oriented/programming/4-principles/):

- abstraction
- encapsulation
- inheritance
- polymorphism

--

We have already been using all 4 of these principles throughout the course

&rArr; it's time to formalise what they mean

---
name: abstraction
class: section

# Abstraction

---

# Abstraction

Abstraction aims to provide a simplified interface to otherwise complex
systems. 
- this allows us to focus on how to *use* these abstractions to solve problems
- without worrying about the details of *how* these abstractions are implemented

--
 
We use abstractions all the time:
- cars provides a uniform and familiar interface to the driver
  - regardless of the type of engine, gearbox, etc. 
--
- TVs can be operated by remote control
  - without the need to understand whether this is a plasma or LCD screen,
    whether the signal comes over the air, via cable, or the internet, etc. 
--
- a coffee machine can be operated by providing water and coffee beans, then pushing the right button
  - without needing to worry about the temperature and pressure of the water,
    the coarseness of the grind, etc.

--

These are all examples of *abstraction*

---

# Abstraction in OOP

Abstraction can be achieved in C++ by providing *intuitive interfaces* to
potentially complex objects

The most common manifestation is the use of classes with methods

--

Example, the `Image` class that we set up for the fMRI project:
- this provides an intuitive way to access individual pixels by providing their
  coordinates
- even though the pixels are stored in a one-dimensional `std::vector`
  internally

--

The various segments in the robot arm projects also provide a level of
abstraction
- the `tip_position()` method provides the position without the need to worry
  about how it was computed

--

But functions can also provide abstractions:
- we don't need to worry about how to load a PGM file if we know how to use the
  `load_pgm()` function

---
name: encapsulation
class: section

# Encapsulation

---

# Encapsulation

Encapsulation aims to maintain the integrity of a system, by protecting its
internal components and preventing direct manipulation other than through the
interface provided
- it is closely related to abstraction, but more focussed on maintaining integrity
- this allows us to use complex objects without worrying about causing
  accidental damage

--

Again, there are plenty of everyday examples of encapsulation:
- many electrical devices use non-standard, sometimes hidden screws to prevent
  users from trying to 'fix' their device
- modern smartphones are locked down to prevent malicious or accidental damage
  to the operating system
- trying to open up your laptop will most likely void your warranty...

--

All of these are examples of encapsulation: 
- they aim to ensure the integrity of an object or system

---

# Encapsulation in OOP

Encapsulation can be achieved in C++ by protecting the internal *state* of
objects

The most common way is to use classes, storing the state of the object as
private or protected attributes, along with suitably designed public methods to
interact with these attributes safely
- these methods need to provide both the abstraction and ensure the integrity
  of the data in the class

--

For example, consider our Image class:
- its state consists of the image dimensions (integers) and the vector of
  intensities
- what if we wanted to resize an existing image? 
- could we just set the image dimensions to the desired size?

--

&rArr; no, since changing the image dimensions changes the number of pixels
- the vector of intensities would need to be resized to match!
- what if we wanted to preserve any intensities already present in the image?

--

The current implementation *protects* these attributes, ensuring they cannot be
modified other than through the methods provided.

---
name: inheritance
class: section

# Inheritance

---

# Inheritance

Inheritance allows one class to derive from and extent another class, allowing
strongly related objects to share common attributes and methods
- it allows for code re-use, simplifying the implementation and maintenance of
  shared functionality
- it is used to implement multiple sub-types that share a common set of
  features

--

Examples of inheritance include:
- cars that share a common chassis and engine, but can be customised with
  different bodywork, furnishings, and extras
  - e.g. Volkswagen Golf, Audi A3, and Skoda Octavia
--
- laptops are often designed as a series, with a range of models sharing common
  attributes (chassis, screen, battery, etc), but different CPUs, memory,
  storage, etc. 

--

These are examples of making use of a common base, which can then be extended
in different ways for specific products
- this means developpers can optimise a single shared base, and spend
  more time on the features specific to each product
 
---

# Inheritance in OOP

Inheritance in achieved in OOP by allowing a *base class* to be inherited by
one or more *derived classes*

- The data members of the base class are also present in any derived class
  - The derived class *is* a realisation of the base class

- The methods of the base class are also available to the derived class and
  external code
  - depending on the level of access provided and mode of inheritance

- Derived classes can *extend* the base class by adding more data members and
  providing additional functionality

- Derived class can also provide their own implementation of some of the
  methods of the base class 
  - this is the basis of [runtime polymorphism](https://www.geeksforgeeks.org/cpp-polymorphism/)

--

We have seen this in action in our robot arm project


---
name: polymorphism
class: section

# Polymorphism

---

# Polymorphism

The word comes from Greek, and means 'many forms'

[Polymorphism](https://www.geeksforgeeks.org/cpp-polymorphism/) refers to the
ability to define different objects that provide the *same interface*
- it allows us to focus on *using* the object, rather than worrying about *how*
  this is implemented

--

There are many day-to-day examples of polymorphism:

- cars all have a steering wheel and pedals
  - even though what these do may be implemented completely differently for
    different types of car
--
- bank accounts all have one or more account holders, balance, history of
  previous transactions, etc. 
  - but come in different variants: current, savings, investment, mortgage, ...
--
- many numerical problems can be represented as a *cost function*, which
  computes a *cost* for a given set of input parameters
  - solving these problems can be done by optimisation: finding the set of
    parameters that minimises the output cost function value
  - ... even though the internal calculations of the cost function may be
    completely different, and will not be known to the optimisation algorithm

--

These all involve objects with a known, common interface, but different implementations



---

# Polymorphism in OOP

C++ supports different types of polymorphism:

## Compile-time or *static* polymorphism

In this form, a common interface is defined in the (human-readable) C++ code, and the compiler
deduces which implementation to use when generating the binary code

## Run-time or *dynamic* polymorphism

In this form, a common interface is defined in the C++ code, and *also* 
in the generated binary code. The compiler implements the necessary machinery
to ensure that the program can work with any object that provides the expected
interface, but cannot make assumptions regarding which specific subtype might
be provided at any point in time while running.

The decision as to which specific implementation is to be used is therefore
made while the program is running: dynamically, at run-time.

---
name: compiletime_polymorphism

# Compile-time polymorphism

C++ provides two main ways to achieve compile-time polymorphism:

## [Function overloading](https://www.geeksforgeeks.org/function-overloading-c/)

We can provide multiple functions with the same name, but different arguments
- the compiler will then use the appropriate version by [overload
  resolution](https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/)

```
void display (int x)                { std::cout << x << "\n"; }
void display (double d)             { std::cout << d << "\n"; }
void display (const std::string& s) { std::cout << s << "\n"; }

...
double val = 10.2;
display (val);    // <= the compiler can deduce which version to invoke here

...
std::string mesg = "not good!";
display (mesg);   // <= the compiler can deduce which different version to use here
```

---

# Compile-time polymorphism

C++ provides two main ways to achieve compile-time polymorphism:

## [Template functions](https://www.learncpp.com/cpp-tutorial/function-templates/)

We can specify a function as taking one or more *generic* argument types
- When encountered in the code, the compiler can then substitute the type
  provided to generate the code for the function

```
template <typename X>
  void display (const X& x)     { std::cout << x << "\n"; }

...
double val = 10.2;
display (val);    // <= the compiler can substitute 'double' instead of 'X' here

...
std::string mesg = "not good!";
display (mesg);   // <= the compiler can substitute 'std::string' instead of 'X' here
```

---

# Compile-time polymorphism

C++ provides two main ways to achieve compile-time polymorphism:

## [Template classes](https://www.learncpp.com/cpp-tutorial/template-classes/)

We can also create template classes in this way:

```
template <typename X> 
  class Complex {
    public: 
      void display () const { std::cout << "(" << real << "," << imag << ")\n";
    ...
    private:
      X real, imag;
  };


Complex<int>    ci { 3, 2 };
Complex<double> cd { 1.0, 0.5 };
```

---
name: runtime_polymorphism

# Run-time polymorphism

In C++, runtime polymorphism is typically achieved using [inheritance and
virtual functions](https://www.learncpp.com/cpp-tutorial/virtual-functions/).

--

We define a *base class* to specify the expected *interface*
- we specify which methods (behaviours) can be
  [overridden](https://www.geeksforgeeks.org/function-overriding-in-cpp/) using
  the `virtual` keyword

--

We can then define *derived classes* that
[inherit](https://www.geeksforgeeks.org/inheritance-in-c/) from the *base class*
- they will provide the interface specified in the base class
- but can also extend it with additional methods & behaviours specific to their
  role
- they can also
  [override](https://www.geeksforgeeks.org/function-overriding-in-cpp/) any
  methods marked `virtual` and provide their own *implementation*
  - note: methods denoted as [pure
    virtual](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
    in the base class *must* be [overridden](https://www.geeksforgeeks.org/function-overriding-in-cpp/) 
    in the derived class

--

Which implementation to invoke will be determined at runtime, at the point of
use, based on the specific *type* of the object being handled at that time
- The compiler knows all derived classes provide the interface
  specified in the base class, so can generate code to process any object of
  type base, and that code can then also be used with any derived types 
--
- For this to work, we have to use references, pointers or iterators that are
  declared to refer to objects of base class types, but actually refer to *instances* of
  derived type

---

# Run-time polymorphism

For example, let's design a class for a generic *problem*:

```
class ProblemBase {
  public:
    virtual int size () const = 0;
    virtual double eval (const std::vector<double>& x) const = 0;
};
```

---

# Run-time polymorphism

We can then provide a derived class to exponential fitting:

```
class Exponential : public ProblemBase {
  public:
    Exponential (const std::vector<double>& measurements, 
                 const std::vector<double>& timepoints) :
       m (measurements), t (timepoints) { } 
    int size () const override { return 2; }
    double eval (const std::vector<double>& x) const override {
      double cost = 0.0;
      for (int n = 0; n < m.size(); n++) {
        double diff = m[n] - x[0] * std::exp (x[1]*t[n]);
        cost += diff*diff;
      }
      return cost;
    }
    double eval (const std::vector<double>& x) const override {
  private: 
    std::vector<double> m, t;
};
```

---

# Run-time polymorphism

We can then provide a derived class to exponential fitting:

```
class Exponential : public ProblemBase {
  public:
*   Exponential (const std::vector<double>& measurements, 
*                const std::vector<double>& timepoints) :
*      m (measurements), t (timepoints) { } 
    int size () const override { return 2; }
    double eval (const std::vector<double>& x) const override {
      double cost = 0.0;
      for (int n = 0; n < m.size(); n++) {
        double diff = m[n] - x[0] * std::exp (x[1]*t[n]);
        cost += diff*diff;
      }
      return cost;
    }
    double eval (const std::vector<double>& x) const override {
  private: 
*   std::vector<double> m, t;
};
```

.explain-bottomright[
We can provide the measurements and their corresponding time points in the
constructor
]

---

# Run-time polymorphism

We can then provide a derived class to exponential fitting:

```
class Exponential : public ProblemBase {
  public:
    Exponential (const std::vector<double>& measurements, 
                 const std::vector<double>& timepoints) :
       m (measurements), t (timepoints) { } 
    int size () const override { return 2; }
*   double eval (const std::vector<double>& x) const override {
*     double cost = 0.0;
*     for (int n = 0; n < m.size(); n++) {
*       double diff = m[n] - x[0] * std::exp (x[1]*t[n]);
*       cost += diff*diff;
*     }
*     return cost;
*   }
*   double eval (const std::vector<double>& x) const override {
  private: 
    std::vector<double> m, t;
};
```

.explain-topright[
... and then evaluates the goodness of fit:
$$
\phi = \sum_n (x_0 \exp (x_1 t_n) - m_n)^2
$$
In other words, the sum of squares difference between measurements
*m<sub>n</sub>* at
specified times *t<sub>n</sub>* and corresponding predictions from exponential model
parameterised by amplitude *x*<sub>0</sub> and exponent *x*<sub>1</sub>
]

---

# Run-time polymorphism

We can then write a generic solver for any problem defined in this way:

```
std::vector<double> solve (const ProblemBase& problem);
```
which could use any suitable approach to identify the optimal parameters and
return the solution vector.


---
name: relationships
class: section

# Relationships between classes

---
name: association

# Association

---
name: composition

# Composition 

---
name: aggregation

# Aggregation

---
name: inheritance_relationship

# Inheritance

---
name: relationship_examples

# Examples of relationships

---
name: design_principles
class: section

# Design principles

---
name: solid

# The SOLID principles

---
name: composition_over_inheritance

# Favor Composition over Inheritance

---
name: design_dry

# Don't repeat yourself

---
name: yagni

# You ain't gonna need it!



