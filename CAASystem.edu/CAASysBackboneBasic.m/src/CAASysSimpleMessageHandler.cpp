// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAASysSimpleMessageHandler.h"

//C++ Standard library
#include <iostream.h>      

extern int EndConditionLoop ;

//---------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIMessageReceiver.h"
TIE_CATIMessageReceiver(CAASysSimpleMessageHandler);

// To declare that the class is a component main class
//
CATImplementClass(CAASysSimpleMessageHandler, Implementation, CATBaseUnknown, CATNull);

// 
// To declare that CAASysSimpleMessageHandler implements CATIMessageReceiver 
// insert the following line in the interface dictionary:
//
//    CAASysSimpleMessageHandler CATIMessageReceiver  libCAASysBackboneBasic
//
// 
//---------------------------------------------------------------------------

CAASysSimpleMessageHandler::CAASysSimpleMessageHandler()
{
   cout << "CAASysSimpleMessageHandler::CAASysSimpleMessageHandler()"<< endl;
}

//---------------------------------------------------------------------------

CAASysSimpleMessageHandler::~CAASysSimpleMessageHandler()
{
   cout << "CAASysSimpleMessageHandler::~CAASysSimpleMessageHandler()"<< endl;
}

//---------------------------------------------------------------------------

void CAASysSimpleMessageHandler::HandleMessage(CATICommMsg* iMessage)
{
  cout << " CAASysSimpleMessageHandler::HandleMessage" << endl;
  cout <<endl<< endl;

  cout <<"Backbone daemon present and fully functional" << endl ;
  cout <<"The CAASysReceiverAppli has received the message " ;
  cout <<" from the CAASysSenderAppli " << endl ;
  cout <<endl<< endl;

  // The process can be stopped
  EndConditionLoop ++ ;
}
