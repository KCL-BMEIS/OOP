---
layout: presentation
title: "Week 1, session 2: Introduction"
---

class: title

5CCYB041
# OBJECT-ORIENTED PROGRAMMING
### Week 1, session 2
## Introduction

---

# Other forms of iteration

The `for` loop is by far the most commonly-used looping structure, but others exist and are sometimes more appropriate

--

The `while` loop takes this form:
```
while (condition)
  statement;
```
This will keep running `statement` as long as `condition` is true

--

The `do ... while` loop takes this form:
```
do 
  statement;
while (condition);
```
This will also run `statement` as long as `condition` is true. The difference with the regular `while` loop is that `condition` is tested *after* running `statement`


---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
switch (variable) {
  case value1: 
    statement;
    ...
    statement;
    break;
  case value2:
    statement;
    break;
  ...
  default:
    statement; 
}
```


---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
`switch` (variable) {
  case value1: 
    statement;
    ...
    statement;
    break;
  case value2:
    statement;
    break;
  ...
  default:
    statement; 
}
```
.explain-bottom[
the `switch` keyword denotes the start of our conditional section of code
]


---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
switch (`variable`) {
  case value1: 
    statement;
    ...
    statement;
    break;
  case value2:
    statement;
    break;
  ...
  default:
    statement; 
}
```
.explain-bottom[
`variable` is the variable whose value will determine the code to run
]


---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
switch (variable) {
* case value1: 
    statement;
    ...
    statement;
    break;
  case value2:
    statement;
    break;
  ...
  default:
    statement; 
}
```
.explain-bottom[
for each value of `variable` that we want to handle (e.g `value1`), we use the `case` keyword to label the matching section of code, using this syntax
]


---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
switch (variable) {
  case value1: 
*   statement;
*   ...
*   statement;
    break;
  case value2:
    statement;
    break;
  ...
  default:
    statement; 
}
```
.explain-bottom[
immediately after the `case` label, we insert the code to be run. This can consist of multiple lines &ndash; no need for braces here.
]


---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
switch (variable) {
  case value1: 
    statement;
    ...
    statement;
*   break;
  case value2:
    statement;
    break;
  ...
  default:
    statement; 
}
```
.explain-bottom[
... but we do need to close off the last statement of the code for that case with the `break` keyword!

More on the `break` statement shortly...
]

---

# Other forms of conditional execution

The `if` statement is by far the most common structure for conditional execution, but other forms exist.

The `switch` statement allows you to execute different section of code depending on the *value* of a variable. It takes this general form:
```
switch (variable) {
  case value1: 
    statement;
    ...
    statement;
    break;
  case value2:
    statement;
    break;
  ...
* default:
    statement; 
}
```
.explain-middle[
We can also have a catch-all `default` label at the end, which will be executed in case none of the other labels matched
]

