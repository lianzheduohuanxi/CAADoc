// =========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
// =========================================================================
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
// 
// CAAGSMSewSkinBasicCmd
//---------------------------------------------------------------------
// 
//  Sew Skin Basic Command 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//--------------------------------------------------------------------

// MINC 
#include "CATDiaAction.h"
#include "CATDialogState.h"
#include "CATDlgEngUtility.h"
#include "CATDlgNotify.h"
#include "CATDlgUtility.h"
#include "CATDlgWindow.h"
#include "CATMfErrUpdate.h"
#include "CATPathElementAgent.h"
#include "CATSO.h"

#include "CAAGsiServices.h"
#include "CAAGsiServicesBody.h"


// Local  Framework
#include "CAAGSMSewSkinBasicCmd.h"
#include "CAAGSMSewSkinBasicDlg.h"        // needed to create an edition dialog box
#include "CAAGSMSewSkinBasicUINotifications.h"

#include "CAAGSMIntegrationCmdServices.h"


// #include "CAAGSMSewSkinBasicModel.h"	
#include "CAAIGSMFeaturesSplFactory.h"
#include "CAAIGSMSewSkinBasic.h" 


// ApplicationFrame Framework
#include "CATFrmEditor.h"                 // needed to retrieve the editor and then to highight objects
#include "CATApplicationFrame.h"
// Dialog Framework
#include "CATDlgDialog.h"                 // needed to return the dialog box to GiveMyPanel method of
// father class CATMMUiPanelStateCommand

// DialogEngine Framework
#include "CATFeatureImportAgent.h"        // needed to be able to pick any element whatever its context is

// ObjectModelerBase Framework
#include "CATIContainer.h"                // needed to create a GSM tool in case it is necessary

// ObjectSpecsModeler Framework

#include "CATISpecObject.h"               // needed to manage feature

// MechanicalModeler Framework
#include "CATIMechanicalRootFactory.h"    // needed to create a GSM tool in case it is necessary
#include "CATIGSMTool.h"                  // needed to manage GSM tools

// MechanicalModelerUI Framework
#include "CATPrtUpdateCom.h"              // needed to update the feature according to the user's update settings
#include "CATIUpdateError.h"              // needed to update the feature according to the user's update settings

// MecModInterfaces Framework
#include "CATIPrtPart.h"                  // needed to look for a GSM tool
#include "CATIMfBRep.h"                // needed to declare the modes of BRep feature creation
#include "CATMfBRepDefs.h"                // needed to declare the modes of BRep feature creation

//System
#include "CATUnicodeString.h"

// Visualization Framework
#include "CATPathElement.h"               // needed to highlight objects
#include "CATHSO.h"                       // needed to highlight objects
#include "CATIVisProperties.h"            // needed to change Combined Curve's graphical appearance

#include "CATIGSMFactory.h"
#include "CATIGSMUIFactory.h"
#include "CATIGSMProceduralView.h"

#include "CATStateActivateNotification.h"
#include "CATCSO.h"
#include "CATCommandGlobalUndo.h"

#include "CATIRedrawEvent.h"

//GSMInterfaces
#include "CATIGSMAssemble.h"


// #define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 



#define HighlightField1 (ActionMethod)&CAAGSMSewSkinBasicCmd::Highlight_Field1
#define HighlightField2 (ActionMethod)&CAAGSMSewSkinBasicCmd::Highlight_Field2
#define ResetHighlight  (ActionMethod)&CAAGSMSewSkinBasicCmd::Reset_Highlight


// This Command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 


CATCreateClass(CAAGSMSewSkinBasicCmd);



//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : constructor / CmdInfo 
// Deriving from CATMMUIPanelStateCmd provides an association between 
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
CAAGSMSewSkinBasicCmd::CAAGSMSewSkinBasicCmd( ):
CATMMUIPanelStateCmd("SewSkinCommand"),
_pSurfaceToSewAgent        (NULL),
_pSurfaceSupportAgent      (NULL),
_pSurfaceToSewFieldAgent   (NULL),
_pSurfaceSupportFieldAgent (NULL),
_piSpecOnSurfaceToSew      (NULL_var),
_piSpecOnSurfaceSupport    (NULL_var),
_RemoveElement			   (NULL),
_InvertOri				   (NULL),
_piSewSkin                 (NULL),
_panel	                   (NULL),
_editor			           (NULL),
_HSO			           (NULL)
{
    _ActiveField = 0;
    _mode = 1;
    _piSewSkin = NULL ;
    
    SetUndoTitleToTheCmd();
}

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between 
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
CAAGSMSewSkinBasicCmd::CAAGSMSewSkinBasicCmd( CAAIGSMSewSkinBasic *i_piSewSkin):
CATMMUIPanelStateCmd("SewSkinCommand"),
_pSurfaceToSewAgent          (NULL),
_pSurfaceSupportAgent      (NULL),
_pSurfaceToSewFieldAgent    (NULL),
_pSurfaceSupportFieldAgent(NULL),
_piSpecOnSurfaceToSew       (NULL_var),
_piSpecOnSurfaceSupport        (NULL_var),
_RemoveElement					(NULL),
_InvertOri						(NULL),
_piSewSkin      (NULL),
_panel			(NULL),
_editor			(NULL),
_HSO			(NULL)
{
    _ActiveField = 0;
    _mode = 1;
    
    if (i_piSewSkin) {
        _piSewSkin = i_piSewSkin;
        if (NULL != _piSewSkin ) { 
            _piSewSkin->AddRef();
            _mode = 0;
            
        }
    }
    SetUndoTitleToTheCmd();
}

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : destructor
//-----------------------------------------------------------------------------
CAAGSMSewSkinBasicCmd::~CAAGSMSewSkinBasicCmd()
{
    
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::~CAAGSMSewSkinBasicCmd) "  << endl; 
#endif
    _piSewSkin                   = NULL ; 
    _piSpecOnSurfaceToSew        = NULL_var ; 
    _piSpecOnSurfaceSupport      = NULL_var ;  

    if (_piSewSkin ) _piSewSkin -> Release() ; _piSewSkin = NULL ; 

    _pSurfaceToSewAgent          = NULL ;
    _pSurfaceSupportAgent        = NULL ;
    
    _pSurfaceToSewFieldAgent     = NULL ;
    _pSurfaceSupportFieldAgent   = NULL ;
    
    _panel                 = NULL ;
    
    _editor                = NULL ;
    _HSO                   = NULL ;
    _RemoveElement		   = NULL;
    _InvertOri			   = NULL;
    
    
    
}


