// COPYRIGHT DASSAULT SYSTEMES 2012
#ifndef CAAV5V6MmrPartWksAdn_H
#define CAAV5V6MmrPartWksAdn_H

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
//
// Note : CAAV5V6MmrPartWksAdn is the same use case as CAAMmrPartWksAdn. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class CATCmdContainer;


class CAAV5V6MmrPartWksAdn : public CATBaseUnknown
{
  CATDeclareClass;
  
  public:
     CAAV5V6MmrPartWksAdn();
     virtual ~CAAV5V6MmrPartWksAdn();
  
     // Creates the command headers
     void CreateCommands();

     // Arranges the commands in toolbars and menubar
     CATCmdContainer * CreateToolbars();

  private :

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAV5V6MmrPartWksAdn(const CAAV5V6MmrPartWksAdn &iObjectToCopy);

     // Assigment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAV5V6MmrPartWksAdn & operator = (const CAAV5V6MmrPartWksAdn &iObjectToCopy);
};
#endif
