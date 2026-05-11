// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAMfgTPESplitToolPathCom:
//
// Sample code for : CAA Manufacturing
// Mission         : Split a toolpath
//
// Type            : Interactive functionality
//
// How to run it   : 1-You need the Use Case CAAMfgTPESplitToolPathCommand 
//                     You can add this new command in the tool as decribed in use-case CAATPEAddToolBar
//                   2-Build the CAAMfgTPESplitToolPathCommand library.
//                     You need to generate all the Use Cases of the framework CAAToolPathEditorItf.edu
//                   3-Create the runtime view.
//					 4-Launch CATIA.
//                   5-Enter in Surfacic machining workbench in NC Manufacturing workshop.
//                   6-Create a new activity and do the replay.
//                   7-Select the tool path and click on the icon representing the command "Split tool path". A tool path is displayed, with points.
//                   8-Select a point on the tool path. Then this tool path is splitted and two tool pathes appear in the PPR Tree..
//
//=============================================================================
//
#define CAAEpsilon .001


// Includes
#include "CAAMfgTPESplitToolPathCom.h" 

// Interfaces CATIA
#include "CATISpecObject.h"
#include "CATString.h"

#include "CATPathElementAgent.h"
#include "CATPathElement.h"

// Interfaces Mfg.
#include "CATIMfgActivity.h"
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgTPMultipleMotion.h"
#include "CATIMfgToolPathComponents.h"
#include "CATIMfgTPTransformation.h"
#include "CATIMfgTPSaveData.h"

#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgToolPathFactory.h"

#include "CATIMfg3DToolPathVisu.h"
#include "CATIMfg3DToolPathVisuData.h"

#include "CATFrmEditor.h"
#include "CATFrmLayout.h"
#include "CATFrmWindow.h"
#include "CATFrmGraphAnd3DWindow.h"
#include "CATVisManager.h"

#include "CAT3DViewpoint.h"
#include "CATIRedrawEvent.h"
#include "CAT3DViewer.h"
#include "CATEdit.h"
#include "CATModify.h"
#include "CATIModelEvents.h"
#include "CATSO.h"

#include "CATIContainer.h"

#include "CATSelector.h"
#include "CATRep.h"
#include "CAT3DPointRep.h"
#include "CATGraphicElementIntersection.h"

#include "CATMathPoint.h"
#include "CATInstantiateComponent.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg( CAAMfgTPESplitToolPathCom,CATString);

//========================================================================
// Constructor
//========================================================================
CAAMfgTPESplitToolPathCom::CAAMfgTPESplitToolPathCom( CATString* argument) :
  CATStateCommand ((*argument), CATDlgEngOneShot, CATCommandModeExclusive),
	_ToolPahVisu(NULL), _TPSelectionAgent(NULL), _TPEndAgent(NULL),
    _iid(NULL), _PointNumber(-1), _Selector(NULL),	_CurrentPointRep(NULL),
	_VisuManager(NULL),  _Viewer(NULL), _TPRep(NULL)
{
	_Activity=NULL_var;
	_ToolPath=NULL_var;
	_TPMultipleMotion=NULL_var;
	
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
CAAMfgTPESplitToolPathCom::~CAAMfgTPESplitToolPathCom()
{	
	RemovePointRep();

	DeleteController();

	if (_TPSelectionAgent) {_TPSelectionAgent->RequestDelayedDestruction();_TPSelectionAgent=NULL;};
	if (_TPEndAgent) {_TPEndAgent->RequestDelayedDestruction();_TPEndAgent=NULL;};
	if (_Selector) {_Selector->RequestDelayedDestruction();_Selector=NULL;};

	_Activity=NULL_var;
	_ToolPath=NULL_var;
	_TPMultipleMotion=NULL_var;
	_CurrentPointRep=NULL;
	_TPRep=NULL;

	_Viewer=NULL;

}

//========================================================================
// Build Graph
//========================================================================
void CAAMfgTPESplitToolPathCom::BuildGraph()
{  
	// To Select tool path.
	_TPSelectionAgent = new CATPathElementAgent("ToolPathSelection");
	if (NULL != _TPSelectionAgent) {
		_TPSelectionAgent->SetOrderedElementType(CATIMfgCompoundTraject::ClassName());
		_TPSelectionAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngMultiAcquisition);
		AddCSOClient(_TPSelectionAgent);
	}

	// To terminate the command
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
                       Action((ActionMethod) &CAAMfgTPESplitToolPathCom::GetSelection));

    AddTransition (secondState, NULL,
                   IsOutputSetCondition(_TPEndAgent),
                   Action((ActionMethod) &CAAMfgTPESplitToolPathCom::End));
}

