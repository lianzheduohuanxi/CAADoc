// COPYRIGHT DASSAULT SYSTEMES 2012 

#include "CATIAV5Level.h"

// local CAAV5V6ExtMechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrCombCrvPanelStCmd.h"
#include "CAAV5V6ExtMmrCombinedCurveDlg.h"       // needed to create an edition dialog box
#include "CAAIV5V6ExtMmrCombinedCurve.h"         // needed to query the Combined Curve about its inputs (edition mode)
#include "CAAIV5V6ExtMmrCombCrvFactory.h"		    // needed to create a Combined Curve (creation mode)

// CATMecModExtendItf Framework
#include "CATIMmiUpdateError.h"
#include "CATIMmiErrUpdate.h"
#include "CATMmiExtendServicesFactory.h"

// System Framework
#include "CATGetEnvValue.h"               // To define the type of development
#include "CATBoolean.h"
#include "CATLib.h"
#include "CATCreateExternalObject.h"
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h" 
#include "CATLISTV_CATBaseUnknown.h"
#include "CATError.h"

// AfrFoundation Framework for V6
// ApplicationFrame for V5
#include "CATFrmEditor.h"                 // needed to retrieve the editor and then to highight objects

// Dialog Framework
#include "CATDlgDialog.h"                 // needed to return the dialog box to GiveMyPanel method of
                                          // father class CATMmrPanelStateCmd
// DialogEngine Framework
#include "CATDialogState.h"
#include "CATStateActivateNotification.h" // to distinguish begin/resume state in the command activation

// ObjectModelerSystem Framework
#include "CATIAlias.h"

// VisualizationInterfaces Framework for V6
// InteractiveInterfaces Framework for V5
#include "CATIBuildPath.h"                // needed to build a path element to highlight a feature

// VisualizationInterfaces Framework for V6
// VisualizationBase Framework for V5
#include "CATPathElement.h"               // needed to highlight objects

// VisualizationInterfaces Framework for V6
// Visualization Framework for V5
#include "CATIVisProperties.h"            // needed to change Combined Curve's graphical appearance
#include "CATVisPropertiesValues.h"

// VisualizationController Framework for V6
// Visualization Framework for V5
#include "CATHSO.h"                       // needed to highlight objects    

// CATMecModUseItf framework
#include "CATIMmiGeometricalSet.h"        // Only for GSMTool feature
#include "CATIGSMTool.h"                  // GSMTool and HybridBody features
#include "CATIMmiUseLinearBodyServices.h" //  To insert in ordered and linear body
#include "CATIMmiNonOrderedGeometricalSet.h"  // Only for GS feature
#include "CATIMmiUseBasicInsertion.h"
#include "CATIMmiPrtContainer.h" 
#include "CATIMmiUseUpdateError.h"
#include "CATMmiUseServicesFactory.h"

// CATMecModUIUseItf framework for V6
// MechanicalModelerUI Framework for V5
#include "CATPrtUpdateCom.h"              // needed to update the feature according to the user's update settings
#include "CATFeatureImportAgent.h"        // needed to be able to pick any element whatever its context is

// CATMecModLiveUseItf framework
#include "CATIBasicTool.h"                // To retrieve the current tool
#include "CATIMmiMechanicalFeature.h"
#include "CATIMmiUseBodyContent.h"
#include "CATIMmiUsePrtPart.h"                  // needed to look for a GSM tool

//GSMUseItf
#include "CATIGSMUseSpline.h"
#include "CATIGSMUseLine.h"

// FeatureModelerExt 
#include "CATFmContainerFacade.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"
#include "CATISpecObject.h"
// C++ Standard library
#include "iostream.h" 

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// CATMecModUIUseItf framework
#include "CATMmiUseServicesFactory.h" 

// CATMecModUseItf framework
#include "CATIMmiUseSetFactory.h"         // needed to create a GS 

#else
//============================================== 
// V5 only
//============================================== 

// MecModInterfaces Framework
#include "CATIMechanicalRootFactory.h"

#endif