///////////////////////////
// Launching the Command //
///////////////////////////


//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : CreateStartFeat
//-----------------------------------------------------------------------------

void CAAGSMSewSkinBasicCmd::CreateStartFeat()
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::CreateStartFeat() "  << endl; 
#endif 
    HRESULT rc = S_OK ; 
    
    // Editor 
    // ----------------------------------------------
    _editor = CATFrmEditor::GetCurrentEditor();
    _HSO = NULL ;
    
    if ( NULL != _editor ){	
        _HSO = _editor->GetHSO();
    }
    // Edition mode.
    // ---------------------------------------------------------------
    if ( _mode == 0 ) 
    {
        // Reads the inputs of the SewSkin.
        if (NULL != _piSewSkin ) { 
           rc  = _piSewSkin->GetSurfaceToSew  (_piSpecOnSurfaceToSew );
           rc  = _piSewSkin->GetSurfaceSupport(_piSpecOnSurfaceSupport) ;
         /*   // Manage Contextual Features Visu
            CATISpecObject_var ViewSpec = _piSewSkin;
            if (NULL_var !=  ViewSpec ) { 
                rc = ManageContextualFeatureVisu(ViewSpec,CATShowAttr);
                
                // Manage Input Features Visu
                ChangeInputFeaturesVisu(CATShowAttr);
            }
            */
        }   
    }
    // Creation mode.
    // ---------------------------------------------------------------
    else 
    {
       	CATIContainer_var cont = CAAGsiGetCurrentContainer();
        // CAAIGSMFeaturesSplFactory
        // gets a pointer on CATIMechanicalRootFactory from this feature container
        CAAIGSMFeaturesSplFactory_var pFeaturesSplFactory = cont;
        if ( !!  pFeaturesSplFactory  ) 
        {
            _piSewSkin  = pFeaturesSplFactory  -> CreateSewSkinBasic (_piSpecOnSurfaceToSew   , _piSpecOnSurfaceSupport);
            
        }
        
        if (NULL != _piSewSkin) { 
            
            CATISpecObject_var piSpecOnSew           = _piSewSkin;
            CATIGSMProceduralView_var Obj            = piSpecOnSew; 
            Obj                                      -> InsertInProceduralView() ;
            
        }
        else { 
#ifdef DEBUG_GSD_CAASAMPLE
           cout << "(CAAGSMSewSkinBasicCmd::CreateStartFeat)  FAILED TO CREATE FEATURE "  << endl; 
#endif
        }

    }
    
}




