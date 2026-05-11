#ifndef CAAESysMyInterfaceForComponent_H
#define CAAESysMyInterfaceForComponent_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAASysComponent component and implementing the 
//  CAAISysMyInterface interface.
//
//  See the CAASysComponentCreate module which contains a sample to use
//  this interface.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysMyInterfaceForComponent : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysMyInterfaceForComponent();
    virtual ~CAAESysMyInterfaceForComponent();

    // CAAIMyInterface 
    // -------------------

    virtual HRESULT  Print();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysMyInterfaceForComponent(const CAAESysMyInterfaceForComponent &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysMyInterfaceForComponent & operator = (const CAAESysMyInterfaceForComponent &iObjectToCopy);

};
#endif
