#ifndef CAAEVisVisuRootObject_H
#define CAAEVisVisuRootObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands. Moreover, another document (CAASample) with its own root object 
//  uses the same elements
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAASysGeomRootObject and CAASysSampRootObject components
//  (root objects of the ACOGeometry and ACODoc document), implementing the
//  CATI3DGeoVisu interface to enable the visualization of the root objects.
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
#include "CATExtIVisu.h"   // Visualization Framework

class CAAEVisVisuRootObject : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisVisuRootObject();
    virtual ~CAAEVisVisuRootObject();

    // Constructs a CAT3DBagRep which contains all CAASysxxx objects. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep() ;

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuRootObject(const CAAEVisVisuRootObject &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuRootObject & operator = (const CAAEVisVisuRootObject &iObjectToCopy);

};

#endif
