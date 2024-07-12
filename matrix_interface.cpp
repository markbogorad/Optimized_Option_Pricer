// matrix_interface.cpp
// 
// Implementation of matrix interface
//
// @author Mark Bogorad
// @version 1.0 

#include "matrix_interface.hpp"
#include <iostream>
#include <iomanip> // For formatted output
#include <memory> // For smart pointers

matrix_interface::matrix_interface(const std::string& variable_to_vary, double begin, double end, double h) 
    : variable_to_vary(variable_to_vary) {
    // Hardcoded values for other parameters
    spot = 110.0;
    strike = 100.0;
    rate = 0.1;
    volatility = 0.1;
    maturity = 1.0; // 1 year
    cost_of_carry = 0.02;
    option_type = 2; // 1: European, 2: American, 3: Asian
    call_put_type = 1; // 1: Call, 2: Put
    nSimulations = 10000;
    nTimeSteps = 252;

    // Generate varying values
    generate_varying_values(begin, end, h);
}

void matrix_interface::generate_varying_values(double begin, double end, double h) {
    for (double value = begin; value <= end; value += h) {
        varying_values.push_back(value);
    }
}

void matrix_interface::set_parameters(double value) {
    if (variable_to_vary == "spot") {
        spot = value;
    } else if (variable_to_vary == "strike") {
        strike = value;
    } else if (variable_to_vary == "rate") {
        rate = value;
    } else if (variable_to_vary == "volatility") {
        volatility = value;
    } else if (variable_to_vary == "maturity") {
        maturity = value;
    } else if (variable_to_vary == "cost_of_carry") {
        cost_of_carry = value;
    }
}

void matrix_interface::console_pricing() {
    results_matrix.clear();
    american_results_matrix.clear();

    for (double value : varying_values) {
        set_parameters(value);

        std::unique_ptr<option> opt;
        double price = 0.0;

        if (option_type == 1) { // European
            auto european_opt = std::make_unique<european_option>(spot, strike, rate, maturity, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT);
            price = european_opt->price();
            double delta = european_opt->delta();
            double gamma = european_opt->gamma();
            double vega = european_opt->vega();
            double theta = european_opt->theta();
            double rho = european_opt->rho();
            double pcp_price = 0.0;
            if (call_put_type == 1) {
                pcp_price = european_opt->pcp_put_price(price);
            } else {
                pcp_price = european_opt->pcp_call_price(price);
            }
            results_matrix.push_back({value, price, delta, gamma, vega, theta, rho, pcp_price});
        } else if (option_type == 2) { // American
            auto american_opt = std::make_unique<american_option>(spot, strike, rate, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT);
            price = american_opt->price();
            american_results_matrix.push_back({value, price});
        } else if (option_type == 3) { // Asian
            auto asian_opt = std::make_unique<asian_option>(spot, strike, rate, maturity, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT, nSimulations, nTimeSteps);
            price = asian_opt->price();
            results_matrix.push_back({value, price});
        } else {
            std::cerr << "Invalid option type selected." << std::endl;
            return;
        }
    }

    print_results_matrix();
}

void matrix_interface::print_results_matrix() {
    if (option_type == 2) { // American option
        std::cout << std::setw(15) << "Varying Value" 
                  << std::setw(15) << "Option Price" 
                  << std::endl;
        for (const auto& row : american_results_matrix) {
            for (double val : row) {
                std::cout << std::setw(15) << val;
            }
            std::cout << std::endl;
        }
    } else { // European and Asian options
        std::cout << std::setw(15) << "Varying Value" 
                  << std::setw(15) << "Option Price" 
                  << std::setw(10) << "Delta" 
                  << std::setw(10) << "Gamma" 
                  << std::setw(10) << "Vega" 
                  << std::setw(10) << "Theta" 
                  << std::setw(10) << "Rho" 
                  << std::setw(15) << "PCP Price" 
                  << std::endl;
        for (const auto& row : results_matrix) {
            for (double val : row) {
                std::cout << std::setw(15) << val;
            }
            std::cout << std::endl;
        }
    }
}

void matrix_interface::display_results() {
    console_pricing();
}
