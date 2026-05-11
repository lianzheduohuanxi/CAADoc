#ifndef CAAVis2DGraphVisuAdapter_H
#define CAAVis2DGraphVisuAdapter_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Adapter for the CAAIVis2DGraphVisu interface. 
//
//===========================================================================

// Visualization FrameWork
#include "CATExtIVisu.h"   // To derive from
#include "CAT3x3Matrix.h"

class CAAVis2DGraphVisuAdapter : public CATExtIVisu
{

public :

   CAAVis2DGraphVisuAdapter();
   virtual ~CAAVis2DGraphVisuAdapter();

   virtual CAT3x3Matrix & GetPositioningMatrix();
   virtual void IncrementPositioningMatrix();

private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAVis2DGraphVisuAdapter(const CAAVis2DGraphVisuAdapter &iObjectToCopy);
  
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAVis2DGraphVisuAdapter & operator = (const CAAVis2DGraphVisuAdapter &iObjectToCopy);
  
protected : 

   // 2D matrix used to known where to add a new child.
   CAT3x3Matrix _PositioningMat;

};
#endif
