#include <systemc.h>
#include "Master.hpp"
#include "timer.h"


SC_MODULE(top) {
        sc_clock clk; 
        
        sc_signal<bool> reset_n_tb;
        sc_signal<bool>                 device_req_tb;
        sc_signal<sc_uint<DataWidth>>   device_addr_tb;
        sc_signal<bool>                 device_we_tb;
        sc_signal<sc_uint<DataWidth/8>> device_be_tb;
        sc_signal<sc_uint<DataWidth>>   device_wdata_tb;
        sc_signal<bool>                 device_rvalid_tb;
        sc_signal<sc_uint<DataWidth>>   device_rdata_tb;
        sc_signal<bool>                 device_err_tb;
        sc_signal<bool>                 device_intr_tb;

        Master* M;
        timer* S;

        SC_CTOR(top): 
                clk("CLK", 10, SC_NS),
                reset_n_tb("reset_n"),
                device_req_tb("device_req"),
                device_addr_tb("device_addr"),
                device_we_tb("device_we"),
                device_wdata_tb("device_wdata"),
                device_rvalid_tb("device_rvalid"),
                device_rdata_tb("device_rdata"),
                device_err_tb("device_err"),
                device_intr_tb("device_intr")
        {
                M = new Master("Master");
                M->clk_i(clk);
                M->rst_n(reset_n_tb);
                M->device_req(device_req_tb);
                M->device_addr(device_addr_tb);
                M->device_we(device_we_tb);
                M->device_be(device_be_tb);
                M->device_wdata(device_wdata_tb);
                M->device_rvalid(device_rvalid_tb);
                M->device_rdata(device_rdata_tb);
                M->device_err(device_err_tb);
                M->device_intr(device_intr_tb);

                S = new timer("Slave", "timer", 0, NULL);
                S->clk_i(clk);
                S->rst_ni(reset_n_tb);
                S->timer_req_i(device_req_tb);
                S->timer_addr_i(device_addr_tb);
                S->timer_we_i(device_we_tb);
                S->timer_be_i(device_be_tb);
                S->timer_wdata_i(device_wdata_tb);
                S->timer_rvalid_o(device_rvalid_tb);
                S->timer_rdata_o(device_rdata_tb);
                S->timer_err_o(device_err_tb);
                S->timer_intr_o(device_intr_tb);
        }

        ~top() {
                delete S;
                delete M;
        }

};


SC_MODULE_EXPORT(top);
