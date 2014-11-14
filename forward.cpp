
#include "forward.h"

/**
 * Callback for the forward detection of \c forward module.
 */
void forward::detect_forward()
{
	bool flag = false;

	forwd_exe_ifid_regdata1.write(0);
	forwd_exe_ifid_regdata2.write(0);

	printf("Nova iteracao:----------\n");

	if(RegWrite_exe.read()){
		if(WriteReg_exe.read() == rs_id.read()){ // forwarding de ALUout -> regdata1
			forwd_exe_ifid_regdata1.write(1);
			flag=true;
			printf("EXE->ID/EXE: forward de ALUout->regdata1 = mux->sel %i\n", forwd_exe_ifid_regdata1.read());
		}
		if(WriteReg_exe.read() == rt_id.read()){ // forwarding de ALUout -> regdata2
			forwd_exe_ifid_regdata2.write(1);
			flag=true;
			printf("EXE->ID/EXE: forward de ALUout->regdata2 = mux->sel %i\n", forwd_exe_ifid_regdata2.read());
		}
	}
	if(!flag)
		printf("Sem forwarding\n");
}

