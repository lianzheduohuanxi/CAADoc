#ifndef CAAEVisVisuCuboid_H
#define CAAEVisVisuCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAASysCuboid component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the Cuboids.
//  This class derives from the CATExtIVisu adapter.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATExtIVisu ( Visualization Framework) 
//                CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//
//  BuildRep
//
//===========================================================================
// Visualization Framework
#include "CATExtIVisu.h" // Visualization Framework

class  CAAEVisVisuCuboid : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:
    CAAEVisVisuCuboid();
    virtual ~CAAEVisVisuCuboid();

    // Constructs the CAT3DRep for the Cuboid. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuCuboid(const CAAEVisVisuCuboid &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuCuboid & operator = (const CAAEVisVisuCuboid &iObjectToCopy);

};
#endif 
