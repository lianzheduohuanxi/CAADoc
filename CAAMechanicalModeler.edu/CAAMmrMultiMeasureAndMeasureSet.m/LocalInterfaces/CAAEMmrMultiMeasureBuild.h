#ifndef CAAEMmrMultiMeasureBuild_H
#define CAAEMmrMultiMeasureBuild_H

// COPYRIGHT DASSAULT SYSTEMES 2007
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  DataExtension implementing the CATIBuild interface
//  which  manages the replacement of a Feature by another one for a given Role.   
//
//                   
//  This extension extends the MmrMultiMeasure Features.
//
//===========================================================================
#include "CATIBuild.h"

class CATUnicodeString;
class CATISpecObject_var;

class CAAEMmrMultiMeasureBuild: public CATIBuild
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

public:
	// Constructor - Destructor //
	CAAEMmrMultiMeasureBuild();
  virtual ~CAAEMmrMultiMeasureBuild();
	
  // CATIBuild's Methods //
  HRESULT Build();

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrMultiMeasureBuild(CAAEMmrMultiMeasureBuild&);
    CAAEMmrMultiMeasureBuild& operator=(CAAEMmrMultiMeasureBuild&);

    void RaiseAnError(const CATUnicodeString& iErrorLabel, CATISpecObject_var &iAssociatedFeature);
};
#endif
