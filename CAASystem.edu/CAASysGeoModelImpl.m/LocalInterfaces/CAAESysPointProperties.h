#ifndef CAAESysPointProperties_H
#define CAAESysPointProperties_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAIPointProperties interface. 
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
#include "CAAISysPointProperties.h" // To have the marker type

class CAAESysPointProperties: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysPointProperties();
    virtual ~CAAESysPointProperties();

    virtual HRESULT GetMarkerType(CAAISysPointProperties::MarkerType & oMarkerType ) ;
    virtual HRESULT SetMarkerType(const CAAISysPointProperties::MarkerType iMarkerType) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysPointProperties(const CAAESysPointProperties &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysPointProperties & operator = (const CAAESysPointProperties &iObjectToCopy);

  private:

    CAAISysPointProperties::MarkerType _MarkerType ;
	
};
#endif
