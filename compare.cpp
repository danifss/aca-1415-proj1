// comparator

#include "compare.h"

void compare::calc(){
	if(opt.read() == 0){
		res.write(op1.read() == op2.read());
	}
	else{
		res.write(op1.read() != op2.read());
	}
}