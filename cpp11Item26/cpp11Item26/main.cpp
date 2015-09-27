//
//  main.cpp
//  cpp11Item26
//
//  Item 26: Avoid overloading on universal references
//  - Functions taking universal references are the greediest functions in C++.
//  - Perfect-forwarding constructors are especially problematic.
//    - They’re typically better matches than copy constructors for non-const lvalues.
//    - They can hijack derived class calls to base class copy and move constructors.
//
//  Created by Daosheng Mu on 9/27/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>

template<typename T>
void logAndAdd(T&& name)
{
    std::cout << "Universal reference overload." << std::endl;
    std::cout << name << std::endl;
}

void logAndAdd(int log)
{
    std::cout << "int overload." << std::endl;
    std::cout << log << std::endl;
}

class Person
{
public:
    template<typename T>
    explicit Person(T&& n)
     //   :person(std::forward<T>(n))
    {
        std::cout << "Universal reference constructor" << std::endl;
    }
    
    explicit Person(Person& n)             // instantiated from
   // : name(std::forward<Person&>(n))      // perfect-forwarding template
    {}
    
    explicit Person(Person&& p)
       // :name(std::forward<Person&>(p))
    {
        
    }
    
    explicit Person(int idx)
        :name(std::to_string(idx))
    {
        std::cout << "int constructor" << std::endl;
    }
    
private:
    std::string name;
};

class BigObject
{
public:
    template<typename T>
    BigObject(T&& n)
    {
        std::cout << "Universal reference constructor" << std::endl;
    }
    
    BigObject(const BigObject&)
    {
        std::cout << "const copy constructor" << std::endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::string petName("Darla");
    logAndAdd(petName);
    logAndAdd(22);
    
    // Functions taking universal references are the greediest functions in C++.
    short shortVar = 16;
    logAndAdd(shortVar);

    std::cout << "Perfect forwarding." << std::endl;
    Person p("Nancy");
    auto cloneOfP(p);
    
    std::cout << "Overloading test." << std::endl;
    BigObject ob("test");
    auto copy(ob);
    const BigObject cobj("test");
    auto copy1(cobj);

    std::cout << "Hello, World!\n";
    return 0;
}
