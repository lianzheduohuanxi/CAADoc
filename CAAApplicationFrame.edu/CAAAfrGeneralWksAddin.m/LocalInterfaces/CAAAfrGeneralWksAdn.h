// COPYRIGHT DASSAULT SYSTEMES 2002
#ifndef CAAAfrGeneralWksAdn_H
#define CAAAfrGeneralWksAdn_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which represents an addin of the General Workshop.
//  It implements the CATIAfrGeneralWksAddin interface which is
//  specified by the General workshop as the interface to implement in its
//  addins. 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class CATCmdContainer;


class CAAAfrGeneralWksAdn : public CATBaseUnknown
{
  CATDeclareClass;
  
  public:
     CAAAfrGeneralWksAdn();
     virtual ~CAAAfrGeneralWksAdn();
  
     // Creates the command headers
     void CreateCommands();

     // Arranges the commands in toolbars and menubar
     CATCmdContainer * CreateToolbars();

  private :

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeneralWksAdn(const CAAAfrGeneralWksAdn &iObjectToCopy);

     // Assigment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeneralWksAdn & operator = (const CAAAfrGeneralWksAdn &iObjectToCopy);
};
#endif
