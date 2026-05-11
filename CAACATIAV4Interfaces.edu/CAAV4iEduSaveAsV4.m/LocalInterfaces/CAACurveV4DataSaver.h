//
// make your own implementation to compute the V4 data from your V5 surface
#ifndef CAACurveV4DataSaver_H
#define CAACurveV4DataSaver_H
#include "CATBaseUnknown.h"
class CAACurveV4DataSaver : public CATBaseUnknown
{
  CATDeclareClass;
  public : 
  CAACurveV4DataSaver();
  virtual ~CAACurveV4DataSaver();
  HRESULT GetData(int & oV4Type, double * & oV4Block); 
  HRESULT GetUserIntent(int & oIntent);
  HRESULT GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData);
};
#endif
