#ifndef CAAVisModelCGRObject_H
#define CAAVisModelCGRObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAAVisModelCGRObject component.
//  
//  This class must C++ derives from the implementation class
//  of the component CAAVisModelObject(ie the CAAVisModelObject class ).
//  
//  This class declares too, with the macros CATDeclareClass (in the header file) 
//  and CATImplementClass (in the cpp file), that's the component named, 
//  CAAVisModelCGRObject, Object Modeler (OM) derives from the CAAVisModelObject 
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
//  |                       |-o CAAIVisModelCGRObject
//  |                       |
//  |  CAAVisModelCGRObject |-o CATI3DGeoVisu      
//  |                       |
//  -------------------------
//
//
//===========================================================================  
//  Usage:
//  ------
//  The component CAAVisModelCGRObject is used in the CAAVisManagerAppli Sample 
//
//===========================================================================

//Local FrameWork
#include "CAAVisModelObject.h"  // to derive from
#include "CAAVisManagerComp.h" // to export the class 


class ExportedByCAAVisManagerComp CAAVisModelCGRObject : public CAAVisModelObject
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

public :

   CAAVisModelCGRObject();
   virtual ~CAAVisModelCGRObject();

private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAVisModelCGRObject(const CAAVisModelCGRObject &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAVisModelCGRObject & operator = (const CAAVisModelCGRObject &iObjectToCopy);


};

#endif
