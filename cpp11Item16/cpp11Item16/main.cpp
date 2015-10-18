//
//  main.cpp
//  cpp11Item16
//
//  Item 16: Make const member functions thread-safe
//  - Make const member functions thread-safe unless they’ll never be used in a concurrent context.
//  - Use of std::atomic may offer better performance than mutex, but only suitable for manipulation of single variable or memory location.
//
//  Created by Daosheng Mu on 10/18/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <mutex>
#include <cmath>

class Polynomial {
public:
    using RootType = std::vector<double>;
    
    RootType roots() const
    {
        std::lock_guard<std::mutex> g(m);
        if (!rootAreValid)
        {
            rootAreValid = true;
        }
        
        return rootVals;
    }
    
private:
    mutable std::mutex m;
    mutable bool rootAreValid{ false };
    mutable RootType rootVals{};
};

class Point {
public:
    double distFromOrigin() const noexcept
    {
        ++callCount;
        
        return std::hypot(x, y);
    }
private:
    mutable std::atomic<unsigned> callCount{0};
    double x, y;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
