#ifndef REG_MEM_MEM2_H
#define REG_MEM_MEM2_H

/**
 *
 * reg_mem_mem2_t module interface.
 */

#include <systemc.h>

#include "regT.h"



SC_MODULE(reg_mem_mem2_t) {

    // Ports

    sc_in  < bool > clk;
    sc_in  < bool > reset;
    sc_in  < bool > enable;

    sc_in  < bool > Link_mem;
    sc_out  < bool > Link_mem2;

    sc_in  < sc_uint<32> > aluOut_mem, PC4_mem;
    sc_out < sc_uint<32> > aluOut_mem2, PC4_mem2;

    sc_in  < sc_uint<5> > WriteReg_mem, rs_mem;
    sc_out < sc_uint<5> > WriteReg_mem2, rs_mem2;

    sc_in  < bool > MemtoReg_mem, RegWrite_mem;
    sc_out < bool > MemtoReg_mem2, RegWrite_mem2;

    sc_in  < sc_uint<32> > PC_mem;    // only for visualization purposes
    sc_out < sc_uint<32> > PC_mem2;   // only for visualization purposes
    sc_in  < bool > valid_mem;        // only for visualization purposes
    sc_out < bool > valid_mem2;       // only for visualization purposes
    sc_in  < bool > Branch_mem;       // only for visualization purposes
    sc_out < bool > Branch_mem2;      // only for visualization purposes

    // Modules

    regT < sc_uint<32> > *aluOut, *PC4;
    regT < sc_uint<5> > *WriteReg, *rs;
    regT < bool > *MemtoReg, *RegWrite, *Link;

    regT < sc_uint<32> > *PC;        // only for visualization purposes
    regT < bool > *valid, *Branch;   // only for visualization purposes

    SC_CTOR(reg_mem_mem2_t) {

        PC4 = new regT < sc_uint<32> > ("pc4exemem");;
        PC4->din(PC4_mem);
        PC4->dout(PC4_mem2);
        PC4->clk(clk);
        PC4->enable(enable);
        PC4->reset(reset);

        Link = new regT < bool >("linkexemem");
        Link->din(Link_mem);
        Link->dout(Link_mem2);
        Link->clk(clk);
        Link->enable(enable);
        Link->reset(reset);

        aluOut = new regT < sc_uint<32> > ("aluOut");;
        aluOut->din(aluOut_mem);
        aluOut->dout(aluOut_mem2);
        aluOut->clk(clk);
        aluOut->enable(enable);
        aluOut->reset(reset);

        WriteReg = new regT < sc_uint<5> > ("WriteReg");;
        WriteReg->din(WriteReg_mem);
        WriteReg->dout(WriteReg_mem2);
        WriteReg->clk(clk);
        WriteReg->enable(enable);
        WriteReg->reset(reset);

        rs = new regT < sc_uint<5> > ("rs");;
        rs->din(rs_mem);
        rs->dout(rs_mem2);
        rs->clk(clk);
        rs->enable(enable);
        rs->reset(reset);

        MemtoReg = new regT < bool >("MemtoReg");
        MemtoReg->din(MemtoReg_mem);
        MemtoReg->dout(MemtoReg_mem2);
        MemtoReg->clk(clk);
        MemtoReg->enable(enable);
        MemtoReg->reset(reset);
        
        // Visualization purposes
        Branch = new regT < bool >("Branch");
        Branch->din(Branch_mem);
        Branch->dout(Branch_mem2);
        Branch->clk(clk);
        Branch->enable(enable);
        Branch->reset(reset);

        RegWrite = new regT < bool >("RegWrite");
        RegWrite->din(RegWrite_mem);
        RegWrite->dout(RegWrite_mem2);
        RegWrite->clk(clk);
        RegWrite->enable(enable);
        RegWrite->reset(reset);

        // Visualization purposes
        PC = new regT < sc_uint<32> > ("PC");;
        PC->din(PC_mem);
        PC->dout(PC_mem2);
        PC->clk(clk);
        PC->enable(enable);
        PC->reset(reset);

        valid = new regT < bool > ("valid");;
        valid->din(valid_mem);
        valid->dout(valid_mem2);
        valid->clk(clk);
        valid->enable(enable);
        valid->reset(reset);
    }
};

#endif