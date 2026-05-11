// COPYRIGHT DASSAULT SYSTEMES 2000 

// Local  Framework
#include "CAAMmrCombCrvPanelStCmd.h"
#include "CAAMmrCombinedCurveDlg.h"       // needed to create an edition dialog box

// CAAMechanicalModeler.edu framework
#include "CAAIMmrCombinedCurve.h"         // needed to query the Combined Curve about its inputs ( edition mode )
#include "CAAIMmrCombCrvFactory.h"		  // needed to create a Combined Curve ( creation mode )

// ApplicationFrame Framework
#include "CATFrmEditor.h"                 // needed to retrieve the editor and then to highight objects

// Dialog Framework
#include "CATDlgDialog.h"                 // needed to return the dialog box to GiveMyPanel method of
                                          // father class CATMMUiPanelStateCommand
// DialogEngine Framework
#include "CATFeatureImportAgent.h"        // needed to be able to pick any element whatever its context is
#include "CATStateActivateNotification.h" // to distinguish begin/resume state in the command activation
#include "CATDialogState.h"

// ObjectModelerBase Framework
#include "CATIContainer.h"                // needed to create a GS (Geometrical Set)

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"               // needed to manage feature
#include "CATIDescendants.h"              // needed to aggregate the newly created combined curve

// InteractiveInterfaces
#include "CATIBuildPath.h"                // needed to build a path element to highlight a feature

// MechanicalModeler Framework
#include "CATIMechanicalRootFactory.h"    // needed to create a GS 
#include "CATIGSMTool.h"                  // GSMTool and HybridBody features
#include "CATIBasicTool.h"                // To retrieve the current tool
#include "CATIMmiGeometricalSet.h"        // Only for GSMTool feature
#include "CATIMmiNonOrderedGeometricalSet.h"  // Only for GS feature

// MechanicalModelerUI Framework
#include "CATPrtUpdateCom.h"              // needed to update the feature according to the user's update settings
#include "CATMmrLinearBodyServices.h"     // To insert in ordered and linear body

// MecModInterfaces Framework
#include "CATIPrtPart.h"                  // needed to look for a GSM tool
#include "CATMfBRepDefs.h"                // needed to declare the modes of BRep feature creation
       
// Visualization Framework
#include "CATPathElement.h"               // needed to highlight objects
#include "CATHSO.h"                       // needed to highlight objects    
#include "CATIVisProperties.h"            // needed to change Combined Curve's graphical appearance
#include "CATVisPropertiesValues.h"
#include "iostream.h"       

//System framework
#include "CATGetEnvValue.h"               // To define the type of development
#include "CATBoolean.h"
#include "CATLib.h"

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 
CATCreateClass(CAAMmrCombCrvPanelStCmd);


