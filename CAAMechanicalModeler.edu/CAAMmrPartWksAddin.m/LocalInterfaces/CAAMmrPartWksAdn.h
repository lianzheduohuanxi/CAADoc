// COPYRIGHT DASSAULT SYSTEMES 2002
#ifndef CAAMmrPartWksAdn_H
#define CAAMmrPartWksAdn_H

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
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class CATCmdContainer;


class CAAMmrPartWksAdn : public CATBaseUnknown
{
  CATDeclareClass;
  
  public:
     CAAMmrPartWksAdn();
     virtual ~CAAMmrPartWksAdn();
  
     // Creates the command headers
     void CreateCommands();

     // Arranges the commands in toolbars and menubar
     CATCmdContainer * CreateToolbars();

  private :

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAMmrPartWksAdn(const CAAMmrPartWksAdn &iObjectToCopy);

     // Assigment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAMmrPartWksAdn & operator = (const CAAMmrPartWksAdn &iObjectToCopy);
};
#endif
