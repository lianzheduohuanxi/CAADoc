#ifndef CAAEVis3DGeoVisuForSphere_H
#define CAAEVis3DGeoVisuForSphere_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelSphere component, implementing the  
//  CATI3DGeoVisu interface. 
//  This class derives from the CATExtIVisu adapter.
//
//===========================================================================

#include "CATExtIVisu.h" //  To derive from

class CATRep;

class CAAEVis3DGeoVisuForSphere : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

  public :

  CAAEVis3DGeoVisuForSphere();
  virtual ~CAAEVis3DGeoVisuForSphere();

  CATRep * BuildRep();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForSphere(const CAAEVis3DGeoVisuForSphere &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForSphere & operator = (const CAAEVis3DGeoVisuForSphere &iObjectToCopy);

};

#endif
