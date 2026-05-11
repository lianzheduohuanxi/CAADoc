// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
#ifndef CAAESchAppComponent_H
#define CAAESchAppComponent_H

#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

class CATISchComponent;
class CATISchAppConnectable;
class CATISchRoute;
class CATISchGRR;
class CATDocument;
class CATICStringList;

class CAAESchAppComponent : public CATBaseUnknown                           
{
  public:

  CATDeclareClass;

  CAAESchAppComponent();
  virtual ~CAAESchAppComponent();

  /**
  * Create a component instance.
  * @param oNewAppCompInst
  *   Interface pointer (CATISchAppComponent) to the new <b>application</b>
  *   component instance placed.
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
  virtual HRESULT AppCreateComponentInst (IUnknown **oNewAppCompInst);

  /**
  * Create Local Reference object. Given a reference object (the "this"),
  * This method make a copy of the reference into another document.
  * @param iDocToCopyTo
  *   Pointer to a document to copy the reference to,
  * @param oNewAppCompRef
  *   Interface pointer (CATISchAppComponent) to the new <b>application</b>
  *   component Reference copied.
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
  virtual HRESULT AppCreateLocalReference (CATDocument *iDocToCopyTo,
    IUnknown **oNewAppCompRef);

  /**
  * @deprecated V5R15 
  * Use @href CAAESchAppComponent#AppListGRRNames2 instead.
  * Find all the valid graphical representation names
  * of an application component.
  * @param oLGRRNames
  *   A list of all the valid graphical representation names
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
  virtual HRESULT AppListGRRNames (CATICStringList **oLGRRNames);

  /**
  * @deprecated V5R15 
  * Use @href CAAESchAppComponent#AppGetDefaultGRRName2 instead.
  * Get the default graphical representation names
  * of an application component.
  * @param oGRRDefaultName
  *   The default name to be used for the graphical representation
  *   of a component
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
  virtual HRESULT AppGetDefaultGRRName (char **oGRRDefaultName);

  /**
  * Find all the valid graphical representation names
  * of an application component.
  * @param oLGRRNames
  *   A list of all the valid graphical representation names
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
  virtual HRESULT AppListGRRNames2 (CATListOfCATUnicodeString &oLGRRNames);

  /**
  * Get the default graphical representation names
  * of an application component.
  * @param oGRRDefaultName
  *   The default name to be used for the graphical representation
  *   of a component
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
  virtual HRESULT AppGetDefaultGRRName2 (CATUnicodeString &oGRRDefaultName);

  /**
  * Post process after placing an application component instance 
  * @param iNewCompInst
  *   The newly placed component instance
  *   (CATISchComponent interface pointer).
  * @param iCntbleConnectedTo
  *   The connectable that the placed component is connected to or 
  *   placed onto
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
  virtual HRESULT AppPostPlaceProcess (CATISchComponent *iNewCompInst, 
    CATISchAppConnectable *iCntblConnectedTo);
 
  /**
  * Post process after sliding a component
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
  virtual HRESULT AppPostSlideProcess (void);

  /**
  * Post process after reconnecting a component to
  * a different compatible configuration.
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
  virtual HRESULT AppPostFlipConnectedProcess (void);

  /**
  * Post process after flipping an inserted component
  * about the inserted line segment of the route.
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
  virtual HRESULT AppPostFlipOnLineProcess (void);

  /**
  * Post process after flipping a component in "x"
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
  virtual HRESULT AppPostFlipHorizontalProcess (void);

  /**
  * Post process after flipping a component in "y"
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
  virtual HRESULT AppPostFlipVerticalProcess (void);

  /**
  * Post process after uninserting a component, disconnecting
  * it from a route.
  * @param iOldAppRoute1
  *   One of the route that was connected 
  *   to one connector of the inserted
  *   component before the operation.
  * @param iOldAppRoute2
  *   The other route 
  *   that was connected to the other connector 
  *   of the inserted component before the operation.
  *   This would be NULL if the component was connected at extremity.
  * @param iNewAppRoute
  *   The new route 
  *   created after the operation. 
  *   This would be NULL if the component was connected at extremity.
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
  virtual HRESULT AppPostUninsertProcess (CATISchRoute *iOldAppRoute1,
    CATISchRoute *iOldAppRoute2, CATISchRoute *iNewAppRoute);    

  /**
  * Post process after switching a component's graphic representation
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
  virtual HRESULT AppPostSwitchGraphicProcess (CATISchGRR *iGRR);

  /**
  * Query whether the application component can be placed in free space.
  * @param oBYes
  *   If TRUE, the component can be slided.
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
  virtual HRESULT AppOKToPlaceInSpace (boolean *oBYes);

  /**
  * Query whether the application component can be slided.
  * @param oBYes
  *   If TRUE, the component can be slided.
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
  virtual HRESULT AppOKToSlide (boolean *oBYes);

  /**
  * Query whether it is OK to reconnect a component to
  * a different compatible configuration.
  * @param oBYes
  *   If TRUE, then it is OK to flip the component.
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
  virtual HRESULT AppOKToFlipConnected (boolean *oBYes);

  /**
  * Query whether it is OK to flip a component about
  * its inserted line.
  * @param oBYes
  *   If TRUE, then it is OK to flip the component.
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
  virtual HRESULT AppOKToFlipOnLine (boolean *oBYes);

  /**
  * Query whether it is OK to flip the application component about X.
  * @param oBYes
  *   If TRUE, then it is OK to flip the component.
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
  virtual HRESULT AppOKToFlipVertical (boolean *oBYes);

  /**
  * Query whether it is OK to flip the application component about Y.
  * @param oBYes
  *   If TRUE, then it is OK to flip the component.
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
  virtual HRESULT AppOKToFlipHorizontal (boolean *oBYes);

  /**
  * Query whether it is OK to uninsert the application component.
  * @param oBYes
  *   If TRUE, then it is OK to uninsert the component.
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
  virtual HRESULT AppOKToUninsert (boolean *oBYes);

  /**
  * Query whether it is OK to scale the application component.
  * @param oBYes
  *   If TRUE, then it is OK to scale the component.
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
  virtual HRESULT AppOKToScale (boolean *oBYes);

  private:

  CAAESchAppComponent (const CAAESchAppComponent &);
  CAAESchAppComponent &operator = (const CAAESchAppComponent &);

}; 
#endif