//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : BuildGraph()
//-----------------------------------------------------------------------------
void CAAGSMSewSkinBasicCmd::BuildGraph()
{
    
    
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::BuildGraph) "  << endl; 
#endif     
    // creates the dialog box
    // ---------------------------------------------------------------
    _panel = new CAAGSMSewSkinBasicDlg(this);
    _panel->Build();
    
    
    // Agent _HSO
    _pSurfaceToSewAgent           = new CATFeatureImportAgent ( "SurfaceToSewAgent"     , NULL , NULL , MfNoDuplicateFeature ) ;
    _pSurfaceSupportAgent         = new CATFeatureImportAgent ( "SurfaceSupportAgent"     , NULL , NULL , MfNoDuplicateFeature ) ;
    _pSurfaceToSewFieldAgent      = new CATDialogAgent  ( "SurfaceToSewFieldAgent"    ) ;
    _pSurfaceSupportFieldAgent    = new CATDialogAgent  ( "SurfaceSupportFieldAgent"    ) ;
    _RemoveElement				  = new CATDialogAgent  ( "Clear Selection"          ) ;
    _InvertOri				      = new CATDialogAgent  ( "Invert Orientation"          ) ;
    //-----------------------------------------------------------------------------
    // Selection Agents
    //-----------------------------------------------------------------------------
    
    // _pSurfaceToSewAgent to select a SurfaceToSew
    _pSurfaceToSewAgent -> SetOrderedElementType ( "CATIMfBiDimResult" );
    _pSurfaceToSewAgent -> AddOrderedElementType ( "CATSurface"            );
    _pSurfaceToSewAgent -> AddOrderedElementType ( "CATFace"            );
    _pSurfaceToSewAgent -> AddOrderedElementType ( "CATShell"             );
    _pSurfaceToSewAgent -> SetBehavior      ( CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot         );
    _pSurfaceToSewAgent -> SetAgentBehavior ( MfPermanentBody           | MfLastFeatureSupport | MfRelimitedFeaturization );
    
        _pSurfaceSupportAgent -> SetOrderedElementType ( "CATIMfBiDimResult" );
        _pSurfaceSupportAgent -> AddOrderedElementType ( "CATSurface"         );
        _pSurfaceSupportAgent -> AddOrderedElementType ( "CATFace"            );
        _pSurfaceSupportAgent -> AddOrderedElementType ( "CATShell"             );
    _pSurfaceSupportAgent -> SetBehavior      ( CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot         );
    _pSurfaceSupportAgent -> SetAgentBehavior ( MfPermanentBody           | MfLastFeatureSupport | MfRelimitedFeaturization );
    
    // _pSurfaceToSewFieldAgent and _pSurfaceSupportFieldAgent to change current acquisition type
    _pSurfaceToSewFieldAgent       -> AcceptOnNotify (_panel, CAASurfaceToSewFieldActivate::ClassName() );
    _pSurfaceSupportFieldAgent     -> AcceptOnNotify (_panel, CAASupportFieldActivate::ClassName() );
    
    
    //-----------------------------------------------------------------------------
    // Clear Selection 
    //-----------------------------------------------------------------------------
    _RemoveElement -> AcceptOnNotify(NULL, CAAGSMSewSkinBasicUIRemoveElement::ClassName());
    
    //-----------------------------------------------------------------------------
    // Invert Input Direction
    //-----------------------------------------------------------------------------
    _InvertOri -> AcceptOnNotify(NULL, CAAInvertOrientation::ClassName());
    
    //-----------------------------------------------------------------------------
    // Command States
    //-----------------------------------------------------------------------------
    
    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and Cancel States.
    
    
    // State 1
    CATDialogState *WaitingForSurfToSew= GetInitialPanelState("Select a Surface to sew");
    WaitingForSurfToSew -> AddDialogAgent ( _pSurfaceToSewAgent           ); 
    WaitingForSurfToSew -> AddDialogAgent ( _pSurfaceToSewFieldAgent ); 
    WaitingForSurfToSew -> AddDialogAgent ( _pSurfaceSupportFieldAgent ); 
    WaitingForSurfToSew -> AddDialogAgent ( _RemoveElement ); 
    WaitingForSurfToSew -> AddDialogAgent ( _InvertOri ); 
    // State 2
    CATDialogState *WaitingForSurfSupport = AddPanelState("Select Surface support");
    WaitingForSurfSupport -> AddDialogAgent ( _pSurfaceSupportAgent   ); 
    WaitingForSurfSupport -> AddDialogAgent ( _pSurfaceToSewFieldAgent ); 
    WaitingForSurfSupport -> AddDialogAgent ( _pSurfaceSupportFieldAgent ); 
    WaitingForSurfSupport -> AddDialogAgent ( _RemoveElement );  
    WaitingForSurfSupport -> AddDialogAgent ( _InvertOri ); 

    // Final State
    CATDialogState *FinalState= AddPanelState("Click OK,Cancel or Preview");
    FinalState -> AddDialogAgent ( _pSurfaceToSewFieldAgent ); 
    FinalState -> AddDialogAgent ( _pSurfaceSupportFieldAgent ); 
    FinalState -> AddDialogAgent ( _RemoveElement );  
    FinalState -> AddDialogAgent ( _InvertOri ); 
    //------------------------------------------------------------------------------
    //   Actions : entering/leaving a state // To manage correctly Undo/Redo of highlight
    //------------------------------------------------------------------------------
    
    CATDiaAction * EnterAction1 = Action(HighlightField1);
    if(EnterAction1 ) EnterAction1 -> SetAfterRedoMethod(HighlightField1);
    CATDiaAction * LeaveAction1 = Action(NULL);
    if(LeaveAction1 ) LeaveAction1 -> SetAfterUndoMethod(HighlightField1);
    
    CATDiaAction * EnterAction2 = Action(HighlightField2);
    if(EnterAction2 ) EnterAction2 -> SetAfterRedoMethod(HighlightField2);
    CATDiaAction * LeaveAction2 = Action(NULL);
    if(LeaveAction2 ) LeaveAction2 -> SetAfterUndoMethod(HighlightField2);
    
    CATDiaAction * EnterAction3 = Action(ResetHighlight);
    if(EnterAction3 ) EnterAction3 -> SetAfterRedoMethod(ResetHighlight);
    CATDiaAction * LeaveAction3 = Action(NULL);
    if(LeaveAction3 ) LeaveAction3 -> SetAfterUndoMethod(ResetHighlight);
    
    
    
    WaitingForSurfToSew -> SetEnterAction(EnterAction1);
    WaitingForSurfToSew -> SetLeaveAction(LeaveAction1);
    WaitingForSurfSupport   -> SetEnterAction(EnterAction2);
    WaitingForSurfSupport   -> SetLeaveAction(LeaveAction2);
    
    FinalState   -> SetEnterAction(EnterAction3);
    FinalState   -> SetLeaveAction(LeaveAction3);
    
    
    //------------------------------------------------------------------------------
    //   Actions : Update Model
    //------------------------------------------------------------------------------
    CATDiaAction   * SurfaceToSewSelection  = NULL;
    SurfaceToSewSelection = Action((ActionMethod)&CAAGSMSewSkinBasicCmd::ElementSelected, NULL, NULL, (void *) _pSurfaceToSewAgent);
    if (SurfaceToSewSelection) { 
        SurfaceToSewSelection -> SetAfterUndoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel);
        SurfaceToSewSelection -> SetAfterRedoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel);
    }
    
    CATDiaAction   * SurfaceSupportSelection  = NULL;
    SurfaceSupportSelection = Action((ActionMethod)&CAAGSMSewSkinBasicCmd::ElementSelected, NULL, NULL, (void *) _pSurfaceSupportAgent);
    if (SurfaceSupportSelection) {
        SurfaceSupportSelection -> SetAfterUndoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel);
        SurfaceSupportSelection -> SetAfterRedoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel);
    }
    //------------------------------------------------------------------------------
    //   Actions : UI selection
    //------------------------------------------------------------------------------
    CATDiaAction   * Field1Selection  = NULL;
    Field1Selection = Action(HighlightField1);
    if (Field1Selection){
        Field1Selection -> SetAfterUndoMethod(HighlightField1);
        Field1Selection -> SetAfterRedoMethod(HighlightField1);
    }
    
    CATDiaAction   * Field2Selection  = NULL;
    Field2Selection = Action(HighlightField2);
    if (Field2Selection){
        Field2Selection -> SetAfterUndoMethod(HighlightField2);
        Field2Selection -> SetAfterRedoMethod(HighlightField2);
    }
    //------------------------------------------------------------------------------
    //   Actions : Clear selection
    //------------------------------------------------------------------------------
    CATDiaAction   * ClearSelection  = NULL;
    ClearSelection = Action((ActionMethod)&CAAGSMSewSkinBasicCmd::ClearSelection);
    if (ClearSelection){
        ClearSelection -> SetAfterUndoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::UndoClearSelection);
        ClearSelection -> SetAfterRedoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::ClearSelection);
    }
    //------------------------------------------------------------------------------
    //   Actions : InvertInputOrientation
    //------------------------------------------------------------------------------
    CATDiaAction   * InvertInputOrientation  = NULL;
    InvertInputOrientation = Action((ActionMethod)&CAAGSMSewSkinBasicCmd::InvertInputOrientation);
    if (InvertInputOrientation){
        InvertInputOrientation -> SetAfterUndoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel);
        InvertInputOrientation -> SetAfterRedoMethod((ActionMethod)&CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel);
    }
    
    //-----------------------------------------------------------------------------
    // Transitions
    //-----------------------------------------------------------------------------
    AddTransition ( WaitingForSurfToSew,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceToSewAgent  ) ,SurfaceToSewSelection );
    AddTransition ( WaitingForSurfToSew ,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceSupportFieldAgent ) ,Field2Selection );
    AddTransition ( WaitingForSurfToSew ,WaitingForSurfToSew,IsOutputSetCondition ( _pSurfaceToSewFieldAgent ) ,Field1Selection );
    AddTransition ( WaitingForSurfToSew ,WaitingForSurfToSew,IsOutputSetCondition ( _RemoveElement ) ,ClearSelection );
    AddTransition ( WaitingForSurfToSew ,WaitingForSurfToSew,IsOutputSetCondition ( _InvertOri ) ,InvertInputOrientation );
    
    
    
    AddTransition ( WaitingForSurfSupport,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceSupportFieldAgent  ) ,Field2Selection );
    AddTransition ( WaitingForSurfSupport ,FinalState, IsOutputSetCondition ( _pSurfaceSupportAgent ) ,SurfaceSupportSelection );
    AddTransition ( WaitingForSurfSupport ,WaitingForSurfToSew,IsOutputSetCondition ( _pSurfaceToSewFieldAgent ) ,Field1Selection );
    AddTransition ( WaitingForSurfSupport ,WaitingForSurfSupport,IsOutputSetCondition ( _RemoveElement ) ,ClearSelection );
    AddTransition ( WaitingForSurfSupport ,WaitingForSurfSupport,IsOutputSetCondition ( _InvertOri ) ,InvertInputOrientation );
    
    AddTransition ( FinalState,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceSupportFieldAgent  ) ,Field2Selection );
    AddTransition ( FinalState ,WaitingForSurfToSew,IsOutputSetCondition ( _pSurfaceToSewFieldAgent ) ,Field1Selection );
    AddTransition ( FinalState ,FinalState,IsOutputSetCondition ( _RemoveElement ) ,ClearSelection );
    AddTransition ( FinalState ,FinalState,IsOutputSetCondition ( _InvertOri ) ,InvertInputOrientation );
    
    
    // Created the first Feature;
    CreateStartFeat();    
    
    // Fills in the dialog panel fields.
    UpdatePanelFields();
    
    // Checks whether the OK button can be pressed.
    CheckOKSensitivity();
				
}


