
#include "forward.h"

/**
 * Callback for the forward detection of \c forward module.
 */
void forward::detect_forward()
{
	bool flag = false;
	bool forwd_mem2_idexe1, forwd_mem2_idexe2 = false;
	bool forwd_mem_idexe1, forwd_mem_idexe2 = false;
	bool forwd_exe_idexe1, forwd_exe_idexe2 = false;

	forwd_idexe_r1_1.write(0);
	forwd_idexe_r1_2.write(0);
	forwd_idexe_r2_1.write(0);
	forwd_idexe_r2_2.write(0);

	printf("Nova iteracao:----------\n");

	if(rd_id.read() != 0){
		if(RegWrite_mem2.read() 
			&& !RegWrite_exe.read() 
			&& !RegWrite_mem.read() 
			&& (WriteReg_mem2.read() == rs_id.read())){ // forwarding MEM2->ID/EXE
			
			forwd_mem2_idexe1 = true;
		 	flag=true;

		 	forwd_idexe_r1_1.write(0); forwd_idexe_r1_2.write(1);
		}
		if(RegWrite_mem.read() 
			&& !RegWrite_exe.read() 
			&& (WriteReg_mem.read() == rs_id.read())){ // forwarding MEM->ID/EXE
			
			forwd_mem_idexe1 = true;
			flag=true;

			forwd_idexe_r1_1.write(1); forwd_idexe_r1_2.write(0);
		}
		if(RegWrite_exe.read() 
			&& (WriteReg_exe.read() == rs_id.read())){ // forwarding EXE->ID/EXE
			
			forwd_exe_idexe1 = true;
			flag=true;

			forwd_idexe_r1_1.write(1); forwd_idexe_r1_2.write(1);
		}


		if(RegWrite_mem2.read() 
			&& !RegWrite_exe.read() 
			&& !RegWrite_mem.read() 
			&& (WriteReg_mem2.read() == rt_id.read())){ // forwarding MEM2->ID/EXE
			
			forwd_mem2_idexe2 = true;
		 	flag=true;

		 	forwd_idexe_r2_1.write(0); forwd_idexe_r2_2.write(1);
		}
		if(RegWrite_mem.read() 
			&& !RegWrite_exe.read() 
			&& (WriteReg_mem.read() == rt_id.read())){ // forwarding MEM->ID/EXE
			
			forwd_mem_idexe2 = true;
			flag=true;

			forwd_idexe_r2_1.write(1); forwd_idexe_r2_2.write(0);
		}
		if(RegWrite_exe.read() 
			&& (WriteReg_exe.read() == rt_id.read())){ // forwarding EXE->ID/EXE
			
			forwd_exe_idexe2 = true;
			flag=true;

			forwd_idexe_r2_1.write(1); forwd_idexe_r2_2.write(1);
		}
	}



	// Gerar sinais de select dos multiplexers
	// if(flag && (rd_id.read() != 0)){
	// 	//// NAO ALTERAR A ORDEM!!!
	// 	if(forwd_mem2_idexe1){ // forwd mem2->idexe redata1
	// 		forwd_idexe_r1_1.write(0); forwd_idexe_r1_2.write(1);
	// 	}
	// 	if(forwd_mem2_idexe2){ // forwd mem2->idexe redata2
	// 		forwd_idexe_r2_1.write(0); forwd_idexe_r2_2.write(1);
	// 	}

	// 	if(forwd_mem_idexe1){ // forwd mem->idexe redata1
	// 		forwd_idexe_r1_1.write(1); forwd_idexe_r1_2.write(0);
	// 	}
	// 	if(forwd_mem_idexe2){ // forwd mem->idexe redata2
	// 		forwd_idexe_r2_1.write(1); forwd_idexe_r2_2.write(0);
	// 	}
		
	// 	if(forwd_exe_idexe1){ // forwd exe->idexe redata1
	// 		forwd_idexe_r1_1.write(1); forwd_idexe_r1_2.write(1);
	// 	}
	// 	if(forwd_exe_idexe2){ // forwd exe->idexe redata2
	// 		forwd_idexe_r2_1.write(1); forwd_idexe_r2_2.write(1);
	// 	}
	// }
	// else{ // No forwarding
	// 	forwd_idexe_r1_1.write(0);
	// 	forwd_idexe_r1_2.write(0);
	// 	forwd_idexe_r2_1.write(0);
	// 	forwd_idexe_r2_2.write(0);
	// }

	if(!flag)
		printf("Sem forwarding\n");
	else{
		printf("regdata1 sel0/sel1: %i", forwd_idexe_r1_1.read());
		printf("%i\n", forwd_idexe_r1_2.read());
		printf("regdata2 sel0/sel1: %i", forwd_idexe_r2_1.read());
		printf("%i\n\n", forwd_idexe_r2_2.read());
	}

	// if(rd_id.read() == 0){
	// 	forwd_idexe_r1_1.write(0);
	// 	forwd_idexe_r1_2.write(0);
	// 	forwd_idexe_r2_1.write(0);
	// 	forwd_idexe_r2_2.write(0);
	// }

}

