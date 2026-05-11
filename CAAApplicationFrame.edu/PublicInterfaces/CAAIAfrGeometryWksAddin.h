#ifndef CAAIAfrGeometryWksAddin_h
#define CAAIAfrGeometryWksAddin_h

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
//  Interface that the addins of the CAAAfrGeometryWks workshop must implement.
//
//  An addin enables to add new toolbars into a workshop.
//
//  The workshop returns this interface name in its GetAddinInterface method.
//  This interface must derive from CATIWorkbenchAddin.
//
//  Illustrates:
//     - defining an interface for the addins of a workshop
//
//===========================================================================
//  Inheritance:
//  ------------
//       CATIWorkbenchAddin (ApplicationFrame Framework)
//           CATBaseUnknown (System Framework)
//
//===========================================================================
// ApplicationFrame Framework
#include <CATIWorkbenchAddin.h>  // Needed to derive from CATIWorkbenchAddin
// Local Framework
#include "CAAAfrGeometryWshop.h"   // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAAAfrGeometryWshop
extern IID ExportedByCAAAfrGeometryWshop IID_CAAIAfrGeometryWksAddin;


class ExportedByCAAAfrGeometryWshop CAAIAfrGeometryWksAddin : public CATIWorkbenchAddin
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;

  public:
};


#endif
