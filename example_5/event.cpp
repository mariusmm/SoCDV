#include <systemc.h>

SC_MODULE(EventExample) {
    sc_event event;  // Declare the event

    void process1() {
        cout << "Process 1 is running" << endl;
        wait(5, SC_NS);  // Wait for 5 ns
        event.notify();  // Trigger the event after 5 ns
        cout << "Process 1 triggered the event" << endl;
    }

    void process2() {
        cout << "Process 2 is waiting for the event" << endl;
        wait(event);  // Wait until the event is triggered
        cout << "Process 2 resumed after event trigger" << endl;
    }

    SC_CTOR(EventExample) {
        SC_THREAD(process1);  // Register process1 as a thread
        SC_THREAD(process2);  // Register process2 as a thread
    }
};

int sc_main(int argc, char* argv[]) {
    EventExample example("EventExample");  // Instantiate the EventExample module
    sc_start(10, SC_NS);  // Start the simulation for 10 ns
    return 0;
}
