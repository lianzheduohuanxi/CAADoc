// COPYRIGHT DASSAULT SYSTEMES  2002
//-------------------------------------------------------------
//
// Implementation of the CATIOptAlgorithmUIFactory interface
// for the feature CAAPeoUserAlgo by using the CATOptAlgorithmUIFactoryAdapter..
// It allows the user algorithm to be visible in the Optimizer UI.
//
// In the current .dic, we have added the following row:
// CAAPeoUserAlgo	CATIOptAlgorithmUIFactory	LibCAAPeoCreateUserAlgorithm
//
//-------------------------------------------------------------

#ifndef _CAAPeoUserAlgoUIFactory_
#define _CAAPeoUserAlgoUIFactory_

#include "CATBaseUnknown.h"

#include "CATOptAlgorithmUIFactoryAdapter.h"

// OptimizationInterfaces
#include "CATIOptOptimization.h"

// Dialog
#include "CATDlgFrame.h"
#include "CATDlgDialog.h"


//----------------------------------------------------------------------

class CAAPeoUserAlgoUIFactory : public CATOptAlgorithmUIFactoryAdapter
{

  CATDeclareClass;

  public:

	CAAPeoUserAlgoUIFactory();
	virtual ~CAAPeoUserAlgoUIFactory();

	/**
	* This method instanciates and builds a CAAPeoUserAlgoSettingsFrame that will allow
	* interactiv changes of the user algorithm settings (Radio buttons, checks, 
	* text editor...).
	* @param iFather
	* the father dialog object of the instanciated frame . This object is automatically
	* given by the Optimizer UI as soon as you choose the CAAPeoUserAlgorithm in the algorithms list.
	* @param iStyle
	* the style of the instanciated frame . It is automatically
	* given by the Optimizer UI as soon as you choose the CAAPeoUserAlgorithm
	* in the algorithms list in order to be in accordance with the dialog configuration.
	* @return
	* the instanciated frame.
    */
	CATDlgFrame* CreateAlgoSettingsFrame(CATDialog* iFather, CATDlgStyle iStyle);


	/*
	* This method instanciates and builds a CAAPeoUserAlgoStopDialog that will
	* give the run progress and allow the manual algorithm run interruption.
	* @param iFather
	* the father dialog object of the instanciated dialog object . The father is automatically
	* given by the Optimizer UI as soon as you launch the CAAPeoUserAlgorithm algorithm.
	* @param iStyle
	* the style of the instanciated dialog . It is automatically
	* given by the Optimizer UI as soon as you launch the CAAPeoUserAlgorithm algorithm
	* in order to be in accordance with the dialog configuration.
	* @return
	* the instanciated stop dialog.
	*/
	CATDlgDialog* CreateStopAlgoDialog(CATDialog* iFather, CATDlgStyle iStyle,const CATIOptOptimization_var& iOptim);
  
  private:

};

//----------------------------------------------------------------------

#endif
