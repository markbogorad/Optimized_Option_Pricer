
---

# **Optimized Option Pricer**

![C++](https://img.shields.io/badge/C++-20-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-green)
![Monte Carlo](https://img.shields.io/badge/Monte%20Carlo-Simulation-yellow)
![Numerical Methods](https://img.shields.io/badge/Numerical%20Methods-Crank--Nicolson-orange)

---

## **About**  
An advanced C++ application for option pricing, building on previous work to enhance speed, modularity, and scalability. This project supports European, American, and Asian options using the Black-Scholes model, numerical methods, and Monte Carlo simulations. It includes four user interfaces and is designed for performance and precision in option valuation.  

---

## **UML Diagram**  
The class structure and design dependencies are captured in the following UML diagram:

![UML Diagram](UML.png)

---

## **Demo**  
Watch the full demo of the project:  

[![Optimized Option Pricer Demo](https://img.youtube.com/vi/MLFRqJ9nKtE/0.jpg)](https://youtu.be/MLFRqJ9nKtE)  
*Click the thumbnail to watch the video.*

---

## **Features**
- **Pricing Models**:
  - European and American perpetual options priced via Black-Scholes and numerical methods.
  - Asian options priced using Monte Carlo simulations for average price movement replication.
- **Interfaces**:
  - Multiple user interfaces for flexibility in input handling and interaction.
- **Optimizations**:
  - Modular design for improved maintainability and scalability.
  - Focus on performance, leveraging efficient algorithms and data structures.

---

## **Structure**
- **Core Classes**:
  - `european_option`, `american_option`, `asian_option`: Implement pricing logic for different option types.
- **Interfaces**:
  - Includes console-based and file-based interaction for user inputs and outputs.
- **Numerical Methods**:
  - Implements Crank-Nicolson and other techniques for solving partial differential equations.

---

## **Usage**  
### **Compilation**
1. Clone the repository:
   ```bash
   git clone https://github.com/markbogorad/Optimized_Option_Pricer.git
   cd Optimized_Option_Pricer
   ```

2. Build the project using `CMake`:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. Run the executable:
   ```bash
   ./OptionPricer
   ```

### **Requirements**
- **C++ Compiler**: C++20 or later.
- **CMake**: Version 3.20 or later.

---

## **Future Improvements**
1. Extend support for additional exotic options like Barrier and Lookback options.
2. Optimize Monte Carlo simulations for multi-threaded environments.
3. Implement GPU-based acceleration for faster numerical computations.

---

## **License**
This project is licensed under the **MIT License**. See the [LICENSE](./LICENSE) file for details.

---
