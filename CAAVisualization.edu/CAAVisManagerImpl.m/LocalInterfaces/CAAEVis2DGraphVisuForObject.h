#ifndef CAAEVis2DGraphVisuForObject_H
#define CAAEVis2DGraphVisuForObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelObject component, implementing the  
//  CAAIVis2DGraphVisu interface. 
//  This class derives from the CAAVis2DGraphVisuAdapter adapter.
//
//===========================================================================
#include "CAAVis2DGraphVisuAdapter.h" // To derive from

class CAAEVis2DGraphVisuForObject : public CAAVis2DGraphVisuAdapter
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

  public :

  CAAEVis2DGraphVisuForObject();
  virtual ~CAAEVis2DGraphVisuForObject();

  CATRep * BuildRep();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis2DGraphVisuForObject(const CAAEVis2DGraphVisuForObject &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis2DGraphVisuForObject & operator = (const CAAEVis2DGraphVisuForObject &iObjectToCopy);

};
#endif
