#ifndef CAAECafRootProperties_H
#define CAAECafRootProperties_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIRootProperties interface. 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//     
//===========================================================================
//  Main Methods:
//  -------------
//  
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"     // to derive from  CATBaseUnknown
#include "CATListOfCATString.h" // Needed by the GetListOfEditors method

class CAAECafRootProperties: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAECafRootProperties();
    virtual ~CAAECafRootProperties();

    /**
    * Returns list of properties editors associated to the selection.
    */

    virtual CATListOfCATString GetListOfEditors ()  ;

    /**
    * 
    * Method to give the father associated to the selection.
    */
    virtual void GetAssociatedObject () ; 

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafRootProperties(const CAAECafRootProperties &iObjectToCopy);
    	
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafRootProperties & operator = (const CAAECafRootProperties &iObjectToCopy);
    	
};
#endif
