#ifndef CAAEAfrActivateWorkbenchOnPart_H
#define CAAEAfrActivateWorkbenchOnPart_H

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is a data extension of the MechanicalPart object. It is
//  an implementation of the CATIAfrActivateWorkbench interface in order to 
//  specify the first workbench to launch when a Part object is UI activated.
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from  
#include "CATString.h"        // Needed by GetInitialWorkbench

class CAAEAfrActivateWorkbenchOnPart: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrActivateWorkbenchOnPart();
    virtual ~CAAEAfrActivateWorkbenchOnPart();

    // GetInitialWorkbench
    // ------------
    // Returns the workbench identifier.
    //

    CATString & GetInitialWorkbench();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrActivateWorkbenchOnPart(const CAAEAfrActivateWorkbenchOnPart &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrActivateWorkbenchOnPart & operator = (const CAAEAfrActivateWorkbenchOnPart &iObjectToCopy);

  private:

      CATString _WbName ;

};
#endif
