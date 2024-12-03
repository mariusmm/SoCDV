#ifndef __MASTER_H__
#define __MASTER_H__

#include <systemc>

#include "bus.hpp"

using namespace std;
using namespace sc_core;

// Master module
SC_MODULE(Master) {
    sc_port<BusInterface> bus;  // Port to the bus
    sc_in<bool> clk;

    void master_process();

    SC_CTOR(Master) {
        SC_THREAD(master_process);
        sensitive << clk.pos();
    }
};

#endif