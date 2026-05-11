#include <math.h>

#include "CAAECloAppWeldOffset.h"
#include "CATUnicodeString.h"

#define WeldSetOn "WELD SET ON"
#define WeldStubOn "WELD STUB ON"
#define WeldStubIn "WELD STUB IN"
#define WeldLinear "WELD LINEAR"
#define WeldCalculated "WELD CALCULATED"

CATImplementClass( CAAECloAppWeldOffset,
                   DataExtension, 
                   CATBaseUnknown,
                   CATPiping );
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICloAppWeldOffset.h"
TIE_CATICloAppWeldOffset( CAAECloAppWeldOffset); 

//-----------------------------------------------------------------------------
// CATEPipWeldRule : constructor
//-----------------------------------------------------------------------------
CAAECloAppWeldOffset::CAAECloAppWeldOffset():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CATEPipWeldRule : destructor
//-----------------------------------------------------------------------------
CAAECloAppWeldOffset::~CAAECloAppWeldOffset()
{
}


HRESULT CAAECloAppWeldOffset::GetWeldOffset( const wchar_t* iaWeldEndStyle,
                                             const double idRunInsideRadius,
                                             const double idRunOutsideRadius,
                                             const double idBranchInsideRadius,
                                             const double idBranchOutsideRadius,
                                             const double idWeldGap,
                                             double* odWeldOffset  )   
{
  HRESULT RC = S_OK;
  CATUnicodeString offsetType;
  offsetType.BuildFromWChar(iaWeldEndStyle);
  printf ( "offsetType=%s\n",offsetType.ConvertToChar());
  
  if ( offsetType == WeldLinear )
  {
    //  for example, change the follwing default to 2 times the weldGap if the offsettype is WeldLinear 
    //  *odWeldOffset = idWeldGap;  

    *odWeldOffset = 2*idWeldGap;
  }
  else if ( offsetType == WeldCalculated )
  {
    *odWeldOffset = idWeldGap;
  }
  else if ( offsetType == WeldStubOn )
  {
    if ( idRunOutsideRadius > idBranchInsideRadius )
      *odWeldOffset = sqrt( idRunOutsideRadius*idRunOutsideRadius - idBranchInsideRadius*idBranchInsideRadius ) + idWeldGap;
    else 
      RC = E_FAIL;
  }
  else if ( offsetType == WeldStubIn )
  {
    double x = idBranchOutsideRadius + idWeldGap;
    if ( idRunInsideRadius > x )
      *odWeldOffset = sqrt ( idRunInsideRadius*idRunInsideRadius - x*x );
    else
      RC = E_FAIL;
  }
  else if ( offsetType == WeldSetOn )
  {
    *odWeldOffset = idRunOutsideRadius + idWeldGap;
  }
  else 
  {
    RC = E_FAIL;
  }
  
  return RC;
}

