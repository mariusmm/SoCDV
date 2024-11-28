#include "Slave.hpp"

#define MTIME_LOW       0x00
#define MTIME_HIGH      0x04
#define MTIMECMP_LOW    0x08
#define MTIMECMP_HIGH   0x0C

// Implements the reset and basic Timer functionality
void Slave::process() {

    while(true) {

        wait();

        if (rst_n.read() == false) {
            wait();
            mtime_q = 0;
            mtimecmp_q = 0;
        } else {
            mtime_q = mtime_d;
            mtimecmp_q = mtimecmp_d;
            
        }

        mtime_inc = mtime_q + 1;
        mtime_d = mtime_inc;

        std::cout << sc_time_stamp() << " MTIME_D: " << std::hex << mtime_q << "\n";
    }
}

// Implements FF for registered outputs rvalid and device_rdata
void Slave::outputs(){
    
    device_rvalid.write( device_req.read() );
    
    if (device_req.read() == true) {
        if (device_we.read() == true) {
            // write request
            switch (device_addr.read()) {
                case MTIME_LOW: {
                    std::cout << sc_time_stamp() << " W: MTIME_LOW\n";
                    mtime_d &= ~0x00000000FFFFFFFF;
                    mtime_d |= device_wdata.read();
                    break;
                }
                case MTIME_HIGH: {
                    std::cout << sc_time_stamp() << " W: MTIME_HIGH\n";
                    mtime_d &= ~0xFFFFFFFF00000000;
                    mtime_d |= device_wdata.read() << 32;
                    break;
                    }
                case MTIMECMP_LOW: {
                    std::cout << sc_time_stamp() << " W: MTIMECMP_LOW\n";
                    mtimecmp_d &= ~0x00000000FFFFFFFF;
                    mtimecmp_d |= device_wdata.read();                        
                    break;
                    }
                case MTIMECMP_HIGH: {
                    std::cout << sc_time_stamp() << " W: MTIMECMP_HIGH\n";
                    mtimecmp_d &= ~0xFFFFFFFF00000000;
                    mtimecmp_d |= device_wdata.read() << 32;
                    break;}
                default: {
                    std::cout << "W: Error!\n";
                }
            } 
        } else {
            // read request
            switch (device_addr.read()) {
                case MTIME_LOW: {
                    std::cout << sc_time_stamp() << " R: MTIME_LOW\n";
                    device_rdata.write(mtime_q & 0x00000000FFFFFFFF);
                    break;
                    }
                case MTIME_HIGH: {
                    std::cout << sc_time_stamp() << " R: MTIME_HIGH\n";
                    device_rdata.write((mtime_q & 0xFFFFFFFF00000000 ) >> 32);
                    break;
                    }
                case MTIMECMP_LOW: {
                    std::cout << sc_time_stamp() << " R: MTIMECMP_LOW\n";
                    device_rdata.write(mtimecmp_q & 0x00000000FFFFFFFF);
                    break;
                    }
                case MTIMECMP_HIGH: {
                    std::cout << sc_time_stamp() << " R: MTIMECMP_HIGH\n";
                    device_rdata.write((mtimecmp_q & 0xFFFFFFFF00000000) >> 32);
                    break;
                    }
                default: {
                    std::cout << "W: Error!\n";
                }
            }
        }
    }
    
}