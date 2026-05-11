#include "CAAPeoUserAlgoUIFactory.h"

// this file gives the implementation of the CATIOptAlgorithmUIFactory interface ...
#include "TIE_CATIOptAlgorithmUIFactory.h"
TIEchain_CATIOptAlgorithmUIFactory( CAAPeoUserAlgoUIFactory);

// ... for the feature CAAPeoUserAlgo
CATImplementClass(CAAPeoUserAlgoUIFactory,DataExtension,CATBaseUnknown,CAAPeoUserAlgo);

// dialog
#include "CATDlgGridConstraints.h"

// Others interfaces supported by this feature
#include "CATIInstance.h"
#include "CATIOptAlgorithm.h"

#include <iostream.h>

// CAAOptimizationInterfaces.edu
#include "CAAPeoUserAlgoSettingsFrame.h"  // derives from CATDlgFrame
#include "CAAPeoUserAlgoStopDialog.h"	  // derives from CATDlgDialog
#include "CAAPeoUserAlgoFeatureDefines.h" 

// OptimizationInterfaces
#include "CATIOptProblem.h"



CAAPeoUserAlgoUIFactory::CAAPeoUserAlgoUIFactory()
{
}


CAAPeoUserAlgoUIFactory::~CAAPeoUserAlgoUIFactory()
{
}

/**
* This method instanciates a CAAPeoUserAlgoSettingsFrame that will allow
* interactiv changes of the algorithm settings (Radio buttons, checks, 
* text editor...).
*/
CATDlgFrame* CAAPeoUserAlgoUIFactory::CreateAlgoSettingsFrame(CATDialog* iFather, CATDlgStyle iStyle)
{

	CATIOptAlgorithm_var algo = this;
	if(!algo)
		return NULL;

	// instanciates the frame that contains many dialog objects that allow the algorithm settings changes
	CAAPeoUserAlgoSettingsFrame* algoSettingsFrm = new CAAPeoUserAlgoSettingsFrame(iFather,iStyle,"CAAPeoUserAlgoSettingsFrame");

	// builds the dialog (creates objects and puts callbacks ...)
	if( FAILED(algoSettingsFrm->Build(algo)) )
	{
		cerr << "\n\n!!!! BUILD FAILED !!!\n\n";
		algoSettingsFrm = NULL;
	}

	// returns the instanciated frame
	return algoSettingsFrm;
}


/*
* This method instanciates a CATOptSAAndGradStopDialog that will
* allow the algorithm run interruption.
*/
CATDlgDialog* CAAPeoUserAlgoUIFactory::CreateStopAlgoDialog(CATDialog* iFather, CATDlgStyle iStyle, const CATIOptOptimization_var& iOptim)
{
	CATIOptAlgorithm_var algo = this;
	if(!algo)
		return NULL;

	if(!iOptim)
		return NULL;

	// get the algorithm settings needed to build the CAAPeoUserAlgoStopDialog
	double maxTime;
	algo->GetSetting(UserAlgoMaxTimeSetting /* CAAPeoUserAlgoFeatureDefines.h */, maxTime);

	double nbUpdatesMax;
	algo->GetSetting(UserAlgoNbUpdatesMaxSetting, nbUpdatesMax);

	int updateVisu = 0;
	updateVisu = iOptim->GetUpdateVisualizationFlag();

	// instanciates the stop dialog
	CAAPeoUserAlgoStopDialog* stopDlg = new CAAPeoUserAlgoStopDialog( iFather,iStyle,"CAAPeoUserAlgoStopDialog",maxTime,nbUpdatesMax, updateVisu,iOptim);

	// builds the stop dialog (creates objects and puts callbacks ..)
	stopDlg->Build();
	stopDlg->SetVisibility(CATDlgShow);

	// returns the instanciated stop dialog
	return stopDlg;
}


