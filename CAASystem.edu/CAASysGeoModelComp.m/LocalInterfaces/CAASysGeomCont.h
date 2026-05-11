#ifndef CAASysGeomCont_H
#define CAASysGeomCont_H

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysGeomCont component.
//
//  This component is the container of the document, that is to say an object
//  which creates and contains all the document's object.
//
//  
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"


class  CAASysGeomCont: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysGeomCont();
    virtual ~CAASysGeomCont();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysGeomCont(const CAASysGeomCont &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysGeomCont & operator = (const CAASysGeomCont &iObjectToCopy);

};
#endif
