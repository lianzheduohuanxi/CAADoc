#ifndef CAAVisModelCuboid_H
#define CAAVisModelCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAAVisModelCuboid component.
//  
//  This class must C++ derives from the implementation class
//  of the component CAAVisModelObject(ie the CAAVisModelObject class ).
//  
//  This class declares too, with the macros CATDeclareClass (in the header file) 
//  and CATImplementClass (in the cpp file), that's the component named, 
//  CAAVisModelCuboid, Object Modeler (OM) derives from the CAAVisModelObject 
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
//  |                       |-o CAAIVisModelCuboid
//  |                       |
//  |  CAAVisModelCuboid    |-o CATI3DGeoVisu      
//  |                       |
//  -------------------------
//
//
//===========================================================================  
//  Usage:
//  ------
//  The component CAAVisModelCuboid is used in the CAAVisManagerAppli Sample 
//
//===========================================================================

// Local framework
#include "CAAVisModelObject.h" // to C++ derives from
#include "CAAVisManagerComp.h" // to export the class

class ExportedByCAAVisManagerComp CAAVisModelCuboid : public CAAVisModelObject
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public :

    CAAVisModelCuboid();
    virtual ~CAAVisModelCuboid();

private :

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAVisModelCuboid(const CAAVisModelCuboid &iObjectToCopy);

   // Assignment operaror, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAVisModelCuboid & operator = (const CAAVisModelCuboid &iObjectToCopy);

};

#endif