////////////////////////////////////////////////////////////////////
// Actions launched with UI notifications received from the panel //
////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd :: Action entering or leaving a State()
//-----------------------------------------------------------------------------

CATBoolean CAAGSMSewSkinBasicCmd::Highlight_Field1(void *)
{ SetActiveField(1); _pSurfaceToSewFieldAgent->InitializeAcquisition(); return TRUE; }

CATBoolean CAAGSMSewSkinBasicCmd::Highlight_Field2(void *)
{ SetActiveField(2); _pSurfaceSupportFieldAgent->InitializeAcquisition(); return TRUE; }

CATBoolean CAAGSMSewSkinBasicCmd::Reset_Highlight(void *)
{ SetActiveField(0); return TRUE; } //Clear Select of Highlighted Field for Final State of the Automat



//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : ClearSelection()
//
//-----------------------------------------------------------------------------
CATBoolean CAAGSMSewSkinBasicCmd::ClearSelection(void * data)
{
    
    int activefield = _ActiveField;
    CATISpecObject * Spec_pSelection  = NULL;
    
    // Unset attributes by sending a NULL pointer
    UpdateDataInModel(Spec_pSelection);
    
    UpdatePanelFields();
    CheckOKSensitivity();
    SetActiveField(activefield);
    
    // gets ready for next acquisition
    _RemoveElement -> InitializeAcquisition();

	return CATTrue;
    
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods used by father command CATMMUIPanelStateCommand or by the dialog Panel to Retrieve data   //
///////////////////////////////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : GiveMyPanel()
//-----------------------------------------------------------------------------
CATDlgDialog* CAAGSMSewSkinBasicCmd::GiveMyPanel()
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::GiveMyPanel) "  << endl; 
#endif 
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (_panel);
}

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd::GiveMyFeature()
//-----------------------------------------------------------------------------
CATISpecObject_var CAAGSMSewSkinBasicCmd::GiveMyFeature()
{
    
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::GiveMyFeature) "  << endl; 
#endif 
    CATISpecObject_var MyFeature(_piSewSkin);
    return MyFeature;
}

