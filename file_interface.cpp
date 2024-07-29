// file_interface.cpp
// 
// Implementation of file interface. Designed to read parameters from options.txt 
//
// @author Mark Bogorad
// @version 1.0 

#include "file_interface.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // For formatted output
#include <memory> // For smart pointers

file_interface::file_interface() 
    : spot(1.0), strike(1.0), rate(1.0), volatility(1.0), maturity(1.0),
      cost_of_carry(0.0), option_type(1), call_put_type(1), nSimulations(10000), nTimeSteps(252) {
}

file_interface::file_interface(const std::string& filename) {
    read_parameters(filename);
}

void file_interface::read_parameters(const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, ':')) {
            std::string value;
            if (std::getline(iss, value)) {
                std::istringstream value_stream(value);
                if (key == "spot") value_stream >> spot;
                else if (key == "strike") value_stream >> strike;
                else if (key == "rate") value_stream >> rate;
                else if (key == "volatility") value_stream >> volatility;
                else if (key == "maturity") value_stream >> maturity;
                else if (key == "cost_of_carry") value_stream >> cost_of_carry;
                else if (key == "option_type") value_stream >> option_type;
                else if (key == "call_put_type") value_stream >> call_put_type;
                else if (key == "nSimulations") value_stream >> nSimulations;
                else if (key == "nTimeSteps") value_stream >> nTimeSteps;
            }
        }
    }
}

void file_interface::console_pricing() {
    std::unique_ptr<option> opt;

    if (option_type == 1) { // European
        auto european_opt = std::make_unique<european_option>(spot, strike, rate, maturity, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT);
        std::cout << std::fixed << std::setprecision(5); // Set precision for floating-point numbers
        std::cout << "Option Price: " << european_opt->price() << std::endl;
        display_greeks(*european_opt);
        calculate_and_check_parity(*european_opt);
    } else if (option_type == 2) { // American
        auto american_opt = std::make_unique<american_option>(spot, strike, rate, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT);
        std::cout << std::fixed << std::setprecision(5); // Set precision for floating-point numbers
        std::cout << "Option Price: " << american_opt->price() << std::endl;
    } else if (option_type == 3) { // Asian
        auto asian_opt = std::make_unique<asian_option>(spot, strike, rate, maturity, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT, nSimulations, nTimeSteps);
        std::cout << std::fixed << std::setprecision(5); // Set precision for floating-point numbers
        std::cout << "Option Price: " << asian_opt->price() << std::endl;
    } else {
        std::cerr << "Invalid option type selected." << std::endl;
        return;
    }
}

void file_interface::display_greeks(const european_option& opt) {
    std::cout << std::fixed << std::setprecision(5); // Set precision for floating-point numbers
    std::cout << "Delta: " << opt.delta() << std::endl;
    std::cout << "Gamma: " << opt.gamma() << std::endl;
    std::cout << "Vega: " << opt.vega() << std::endl;
    std::cout << "Theta: " << opt.theta() << std::endl;
    std::cout << "Rho: " << opt.rho() << std::endl;
}

void file_interface::check_put_call_parity(const european_option& opt, double other_option_price) {
    bool parity_holds = false;
    if (call_put_type == option::CALL) { // Call
        parity_holds = opt.pcp_check(opt.price(), other_option_price);
    } else { // Put
        parity_holds = opt.pcp_check(other_option_price, opt.price());
    }
    
    if (parity_holds) {
        std::cout << "Put-Call Parity holds." << std::endl;
    } else {
        std::cout << "Put-Call Parity does not hold." << std::endl;
    }
}

void file_interface::calculate_and_check_parity(const european_option& opt) {
    if (call_put_type == 1) { // Call
        double put_price = opt.pcp_put_price(opt.price());
        std::cout << "Resulting Put Price via Put-Call Parity: " << put_price << std::endl;
        check_put_call_parity(opt, put_price);
    } else { // Put
        double call_price = opt.pcp_call_price(opt.price());
        std::cout << "Resulting Call Price via Put-Call Parity: " << call_price << std::endl;
        check_put_call_parity(opt, call_price);
    }
}

void file_interface::display_results() {
    console_pricing();
}
