#ifndef CAAEAfrEditPlane_h
#define CAAEAfrEditPlane_h

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
//  Data extension of the CAASysPlane component, implementing the CATIEdit 
//  interface to enable the edition of the planes.
//  This class derives from the CATExtIEdit adapter.
//
//  Illustrates:
//     programming the edition of an object by implementing the CATIEdit
//     interface.
//
//  The CATIEdit interface has 2 methods: Activate and GetPanelItem. 
//  Only Activate needs to be redefined. Its aim is to return a command
//  be edits the object.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATExtIEdit ( ApplicationFrame Framework) 
//                CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//  
// Activate: Returns a CATCommand to edit the selected plane
//
//===========================================================================

// APplicationFrame framework
#include "CATExtIEdit.h" // Needed to derive from CATExtIEdit

class CAAEAfrEditPlane : public CATExtIEdit
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAEAfrEditPlane();
    virtual ~CAAEAfrEditPlane();

    // Activate
    // --------
    // Creates the plane dialog box and returns it. 
    //
    // iPath is the path from the root object to the selected object
    //
    virtual CATCommand  * Activate(CATPathElement * iPath);

 private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditPlane(const CAAEAfrEditPlane &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditPlane & operator = (const CAAEAfrEditPlane &iObjectToCopy);

};
#endif
