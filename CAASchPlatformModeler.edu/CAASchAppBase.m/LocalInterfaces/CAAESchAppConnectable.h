// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
#ifndef CAAESchAppConnectable_H
#define CAAESchAppConnectable_H

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"

class CATIUnknownList;
class CATISchAppConnector;
class CATICStringList;

class CAAESchAppConnectable : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppConnectable();
  virtual ~CAAESchAppConnectable();

  /**
  * Find all the connectors of this application object.
  * @param oLCntrClassFilter
  *   A list of all the class types for filtering the output connector
  *   list.
  * @param oLCntrs
  *   A list of connectors included in this connection.
  *   (members are CATISchAppConnector interface pointers).
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
  virtual HRESULT AppListConnectors (CATICStringList *iLCntrClassFilter,
    CATIUnknownList **oLCntrs);

  /**
  * Find all the application objects connected to this object through
  * their connectors.
  * @param oLCntrClassFilter
  *   A list of all the class types for filtering the output application
  *   objects list.
  * @param oLCntbles
  *   A list of application objects connected to this object.
  *   (members are CATISchAppConnectable interface pointers). 
  * @param oLCntrsOnThisObj
  *   A list of connectors on this object through which 
  *   the connection is made.
  *   (members are CATISchAppConnector interface pointers).
  * @param oLCntrsOnConnected
  *   A list of connectors on the connected objects through which 
  *   the connection is made.
  *   (members are CATISchAppConnector interface pointers).
  *   Members in this list corresponds to those in oLCntrsOnThisObj in
  *   making the corresponding connections.
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
  virtual HRESULT AppListConnectables (CATICStringList *iLCntbleClassFilter,
    CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrsOnThisObj,
    CATIUnknownList **oLCntrsOnConnected);

  /**
  * Add a connector.
  * @param iClassType 
  *   Class type of the connector to be added.
  * @param oNewAppCntr
  *   The new Application Connector object created.
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
  virtual HRESULT AppAddConnector (const char *iClassType,
    CATISchAppConnector **oNewAppCntr);
  
  /**
  * Remove a connector.
  * @param iCntrToRemove
  *    The application connector object to be removed 
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
  virtual HRESULT AppRemoveConnector (CATISchAppConnector *iCntrToRemove);

  /**
  * List the valid application connector types allowed to be created.
  * @param oLValidCntrTypes
  *   A list of connector class types allowed.
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
  virtual HRESULT AppListValidCntrTypes (CATICStringList **oLValidCntrTypes);

  /**
  * Get the reference name of a connectable. It will be displayed in catalogs.
  * @param oReferenceName
  *   The name of the reference
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
  virtual HRESULT AppGetReferenceName (char **oReferenceName);

  /**
  * Set the reference name of a connectable. It will be displayed in catalogs.
  * @param iReferenceName
  *   The name of the reference
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
  virtual HRESULT AppSetReferenceName (const char *iReferenceName);

  private:

  CAAESchAppConnectable (const CAAESchAppConnectable &);
  CAAESchAppConnectable &operator = (const CAAESchAppConnectable &);

}; 
#endif
