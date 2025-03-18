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

--

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

--

<br>
We can then write a function to minimise any problem defined in this way:

```
std::vector<double> minimise (const ProblemBase& problem);
```
which could use some suitable [optimisation
algorithm](https://en.wikipedia.org/wiki/Category:Optimization_algorithms_and_methods)
to identify and return the optimal parameter vector.


---

# Run-time polymorphism

.columns[
.col[
One such problem might be to fit an exponential:
$$
S = x_0 \exp (x_1 t)
$$
to a set of measurements of acquired at various times.
]
.col[
![:scale 100%](images/exponential_fitting.png)
]
]

The task is to identify the parameters of the curve that minimise the sum of
squared differences between the fitted curve and the measurements. 

---

# Run-time polymorphism

We can then represent our exponential fitting problem by deriving from `ProblemBase`:

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
        double diff = x[0] * std::exp (x[1]*t[n]) - m[n];
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

We can then represent our exponential fitting problem by deriving from `ProblemBase`:

```
class Exponential : public ProblemBase {
  public:
    Exponential (const std::vector<double>& measurements, 
                 const std::vector<double>& timepoints) :
       m (measurements), t (timepoints) { } 
*   int size () const override { return 2; }
    double eval (const std::vector<double>& x) const override {
      double cost = 0.0;
      for (int n = 0; n < m.size(); n++) {
        double diff = x[0] * std::exp (x[1]*t[n]) - m[n];
        cost += diff*diff;
      }
      return cost;
    }
    double eval (const std::vector<double>& x) const override {
  private: 
    std::vector<double> m, t;
};
```

.explain-bottomright[
The problem is characterised by 2 parameters: the amplitude and decay rate
$$
S = x_0 \exp (x_1 t)
$$
]

---

# Run-time polymorphism

We can then represent our exponential fitting problem by deriving from `ProblemBase`:

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
*       double diff = x[0] * std::exp (x[1]*t[n]) - m[n];
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
The `eval()` call evaluates the goodness of fit:
$$
\phi = \sum_n (x_0 \exp (x_1 t_n) - m_n)^2
$$
In other words, the sum of squares difference between measurements
*m<sub>n</sub>* at
specified times *t<sub>n</sub>* and corresponding predictions from the exponential model
parameterised by amplitude *x*<sub>0</sub> and exponent *x*<sub>1</sub>
]

---

# Run-time polymorphism

We can then represent our exponential fitting problem by deriving from `ProblemBase`:

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
        double diff = x[0] * std::exp (x[1]*t[n]) - m[n];
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

Similarly, we could use this approach to solve any other problem of interest that can be
expressed as a cost that depends on a vector of parameters.

- the placement of sensors to optimise sensitivity to a signal of interest
- optimising the parameters of a machine learning algorithm
- finding the transformation that best aligns two images
- ...

--

