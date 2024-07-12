// matrix_interface.hpp
// 
// Interface for an output of incrementally varying parameters and results stored in a matrix
//
// @author Mark Bogorad
// @version 1.0 

#ifndef MATRIX_INTERFACE_HPP
#define MATRIX_INTERFACE_HPP

#include "interfaces.hpp"
#include "european_option.hpp"
#include "american_option.hpp"
#include "asian_option.hpp"
#include <vector>
#include <string>

class matrix_interface : public interfaces {
public:
    matrix_interface(const std::string& variable_to_vary, double begin, double end, double h);
    void display_results() override; // Main function to run the interface

private:
    void console_pricing();
    void display_greeks(const european_option& opt);
    void check_put_call_parity(const european_option& opt, double other_option_price);
    void calculate_and_check_parity(const european_option& opt);
    void set_parameters(double value);
    void generate_varying_values(double begin, double end, double h);
    void print_results_matrix();

    // Variables
    std::string variable_to_vary;
    std::vector<double> varying_values;
    std::vector<std::vector<double>> results_matrix;
    std::vector<std::vector<double>> american_results_matrix;

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

#endif // MATRIX_INTERFACE_HPP
