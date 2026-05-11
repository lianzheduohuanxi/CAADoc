// -------------------------------------------------------------------
// Copyright Dassault Systemes 2006
//---------------------------------------------------------------------
// Shade Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMFrmSelectorCtx
//---------------------------------------------------------------------
// 
//  Dialog widget integrating  GSD contextual menu  activation 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 06/06/01 > PEY 
//---------------------------------------------------------------------

// MINC 
#include "CATBoolean.h"
#include "CATBooleanDef.h"
#include "CATIContainer.h"
#include "CATIGeometricalElement.h"
#include "CATNotification.h"
#include "CATPathElement.h"

#include "CAAGSMFrmSelectorCtx.h"
#include "CAAGSMFrmCtxMenuList.h"
#include "CAAGSMFrmSelectorCtxMenuDef.h"

//#include "CAAGSMFrmSelectorCtxNotifications.h"
#include "CAAGSMFrmCtxMenuInfoUser.h"


#include "CAAGsiServices.h"
#include "CAAGsiServicesBody.h"

#include "CATMMUIPanelStateCmd.h"
#include "CATDlgFrame.h"

//System
#include "CATUnicodeString.h"
#include "CATString.h"

//Dialog
#include "CATDlgSelectorList.h"
#include "CATDlgGridConstraints.h"

#include "CATDlgPushItem.h"
#include "CATDlgPushButton.h"
#include "CATDlgContextualMenu.h"
#include "CATDlgSeparatorItem.h"

//ObjectSpecsModeler
#include "CATLISTV_CATISpecObject.h"


//SO
#include "CATFrmEditor.h"
#include "CATHSO.h"

#include "CATGSMUICmdInfo.h"
#include "CATIPrtPart.h"
#include "CATIGSMUIFactory.h"
#include "CATIIcon.h"
#include "CATIMfBRep.h"

#include "CATIDescendants.h"
#include "CATBody.h"

#define CLEAR  1
//#define  DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h" 
#endif 

// ------------------------------------------
#include "CATFrmEditor.h"
#include "CATMathAxis.h"
#include "CATMathVector.h"
#include "CATMathPoint.h"
int IsCurrentAxisOIJK () 
{ 
	int IsCurrentAxisOIJK  =0 ; 
	double Precision = 0.001; //@GSD_ES_NoChange (angle tolerance)
	CATMathAxis CurAxis = CATFrmEditor::GetCurrentEditor()->GetCurrentLocalAxisSystem();
	CATMathVector VX,VY,VZ;
	CATMathPoint PtO;
	CurAxis.GetDirections(VX,VY,VZ);
	CurAxis.GetOrigin(PtO);
	if( VX.AngleTo(CATMathI)<Precision && VY.AngleTo(CATMathJ)<Precision && VZ.AngleTo(CATMathK)<Precision && PtO.DistanceTo(CATMathO)< Precision ) //@ GSD_ES_Done 
		IsCurrentAxisOIJK =  1;	
	return IsCurrentAxisOIJK; 
}
//
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
// |CATDlgGridLayout
CAAGSMFrmSelectorCtx::CAAGSMFrmSelectorCtx(CATMMUIPanelStateCmd  * iFatherCmd, CATDialog * iParent , const CATString &iDialogObjectName,const CAAGSMFrmSelectorCtxMenuDef  iAvailableCtxMenu)                                         
: CATDlgFrame(iParent,iDialogObjectName,CATDlgFraNoTitle |CATDlgFraNoFrame |CATDlgGridLayout ),
_sel_selector(NULL),_label_dlg (NULL),_Frame(NULL),_contextual(NULL)

