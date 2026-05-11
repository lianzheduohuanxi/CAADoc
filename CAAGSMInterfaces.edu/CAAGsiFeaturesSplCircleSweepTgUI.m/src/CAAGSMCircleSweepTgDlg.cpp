// =========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
// =========================================================================
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent dialog box 
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
#include "CATISpecObject.h"
#include "CATUnicodeString.h"

#include "CAAGSMCircleSweepTgDlg.h" 
#include "CAAGSMCircleSweepTgUINotifications.h"

#include "CAAGsiServices.h"
#include "CAAGsiServicesBody.h"

//ApplicationFrame Framework
#include "CATApplicationFrame.h"    // needed to get the window of the frame

//Dialog Framework
#include "CATDlgGridConstraints.h"  // needed to locate dialog element on the box's grid

#include "CATFrmEditor.h"
#include "CATIPrtPart.h"
#include "CATIGSMFactory.h"
#include "CATIGSMUIFactory.h"
#include "CAAIGSMCircleSweepTg.h"
#include "CATMMUIPanelStateCmd.h"
//Mathematics
#include "CATMathPoint.h"
#include "CATMathAxis.h"
#include "CATMathVector.h"

#include "CATGSMUICmdInfo.h"
#include "CATIMfBRep.h"
#include "CATIDescendants.h"

#include "CATBody.h"

#ifdef V5R17_DLGEDITOR_CTXMENU 
#include "CAAGsiFeaturesSplUI.h" 
#include "CAAGSMFrmSelectorCtx.h"  
#include "CAAGSMFrmSelectorCtxMenuDef.h"  
#endif 

// #define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
// CATDlgWndBtnOKCancelPreview
CAAGSMCircleSweepTgDlg::CAAGSMCircleSweepTgDlg(CAAGSMCircleSweepTgCmd* FatherCom ) :
CATDlgDialog ( ( CATApplicationFrame::GetApplicationFrame() ) -> GetMainWindow ( ) ,
			  "CircleSweepTg", 
			  CATDlgGridLayout | CATDlgWndOK | CATDlgWndPREVIEW | CATDlgWndCANCEL | CATDlgWndNoResize ),
			  _sel_CurveRef   ( NULL ),
			  _sel_SurfaceSupport  ( NULL ),
#ifdef V5R17_DLGEDITOR_CTXMENU
			  _selCtx_CurveRef   ( NULL ),
			  _selCtx_SurfaceSupport  ( NULL ),
#endif 
			  _pDlgCheckTrim(NULL), _pDlgVal(NULL), 
			  _InvertButton			(NULL),
			  _pFraValue (NULL),
			  _pFatherCommand (FatherCom)


{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgDlg::CAAGSMCircleSweepTgDlg) "  << endl; 
#endif     


	// Creation of the Notifications
	_ClearSelection   = new CAACircleSweepTgUIRemoveElement();

	_Field1Selected   = new CAACircleSweepTgUICurveRefFieldActivate();
	_Field2Selected   = new CAACircleSweepTgUISupportFieldActivate();
	_Invert		      = new CAACircleSweepTgUIInvertOrientation();
	_ValueChanged     = new CAACircleSweepTgUIValueChanged();
	_TrimChanged      = new CAACircleSweepTgUITrimChanged();
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------

CAAGSMCircleSweepTgDlg::~CAAGSMCircleSweepTgDlg()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgDlg::~CAAGSMCircleSweepTgDlg) "  << endl; 
#endif     



	if (_ClearSelection) { _ClearSelection -> Release(); _ClearSelection    = NULL;}
	if (_Field1Selected) { _Field1Selected -> Release(); _Field1Selected    = NULL;}
	if (_Field2Selected) { _Field2Selected -> Release(); _Field2Selected    = NULL;}
	if (_Invert        ) { _Invert         -> Release(); _Invert            = NULL;}
	if (_ValueChanged  ) { _ValueChanged   -> Release(); _ValueChanged      = NULL;}
	if (_TrimChanged  )  { _TrimChanged    -> Release(); _TrimChanged      = NULL;}



	//  Do not delete the control elements of your dialog: 
	//     this is done automatically
	//  --------------------------------------------------

