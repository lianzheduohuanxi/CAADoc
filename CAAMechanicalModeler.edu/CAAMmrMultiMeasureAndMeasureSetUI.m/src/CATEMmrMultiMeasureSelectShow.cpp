// -------------------------------------------------------------------
// Copyright Dassault Systemes 2007
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Source:  CATEMmrMultiMeasureSelectShow.cpp
//---------------------------------------------------------------------
//
// CATEMmrMultiMeasureSelectShow : Implementation of CATISelectShow
// for CAAMmrMultiMeasure & CAAMmrMeasureSet.
//
//---------------------------------------------------------------------

#include "CATEMmrMultiMeasureSelectShow.h"

#include "TIE_CATISelectShow.h"

TIE_CATISelectShow(CATEMmrMultiMeasureSelectShow);

CATBeginImplementClass(CATEMmrMultiMeasureSelectShow, DataExtension, CATExtISelectShow, CAAMmrMultiMeasure);
CATAddExtendedImplementation(CAAMmrMeasureSet);
CATEndImplementClass(CATEMmrMultiMeasureSelectShow);

// 
// To declare that CAAMmrMultiMeasure & CAAMmrMeasureSet implement CATISelectShow, insert 
// the following line in the interface dictionary :
//
// CAAMmrMultiMeasure   CATISelectShow   libCAAMmrMultiMeasureAndMeasureSetUI
// CAAMmrMeasureSet     CATISelectShow   libCAAMmrMultiMeasureAndMeasureSetUI

CATEMmrMultiMeasureSelectShow::CATEMmrMultiMeasureSelectShow()
{
}

CATEMmrMultiMeasureSelectShow::~CATEMmrMultiMeasureSelectShow()
{
}

HRESULT CATEMmrMultiMeasureSelectShow::GetElementForHideShow(CATPathElement *iPathElt,CATBaseUnknown *& oSelectedObject, int& oPostProcess)
{
  oPostProcess = 0;

  // We retrieve the feature itself
  oSelectedObject = this;
  
  return S_OK;

}

CATBaseUnknown * CATEMmrMultiMeasureSelectShow::GetElement(CATPathElement *iPathElt)
{
   // 
   // We Provide an empty implementation for GetElement in order to remove the mkmk warning message
   // CAAV5-WARNING: deprecated API for CAA V5
   // CAAV5-WARNING: CATExtISelectShow::GetElement(CATPathElement*)  V5R13 deprecated.
   //
   return NULL ; 
} 

