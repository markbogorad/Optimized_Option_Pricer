// option.hpp
// 
// Serves as the base class for different option types, defining pure virtual pricing and toggle functions as well as the variable capturing option type.
// 
// @file Option.hpp
// @author Mark Bogorad
// @version 2.0 

#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>
#include <vector>

class option {
public:
    virtual double price() const = 0; // Pure virtual function for price
    virtual ~option() = default; // Will destroy all derived option class instances
    virtual void toggle () = 0; // to switch between calls and puts

    static const int CALL; // defining call options
    static const int PUT; // defining put options

    option(int option_type) : option_type(option_type) {} // Constructor for option type

protected:
    int option_type; // true if option is a call, false if it's a put
};

#endif // OPTION_HPP