#ifdef V5R17_DLGEDITOR_CTXMENU
	_selCtx_CurveRef   = NULL ;
	_selCtx_SurfaceSupport  = NULL ;
#endif  
	_sel_CurveRef   = NULL ;
	_sel_SurfaceSupport  = NULL ;

	_pFatherCommand = NULL;

	_InvertButton= NULL;
	_pFraValue       = NULL;
	_pDlgVal   = NULL;
	_pDlgCheckTrim   = NULL;

}

//-------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::Build()
//-------------------------------------------------------------------------

void CAAGSMCircleSweepTgDlg::Build()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgDlg::Build) "  << endl; 
#endif 


	CATUnicodeString title = "Circle Sweep Tgt " ;
	SetTitle(title);

	// Creates the CATDlgLabel for the input field's names.
	// -------------------------------------------------------------

	// Creates the 2 input fields .
	CATUnicodeString Prompt_nosel = "no selection";
#ifdef V5R17_DLGEDITOR_CTXMENU
	// ..... With Contextual Menu 
	// Select a finit wire curve 
	// #define SAMPLETEST
#ifdef SAMPLETEST
	_selCtx_CurveRef = new CAAGSMFrmSelectorCtx ( (CATMMUIPanelStateCmd *) _pFatherCommand,  this , CATString("Guide"),Id_AllForTest) ;
#else 
	_selCtx_CurveRef = new CAAGSMFrmSelectorCtx ( (CATMMUIPanelStateCmd *) _pFatherCommand, this , CATString("Guide"),Id_FiniteWireCurveMenu) ;
#endif 
	_selCtx_CurveRef ->SetClearNotification((CATNotification *)  _ClearSelection );
	_sel_CurveRef = _selCtx_CurveRef-> GetEditor(); 
	CATDlgLabel * label_CurveRef  = _selCtx_CurveRef-> GetLabel(); 

#else 
	// ..... Without  Contextual Menu 
	CATDlgLabel * label_CurveRef  = new CATDlgLabel( this , CATString("Guide") );
	_sel_CurveRef  = new CATDlgSelectorList( this , CATString("Selc1"),CATDlgDataModify);
	_sel_CurveRef->SetVisibleTextHeight(1);
	_sel_CurveRef->SetLine(Prompt_nosel,0,CATDlgDataModify);
#endif     

#ifdef V5R17_DLGEDITOR_CTXMENU 
	// ..... With Contextual Menu 
	// Select a finite Surface 
	_selCtx_SurfaceSupport = new CAAGSMFrmSelectorCtx ( (CATMMUIPanelStateCmd *) _pFatherCommand , this ,CATString("Support"),Id_FiniteSurfacesMenu) ;
	_selCtx_SurfaceSupport ->SetClearNotification((CATNotification *) _ClearSelection );
	_sel_SurfaceSupport = _selCtx_SurfaceSupport-> GetEditor(); 
	CATDlgLabel * label_SurfaceSupport = _selCtx_SurfaceSupport-> GetLabel(); 

#else 
	// ..... Without  Contextual Menu 
	CATDlgLabel * label_SurfaceSupport= new CATDlgLabel( this , CATString("Support") );
	_sel_SurfaceSupport = new CATDlgSelectorList( this , CATString("Selc2"),CATDlgDataModify);
	_sel_SurfaceSupport->SetVisibleTextHeight(1);
	_sel_SurfaceSupport->SetLine(Prompt_nosel,0,CATDlgDataModify);
