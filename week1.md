---
layout: presentation
title: "Week 1: Introduction"
---

class: center, top, right, title
background-image: url(images/title.jpg)
background-size: cover

.title[
5CCYB041

# OBJECT-ORIENTED PROGRAMMING


## Week 1: Introduction
]

---

# Teaching team

## Module leads

.center[ .left-col[ ![:scale 25%](images/donald.jpg) <br> J-Donald Tournier ]
.right-col[ ![:scale 25%](images/michela.jpg) <br> Michela Antonelli ] ]

## Lecturers

.center[ .left-col[ ![:scale 25%](images/toby.jpg) <br> Tobias Wood ]
.right-col[ ![:scale 25%](images/marc.jpg) <br> Marc Modat ] ]

---

# Week 1: Introduction

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

