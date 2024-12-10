#ifndef _TARGET__H_
#define _TARGET__H_

#include "tlm.h"                            // TLM headers
#include "tlm_utils/simple_target_socket.h" // TLM simple initiator socket

class Target
    : public sc_core::sc_module
{
public:
    tlm_utils::simple_target_socket<Target> target_socket;

    Target(sc_core::sc_module_name name) : sc_module(name), target_socket("target_socket")
    {

        target_socket.register_b_transport(this, &Target::my_b_transport);
    }

private:
    void my_b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay)
    {
        // Get all transaction data
        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64 adr = trans.get_address();
        unsigned char *ptr = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        [[maybe_unused]] unsigned char *byt = trans.get_byte_enable_ptr();  // Not used
        [[maybe_unused]] unsigned int wid = trans.get_streaming_width();    // Not used

        sc_core::sc_time LATENCY;

        if (adr >= sc_dt::uint64(1024))
        {
            trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
            return;
        }

        if (cmd == tlm::TLM_READ_COMMAND)
        {
            std::copy_n(mem.cbegin() + adr, len, ptr);
            std::cout << sc_core::sc_time_stamp() << ". Target Reading\n";
            LATENCY = sc_core::sc_time(100, sc_core::SC_NS);
        }
        else if (cmd == tlm::TLM_WRITE_COMMAND)
        {
            std::copy_n(ptr, len, mem.begin() + adr);
            std::cout << sc_core::sc_time_stamp() << ". Target Writing " << std::hex << adr << " <- "
                      << static_cast<int>(ptr[0]) << ", "
                      << static_cast<int>(ptr[1]) << ", "
                      << static_cast<int>(ptr[2]) << ", "
                      << static_cast<int>(ptr[3]) << ", "
                      << static_cast<int>(ptr[4]) << ", "
                      << static_cast<int>(ptr[5]) << ", "
                      << static_cast<int>(ptr[6]) << ", "
                      << static_cast<int>(ptr[7])
                      << "\n";
            LATENCY = sc_core::sc_time(33, sc_core::SC_NS);
        }

        delay = LATENCY;
        sc_core::wait(delay);

        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }

    std::array<uint8_t, 1024> mem{};
};

#endif