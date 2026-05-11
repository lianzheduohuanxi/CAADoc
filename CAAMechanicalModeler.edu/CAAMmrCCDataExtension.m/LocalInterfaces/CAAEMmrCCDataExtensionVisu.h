#ifndef CAAEMmrCCDataExtensionVisu_H_
#define CAAEMmrCCDataExtensionVisu_H_

// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrCCDataExtension.cpp
// Provide implementation to interface
//      CATICCGeoVisu i.e. CATIVisu for CAAMmrCCDataExtension
//======================================================================================

#include "CATExtIVisu.h"

class CAAEMmrCCDataExtensionVisu : public CATExtIVisu
{

  CATDeclareClass;

public:

  CAAEMmrCCDataExtensionVisu();
  virtual ~CAAEMmrCCDataExtensionVisu();

  // interface CATIVisu
  CATRep *BuildRep();
  int ModifyRep(const CATNotification & iInfo);

};
#endif
