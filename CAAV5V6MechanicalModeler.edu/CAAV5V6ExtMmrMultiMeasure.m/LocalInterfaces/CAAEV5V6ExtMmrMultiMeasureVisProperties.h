#ifndef CAAEV5V6ExtMmrMultiMeasureVisProperties_H
#define CAAEV5V6ExtMmrMultiMeasureVisProperties_H
// COPYRIGHT DASSAULT SYSTEMES 2012
#include "CATExtIVisProperties.h"

class CAAEV5V6ExtMmrMultiMeasureVisProperties: public CATExtIVisProperties
{
  CATDeclareClass;

public:
  // Standard constructors and destructors
  // -------------------------------------
  CAAEV5V6ExtMmrMultiMeasureVisProperties();
  virtual ~CAAEV5V6ExtMmrMultiMeasureVisProperties();

  // IsGeomTypeDefined
  HRESULT IsGeomTypeDefined( CATVisGeomType & iGeomType );
  // GetSubTypeFromPath : For Graphic Property table
  HRESULT GetSubTypeFromPath(CATPathElement     & iPathElement,
                             CATVisPropertyType   iPropertyType,
                             CATVisGeomType     & oGeomType,
                             unsigned int       & oPropertyNumber );

private:
  //--------------------------------------------------------------------
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEV5V6ExtMmrMultiMeasureVisProperties( const CAAEV5V6ExtMmrMultiMeasureVisProperties& );
  CAAEV5V6ExtMmrMultiMeasureVisProperties& operator = ( const CAAEV5V6ExtMmrMultiMeasureVisProperties& );
};

#endif
