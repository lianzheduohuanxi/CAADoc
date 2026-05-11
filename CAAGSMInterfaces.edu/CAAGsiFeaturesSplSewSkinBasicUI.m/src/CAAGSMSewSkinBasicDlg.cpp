// =========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
// =========================================================================
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
// 
// CAAGSMSewSkinBasicDlg
//---------------------------------------------------------------------
// 
//  Sew Skin Basic dialog box 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------


// Local Framework
// MINC 
#include "CATBooleanDef.h"
#include "CATDlgLabel.h"
#include "CATIGeometricalElement.h"
#include "CATUnicodeString.h"

#include "CAAGSMSewSkinBasicDlg.h" 
#include "CAAGSMSewSkinBasicUINotifications.h"

//ApplicationFrame Framework
#include "CATApplicationFrame.h"    // needed to get the window of the frame

//Dialog Framework
#include "CATDlgGridConstraints.h"  // needed to locate dialog element on the box's grid

#include "CATFrmEditor.h"
#include "CATIPrtPart.h"
#include "CATIGSMFactory.h"
#include "CATIGSMUIFactory.h"

//Mathematics
#include "CATMathPoint.h"
#include "CATMathAxis.h"
#include "CATMathVector.h"

#include "CATGSMUICmdInfo.h"
#include "CATIMfBRep.h"
#include "CATIDescendants.h"

#include "CATBody.h"

//#define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 


 
// static CAACmdInfoUser UserInfo ; 
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
// CATDlgWndBtnOKCancelPreview
CAAGSMSewSkinBasicDlg::CAAGSMSewSkinBasicDlg(CAAGSMSewSkinBasicCmd* FatherCom ) :
CATDlgDialog ( ( CATApplicationFrame::GetApplicationFrame() ) -> GetMainWindow ( ) ,
              "SewSkin", 
              CATDlgGridLayout | CATDlgWndOK | CATDlgWndPREVIEW | CATDlgWndCANCEL | CATDlgWndNoResize ),
              _sel_SurfaceToSew   ( NULL ),
              _sel_SurfaceSupport  ( NULL ),
              _InvertButton			(NULL),
              _TheCommand (FatherCom)
{

    
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicDlg::CAAGSMSewSkinBasicDlg) "  << endl; 
#endif     
    
   
    // Creation of the Notifications
    _ClearSelection   = new CAAGSMSewSkinBasicUIRemoveElement();
    
    _Field1Selected   = new CAASurfaceToSewFieldActivate();
    _Field2Selected   = new CAASupportFieldActivate();
    _Invert		      = new CAAInvertOrientation();
    // never call the Build method of the panel from the constructor
    // it is much better to call it from the same method that created (new) the panel
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------

CAAGSMSewSkinBasicDlg::~CAAGSMSewSkinBasicDlg()
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicDlg::~CAAGSMSewSkinBasicDlg) "  << endl; 
#endif     

    if (_ClearSelection) { _ClearSelection -> Release(); _ClearSelection    = NULL;}
    if (_Field1Selected) { _Field1Selected -> Release(); _Field1Selected    = NULL;}
    if (_Field2Selected) { _Field2Selected -> Release(); _Field2Selected    = NULL;}
    if (_Invert        ) { _Invert         -> Release(); _Invert            = NULL;}
    


    //  Do not delete the control elements of your dialog: 
    //     this is done automatically
    //  --------------------------------------------------
    
    _sel_SurfaceToSew   = NULL ;
    _sel_SurfaceSupport  = NULL ;
    _TheCommand = NULL;
    _InvertButton= NULL;

}

//-------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::Build()
//-------------------------------------------------------------------------

