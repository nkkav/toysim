/***************************************************************/
/*  File       : toy_isa.cpp
 *  Description: Instruction behaviors.
 *  Author     : Nikolaos Kavvadias <nikos@nkavvadias.com>
 *
 *  Copyright (C) 2010, 2011, 2012, 2013, 2014 Nikolaos Kavvadias
 *
 *  Author affiliation:
 *    Dr. Nikolaos Kavvadias
 *    Independent Consultant -- Research Scientist
 *    Kornarou 12 Rd., Nea Ampliani,
 *    35100 Lamia, Greece
 *                                                             
 *  Contact information for the ArchC team:                     
 *    The ArchC Team                                              
 *    Computer Systems Laboratory (LSC)                           
 *    IC-UNICAMP                                                  
 *    http://www.lsc.ic.unicamp.br                                
 */
/***************************************************************/

#include  "toy_isa.H"
#include  "toy_isa_init.cpp"
#include  "toy_bhv_macros.H"
#include  <stdio.h>
#include  <ctype.h>

//If you want debug information for this model, uncomment next line
//#define DEBUG_MODEL
#include "ac_debug_model.H"

using namespace toy_parms;

// Sign and bitwidth types for conversion operators (zxt, sxt)
#define T_UNSIGNED      0
#define T_SIGNED        1
#define T_BYTE          0
#define T_SHORT         1
#define T_WORD          2

#define SIGN_EXTEND_8(s)  ((signed int)((s & 0x00000080) ? (s | 0xffffff00) : (s & 0x000000ff)))
#define SIGN_EXTEND_16(s) ((signed int)((s & 0x00008000) ? (s | 0xffff0000) : (s & 0x0000ffff)))
#define ZERO_EXTEND_8(s)  ((unsigned int)((s & 0x000000ff)))
#define ZERO_EXTEND_16(s) ((unsigned int)((s & 0x0000ffff)))


//!User defined macros to reference registers.
#define Gp   13
#define Sp   14          
#define Ra   15
#define Pc   16


inline void update_cycle(ac_reg<unsigned>& ac_cycle, unsigned int increment)
{
  ac_cycle += increment;
}

//!Generic instruction behavior method.
void ac_behavior( instruction )
{
  dbg_printf("----- Cycle %#d -----\n", (int) CYC);
  dbg_printf("----- PC=%#x ----- %lld\n", (int) ac_pc, ac_instr_counter);
#ifndef NO_NEED_PC_UPDATE
  ac_pc += 2;
#endif   
};

//! Instruction Format behavior methods.
void ac_behavior( Type_R ){}
void ac_behavior( Type_I ){}


//!Behavior called before starting simulation
void ac_behavior(begin)
{
  dbg_printf("@@@ begin behavior @@@\n");
  RB[0] = 0;
  ac_pc = 0x00; // FIXME: Is this correct? (0x00 or 0x10 ?)
  CYC   = 0x00000000;
}

//!Behavior called after finishing simulation
void ac_behavior(end)
{
  int i;

  dbg_printf("@@@ end behavior @@@\n");
  printf("----- Cycle %#d -----\n", (int)CYC);
  // Report register contents.
  dbg_printf("@@@ Reporting RB register data @@@\n");
  //
  for (i = 0; i < 16; i++) {
    dbg_printf("RB[%#x] = %#x\n", i, RB[i]);
  }
}
        
