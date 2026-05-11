// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Class "CAAOsmAddOp":
// -------------------------------
//
// This is the implementation of the CATIBuild interface for the "CAAOsmAddOp" feature.
// A "Build" operation calculates the values of attributes according to their
// pre-defined function.  Its execution is triggered by the execution of an
// "Update" operation so as to update all current values.  To perform this "Build"
// operation, the three attributes of the "CAAOsmAdd" feature are retrieved, the values of
// the first two, "First" and "Second" are added together and their sum is stored
// as the value of the "Sum" attribute.  Thus, "Sum" wil have an updated value
// whenever an "Update" operation is requested.

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

#ifndef CAAOsmAddOp_H_ 
#define CAAOsmAddOp_H_ 

#include "CATBaseUnknown.h" 

class CAAOsmAddOp : public CATBaseUnknown 
{
 public:

  CATDeclareClass;
  HRESULT	Build() ; 
};
#endif
