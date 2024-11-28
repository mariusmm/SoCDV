#include "testbench.hpp"  // Include the testbench header

int sc_main(int argc, char* argv[]) {

    sc_clock clk("clock", sc_time(10, SC_NS), 0.5,  SC_ZERO_TIME);
    
    Testbench tb("Testbench");  // Instantiate the testbench
    
    tb.clk(clk);                // Bind the main clock
    sc_start();                 // Start the simulation
    
    return 0;
}

