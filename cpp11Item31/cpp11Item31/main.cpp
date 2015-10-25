//
//  main.cpp
//  cppItem31
//
//  Item 31: Avoid default capture modes
//  // lambda
//  - Lambda syntax
//      - []: capture nothing
//      - [=]: capture all automatic variables used by value (default capture mode)
//      - [&]: capture all automatic variables used by reference (default capture mode)
//      - [a, &b]: capture a by value and b by reference
//      - Default by-reference capture can lead to dangling references
//      - Default by-value capture is susceptible to dangling pointers
//  - for_each(begin(v), end(v), [] (const auto& n) { cout < n < endl; }); // Only c++14
//      - lambda expression: an expression, part of the source code. (compile time, auto)
//      - closure class: a class from which a closure is instantiated. (compile time)
//
//  Created by Daosheng Mu on 10/25/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <vector>

using FilterContainer =                     // see Item 9 for
std::vector<std::function<bool(int)>>;

template <typename Container>
void print_container(const Container& v)
{
    for_each(begin(v), end(v), [] (const decltype(*begin(v)) &n ) {
        std::cout << n << std::endl;
    });
}

FilterContainer filters;                    // filtering funcs

void addFiler() {
    
    auto divisor = 3;
    
//    filters.emplace_back( [&](int value) { return value % divisor == 0; }  // divisor will be dangle
//                         );
//    filters.emplace_back( [&divisor](int value) { return value % divisor == 0; }  // divisor will be dangle
//                         );
//    filters.emplace_back( [=](int value) { return value % divisor == 0; }  // divisor can't dangle
//                         );
    
    filters.emplace_back( [divisor](int value) { return value % divisor == 0; }  // Might better
                         );
}

class Widget {
    
public:
    void addFilter() const;
    
private:
    int divisor;    // Used in the filter
};

void Widget::addFilter() const
{
    // Error, divisor can't be captured.
//    filters.emplace_back( [divisor](int value) { return value % divisor == 0; } );
    
    auto currentObjectPtr = this;
    filters.emplace_back( [currentObjectPtr](int value) { return value % currentObjectPtr->divisor == 0; } );
    
    // Correct answer
    auto divisorCopy = divisor; // Make divisor its own life time instead of depending on Widget's life time.
    filters.emplace_back( [=](int value) { return value % divisorCopy == 0; } );
    
    static auto divisorS = 100;
    filters.emplace_back(
                         [=](int value)                     // captures nothing!
                         { return value % divisorS == 0; }   // refers to above static
                         );
    
    ++divisorS;
}

int main(int argc, const char * argv[]) {
    
    addFiler();
    addFiler();
    
    std::cout << "the length of filter " << filters.size() << std::endl;
    
    std::cout << "Hello, World!\n";
    return 0;
}
