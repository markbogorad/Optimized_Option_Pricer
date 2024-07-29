// main.cpp
// 
// Each on of these tests a different interface. Uncomment one to try
//
// @author Mark Bogorad
// @version 1.0 


#include "console_interface.hpp"
int main() {
    console_interface ci;
    ci.display_results();
    return 0;
}


/*
#include "hardcoded_interface.hpp"
int main() {
    hardcoded_interface hi;
    hi.display_results();
    return 0;
}

#include "file_interface.hpp"
int main() {
    file_interface fi("options.txt"); // insert name of file to be read
    fi.display_results();
    return 0;
}

#include "matrix_interface.hpp"

int main() {
    matrix_interface mi("spot", 100.0, 120.0, 1.0); // Vary "spot" from 100 to 120 with a step size of 5
    mi.display_results();
    return 0;
}
*/