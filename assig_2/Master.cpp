#include "Master.hpp"


void Master::write_data(uint32_t addr, uint32_t data) {
  wait();
  device_req.write(true);
  device_addr.write(addr);
  device_we.write(true);
  device_be.write(0xF);
  device_wdata.write(data);
  wait();
  device_req.write(false);
  device_addr.write(0);
  device_we.write(false);
  device_wdata.write(0);
}

uint32_t Master::read_data(uint32_t addr) {
  wait();
  device_req.write(true);
  device_addr.write(addr);
  device_we.write(false);
  wait();
  wait();
  device_req.write(false);
  device_addr.write(0);
  device_we.write(false);
  device_wdata.write(0);
  return device_rdata.read();
}

void Master::tb_process() {
  rst_n.write(true);  // Assert rst_n
  wait(50, SC_NS);    // Hold rst_n for one clock cycle
  rst_n.write(false);  // Deassert rst_n
  wait(75, SC_NS);     // Run for five clock cycles
  rst_n.write(true);  // Assert rst_n again
  sc_time start_time = sc_time_stamp();

  wait(30, SC_NS);

  // Write access to register @4 value 0x12
  std::cout << sc_time_stamp() << " Write 0x12 -> @4\n";
  write_data(0x04, 0x12);

  wait(30, SC_NS);

  // read back the TIME LOW register (@0)
  uint32_t r_data = read_data(0x00);
  std::cout << sc_time_stamp() << " Read @0 : " << std::hex << r_data << "\n";
  
  // Check that the timer has the correct count time
  auto calculation = floor((sc_time_stamp() - start_time) / sc_time(10, SC_NS) - 1);
  if (calculation != r_data) {
    std::cout << "ERROR: Current TIMERL value: " << r_data << ". Should be: " << calculation << "\n";
    sc_stop();
  }

  wait(30, SC_NS);

  // read back the TIME HIGH register (@4)
  r_data = read_data(0x04);
  std::cout << sc_time_stamp() << " Read @4 : " << std::hex << r_data << "\n";
 
  // Value of TIMERH should be still 0x12
  if (r_data != 0x12) {
    std::cout << "ERROR: Current TIMERH value " << r_data << ". Should be: " << 0x12 << "\n";
    sc_stop();
  }

  std::cout << "OK" << "\n";

  wait(70, SC_NS);
#ifndef MTI_SYSTEMC
  sc_stop();  // End simulation
#endif
}
