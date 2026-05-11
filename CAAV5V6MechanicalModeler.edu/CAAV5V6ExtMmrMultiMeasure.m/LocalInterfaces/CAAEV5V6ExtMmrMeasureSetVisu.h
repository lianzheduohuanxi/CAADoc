// COPYRIGHT DASSAULT SYSTEMES 2012
//
// CAAEV5V6ExtMmrMultiMeasureVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAV5V6ExtMmrMultiMeasure
//======================================================================================

#ifndef CAAEV5V6ExtMmrMeasureSetVisu_H_
#define CAAEV5V6ExtMmrMeasureSetVisu_H_
  
#include "CATExtIVisu.h"

class CAAEV5V6ExtMmrMeasureSetVisu : public CATExtIVisu
{

  CATDeclareClass;
  
public:

  CAAEV5V6ExtMmrMeasureSetVisu();
  virtual ~CAAEV5V6ExtMmrMeasureSetVisu();
  
  // interface CATIVisu
  CATRep *BuildRep();
  
};
#endif
