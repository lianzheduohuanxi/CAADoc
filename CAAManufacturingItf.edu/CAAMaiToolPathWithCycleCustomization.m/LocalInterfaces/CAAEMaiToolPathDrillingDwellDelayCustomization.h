#ifndef CAAEMaiToolPathDrillingDwellDelayCustomization_h
#define CAAEMaiToolPathDrillingDwellDelayCustomization_h

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
//  Data extension of the "DrillingDwellDelay" Late Type. 
//
//===========================================================================
//  Usage:
//  ------
//
//  Launch CATIA V5, Create a "Drilling Dwell Delay" operation inside Prismatic
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

class CAAEMaiToolPathDrillingDwellDelayCustomization : public CATBaseUnknown
{
  // Used in conjonction with CATImplementClass in the .cpp file
	CATDeclareClass;
  
public:
    CAAEMaiToolPathDrillingDwellDelayCustomization();
    virtual ~CAAEMaiToolPathDrillingDwellDelayCustomization();
 
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
    CAAEMaiToolPathDrillingDwellDelayCustomization(const CAAEMaiToolPathDrillingDwellDelayCustomization &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiToolPathDrillingDwellDelayCustomization & operator  = (const CAAEMaiToolPathDrillingDwellDelayCustomization &iObjectToCopy);
 
};
#endif