int CAAGSMSewSkinBasicCmd::GetActiveField()
{
    return _ActiveField;
}

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : GetMode()
//-----------------------------------------------------------------------------
int CAAGSMSewSkinBasicCmd::GetMode()
{
    // This very simple methods checks if the user is creating or editing the Combined Curve.
    // This data is used by father command CATMMUIPanelStateCommand and by CATPrtUpdateCom.
    // They both provide standard edition command behaviour :
    // for example, it is not possible to create a sick Combined Curve ( a Combined Curve generating an error )
    
    return _mode;  // 0 : edit mode 
    // 1 : creation mode    
}

CATISpecObject_var CAAGSMSewSkinBasicCmd:: GetSurfaceToSew()
{
    return _piSpecOnSurfaceToSew;
}

CATISpecObject_var CAAGSMSewSkinBasicCmd:: GetSurfaceSupport()
{
    return _piSpecOnSurfaceSupport;
}


//////////////////////
// Panel Management //
//////////////////////

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : UpdatePanelFields()
//-----------------------------------------------------------------------------
void CAAGSMSewSkinBasicCmd::UpdatePanelFields()
{
    
    
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::UpdatePanelFields) "  << endl; 
#endif 
    // gets the name of the selected elements and put these names into the Combined Curve edition dialog box relevant text fields
    
    // To Sew
    if ( !!_piSpecOnSurfaceToSew  ) {
        //_panel->SetName(1, _piSpecOnCurve1->GetDisplayName());
        CATBaseUnknown_var IFtrBase (_piSpecOnSurfaceToSew); 
        _panel->SetName(1,  CAAGsiGetSpecDisplayName(IFtrBase));
    }
    else
        _panel->SetName(1, CATUnicodeString("no selection"));
    
    // Support 
    if ( !!_piSpecOnSurfaceSupport){
        // _panel->SetName(2, _piSpecOnDir1->GetDisplayName());
        CATBaseUnknown_var IFtrBase (_piSpecOnSurfaceSupport); 
        _panel->SetName(2,  CAAGsiGetSpecDisplayName(IFtrBase));
    }
    else
        _panel->SetName(2, CATUnicodeString("no selection"));
    
    
    return ;
}


//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : SetActiveField()
//-----------------------------------------------------------------------------
void CAAGSMSewSkinBasicCmd::SetActiveField(int ActiveField)
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::SetActiveField) Field = "  <<ActiveField << endl; 
#endif 
    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    _ActiveField = ActiveField;
    
    // first let's empty current highlighted objects
    if (_HSO) _HSO->Empty();  
    
    
    // Gets a pointer on CATISpecObject on the geometrical element to highlight
    CATISpecObject_var piSpecOnGeomElem = NULL_var;
    if ( 1 == ActiveField ){
        piSpecOnGeomElem = _piSpecOnSurfaceToSew;
    }
    else if ( 2 == ActiveField ){
        piSpecOnGeomElem = _piSpecOnSurfaceSupport;
    }
    
    // Analyse selction 
    if (!! piSpecOnGeomElem )
    {

        CATPathElement* pPathElement = NULL;
        CATTry
        {
            pPathElement = GivePathElementFrom(piSpecOnGeomElem);
            if(NULL != pPathElement)
            {
                if (_HSO) _HSO->AddElement(pPathElement); 

            }
        }
        CATCatch (CATError, Error)
        {
            ErrorPanel("Error", "Error in <CAAGSMSewSkinBasicCmd :: SetActiveField> Unable to create PathElement ", 1 );
            Flush(Error);
        }
        CATEndTry;
        if (pPathElement != NULL) { 
            pPathElement->Release();  pPathElement = NULL ;
        }

    }
    _panel->HighLightCurrentPanelField(ActiveField); // puts the focus on the Active Field in the Combined Curve edition dialog box	
}



//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : CheckOKSensitivity()
//-----------------------------------------------------------------------------
void CAAGSMSewSkinBasicCmd::CheckOKSensitivity()
{
    if ( !!_piSpecOnSurfaceToSew && !!_piSpecOnSurfaceSupport  ){
        _panel->SetOKSensitivity(CATDlgEnable);
        _panel->SetPREVIEWSensitivity(CATDlgEnable);
    }
    else{
        _panel->SetOKSensitivity(CATDlgDisable);
        _panel->SetPREVIEWSensitivity(CATDlgEnable);
    }
    return;
}



