// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAMaiUserActivityComputeTP:
// Implementation d'interface
//
// ===================================================================

#ifndef CAAMaiUserActivityComputeTP_h
#define CAAMaiUserActivityComputeTP_h

#include "CATBaseUnknown.h"
#include "CATIContainer.h"
#include "CATIMfgToolPath.h"

class CAAMaiUserActivityComputeTP : public CATBaseUnknown

{
  CATDeclareClass;

public:
 
  CAAMaiUserActivityComputeTP();
  virtual ~CAAMaiUserActivityComputeTP();

  HRESULT  ComputeToolPath  (const CATIContainer_var& container,CATIMfgToolPath_var&); 


};

#endif//CAAMaiUserActivityComputeTP_h

