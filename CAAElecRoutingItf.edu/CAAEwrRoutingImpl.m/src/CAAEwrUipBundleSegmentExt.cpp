//*****************************************************************************
// CATIA Version 5 Release 9 Framework ElecModelerBase
// Copyright Dassault Systemes 2002
//*****************************************************************************
//  Abstract:
//  ---------
//    
//  Adhesion to CATIEwrUipBundleSegment
//    
//*****************************************************************************
//  Usage:
//  ------
//    
//*****************************************************************************
//  Inheritance:
//  ------------
//
//  
//
//*****************************************************************************
//  Main Methods:
//  -------------
//
//*****************************************************************************
//  Historic
//  --------
//
//*****************************************************************************
#include "CAAEwrUipBundleSegmentExt.h"
#include "CATMathConstant.h"
#include <math.h>


// Adhesions
#include "TIE_CATIEwrUipBundleSegment.h"
TIE_CATIEwrUipBundleSegment(CAAEwrUipBundleSegmentExt);

CATBeginImplementClass(CAAEwrUipBundleSegmentExt, CodeExtension, CATBaseUnknown, ElecBundleSegmentE);
CATAddClassExtension(ElecBundleSegmentC);
CATEndImplementClass(CAAEwrUipBundleSegmentExt);

//============================================================================
// Ctor
//============================================================================

CAAEwrUipBundleSegmentExt::CAAEwrUipBundleSegmentExt()
{
  
}

//============================================================================
// Dtor
//============================================================================

CAAEwrUipBundleSegmentExt::~CAAEwrUipBundleSegmentExt()
{
  
}

//==========================================================================
// ComputeDiameter
//==========================================================================
HRESULT CAAEwrUipBundleSegmentExt::ComputeDiameter(const CATListOfDouble iListOfWireDiameters, 
                                                   double & oBundleSegmentDiameter)

{
  oBundleSegmentDiameter = 0.;
  
  int nbDiam = iListOfWireDiameters.Size();
  double Area = 0.;
  
  for (int ii=1;ii<=nbDiam;ii++)
    Area += CATPI * iListOfWireDiameters[ii] * iListOfWireDiameters[ii] /4.;
  

  oBundleSegmentDiameter = sqrt (Area * 4. / CATPI);;
  
  return S_OK;
  
}

//==========================================================================
// ComputeBendRadius
//==========================================================================
HRESULT CAAEwrUipBundleSegmentExt::ComputeBendRadius(const CATListOfDouble iListOfWireBendRadius, 
                                                     double & oBundleSegmentBendRadius)
{
  
  oBundleSegmentBendRadius=0.;
  
  int nbRad=iListOfWireBendRadius.Size();
  
  for (int ii=1;ii<=nbRad;ii++)
  {
    if (iListOfWireBendRadius[ii] > oBundleSegmentBendRadius)
    {
      oBundleSegmentBendRadius = iListOfWireBendRadius[ii];
    }
  }
  
  return S_OK;
  
}






