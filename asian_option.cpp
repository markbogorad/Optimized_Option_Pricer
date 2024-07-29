// asian_option.hpp
// 
// Implementation of asian_option. Priced using a monte-carlo simulation to get average price under a random walk (in pricing_methods)
//
// @author Mark Bogorad
// @version 1.0 

#include "asian_option.hpp"
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <vector>

asian_option::asian_option() : option(1), strike(0), maturity(0), spot(0), rate(0), volatility(0), cost_of_carry(0), n_simulations(10000), n_time_steps(252) {}

asian_option::asian_option(double K, double T, double S, double r, double sig, double b, int option_type, int nSimulations, int nTimeSteps)
    : strike(K), maturity(T), spot(S), rate(r), volatility(sig), cost_of_carry(b), option(option_type), n_simulations(nSimulations), n_time_steps(nTimeSteps) {}

double asian_option::price() const {
 if (option_type == CALL) {
        return pricer.price_asian_call(strike, maturity, spot, rate, volatility, cost_of_carry, n_simulations, n_time_steps);
    } else if (option_type == PUT) {
        return pricer.price_asian_put(strike, maturity, spot, rate, volatility, cost_of_carry, n_simulations, n_time_steps);
    } else {
        throw std::domain_error("Invalid option type. Select 1 for Asian call or 2 for Asian put.");
    }
}

void asian_option::toggle() {
    option_type = (option_type == option::CALL) ? option::PUT : option::CALL;
}
