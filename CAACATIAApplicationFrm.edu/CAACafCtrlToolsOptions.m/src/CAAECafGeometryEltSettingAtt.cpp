// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAECafGeometryEltSettingAtt.h"

#include <iostream.h>

// System Framework
#include <CATString.h>
#include <CATErrorDef.h>   // for the FAILED macro
#include "CATSettingRepository.h"
#include "CATSettingInfo.h"

//--------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAICafGeometryEltSettingAtt.h"
TIE_CAAICafGeometryEltSettingAtt(CAAECafGeometryEltSettingAtt);

// To declare that the class is a data extension of CAACafGeometryEltSettingCtrl
//
CATImplementClass(CAAECafGeometryEltSettingAtt,DataExtension,CATBaseUnknown,CAACafGeometryEltSettingCtrl);

// 
// To declare that CAAECafGeometryEltSettingAtt implements CAAICafGeometryEltSettingAtt, 
// insert these following lines in the interface dictionary:
//
//    CAACafGeometryEltSettingCtrl     CAAICafGeometryEltSettingAtt  libCAACafCtrlToolsOptions
//
//--------------------------------------------------------------------

CAAECafGeometryEltSettingAtt::CAAECafGeometryEltSettingAtt():_pSettingRep(NULL)
{
   _pSettingRep = CATSettingRepository::GetRepository("CAACafGeometryElt") ;
}

//--------------------------------------------------------------------

CAAECafGeometryEltSettingAtt::~CAAECafGeometryEltSettingAtt()
{
   _pSettingRep = NULL ;
}

//--------------------------------------------------------------------
HRESULT CAAECafGeometryEltSettingAtt::Initialize()
{

  HRESULT rc = S_OK ;
  HRESULT rctemp = E_FAIL ;

  CATString ident ;
  rctemp =  GetIdentifierVisibility(ident);
  if ( FAILED(rctemp) )
	  rc = rctemp ;

  rctemp = GetImplPointVisibility(ident);
  if ( FAILED(rctemp) )
	  rc = rctemp ;

  int value ;
  rc = GetMaxPointCurve(value);
  if ( FAILED(rctemp) )
	  rc = rctemp ;
  
  return rc ;

}
//--------------------------------------------------------------------
HRESULT   CAAECafGeometryEltSettingAtt::GetIdentifierVisibility(CATString & oIdVisibility)  
{
  HRESULT rc = E_FAIL ;

  if ( NULL != _pSettingRep )
  {
	 // The init value
	 CATString Ident("IdHide");
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

HRESULT   CAAECafGeometryEltSettingAtt::SetIdentifierVisibility(const CATString & iIdVisibility) 
{
  HRESULT rc = E_FAIL ;

  CATString StIdHide("IdHide");
  CATString StIdShow("IdShow");
  CATString StIdPreSelectShow("IdPreSelectShow");

  if ( (StIdHide == iIdVisibility) || 
	   (StIdShow == iIdVisibility) ||
	   (StIdPreSelectShow == iIdVisibility) )
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

HRESULT   CAAECafGeometryEltSettingAtt::GetInfoIdentifierVisibility(CATSettingInfo * oInfo )  
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
//--------------------------------------------------------------------
HRESULT   CAAECafGeometryEltSettingAtt::GetMaxPointCurve(int & oMaxPoint)      
{
  HRESULT rc = E_FAIL ;

  if ( NULL != _pSettingRep )
  {
	 // The init value 
	 int MaxPoint = 10 ;
	 // 
     long flag = _pSettingRep->ReadSetting("MaxPointCurve",&MaxPoint);

	 if ( 1 == flag )
	 {
         oMaxPoint = MaxPoint ;
	     rc =S_OK;
	 }
  }
  return rc ;
}

HRESULT   CAAECafGeometryEltSettingAtt::SetMaxPointCurve(const int iMaxPoint)  
{
  HRESULT rc = E_FAIL ;

  if ( (iMaxPoint >= 2) && (iMaxPoint <= 100 ) )
  {
     if ( NULL != _pSettingRep )
	 {
	    int MaxPoint = iMaxPoint ;
        long flag = _pSettingRep->WriteSetting("MaxPointCurve",&MaxPoint);
	    if ( 1 == flag )
		{
	       rc =S_OK;
		}
	 }
  }
  return rc ;
}

HRESULT   CAAECafGeometryEltSettingAtt::GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray ,
                                                                int * oNbSettingInfo)  

{
    HRESULT rc = E_FAIL ;

    if ( (NULL != _pSettingRep) && ( NULL != oNbSettingInfo) && ( NULL != oInfoArray ) )
    {

       *oNbSettingInfo = 0 ;
       *oInfoArray = NULL ;

       CATSettingInfo info ;
       long flag = _pSettingRep->GetInfo("MaxPointCurve",&info) ;
		
       if ( 0 == flag )
       {
          *oNbSettingInfo = 1 ;
          *oInfoArray = new CATSettingInfo [*oNbSettingInfo] ;
          (*oInfoArray)[0] = info ;

          rc = S_OK ;
       }
    }
    return rc ;
}
//--------------------------------------------------------------------

HRESULT   CAAECafGeometryEltSettingAtt::GetImplPointVisibility(CATString & oImplPointVisibility)  
{
  HRESULT rc = E_FAIL ;

  if ( NULL != _pSettingRep )
  {
	 //  The init value 
     CATString ImplPoint("ImplPointHide");
     //
     long flag = _pSettingRep->ReadSetting("ImplPoint",&ImplPoint);

	 if ( 1 == flag )
	 {
         oImplPointVisibility = ImplPoint ;
	     rc =S_OK;
	 }
  }
    return rc ;
}

HRESULT   CAAECafGeometryEltSettingAtt::SetImplPointVisibility(const CATString & iImplPointVisibility) 
{
  HRESULT rc = E_FAIL ;
  
  CATString StImplPointShow("ImplPointShow");
  CATString StImplPointHide("ImplPointHide");

  if ( (StImplPointShow == iImplPointVisibility) || 
	   (StImplPointHide == iImplPointVisibility) )	   
  {
     if ( NULL != _pSettingRep )
	 {
	    CATString ImplPoint = iImplPointVisibility ;
        long flag = _pSettingRep->WriteSetting("ImplPoint",&ImplPoint);
	    if ( 1 == flag )
		{
			rc =S_OK;
		}
	 }
  }
  return rc ;
}
 
HRESULT   CAAECafGeometryEltSettingAtt::GetInfoImplPointVisibility(CATSettingInfo * oInfo)  
{
  HRESULT rc = E_FAIL ;

  if ( NULL != _pSettingRep )
  {
	 long flag = _pSettingRep->GetInfo("ImplPoint",oInfo) ;
		
     if ( 0 == flag )
	 {
		rc = S_OK ;
	 }
  }
    return rc ;
}
//--------------------------------------------------------------------
