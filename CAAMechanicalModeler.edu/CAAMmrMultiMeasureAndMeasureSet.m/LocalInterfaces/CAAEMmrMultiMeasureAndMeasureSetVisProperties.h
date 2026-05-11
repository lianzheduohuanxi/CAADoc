#ifndef CAAEMmrMultiMeasureAndMeasureSetVisProperties_H
#define CAAEMmrMultiMeasureAndMeasureSetVisProperties_H
// COPYRIGHT DASSAULT SYSTEMES 2007
#include "CATExtIVisProperties.h"

class CAAEMmrMultiMeasureAndMeasureSetVisProperties: public CATExtIVisProperties
{
  CATDeclareClass;

public:
  // Standard constructors and destructors
  // -------------------------------------
  CAAEMmrMultiMeasureAndMeasureSetVisProperties();
  virtual ~CAAEMmrMultiMeasureAndMeasureSetVisProperties();

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
  CAAEMmrMultiMeasureAndMeasureSetVisProperties( const CAAEMmrMultiMeasureAndMeasureSetVisProperties& );
  CAAEMmrMultiMeasureAndMeasureSetVisProperties& operator = ( const CAAEMmrMultiMeasureAndMeasureSetVisProperties& );
};

#endif
