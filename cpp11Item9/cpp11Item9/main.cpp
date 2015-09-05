//
//  main.cpp
//  cpp11Item9
//
// Item 9: Type alias
// Prefer alias (using) declaration to typedefs
// typedef doesn't support template
//
//  Created by Daosheng Mu on 9/5/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSSType;
using UPtrMapSSAlias = std::unique_ptr<std::unordered_map<std::string, std::string>>;

template <typename T>
class MyWidget{
    
public:
    T a;
};


//template<typename T>
//std::list<T, MyWidget<T>> stdList;   // vaiable templates only supports in C++14

// Workaroud for supporing template in typedef
template <typename T>
struct MyAllocList {
    typedef std::list<T> type;
};

template <typename T>
class MyAllocListClass {
    
private:
    typename MyAllocList<T>::type list;
    
    enum class WineType{ white, red };
    WineType type;
};

template <typename T>
using AliasStdList = std::list<T>;
using AliasStdListInt = AliasStdList<int>;

template <typename T>
using remove_const_t = typename std::remove_const<T>::type;

// Typedef not support template
//template <typename T>
//typedef std::list<T> typeStdList;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    AliasStdListInt list;
    list.push_front( 1 );
    list.push_front( 2 );
    
    MyAllocList<int>::type typeStdListInt;
    typeStdListInt.push_front( 1 );

    
    MyAllocListClass<int> typeStdListClassInt;
    
    std::cout << "Hello, World!\n";
    return 0;
}
