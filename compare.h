#ifndef COMPMOD_H
#define COMPMOD_H


#include <systemc.h>


SC_MODULE(compare){
	sc_in< sc_uint<32> >  op1;
	sc_in< sc_uint<32> >  op2;
	sc_in< bool > opt;
	sc_out< bool > res;


	SC_CTOR(compare){
		SC_METHOD(calc);
    	sensitive << op1 << op2 << opt;
	}
	void calc();
};

#endif