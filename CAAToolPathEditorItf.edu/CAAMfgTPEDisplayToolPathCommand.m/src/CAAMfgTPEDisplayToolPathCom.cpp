// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAMfgTPEDisplayToolPathCom:
//
// Sample code for : CAA Manufacturing
// Mission         : Display tool path in Tool Path Editor.
//
// Type            : Interactive functionality
//
// How to run it   : 1-You need the Use Case CAAMfgTPEDisplayToolPathCommand 
//                     You can add this new command in the tool abr decribed in use-case CAATPEAddToolBar
//                   2-Build the CAAMfgTPEDisplayToolPathCommand library.
//                     In this library there is the code that defines a command which display a selection
//                     of tool pathes.
//                     You need to generate all the Use Cases of the framework CAAToolPathEditorItf.edu
//                   3-Create the runtime view.
//					 4-Launch CATIA.
//                   5-Enter in Surfacic machining workbench in NC Manufacturing workshop.
//                   6-Create a new activity and do the replay.
//                   6-Click on the "Display tool pathes" Command
//                   7-Select an icon of tool path in the tree.
//					 8- Double-click in the 3d viewer to end the command, or click on the command 
//
//=============================================================================
//
// Interfaces CATIA
#include "CATISpecObject.h"
#include "CATString.h"

#include "CATPathElementAgent.h"
#include "CATPathElement.h"

// Interfaces Mfg
#include "CATIMfgActivity.h"
#include "CATIMfgToolPath.h"
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathFactory.h"
#include "CATIMfgToolPathComponents.h"
#include "CATIMfgToolPathManagement.h"
#include "CATIMfg3DToolPathVisu.h"
#include "CATIMfg3DToolPathVisuData.h"

#include "CATFrmLayout.h"
#include "CATFrmWindow.h"
#include "CATFrmGraphAnd3DWindow.h"
#include "CATVisManager.h"

#include "CAT3DViewpoint.h"

#include "CAT3DViewer.h"
#include "CATEdit.h"
#include "CATModify.h"
#include "CATIModelEvents.h"
#include "CATSO.h"
#include "CATIContainer.h"

#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgToolPathFactory.h"
#include "CATIMfgToolPathComponents.h"

#include "CAAMfgTPEDisplayToolPathCom.h" 

#include "CATInstantiateComponent.h"
#include "LifeCycleObject.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg( CAAMfgTPEDisplayToolPathCom,CATString);

//========================================================================
// Constructor
//========================================================================
CAAMfgTPEDisplayToolPathCom::CAAMfgTPEDisplayToolPathCom( CATString* argument) :
  CATStateCommand ((*argument), CATDlgEngOneShot, CATCommandModeExclusive),
	_ToolPahVisu(NULL), _TPSelectionAgent(NULL), _TPEndAgent(NULL),
    _iid(NULL), 
	_VisuManager(NULL),  _Viewer(NULL)
{
	_ToolPath=NULL_var;

	CATFrmLayout* ptrFrmLayout = CATFrmLayout::GetCurrentLayout();
	if ( ptrFrmLayout) {
		const CATFrmWindow * ptrFrmWindow = ptrFrmLayout->GetCurrentWindow () ;
		if (ptrFrmWindow && ptrFrmWindow->IsAKindOf(CATFrmGraphAnd3DWindow::ClassName()) ) {
			CATFrmGraphAnd3DWindow* ptr3DWindow = (CATFrmGraphAnd3DWindow*)ptrFrmWindow;
			CATViewer * viewer = ptr3DWindow->GetGraphicViewer();
			if( viewer && viewer->IsAKindOf(CAT3DViewer::ClassName()) ) 
				_Viewer = (CAT3DViewer*)viewer;
		}
	}
}

//========================================================================
// Destructor
//========================================================================
CAAMfgTPEDisplayToolPathCom::~CAAMfgTPEDisplayToolPathCom()
{	
	// Clean Controller
	DeleteController();

	// Delete dialog agents
    if (_TPSelectionAgent) {_TPSelectionAgent->RequestDelayedDestruction();_TPSelectionAgent=NULL;};
	if (_TPEndAgent) {_TPEndAgent->RequestDelayedDestruction();_TPEndAgent=NULL;};

    // Delete temporary compound traject
    CATIMfgToolPathComponents_var hComponents (_ToolPath);
    if (!!hComponents)
    {
        hComponents->RemoveAll(); 
        LifeCycleObject_var hToolPathLife = _ToolPath;
	    if (!! hToolPathLife)
		    hToolPathLife->remove();
    }
	_ToolPath=NULL_var;

	_Viewer=NULL;
}

