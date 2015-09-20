//
//  main.cpp
//  cpp11Item23
//
//  Item 23: Understand std::move and std::forward.
//  std::move
//  - Don’t declare objects const if you want to be able to move from them. Move requests on const objects are silently transformed into copy operations.
//  - It does cast. It doesn’t move. It just helps you get a rvalue reference
//
//  std::forward
//  - A conditional cast
//  - std::forward casts its argument to an rvalue only if that argument is bound to an rvalue. (Not <Type&>)
//  - Neither std::move nor std::forward do anything at runtime.
//
//  Created by Daosheng Mu on 9/20/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

// std::move
template< class T > struct remove_reference      {typedef T type;};
template< class T > struct remove_reference<T&>  {typedef T type;};
template< class T > struct remove_reference<T&&> {typedef T type;};

template<typename T>
typename remove_reference<T>::type&&
Move(T&& param)
{
    using ReturnType = typename remove_reference<T>::type&&;    // alias declaration. Item 9
    
    return static_cast<ReturnType>(param);
}

class Annotation
{
public:
    Annotation(const std::string text) // Move requests on const objects are silently transformed into copy operations. It should be changed in this way, Annotation(std::string& text)
    : value(Move(text))
    {
        
    }
    
private:
    std::string value;
};

// std::forward
template<typename _Tp>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type& __t) noexcept    // lvalue
{
    return static_cast<_Tp&&>(__t);
}

template<typename _Tp>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type&& __t) noexcept   // rvalue
{
    static_assert(!std::is_lvalue_reference<_Tp>::value, "Can't forward an rvalue as an lvalue.");
    
    return static_cast<_Tp&&>(__t);
}

std::function<void(void)> mf;
//void Set(const std::function<void(void)>& f) { mf = f; }
//void Set(const std::function<void(void)>&& f) { mf = std::move(f); }
// ==> refactory to
template<class T>
void Set(T&& f) { mf = std::forward<T>(f); }    // Perfect forwarding
void Set(std::function<void(void)> f) { mf = std::move(f); }    // copy(move) and move

class Widget
{
public:
    Widget() {}
    
    Widget(Widget&& rhs)
    : s(std::move(rhs.s))   // Item 25: std::move on rvalue reference. std::forward on universal reference
    {
        std::cout << "Widget move constructor. \n";
    }
    
//    Widget(Widget&& rhs)
//    : s(std::forward<std::string>(rhs.s))   // Item 25: std::move on rvalue reference. std::forward on universal reference
//    {
//        std::cout << "Widget move constructor. \n";
//    }
    
    std::string s;
};

void process(const Widget& lValArg) {}
void process(Widget&& rValArg) {}

template<typename T>
void logAndProcess(T&& param)
{
    std::cout << "Enter logAndProcess func. \n";
    process(forward<T>(param));
}

int main(int argc, const char * argv[])
{
    // insert code here...
    
    // std::move
    std::string str = "Hello";
    std::vector<std::string> v;
    
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
 
    v.push_back(Move(str));
    
    std::cout << "After move, str is \"" << str << "\"\n";
    std::cout << "The contents of the vector are \"" << v[0] << "\", \"" << v[1] << "\"\n";
    
    // string move assignment operator is often implemented as swap,
    // in this case, the moved-from object is NOT empty
    std::string str2 = "Good-bye";
    std::cout << "Before move from str2, str2 = '" << str2 << "'\n";
    v[0] = Move(str2);
    std::cout << "After move from str2, str2 = '" << str2 << "'\n";
    std::cout << "After move from str2, str2 = '" << v[0] << "'\n";
    
    std::string s1("Hello");
    Annotation a1(s1);
    std::cout << "After move, s1 is \"" << s1 << "\"\n";
    
    
    // std::forward
    
    Widget a;
    //forward<Widget&> (std::move(a));     // It fails at "template argument substituting _Tp is an lvalue reference type."
    forward<Widget> (std::move(a));     // It fails at "template argument substituting _Tp is an lvalue reference type."
    
    Widget w;
    logAndProcess(w);
    logAndProcess(std::move(w));
    
    Widget w1(std::move(w));
    
    std::cout << "Hello, World!\n";
    return 0;
}
