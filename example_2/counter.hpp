#include <systemc.h>

// Counter Module using SC_THREAD
SC_MODULE(Counter) {
    sc_in<bool> clk;      // Clock signal
    sc_in<bool> reset;    // Reset signal
    sc_out<int> count;    // Counter output

    void process() {
        // Initialize the counter to 0
        count.write(0);
        wait(); // Wait for the first clock cycle to start

        while (true) {
            if (reset.read() == true) {
                count.write(0);  // Reset the counter
            } else {
                count.write(count.read() + 1);  // Increment the counter
            }
            wait();  // Wait for the next clock cycle
        }
    }

    SC_CTOR(Counter) {
        SC_THREAD(process);  // Register the process as a thread
        sensitive << clk.pos();  // Trigger the process on the positive edge of the clock
    }
};
