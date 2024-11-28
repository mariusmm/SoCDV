#include <systemc.h>

#define DataWidth 32


SC_MODULE(Slave) {
    sc_in<bool> clk_i;
    sc_in<bool> rst_n;
    
    // Bus interface
    sc_in<bool>                   device_req;
    sc_in<sc_uint<DataWidth>>     device_addr;
    sc_in<bool>                   device_we;
    sc_in<sc_uint<DataWidth/8>>   device_be;
    sc_in<sc_uint<DataWidth>>     device_wdata;
    sc_out<bool>                  device_rvalid;
    sc_out<sc_uint<DataWidth>>    device_rdata;
    sc_out<bool>                  device_err;
    sc_out<bool>                  device_intr;

    SC_CTOR(Slave) {
        SC_THREAD(process);         // Register the process as a thread
        sensitive << clk_i.neg();   // Trigger the process on the negative edge of the clock
    }

private:
    void process();
    
    sc_uint<64> mtime_q;
    sc_uint<64> mtime_d;
    sc_uint<64> mtime_inc;

    sc_uint<64> mtimecmp_q;
    sc_uint<64> mtimecmp_d;
    
};