#ifndef REG_ID_EXE_H
#define REG_ID_EXE_H

/**
 *
 * reg_id_exe_t module interface.
 */

#include <systemc.h>

#include "regT.h"

/**
 * reg_id_exe_t module.
 * reg_id_exe_t module is the ID/EXE pipeline register. 
 */

SC_MODULE(reg_id_exe_t) {

	// Ports
	
	sc_in  < bool > clk;
	sc_in  < bool > reset;
	sc_in  < bool > enable;

	sc_in < bool > Link_id;
	sc_out < bool > Link_exe;

	sc_in  < sc_uint<32> > rega_id, regb_id, imm_id, PC4_id;
	sc_out < sc_uint<32> > rega_exe, regb_exe, imm_exe, PC4_exe;

	sc_in  < sc_uint<5> > rs_id, rt_id, rd_id;       // signals to propagate rs, rt, and rd values
	sc_out < sc_uint<5> > rs_exe, rt_exe, rd_exe;    // signals to propagate rs, rt, and rd values

	sc_in  < bool > MemRead_id, MemWrite_id, MemtoReg_id, RegDst_id;
	sc_out < bool > MemRead_exe, MemWrite_exe, MemtoReg_exe, RegDst_exe;

	sc_in  < bool > Branch_id, ALUSrc_id, RegWrite_id;
	sc_out < bool > Branch_exe, ALUSrc_exe, RegWrite_exe;

	sc_in  < sc_uint<3> > ALUOp_id;
	sc_out < sc_uint<3> > ALUOp_exe;

	sc_in  < sc_uint<32> > PC_id;   // only for visualization purposes
	sc_out < sc_uint<32> > PC_exe;  // only for visualization purposes
	sc_in  < bool > valid_id;       // only for visualization purposes
	sc_out < bool > valid_exe;      // only for visualization purposes

	// Modules
	
	regT < sc_uint<32> > *rega,*regb,*imm,*PC4;
	regT < sc_uint<5> > *rs, *rt, *rd;
	regT < bool > *Link, *MemRead, *MemWrite, *MemtoReg, *Branch,
				*RegWrite, *ALUSrc, *RegDst;
	regT < sc_uint<3> > *ALUOp;

	regT < sc_uint<32> > *PC;      // only for visualization purposes
	regT < bool > *valid;          // only for visualization purposes

	SC_CTOR(reg_id_exe_t) {


		Link = new regT < bool > ("linkidexe");;
		Link->din(Link_id);
		Link->dout(Link_exe);
		Link->clk(clk);
		Link->enable(enable);
		Link->reset(reset);

		rega = new regT < sc_uint<32> > ("rega");;
		rega->din(rega_id);
		rega->dout(rega_exe);
		rega->clk(clk);
		rega->enable(enable);
		rega->reset(reset);

		regb = new regT < sc_uint<32> >("regb");
		regb->din(regb_id);
		regb->dout(regb_exe);
		regb->clk(clk);
		regb->enable(enable);
		regb->reset(reset);

		rs = new regT < sc_uint<5> > ("rs");
		rs->din(rs_id);
		rs->dout(rs_exe);
		rs->clk(clk);
		rs->enable(enable);
		rs->reset(reset);

		rt = new regT < sc_uint<5> > ("rt");
		rt->din(rt_id);
		rt->dout(rt_exe);
		rt->clk(clk);
		rt->enable(enable);
		rt->reset(reset);

		rd = new regT < sc_uint<5> > ("rd");
		rd->din(rd_id);
		rd->dout(rd_exe);
		rd->clk(clk);
		rd->enable(enable);
		rd->reset(reset);

		RegDst = new regT < bool > ("RegDst");
		RegDst->din(RegDst_id);
		RegDst->dout(RegDst_exe);
		RegDst->clk(clk);
		RegDst->enable(enable);
		RegDst->reset(reset);

		PC4 = new regT < sc_uint<32> >("PC4");
		PC4->din(PC4_id);
		PC4->dout(PC4_exe);
		PC4->clk(clk);
		PC4->enable(enable);
		PC4->reset(reset);

		imm = new regT < sc_uint<32> >("imm");
		imm->din(imm_id);
		imm->dout(imm_exe);
		imm->clk(clk);
		imm->enable(enable);
		imm->reset(reset);

		MemRead = new regT < bool >("MemRead");
		MemRead->din(MemRead_id);
		MemRead->dout(MemRead_exe);
		MemRead->clk(clk);
		MemRead->enable(enable);
		MemRead->reset(reset);

		MemWrite = new regT < bool >("MemWrite");
		MemWrite->din(MemWrite_id);
		MemWrite->dout(MemWrite_exe);
		MemWrite->clk(clk);
		MemWrite->enable(enable);
		MemWrite->reset(reset);

		MemtoReg = new regT < bool >("MemtoReg");
		MemtoReg->din(MemtoReg_id);
		MemtoReg->dout(MemtoReg_exe);
		MemtoReg->clk(clk);
		MemtoReg->enable(enable);
		MemtoReg->reset(reset);

		Branch = new regT < bool >("Branch");
		Branch->din(Branch_id);
		Branch->dout(Branch_exe);
		Branch->clk(clk);
		Branch->enable(enable);
		Branch->reset(reset);

		RegWrite = new regT < bool >("RegWrite");
		RegWrite->din(RegWrite_id);
		RegWrite->dout(RegWrite_exe);
		RegWrite->clk(clk);
		RegWrite->enable(enable);
		RegWrite->reset(reset);

		ALUSrc = new regT < bool >("ALUSrc");
		ALUSrc->din(ALUSrc_id);
		ALUSrc->dout(ALUSrc_exe);
		ALUSrc->clk(clk);
		ALUSrc->enable(enable);
		ALUSrc->reset(reset);

		ALUOp = new regT < sc_uint<3> >("ALUOp");
		ALUOp->din(ALUOp_id);
		ALUOp->dout(ALUOp_exe);
		ALUOp->clk(clk);
		ALUOp->enable(enable);
		ALUOp->reset(reset);

		PC = new regT < sc_uint<32> >("PC");
		PC->din(PC_id);
		PC->dout(PC_exe);
		PC->clk(clk);
		PC->enable(enable);
		PC->reset(reset);

		valid = new regT < bool >("valid");
		valid->din(valid_id);
		valid->dout(valid_exe);
		valid->clk(clk);
		valid->enable(enable);
		valid->reset(reset);

	}
};

#endif
