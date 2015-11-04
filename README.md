# cpp11Practice
Practices for "Effective Modern C++" book

Item 7: Distinguish between () and {} when creating objects.
 - Autogen constructor
 - Implicit return
 - Narrowing conversion constraint

Item 8: Prefer nullptr to 0 and NULL
 - Use nullptr!!

Item 9: Type alias
 - Prefer alias (using) declaration to typedefs
 - typedef doesn't support template.

Item 10: Scoped enum
 - Prefer scoped enums to unscoped enums
 - Origin types in enum can't be refined
 - No naming pollution
 - No implicit cast
 - Can be forward-declared

Item 11: Deleted functions
 - Prefer deleted functions to private undefined ones
 - Can forbid functions in public scopes, better for compile-error information
 - Can forbid friend classes
 - Can forbid unwanted implicit cast

Item12: Declare overriding functions override
 - To these constraints, which were also part of C++98, C++11 adds one more
 - The functions’ reference qualifiers must be identical
 - Member function reference qualifiers make it possible to treat lvalue and rvalue objects differently.

Item 13: Prefer const_iterators to iterators
 - Prefer non-member versions of begin, end, rbegin

Item 14: Declare functions noexcept if they won’t emit exceptions
 - Most functions, quite properly lack the noexcept designation.
 - Optimization is important, but correctness is more important.
 - All memory deallocation functions and all destructors—both user-defined and compiler-generated—are implicitly noexcept
 - Noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.

Item 15: Use constexpr whenever possible
  - constexpr objects are const and are initialized with values known during compilation.
  - constexpr functions can produce compile-time results when called with arguments whose values are known during compilation
  - constexpr objects and functions may be used in a wider range of contexts than non-constexpr objects and functions
  - constexpr is part of an object’s or function’s interface
  - Const vs. constexpr
    - constexpr shall be used in contexts where c++ require integral constant expression
      - Specification of array size
      - Integral template arguments
      - Enumerator values
      - Alignment specifiers
      - All constexpr objects are const, but not all const objects are constexpr
  - Limitation in C++ 11
    - Contain no more than a single executable statement : a return
    - conditional "?" recursion
    - Member function
      - Constexpr member functions are implicitly const.
      - Should take and return literal types. (bult-in types except void qualify)

Item 16: Make const member functions thread-safe
  - Make const member functions thread-safe unless they’ll never be used in a concurrent context.
  - Use of std::atomic may offer better performance than mutex, but only suitable for manipulation of single variable or memory location.

Item 17: Understand special member function generation
  - Special member functions are those compilers may generate on their own : default ctor/dtor, copy/move operations.
  - Move Ops are generated only if classes lacking explicitly declared move ops, copy ops, or a dtor.
  - 2 copy operations are independent
  - If declaring one Move operator
    - Something about how move-ctor should be implemented.
    - Default move-assignment op may do things wrong.
  - Declaring a move op in a class causes compiler to disable the copy ops.
  - Move ops won’t be generated for any class that explicitly declares a copy op
  - If you declare any of a dtor, copy-ctor, or copy-assignment op, you should declare all three.
  - C++11 won’t generate move ops if there’s user-declared dtor.
  - When to generate MOVE ops
    - Only if these 3 things are true in the class.
    - No copy operations are declared.
    - No move operations are declared.
    - No destructor is declared.

Item 23-0: Prerequisite
 - Type&& can only bind to non-const rvalue
 - Implicitly-declared move constructor
   - no user-declared copy constructors.  no copy constructor, =delete operator as well
   - no user-declared copy assignment operators.   no operator=(const &)
   - no user-declared move assignment operators.   no operator=(&&)
   - no user-declared destructors
   - move constructor is not defined as deleted.
   - compiler will declare a move constructor as a non-explicit inline public member of its class with the signature T::T(T&&).

Item 23: Understand std::move and std::forward.
 - std::move
   - Don’t declare objects const if you want to be able to move from them. Move requests on const objects are silently transformed into copy operations.
   - It does cast. It doesn’t move. It just helps you get a rvalue reference

 - std::forward
   - A conditional cast
   - std::forward casts its argument to an rvalue only if that argument is bound to an rvalue. (Not <Type&>)
   - Neither std::move nor std::forward do anything at runtime.

Item 24: Distinguish universal references from rvalue references
 - Universal references can bind to const or non-const objects, to volatile or non-volatile objects, even to objects that are both const and volatile. They can bind to virtually anything.
 - A function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the parameter or object is a universal reference.
 - If the form of the type declaration isn’t precisely type&&, or if type deduction does not occur, type&& denotes an rvalue reference.
 - Universal references correspond to rvalue references if they’re initialized with rvalues. They correspond to lvalue references if they’re initialized with lvalues.

