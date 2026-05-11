//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
//========================================================================
//
// Sample code for : CAA Manufacturing
// Mission         : Command that cuts a tool path by a point on the tool path.                   
//
// Type            : Interactive functionality
//
// How to run it   : 1-Build the CAAMfgTPEAddCmdInCutAreaToolBar.
//                     In this library there is the code that add two commands in the cut area tool bar.
//                   2-Create the runtime view.
//					      3-Launch CATIA.
//                   4-Enter in Surfacic machining workbench in NC Manufacturing workshop.
//                   5-Create a new activity and do the replay.
//                   6-Click on the "Tool Path" contextual menu and choose item "Cut Area"
//                   7-Two new commands are available
//							8-Choose commands "Cut by a point on a tool path"
//
//========================================================================
// October 2002 Creation                                       C.RIMBAUD
//========================================================================
//

#include "CAAMfgTPEOnePointSelectionUserCom.h"

#include "CATIMfgTPECutAreasEditor.h"

#include "CATFrmLayout.h"
#include "CATFrmWindow.h"
#include "CATFrmGraphAnd3DWindow.h"

#include "CAT3DViewer.h"
#include "CATRep.h"
#include "CATGraphicElementIntersection.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg( CAAMfgTPEOnePointSelectionUserCom, CATString);


//========================================================================
// Constructor
//========================================================================
CAAMfgTPEOnePointSelectionUserCom::CAAMfgTPEOnePointSelectionUserCom (void* ipCutAreasEditor)
							: CATStateCommand("TPESelectionUserOnePoint", NULL, CATCommandModeShared),
							  _Selector(NULL), _Viewer(NULL),
							  _pCutAreasEditor((CATIMfgTPECutAreasEditor*) ipCutAreasEditor),
							  _HasPoint(CATFalse), _PointAgent(NULL),
                        _PreactivateCB(NULL),
							  _MoveCB(NULL),
							  _EndPreactivateCB(NULL)
{
	CATFrmLayout* ptrFrmLayout = CATFrmLayout::GetCurrentLayout();
	if ( ptrFrmLayout)
    {
		const CATFrmWindow * ptrFrmWindow = ptrFrmLayout->GetCurrentWindow () ;
		if (ptrFrmWindow && ptrFrmWindow->IsAKindOf(CATFrmGraphAnd3DWindow::ClassName()) )
        {
			CATFrmGraphAnd3DWindow* ptr3DWindow = (CATFrmGraphAnd3DWindow*)ptrFrmWindow;
			CATViewer * viewer = ptr3DWindow->GetGraphicViewer();
			if( viewer && viewer->IsAKindOf(CAT3DViewer::ClassName()) ) 
				_Viewer = (CAT3DViewer*)viewer;
		}
	}

  //Creation of the selector. Tool path can be pointed.
  CATRep* Rep = NULL;
  if (NULL != _pCutAreasEditor)  Rep = _pCutAreasEditor->GetToolPathRep();
  _Selector = new CATSelector (this,"ToolPathSelector", Rep);

  _PreactivateCB    = AddAnalyseNotificationCB (_Selector,
	                                            _Selector->GetCATPreactivate(),
							                    (CATCommandMethod)&CAAMfgTPEOnePointSelectionUserCom::PreActivate,NULL);
  _MoveCB           = AddAnalyseNotificationCB (_Selector,
	                                            _Selector->GetCATMove(),
							                    (CATCommandMethod)&CAAMfgTPEOnePointSelectionUserCom::Move,NULL);
  _EndPreactivateCB = AddAnalyseNotificationCB (_Selector,
	                                            _Selector->GetCATEndPreactivate(),
							                    (CATCommandMethod)&CAAMfgTPEOnePointSelectionUserCom::EndPreActivate,NULL);

}

//========================================================================
// Destructor
//========================================================================
CAAMfgTPEOnePointSelectionUserCom::~CAAMfgTPEOnePointSelectionUserCom()
{ 
	if (_PreactivateCB)    
		RemoveAnalyseNotificationCB (_PreactivateCB);
	_PreactivateCB = NULL;

	if (_MoveCB)           
		RemoveAnalyseNotificationCB (_MoveCB);
	_MoveCB = NULL;

	if (_EndPreactivateCB) 
		RemoveAnalyseNotificationCB (_EndPreactivateCB);
	_EndPreactivateCB = NULL;

	if (_PointAgent) 
		_PointAgent->RequestDelayedDestruction(); 
	_PointAgent = NULL; 

	if (_Selector)
		_Selector->RequestDelayedDestruction(); 
	_Selector = NULL; 

	_pCutAreasEditor = NULL;
	_Viewer = NULL;
}

