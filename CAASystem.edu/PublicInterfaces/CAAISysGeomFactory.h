#ifndef CAAISysGeomFactory_H
#define CAAISysGeomFactory_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface representing a factory which creates model objects.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Create: instantiates model objects
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Local framework
#include "CAASysGeoModelInf.h" // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysGeomFactory;

class ExportedByCAASysGeoModelInf CAAISysGeomFactory : public CATBaseUnknown
{

  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  // Different kind of object created by this factory. 
  // Root     : CAASysGeomRootObject
  // Point    : CAASysPoint 
  // Plane    : CAASysPlane
  // Line     : CAASysLine
  // Polyline : CAASysPolyline
  // Circle   : CAASysCircle
  // Ellipse  : CAASysEllipse
  // Cuboid   : CAASysCuboid
  // Cylinder : CAASysCylinder
  //
  enum GeomObject  {Root, Point, Plane, Line, Polyline, Circle, Ellipse,Cuboid, Cylinder};

  // Create
  // ------
  // Instanciates an object and returns its asked interface pointer . 
  // 
  virtual HRESULT Create ( const CAAISysGeomFactory::GeomObject  iObjectType,
                           const IID                            &iRequestInterfaceIID,          
                           CATBaseUnknown **oCreatedObj) const =0 ;
 
};

#endif
