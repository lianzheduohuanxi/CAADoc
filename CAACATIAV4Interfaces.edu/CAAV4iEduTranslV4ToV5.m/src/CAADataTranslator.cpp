#include "CAADataTranslator.h"
#include "CATBaseUnknown.h"

#include "CATV4iV4Element.h"
#include "iostream.h"

#include "TIE_CATIV4DataTranslator.h"
TIE_CATIV4DataTranslator(CAADataTranslator);

CATImplementClass(CAADataTranslator , CodeExtension, CATBaseUnknown, V4iV4Element); 
//-----------------------------------------------------------------------------
//  CAAImplementDA2::CAAImplementDA2()
//-----------------------------------------------------------------------------
CAADataTranslator::CAADataTranslator() 
{
}
//
//-----------------------------------------------------------------------------
//  CAAImplementDA2::CAAImplementDA2()
//-----------------------------------------------------------------------------
//
CAADataTranslator::~CAADataTranslator()
{ 
}
// ----------------------------------------------------------------------------
//  CAAImplementDA2::GetUserIntent
// ----------------------------------------------------------------------------
//    
HRESULT CAADataTranslator::GetUserIntent(CATV4iV4Element * V4Elem, int & oIntent)
{
  HRESULT rc = S_OK;
  
  int TypePrim(0);
  int TypeSec(0);
 
  if (V4Elem) 
  {
	  V4Elem-> GetType(TypePrim,TypeSec);
  }

  cout << "TypePrim= "<< TypePrim << endl;
  cout << "TypeSec= "<< TypeSec << endl;

  oIntent=1;

  return rc;
}