//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between 
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
CAAMmrCombCrvPanelStCmd::CAAMmrCombCrvPanelStCmd( CAAIMmrCombinedCurve *ipiCombinedCurve):
CATMMUIPanelStateCmd("CombinedCurveCommand"),
_pCurveAgent          (NULL),
_pDirectionAgent      (NULL),
_pCurve1FieldAgent    (NULL),
_pDirection1FieldAgent(NULL),
_pCurve2FieldAgent    (NULL),
_pDirection2FieldAgent(NULL),
_piSpecOnCurve1       (NULL),
_piSpecOnDir1         ( NULL ),
_piSpecOnCurve2       ( NULL ),
_piSpecOnDir2         ( NULL ),
_piCombinedCurve      ( NULL ) ,
_ActiveField          (0)
{
    cout <<"CAAMmrCombCrvPanelStCmd::CAAMmrCombCrvPanelStCmd" << endl;

    _mode = 1; // creation mode

    if ( ipiCombinedCurve != NULL ) 
    {
        // Edition mode.
        _mode = 0;
               
        // Memorises what curve is being edited.
        _piCombinedCurve = ipiCombinedCurve;
        _piCombinedCurve->AddRef();
        
        // Reads the inputs of the Combined Curve.
        HRESULT rc= E_FAIL ;
        
        rc = _piCombinedCurve->GetCurve (1 , &_piSpecOnCurve1 );
        if ( FAILED(rc) ) 
            return ;
        
        rc = _piCombinedCurve->GetDirection ( 1 , &_piSpecOnDir1 );
        if ( FAILED(rc) ) 
            return ;
        
        rc = _piCombinedCurve->GetCurve ( 2 , &_piSpecOnCurve2 );
        if ( FAILED(rc) ) 
            return ;
        
        rc = _piCombinedCurve->GetDirection ( 2 , &_piSpecOnDir2 );
        if ( FAILED(rc) ) 
            return ;
    }
    
    // creates the dialog box
    _panel = new CAAMmrCombinedCurveDlg();

    // builds the dialog box 
    // ! do not call panel->Build from the panel constructor
    _panel->Build();
    
    // To manage the highlight of the Combined Curve and the UI active object that 
    // is used to agregate the Combined Curve at the right place.
    _editor = CATFrmEditor::GetCurrentEditor();
    _HSO = NULL ;
    if ( NULL != _editor )
    {
       _HSO = _editor->GetHSO();
    }
        
    // Fills in the dialog panel fields.
    UpdatePanelFields();

    // Checks whether the OK button can be pressed.
    CheckOKSensitivity();
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : destructor
//-----------------------------------------------------------------------------
CAAMmrCombCrvPanelStCmd::~CAAMmrCombCrvPanelStCmd()
{
    cout <<"CAAMmrCombCrvPanelStCmd::~CAAMmrCombCrvPanelStCmd" << endl;

    // Releases member data pointers before leaving.
    if ( _piCombinedCurve != NULL )
        _piCombinedCurve->Release();
    _piCombinedCurve       = NULL ;
    
    if ( _piSpecOnCurve1 != NULL ) 
        _piSpecOnCurve1->Release();
    _piSpecOnCurve1        = NULL ; 
    
    if ( _piSpecOnDir1 != NULL )  
        _piSpecOnDir1->Release();
    _piSpecOnDir1          = NULL ;  
    
    if ( _piSpecOnCurve2 != NULL ) 
        _piSpecOnCurve2->Release();
    _piSpecOnCurve2        = NULL ; 
    
    if ( _piSpecOnDir2 != NULL ) 
        _piSpecOnDir2->Release();
    _piSpecOnDir2          = NULL ;

    if ( NULL != _pCurveAgent )
    {
       _pCurveAgent->RequestDelayedDestruction();
       _pCurveAgent           = NULL ;
    }

    if ( NULL != _pDirectionAgent )
    {
       _pDirectionAgent->RequestDelayedDestruction();
       _pDirectionAgent       = NULL ;
    }

    if ( NULL != _pCurve1FieldAgent )
    {
       _pCurve1FieldAgent->RequestDelayedDestruction();
       _pCurve1FieldAgent     = NULL ;
    }

    if ( NULL != _pDirection1FieldAgent )
    {
       _pDirection1FieldAgent->RequestDelayedDestruction();
       _pDirection1FieldAgent = NULL ;
    }

    if ( NULL != _pCurve2FieldAgent )
    {
       _pCurve2FieldAgent->RequestDelayedDestruction();
       _pCurve2FieldAgent     = NULL ;
    }

    if ( NULL != _pDirection2FieldAgent )
    {
       _pDirection2FieldAgent->RequestDelayedDestruction();
       _pDirection2FieldAgent = NULL ;
    }

    if ( NULL != _panel )
    { 
       _panel->RequestDelayedDestruction();
       _panel                 = NULL ;
    }

    _editor                = NULL ;
    _HSO                   = NULL ;
}
 
//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : BuildGraph()
//-----------------------------------------------------------------------------
void CAAMmrCombCrvPanelStCmd::BuildGraph()
{
   // Agent Creation 
   _pCurveAgent  = new CATFeatureImportAgent ( "CurveAgent"     , NULL , NULL , MfNoDuplicateFeature ) ;
   _pDirectionAgent =  new CATFeatureImportAgent ( "DirectionAgent" , NULL , NULL , MfNoDuplicateFeature ) ; 
   _pCurve1FieldAgent  = new CATDialogAgent    ( "Curve1ActiveFieldAgent"    ) ;
   _pDirection1FieldAgent= new CATDialogAgent  ( "Direction1ActiveFieldAgent") ;
   _pCurve2FieldAgent    = new CATDialogAgent  ( "Curve2ActiveFieldAgent"    ) ;
   _pDirection2FieldAgent= new CATDialogAgent  ( "Direction2ActiveFieldAgent") ;

    //-----------------------------------------------------------------------------
    // Selection Agents
    //-----------------------------------------------------------------------------
    
    // _pCurveAgent to select a curve
    _pCurveAgent -> SetOrderedElementType ( "CATIMfMonoDimResult" );
    _pCurveAgent -> AddOrderedElementType ( "CATCurve"            );
    _pCurveAgent -> AddOrderedElementType ( "CATEdge"             );
    _pCurveAgent -> AddOrderedElementType ( "CATWire"             );
    _pCurveAgent -> SetBehavior      ( CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot         );
    _pCurveAgent -> SetAgentBehavior ( MfPermanentBody           | MfLastFeatureSupport | MfRelimitedFeaturization );
        
    // _pDirectionAgent to select a direction
    _pDirectionAgent -> SetOrderedElementType ( "CATIMfLine" );
    _pDirectionAgent -> AddOrderedElementType ( "CATLine"    );
    _pDirectionAgent -> SetBehavior      ( CATDlgEngWithPrevaluation | CATDlgEngWithCSO );//|CATDlgEngOneShot);
    _pDirectionAgent -> SetAgentBehavior ( MfPermanentBody           | MfLastFeatureSupport | MfRelimitedFeaturization );

    // Setting an ID to be able to read the created import
    GUID guid =  { /* c17e43d3-2b56-4753-bfe5-bb5f289e2091 */
    0xc17e43d3,
    0x2b56,
    0x4753,
    {0xbf, 0xe5, 0xbb, 0x5f, 0x28, 0x9e, 0x20, 0x91}
     };

    _pDirectionAgent->SetImportApplicativeId(guid);
    
    // _pCurveFieldAgent and _pDirectionFieldAgent to change current acquisition type
    _pCurve1FieldAgent     -> AcceptOnNotify ( _panel->GetField(1) , _panel->GetField(1)->GetListSelectNotification() );
    _pCurve2FieldAgent     -> AcceptOnNotify ( _panel->GetField(3) , _panel->GetField(3)->GetListSelectNotification() );
    _pDirection1FieldAgent -> AcceptOnNotify ( _panel->GetField(2) , _panel->GetField(2)->GetListSelectNotification() );
    _pDirection2FieldAgent -> AcceptOnNotify ( _panel->GetField(4) , _panel->GetField(4)->GetListSelectNotification() );

    //-----------------------------------------------------------------------------
    // Command States
    //-----------------------------------------------------------------------------

    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and Cancel States.

    // Curve selection state
    CATDialogState *WaitForCurveState= GetInitialPanelState("Select a curve or another input field");
    WaitForCurveState -> AddDialogAgent ( _pCurveAgent           ); 
    WaitForCurveState -> AddDialogAgent ( _pDirection1FieldAgent ); 
    WaitForCurveState -> AddDialogAgent ( _pDirection2FieldAgent ); 
    WaitForCurveState -> AddDialogAgent ( _pCurve1FieldAgent     ); 
    WaitForCurveState -> AddDialogAgent ( _pCurve2FieldAgent     ); 

    // Direction selection state
    CATDialogState *WaitForDirectionState= AddPanelState("Select a direction or another input field");
    WaitForDirectionState -> AddDialogAgent ( _pDirectionAgent       );
    WaitForDirectionState -> AddDialogAgent ( _pCurve1FieldAgent     );
    WaitForDirectionState -> AddDialogAgent ( _pCurve2FieldAgent     );
    WaitForDirectionState -> AddDialogAgent ( _pDirection1FieldAgent ); 
    WaitForDirectionState -> AddDialogAgent ( _pDirection2FieldAgent ); 

    //-----------------------------------------------------------------------------
    // Transitions
    //-----------------------------------------------------------------------------

    // From Curve to Curve ( click on several curves to change of curve )
    AddTransition ( WaitForCurveState , WaitForCurveState , 
                    IsOutputSetCondition ( _pCurveAgent ) ,
                    Action ( ( ActionMethod ) &CAAMmrCombCrvPanelStCmd::CurveSelected ) );   

    AddTransition ( WaitForCurveState , WaitForCurveState , 
                    IsOutputSetCondition ( _pCurve1FieldAgent ) ,
                    Action ( ( ActionMethod ) &CAAMmrCombCrvPanelStCmd::Curve1FieldSelected ) );   

    AddTransition ( WaitForCurveState , WaitForCurveState , 
                    IsOutputSetCondition ( _pCurve2FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Curve2FieldSelected ) );   

    // From Curve to Direction
    AddTransition ( WaitForCurveState , WaitForDirectionState , 
                    IsOutputSetCondition ( _pDirection1FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Direction1FieldSelected ) );   
    
    AddTransition ( WaitForCurveState , WaitForDirectionState , 
                    IsOutputSetCondition ( _pDirection2FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Direction2FieldSelected ) );   
        
    // From Direction to Direction  ( click on several directions to change of curve )
    AddTransition ( WaitForDirectionState , WaitForDirectionState , 
                    IsOutputSetCondition ( _pDirectionAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::DirectionSelected ) );   

    AddTransition ( WaitForDirectionState , WaitForDirectionState , 
                    IsOutputSetCondition ( _pDirection1FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Direction1FieldSelected ) );   

    AddTransition ( WaitForDirectionState , WaitForDirectionState , 
                    IsOutputSetCondition ( _pDirection2FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Direction2FieldSelected ) );   

    // From Direction to Curve 
    AddTransition ( WaitForDirectionState , WaitForCurveState , 
                    IsOutputSetCondition ( _pCurve1FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Curve1FieldSelected ) );   
    
    AddTransition ( WaitForDirectionState , WaitForCurveState , 
                    IsOutputSetCondition ( _pCurve2FieldAgent ) ,
                    Action ( (ActionMethod )& CAAMmrCombCrvPanelStCmd::Curve2FieldSelected ) );   

}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : GiveMyPanel()
//-----------------------------------------------------------------------------
CATDlgDialog* CAAMmrCombCrvPanelStCmd::GiveMyPanel()
{
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (_panel);
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : CancelAction()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::CancelAction(void *)
{
    // Unset Repeat mode  when cancel or close is clicked 
    if (_editor) _editor -> UnsetRepeatedCommand();
    return TRUE ; 
} 

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : OkAction()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::OkAction(void *)
{  
    HRESULT rc = E_FAIL;

    // EDS 4/7/2005 (RI 492591): Vider les SO en sortie de commande
    EmptySO();

    //
    // 0- Modifies or creates the CC 
    //
    if ( 0 == GetMode() && (NULL !=_piCombinedCurve) )
    {
        // Updates the combine with its new curves inputs.
        rc = _piCombinedCurve -> SetCurve     ( 1 , _piSpecOnCurve1 );
        if ( FAILED(rc) ) 
            return FALSE;
        
        rc = _piCombinedCurve -> SetDirection ( 1 , _piSpecOnDir1   );
        if ( FAILED(rc) ) 
            return FALSE;
        
        rc = _piCombinedCurve -> SetCurve     ( 2 , _piSpecOnCurve2 );
        if ( FAILED(rc) ) 
            return FALSE;
        
        rc = _piCombinedCurve -> SetDirection ( 2 , _piSpecOnDir2   );
        if ( FAILED(rc) ) 
            return FALSE;

    }
    else
    {
        rc = CreateCombinedCurve();        
    }
    
    //
    // 1- Queries the CATISpecObject interface to update the Combined Curve
    //
    CATISpecObject *piSpecOnCombinedCurve = NULL;

    if ( SUCCEEDED(rc) && (NULL != _piCombinedCurve) )
    {
       rc = _piCombinedCurve->QueryInterface( IID_CATISpecObject , (void**) &piSpecOnCombinedCurve );
    }

    //
    // 2- Updates
    //
    if ( SUCCEEDED(rc) && (NULL != piSpecOnCombinedCurve ) )
    {
       // Uses CATPrtUpdateCom to update the Combined Curve ( manual update mode )
       // or the whole part ( automatic update mode ).
       // CATPrtUpdateCom also encapsulates interactive error management ( edit / delete, etc...)
    
       // piSpecOnCombinedCurve= the feature to update, translated into part->update 
        // in case of automatic update
       // 1= respects update interactive setting ( manual / automatic ) setting
       // GetMode= creation or modification. Prevents the user from creating a feature in error
       //
       CATPrtUpdateCom *pUpdateCommand =  new CATPrtUpdateCom ( piSpecOnCombinedCurve ,  
                                                             1                    ,  
                                                             GetMode()            ); 
    }
                         
    //
    // 3- Inserts if necessary ( if inside an ordered (and linear) body )
    //
    if (SUCCEEDED(rc) && (NULL != piSpecOnCombinedCurve ) )
    {
       CATBoolean IsInsideOrderedBody = FALSE ;
       rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);
       if ( SUCCEEDED(rc) && (TRUE == IsInsideOrderedBody) )
       {
          // Invoke the Insert method is mandatory
          // 
          CATBaseUnknown_var spBUOnCC = piSpecOnCombinedCurve ;
          rc = CATMmrLinearBodyServices::Insert(spBUOnCC);
       }
    }

    //
    // 4- Let's give our Combined Curve a better appearance
    //
    if ( SUCCEEDED(rc) && (1 == GetMode()) && (NULL != piSpecOnCombinedCurve ))
    {
       CATIVisProperties *piGraphPropOnCombinedCurve = NULL;
       rc = piSpecOnCombinedCurve->QueryInterface( IID_CATIVisProperties, 
                                                        (void**)& piGraphPropOnCombinedCurve);
       if ( SUCCEEDED(rc) ) 
       {
           CATVisPropertiesValues Attribut;
           Attribut.SetColor(255, 255, 0); // yellow
           Attribut.SetWidth(4);           // medium thickness
           piGraphPropOnCombinedCurve->SetPropertiesAtt(Attribut, CATVPAllPropertyType, CATVPLine);

           piGraphPropOnCombinedCurve->Release();
           piGraphPropOnCombinedCurve = NULL ;
       }
    }

    if ( NULL != piSpecOnCombinedCurve )
    {
       piSpecOnCombinedCurve->Release(); 
       piSpecOnCombinedCurve = NULL ;
    }

    if ( SUCCEEDED(rc) )
       return TRUE;
    else
       return FALSE;
}



//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd::GiveMyFeature()
//-----------------------------------------------------------------------------
CATISpecObject_var CAAMmrCombCrvPanelStCmd::GiveMyFeature()
{
    CATISpecObject_var MyFeature(_piCombinedCurve);
    return MyFeature;
}



//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : CurveSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::CurveSelected(void*)
{

    // checks if the selected object must be added ( not  selected yet ) or removed ( already selected ) as input curve
    ElementSelected(_pCurveAgent);  
    
    // gets ready for next acquisition
    _pCurveAgent->InitializeAcquisition();
    
    return TRUE;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : DirectionSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::DirectionSelected(void*)
{
    // checks if the selected object must be added ( not  selected yet ) or removed ( already selected ) as input direction
    ElementSelected(_pDirectionAgent);  

    // gets ready for next acquisition
    _pDirectionAgent->InitializeAcquisition();
    
    return TRUE;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : Curve1FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::Curve1FieldSelected(void*)
{
    // put the focus on the first field of the Combined Curve edition dialog box 
    // ( first curve ) and highlight the corresponding geometrical element 
    SetActiveField(1);
    
    // gets ready for next acquisition
    _pCurve1FieldAgent->InitializeAcquisition();
    
    return TRUE;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : Direction1FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::Direction1FieldSelected(void*)
{
    // put the focus on the second field of the Combined Curve edition dialog box
    // ( first direction ) and highlight the corresponding geometrical element 
    SetActiveField(2);
    
    // gets ready for next acquisition
    _pDirection1FieldAgent->InitializeAcquisition();
    
    return TRUE;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : Curve2FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::Curve2FieldSelected(void*)
{

    // put the focus on the third field of the Combined Curve edition dialog box
    // ( second curve ) and highlight the corresponding geometrical element 
    SetActiveField(3);
    
    // gets ready for next acquisition
    _pCurve2FieldAgent->InitializeAcquisition();
    
    return TRUE;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : Direction2FieldSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAMmrCombCrvPanelStCmd::Direction2FieldSelected(void*)
{
    // put the focus on the fourth field of the Combined Curve edition dialog box
    // ( second direction ) and highlight the corresponding geometrical element 
    SetActiveField(4);
    
    // gets ready for next acquisition
    _pDirection2FieldAgent->InitializeAcquisition();
    
    return TRUE;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : SetActiveField()
//-----------------------------------------------------------------------------
void CAAMmrCombCrvPanelStCmd::SetActiveField(int ActiveField)
{

    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    _ActiveField = ActiveField;
    
    // first let's empty current highlighted objects
    if ( NULL != _HSO )
    {
       _HSO->Empty(); 
    }
    
    
    // Gets a pointer on CATISpecObject on the geometrical element to highlight
    CATISpecObject *piSpecOnGeomElem = NULL;
    if ( 1 == ActiveField )
        piSpecOnGeomElem = _piSpecOnCurve1;
    if ( 2 == ActiveField )
        piSpecOnGeomElem = _piSpecOnDir1;
    if ( 3 == ActiveField )
        piSpecOnGeomElem = _piSpecOnCurve2;
    if ( 4 == ActiveField )
        piSpecOnGeomElem = _piSpecOnDir2;


    if ( (piSpecOnGeomElem != NULL) && (NULL != _HSO) && (NULL !=_editor) )
    {
        // uses this pointer to build a path element
        CATIBuildPath *piBuildPath = NULL;
        HRESULT rc = piSpecOnGeomElem->QueryInterface( IID_CATIBuildPath, 
                                                       (void**) &piBuildPath );
        if ( SUCCEEDED(rc) )
        {
            CATPathElement Context = _editor->GetUIActiveObject();
            CATPathElement *pPathElement = NULL ;
            rc = piBuildPath->ExtractPathElement(&Context,&pPathElement);

            if (pPathElement != NULL)
            {   // the geometrical element corresponding to the active field is now highlighted
               _HSO->AddElement(pPathElement); 
                
                pPathElement->Release();
                pPathElement = NULL ;
            }
            
            piBuildPath->Release(); 
            piBuildPath = NULL ;
        }
    }
    
    _panel->SetActiveField(ActiveField); // puts the focus on the Active Field is the Combined Curve edition dialog box

}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : ElementSelected()
//-----------------------------------------------------------------------------
void CAAMmrCombCrvPanelStCmd::ElementSelected(CATFeatureImportAgent *pAgent)
{
    cout <<" CAAMmrCombCrvPanelStCmd::ElementSelected" << _ActiveField << endl;

    if ( (pAgent == NULL) || (_ActiveField == 0) )
        return;
    
    // translates the selection into the good pointer on a CATBaseUnknwon model element
    CATBaseUnknown *pSelection = pAgent->GetElementValue(pAgent->GetValue());
    
    if ( NULL != pSelection )
    {
       // gets a pointer on CATISpecObject for this element
       CATISpecObject *piSpecOnSelection = NULL;
       HRESULT rc = pSelection->QueryInterface(IID_CATISpecObject, (void**)&piSpecOnSelection);
       if ( FAILED(rc) ) 
       {
           return;
       }
       
       // checks whether the selected element is the same than the one "in" the active field
       // o if this element is the same, the user wants to erase his selection.
       // o otherwise, the user wants to replace the old selected element by the new one.
       switch ( _ActiveField )
       {
       case 1 :
           { 
               if ( _piSpecOnCurve1 == piSpecOnSelection) // same one
               {
                   _piSpecOnCurve1->Release() ;// this pointeur is not null 
                   _piSpecOnCurve1 = NULL ; // erases the selection
               }                
               else
               {
                   if ( NULL != _piSpecOnCurve1) _piSpecOnCurve1->Release() ; 
                   _piSpecOnCurve1 = piSpecOnSelection; // other one, replaces the selection
                   _piSpecOnCurve1->AddRef() ;
               }                
               
               break;
           }
       case 2 :
           { 
               if ( _piSpecOnDir1 == piSpecOnSelection) 
               {
                   _piSpecOnDir1->Release() ;// this pointeur is not null 
                   _piSpecOnDir1 = NULL ;
               }
               else
               {
                   if ( NULL != _piSpecOnDir1) _piSpecOnDir1->Release() ; 
                   _piSpecOnDir1 = piSpecOnSelection;
                   _piSpecOnDir1->AddRef();
               }
               break;
           }
       case 3 :
           { 
               if ( _piSpecOnCurve2 == piSpecOnSelection) 
               {
                   _piSpecOnCurve2->Release();            
                   _piSpecOnCurve2 = NULL ;
               }
               else
               {
                   if ( NULL != _piSpecOnCurve2) _piSpecOnCurve2->Release() ; 
                   _piSpecOnCurve2 = piSpecOnSelection;
                   _piSpecOnCurve2->AddRef();
               }
               break;
           }
       case 4 :
           { 
               if ( _piSpecOnDir2 == piSpecOnSelection) 
               {
                   _piSpecOnDir2->Release();
                   _piSpecOnDir2 = NULL ;
               }
               else
               {
                   if ( NULL != _piSpecOnDir2) _piSpecOnDir2->Release() ; 
                   _piSpecOnDir2 = piSpecOnSelection;
                   _piSpecOnDir2->AddRef();
               }
               break;
           }
       }
       
       piSpecOnSelection->Release();
       piSpecOnSelection = NULL ;

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
// CAAMmrCombCrvPanelStCmd : CheckOKSensitivity()
//-----------------------------------------------------------------------------
void CAAMmrCombCrvPanelStCmd::CheckOKSensitivity()
{
    if ( _piSpecOnCurve1 != NULL && _piSpecOnDir1 != NULL && _piSpecOnCurve2 != NULL && _piSpecOnDir2 != NULL )
        _panel->SetOKSensitivity(CATDlgEnable);
    else
        _panel->SetOKSensitivity(CATDlgDisable);

    return;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : UpdatePanelFields()
//-----------------------------------------------------------------------------
void CAAMmrCombCrvPanelStCmd::UpdatePanelFields()
{
    // gets the name of the selected elements and put these names into the Combined Curve edition dialog box relevant text fields

    if ( _piSpecOnCurve1 != NULL )
        _panel->SetName(1, _piSpecOnCurve1->GetDisplayName());
    else
        _panel->SetName(1, CATUnicodeString("no selection"));
    
    if ( _piSpecOnDir1 != NULL )
        _panel->SetName(2, _piSpecOnDir1->GetDisplayName());
    else
        _panel->SetName(2, CATUnicodeString("no selection"));

    if ( _piSpecOnCurve2 != NULL )
        _panel->SetName(3, _piSpecOnCurve2->GetDisplayName());
    else
        _panel->SetName(3, CATUnicodeString("no selection"));

    if ( _piSpecOnDir2 != NULL )
        _panel->SetName(4, _piSpecOnDir2->GetDisplayName());
    else
        _panel->SetName(4, CATUnicodeString("no selection"));

    return ;
}

//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : GetMode()
//-----------------------------------------------------------------------------
int CAAMmrCombCrvPanelStCmd::GetMode()
{
    // This very simple methods checks if the user is creating or editing the Combined Curve.
    // This data is used by father command CATMMUIPanelStateCommand and by CATPrtUpdateCom.
    // They both provide standard edition command behaviour :
    // for example, it is not possible to create a sick Combined Curve ( a Combined Curve generating an error )

    return _mode;  // 0 : edit mode 
                   // 1 : creation mode    
}

//-----------------------------------------------------------------------------

HRESULT CAAMmrCombCrvPanelStCmd::CreateCombinedCurve()
{
    cout <<" CAAMmrCombCrvPanelStCmd::CreateCombinedCurve" << endl;

    HRESULT rc = E_FAIL ;

    //
    // 1- Looking for a body to create the Combined Curve
    //    
    // 

    // CATIGSMTool is implemented by the HybridBody and GSMTool StartUp
    // it is a valid pointer to handle the body which will contain the new
    // Combined Curve
    //
    CATIGSMTool * piGSMTool = NULL ;

    char * pCombCrvOGS = NULL ;
    CATLibStatus result = ::CATGetEnvValue("CAAMmrCombCrvOGS",&pCombCrvOGS);  
    if ( (CATLibError == result) || ( NULL == pCombCrvOGS) )
    {
        char * pCombCrvNoHybridBody = NULL ;
        result = ::CATGetEnvValue("CAAMmrCombCrvNoHybridBody",&pCombCrvNoHybridBody); 
        if ( (CATLibError == result) || ( NULL == pCombCrvNoHybridBody) )
        {
           // Looking for or creating only a Geometrical Set
           // The result cannot be an ordered geometrical set or an hybrid body
           // 
           rc = LookingForGeomSet(&piGSMTool);
        }else
        {
           free (pCombCrvNoHybridBody) ;
           pCombCrvNoHybridBody = NULL ;

           // Looking for an OGS or a GS, or creating a Geometrical Set
           // The result cannot be an hybrid body
           //
           rc = LookingForGeomSetOrOrderedGeomSet(&piGSMTool);   
        }
    }else
    {
       free (pCombCrvOGS) ;
       pCombCrvOGS = NULL ;

       // Looking for any type of mechanical bodies, or creating a Geometrical Set
       // The result cannot be a former solid body
       //
       rc = LookingForAnyTypeOfBody(&piGSMTool);       
    }

    //
    // 2- Creating the Combined Curve
    // 
    CATISpecObject * piSpecOnCombinedCurve = NULL ;

    if ( SUCCEEDED(rc) && ( NULL != piGSMTool) )
    {   
       // 
       // Uses CAAIMmrCombCrvFactory implemented by CATPrtCont
       // 
       CATISpecObject_var piSpecObjOnTool = piGSMTool ;
       if ( NULL_var != piSpecObjOnTool )
       {
          // GetFeatContainer for a mechanical feature
          // is CATPrtCont, the specification container
          CATIContainer_var spContainer = piSpecObjOnTool->GetFeatContainer();  

          if ( NULL_var != spContainer )
          {
             CAAIMmrCombCrvFactory *piCombinedCurveFactory = NULL;
             rc = spContainer->QueryInterface( IID_CAAIMmrCombCrvFactory , 
                                                    (void**)& piCombinedCurveFactory );
             if ( SUCCEEDED(rc) )
             {
                // creates the Combined Curve
                
                rc = piCombinedCurveFactory -> CreateCombinedCurve ( _piSpecOnCurve1       ,
                                                               _piSpecOnDir1         ,
                                                               _piSpecOnCurve2       ,
                                                               _piSpecOnDir2         ,
                                                               &piSpecOnCombinedCurve );

            
                if ( SUCCEEDED(rc) )
                {
                   rc = piSpecOnCombinedCurve->QueryInterface( IID_CAAIMmrCombinedCurve , 
                                                        (void**) &_piCombinedCurve );
        
                }

                piCombinedCurveFactory->Release();
                piCombinedCurveFactory = NULL ;
             }
          }else rc = E_FAIL ;
        }else rc = E_FAIL ;
     }

     //
     // 3- Aggregating the newly Combined Curve in the Geometrical Set
     // 
     if ( SUCCEEDED(rc) && (NULL != piGSMTool) && (NULL !=piSpecOnCombinedCurve) )
     {
         CATIDescendants * pIDescendantsOnGSMTool = NULL ;
         rc = piGSMTool->QueryInterface(IID_CATIDescendants, (void**) & pIDescendantsOnGSMTool);
         if ( SUCCEEDED(rc) )
         {
            // Checks the type of the GSMTool
            // 
            int TypeOrderedBody = -1 ;
            piGSMTool->GetType(TypeOrderedBody);

            if ( 1 == TypeOrderedBody )
            {  // OGS/HB : the CC is set after the current feature or at the end
               //       of the set, if the current feature is the set itself
               //
               cout <<" Ordered and linear body " << endl;
               int pos = 0 ;
               CATISpecObject_var CurrentElt = GetCurrentFeature() ;
               if ( NULL_var != CurrentElt)
               {
                   pos = pIDescendantsOnGSMTool->GetPosition(CurrentElt);                   
               }

               if ( 0 == pos )
               {
                  // The current feature is the GSMTool itself
                  // the CC is appended at the end
                  pIDescendantsOnGSMTool->Append(piSpecOnCombinedCurve);
               }else
               {
                  // the current feature is inside the GSMTool
                  // the CC is appended just below it (which can be at the end)
                  pIDescendantsOnGSMTool->AddChild(piSpecOnCombinedCurve,pos+1);
               }
            }else
            {  // GS : the CC is set at the end of the set
               cout <<" GS case " << endl;
               pIDescendantsOnGSMTool->Append(piSpecOnCombinedCurve);
            }

            pIDescendantsOnGSMTool->Release();
            pIDescendantsOnGSMTool = NULL ;
         }
     }

    if ( NULL != piGSMTool )
    {
         piGSMTool->Release();
         piGSMTool = NULL ;
    }

    if ( NULL != piSpecOnCombinedCurve )
    {
         piSpecOnCombinedCurve->Release();
         piSpecOnCombinedCurve = NULL ;
    }

    return rc ;
}

//-----------------------------------------------------------------------------

HRESULT CAAMmrCombCrvPanelStCmd::LookingForGeomSet(CATIGSMTool ** piGsmtool)
{
    if ( (NULL == piGsmtool) || (NULL ==_editor) ) return E_FAIL ;

    HRESULT rc= E_FAIL ;

    *piGsmtool = NULL ;

    // Retrieves the Part feature which holds the current tool
    // 
    CATIPrtPart * pIPrtPart = NULL ;
    CATPathElement PathAct = _editor->GetUIActiveObject();
    rc = PathAct.Search(IID_CATIPrtPart,(void**)&pIPrtPart) ;

    if ( SUCCEEDED(rc) && ( NULL!=pIPrtPart) )
    {
       CATBoolean ToolToCreate = TRUE ;

       CATIBasicTool_var CurrentTool ;
       CurrentTool = pIPrtPart->GetCurrentTool() ;

       if ( NULL_var != CurrentTool )
       {
          // is it a GS ?
          CATIMmiNonOrderedGeometricalSet * pIGSOnCurrentTool = NULL ;
          rc = CurrentTool->QueryInterface(IID_CATIMmiNonOrderedGeometricalSet, 
                                            (void**) &pIGSOnCurrentTool);
          if ( SUCCEEDED(rc) )
          {
             // Ok we have found a valid geometrical set
             ToolToCreate = FALSE ;

             rc = pIGSOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**) piGsmtool);

             pIGSOnCurrentTool->Release();
             pIGSOnCurrentTool = NULL ;
                  
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

HRESULT CAAMmrCombCrvPanelStCmd::LookingForGeomSetOrOrderedGeomSet(CATIGSMTool ** piGsmtool)
{
   if ( (NULL == piGsmtool) || (NULL ==_editor) ) return E_FAIL ;

   HRESULT rc= E_FAIL ;

   *piGsmtool = NULL ;

   CATIPrtPart * pIPrtPart = NULL ;
   CATPathElement PathAct = _editor->GetUIActiveObject();
    
   rc = PathAct.Search(IID_CATIPrtPart,(void**)&pIPrtPart)  ;

   if ( SUCCEEDED(rc) && ( NULL!=pIPrtPart) )
   {
       CATBoolean ToolToCreate = TRUE ;  

       CATIBasicTool_var CurrentTool ;
       CurrentTool = pIPrtPart->GetCurrentTool() ;

       if ( NULL_var != CurrentTool )
       {
          // is it a GSMTool ?
          CATIMmiGeometricalSet * pIGSMToolOnCurrentTool = NULL ;
          rc = CurrentTool->QueryInterface(IID_CATIMmiGeometricalSet, (void**) &pIGSMToolOnCurrentTool);
          if ( SUCCEEDED(rc) )
          {
              // Ok we have found a valid geometrical set ( ordered or not )
              ToolToCreate = FALSE ;

              rc = pIGSMToolOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**) piGsmtool);

              pIGSMToolOnCurrentTool->Release();
              pIGSMToolOnCurrentTool = NULL ;
          }
       }

       if ( (TRUE == ToolToCreate) )
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

HRESULT CAAMmrCombCrvPanelStCmd::LookingForAnyTypeOfBody(CATIGSMTool ** piGsmtool)
{
   if ( (NULL == piGsmtool) || (NULL ==_editor) ) return E_FAIL ;

   HRESULT rc= E_FAIL ;

   *piGsmtool = NULL ;

   CATIPrtPart * pIPrtPart = NULL ;
   CATPathElement PathAct = _editor->GetUIActiveObject();
    
   rc = PathAct.Search(IID_CATIPrtPart,(void**)&pIPrtPart)  ;

   if ( SUCCEEDED(rc) && ( NULL!=pIPrtPart) )
   {
       CATBoolean ToolToCreate = TRUE ;  

       CATIBasicTool_var CurrentTool ;
       CurrentTool = pIPrtPart->GetCurrentTool() ;

       if ( NULL_var != CurrentTool )
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

HRESULT CAAMmrCombCrvPanelStCmd::CreateTool(CATIPrtPart * pIPrtPart, CATIGSMTool ** pIGsmTool)
{
    if ( ( pIGsmTool == NULL) || ( NULL == pIPrtPart ) )
    {
        return E_FAIL ;
    }

    *pIGsmTool  = NULL ;

    HRESULT rc = E_FAIL ;

    CATISpecObject * pISpecOnPart = NULL ;
    rc = pIPrtPart->QueryInterface(IID_CATISpecObject,(void**) &pISpecOnPart) ;
    if ( SUCCEEDED(rc) )
    {
        
       // GetFeatContainer for a mechanical feature
       // is CATPrtCont, the specification container
       CATIContainer_var spContainer = pISpecOnPart->GetFeatContainer();  
       if ( NULL_var != spContainer )
       {
          // 
          CATIMechanicalRootFactory * pMechanicalRootFactory = NULL;
          rc = spContainer->QueryInterface( IID_CATIMechanicalRootFactory , 
                                           ( void**)& pMechanicalRootFactory );
          if ( SUCCEEDED(rc) )
          {
              // creates a new GS aggregated by the Part feature
              CATISpecObject_var spiSpecOnGSMTool;
              rc = pMechanicalRootFactory->CreateGeometricalSet( "" , pIPrtPart,spiSpecOnGSMTool);

              pMechanicalRootFactory->Release();
              pMechanicalRootFactory = NULL ;

              if ( NULL_var != spiSpecOnGSMTool )
              {
                  spiSpecOnGSMTool->QueryInterface(IID_CATIGSMTool, (void**) &(*pIGsmTool));
              }
          }
       }

       pISpecOnPart->Release();
       pISpecOnPart = NULL ;

    }

    return rc ;
}

//-----------------------------------------------------------------------------

CATStatusChangeRC CAAMmrCombCrvPanelStCmd::Activate (CATCommand * iCmd,
                                                     CATNotification * iNotif)
{
    cout <<" CAAMmrCombCrvPanelStCmd::Activate" << endl; 

    // Sets the CC as the current feature 
    // only in edition mode and if the CC is inside an ordered body
    //
    if ( (NULL!= iNotif) && (0 == GetMode()) && (NULL !=_piCombinedCurve) )
    {
       CATBoolean IsInsideOrderedBody = FALSE ;
       HRESULT rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);
       if ( SUCCEEDED(rc) && (TRUE == IsInsideOrderedBody) )
       {
          // In case of first activation, SetCombCrvAsCurrentFeature will
          // keep the feature to restore at the end of the command
      
          if (((CATStateActivateNotification *) iNotif) -> GetType() 
                 ==  CATStateActivateNotification::Begin)
          {              
             // GetCurrentFeature is a method of CATMMUIStateCommand
             _spSpecObjOnPreviousCurrentFeat = GetCurrentFeature();
          }

          CATISpecObject * pSpecObjectOnCombCrv = NULL ;
          rc = _piCombinedCurve->QueryInterface(IID_CATISpecObject,
                                                  (void**) &pSpecObjectOnCombCrv);
          if (SUCCEEDED(rc))
          {
             // Sets the CC as current - method of CATMMUIStateCommand
             SetCurrentFeature(pSpecObjectOnCombCrv);

             pSpecObjectOnCombCrv->Release();
             pSpecObjectOnCombCrv = NULL ;
          }
       }

    }
	// In creation mode, sets the current feature as active object  
    //
	
    if ( (NULL!= iNotif) && (1 == GetMode()) && (NULL ==_piCombinedCurve) )
    {
		// GetCurrentFeature is a method of CATMMUIStateCommand
         CATISpecObject_var CurrentFeat = GetCurrentFeature();
		// Set the current feature as active object
		SetActiveObject(CurrentFeat);
	}

    return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------
CATStatusChangeRC CAAMmrCombCrvPanelStCmd::Deactivate (CATCommand * iCmd,
                                                     CATNotification * iNotif)
{
    cout << " CAAMmrCombCrvPanelStCmd::Deactivate" << endl; 

    // Restores the old current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if ( 0 == GetMode() )
    {
       CATBoolean IsInsideOrderedBody = FALSE ;
       HRESULT rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);
       if ( SUCCEEDED(rc) && (TRUE == IsInsideOrderedBody) )
       {
          // method of CATMMUIStateCommand
          SetCurrentFeature(_spSpecObjOnPreviousCurrentFeat);
       }
    }

    return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------
CATStatusChangeRC CAAMmrCombCrvPanelStCmd::Cancel (CATCommand * iCmd,
                                                     CATNotification * iNotif)
{
    cout <<" CAAMmrCombCrvPanelStCmd::Cancel" << endl; 

    // Check if the CC is inside an ordered body
    CATBoolean IsInsideOrderedBody = FALSE ;
    HRESULT rc = IsCombCrvInsideOrderedBody(IsInsideOrderedBody);

    // Restores the old current feature in edition mode
    // and if the CC is inside an ordered body
    if ( (0 == GetMode()) && SUCCEEDED(rc) && (TRUE ==IsInsideOrderedBody) )
    {
       // method of CATMMUIStateCommand
       SetCurrentFeature(_spSpecObjOnPreviousCurrentFeat);     
    }

    // Set the newly CC as the current feature in creation mode
    // and if the CC is inside an ordered body
    if ( (1 == GetMode()) && SUCCEEDED(rc) && (NULL!=_piCombinedCurve) 
        && (TRUE ==IsInsideOrderedBody) ) 
    {
       CATISpecObject * pSpecObjectOnCombCrv = NULL ;
       rc = _piCombinedCurve->QueryInterface(IID_CATISpecObject,
                                                  (void**) &pSpecObjectOnCombCrv);
       if (SUCCEEDED(rc))
       {
          // Sets the CC as current - method of CATMMUIStateCommand
          SetCurrentFeature(pSpecObjectOnCombCrv);

          pSpecObjectOnCombCrv->Release();
          pSpecObjectOnCombCrv = NULL ;

       }
    }

    return CATMMUIPanelStateCmd::Cancel(iCmd,iNotif);
    
}

//-----------------------------------------------------------------------------
HRESULT CAAMmrCombCrvPanelStCmd::IsCombCrvInsideOrderedBody(CATBoolean & oIsInsideOrderedBody )
{
    //
    // returns TRUE if the CC is inside an ordered body
    // otherwise FALSE 
    //
    HRESULT rc = E_FAIL ;

    oIsInsideOrderedBody = FALSE ;
    
    if ( NULL != _piCombinedCurve )
    {
       CATISpecObject * pSpecObjectOnCombCrv = NULL ;
       rc = _piCombinedCurve->QueryInterface(IID_CATISpecObject,
                                                  (void**) &pSpecObjectOnCombCrv);
       if ( SUCCEEDED(rc) )
       { 
           // Retrieve the father of the CC 
           CATISpecObject * pFatherCC = NULL ;
           pFatherCC = pSpecObjectOnCombCrv->GetFather();
           if ( NULL != pFatherCC )
           {
               // The father must be a GSMTool or an HybridBody
               CATIGSMTool *piGSMToolFatherCC = NULL;
               rc = pFatherCC->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFatherCC);
               if ( SUCCEEDED(rc) )
               {
                  // The father can be a ordered or not
                  int IsAnOrderedBody = -1 ;
                  piGSMToolFatherCC->GetType(IsAnOrderedBody) ;
                  if ( 1 == IsAnOrderedBody )
                  {
                     oIsInsideOrderedBody = TRUE ;
                  } 

                  piGSMToolFatherCC->Release();
                  piGSMToolFatherCC = NULL ;
               }

               pFatherCC->Release();
               pFatherCC = NULL ;
           }else rc = E_FAIL ;

           pSpecObjectOnCombCrv->Release();
           pSpecObjectOnCombCrv = NULL ;
       }
    }

    return rc ;

}



