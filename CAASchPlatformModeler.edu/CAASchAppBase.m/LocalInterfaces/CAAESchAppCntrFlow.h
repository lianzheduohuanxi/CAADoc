// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
#ifndef CAAESchAppCntrFlow_H
#define CAAESchAppCntrFlow_H

#include "CATSchGeneralEnum.h"                           

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"
#include "CATIUnknownList.h"

class CATISchAppConnector;
class CATISchAppConnectable;

class CAAESchAppCntrFlow : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppCntrFlow();
  virtual ~CAAESchAppCntrFlow();

  /**
  * Query the application Flow Capability property of this connector.
  * @param oEFlowCapability
  *   Flow Capability.
  *   @see CATSchCntrFlowCapability
  * @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>operation is successful</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>operation failed</dd>
  *   </dl>
  */
  HRESULT AppGetFlowCapability (
    CATSchCntrFlowCapability *oEFlowCapability);

  /**
  * Set the application Flow Capability property of this connector.
  * @param iEFlowCapability
  *   Flow Capability property to be set.
  *   @see CATSchCntrFlowCapability
  * @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>operation is successful</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>operation failed</dd>
  *   </dl>
  */
  HRESULT AppSetFlowCapability (
    CATSchCntrFlowCapability iEFlowCapability);

  /**
  * Query the application Flow Reality property of this connector.
  * @param oEFlowReality
  *   Flow Reality.
  *   @see CATSchCntrFlowReality
  * @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>operation is successful</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>operation failed</dd>
  *   </dl>
  */
  HRESULT AppGetFlowReality (
    CATSchCntrFlowReality *oEFlowReality);

  /**
  * Set the application Flow Reality property of this connector.
  * @param iEFlowReality
  *   Flow Reality property to be set.
  *   @see CATSchCntrFlowReality
  * @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>operation is successful</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>operation failed</dd>
  *   </dl>
  */
  HRESULT AppSetFlowReality (
    CATSchCntrFlowReality iEFlowReality);

  private:

  CAAESchAppCntrFlow (const CAAESchAppCntrFlow &);
  CAAESchAppCntrFlow &operator = (const CAAESchAppCntrFlow &);

  boolean DeriveFlowReality (CATISchAppConnector *iAppCntr,
    CATISchAppConnectable *iConnectable, int CnxOrFlow, int *ioCntrCount,
    CATSchCntrFlowReality *oEFlowReality);

  HRESULT FindConnectedCntr (CATISchAppConnector *iAppCntr,
    CATISchAppConnector **oAppCntr);

  HRESULT FindInternalFlowCntrs (CATISchAppConnector *iAppCntr,
    CATISchAppConnectable *iAppCntbl, CATIUnknownList **oLSchCntrs);

}; 
#endif