#endif     


	//Creates radius / 
	_pFraValue   = new CATDlgFrame(this, "FraRadius", CATDlgFraNoFrame);
	CATDlgLabel *  label_val = new CATDlgLabel      (_pFraValue,CATString("Radius"),CATDlgLabCenter  );
	_pDlgVal = new CATDlgSpinner(_pFraValue, "RadiusSpinner", CATDlgSpnEntry);
	_pDlgVal -> SetRange(0.000, 1000.000, (float)1.000);
	_pDlgVal ->SetFormat ("%3.3f") ;


	//Creates invert solution 
	CATDlgLabel * label_InvertOri= new CATDlgLabel( this , "InvertLabel",CATDlgLabRight );
	_InvertButton = new CATDlgPushButton(this,CATString("Insert Solution "));

	//Creates trim Option  / If Trim - Feature if of type modification 
	_pDlgCheckTrim = new CATDlgCheckButton (this ,"TrimOption");
	_pDlgCheckTrim -> SetState (CATDlgUncheck , 0) ;


	// Analyse Notifs
	// -------------------------------------------------------------
	// Creates the listeners linked to the fields and button

	AddAnalyseNotificationCB(_sel_CurveRef, _sel_CurveRef->GetListSelectNotification(),
		(CATCommandMethod)&CAAGSMCircleSweepTgDlg::AnalyseNotifs, (CATCommandClientData)field_1);

	AddAnalyseNotificationCB(_sel_SurfaceSupport, _sel_SurfaceSupport->GetListSelectNotification(),
		(CATCommandMethod)&CAAGSMCircleSweepTgDlg::AnalyseNotifs, (CATCommandClientData)field_2);

	AddAnalyseNotificationCB(_InvertButton,_InvertButton->GetPushBActivateNotification(), 
		(CATCommandMethod)&CAAGSMCircleSweepTgDlg::AnalyseNotifs,(CATCommandClientData)invert);	   	   

	AddAnalyseNotificationCB(_pDlgVal,_pDlgVal -> GetSpinnerModifyNotification() , 
		(CATCommandMethod)&CAAGSMCircleSweepTgDlg::AnalyseNotifs,(CATCommandClientData)val);	   	   

	AddAnalyseNotificationCB(_pDlgCheckTrim,_pDlgCheckTrim -> GetChkBModifyNotification()  , 
		(CATCommandMethod)&CAAGSMCircleSweepTgDlg::AnalyseNotifs,(CATCommandClientData)trimmode);	   	   

	// Uses the grid of the panel to position the label and the input fields.
	// -------------------------------------------------------------

#ifdef V5R17_DLGEDITOR_CTXMENU 
	CATDlgGridConstraints cst;  
	cst.Justification = CATGRID_4SIDES;
	cst.H_Span=1;     cst.V_Span=1;

	// first column : labels.
	cst.Column=0;     

	cst.Row=0; _selCtx_CurveRef      -> SetGridConstraints(cst);
	cst.Row=1; _selCtx_SurfaceSupport -> SetGridConstraints(cst);
	cst.Row=2; _InvertButton         -> SetGridConstraints(cst);
	cst.Row=3; _pFraValue            -> SetGridConstraints(cst);
	cst.Row=4; _pDlgCheckTrim       -> SetGridConstraints(cst);

#else 
	CATDlgGridConstraints cst;  
	cst.Justification = CATGRID_4SIDES;
	cst.H_Span=1;     cst.V_Span=1;

	// first column : labels.
	cst.Column=0;     

	cst.Row=0; label_CurveRef      -> SetGridConstraints(cst);
	cst.Row=1; lable_SurfaceSupport -> SetGridConstraints(cst);
	cst.Row=2; _InvertButton         -> SetGridConstraints(cst);
	cst.Row=3; _pFraValue            -> SetGridConstraints(cst);
	cst.Row=4; _pDlgCheckTrim       -> SetGridConstraints(cst);

	// second column : input fields.
	cst.Column=1;     

	cst.Row=0; _sel_CurveRef         -> SetGridConstraints(cst);
	cst.Row=1; _sel_SurfaceSupport   -> SetGridConstraints(cst);
	cst.Row=2; _InvertButton         -> SetGridConstraints(cst);
	cst.Row=3; _pFraValue            -> SetGridConstraints(cst);
#endif 
	SetVisibility(CATDlgShow);

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgDlg::Build)End  "  << endl; 
#endif     
}

