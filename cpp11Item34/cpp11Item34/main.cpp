//
//  main.cpp
//  cpp11Item34
//
//  Item 34: Prefer lambdas to std::bind
//  - Why lambda?
//      - More readable
//      - More expressive
//      - More efficient
//  - lambda vs. std::bind
//      - C++14, use lambda
//      - C++11, use lambda but std::bind in
//          - Move capture
//          - Polymorphic function objects
//
//  Created by Daosheng Mu on 11/1/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

double my_divide(double x, double y) { return x / y; }

using namespace std::placeholders;
auto fn_rounding = std::bind<int> (my_divide, _1, _2);

auto lowVal = 0;
auto highVal = 100;

class PolyWidget {
public:
    template<typename T>
    void operator() (const T& param) {}
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    // std::bind
    std::cout << fn_rounding(10, 3) << std::endl;
    
    // Readable
//    auto betweenL = [lowVal, highVal](const auto& val) {  //  build fail on cpp11
//        return lowVal <= val && val <= highVal;};
//
    auto betweenB = std::bind(std::logical_and<>(),
                             std::bind(std::less_equal<>(), lowVal, _1),
                              std::bind(std::less_equal<>(), _1, highVal));
    
    
//    auto betweenL11 = [lowVal, highVal](int val) {  return lowVal <= val && val <= highVal;};
//
//
    
    auto betweenB1 = std::bind(std::logical_and<bool>(),
                              std::bind(std::less_equal<int>(), lowVal, _1),
                              std::bind(std::less_equal<int>(), _1, highVal));

    PolyWidget pw;
    auto boundPW = std::bind(pw, _1);
    boundPW(1930);  // int
    boundPW(nullptr);  // nullptr
    boundPW("Rose");  // string
    
    auto boundPWAuto = [pw](const auto& param) {pm(param);}; // C++14
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
