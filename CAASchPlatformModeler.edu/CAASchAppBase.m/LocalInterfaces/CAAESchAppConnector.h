// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
#ifndef CAAESchAppConnector_H
#define CAAESchAppConnector_H

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"

class CATIUnknownList;
class CATICStringList;
class CATISchAppConnectable;
class CATISchAppConnector;
class CATISchAppConnection;

class CAAESchAppConnector : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppConnector();
  virtual ~CAAESchAppConnector();

  /**
  * Find the application object that owns this connector.
  * @param oConnectable
  *   An application object that the connector belongs to.
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
  HRESULT AppGetAssociatedConnectable (
    CATISchAppConnectable **oConnectable);

  /**
  * Find all the class types of connector that are compatible with
  * this connector for connections.
  * @param oLCntrCompatClassTypes
  *   A list of all the class types of connectors that are compatible
  *   with this connector for connections.
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
  HRESULT AppListCompatibleTypes (
    CATICStringList **oLCntrCompatClassTypes);

  /**
  * Find all the connections that include this connector.
  * @param oLCntnClassFilter
  *   A list of all the class types for filtering the output connection
  *   list.
  * @param oLConnections
  *   A list of connections that include this connector
  *   (members are CATISchAppConnection interface pointers).
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
  HRESULT AppListConnections (CATICStringList *iLCntnClassFilter,
    CATIUnknownList **oLConnections);

  /**
  * Connect to an input connector.
  * @param iCntrToConnect
  *   A schematic connector object to connect to
  * @param oConnection
  *   Connection created
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
  HRESULT AppConnect (CATISchAppConnector *iCntrToConnect,
    CATISchAppConnection **oConnection );

  /**
  * Connect to an input connector for Branch.
  * @param iCntrToConnect
  *   A schematic connector object to connect to
  * @param oConnection
  *   Connection created
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
  HRESULT AppConnectBranch (CATISchAppConnector *iCntrToConnect,
    CATISchAppConnection **oConnection );

  /**
  * Disconnect from an input connector.
  * @param iCntrToDisconnect
  *   A schematic connector object to disconnect from
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
  HRESULT AppDisconnect (CATISchAppConnector *iCntrToDisConnect);
  
  /**
  * Query whether it is OK to no show the connector after it is connected.
  * @param oBYes
  *   If TRUE, then it is OK to no show.
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
  HRESULT AppOKToNoShowConnectedCntr (boolean *oBYes);

  /**
  * Query whether the connector has been connected 
  * @param oBYes
  *   If TRUE, then it is connected
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
  virtual HRESULT AppIsCntrConnected (boolean *oBYes);


  private:

  CAAESchAppConnector (const CAAESchAppConnector &);
  CAAESchAppConnector &operator = (const CAAESchAppConnector &);

}; 
#endif
