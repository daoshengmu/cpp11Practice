//
//  main.cpp
//  cpp11Item30
//
//  Item30: Familiarize yourself with perfect forwarding failure cases
//  - Forwarding: one function passes its parameters to another function
//      - Only reference parameters should be considered.
//  - Perfect forwarding: don’t just forward objects, but also forward their salient characteristics
//      - types
//      - whether are lvalue or rvalue
//      - whether are const or volatile
//  - Perfect forwarding fails while
//      - Compilers are unable to deduce a type
//      - Compilers deduce the “wrong” type
//  - Pass 0 or NULL as a null pointer to a template, deducing an integral type (typically int)
//      - Would not be a perfect forwarding
//      - pass nullptr instead of 0 or NULL
//  - Overload function names and template names
//      - Function is not a type, can’t be deduced
//  - The kinds of arguments that lead to perfect forwarding fails
//      - braced initializers
//      - null pointers expressed as 0 or NULL
//      - declaration-only integral const static data members
//      - template and overloaded function names
//      - bitfields
//
//  Created by Daosheng Mu on 10/18/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <vector>


void f(std::size_t val)
{
    std::cout << val << std::endl;
}

template<typename T>
void fwd(T&& param)                  // accept any argument
{
    std::cout << "fwd()" << std::endl;
  //  param(12);
   // f(std::forward<T>(param));         // forward it to f
}

class Widget {
public:
    static constexpr std::size_t MinVals = 28; // MinVals' declaration
};
//constexpr std::size_t Widget::MinVals;

// no defn. for MinVals
        // use of MinVals

using ProcessFuncType =                        // make typedef;
int (*)(int);
int processVal(int value)
{
    std::cout << "I am processVal(int value)" << std::endl;
    return 1;
}
int processVal(int value, int priority)
{
    std::cout << "I am processVal(int value, int priority)" << std::endl;
    return 1;
}

ProcessFuncType processValPtr = processVal;

void f(int (*pf)(int))
{
    pf(10);
}

//void f(int (pf)(int)) {}            // declares same f as above

struct IPv4Header {
    std::uint32_t version:4,
    IHL:4,
    DSCP:6,
    ECN:2,
    totalLength:16;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::vector<int> widgetData;
    widgetData.reserve(Widget::MinVals);
    
    f(Widget::MinVals);
   // fwd(Widget::MinVals);
    
    f(processVal);                  // fine

    //fwd(processVal);                // which processVal?
    fwd(processValPtr);
    fwd(static_cast<ProcessFuncType>(processVal));  // also fine
    
    
    IPv4Header h;
    f(h.totalLength);              // fine
//  fwd(h.totalLength);          // error! fwd’s parameter is a reference, and h.totalLength is a non-const bitfield
    
    // copy bitfield value; see Item 6 for info on init. form
    auto length = static_cast<std::uint16_t>(h.totalLength);
    fwd(length);                        // forward the copy
    
    std::cout << "Hello, World!\n";
    return 0;
}







