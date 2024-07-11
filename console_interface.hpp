#ifndef CONSOLE_INTERFACE_HPP
#define CONSOLE_INTERFACE_HPP

#include "interfaces.hpp"
#include "european_option.hpp"

class console_interface : public interfaces {
public:
    void display_results() override;

private:
    void display_options();
    void display_call_put();
    void enter_parameters();
    void console_pricing();
    void display_greeks(const european_option& opt);
    void check_put_call_parity(const european_option& opt, double other_option_price);
    void calculate_and_check_parity(const european_option& opt);

    int option_type;
    int call_put_type;
    double strike, spot, rate, volatility, maturity, cost_of_carry;
    int nSimulations;
    int nTimeSteps;
};

#endif // CONSOLE_INTERFACE_HPP