Item 25: Use std::move on rvalue references
 - Rvalue references bind only to objects that are candidates for moving.
 - rvalue references should be unconditionally cast to rvalues (via std::move)
 - Universal references should be conditionally cast to rvalues (via std::forward)
 - Use std::forward on universal references
 - Never use std::move with universal references
 - Do not perform the same optimization on local variables that you’re returning. Due to RVO.
   - The type of the local object is the same as that returned by the function
   - The local object is what’s being returned
   - Do the same thing for rvalue references and universal references being returned from functions that return by value.
   - Never apply std::move or std::forward to local objects for RVO

Item 26: Avoid overloading on universal references
  - Functions taking universal references are the greediest functions in C++.
  - Perfect-forwarding constructors are especially problematic.
    - They’re typically better matches than copy constructors for non-const lvalues.
    - They can hijack derived class calls to base class copy and move constructors.

Item 27: Familiarize yourself with alternatives to overloading on universal references
  - Abandon overloading
    - Different function name
    - Not working for constructor
  - Pass by const T&
    - Not efficient. (recall the literal string case)
  - Pass by value
    - If the copy must happened

Item 28: Understand reference collapsing
  - Can't delcare reference to reference
  - For universal reference. When compilers generate references to references, reference collapsing dictates what happens next.
  - If either reference is an lvalue reference, the result is an lvalue reference. Otherwise (i.e., if both are rvalue references) the result is an rvalue reference.
  - Reference collapsing happens
    - Template instantiation
    - Type generation for auto variables
    - typedefs and alias declarations(using)
    - decltype
  - Universal reference is a rvalue reference while it's satisfied.
    - Type deduction distinguishes lvalues from rvalues
    - Reference collapsing occurs

Item 29: Assume that move operation are not present, not cheap, and not used
  - C++11 is willing to generate move operation for classes that lack them
    - no copy operation
    - no move operation
    - no destructors
  - Data members or base classes of types that have disabled moving
  - Cheap moving container: std::vector (store pointer). Non-cheap: std::array (store content)
  - std::string offers constant time move and linear time copy
    - SSO is implemented while capacity is no more than 15 characters
    - Moves are no faster than copies

Item 30: Familiarize yourself with perfect forwarding failure cases
  - Forwarding: one function passes its parameters to another function
    - Only reference parameters should be considered.
  - Perfect forwarding: don’t just forward objects, but also forward their salient characteristics
    - types
    - whether are lvalue or rvalue
    - whether are const or volatile
  - Perfect forwarding fails while
    - Compilers are unable to deduce a type
    - Compilers deduce the “wrong” type
  - Pass 0 or NULL as a null pointer to a template, deducing an integral type (typically int)
    - Would not be a perfect forwarding
    - pass nullptr instead of 0 or NULL
  - Overload function names and template names
    - Function is not a type, can’t be deduced
  - The kinds of arguments that lead to perfect forwarding fails
    - braced initializers
    - null pointers expressed as 0 or NULL
    - declaration-only integral const static data members
    - template and overloaded function names
    - bitfields

Item 31: Avoid default capture modes
  // lambda
  - Lambda syntax
    - []: capture nothing
    - [=]: capture all automatic variables used by value (default capture mode)
    - [&]: capture all automatic variables used by reference (default capture mode)
    - [a, &b]: capture a by value and b by reference
    - Default by-reference capture can lead to dangling references
    - Default by-value capture is susceptible to dangling pointers
  - for_each(begin(v), end(v), [] (const auto& n) { cout < n < endl; }); // Only c++14
    - lambda expression: an expression, part of the source code. (compile time, auto)
    - closure class: a class from which a closure is instantiated. (compile time)

Item 32: Use init capture to move objects into closures
  - lambda
    - If you have a move-only object (e.g., a std::unique_ptr), you cannot get it into a closure in C++11.
    - c++14: the name of a data member in the closure class generated from the lambda
    - an expression initializing that data member.
  - std::bind()
    - First argument: callable object
    - Subsequent arguments: lvalues are copy constructed; rvalues are move constructed.
  - Prefer lambdas to std::bind.
  - Use C++14’s init capture to move objects into closures.
  - In C++11, emulate init capture via hand-written classes or std::bind.

Item 33: Use decltype on auto&& parameters to std::forward them
  - Generic lambdas in C++ 14
    - Use auto in parameter specification
  - declType
    -   x               lvalue                          rvalue
    -   auto&& x        lvalue ref                      rvalue ref
    -   declype(x)      lvalue ref T&                   rvalue ref T or T&&
    -   std::forward    Widget& forward(Widget& param)      Widget&& forward(Widget& param)
                          {return static_cast<Widget&>(param);}   {return static_cast<Widget&&>(param);}
                                                              Widget&& && forward(Widget& param)
                                                                  {return static_cast<Widget&& &&>(param);}

Item 34: Prefer lambdas to std::bind
- Why lambda?
    - More readable
    - More expressive
    - More efficient
- lambda vs. std::bind
    - C++14, use lambda
    - C++11, use lambda but std::bind in
        - Move capture
        - Polymorphic function objects



