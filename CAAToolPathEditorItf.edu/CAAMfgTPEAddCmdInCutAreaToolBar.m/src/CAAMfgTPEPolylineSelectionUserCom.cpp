//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
//========================================================================
//
// Sample code for : CAA Manufacturing
// Mission         : Command that cuts polyline on a tool path.        
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
//					 8-Choose commands "Cut polyline on a tool path"
//
//========================================================================
// October 2002 Creation                                       C.RIMBAUD
//========================================================================
//

#include "CAAMfgTPEPolylineSelectionUserCom.h"

#include "CATIMfgTPECutAreasEditor.h"
#include "CATIMfgTPMultipleMotion.h"

#include "CATFrmLayout.h"
#include "CATFrmWindow.h"
#include "CATFrmGraphAnd3DWindow.h"
#include "CAT3DViewer.h"
#include "CATSelector.h"

#include "CATDialog.h"
#include "CATDialogAgent.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg( CAAMfgTPEPolylineSelectionUserCom, CATString);

//========================================================================
// Constructor
//========================================================================
CAAMfgTPEPolylineSelectionUserCom::CAAMfgTPEPolylineSelectionUserCom (void* ipCutAreasEditor)
									: CATStateCommand("TPEPolygonSelection",NULL,CATCommandModeShared),
										_PointAgent(NULL), _Viewer(NULL), _Selector(NULL),
										_EndAgent(NULL),_NumPolyline(0)
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
	_piCutEditor = (CATIMfgTPECutAreasEditor*)ipCutAreasEditor;
	// Erase of the last preview
	if (NULL != _piCutEditor) 
	{
		_piCutEditor->ClearAll();
		_piCutEditor->BeginPolylineToCut();
	}

  // Create the selector.
  CATRep* Rep = NULL;
  if (NULL != _piCutEditor)  
	  Rep = _piCutEditor->GetToolPathRep();

  _Selector = new CATSelector (this,"ToolPathSelector", Rep);

}

//========================================================================
// Destructor
//========================================================================
CAAMfgTPEPolylineSelectionUserCom::~CAAMfgTPEPolylineSelectionUserCom()
{ 
	if ( _EndAgent )
		_EndAgent->RequestDelayedDestruction(); 
	_EndAgent=NULL;

	if (_Selector)
		_Selector->RequestDelayedDestruction(); 
	_Selector = NULL; 

	if (_PointAgent)
		_PointAgent->RequestDelayedDestruction(); 
	_PointAgent = NULL; 

	_piCutEditor=NULL;
	_Viewer = NULL;
}

//========================================================================
// End
//========================================================================
CATBoolean CAAMfgTPEPolylineSelectionUserCom::End(void *data)
{
	if ( _Viewer ) {
		_Viewer->SetCursor(CATDialog::NorthWestArrow);
	}

	// End of the selection of polyline
	if (NULL != _piCutEditor) 
		_piCutEditor->EndPolylineToCut();

   RequestDelayedDestruction();
   return CATTrue;
}

//========================================================================
// BuildGraph
//========================================================================
void CAAMfgTPEPolylineSelectionUserCom::BuildGraph()
{   
	_PointAgent = new CATDialogAgent("Point");
	if (NULL != _Selector)
	{
		_PointAgent->AcceptOnNotify(_Selector, _Selector->GetCATActivate());
		_PointAgent->SetBehavior(CATDlgEngWithPrevaluation|
										CATDlgEngWithUndo|CATDlgEngRepeat|
										CATDlgEngAcceptOnPrevaluate);

		// Dialog States
		CATDialogState* InitState = GetInitialState("UserPolylineSelection");
		if (NULL != InitState)
		{
			InitState->AddDialogAgent(_PointAgent); 

			_EndAgent = new CATPathElementAgent("End");
			if (NULL != _EndAgent)
			{
				_EndAgent->AcceptOnNotify(NULL, CATEdit::ClassName());
				InitState->AddDialogAgent(_EndAgent); 

				AddTransition( InitState, InitState, 
			        				IsOutputSetCondition(_PointAgent),
									Action((ActionMethod)& CAAMfgTPEPolylineSelectionUserCom::LineSelection));

				AddTransition( InitState, NULL, 
									IsOutputSetCondition(_EndAgent),
									Action((ActionMethod)& CAAMfgTPEPolylineSelectionUserCom::End));
				SetRepeatMode(ON);
			}
		}
	}
}

