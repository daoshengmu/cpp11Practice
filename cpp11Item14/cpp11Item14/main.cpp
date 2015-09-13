//
//  main.cpp
//  cpp11Item14
//
//  Item 14: Declare functions noexcept if they won’t emit exceptions
//  - Most functions, quite properly lack the noexcept designation.
//  - Optimization is important, but correctness is more important.
//  - All memory deallocation functions and all destructors—both user-defined and compiler-generated—are implicitly noexcept
//  - Noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
//
//  Created by Daosheng Mu on 9/13/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//
#include <iostream>


// Conditional noexcept
template <class T, size_t N>
void Swap( T (&a)[N] , T (&b)[N] ) noexcept( noexcept( swap( *a, *b ) ) ) // No except
{
    
}

//template <class T1, class T2>
//struct pair{
//    
//    void Swap( pair& p ) noexcept( noexcept( swap( first, p.first ) ) &&
//                                  noexcept( swap( second, p.second ) ) );  // No except
//};


struct Bad
{
    Bad() {}
    Bad(Bad&& ) // may throw
    {
        std::cout << "Throwing move constructor called" << std::endl;
    }
    
    Bad(Bad& )  // may throw as well
    {
        std::cout << "Throwing copy constructor called\n";
    }
    
};

struct Good
{
    Good() {}
    Good(Good&& ) noexcept // may throw
    {
        std::cout << "Non-Throwing move constructor called" << std::endl;
    }
    
    Good(Good& ) noexcept // may throw as well
    {
        std::cout << "Non-Throwing copy constructor called\n";
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Good g;
    Bad b;
    
    Good g2 = std::move_if_noexcept( g );
    Bad b2= std::move_if_noexcept( b );
    
    std::cout << "Hello, World!\n";
    return 0;
}
