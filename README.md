# cpp11Practice
Practices for "Effective Modern C++" book

Item 7: Distinguish between () and {} when creating objects.
 - Autogen constructor
 - Implicit return
 - Narrowing conversion constraint

Item 8: Prefer nullptr to 0 and NULL.
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
 