
#include "hazard.h"

/**
 * Callback for the hazrd detection of \c hazard module.
 */
void hazard::detect_hazard()
{
	//data hazards
	if( rs.read() != 0 && rs.read() == WriteReg_exe.read() && RegWrite_exe.read() == true
        || rs.read() != 0 && rs.read() == WriteReg_mem.read() && RegWrite_mem.read() == true
        || rs.read() != 0 && rs.read() == WriteReg_mem2.read() && RegWrite_mem2.read() == true
        || rt.read() != 0 && rt.read() == WriteReg_exe.read() && RegWrite_exe.read() == true
        || rt.read() != 0 && rt.read() == WriteReg_mem.read() && RegWrite_mem.read() == true
        || rt.read() != 0 && rt.read() == WriteReg_mem2.read() && RegWrite_mem2.read() == true){

		enable_pc.write(false);
		enable_ifid.write(false);
		reset_ifid.write(false);
		reset_idexe.write(true);
		reset_exemem.write(false);
	}
	else
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

		else{
			enable_pc.write(true);
			enable_ifid.write(true);
			reset_idexe.write(false);
			reset_ifid.write(false);
			reset_exemem.write(false);
		}	



	}



}

