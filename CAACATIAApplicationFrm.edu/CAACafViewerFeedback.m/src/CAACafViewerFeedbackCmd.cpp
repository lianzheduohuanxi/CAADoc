// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAACafViewerFeedbackCmd.h"
#include "CAACafViewerFeedbackManager.h"

//C++ standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClassArg(CAACafViewerFeedbackCmd,void *);

//-------------------------------------------------------------------------

CAACafViewerFeedbackCmd::CAACafViewerFeedbackCmd(void *iArgument): 
                       CATCommand(NULL,"CAACafViewerFeedbackCmdId")
{
  cout << "CAACafViewerFeedbackCmd void constructor" << endl ; 
 
  // Retrieves the unique CAACafViewerFeedbackManager class instance
  // which manages the visual feedback
  //
  CAACafViewerFeedbackManager * pCAACafViewerFeedbackManager = NULL ;
  CAACafViewerFeedbackManager::GetManager(&pCAACafViewerFeedbackManager);
  if ( NULL != pCAACafViewerFeedbackManager )
  {
     int state = CATPtrToINT32(iArgument) ;

     if ( 1 == state )
     {
        pCAACafViewerFeedbackManager->SetViewerFeedbackOn();
     }else
     {
        pCAACafViewerFeedbackManager->SetViewerFeedbackOff();
     }

     pCAACafViewerFeedbackManager->Release();
     pCAACafViewerFeedbackManager = NULL ;
  }

   // This command is undefined, once a CATCommand is by default undefined.
   // It means that it is not seen by the focus manager, and by consequence 
   // it cannot be activated , deactivated or even canceled. So this command,
   // launched by a command header, must do a suicide.
   // But attention, a RequestDelayedDestruction in a constructor if possible
   // only if the three following conditions are ALL met:
   // 
   // 1 - The class is not derived and will be never derived
   // 2 - The class has any methods, to avoid to call them after the constructor
   // 3 - RequestDelayedDestruction is the last instruction of the constructor
   // 
  RequestDelayedDestruction();
}

//--------------------------------------------------------------------------

CAACafViewerFeedbackCmd::~CAACafViewerFeedbackCmd()
{
  cout << "CAACafViewerFeedbackCmd destructor" << endl ;
}

