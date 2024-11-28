#include <systemc.h>
#include "Master.hpp"
#include "Slave.hpp"

int sc_main(int argc, char* argv[]) {


        sc_clock clk("CLK", 10, SC_NS);
        
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
            
        Master M("Master_TB");
        Slave S("Slave");

        M.clk_i(clk);
        M.rst_n(reset_n_tb);
        M.device_req(device_req_tb);
        M.device_addr(device_addr_tb);
        M.device_we(device_we_tb);
        M.device_be(device_be_tb);
        M.device_wdata(device_wdata_tb);
        M.device_rvalid(device_rvalid_tb);
        M.device_rdata(device_rdata_tb);
        M.device_err(device_err_tb);
        M.device_intr(device_intr_tb);


        S.clk_i(clk);
        S.rst_n(reset_n_tb);
        S.device_req(device_req_tb);
        S.device_addr(device_addr_tb);
        S.device_we(device_we_tb);
        S.device_be(device_be_tb);
        S.device_wdata(device_wdata_tb);
        S.device_rvalid(device_rvalid_tb);
        S.device_rdata(device_rdata_tb);
        S.device_err(device_err_tb);
        S.device_intr(device_intr_tb);

        sc_trace_file *trace_file = sc_create_vcd_trace_file("trace_file");
        sc_trace(trace_file, clk, "clk");
        sc_trace(trace_file, reset_n_tb, "reset_n");
        sc_trace(trace_file, device_req_tb, "device_req");
        sc_trace(trace_file,device_addr_tb, "device_addr");
        sc_trace(trace_file,device_we_tb, "device_we");
        sc_trace(trace_file,device_be_tb, "device_be");
        sc_trace(trace_file,device_wdata_tb, "device_wdata");
        sc_trace(trace_file,device_rvalid_tb, "device_rvalid");
        sc_trace(trace_file,device_rdata_tb, "device_rdata");
        sc_trace(trace_file,device_err_tb, "device_err");
        sc_trace(trace_file,device_intr_tb, "device_intr");

        sc_start();

        sc_close_vcd_trace_file(trace_file);
        return 0;
}