{
	//cout <<"=========> (CAAGSMFrmSelectorCtx::CAAGSMFrmSelectorCtx) Start CONSTRUCTOR  "  <<endl ; 
	// Creation of the Notifications
	_iFatherCmd       = iFatherCmd; 

	_pCurrentFeature  = NULL ;   
	_DlgClearSelection = NULL;
	_CtxMenu = iAvailableCtxMenu; 

    //cout <<"(CAAGSMFrmSelectorCtx::~CAAGSMFrmSelectorCtx) INIT _InfoListSize = "<< _InfosList.Size() <<endl; 
    _InfosList.RemoveAll();   // PEY MLK 07.10.03 

	// Creates the CATDlgLabel for the input field's names.
	// -------------------------------------------------------------

	CATUnicodeString Prompt_nosel = "no selection";
	_label_dlg  = new CATDlgLabel(this, iDialogObjectName , CATDlgLabLeft);
	_sel_selector= new CATDlgSelectorList(this, CATString("Selector"),CATDlgDataModify);
	_sel_selector->SetVisibleTextHeight(1);
	_sel_selector->SetVisibleTextWidth (15);
	_sel_selector->SetLine(Prompt_nosel,0,CATDlgDataModify);


	//Creates the contextual menus with their Listeners
	// -------------------------------------------------------------
	_contextual = new CATDlgContextualMenu (_sel_selector, CATString("ContextSelector"), CATDlgCtxEmpty); 
	AddAnalyseNotificationCB(_contextual,_contextual->GetVisibilityNotification(), (CATCommandMethod)&CAAGSMFrmSelectorCtx::ContextualMenuActivation,_sel_selector);	   	   


	// Uses the grid of the panel to position the label and the input fields.
	// -------------------------------------------------------------

	CATDlgGridConstraints cst;  
	cst.Justification = CATGRID_4SIDES;
	cst.H_Span=1;     cst.V_Span=1;
	// first column : labels.

	cst.Column=0;     
	cst.Row=0; _label_dlg        -> SetGridConstraints(cst);

	cst.Column=1;     
	cst.Row=0; _sel_selector      -> SetGridConstraints(cst);

}

//
//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAGSMFrmSelectorCtx::~CAAGSMFrmSelectorCtx ()
{
	//  cout <<"=========>  (CAAGSMFrmSelectorCtx::~CAAGSMFrmSelectorCtx) Start DESTRUCTOR  "  <<endl ; 
	_iFatherCmd       =  NULL;
	//  if (_ClearSelection) { _ClearSelection -> Release();  _ClearSelection   = NULL;}
	_sel_selector   = NULL;
	_label_dlg      = NULL;
	_Frame          = NULL;
	_contextual     = NULL;

    // Clean Up Info list ( use for contextual menus ) 
	int size = _InfosList.Size(); // PEY MLK 07.10.03 
    if(size) {
        CAAGSMFrmCtxMenuInfoUser *UserInfo = NULL; 
		for(int i=1; i<=size; i++) 	{
            UserInfo = NULL;  
            UserInfo =(CAAGSMFrmCtxMenuInfoUser *)  _InfosList[i] ; 
            if (NULL != UserInfo){ 
                delete UserInfo ;UserInfo = NULL;
            }
        
		}
	}
    _InfosList.RemoveAll(); 



    // Release Current Feature 
    if (NULL !=  _pCurrentFeature ) {
		_pCurrentFeature -> Release() ; 
		_pCurrentFeature = NULL;     
	}	
	
	_DlgClearSelection = NULL;
	// cout <<"(CAAGSMFrmSelectorCtx::~CAAGSMFrmSelectorCtx) end "  <<endl ; 

}

//
//-------------------------------------------------------------------------
// Contextual Menu / Analyse Notifications 
//-------------------------------------------------------------------------

void CAAGSMFrmSelectorCtx::AnalyseNotifs(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData modifId)
{

	int whichAction=  CATPtrToINT32(modifId);

	switch (whichAction)
	{
	case CLEAR:
		if (_DlgClearSelection){ 

			SendNotification (GetFather(), _DlgClearSelection);
		}
		break;
	default:
		break;
	}

}


