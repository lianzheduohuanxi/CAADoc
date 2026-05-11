#ifndef CAAISysPoint_h
#define CAAISysPoint_h

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a point object.
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
//  SetCoord/GetCoord
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// local Framework
#include "CAASysGeoModelInf.h" // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysPoint;

class ExportedByCAASysGeoModelInf CAAISysPoint : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;

  public:

    virtual HRESULT SetCoord(const float iX, const float iY, const float iZ)  = 0;
    virtual HRESULT GetCoord(float & oX, float & oY, float & oZ)  const = 0;

};

#endif
