#ifndef GATESBITWISEMOD_H
#define GATESBITWISEMOD_H

/**
 * \c several gates module interface
 */

#include <systemc.h>

/**
 * \c andgate module.
 * \c andgate module models a two input and gate
 *   - input ports
 *   	- \c bool \c din1	- first input
 *   	- \c bool \c din2	- second input
 *   - output ports
 *   	- \c bool \c dout	- result
 */

SC_MODULE(andbitwise) {
  
  sc_in< sc_uint<32> >  din1;
  //sc_in< sc_uint<32> >  din2;
  sc_out< sc_uint<32> > dout;

  SC_CTOR(andbitwise)
     {      
      SC_METHOD(entry);
      sensitive << din1;
    }
  
  void entry();
};

/**
 * \c orgate module.
 * \c orgate module models a two input or gate
 *   - input ports
 *   	- \c bool \c din1	- first input
 *   	- \c bool \c din2	- second input
 *   - output ports
 *   	- \c bool \c dout	- result
 */

SC_MODULE(orbitwise) {
  
  sc_in< sc_uint<32> >  din1;
  sc_in< sc_uint<32> >  din2;
  sc_out< sc_uint<32> > dout;

  SC_CTOR(orbitwise)
     {      
      SC_METHOD(entry);
      sensitive << din1 << din2;
    }
  
  void entry();
};

#endif
