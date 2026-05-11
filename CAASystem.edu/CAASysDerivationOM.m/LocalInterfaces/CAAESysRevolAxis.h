#ifndef CAAESysRevolAxis_H
#define CAAESysRevolAxis_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAASysRevolSurface component, implementing the 
//  CAAISysRevolAxis interface. 
//
//                    
//===========================================================================

#include "CATBaseUnknown.h"   // to derive from  CATBaseUnknown


class CAAESysRevolAxis: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysRevolAxis();
    virtual ~CAAESysRevolAxis();

    virtual HRESULT GetAxis(float &oX , float &oY ,float &oZ  )            ;      
    virtual HRESULT SetAxis(const float iX,const float iY,const float iZ ) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysRevolAxis(const CAAESysRevolAxis &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysRevolAxis & operator = (const CAAESysRevolAxis &iObjectToCopy);

  private :

    float _X ;
    float _Y ;
    float _Z ;

};
#endif