//========================================================================
// End : To Terminate the command
//========================================================================
boolean CAAMfgTPESplitToolPathCom::End (void* data)
{
   RequestDelayedDestruction();
   return (CATTrue);
}

//===========================================================================
// CreateController : Create the rep of the tool path
//===========================================================================
void CAAMfgTPESplitToolPathCom::CreateController()
{
	if (!!_ToolPath) {

		// We initialize how the tool path will be displayed
		CATIMfg3DToolPathVisuData_var VisuData (_ToolPath);
		int DisplayTPWithPoints =1;
		if (!!VisuData)
			HRESULT RC = VisuData->SetDisplayMode(DisplayTPWithPoints);

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
// DeleteController ;  Delete the rep of the tool path
//===========================================================================
void CAAMfgTPESplitToolPathCom::DeleteController()
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
void CAAMfgTPESplitToolPathCom::DispatchInfo() 
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
boolean CAAMfgTPESplitToolPathCom::GetSelection (void* data)
{ 
	CATBoolean RESULT = CATFalse;

	CATSO* selectedObjects = NULL;
	if (NULL != _TPSelectionAgent)
		selectedObjects = _TPSelectionAgent->GetListOfValues();
	
	// We display only one tool path in this command
	if ( selectedObjects ) {
		if ( selectedObjects->GetSize() == 1 ) {

			CATPathElement* pathElement=NULL;

			CATIMfgCompoundTraject* ptrCTraject=NULL;
			CATIMfgCompoundTraject_var itfCmpTraject;

			pathElement = (CATPathElement*) (*selectedObjects)[0];
			if (NULL != pathElement) {

				// A CATIMfgCOmpoundTraject must have been seletecd
				ptrCTraject = (CATIMfgCompoundTraject *) (pathElement->FindElement(CATIMfgCompoundTraject::ClassId()));
				itfCmpTraject = ptrCTraject;

				if (!! itfCmpTraject ) {
					_ToolPath = itfCmpTraject;

					CATIMfgToolPathComponents_var itfComponents =_ToolPath;
					CATListValCATBaseUnknown_var* Liste = NULL;
					if (!!itfComponents) Liste = itfComponents->GetAllElements();

					if ( Liste )
					{
						_TPMultipleMotion = (*Liste)[1];
						delete Liste;
					}

					ptrCTraject->Release();
					ptrCTraject=NULL;
					RESULT = CATTrue;

					// We get the activity to be able to redraw the tree under the corresponding activity.
					CATIMfgActivity* ptrActivity = (CATIMfgActivity *) (pathElement->FindElement(CATIMfgActivity::ClassId()));
					if (NULL != ptrActivity ) {
						_Activity = ptrActivity;
						ptrActivity->Release();
						ptrActivity=NULL;
					}
				}
				
				pathElement=NULL;
			}

			// Display the tool path.
			CreateController();
			DispatchInfo();
			// To Select points.
			SetSelector();

		}
	}

	return RESULT;
}

//===========================================================================
// SetSelector : create the selector of points
//===========================================================================
void CAAMfgTPESplitToolPathCom::SetSelector() 
{
	// To get the rep of the points
	CATIMfg3DToolPathVisuData_var VisuData (_ToolPath);
	if (!! VisuData) { 
		if ( SUCCEEDED(VisuData->GetPointsRep(&_TPRep) ) ) {

			if ( _Selector == NULL ) {
				_Selector = new CATSelector (this,"ToolPathSelector", _TPRep);
				AddAnalyseNotificationCB ( _Selector,
													_Selector->GetCATPreactivate(),
													(CATCommandMethod)&CAAMfgTPESplitToolPathCom::PreActivate,NULL);
				AddAnalyseNotificationCB ( _Selector,
													_Selector->GetCATActivate(),
													(CATCommandMethod)&CAAMfgTPESplitToolPathCom::ActivateSelector,NULL);
				AddAnalyseNotificationCB ( _Selector,
													_Selector->GetCATMove(),
													(CATCommandMethod)&CAAMfgTPESplitToolPathCom::Move,NULL);
				AddAnalyseNotificationCB ( _Selector,
													_Selector->GetCATEndPreactivate(),
													(CATCommandMethod)&CAAMfgTPESplitToolPathCom::EndPreActivate,NULL);
			}
			else {
				_Selector->AssociateToRep(_TPRep);
			}
		}
	}
}

//===========================================================================
// PreActivate :To process the preactivate event. 
//===========================================================================
void CAAMfgTPESplitToolPathCom::PreActivate (CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{
	EndPreActivate (c1,c2,c3);

	CATGraphicElementIntersection* Intersection = NULL;
	if (NULL != _Selector)
	{
		Intersection = (CATGraphicElementIntersection*) 
							_Selector->SendCommandSpecificObject (CATGraphicElementIntersection::ClassName(), c2);
	}
	if (!Intersection) return;

	CATMathPoint point = Intersection->point;
	Intersection->Release();

	// we create a rep of the selected point.
	_CurrentPointRep = new CAT3DPointRep (point,FULLSQUARE);
	if ( _Viewer ) _Viewer->AddRep(_CurrentPointRep);
 	
}

//===========================================================================
// ActivateSelector : To process the selection of a point.
//===========================================================================
void CAAMfgTPESplitToolPathCom::ActivateSelector(CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{	
	CATGraphicElementIntersection* Intersection = NULL;
	if (NULL != _Selector) 
	{
		Intersection = (CATGraphicElementIntersection*) 
					  _Selector->SendCommandSpecificObject (CATGraphicElementIntersection::ClassName(), c2);
	}

	// Only for internal Use.
	CATMathPoint* mathPoint = (CATMathPoint *)c3;
	if ( NULL == Intersection )
	{
		if ( NULL  != mathPoint)
		{
			Intersection = new CATGraphicElementIntersection(*mathPoint);
		}
	}
	// 

	if (!Intersection) return;
	CATMathPoint point = Intersection->point;
	Intersection->Release();

	SetPreActivatedPoint(point);
   
	// To split the tool path at the selected point.
	if ( SplitToolPath() )
		End(NULL);
}

//===========================================================================
// SplitToolPath : To split the tool path.
//===========================================================================
boolean CAAMfgTPESplitToolPathCom::SplitToolPath()
{	
	boolean isSplit=FALSE;

	if ( !! _TPMultipleMotion ) {
		if ( _PointNumber > 1 && _PointNumber < _TPMultipleMotion->GetNumberOfTipPoints() ) {
			CATIMfgTPTransformation_var itfTransformation (_TPMultipleMotion);
			if (!! itfTransformation) {
				CATIMfgTPMultipleMotion_var MultipleMotion2 (NULL_var);
				if ( itfTransformation->Split (_PointNumber,MultipleMotion2) ) {

					// To Store the datas int the model.
					CATIMfgTPSaveData_var itfSaveData1 = _TPMultipleMotion;
					if ( !!itfSaveData1)
						itfSaveData1->SaveData ();
					CATIMfgTPSaveData_var itfSaveData2 = MultipleMotion2;
					if ( !!itfSaveData2)
						itfSaveData2->SaveData ();
					
					// We must create two new MfgCompoundTraject.
					// Each will have only one MfgpMultipleMotion.
					// At the end, we must have
					// MfgCompoundTraject -
					//                    MfgCompoundTraject 1 -
					//														 MfgMultipleMotion
					//                    MfgCompoundTraject 2
					//														 MfgMultipleMotion
					CATIMfgToolPathFactory_var spTPFactory;
					CATIContainer_var spContainer;
					GetToolPathFactory (spContainer);
					spTPFactory = spContainer;

					CATIMfgCompoundTraject_var itfCompound1=NULL_var;
					CATIMfgCompoundTraject_var itfCompound2=NULL_var;

					if (NULL_var!=spTPFactory) {
						itfCompound1 = spTPFactory->CreateMfgCompoundTraject ();
						itfCompound2 = spTPFactory->CreateMfgCompoundTraject ();

						//piToolPathFactory->Release();

						CATIMfgToolPathComponents_var itfComponents1(itfCompound1);
						if ( !! itfComponents1 )
							itfComponents1->AddElement(_TPMultipleMotion);

						CATIMfgToolPathComponents_var itfComponents2(itfCompound2);
						if ( !! itfComponents2 )
							itfComponents2->AddElement(MultipleMotion2);

						CATIMfgToolPathComponents_var itfComponents(_ToolPath);
						if ( !! itfComponents && !! itfComponents1 && !! itfComponents2 ) {
							isSplit = TRUE;

							// To mark each MfgCompoundTraject as a sub tool path
							itfCompound1->SetSubToolPathFlag(CATTrue);
							itfCompound2->SetSubToolPathFlag(CATTrue);

							itfComponents->RemoveAll();
							itfComponents->AddElement(itfCompound1);
							itfComponents->AddElement(itfCompound2);

							// To display these two tool path in the tree.
							if ( !!_Activity ) {
								CATIRedrawEvent_var Event(_Activity->GetImpl());
								if (!!Event) Event->Redraw();
							}
						}

					}
				}
			}
		}
	}
	return isSplit;
}

//===========================================================================
// Move : Processing of the move event.
//===========================================================================
void CAAMfgTPESplitToolPathCom::Move (CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{	
	PreActivate (c1,c2,c3);
}

//===========================================================================
// EndPreActivate : End of the preactivate event.
//===========================================================================
void CAAMfgTPESplitToolPathCom::EndPreActivate (CATCommand*, CATNotification*, CATCommandClientData)
{
	RemovePointRep();

	if (_Viewer) 
		_Viewer->Draw();
}

//===========================================================================
// SetPreActivatedPoint : To search the index of the selected point
//===========================================================================
void CAAMfgTPESplitToolPathCom::SetPreActivatedPoint (CATMathPoint &Point)
{
   _PointNumber   = 0;
   double distance, distance2;

   if ( !! _TPMultipleMotion ) 
	{
		int NbPoint=1;
		double x,y,z;
		_TPMultipleMotion->GetTipPoint (NbPoint,x,y,z);
		CATMathPoint aPoint(x,y,z);
		// To get the number of points of th MfgTPMultipleMotion
		NbPoint = _TPMultipleMotion->GetNumberOfTipPoints();

		distance = aPoint.SquareDistanceTo(Point);
		_PointNumber = 1;
		// loop on all the point of the tool path.
		for ( int j=2; j<=NbPoint; j++) {
			double x,y,z;
			_TPMultipleMotion->GetTipPoint (j,x,y,z);
			aPoint.SetCoord(x,y,z);

			distance2 = aPoint.SquareDistanceTo(Point);
			if ( distance2 <= distance + CAAEpsilon )  {
				_PointNumber = j;
				distance = distance2;
			}
		} 
      
		_TPMultipleMotion->GetTipPoint (_PointNumber,x,y,z);
		Point.SetCoord (x,y,z);
   }
}

//========================================================================
//  GetToolPathContainer : To Get the container of tool pathes.
//========================================================================
HRESULT CAAMfgTPESplitToolPathCom::GetToolPathFactory(CATIContainer_var& oContainer)
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

//===========================================================================
// RemovePointRep : To remove the rep of the point.
//===========================================================================
void CAAMfgTPESplitToolPathCom::RemovePointRep()
{ 
	if (_CurrentPointRep ) {
		if (_Viewer) 
			_Viewer->RemoveRep(_CurrentPointRep);

		// Rep must be destroyed
		_CurrentPointRep->Destroy();
		_CurrentPointRep = NULL;
	}
}

//========================================================================
// Valuate: Internal test
//========================================================================
void CAAMfgTPESplitToolPathCom::Valuate (const CATBaseUnknown_var& iValue)     
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

			PreActivate(NULL, NULL, NULL);

			CATMathPoint* point1 = new CATMathPoint (10.,20.0,30.0);
			ActivateSelector(NULL, NULL, point1);
			delete point1;

		}
	}
}
