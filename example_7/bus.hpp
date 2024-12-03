#ifndef __BUS_H__
#define __BUS_H__

#include <systemc>

using namespace std;
using namespace sc_core;


// Define the bus interface
class BusInterface : public sc_interface {
public:
    virtual void write(int address, int data) = 0;  // Write operation
    virtual int read(int address) = 0;             // Read operation
    virtual bool is_ready() const = 0;             // Check if the bus is ready
};


// Custom Bus Channel
class AddressDataBus : public BusInterface {
private:
    int address_line;  
    int data_line;     
    bool ready;        
    bool is_write;   

public:  
    sc_event bus_event;  // Event to signal the slave about a transaction

public:
    // Constructor
    AddressDataBus() : address_line(0), data_line(0), ready(true), is_write(false) {}

    // Write operation
    void write(int address, int data) override;

    // Read operation
    int read(int address) override;

    // Set the result of a slave operation
    void set_slave_response(int data);

    // Check if the bus is ready
    bool is_ready() const override;

    // Get the current address
    int get_address() const;

    // Get the current data
    int get_data() const;

    // Check if the operation is a write
    bool is_write_operation() const;
};

#endif