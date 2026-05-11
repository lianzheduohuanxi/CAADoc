// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgTimeOutCommand.h"
#include "CAADlgInterApplication.h"

//C++ standard Library
#include <iostream.h>
//------------------------------------------------------------------------

CAADlgTimeOutCommand::CAADlgTimeOutCommand(CAADlgInterApplication * iParent): 
                  CATCommand((CATApplication *)iParent) 
{
  cout << "The Command which sets a time out is created" << endl; 

  if ( NULL != iParent )
  {
     // in 5ms, the CAADlgTimeOut method should be called
     int    Time       = 5 ;
     void * UsefulData = (void*) iParent ;

     // Time out sets on the application
     iParent->AddTimeOut(Time, this, UsefulData, (void (*)())CAADlgTimeOutCommand::CAADlgTimeOut);
  }
}

//------------------------------------------------------------------------

CAADlgTimeOutCommand::~CAADlgTimeOutCommand()
{
  cout << "The Command which sets a time out is deleted" << endl; 
}

//------------------------------------------------------------------------

void CAADlgTimeOutCommand::CAADlgTimeOut(CATCommand * iToClient  , 
                                         int          iTime, 
                                         void       * iUsefulData) 
{
  cout << "The time of " << iTime << "ms is ellapsed" << endl;

  if (NULL != iUsefulData )
  {
     // The UsefulData is my application
     CAADlgInterApplication * pMyApplication = (CAADlgInterApplication *) iUsefulData;
     
     // That's finished the current interactive application 
     pMyApplication->Destroy() ;
  }
}

//------------------------------------------------------------------------