/////////////////////////////////////
// Dialog with GSD shared commands //
/////////////////////////////////////




//------------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd::Activate
//------------------------------------------------------------------------------
CATStatusChangeRC CAAGSMSewSkinBasicCmd::Activate (CATCommand *iCmd, CATNotification *iNotif)
{
    //all the following code aims at forcing the selection of the created feature as an input for Combined Curve
    //the feature, created with the contextual menu, has no parents and is in the CSO
    
    if (NULL != iNotif ) {
        
        if (((CATStateActivateNotification*)iNotif)->GetType() == CATStateActivateNotification::Resume)
        {
            
            
            CATDialogState * CurState = GetCurrentState();
            
            //  we find the CATPathElementAgent which is associated to it
            //    Note: in fact, we get the first agent which is a CATPathElementAgent!
            CATCommand * CurAgent = NULL;
            if(CurState) {
                    
                CurState -> InitAgentList();
                while(CurAgent=CurState->GetNextAgent()) {
                    if(CurAgent ->IsAKindOf("CATPathElementAgent")){
                        break; 
                    }
                }
            }
            
            // we do the transfer from the  CSO to the waiting agent
            if(CurAgent) {
                
                CATCSO * CurCSO = GetCSO();
                if(CurCSO) {
                    
                    CATSO* listOfPathInCSO= NULL;
                    int CSOSize = CurCSO -> GetSize();
                    if(CSOSize != 0) {
                        // === Getting the PathElements which are in the CSO ==========
                        // we put all the paths in the list listOfPathInCSO
                        CurCSO -> InitElementList();
                        
                        CATBaseUnknown *hUnknown= NULL;
                        while (hUnknown= CurCSO->NextElement()) { // no addref
                            
                            if (!listOfPathInCSO) listOfPathInCSO= new CATSO(); // you must not free listOfPathInCSO. Warning SO begin with indice 0
                            if(hUnknown->IsAKindOf(CATPathElement::ClassName()))
                                listOfPathInCSO-> AddElement(hUnknown);
                        }
                        
                        // === we value the waiting agent with the content of the CSO ==========
                        CATPathElementAgent * CurPathAgent = (CATPathElementAgent *) CurAgent;
                        if (CurPathAgent) {
                            
                            // (1) we save manually  because the agent valuation done after do not do it
                            CATCommandGlobalUndo * GlobalUndo = new CATCommandGlobalUndo();
                            if(GlobalUndo)
                            {
                                AddLocalUndo(GlobalUndo);
                                GlobalUndo -> Release();
                                GlobalUndo = NULL;
                            }
                            
                            CATDlgEngBehavior Beh = CurPathAgent -> GetBehavior();
                            
                            if(Beh & CATDlgEngMonoAcquisition) {
                                
                                if (listOfPathInCSO) {
                                    
                                    // that is THE line
                                    // we value CurPathAgent with the first element of the list, that means the last created one
                                    CurPathAgent -> SetValue( (CATPathElement *) (*listOfPathInCSO)[0]);
                                }
                            }
                            else if (Beh & CATDlgEngMultiAcquisition) {
                                
                                if (listOfPathInCSO) CurPathAgent -> SetListOfValues(listOfPathInCSO);
                                
                            }
                            
                            
                            CurPathAgent -> SetValuation();
                            
                            // (2) once got, we remove what was taken from the CSO
                            if (listOfPathInCSO) 
							{
								if (CurCSO) 
								{
									for (int index= 0; index<= (listOfPathInCSO->GetSize())-1; index++)	
									{
										CurCSO -> RemoveElement((CATPathElement *) (*listOfPathInCSO)[index], 0);
									}
									CurCSO -> DispatchChange();
                                }
                            }
                            
                            // (3) but we put it candidate for the HSO
                            if (listOfPathInCSO) {
                                
                                CATHSO *HSO = GetHSO();
                                for (int k=0; k<= (listOfPathInCSO->GetSize())-1; k++){				
                                    if (HSO) HSO -> AddElements((CATPathElement *) (*listOfPathInCSO)[k]);
                                }
                                if (HSO) HSO-> EndAddElements();
                            }
                            
                        }
                    }
                    
                    
                    //LST 20/08/02 : MLK
                    if(listOfPathInCSO) {listOfPathInCSO->Release();listOfPathInCSO=NULL;}
                    
                }
            }
            
        }
        else
            EmptySO();
        
   }
   return(CATMMUIPanelStateCmd::Activate(iCmd,iNotif));
   
}




///////////////
// UNDO/REDO //
///////////////


CATBoolean CAAGSMSewSkinBasicCmd::SynchronizeViewWithModel(void* data)
{
    HRESULT rc=S_OK;
    
    CATTry{
        if (_piSewSkin != NULL){ 
             rc=_piSewSkin -> GetSurfaceToSew (_piSpecOnSurfaceToSew);
             rc=_piSewSkin -> GetSurfaceSupport(_piSpecOnSurfaceSupport);
        } 
        
    }
    CATCatch (CATError, Error)  {
        // Error Panel Displayed
        ErrorPanel("Error", "Error in <CAAGSMSewSkinBasicCmd :: SynchronizeViewWithModel()> ", 1 );
    }
    CATEndTry;
    
    UpdatePanelFields();
    CheckOKSensitivity();
    return TRUE;
}