CATCreateClass(CAAV5V6ExtMmrCombCrvPanelStCmd);

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : constructor
// Deriving from CATMmrPanelStateCmd provides an association between 
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
CAAV5V6ExtMmrCombCrvPanelStCmd::CAAV5V6ExtMmrCombCrvPanelStCmd(CAAIV5V6ExtMmrCombinedCurve *ipiCombinedCurve):
CATMmrPanelStateCmd("V5V6ExtCombinedCurveCommand"),
#else
//============================================== 
// V5 only
//============================================== 
CAAV5V6ExtMmrCombCrvPanelStCmd::CAAV5V6ExtMmrCombCrvPanelStCmd(CAAIV5V6ExtMmrCombinedCurve *ipiCombinedCurve):
CATMMUIPanelStateCmd("V5V6ExtCombinedCurveCommand"),
#endif
_pCurveAgent          (NULL),
_pDirectionAgent      (NULL),
_pCurve1FieldAgent    (NULL),
_pDirection1FieldAgent(NULL),
_pCurve2FieldAgent    (NULL),
_pDirection2FieldAgent(NULL),
_piCurve1              (NULL),
_piDir1                (NULL),
_piCurve2              (NULL),
_piDir2                (NULL),
_piCombinedCurve      (NULL) ,
_ActiveField          (0)
{
  cout <<"CAAV5V6ExtMmrCombCrvPanelStCmd::CAAV5V6ExtMmrCombCrvPanelStCmd" << endl;

  _mode = 1; // creation mode

  if (ipiCombinedCurve != NULL) 
  {
    // Edition mode.
    _mode = 0;
               
    // Memorises what curve is being edited.
    _piCombinedCurve = ipiCombinedCurve;
    _piCombinedCurve->AddRef();
        
    // Reads the inputs of the Combined Curve.
    HRESULT rc= E_FAIL;
    rc = _piCombinedCurve->GetCurve(1, _piCurve1);
    if (FAILED(rc)) 
      return;
        
    rc = _piCombinedCurve->GetDirection(1, _piDir1);
    if (FAILED(rc)) 
      return;
        
    rc = _piCombinedCurve->GetCurve(2, _piCurve2);
    if (FAILED(rc)) 
      return;
        
    rc = _piCombinedCurve->GetDirection(2, _piDir2);
    if (FAILED(rc)) 
      return ;
  }
    
  // creates the dialog box
  _panel = new CAAV5V6ExtMmrCombinedCurveDlg();

  // builds the dialog box 
  // ! do not call panel->Build from the panel constructor
  _panel->Build();
    
  // To manage the highlight of the Combined Curve and the UI active object that 
  // is used to agregate the Combined Curve at the right place.
  _editor = CATFrmEditor::GetCurrentEditor();
  _HSO = NULL;
  if (NULL != _editor)
  {
    _HSO = _editor->GetHSO();
  }
        
  // Fills in the dialog panel fields.
  UpdatePanelFields();

  // Checks whether the OK button can be pressed.
  CheckOKSensitivity();
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : destructor
//-----------------------------------------------------------------------------
CAAV5V6ExtMmrCombCrvPanelStCmd::~CAAV5V6ExtMmrCombCrvPanelStCmd()
{
  cout <<"CAAV5V6ExtMmrCombCrvPanelStCmd::~CAAV5V6ExtMmrCombCrvPanelStCmd" << endl;

  // Releases member data pointers before leaving.
  if (_piCombinedCurve != NULL)
  {
    _piCombinedCurve->Release();
    _piCombinedCurve = NULL;
  }

  if (_piCurve1 != NULL)
  { 
    _piCurve1->Release();
    _piCurve1 = NULL;
  } 
    
  if (_piDir1 != NULL)
  {  
    _piDir1->Release();
    _piDir1 = NULL;  
  }
   
  if (_piCurve2 != NULL)
  { 
    _piCurve2->Release();
    _piCurve2 = NULL; 
  }

  if (_piDir2 != NULL)
  { 
    _piDir2->Release();
    _piDir2 = NULL;
  }

  if (NULL != _pCurveAgent)
  {
    _pCurveAgent->RequestDelayedDestruction();
    _pCurveAgent = NULL;
  }

  if (NULL != _pDirectionAgent)
  {
    _pDirectionAgent->RequestDelayedDestruction();
    _pDirectionAgent = NULL;
  }

  if (NULL != _pCurve1FieldAgent)
  {
    _pCurve1FieldAgent->RequestDelayedDestruction();
    _pCurve1FieldAgent = NULL;
  }

  if (NULL != _pDirection1FieldAgent)
  {
    _pDirection1FieldAgent->RequestDelayedDestruction();
    _pDirection1FieldAgent = NULL;
  }

  if (NULL != _pCurve2FieldAgent)
  {
    _pCurve2FieldAgent->RequestDelayedDestruction();
    _pCurve2FieldAgent = NULL;
  }

  if (NULL != _pDirection2FieldAgent)
  {
    _pDirection2FieldAgent->RequestDelayedDestruction();
    _pDirection2FieldAgent = NULL;
  }

  if (NULL != _panel)
  { 
    _panel->RequestDelayedDestruction();
    _panel = NULL;
  }

  _editor = NULL;
  _HSO = NULL;
}
 
//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : BuildGraph()
//-----------------------------------------------------------------------------
void CAAV5V6ExtMmrCombCrvPanelStCmd::BuildGraph()
{
  // Agent Creation 
  _pCurveAgent           = new CATFeatureImportAgent("CurveAgent", NULL, NULL, MfNoDuplicateFeature);
  _pDirectionAgent       = new CATFeatureImportAgent("DirectionAgent", NULL, NULL, MfNoDuplicateFeature); 
  _pCurve1FieldAgent     = new CATDialogAgent("Curve1ActiveFieldAgent");
  _pDirection1FieldAgent = new CATDialogAgent("Direction1ActiveFieldAgent");
  _pCurve2FieldAgent     = new CATDialogAgent("Curve2ActiveFieldAgent");
  _pDirection2FieldAgent = new CATDialogAgent("Direction2ActiveFieldAgent");

  //-----------------------------------------------------------------------------
  // Selection Agents
  //-----------------------------------------------------------------------------
    
  // _pCurveAgent to select a curve
  _pCurveAgent->SetOrderedElementType("CATIMfMonoDimResult");
  _pCurveAgent->AddOrderedElementType("CATCurve"           );
  _pCurveAgent->AddOrderedElementType("CATEdge"            );
  _pCurveAgent->AddOrderedElementType("CATWire"            );
  _pCurveAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO | CATDlgEngOneShot);
  _pCurveAgent->SetAgentBehavior(MfPermanentBody | MfLastFeatureSupport | MfRelimitedFeaturization);
        
 // _pDirectionAgent to select a direction
 _pDirectionAgent->SetOrderedElementType("CATIMfLine");
 _pDirectionAgent->AddOrderedElementType("CATLine");
 _pDirectionAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO);//|CATDlgEngOneShot);
 _pDirectionAgent->SetAgentBehavior(MfPermanentBody | MfLastFeatureSupport | MfRelimitedFeaturization);

 // Setting an ID to be able to read the created import
 GUID guid =  { /* c17e43d3-2b56-4753-bfe5-bb5f289e2091 */
    0xc17e43d3,
    0x2b56,
    0x4753,
    {0xbf, 0xe5, 0xbb, 0x5f, 0x28, 0x9e, 0x20, 0x91}
     };

 //_pDirectionAgent->SetImportApplicativeId(guid);
    
 // _pCurveFieldAgent and _pDirectionFieldAgent to change current acquisition type
 _pCurve1FieldAgent->AcceptOnNotify(_panel->GetField(1), _panel->GetField(1)->GetListSelectNotification());
 _pCurve2FieldAgent->AcceptOnNotify(_panel->GetField(3), _panel->GetField(3)->GetListSelectNotification());
 _pDirection1FieldAgent->AcceptOnNotify(_panel->GetField(2), _panel->GetField(2)->GetListSelectNotification());
 _pDirection2FieldAgent->AcceptOnNotify(_panel->GetField(4), _panel->GetField(4)->GetListSelectNotification());

 //-----------------------------------------------------------------------------
 // Command States
 //-----------------------------------------------------------------------------

 // Uses "PanelStates" instead of standard "DialogStates".
 // Theses states are provided by father class CATMmrPanelStateCmd.
 // They make it possible for you not to worry about transition to OK and Cancel States.

 // Curve selection state
 CATDialogState *WaitForCurveState= GetInitialPanelState("Select a curve or another input field");
 if (WaitForCurveState)
 {
   WaitForCurveState->AddDialogAgent(_pCurveAgent); 
   WaitForCurveState->AddDialogAgent(_pDirection1FieldAgent); 
   WaitForCurveState->AddDialogAgent(_pDirection2FieldAgent); 
   WaitForCurveState->AddDialogAgent(_pCurve1FieldAgent); 
   WaitForCurveState->AddDialogAgent(_pCurve2FieldAgent); 
 }

 // Direction selection state
 CATDialogState *WaitForDirectionState= AddPanelState("Select a direction or another input field");
 if (WaitForDirectionState)
 {
   WaitForDirectionState->AddDialogAgent(_pDirectionAgent);
   WaitForDirectionState->AddDialogAgent(_pCurve1FieldAgent);
   WaitForDirectionState->AddDialogAgent(_pCurve2FieldAgent);
   WaitForDirectionState->AddDialogAgent(_pDirection1FieldAgent); 
   WaitForDirectionState->AddDialogAgent(_pDirection2FieldAgent);
 } 

 //-----------------------------------------------------------------------------
 // Transitions
 //-----------------------------------------------------------------------------

 // From Curve to Curve ( click on several curves to change of curve )
 AddTransition(WaitForCurveState, WaitForCurveState, 
                    IsOutputSetCondition(_pCurveAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::CurveSelected));   

 AddTransition(WaitForCurveState, WaitForCurveState, 
                    IsOutputSetCondition(_pCurve1FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Curve1FieldSelected));   

 AddTransition(WaitForCurveState, WaitForCurveState, 
                    IsOutputSetCondition(_pCurve2FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Curve2FieldSelected));   

 // From Curve to Direction
 AddTransition(WaitForCurveState, WaitForDirectionState, 
                    IsOutputSetCondition(_pDirection1FieldAgent),
                    Action((ActionMethod ) &CAAV5V6ExtMmrCombCrvPanelStCmd::Direction1FieldSelected));   
    
 AddTransition(WaitForCurveState, WaitForDirectionState, 
                    IsOutputSetCondition(_pDirection2FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Direction2FieldSelected));   
        
 // From Direction to Direction  ( click on several directions to change of curve )
 AddTransition(WaitForDirectionState, WaitForDirectionState, 
                    IsOutputSetCondition(_pDirectionAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::DirectionSelected));   

 AddTransition(WaitForDirectionState, WaitForDirectionState, 
                    IsOutputSetCondition(_pDirection1FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Direction1FieldSelected));   

 AddTransition(WaitForDirectionState, WaitForDirectionState, 
                    IsOutputSetCondition(_pDirection2FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Direction2FieldSelected));   

 // From Direction to Curve 
 AddTransition(WaitForDirectionState, WaitForCurveState, 
                    IsOutputSetCondition(_pCurve1FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Curve1FieldSelected));   
    
 AddTransition(WaitForDirectionState, WaitForCurveState, 
                    IsOutputSetCondition(_pCurve2FieldAgent),
                    Action((ActionMethod) &CAAV5V6ExtMmrCombCrvPanelStCmd::Curve2FieldSelected));   

}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : GiveMyPanel()
//-----------------------------------------------------------------------------
CATDlgDialog* CAAV5V6ExtMmrCombCrvPanelStCmd::GiveMyPanel()
{
  // Used by father class CATMmrPanelStateCmd to be notified of events
  // sent by the OK and CANCEl press button.
  return (_panel);
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : CancelAction()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::CancelAction(void *)
{
  // Unset Repeat mode  when cancel or close is clicked 
  if (_editor) 
		_editor->UnsetRepeatedCommand();
  return TRUE ; 
} 

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : OkAction()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::OkAction(void *)
{  
  HRESULT rc = E_FAIL;

  // EDS 4/7/2005 (RI 492591): Vider les SO en sortie de commande
  EmptySO();

  //Modify or create the CombinedCurve 
  if (0 == GetMode() && (NULL !=_piCombinedCurve))
  {
    // Updates the combine with its new curves inputs.
    rc = _piCombinedCurve->SetCurve(1, _piCurve1);
    if (FAILED(rc)) 
      return FALSE;
        
    rc = _piCombinedCurve->SetDirection(1, _piDir1);
    if (FAILED(rc)) 
      return FALSE;
        
    rc = _piCombinedCurve->SetCurve(2, _piCurve2);
    if (FAILED(rc)) 
      return FALSE;
        
    rc = _piCombinedCurve->SetDirection(2, _piDir2);
    if (FAILED(rc)) 
      return FALSE;
  }
  else
  {
    rc = CreateCombinedCurve();        
  }
    
  //Update the Combined Curve
  CATBaseUnknown *pCombinedCurveObject = NULL;
  if (SUCCEEDED(rc) && (NULL != _piCombinedCurve))
  {
    rc = _piCombinedCurve->QueryInterface(IID_CATBaseUnknown, (void**) &pCombinedCurveObject);  
    if (SUCCEEDED(rc))
    {
      // Uses CATPrtUpdateCom to update the Combined Curve ( manual update mode )
      // or the whole part ( automatic update mode ).
      // CATPrtUpdateCom also encapsulates interactive error management ( edit / delete, etc...)
    
      // pCombinedCurveObject = the feature to update, translated into part->update 
      // in case of automatic update
      // 1= respects update interactive setting ( manual / automatic ) setting
      // GetMode= creation or modification. Prevents the user from creating a feature in error
      //
      CATPrtUpdateCom *pUpdateCommand = new CATPrtUpdateCom(pCombinedCurveObject, 1, GetMode());

	  // This section is useless for the usecase because the updadte errors are managed bt the update command. 
	  // It's just to show how to use the update error interfaces.
      CATIMmiUseUpdateError_var UpdateError = pCombinedCurveObject;
	  if (UpdateError != NULL_var)
	  {
		rc = UpdateError->HasAnUpdateError();
		if (rc == S_OK)
		{ 
		   CATUnicodeString ErrMsg;
           rc = UpdateError->GetDiagnostic(ErrMsg);
		   cout << "update error message = " <<ErrMsg.ConvertToChar() << endl;

		   CATLISTV(CATIMmiMechanicalFeature_var) SickFeatures;
           rc = UpdateError->GetAssociatedSickFeatures(SickFeatures);
		   int nbSickFeat = SickFeatures.Size();
					 
		   if (nbSickFeat)
		   {
			 cout << "Number of sick features = " << nbSickFeat << endl;
        
             CATUnicodeString ErrFullMsg;
             rc = UpdateError->GetFullDiagnostic(ErrFullMsg);
			 cout << "update error message = " <<ErrFullMsg.ConvertToChar() << endl;
		   }

		   // Get more information on the error
		   CATIMmiUpdateError_var UpdateErrorExt = pCombinedCurveObject;
		   if (UpdateErrorExt != NULL_var)
		   {
			 CATError* Err=NULL;
             rc = UpdateErrorExt->GetMmiUpdateError(Err);
			 if (SUCCEEDED(rc))
			 {
               CATIMmiErrUpdate *piErrorAccess = NULL;
               rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

			   if (SUCCEEDED(rc) && piErrorAccess)
			   {
				 rc = piErrorAccess->IsAnUpdateError(Err);
				 if (SUCCEEDED(rc))
				 {
                    CATUnicodeString ErrMsg2;
                    rc = piErrorAccess->GetMmiDiagnostic(Err, ErrMsg2);
					cout << "update error message = " << ErrMsg2.ConvertToChar() << endl;	
					CATUnicodeString ErrMsg3;
                    rc = piErrorAccess->GetMmiFullDiagnostic(Err, ErrMsg3);
				    cout << "update error full diagnostic = " << ErrMsg3.ConvertToChar() << endl;			
					CATUnicodeString ErrMsg4;
                    rc = piErrorAccess->GetMmiNLSDiagnostic(Err, ErrMsg4);
					cout << "update error message = " << ErrMsg4.ConvertToChar() << endl;			
				  }
				  piErrorAccess->Release();
				  piErrorAccess=NULL;
				}
			  }
		    }
 
			rc = E_FAIL;
		  }
		}
    }
  }                       

  //Insert if necessary ( if inside an ordered (and linear) body )
  //
  if (SUCCEEDED(rc) && (NULL != pCombinedCurveObject))
  {
    CATBoolean IsInsideOrderedBody = FALSE;
    rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);
    if (SUCCEEDED(rc) && (TRUE == IsInsideOrderedBody))
    {
      // Invoke the Insert method is mandatory 
      CATBaseUnknown_var spBUOnCC = pCombinedCurveObject;
      
      CATIMmiUseLinearBodyServices *OGSServices = NULL;
      rc = CATMmiUseServicesFactory::CreateMmiUseLinearBodyServices(OGSServices);

      if (SUCCEEDED(rc) && OGSServices)
      {
        rc = OGSServices->Insert(spBUOnCC);
        OGSServices->Release();
        OGSServices=NULL;
      }
    }
  }

  //Give the Combined Curve a better appearance
  if (SUCCEEDED(rc) && (1 == GetMode()) && (NULL != pCombinedCurveObject))
  {
    CATIVisProperties *piGraphPropOnCombinedCurve = NULL;
    rc = pCombinedCurveObject->QueryInterface(IID_CATIVisProperties, (void**)& piGraphPropOnCombinedCurve);
    if (SUCCEEDED(rc)) 
    {
      CATVisPropertiesValues Attribut;
      Attribut.SetColor(255, 255, 0); // yellow
      Attribut.SetWidth(4);           // medium thickness
      piGraphPropOnCombinedCurve->SetPropertiesAtt(Attribut, CATVPAllPropertyType, CATVPLine);

      piGraphPropOnCombinedCurve->Release();
      piGraphPropOnCombinedCurve = NULL ;
    }
  }

  if (NULL != pCombinedCurveObject)
  {
    pCombinedCurveObject->Release(); 
    pCombinedCurveObject = NULL ;
  }

  return rc;
 
}