//-------------------------------------------------------------------------
// Contextual Menu /Set Contextual Menus (Obsolete , use InitContextualItem)
//-------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::SetContextualItems(CATListOfCATUnicodeString &Name, CATListOfCATUnicodeString &Icon, CATListOfCATUnicodeString &StartUp) 
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::SetContextualItems) "  << endl; 
#endif 
	_Name.RemoveAll(); 
	_Icon.RemoveAll() ;
	_StartUp.RemoveAll(); 
	int nb_item = Name.Size() ; 
	int nb_item2 = Icon.Size() ; 
	int nb_item3 = StartUp.Size() ; 
#ifdef DEBUG_GSD_CAASAMPLE
	cout << " size 1 = "<<nb_item<< "/ size 2 = "<<nb_item2<< " / size 3 = "<<nb_item3<< endl; 
#endif 
	int k = 0 ; 
	for (k=1;k <=nb_item;k++) { 
#ifdef DEBUG_GSD_CAASAMPLE
		cout << " CMd Des =  "<< Name[k] <<" and  "<< Icon[k] <<" and  "<< StartUp[k]<< endl; 
#endif 
		_Name.Append(Name[k]) ; 
		_Icon.Append(Icon[k]) ; 
		_StartUp.Append(StartUp[k]) ; 
	}
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::SetContextualItems) End "  << endl; 
#endif 
}


