//
//  main.cpp
//  cpp11Item33
//
//  Item 33: Use decltype on auto&& parameters to std::forward them
//  - Generic lambdas in C++ 14
//      - Use auto in parameter specification
//  - declType
//      -   x               lvalue                          rvalue
//      -   auto&& x        lvalue ref                      rvalue ref
//      -   declype(x)      lvalue ref T&                   rvalue ref T or T&&
//      -   std::forward    Widget& forward(Widget& param)      Widget&& forward(Widget& param)
//                          {return static_cast<Widget&>(param);}   {return static_cast<Widget&&>(param);}
//                                                              Widget&& && forward(Widget& param)
//                                                                  {return static_cast<Widget&& &&>(param);}
//
//  Created by Daosheng Mu on 11/1/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

int normalize() {
    return 1;
}

int func(int) {
    return 1;
}

// closure class’s function call operator
class SomeCompilerGeneratedClassName {
public:
    template<typename T>
    auto operator()(T x) const
    { return func(normalize()); }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    // Use auto in parameter specification
    auto f = [](auto x) { return func(normalize(x)); };
    
    // Perfect forward
    auto f1 = [](auto x) { return func(normalize(std::forward<>(x))); };
    
    // Finally
    auto f2 = [](auto x) { return func(normalize(std::forward<decltype(x)>(x))); };
    
    std::cout << "Hello, World!\n";
    return 0;
}
