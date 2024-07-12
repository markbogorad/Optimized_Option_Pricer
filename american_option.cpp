// american_option.hpp
// 
// American option class implementation
//
// @author Mark Bogorad
// @version 2.0 

#include "american_option.hpp"
#include "pricing_methods.hpp"
#include <stdexcept>

// Default constructor
american_option::american_option()
    : spot(0), strike(0), rate(0), volatility(0), cost_of_carry(0), option(option::CALL) {}

// Parameterized constructor
american_option::american_option(double S, double K, double r, double sig, double b, int option_type)
    : spot(S), strike(K), rate(r), volatility(sig), cost_of_carry(b), option(option_type) {}

// Implementation of price method
double american_option::price() const {
    if (option_type == CALL) {
        return pricer.price_american_call(spot, strike, rate, volatility, cost_of_carry);
    } else if (option_type == PUT) {
        return pricer.price_american_put(spot, strike, rate, volatility, cost_of_carry);
    } else {
        throw std::domain_error("Invalid option type. Select 1 for American call or 2 for American put.");
    }
}

// Implementation of toggle method
void american_option::toggle() {
    option_type = (option_type == CALL) ? PUT : CALL;
}


const int option::CALL = 1;
const int option::PUT = 2;

