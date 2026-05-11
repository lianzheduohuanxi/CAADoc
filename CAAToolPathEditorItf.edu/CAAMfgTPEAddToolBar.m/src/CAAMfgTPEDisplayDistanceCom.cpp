// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAMfgTPEDisplayDistanceCom:
//
// Sample code for : CAA Manufacturing
// Mission         : Command that compute and display the distance between two points 
//                   on the same tool path.
//                   
//
// Type            : Interactive functionality
//
// How to run it   : 1-You need the Use Case CAATPEAddToolBar in order to generate 
//                     a new toolbar
//                   2-Build the CAATPEAddToolBar library.
//                     In this library there is the code that defines a new command, and the code
//                     for an add-in in Surfacic Machining Workbench, to define a new command
//                     header that will enable you to display a distance between two points of 
//                     a tool path.
//                     You need to generate all the Use Cases f the framewor CAAToolPathEditor.edu.
//                   3-Create the runtime view.
//					 4-Launch CATIA.
//                   5-Enter in Surfacic machining workbench in NC Manufacturing workshop.
//                   6-Create a new activity and do the replay.
//                   6-Click on the "Display distance" Command
//                   7-Select an icon of tool path in the tree.
//
//
//=============================================================================

// Includes
#include "CAAMfgTPEDisplayDistanceCom.h" 

// Interfaces CATIA
#include "CATISpecObject.h"
#include "CATString.h"

#include "CATBaseUnknown.h"
#include "CATPathElementAgent.h"
#include "CATPathElement.h"

// Interfaces Mfg.
#include "CATIMfgToolPath.h"
#include "CATIMfgCompoundTraject.h"

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

#include "CATSelector.h"
#include "CATGraphicAttributeSet.h"
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DMarkerGP.h"
#include "CAT3DLineGP.h"
#include "CAT3DCustomRep.h"
#include "CATRep.h"
#include "CAT3DCustomRep.h"
#include "CAT3DPointRep.h"
#include "CATGraphicElementIntersection.h"

#include "CATUnicodeString.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeMagnitude.h"
#include "CATICkeUnit.h"

#include "CATMathPoint.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg( CAAMfgTPEDisplayDistanceCom,CATString);

//========================================================================
// Constructor
//========================================================================
CAAMfgTPEDisplayDistanceCom::CAAMfgTPEDisplayDistanceCom( CATString* argument) :
  CATStateCommand ((*argument), CATDlgEngOneShot, CATCommandModeExclusive),
	_ToolPahVisu(NULL), _TPSelectionAgent(NULL), _TPEndAgent(NULL),
    _iid(NULL), _Distance(0.0), _Selector(NULL),	_CurrentPointRep(NULL), _DistanceRep(NULL),
	_VisuManager(NULL),  _Viewer(NULL), _hasFirstPoint(CATFalse), _hasSecondPoint(CATFalse)
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
CAAMfgTPEDisplayDistanceCom::~CAAMfgTPEDisplayDistanceCom()
{	
	RemovePointRep();
	RemoveDistanceRep();

	DeleteController();

	if (_TPSelectionAgent) {_TPSelectionAgent->RequestDelayedDestruction();_TPSelectionAgent=NULL;};
	if (_TPEndAgent) {_TPEndAgent->RequestDelayedDestruction();_TPEndAgent=NULL;};
	if (_Selector) {_Selector->RequestDelayedDestruction();_Selector=NULL;};

	_ToolPath=NULL_var;
	_Viewer=NULL;

}

//========================================================================
// Build Graph : 
//========================================================================
void CAAMfgTPEDisplayDistanceCom::BuildGraph()
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
                       Action((ActionMethod) &CAAMfgTPEDisplayDistanceCom::GetSelection));

    AddTransition (secondState, NULL,
                   IsOutputSetCondition(_TPEndAgent),
                   Action((ActionMethod) &CAAMfgTPEDisplayDistanceCom::End));
}

//========================================================================
// End : End of the command.
//========================================================================
CATBoolean CAAMfgTPEDisplayDistanceCom::End (void* data)
{
   RequestDelayedDestruction();
   return (CATTrue);
}

