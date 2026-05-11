#ifndef CAAEVis3DGeoVisuForCGRObject_H
#define CAAEVis3DGeoVisuForCGRObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelCGRObject component, implementing the  
//  CATI3DGeoVisu interface. 
//  This class derives from the CATExtIVisu adapter.
//
//===========================================================================
#include "CATExtIVisu.h" //  To derive from

class CATRep;

class CAAEVis3DGeoVisuForCGRObject : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

  public :

  CAAEVis3DGeoVisuForCGRObject();
  virtual ~CAAEVis3DGeoVisuForCGRObject();

  virtual CATRep * GetRep();
  virtual CATRep * BuildRep();
  virtual void UnreferenceRep ();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForCGRObject(const CAAEVis3DGeoVisuForCGRObject &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVis3DGeoVisuForCGRObject & operator = (const CAAEVis3DGeoVisuForCGRObject &iObjectToCopy);

};
#endif
