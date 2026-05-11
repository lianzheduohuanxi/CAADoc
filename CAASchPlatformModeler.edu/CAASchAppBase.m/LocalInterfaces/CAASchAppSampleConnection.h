// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================

#ifndef CAASchAppSampleConnection_H
#define CAASchAppSampleConnection_H

#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATErrorDef.h"
#include "CATBooleanDef.h"
#include "CATIConnector.h"

class CATIUnknownList;
class CATICStringList;
class CATISchAppConnector;

//-----------------------------------------------------------------------------
class CAASchAppSampleConnection : public CATBaseUnknown
{

  CATDeclareClass;

  public:

  CAASchAppSampleConnection (const IUnknown* iCntr1=NULL,
    const IUnknown* iCntr2=NULL);
  virtual ~CAASchAppSampleConnection();

  CATIConnector_var _spCntr1;
  CATIConnector_var _spCntr2;

  virtual HRESULT AppListConnectors (CATICStringList *iLCntrClassFilter,
    CATIUnknownList **oLCntrs);

  virtual HRESULT AppListConnectables (CATICStringList *iLCntbleClassFilter,
    CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrs);

  virtual HRESULT AppAddConnector (CATISchAppConnector *iCntrToAdd);

  virtual HRESULT AppRemoveConnector (CATISchAppConnector *iCntrToRemove);


  private:
  CAASchAppSampleConnection (const CAASchAppSampleConnection &);
  CAASchAppSampleConnection &operator = (const CAASchAppSampleConnection &);

};
#endif
