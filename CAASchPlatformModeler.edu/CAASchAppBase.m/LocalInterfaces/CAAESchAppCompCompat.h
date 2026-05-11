// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAESchAppCompCompat
// Implements CATISchAppCompatible for CAASCHEDUFunctionalPart type
//
//=============================================================================
#ifndef CAAESchAppCompCompat_H
#define CAAESchAppCompCompat_H

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"

class CATIUnknownList;
class CATISchAppConnector;
class CATICStringList;

class CAAESchAppCompCompat : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppCompCompat();
  virtual ~CAAESchAppCompCompat();

  virtual HRESULT AppIsTargetOKForRoute (const char *iRouteCntrClassType,
    CATIUnknownList **oLOKCntrs, boolean *oBYes);

  virtual HRESULT AppIsTargetOKForPlace (CATIUnknownList *iLCompSourceCntrs,
    CATIUnknownList **oLTargetCntrs, boolean *oBYes);

  virtual HRESULT AppIsTargetOKForInsert (CATIUnknownList *iLCompSourceCntrs,
    CATIUnknownList **oLSourceCntrs, boolean *oBYes);

  private:

  CAAESchAppCompCompat (const CAAESchAppCompCompat &);
  CAAESchAppCompCompat &operator = (const CAAESchAppCompCompat &);

  // if iMatch memory is provided, that the matching type index in 
  // the list will be output
  boolean IsConnectorsCompatible (
    CATISchAppConnector *iAppCntrSrc, CATICStringList *iCStrTgtCompatTypes,
    int *iMatch=NULL);                           
}; 
#endif
