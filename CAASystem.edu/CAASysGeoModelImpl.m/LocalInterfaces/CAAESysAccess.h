#ifndef CAAESysAccess_H
#define CAAESysAccess_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAISysAccess interface which associates a 
//  container with its objects in the CAAGeometry document.
//  Every container's object implements this interface to know its
//  container. 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  SetContainer: Sets the container
//  GetContainer: Retrieves the container
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"  //Needed to derive from CATBaseUnknown


class CAAESysAccess : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysAccess();
    virtual ~CAAESysAccess();

    // Sets the container
    virtual  HRESULT  SetContainer (CATBaseUnknown * iContainer) ;
    // Retrieves the container
    virtual  HRESULT  GetContainer(CATBaseUnknown  ** oContainer) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysAccess(const CAAESysAccess &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysAccess & operator = (const CAAESysAccess &iObjectToCopy);

  private:

    CATBaseUnknown      * _pContainer ;

};
#endif
