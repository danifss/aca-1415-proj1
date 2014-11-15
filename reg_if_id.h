#ifndef REG_IF_ID_H
#define REG_IF_ID_H

/**
 *
 * reg_if_id_t module interface.
 */

#include <systemc.h>

#include "regT.h"

/**
 * reg_if_id_t module.
 * reg_if_id_t module is the IF/ID pipeline register. 
 */

SC_MODULE(reg_if_id_t) {

	// Ports
	
	sc_in  < bool > clk;
	sc_in  < bool > reset;
	sc_in  < bool > enable;

	sc_in  < sc_uint<32> > inst_if, PC4_if;
	sc_out < sc_uint<32> > inst_id, PC4_id;

	sc_in  < sc_uint<32> > forwrd_ifid1_if, forwrd_ifid2_if; // forward signals
	sc_out < sc_uint<32> > forwrd_ifid1_id, forwrd_ifid2_id; // forward signals

	sc_in  < bool > mux_rs_sel_if, mux_rt_sel_if; // mux selection signals
	sc_out < bool > mux_rs_sel_id, mux_rt_sel_id; // mux selection signals

	sc_in  < sc_uint<32> > PC_if;     // only for visualization purposes
	sc_in  < bool >        valid_if;  // only for visualization purposes
	sc_out < sc_uint<32> > PC_id;     // only for visualization purposes
	sc_out < bool >        valid_id;  // only for visualization purposes

	// Modules

	regT < sc_uint<32> > *inst, *PC4;

	regT < sc_uint<32> > *forwrd_ifid1, *forwrd_ifid2;
	regT < bool > *mux_rs_sel, *mux_rt_sel;

	regT < sc_uint<32> > *PC;        // only for visualization purposes
	regT < bool > *valid;            // only for visualization purposes

	SC_CTOR(reg_if_id_t) {

		inst = new regT < sc_uint<32> > ("inst");;
		inst->din(inst_if);
		inst->dout(inst_id);
		inst->clk(clk);
		inst->enable(enable);
		inst->reset(reset);

		PC4 = new regT < sc_uint<32> > ("PC4");;
		PC4->din(PC4_if);
		PC4->dout(PC4_id);
		PC4->clk(clk);
		PC4->enable(enable);
		PC4->reset(reset);

		forwrd_ifid1 = new regT < sc_uint<32> > ("forwrd_ifid1");
		forwrd_ifid1->din(forwrd_ifid1_if);
		forwrd_ifid1->dout(forwrd_ifid1_id);
		forwrd_ifid1->clk(clk);
		forwrd_ifid1->enable(enable);
		forwrd_ifid1->reset(reset);

		forwrd_ifid2 = new regT < sc_uint<32> > ("forwrd_ifid2");
		forwrd_ifid2->din(forwrd_ifid2_if);
		forwrd_ifid2->dout(forwrd_ifid2_id);
		forwrd_ifid2->clk(clk);
		forwrd_ifid2->enable(enable);
		forwrd_ifid2->reset(reset);

		mux_rs_sel = new regT < bool > ("mux_rs_sel");
		mux_rs_sel->din(mux_rs_sel_if);
		mux_rs_sel->dout(mux_rs_sel_id);
		mux_rs_sel->clk(clk);
		mux_rs_sel->enable(enable);
		mux_rs_sel->reset(reset);

		mux_rt_sel = new regT < bool > ("mux_rt_sel");
		mux_rt_sel->din(mux_rt_sel_if);
		mux_rt_sel->dout(mux_rt_sel_id);
		mux_rt_sel->clk(clk);
		mux_rt_sel->enable(enable);
		mux_rt_sel->reset(reset);

		PC = new regT < sc_uint<32> > ("PC");;
		PC->din(PC_if);
		PC->dout(PC_id);
		PC->clk(clk);
		PC->enable(enable);
		PC->reset(reset);

		valid = new regT < bool > ("valid");;
		valid->din(valid_if);
		valid->dout(valid_id);
		valid->clk(clk);
		valid->enable(enable);
		valid->reset(reset);
		
	}
};

#endif
