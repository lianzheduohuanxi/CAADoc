#ifndef CAAEwrUipBundleSegmentExt_H
#define CAAEwrUipBundleSegmentExt_H

// COPYRIGHT DASSAULT SYSTEMES 2002

// inherited from
#include "CATBaseUnknown.h"

// forward declaration
#include "CATListOfDouble.h"


class CAAEwrUipBundleSegmentExt: public CATBaseUnknown
{
  CATDeclareClass;
  
public:
  
  CAAEwrUipBundleSegmentExt();
  virtual ~CAAEwrUipBundleSegmentExt();
  
  /**
  * Returns the value of bundle segment diameter (in mm) fonction
  * of the values of the diameters of the wires contained in it.     
  *  
  * iListOfWireDiameters
  *   The list of the diameters of the wires contained in the bundle segment
  *   (the diameters must be expressed in mm)
  * oBundleSegmentDiameter
  *   The value of the bundle segment diameter 
  *   (the diameter must be expressed in mm)
  */
  HRESULT ComputeDiameter (const CATListOfDouble iListOfWireDiameters , double & oBundleSegmentDiameter); 
  
  /**
  * Returns the value of bundle segment bend radius (in mm) fonction
  * of the values of the bend radii of the wires contained in it.     
  *  
  * iListOfWireBendRadius
  *   The list of the bend radii of the wires contained in the bundle segment
  *   (the bend radii must be expressed in mm)
  * oBundleSegmentBendRadius
  *   The value of the bundle segment bend radius
  *   (the value must be expressed in mm)
  */ 
  HRESULT ComputeBendRadius (const CATListOfDouble iListOfWireBendRadius, double & oBundleSegmentBendRadius);
  
private:
  
  CAAEwrUipBundleSegmentExt(const CAAEwrUipBundleSegmentExt &);
  CAAEwrUipBundleSegmentExt& operator=(const CAAEwrUipBundleSegmentExt &); 
  
};

#endif
