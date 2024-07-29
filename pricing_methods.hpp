// picing_methods.hpp
//
// pricing_methods header file
// 
// @author Mark Bogorad
// @version 2.0

#ifndef PRICING_METHODS_HPP
#define PRICING_METHODS_HPP

#include "option.hpp"
#include <iostream>
#include <vector>
#include <random>

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
    double PCP_put_to_call(double S, double K, double r, double T, double p) const; // Put-call parity (PCP) price for CALL (given put get call price)
    double PCP_call_to_put(double S, double K, double r, double T, double c) const; // Put-call parity price for PUT (given put get call)
    bool PCP_check(double S, double K, double r, double T, double c, double p) const; // Check for put-call parity relationship holding  

// Greeks functions (not making a seperate class for these because they use BS pricing variables and are basically an extension of BS)
    // Delta for call and put
    double delta_call(double S, double K, double r, double T, double sig, double b) const; 
    double delta_put(double S, double K, double r, double T, double sig, double b) const;  
    // Gamma
    double gamma(double S, double K, double r, double T, double sig, double b) const; 
    // Vega
    double vega(double S, double K, double r, double T, double sig, double b) const;
    // Theta for call and put
    double theta_call(double S, double K, double r, double T, double sig, double b) const;
    double theta_put(double S, double K, double r, double T, double sig, double b) const;
    // Rho for call and put
    double rho_call(double S, double K, double r, double T, double sig, double b) const;
    double rho_put(double S, double K, double r, double T, double sig, double b) const;

// Black-Scholes for American options formulae
    double y1(double K, double r, double sig, double b) const;
    double y2(double K, double r, double sig, double b) const;
    double price_american_call(double S, double K, double r, double sig, double b) const;
    double price_american_put(double S, double K, double r, double sig, double b) const;

// Black-Scholes for Asian options simulated with Monte-Carlo
    std::vector<double> random_walk(double S, double T, double r, double sig, int N, std::mt19937& rng) const;
    double price_asian_call(double S, double K, double T, double r, double sig, double b, int N, int M) const;
    double price_asian_put(double S, double K, double T, double r, double sig, double b, int N, int M) const;

};

#endif // PRICING_METHODS_HPP