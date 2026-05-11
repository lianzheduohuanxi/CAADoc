#ifndef CAAEAfrEditPoint_h
#define CAAEAfrEditPoint_h

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
//  Data extension of the CAASysPoint component, implementing the CATIEdit 
//  interface to enable the edition of the points.
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
// Activate: Returns a CATCommand to edit the selected point.
//
//===========================================================================
// ApplicationFrame Framework
#include "CATExtIEdit.h"   //Needed to derive from CATExtIEdit

class CAAEAfrEditPoint : public CATExtIEdit
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAEAfrEditPoint();
    virtual ~CAAEAfrEditPoint();

    // Activate
    // --------
    // Returns a CATCommand to edit the selected point.
    // iPath is the path from the root object to the selected object
    //
    virtual CATCommand  * Activate(CATPathElement * iPath);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditPoint(const CAAEAfrEditPoint &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditPoint & operator = (const CAAEAfrEditPoint &iObjectToCopy);

};
#endif
