/**
* @quickReview TVQ 02:08:02
*/
/**
* @fullReview TVQ 02:07:16
*/
#include "CAAPeoUserAlgoSettingsFrame.h"
#include "CAAPeoUserAlgoFeatureDefines.h"

// Dialog
#include "CATDlgGridConstraints.h"


CAAPeoUserAlgoSettingsFrame::CAAPeoUserAlgoSettingsFrame( CATDialog *iParent, CATDlgStyle iStyle, const CATString& iDialogObjectName)
 : CATDlgFrame(iParent,iDialogObjectName,iStyle)
{
	_algo = NULL_var;

	_terminationFrm = NULL;

	_maxEvalLbl = NULL;
	_maxEvalEditor = NULL;
	
	_timeLbl = NULL;
	_timeEditor = NULL;

}

CAAPeoUserAlgoSettingsFrame::~CAAPeoUserAlgoSettingsFrame()
{
	_algo = NULL_var;

	 _terminationFrm = NULL;

	_maxEvalLbl = NULL;
	_maxEvalEditor = NULL;
	
	_timeLbl = NULL;
	_timeEditor = NULL;

}

HRESULT CAAPeoUserAlgoSettingsFrame::Build(CATIOptAlgorithm_var spiAlgo)
{

	if(!spiAlgo)
		return E_FAIL;

	_algo = spiAlgo;

	_terminationFrm = new CATDlgFrame(this,"TerminationCriteriaFrm",CATDlgGridLayout);
	{
		_terminationFrm->SetTitle("Termination criteria");
		_terminationFrm->SetGridConstraints(0, 0, 2, 1, CATGRID_4SIDES);
		_terminationFrm->SetGridColumnResizable(0,1);
		_terminationFrm->SetGridColumnResizable(1,1);

		CATUnicodeString tmp;


		//* Max evaluations
		_maxEvalLbl = new CATDlgLabel(_terminationFrm, "MaxNbEvaluationsLbl");
		_maxEvalLbl->SetTitle("Maximum number of updates");
		_maxEvalLbl -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

		_maxEvalEditor = new CATDlgEditor(_terminationFrm, "MaxEvalEditor", CATDlgEdtInteger);
		_maxEvalEditor -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
		
		//	=> init from feature (if algo has just been created, it uses the default feature values)
		double nbMax;
		_algo->GetSetting(UserAlgoNbUpdatesMaxSetting, nbMax);
		tmp.BuildFromNum((int) nbMax);
		_maxEvalEditor->SetText(tmp);


		//* Max Time
		_timeLbl = new CATDlgLabel(_terminationFrm, "MaxTimeChkB");
		_timeLbl -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
		_timeLbl ->SetTitle("Maximum time (minutes)");
		_timeEditor = new CATDlgEditor(_terminationFrm, "MaxTimeEditor", CATDlgEdtInteger);
		_timeEditor -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);


		//	=>init from feature (if algo has just been created, it uses the default feature values)
		double time;
		_algo->GetSetting(UserAlgoMaxTimeSetting, time);
		tmp.BuildFromNum((int) time);
		_timeEditor->SetText(tmp);
		
	}

	// CALLBACKS :


	//-> changement de valeur du nb max d'évaluations
	AddAnalyseNotificationCB (_maxEvalEditor, 
							  _maxEvalEditor->GetEditModifyNotification(),
							  (CATCommandMethod)&CAAPeoUserAlgoSettingsFrame::OnChangeMaxEval,
							  NULL);
		
	//-> modif de la valeur de _timeEditor
	AddAnalyseNotificationCB (_timeEditor, 
							  _timeEditor->GetEditModifyNotification(),
							  (CATCommandMethod)&CAAPeoUserAlgoSettingsFrame::OnChangeTime,
							  NULL);


	return S_OK;
}


// methode appelée dès que l'on check/uncheck le checkbutton ou que l'on modifie le nb d'update without improvement
//Comme le stoppingCriterion est lié au temps et au NoImprovement => il faut mettre a jour en fonction des 2
void CAAPeoUserAlgoSettingsFrame::OnChangeMaxEval(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	if(!_algo)
		return;

	_algo->SetSetting(UserAlgoNbUpdatesMaxSetting, _maxEvalEditor->GetIntegerValue());	
}


// methode appelée dès que l'on check/uncheck le checkbutton ou que l'on modifie le temps max
// Comme le stoppingCriterion est lié au temps et au NoImprovement => il faut mettre a jour en fonction des 2
void CAAPeoUserAlgoSettingsFrame::OnChangeTime(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	if(!_algo)
		return;

	_algo->SetSetting(UserAlgoMaxTimeSetting, _timeEditor->GetIntegerValue());
}

