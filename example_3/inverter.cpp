#include<systemc>
#include<cstdlib>
#include<cstring>

#include "inverter.hpp"

using namespace std;
using namespace sc_core;

void inverter::invert()
{
	while(1)
	{
		wait();
		out.write(! in.read() );
	}
}


