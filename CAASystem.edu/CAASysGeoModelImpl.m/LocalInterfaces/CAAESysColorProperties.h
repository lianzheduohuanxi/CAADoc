#ifndef CAAESysColorProperties_H
#define CAAESysColorProperties_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAIColorProperties interface. 
//
//
//===========================================================================
//  Inheritance:
//  ------------
//                CATBaseUnknown (System Framework).
//                    
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   // to derive from  CATBaseUnknown


class CAAESysColorProperties: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysColorProperties();
    virtual ~CAAESysColorProperties();

    virtual HRESULT GetColor(int & oRed, int & oGreen, int & oBlue)   ;
    virtual HRESULT SetColor(const int iRed, const int iGreen, const int iBlue )  ; 

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysColorProperties(const CAAESysColorProperties &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysColorProperties & operator = (const CAAESysColorProperties &iObjectToCopy);

  private:

    int _Red, _Blue, _Green  ;
	
};
#endif
