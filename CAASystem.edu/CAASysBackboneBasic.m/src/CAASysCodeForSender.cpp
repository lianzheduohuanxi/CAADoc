// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAASysCodeForSender.h"

// System Framework
#include "CATGetBackboneConnection.h" 
#include "CATInstantiateComponent.h" 
#include <CATErrorDef.h>  // For SUCCEEDED macro

// Local Framework
#include "CAAISysDataRequest.h"  // Interface to set/get data on the CAASysDataMessage

//C++ Standard library
#include <iostream.h>  

int CAASysCodeForSender()
{
   cout << "Creation of an application seen has message sender " << endl;

   //----------------------------------------------------
   // Retrieves an instance of a backbone bus (default bus)
   //----------------------------------------------------

   CATICommunicator * pICommunicator = NULL ;
   pICommunicator = ::CATGetBackboneConnection() ;

   if ( NULL == pICommunicator )
   {
      cout << "Unable to contact the backbone bus"<< endl;
      return 2 ;
   }

   //--------------------------------------------------
   // Declares the current application under the 
   // identificator: CAASysSenderAppli 
   //--------------------------------------------------
   CATApplicationClass SenderApplicationId  = "CAASysSenderAppli" ;

   HRESULT rc=pICommunicator->Declare(SenderApplicationId);
   if ( FAILED(rc) )
   { 
      cout << "Unable to declare on the backbone bus "<< endl;
   }

   // Identificator on the backbone bus of the receiver application
   // 
   CATApplicationClass ReceiverApplicationId = "CAASysReceiverAppli" ;

   //--------------------------------------------------
   // Send the first message 
   //--------------------------------------------------

   if ( SUCCEEDED(rc) )
   {
      cout << "CAASysSenderAppli is declared on the backbone bus" << endl;
         
      CATICommMsg * pICommMsg =NULL;
      rc = ::CATInstantiateComponent("CAASysSimpleMessage",
	                       IID_CATICommMsg,
			               (void **)&pICommMsg);                    
      if ( SUCCEEDED(rc) )
      {
         // The first message is sent to the CAASysReceiverAppli Application
         //
         rc = pICommunicator->SendRequest(ReceiverApplicationId, pICommMsg);
         if ( SUCCEEDED(rc) )
         {
            cout << " Send is successful" << endl;
		 }else
         {
           cout << " Send is unsuccessful" << endl;
         } 

         pICommMsg->Release();
         pICommMsg = NULL ;
	  }


   }
  
   //--------------------------------------------------
   // Send the second message
   //--------------------------------------------------

   if ( SUCCEEDED(rc) )
   {
      cout << "CAASysSenderAppli is declared on the backbone bus" << endl;
         
      CAAISysDataRequest * pIRequest = NULL ;
      rc = ::CATInstantiateComponent("CAASysDataMessage",
	                       IID_CAAISysDataRequest,
			               (void **)&pIRequest);  
             
      if ( SUCCEEDED(rc) )
      {
         float Radius = 1.9f ;
         int Nb = 2      ;

         float Sags[3]   ;
         Sags[0] = 1.0f  ;
	     Sags[1] = 0.5f ;
         Sags[2] = 0.02f ;

         pIRequest->SetData(Radius,Nb,"Red",Sags) ;

         CATICommMsg * pICommMsg =NULL;
         rc = pIRequest->QueryInterface(IID_CATICommMsg,(void**)&pICommMsg);
                                                 
         if ( SUCCEEDED(rc) )
         {
            rc = pICommunicator->SendRequest(ReceiverApplicationId, pICommMsg);
            if ( SUCCEEDED(rc))
            {
              cout << " Send is successful" << endl;
            }else
            {
              cout << " Send is unsuccessful" << endl;
            } 

            pICommMsg->Release();
            pICommMsg = NULL ;
         }
      
         pIRequest->Release();
         pIRequest = NULL ;
      }
   }

   pICommunicator->Release();
   pICommunicator = NULL ;

   if ( SUCCEEDED(rc) )
   {
      return 0 ;
   }else
   {
      return 1 ;
   }
}
