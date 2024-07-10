// european_option.cpp
// Level 9 Group A
// 
// Implementation of European Option class
//
// @file Option.hpp
// @author Mark Bogorad
// @version 2.0 

#include "european_option.hpp"
#include "pricing_methods.hpp"

european_option::european_option()
    : option(1), strike(0), maturity(0), spot(0), rate(0), volatility(0) {}

european_option::european_option(double K, double T, double S, double r, double sig, double b, int option_type)
    : strike(K), maturity(T), spot(S), rate(r), volatility(sig), cost_of_carry(b), option(option_type) {
    this->option_type = option_type;
}

double european_option::price() const {
    if (option_type == CALL) {
        return pricer.price_european_call(strike, maturity, spot, rate, volatility, cost_of_carry);
    } else if (option_type == PUT) {
        return pricer.price_european_put(strike, maturity, spot, rate, volatility, cost_of_carry);
    } else {
        throw std::domain_error("Select 1 for call or 2 for put");
    }
}

void european_option::toggle() {
    option_type = (option_type == CALL) ? PUT : CALL;
}


/*
// Option Price
double EuropeanOption::Price() const {
    // Sanity check
    if (S <= 0 || K <= 0 || sigma <= 0 || T <= 0) {
        throw std::domain_error("Invalid input: All input values must be positive.");
    }
    // Then point to BSPricer to calculate the price
    if (option_type == 1) {
        return BS->CallPrice(S, K, r, T, sigma, b, option_type);
    } else if (option_type == 2) {
        return BS->PutPrice(S, K, r, T, sigma, b, option_type);
    }
    else {
        throw std::domain_error("Select 1 for call 2 for put"); // Throw error if neither 1 or 2 is selected
    }
}

double EuropeanOption::PCP_Price() const {
    // Sanity check
    if (S <= 0 || K <= 0 || sigma <= 0 || T <= 0) {
        throw std::domain_error("Invalid input: All input values must be positive.");
    }

     // Calculate call and put prices directly using BSPricer. Needed 
    double c = BS->CallPrice(S, K, r, T, sigma, b, option_type);
    double p = BS->PutPrice(S, K, r, T, sigma, b, option_type);

    // Use put-call parity to check or calculate the other price
    // Assuming option_type indicates which price to return based on PCP
    if (option_type == 1) {
        // Calculate and return put price from known call price using PCP formula
        return BS->PCP_CallPrice(S, K, r, T, p);
    } else if (option_type == 2) {
        // Calculate and return call price from known put price using PCP formula
        return BS->PCP_PutPrice(S, K, r, T, c);
    }
    else {
        throw std::domain_error("Select 1 for call 2 for put");
    }
}

*/