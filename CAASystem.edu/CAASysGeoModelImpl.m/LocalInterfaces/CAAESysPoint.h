#ifndef CAAESysPoint_H
#define CAAESysPoint_H

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysPoint component and implementing the 
//  CAAISysPoint interface.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  SetCoord/GetCoord
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"            // to derive from  CATBaseUnknown

class CAAESysPoint: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysPoint();
    virtual ~CAAESysPoint();

    virtual HRESULT SetCoord(const float iX, const float iY, const float iZ ) ; 
    virtual HRESULT GetCoord(float     & oX, float     & oY, float     & oZ )  const  ;
 
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysPoint(const CAAESysPoint &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysPoint & operator = (const CAAESysPoint &iObjectToCopy);

  private:

    float _X, _Y, _Z  ;
	
};
#endif
