#ifndef CAAECafGeometryViewSettingAtt_H
#define CAAECafGeometryViewSettingAtt_H

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of CAACafGeometryViewSettingCtrl to implement the 
//  CAAICafGeometryViewSettingAtt. This interface enables to handle 
//  each attribut of the setting repository CAACafGeometryView
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"
class CATSettingRepository ;

// Local Framework
#include "CAAICafGeometryViewSettingAtt.h" // Implemented interface

class CAAECafGeometryViewSettingAtt: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAECafGeometryViewSettingAtt();
    virtual ~CAAECafGeometryViewSettingAtt();

    // This method calls all Getxxx methods. 
    virtual  HRESULT Initialize() ;

    virtual  HRESULT   Get3DRepresentationMode(CATString & oIdVisibility)   ;

    virtual  HRESULT   Set3DRepresentationMode(const CATString & iIdVisibility)  ;

    virtual  HRESULT   GetInfo3DRepresentationMode(CATSettingInfo * oInfo)  ;


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafGeometryViewSettingAtt(const CAAECafGeometryViewSettingAtt &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafGeometryViewSettingAtt & operator = (const CAAECafGeometryViewSettingAtt &iObjectToCopy);

  private:

    CATSettingRepository *   _pSettingRep     ;
};
#endif
