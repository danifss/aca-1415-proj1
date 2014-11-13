//mips.cpp

/**
 *
 * MIPS module implementation.
 */

#include "mips.h"

/**
 * buils IF stage components 
 */
void mips::buildIF(void) {
    // Program Counter
    PCreg = new registo("PCregister");
    PCreg->din(NPC);
    PCreg->dout(PC);
    PCreg->clk(clk);
    PCreg->reset(reset);
    PCreg->enable(enable_pc);

    // Instruction Memory
    instmem = new imem("imem");
    instmem->addr(PC);
    instmem->inst(inst);

    // Adds 4 to Program Counter
    add4 = new add("add4");
    add4->op1(PC);
    add4->op2(const4);
    add4->res(PC4);

    // Selects Next Program Counter Value
    mPC = new muxj< sc_uint < 32 > > ("mPC");
    mPC->sel(BranchTaken);
    mPC->selj(Jump);
    mPC->din0(PC4);
    mPC->din1(BranchTarget);
    mPC->dinj(JumpTarget); //ALTERAR PARA JUMP TARGET
    mPC->dout(NPC_prev);
}

/**
 * buils ID stage components 
 */
void mips::buildID(void) {
    // Decodes Instruction
    dec1 = new decode("decode");
    dec1->inst(inst_id);
    dec1->rs(rs);
    dec1->rt(rt);
    dec1->rd(rd);
    dec1->imm(imm);
    dec1->opcode(opcode);
    dec1->shamt(shamt);
    dec1->funct(funct);

    // Selects Register to Write
    mr = new mux< sc_uint < 5 > > ("muxRDst");
    mr->sel(RegDst);
    mr->din0(rt);
    mr->din1(rd);
    mr->dout(WriteReg_prev);


    // If jal selects reg31 to write
    link = new muxl< sc_uint < 5 > > ("muxJal");
    link->sel(Link);
    link->din0(WriteReg_prev);
    link->dout(WriteReg);


    // Register File
    rfile = new regfile("regfile");

    rfile->reg1(rs);
    rfile->reg2(rt);
    rfile->regwrite(WriteReg_wb);
    rfile->data1(regdata1);
    rfile->data2(regdata2);

    rfile->wr(RegWrite_wb);
    rfile->datawr(WriteVal);

    rfile->clk(clk);
    rfile->reset(reset);

    // 16 to 32 bit signed Immediate extension
    e1 = new ext("ext");
    e1->din(imm);
    e1->dout(imm_ext);

    // Control
    ctrl = new control("control");

    ctrl->opcode(opcode);
    ctrl->funct(funct);
    ctrl->RegDst(RegDst);
    ctrl->Branch(Branch);
    ctrl->BranchType(BranchType);
    ctrl->Jump(Jump);
    ctrl->JumpReg(JumpReg);
    ctrl->Link(Link);
    ctrl->MemRead(MemRead);
    ctrl->MemWrite(MemWrite);
    ctrl->MemtoReg(MemtoReg);
    ctrl->ALUOp(ALUOp);
    ctrl->ALUSrc(ALUSrc);
    ctrl->RegWrite(RegWrite);


    // shift left 2 imm_ext 
    sl2 = new shiftl2("sl2");
    sl2->din(imm_ext);
    sl2->dout(addr_ext);


    // obter 4 bits mais significativos do PC+4
    pc4bitms = new andbitwise("pc4bitms");
    pc4bitms->din1(PC4_id);
    pc4bitms->dout(PC4_id_4bitms);


    // (pc+4) | addr_ext
    jumpT = new orbitwise("pc4addr");
    jumpT->din1(PC4_id_4bitms);
    jumpT->din2(addr_ext);
    jumpT->dout(JumpTarget);


    // Jump Register
    jumpM = new mux< sc_uint < 32 > > ("muxJump");
    jumpM->sel(JumpReg);
    jumpM->din0(NPC_prev);
    jumpM->din1(regdata1);
    jumpM->dout(NPC);

    // Jump and Link

    // Adds Branch Immediate to Program Counter + 4
    addbr = new add("addbr");
    addbr->op1(PC4_id);
    addbr->op2(addr_ext);
    addbr->res(BranchTarget);


    // Comparator
    comp = new compare("comp");
    comp->op1(regdata1);
    comp->op2(regdata2);
    comp->opt(BranchType);
    comp->res(res_comp);


    // Enables Branch
    a1 = new andgate("a1");
    a1->din1(Branch);
    a1->din2(res_comp);
    a1->dout(BranchTaken);

}

