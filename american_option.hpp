// american_option.hpp
// 
// American Options: derived from Option abstract base class.
//
// @file EuropeanOption.hpp
// @author Mark Bogorad
// @version 2.0 

#ifndef AMERICAN_OPTION_HPP
#define AMERICAN_OPTION_HPP

#include "option.hpp"
#include "pricing_methods.hpp"

class american_option : public option {
    friend class pricing_methods;
public:
    american_option();
    american_option(double strike, double spot, double rate, double volatility, double cost_of_carry, int option_type = 1);
    double price() const override;
    void toggle() override;

private:
    double strike;
    double spot;
    double rate;
    double volatility;
    double cost_of_carry;
    pricing_methods pricer;
};

#endif // AMERICAN_OPTION_HPP