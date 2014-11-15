#ifndef MUXJMOD_H
#define MUXJMOD_H

/**
 *
 * 3:1 Mux module template.
 */

#include <systemc.h>

/**
 * Mux module.
 * Mux module models a generic 3:1 multiplexor of template type T. 
 * Implementation based on a template class.
 *
 *   - input ports
 *   	- \c T \c din0		- input 
 *   	- \c T \c din1		- input
 *     - \c T \c dinj    - input 
 *   	- \c bool \c sel		- select 
 *     - \c bool \c selj    - select 
 *   - output ports
 *   	- \c T \c dout		- output
 */

template <class T> class muxj: public sc_module
{
public:
  sc_in< T >  din0;
  sc_in< T >  din1; 
  sc_in< T >  dinj;         
  sc_in< bool >  sel;
  sc_in< bool >  selj;        
  sc_out< T > dout;

  SC_CTOR(muxj)
     {      
      SC_METHOD(entry);
      sensitive << din0 << din1  << dinj << selj << sel;
    }
  
  void entry();
};


template <class T> void muxj<T>::entry()
{
    if(selj.read()){
      //JUMP
      dout.write(dinj.read());
    }
    else if(sel.read()){
      //BRANCH
     dout.write(din1.read());
    }
    else{
      //PC+4
      dout.write(din0.read());
    }
}

#endif