//-------------------------------------------------------------------------
// Contextual Menu / Init Contextual Menus 
//-------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::InitContextualItems(CATDlgContextualMenu* & Ctx)
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::InitContextualItems) "  << endl; 
#endif 
	CAAGSMFrmCtxMenuList* pCtxMenuList= CAAGSMFrmCtxMenuList::GetCtxMenuList();
	if(NULL==pCtxMenuList) return ;

	CAAGSMFrmCtxMenu *pCtxMenu = NULL ; 


	CATUnicodeString strName, strIcon , strStartup, strInfo ; 
	if(_CtxMenu & Id_NoMenu)
	{

	}
	else
	{
		//Sketch 
		if(_CtxMenu & Id_SketchBased){
			int IndexMenu 	= iKey_SketchBased ; 		
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// Point 
		if(_CtxMenu & Id_PointMenu) {
			int IndexMenu 	=iKey_PointMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		if(_CtxMenu & Id_MidpointMenu){
			int IndexMenu 	=iKey_MidpointMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		if(_CtxMenu & Id_EndpointMenu){
			int IndexMenu 	=iKey_EndpointMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// Line & Axis 
		if(_CtxMenu & Id_LineMenu){
			int IndexMenu 	=iKey_LineMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		if(_CtxMenu & Id_RefAxisMenu){
			int IndexMenu 	=iKey_RefAxisMenu ; 		
			int k = 0 ; 
			// Ref Axis 
			for (  k= 1 ; k<=3 ; k++ ) { 
				pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu+k); 
				if (pCtxMenu != NULL) { 
					ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx ,1 ,pCtxMenu -> _Info );    
				}
			}
			// Local Axis ? 
			if(!IsCurrentAxisOIJK()){
				for (k= 4 ; k<=6 ; k++ ) { 
					pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu+k); 
					if (pCtxMenu != NULL) { 
						ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx ,1 ,pCtxMenu -> _Info );    
					}
				}
			}
			// Compass 
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu+7); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx ,1 ,pCtxMenu -> _Info );    
			}

		}

		// Plane and Ref 
		if(_CtxMenu & Id_PlaneMenu){
			int IndexMenu 	=iKey_PlaneMenu; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		if(_CtxMenu & Id_RefPlanesMenu){
			int IndexMenu 	=iKey_RefPlanesMenu ; 			
			// Ref Axis
			int k = 0 ; 
			for ( k= 1 ; k<=3 ; k++ ) { 
				pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu+k); 
				if (pCtxMenu != NULL) { 
					ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx ,1 ,pCtxMenu -> _Info );    
				}
			}
			// Local Axis ? 
			if(!IsCurrentAxisOIJK()){
				for ( k= 4 ; k<=6 ; k++ ) { 
					pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu+k); 
					if (pCtxMenu != NULL) { 
						ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx ,1 ,pCtxMenu -> _Info );    
					}
				}
			}
		}

		// Interst 
		if(_CtxMenu & Id_IntersectMenu){
			int IndexMenu 	=iKey_IntersectMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// project 
		if(_CtxMenu & Id_ProjectMenu){
			int IndexMenu 	=iKey_ProjectMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// Assemble 
		if(_CtxMenu & Id_AssembleMenu){
			int IndexMenu 	=iKey_AssembleMenu; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// Boundary 
		if(_CtxMenu			& Id_BoundaryMenu){
			int IndexMenu 	=iKey_BoundaryMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// Extract 
		if(_CtxMenu & Id_ExtractMenu){
			int IndexMenu 	=iKey_ExtractMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		if(_CtxMenu & Id_ExtractC0Menu){
			int IndexMenu 	=iKey_ExtractC0Menu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		if(_CtxMenu & Id_ExtractC1Menu){
			int IndexMenu 	=iKey_ExtractC1Menu; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		if(_CtxMenu & Id_ExtractMultiMenu){
			int IndexMenu 	=iKey_ExtractMultiMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Extrapol 
		if(_CtxMenu & Id_ExtrapolMenu){
			int IndexMenu 	=iKey_ExtrapolMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		// law 
		if(_CtxMenu & Id_LawMenu){
			int IndexMenu 	=iKey_LawMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Extremum 
		if(_CtxMenu & Id_ExtremumMenu){
			int IndexMenu 	=iKey_ExtremumMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		//Curve Smooth 
		if(_CtxMenu & Id_CurveSmoothMenu){
			int IndexMenu 	=iKey_CurveSmoothMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Spine 
		if(_CtxMenu & Id_SpineMenu){
			int IndexMenu 	=iKey_SpineMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		//Loft
		if(_CtxMenu & Id_LoftMenu){
			int IndexMenu 	=iKey_LoftMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		//MultiplePoint
		if(_CtxMenu & Id_MultiplePointMenu){
			int IndexMenu 	=iKey_MultiplePointMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// Affinity 
		if(_CtxMenu & Id_AffinityMenu){
			int IndexMenu 	=iKey_AffinityMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Extrude 
		if(_CtxMenu & Id_ExtrudeMenu){
			int IndexMenu 	=iKey_ExtrudeMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Offset 
		if(_CtxMenu & Id_OffsetMenu){
			int IndexMenu 	= iKey_OffsetMenu; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Trim 
		if(_CtxMenu & Id_TrimMenu){
			int IndexMenu 	=iKey_TrimMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//Split 
		if(_CtxMenu & Id_SplitMenu){
			int IndexMenu 	=iKey_SplitMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
		//CurvePar 
		if(_CtxMenu & Id_CurveParMenu){
			int IndexMenu 	=iKey_CurveParMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		// AxisSystem 
		if(_CtxMenu & Id_AxisSystemMenu){
			int IndexMenu 	=iKey_AxisSystemMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}

		//Inverse 
		if(_CtxMenu & Id_InverseMenu){
			int IndexMenu 	=iKey_InverseMenu ; 						
			pCtxMenu = pCtxMenuList -> GetFromKey(IndexMenu); 
			if (pCtxMenu != NULL) { 
				ItemContextualMenu( pCtxMenu -> _Name  ,pCtxMenu -> _Icon   , pCtxMenu -> _Startup, 0, Ctx );    
			}
		}
	}
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::SetContextualItems) End "  << endl; 
#endif 
}



//-------------------------------------------------------------------------
// Contextual Menu /  Build of the Contextual Menus	
//-------------------------------------------------------------------------
// Rule 
// Creates an Item Of the Contextual Menu with its Label, Icon, 
// and add a data to know if the feature is to be edited or not
//-------------------------------------------------------------------------

void CAAGSMFrmSelectorCtx::ItemContextualMenu (CATUnicodeString Label ,CATUnicodeString Icon_Name,CATUnicodeString StartUpName,int EditMode, CATDlgContextualMenu* & Ctx,int iInfo, CATUnicodeString StrInfo)
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::ItemContextualMenu) "  << endl; 
#endif     
	CATString NameOfMenu  (Label.ConvertToChar())  ; 
	CATDlgPushItem * Item      = new CATDlgPushItem (Ctx,  NameOfMenu);
	CATString NameOfMyIcone (Icon_Name.ConvertToChar());
	Item      -> SetIconName(NameOfMyIcone); 

	CAAGSMFrmCtxMenuInfoUser *UserInfo = new CAAGSMFrmCtxMenuInfoUser(); 
	if (NULL!= UserInfo) {
		CATGSMUICmdInfo * info     = UserInfo -> GetCmdInfo () ;

		if (  NULL!= info ) { 
			UserInfo ->SetEditMode   (EditMode) ; 
			info     ->SetStartUpName(StartUpName);
			if (iInfo ==1) { 
				info     ->SetSelectorContextualItem(StrInfo);
			}
			// NEW Update for AGGREGATION
			// Creation 
			// !! Warning if Mode set to one  => Need to support aggregation of contextual feature for the current feature in the model
			// Default Value is = 0;
			// #define NO_AGG 
#ifdef NO_AGG
			int Agg_mode = 0 ;
			info->SetContextualFeaturesAggregMode(Agg_mode);
			// No aggregation Mode 
			//            if (EditMode==0) {
			//                info->SetContextualFeaturesAggregMode(0);// It is Not to be Aggregated
			//            } 
#else 
			// aggregation mode 
			int Agg_mode = 1; 
			info->SetContextualFeaturesAggregMode(Agg_mode);
			//            if (EditMode==0) {
			//                info->SetContextualFeaturesAggregMode(1);// It is a creation Item => The feature has to be Aggregated
			//            } 
#endif   

			// Edit  
			if (EditMode==1)  {
				new CATDlgSeparatorItem(Ctx,"Separator");
			}
			// It is an edition Item => The feature is already Aggregated
    		_InfosList.Append(UserInfo);

			//_InfosList.Append(info);
			AddAnalyseNotificationCB(Item, Item->GetMenuIActivateNotification(), (CATCommandMethod)& CAAGSMFrmSelectorCtx::ContextualMenuSelection,UserInfo);          
		}
	}
#ifdef DEBUG_GSD_CAASAMPLE
	    cout << "(CAAGSMFrmSelectorCtx::ItemContextualMenu) End"  << endl; 
#endif     
}

// ---------------------------------------------------------------------------------------------
// Contextual Menu /Activate Contexctual Menu 
// ---------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::ContextualMenuActivation(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData data)
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::ContextualMenuActivation) "  << endl; 
#endif 
	// Handle input parameter 

	CATDlgContextualMenu* Ctx        = (CATDlgContextualMenu*) fromClient;
	CATDlgSelectorList* Select       = (CATDlgSelectorList*) data; // casting of data
	CATUnicodeString StartUpType     = "";


	if (Ctx->GetVisibility()==CATDlgShow) 
	{

		SetSelect() ; 
	
		// Item to Clear Selection for Directions
		if (_pCurrentFeature) {
			CATDlgPushItem * Item = new CATDlgPushItem (Ctx,"Clear Selection");
			AddAnalyseNotificationCB(Item, Item->GetMenuIActivateNotification(), (CATCommandMethod)& CAAGSMFrmSelectorCtx::AnalyseNotifs,(CATCommandClientData) CLEAR);
			new CATDlgSeparatorItem(Ctx,"Separator");
		}


		// If the Feature exists, if Feature is not Infinite, If it is not a BRep
		// we offer the possibility to Edit it by the mean of an item in Contextual Menu
		CATIMfBRep_var spBrepSpec = _pCurrentFeature;

		if (_pCurrentFeature && !(IsAnInfiniteFeature(_pCurrentFeature)) && !spBrepSpec) {

			// Edit Item ? 
			// ------------------------------------------------
			// Is Feature contextual ? 
			// 1/ Feature to edit is contextuel , NEC  he is aggregated under a feature 
			// 2/ The current feature is the feature created/edited by the current command (FatherCommand->GiveByFeature) 
			// and  is "logically"  the father of the feature to edit 

			// Current Feature within the command 
			CATISpecObject_var ispCurrentCmdFeature ; 
			if (_iFatherCmd != NULL ) { 
				ispCurrentCmdFeature = _iFatherCmd -> GiveMyFeature() ;
			} 

			// Father of Edited Feature 
			CATISpecObject_var  spFatherOfFeatureToEdit; 
			CATISpecObject * pFatherFtr  = _pCurrentFeature->GetFather();
			if (NULL!= 	pFatherFtr) { 
				spFatherOfFeatureToEdit =  pFatherFtr ;
				pFatherFtr-> Release() ; pFatherFtr = NULL; 
			}


			// If feature to edit is not a BRep but is aggregated untder the current feature IT IS A CONTEXTUAL Feature 
			if 	(  (NULL_var != spFatherOfFeatureToEdit          )    && 
				   (spFatherOfFeatureToEdit ==  ispCurrentCmdFeature)      )  { 

				CATISpecObject * start = _pCurrentFeature->GetStartUp();
				CATIIcon_var spIcon = start; 
				if (start) {
					StartUpType = start->GetName();

					// Icon Name 
					CATIIcon_var spIcon = start;
					CATUnicodeString IconName ; 
					spIcon ->GetIconName(IconName);  

					// Menu Edit 
					ItemContextualMenu ( "Edit", IconName   ,StartUpType, 1 , Ctx );

					if(start) {start->Release(); start = NULL;}
				}                
				
			}
		}
		//if (NULL!= _pCurrentFeature) { _pCurrentFeature->Release(); _pCurrentFeature = NULL; }


		// Usual Items of Menu  
		// ------------------------------------------------------------
		InitContextualItems(Ctx) ;
	}
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::ContextualMenuActivation) End "  << endl; 
#endif 

}

// ---------------------------------------------------------------------------------------------
// Contextual Menu /Selection of an Item in Contextual Menu 
// ---------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::ContextualMenuSelection(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData data)
{	
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::ContextualMenuSelection) "  << endl; 
#endif 
	HRESULT rc = S_OK;

	CAAGSMFrmCtxMenuInfoUser     * pUserInfo  = (CAAGSMFrmCtxMenuInfoUser *) data; 
	CATGSMUICmdInfo * info  = NULL ;
	int               Edt   = 0 ; 
	if (pUserInfo!=NULL) { 
		info  =  pUserInfo  -> GetCmdInfo  ()  ; 
		Edt   =  pUserInfo  -> GetEditMode (); 
	}  

	if(info)
	{

		////##################### WARNING ################################################
		//// In this Sample we have decided to have a standard GSD behavior:
		//// 1- We support Aggregation in the Model
		//// 2- We automatically aggregate feature created by the mean of contextual menus
		//// 3- We consider that ONLY Contextual Features are editable


		boolean IsToEdit = FALSE;
		// int edit = info->GetContextualFeaturesAggregMode();
		// if(edit==0) IsToEdit = TRUE;
		if(Edt==1) IsToEdit = TRUE;
		////##############################################################################


		// Retrieve Part
		// Looking for the part within the UI active object
		CATIPrtPart    * piPrtPart  = NULL;
		CATFrmEditor   *  editor       = CATFrmEditor::GetCurrentEditor();
		if (NULL != editor ) {
			CATPathElement PathAct =  editor->GetUIActiveObject();
			rc = PathAct.Search(IID_CATIPrtPart,(void**)&piPrtPart) ;
		}  

		// Retrieve GSD Factory 
		// asks a pointer on CATISpecObjet on the part
		CATIGSMUIFactory_var Facto    = NULL_var ;
		if ( SUCCEEDED(rc) && ( NULL!=piPrtPart) )
		{
			CATISpecObject *piSpecOnPart = NULL;

			piPrtPart->QueryInterface( IID_CATISpecObject, ( void**) &piSpecOnPart );
			if (NULL  != piSpecOnPart) { 

				// retrieves part feature container
				CATIContainer_var spContainer = piSpecOnPart->GetFeatContainer();
				if (NULL_var != spContainer) { 
					Facto    = spContainer ;
				}
				piSpecOnPart->Release();    piSpecOnPart = NULL ;
			}       
			piPrtPart ->Release(); piPrtPart = NULL ;
		}
		CATCommand * MyCmd = NULL;

		// Contextual menu 
		if(!!Facto) {
			if (IsToEdit)  {
				// Edit 
				// we are editing the feature  by the mean of the contextual menu
				CATISpecObject_var spEdited =  _pCurrentFeature; 
				MyCmd = Facto -> EditCommand(spEdited,"CATIGSMUICommandEdit", NULL, CATCommandModeShared); 

			}
			else  {
				// Creation 
				// we are creating a feature by the mean of the contextual menu
				// !! Warning: Temporary flag for Aggregation is set to one  
				// => Need to support aggregation of contextual feature for the current feature in the model 
				MyCmd = Facto -> CreationCommand(info,"CATGSMUICommandCreation", NULL, CATCommandModeShared);

			}
		}


	}

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMFrmSelectorCtx::ContextualMenuSelection) End "  << endl; 
#endif 
}



//---------------------------------------------------------------------------------------------------
// Contextual Menu / IsAnInfiniteFeature() : Check if feature selected is not  infinite for edit 
//---------------------------------------------------------------------------------------------------
CATBoolean CAAGSMFrmSelectorCtx::IsAnInfiniteFeature(CATISpecObject * Feat)
{
	boolean returnCode = FALSE;
	HRESULT rc = E_FAIL; 
	if (NULL != Feat) { 
		// queries the interface CATIGeometricalElement on the Feature selected
		CATIGeometricalElement * piGeometricalElement = NULL;
		rc = Feat->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElement );

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



//---------------------------------------------------------------------------------------------------
// Selector / Set select 
//---------------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::SetSelect()
{
	// cout <<"(CAAGSMFrmSelectorCtx::SetSelect)  "  <<endl ; 
	CATUnicodeString FirstLine[1]; 
	_sel_selector->GetLine(FirstLine[0], 0);
	_sel_selector->SetSelect(FirstLine,1,0);	
}

//---------------------------------------------------------------------------------------------------
// Selector / Clear Select 
//---------------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::ClearSelect()
{
	// cout <<"(CAAGSMFrmSelectorCtx::ClearSelect)  "  <<endl ; 
	_sel_selector->ClearSelect();
}

//---------------------------------------------------------------------------------------------------
// Selector / get dialog widget 
//---------------------------------------------------------------------------------------------------
CATDlgSelectorList* CAAGSMFrmSelectorCtx::GetEditor()
{
	// cout <<"(CAAGSMFrmSelectorCtx::GetEditor)  "  <<endl ; 
	return _sel_selector;
}


//---------------------------------------------------------------------------------------------------
// Selector / get dialog label 
//---------------------------------------------------------------------------------------------------
CATDlgLabel* CAAGSMFrmSelectorCtx::GetLabel()
{
	// cout <<"(CAAGSMFrmSelectorCtx::GetEditor)  "  <<endl ; 
	return _label_dlg;
}

//---------------------------------------------------------------------------------------------------
// Selector / Launch Clear notification 
//---------------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::SetClearNotification(CATNotification * Notif )
{
	_DlgClearSelection=  Notif; 
}

//---------------------------------------------------------------------------------------------------
// Selector / Get Selection notification 
//---------------------------------------------------------------------------------------------------
CATNotification* CAAGSMFrmSelectorCtx::GetSelectNotification()
{
	CATNotification *	rcnotif = NULL;
	if ( _sel_selector) 
		rcnotif = _sel_selector->GetListSelectNotification();
	return rcnotif;
}

//---------------------------------------------------------------------------------------------------
// Selector / Send selection notification to selector dialog panel father 
//---------------------------------------------------------------------------------------------------
HRESULT CAAGSMFrmSelectorCtx::Select()
{
	HRESULT rc = CATReturnFailure;
	if(_sel_selector)
	{
		_sel_selector->SendNotification(GetFather(),_sel_selector->GetListSelectNotification());
		rc = CATReturnSuccess;
	}
	return rc;
}

//---------------------------------------------------------------------------------------------------
// Selector / Send notification 
//---------------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::SendNotif(CATCommand *c, CATNotification *n, CATCommandClientData d)
{
	// on simule le clic dans le champ
	if(_sel_selector) 
	{
		CATCommand * pFather = GetFather();
		if (pFather)
		{
			_sel_selector ->SendNotification(pFather,_sel_selector->GetListSelectNotification());
			// on demande le traitement immediat de la notif
			pFather -> ReceiveNotification(_sel_selector,_sel_selector->GetListSelectNotification());
		}
	}
}

//---------------------------------------------------------------------------------------------------
// Selector / Check selector selection status 
//---------------------------------------------------------------------------------------------------
CATBoolean CAAGSMFrmSelectorCtx::IsSelected() 
{ 
	CATBoolean rc = CATFalse;
	if (_sel_selector)
	{
		if (0 != _sel_selector -> GetSelectCount())
			rc = CATTrue;
	}

	return rc;
}

//---------------------------------------------------------------------------------------------------
// Selector / Initialize selector with a feature 
//---------------------------------------------------------------------------------------------------
void CAAGSMFrmSelectorCtx::SetFeature(const CATISpecObject_var ihFtr, CATBoolean ibCleanHSO)
{

	int RetStatus = 0 ; 
	if (_sel_selector)	 {

		int nbsel = _sel_selector -> GetSelectCount();

		//Affichage du texte
		if ( NULL_var != ihFtr) {
			
			// Update current feature // QI to add ref on the spec object 
			CATISpecObject * piSpecObj = NULL; 
			HRESULT rc =ihFtr->QueryInterface ( IID_CATISpecObject, (void**) &piSpecObj );
			if ( SUCCEEDED(rc) ) { 

				// Is it a New Feature ? / previous one 
				if (! (piSpecObj ->IsEqual( (CATBaseUnknown *) _pCurrentFeature)) )  { 
					{
							
				     	// Reset Current feature before changes
						if ( NULL != _pCurrentFeature ) {
							_pCurrentFeature -> Release() ; _pCurrentFeature = NULL;
						} 

						// Upgrade Current feature reference (Release to be done in class destructor) 
						_pCurrentFeature = piSpecObj;


						// MAJ Panel Field 
						CATBaseUnknown_var IFtrBase (_pCurrentFeature); 
						CATUnicodeString  texte =  CAAGsiGetSpecDisplayName(IFtrBase);
						_sel_selector->SetLine(texte,0,CATDlgDataModify);
					}

				}
				else { 
					piSpecObj -> Release () ; 
					piSpecObj=NULL; 
				}
			}
		}
		else {

			// Reset Current feature 
			if (NULL !=  _pCurrentFeature ) {
				_pCurrentFeature -> Release() ; _pCurrentFeature = NULL;     
			}	

			// MAJ Panel Field 
			CATUnicodeString Prompt_nosel = "no selection";
			_sel_selector->SetLine(Prompt_nosel,0,CATDlgDataModify);


		}
		
		// Set up Field as  selected 
		if (nbsel>0) 		SetSelect();

	}
}
