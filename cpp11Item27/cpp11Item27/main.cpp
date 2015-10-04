//
//  main.cpp
//  cpp11Item27
//
//  Item 27: Familiarize yourself with alternatives to overloading on universal references
//  - Abandon overloading
//    - Different function name
//    - Not working for constructor
//  - Pass by const T&
//    - Not efficient. (recall the literal string case)
//  - Pass by value
//    - If the copy must happened
//
//  Created by Daosheng Mu on 10/4/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

// Use Tag dispatch. Not working for constructor
template<typename T>
void logAndAddImp(T&& name, std::false_type)
{
    std::cout << "name is " << name << std::endl;
    std::cout << "logAndAddImp is not integral" << std::endl;
}

template<typename T>
void logAndAddImp(T&& name, std::true_type)
{
    std::cout << "name is " << name << std::endl;
    std::cout << "logAndAddImp is integral" << std::endl;
}

template<typename T>
void logAndAdd(T&& name)
{
    logAndAddImp(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
}

class Person
{
public:
    //template<typename T, typename = typename std::enable_if<!std::is_same<Person, T>::value>::type>
   // template<typename T, typename = typename std::enable_if<!std::is_same<Person, typename std::decay<T>::type>::value>::type>   // std::decay - remove const, reference or volatile
    template<typename T, typename = typename std::enable_if<!std::is_base_of<Person, typename std::decay<T>::type>::value && !std::is_integral<typename std::remove_reference<T>::type>::value>::type>   // std::decay - remove const, reference or volatile
    explicit Person(T&& n)
        :name(std::forward<T>(n))
    {
        std::cout << "Person move constructor" << std::endl;
    }
    
    explicit Person(int idx)
        :name(std::to_string(idx))
    {
        
    }
    
    explicit Person( const Person& )
    {
        std::cout << "Person copy constructor" << std::endl;
    }
    
    explicit Person()
    {
        std::cout << "Person constructor" << std::endl;
    }
    
private:
    std::string name;
};

class SpecialPerosn : public Person
{
public:
    SpecialPerosn(const SpecialPerosn& rhs)
    :Person(rhs)
    {
        
    }
    
    SpecialPerosn(SpecialPerosn&& rhs)
    :Person(std::move(rhs))
    {
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::string name("123");
    logAndAdd(name);
    std::cout << "name is " << name << std::endl;

    int k = 456;
    logAndAdd(k);
    std::cout << "name is " << k << std::endl;

    Person p("Nancy");
    auto cloneOfP(p);
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
