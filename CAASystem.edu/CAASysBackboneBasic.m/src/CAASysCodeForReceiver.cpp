// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAASysCodeForReceiver.h"

//C++ Standard library
#include <iostream.h>    
   
// System Framework
#include "CATGetBackboneConnection.h"        
#include "CATICommunicator.h"        
#include "CATICommunicatorLoop.h"    // To wait a message
#include "CATIMessageReceiver.h"     // To set the handle class
#include <CATErrorDef.h>             // for the SUCCEEDED macro

// Local framework 
// Class Message and handle Class 
#include "CAASysSimpleMessageHandler.h"
#include "CAASysDataMessageHandler.h"

// Global value to indicate the end of the process when the two messages
// are received.
//
int EndConditionLoop = 0 ;


int CAASysCodeForReceiver()
{
   int ReturnCode = 1 ;

   cout << "Creation of an application seen has message receiver " << endl;

   // Data used after
   CATIMessageReceiver        * pIMessageReceiver  = NULL ;
   CATIMessageReceiver        * pIMessageReceiver2 = NULL ;
   CATApplicationClass ReceiverApplicationId   = "CAASysReceiverAppli" ;
   CATMessageClass     SimpleMessClassName     = "CAASysSimpleMessage" ;
   CATMessageClass     DataMessClassName       = "CAASysDataMessage";

   HRESULT rc= E_FAIL ;

   //----------------------------------------------------
   // Retrieves an instance of a backbone bus 
   //----------------------------------------------------
   CATICommunicator * pICommunicator = NULL ;
   pICommunicator = ::CATGetBackboneConnection() ;

   if ( NULL == pICommunicator )
   {
      cout << "unable to contact backbone bus"<< endl;
      return 2 ;
   }
   //--------------------------------------------------
   // Declares the current application with the 
   // CAASysReceiverAppli identificator on the backbone bus
   //--------------------------------------------------
   
   rc=pICommunicator->Declare(ReceiverApplicationId);
   if ( FAILED(rc) )
   { 
      cout << "Unable to declare the application on the backbone bus "<< endl;
   }else
   {
      cout << "CAASysReceiverAppli is declared on the backbone bus" << endl;
   }
      
   if ( SUCCEEDED(rc) )
   {
      //--------------------------------------------------
      // Declares message class that the application
      // CAASysReceiverAppli can receive
      //
      //--------------------------------------------------

           
      CAASysSimpleMessageHandler * pHandler  = NULL ;
      pHandler = new  CAASysSimpleMessageHandler();
           
      if ( NULL != pHandler )
      {
         rc = pHandler->QueryInterface(IID_CATIMessageReceiver,
                                                 (void**)&pIMessageReceiver);
           
         if ( SUCCEEDED(rc) )
         {
             rc=pICommunicator->AssociateHandler(ReceiverApplicationId, 
                                            SimpleMessClassName,
                                            pIMessageReceiver);
             if ( FAILED(rc) )
             {
                cout <<"Unable to associate Handler to the backbone bus"<< endl;
             }else
             {   
                cout <<"OK to associate Handler to the backbone bus"<< endl;
             }
         }

         pHandler->Release();
         pHandler = NULL ;
      }

   }

   if ( SUCCEEDED(rc) )
   {
         //--------------------------------------------------
         // Declares message class that the application 
         // CAASysReceiverAppli can receive
         //--------------------------------------------------
           
         CAASysDataMessageHandler * pHandler        = NULL ;
         pHandler = new  CAASysDataMessageHandler();

         if ( NULL != pHandler )
         {
            rc = pHandler->QueryInterface(IID_CATIMessageReceiver,
                                           (void**)&pIMessageReceiver2);
           
            if ( SUCCEEDED(rc) )
            {
               
               rc=pICommunicator->AssociateHandler(ReceiverApplicationId, 
                                            DataMessClassName,
                                            pIMessageReceiver2);
               if ( FAILED(rc) )
               {
                 cout << "unable to associate Handler to the backbone bus"<< endl;
               }else
               {   
                 cout << "OK to associate Handler to the backbone bus"<< endl;
               } 
            }

            pHandler->Release();
            pHandler = NULL ;
        }

   }

   if ( SUCCEEDED(rc) )
   {
      // All's is OK , the application can receive message 
      // Wait a moment to receive a message 
      //
      CATICommunicatorLoop * pILoop = NULL ;
      rc = pICommunicator->QueryInterface(IID_CATICommunicatorLoop, (void**)&pILoop);
                    
      if ( SUCCEEDED(rc) )
      {
         // In the handler,dedicated to each message, when a
         // message is received, EndConditionLoop is increased. The 
         // Loop is ended when EndConditionLoop is 0 or when the time
         // is over.

         EndConditionLoop = -2 ; 
         pILoop->WaitingLoop(0, 6000 , &EndConditionLoop);

         pILoop ->Release();
         pILoop = NULL ;

         // OK 
         ReturnCode = 0 ;
      }
         
   }

   if ( NULL != pIMessageReceiver )
   {
      // No more need of the handler for the first message class
      pICommunicator->RemoveHandler(ReceiverApplicationId,
                                    SimpleMessClassName,
                                    pIMessageReceiver);
      pIMessageReceiver->Release();
      pIMessageReceiver = NULL ;
   }

   if ( NULL != pIMessageReceiver2 )
   {
      // No more need of the handler for the second message class
      pICommunicator->RemoveHandler(ReceiverApplicationId,
                                    DataMessClassName,
                                    pIMessageReceiver2);
      pIMessageReceiver2->Release();
      pIMessageReceiver2 = NULL ;
   }

   if ( NULL !=  pICommunicator )
   {
      pICommunicator->Release();
      pICommunicator = NULL ;
   }

   return ReturnCode ;
}
