#ifndef CAAESysComponentBOA_H
#define CAAESysComponentBOA_H

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of base class CAASysComponentBOA
//  for the implementation of the interface CAAISysInterface 
//  using the Basic Object Adapter (BOA).
//
//  See the CAASysUseBOA module which contains a sample to use
//  this interface.
//
//===========================================================================

// System Framework
#include "CAAISysInterface.h"   //Needed to derive from CAAISysInterface

class CAAESysComponentBOA : public CAAISysInterface
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysComponentBOA();
    virtual ~CAAESysComponentBOA();

    // CAAISysInterface 
    // -------------------

    virtual HRESULT ToString();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysComponentBOA(const CAAESysComponentBOA &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysComponentBOA & operator = (const CAAESysComponentBOA &iObjectToCopy);

};
#endif
