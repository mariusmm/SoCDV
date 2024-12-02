#include <systemc.h>

#define DataWidth 32

// Module using SC_THREAD that mimics a IBEX Master
// This module is a simple testbench for the Timer IBEX IP Slave
SC_MODULE(Master) {
    sc_in<bool> clk_i;
    sc_out<bool> rst_n;
    
    // Bus interface
    sc_out<bool>                 device_req;
    sc_out<sc_uint<DataWidth>>   device_addr;
    sc_out<bool>                 device_we;
    sc_out<sc_uint<DataWidth/8>> device_be;
    sc_out<sc_uint<DataWidth>>   device_wdata;
    sc_in<bool>                  device_rvalid;
    sc_in<sc_uint<DataWidth>>    device_rdata;
    sc_in<bool>                  device_err;
    sc_in<bool>                  device_intr;

    void tb_process();
    void write_data(uint32_t addr, uint32_t data);
    uint32_t read_data(uint32_t addr);
    
    SC_CTOR(Master) {
        SC_THREAD(tb_process);      // Register the process as a thread
        sensitive << clk_i.pos();   // Trigger the process on the positive edge of the clock
    }
};