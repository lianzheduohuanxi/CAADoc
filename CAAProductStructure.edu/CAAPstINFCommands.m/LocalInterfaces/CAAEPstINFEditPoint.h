// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFEditPoint_h
#define CAAEPstINFEditPoint_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFPoint component, implementing the CATIEdit 
//  interface to enable the edition of the points.
//
//  This class derives from the CATExtIEdit adapter.
//
//  Illustrates programming the edition of an object by implementing the CATIEdit
//  interface of the ApplicationFrame framework.
//
//  The CATIEdit interface has 2 methods: Activate and GetPanelItem. 
//  Only Activate needs to be redefined. Its aim is to return a command
//  that edits the object.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATExtIEdit (ApplicationFrame Framework)
//     CATBaseUnknown (System Framework)  
//
//===========================================================================
//  Main Method:
//  ------------
//  
//  Activate: Returns a CATCommand to edit the selected point.
//
//===========================================================================

// ApplicationFrame Framework
#include "CATExtIEdit.h"   // Needed to derive from CATExtIEdit

class CAAEPstINFEditPoint : public CATExtIEdit
{
  CATDeclareClass;

  public :

    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFEditPoint();
    virtual ~CAAEPstINFEditPoint();

    // Activate
    // --------
    // Returns a CATCommand to edit the selected point.
    // iPath is the path from the root object to the selected object
    //
    virtual CATCommand  * Activate(CATPathElement *ipPath);

  private :

    // Copy constructor and assignment operator, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
	//-----------------------------------------------------------------------------------
    CAAEPstINFEditPoint(const CAAEPstINFEditPoint &iObjectToCopy);
    CAAEPstINFEditPoint & operator = (const CAAEPstINFEditPoint &iObjectToCopy);

};
#endif