//!Instruction load behavior method.
void ac_behavior( load )
{
  int temp;
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- mem[%d]\n", rd, imm8);
  if ((unsigned)imm8 == 255 && op == 8) {
    scanf("%4hX", &temp);
    DM.write(255, temp);
  }
  RB[rd] = DM.read(imm8);
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction store behavior method.
void ac_behavior( store )
{
  update_cycle(CYC, 1);
  dbg_printf("mem[%d] <- R[%d]\n", imm8, rd);
  DM.write(imm8, RB[rd]);
  if ((unsigned)imm8 == 255 && op == 9) {
    printf("%04hX\n", DM.read(255));  
  }
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction loadi behavior method.
void ac_behavior( loadi )
{
  int temp;	
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- mem[R[%d]]\n", rd, rt);
  if (RB[rt] == 255 && op == 10) {
    scanf("%4hX", &temp);
    DM.write(255, temp);
  }
  RB[rd] = DM.read(RB[rt] & 0xff);
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction storei behavior method.
void ac_behavior( storei )
{
  update_cycle(CYC, 1);
  dbg_printf("mem[R[%d]] <- R[%d]\n", rt, rd);
  DM.write(RB[rt] & 0xff, RB[rd]);
  if (RB[rt] == 255 && op == 11) {
    printf("%04hX\n", DM.read(255));  
  }
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction lda behavior method.
void ac_behavior( lda )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- %d\n", rd, imm8 & 0xFF);
  RB[rd] = imm8;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction add behavior method.
void ac_behavior( add )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- R[%d] + R[%d]\n", rd, rs, rt);
  RB[rd] = RB[rs] + RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction sub behavior method.
void ac_behavior( sub )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- R[%d] - R[%d]\n", rd, rs, rt);
  RB[rd] = RB[rs] - RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction instr_and behavior method.
void ac_behavior( instr_and )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- R[%d] & R[%d]\n", rd, rs, rt);
  RB[rd] = RB[rs] & RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction instr_xor behavior method.
void ac_behavior( instr_xor )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- R[%d] ^ R[%d]\n", rd, rs, rt);
  RB[rd] = RB[rs] ^ RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction shl behavior method.
void ac_behavior( shl )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- R[%d] << R[%d]\n", rd, rs, rt);
  RB[rd] = RB[rs] << RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction shr behavior method.
void ac_behavior( shr )
{
  update_cycle(CYC, 1);
  dbg_printf("R[%d] <- R[%d] >> R[%d]\n", rd, rs, rt);
  RB[rd] = RB[rs] >> RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};
     
//!Instruction jal behavior method.
void ac_behavior( jal )
{
  update_cycle(CYC, 2);
  dbg_printf("R[%d] <-- pc; pc <- %d\n", rd, imm8);
  // Save the value of PC + 8 (return address) in $ra ($31) and
  // jump to the address given by PC(31...28)||(addr<<2)
  // It must also flush the instructions that were loaded into the pipeline
  RB[Ra] = ac_pc+1; //ac_pc is pc+4, we need pc+8
  ac_pc = imm8;
//  addr = addr << 2;
//#ifndef NO_NEED_PC_UPDATE
//  ac_pc = (ac_pc & 0xF0000000) | addr;
//#endif
  dbg_printf("Target = %#x\n", imm8);
  dbg_printf("Return = %#x\n", ac_pc+1);
};

//!Instruction jreg behavior method.
void ac_behavior( jreg )
{
  update_cycle(CYC, 2);
  dbg_printf("pc <- R[%d]\n", rd);
#ifndef NO_NEED_PC_UPDATE
  ac_pc = RB[rd];
#endif
  dbg_printf("Target = %#x\n", RB[rd]);
};

//!Instruction jzer behavior method.
void ac_behavior( jzer )
{
  update_cycle(CYC, 2);
  dbg_printf("if (R[%d] == 0) pc <- %d\n", rd, imm8);
  if (RB[rd] == 0x00) {
#ifndef NO_NEED_PC_UPDATE
    ac_pc = imm8;
#endif
    dbg_printf("Taken to %#x\n", ac_pc);
  }
};

//!Instruction jpos behavior method.
void ac_behavior( jpos )
{
  update_cycle(CYC, 2);
  dbg_printf("if (R[%d] > 0) pc <- %d\n", rd, imm8);
  if (RB[rd] > 0x00) {
#ifndef NO_NEED_PC_UPDATE
    ac_pc = imm8;
#endif
    dbg_printf("Taken to %#x\n", ac_pc);
  }
};

//!Instruction halt behavior method.
void ac_behavior( instr_halt )
{
  update_cycle(CYC, 1);
  dbg_printf("halt\n");
  stop();
}