void CAAGSMSewSkinBasicDlg::Build()
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicDlg::Build) "  << endl; 
#endif 

    
    CATUnicodeString title = "Sew Surface " ;
    SetTitle(title);
 
    // Creates the CATDlgLabel for the input field's names.
    // -------------------------------------------------------------
    
    CATDlgLabel * label_SurfaceToSew  = new CATDlgLabel( this , CATString("LabelS1") );
    CATDlgLabel * label_SurfaceSupport = NULL ; 
        label_SurfaceSupport= new CATDlgLabel( this , CATString("LabelS2") );
    
    CATDlgLabel * label_InvertOri= new CATDlgLabel( this , "InvertLabel",CATDlgLabRight );
    
    // Creates the 2 input fields .
    CATUnicodeString Prompt_nosel = "no selection";
    
    _sel_SurfaceToSew  = new CATDlgSelectorList( this , CATString("Selc1"),CATDlgDataModify);
    _sel_SurfaceToSew->SetVisibleTextHeight(1);
    _sel_SurfaceToSew->SetLine(Prompt_nosel,0,CATDlgDataModify);
    
    
    _sel_SurfaceSupport = new CATDlgSelectorList( this , CATString("Selc2"),CATDlgDataModify);
    _sel_SurfaceSupport->SetVisibleTextHeight(1);
    _sel_SurfaceSupport->SetLine(Prompt_nosel,0,CATDlgDataModify);
    
    //Creates the 2 contextual menus with their Listeners
    
    
    

    //Creates the button to enable inversion of the Sew Skin
    _InvertButton = new CATDlgPushButton(this,CATString("InvertOrientation"));
    

    // Analyse Notifs
    // -------------------------------------------------------------
    // Creates the listeners linked to the fields and button
    AddAnalyseNotificationCB(_sel_SurfaceToSew, _sel_SurfaceToSew->GetListSelectNotification(),
        (CATCommandMethod)&CAAGSMSewSkinBasicDlg::AnalyseNotifs, (CATCommandClientData)field_1);
    
    AddAnalyseNotificationCB(_sel_SurfaceSupport, _sel_SurfaceSupport->GetListSelectNotification(),
        (CATCommandMethod)&CAAGSMSewSkinBasicDlg::AnalyseNotifs, (CATCommandClientData)field_2);
    
    AddAnalyseNotificationCB(_InvertButton,_InvertButton->GetPushBActivateNotification(), 
        (CATCommandMethod)&CAAGSMSewSkinBasicDlg::AnalyseNotifs,(CATCommandClientData)invert);	   	   
    

    // Uses the grid of the panel to position the label and the input fields.
    // -------------------------------------------------------------
    CATDlgGridConstraints cst;  
    cst.Justification = CATGRID_4SIDES;
    cst.H_Span=1;     cst.V_Span=1;
    
    // first column : labels.
    cst.Column=0;     
    
    cst.Row=0; label_SurfaceToSew    -> SetGridConstraints(cst);
    cst.Row=1; label_SurfaceSupport  -> SetGridConstraints(cst);
    cst.Row=2; label_InvertOri  -> SetGridConstraints(cst);
    
    // second column : input fields.
    cst.Column=1;     
    
    cst.Row=0; _sel_SurfaceToSew     -> SetGridConstraints(cst);
    cst.Row=1; _sel_SurfaceSupport   -> SetGridConstraints(cst);
    cst.Row=2; _InvertButton         -> SetGridConstraints(cst);

    // Finally, makes the panel appear.
    SetVisibility(CATDlgShow);
    
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMSewSkinBasicDlg::Build)End  "  << endl; 
#endif     
}

//-------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::HighLightCurrentPanelField()
//-------------------------------------------------------------------------

void CAAGSMSewSkinBasicDlg::HighLightCurrentPanelField(int iFieldNumber)
{
    CATUnicodeString FirstLine[1]; // SetSelect() wants an array as parameter
    
    //  Deselects all others field when changing of active field ( by clicking in another one ).
    _sel_SurfaceToSew -> ClearSelect();
    _sel_SurfaceSupport    -> ClearSelect();
    
    // Highlights the active field
    if ( 1 == iFieldNumber ) 
    {
        _sel_SurfaceToSew -> GetLine(FirstLine[0], 0); // we get the line of the selector list to be highlighted
        _sel_SurfaceToSew -> SetSelect(FirstLine, 1,0); // selects and highlights the selected line
    }
    if ( 2 == iFieldNumber ) 
    {
        _sel_SurfaceSupport -> GetLine(FirstLine[0], 0);
        _sel_SurfaceSupport -> SetSelect(FirstLine, 1,0);
    }
    return ;
}

