#ifndef CAAPriPrtCfgAdn_H
#define CAAPriPrtCfgAdn_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which represents an addin of the Part Design Workbench.
//  It implements the CATIPrtCfgAddin interface which is
//  specified by the PrtCfg workbench as the interface to implement for its
//  addins. 
//
//  Illustrates:
//     - creating a workbench addin
//     - instantiating command headers
//
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

// ApplicationFrame framwork
class CATCmdContainer;       // Needed by CreateToolbars


class CAAPriPrtCfgAdn : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:
     CAAPriPrtCfgAdn();
     virtual ~CAAPriPrtCfgAdn();

     // Instantiates the command headers for the commands
     void CreateCommands();

     // Creates toolbars and arranges the commands inside
     CATCmdContainer * CreateToolbars();
  
  private:

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAPriPrtCfgAdn(const CAAPriPrtCfgAdn &iObjectToCopy);

     // Assigment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAPriPrtCfgAdn & operator = (const CAAPriPrtCfgAdn &iObjectToCopy);

};
#endif
