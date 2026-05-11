#ifndef CAAECafGeometryEltSettingAtt_H
#define CAAECafGeometryEltSettingAtt_H

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of  CAACafGeometryEltSettingCtrl to implement the 
//  CAAICafGeometryEltSettingAtt. This interface enables to handle 
//  each attribut of the setting repository CAACafGeometryElt
//  
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"
class CATSettingRepository ;

// Local Framework
#include "CAAICafGeometryEltSettingAtt.h" // Implemented interface

class CAAECafGeometryEltSettingAtt: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAECafGeometryEltSettingAtt();
    virtual ~CAAECafGeometryEltSettingAtt();

    // This method calls all Getxxx methods. 
    virtual  HRESULT Initialize() ;

    virtual  HRESULT   GetIdentifierVisibility(CATString & oIdVisibility)   ;

    virtual  HRESULT   SetIdentifierVisibility(const CATString & iIdVisibility)  ;

    virtual  HRESULT   GetInfoIdentifierVisibility(CATSettingInfo * oInfo)  ;


    virtual  HRESULT   GetMaxPointCurve(int & oMaxPoint)       ;

    virtual  HRESULT   SetMaxPointCurve(const int iMaxPoint)  ;

    virtual  HRESULT   GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray, int * oNbInfo)  ;


    virtual  HRESULT   GetImplPointVisibility(CATString & oImplPointVisibility)        ;
    
    virtual  HRESULT   SetImplPointVisibility(const CATString & iImplPointVisibility)  ;

    virtual  HRESULT   GetInfoImplPointVisibility(CATSettingInfo * oInfo)  ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafGeometryEltSettingAtt(const CAAECafGeometryEltSettingAtt &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafGeometryEltSettingAtt & operator = (const CAAECafGeometryEltSettingAtt &iObjectToCopy);

  private:

    CATSettingRepository *   _pSettingRep     ;
};
#endif