//-------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::SetName()
//-------------------------------------------------------------------------

void CAAGSMSewSkinBasicDlg::SetName(int iFieldNumber , CATUnicodeString iName )
{
    // Writes the name of the selected objet in the active field.
    // Replaces it if the object was already selected.
    
    switch (iFieldNumber )
    {
    case 1 : { _sel_SurfaceToSew  -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case 2 : { _sel_SurfaceSupport   -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    }
    return ;
}

//-------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::GetField()
//-------------------------------------------------------------------------

CATDlgSelectorList* CAAGSMSewSkinBasicDlg::GetField(int iFieldNumber)
{
    // returns the active field ( used by the state command ).
    switch (iFieldNumber )
    {   
    case 1 : return _sel_SurfaceToSew;
    case 2 : return _sel_SurfaceSupport ;
    }
    return NULL ;
}


//-------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::AnalyseNotifs()
// Methods dispatching the notifications
//-------------------------------------------------------------------------

void CAAGSMSewSkinBasicDlg::AnalyseNotifs(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData modifId)
{
    
    int whichAction=  CATPtrToINT32(modifId);
    
    switch (whichAction)
    {
    case field_1:
        SendNotification (GetFather (),_Field1Selected );
        break;
    case field_2:
        SendNotification (GetFather (), _Field2Selected);
        break;
    case clear:
        SendNotification (GetFather (), _ClearSelection);
        break;
    case invert:
        SendNotification (GetFather (), _Invert);
        break;
        
    default:
        break;
    }
    
}


//-------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::AutoFieldSelection()
// Simulates a Clic on SelectField of the panel
//-------------------------------------------------------------------------

void CAAGSMSewSkinBasicDlg::AutoFieldSelection  (	CATDlgSelectorList* SelectField )
{
    
    //Simulate Clic in Panel sending a notification to the father command
    if(SelectField ) 
    {
        //Highlight of the field in the panel
        if (_sel_SurfaceToSew == SelectField){
            // to be sure that Active field is changed before sending the notif
            _TheCommand->SetActiveField(1); 			
            AnalyseNotifs(NULL,NULL,(void*)field_1);
            
        }
        else if (_sel_SurfaceSupport == SelectField){
            _TheCommand->SetActiveField(2);
            AnalyseNotifs(NULL,NULL,(void*)field_2);
            
        }
        
    }
    
}





//---------------------------------------------------------------------------------------------------
// CAAGSMSewSkinBasicDlg::IsAnInfiniteFeature()
//---------------------------------------------------------------------------------------------------
boolean CAAGSMSewSkinBasicDlg::IsAnInfiniteFeature(CATISpecObject * Feat)
{
    boolean returnCode = FALSE;
    HRESULT rc = E_FAIL; 
    if (NULL != Feat) { 
        // queries the interface CATIGeometricalElement on the Feature selected
        CATIGeometricalElement * piGeometricalElement = NULL;
        rc = Feat->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElement );
        //if (Feat) {Feat->Release(); Feat=NULL;}
        
        if ( SUCCEEDED(rc) ) {
            
            // uses GetBodyResult to retrieve the first body
            CATBody_var spiBodyOfCurve = piGeometricalElement->GetBodyResult();
            
            //prevents the selection of Infinite Elements
            if(!!spiBodyOfCurve) {
                if (spiBodyOfCurve->HasInfiniteGeometry()) {returnCode = TRUE;}		  
            }
            piGeometricalElement->Release(); piGeometricalElement = NULL;
        }
    }
    return returnCode;
}

