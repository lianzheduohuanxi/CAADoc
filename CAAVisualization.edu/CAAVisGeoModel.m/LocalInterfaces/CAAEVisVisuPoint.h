#ifndef CAAEVisVisuPoint_H
#define CAAEVisVisuPoint_H

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
//  Data extension of the CAASysPoint component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the points.
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

class  CAAEVisVisuPoint : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:
    CAAEVisVisuPoint();
    virtual ~CAAEVisVisuPoint();

    // Constructs the CAT3DRep for the Point. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuPoint(const CAAEVisVisuPoint &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuPoint & operator = (const CAAEVisVisuPoint &iObjectToCopy);
};
#endif 
