// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrQueryExploreCmd.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h"

// Dialog Framework 
#include "CATDlgProgress.h"
#include "CATInteractiveApplication.h"

// System Framework
#include "CATFrmEditor.h"
#include "CATApplication.h"

// Mathematic Framework
#include "CATMath.h"

// C++ Standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAAfrQueryExploreCmd);

//-------------------------------------------------------------------------

CAAAfrQueryExploreCmd::CAAAfrQueryExploreCmd(): 
                   CATCommand(NULL,"QueryExplodeCmdId")
{
  cout << "CAAAfrQueryExploreCmd void constructor" << endl ;
  
  // This command is exclusive, by default a CATCommand is undefined	
  RequestStatusChange(CATCommandMsgRequestExclusiveMode);
}

//--------------------------------------------------------------------------

CAAAfrQueryExploreCmd::~CAAAfrQueryExploreCmd()
{
  cout << "CAAAfrQueryExploreCmd destructor" << endl ;
}

//--------------------------------------------------------------------------

CATStatusChangeRC CAAAfrQueryExploreCmd::Activate(CATCommand      *iPublisher,
                                                  CATNotification *iNotification)
{
  cout << "CAAAfrQueryExploreCmd Activate" << endl ;

  CATApplicationFrame * pFrame = NULL ;
  CATDialog * pParent = NULL ;
  pFrame = CATApplicationFrame::GetFrame() ;
  if ( NULL != pFrame )
  {
    // pParent is the Dialog object dedicated to the current document. 
    //
    pParent = pFrame->GetMainWindow() ;
  }
   
  if ( NULL != pParent )
  {
 
        // Creates a progress bar in the status bar
        CATDlgProgress * pProgress = NULL ;
        pProgress = new CATDlgProgress(pParent, "MyProgressBar");

        // Sets the progress bar's properties
        pProgress->SetRange(0, 10);  // progress 
        pProgress->SetStep(1);       // with 1% steps
        pProgress->SetPos(0);        // beginning from 0.
        pProgress->SetVisibility(CATDlgShow);

        // Useful to redraw the progress bar at each step
        CATInteractiveApplication * pInterApplication = NULL ;
        pInterApplication = (CATInteractiveApplication *)CATApplication::MainApplication();
   
        if ( NULL != pInterApplication )
        {
           // Simulation of a long task 
           for (int i=1 ; i <= 10 ; i++)
           {
              // Sets the Cursor busy at each loop
              // because UpdateDisplay(), unsets it. 
              CATApplicationFrame::SetBusyCursor();

              // The long task 
              Compute();

              // Changes the progress bar value 
              pProgress->StepIt();

              // Updates the display of the progress bar 
              pInterApplication->UpdateDisplay() ;
           }

           // Long Task done
           pProgress->SetVisibility(CATDlgHide);
           pProgress->RequestDelayedDestruction();
           pProgress= NULL ;
        }
     }
  
  return CATStatusChangeRCCompleted ;
}

//---------------------------------------------------------------------------------

CATStatusChangeRC CAAAfrQueryExploreCmd::Cancel(CATCommand      *iPublisher,
	                                            CATNotification *iNotification)
{
  cout << "CAAAfrQueryExploreCmd Cancel" << endl ;

  // This method is called when this command is cancelled by another exclusive
  // command. But a simple CATCommand is not automatically deallocated.
  // A request of deallocation must be done here.
  RequestDelayedDestruction();

  return CATStatusChangeRCCompleted ;
}

//---------------------------------------------------------------------------------

void CAAAfrQueryExploreCmd::Compute()
{
  // Simulated task
  double a = 2  ;
  for ( int j= 1 ; j < 10000000 ; j++ )
  {
    a = CATSqrt(a) ;
  }
}
