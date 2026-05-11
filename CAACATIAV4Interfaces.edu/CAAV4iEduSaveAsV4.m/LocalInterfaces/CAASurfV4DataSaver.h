//
// make your own implementation to compute the V4 data from your V5 surface
#ifndef CAASurfV4DataSaver_H
#define CAASurfV4DataSaver_H
#include "CATBaseUnknown.h"
class CAASurfV4DataSaver : public CATBaseUnknown
{
  CATDeclareClass;
  public : 
  CAASurfV4DataSaver();
  virtual ~CAASurfV4DataSaver();
  HRESULT GetData(int & oV4Type, double * & oV4Block); 
  HRESULT GetUserIntent(int & oIntent);
  HRESULT GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData);
};
#endif
