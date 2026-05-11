#ifndef CAAECafVisuEllipse_H
#define CAAECafVisuEllipse_H

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
//  Data extension of the CAASysEllipse component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the ellipses.
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

class CAAECafVisuEllipse : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAECafVisuEllipse();
    virtual ~CAAECafVisuEllipse();

    // Constructs the CAT3DRep for the Ellipse. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAECafVisuEllipse(const CAAECafVisuEllipse &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAECafVisuEllipse & operator = (const CAAECafVisuEllipse &iObjectToCopy);
};
#endif
