// COPYRIGHT DASSAULT SYSTEMES 2002
#ifndef CAAMmrDebugAdn_H
#define CAAMmrDebugAdn_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which represents an addin of the Part Document Workshop.
//  It implements the CATIPrtWksAddin interface which is
//  specified by the PartWks workshop as the interface to implement in its
//  addins. 
//
//  Illustrates:
//     - creating a workshop addin
//     - instantiating command headers
//     - using the CATMmuDebugCAA mechanical command 
//
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class CATCmdContainer;


class CAAMmrDebugAdn : public CATBaseUnknown
{
  CATDeclareClass;
  
  public:
     CAAMmrDebugAdn();
     virtual ~CAAMmrDebugAdn();
  
     // Creates the command headers
     void CreateCommands();

     // Arranges the commands in toolbars and menubar
     CATCmdContainer * CreateToolbars();

  private :

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAMmrDebugAdn(const CAAMmrDebugAdn &iObjectToCopy);

     // Assigment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAMmrDebugAdn & operator = (const CAAMmrDebugAdn &iObjectToCopy);
};
#endif
