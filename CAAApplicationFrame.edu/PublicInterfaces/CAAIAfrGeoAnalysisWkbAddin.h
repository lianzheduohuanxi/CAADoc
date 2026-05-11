#ifndef CAAIAfrGeoAnalysisWkbAddin_h
#define CAAIAfrGeoAnalysisWkbAddin_h

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
//  Interface that the addins of the CAAAfrGeoAnalysisWkb workbench must implement.
//
//  An addin enables to add new toolbars into a workbench.
//
//  The workbench returns this interface name in its GetAddinInterface method.
//  This interface must derive from CATIWorkbenchAddin.
//
//  Illustrates:
//     - defining an interface for the addins of a workbench
//
//===========================================================================
//  Inheritance:
//  ------------
//       CATIWorkbenchAddin (ApplicationFrame Framework)
//           CATBaseUnknown (System Framework)
//
//===========================================================================
// ApplicationFrame Framework
#include <CATIWorkbenchAddin.h>       //Needed to derive from CATIWorkbenchAddin

// Local Framework
#include "CAAAfrGeoAnalysisWbench.h"  //Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAAAfrGeoAnalysisWkb
extern IID ExportedByCAAAfrGeoAnalysisWbench IID_CAAIAfrGeoAnalysisWkbAddin;

class ExportedByCAAAfrGeoAnalysisWbench  CAAIAfrGeoAnalysisWkbAddin: public CATIWorkbenchAddin
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:
};


#endif
