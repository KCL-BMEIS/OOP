---
layout: default
title: "Exercise solutions: Control structures"
---

# Exercise solutions: Control structures

## Exercise 1

The solution to the Exercise 12 from the "Basics of C++" worksheet has been
modified to include a if-else statement around the area computation code:

```c++
#include <iostream>
#include <cmath>
#include <stdexcept>

int main ()
{
    float a, b, c;
    std::cout << "Enter the values of a b c: ";
    std::cin >> a >> b >> c;

    // check:
    if (((a + b) <= c) || ((a + c) <= b) || ((b + c) <= a))
      throw std::runtime_error ("Not a valid triangle");

    float s = (a + b + c) / 2.0;
    float area = std::sqrt (s * (s - a) * (s - b) * (s - c));

    std::cout << "The area of the triangle is " << area << "\n";
    return 0;
}
```

---

## Exercise 2

Solution (input from terminal):

```c++
#include <iostream>

int main ()
{
    // read mass and height and
    // compute BMI classification

    // read mass and height
    std::cout << "Enter mass height (separated by space ): ";
    float mass, height;
    std::cin >> mass >> height;

    // compute and display BMI
    float bmi = mass / (height * height);
    std::cout << "Your BMI is " << bmi << "\n";

    // classify
    if (bmi < 18.5)
        std::cout << "Underweight\n";
    else {
        if (bmi < 25)
            std::cout << "Normal\n";
        else {
            if (bmi < 30)
                std::cout << "Overweight\n";
            else
                std::cout << "Obese\n";
        }
    }

    return 0;
}
```

Solution (command-line arguments):

```c++
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

int main (int argc, char* argv[])
{
    // read mass and height and
    // compute BMI classification

    std::vector<std::string> args (argv, argv+argc);
    if (args.size() < 3)
        throw std::runtime_error ("expected mass & height as arguments");

    float mass = std::stod (args[1]);
    float height = std:stod (args[2]);

    // compute and display BMI
    float bmi = mass / (height * height);
    std::cout << "Your BMI is " << bmi << "\n";

    // classify
    if (bmi < 18.5)
        std::cout << "Underweight\n";
    else {
        if (bmi < 25)
            std::cout << "Normal\n";
        else {
            if (bmi < 30)
                std::cout << "Overweight\n";
            else
                std::cout << "Obese\n";
        }
    }

    return 0;
}
```

---

## Exercise 3

The solution to Exercise 11 from the "Basics of C++" worksheet has been
modified to add code to compute the term in the square root and ensure it is
positive:

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

    // first check if roots are imaginary:
    float v = b * b - 4.0 * a * c;
    if (v < 0.0)
        std::cout << "roots are imaginary\n";
    else {
        // roots are real
        // compute roots
        r1 = ( -b + std::sqrt (v) ) / (2.0*a);
        r2 = ( -b - std::sqrt (v) ) / (2.0*a);

        // display answers
        std::cout << "Roots = " << r1 << ", " << r2 << "\n";
    }

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
    // loop through numbers from 1 to 50
    for (int i = 1; i <= 50; i++) {
        // is 'i' a prime number?
        bool isprime = true;
        for (int j = 2; j < i; j++) {
            if ((i % j) == 0) {
                isprime = false;
                // if we know it's not prime,
                // we can break straight away:
                break;
            }
        }
        if (isprime)
        std::cout << i << " is prime" << endl;
    }

    return 0;
}
```

---

## Exercise 5

The solution to Exercise 1 has been modified to add a do-while statement with
input/output statements to ask if user wants to proceed, and then read a
response:

```c++
#include <iostream>
#include <cmath>