#ifdef CATIAV5R23
//============================================== 
// V5 only
//==============================================
//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd::GiveMyFeature()
//-----------------------------------------------------------------------------
CATISpecObject_var CAAV5V6ExtMmrCombCrvPanelStCmd::GiveMyFeature()
{
    CATISpecObject_var MyFeature(_piCombinedCurve);
    return MyFeature;
}
#endif

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : CurveSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::CurveSelected(void*)
{
  // checks if the selected object must be added ( not  selected yet ) or removed ( already selected ) as input curve
  ElementSelected(_pCurveAgent);  
    
  // gets ready for next acquisition
  _pCurveAgent->InitializeAcquisition();
    
  return TRUE;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : DirectionSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::DirectionSelected(void*)
{
  // checks if the selected object must be added ( not  selected yet ) or removed ( already selected ) as input direction
  ElementSelected(_pDirectionAgent);  

  // gets ready for next acquisition
  _pDirectionAgent->InitializeAcquisition();
    
  return TRUE;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : Curve1FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::Curve1FieldSelected(void*)
{
  // put the focus on the first field of the Combined Curve edition dialog box 
  // ( first curve ) and highlight the corresponding geometrical element 
  SetActiveField(1);
    
  // gets ready for next acquisition
  _pCurve1FieldAgent->InitializeAcquisition();
    
  return TRUE;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : Direction1FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::Direction1FieldSelected(void*)
{
  // put the focus on the second field of the Combined Curve edition dialog box
  // ( first direction ) and highlight the corresponding geometrical element 
  SetActiveField(2);
    
  // gets ready for next acquisition
  _pDirection1FieldAgent->InitializeAcquisition();
    
  return TRUE;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : Curve2FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::Curve2FieldSelected(void*)
{
  // put the focus on the third field of the Combined Curve edition dialog box
  // ( second curve ) and highlight the corresponding geometrical element 
  SetActiveField(3);
    
  // gets ready for next acquisition
  _pCurve2FieldAgent->InitializeAcquisition();
    
  return TRUE;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : Direction2FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCombCrvPanelStCmd::Direction2FieldSelected(void*)
{
  // put the focus on the fourth field of the Combined Curve edition dialog box
  // ( second direction ) and highlight the corresponding geometrical element 
  SetActiveField(4);
    
  // gets ready for next acquisition
  _pDirection2FieldAgent->InitializeAcquisition();
    
  return TRUE;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : SetActiveField()
//-----------------------------------------------------------------------------
void CAAV5V6ExtMmrCombCrvPanelStCmd::SetActiveField(int ActiveField)
{
  // this method main goal is to show the user that the acquisition
  // is now dedicated to the input field
  _ActiveField = ActiveField;
    
  // first let's empty current highlighted objects
  if ( NULL != _HSO )
  {
    _HSO->Empty(); 
  }
      
  // Gets the geometrical element to highlight
  CATBaseUnknown_var GeomElem = NULL_var;
  if (1 == ActiveField)
    GeomElem = _piCurve1;
  if (2 == ActiveField)
    GeomElem = _piDir1;
  if (3 == ActiveField)
    GeomElem = _piCurve2;
  if (4 == ActiveField)
    GeomElem = _piDir2;

  if ((GeomElem != NULL_var) && (NULL != _HSO) && (NULL !=_editor))
  {
    // Build a path element
    CATIBuildPath *piBuildPath = NULL;
    HRESULT rc = GeomElem->QueryInterface(IID_CATIBuildPath, (void**) &piBuildPath);
    if (SUCCEEDED(rc))
    {
      CATPathElement Context = _editor->GetUIActiveObject();
      CATPathElement *pPathElement = NULL;
      rc = piBuildPath->ExtractPathElement(&Context,&pPathElement);

      if (pPathElement != NULL)
      {  
        // the geometrical element corresponding to the active field is now highlighted
        _HSO->AddElement(pPathElement); 
                
        pPathElement->Release();
        pPathElement = NULL ;
      }
            
      piBuildPath->Release(); 
      piBuildPath = NULL ;
    }
  }
    
  // puts the focus on the Active Field is the Combined Curve edition dialog box
  _panel->SetActiveField(ActiveField); 

}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : ElementSelected()
//-----------------------------------------------------------------------------
void CAAV5V6ExtMmrCombCrvPanelStCmd::ElementSelected(CATFeatureImportAgent *pAgent)
{
  cout <<" CAAV5V6ExtMmrCombCrvPanelStCmd::ElementSelected" << _ActiveField << endl;

  if ((pAgent == NULL) || (_ActiveField == 0))
    return;
    
  // translates the selection into the good pointer on a CATBaseUnknwon model element
  CATBaseUnknown *pSelection = pAgent->GetElementValue(pAgent->GetValue());
    
  if (NULL != pSelection)
  {
    // checks whether the selected element is the same than the one "in" the active field
    // o if this element is the same, the user wants to erase his selection.
    // o otherwise, the user wants to replace the old selected element by the new one.
    switch(_ActiveField)
    {
      case 1 :
      { 
			  // gets a pointer on CATBaseUnknown for the selection
        CATBaseUnknown *pSelectedSpline1 = NULL;
        HRESULT rc = pSelection->QueryInterface(IID_CATBaseUnknown, (void**)&pSelectedSpline1);
        if (FAILED(rc)) 
          return;
       
        if (_piCurve1 == pSelectedSpline1 && _piCurve1 != NULL) // same one
        {
          _piCurve1->Release() ;// this pointeur is not null 
          _piCurve1 = NULL ; // erases the selection
        }                
        else
        {
          if (NULL != _piCurve1)
            _piCurve1->Release() ; 
          _piCurve1 = pSelectedSpline1; // other one, replaces the selection
          _piCurve1->AddRef() ;
        }                
        pSelectedSpline1->Release();
        pSelectedSpline1  = NULL ;
        break;
      }
      case 2 :
      { 
			  // gets a pointer on CATBaseUnknown for the selection
        CATBaseUnknown *pSelectedLine1 = NULL;
        HRESULT rc = pSelection->QueryInterface(IID_CATBaseUnknown, (void**)&pSelectedLine1);
        if (FAILED(rc)) 
          return;

        if (_piDir1 == pSelectedLine1 && _piDir1 != NULL) 
        {
          _piDir1->Release() ;// this pointeur is not null 
          _piDir1 = NULL ;
        }
        else
        {
          if (NULL != _piDir1) 
            _piDir1->Release() ; 
          _piDir1 = pSelectedLine1;
          _piDir1->AddRef();
        }
			  pSelectedLine1->Release();
        pSelectedLine1  = NULL ;
        break;
      }
      case 3 :
      { 
			  // gets a pointer on CATBaseUnknown for the selection
        CATBaseUnknown *pSelectedSpline2 = NULL;
        HRESULT rc = pSelection->QueryInterface(IID_CATBaseUnknown, (void**)&pSelectedSpline2);
        if (FAILED(rc)) 
          return;

        if (_piCurve2 == pSelectedSpline2 && _piCurve2 != NULL) 
        {
          _piCurve2->Release();            
          _piCurve2 = NULL ;
        }
        else
        {
          if ( NULL != _piCurve2) 
            _piCurve2->Release(); 
          _piCurve2 = pSelectedSpline2;
          _piCurve2->AddRef();
        }
			  pSelectedSpline2->Release();
        pSelectedSpline2 = NULL ;
        break;
      }
      case 4 :
      { 
        // gets a pointer on CATBaseUnknown for the selection
        CATBaseUnknown *pSelectedLine2 = NULL;
        HRESULT rc = pSelection->QueryInterface(IID_CATBaseUnknown, (void**)&pSelectedLine2);
        if ( FAILED(rc)) 
          return;

        if (_piDir2 == pSelectedLine2 && _piDir2 != NULL) 
        {
          _piDir2->Release();
          _piDir2 = NULL ;
        }
        else
        {
          if (NULL != _piDir2) 
            _piDir2->Release() ; 
          _piDir2 = pSelectedLine2;
          _piDir2->AddRef();
        }
			  pSelectedLine2->Release();
        pSelectedLine2 = NULL ;
        break;
      }
    }
       

    // updates the text corresponding to the feature names in the panel fields
    UpdatePanelFields();
       
    // ckecks whether the four fields are filled in or not :
    // o if the four fields are filled, the Combined Curve can be created or modified
    //    => the OK button can be pressed
    // o if at least one field is not filled, the Combined Curve can not be created or modified
    //    => The OK button can not be pressed ( it is grayed )
    CheckOKSensitivity();
  } 

  return;
}       
        
//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : CheckOKSensitivity()
//-----------------------------------------------------------------------------
void CAAV5V6ExtMmrCombCrvPanelStCmd::CheckOKSensitivity()
{
  if (_piCurve1 != NULL && _piDir1 != NULL && _piCurve2 != NULL && _piDir2 != NULL)
    _panel->SetOKSensitivity(CATDlgEnable);
  else
    _panel->SetOKSensitivity(CATDlgDisable);

  return;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : UpdatePanelFields()
//-----------------------------------------------------------------------------
void CAAV5V6ExtMmrCombCrvPanelStCmd::UpdatePanelFields()
{
  // gets the name of the selected elements and put these names into the Combined Curve edition dialog box relevant text fields
  if (_piCurve1 != NULL)
  {
    CATIAlias_var AliasCurve1 = _piCurve1;
    if (AliasCurve1 != NULL_var)
      _panel->SetName(1, AliasCurve1->GetAlias());
    else
	  _panel->SetName(1, CATUnicodeString("no selection"));
  }
  else
    _panel->SetName(1, CATUnicodeString("no selection"));
    
  if (_piDir1 != NULL)
  {
    CATIAlias_var AliasDir1 = _piDir1;
    if (AliasDir1 != NULL_var)
      _panel->SetName(2, AliasDir1->GetAlias());
    else
      _panel->SetName(2, CATUnicodeString("no selection"));
  }
  else
    _panel->SetName(2, CATUnicodeString("no selection"));

  if (_piCurve2 != NULL)
  {
    CATIAlias_var AliasCurve2 = _piCurve2;
    if (AliasCurve2 != NULL_var)
      _panel->SetName(3, AliasCurve2->GetAlias());
    else
      _panel->SetName(3, CATUnicodeString("no selection"));
  }
  else
    _panel->SetName(3, CATUnicodeString("no selection"));

  if (_piDir2 != NULL)
  {
    CATIAlias_var AliasDir2 = _piDir2;
    if (AliasDir2 != NULL_var)
      _panel->SetName(4, AliasDir2->GetAlias());
    else
      _panel->SetName(4, CATUnicodeString("no selection"));
  }
  else
    _panel->SetName(4, CATUnicodeString("no selection"));

  return ;
}

//-----------------------------------------------------------------------------
// CAAV5V6ExtMmrCombCrvPanelStCmd : GetMode()
//-----------------------------------------------------------------------------
int CAAV5V6ExtMmrCombCrvPanelStCmd::GetMode()
{
  // This very simple methods checks if the user is creating or editing the Combined Curve.
  // This data is used by father command CATMmrPanelStateCmd and by CATPrtUpdateCom.
  // They both provide standard edition command behaviour :
  // for example, it is not possible to create a sick Combined Curve ( a Combined Curve generating an error )

  return _mode;  // 0 : edit mode 
                 // 1 : creation mode    
}

//-----------------------------------------------------------------------------

HRESULT CAAV5V6ExtMmrCombCrvPanelStCmd::CreateCombinedCurve()
{
  cout <<" CAAV5V6ExtMmrCombCrvPanelStCmd::CreateCombinedCurve" << endl;

  HRESULT rc = E_FAIL;

  // 1- Looking for a feature set to create the Combined Curve
  
  // CATIGSMTool is implemented by the HybridBody and GSMTool StartUp
  // it is a valid pointer to handle the body which will contain the new
  // Combined Curve
  CATIGSMTool *piGSMTool = NULL;

  char * pCombCrvOGS = NULL;
  CATLibStatus result = ::CATGetEnvValue("CAAMmrCombCrvOGS",&pCombCrvOGS);  
  if ((CATLibError == result) || (NULL == pCombCrvOGS))
  {
    char * pCombCrvNoHybridBody = NULL;
    result = ::CATGetEnvValue("CAAMmrCombCrvNoHybridBody",&pCombCrvNoHybridBody); 
    if ((CATLibError == result) || (NULL == pCombCrvNoHybridBody))
    {
      // Looking for or creating only a Geometrical Set
      // The result cannot be an ordered geometrical set or an hybrid body
      rc = LookingForGeomSet(&piGSMTool);
    }
    else
    {
      free(pCombCrvNoHybridBody);
      pCombCrvNoHybridBody = NULL;

      // Looking for an OGS or a GS, or creating a Geometrical Set
      // The result cannot be an hybrid body
      rc = LookingForGeomSetOrOrderedGeomSet(&piGSMTool);   
    }
  }
  else
  {
    free (pCombCrvOGS);
    pCombCrvOGS = NULL;

    // Looking for any type of mechanical bodies, or creating a Geometrical Set
    // The result cannot be a former solid body
    rc = LookingForAnyTypeOfBody(&piGSMTool);       
  }

  // 2- Creating the Combined Curve
  if (SUCCEEDED(rc) && (NULL != piGSMTool))
  {
    CATIMmiMechanicalFeature_var spMechFeatOnMainTool = piGSMTool;
    if (NULL_var != spMechFeatOnMainTool)
    {
      //Get container
      CATIMmiPrtContainer_var spPrtCont=NULL_var;
      rc = spMechFeatOnMainTool->GetPrtContainer(spPrtCont);
      if (SUCCEEDED(rc) && spPrtCont!= NULL_var)
      {
        CAAIV5V6ExtMmrCombCrvFactory *piCombinedCurveFactory = NULL;
        rc = spPrtCont->QueryInterface(IID_CAAIV5V6ExtMmrCombCrvFactory , (void**)& piCombinedCurveFactory);
        if (SUCCEEDED(rc))
        {
          // Create the Combined Curve        
          rc = piCombinedCurveFactory->CreateCombinedCurve(_piCurve1, _piDir1, _piCurve2,_piDir2, _piCombinedCurve);

          piCombinedCurveFactory->Release();
          piCombinedCurveFactory = NULL ;
        }        
      }

      // Insert in geometrical set 
      CATIMmiUseBasicInsertion_var hBasicInsertion = _piCombinedCurve; 
      if (SUCCEEDED(rc) && (NULL != piGSMTool) && (NULL_var != hBasicInsertion))
      { 
        CATIMmiMechanicalFeature_var hTarget = piGSMTool;

        if (hTarget != NULL_var)
        {
          // Checks the type of the GSMTool 
          int TypeOrderedBody = -1;
          piGSMTool->GetType(TypeOrderedBody);

          if (1 == TypeOrderedBody)
          {  
            // OGS/HB : the CC is set after the current feature or at the end
            //       of the set, if the current feature is the set itself
            //
            cout <<" Ordered and linear body " << endl;
            CATIMmiMechanicalFeature_var CurrentElt = GetCurrentFeature() ;
         
            if (CurrentElt != NULL_var)
            {
              CATIMmiUseBodyContent_var hBodyContent = piGSMTool;
              if (hBodyContent != NULL_var)
              {
                CATListValCATBaseUnknown_var listFeatures;
                hBodyContent-> GetMechanicalFeatures(listFeatures);
                if (listFeatures.Locate(CurrentElt))
                {
                  hBasicInsertion->InsertAfter(CurrentElt);
                }
                else
                {
                  hBasicInsertion->InsertInside(piGSMTool);
                }
              }
            }
          }
          else
          {
            // GS : the CC is set at the end of the set
            cout <<" GS case " << endl;
            hBasicInsertion->InsertInside(piGSMTool);
          }
        }
      }
    }
  }
  

  if ( NULL != piGSMTool )
  {
    piGSMTool->Release();
    piGSMTool = NULL;
  }

  return rc;
}

//-----------------------------------------------------------------------------

HRESULT CAAV5V6ExtMmrCombCrvPanelStCmd::LookingForGeomSet(CATIGSMTool ** piGsmtool)
{
  if ((NULL == piGsmtool) || (NULL ==_editor) ) return E_FAIL;

  HRESULT rc= E_FAIL;

  *piGsmtool = NULL;

  // Retrieve the Part feature which holds the current tool
  CATIMmiUsePrtPart * pIPrtPart = NULL;
  CATPathElement PathAct = _editor->GetUIActiveObject();
  rc = PathAct.Search(IID_CATIMmiUsePrtPart,(void**)&pIPrtPart);

  if (SUCCEEDED(rc) && (NULL!=pIPrtPart))
  {
    CATBoolean ToolToCreate = TRUE;

    CATIBasicTool_var CurrentTool = NULL_var;
    rc = pIPrtPart->GetInWorkObjectTool(CurrentTool);

    if (SUCCEEDED(rc) && NULL_var != CurrentTool)
    {
      // is it a Geometrical Set ?
      CATIMmiNonOrderedGeometricalSet * pIGSOnCurrentTool = NULL;
      rc = CurrentTool->QueryInterface(IID_CATIMmiNonOrderedGeometricalSet, (void**) &pIGSOnCurrentTool);
      if (SUCCEEDED(rc))
      {
        // Ok we have found a valid geometrical set
        ToolToCreate = FALSE;

        rc = pIGSOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**) piGsmtool);

        pIGSOnCurrentTool->Release();
        pIGSOnCurrentTool = NULL;
                  
      }
    }

    if (TRUE == ToolToCreate)
    {
      rc = CreateTool(pIPrtPart,piGsmtool);
    }
  }

  if (NULL != pIPrtPart)
  {
    pIPrtPart->Release();
    pIPrtPart = NULL;
  }

  return rc;
}

//-----------------------------------------------------------------------------

HRESULT CAAV5V6ExtMmrCombCrvPanelStCmd::LookingForGeomSetOrOrderedGeomSet(CATIGSMTool ** piGsmtool)
{
  if ((NULL == piGsmtool) || (NULL ==_editor)) 
    return E_FAIL;

  HRESULT rc= E_FAIL;

  *piGsmtool = NULL;

  CATIMmiUsePrtPart * pIPrtPart = NULL;
  CATPathElement PathAct = _editor->GetUIActiveObject();
    
  rc = PathAct.Search(IID_CATIMmiUsePrtPart,(void**)&pIPrtPart)  ;

  if (SUCCEEDED(rc) && (NULL!=pIPrtPart))
  {
    CATBoolean ToolToCreate = TRUE;  

    CATIBasicTool_var CurrentTool = NULL_var;
    rc = pIPrtPart->GetInWorkObjectTool(CurrentTool);

    if (SUCCEEDED(rc) && NULL_var != CurrentTool)
    {
      // is it a GSMTool ?
      CATIMmiGeometricalSet * pIGSMToolOnCurrentTool = NULL;
      rc = CurrentTool->QueryInterface(IID_CATIMmiGeometricalSet, (void**) &pIGSMToolOnCurrentTool);
      if (SUCCEEDED(rc))
      {
        // Ok we have found a valid geometrical set ( ordered or not )
        ToolToCreate = FALSE;

        rc = pIGSMToolOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**) piGsmtool);

        pIGSMToolOnCurrentTool->Release();
        pIGSMToolOnCurrentTool = NULL;
      }
    }

    if ((TRUE == ToolToCreate))
    {
      rc = CreateTool(pIPrtPart,piGsmtool);
    }

  }

  if (NULL != pIPrtPart)
  {
    pIPrtPart->Release();
    pIPrtPart = NULL ;
  }

  return rc ;
}

//-----------------------------------------------------------------------------

HRESULT CAAV5V6ExtMmrCombCrvPanelStCmd::LookingForAnyTypeOfBody(CATIGSMTool ** piGsmtool)
{
   if ( (NULL == piGsmtool) || (NULL ==_editor) ) return E_FAIL ;

   HRESULT rc= E_FAIL ;

   *piGsmtool = NULL ;

   CATIMmiUsePrtPart * pIPrtPart = NULL ;
   CATPathElement PathAct = _editor->GetUIActiveObject();
    
   rc = PathAct.Search(IID_CATIMmiUsePrtPart,(void**)&pIPrtPart)  ;

   if ( SUCCEEDED(rc) && ( NULL!=pIPrtPart) )
   {
       CATBoolean ToolToCreate = TRUE ;  

       CATIBasicTool_var CurrentTool = NULL_var;
       rc = pIPrtPart->GetInWorkObjectTool(CurrentTool);

       if (SUCCEEDED(rc) && NULL_var != CurrentTool )
       {
          // is it a GSMTool or an hybrid body ?
          CATIGSMTool * pIGSMToolOnCurrentTool = NULL ;
          rc = CurrentTool->QueryInterface(IID_CATIGSMTool, (void**) &pIGSMToolOnCurrentTool);
          if ( SUCCEEDED(rc) )
          {
              // Ok we have found a valid body
              ToolToCreate = FALSE ;

              *piGsmtool = pIGSMToolOnCurrentTool ;
          }
       }

       if ( TRUE == ToolToCreate )
       {
          rc = CreateTool(pIPrtPart,piGsmtool);
       }

   }

   if ( NULL != pIPrtPart )
   {
        pIPrtPart->Release();
        pIPrtPart = NULL ;
   }

   return rc ;
}

//-----------------------------------------------------------------------------

HRESULT CAAV5V6ExtMmrCombCrvPanelStCmd::CreateTool(CATIMmiUsePrtPart * pIPrtPart, CATIGSMTool ** pIGsmTool)
{
  if ((pIGsmTool == NULL) || (NULL == pIPrtPart))
    return E_FAIL;

  *pIGsmTool = NULL;

  HRESULT rc = E_FAIL;

  CATIMmiMechanicalFeature_var spMechFeatOnMainTool = pIPrtPart;
  if (NULL_var != spMechFeatOnMainTool)
  {
    //Get container
    CATIMmiPrtContainer_var spPrtCont=NULL_var;
    rc = spMechFeatOnMainTool->GetPrtContainer(spPrtCont);
    if (SUCCEEDED(rc) && spPrtCont!= NULL_var)
    {
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
      CATIMmiUseSetFactory_var spMechanicalRootFactory = spPrtCont;
      if (spPrtCont != NULL_var)
      {
        CATIMmiMechanicalFeature_var spGSMTool;
	    rc = spMechanicalRootFactory->CreateGeometricalSet("", spMechFeatOnMainTool, spGSMTool);
#else
//============================================== 
// V5 only
//==============================================
      CATIMechanicalRootFactory_var spMechanicalRootFactory = spPrtCont;
      if (spPrtCont != NULL_var)
      {
        CATISpecObject_var spSpecOnGSMTool;
        rc = spMechanicalRootFactory->CreateGeometricalSet( "", pIPrtPart, spSpecOnGSMTool);
		CATIMmiMechanicalFeature_var spGSMTool = spSpecOnGSMTool;
#endif
        if (SUCCEEDED(rc) && spGSMTool != NULL_var)
        {
          rc = spGSMTool->QueryInterface(IID_CATIGSMTool, (void**) &(*pIGsmTool));
        }
      }
    }
  }

  return rc ;
}

//-----------------------------------------------------------------------------

CATStatusChangeRC CAAV5V6ExtMmrCombCrvPanelStCmd::Activate(CATCommand * iCmd, CATNotification * iNotif)
{
  cout <<" CAAV5V6ExtMmrCombCrvPanelStCmd::Activate" << endl; 

  // Sets the Combined Curve as the current feature 
  // only in edition mode and if the CC is inside an ordered body

  if ((NULL!= iNotif) && (0 == GetMode()) && (NULL !=_piCombinedCurve))
  {
    CATBoolean IsInsideOrderedBody = FALSE ;
    HRESULT rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);
    if (SUCCEEDED(rc) && (TRUE == IsInsideOrderedBody))
    {
      // In case of first activation, SetCombCrvAsCurrentFeature will
      // keep the feature to restore at the end of the command
      
      if (((CATStateActivateNotification *)iNotif)->GetType() ==  CATStateActivateNotification::Begin)
      {              
        // GetCurrentFeature is a method of CATMMUIStateCommand
        _spPreviousCurrentFeat = GetCurrentFeature();
      }

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
      CATIMmiMechanicalFeature * piCombCrv = NULL;      
      rc = _piCombinedCurve->QueryInterface(IID_CATIMmiMechanicalFeature, (void**) &piCombCrv);
#else
//============================================== 
// V5 only
//==============================================
	  CATISpecObject * piCombCrv = NULL ;
      rc = _piCombinedCurve->QueryInterface(IID_CATISpecObject, (void**) &piCombCrv);
#endif
	  if (SUCCEEDED(rc))
      {
        // Sets the CC as current - method of CATMMUIStateCommand
        SetCurrentFeature(piCombCrv);

        piCombCrv->Release();
        piCombCrv = NULL ;
      }
    }
  }
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------
CATStatusChangeRC CAAV5V6ExtMmrCombCrvPanelStCmd::Deactivate(CATCommand * iCmd, CATNotification * iNotif)
{
  cout << " CAAV5V6ExtMmrCombCrvPanelStCmd::Deactivate" << endl; 

  // Restores the old current feature
  // only in edition mode and if the CC is inside an ordered body
  //
  if ( 0 == GetMode() )
    {
       CATBoolean IsInsideOrderedBody = FALSE ;
       HRESULT rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);
       if ( SUCCEEDED(rc) && (TRUE == IsInsideOrderedBody) )
       {
          // method of CATMmrStateCommand
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
          SetCurrentFeature(_spPreviousCurrentFeat);
#else
//============================================== 
// V5 only
//==============================================
		   CATISpecObject_var spSpecObjOnPreviousCurrentFeat=_spPreviousCurrentFeat ;
		   SetCurrentFeature(spSpecObjOnPreviousCurrentFeat);
#endif
       }
    }

    return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------
CATStatusChangeRC CAAV5V6ExtMmrCombCrvPanelStCmd::Cancel(CATCommand * iCmd, CATNotification * iNotif)
{
  cout <<" CAAV5V6ExtMmrCombCrvPanelStCmd::Cancel" << endl; 

  // Check if the CC is inside an ordered body
  CATBoolean IsInsideOrderedBody = FALSE;
  HRESULT rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);

  // Restores the old current feature in edition mode
  // and if the CC is inside an ordered body
  if ((0 == GetMode()) && SUCCEEDED(rc) && (TRUE ==IsInsideOrderedBody))
  {
    // method of CATMMUIStateCommand
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
    SetCurrentFeature(_spPreviousCurrentFeat);     
#else
//============================================== 
// V5 only
//==============================================
    CATISpecObject_var spSpecObjOnPreviousCurrentFeat=_spPreviousCurrentFeat ;
    SetCurrentFeature(spSpecObjOnPreviousCurrentFeat);
#endif
  }

  // Set the newly CC as the current feature in creation mode
  // and if the CC is inside an ordered body
  if ((1 == GetMode()) && SUCCEEDED(rc) && (NULL!=_piCombinedCurve) && (TRUE ==IsInsideOrderedBody)) 
  {
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
    CATIMmiMechanicalFeature *piCombCrv = NULL;
    rc = _piCombinedCurve->QueryInterface(IID_CATIMmiMechanicalFeature, (void**) &piCombCrv);
#else
//============================================== 
// V5 only
//==============================================
	 CATISpecObject *piCombCrv = NULL ;
     rc = _piCombinedCurve->QueryInterface(IID_CATISpecObject, (void**) &piCombCrv);
#endif
    if (SUCCEEDED(rc))
    {
      // Sets the CC as current - method of CATMmrStateCommand
      SetCurrentFeature(piCombCrv);

      piCombCrv->Release();
      piCombCrv = NULL ;
    }
  }

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  return CATMmrPanelStateCmd::Cancel(iCmd,iNotif);
#else
//============================================== 
// V5 only
//==============================================
  return CATMMUIPanelStateCmd::Cancel(iCmd,iNotif);
#endif

}

//-----------------------------------------------------------------------------
HRESULT CAAV5V6ExtMmrCombCrvPanelStCmd::IsCombCrvInsideOrderedBody(CATBoolean & oIsInsideOrderedBody )
{
  // returns TRUE if the Combined Curve is inside an ordered body
  // otherwise FALSE 

  HRESULT rc = E_FAIL ;

  oIsInsideOrderedBody = FALSE ;
    
  if (NULL != _piCombinedCurve)
  {
    // Get credential
    CATUnicodeString ClientId("SAMPLES");
    CATUnicodeString CatalogName("CAAV5V6ExtMmrCombinedCurveCatalog");
    CATFmCredentials CredentialForCC;
    CredentialForCC.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, ClientId); 
		CredentialForCC.RegisterAsCatalogOwner(CatalogName,ClientId);

    // Get feature facade
    CATFmFeatureFacade FeatFacadeOnCurve(CredentialForCC, _piCombinedCurve);

    //Get parent feature
    CATFmAttributeValue AttrAsFmValue;
    rc =  FeatFacadeOnCurve.GetParentFeature(AttrAsFmValue);
    if (SUCCEEDED(rc))
    {
      CATFmFeatureFacade FmFeatFacadeOnParent;
      rc = AttrAsFmValue.GetFeature(FmFeatFacadeOnParent);
  		if (SUCCEEDED(rc))
  		{
        // The father must be a GSMTool or an HybridBody
        CATIGSMTool *piGSMToolFatherCC = NULL;
        rc = FmFeatFacadeOnParent.QueryInterfaceOnFeature(IID_CATIGSMTool, (void**) &piGSMToolFatherCC);
        if (SUCCEEDED(rc))
        {
          // The father can be a ordered or not
          int IsAnOrderedBody = -1 ;
          piGSMToolFatherCC->GetType(IsAnOrderedBody) ;
          if (1 == IsAnOrderedBody)
          {
            oIsInsideOrderedBody = TRUE;
          } 

          piGSMToolFatherCC->Release();
          piGSMToolFatherCC = NULL ;
        }
      }     
    }
  }

  return rc ;

}



