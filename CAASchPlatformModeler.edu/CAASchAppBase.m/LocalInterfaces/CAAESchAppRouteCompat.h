// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAESchAppRouteCompat
// Implements CATISchAppCompatible for CAASCHEDUString type
//=============================================================================
#ifndef CAAESchAppRouteCompat_H
#define CAAESchAppRouteCompat_H

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"

class CATIUnknownList;
class CATISchAppConnector;
class CATICStringList;

class CAAESchAppRouteCompat : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppRouteCompat();
  virtual ~CAAESchAppRouteCompat();

  virtual HRESULT AppIsTargetOKForRoute (const char *iRouteCntrClassType,
    CATIUnknownList **oLOKCntrs, boolean *oBYes);

  virtual HRESULT AppIsTargetOKForPlace (CATIUnknownList *iLCompSourceCntrs,
    CATIUnknownList **oLTargetCntrs, boolean *oBYes);

  virtual HRESULT AppIsTargetOKForInsert (CATIUnknownList *iLCompSourceCntrs,
    CATIUnknownList **oLSourceCntrs, boolean *oBYes);

  protected:

  boolean IsConnectorsCompatible (
    CATISchAppConnector *iAppCntrSrc, CATICStringList *iCStrTgtCompatTypes);

  private:

  CAAESchAppRouteCompat (const CAAESchAppRouteCompat &);
  CAAESchAppRouteCompat &operator = (const CAAESchAppRouteCompat &);
                      
}; 
#endif