int main ()
{
    char response = 'y';

    // loop whilst user wants to compute more areas:
    do {
        float a, b, c;
        std::cout << "Enter the values of a b c: ";
        std::cin >> a >> b >> c;

        // check:
        if (((a + b) <= c) || ((a + c) <= b) || ((b + c) <= a))
          std::cout << "Not a valid triangle\n";
        else {
            float s = (a + b + c) / 2.0;
            float area = std::sqrt (s * (s - a) * (s - b) * (s - c));

            std::cout << "The area of the triangle is " << area << "\n";
        }

        // do another one?
        std::cout << "Continue (y/n)? ";
        std::cin >> response;
    } while (response == 'y' || response == 'Y');

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
     int n1 = 0, n2 = 1;

     // print out the first two 1's
     std::cout << n1 << endl;
     std::cout << n2 << endl;

    // loop until sum of two numbers is > 10000
    while ((n1 + n2) <= 10000) {
        // compute and print current Fibonacci number
        int current = n1 + n2;
        std::cout << current << " ";

        // remember most recent 2 numbers in series
        n1 = n2;
        n2 = current;
    }

    return 0;
}
```


---

## Exercise 7

Solution:

```c++
#include <iostream>
#include <cmath>

int main ()
{
    // newton -raphson approximation
    float epsilon;

    // successive approximation
    float x1 = 2.9; // first guess

    do {
        // evaluate function
        float y1 = cos(x1) - x1;

        // compute derivative at x1:
        float y1deriv = -sin(x1) - 1.0;

        // new best guess:
        float x2 = x1 - y1 / y1deriv;

        // error:
        epsilon = std::abs(x2 - x1);

        // update best guess:
        x1 = x2;
    } while (epsilon > 0.001);

    // display result:
    std::cout << "Best guess = " << x1 << endl;

    return 0;
}
```

---

## Exercise 8

Solution:

```c++
#include <iostream>
#include <limits>

int main ()
{
    // program to output stats of sequence of integers
    int count = 0, minimum = std::numeric_limits<int>::max();
    int maximum = std::numeric_limits<int>::min();
    int sum = 0;

    // iteration - must read at least one number
    do {
        // read number
        std::cout << "Enter integer: ";
        int value;
        std::cin >> value;

        // if number is positive, update count, sum, min & max:
        if (value >= 0) {
            count++;
            sum += value;
            minimum = std::min (minimum, value);
            maximum = std::max (maximum, value);
        }
    } while (value >= 0);

    // display stats:
    std::cout << count << " numbers entered\n";
    std::cout << "  sum = " << sum << "\n";
    std::cout << "  range = " << maximum - minimum << "\n";
    std::cout << "  mean = " << static_cast<float>(sum) / count << "\n";

    return 0;
}
```

---

## Exercise 9

Solution:

```c++
#include <iostream>
#include <cmath>

int main ()
{
    // trigonometry application
    int code;

    // loop until -1 entered as code
    do {
        // read numbers
        std::cout << "Enter value & code (1=sin , 2=cos , 3=tan): ";
        float value;
        std::cin >> value >> code;

        // validate code
        switch (code) {
            case 1:
                std::cout << "sin(" << value << ") = "
                     << sin(value) << "\n";
                break;
            case 2:
                std::cout << "cos(" << value << ") = "
                     << cos(value) << "\n";
                break;
            case 3:
                std::cout << "tan(" << value << ") = "
                     << tan(value) << "\n";
                break;
            case -1:
                std::cout << "exiting ...\n";
                break;
            default:
                std::cout << "invalid code - reenter\n";
        }
    } while (code != -1);

    return 0;
}
```

---

## Exercise 10

Solution:

```c++
#include <iostream>
#include <cmath>

int main ()
{
    // error in approximation
    double e;

    // test different values of N, the number
    // of terms in the series
    int N = 1;
    do {

        // use Euler 's approximation to N terms
        double sum = 0.0;
        for (int n = 1; n <= N; n++)
            sum += 1.0/(n*n);

        double approx = std::sqrt (6.0 * sum);

        std::cout << "N = " << N << ", pi ~ " << approx << "\n";

        // what 's the error in approximation?
        e = std::abs (M_PI - approx);

        // increase number of terms in series
        N++;
    } while (e > 0.001);

    // display answer
    std::cout << "Euler's approximation is correct to within 0.001 for N=" 
       << N << "\n";

    return 0;
}
```

