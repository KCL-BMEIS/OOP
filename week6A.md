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

# Designing the base class


