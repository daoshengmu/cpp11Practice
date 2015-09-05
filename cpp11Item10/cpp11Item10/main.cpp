//
//  main.cpp
//  cpp11Item10
//
//  Item 10: Scoped enum
//
//  - Origin types in enum can't be refined
//  - No naming pollution
//  - No implicit cast
//  - Can be forward-declared
//
//  Created by Daosheng Mu on 9/5/15.
//  Copyright (c) 2015 Daosheng Mu. All rights reserved.
//

#include <iostream>


// Can't redefine the same type of enum
//enum SipStatus { eStatusNone, eStatusHold };
//enum HeadsetStatus { eStatusNone, eStatusHold };

enum class Color { white, red };
enum class Wine { white, red };

enum enumColor { white, red };

//enum Car;             // Can't forward-delcaration for enum
enum Car: std::uint8_t; // Give size of underlying type for unscoped enum can solve the problem.
enum class CarClass;

enum UserInfoFields { uName, uEmail, uReputation };
enum class UserInfoFieldsScoped { uName, uEmail, uReputation };

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Color c1 = Color::red;
    //Color c2 = Wine::red;     // It happens error
    //Color c3 = white;         // white is in Color:: scope
    enumColor c4 = white;       // using enumColor type is fine.
    
    // Using static_cast
    if ( static_cast<double>(c1) < 14.5 ) {
        std::cout << "success in static_cast loop." << std::endl;
    }
    
    using UserInfo = std::tuple<std::string, std::string, std::size_t>;
    UserInfo userInfo;
    auto val = std::get<uEmail>(userInfo);
    auto valScoped = std::get<static_cast<size_t>(UserInfoFieldsScoped::uEmail)>(userInfo);
    
    std::cout << "Hello, World!\n";
    return 0;
}