//========================================================================
// Build Graph
//========================================================================
void CAAMfgTPEDisplayToolPathCom::BuildGraph()
{  
	_TPSelectionAgent = new CATPathElementAgent("ToolPathSelection");
	if (NULL != _TPSelectionAgent) {
		_TPSelectionAgent->SetOrderedElementType(CATIMfgCompoundTraject::ClassName());
		_TPSelectionAgent->AddOrderedElementType(CATIMfgActivity::ClassName());
		_TPSelectionAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngMultiAcquisition);
		AddCSOClient(_TPSelectionAgent);
	}

	if ( _TPEndAgent == NULL ) {
		_TPEndAgent = new CATDialogAgent("End");
		if (NULL != _TPEndAgent)
			_TPEndAgent->AcceptOnNotify(NULL, CATEdit::ClassName());
	}


	CATDialogState* firstState = GetInitialState("TPESelectToolPath");
	if (NULL != firstState) firstState->AddDialogAgent(_TPSelectionAgent); 

	CATDialogState* secondState = AddDialogState("TPEEndCommand");
	if (NULL != secondState)
		secondState->AddDialogAgent(_TPEndAgent); 

    CATDialogTransition * firstTransition = 
        AddTransition (firstState, secondState,
                       IsOutputSetCondition(_TPSelectionAgent),
                       Action((ActionMethod) &CAAMfgTPEDisplayToolPathCom::GetSelection));

    AddTransition (secondState, NULL,
                   IsOutputSetCondition(_TPEndAgent),
                   Action((ActionMethod) &CAAMfgTPEDisplayToolPathCom::End));
}

//========================================================================
// End : To Terminate the command
//========================================================================
boolean CAAMfgTPEDisplayToolPathCom::End (void* data)
{
   RequestDelayedDestruction();
   return (CATTrue);
}

//===========================================================================
// CreateController : to Create the rep of the tool path
//===========================================================================
void CAAMfgTPEDisplayToolPathCom::CreateController()
{
	if (!!_ToolPath) {
		CATIMfg3DToolPathVisuData_var VisuData (_ToolPath);
		if (!!VisuData)
			HRESULT RC = VisuData->SetDisplayMode(0);

		_VisuManager = CATVisManager::GetVisManager();

		_iid = new IID ( CATIMfg3DToolPathVisu::ClassId() ); 
		list<IID> listIID;
		listIID.fastadd (_iid);

		CATBaseUnknown_var ModelRoot (_ToolPath);

		_ToolPahVisu = new CATPathElement (ModelRoot);

		if (_Viewer != NULL) {
			CAT3DViewpoint *Viewpoint = &(_Viewer->GetMain3DViewpoint());
			if (NULL != _VisuManager)
				_VisuManager->AttachTo (_ToolPahVisu,Viewpoint,listIID,this);
		}
	}
}

//===========================================================================
// DeleteController : Delete the rep of the tool path
//===========================================================================
void CAAMfgTPEDisplayToolPathCom::DeleteController()
{
	if (_ToolPahVisu) {
      if (NULL != _VisuManager)
			_VisuManager->DetachFrom (_ToolPahVisu);
	  _ToolPahVisu->Release();
	  _ToolPahVisu = NULL;
	}

	if (_iid) 
	  delete _iid;
	_iid = NULL;

	DispatchInfo();
	_VisuManager = NULL;
}

//===========================================================================
// DispatchInfo : To update the rep of the tool path
//===========================================================================
void CAAMfgTPEDisplayToolPathCom::DispatchInfo() 
{
	if(!!_ToolPath) {
		CATISpecObject_var objet (_ToolPath);
		if (!!objet) {
			CATModify Info (objet->GetImpl());
			CATIModelEvents_var Evt (_ToolPath);
			if (!!Evt)
				Evt->Dispatch(Info);
		}
	}
}