/**
 * buils EXE stage components 
 */
void mips::buildEXE(void) {
    // Selects second operand of ALU
    m1 = new mux< sc_uint < 32 > > ("muxOp");
    m1->sel(ALUSrc_exe);
    m1->din0(regb_exe);
    m1->din1(imm_exe);
    m1->dout(ALUIn2);

    // ALU
    alu1 = new alu("alu");
    alu1->din1(rega_exe);
    alu1->din2(ALUIn2);
    alu1->op(ALUOp_exe);
    alu1->dout(ALUOut);
    alu1->zero(Zero);

    // selects RS or RT for destination register
    mux_rsrt = new mux< sc_uint<5> > ("mux_rsrt");
    mux_rsrt->sel(RegDst_exe);
    mux_rsrt->din0(rt_exe);
    mux_rsrt->din1(rd_exe);
    mux_rsrt->dout(WriteReg_exe);
}

/**
 * buils MEM stage components 
 */
void mips::buildMEM(void) {
    // Data Memory
    datamem = new dmem("datamem");

    datamem->addr(ALUOut_mem);
    datamem->din(regb_mem);
    datamem->dout(MemOut);
    datamem->wr(MemWrite_mem);
    datamem->rd(MemRead_mem);
    datamem->clk(clk);


}

/**
 * buils MEM2 stage components 
 */
void mips::buildMEM2(void) {
    // nada a fazer aqui :)
}

/**
 * buils WB stage components 
 */
void mips::buildWB(void) {
    // Selects Result
    // m2 = new mux< sc_uint < 32 > > ("muxRes");
    // m2->sel(MemtoReg_wb);
    // m2->din0(ALUOut_wb);
    // m2->din1(MemOut_wb);
    // m2->dout(WriteVal_prev);

    // muxlinkval = new mux< sc_uint < 32 > > ("muxlinkval");
    // muxlinkval->sel(Link_wb);
    // muxlinkval->din0(WriteVal_prev);
    // muxlinkval->din1(PC4_wb);
    // muxlinkval->dout(WriteVal);

    //Selects Result
    m3 = new muxj< sc_uint<32> > ("muxRes");
    m3->selj(Link_wb);     // MSB
    m3->sel(MemtoReg_wb);  // LSB
    m3->din0(ALUOut_wb);   // valor da ALU
    m3->din1(MemOut_wb);   // valor da MEM
    m3->dinj(PC4_wb);      // valor PC+4
    m3->dout(WriteVal);
}

/**
 * Instantiates the pipeline registers and calls other functions to
 * buils stage specific components 
 */
