---
layout: default
title: "Exercise solutions: Basics of C++"
---

# Exercises solutions: Basics of C++


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

int main (int argc, char* argv[])
{
    std::vector<std::string> args (argv, argv+argc);

    int n = std::stoi (args[1]);
    std::cout << "result = " << std::sqrt (std::abs (n)) << "\n";

    return 0;
}
```


9. Solution:
1 #include <iostream >
2 #include <cmath >
3 using
namespace
std;
4
5 int main ()
6 {
7
double x, y, z, result;
8
cout << "Enter x y z: " << endl;
9
cin >> x >> y >> z;
10
result = pow(x, pow(y,z));
11
cout << "x^y^z = " << result
<< endl;
12
13
return 0;
14 }
10. Solution:
1 #include <iostream >
2 using
namespace
std;
3
4 int main ()
5 {
6
// Program to compute
expression
7
// using
floating
point
arithmetic
4
8
int i;
9
float v, result;
10
cout << "Enter a number :\n";
11
cin >> i;
12
13
// use
decimal
points in numbers to ensure
14
// that
floating
point
arithmetic is used
15
v = (i + 3.0) * (i + 2.0) * (i + 1.0) * i;
16
result = v * v * v;
17
cout << "Result = " << result
<< endl;
18
return 0;
19 }
11. The errors are:
• Line 2: add #include <cmath> to be able to use sqrt function
• Line 14: replace << with >>
• Lines 17, 18: add brackets to correct division expression
Corrected code:
1 #include <iostream >
2 #include <cmath >
3 using
namespace
std;
4
5 int main ()
6 {
7
// compute
roots of quadratic
equation of
8
// form ax^2 + bx + c = 0
9
10
// declare
variables
for
coefficients
and roots
11
float a, b, c, r1 , r2;
12
13
// read
values of coefficients
from user
14
cout << "Enter a b c:" << endl;
15
cin >> a >> b >> c;
16
17
// compute
roots
18
r1 = (-b + sqrt(b*b - 4.0*a*c)) / (2.0 * a);
19
r2 = (-b - sqrt(b*b - 4.0*a*c)) / (2.0 * a);
20
21
// display
answers
22
cout << "Roots = " << r1 << ", " << r2 << endl;
23
24
return 0;
25 }
5
12. Solution:
1 #include <iostream >
2 #include <cmath >
3
4 using
namespace
std;
5
6 int main ()
7 {
8
float a, b, c, s, area;
9
cout << "Enter the values of a b c" << endl;
10
cin >> a >> b >> c;
11
s = (a + b + c) / 2.0;
12
area = sqrt (s * (s - a) * (s - b) * (s - c));
13
cout << "The area of the
triangle is " << area << endl;
14
return 0;
15 }
13. Solution:
1 #include <iostream >
2 #include <cmath >
3
4 using
namespace
std;
5
6 int main ()
7 {
8
// declare
variables
for radius , area , volume
9
float r, area , vol;
10
11
// read
radius
from
keyboard
12
cout << "Enter
radius:" << endl;
13
cin >> r;
14
15
// compute area , vol
16
area = 4.0 * M_PI * r * r;
17
vol = (4.0 / 3.0) * M_PI * r * r * r;
18
19
// display to screen
20
cout << "Surface
area = " << area << endl;
21
cout << "Volume = " << vol << endl;
22
23
return 0;
24 }