//-------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::HighLightCurrentPanelField()
//-------------------------------------------------------------------------

void CAAGSMCircleSweepTgDlg::HighLightCurrentPanelField(int iFieldNumber)
{
	CATUnicodeString FirstLine[1]; // SetSelect() wants an array as parameter

	//  Deselects all others field when changing of active field ( by clicking in another one ).
	_sel_CurveRef          -> ClearSelect();
	_sel_SurfaceSupport    -> ClearSelect();

	// Highlights the active field
	if ( 1 == iFieldNumber ) 
	{
		_sel_CurveRef -> GetLine(FirstLine[0], 0); // we get the line of the selector list to be highlighted
		_sel_CurveRef -> SetSelect(FirstLine, 1,0); // selects and highlights the selected line
	}
	if ( 2 == iFieldNumber ) 
	{
		_sel_SurfaceSupport -> GetLine(FirstLine[0], 0);
		_sel_SurfaceSupport -> SetSelect(FirstLine, 1,0);
	}
	return ;
}

//-------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::SetName()
//-------------------------------------------------------------------------

void CAAGSMCircleSweepTgDlg::SetUserSelectedFeature(int iFieldNumber , const CATISpecObject_var iSpInput  )
{
	// Writes the name of the selected objet in the active field.
	// Replaces it if the object was already selected.
#ifndef V5R17_DLGEDITOR_CTXMENU 
	CATBaseUnknown_var IFtrBase (iSpInput); 
	CATUnicodeString iName=  CAAGsiGetSpecDisplayName(IFtrBase);
#endif 

	switch (iFieldNumber )
	{
	case 1 : 
		{
#ifdef V5R17_DLGEDITOR_CTXMENU 
			_selCtx_CurveRef  -> SetFeature ( iSpInput );
#else
			_sel_CurveRef  -> SetLine ( iName , 0 , CATDlgDataModify );
#endif 
			break; 
		}
	case 2 : 
		{
#ifdef V5R17_DLGEDITOR_CTXMENU 
			_selCtx_SurfaceSupport  -> SetFeature ( iSpInput );
#else
			_sel_SurfaceSupport   -> SetLine ( iName , 0 , CATDlgDataModify );
#endif 
			break; 
		}
	}
}

//-------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::GetField()
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
// Public : GetRadiusValue()
//-------------------------------------------------------------------------
double CAAGSMCircleSweepTgDlg::GetRadiusValue()
{
	if (_pDlgVal  == NULL ) return 0.0;
	return _pDlgVal ->GetCurrentValue();
}

//-------------------------------------------------------------------------
int  CAAGSMCircleSweepTgDlg::GetTrimMode()
{
	int Status = 0 ;
	if (_pDlgCheckTrim  != NULL ){
		if (  _pDlgCheckTrim ->GetState() == CATDlgCheck ) Status = 1 ;
	}
	return Status;

}

//-------------------------------------------------------------------------

// Public : SetRadiusValue()
//-------------------------------------------------------------------------
void CAAGSMCircleSweepTgDlg::SetRadiusValue(double iValue)
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout <<" (CAAGSMCircleSweepTgDlg::SetRadiusValue) Spinner Setup  " << iValue <<endl; 
#endif 
	_pDlgVal ->SetCurrentValue((float)iValue,0);
}

//-------------------------------------------------------------------------
void  CAAGSMCircleSweepTgDlg::SetTrimMode(int iTrim, int Sensitive)
{

	// Dlg Trim status 
	if (iTrim ==1 ) {
		_pDlgCheckTrim ->SetState(CATDlgCheck,0);
	}
	else {
		_pDlgCheckTrim ->SetState(CATDlgUncheck,0);
	}

	// edit + OGSAndHybridBody = Disable 
	if (Sensitive ==0 ) { 
		_pDlgCheckTrim -> SetSensitivity(CATDlgDisable) ;
	}
	else if (Sensitive ==1 ) { 
		_pDlgCheckTrim -> SetSensitivity(CATDlgEnable) ;
	}

}


