#ifndef CAAAfrGeoAnalysisWkb_h
#define CAAAfrGeoAnalysisWkb_h

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
//  Class which represents the CAAAfrGeoAnalysisWkb workbench of the 
//  CATAfrGeometryWks Workshop.
//  It implements the CATIGeometryConfiguration interface which is
//  specified by the workshop as the interface to implement in its
//  workbenches. 
//
//  Illustrates:
//     - creating a workbench 
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
//  CreateWorkbench
//     Creates toolbars and arranges the commands inside
//
//  GetAddinInterface
//     Returns the name of the interface that the addins must implement
//
//===========================================================================

// System Framework
#include <CATBaseUnknown.h> // Needed to derive from CATBaseUnknown
#include "CATListPV.h"      // Needed by GetCustomInterfaces

// ApplicationFrame Framework
class CATCmdWorkbench;      // Needed by CreateWorkbench


class CAAAfrGeoAnalysisWkb : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:

     CAAAfrGeoAnalysisWkb();
     virtual ~CAAAfrGeoAnalysisWkb();

     // CreateCommands
     // ---------------
     // Instantiates the command headers for the commands of the workbench 
     //
     void              CreateCommands();

     // CreateWorkbench
     // ----------------
     // Creates the containers for the workbench, the menus, and the toolbars, 
     // the starters for the commands, and arranges the commands in the menus
     // and toolbars 
     //
     CATCmdWorkbench * CreateWorkbench();
 
     // GetAddinInterface
     // -----------------
     // Returns the name of the interface exposed by the workbench to create
     // add-ins
     //
     CATClassId        GetAddinInterface();

     // GetCustomInterfaces
     // -------------------
     // Useless.
     //
     void GetCustomInterfaces(CATListPV * oDefaultIIDList,
                              CATListPV * oCustomIIDList  ) ;
  
  private:
     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeoAnalysisWkb(const CAAAfrGeoAnalysisWkb &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeoAnalysisWkb & operator = (const CAAAfrGeoAnalysisWkb &iObjectToCopy);

};

#endif
