// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Class "CAAOsmSquareOp":
// ----------------------------------
//
// This is the implementation of the CATIBuild interface for the "CAAOsmSquareOp" feature.
// A "Build" operation calculates the values of attributes according to their
// pre-defined function.  Its execution is triggered by the execution of an
// "Update" operation so as to update all current values.  To perform this "Build"
// operation, the two attributes of the "CAAOsmSquare" feature are retrieved, the value
// of the first, "Num", is squared and the result stored as the value of the
// second, "Square" attribute.  Thus, the attribute "Square" will have an updated
// value whenever an "Update" operation is requested on this feature.
//
//=============================================================================
//  Main Methods:
//  ------------
//
//  GetAttrKey:   Retrieves the attribute key for a given attribute name on a
//                   given feature.
//  GetInteger:   Retrieves the integer value for a given attribute key on a given
//                   feature.
//  SetInteger:   Assigns an integer value to a given attribute key on a given
//                   feature.

//=============================================================================
//  Return Errors:
//  -------------
//  1 - ERROR in QueryInterface
//  2 - ERROR in GetAttrKey
//
//=============================================================================

#ifndef CAAOsmSquareOp_H_ 
#define CAAOsmSquareOp_H_ 

#include "CATBaseUnknown.h" 

class CAAOsmSquareOp : public CATBaseUnknown
{
 public:

  CATDeclareClass;
  HRESULT	Build() ; 
};
#endif
