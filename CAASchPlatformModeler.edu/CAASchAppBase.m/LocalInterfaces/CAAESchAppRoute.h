// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
#ifndef CAAESchAppRoute_H
#define CAAESchAppRoute_H

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"

class CATISchAppRoute;
class CATDocument;
class CATISchRoute;

class CAAESchAppRoute : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppRoute();
  virtual ~CAAESchAppRoute();

  /**
  * Make a local route reference in another document by copying an 
  * existing one in the current document.
  * @param iDocumentToPutCopyIn
  *   Pointer to the document to make the copy in
  * @param oSchRoute
  *   Pointer to the copy.
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
  virtual HRESULT AppCreateLocalReference (CATDocument *iDocumentToPutCopyIn, 
    CATISchAppRoute **oSchAppRoute); 

  /**
  * Break the application route into 2 routes.
  * @param oNewAppRoute
  *   New application route
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
  HRESULT AppBreak (IUnknown **oNewAppRoute);

  /**
  * Post process after breaking an application route into 2 pieces. 
  * @param iOldAppRoute
  *   The old application route object
  * @param iNewAppRoute
  *   The new Application route object
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
  HRESULT AppPostBreakProcess (CATISchRoute *iOldAppRoute, 
    CATISchRoute *iNewAppRoute);

  /**
  * Post process after concatenate 2 application routes into one
  * @param iSchRoute2
  *   Second route 
  *   to be concatenate to this. This route will be deleted.
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
  HRESULT AppPostConcatenateProcess (CATISchRoute *iSchRoute2);

  /**
  * Query whether it is OK to modify (add or remove) the points.
  * @param oBYes
  *   If TRUE, then it is OK to add or remove the points from the application
  *   route
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
  HRESULT AppOKToModifyPoints (boolean *oBYes);

  /**
  * Query whether it is OK to break.
  * @param oBYes
  *   If TRUE, then it is OK to break the application route
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
  HRESULT AppOKToBreak (boolean *oBYes);

  /**
  * Query whether it is OK to concatenate.
  * @param oBYes
  *   If TRUE, then it is OK to concatenate the application route
  *   with another
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
  HRESULT AppOKToConcatenate (boolean *oBYes);

  /**
  * Query whether it is OK to create branch.
  * @param iBranchClassType
  *   Class type of the branch to create.
  * @param oBYes
  *   If TRUE, then it is OK to create a branch from an application route
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
  HRESULT AppOKToBranch (const char* iBranchClassType, boolean *oBYes);

  private:

  CAAESchAppRoute (const CAAESchAppRoute &);
  CAAESchAppRoute &operator = (const CAAESchAppRoute &);

}; 
#endif
