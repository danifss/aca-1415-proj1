
#include "forward.h"

/**
 * Callback for the forward detection of \c forward module.
 */
void forward::detect_forward()
{
	bool flag = false;

	forwd_exe_ifid_regdata1.write(0);
	forwd_exe_ifid_regdata2.write(0);
	forwd_mem_ifid_regdata1.write(0);
	forwd_mem_ifid_regdata2.write(0);
	forwd_exe_idexe_regdata1.write(0);
	forwd_exe_idexe_regdata2.write(0);

	printf("\nNova iteracao:----------\n");


	if(RegWrite_exe.read()){

		///// EXE -> IF/ID
		if(WriteReg_exe.read() == rs_id.read()){
			forwd_exe_ifid_regdata1.write(1);
			flag=true;
			printf("EXE->IF/ID: ALUOut_exe->regdata1 = mux->sel 1\n");
		}
		if(WriteReg_exe.read() == rt_id.read()){
			forwd_exe_ifid_regdata2.write(1);
			flag=true;
			printf("EXE->IF/ID: ALUOut_exe->regdata2 = mux->sel 1\n");
		}


		///// MEM -> IF/ID
		if(WriteReg_mem.read() == rs_id.read()){
			forwd_mem_ifid_regdata1.write(1);
			flag=true;
			printf("MEM->IF/ID: ALUOut_mem->regdata1 = mux->sel 2\n");
		}
		if(WriteReg_mem.read() == rt_id.read()){
			forwd_mem_ifid_regdata2.write(1);
			flag=true;
			printf("MEM->IF/ID: ALUOut_mem->regdata2 = mux->sel 2\n");
		}


		// ///// EXE -> ID/EXE
		// if(WriteReg_exe.read() == rs_id.read()){ // forwarding de ALUout -> regdata1
		// 	forwd_exe_idexe_regdata1.write(1);
		// 	flag=true;
		// 	printf("EXE->ID/EXE: ALUOut->regdata1 = mux->sel 1\n");
		// }
		// if(WriteReg_exe.read() == rt_id.read()){ // forwarding de ALUout -> regdata2
		// 	forwd_exe_idexe_regdata2.write(1);
		// 	flag=true;
		// 	printf("EXE->ID/EXE: ALUOut->regdata2 = mux->sel 1\n");
		// }
	}

//	printf("selj: %i\n",forwd_mem_ifid_regdata1.read());
//	printf("sel:  %i\n",forwd_exe_ifid_regdata1.read());

	// debug
	 if(!flag)
	 	printf("Sem forwarding\n");
}

