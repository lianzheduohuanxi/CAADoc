// COPYRIGHT DASSAULT SYSTEMES  2002
//-------------------------------------------------------------
//
// Class providing the stop dialog for the feature CAAPeoUserAlgo.
// You will have to provide the same service on your own algorithm
// feature if you are in interactiv mode.
//
// This class is used by the implementation of 
// CATIOptAlgorithmUIFactory (here CAAPeoUserAlgoUIFactory)
//-------------------------------------------------------------

#ifndef CAAPeoUserAlgoStopDialog_H
#define CAAPeoUserAlgoStopDialog_H

#include "CATDlgDialog.h"

#include "CATIOptOptimization.h"

#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgProgress.h"

class CAAPeoUserAlgoStopDialog: public CATDlgDialog
{
	DeclareResource( CAAPeoUserAlgoStopDialog, CATDlgDialog )
		
public:
	
	/**
	* This method initializes the stop dialog members variables and put a callback on the algorithm EndIteration
	* receipt.
	*/
	CAAPeoUserAlgoStopDialog(CATDialog* iFather,CATDlgStyle iStyle,const CATString& iDialogObjectName,int maxTime, int maxUpdates, int iUpdateVisu,const CATIOptOptimization_var &optim);
	virtual ~CAAPeoUserAlgoStopDialog();
	
	/**
	* This method builds the stop dialog and put the callback on the stop button.
	*/
	void Build ();
			
private:

	/**
	* This method updates the stop dialog as soon as we receive the EndIteration notification sent by the
	* user algorithm during its run.
	*/
	void OnReceiveEndIterationNotification(CATCallbackEvent ev, void* clientData, CATNotification *notif, CATSubscriberData data, CATCallback cb);
	
	/**
	* This method sets the optimization stop flag to 1 and closes the stop dialog.
	* Notice that the optimization stop flag is checked in the algorithm run to
	* know if the run has to stop.
	*/
	void OnStop(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);

	CATIOptOptimization_var _optimization;
	int _maxTime;
	int _maxUpdateNb;
	int _updateVisu;

	//CATViewer*		_viewer;

	CATDlgLabel*	_emptyLbl1;
	CATDlgLabel*	_updateLbl;
	CATDlgProgress*	_updateProgressBar;
	CATDlgLabel*	_updateCounterLbl;
	CATDlgLabel*	_elapsedLbl;
	CATDlgProgress*	_elapsedProgressBar;
	CATDlgLabel*	_elapsedCounterLbl;

};

//----------------------------------------------------------------------

#endif
