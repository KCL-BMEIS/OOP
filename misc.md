---
layout: presentation
title: "Miscellaneous slides"
---

# Error handling

The previous example is a simple way to handle errors.
- we'll learn a better way when we cover *exceptions* later in the course

--

Some general rules about error handling:

- If your code is making assumptions about its inputs, check them!
  - for example, if your code assumes a parameter is positive, check and alert the user if this is not the case (and exit if appropriate)
  - *this will save you time later on!*

--

- If you can reasonably handle the error, do so, but warn the user about it

--

- Most of the time, the error will be *fatal* (not recoverable), in which case your program should *not* proceed
  - issue an informative message about the problem, and exit with a non-zero exit code

--

- try to detect errors as early as possible 
  - for example: don't start a long batch of processing without first checking that you can create the output file

