//
//  main.cpp
//  cpp11Item8
//
//  Item 8: Prefer nullptr to 0 and NULL.
//
//  Use nullptr!!
//
//  Created by Daosheng Mu on 8/20/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>


void f( int )
{
    std::cout << "f() int " << std::endl;
}

void f( bool )
{
    std::cout << "f() bool " << std::endl;
}

void f( void * )
{
    std::cout << "f() void * " << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    if ( 0 )
    {
        std::cout << "0 do something..." << std::endl;
    }
    
    if ( NULL )
    {
        std::cout << "NULL do something..." << std::endl;
    }
    
    if ( nullptr )
    {
        std::cout << "nullptr do something..." << std::endl;
    }
    
    f( 0 );
    //f( NULL ); // clang++ can't support it.
    f( nullptr );
    
    // Use nullptr !!
    
    return 0;
}
