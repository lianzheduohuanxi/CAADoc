#ifndef CAAEV5V6ExtMmrMultiMeasureVisu_H_
#define CAAEV5V6ExtMmrMultiMeasureVisu_H_

// COPYRIGHT DASSAULT SYSTEMES 2012
//
// CAAEMmrMeasureSetVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrMeasureSet
//======================================================================================

#include "CATExtIVisu.h"

class CAAEV5V6ExtMmrMultiMeasureVisu : public CATExtIVisu {

  CATDeclareClass;
  
public:

  CAAEV5V6ExtMmrMultiMeasureVisu();
  virtual ~CAAEV5V6ExtMmrMultiMeasureVisu();
  
  // interface CATIVisu
  CATRep *BuildRep();
 
};
#endif
