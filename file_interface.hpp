// file_interface.hpp
// 
// Reads option parameters from .txt file
//
// @author Mark Bogorad
// @version 1.0 

#ifndef FILE_INTERFACE_HPP
#define FILE_INTERFACE_HPP

#include "interfaces.hpp"
#include "european_option.hpp"
#include "american_option.hpp"
#include "asian_option.hpp"
#include <string>

class file_interface : public interfaces {
public:
    file_interface();
    file_interface(const std::string& filename);
    void display_results() override; // Main function to run the interface

private:
    void console_pricing();
    void display_greeks(const european_option& opt);
    void check_put_call_parity(const european_option& opt, double other_option_price);
    void calculate_and_check_parity(const european_option& opt);
    void read_parameters(const std::string& filename);

    // Variables
    double spot;
    double strike;
    double rate;
    double volatility;
    double maturity; // 1 year
    double cost_of_carry;
    int option_type; // 1: European, 2: American, 3: Asian
    int call_put_type; // 1: Call, 2: Put
    int nSimulations;
    int nTimeSteps;
};

#endif // FILE_INTERFACE_HPP
