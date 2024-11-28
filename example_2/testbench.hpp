#include <systemc.h>
#include "counter.hpp"  // Include the counter module

// Testbench Module
SC_MODULE(Testbench) {
    //sc_signal<bool> clk;
    sc_in_clk clk;
    sc_signal<bool> reset;    // Reset signal
    sc_signal<int> count;     // Counter output signal

    Counter* counter;         // Pointer to the Counter module

    // Stimulus generation process
    void stimulus() {
        reset.write(true);  // Assert reset
        wait(10, SC_NS);    // Hold reset for one clock cycle

        reset.write(false);  // Deassert reset
        wait(50, SC_NS);     // Run for five clock cycles

        reset.write(true);  // Assert reset again
        wait(10, SC_NS);

        reset.write(false);  // Deassert reset
        wait(30, SC_NS);     // Run for three more clock cycles

        sc_stop();  // End simulation
    }

    // Monitor the counter output
    void monitor() {
        while (true) {
            wait();  // Wait for changes in the clock
            cout << "Time: " << sc_time_stamp()
                 << " | Reset: " << reset.read()
                 << " | Count: " << count.read()
                 << endl;
        }
    }

    SC_CTOR(Testbench) {
        
        counter = new Counter("Counter");  // Instantiate the Counter module
        counter->clk(clk);                 // Bind the clock signal
        counter->reset(reset);             // Bind the reset signal
        counter->count(count);             // Bind the count output signal

        SC_THREAD(stimulus);               // Generate stimulus signals
        SC_THREAD(monitor);                // Monitor the output
        sensitive << clk.neg();
    }

    ~Testbench() {
        delete counter;  // Clean up dynamically allocated module
    }
};
