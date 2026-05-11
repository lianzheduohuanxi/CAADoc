#ifndef CAAISysSurfaceProperties_h
#define CAAISysSurfaceProperties_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface to modify the Surface properties.
//
//===========================================================================

// System Framework
#include <CATBaseUnknown.h>           //Needed to derive from CATBaseUnknown

// Global Unique IDentifier defined in .cpp 
extern IID IID_CAAISysSurfaceProperties;

class CAAISysSurfaceProperties : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

    virtual HRESULT GetColor(int & oRed,int & oGreen,int & oBlue )              = 0;
    virtual HRESULT SetColor(const int iRed,const int iGreen,const int iBlue )  = 0;

};
#endif
