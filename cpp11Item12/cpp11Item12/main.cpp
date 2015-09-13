//
//  main.cpp
//  Item12: Declare overriding functions override
//  - To these constraints, which were also part of C++98, C++11 adds one more
//  - The functions’ reference qualifiers must be identical
//  - Member function reference qualifiers make it possible to treat lvalue and rvalue objects differently.
//
//  Created by Daosheng Mu on 9/12/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

class Base {
public:
    virtual void mf1() const
    {
        
    }
    virtual void mf2( int x )
    {
        
    }
    virtual void mf3() &
    {
        
    }
    virtual void mf4() const
    {
        std::cout << "mf4 function in Base function." << std::endl;
    }
};

class Derived: public Base {
public:
    virtual void mf1() const override
    {
        
    }
    virtual void mf2( int x ) override
    {
        
    }
    virtual void mf3() & override
    {
        
    }
    virtual void mf4() const override
    {
        std::cout << "mf4 function in Derived function." << std::endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Base *b = new Derived();
    b->mf4();
    
    delete b;
    
    return 0;
}