CATBoolean CAAGSMSewSkinBasicCmd::UndoClearSelection(void *)
{ 
    CATBoolean result = SynchronizeViewWithModel(NULL);  SetActiveField(_ActiveField); 
    return TRUE;
} 


///////////////////////////////////////////////////////////
// Actions launched at pushing OK/Preview/Cancel Buttons //
///////////////////////////////////////////////////////////





//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : Ok / Apply / Cancel 
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
CATBoolean CAAGSMSewSkinBasicCmd::PreviewAction(void* iData)
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::Preview) "  << endl; 
#endif 
    CATBoolean returnCode = TRUE;
    
    int result = 0;
    CATTry  {
        
        CATISpecObject_var piSpecOnSew = _piSewSkin; 
        
        CATPrtUpdateCom *pUpdateCommand =  new CATPrtUpdateCom ( piSpecOnSew ,1 ,GetMode());   
        
        CATIUpdateError_var UpdateError = _piSewSkin;
        CATMfErrUpdate *Error=NULL;
        
        Error = UpdateError->GetUpdateError();
        if(Error) result = 1;
        
    }
    
    CATCatch (CATError, Error)  {
        
        // Error Panel Displayed
        ErrorPanel("Error", "Error in <CAAGSMSewSkinBasicCmd :: PreviewAction()> ", 1 );
        
    }
    
    CATEndTry;
    return TRUE;
}


CATBoolean CAAGSMSewSkinBasicCmd::OkAction(void* iData)
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::Ok) "  << endl; 
#endif 
    CATBoolean returnCode = TRUE;
    int result = ComputeBody();	
    returnCode = CATMMUIPanelStateCmd::OkAction(iData);
    return (returnCode);
}


CATBoolean CAAGSMSewSkinBasicCmd::CancelAction(void* iData)
{
    ExecuteUndoAtEnd();	
    CATBoolean   returnCode = CATMMUIPanelStateCmd::CancelAction(iData);
    return (returnCode);
}


CATStatusChangeRC CAAGSMSewSkinBasicCmd::Cancel(CATCommand *iCommand, CATNotification *iNotif)
{
    // Manage Contextual Features Visu
    CATISpecObject_var ViewSpec = _piSewSkin;
    // HRESULT rc = ManageContextualFeatureVisu(ViewSpec,CATNoShowAttr);
    
    // Manage Input Features Visu
    // ChangeInputFeaturesVisu(CATNoShowAttr);
    
    _piSpecOnSurfaceToSew         = NULL_var ; 
    _piSpecOnSurfaceSupport          = NULL_var ;  
    
    if(_panel){       _panel->RequestDelayedDestruction();_panel=NULL;}
    
    _editor                = NULL ;
    if (_HSO)_HSO->Empty() ;
    _HSO = NULL;
    
    if(_editor)        {_editor->Release(); _editor=NULL ;}
    if(_RemoveElement)          {_RemoveElement->Release();   _RemoveElement=NULL   ;}
    if(_InvertOri)          {_InvertOri->Release();   _InvertOri=NULL   ;}
    
    if(_pSurfaceSupportFieldAgent)        {_pSurfaceSupportFieldAgent->Release(); _pSurfaceSupportFieldAgent=NULL ;}
    if(_pSurfaceToSewFieldAgent)          {_pSurfaceToSewFieldAgent->Release();   _pSurfaceToSewFieldAgent=NULL   ;}
    if(_pSurfaceSupportAgent)           {_pSurfaceSupportAgent->Release();    _pSurfaceSupportAgent=NULL    ;}
    if(_pSurfaceToSewAgent)       {_pSurfaceToSewAgent->Release();_pSurfaceToSewAgent=NULL;}
 
    if(_piSewSkin)         {_piSewSkin->Release();_piSewSkin=NULL;}
    
    return(CATMMUIPanelStateCmd::Cancel(iCommand,iNotif));
}




////////////////////////////////////////////////////////////
// Selection of Feature, Update of the Model, Computation //
////////////////////////////////////////////////////////////






//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : ElementSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAGSMSewSkinBasicCmd::ElementSelected(void * Data)
{
    
    // Retrieves Acquisition Agent
    CATFeatureImportAgent *CurrAgent = (CATFeatureImportAgent *) Data; // C-style cast
    if (!CurrAgent) return FALSE;
    
    // translates the selection into the good pointer on a CATBaseUnknwon model element
    CATBaseUnknown *pSelection = CurrAgent->GetElementValue(CurrAgent->GetValue());
    
    // gets ready for next acquisition
    CurrAgent->InitializeAcquisition();
    if (pSelection) {
        
        CATISpecObject * Spec_pSelection  = NULL;
        // gets a pointer on CATISpecObject for this element
        HRESULT rc = pSelection->QueryInterface(IID_CATISpecObject, (void**)&Spec_pSelection);
        if ( FAILED(rc) ) {return FALSE;}
        
        UpdateDataInModel(Spec_pSelection);
        if (Spec_pSelection) {Spec_pSelection->Release(); Spec_pSelection = NULL ;}
    }
    
    return TRUE;
}      



