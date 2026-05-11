// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAASysDataMessageHandler.h"

//C++ Standard library
#include <iostream.h>
      
// Local Framework
#include <CAAISysDataRequest.h> // Interface implemented by the message class
                                // to retrieve data 

// System Framework
#include <CATErrorDef.h> // for the SUCCEDED macro 

// To indicate the end of the application
extern int EndConditionLoop ;

//---------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIMessageReceiver.h"
TIE_CATIMessageReceiver(CAASysDataMessageHandler);

// To declare that the class is a component main class
//
CATImplementClass(CAASysDataMessageHandler, Implementation, CATBaseUnknown, CATNull);

// 
// To declare that CAASysDataMessageHandler implements CATIMessageReceiver 
// insert the following line in the interface dictionary:
//
//    CAASysDataMessageHandler CATIMessageReceiver  libCAASysBackboneBasic
//
// 
//---------------------------------------------------------------------------

CAASysDataMessageHandler::CAASysDataMessageHandler()
{
   cout << "CAASysDataMessageHandler::CAASysDataMessageHandler()"<< endl;
}

//---------------------------------------------------------------------------

CAASysDataMessageHandler::~CAASysDataMessageHandler()
{
   cout << "CAASysDataMessageHandler::~CAASysDataMessageHandler()"<< endl;
}

//---------------------------------------------------------------------------

void CAASysDataMessageHandler::HandleMessage(CATICommMsg* iMessage)
{
  //
  // This Handle is dedicated to the CAASysDataMessage class message 
  //
  cout << " CAASysDataMessageHandler::HandleMessage " << endl ;
  cout <<endl<< endl;

  if ( NULL != iMessage )
  {
     CAAISysDataRequest * pIRequest = NULL ;
     HRESULT rc = iMessage->QueryInterface(IID_CAAISysDataRequest,(void**) &pIRequest);
     if ( SUCCEEDED(rc) )
     {

        float Radius ;
        int   Nb ;
        float * Sags = NULL ;
        char  * Color = NULL ; 

        pIRequest->GetData(Radius,Nb,&Color,&Sags); 
        pIRequest->Release();
        pIRequest = NULL ;

        cout << "The Radius of each Circle is= " << Radius << endl;

        cout << "The Number of Circle is=" << Nb << endl;

        if ( NULL != Color)
        {
           cout << "The Number of each Circle is= " << Color << endl;
           delete [] Color ;
           Color = NULL ;
        }else
        {
           cout << "The Number of each Circle is undefined" << endl;
        }
    
        if ( NULL != Sags )
        {
           cout <<"Each Circle can be drawn with 3 sag = "<< Sags[0] << ", " << Sags[1] <<", " << Sags[2] << endl;
           delete [] Sags ;
           Sags = NULL ;
        }else
        {
           cout <<"Each Circle is drawn with the default sag = " << endl;
        }
    } 
     
  } 

  // The process can be stopped
  EndConditionLoop ++ ;
}
