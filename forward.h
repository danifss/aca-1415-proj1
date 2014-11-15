#ifndef FORWARDMOD_H
#define FORWARDMOD_H

/**
 *
 * forward module interface.
 */

#include <systemc.h>

/**
 * forward module.
 * forward module is the forward detection unit.
 *
 *   - input ports
 *   	- \c sc_uint<5> \c rs	   - first register being read 
 *   	- \c sc_uint<5> \c rt	   - second register being read 
 *   	- \c sc_uint<5> \c WriteReg_exe	   - register to be written (EXE)
 *   	- \c sc_uint<5> \c WriteReg_mem	   - register to be written (MEM)
 *   	- \c bool \c RegWrite_exe	   - control signal of writing registers (EXE)
 *   	- \c bool \c RegWrite_mem	   - control signal of writing registers (MEM)
 *   - output ports
 *   	- \c bool \c enable_pc      - enables PC update
 *   	- \c bool \c enable_ifid    - enables IF/ID update
 *   	- \c bool \c reset_idexe    - resets IF/EXE
 */

SC_MODULE( forward )
{
  public: 
    sc_in< sc_uint<5> >  rs_id, rt_id, rd_id;
    sc_in< sc_uint<5> >  rs_exe, rt_exe, rd_exe;
    sc_in< sc_uint<5> >  WriteReg_exe, WriteReg_mem, WriteReg_mem2, WriteReg_wb;
    sc_in< bool > RegWrite_exe, RegWrite_mem, RegWrite_mem2, RegWrite_wb;
    sc_in< sc_uint<5> > rs_if, rt_if, rd_if;

//	sc_in< bool > MemRead;
//	sc_in< bool > BranchTaken;
//  sc_in< bool > Jump;
//  sc_in< bool > JumpReg;
//  sc_in< bool > Link;


    sc_out< sc_uint<2> > forwd_idexe_r1, forwd_idexe_r2;
    sc_out< sc_uint<2> > forwd_exemem;
    sc_out< bool > forwd_ifid1_sel, forwd_ifid2_sel;
    sc_out< bool > mux_rs_sel, mux_rt_sel;

    SC_CTOR(forward)
    {      
        SC_METHOD(detect_forward);
        sensitive << rs_id << rt_id << rd_id
          << rs_exe << rt_exe << rd_exe
          << rs_if << rt_if << rd_if
		      << WriteReg_exe << RegWrite_exe
		      << WriteReg_mem << RegWrite_mem
          << WriteReg_mem2 << RegWrite_mem2
          << WriteReg_wb << RegWrite_wb;
			//<< MemRead << BranchTaken << Jump << JumpReg << Link;
   }
  
    void detect_forward();
};

#endif
