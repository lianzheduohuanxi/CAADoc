#ifndef CAAEMaiToolPathDrillingCustomization_h
#define CAAEMaiToolPathDrillingCustomization_h

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
//  Data extension of the "Drilling" Late Type. 
//
//===========================================================================
//  Usage:
//  ------
//
//  Launch CATIA V5, Create a "Drilling" operation inside Prismatic
//       Machining Programmer, then replay it. 
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
//  ComputeToolPath
//
//===========================================================================

// Infrastructure interfaces
#include "CATBaseUnknown.h"
#include "CATIContainer.h"

// Manufacturing Interfaces
#include "CATIMfgToolPath.h"

class CAAEMaiToolPathDrillingCustomization : public CATBaseUnknown
{
  // Used in conjonction with CATImplementClass in the .cpp file
	CATDeclareClass;
  
public:
    CAAEMaiToolPathDrillingCustomization();
    virtual ~CAAEMaiToolPathDrillingCustomization();
 
    // ComputeToolPath
	//================
	// Compute the tool path of the current Drilling operation
	//
	//  ispContainer : Interface on the tool path container
	//  ospToolPath  : Computed tool path
	virtual HRESULT ComputeToolPath(const CATIContainer_var   &ispContainer,
                                          CATIMfgToolPath_var &ospToolPath);
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiToolPathDrillingCustomization
		(const CAAEMaiToolPathDrillingCustomization &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiToolPathDrillingCustomization & operator  = 
		(const CAAEMaiToolPathDrillingCustomization &iObjectToCopy);
 
};
#endif


