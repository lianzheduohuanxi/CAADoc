#ifndef CAAPriEShapeFeatProp_H
#define CAAPriEShapeFeatProp_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: Implement interface CATIShapeFeatureProperties
//									
//	
//  Type				    : shared library
//  Inputs					: 
//  Outputs					:
//	 
//  Illustrates     : methods implementation to allow Mechanical 
//                  : Design Form Feature to be patterned.
//										
// Abstract of the sample	:
// ------------------------
//		
//  In this sample we have implemented the mandatory methods to define the properties 
//  of the PatternPad feature:
//  
//
//  Return code of IsAFreeFormFeature   : 1
//  Return code of IsAContextualFeature : 0
//  Return code of CanBePatterned       : 1
//==========================================================================


#include "CATBaseUnknown.h"    // To derive from CATBaseUnknown
#include "CATUnicodeString.h"  // To get string properties
#include "CATMathPlane.h"      // To manage plane

class CATListValCATISpecObject_var;
class CATISpecObject_var;

class CAAPriEShapeFeatProp : public CATBaseUnknown
{
  CATDeclareClass;

  public:
    
    CAAPriEShapeFeatProp();

	virtual ~CAAPriEShapeFeatProp();

    // Indicates if the PatternPad is a form feature
    int IsAFreeFormFeature();

    // Indicates if the PatternPad is a contextual feature
    int  IsAContextualFeature ( );
    
    // Returns the polarity of the PatternPad
    CATUnicodeString GetPolarity ( ) ;
	
    // Returns the sketch associated to the profile of
    // the PatternPad
    CATListValCATISpecObject_var GiveMeYourFavoriteSketches();

    // Returns the BRep specifications of the PatternPad
    CATListValCATISpecObject_var GiveMeYourBRepSpecifications();

    // Indicates if the PatternPad has an axis
    int HasAnAxis() ;

    // Indicates if the PatternPad has an axis
    int HasAnAxis(CATBaseUnknown_var Elt) ;

    // Returns the bouding plane of the PatternPad
    CATMathPlane GetBoundingPlane(CATUnicodeString& Side);

    // Indicates if the PatternPad can be patterned
    int CanBePatterned();
};
#endif
