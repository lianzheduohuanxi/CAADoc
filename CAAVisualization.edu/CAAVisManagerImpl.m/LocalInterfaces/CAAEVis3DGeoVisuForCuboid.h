#ifndef CAAEVis3DGeoVisuForCuboid_H
#define CAAEVis3DGeoVisuForCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelCuboid component, implementing the  
//  CATI3DGeoVisu interface. 
//  This class derives from the CATExtIVisu adapter.
//
//===========================================================================

#include "CATExtIVisu.h" //  To derive from

class CATRep;

class CAAEVis3DGeoVisuForCuboid : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

  public :

  CAAEVis3DGeoVisuForCuboid();
  virtual ~CAAEVis3DGeoVisuForCuboid();

  CATRep * BuildRep();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForCuboid(const CAAEVis3DGeoVisuForCuboid &iObjectToCopy);

  // Assignment operator , not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForCuboid & operator = (const CAAEVis3DGeoVisuForCuboid &iObjectToCopy);

};
#endif
