// COPYRIGHT DASSAULT SYSTEMES  2011
//=============================================================================
//
// CAACloPspSpatialPhysical
//
#ifndef CAACloPspSpatialPhysical_H
#define CAACloPspSpatialPhysical_H

#include "CAAPspBaseEnvProtected.h"
#include "CATError.h"
#include "CATUnicodeString.h"

class CATIMovable;
class CATMathDirection;

//-----------------------------------------------------------------------------

class CAACloPspSpatialPhysical : public CAAPspBaseEnvProtected
{
 public:

  //-------------------------------------------------------------------------
  // Constructor/Destructor
  //-------------------------------------------------------------------------
  CAACloPspSpatialPhysical();
  virtual ~CAACloPspSpatialPhysical();

  HRESULT ListConnectedPhysicalsToSpatial();

  //-------------------------------------------------------------------------
  // Input: iuFileToBeLoaded - path of document name to be loaded (CATProduct
  //        containing geometry, objects ...
  //-------------------------------------------------------------------------

  HRESULT DoSample (const CATUnicodeString &iuFileToBeLoaded);  

};
#endif
