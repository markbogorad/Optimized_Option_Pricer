// pricing_methods.cpp
// 
// Implementation of pricing methods for option type pricing, put-call parity, Greeks, and parameter checks
//
// @author Mark Bogorad
// @version 2.0

#include "pricing_methods.hpp"
#include <iostream>
#include <cmath>
#include <boost/math/distributions/normal.hpp>
#include <random>
#include <vector>

using namespace boost::math;

void pricing_methods::parameter_check(double S, double K, double r, double T, double sig, double b) {
    // Check for NaN
    if (std::isnan(S) || std::isnan(K) || std::isnan(r) || std::isnan(T) || std::isnan(sig) || std::isnan(b)) {
        throw std::invalid_argument("One or more parameters are NaN");
    }

    // Check for infinity
    if (std::isinf(S) || std::isinf(K) || std::isinf(r) || std::isinf(T) || std::isinf(sig) || std::isinf(b)) {
        throw std::invalid_argument("One or more parameters are infinity");
    }

    // Check realistic ranges
    if (r < 0 || r > 1 || b < 0 || b > 1) {
        throw std::invalid_argument("r and b must be between 0 and 1");
    }
    if (std::isnan(S) || std::isnan(K) || std::isnan(r) || std::isnan(T) || std::isnan(sig) || std::isnan(b)) {
        throw std::invalid_argument("Error: One or more parameters are NaN");
    }
    if (std::isinf(S) || std::isinf(K) || std::isinf(r) || std::isinf(T) || std::isinf(sig) || std::isinf(b)) {
        throw std::invalid_argument("Error: One or more parameters are infinity");
    }
    if (T <= 0) throw std::invalid_argument("Error: T must be positive");
    if (sig <= 0) throw std::invalid_argument("Error: sigma must be positive");
    if (r < 0 || r > 1) throw std::invalid_argument("Error: r must be between 0 and 1");
    if (b < 0 || b > 1) throw std::invalid_argument("Error: b must be between 0 and 1");
}

// European Option pricing

