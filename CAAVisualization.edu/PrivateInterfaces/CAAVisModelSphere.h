#ifndef CAAVisModelSphere_H
#define CAAVisModelSphere_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAAVisModelSphere component.
//  
//  This class must C++ derives from the implementation class
//  of the component CAAVisModelObject(ie the CAAVisModelObject class ).
//  
//  This class declares too, with the macros CATDeclareClass (in the header file) 
//  and CATImplementClass (in the cpp file), that's the component named, 
//  CAAVisModelSphere, Object Modeler (OM) derives from the CAAVisModelObject 
//  component.
//  
// 
//  -----------------------
//  |                     |
//  | CAAVisModelObject   |-o CAAIVisModelObject 
//  |                     |-o CAAIVis2DGraphVisu 
//  | impl                |-o CATIModelEvents    
//  ---+-----------------+-
//     |                 |
//     | C++ Derivation  | OM Derivation 
//     | of the          | of the component
//     | implementation  |
//     |                 |
//     |                 |
//     |                 |
//  ---^-----------------^---
//  | impl                  |
//  |                       |-o CAAIVisModelSphere 
//  |                       |
//  |  CAAVisModelSphere    |-o CATI3DGeoVisu      
//  |                       |
//  -------------------------
//
//
//===========================================================================  
//  Usage:
//  ------
//  The component CAAVisModelSphere is used in the CAAVisManagerAppli Sample 
//
//===========================================================================

//Local FrameWork
#include "CAAVisModelObject.h"  // to derive from
#include "CAAVisManagerComp.h" // to export the class 

class ExportedByCAAVisManagerComp CAAVisModelSphere : public CAAVisModelObject
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public :
   
   CAAVisModelSphere ();
   virtual ~ CAAVisModelSphere ();

private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAVisModelSphere(const CAAVisModelSphere &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAVisModelSphere & operator = (const CAAVisModelSphere &iObjectToCopy);

};

#endif