[Runtime polymorphism](https://www.geeksforgeeks.org/cpp-polymorphism/) is
useful when the system needs to interact with a generic type of object, but the
specific type cannot be known at runtime, or may change at runtime.
- the base class can be used to specify the *interface*
- derived classes can provide specific implementations suitable for each sub-type


---
name: relationships
class: section

# Relationships between classes

---

# Relationships between classes

A fundamental aspect of OOP design is to:
- break up a problem into distinct *objects*
- identify the *relationships* between these objects

--

When designing an OOP solution, the first challenge is to identify which
aspects of the problem should be represented as distinct classes
- the general rule is that each class should have a clear, distinct role or *responsability*
  - this is also known as the [single responsability
    principle](https://www.geeksforgeeks.org/single-responsibility-in-solid-design-principle/)

--

The next challenge is to specify how these classes and objects relate to each other. There
are different types of relationships in OOP, including notably:
- dependency
- association
  - aggregation
  - composition
- inheritance


---
name: dependency

# Dependency

Dependency is the most 'loose' form of relationship

Objects may 'know' about each other, but are otherwise independent.
- it may be used to represent "uses-a" relationships

.center[ ![:scale 50%](images/dependency.png) ]

--

For example, a class to load and store a matrix of data would depend on
the `std::string` and the `std::ifstream` classes
- `std::string` is used to provide the filename
- `std::ifstream` might be used internally in the class' `load()` method 

--

More generally, classes `A` & `B` can be said to be in a *dependency*
relationship if class `A` is only used in class `B`'s method(s) (whether as
arguments or local variables), but not in a more persistent manner.

---
name: aggregation

# Association: aggregation

Aggregation implies a weak association between two classes

This applies in situations where one class holds a reference to another, but
does not otherwise 'own' it
- it is said to represent "has-a" relationships

.center[ ![:scale 50%](images/aggregation.png) ]

--

For example, a student has-a university, and vice-versa, but neither 'own' each
other
- this can be considered from the point of view of *lifetime*: closing down the
  university will not automatically terminate the student (or vice-versa)
- it is also possible for the student to drop out of university, or change to a
  different university

---

# Association: aggregation

More examples of aggregation:

- `Company` has-a `Employee` (in fact, has-many `Employee`s) 
  - `Employee`s exist even if `Company` closes
  - An `Employee` can be employed in multiple `Company`s

--

- `Airplane` has-a `Passenger` (again, has-many `Passenger`s)
  - Decommissioning `Airplane` does not imply `Passenger`s need to be terminated
  - Here, `Passenger` can only be on one `Airplane` at a time

--

- `Computer` has-a `Keyboard`
  - `Computer` can exist without a `keyboard`
  - `Keyboard` can be removed, replaced, etc.

--

<br>
Aggregation can be unidirectional or bidirectional
- a `Company` has-a `Employee`, but it's also possible that an `Employee` has-a `Company`
- a `Computer` has-a `Keyboard`, but there is no need to say that
  the `Keyboard` has-a `Computer`...

---
name: composition

# Association: composition 

Composition is implies a stronger association between two classes

This applies in situtations where one class is made up of other objects,
including the other class under consideration
- it can be said to represent "is-made-of" relationships

.center[ ![:scale 50%](images/composition.png) ]

--

For example, a car is-made-of a chassis, engine, 4 wheels, etc. 
- composition implies *ownership*: one object *contains* and manages the other
- it also implies the *lifetime* of the *contained* object is tied to that of
  the *container* object

--

Composition can only be unidirectional
- the *container* object is responsible for the *contained* object
- the *contained* object will (typically) have no knowledge of or reference to its *container*

---

# Association: composition

More examples of composition:

- a `Building` is-made-of (multiple) `Room`s
  - `Room` cannot exist outside of a `Building`

--

- a `Book` is-made-of (many) `Page`s 
  - Here, relationship is one of lifetime: if `Book` is destroyed, so are its `Page`s

--


- `Car` is-made-of `Motor` (amongst other parts!)
  - this is a more contentious example, depending on context
  - `Motor` can be taken out of `Car`, replaced, etc
  - But `Car` is not complete without `Motor`, and `Motor` is (usually!) destroyed if `Car` is destroyed
  - &rArr; this reflects the intention of the designer: a `Car` shall be made-of a `Motor`

---
name: inheritance_relationship

# Inheritance

Inheritance (also known as *generalisation*) is the strongest form of relationship 

This applies in situtations where one class is a specialisation of another,
more general class
- it can be said to represent "is-a" relationships

.center[ ![:scale 50%](images/vertical-hierarchy-light.png) ]

---

# Inheritance

Example of inheritance include:

- a computer screen is-a general type of display, and the computer
   will need to know how to interact with it in a generic way
  - but actual computer screens may use different technologies (LCD, LED, plasma,
    CRT, ...)
  - or use different connectors (VGA, DisplayPort, HDMI, Thunderbolt, ...)
  - and provide different native resolutions and refresh rates, etc. 

--

- `Dog` is-a `Animal`
  - So is `Cat`, `Mouse`, `Pangolin`, ...

--

- `4WheelDrive` is-a `Car`
  - So is `FrontWheelDrive`, `RearWheelDrive`, `Formula1`, ...

--

- `BluetoothMouse` is-a `Mouse`
  - So is `USBMouse`, `PS/2Mouse`, `TouchPad`, `TouchScreen`, ...

---

# Inheritance

Inheritance implies that derived classes are *full instances* of the class they
inherit from
- it is a stronger relationship than ownership
- the *lifetime* of the *base* object is obviously tied to that of the *derived* object
  - the 'base' object is a *part* of the derived object
- inheritance can only be unidirectional

--

Derived classes *extend* the functionality of the base class

--

The Base class will have no 'knowledge' of or dependence on the derived classes

--

Object of a derived type can be used anywhere the Base type is expected

--

... but objects of the Base type cannot be used where a specific derived type is
expected

---
name: oop_design_examples
class: section

# Examples of OOP design

---

# OOP Design: class relationships

Design in Object-Oriented Programming involves:
- identifying relevant *classes* to represent the various components
- identifying *relationships* between these classes / objects

--

The first step in the design process is to take look at the project brief
(or assignment instructions) and map out how to express it in terms of classes
and relationships

--

Let's look at a few illustrative examples

---

# Number representations

We are designing a system to handle mathematics on numbers provided in
different forms: real, rational, and complex

- real numbers can be simply represented as regular floating-point values
- rational numbers are represented as the ratio of two integer numbers
- complex numbers are represented as the combination of real and imaginary
  components, both represented as real numbers

We need to support display and basic operations on these numbers
- for now, let's focus on just one basic operation: negation

We also need to provide:
- a way to simplify a rational number
- a way to get the complex conjugate of a complex number


---

# Number representations

Our design might involves:

- an [abstract base
  class](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
for numbers, specifying the *interface* that all numbers are expecting to
provide. This interface involves (at least) these [pure virtual
methods](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/):
  - a `display()` method
  - a `negate()` method
  - ...

--

- a set of 3 classes that *derive* from that base class, and override the
  implementations for the virtual methods
  - a `Real` class 
  - a `Rational` class, with an additional `simplify()` method
  - a `Complex` class, with an additional `conjugate()` method

--

- the `Complex` class may also be *composed* of two `Real` numbers

--

- All of these classes will also need to provide *getter* (accessor) & *setter*
(mutator) methods to get & set the values

---

# Medical catheters

A medical catheter manufacturer wishes to store information about all of the
catheter types it produces. The following statements summarise the
characteristics of catheters:

- All catheters should have a stiffness (nm<sup>-1</sup>), a cost (in pounds/pence) and a
  diameter. Diameters are represented in the French scale, in which 1Fr =
  0.33mm. All catheter diameters will be an integer between 3Fr and 34Fr

- All catheters produced by the manufacturer are either ablation catheters or
  balloon catheters. Ablation catheters have a power in Watts. Balloon
  catheters have a balloon size in mm

- The company manufactures both MR-compatible and non-MR-compatible ablation
  catheters. MR-compatible ablation catheters consist of a number of segments,
  although the precise number of segments varies

In the software application, the classes for all types of catheter should be able to display their parameters to the screen


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



