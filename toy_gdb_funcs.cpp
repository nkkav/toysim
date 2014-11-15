/***************************************************************/
/*  File       : toy_gdb_funcs.cpp
 *  Description: GDB support for the Princeton TOY machien 
 *               simulator.
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

#include "toy.H"

// 'using namespace' statement to allow access to all
// toy-specific datatypes.
using namespace toy_parms;

int toy::nRegs(void) {
   return 27; //73;
}

ac_word toy::reg_read( int reg ) {
  /* general purpose registers */
  if ( ( reg >= 0 ) && ( reg < 16 ) )
    return RB.read( reg );
  else {
    /* pc */
    if ( reg == 16 )
      return ac_pc;
  }

  return 0;
}

void toy::reg_write( int reg, ac_word value ) {
  /* general purpose registers */
  if ( ( reg >= 0 ) && ( reg < 16 ) )
    RB.write( reg, value );
  else
    {
      /* pc */
      if ( reg == 16 )
        ac_pc = value;
    }
}

unsigned short int toy::mem_read( unsigned int address ) {
  return IM->read( address );
}

void toy::mem_write( unsigned int address, unsigned short int word ) {
  IM->write( address, word );
}