//===========================================================================
// CreateController : Create the rep of the tool path
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::CreateController()
{
	if (!!_ToolPath) {
		CATIMfg3DToolPathVisuData_var VisuData (_ToolPath);
		if (!!VisuData)
        {
		    int DisplayTPWithPoints =1;
			VisuData->SetDisplayMode(DisplayTPWithPoints);
			VisuData->DrawCircle(FALSE); // to display intermediate points in circles motions
        }

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
void CAAMfgTPEDisplayDistanceCom::DeleteController()
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
void CAAMfgTPEDisplayDistanceCom::DispatchInfo() 
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
CATBoolean CAAMfgTPEDisplayDistanceCom::GetSelection (void* data)
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

					ptrCTraject->Release();
					ptrCTraject=NULL;
					RESULT = CATTrue;
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
void CAAMfgTPEDisplayDistanceCom::SetSelector() 
{
	// To get the rep of the points
	CATRep* pointsRep=NULL;          
	CATIMfg3DToolPathVisuData_var VisuData (_ToolPath);
	if (!! VisuData)
		VisuData->GetPointsRep(&pointsRep);

	if ( _Selector == NULL ) {

		_Selector = new CATSelector (this,"ToolPathSelector", pointsRep);
		AddAnalyseNotificationCB ( _Selector,
											_Selector->GetCATPreactivate(),
											(CATCommandMethod)&CAAMfgTPEDisplayDistanceCom::PreActivate,NULL);
		AddAnalyseNotificationCB ( _Selector,
											_Selector->GetCATActivate(),
											(CATCommandMethod)&CAAMfgTPEDisplayDistanceCom::ActivateSelector,NULL);
		AddAnalyseNotificationCB ( _Selector,
											_Selector->GetCATMove(),
											(CATCommandMethod)&CAAMfgTPEDisplayDistanceCom::Move,NULL);
		AddAnalyseNotificationCB ( _Selector,
											_Selector->GetCATEndPreactivate(),
											(CATCommandMethod)&CAAMfgTPEDisplayDistanceCom::EndPreActivate,NULL);
	}
	else {
		_Selector->AssociateToRep(pointsRep);
	}
}


//===========================================================================
// PreActivate :To process the preactivate event. 
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::PreActivate (CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
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

	_CurrentPointRep = new CAT3DPointRep (CATMathPointf(point),FULLSQUARE);
	if ( _Viewer ) _Viewer->AddRep(_CurrentPointRep);
 	
}

//===========================================================================
// ActivateSelector : To process the selection of a point.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::ActivateSelector(CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{	
	CATGraphicElementIntersection* Intersection = NULL;
	if (NULL != _Selector)  {
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

	if ( _hasFirstPoint) {
		_hasSecondPoint = CATTrue;
		_SecondPoint = Intersection->point;
		_Distance = _FirstPoint.DistanceTo(_SecondPoint);

		DisplayDistance ();
		_hasFirstPoint = CATFalse;
	}
	else {
		_hasFirstPoint = CATTrue;
		_FirstPoint = Intersection->point;

		_Distance = _FirstPoint.DistanceTo(_SecondPoint);

		if ( _hasSecondPoint) {
			DisplayDistance ();
			_hasSecondPoint = CATFalse;
		}
	}

	Intersection->Release();

	if ( _Viewer) _Viewer->Draw();

}

//===========================================================================
// DisplayDistance :To display the distance between two points.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::DisplayDistance()
{	
	if ( _hasFirstPoint &&  _hasSecondPoint ) {

		RemoveDistanceRep();

		CATUnicodeString distanceStr;
		ConvertLengthInUnit(_Distance, distanceStr);

		float tab[3] = {(float)_SecondPoint.GetX(),(float)_SecondPoint.GetY(),(float)_SecondPoint.GetZ()};
		CAT3DMarkerGP* arrowGP = new CAT3DMarkerGP(tab,1,FILLED_ARROW);

		CATMathPointf anchor=(_FirstPoint+ _SecondPoint)/2.0;
		CAT3DAnnotationTextGP* textGP  = new CAT3DAnnotationTextGP(anchor,distanceStr,BASE_CENTER);

		float Points[6] = {  (float)_FirstPoint.GetX(), (float)_FirstPoint.GetY(), (float)_FirstPoint.GetZ(),
								  (float)_SecondPoint.GetX(), (float)_SecondPoint.GetY(),(float)_SecondPoint.GetZ()};
		CAT3DLineGP* lineGP = new CAT3DLineGP (Points);

		CATGraphicAttributeSet AttributsDir;
		AttributsDir.SetColor(RED);
		_DistanceRep = new CAT3DCustomRep(lineGP,AttributsDir);
		if (NULL != _DistanceRep) {
			_DistanceRep -> AddGP(textGP,AttributsDir);
			_DistanceRep -> AddGP(arrowGP,AttributsDir);
		}

		if (_Viewer) {
			_Viewer->AddRep(_DistanceRep);
			_Viewer->Draw();
		}
	}
}

//===========================================================================
// Move : Processing of the move event.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::Move (CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{	
	PreActivate (c1,c2,c3);
}

//===========================================================================
// EndPreActivate : End of the preactivate event.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::EndPreActivate (CATCommand*, CATNotification*, CATCommandClientData)
{
	RemovePointRep();
	if ( _Viewer) 
		_Viewer->Draw();
}

//===========================================================================
// ConvertLengthInUnit : To convert a length in the current unit.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::ConvertLengthInUnit(double iLength, CATUnicodeString& ioLengthinUnit)
{
	CATICkeMagnitude_var hMag = CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("LENGTH");
	CATICkeUnit_var stUnit;
	CATICkeUnit_var cuUnit;

	if (!!hMag)
	{
		stUnit = hMag->StorageUnit();
		cuUnit = hMag->CurrentUnit();
		if (!!cuUnit && !!stUnit) 
		{
			ioLengthinUnit = cuUnit->Show(stUnit->Convert(iLength));
		}
	}
}

//===========================================================================
// RemoveDistanceRep :To remove the rep of the distance.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::RemoveDistanceRep()
{ 
	if (_DistanceRep ) {
		if (_Viewer) 
			_Viewer->RemoveRep(_DistanceRep);

		// Rep must be destroyed
		_DistanceRep->Destroy();
		_DistanceRep = NULL;
	}
}

//===========================================================================
// RemovePointRep :  To remove the rep of the point.
//===========================================================================
void CAAMfgTPEDisplayDistanceCom::RemovePointRep()
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
// Valuate: Internal Test
//========================================================================
void CAAMfgTPEDisplayDistanceCom::Valuate (const CATBaseUnknown_var& iValue)     
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


			//
			CATUnicodeString oString;
			double dist = 3.45;
			ConvertLengthInUnit(dist, oString);
			// 
			PreActivate(NULL, NULL, NULL);

			CATMathPoint* point1 = new CATMathPoint (10.,20.0,30.0);
			ActivateSelector(NULL, NULL, point1);
			CATMathPoint* point2= new CATMathPoint (-10.,-20.0,30.0);
			ActivateSelector(NULL, NULL, point2);

			Move(NULL, NULL, NULL);
			EndPreActivate(NULL, NULL, NULL);

			delete point1; delete point2;
		}
	}
}
