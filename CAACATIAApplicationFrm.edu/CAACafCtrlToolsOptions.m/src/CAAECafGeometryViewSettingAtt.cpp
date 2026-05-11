// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAECafGeometryViewSettingAtt.h"

#include <iostream.h>

// System Framework
#include "CATString.h"
#include "CATSettingRepository.h"

//--------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAICafGeometryViewSettingAtt.h"
TIE_CAAICafGeometryViewSettingAtt(CAAECafGeometryViewSettingAtt);

// To declare that the class is a data extension of CAACafGeometryViewSettingCtrl
//
CATImplementClass(CAAECafGeometryViewSettingAtt,DataExtension,CATBaseUnknown,CAACafGeometryViewSettingCtrl);

// 
// To declare that CAAECafGeometryViewSettingAtt implements CAAICafGeometryViewSettingAtt, 
// insert these following lines in the interface dictionary:
//
//    CAACafGeometryViewSettingCtrl     CAAICafGeometryViewSettingAtt  libCAACafCtrlToolsOptions
//
//--------------------------------------------------------------------

CAAECafGeometryViewSettingAtt::CAAECafGeometryViewSettingAtt():_pSettingRep(NULL)
{
   _pSettingRep = CATSettingRepository::GetRepository("CAACafGeometryView") ;
}

//--------------------------------------------------------------------

CAAECafGeometryViewSettingAtt::~CAAECafGeometryViewSettingAtt()
{
   _pSettingRep = NULL ;
}

//--------------------------------------------------------------------
HRESULT CAAECafGeometryViewSettingAtt::Initialize()
{
  HRESULT rc = S_OK ;

  CATString ident ;
  rc = Get3DRepresentationMode(ident);  

  return rc ;
}

//--------------------------------------------------------------------
HRESULT   CAAECafGeometryViewSettingAtt::Get3DRepresentationMode(CATString & oIdVisibility)  
{
  HRESULT rc = E_FAIL ;

  if ( NULL != _pSettingRep )
  {
	 // The init value
	 CATString Ident("IdPlane");
	 //
     long flag = _pSettingRep->ReadSetting("Identifier",&Ident);

	 if ( 1 == flag )
	 {
         oIdVisibility = Ident ;
	     rc =S_OK;
	 }
  }
  return rc ;
}

HRESULT   CAAECafGeometryViewSettingAtt::Set3DRepresentationMode(const CATString & iIdVisibility) 
{
  HRESULT rc = E_FAIL ;

  CATString StIdPlane("IdPlane");
  CATString StIdAxis("IdAxis");
  CATString StIdWall("IdWall");

  if ( (StIdPlane == iIdVisibility) || 
	   (StIdAxis  == iIdVisibility) ||
	   (StIdWall  == iIdVisibility) )
  {
     if ( NULL != _pSettingRep )
	 {
	     CATString Ident = iIdVisibility ;

         long flag = _pSettingRep->WriteSetting("Identifier",&Ident);
	     if ( 1 == flag )
		 {
	        rc =S_OK;
		 }
	 }
  }
  return rc ;
}

HRESULT   CAAECafGeometryViewSettingAtt::GetInfo3DRepresentationMode(CATSettingInfo * oInfo)
{
  HRESULT rc = E_FAIL ;

  if ( NULL != _pSettingRep )
  {
	 long flag = _pSettingRep->GetInfo("Identifier",oInfo) ;
		
     if ( 0 == flag )
	 {
		rc = S_OK ;
	 }
  }
  return rc ;
}
