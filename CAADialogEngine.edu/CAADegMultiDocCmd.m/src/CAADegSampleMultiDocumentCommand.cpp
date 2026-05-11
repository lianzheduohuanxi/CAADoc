// DialogEngine Framework
#include "CATOtherDocumentAgent.h"

// LocalFramework
#include "CAADegSampleMultiDocumentCommand.h"

// C++ Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegSampleMultiDocumentCommand);


//-------------------------------------------------------------------------

CAADegSampleMultiDocumentCommand::CAADegSampleMultiDocumentCommand() :
  _AcquisitionAgent ("CAADegSampleMultiDocumentCommandId")
{
   cout << "CAADegSampleMultiDocumentCommand::CAADegSampleMultiDocumentCommand"<< endl;
}

//-------------------------------------------------------------------------

CAADegSampleMultiDocumentCommand::~CAADegSampleMultiDocumentCommand()
{
  cout << "CAADegSampleMultiDocumentCommand::~CAADegSampleMultiDocumentCommand"<< endl;
}

//-------------------------------------------------------------------------

void CAADegSampleMultiDocumentCommand::BuildGraph()
{
  cout << "CAADegSampleMultiDocumentCommand::BuildGraph"<< endl;
  
  // -------------
  // Agent Creation
  // -------------

  // _fromCommand is a data of CATMultiDocumentCommand
  //
  if( NULL != _fromCommand )
  {
    // This agent has the same behavior that the behavior of the 
    // CATOtherDocumentAgent defined in the CAADegCreateCylinder2Cmd command
    // 
    _AcquisitionAgent.SetBehavior(_fromCommand->GetBehavior());
  }
  else
  {
    _AcquisitionAgent.SetBehavior(CATDlgEngWithPSOHSO);
  }

  // This agent allows the end user to select circles
  _AcquisitionAgent.SetElementType("CAAISysCircle");
  
  // --------------
  // State Creation
  // --------------

  CATDialogState * pInitialState = GetInitialState("SelectACircleId");
  pInitialState->AddDialogAgent(&_AcquisitionAgent); 

  // -------------------
  // Transition Creation
  // --------------------
  
  CATDialogTransition *pTransition= AddTransition
  (
     pInitialState,
     NULL,
	 NULL,
	 Action((ActionMethod) &CAADegSampleMultiDocumentCommand::SelectionDone)
  ) ;
  
}

//-------------------------------------------------------------------------

CATBoolean CAADegSampleMultiDocumentCommand::SelectionDone(void * iDummy)
{
  cout << "CAADegSampleMultiDocumentCommand::SelectionDone"<< endl;

  CATBoolean OKCode = FALSE;

  // The CATOtherDocumentAgent will be valuated
  //
  if (_AcquisitionAgent.GetBehavior() & CATDlgEngMultiAcquisition)
  {
	// The agent instantiated in the CAADegCreateCylinder2 command 
	// will be valuated 
    ReturnListOfValues(_AcquisitionAgent.GetListOfValues());
  }
  else
  {
	// The agent instantiated in the CAADegCreateCylinder2 command 
	// will be valuated 
    ReturnValue(_AcquisitionAgent.GetValue());
  }

  OKCode = TRUE;
  
  return OKCode;
}

//-------------------------------------------------------------------------
