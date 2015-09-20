//
//  main.cpp
//  cpp11Item24
//
//  Item 24: Distinguish universal references from rvalue references
//  - Universal references can bind to const or non-const objects, to volatile or non-volatile objects, even to objects that are both const and volatile. They can bind to virtually anything.
//  - A function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the parameter or object is a universal reference.
//  - If the form of the type declaration isn’t precisely type&&, or if type deduction does not occur, type&& denotes an rvalue reference.
//  - Universal references correspond to rvalue references if they’re initialized with rvalues. They correspond to lvalue references if they’re initialized with lvalues.
//
//  Created by Daosheng Mu on 9/20/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <vector>

template<typename T>
void f(T&& param)   // param is an universal reference. Deduction happened
{
    
}

class Widget
{
    
};

void f(Widget&& param)  // param is a rvalue reference. No deduction
{
    
}

template <typename T>
void f(const T&& param) // param is a rvalue reference.
{
    
}

class President
{
public:
    std::string name;
    std::string country;
    int year;
    
    President(std::string p_name, std::string p_country, int p_year)
        :name(p_name), country(p_country), year(p_year)
    {
        std::cout << "I am being constructed." << std::endl;
        std::cout << "Name:" << name << std::endl;
    }
    
    President(const President& in) // Copy construtor
        :name(in.name), country(in.country), year(in.year)
    {
        std::cout << "I am being copy-constructed." << std::endl;
        std::cout << "Name:" << name << std::endl;
    }
    
    President(President&& in) noexcept
        : name(std::move(in.name)), country(std::move(in.country)), year(std::move(in.year))
    {
        std::cout << "I am being move-constructed." << std::endl;
        std::cout << "Name:" << name << std::endl;
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    int var1 = 10;
    auto&& var2 = var1; // var2 is an universal reference. Deduction happened
    
    // Rvalue reference
    Widget&& val3 = Widget();   // val3 is a rvalue reference. No deduction
    
    
    std::vector<President> elections;

    std::cout << "\n";
    std::cout << "push_back\n";
    
    President p1("Kyle", "Japan", 1960);
    President&& p2 = President("Mike", "Korean", 1960);
    
    // push_back construct then call copy or move
    elections.push_back(p1);
    elections.push_back(p2);    // push_back will allocate new buffer for new item. Therefore, old items have to be copied again.
    
    std::cout << "\n";
    std::cout << "emplace_back\n";
    elections.emplace_back("Jason", "the United States", 1940);
    elections.emplace_back("Herry", "Norway", 1970);

    std::cout << "Size is: " << elections.size() << std::endl;
    std::cout << elections[3].name << std::endl;
    
    std::cout << "\n";
    std::cout << "Hello, World!\n";
    return 0;
}
