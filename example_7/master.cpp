#include "master.hpp"

void Master::master_process() {
    for (int i = 0; i < 5; ++i) {
        wait();  // Wait for clock edge

        if (bus->is_ready()) {
            if (i % 2 == 0) {
                bus->write(i, i * 10);  // Perform write operation
            } else {
                int data = bus->read(i);  // Perform read operation
                cout << sc_time_stamp() << ". Master: Read data " << data << " from address " << i << endl;
            }
        } else {
            cout << sc_time_stamp() << ". Master: Bus not ready yet" << endl;
        }
    }
}