#ifndef  CAADlgBBEditorMessage_H
#define  CAADlgBBEditorMessage_H

// COPYRIGHT DASSAULT SYSTEMES 2000	

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  Message class for backbone. This Message is with data 
//
//  A backbone message is a message which may be sent to another application 
//  through the backbone bus  
//
//  All backbone messages class must   :
//
//      - Declare that it is a component (CATDeclareClass/CATImplementClass)
//         wich OM derives from the CATBBMessage component 
//
//      - C++ Derive from CATBBMessage 
//
//      - Implement CATIStreamMsg   (here in the implementation class )                   
//        --> They must follow correct rules to stream their data
//
//      - Implement by Code Extension CATICreateInstance 
//
//=============================================================================
// System Framework
#include "CATBBMessage.h"


class  CAADlgBBEditorMessage : public CATBBMessage
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;
  
   public:
      CAADlgBBEditorMessage();
      virtual ~CAADlgBBEditorMessage();     

      // ------------------------
      // CATIStreamMsg Interface
      // ------------------------
	  virtual HRESULT StreamData    ( void **oBuffer, uint32 *oLen);
      virtual HRESULT UnstreamData  ( void  *iBuffer, uint32  iLen);
      virtual HRESULT FreeStreamData( void  *iBuffer, uint32  iLen);
      virtual HRESULT SetMessageSpecifications();
  
      // ------------------------
      // CAAIDlgDataRequest Interface
      // ------------------------
      virtual HRESULT GetData  ( char ** oText);
	  virtual HRESULT SetData  (const char *iText) ;
      
  private:

      // Copy constructor, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAADlgBBEditorMessage(const CAADlgBBEditorMessage &iObjectToCopy);

      // Assignment operator, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAADlgBBEditorMessage & operator = (const CAADlgBBEditorMessage &iObjectToCopy);

  private :
 
      // The text to send
      char  * _Text ;

};

#endif
