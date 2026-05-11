#ifndef CAAEVisVisuCircle_H
#define CAAEVisVisuCircle_H

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
//  Data extension of the Circle component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the circles.
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
#include "CATExtIVisu.h"  // Need to derive from

class CAAEVisVisuCircle : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisVisuCircle();
    virtual ~CAAEVisVisuCircle();

    // Constructs the CAT3DRep for the Circle. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuCircle(const CAAEVisVisuCircle &iObjectToCopy);

  // Assignment constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuCircle & operator = (const CAAEVisVisuCircle &iObjectToCopy);

};
#endif
