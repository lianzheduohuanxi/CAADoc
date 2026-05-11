#ifndef CAAISysRevolAxis_h
#define CAAISysRevolAxis_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface to manage an axis of revolution 
//
//===========================================================================

// System Framework
#include <CATBaseUnknown.h>           //Needed to derive from CATBaseUnknown

// Global Unique IDentifier defined in .cpp 
extern IID IID_CAAISysRevolAxis;

class CAAISysRevolAxis : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

    virtual HRESULT GetAxis(float &oX , float &oY ,float &oZ  )            = 0;      
    virtual HRESULT SetAxis(const float iX,const float iY,const float iZ ) = 0;

};
#endif
