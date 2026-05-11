#ifndef CAAEMaiOpenCancelEditor_h
#define CAAEMaiOpenCancelEditor_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Implementation of CATIMfgComputeToolPathCom.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the "Drilling" Late Type. 
//
//===========================================================================
//  Usage:
//  ------
//
//  Launch CATIA V5, Create a "Drilling" operation inside Prismatic
//       Machining Programmer, then click on cancel. 
//  
//===========================================================================
//  Inheritance:
//  ------------
//
//  CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  OnCancelButton
//
//===========================================================================

// Infrastructure interfaces
#include "CATBaseUnknown.h"

// Manufacturing Interfaces

class CAAEMaiOpenCancelEditor : public CATBaseUnknown
{
	CATDeclareClass;
  
public:
    CAAEMaiOpenCancelEditor();
    virtual ~CAAEMaiOpenCancelEditor();
 
    // OnCancelButton
	HRESULT OnCancelButton();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiOpenCancelEditor (const CAAEMaiOpenCancelEditor &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiOpenCancelEditor & operator  = (const CAAEMaiOpenCancelEditor &iObjectToCopy);
 
};
#endif


