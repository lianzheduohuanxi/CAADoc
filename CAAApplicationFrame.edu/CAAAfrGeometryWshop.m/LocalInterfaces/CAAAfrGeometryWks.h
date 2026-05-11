#ifndef CAAAfrGeometryWks_h
#define CAAAfrGeometryWks_h

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
//  Class which represents the CAAAfrGeometryWks Workshop.
//  It implements the CATIWorkshop interface.
//
//  Illustrates:
//     - creating a workshop
//     - instantiating command headers
//
//===========================================================================
//  Inheritance:
//  ------------
//           CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateCommands
//     Instantiates the command headers
//
//  CreateWorkshop
//     Creates toolbars and arranges the commands inside
//
//  GetWorkbenchInterface
//     Returns the name of the interface that the workbenches must implement
//
//  GetAddinInterface
//     Returns the name of the interface that the addins must implement
//
//===========================================================================
// System Framework
#include <CATBaseUnknown.h>  // Needed to derive from CATBaseUnknown

// ApplicationFrame framework
class CATCmdWorkshop;        // Needed by CreateWorkshop


class CAAAfrGeometryWks : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:

     CAAAfrGeometryWks();
     virtual ~CAAAfrGeometryWks();
  
     // CreateCommands
     // ---------------
     // Instantiates the command headers for the commands of the workshop
     // 
     void             CreateCommands();

     // CreateWorkshop
     // ---------------
     // Creates the containers for the workshop, the menus, and the toolbars,
     // the starters for the commands, and arranges the commands in the menus 
     // and toolbars 
     //
     CATCmdWorkshop * CreateWorkshop();

     // GetWorkbenchInterface
     // ---------------------
     // Returns the name of the interface exposed by the workshop 
     // to create workbenches 
     //
     CATClassId       GetWorkbenchInterface();

     // GetAddinInterface
     // ------------------
     // Returns the name of the interface exposed by the workshop to 
     // create add-ins
     //
     CATClassId       GetAddinInterface();

  private:

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeometryWks(const CAAAfrGeometryWks &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeometryWks & operator = (const CAAAfrGeometryWks &iObjectToCopy);
};

#endif
