#ifndef CAAEV5V6ExtMmrCCDataExtensionVisu_H_
#define CAAEV5V6ExtMmrCCDataExtensionVisu_H_

// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// Provide implementation to interface
//      CATI3DGeoVisu for CAAV5V6ExtMmrCCDataExtension
//======================================================================================

// Visualization Framework for V5
// VisualizationController Framework for V6
#include "CATExtIVisu.h"

class CAAEV5V6ExtMmrCCDataExtensionVisu : public CATExtIVisu
{

  CATDeclareClass;

public:

  CAAEV5V6ExtMmrCCDataExtensionVisu();
  virtual ~CAAEV5V6ExtMmrCCDataExtensionVisu();

  // interface CATIVisu
  CATRep *BuildRep();
  int ModifyRep(const CATNotification & iInfo);

};
#endif
