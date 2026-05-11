//
// make your own implementation to compute the V4 data from your V5 surface
#include "CAACurveV4DataSaver.h"
#include "CATBaseUnknown.h"
#include "CATIForeignCurve.h"

#include "TIE_CATIV4DataSaver.h"
TIE_CATIV4DataSaver(CAACurveV4DataSaver);

CATImplementClass(CAACurveV4DataSaver , CodeExtension, CATBaseUnknown, CATForeignCurveCGM); 

//-----------------------------------------------------------------------------
//  CAACurveV4DataSaver::CAAV4DataSaver()
//-----------------------------------------------------------------------------
CAACurveV4DataSaver::CAACurveV4DataSaver() 
{
}
//
//-----------------------------------------------------------------------------
//  CAASurfV4DataSaver::CAASurfV4DataSaver()
//-----------------------------------------------------------------------------
//
CAACurveV4DataSaver::~CAACurveV4DataSaver()
{ 
}
//
// ----------------------------------------------------------------------------
//  CAASurfV4DataSaver::GetData
// ----------------------------------------------------------------------------
//    
HRESULT CAACurveV4DataSaver::GetData(int & oV4Type, double * & oV4Block) 
{
  CATIForeignCurve_var forCurve = this;
  //
  // read your foreign curve data
  //
  // set the equivalent V4 type oV4Type
  //
  // allocate and fill the V4 CATGEO data block oV4Block
  // here is an example where a V4 polynomial block is computed
  // this is very specific - it should be computed from the foreign curve modelisation
  HRESULT rc = S_OK;
  oV4Type = 3;
  oV4Block = new double[48];
  union {short i2[4]; float r4[2]; double r8;};
  r8 = 0;
  i2[0] = 1;
  i2[1] = 2;
  oV4Block[0] = r8;
  oV4Block[1] = 0;
  oV4Block[2] = 1;
  int iadmat = 3;
  r8 = 0;
  i2[0] = 2;
  i2[1] = 111;
  oV4Block[0+iadmat] = r8;
  r8 = 0;
  i2[0] = 22;
  i2[1] = 6;
  i2[2] = 16;
  oV4Block[1+iadmat] = r8;
  oV4Block[2+iadmat] = 90.227;
  oV4Block[3+iadmat] = -0.724;
  oV4Block[4+iadmat] = -13.684;
  oV4Block[5+iadmat] = -1.182;
  oV4Block[6+iadmat] = 0.679;
  oV4Block[7+iadmat] = 0.189;
  oV4Block[8+iadmat] = 10.355;
  oV4Block[9+iadmat] = 39.202;
  oV4Block[10+iadmat] = -0.305;
  oV4Block[11+iadmat] = -3.402;
  oV4Block[12+iadmat] = -0.515;
  oV4Block[13+iadmat] = 0.199;
  oV4Block[14+iadmat] = 0;
  oV4Block[15+iadmat] = 0;
  oV4Block[16+iadmat] = 0;
  oV4Block[17+iadmat] = 0;
  oV4Block[18+iadmat] = 0;
  oV4Block[19+iadmat] = 0;
/** @c++ansi mcf 2004-10-08.12:01:29 [ '=' : truncation from 'double' to 'float'] **/
  r4[0] = 75.47f;
  r4[1] = 90.26f;
  oV4Block[20+iadmat] = r8;
  r4[0] = 10.32f;
  r4[1] = 45.56f;
  oV4Block[21+iadmat] = r8;
  r4[0] = -0.03f;
  r4[1] = 0.03f;
  oV4Block[22+iadmat] = r8;
  r8 = 0;
  i2[0] = 22;
  i2[1] = 6;
  i2[2] = 17;
  oV4Block[23+iadmat] = r8;
  oV4Block[24+iadmat] = 75.505;
  oV4Block[25+iadmat] = -29.606;
  oV4Block[26+iadmat] = -12.702;
  oV4Block[27+iadmat] = 4.210;
  oV4Block[28+iadmat] = 0.539;
  oV4Block[29+iadmat] = -0.247;
  oV4Block[30+iadmat] = 45.534;
  oV4Block[31+iadmat] = 28.915;
  oV4Block[32+iadmat] = -12.915;
  oV4Block[33+iadmat] = -4.042;
  oV4Block[34+iadmat] = 2.067;
  oV4Block[35+iadmat] = -0.256;
  oV4Block[36+iadmat] = 0;
  oV4Block[37+iadmat] = 0;
  oV4Block[38+iadmat] = 0;
  oV4Block[39+iadmat] = 0;
  oV4Block[40+iadmat] = 0;
  oV4Block[41+iadmat] = 0;
  r4[0] = 37.67f;
  r4[1] = 75.53f;
  oV4Block[42+iadmat] = r8;
  r4[0] = 45.50f;
  r4[1] = 59.40f;
  oV4Block[43+iadmat] = r8;
  r4[0] = -0.03f;
  r4[1] = 0.03f;
  oV4Block[44+iadmat] = r8;
  return rc;
}
//
// ----------------------------------------------------------------------------
//  CAASurfV4DataSaver::GetUserIntent
// ----------------------------------------------------------------------------
//    
HRESULT CAACurveV4DataSaver::GetUserIntent(int & oIntent)
{
  HRESULT rc = S_OK;
  // 0 do not compute the V4 data 
  // 1 do the standard process 
  // 2 let the customer do 
  oIntent = 1;
  return rc;
}
//
// ----------------------------------------------------------------------------
//  CAASurfV4DataSaver::GetSplineConstraintData
// ----------------------------------------------------------------------------
//    
HRESULT CAACurveV4DataSaver::GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData)
{
  //
  // read your foreign curve data
  //
  // set the equivalent V4 type oV4SplineType
  //
  // allocate and fill the V4 constraint block oV4Block
  // here is an example where a V4 constraint block is computed
  // this is very specific - it should be computed from the foreign curve modelisation
  HRESULT rc = S_OK;
  oV4SplineType=2;
  oV4BlockLength=7;
  oV4BlockData = new double[7];
  union {int i4[2]; double r8;};
  r8 = 0;
  i4[0] = 3;
  oV4BlockData[0] = r8;
  i4[0] = 0;
  i4[1] = 0;
  oV4BlockData[1] = r8;
  oV4BlockData[2] = 0;
  i4[0] = 0;
  i4[1] = 0;
  oV4BlockData[3] = r8;
  oV4BlockData[4] = 39.126;
  i4[0] = 0;
  i4[1] = 0;
  oV4BlockData[5] = r8;
  oV4BlockData[6] = 80.533;
  return rc;
}
