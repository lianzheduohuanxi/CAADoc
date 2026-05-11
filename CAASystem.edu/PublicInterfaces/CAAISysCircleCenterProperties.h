#ifndef CAAISysCircleCenterProperties_h
#define CAAISysCircleCenterProperties_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface to modify the CircleCenter properties.
//
//===========================================================================
//  Inheritance:
//  ------------
//               CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Methods:
//  -------------
//
//  GetMarkerType     
//  SetMarkerType
//
//===========================================================================

// System Framework
#include <CATBaseUnknown.h>           //Needed to derive from CATBaseUnknown

// Local Framework
#include <CAASysGeoModelInf.h>        //Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAASysGeoModelInf
extern ExportedByCAASysGeoModelInf IID IID_CAAISysCircleCenterProperties;

class ExportedByCAASysGeoModelInf CAAISysCircleCenterProperties : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

    enum MarkerType  {Dot, Cross, Plus, Star};

    virtual HRESULT GetMarkerType(CAAISysCircleCenterProperties::MarkerType & oMarkerType )    = 0;      
    virtual HRESULT SetMarkerType(const CAAISysCircleCenterProperties::MarkerType iMarkerType) = 0;

};
#endif
