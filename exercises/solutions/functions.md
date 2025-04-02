---
layout: default
title: "Exercise solutions: Functions
---

# Exercise solutions: Functions


## Exercise 1

Solution:

**`main.cpp`:**

```c++
#include <iostream>
#include "hmean.h"

int main ()
{
    float x, y;
    do {
        std::cout << "Enter two numbers: ";
        std::cin >> x >> y;
        if (((x != 0) && (y != 0)))
        std::cout << "Harmonic mean = " << harmonic_mean(x, y) << "\n";
    } while ((x != 0) && (y != 0));

    return 0;
}
```

**`hmean.h`:**

```c++
#pragma once

float harmonic_mean (float x, float y);
```

**`hmean.cpp`:**

```c++
#include "hmean.h"

float harmonic_mean (float x, float y)
{
    return ((2 * x * y) / (x + y));
}
```

---

## Exercise 2

Solution:

**`main.cpp`:**

```c++
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "fn.h"

int main (int argc, char* argv)
{
    std::vector<std::string> args (argv, argv+argc);
    if (args.size() < 2)
        throw std::runtime_error ("expected floating-point value as argument");

    float x = std::stod (args[1]);

    float val = f(x);
    std::cout << "Value of expression = " << val << "\n";

    return 0;
}
```


**`fn.h`:**

```c++
#pragma once

float f (float x);
```

**`fn.cpp`:**

```c++
#include "fn.h"

float f (float x)
{
    float result;
    result = x * x * x;
    result -= 5.0 * x * x;
    result += 12.0 * x;
    result -= 24.0;
    return result;
}
```



---

## Exercise 3

Solution:

**`main.cpp`:**

```c++
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "convert.h"

int main (int argc, char* argv)
{
    std::vector<std::string> args (argv, argv+argc);
    if (args.size() < 2)
        throw std::runtime_error ("expected value in HU as argument");

    std::cout << hu << " HU = " << HU_to_AC(hu) << " cm -1\n";

    return 0;
}
```


**`convert.h`:**

```c++
#pragma once

float HU_to_AC (float hu);
```


**`convert.cpp`:**

```c++
#include <iostream>
#include "convert.h"

float HU_to_AC (float hu)
{
    if (hu <= 0.0)
        return 0.093 + hu * 0.000093;
    else
        return 0.093 + hu * 0.000055031;
}
```

---

## Exercise 4

Solution:

**`main.cpp`:**

```c++
#include <iostream>
#include <vector>
#include <string>

#include "prime.h"

int main (int argc, char* argv)
{
    std::vector<std::string> args (argv, argv+argc);
    int num = 50;
    if (args.size() > 1)
        num = std::stoi (args[1]);

    display_primes (num);

    return 0;
}
```

**`prime.h`:**

```c++
#pragma once

bool is_prime (int i);
void display_primes (int n = 50);
```

**`prime.cpp`:**

```c++
#include <iostream>
#include "prime.h"

bool is_prime (int i)
{
    // special case: 1 is not prime
    if (i == 1)
        return false;

    for (int j = 2; j < i; j++)
        if ((i % j) == 0)
            return false;

    return true;
}


void display_primes (int n)
{
    std::cout << "prime numbers up to " << n << ": ";
    for (int i = 1; i <= n; i++) {
        if (is_prime(i))
            std::cout << i << " ";
    }
    std::cout << "\n";
}
```

---

## Exercise 5

Solution:


**`main.cpp`:**

```c++
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "rlencode.h"

// program to perform run -length encoding on string
int main (int argc, char* argv)
{
    std::vector<std::string> args (argv, argv+argc);
    if (args.size() < 2)
        throw std::runtime_error ("expected string as argument");

    rl_encode (args[1]);

    return 0;
}
```

**`rlencode.h`:**

```c++
#pragma once

#include <string>

void rl_encode (const std:: string& str);
```

