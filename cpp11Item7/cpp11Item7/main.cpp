//
//  main.cpp
//  cpp11Item7
//
// Item 7: Distinguish between () and {} when creating objects.
//
// - Autogen constructor
// - Implicit return
// - Narrowing conversion constraint
//
//  Created by Daosheng Mu on 8/19/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <vector>

class MyClass
{
public:
    MyClass( int aA, float aB ): a( aA ), b( aB ) {}
    int a{0};
    float b{0};
};

MyClass funcRtn() {
    
    return { 1, 3 };
}

MyClass funcRtn1() {
    
    return MyClass{ 6, 7 }; // It support MyClass( 6, 7 ) as well.
}

void vectorTest()
{
    std::vector<int> v1( 10, 20 );
    std::cout << "size: " << v1.size() << " 1st: " << v1[0] << " 2nd: " << v1[1] << std::endl;
    
    std::vector<int> v2{ 10, 20 };
    std::cout << "size: " << v2.size() << " 1st: " << v2[0] << " 2nd: " << v2[1] << std::endl;
}


template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
        std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // copy list-initialization in return statement
        // this is NOT a use of std::initializer_list
    }
};

void initializerList()
{
    S<int> s = { 1, 2, 3, 4, 5 };
}

class Widget
{
public:
    Widget( int i, bool b ) { std::cout << "Widget construct bool\n"; }
    Widget( int i, double b ) { std::cout << "Widget construct double \n" ; }
//    Widget( std::initializer_list<std::string> il )
//    { std::cout << "Widget construct initializer_list \n" ; } // type to int will be error.(narrow conversion constraint) to double is ok
    Widget( std::initializer_list<long double> il )
    { std::cout << "Widget construct initializer_list \n" ; } // type to int will be error.(narrow conversion constraint) to double is ok
    
    Widget( const Widget& aW )
    {
        std::cout << "Widget copy constructor\n";
    }
    
//    operator float() const        // This will happen error. I don't know what it means.
//    {
//        std::cout << "operator float\n";
//    }

};

void tryInitializer()
{
    Widget w1( 10, 2.0 );
    Widget w2{ 10, 2.0 };
    
    Widget w5(w1);
    Widget w6{w1};
    Widget w7(std::move(w1));
    Widget w8{std::move(w1)};
    
    Widget w9( 1, 2.0 );
    //float b = w9;  // Error
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    MyClass c{ 3, 4.0 };  // a = 3.0 will fail
    std::cout << c.b << std::endl;
    MyClass c1( 2.0, 5.0 );
    std::cout << c1.b << std::endl;
    
    MyClass c2( funcRtn() );
    std::cout << c2.b << std::endl;
    
    // Print vector
    vectorTest();
    
    initializerList();
    tryInitializer();
    
    return 0;
}

