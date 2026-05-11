#ifndef  CAASysSimpleMessageHandler_H
#define  CAASysSimpleMessageHandler_H

// COPYRIGHT DASSAULT SYSTEMES 2000   

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  Callback class for the  CAASysDataMessage message class. 
//  
//  When an application receives a CAASysDataMessage message the 
//  handleMessage method is called.
//  
//=============================================================================
// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CATICommMsg ;

class  CAASysSimpleMessageHandler : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;
  
   public:

   CAASysSimpleMessageHandler();
   virtual ~CAASysSimpleMessageHandler();

   // CATIMessageReceiver Interface
   // ------------------------------
   // iMessage is an interface pointer on the CAASysDataMessage
   // component.
   //
   void HandleMessage(CATICommMsg * iMessage) ;

  private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAASysSimpleMessageHandler(const CAASysSimpleMessageHandler &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAASysSimpleMessageHandler & operator =(const CAASysSimpleMessageHandler &iObjectToCopy);
};

#endif
