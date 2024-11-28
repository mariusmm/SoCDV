
#include <systemc>
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace sc_core;

SC_MODULE(inverter)
{
	sc_in<bool> in;
	sc_out<bool> out;

	void invert();
	SC_CTOR(inverter)
	{
		SC_THREAD(invert);
		sensitive << in; // sensitive to changes in the input
	}
	~inverter(){}
};