//========================================================================
// Cancel
//========================================================================
CATStatusChangeRC CAAMfgTPEPolylineSelectionUserCom::Cancel(CATCommand* iFromCmd, CATNotification* iNotif)
{
	RequestDelayedDestruction();
	return CATStatusChangeRCCompleted;
}

//========================================================================
// LineSelection
//========================================================================
CATBoolean CAAMfgTPEPolylineSelectionUserCom::LineSelection(void* Data)
{	
	// Simulate a selection of polyline.
	CATListOfInt Liste;

	CATIMfgToolPath_var toolPath;
	CATIMfgCompoundTraject_var compoundTraject;
	if (_piCutEditor && SUCCEEDED(_piCutEditor->GetToolPath(toolPath) ) )
	{
		compoundTraject = toolPath;
		if ( !! compoundTraject ) 
		{
			CATListValCATBaseUnknown_var ListofElement;
			boolean result = compoundTraject->GetAllElementaryTrajects(ListofElement);

			int NbElement = ListofElement.Size();
			if ( NbElement == 1)
			{
				CATIMfgTPMultipleMotion_var spMultipleMotion (ListofElement[1]);
				if (NULL_var != spMultipleMotion) 
				{
					int number=0;
					spMultipleMotion->GetNumberOfSubTrajects(number);

					_NumPolyline++;
					if (_NumPolyline < number)
						Liste.Append(_NumPolyline);

					_NumPolyline++;
					if (_NumPolyline < number)
						Liste.Append(_NumPolyline);

				}
			}
		}
	}
	if (_piCutEditor) _piCutEditor->LoadPolylineToCut(&Liste);
	Liste.RemoveAll();

	if ( !! compoundTraject ) 
	{
		CATListValCATBaseUnknown_var ListofElement;
		boolean result = compoundTraject->GetAllElementaryTrajects(ListofElement);

		int NbElement = ListofElement.Size();
		if ( NbElement == 1)
		{
			CATIMfgTPMultipleMotion_var spMultipleMotion (ListofElement[1]);
			if (NULL_var != spMultipleMotion) 
			{
				int number;
				spMultipleMotion->GetNumberOfSubTrajects(number);

				_NumPolyline++;
				if (_NumPolyline < number)
					Liste.Append(_NumPolyline);
			}
		}
	}
	if (_piCutEditor) _piCutEditor->LoadPolylineToCut(&Liste);

	if (NULL != _PointAgent) _PointAgent->InitializeAcquisition();

	return CATTrue;
}

//========================================================================
// Desactivate
//========================================================================
CATStatusChangeRC CAAMfgTPEPolylineSelectionUserCom::Desactivate(CATCommand* iFromCmd, CATNotification* iNotif)
{
	Cancel(iFromCmd, iNotif);
	return CATStatusChangeRCCompleted;
}

//========================================================================
// Activate
//========================================================================
CATStatusChangeRC CAAMfgTPEPolylineSelectionUserCom::Activate(CATCommand* iFromCmd, CATNotification* iNotif)
{
	return CATStatusChangeRCCompleted;
}

//===========================================================================
// Internal Test
//===========================================================================
void CAAMfgTPEPolylineSelectionUserCom::Valuate (int iSwitch)
{
	if ( iSwitch == 1 )
	{
		if (NULL != _PointAgent)
			_PointAgent->Accept();
	}
	else if (iSwitch == 2) 
   {
		if (NULL != _EndAgent)
			_EndAgent->Accept();
	}
}
