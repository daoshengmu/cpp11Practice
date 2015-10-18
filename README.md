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

Item30: Familiarize yourself with perfect forwarding failure cases
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

