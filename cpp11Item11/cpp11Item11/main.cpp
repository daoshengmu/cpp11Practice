//
//  main.cpp
//  cpp11Item11
//
//  Item 11: Deleted functions
//  - Prefer deleted functions to private undefined ones
//  - Can forbid functions in public scopes, better for compile-error information
//  - Can forbid friend classes
//  - Can forbid unwanted implicit cast
//
//  Created by Daosheng Mu on 9/5/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>


#define DISALLOW_COPY_AND_ASSIGN_CONSTRUCTORS( ClassName ) \
    ClassName( const ClassName& ); \
    ClassName& operator = ( const ClassName& );

class MyClass {
    
public:
    MyClass()
    {
        
    }
    
private:
    DISALLOW_COPY_AND_ASSIGN_CONSTRUCTORS( MyClass );
};

class MyDelClass {
    
public:
    MyDelClass() = default;
    MyDelClass( const MyDelClass& ) = delete;
    MyDelClass& operator=( const MyDelClass& ) = delete;
    
    void isAcceptable( int val )
    {
        std::cout << "input value is " << val << std::endl;
    }
    
    void isAcceptable( float val ) = delete;
    void isAcceptable( char val ) = delete;
    void isAcceptable( bool val ) = delete;
    
    template<typename T>
    void processPointer( T* val )
    {
        std::cout << "process pointer value in class " << val << std::endl;
    }
    
private:              
//    template<>                                  // Error
//    void processPointer<void>( void* val ) = delete;
};

template<>
void MyDelClass::processPointer<void>( void* ) = delete;
template<>
void MyDelClass::processPointer<MyClass>( MyClass* val ) = delete;


template<typename T>
void processPointer( T* val )
{
    std::cout << "process pointer value " << val << std::endl;
}

template<>
void processPointer<void>( void* val ) = delete;

template<>
void processPointer<MyClass>( MyClass* val ) = delete;


int main(int argc, const char * argv[]) {
    // insert code here...
    MyClass a;
//    MyClass b(a);
//    MyClass c = a;
    
    MyDelClass a1;
//    MyClass b1(a1);
//    MyDelClass c1 = a1;
    a1.isAcceptable( 10 );
//    a1.isAcceptable( 10.345 );    // implicit-cast is disable.
//    a1.isAcceptable( 'c' );       // implicit-cast is disable.
//    a1.isAcceptable( true );      // implicit-cast is disable.
    
    const char* str = "I'm fool";
    processPointer( str );
    
    MyClass* obj = new MyClass();
//    processPointer( obj );        // This template type is disable
    delete obj;
    
    void* vPtr = nullptr;
//    processPointer( vPtr );       // This template type is disable
    
    a1.processPointer( str );
//    a1.processPointer( obj );     // This template type is disable
//    a1.processPointer( vPtr );    // This template type is disable
    
    std::cout << "Hello, World!\n";
    
    return 0;
}

