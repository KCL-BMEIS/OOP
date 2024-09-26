---
layout: presentation
title: "Week 1: Introduction"
---

class: center, middle, title
background-image: url(images/title.jpg)
background-size: cover

.title[
# OBJECT-ORIENTED PROGRAMMING

5CCYB041

## Week 1: Introduction
]

---

# Teaching team

## Module leads

- ![donald](images/donald.jpg) J-Donald Tournier (jacques-donald.tournier@kcl.ac.uk)
- ![michela](images/michela.jpg) Michela Antonelli (michela.antonelli@kcl.ac.uk)

## Lecturers

- ![toby](images/toby.jpg) Tobias Wood (tobias.wood@kcl.ac.uk)
- ![marc](images/marc.jpg) Marc Modat (marc.modat@kcl.ac.uk)

---

## Week 1: Introduction

## Topics to be covered:

- the command-line
- navigating the filesystem
- invoking the compiler
- using an editor
- writing our first `hello_world.cpp`


---

# Agenda

1. Introduction
2. Deep-dive
3. ...

[NOTE]: Note that you need active internet connection to access remark.js script file

---

# Hello World

```
#include <iostream>

int main ()
{
* std::cout << "Hello World!" << std::endl;
  return 0;
}
```

---

# Hello World

```
#include <iostream>

int main ()
{
  std::cout << "Hello World!" << std::endl;
  `return` 0;
}
```
