// parameter_generator.hpp
// 
// Serves as the base class for different option types, holding key option parameters and defining the price interface.
// 
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 
#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <vector>

class interfaces {
public:
    virtual void display_results() = 0;
    virtual ~interfaces() = default;
protected:
    interfaces() = default; // Default constructor

};

#endif // INTERFACES_HPP
