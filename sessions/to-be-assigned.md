# Topics not yet covered:

- [`switch` statement](https://www.geeksforgeeks.org/switch-statement-in-cpp/)
- jump statements: [`break` and `continue`](https://www.w3schools.com/cpp/cpp_break.asp)
- [conditional (ternary) operator (`?:`)](https://www.geeksforgeeks.org/cpp-ternary-or-conditional-operator/)
- [Resource Acquisition Is Initialization (RAII)](https://www.geeksforgeeks.org/resource-acquisition-is-initialization/)
- [the function stack](https://www.geeksforgeeks.org/function-call-stack-in-c/)
- [recursion](https://www.geeksforgeeks.org/cpp-recursion/)
- categories using [enumerated types (`enums`)](https://www.geeksforgeeks.org/enumeration-in-cpp/)
- [class destructor](https://www.geeksforgeeks.org/destructors-c/)
- multi-line comments and why they're usually best avoided
- dynamic vs. static type checking
- `std::array`
- difference between `std::vector::operator[]` and `std::vector::at()` in terms of bounds checking
- expressions with mixed types, implicit type casting, integer promotion, ...
- destructors
- static data members
- copy constructor
- virtual functions
- pure virtual functions
- abstract and concrete classes
- inheritance vs. composition
- member function overloading
- difference between virtual and overloaded functions
- static / dynamic binding 
- OOP design - REQUIRES A LOT OF THOUGHT!
- UML
- composition / aggregation / inheritance
- operator overloading
- friend functions
- operator overloading: global or member?
- `this` pointer
- overloading the assignment operator
- runtime vs. compile-time/static polymorphism
- object lifetime & ownership
  - relationship to composition & aggregation, etc.
- OOP principles: encapsulation, polymorphism, inheritance, abstraction
- [OOP design principles](https://hackernoon.com/10-oop-design-principles-every-programmer-should-know-f187436caf65) ([SOLID](https://www.digitalocean.com/community/conceptual-articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design)): 
  - DRY (Don’t repeat yourself)
  - Encapsulate What Changes
  - Open Closed Design Principle
  - Single Responsibility Principle
  - Dependency Injection or Inversion principle
  - Favor Composition over Inheritance
  - Liskoff substitution principle
  - Interface Segregation Principle
  - Programming for Interface not implementation
  - Delegation principles




---
  
# Open questions:

- how use inheritance in a meaningful way without pointers?
  - should be fine using *references* instead
- how to demonstrate aggregation without pointers?
  - can demonstrate construction of member (const) reference 
  - note that [non-const references are not recommended in the C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-constref)
    - but only because this makes the class copy-constructable, but not copy-assignable
    - if anything, highlights issues of ownership and lifetime, which are a serious problem with aggregation
- [blog abour OOP design process](https://www.mdfaisal.com/blog/first-5-steps-of-object-oriented-design)
  - how to teach design?
  - how to *assess* design?

---

# NOT covered in course:

- Why not use pointers and manual memory management? See recommendations in this video:
  - [Kate Gregory: Stop Teaching C](https://www.youtube.com/watch?v=YnWhqhNdYyk)
  - and these blog posts:
      - [C++ Will No Longer Have Pointers](https://www.fluentcpp.com/2018/04/01/cpp-will-no-longer-have-pointers/)
      - [Raw Pointers Are Gone!](https://arne-mertz.de/2018/04/raw-pointers-are-gone/)
      - [No New New: Raw Pointers Removed from C++](https://www.modernescpp.com/index.php/no-new-new/)
      - [Deprecating Raw Pointers in C++20](https://www.cppstories.com/2018/04/deprecating-pointers/)
      - [No more pointers](https://blog.tartanllama.xyz/no-pointers/)


