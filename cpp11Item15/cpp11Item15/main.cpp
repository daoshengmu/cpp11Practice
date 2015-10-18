//
//  main.cpp
//  cpp11Item15
//
//  Item 15: Use constexpr whenever possible
//  - constexpr objects are const and are initialized with values known during compilation.
//  - constexpr functions can produce compile-time results when called with arguments whose values are known during compilation
//  - constexpr objects and functions may be used in a wider range of contexts than non-constexpr objects and functions
//  - constexpr is part of an object’s or function’s interface
//  - Const vs. constexpr
//      - constexpr shall be used in contexts where c++ require integral constant expression
//          - Specification of array size
//          - Integral template arguments
//          - Enumerator values
//          - Alignment specifiers
//      - All constexpr objects are const, but not all const objects are constexpr
//  - Limitation in C++ 11
//      - Contain no more than a single executable statement : a return
//      - conditional "?" recursion
//      - Member function
//          - Constexpr member functions are implicitly const.
//          - Should take and return literal types. (bult-in types except void qualify)
//
//  Created by Daosheng Mu on 10/18/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <array>

constexpr int Pow(int base, int exp) noexcept // Clang can't compile, but gcc can
{
    return (exp==0 ? 1 : base * std::pow(base, exp) );
}

//constexpr int Pow1(int base, int exp)  // Clang can't compile
//{
//    return std::pow(base, exp);
//}

constexpr int Pow2(int base, int exp)  noexcept // Clang can't compile, but gcc can
{
    return (exp==0 ? 1 : base * pow(base, exp) );
}

int GetRand(int aMod) {
    auto r = rand() % aMod;
    std::cout << "rand num " << r << std::endl;
    return r;
}

class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
    : x(xVal), y(yVal)
    {
        
    }
    
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }
    
    void setX(double newX) noexcept { x = newX; }
    void setY(double newY) noexcept { y = newY; }   // C++14 can return constexpr void
    
private:
    double x, y;
};

constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept
{
    return { (p1.xValue() + p2.xValue() ) / 2,  (p1.yValue() + p2.yValue() ) / 2 };
}

// C++14 can return reflection of p with respect to the origin.
//constexpr Point reflection(const Point& p) noexcept
//{
//    Point result;
//    
//    result.setX(-p.xValue());
//    result.setY(-p.yValue());
//    
//    return result;
//}

int main(int argc, const char * argv[]) {
    // insert code here...
//    int sz; // failed
//    int sz = 10; // failed
    const int sz = 15; // Success. constexpr objects are initialized with values known during compilation.
    
    constexpr auto arraySize1 = sz;
    std::array<int, sz> data1;
    
    constexpr auto arraySize2 = 10;
    std::array<int, arraySize2> data2;
    
    const auto arraySize3 = sz;     // Ok. arraysize3 is const copy of sz
    std::array<int, arraySize3> data3;  // Error. arraySize3 is not known at compilation time.
    
   // std::array<int, Pow(3, sz)> ary;  // Clang can't compile, but gcc can // Compile time constant
    
    srand(time(NULL));
    auto base = GetRand(10);
    auto exp = GetRand(3);
    
    std::cout << Pow(base, exp) << std::endl;  // run-time constant
    
    constexpr Point p1(9.4, 10.8);
    constexpr Point p2(10.2, 3.8);
    
    constexpr auto mid = midpoint(p1, p2);
    
    std::cout << "Hello, World!\n";
    return 0;
}
