#ifndef CAAVisModelObject_H
#define CAAVisModelObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAAVisModelObject component.
//  
//  This class declares, with the macros CATDeclareClass (in the header file) 
//  and CATImplementClass (in the cpp file), that's CAAVisModelObject
//  is an Object Modeler component
//  
//
//  Interfaces implemented (by extension) by this component:
//
//  -----------------------
//  |                     |
//  | CAAVisModelObject   |-o CAAIVisModelObject 
//  |                     |-o CAAIVis2DGraphVisu 
//  |                     |-o CATIModelEvents    
//  ----------------------
//
//===========================================================================  
//  Usage:
//  ------
//  The component CAAVisModelObject is used in the CAAVisManagerAppli Sample 
//
//===========================================================================

// System Framework 
#include "CATBaseUnknown.h" // To derive from

// Local framework
#include "CAAVisManagerComp.h" // Needed to export the class 

class ExportedByCAAVisManagerComp CAAVisModelObject : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:
  
  CAAVisModelObject();

  virtual ~CAAVisModelObject();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAVisModelObject(const CAAVisModelObject &iObjectToCopy);
  
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAVisModelObject & operator = (const CAAVisModelObject &iObjectToCopy);
  
};


#endif