//-------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::AnalyseNotifs()
// Methods dispatching the notifications
//-------------------------------------------------------------------------

void CAAGSMCircleSweepTgDlg::AnalyseNotifs(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData modifId)
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout <<"(CAAGSMCircleSweepTgDlg::AnalyseNotifs) "<< endl; 
#endif     
	int whichAction=  CATPtrToINT32(modifId);

#ifdef DEBUG_GSD_CAASAMPLE
	cout <<"whichAction = "<< whichAction <<endl; 
#endif 
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
	case val :
		SendNotification (GetFather (),_ValueChanged );
		break;
	case trimmode :
		SendNotification (GetFather (),_TrimChanged );
		break;
	default:
		break;
	}

#ifdef DEBUG_GSD_CAASAMPLE
	cout <<"(CAAGSMCircleSweepTgDlg::AnalyseNotifs) END "<<endl;
#endif 
}

//-------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::AutoFieldSelection()
// Simulates a Clic on SelectField of the panel
//-------------------------------------------------------------------------

void CAAGSMCircleSweepTgDlg::AutoFieldSelection  (	CATDlgSelectorList* SelectField )
{

	//Simulate Clic in Panel sending a notification to the father command
	if(SelectField ) 
	{

		//Highlight of the field in the panel
		if (_sel_CurveRef == SelectField){
			// to be sure that Active field is changed before sending the notif
			_pFatherCommand->SetActiveField(1); 			
			AnalyseNotifs(NULL,NULL,(void*)field_1);

		}
		else if (_sel_SurfaceSupport == SelectField){
			_pFatherCommand->SetActiveField(2);
			AnalyseNotifs(NULL,NULL,(void*)field_2);

		}
	}

}




//---------------------------------------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg::IsAnInfiniteFeature()
//---------------------------------------------------------------------------------------------------
boolean CAAGSMCircleSweepTgDlg::IsAnInfiniteFeature(CATISpecObject * Feat)
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


//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : UpdatePanel()
//-----------------------------------------------------------------------------
void CAAGSMCircleSweepTgDlg::UpdatePanel()
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgDlg::UpdatePanelFields) "  << endl; 
#endif 
	
	// Synchronize Pane lwith Data Model
	// -----------------------------------------------------------------
	CATISpecObject_var spCurve  ,   spSurface; 
	CAAIGSMCircleSweepTg_var  spSweepTg = _pFatherCommand ->GiveMyFeature () 	; 

	if (!! spSweepTg) { 

		// SetUp Fields 
		// Curve Ref 
		spSweepTg->GetCurveRef(spCurve); 
		if  (NULL_var != spCurve) { 
			SetUserSelectedFeature (1 ,spCurve );
		}
		else {
			SetUserSelectedFeature (1 ,NULL_var );
		}

		// Support Surface 
		spSweepTg->GetSurfaceSupport(spSurface); 
		if  (NULL_var != spSurface) { 
			SetUserSelectedFeature (2 ,spSurface );
		}
		else {
			SetUserSelectedFeature (2,NULL_var );
		}


		double radius = 0.0 ; 
		spSweepTg->GetRadius(radius);
		SetRadiusValue         ( radius);


		int Sensitivity  = _pFatherCommand -> GetContext() ;
		int iTrim = 0; 
		spSweepTg->GetTrimMode(iTrim );
		SetTrimMode          (iTrim,Sensitivity );
	}

	// Sensitivity 
	// -----------------------------------------------------------------
	if ( !!spCurve && !!spSurface  ){
		SetOKSensitivity(CATDlgEnable);
		SetPREVIEWSensitivity(CATDlgEnable);
		_InvertButton  -> SetSensitivity(CATDlgEnable);   // Invert only if result computed 
	}
	else{
		SetOKSensitivity(CATDlgDisable);
		SetPREVIEWSensitivity(CATDlgEnable);
		_InvertButton -> SetSensitivity(CATDlgDisable);  // Invert only if result computed 
	}
	return;
}



