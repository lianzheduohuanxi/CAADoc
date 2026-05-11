// COPYRIGHT DASSAULT SYSTEMES 2007

#ifndef CATEMmrMultiMeasureSelectShow_H
#define CATEMmrMultiMeasureSelectShow_H


#include "CATExtISelectShow.h"

//---------------------------------------------------------------------
// CATEMmrMultiMeasureSelectShow
//---------------------------------------------------------------------
//
// CATEMmrMultiMeasureSelectShow : Implementation of CATISelectShow
// for CAAMmrMultiMeasure & CAAMmrMeasureSet.
//
// To determine which features are hidden on Hide/Show command.
//---------------------------------------------------------------------

class CATEMmrMultiMeasureSelectShow: public CATExtISelectShow
{
  CATDeclareClass;

public:

  CATEMmrMultiMeasureSelectShow();
  ~CATEMmrMultiMeasureSelectShow();

  HRESULT GetElementForHideShow(CATPathElement *iPathElt,CATBaseUnknown *& oSelectedObject, int& oPostProcess);
  CATBaseUnknown * GetElement(CATPathElement *iPathElt);

};

#endif
