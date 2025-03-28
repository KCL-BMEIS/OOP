---
layout: default
title: "Exercise solutions: Basics of C++"
---

# Exercise solutions: Basics of C++


## Exercise 1

The bugs are:

- Line 3: no space in floaty;
- Lines 4 and 9: two variables declared with name z
- Line 6: no data type for constant max
- Line 7: constant e not initialised when declared
- Line 9: no semi-colon in char c

---

# Exercise 2

The answers are:

- Answer = 4.2
- Answer = 4
- Answer = 1
- Answer = undefined: this will result in a compilation error since the modulus
  operator is undefined for floating point arithmetic

Program listing:

```c++
#include <iostream >

int main ()
{
    // Program to compute result of expression
    // (a):
    std::cout << "Value = " << (7.0 * 3) / 5 << "\n";
    // answer: 4.2

    // (b):
    std::cout << "Value = " << (7 * 3) / 5 << "\n";
    // answer: 4

    // (c):
    std::cout << "Value = " << (7 * 3) % 5 << "\n";
    // answer: 1

    // (d):
    // std::cout << "Value = " << (7.0 * 3) % 5 << endl;
    // will not compile: modulo operator undefined
    // for floating point types!

    return 0;
}
```

---

## Exercise 3

There was an error on line 14 - we need to force the program to use
floating point arithmetic rather than integer arithmetic. The corrected
code is as follows:

```c++
# include <iostream>

int main ()
{
    // program to convert distances between miles and km
    float km, miles, km_in_miles ;

    // read distance in miles
    std::cout << "Enter distance in miles: ";
    std::cin >> miles ;

    // convert to km
    km_in_miles = (5.0/8.0); // one km in units of miles
    km = miles / km_in_miles;

    // display in km
    std::cout << " This equates to " << km << " km\n";

    return 0;
}
```

---

## Exercise 4

Solution:
```c++
#include <iostream>

int main ()
{
    // Program to compute result and remainder
    // using integer arithmetic

    int n, result , remainder;

    std::cout << "Enter a number: ";
    std::cin >> n;

    result = (2 + 3 * 3) / n;
    remainder = (2 + 3 * 3) % n;

    std::cout << "Result = " << result << "\n";
    std::cout << "Remainder = " << remainder << "\n";

    return 0;
}
```

---

## Exercise 5

Modified solution:
```c++
#include <iostream>

int main ()
{
    // Program to compute result and remainder
    // using integer arithmetic

    int n;
    float result;

    std::cout << "Enter a number: ";
    std::cin >> n;

    result = (2.0 + 3.0 * 3.0) / n;
    remainder = (2.0 + 3.0 * 3.0) % n;

    std::cout << "Result = " << result << "\n";

    return 0;
}
```

---

## Exercise 6

Solution:

```c++
#include <iostream >

int main ()
{
    int x=5, y=10;

    // (a)
    std::cout << ++x << "\n";

    // (b)
    std::cout << y-- << "\n";

    return 0;
}
```

---

## Exercise 7

### (a) 

No compilation error, although behaviour at run-time undefined due to division
by zero.

### (b) 

No compilation error. the `std::abs()` function is a template function and will
return a value of the same type as its argument, i.e. an `int` in this case.

### (c) 

Compilation error. The modulus operator will only work for integer values,
and this will be checked at compile-time as C++ uses static type checking.

---

## Exercise 8

Solution (reading from terminal):

```c++
#include <cmath>
#include <cstdlib>

int main ()
{
    int n;

    std::cout << "Enter number: ";
    std::cin >> n;

    std::cout << "result = " << std::sqrt (std::abs (n)) << "\n";

    return 0;
}
```


Solution (using command-line argument):

```c++
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>

int main (int argc, char* argv[])
{
    std::vector<std::string> args (argv, argv+argc);

    if (args.size() < 2)
      throw std::runtime_error ("expected at least one argument");

    int n = std::stoi (args[1]);
    std::cout << "result = " << std::sqrt (std::abs (n)) << "\n";

    return 0;
}
```

---

## Exercise 9


Solution:

```c++
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>

int main (int argc, char* argv[])
{
    std::vector<std::string> args (argv, argv+argc);

    if (args.size() < 4)
      throw std::runtime_error ("expected 3 arguments");

    double x = std::stod (args[1]);
    double y = std::stod (args[2]);
    double z = std::stod (args[3]);

    double result = std::pow (x, std::pow (y,z));
    std::cout << "x^y^z = " << result << "\n";

    return 0;
}
```

## Exercise 10

Solution:

```c++
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>

int main (int argc, char* argv[])
{
    // Program to compute expression
    // using floating point arithmetic

    std::vector<std::string> args (argv, argv+argc);

    if (args.size() < 2)
      throw std::runtime_error ("expected one integer argument");

    int i = std::stoi (args[1]);

    // use decimal points in numbers to ensure
    // that floating-point arithmetic is used:
    float v = (i + 3.0) * (i + 2.0) * (i + 1.0) * i;
    float result = v * v * v;

    std::cout << "Result = " << result << "\n";
    return 0;
}
```

---

## Exercise 11

The errors are:
- add #include <cmath> to be able to use sqrt function
- at line that starts with `std::cin`: replace `<<` with `>>`
- when computing roots `r1` & `r2`: add brackets to correct division expression

Corrected code:

```c++
#include <iostream>
#include <cmath>

int main ()
{
    // compute roots of quadratic equation of form ax^2 + bx + c = 0

    // declare variables for coefficients and roots
    float a, b, c, r1, r2;

    // read values of coefficients from user
    std::cout << "Enter a b c: ";
    std::cin >> a >> b >> c;

    // compute roots
    r1 = ( -b + std::sqrt (b*b - 4.0*a*c) ) / (2.0*a);
    r2 = ( -b - std::sqrt (b*b - 4.0*a*c) ) / (2.0*a);

    // display answers
    std::cout << "Roots = " << r1 << ", " << r2 << "\n";
    return 0;
}
```

---

## Exercise 12

Solution:

```c++
#include <iostream>
#include <cmath>

int main ()
{
    float a, b, c;
    std::cout << "Enter the values of a b c: ";
    std::cin >> a >> b >> c;

    float s = (a + b + c) / 2.0;
    float area = std::sqrt (s * (s - a) * (s - b) * (s - c));

    std::cout << "The area of the triangle is " << area << "\n";
    return 0;
}
```


---

## Exercise 13

Solution:

```c++
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>

int main (int argc, char* argv[])
{
    // Program to compute expression
    // using floating point arithmetic

    std::vector<std::string> args (argv, argv+argc);

    if (args.size() < 2)
      throw std::runtime_error ("expected one floating-point argument");

    float r = std::stod (args[1]);

    // compute area , vol
    float area = 4.0 * M_PI * r * r;
    float vol = (4.0 / 3.0) * M_PI * r * r * r;

    // display to terminal:
    std::cout << "Surface area = " << area << "\n";
    std::cout << "Volume = " << vol << "\n";

    return 0;
}
```

