
#include "hazard.h"

/**
 * Callback for the hazard detection of \c hazard module.
 */
void hazard::detect_hazard()
{
	bool stall = false;
	//data hazards

	if(rs.read() != 0 && rs.read() == WriteReg_exe.read() && RegWrite_exe.read() == true && Branch.read()
		|| rt.read() != 0 && rt.read() == WriteReg_exe.read() && RegWrite_exe.read() == true && Branch.read()){
		stall = true;
		// se for branch e tem um hazard de dados para IF/ID faz stall
		// depois deste stall ja e possivel fazer forwarding para IF/ID
		enable_pc.write(false);
		enable_ifid.write(false);
		reset_ifid.write(false);
		reset_idexe.write(true);
		reset_exemem.write(false);
	}
	////////////////////////////////
	if((RegWrite_exe.read() == true) && (MemRead_exe.read() == true) && (rt.read() == WriteReg_exe.read())
		&& (rt.read() != 0)) {
		stall = true;
		// SE escrever num registo; a instrucao seguinte for ler da memoria
		//  E: os registos RT e WriteReg_exe forem iguais, entao ha necessidade de um stall
		enable_pc.write(false);
		enable_ifid.write(false);
		reset_ifid.write(false);
		reset_idexe.write(true);
		reset_exemem.write(false);

	}
	else if((RegWrite_exe.read() == true) && (MemRead_exe.read() == true) && (rs.read() == WriteReg_exe.read())
			&& (rs.read() != 0)) {
		stall = true;	
		// SE nao escrever num registo; a instrucao seguinte for ler da memoria
		//  E: os registos RS e WriteReg_exe forem iguais, entao ha necessidade de um stall
		enable_pc.write(false);
		enable_ifid.write(false);
		reset_ifid.write(false);
		reset_idexe.write(true);
		reset_exemem.write(false);
	}
	////////////////////////////////
	if((RegWrite_mem.read() == true) && (MemRead_mem.read() == true) && (rt.read() == WriteReg_mem.read())
		&& (rt.read() != 0)) {
		stall = true;
		// SE escrever num registo; a instrucao seguinte for ler da memoria
		//  E: os registos RT e WriteReg_mem forem iguais, entao ha necessidade de um stall
		enable_pc.write(false);
		enable_ifid.write(false);
		reset_ifid.write(false);
		reset_idexe.write(true);
		reset_exemem.write(false);

	}
	else if((RegWrite_mem.read() == true) && (MemRead_mem.read() == true) && (rs.read() == WriteReg_mem.read())
			&& (rs.read() != 0)) {
		stall = true;	
		// SE nao escrever num registo; a instrucao seguinte for ler da memoria
		//  E: os registos RS e WriteReg_mem forem iguais, entao ha necessidade de um stall
		enable_pc.write(false);
		enable_ifid.write(false);
		reset_ifid.write(false);
		reset_idexe.write(true);
		reset_exemem.write(false);
	}
	// else if((RegWrite.read() == false) && (MemWrite.read() == true) && (RegWrite_exe.read() == true)
	// 	&& (MemRead_exe.read() == true) && (rt.read() == WriteReg_exe.read())) {
	// 	// SE EM EXE: nao escrever num registo, for escrever na memoria; SE EM MEM for escrever num registo, for ler da memoria
	// 	//         E: os registos RT tanto de EXE como de MEM forem iguais, entao ha necessidade de um stall
	// 	enable_pc.write(false);
	// 	enable_ifid.write(false);
	// 	reset_ifid.write(false);
	// 	reset_idexe.write(true);
	// 	reset_exemem.write(false);

	// }
	// else if((RegWrite_exe.read() == false) && (MemWrite_exe.read() == true) && (RegWrite_mem.read() == true)
	// 		&& (MemRead_mem.read() == true) && (WriteReg_exe.read() == WriteReg_mem.read())) {
	// 	// SE EM EXE: nao escrever num registo, for escrever na memoria; SE EM MEM for escrever num registo, for ler da memoria
	// 	//         E: os registos RT tanto de EXE como de MEM forem iguais, entao ha necessidade de um stall
	// 	enable_pc.write(false);
	// 	enable_ifid.write(false);
	// 	reset_ifid.write(false);
	// 	reset_idexe.write(false);
	// 	reset_exemem.write(true);

	// }
	if(stall == false)
	{
		
		/*  se o branch for executado  */
		if( BranchTaken.read() == true){
			enable_pc.write(true);
			enable_ifid.write(true);
			reset_ifid.write(true);
			reset_idexe.write(true);
			reset_exemem.write(false);
		}

		/*  se for um jump ou jump register  */
		else if( (Jump.read() == true || JumpReg.read() == true) && Link.read() == false ){
			enable_pc.write(true);
			enable_ifid.write(false);
			reset_ifid.write(true);
			reset_idexe.write(true);
			reset_exemem.write(false);
					
		}
		/*  se for um jal ou jalr  */
		else if( (Jump.read() == true || JumpReg.read() == true) && Link.read() == true ){
			enable_pc.write(true);
			enable_ifid.write(false);
			reset_ifid.write(true);
			reset_idexe.write(false);
			reset_exemem.write(false);
					
		}
		/* normal flow */
		else{
			enable_pc.write(true);
			enable_ifid.write(true);
			reset_idexe.write(false);
			reset_ifid.write(false);
			reset_exemem.write(false);
		}

	}



}

