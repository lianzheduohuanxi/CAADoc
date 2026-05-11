#ifndef CAAAfrGeoChartWindowAdn_H
#define CAAAfrGeoChartWindowAdn_H

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
//  Class which represents an addin of the CAAAfrGeometryWks Workshop.
//  It implements the CAAIAfrGeometryWksAddin interface which is
//  specified by the workshop as the interface to implement in its
//  addins. 
//
//  Illustrates:
//     - creating a workshop addin
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
//  CreateToolbars
//     Creates toolbars/modifies the menubar and arranges the commands inside
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown 

// ApplicationFrame framework
class CATCmdContainer;      // Needed by CreateToolbars

class CAAAfrGeoChartWindowAdn : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:

     CAAAfrGeoChartWindowAdn();
     virtual ~CAAAfrGeoChartWindowAdn();

     // Instantiates the command headers for the commands 
     void CreateCommands();

     // Creates toolbars and arranges the commands inside
     CATCmdContainer * CreateToolbars();

  private:

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeoChartWindowAdn(const CAAAfrGeoChartWindowAdn &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAAfrGeoChartWindowAdn & operator = (const CAAAfrGeoChartWindowAdn &iObjectToCopy);
};
#endif
