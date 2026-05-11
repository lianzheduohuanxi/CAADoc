#ifndef CAAESysSurfaceProperties_H
#define CAAESysSurfaceProperties_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAISysSurfaceProperties interface. 
//

//===========================================================================
//  Inheritance:
//  ------------
//                CATBaseUnknown (System Framework).
//                    
//===========================================================================

#include "CATBaseUnknown.h"   // to derive from  CATBaseUnknown


class CAAESysSurfaceProperties: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysSurfaceProperties();
    virtual ~CAAESysSurfaceProperties();

    virtual HRESULT GetColor(int & oRed, int & oGreen, int & oBlue)   ;
    virtual HRESULT SetColor(const int iRed, const int iGreen, const int iBlue )  ; 

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysSurfaceProperties(const CAAESysSurfaceProperties &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysSurfaceProperties & operator = (const CAAESysSurfaceProperties &iObjectToCopy);

  private:

    int _Red, _Blue, _Green  ;
	
};
#endif
