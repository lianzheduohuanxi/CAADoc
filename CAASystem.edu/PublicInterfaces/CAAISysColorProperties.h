#ifndef CAAISysColorProperties_h
#define CAAISysColorProperties_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface to modify the color .
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
//  GetColor     
//  SetColor 
//
//===========================================================================

// System Framework
#include <CATBaseUnknown.h>           //Needed to derive from CATBaseUnknown

// Local Framework
#include <CAASysGeoModelInf.h>        //Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAASysGeoModelInf
extern ExportedByCAASysGeoModelInf IID IID_CAAISysColorProperties;

class ExportedByCAASysGeoModelInf CAAISysColorProperties : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

    virtual HRESULT GetColor(int & oRed,int & oGreen,int & oBlue )              = 0;
    virtual HRESULT SetColor(const int iRed,const int iGreen,const int iBlue )  = 0;
};


#endif
