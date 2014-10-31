
#include "gatesbitwise.h"

/**
 * \c andbitwise module callback function.
 */
void andbitwise::entry()
{
   dout.write(din1.read() & 0xF0000000);
}

/**
 * \c orbitwise module callback function.
 */
void orbitwise::entry()
{
   dout.write(din1.read() | din2.read());
}
