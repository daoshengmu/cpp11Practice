//
//  main.cpp
//  cpp11Item13
//
//  Item 13: Prefer const_iterators to iterators
//  - Prefer non-member versions of begin, end, rbegin
//
//  Created by Daosheng Mu on 9/13/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>
#include <vector>

void showIteratorItems( const std::vector<int>& values );

template <class C>
auto cbegin( const C& container )->decltype(std::begin(container))
{
    return std::begin(container);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //C++ 98
    std::vector<int>values;
    values.push_back(1980);
    values.push_back(1981);
    values.push_back(1983);
    values.push_back(2001);
    values.push_back(2002);
    
    showIteratorItems( values );
    
    std::cout << "\n\n" << std::endl;
    
    std::vector<int>::iterator it = std::find( values.begin(), values.end(), 1983 );
    values.insert( std::next(it), 2000 );
    
    showIteratorItems( values );
    
    typedef std::vector<int>::iterator IterT;
    typedef std::vector<int>::const_iterator ConstIterT;
    
    std::cout << "\n\n" << std::endl;
    
    ConstIterT ci = std::find( static_cast<ConstIterT>(values.begin()), static_cast<ConstIterT>(values.end()), 1983 );
    values.insert( static_cast<ConstIterT>(std::next(ci)), 1999 );
    
    showIteratorItems( values );
    
    std::cout << "\n\n" << std::endl;
    
    //C++ 11
    ConstIterT constIt = std::find( values.cbegin(), values.cend(), 1983 );
    //ConstIterT constIt = std::find( cbegin( values ), values.cend(), 1983 );  // Implement cbegin() in c++ 11
    
    values.insert( std::next( constIt ), 1998 );
    
    showIteratorItems( values );
    
    std::cout << "\n\n" << std::endl;
    
    // C++ 14
    // std::cbegin(), std::cend()
    
    std::cout << "Hello, World!\n";
    
    return 0;
}

void showIteratorItems( const std::vector<int>& values )
{
    for ( int n : values )
    {
        std::cout << "vector item: " << n << std::endl;
    }
}