//========================================================================
// GetSelection : To get the tool path
//========================================================================
boolean CAAMfgTPEDisplayToolPathCom::GetSelection (void* data)
{ 
	CATBoolean RESULT = CATFalse;

	CATSO* selectedObjects = NULL;
	if (NULL != _TPSelectionAgent)
		selectedObjects = _TPSelectionAgent->GetListOfValues();
	
	if ( selectedObjects ) {
		int NbPath = selectedObjects->GetSize();
		if ( NbPath > 0 ) {

			RESULT = CATTrue;

			// We must create a new MfgCompoundTraject.
			// He will contain all the selected tool pathes.
			// The structure must be like this 
			// 
			// MfgCompoundTraject -
			//                    MfgCompoundTraject 1 -
			//														 MfgMultipleMotion
			//                    MfgCompoundTraject 2
			//														 MfgMultipleMotion
			// 
			//                    MfgCompoundTraject n
			//														 MfgMultipleMotion
			// only one MfgMultipleMotion by MfgCompoundTraject.
			if (NULL_var ==  _ToolPath ) {
				CATIContainer_var spContainer = NULL_var;
				GetToolPathFactory (spContainer);
				if (NULL_var != spContainer) { 
					CATIMfgToolPathFactory_var spTPFactory = spContainer;
					_ToolPath = spTPFactory->CreateMfgCompoundTraject ();
				}
			}
			
			CATIMfgToolPathComponents_var itfComponents (_ToolPath);
			if ( !!_ToolPath && !!itfComponents ) {

				CATPathElement* ptrCurrentElement=NULL;

				CATIMfgCompoundTraject* ptrCTraject=NULL;
				CATIMfgCompoundTraject_var itfCmpTraject;

				CATIMfgActivity* ptrActivity=NULL;
				CATIMfgActivity_var itfActivity;

				for ( int ind=0;  ind < NbPath ; ind++) {

					ptrCurrentElement = (CATPathElement*) (*selectedObjects)[ind];
					if (NULL != ptrCurrentElement) {

						// suppression de l'element
						ptrCTraject = (CATIMfgCompoundTraject *) (ptrCurrentElement->FindElement(CATIMfgCompoundTraject::ClassId()));
						itfCmpTraject = ptrCTraject;

						if (!! itfCmpTraject ) {
							// A Compound traject is selected.
							ptrCTraject->Release();
							itfComponents->AddElement(itfCmpTraject,0);
							ptrCTraject=NULL;
						}
						else {
							// An activity is selected.
							// We add all her tool pathes.
							ptrActivity = (CATIMfgActivity *) (ptrCurrentElement->FindElement(CATIMfgActivity::ClassId()));
							itfActivity = ptrActivity;
							if (!!itfActivity ) {
								ptrActivity->Release();
								CATIMfgToolPathManagement_var itfManagement = itfActivity;
								CATIMfgToolPath_var ToolPath(NULL_var);
								if (!!itfManagement)
									HRESULT RC = itfManagement->GetToolPath(ToolPath);
								itfComponents->AddElement(ToolPath,0);
								ptrActivity=NULL;
							}
						}
						
						ptrCurrentElement=NULL;

					}
				}

				// Display the tool path.
				CreateController();
				DispatchInfo();
			}
		}
	}

	return RESULT;
}

//========================================================================
//  GetToolPathContainer : To Get the container of tool pathes.
//========================================================================
HRESULT CAAMfgTPEDisplayToolPathCom::GetToolPathFactory(CATIContainer_var& oContainer)
{
	HRESULT RC = S_OK;
	oContainer = NULL_var;
	
	CATTry
	{
		CATIMfgManufacturingFactories *piFact=NULL;

		CATString ClassName("CATMfgManufacturingFactories");
		CATInstantiateComponent(ClassName,
										CATIMfgManufacturingFactories::ClassId(),
										(void**) &piFact);

		if ( NULL != piFact)
		{
			HRESULT Res = piFact->GetManufacturingToolPathFactory (oContainer);	
			piFact->Release();
		} 
	}

	CATCatch (CATError,Error)
	{
		if (NULL != Error)
			Error->CATSetLastError ();
		RC = E_FAIL;
	}
	
	CATEndTry;
	return RC;
}

//========================================================================
// Valuate: Internal tests
//========================================================================
void CAAMfgTPEDisplayToolPathCom::Valuate (const CATBaseUnknown_var& iValue)     
{
	if ( !iValue ) {
		End(NULL);
	}
	else if ( iValue->IsAKindOf("CATIMfgToolPath") ) {
		if (_TPSelectionAgent)  {
			CATSO* so = new CATSO();
			CATPathElement* path = new CATPathElement (iValue);
			so->AddElement(path);
			_TPSelectionAgent->SetListOfValues (so);
			_TPSelectionAgent->SetValuation();
			_TPSelectionAgent->Accept();
			path->RemoveElement(iValue);
			path->Release();
			so->Release();
		}
	}
}










