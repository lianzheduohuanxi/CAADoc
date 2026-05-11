#ifndef CAAESysCircleCenterProperties_H
#define CAAESysCircleCenterProperties_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAICircleCenterProperties interface. 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//         
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"     // to derive from  CATBaseUnknown

// Local Framework
#include "CAAISysCircleCenterProperties.h" // To have the marker type

class CAAESysCircleCenterProperties: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCircleCenterProperties();
    virtual ~CAAESysCircleCenterProperties();

    virtual HRESULT GetMarkerType(CAAISysCircleCenterProperties::MarkerType & oMarkerType ) ;
    virtual HRESULT SetMarkerType(const CAAISysCircleCenterProperties::MarkerType iMarkerType) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCircleCenterProperties(const CAAESysCircleCenterProperties &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCircleCenterProperties & operator = (const CAAESysCircleCenterProperties &iObjectToCopy);

  private:

    CAAISysCircleCenterProperties::MarkerType _MarkerType ;
	
};
#endif
