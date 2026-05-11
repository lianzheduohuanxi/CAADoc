// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAEV5V6ExtMmrMultiMeasureSelectShow_H
#define CAAEV5V6ExtMmrMultiMeasureSelectShow_H


#include "CATExtISelectShow.h"

//---------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureSelectShow
//---------------------------------------------------------------------
//
// CAAEV5V6ExtMmrMultiMeasureSelectShow : Implementation of CATISelectShow
// for CAAV5V6ExtMmrMultiMeasure & CAAV5V6ExtMmrMeasureSet.
//
// To determine which features are hidden on Hide/Show command.
//---------------------------------------------------------------------

class CAAEV5V6ExtMmrMultiMeasureSelectShow: public CATExtISelectShow
{
  CATDeclareClass;

public:

  CAAEV5V6ExtMmrMultiMeasureSelectShow();
  ~CAAEV5V6ExtMmrMultiMeasureSelectShow();

  HRESULT GetElementForHideShow(CATPathElement *iPathElt,CATBaseUnknown *& oSelectedObject, int& oPostProcess);
  CATBaseUnknown * GetElement(CATPathElement *iPathElt);
};

#endif
