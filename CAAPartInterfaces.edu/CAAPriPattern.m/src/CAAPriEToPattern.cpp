// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

/**
 * @quickReview BAG 04:02:25
 */


// Local Framework
#include "CAAPriEToPattern.h"

// PartInterfaces Framework
#include "CATIPrtToPattern.h"


// To declare that the class 
// is a DataExtension of (late type) CAAPriPatternPad
CATImplementClass(CAAPriEToPattern, 
									DataExtension, 
									CATBaseUnknown, 
									CAAPriPatternPad);

#include <TIE_CATIPrtToPattern.h>
TIE_CATIPrtToPattern(CAAPriEToPattern);

// To declare that PatternPad implements CATIPrtToPattern, insert 
// the following line in the interface dictionary:
//
// PatternPad  CATIPrtToPattern  libCAAPriPattern


//-------------------------------------------------------------------------
// SpecificPatternNecessity method
//-------------------------------------------------------------------------
boolean CAAPriEToPattern::SpecificPatternNecessity()
{
	return FALSE;
}

//-------------------------------------------------------------------------
// ValidForUserPattern method
//-------------------------------------------------------------------------
boolean CAAPriEToPattern::ValidForUserPattern()
{
	return FALSE;
}
