// COPYRIGHT DASSAULT SYSTEMES 2007
//
// CAAEMmrMultiMeasureVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrMultiMeasure
//======================================================================================

#ifndef CAAEMmrMeasureSetVisu_H_
#define CAAEMmrMeasureSetVisu_H_
  
#include "CATExtIVisu.h"

class CAAEMmrMeasureSetVisu : public CATExtIVisu {

  CATDeclareClass;
  
public:

  CAAEMmrMeasureSetVisu();
  virtual ~CAAEMmrMeasureSetVisu();
  
  // interface CATIVisu
  CATRep *BuildRep();
  
};
#endif
