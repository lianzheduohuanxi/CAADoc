#ifndef CAAEVisVisuWireBox_H
#define CAAEVisVisuWireBox_H

// COPYRIGHT DASSAULT SYSTEMES 1999


//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisWireBox component, implementing the CATI3DGeoVisu 
//  interface to enable you the visualization of the wire box.
//  This class derives from the CATExtIVisu adaptor class of the CATI3DGeoVisu 
//  interface. 
//
//===========================================================================
// Visualization Framework
#include "CATExtIVisu.h"   // Need to derive from

class CAAEVisVisuWireBox : public CATExtIVisu 
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisVisuWireBox();
    virtual ~CAAEVisVisuWireBox();

    // Constructs the CAT3DRep for the Plane. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuWireBox(const CAAEVisVisuWireBox &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuWireBox & operator = (const CAAEVisVisuWireBox &iObjectToCopy);
};
#endif
