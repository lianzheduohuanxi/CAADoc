#ifndef CAAPriEToPattern_H
#define CAAPriEToPattern_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//=========================================================================
//  Sample code for : Part Interfaces
//  Mission					: Implement interface CATIPrtToPattern
//									
//	
//  Type					  : shared library
//  Inputs					: 
//  Outputs					:  
//	 
//  Illustrates			: CATIPrtToPattern interface implementation
//                  : for PatternPad feature
//										
//
// Abstract of the sample	:
// ------------------------
//		
//		
//===========================================================================

#include "CATBaseUnknown.h" // To derive from CATBaseUnknown
#include "CATDiaAction.h"

class CAAPriEToPattern : public CATBaseUnknown
{
  CATDeclareClass;

  public:

	  // implemented
    boolean SpecificPatternNecessity();

    // implemented
    boolean ValidForUserPattern();
};
#endif
