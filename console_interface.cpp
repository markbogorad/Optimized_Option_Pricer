#include "console_interface.hpp"
#include <iostream>
#include <memory> // For smart pointers
#include "option.hpp"
#include "european_option.hpp"
#include "american_option.hpp"
#include "asian_option.hpp"

void console_interface::display_options() {
    std::cout << "Select Option Type:" << std::endl;
    std::cout << "1. European" << std::endl;
    std::cout << "2. American" << std::endl;
    std::cout << "3. Asian" << std::endl;
}

void console_interface::display_call_put() {
    std::cout << "Select Call/Put Type:" << std::endl;
    std::cout << "1. Call" << std::endl;
    std::cout << "2. Put" << std::endl;
}

void console_interface::enter_parameters() {
    std::cout << "Enter spot price: ";
    std::cin >> spot;
    std::cout << "Enter strike price: ";
    std::cin >> strike;
    std::cout << "Enter risk-free rate: ";
    std::cin >> rate;

    if (option_type == 1 || option_type == 3) { 
        std::cout << "Enter maturity: ";
        std::cin >> maturity;
    }

    std::cout << "Enter volatility: ";
    std::cin >> volatility;
    std::cout << "Enter cost of carry (e.g., 0 for futures, risk-free rate for stock options): ";
    std::cin >> cost_of_carry;

    if (option_type == 3) { // Asian
        std::cout << "Entering Monte-Carlo Simulation" << std::endl;
        std::cout << "Enter number of simulations: ";
        std::cin >> nSimulations;
        std::cout << "Enter number of time steps: ";
        std::cin >> nTimeSteps;
    }
}

void console_interface::console_pricing() {
    std::unique_ptr<option> opt;

    if (option_type == 1) { // European
        auto european_opt = std::make_unique<european_option>(spot, strike, rate, maturity, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT);
        std::cout << "Option Price: " << european_opt->price() << std::endl;
        display_greeks(*european_opt);
        calculate_and_check_parity(*european_opt);
    } else if (option_type == 2) { // American
        opt = std::make_unique<american_option>(spot, strike, rate, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT);
        std::cout << "Option Price: " << opt->price() << std::endl;
    } else if (option_type == 3) { // Asian
        opt = std::make_unique<asian_option>(spot, strike, rate, maturity, volatility, cost_of_carry, (call_put_type == 1) ? option::CALL : option::PUT, nSimulations, nTimeSteps);
        std::cout << "Option Price: " << opt->price() << std::endl;
    } else {
        std::cerr << "Invalid option type selected." << std::endl;
        return;
    }
}

void console_interface::display_greeks(const european_option& opt) {
    std::cout << "Delta: " << opt.delta() << std::endl;
    std::cout << "Gamma: " << opt.gamma() << std::endl;
    std::cout << "Vega: " << opt.vega() << std::endl;
    std::cout << "Theta: " << opt.theta() << std::endl;
    std::cout << "Rho: " << opt.rho() << std::endl;
}

void console_interface::check_put_call_parity(const european_option& opt, double other_option_price) {
    bool parity_holds = false;
    if (call_put_type == option::CALL) { // Call
        parity_holds = opt.pcp_check(opt.price(), other_option_price);
    } else { // Put
        parity_holds = opt.pcp_check(other_option_price, opt.price());
    }
    
}

void console_interface::calculate_and_check_parity(const european_option& opt) {
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

void console_interface::display_results() {
    display_options();
    std::cin >> option_type;

    display_call_put();
    std::cin >> call_put_type;

    enter_parameters();
    console_pricing();
}
