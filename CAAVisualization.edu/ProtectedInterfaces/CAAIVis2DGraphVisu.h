#ifndef CAAIVis2DGraphVisu_H
#define CAAIVis2DGraphVisu_H

// COPYRIGHT DASSAULT SYSTEMES 1999


//===========================================================================
// Abstract : 
// ----------
//     Interface which  defines a 2D symbolic graphic representation. 
//     
//     Each component is represented by a gray box with its name written
//     inside. At each node of the model there is translation to 
//     represent the model tree.
//
//===========================================================================
//
//  Usage :  
//  -------  
//     is implemented on a component to allow it's 2D symbolic visualization.
//
//===========================================================================

// Visualization FrameWork
class CAT3x3Matrix ;
#include "CATIVisu.h" // Needed to derive from CATIVisu

// Local framework
#include "CAAVisManagerInt.h"  // Needed to export the IID and the class


// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisManagerInt IID IID_CAAIVis2DGraphVisu;

class  ExportedByCAAVisManagerInt CAAIVis2DGraphVisu : public CATIVisu
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;
public: 

   virtual CAT3x3Matrix & GetPositioningMatrix()=0;
   virtual void IncrementPositioningMatrix()=0;
} ; 


#endif
