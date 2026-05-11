#ifndef  CAADlgBBEditorMessageHandler_H
#define  CAADlgBBEditorMessageHandler_H

// COPYRIGHT DASSAULT SYSTEMES 2000	

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Callback class for the  CAADlgBBEditorMessage message class. 
//  
//  When an application receives a CAADlgBBEditorMessage message the 
//  handleMessage method is called.
//
//=============================================================================
// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CATICommMsg ;

class  CAADlgBBEditorMessageHandler : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;
  
   public:
      CAADlgBBEditorMessageHandler();
      virtual ~CAADlgBBEditorMessageHandler();

      // CATIMessageReceiver Interface
      // ------------------------------
      // iMessage is an interface pointer on the CAADlgBBEditorMessage
      // component.
      //
      void HandleMessage(CATICommMsg * iMessage) ;

  private:

      // Copy constructor, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAADlgBBEditorMessageHandler(const CAADlgBBEditorMessageHandler &iObjectToCopy);

      // Assignment operator, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAADlgBBEditorMessageHandler & operator = (const CAADlgBBEditorMessageHandler &iObjectToCopy);
};

#endif
