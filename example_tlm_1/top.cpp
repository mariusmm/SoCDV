#include "initiator.hpp"
#include "target.hpp"
int sc_main(int argc, char *argv[])
{

    Initiator my_initiator("My_init");
    Target my_target("my_target");

    my_initiator.initiator_socket(my_target.target_socket);

    sc_core::sc_start();

    return 0;
}