void mips::buildArchitecture(void) {

    const4 = 4;
    const1 = true;

    buildIF();

    //reg_if_id
    reg_if_id = new reg_if_id_t("reg_if_id");
    reg_if_id->inst_if(inst);
    reg_if_id->inst_id(inst_id);
    reg_if_id->PC4_if(PC4);
    reg_if_id->PC4_id(PC4_id);
    reg_if_id->PC_if(PC);
    reg_if_id->PC_id(PC_id);
    reg_if_id->valid_if(const1);
    reg_if_id->valid_id(valid_id);
    reg_if_id->clk(clk);
    reg_if_id->reset(reset_ifid);
    reg_if_id->enable(enable_ifid);

    or_reset_ifid = new orgate("or_reset_ifid");
    or_reset_ifid->din1(reset);
    or_reset_ifid->din2(reset_haz_ifid);
    or_reset_ifid->dout(reset_ifid);

    buildID();

    //reg_id_exe
    reg_id_exe = new reg_id_exe_t("reg_id_exe");
    reg_id_exe->Link_id(Link);
    reg_id_exe->Link_exe(Link_exe);
    reg_id_exe->rega_id(regdata1);
    reg_id_exe->rega_exe(rega_exe);
    reg_id_exe->regb_id(regdata2);
    reg_id_exe->regb_exe(regb_exe);
    reg_id_exe->imm_id(imm_ext);
    reg_id_exe->imm_exe(imm_exe);
    reg_id_exe->rs_id(rs);
    reg_id_exe->rs_exe(rs_exe);
    reg_id_exe->rt_id(rt);
    reg_id_exe->rt_exe(rt_exe);
    reg_id_exe->rd_id(rd);
    reg_id_exe->rd_exe(rd_exe);
    reg_id_exe->PC4_id(PC4_id);
    reg_id_exe->PC4_exe(PC4_exe);
//    reg_id_exe->WriteReg_id(WriteReg);
//    reg_id_exe->WriteReg_exe(WriteReg_exe);
    reg_id_exe->MemRead_id(MemRead);
    reg_id_exe->MemRead_exe(MemRead_exe);
    reg_id_exe->MemWrite_id(MemWrite);
    reg_id_exe->MemWrite_exe(MemWrite_exe);
    reg_id_exe->MemtoReg_id(MemtoReg);
    reg_id_exe->MemtoReg_exe(MemtoReg_exe);
    reg_id_exe->Branch_id(Branch);
    reg_id_exe->Branch_exe(Branch_exe);
    reg_id_exe->RegWrite_id(RegWrite);
    reg_id_exe->RegWrite_exe(RegWrite_exe);
    reg_id_exe->ALUSrc_id(ALUSrc);
    reg_id_exe->ALUSrc_exe(ALUSrc_exe);
    reg_id_exe->ALUOp_id(ALUOp);
    reg_id_exe->ALUOp_exe(ALUOp_exe);
    reg_id_exe->RegDst_id(RegDst);
    reg_id_exe->RegDst_exe(RegDst_exe);
    reg_id_exe->PC_id(PC_id);
    reg_id_exe->PC_exe(PC_exe);
    reg_id_exe->valid_id(valid_id);
    reg_id_exe->valid_exe(valid_exe);
    reg_id_exe->clk(clk);
    reg_id_exe->reset(reset_idexe);
    reg_id_exe->enable(const1);

    or_reset_idexe = new orgate("or_reset_idexe");
    or_reset_idexe->din1(reset);
    or_reset_idexe->din2(reset_haz_idexe);
    or_reset_idexe->dout(reset_idexe);


    buildEXE();

    //reg_exe_mem
    reg_exe_mem = new reg_exe_mem_t("reg_exe_mem");
    reg_exe_mem->PC4_exe(PC4_exe);
    reg_exe_mem->PC4_mem(PC4_mem);
    reg_exe_mem->Link_exe(Link_exe);
    reg_exe_mem->Link_mem(Link_mem);
    reg_exe_mem->aluOut_exe(ALUOut);
    reg_exe_mem->aluOut_mem(ALUOut_mem);
    reg_exe_mem->MemRead_exe(MemRead_exe);
    reg_exe_mem->MemRead_mem(MemRead_mem);
    reg_exe_mem->MemWrite_exe(MemWrite_exe);
    reg_exe_mem->MemWrite_mem(MemWrite_mem);
    reg_exe_mem->MemtoReg_exe(MemtoReg_exe);
    reg_exe_mem->MemtoReg_mem(MemtoReg_mem);
    reg_exe_mem->RegWrite_exe(RegWrite_exe);
    reg_exe_mem->RegWrite_mem(RegWrite_mem);
    reg_exe_mem->Branch_exe(Branch_exe);
    reg_exe_mem->Branch_mem(Branch_mem);
    reg_exe_mem->BranchTarget_exe(BranchTarget);
    reg_exe_mem->BranchTarget_mem(BranchTarget_mem);
    reg_exe_mem->regb_exe(regb_exe);
    reg_exe_mem->regb_mem(regb_mem);
    reg_exe_mem->WriteReg_exe(WriteReg_exe);
    reg_exe_mem->WriteReg_mem(WriteReg_mem);
    reg_exe_mem->rs_exe(rs_exe);
    reg_exe_mem->rs_mem(rs_mem);
    reg_exe_mem->PC_exe(PC_exe);
    reg_exe_mem->PC_mem(PC_mem);
    reg_exe_mem->valid_exe(valid_exe);
    reg_exe_mem->valid_mem(valid_mem);
    reg_exe_mem->clk(clk);
    reg_exe_mem->reset(reset_exemem);
    reg_exe_mem->enable(const1);

    or_reset_exemem = new orgate("or_reset_exemem");
    or_reset_exemem->din1(reset);
    or_reset_exemem->din2(reset_haz_exemem);
    or_reset_exemem->dout(reset_exemem);

    buildMEM();

    reg_mem_mem2 = new reg_mem_mem2_t("reg_mem_mem2");
    reg_mem_mem2->PC4_mem(PC4_mem);
    reg_mem_mem2->PC4_mem2(PC4_mem2);
    reg_mem_mem2->Link_mem(Link_mem);
    reg_mem_mem2->Link_mem2(Link_mem2);
    reg_mem_mem2->aluOut_mem(ALUOut_mem);
    reg_mem_mem2->aluOut_mem2(ALUOut_mem2);
    reg_mem_mem2->MemtoReg_mem(MemtoReg_mem);
    reg_mem_mem2->MemtoReg_mem2(MemtoReg_mem2);
    reg_mem_mem2->RegWrite_mem(RegWrite_mem);
    reg_mem_mem2->RegWrite_mem2(RegWrite_mem2);
    reg_mem_mem2->Branch_mem(Branch_mem);
    reg_mem_mem2->Branch_mem2(Branch_mem2);
    reg_mem_mem2->WriteReg_mem(WriteReg_mem);
    reg_mem_mem2->WriteReg_mem2(WriteReg_mem2);
    reg_mem_mem2->rs_mem(rs_mem);
    reg_mem_mem2->rs_mem2(rs_mem2);
    reg_mem_mem2->PC_mem(PC_mem);
    reg_mem_mem2->PC_mem2(PC_mem2);
    reg_mem_mem2->valid_mem(valid_mem);
    reg_mem_mem2->valid_mem2(valid_mem2);
    reg_mem_mem2->clk(clk);
    reg_mem_mem2->reset(reset);
    reg_mem_mem2->enable(const1);

    buildMEM2();

    //reg_mem_wb
    reg_mem2_wb = new reg_mem2_wb_t("reg_mem_wb");
    reg_mem2_wb->PC4_mem2(PC4_mem2);
    reg_mem2_wb->PC4_wb(PC4_wb);
    reg_mem2_wb->Link_mem2(Link_mem2);
    reg_mem2_wb->Link_wb(Link_wb);
    reg_mem2_wb->aluOut_mem2(ALUOut_mem2);
    reg_mem2_wb->aluOut_wb(ALUOut_wb);
    reg_mem2_wb->memOut_mem2(MemOut);
    reg_mem2_wb->memOut_wb(MemOut_wb);
    reg_mem2_wb->MemtoReg_mem2(MemtoReg_mem2);
    reg_mem2_wb->MemtoReg_wb(MemtoReg_wb);
    reg_mem2_wb->RegWrite_mem2(RegWrite_mem2);
    reg_mem2_wb->RegWrite_wb(RegWrite_wb);
    reg_mem2_wb->WriteReg_mem2(WriteReg_mem2);
    reg_mem2_wb->WriteReg_wb(WriteReg_wb);
    reg_mem2_wb->PC_mem2(PC_mem2);
    reg_mem2_wb->PC_wb(PC_wb);
    reg_mem2_wb->valid_mem2(valid_mem2);
    reg_mem2_wb->valid_wb(valid_wb);
    reg_mem2_wb->clk(clk);
    reg_mem2_wb->reset(reset);
    reg_mem2_wb->enable(const1);

    buildWB();

    hazard_unit = new hazard("hazard_unit");
    hazard_unit->rs(rs);
    hazard_unit->rt(rt);
    hazard_unit->WriteReg_exe(WriteReg_exe);
    hazard_unit->RegWrite_exe(RegWrite_exe);
    hazard_unit->WriteReg_mem(WriteReg_mem);
    hazard_unit->RegWrite_mem(RegWrite_mem);
    hazard_unit->WriteReg_mem2(WriteReg_mem2);
    hazard_unit->RegWrite_mem2(RegWrite_mem2);
    hazard_unit->enable_pc(enable_pc);
    hazard_unit->enable_ifid(enable_ifid);
    hazard_unit->reset_idexe(reset_haz_idexe);
    hazard_unit->MemRead(MemRead);
    hazard_unit->reset_ifid(reset_haz_ifid);
    hazard_unit->reset_exemem(reset_haz_exemem);
    hazard_unit->BranchTaken(BranchTaken);
    hazard_unit->Jump(Jump);
    hazard_unit->JumpReg(JumpReg);
    hazard_unit->Link(Link);
}

mips::~mips(void) {
    delete PCreg;
    delete instmem;
    delete add4;
    delete mPC;
    delete dec1;
    delete mr;
    delete link;
    delete rfile;
    delete e1;
    delete ctrl;
    delete sl2;
    delete pc4bitms;
    delete jumpT;
    delete jumpM;
    delete addbr;
    delete comp;
    delete a1;
    delete m1;
    delete alu1;
    delete mux_rsrt;
    delete datamem;
    delete m3;
//    delete m2;
//    delete muxlinkval;

    delete hazard_unit;
    delete or_reset_ifid;
    delete or_reset_idexe;
    delete or_reset_exemem;
    delete reg_if_id;
    delete reg_id_exe;
    delete reg_exe_mem;
    delete reg_mem_mem2;
    delete reg_mem2_wb;
}
