// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  This Sample illustrates how to use the backbone bus to communicate beetween 
//  applications:
//
//    - Connection to the backbone bus
//    - Creation of message class with or without data 
//    - Declaration of message class that an application can receive
//    - Send a message 
//    - wait a message
// 
//=============================================================================
//  Abstract of the main
//  --------------------
//
//  Creation of a connection to the backbone for the application named 
//  CAASysReceiverAppli. This application can receive two kinds of message:
//     - a simple message 
//     - a message with data about Circle ( nb, color, radius ... )
//  
//  Creation of a connection to the backbone for the application named 
//  CAASysSenderAppli. This application sends a simple message and a message
//  with data. 
//  
//  
//=============================================================================
//  How to launch:
//  -------------
//
//  Type in two processes and in this order:
//
//   1)   CAASysBackboneBasic receiver 
//   2)   CAASysBackboneBasic sender
//  
//  The different traces of the sample appears on the standard output.
//
//  Return Code:
//     0 : OK
//     1 : KO
//     2 : KO , pb in the backbone bus connexion
//
//=============================================================================

//C++ Standard library
#include <iostream.h>      

// System Framework 
#include  "CATString.h"  // to read the argument

// All Code for an application seen has message receiver
#include "CAASysCodeForReceiver.h"

// All Code for an application seen has message sender
#include "CAASysCodeForSender.h"

int main(int argc, char* argv[])
{
  int ReturnCode = 0;

  cout << endl << "The Sample CAASysBackboneBasic begins....." << endl<<endl;

  //------------------
  // Arguments to test
  //------------------
  if ( 2 != argc )
  {
    cout <<"Usage: CAASysBackboneBasic (receiver | sender)"<< endl;
    cout <<"  sender  -> The application is seen has a message's sender" << endl;
    cout <<"  receiver-> The application is seen has a message's receiver" << endl;
    cout <<" Launch first with the [receiver] argument"<< endl;
    ReturnCode = 1 ;
      
  } else
  {

     CATString InputName=argv[1];

     if ( 0 == InputName.Compare("receiver") )
     { 
        // All Code for an application seen has message receiver
        ReturnCode = CAASysCodeForReceiver();

     }else if ( 0 == InputName.Compare("sender") )
     {      
        // All Code for an application seen has message sender
        ReturnCode = CAASysCodeForSender();

     }else
     {
       cout <<"Usage: CAASysBackboneBasic (receiver | sender)"<< endl;
       cout <<"  sender  -> The application is seen has a message's sender" << endl;
       cout <<"  receiver-> The application is seen has a message's receiver" << endl;
       cout <<" Launch first with the [receiver] argument"<< endl;
       ReturnCode = 1 ;
     }
  }
  
  cout << endl << "The Sample CAASysBackboneBasic is finished" << endl<<endl;

  return ReturnCode ;
}
