// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrMultiMeasureSelectShow.cpp 
//  Provide implementation to interface CATISelectShow for CAAV5V6ExtMmrMultiMeasure & CAAV5V6ExtMmrMeasureSet.
//
// Note : CAAEV5V6ExtMmrMultiMeasureSelectShow is the same use case as CAAEMmrMultiMeasureSelectShow. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CAAEV5V6ExtMmrMultiMeasureSelectShow.h"

#include "TIE_CATISelectShow.h"

TIE_CATISelectShow(CAAEV5V6ExtMmrMultiMeasureSelectShow);

CATBeginImplementClass(CAAEV5V6ExtMmrMultiMeasureSelectShow, DataExtension, CATExtISelectShow, CAAV5V6ExtMmrMultiMeasure);
CATAddExtendedImplementation(CAAV5V6ExtMmrMeasureSet);
CATEndImplementClass(CAAEV5V6ExtMmrMultiMeasureSelectShow);

// 
// To declare that CAAV5V6ExtMmrMultiMeasure & CAAV5V6ExtMmrMeasureSet implement CATISelectShow, insert 
// the following line in the interface dictionary :
//
// CAAV5V6ExtMmrMultiMeasure   CATISelectShow   libCAAV5V6ExtMmrMultiMeasureUI
// CAAV5V6ExtMmrMeasureSet     CATISelectShow   libCAAV5V6ExtMmrMultiMeasureUI

CAAEV5V6ExtMmrMultiMeasureSelectShow::CAAEV5V6ExtMmrMultiMeasureSelectShow()
{
}

CAAEV5V6ExtMmrMultiMeasureSelectShow::~CAAEV5V6ExtMmrMultiMeasureSelectShow()
{
}

HRESULT CAAEV5V6ExtMmrMultiMeasureSelectShow::GetElementForHideShow(CATPathElement *iPathElt,CATBaseUnknown *& oSelectedObject, int& oPostProcess)
{
  oPostProcess = 0;

  // We retrieve the feature itself
  oSelectedObject = this;
  
  return S_OK;

}

CATBaseUnknown * CAAEV5V6ExtMmrMultiMeasureSelectShow::GetElement(CATPathElement *iPathElt)
{

   return NULL;

}



