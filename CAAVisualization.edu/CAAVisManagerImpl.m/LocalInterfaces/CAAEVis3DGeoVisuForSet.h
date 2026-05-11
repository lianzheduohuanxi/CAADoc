#ifndef CAAEVis3DGeoVisuForSet_H
#define CAAEVis3DGeoVisuForSet_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelSetOfObject component, implementing the  
//  CATI3DGeoVisu interface. 
//  This class derives from the CATExtIVisu adapter.
//
//===========================================================================

#include "CATExtIVisu.h" //  To derive from

// Visualization Framework
class CATRep;

class CAAEVis3DGeoVisuForSet : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

  public :

  CAAEVis3DGeoVisuForSet();
  virtual ~CAAEVis3DGeoVisuForSet();

  CATRep * BuildRep();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForSet(const CAAEVis3DGeoVisuForSet &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForSet & operator = (const CAAEVis3DGeoVisuForSet &iObjectToCopy);

};

#endif
