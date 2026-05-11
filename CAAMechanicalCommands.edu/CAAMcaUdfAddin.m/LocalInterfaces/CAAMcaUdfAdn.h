#ifndef CAAMcaUdfAdn_H
#define CAAMcaUdfAdn_H

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which represents an addin of the Generative Shape Design Workbench.
//  It implements the CATIShapeDesignWorkshopAddin interface.
//
//  Illustrates:
//     - creating a workbench addin
//     - instantiating a command which creates and edits a user feature
//
//=========================================================================== 
//  How to launch 
//  -------------
//  
//  1) Remove the # sign before the following line in the interface dictionary 
//     CAAMcaUdfAddin  CATIShapeDesignWorkshopAddin libCAAMcaUdfAddin
//  2) Launch CNext 
//  3) Select the Generative Shape Design workbench in the Start menu 
//  
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateCommands
//     Instantiates the command headers
//
//  CreateToolbars
//     Creates toolbars and arranges the commands inside
//
//===========================================================================
// System framework
#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

// ApplicationFrame framwork
class CATCmdContainer;       // Needed by CreateToolbars


class CAAMcaUdfAdn : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:
     CAAMcaUdfAdn();
     virtual ~CAAMcaUdfAdn();

     // Instantiates the command headers for the commands
     void CreateCommands();

     // Creates toolbars and arranges the commands inside
     CATCmdContainer * CreateToolbars();
  
  private:

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAMcaUdfAdn(const CAAMcaUdfAdn &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAMcaUdfAdn & operator = (const CAAMcaUdfAdn &iObjectToCopy);

};
#endif
