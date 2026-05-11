#ifndef CAAIVisModelCuboid_H
#define CAAIVisModelCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//
// Abstract of the class: 
// -----------------------
// Interface which characterizes a CAAVisModelCuboid object. 
//
//
// The Cuboid is represented by 8 vertices, ie 8*3 float. 
// Each vertices is placed like this:
//
//
//              X4 --------------X7
//            /  .                   /  |
//         /     .                 /    |
//       /     X3 .............../........X2
//    X5 -------------X6      /
//    |    .                 |       /
//    |  .                   |    /
//   X0--------------X1
//
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Local framework
#include "CAAVisManagerInt.h"  // Needed to export the IID and the class

// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisManagerInt IID IID_CAAIVisModelCuboid;

class ExportedByCAAVisManagerInt CAAIVisModelCuboid : public CATBaseUnknown
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  // Retrieves vertices of the cuboid. 
  // The length of the array is 24 = 8 vertices * 3 coordinates (x,y,z)
  // don't delete the array after the call.
  //
  virtual HRESULT GetVertices(float ** oVertices) = 0;

  // Sets vertices of the cuboid. 
  virtual HRESULT SetVertices(float  * iVertices) = 0;
};

#endif 
