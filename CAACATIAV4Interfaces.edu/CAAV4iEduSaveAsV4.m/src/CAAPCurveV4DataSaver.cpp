#include "CAAPCurveV4DataSaver.h"
#include "CATBaseUnknown.h"
#include "CATIForeignPCurve.h"

#include "TIE_CATIV4DataSaver.h"
TIE_CATIV4DataSaver(CAAPCurveV4DataSaver);

CATImplementClass(CAAPCurveV4DataSaver , CodeExtension, CATBaseUnknown, CATForeignPCurveCGM); 

//-----------------------------------------------------------------------------
//  CAAPCurveV4DataSaver::CAAGobSplineV4DataSaver()
//-----------------------------------------------------------------------------
CAAPCurveV4DataSaver::CAAPCurveV4DataSaver() 
{
}
//
//-----------------------------------------------------------------------------
//  CAAPCurveV4DataSaver::CAAGobSplineV4DataSaver()
//-----------------------------------------------------------------------------
//
CAAPCurveV4DataSaver::~CAAPCurveV4DataSaver()
{ 
}
//
// ----------------------------------------------------------------------------
//  CAAPCurveV4DataSaver::GetData
// ----------------------------------------------------------------------------
//    
HRESULT CAAPCurveV4DataSaver::GetData(int & oV4Type, double * & oV4Block) 
{
  HRESULT rc = S_OK;
  oV4Type = 0;
  oV4Block = NULL;
  CATIForeignPCurve_var forCurve = this;
  //
  // read your foreign curve data
  //
  // set the equivalent V4 type oV4Type
  //
  // allocate and fill the V4 CATGEO data block oV4Block
  return rc;
}
//
// ----------------------------------------------------------------------------
//  CAAPCurveV4DataSaver::GetUserIntent
// ----------------------------------------------------------------------------
//    
HRESULT CAAPCurveV4DataSaver::GetUserIntent(int & oIntent)
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
//  CAAPCurveV4DataSaver::GetUserIntent
// ----------------------------------------------------------------------------
//    
HRESULT CAAPCurveV4DataSaver::GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData)
{
  HRESULT rc = S_OK;
  oV4SplineType = 0;
  oV4BlockLength = 0;
  oV4BlockData = NULL;
  return rc;
}
