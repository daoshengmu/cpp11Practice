//
//  main.cpp
//  cpp11Item25
//
//  Item 25: Use std::move on rvalue references
//  - Rvalue references bind only to objects that are candidates for moving.
//  - rvalue references should be unconditionally cast to rvalues (via std::move)
//  - Universal references should be conditionally cast to rvalues (via std::forward)
//  - use std::forward on universal references
//  - Never use std::move with universal references
//  - Do not perform the same optimization on local variables that you’re returning. Due to RVO.
//      - the type of the local object is the same as that returned by the function
//      - the local object is what’s being returned
//  - Do the same thing for rvalue references and universal references being returned from functions that return by value.
//  - Never apply std::move or std::forward to local objects for RVO
//
//  Created by Daosheng Mu on 9/27/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

class Foo
{
    
};

class Widget
{
public:
    Widget() = default;
    Widget( Widget&& rhs )
    : name(std::move(rhs.name)), p(std::move(rhs.p))
    {
        
    }
    
    // std::move would have chance to unconditionally cast rvalues.
//    template<typename T>
//    void SetName( T& newName )
//    {
//        std::cout << "I am rvalue." << std::endl;
//       // name = std::move( newName );
//    }
    
    // Unless we declare the other const rvalue to assist. It would have to maintain more source code
    template<typename T>
    void SetName( const T& newName )
    {
        std::cout << "I am const rvalue." << std::endl;
    }
    
//    template<typename T>  // Never use std::move with universal references
//    void SetName( T&& newName )
//    {
//        std::cout << "I am rvalue reference." << std::endl;
//        name = std::move( newName );
//    }

    void SetName( std::string newName )
    {
        std::cout << "I am rvalue reference." << std::endl;
        name = std::move( newName );
    }
    
    Widget operator+( const Widget& rhs )
    {
        this->name += rhs.name;
        return std::move( *this );
    }
    
public:
    std::string name;
    Foo p;
};

template <typename T>
Widget resetNameAnyCopy(T &&w)
{
    w.name = "reset";
    return std::forward<T>(w);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Widget w1;
    w1.name = "I am w1";
    Widget w2(std::move(w1));
    
    std::cout << "W2 name is " << w2.name << std::endl;
    
    auto n = "12345";
    w2.SetName( n );
    std::cout << "W2 name is " << w2.name << std::endl;
    std::cout << "n is " << n<< std::endl;

    w1.name = "I am w1 back ";
    std::cout << "W1 name is " << w1.name << std::endl;
    Widget w3 = w1 + w2;
    std::cout << "W1 name is " << w1.name << std::endl;
    std::cout << "W2 name is " << w2.name << std::endl;
    std::cout << "W3 name is " << w3.name << std::endl;
    
    Widget w4 = resetNameAnyCopy<Widget>(std::move(w3));
    std::cout << "W3 name is " << w3.name << std::endl;
    std::cout << "W4 name is " << w4.name << std::endl;
    
    std::cout << "Hello, World!\n";
    return 0;
}