//========================================================================
// BuildGraph
//========================================================================
void CAAMfgTPEOnePointSelectionUserCom::BuildGraph()
{   
	_PointAgent = new CATDialogAgent("Point");
	if (NULL != _Selector)
		_PointAgent->AcceptOnNotify(_Selector, _Selector->GetCATActivate());

	// Dialog States
	CATDialogState* InitState = GetInitialState("OnePointModification");
	if (NULL != InitState) 
		InitState->AddDialogAgent(_PointAgent); 

	// Transitions
	AddTransition (InitState,NULL, 
						AndCondition ( Condition ( (ConditionMethod) &CAAMfgTPEOnePointSelectionUserCom::HasPoint),
						IsOutputSetCondition(_PointAgent)),
						Action((ActionMethod)& CAAMfgTPEOnePointSelectionUserCom::SelectPoint));

	SetRepeatMode(OFF);
}

//========================================================================
// Activate
//========================================================================
CATStatusChangeRC CAAMfgTPEOnePointSelectionUserCom::Activate(CATCommand* iFromCmd, CATNotification* iNotif)
{
	if ( NULL != _pCutAreasEditor) 
		_pCutAreasEditor->ClearAll();

	return CATStatusChangeRCCompleted;
}

//========================================================================
// Desactivate
//========================================================================
CATStatusChangeRC CAAMfgTPEOnePointSelectionUserCom::Desactivate(CATCommand* iFromCmd, CATNotification* iNotif)
{
  Cancel(iFromCmd, iNotif);
  return CATStatusChangeRCCompleted;

}

//========================================================================
// Cancel
//========================================================================
CATStatusChangeRC CAAMfgTPEOnePointSelectionUserCom::Cancel(CATCommand* iFromCmd, CATNotification* iNotif)
{
	RequestDelayedDestruction();
	return CATStatusChangeRCCompleted;
}

//===========================================================================
// PreActivate
//===========================================================================
void CAAMfgTPEOnePointSelectionUserCom::PreActivate (CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{
	// Erase of the last preview
	EndPreActivate (c1,c2,c3);

	// Get the point.
	CATGraphicElementIntersection* Intersection = NULL;
	if (NULL != _Selector)   
	  Intersection = (CATGraphicElementIntersection*) 
							_Selector->SendCommandSpecificObject (CATGraphicElementIntersection::ClassName(), c2);

	if ( Intersection) {
		CATMathPoint aPoint;
		aPoint = Intersection->point;
		Intersection->Release();

		_CurrentPoint = aPoint; 
		_HasPoint = CATTrue;
	}
}

//===========================================================================
// Move
//===========================================================================
void CAAMfgTPEOnePointSelectionUserCom::Move (CATCommand* c1, CATNotification* c2, CATCommandClientData c3)
{	
	PreActivate (c1,c2,c3);
}

//===========================================================================
// EndPreActivate
//===========================================================================
void CAAMfgTPEOnePointSelectionUserCom::EndPreActivate (CATCommand*, CATNotification*, CATCommandClientData)
{
}

//===========================================================================
// SelectPoint
//===========================================================================
CATBoolean CAAMfgTPEOnePointSelectionUserCom::SelectPoint (void* Data)
{
   // The point is given to the interface CATIMfgTPECutAreasEditor.
	if (_pCutAreasEditor != NULL && HasPoint(NULL) )
		_pCutAreasEditor->LoadOneCuttingPoint(_CurrentPoint);

	return CATTrue;
}

//===========================================================================
// HasPoint
//===========================================================================
CATBoolean CAAMfgTPEOnePointSelectionUserCom::HasPoint (void* Data)
{
	return _HasPoint;
}

//===========================================================================
// Internal Test
//===========================================================================
void CAAMfgTPEOnePointSelectionUserCom::Valuate (const CATMathPoint& point)
{
	_CurrentPoint=point;
	_HasPoint = CATTrue;
}
