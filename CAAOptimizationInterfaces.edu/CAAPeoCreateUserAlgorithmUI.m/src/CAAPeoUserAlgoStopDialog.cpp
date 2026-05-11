#include "CAAPeoUserAlgoStopDialog.h"

// ApplicationFrame
#include "CATInteractiveApplication.h"

// Dialog
#include "CATDlgGridConstraints.h"

// OptimizationInterfaces
#include "CATIOptAlgorithm.h"

// CAAOptimizationInterfaces.edu
#include "CAAPeoUserAlgorithmNotif.h"

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAPeoUserAlgoStopDialog::CAAPeoUserAlgoStopDialog(CATDialog* iFather,CATDlgStyle iStyle,const CATString& iDialogObjectName,int maxTime, int maxUpdateNb,int updateVisu,const CATIOptOptimization_var &iOptim):
CATDlgDialog (iFather,iDialogObjectName,iStyle)
{
	// can't go on if no optimization is running
	_optimization = iOptim;
	if (!_optimization)
		return;
	
	_maxTime = maxTime;
	_maxUpdateNb = maxUpdateNb;
	_updateVisu = updateVisu;
//	_viewer = NULL;

	_emptyLbl1 = NULL;
	_updateLbl = NULL;
	_updateProgressBar = NULL;
	_updateCounterLbl = NULL;
	_elapsedLbl = NULL;
	_elapsedProgressBar = NULL;
	_elapsedCounterLbl = NULL;

	CATIOptAlgorithm_var algorithm = _optimization->GetAlgorithm();

	// puts the callback on the EndIteration receipt
	if (!!algorithm)
		AddCallback(algorithm->GetCallbackManager(), algorithm->GetEndIterationNotification(), 
					(CATSubscriberMethod)&CAAPeoUserAlgoStopDialog::OnReceiveEndIterationNotification,NULL);

}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAPeoUserAlgoStopDialog::~CAAPeoUserAlgoStopDialog()
{

	// unlocks the visualization
/*	if (_viewer)
	{
		_viewer->LockDrawRequest(0);
		_viewer = NULL;
	}
*/
	// removes the callback on the EndIteration receipt
	if (!!_optimization)
	{
		CATIOptAlgorithm_var algorithm = _optimization->GetAlgorithm();
		if (!!algorithm)
		{
			RemoveCallbacksOn(algorithm, algorithm->GetEndIterationNotification(), NULL);
		}
	}

	_optimization = NULL_var;

	_emptyLbl1 = NULL;
	_updateLbl = NULL;
	_updateProgressBar = NULL;
	_updateCounterLbl = NULL;
	_elapsedLbl = NULL;
	_elapsedProgressBar = NULL;
	_elapsedCounterLbl = NULL;
}



void CAAPeoUserAlgoStopDialog::Build()
{

	SetGridColumnResizable(0,1);

	// editor giving the current best objectiv value
	_emptyLbl1 = new CATDlgLabel(this, "EmptyLbl1");
	_emptyLbl1 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
	_emptyLbl1->SetVisibility(CATDlgHide);

	// update number progress
	_updateLbl = new CATDlgLabel(this, "UpdateLbl");
	_updateLbl -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	_updateLbl->SetTitle("Number of updates already done");
	_updateProgressBar = new CATDlgProgress(this, "UpdateProgressBar");
	_updateProgressBar -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	_updateCounterLbl = new CATDlgLabel(this, "UpdateCounterLbl");
	_updateCounterLbl -> SetGridConstraints(2, 2, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);

	_updateProgressBar->SetRange(0, _maxUpdateNb);

	//time progress
	_elapsedLbl = new CATDlgLabel(this, "ElapsedLbl");
	_elapsedLbl -> SetGridConstraints(3, 0, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	_elapsedLbl->SetTitle("Elapsed time");
	_elapsedProgressBar = new CATDlgProgress(this, "ElapsedProgressBar");
	_elapsedProgressBar -> SetGridConstraints(3, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	_elapsedCounterLbl = new CATDlgLabel(this, "ElapsedCounterLbl");
	_elapsedCounterLbl -> SetGridConstraints(3, 2, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);

	_elapsedProgressBar->SetRange(0, _maxTime * 60);  // maxTime in minutes and progress bar in secondes...

	//stop button = OK button of this CATDlgDialog
	SetOKTitle("Stop");	

	AddAnalyseNotificationCB(this, GetDiaOKNotification(), (CATCommandMethod)&CAAPeoUserAlgoStopDialog::OnStop, NULL);


	// gets the viewer to be able to update the visualization
/*	CATFrmLayout * layout = CATFrmLayout::GetCurrentLayout();
	if (layout) 
	{
		CATFrmWindow *curWindow = layout->GetCurrentWindow();
		if (curWindow) 
		{
			_viewer = curWindow->GetViewer();
			if (_viewer)
			{

//				if(!_updateVisu)
//				{
					// to lock modification until we receive a notification
					_viewer->LockDrawRequest(1);
//				}
//				else
//				{
					// to unlock the modification
//					_viewer->LockDrawRequest(0);
//				}

			}
		}
	}
*/
}



void CAAPeoUserAlgoStopDialog::OnReceiveEndIterationNotification(CATCallbackEvent ev, void* clientData, CATNotification *notif, CATSubscriberData data, CATCallback cb)
{
/*	if(_updateVisu)
	{
		_viewer->LockDrawRequest(0);
	}
*/

	// get the notification sent and its values
	CAAPeoUserAlgorithmNotif* userNotif = (CAAPeoUserAlgorithmNotif*) notif;
	if(!userNotif)
		return;

	int elapsedTime = userNotif->GetElapsedTime();
	int currentUpdate = userNotif->GetCurrentUpdate();

	CATUnicodeString title,tmp;

	// -> update nb progress
	_updateProgressBar->SetPos(currentUpdate);
	
	title.BuildFromNum(currentUpdate);
	title.Append("/");
	tmp.BuildFromNum(_maxUpdateNb);
	title.Append(tmp);
	_updateCounterLbl->SetTitle(title);

	// -> time progress
	_elapsedProgressBar->SetPos(elapsedTime); // elapsedTime is given secondes and the progress bar is in secondes.
	int min, sec;
	min = elapsedTime/60;
	sec = elapsedTime - min*60;
	
	if (min)
	{
		title.BuildFromNum(min);
		title.Append(":");
	}
	else
		title = "0:";
	tmp.BuildFromNum(sec);
	if (tmp.GetLengthInChar() == 1)
		tmp = "0" + tmp;
	title.Append(tmp);
	title.Append("/");
	tmp.BuildFromNum(_maxTime); // maxTime is given in minutes
	tmp.Append(":00");
	title.Append(tmp);
	
	_elapsedCounterLbl->SetTitle(title);

	// forces the application refresh
	CATInteractiveApplication *app = (CATInteractiveApplication *) CATApplication::MainApplication();
	if (app)
		app->UpdateDisplay();

/*	if(_updateVisu)
	{
		// to lock modification until we receive a notification
		_viewer->LockDrawRequest(1);
	}
*/
}

void CAAPeoUserAlgoStopDialog::OnStop(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	// we update the stop flag. This flag is checked by the algorithm before each update
	// to know if the algorithm run has to go on.
	_optimization->RunHasToStop(1);
	SendNotification(GetFather(), GetDiaOKNotification());
}

