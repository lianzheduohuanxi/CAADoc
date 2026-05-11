//  COPYRIGHT  DASSAULT  SYSTEMES  2009-2010
//===================================================================  
//  
//  CATUExitPVRCommand.h  
//      Provide  implementation  to  interface  CATIUExitPVRCommands.  
//  
//===================================================================  
//  
//  December  2009    Creation: ITW  
//  July      2010    Update:   JLM ==> Quick code review
//  
//===================================================================  
#ifndef  CATUExitPVRCommand_H  
#define  CATUExitPVRCommand_H  

#include  "CATBaseUnknown.h"  

#include  "CATIUExitPVRCommands.h"  

#include  "CATErrorDef.h"  
#include  <stdlib.h>  

//-----------------------------------------------------------------------  

/**  
  *  Provide  implementation  for  a  CATUExitCrypt.  
  *  <br>  
  *  It implements the interfaces:  
  *    <ul>  
  *    <li> @see NavigatorInterfaces.CATIUExitCrypt </li> 
  *    </ul>  
  */  
class  CATUExitPVRCommand:  public  CATBaseUnknown  
{  
   CATDeclareClass ;  

public:  

   //  Standard  constructors  and  destructors  for  an  implementation  class  
   //  -----------------------------------------------------------------  
   CATUExitPVRCommand() ;  
   virtual  ~CATUExitPVRCommand() ;  

   /** 
     * User Exit called after opening a PRC from PVR specication.
     *
     * <br><b>Role</b>: Enables to implement customer operation after the PRC is opened from a PVR opened in CATIA.
     *
     * @param ixPVRDoc [in]
     *   PVR CATProduct document.
     *
     * @param ixPRCDoc [in]
     *   PRC CATProduct document.
     *
     * @return
     *   <code>S_OK</code> if everything ran ok, otherwise...
     */
     virtual HRESULT AfterPRCOpenFromPVR( CATDocument * ixPVRDoc , CATDocument * ixPRCDoc ) ;

   /** 
     * Enables to update an attribute value on PVR document.
     *
     * <br><b>Role</b>: Enables to update an attribute value on document to capture in particular PVR synchronization status.
     *
     * @param ixPVRDoc [in]
     *   Product View Result document in loaded in CATIA session.
     *
     * @param inIsyncNeeded [in]
     *   Synchronization status.
     *   <br><b>Legal values</b>: 
     *   <dl>
     *   <dt>0</dt>  <dd>Means that PVR product structure is up to date compared to ENOVIA structure.<dd>
     *   <dt>1</dt>  <dd>Means that PVR product structure need to be synchronized.<dd>
     *   </dl>
     *
     * @param ocAttrId [out]
     *   Id of the attribute that need to be updated.
     *
     * @param ocAttrVal [out]
     *   Attribute value to be set.
     *
     * @return
     *   <code>S_OK</code> if everything ran ok, otherwise...
     *   Method return code 
     *   <br><b>Legal values</b>: 
     *   <dl>
     *   <dt>S_OK</dt>    <dd>If user exit run well and an attribute value needs to be updated.<dd>
     *   <dt>S_FALSE</dt> <dd>If user exit run well and no attribute update is required.<dd>
     *   <dt>E_FAIL</dt>  <dd>In case of error in the user exit.<dd>
     *   </dl>
     */
     virtual HRESULT UpdateAttributeOnPvrSynchro( CATDocument      * ixPVRDoc
                                                , int                inIsyncNeeded
                                                , CATUnicodeString & ocAttrId 
                                                , CATUnicodeString & ocAttrVal ) ;  
   /** 
     * Enables to define default name to be used in Product View Result (PVR) document creation command.
     *
     * <br><b>Role</b>: Enables to define default name for PVR and Expand Capture name in Product View Result document creation command.
     *  <ul>
     *  <li>Default name for PVR is generated using Part Master or PRC name concatenated with "_PVR" character string.</li>
     *  <li>Default name for Expand Capture (PVS) is generated using Part Master or PRC name concatenated with "_PVS" character string.</li>
     *  </ul>
     *  <b><u>Note:</u></b> User Exit will be called at PVR creation command initiation and when end-user will request to go back to default name concerning PVR or PVS.
     *
     * @param ilNewFrom [in]
     *   One existing Product View Result document will be used to initialized new PVR.
     *
     * @param ilFilteredPVR [in]
     *   PVR will be associated to an Expand Capture.
     *
     * @param iAttributeIdLst [in]
     *   List of attribute Id build by having a prefix for object type followed by character '.' as separator and the attribute Id.
     *   <br><b>Legal values</b>: 
     *   <dl>
     *   <dt>PV.V_ID</dt>    <dd>For the attribute V_ID of the Part Version (root of the PVR assembly).<dd>
     *   <dt>PRC.V_Name</dt> <dd>For the attribute V_Name of the PRC (root of the PVR assembly or the assembly).<dd>
     *   </dl>
     *
     *   <br><b>Legal values for object types</b>: 
     *   <dl>
     *   <dt>PRC</dt>  <dd>Product Root Class representing the root of the assembly of the PVR to be created or the PRC on which the part instance is located.<dd>
     *   <dt>PVS</dt>  <dd>Expand Capture (PVS) selected if defined in PVR creation command context.<dd>
     *   <dt>PV</dt>   <dd>Part Version representing the root of the assembly of the PVR.<dd>
     *   </dl>
     *
     * @param iAttributeValueLst [in]
     *   List of attribute values corresponding to <b><i>iAttributeIdLst</i></b>.
     *
     * @param iocPVRName [inout]
     *   Default name for PVR to be created.
     *
     * @param iocPVSName [inout]
     *   Default name to be used in case of PVS creation.
     *
     * @return
     *   Method return code.
     *   <br><b>Legal values</b>:
     *   <dl>
     *   <dt>S_OK</dt>    <dd>If user exit run well.<dd>
     *   <dt>E_FAIL</dt>  <dd>In case of error in the user exit.<dd>
     *   </dl>
     */
     virtual HRESULT GetDefaultNamesForPVRCreation( int                                ilNewFrom
                                                  , int                                ilFilteredPVR
                                                  , const CATListValCATUnicodeString & iAttributeIdLst
                                                  , const CATListValCATUnicodeString & iAttributeValueLst
                                                  , CATUnicodeString                 & iocPVRName
                                                  , CATUnicodeString                 & iocPVSName           ) ;   
} ;  

#endif  







