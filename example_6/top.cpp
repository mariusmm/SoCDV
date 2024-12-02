#include <systemc.h>
#include "Master.hpp"

#ifdef MTI_SYSTEMC
#include "Slave.h"
#else
#include "Slave.hpp"
#endif

#ifdef MTI_SYSTEMC
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
        Slave* S;

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

                S = new Slave("Slave", "Slave");
                S->clk_i(clk);
                S->rst_n(reset_n_tb);
                S->device_req(device_req_tb);
                S->device_addr(device_addr_tb);
                S->device_we(device_we_tb);
                S->device_be(device_be_tb);
                S->device_wdata(device_wdata_tb);
                S->device_rvalid(device_rvalid_tb);
                S->device_rdata(device_rdata_tb);
                S->device_err(device_err_tb);
                S->device_intr(device_intr_tb);

        }

        ~top() {
                delete S;
                delete M;
        }

};


SC_MODULE_EXPORT(top);

#else
int sc_main(int argc, char* argv[]) {

        Master* M;
        Slave* S;

        sc_clock  clk("CLK", 10, SC_NS); 
        
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

        S = new Slave("Slave");
        S->clk_i(clk);
        S->rst_n(reset_n_tb);
        S->device_req(device_req_tb);
        S->device_addr(device_addr_tb);
        S->device_we(device_we_tb);
        S->device_be(device_be_tb);
        S->device_wdata(device_wdata_tb);
        S->device_rvalid(device_rvalid_tb);
        S->device_rdata(device_rdata_tb);
        S->device_err(device_err_tb);
        S->device_intr(device_intr_tb);

        sc_start();

        return 0;
}
#endif
