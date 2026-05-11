#ifndef CATICAAAfrGeometryWksConfiguration_h
#define CATICAAAfrGeometryWksConfiguration_h

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
//  Interface that the workbenches of the CAAAfrGeometryWks workshop must 
//  implement.
//
//  The workshop returns this interface name in its GetWorkbenchInterface method.
//  This interface must derive from CATIWorkbench. Its name must be composed of
//  "CATI" + workshopName + "Configuration".
//
//  Illustrates:
//     - defining an interface for the workbenches of a workshop
//
//===========================================================================
//  Inheritance:
//  ------------
//       CATIWorkbench (ApplicationFrame Framework)
//           CATBaseUnknown (System Framework)
//
//===========================================================================

// ApplicationFrame Framework
#include <CATIWorkbench.h>     // Needed to derive from CATIWorkbench

// Local Framework
#include "CAAAfrGeometryWshop.h" // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAAAfrGeometryWshop
extern IID ExportedByCAAAfrGeometryWshop IID_CATICAAAfrGeometryWksConfiguration;

class ExportedByCAAAfrGeometryWshop CATICAAAfrGeometryWksConfiguration : public CATIWorkbench
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;

  public:
};


#endif
