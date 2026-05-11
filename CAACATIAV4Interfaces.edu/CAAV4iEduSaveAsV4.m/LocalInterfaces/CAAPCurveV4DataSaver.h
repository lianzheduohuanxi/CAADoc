#ifndef CAAPCurveV4DataSaver_H
#define CAAPCurveV4DataSaver_H
#include "CATBaseUnknown.h"
class CAAPCurveV4DataSaver : public CATBaseUnknown
{
  CATDeclareClass;
  public : 
  CAAPCurveV4DataSaver();
  virtual ~CAAPCurveV4DataSaver();
  HRESULT GetData(int & oV4Type, double * & oV4Block); 
  HRESULT GetUserIntent(int & oIntent);
  HRESULT GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData);
};
#endif
