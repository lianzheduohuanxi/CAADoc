// COPYRIGHT DASSAULT SYSTEMES  2002
//-------------------------------------------------------------
//
// Class providing the settings frame for the CAAPeoUserAlgo algorithm.
// If you are in interactiv mode and if your algorithm has at least
// one setting which can be modify by the user, you will have to
// provide the same service.
//
// This class is used by the implementation of 
// CATIOptAlgorithmUIFactory (here CAAPeoUserAlgoUIFactory)
//-------------------------------------------------------------

#ifndef CAAPeoUserAlgoSettingsFrame_H
#define CAAPeoUserAlgoSettingsFrame_H

// OptmizationInterfaces
#include "CATIOptAlgorithm.h"

// Dialog
#include "CATDlgFrame.h"
#include "CATDlgRadioButton.h"
#include "CATDlgEditor.h"
#include "CATDlgCheckButton.h"
#include "CATDlgLabel.h"
#include "CATDlgCombo.h"


class CAAPeoUserAlgoSettingsFrame: public CATDlgFrame
{
	
public:
	
	/**
	* This method initializes the frame member variables.
	*/
	CAAPeoUserAlgoSettingsFrame( CATDialog *iParent,CATDlgStyle iStyle, const CATString& iDialogObjectName);
	virtual ~CAAPeoUserAlgoSettingsFrame();

	/**
	* This method builds the frame and puts the callbacks used to update the
	* user algorithm settings.
	*/
	virtual HRESULT Build(CATIOptAlgorithm_var spiAlgo);

	/**
	* These methods are called each time you modify the corresponding
	* setting, in order to update the algorithm feature.
	*/
	void OnChangeMaxEval(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);
	void OnChangeTime(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);

	
protected:
	
	CATIOptAlgorithm_var _algo;

	CATDlgFrame* _terminationFrm;
	CATDlgLabel* _maxEvalLbl;
	CATDlgEditor* _maxEvalEditor;
	
	CATDlgLabel*		_timeLbl;
	CATDlgEditor*      _timeEditor;
	

		
private:


};

//-----------------------------------------------------------------------

#endif

