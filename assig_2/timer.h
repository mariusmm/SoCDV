#ifndef _SCGENMOD_timer_
#define _SCGENMOD_timer_

#include "systemc.h"

class timer : public sc_foreign_module
{
public:
    sc_in<bool> clk_i;
    sc_in<bool> rst_ni;
    sc_in<bool> timer_req_i;
    sc_in<sc_uint<32> > timer_addr_i;
    sc_in<bool> timer_we_i;
    sc_in<sc_uint<4> > timer_be_i;
    sc_in<sc_uint<32> > timer_wdata_i;
    sc_out<bool> timer_rvalid_o;
    sc_out<sc_uint<32> > timer_rdata_o;
    sc_out<bool> timer_err_o;
    sc_out<bool> timer_intr_o;


    timer(sc_module_name nm, const char* hdl_name,
       int num_generics, const char** generic_list)
     : sc_foreign_module(nm),
       clk_i("clk_i"),
       rst_ni("rst_ni"),
       timer_req_i("timer_req_i"),
       timer_addr_i("timer_addr_i"),
       timer_we_i("timer_we_i"),
       timer_be_i("timer_be_i"),
       timer_wdata_i("timer_wdata_i"),
       timer_rvalid_o("timer_rvalid_o"),
       timer_rdata_o("timer_rdata_o"),
       timer_err_o("timer_err_o"),
       timer_intr_o("timer_intr_o")
    {
        elaborate_foreign_module(hdl_name, num_generics, generic_list);
    }
    ~timer()
    {}

};

#endif

