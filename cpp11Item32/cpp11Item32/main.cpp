//
//  main.cpp
//  cpp11Item32
//
//  Item 32: Use init capture to move objects into closures
//  - lambda
//      - If you have a move-only object (e.g., a std::unique_ptr), you cannot get it into a closure in C++11.
//      - c++14: the name of a data member in the closure class generated from the lambda
//      - an expression initializing that data member.
//  - std::bind()
//      - First argument: callable object
//      - Subsequent arguments: lvalues are copy constructed; rvalues are move constructed.
//  - Prefer lambdas to std::bind.
//  - Use C++14’s init capture to move objects into closures.
//  - In C++11, emulate init capture via hand-written classes or std::bind.
//
//  Created by Daosheng Mu on 10/25/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>

class Widget {
public:
    bool isValidated() const;
    bool isProcessed() const;
    bool isArchived() const;
    
private:
    
};

struct Vec3
{
    int x, y, z;
    Vec3() : x(0), y(0), z(0) { }
    Vec3(int x, int y, int z) :x(x), y(y), z(z) { }
    friend std::ostream& operator<<(std::ostream& os, Vec3& v) {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}';
    }
};

auto foo(int n) {
    return [n] (int i) mutable { return n += i; };
}

std::vector<double> data;

int main(int argc, const char * argv[]) {

    auto pw = std::make_unique<Widget>();   // Enable c++ 14 on XCode
    auto func = [pw = std::move(pw)]               // init data mbr
    { return pw->isValidated()              // in closure w/
        && pw->isArchived(); };             // std::move(pw)
    
    auto func14Move = [data = std::move(data)] {};
    
    auto func11Move =                       // emulate move capture in C++11
                std::bind(                              // C++11 emulation
                          [](const std::vector<double>& data)   // of init capture
                          { /* uses of data */ },
                          std::move(data)
                          );
    
    auto funcMutable =                      // emulate move capture of mutable lambda in C++11
    std::bind(                               // C++11 emulation
              [](std::vector<double>& data) mutable  // of init capture
              { /* uses of data */ },                // for mutable lambda
              std::move(data)
              );
    
    auto funcPW = [pw = std::make_unique<Widget>()]    // as before,
                { return pw->isValidated()           // create pw
                    && pw->isArchived(); };     // in closure
    
    auto funcBind = std::bind(
                  [](const std::unique_ptr<Widget>& pw)
                  { return pw->isValidated()
                      && pw->isArchived(); },
                  std::make_unique<Widget>()
                  );
    
    auto accumulator = foo(100);
    std::cout << accumulator(4) << std::endl;
    std::cout << accumulator(4) << std::endl;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