**`rlencode.cpp`:**

```c++
#include <iostream>
#include <string>

#include "rlencode.h"

void rl_encode (const std::string& str)
{
    char c = str [0];
    int count = 1;
    for (auto n : str) {
        if (n == c)
            count++;
        else {
            std::cout << static_cast<int>(c) << " " << count << " ";
            c = n;
            count = 1;
        }
    }
    std::cout << static_cast<int>(c) << " " << count << "\n";
}
```

---

## Exercise 6

### Part A: 

The two errors were:
- The prototype (in `sphere.h`) and function signature (in `sphere.cpp`) of the
  `sphere()` function do not match. The argument to the function in `sphere.cpp`
  should be `float`, not `int`.
- The constant pi has local scope, i.e. it is only accessible from within the
  `main()` function. Its definition should be moved to the `sphere.cpp` file. Or,
  alternatively, the built-in `M_PI` constant from the `<cmath>` include file can
  be used.


Corrected code:

**`main.cpp`:**

```c++
#include <iostream >
#include "sphere.h"

int main () {

    float r;
    do {
        std::cout << "Enter radius (type -ve number to stop ) ";
        std::cin >> r;

        if (r >= 0.0)
            std::cout << "V = " << sphere(r) << "\n";
    } while (r >= 0.0);
}
```

**`sphere.h`:**

```c++
#pragma once

float sphere (float);
```

**`sphere.cpp`:**

```c++
#include "sphere.h"

float sphere (float r)
{
    const float pi = 3.14159265;

    float cube = r * r * r;
    return ((4.0 * pi * cube) / 3.0);
}
```



### Part B:


**main.cpp:**

```c++
#include <iostream>

#include "sphere.h"

int main () {
    float r;
    do {
        cout << "Enter radius (type -ve number to stop): ";
        cin >> r;
        if (r < 0)
            break;
        auto m = sphere (r);
        std::cout << "V = " << m.vol << ", A = " << m.area << endl;
    } while (r >= 0);
}
```


**`sphere.h`:**

```c++
#pragma once

struct VolArea {
    float vol, area;
};

VolArea sphere (float r);
```

**`sphere.cpp`:**

```c++
#include "sphere.h"

VolArea sphere (float r)
{
    const float pi = 3.14159265;

    float cube = r * r * r;
    return { (4.0 * pi * cube) / 3.0, 4.0 * pi * r * r };
}
```


---

## Exercise 7

Solution:

**`main.cpp`:**

```c++
#include <iostream >

#include "reverse.h"

// program to print out in reverse order
// characters read from keyboard
int main ()
{
    reverse ();
    return 0;
}
```

**`reverse.h`:**

```c++
#pragma once

void reverse ();
```

**`reverse.cpp`:**

```c++
#include <iostream>

#include "reverse.h"

void reverse ()
{
    char ch;
    std::cin.get(ch);
    if (ch != '\n') {
        reverse ();
        std::cout.put(ch);
    }
}
```

---

## Exercise 8


### Recursive solution:

**`main.cpp`:**

```c++
#include <iostream>
#include "conv_bin.h"

// program to convert decimal to binary
int main ()
{
    int n;

    std::cout << "Enter decimal number (0 -255): ";
    std::cin >> n;
    conv_bin(n ,1);
    return 0;
}
```


**`conv_bin.h`:**

```c++
#pragma once

void conv_bin(int n, int unit);
```

**`conv_bin.cpp`:**

```c++
#include <iostream>

#include "conv_bin.h"

void conv_bin (int n, int unit)
{
    if (unit > 128)
        return;

    conv_bin (n/2, unit*2);
    std::cout << n%2;
}
```


### Iterative solution:


**`main.cpp`:**

```c++
#include <iostream>

#include "conv_bin.h"

// program to convert decimal to binary
int main ()
{
    int n;
    std::cout << "Enter decimal number (0 -255): ";
    std::cin >> n;
    conv_bin(n);
    return 0;
}
```


