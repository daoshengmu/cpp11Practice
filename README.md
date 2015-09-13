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

