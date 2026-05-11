#ifndef CAADegGeoSDOAdn_H
#define CAADegGeoSDOAdn_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which represents an addin of the CAAAfrGeoCreationWkb Workbench.
//  It implements the CAAIAfrGeoCreationWkbAddin interface which is
//  specified by the workbench as the interface to implement in its
//  addins. 
//
//  Illustrates:
//     - creating a workbench addin
//     - instantiating a CATCommandHeaderWithSDOForAgent
//
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


class CAADegGeoSDOAdn : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:
     CAADegGeoSDOAdn();
     virtual ~CAADegGeoSDOAdn();

     // Instantiates the command headers for the commands
     void CreateCommands();

     // Creates toolbars and arranges the commands inside
     CATCmdContainer * CreateToolbars();
  
  private:

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAADegGeoSDOAdn(const CAADegGeoSDOAdn &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAADegGeoSDOAdn & operator = (const CAADegGeoSDOAdn &iObjectToCopy);

};
#endif
