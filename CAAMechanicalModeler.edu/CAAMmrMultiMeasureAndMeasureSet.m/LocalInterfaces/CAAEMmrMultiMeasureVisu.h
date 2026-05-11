#ifndef CAAEMmrMultiMeasureVisu_H_
#define CAAEMmrMultiMeasureVisu_H_

// COPYRIGHT DASSAULT SYSTEMES 2007
//
// CAAEMmrMeasureSetVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrMeasureSet
//======================================================================================

#include "CATExtIVisu.h"

class CAAEMmrMultiMeasureVisu : public CATExtIVisu {

  CATDeclareClass;
  
public:

  CAAEMmrMultiMeasureVisu();
  virtual ~CAAEMmrMultiMeasureVisu();
  
  // interface CATIVisu
  CATRep *BuildRep();
 
};
#endif
