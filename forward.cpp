
#include "forward.h"

/**
 * Callback for the forward detection of \c forward module.
 */
void forward::detect_forward()
{
	// bool flag = false;


	forwd_ifid1_sel.write(0);
	forwd_ifid2_sel.write(0);
	mux_rs_sel.write(0);
	mux_rt_sel.write(0);


	// mux_forwd_regdata1 ID/EXE 1
	if (RegWrite_mem.read() && (rs_id.read() == WriteReg_mem.read())){
		forwd_idexe_r1.write(3);
	}
	else if (RegWrite_mem2.read() && (rs_id.read() == WriteReg_mem2.read())){
		forwd_idexe_r1.write(2);
	}
	else if (RegWrite_exe.read() && (rs_id.read() == WriteReg_exe.read())){
		forwd_idexe_r1.write(1);
	}
	else{
		forwd_idexe_r1.write(0);
	}
	// mux_forwd_regdata2 ID/EXE 2
	if (RegWrite_mem.read() && (rt_id.read() == WriteReg_mem.read())){
		forwd_idexe_r2.write(3);
	}
	else if (RegWrite_mem2.read() && (rt_id.read() == WriteReg_mem2.read())){
		forwd_idexe_r2.write(2);
	}
	else if (RegWrite_exe.read() && (rt_id.read() == WriteReg_exe.read())){
		forwd_idexe_r2.write(1);
	}
	else{
		forwd_idexe_r2.write(0);
	}

	// mux_forwd_exemem EXE/MEM
	if (RegWrite_mem.read() && (rt_exe.read() == WriteReg_mem.read())){
		forwd_exemem.write(3);
	}
	else if (RegWrite_mem2.read() && (rt_exe.read() == WriteReg_mem2.read())){
		forwd_exemem.write(2);
	}
	else if (RegWrite_wb.read() && (rt_exe.read() == WriteReg_wb.read())){
		forwd_exemem.write(1);
	}
	else{
		forwd_exemem.write(0);
	}
}