//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : UpdateDataInModel()
//-----------------------------------------------------------------------------
void CAAGSMSewSkinBasicCmd::UpdateDataInModel(CATISpecObject *  & pSelection)
{
    HRESULT rc = S_OK;
    // we replace the old selected element by the new one.
    switch ( _ActiveField )
    {
    case 1 :
        { 
            _piSpecOnSurfaceToSew=NULL_var; 		
            // gets a pointer on CATISpecObject for this element
            _piSpecOnSurfaceToSew = pSelection;
            // Update of the feature Combined Curve
            if (_piSewSkin){
                rc = _piSewSkin -> SetSurfaceToSew (_piSpecOnSurfaceToSew);
                if (FAILED(rc)) return;
            }
            break;
        }
    case 2 :
        {
            _piSpecOnSurfaceSupport = NULL_var; 
            
            _piSpecOnSurfaceSupport = pSelection;
            
            // Update of the feature Combined Curve
            if (_piSewSkin){
                rc = _piSewSkin -> SetSurfaceSupport (_piSpecOnSurfaceSupport);
                if (FAILED(rc)) return;
            }
            break;
        }
        
    }
    
    if (pSelection) {pSelection->Release();pSelection = NULL ;}
    
    // updates the text corresponding to the feature names in the panel fields
    UpdatePanelFields();	
    // ckecks whether the 2 fields are filled in or not :
    CheckOKSensitivity();
    
    return;
    
}       



CATBoolean CAAGSMSewSkinBasicCmd::InvertInputOrientation(void* data)
{
    HRESULT rc = S_OK ; 
    _InvertOri->InitializeAcquisition();
    if(_piSewSkin)	{
        rc =_piSewSkin -> InvertOrientation();
    }
    if ( !!_piSpecOnSurfaceToSew && !!_piSpecOnSurfaceSupport  ){
        CATBoolean Bool = PreviewAction(NULL);
    }
    return TRUE;
}



//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : Compute Body 
//-----------------------------------------------------------------------------

// ***********************************************
// *** Calcul                                  ***
// ***********************************************
int  CAAGSMSewSkinBasicCmd::ComputeBody()
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicCmd::ComputeBody) "  << endl; 
#endif 
    int result = 0;
    
    CATTry  {
        
        UpdatePanelFields();	
        CATISpecObject_var piSpecOnSew = _piSewSkin; 
        //__________________________________________________________________________________
        // Uses CATPrtUpdateCom to update the Combined Curve ( manual update mode )
        // or the whole part ( automatic update mode ).
        // CATPrtUpdateCom also encapsulates interactive error management ( edit / delete, etc...)
        
        // piSpecOnCombinedCurve= the feature to update, translated into part->update in case of automatic update
        // 1= respects update interactive setting ( manual / automatic ) setting
        // GetMode= creation or modification. Prevents the user from creating a feature in error
        //__________________________________________________________________________________
        
        CATPrtUpdateCom *pUpdateCommand =  new CATPrtUpdateCom ( piSpecOnSew ,  
            1                    ,  
            GetMode()       );   
        
        
        CATIUpdateError_var UpdateError = _piSewSkin;
        CATMfErrUpdate *Error=NULL;
        
        Error = UpdateError->GetUpdateError();
        if(Error) result = 1;
        
    }
    
    CATCatch (CATError, Error)  {
        
        // Error Panel Displayed
        ErrorPanel("Error", "Error in <CAAGSMSewSkinBasicCmd :: ComputeBody()> ", 1 );
        
    }
    
    CATEndTry;
    
    return result;
    
    
}








//------------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd::UpdateOKAction()
//------------------------------------------------------------------------------

CATBoolean CAAGSMSewSkinBasicCmd::UpdateOKAction(void*data)
{

	CATIRedrawEvent_var redraw = _piSewSkin;
	if (!!redraw)
	{
		redraw->RedrawParent();
		redraw->Redraw();
	}
	// DatumMode  ? 
	int iCreationMode = GetMode() ; 
	if (iCreationMode ==1 ) { 
		CAAGSMIntegrationCmdServices::ValidateResult(_piSewSkin); 
	}

	return (CATMMUIPanelStateCmd::UpdateOKAction(data));
}


///////////////////
// General tools //
///////////////////

//-----------------------------------------------------------------------------
// CAAGSMSewSkinBasicCmd : ErrorPanel()
// param iType : =1 ErrorMessage
//				 =2 WarningMessage
//				 =3 InformationMessage
//				 default ErrorMsg
//-----------------------------------------------------------------------------
void CAAGSMSewSkinBasicCmd::ErrorPanel(CATUnicodeString Title, CATUnicodeString Text, int iType )
{
    //Recuperation de la fenetre mere
    CATDlgWindow* FatherWindow=(CATApplicationFrame::GetFrame())->GetApplicationDocument();
    
    
    CATDlgStyle Style=CATDlgNfyOK | CATDlgWndModal;
    switch(iType)
	{
		case 1:Style=Style|CATDlgNfyError;break;
		case 2:Style=Style|CATDlgNfyWarning;break;
		case 3:Style=Style|CATDlgNfyInformation;break;
		default:Style=Style|CATDlgNfyError;break;
	}

	//creation du panel
	CATDlgNotify *Panel=new CATDlgNotify(FatherWindow, "ErrorPanel",Style);

	//creation des textes
	int selectedButton = Panel->DisplayBlocked(Text,Title);
	
	if (selectedButton == 1)
	{
		Panel->RequestDelayedDestruction();
		RequestDelayedDestruction();
	}

	FatherWindow=NULL;
	Panel=NULL;
}

void CAAGSMSewSkinBasicCmd::SetUndoTitleToTheCmd()
{
  CATUnicodeString undoTitle = "";
	undoTitle = CATMsgCatalog::BuildMessage("CAAGSMSewSkinBasicCmd", "SewSkinBasicCommand.UndoTitle");
  SetUndoTitle(undoTitle);
}
