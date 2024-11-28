#include <systemc>
#include <cstdlib>
#include <cstring>

#include "inverter.hpp"

using namespace std;
using namespace sc_core;

#ifdef MTI_SYSTEMC
SC_MODULE(top) {
	sc_signal<bool> signal_in;
	sc_signal<bool> signal_out;

	void sc_main_body();

	SC_CTOR(top) : signal_in("in"), signal_out("out") 
	{
		SC_THREAD(sc_main_body);
	}

};

void top::sc_main_body() {
	bool input_sets[] = {true, false, false, true, true, true, false, true, false, false, false, true, true, false, false, true, true, false};
	int length = *(&input_sets + 1) - input_sets;
	
	inverter I("1-bit-inverter");
	I.in(signal_in);
	I.out(signal_out);

	for(int i = 0; i < length; ++i)
	{
		signal_in.write(input_sets[i]);
		wait(2.0, SC_NS);

		//Print time to console and display signal value
		//cout << sc_time_stamp().to_seconds() << " Input "<<signal_in.read()<<" Output "<< signal_out.read() << endl;

	}
}

SC_MODULE_EXPORT(top);

#else 
int sc_main(int argc, char* argv[]) {
	sc_signal<bool> signal_in;
	sc_signal<bool> signal_out;
bool input_sets[] = {true, false, false, true, true, true, false, true, false, false, false, true, true, false, false, true, true, false};
	int length = *(&input_sets + 1) - input_sets;
	
	inverter I("1-bit-inverter");
	I.in(signal_in);
	I.out(signal_out);

  sc_trace_file *trace_file = sc_create_vcd_trace_file("trace_file");
  sc_trace(trace_file, signal_in, "in");
  sc_trace(trace_file, signal_out, "out");


	for(int i = 0; i < length; ++i)
	{
		signal_in.write(input_sets[i]);
		sc_start(2.0, SC_NS);

		//Print time to console and display signal value
		cout << sc_time_stamp().to_seconds() << " Input "<<signal_in.read()<<" Output "<< signal_out.read() << endl;

	}

	sc_stop();
 
 sc_close_vcd_trace_file(trace_file);
	return 0;
}


#endif
