// european_option.cpp
// 
// Implementation of European Option class
//
// @author Mark Bogorad
// @version 2.0 

#include "european_option.hpp"
#include "pricing_methods.hpp"

european_option::european_option()
    : spot(0), strike(0), rate(0), maturity(0), volatility(0), cost_of_carry(0), option(1) {}

european_option::european_option(double S, double K, double r, double T, double sig, double b, int option_type)
    : spot(S), strike(K), rate(r), maturity(T), volatility(sig), cost_of_carry(b), option(option_type) {
    this->option_type = option_type;
}

double european_option::price() const {
    if (option_type == CALL) {
        return pricer.price_european_call(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else if (option_type == PUT) {
        return pricer.price_european_put(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else {
        throw std::domain_error("Select 1 for call or 2 for put");
    }
}

void european_option::toggle() {
    option_type = (option_type == CALL) ? PUT : CALL;
}

// Put-Call Parity methods
double european_option::pcp_call_price(double put_price) const {
    return pricer.PCP_put_to_call(spot, strike, rate, maturity, put_price);
}

double european_option::pcp_put_price(double call_price) const {
    return pricer.PCP_call_to_put(spot, strike, rate, maturity, call_price);
}

bool european_option::pcp_check(double call_price, double put_price) const {
    return pricer.PCP_check(spot, strike, rate, maturity, call_price, put_price);
}

// Greeks
double european_option::delta() const {
    if (option_type == CALL) {
        return pricer.delta_call(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else if (option_type == PUT) {
        return pricer.delta_put(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else {
        throw std::domain_error("Select 1 for call or 2 for put");
    }
}


double european_option::gamma() const {
    return pricer.gamma(spot, strike, rate, maturity, volatility, cost_of_carry);
}

double european_option::vega() const {
    return pricer.vega(spot, strike, rate, maturity, volatility, cost_of_carry);
}

double european_option::theta() const {
    if (option_type == CALL) {
        return pricer.theta_call(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else if (option_type == PUT) {
        return pricer.theta_put(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else {
        throw std::domain_error("Select 1 for call or 2 for put");
    }
}

double european_option::rho() const {
     if (option_type == CALL) {
        return pricer.rho_call(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else if (option_type == PUT) {
        return pricer.rho_put(spot, strike, rate, maturity, volatility, cost_of_carry);
    } else {
        throw std::domain_error("Select 1 for call or 2 for put");
    }
}
