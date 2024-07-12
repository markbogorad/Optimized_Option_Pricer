// european_option.hpp
// 
// European Options: derived from option abstract base class.
//
// @author Mark Bogorad
// @version 2.0 

#include "option.hpp"
#include "pricing_methods.hpp"

#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

class european_option : public option {
    friend class pricing_methods; // friend of pricing_methods to use european option variables in the calculations
public:
    european_option();
    european_option(double S, double K, double r, double T, double sig, double b, int option_type);
    double price() const override;
    void toggle() override;
    
      // Put-Call Parity methods
    double pcp_call_price(double put_price) const;
    double pcp_put_price(double call_price) const;
    bool pcp_check(double call_price, double put_price) const;

    // Greeks
    double delta() const;
    double gamma() const;
    double vega() const;
    double theta() const;
    double rho() const;

private:
    double spot;
    double strike;
    double rate;
    double maturity;
    double volatility;
    double cost_of_carry;
    pricing_methods pricer;
};

#endif // EUROPEAN_OPTION_HPP

