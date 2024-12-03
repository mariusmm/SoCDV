#include <systemc>

#include "bus.hpp"
#include "master.hpp"
#include "slave.hpp"

using namespace std;
using namespace sc_core;

// Top module
SC_MODULE(Top) {
    sc_clock clk;
    AddressDataBus bus;  // Custom bus channel

    Master master;
    Slave slave;

    SC_CTOR(Top)
        : clk("clk", 10, SC_NS), bus(), master("Master"), slave("Slave") {
        master.bus(bus);
        master.clk(clk);

        slave.bus(bus);
        slave.clk(clk);
    }
};

// sc_main
int sc_main(int argc, char* argv[]) {
    Top top("Top");
    sc_start(500, SC_NS);  // Run simulation for 100 ns
    return 0;
}