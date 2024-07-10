// EuropeanOption.hpp
// 
// European Options: derived from Option abstract base class.
//
// @file EuropeanOption.hpp
// @author Mark Bogorad
// @version 2.0 

#include "option.hpp"
#include "pricing_methods.hpp"

#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

class european_option : public option {
    friend class pricing_methods;
public:
    european_option();
    european_option(double strike, double maturity, double spot, double rate, double volatility, double cost_of_carry, int option_type = 1);
    double price() const override;
    void toggle() override;

private:
    double strike;
    double maturity;
    double spot;
    double rate;
    double volatility;
    double cost_of_carry;
    pricing_methods pricer;
};

#endif // EUROPEAN_OPTION_HPP

