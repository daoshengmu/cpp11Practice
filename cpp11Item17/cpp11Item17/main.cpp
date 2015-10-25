//
//  main.cpp
//  cpp11Item17
//
//  Item 17: Understand special member function generation
//  - Special member functions are those compilers may generate on their own : default ctor/dtor, copy/move operations.
//  - Move Ops are generated only if classes lacking explicitly declared move ops, copy ops, or a dtor.
//  - 2 copy operations are independent
//  - If declaring one Move operator
//      - Something about how move-ctor should be implemented.
//      - Default move-assignment op may do things wrong.
//  - Declaring a move op in a class causes compiler to disable the copy ops.
//  - Move ops won’t be generated for any class that explicitly declares a copy op
//  - If you declare any of a dtor, copy-ctor, or copy-assignment op, you should declare all three.
//  - C++11 won’t generate move ops if there’s user-declared dtor.
//  - When to generate MOVE ops
//      - Only if these 3 things are true in the class.
//      - No copy operations are declared.
//      - No move operations are declared.
//      - No destructor is declared.
//
//  Created by Daosheng Mu on 10/25/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <map>

class Widget {
    
public:
    ~Widget() {}        // User defined ctor.
    
    Widget(const Widget& w) = default;  // default copy ctor
    Widget& operator = (const Widget&) = default;  // copy assignment
    
};

class StringTable {     // Copy operator will not be affected. but move ops...
public:
    StringTable()
    {
        std::cout << "StringTable constructor..." << std::endl;
    }
    
    ~StringTable()
    {
        std::cout << "StringTable destructor..." << std::endl;
    }
    
private:
    std::map<int, std::string> values;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
