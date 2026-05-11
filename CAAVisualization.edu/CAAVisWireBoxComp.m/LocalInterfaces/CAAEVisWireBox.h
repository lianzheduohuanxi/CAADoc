#ifndef CAAEVisWireBox_H
#define CAAEVisWireBox_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAAVisWireBox component and implementing the 
//  CAAIVisWireBox interface.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by SetCenterBox & GetCenterBox

class CAAEVisWireBox : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAEVisWireBox();
    virtual ~CAAEVisWireBox();

    virtual HRESULT SetDimBox( const float iDimBox ); 
    virtual HRESULT GetDimBox( float * oDimBox );  
    virtual HRESULT SetCenterBox(const CATMathPoint  & iCenter) ;
    virtual HRESULT GetCenterBox(CATMathPoint        & oCenter) const ;


  private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
    CAAEVisWireBox(const CAAEVisWireBox &iObjectToCopy);
 
   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
    CAAEVisWireBox & operator = (const CAAEVisWireBox &iObjectToCopy);
 
  private :

    float        _DimBox ;
    CATMathPoint _CenterBox ;
};

#endif
