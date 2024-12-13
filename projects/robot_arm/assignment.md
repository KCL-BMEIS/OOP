# Modular robot arm control

## Introduction

A new modular design is being trialled for application in surgery. The arm can be assembled from modular segments, designed to be assembled into arbitrary configuration by slotting the end connector of one segment into the matching slot of the next segment. Available segments consist of a straight connector, a rotating joint, a bending (revolute) joint, and the instrument tip, as shown in the figure below. 

---

![Parts for the robot arm](parts.png)

*The various segment modules available for the robotic arm.*

---

These segments can be manufactured to various lengths. For the bending joint, the pivot point is always halfways along it length. The rotating and bending joint are the only two that can be controlled by setting their angle parameter, as illustrated above. 

A research team is investigating the possibility of using this modular design for a robotic arm to be used in surgery. They have settled on the design shown in the figure below:

---

![Fully configured robot arm](full_arm.png)

*The full design for the robotic arm to be assembled in this project.*

---

The challenge to be tackled in this project is to compute the exact position, speed and acceleration of the surgical instrument tip given the angles for each of the joints. This information is critical in ensuring the accuracy and safety of any procedure using the robot.


## Instructions

Your task in this coursework is to write C++ code capable of representing the state of the robotic arm, which will eventually be used to control it. Your code will need to read a file containing the angles for each of the joints for each time point. From that, it will need to compute the position, speed and acceleration of the tip and ensure the parameters in the file do not exceed the device's safety thresholds. 

Ideally, the code should also trace out the trajectory of the surgical tip and display it as a projection along the 3 main axes, as illustrated in the example terminal output below. 

---

![Example output of project](terminal_output.png)

*Example output from the program, showing the trajectory of the tip projected in the x-y, x-z and y-z planes, along with a plot of the expected speed and acceleration of the surgical tip as a function of time, based on the parameters provided.*

---

Note that while the configuration of the arm has already been finalised, your code should be designed to allow different configurations should the design change at a later stage. 

### The parameters file

The [data folder](data/) contains 3 parameter files for you to process. These are simple text files, consisting of one line per time point, with a 0.1s time interval. Each line lists the angles (in radians) for each of the joints in the robot arm. The angles are provided in radians, and ordered from the root to the tip of the arm.

### Representing the modular segments

The next challenge is to represent all these different segment types using standard C++ functionality, while ensuring the segments can be arranged in any arbitrary order. There are various ways of doing this, but the most obvious here is to use inheritance. 

### Displaying the trajectory and associated information

As with the [fMRI project](), we will rely on the [terminal graphics project](https://github.com/jdtournier/terminal_graphics) project to display our results directly in a sixel-compatible terminal (see [the relevant section of the fMRI project](https://github.com/KCL-BMEIS/OOP_projects/blob/main/fMRI/assignment.md#inspecting-the-time-course-information) for details). 

### Computing speed and acceleration

To compute the speed of the surgical tip, we will first need to compute the positions $\\{ \mathbf{x}_i \\}$ of the tip at each time point. From this, can we compute the speed using the central finite difference:

$$ v_t = \frac{1}{\delta t} \left( \mathbf{x}_{t+1} - \mathbf{x}_{t-1}\right) $$

