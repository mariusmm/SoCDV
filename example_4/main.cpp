
#include <systemc.h>

SC_MODULE(Producer) {
    sc_port<sc_fifo_out_if<int>> out_port;  // Interface port
   sc_in<bool> clk; 
    void write_data() {
      while(1) {
        int value = 0;
        wait();
        value++;
        out_port->write(value);  // Write data to FIFO
        std::cout << "@" << sc_time_stamp() << " Producer wrote: " << value << std::endl;
      }
    }

    SC_CTOR(Producer) {
        SC_THREAD(write_data);
        sensitive << clk.pos();
    }
};

SC_MODULE(Consumer) {
    sc_port<sc_fifo_in_if<int>> in_port;  // Interface port
 sc_in<bool> clk; 
    void read_data() {
    while(1) {
        wait();
        int data = in_port->read();  // Read data from FIFO
        std::cout << "@" << sc_time_stamp() << " Consumer read: " << data << std::endl;
        }
    }

    SC_CTOR(Consumer) {
        SC_THREAD(read_data);
        sensitive << clk.pos();
    }
};


int sc_main(int argc, char* argv[]) {

    sc_clock clk("clk", 10, SC_NS);
    sc_fifo<int> fifo("fifo", 4);
    Producer producer("Producer");
    Consumer consumer("consumer");

    producer.out_port(fifo);
    producer.clk(clk);
    
    consumer.in_port(fifo);
    consumer.clk(clk);
    
    sc_start(100, SC_NS);  // Start the simulation for 100 ns
    return 0;
}