**`conv_bin.h`:**

```c++
#pragma once

void conv_bin (int);
```

**`conv_bin.cpp`:**

```c++
#include <iostream>

#include "conv_bin.h"

void conv_bin (int n)
{
    int res = n;
    for (int i = 128; i > 0; i /= 2) {
        std::cout << res / i;
        res = res % i;
    }
}
```


---

## Exercise 9

Solution:

**`main.cpp`:**

```c++
#include <iostream>

#include "hanoi.h"

int main ()
{
    // move 3 disks from peg 1 to peg 3 using peg 2 as spare:
    tower (3, 1, 3, 2);
    return 0;
}
```

**`hanoi.h`:**

```c++
#pragma once

void tower (int n, int from, int to, int spare);
```

**`hanoi.cpp`:**

```c++
#include <iostream >

#include "hanoi.h"

void tower (int n, int from, int to, int spare)
{
    if (n == 1) // anchor condition
        std::cout << "move disk from peg " << from << " to peg " << to << endl;
    else { // inductive step
        tower (n - 1, from , spare , to);
        std::cout << "move disk from peg " << from << " to peg " << to << endl;
        tower (n - 1, spare , to , from );
    }
}
```

---

## Exercise 10

Solution:

**`main.cpp`:**

```c++
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "trig.h"

// program to compute trigonometric functions using indirect recursion
int main (int argc, char* argv)
{
    std::vector<std::string> args (argv, argv+argc);
    if (args.size() < 3)
        throw std::runtime_error ("expected function and value as arguments");

    float x = std::stod (args[2]);
    float result;

    if (args[1] == "sin") 
        result = mysin(x);
    else if (args[1] == "cos")
        result = mycos(x);
    else if (args[1] == "tan")
        result = mytan(x);
    else 
        throw std::runtime_error ("invalid function name: \"" + args[1] + "\"");

    std::cout << "Result: " << args[1] << "(" << x << ") = " << result << "\n";
}
```

**`trig.h`:**

```c++
#pragma once

float mysin (float x);
float mytan (float x);
float mycos (float x);
```

**`trig.cpp`:**

```c++
#include "trig.h"

const float small = 0.1;

float mysin (float x) 
{
    if (x < small)
        return x - x * x * x / 6.0;

    float sin_term = mysin(x / 3.0);
    float tan_squared = mytan(x / 3.0);
    tan_squared *= tan_squared;
    float tan_denom = 3.0 - tan_squared;
    float tan_numer = 1.0 + tan_squared;
    return sin_term * tan_denom / tan_numer;
}

float mytan (float x) {
    return mysin(x) / mycos(x);
}

float mycos (float x) {

    return 1 - mysin(x / 2);
}
```



---

## Exercise 11

Solution:


**`main.cpp`:**

```c++
#include <iostream>
#include <cmath>
#include <stdexcept>

double model (double a, double b, double c)
{
    if (c <= -1.0)
        throw std::runtime_error ("c must be larger than -1");

    if (c == 0.0)
        throw std::runtime_error ("c must be non -zero");

    double x = a - b / std::log (c + 1.0);

    if (x < 0.0)
        throw std::runtime_error ("a must be larger than b/log(c+1)");

    return std::sqrt (x);
}

int main ()
{
    std::vector<std::string> args (argv, argv+argc);
    if (args.size() < 4)
        throw std::runtime_error ("expected 3 floating-point arguments");

    try {
        double a = std::stod (args[1]);
        double b = std::stod (args[2]);
        double c = std::stod (args[3]);

        double value = model (a, b, c);

        std::cout << "result = " << value << "\n";
    }
    catch (const std::exception& error) {
        std::cerr << "error in calculation: " << error.what() << "\n";
    }
    catch (...) {
        std::cout << "unexpected error\n";
    }

    return 0;
}
```

