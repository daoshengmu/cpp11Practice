//
//  main.cpp
//  cpp11Item23
//
//  Item 23-0: Prerequisite
//  - Type&& can only bind to non-const rvalue
//  - Implicitly-declared move constructor
//      - no user-declared copy constructors.  no copy constructor, =delete operator as well
//      - no user-declared copy assignment operators.   no operator=(const &)
//      - no user-declared move assignment operators.   no operator=(&&)
//      - no user-declared destructors
//      - move constructor is not defined as deleted.
//      - compiler will declare a move constructor as a non-explicit inline public member of its class with the signature T::T(T&&).
//
//
//  Created by Daosheng Mu on 9/20/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//


#include <iostream>
#include <string>

class A
{
public:
    std::string s;
    
    A(): s("test") {}
    
    A( const std::string& s1 ): s(s1) {}
    A( const A& o ) : s( o.s ) { std::cout<< "std move failed." << std::endl;  }
    A( A&& o ) noexcept : s( std::move(o.s) ) { std::cout << "std move success." << std::endl; }
};

A&& f( A&& w )
{
    A temp = w;
    
    std::cout<< "A func." << std::endl;
    return std::move(temp);
}

// Universal reference
template<class T>
void Foo( T&& t )
{
    //T&& a = std::move( t );     // error because T = int&, T&& = int&
}

int&& f1() {
    int i = 0;
    
    return std::move(i);
}

int main(int argc, const char * argv[])
{
    // insert code here...
    A a1 = f(A("123"));
    std::cout<< "123 output: " << a1.s << std::endl;
    A a2 = std::move(a1);
    
    int a = 10;
    Foo( a );
    
    // decltype
    int i = 0;

    auto x3a = i;               // decltype(x3a) is int
    decltype(i) x3d = i;        // decltype(x3d) is int
    auto x4a = (i);             // decltype(x4a) is int
    decltype((i)) x4d = (i);    // decltype(x4d) is int&
    auto x5a = (i);             // decltype(x5a) is int
    decltype(f1()) x5d = f1();  // decltype(x5d) is int&&
    
    std::cout << "Hello, World!\n";
    return 0;
}
