#ifndef  CAASysSimpleMessage_H
#define  CAASysSimpleMessage_H

// COPYRIGHT DASSAULT SYSTEMES 2000   

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  Message class for backbone. This Message is without data 
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
//
//=============================================================================
// System Framework
#include "CATBBMessage.h" 

class  CAASysSimpleMessage : public CATBBMessage
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;
  
   public:

      CAASysSimpleMessage();
      virtual ~CAASysSimpleMessage();

      // CATIStreamMsg Interface
      virtual HRESULT UnstreamData  ( void  *iBuffer, uint32  iLen);
      virtual HRESULT StreamData    ( void **oBuffer, uint32 *oLen);
      virtual HRESULT FreeStreamData( void  *iBuffer, uint32  iLen);
      virtual HRESULT SetMessageSpecifications();
  
  private:

      // Copy constructor, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAASysSimpleMessage(const CAASysSimpleMessage &iObjectToCopy);

      // Assignment operator, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAASysSimpleMessage & operator = (const CAASysSimpleMessage &iObjectToCopy);
};

#endif
