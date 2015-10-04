//
//  main.cpp
//  cpp11Item28
//
//  Item 28: Understand reference collapsing
//  - Can't delcare reference to reference
//  - For universal reference. When compilers generate references to references, reference collapsing dictates what happens next.
//  - If either reference is an lvalue reference, the result is an lvalue reference. Otherwise (i.e., if both are rvalue references) the result is an rvalue reference.
//  - Reference collapsing happens
//    - Template instantiation
//    - Type generation for auto variables
//    - typedefs and alias declarations(using)
//    - decltype
//  - Universal reference is a rvalue reference while it's satisfied.
//    - Type deduction distinguishes lvalues from rvalues
//    - Reference collapsing occurs
//
//  Created by Daosheng Mu on 10/4/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

template<typename T>
void func(T&& param)
{
    std::cout << "func ..." << std::endl;
}

class Widget
{
    
};

template<typename T>
class Gadget
{
public:
    typedef T&& RvalueRefToT;
};

//void func(Widget& && param)   // can't declare reference to reference, "reference collapsing"
//{
//    
//}

Widget widgetFactory()
{
    return Widget();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Widget w;
    func(w);    // Actually param is T&, but universal reference helps us deduct it to l-value.
    
    int x;
    
    //auto& &rx = x;  // error! can't declare reference to reference
    
    auto&& w1 = w;    // Widget& &&w1 = w; w1 is an lValue reference(Widget&).
    auto&& w2 = widgetFactory(); // Widget&& w2 = widgetFactory(); w2 is an rvalue reference(Widget&&).
    
    Gadget<int &> g;    // typedef int& && RvalueRefToT; reference collapsing=> typedef int& RvalueRefToT;
    
    int a = 0;
    decltype((a)) && b = a; // int&& b = a;
    
    std::cout << "Hello, World!\n";
    return 0;
}
