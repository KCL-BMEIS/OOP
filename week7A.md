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

# Picking up where we left off

We continue working on our [robot arm
project](https://github.com/KCL-BMEIS/OOP/blob/main/projects/robot_arm/assignment.md)

You can find the most up to date version in [the project's `solution/`
folder](https://github.com/KCL-BMEIS/OOP/tree/robot_solution/projects/robot_arm/solution)

.explain-bottom[
Make sure your code is up to date now!
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
    the coarseness of the graine, etc.

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
- it is used to implement multiple sub-types that shared a common set of
  features

--

Examples of inheritance include:
- cars that share a common chassis and engine, but can be customised with
  different bodywork, furnishing, and extras
  - e.g. Volkswagen Golf, Audi A3, and Skoda Octavia
--
- laptops are often designed as a series, with a range of models sharing common
  attributes (chassis, screen, battery, etc), but different CPUs, memory,
  storage, etc. 

--

These are examples of making use of a common base, which can then be extended
in different ways for specific products
- this means developpers can spend less time optimising one shared base, and
  more time on the features specific to each product
 
---

# Inheritance in OOP

Inheritance in achieved in OOP by allowing a *base class* to be inherited by
one or more *derived classes*


---
name: polymorphism
class: section

# Polymorphism

---

# Polymorphism


---

# Polymorphism in OOP


---
name: relationships
class: section

# Relationships between classes

---

# Composition 

---

# Aggregation

---

# Inheritance

---
