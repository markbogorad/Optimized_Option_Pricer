// BSPricer.hpp
//
// Black-Scholes calculation methods: Pricing for call/put, Put-Call parity pricing, Put-Call parity holding, Greeks
// 
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 02/04/2024

#ifndef PRICING_METHODS_HPP
#define PRICING_METHODS_HPP

#include "option.hpp"
#include <iostream>

class pricing_methods {
public:
// Parameter sanity check function
    void parameter_check(double S, double K, double r, double T, double sig, double b);

// Black-Scholes for European options formulae
    double d1(double S, double K, double r, double T, double sig, double b) const; // BS D1 parameter
    double d2(double S, double K, double r, double T, double sig, double b) const; //BS D2 parameter
    double price_european_call(double S, double K, double r, double T, double sig, double b) const;
    double price_european_put(double S, double K, double r, double T, double sig, double b) const;

// European option put-call parity functions
    double euro_pcp_call_price(double S, double K, double r, double T, double p) const; // Put-call parity (PCP) price for CALL (given put get call price)
    double euro_pcp_put_price(double S, double K, double r, double T, double c) const; // Put-call parity price for PUT (given put get call)
    bool euro_pcp_check(double S, double K, double r, double T, double c, double p) const; // Check for put-call parity relationship holding  

// Greeks functions (not making a seperate class for these because they use BS pricing variables and are basically an extension of BS)
    // Delta
    double euro_call_delta(double S, double K, double r, double T, double sig, double b) const; 
    double euro_put_delta(double S, double K, double r, double T, double sig, double b) const;  
    // Gamma
    double euro_gamma(double S, double K, double r, double T, double sig, double b) const; 

// Divided differences functions
    double divided_differences_delta_approx(double h) const; // Approximate Delta
    double divided_differences_gamma_approx(double h) const; // Approximate Gamma

// Black-Scholes for American options formulae
    double y1(double K, double r, double sig, double b) const;
    double y2(double K, double r, double sig, double b) const;
    double price_american_call(double S, double K, double r, double sig, double b) const;
    double price_american_put(double S, double K, double r, double sig, double b) const;

// Black-Scholes for Asian options simulated with Monte-Carlo

};

#endif // PRICING_METHODS_HPP