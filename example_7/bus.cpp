#include "bus.hpp"

 // Write operation
void AddressDataBus::write(int address, int data) {
    if (!ready) {
        SC_REPORT_ERROR("AddressDataBus", "Bus is not ready for a new operation");
        return;
    }
    address_line = address;
    data_line = data;
    is_write = true;
    ready = false;

    // we can model that the bus spent some time or some clock cycles
    // wait(125, SC_NS);
    // wait(5);

    bus_event.notify();
    cout << sc_time_stamp() << ". Bus: WRITE to address " << address << " data " << data << endl;
}

// Read operation
int AddressDataBus::read(int address) {
    if (!ready) {
        SC_REPORT_ERROR("AddressDataBus", "Bus is not ready for a new operation");
        return -1;  // Error value
    }
    address_line = address;
    is_write = false;
    ready = false;
    cout << sc_time_stamp() << ". Bus: READ from address " << address << " returning data " << data_line << endl;

    // we can model that the bus spent some time or some clock cycles
    // wait(125, SC_NS);
    // wait(5);
    
    bus_event.notify();  // Notify slave of a new transaction
    wait(bus_event); 
    return data_line;
}

void AddressDataBus::set_slave_response(int data) {
    data_line = data;
    ready = true;
    bus_event.notify();  // Notify master that the transaction is complete
}

// Check if the bus is ready
bool AddressDataBus::is_ready() const {
    return ready;
}

int AddressDataBus::get_address() const {
        return address_line;
}

 // Get the current data
int AddressDataBus::get_data() const {
    return data_line;
}

// Check if the operation is a write
bool AddressDataBus::is_write_operation() const {
    return is_write;
}