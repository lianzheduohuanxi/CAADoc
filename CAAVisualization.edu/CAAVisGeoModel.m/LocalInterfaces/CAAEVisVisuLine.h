#ifndef CAAEVisVisuLine_H
#define CAAEVisVisuLine_H

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
//  Data extension of the CAASysLine component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the lines.
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
#include "CATExtIVisu.h"    // Need to derive from

class CAAEVisVisuLine : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisVisuLine();
    virtual ~CAAEVisVisuLine();

    // Constructs the CAT3DRep for the Line. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuLine(const CAAEVisVisuLine &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuLine & operator = (const CAAEVisVisuLine &iObjectToCopy);

};
#endif
