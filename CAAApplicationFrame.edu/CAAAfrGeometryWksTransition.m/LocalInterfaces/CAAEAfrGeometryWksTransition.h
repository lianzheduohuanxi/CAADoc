#ifndef CAAEAfrGeometryWksTransition_h
#define CAAEAfrGeometryWksTransition_h

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
//  Extension of the CAAAfrGeometryWks workshop which enables to manage the
//  transitions to this workshop.
//  This is useful when the user selects the workshop from the start menu.
//
//  This class implements the CATIWorkbenchTransition interface and is
//  a data extension of a late type, whose name is composed of:
//  workshopName + "_trans".
//  It derives from the CATExtIWorkbenchTransition adapter.
//  It gives the document type associated with the workshop,
//  so that a document of this type can be activated or created when the
//  workshop is selected.
//
//  Illustrates:
//    Managing workshop transitions.
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATExtIWorkbenchTransition   (ApplicationFrame Framework)
//            CATBaseUnknown (System Framework)
//
//===========================================================================
// ApplicationFrame Framework 
#include "CATExtIWorkbenchTransition.h"   // Need to derive from

class CAAEAfrGeometryWksTransition : public CATExtIWorkbenchTransition
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:


     CAAEAfrGeometryWksTransition();
     virtual ~CAAEAfrGeometryWksTransition();
  
     // DoTransition
     // ------------
     //  Executes the default code from CATExtIWorkbenchTransition
     //  the document _newDoc is opened except if :
     //      - the user requests a workbench of the same workshop (in this case, 
     //        the document is already opened) 
     //      - toWS is not the workshop extending with the current class
     //
	 // Returns 1 if it actually performs the transition, 
	 //         0 to let CATIA do it. 
     int DoTransition( const CATString & ifromWS ,
                       const CATString & ifromWB ,
                       const CATString & itoWS   ,
                       const CATString & itoWB   );

  private:

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAEAfrGeometryWksTransition(const CAAEAfrGeometryWksTransition &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAEAfrGeometryWksTransition & operator = (const CAAEAfrGeometryWksTransition &iObjectToCopy);

};

#endif
