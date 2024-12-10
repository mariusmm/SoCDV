#include "tlm.h"                               // TLM headers
#include "tlm_utils/simple_initiator_socket.h" // TLM simple initiator socket

class Initiator
    : public sc_core::sc_module
{
public:
    tlm_utils::simple_initiator_socket<Initiator> initiator_socket;

    Initiator(sc_core::sc_module_name name) : sc_module(name), initiator_socket("initiator_socket")
    {
        SC_THREAD(initiator_thread);
    }

private:
    void initiator_thread()
    {
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        tlm::tlm_generic_payload init_transaction;
        uint8_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        int address = 0;

        std::cout << "************************* WRITING ********************\n";
        do
        {
            init_transaction.set_command(tlm::TLM_WRITE_COMMAND);
            init_transaction.set_data_length(8);
            init_transaction.set_streaming_width(8);
            init_transaction.set_byte_enable_ptr(nullptr);
            init_transaction.set_dmi_allowed(false);
            init_transaction.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

            init_transaction.set_address(address);
            init_transaction.set_data_ptr(reinterpret_cast<unsigned char *>(data));

            std::cout << sc_core::sc_time_stamp() << ". Init: Writing @" << std::hex << address << " <- "
                      << static_cast<int>(data[0]) << ", "
                      << static_cast<int>(data[1]) << ", "
                      << static_cast<int>(data[2]) << ", "
                      << static_cast<int>(data[3]) << ", "
                      << static_cast<int>(data[4]) << ", "
                      << static_cast<int>(data[5]) << ", "
                      << static_cast<int>(data[6]) << ", "
                      << static_cast<int>(data[7])
                      << "\n";

            initiator_socket->b_transport(init_transaction, delay);

            if (init_transaction.get_response_status() != tlm::TLM_OK_RESPONSE)
            {
                std::cout << "Error in response status\n";
                sc_core::sc_stop();
            }
            else
            {
                std::cout << sc_core::sc_time_stamp() << ". Init: Transaction OK\n";
            }

            for (auto &item : data)
            {
                item++;
            }

            address += 8;

            wait(50, sc_core::SC_NS);
        } while (address < 30);

        std::cout << "************************* READING ********************\n";
        // Do some reads to check that the Target is working as a Memory
        address = 0;
        do
        {
            init_transaction.set_command(tlm::TLM_READ_COMMAND);
            init_transaction.set_data_length(8);
            init_transaction.set_streaming_width(8);
            init_transaction.set_byte_enable_ptr(nullptr);
            init_transaction.set_dmi_allowed(false);
            init_transaction.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

            init_transaction.set_address(address);
            init_transaction.set_data_ptr(reinterpret_cast<unsigned char *>(data));

            initiator_socket->b_transport(init_transaction, delay);

            std::cout << sc_core::sc_time_stamp() << ". Init: Reading @" << std::hex << address << " <- "
                      << static_cast<int>(data[0]) << ", "
                      << static_cast<int>(data[1]) << ", "
                      << static_cast<int>(data[2]) << ", "
                      << static_cast<int>(data[3]) << ", "
                      << static_cast<int>(data[4]) << ", "
                      << static_cast<int>(data[5]) << ", "
                      << static_cast<int>(data[6]) << ", "
                      << static_cast<int>(data[7])
                      << "\n";

            if (init_transaction.get_response_status() != tlm::TLM_OK_RESPONSE)
            {
                std::cout << "Error in response status\n";
                sc_core::sc_stop();
            }
            else
            {
                std::cout << sc_core::sc_time_stamp() << ". Init: Transaction OK\n";
            }

            for (auto &item : data)
            {
                item++;
            }

            address += 8;

            wait(50, sc_core::SC_NS);

        } while (address < 30);

        sc_core::sc_stop();
    }
};