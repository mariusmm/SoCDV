#include <systemc>

#include "bus.hpp"

// Slave module
SC_MODULE(Slave) {
    sc_port<BusInterface> bus;  // Port to the bus
    sc_in<bool> clk;
    int memory[10];

    void slave_process() {
        AddressDataBus* my_bus = dynamic_cast<AddressDataBus*>(bus.get_interface());
        while (true) {
            wait(my_bus->bus_event);
            
            if (my_bus->is_write_operation()) {
                // Handle write operation
                int address = my_bus->get_address();
                int data = my_bus->get_data();
                memory[address] = data;  // Store data in memory
                cout << sc_time_stamp() << ". Slave: Stored data " << data << " at address " << address << endl;
                my_bus->set_slave_response(0);  // Acknowledge write
            } else {
                // Handle read operation
                int address = my_bus->get_address();
                int data = memory[address];  // Retrieve data from memory
                cout << sc_time_stamp() << ". Slave: Returned data " << data << " from address " << address << endl;
                my_bus->set_slave_response(data);  // Send response
            }


            
        }
    }

    SC_CTOR(Slave) {
        SC_THREAD(slave_process);
        sensitive << clk.pos();
    }
};