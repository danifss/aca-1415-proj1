#ifndef MUX4MOD_H
#define MUX4MOD_H

/**
 *
 * 4:1 Mux module template.
 */

#include <systemc.h>

/**
 * Mux module.
 * Mux module models a generic 4:1 multiplexor of template type T. 
 * Implementation based on a template class.
 *
 *   - input ports
 *   	- \c T \c din0     - input 
 *   	- \c T \c din1     - input
 *    - \c T \c din2     - input 
 *    - \c T \c din3     - input 
 *   	- \c bool \c sel0	 - select 
 *    - \c bool \c sel1  - select 
 *   - output ports
 *   	- \c T \c dout     - output
 */

template <class T> class mux4: public sc_module
{
public:
  sc_in< T >  din0;
  sc_in< T >  din1;
  sc_in< T >  din2;
  sc_in< T >  din3;
  sc_in< bool >  sel0;
  sc_in< bool >  sel1;
  sc_out< T > dout;

  SC_CTOR(mux4)
     {      
      SC_METHOD(entry);
      sensitive << din0 << din1 << din2 << din3 << sel0 << sel1; // MSB << LSB ???
    }
  
  void entry();
};


template <class T> void mux4<T>::entry()
{
  if(sel1.read() && sel0.read()){ // 11
    dout.write(din3.read());
  }
  else if(sel1.read() && !sel0.read()){ // 10
    dout.write(din2.read());
  }
  else if(!sel1.read() && sel0.read()){ // 01
    dout.write(din1.read());
  }
  else{ // 00
    dout.write(din0.read());
  }
}

#endif
