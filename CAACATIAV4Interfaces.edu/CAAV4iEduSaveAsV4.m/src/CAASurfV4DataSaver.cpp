//
// make your own implementation to compute the V4 data from your V5 surface
#include "CAASurfV4DataSaver.h"
#include "CATBaseUnknown.h"
#include "CATIForeignSurface.h"

#include "TIE_CATIV4DataSaver.h"
TIE_CATIV4DataSaver(CAASurfV4DataSaver);

CATImplementClass(CAASurfV4DataSaver , CodeExtension, CATBaseUnknown, CATForeignSurfaceCGM); 

//-----------------------------------------------------------------------------
//  CAASurfV4DataSaver::CAASurfV4DataSaver()
//-----------------------------------------------------------------------------
CAASurfV4DataSaver::CAASurfV4DataSaver() 
{
}
//
//-----------------------------------------------------------------------------
//  CAASurfV4DataSaver::CAASurfV4DataSaver()
//-----------------------------------------------------------------------------
//
CAASurfV4DataSaver::~CAASurfV4DataSaver()
{ 
}
//
// ----------------------------------------------------------------------------
//  CAASurfV4DataSaver::GetData
// ----------------------------------------------------------------------------
//    
HRESULT CAASurfV4DataSaver::GetData(int & oV4Type, double * & oV4Block) 
{
  oV4Type = 0;
  oV4Block = NULL;
  HRESULT rc = S_OK;
  CATIForeignSurface_var forSurf = this;
  //
  // read your foreign surface data
  //
  // set the equivalent V4 type oV4Type
  //
  // allocate and fill the V4 CATGEO data block oV4Block
  return rc;
}
//
// ----------------------------------------------------------------------------
//  CAASurfV4DataSaver::GetUserIntent
// ----------------------------------------------------------------------------
//    
HRESULT CAASurfV4DataSaver::GetUserIntent(int & oIntent)
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
HRESULT CAASurfV4DataSaver::GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData)
{
  HRESULT rc = S_OK;
  oV4SplineType=0;
  oV4BlockLength=0;
  oV4BlockData=NULL;
  return rc;
}