// D1:
double pricing_methods::d1 (double S, double K, double r, double T, double sig, double b) const {
    return (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
}

// D2:
double pricing_methods::d2 (double S, double K, double r, double T, double sig, double b) const {

    double d1Value = d1(S, K, r, T, sig, b); // Using d1Value for modularity and to make negative in put pricing (can't directly change scope of variable)
    return d1Value - (sig * sqrt(T));
} 

// Black-Scholes Call Price
double pricing_methods::price_european_call(double S, double K, double r, double T, double sig, double b) const {
    double d1Value = d1(S, K, r, T, sig, b);
    double d2Value = d2(S, K, r, T, sig, b);

    normal_distribution<> N(0, 1);
    return (S * exp((b - r) * T) * cdf(N, d1Value)) - (K * exp(-r * T) * cdf(N, d2Value));
}

// Black-Scholes Put Price
double pricing_methods::price_european_put(double S, double K, double r, double T, double sig, double b) const {
    
    double d1Value = d1(S, K, r, T, sig, b);
    double d2Value = d2(S, K, r, T, sig, b);
    normal_distribution<> N(0, 1);
    
    return (K * exp(-r * T) * cdf(N, -d2Value)) - (S * exp((b - r) * T) * cdf(N, -d1Value));
}

// Put-Call Parity pricing methods (for european_option only):
// Given a put, return a call
double pricing_methods::PCP_put_to_call(double S, double K, double r, double T, double p) const {
	return p + S - K * exp(-r * T); // Uses put (p) in calculation
}

// Given a call, return a put
double pricing_methods::PCP_call_to_put(double S, double K, double r, double T, double c) const { 
	return c + K * exp(-r * T) - S; // Uses call (c) in calculation
}

// Function to check if pcp holds
bool pricing_methods::PCP_check(double S, double K, double r, double T, double c, double p) const {
    double LHS = c + K * exp(-r * T); // Left hand side of Put-Call parity equation
    double RHS = p + S; // Right hand side of Put-Call parity equation
    const double Tolerance = 0.01; // Tolerance for rounding errors and other slight impercisions

    bool ParityHolds = std::abs(LHS - RHS) < Tolerance;
    if (ParityHolds) {
        std::cout << "Put-Call Parity Holds" << std::endl;
        return true;
    } else {
        std::cout << "Put-Call Parity doesn't hold!!" << std::endl;
        return false;
    }
}



// Greeks - only for european_option
// Delta for a Call option
double pricing_methods::delta_call(double S, double K, double r, double T, double sig, double b) const {
    normal_distribution<> N(0, 1);
    double d1Value = d1(S, K, r, T, sig, b);
    return exp((b - r) * T) * cdf(N, d1Value);
}

// Delta for a Put option
double pricing_methods::delta_put(double S, double K, double r, double T, double sig, double b) const {
    normal_distribution<> N(0, 1);
    double d1Value = d1(S, K, r, T, sig, b);
    return exp((b - r) * T) * (cdf(N, d1Value) - 1); // Key difference
}

// Gamma for both Call and Put options (Gamma is the same for both)
double pricing_methods::gamma(double S, double K, double r, double T, double sig, double b) const {
    normal_distribution<> N(0, 1);
    double d1Value = d1(S, K, r, T, sig, b);
    return pdf(N, d1Value) * exp((b - r) * T) / (S * sig * sqrt(T));
}

// Vega for both
double pricing_methods::vega(double S, double K, double r, double T, double sig, double b) const {
    return S * sqrt(T) * pdf(normal_distribution<>(0, 1), d1(S, K, r, T, sig, b));
}

// Theta for Call
double pricing_methods::theta_call(double S, double K, double r, double T, double sig, double b) const {
    double d1Value = d1(S, K, r, T, sig, b);
    double d2Value = d2(S, K, r, T, sig, b);
    double first_term = -S * pdf(normal_distribution<>(0, 1), d1Value) * sig / (2 * sqrt(T));
    double second_term = b * S * cdf(normal_distribution<>(0, 1), d1Value);
    double third_term = r * K * exp(-r * T) * cdf(normal_distribution<>(0, 1), d2Value);
    return first_term - second_term - third_term;
}

// Theta for Put
double pricing_methods::theta_put(double S, double K, double r, double T, double sig, double b) const {
    double d1Value = d1(S, K, r, T, sig, b);
    double d2Value = d2(S, K, r, T, sig, b);
    double first_term = -S * pdf(normal_distribution<>(0, 1), d1Value) * sig / (2 * sqrt(T));
    double second_term = b * S * cdf(normal_distribution<>(0, 1), -d1Value);
    double third_term = r * K * exp(-r * T) * cdf(normal_distribution<>(0, 1), -d2Value);
    return first_term + second_term + third_term;
}

// Rho for call
double pricing_methods::rho_call(double S, double K, double r, double T, double sig, double b) const {
    return K * T * exp(-r * T) * cdf(normal_distribution<>(0, 1), d2(S, K, r, T, sig, b));
}

// Rho for put
double pricing_methods::rho_put(double S, double K, double r, double T, double sig, double b) const {
    return -K * T * exp(-r * T) * cdf(normal_distribution<>(0, 1), -d2(S, K, r, T, sig, b));
}



// American option pricers:
// Y1 variable (for call)
double pricing_methods::y1(double K, double r, double sig, double b) const {
    return (0.5 - (b / (sig * sig)) + sqrt(pow((b / (sig * sig) - 0.5), 2) + (2 * r) / (sig * sig)));
}

// Y2 variable (for put)
double pricing_methods::y2(double K, double r, double sig, double b) const {
    return (0.5 - (b / (sig * sig)) - sqrt(pow((b / (sig * sig) - 0.5), 2) + (2 * r) / (sig * sig)));
}

// American Call Price
double pricing_methods::price_american_call(double S, double K, double r, double sig, double b) const {
    double y1Value = y1(K, r, sig, b);
    return ( (K / (y1Value - 1.0)) * pow(((y1Value - 1.0) / y1Value) * (S / K), y1Value) );
}

// American Put Price
double pricing_methods::price_american_put(double S, double K, double r, double sig, double b) const {
    double y2Value = y2(K, r, sig, b);
    return ( (K / (1.0-y2Value)) * pow(((y2Value - 1.0) / y2Value) * (S / K), y2Value) );
    
}




// Asian option pricing methods
// Function to simulate the path of the underlying asset price
std::vector<double> pricing_methods::random_walk(double S, double T, double r, double sig, int N, std::mt19937& rng) const {
    std::vector<double> path(N + 1);
    path[0] = S;
    std::normal_distribution<> dist(0.0, 1.0);  // Standard normal distribution

    double dt = T / N;  // Time increment
    for (int i = 1; i <= N; ++i) {
        double Z = dist(rng);  // Generate a standard normal random variable
        path[i] = path[i - 1] * std::exp((r - 0.5 * sig * sig) * dt + sig * std::sqrt(dt) * Z);
    }

    return path;
}

// Function to price an Asian call option using Monte Carlo simulation
double pricing_methods::price_asian_call(double S, double K, double T, double r, double sig, double b, int N, int M) const {
    double payoff_sum = 0.0;
    std::mt19937 rng(42); // Random seed for reproducibility

    for (int i = 0; i < M; ++i) {
        std::vector<double> path = random_walk(S, T, r, sig, N, rng);

        // Calculate the arithmetic average price
        double average_price = 0.0;
        for (int j = 1; j <= N; ++j) {
            average_price += path[j];
        }
        average_price /= N;

        // Calculate the payoff
        double payoff = std::max(0.0, average_price - K);
        payoff_sum += payoff;
    }

    // Discount the average payoff to present value
    return (payoff_sum / M) * std::exp(-r * T);
}

// Function to price an Asian put option using Monte Carlo simulation
double pricing_methods::price_asian_put(double S, double K, double T, double r, double sig, double b, int N, int M) const {
    double payoff_sum = 0.0;
    std::mt19937 rng(42); // Random seed for reproducibility

    for (int i = 0; i < M; ++i) {
        std::vector<double> path = random_walk(S, T, r, sig, N, rng);

        // Calculate the arithmetic average price
        double average_price = 0.0;
        for (int j = 1; j <= N; ++j) {
            average_price += path[j];
        }
        average_price /= N;

        // Calculate the payoff for the put option
        double payoff = std::max(0.0, K - average_price);
        payoff_sum += payoff;
    }

    // Discount the average payoff to present value
    return (payoff_sum / M) * std::exp(-r * T);
}
