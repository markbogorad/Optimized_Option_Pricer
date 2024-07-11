// AsianOption.hpp
// 
// asian_option header file, derived from option base class
//
// @author Mark Bogorad
// @version 1.0 

#include "option.hpp"
#include "pricing_methods.hpp"

#ifndef ASIAN_OPTION_HPP
#define ASIAN_OPTION_HPP

class asian_option : public option {
    friend class pricing_methods; // friend of pricing_methods to use european option variables in the calculations
public:
    asian_option();
    asian_option(double strike, double maturity, double spot, double rate, double volatility, double cost_of_carry, int n_simulations, int n_time_steps, int option_type = 1);
    double price() const override;
    void toggle() override;

private:
    double strike;
    double spot;
    double rate;
    double volatility;
    double maturity;
    double cost_of_carry;
    int n_simulations;
    int n_time_steps;
    pricing_methods pricer;
};

#endif // ASIAN_OPTION_HPP