// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEVisWireBox.h"

// C++ Standard library
#include "iostream.h"


//----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAIVisWireBox.h"
TIE_CAAIVisWireBox(CAAEVisWireBox);

// To declare that the class is a data extension of CAAVisWireBox
//
CATImplementClass(CAAEVisWireBox, DataExtension, CATBaseUnknown, CAAVisWireBox);
// 
// To declare that CAAEVisWireBox implements CAAIVisWireBox, insert 
// the following line in the interface dictionary:
//
//    CAAVisWireBox CAAIVisWireBox libCAAVisWireBoxComp
//
//----------------------------------------------------------------------------

CAAEVisWireBox::CAAEVisWireBox():_DimBox(0.2f) 
{
  cout << "CAAEVisWireBox::CAAEVisWireBox" << endl;
}

CAAEVisWireBox::~CAAEVisWireBox()
{
  cout << "CAAEVisWireBox::~CAAEVisWireBox" << endl;

}

HRESULT CAAEVisWireBox::GetDimBox ( float * oDim )
{
   cout << "CAAEVisWireBox::GetDimBox" << endl;
   if ( NULL == oDim ) return E_FAIL;
   
   *oDim = _DimBox;
  
   return S_OK;
}

HRESULT CAAEVisWireBox::SetDimBox ( const float iDim )
{
  cout << "CAAEVisWireBox::SetDimBox" << endl;

  _DimBox = iDim ;

  return S_OK;
}

HRESULT  CAAEVisWireBox::SetCenterBox(const CATMathPoint & iCenter) 
{
cout << "CAAEVisWireBox::SetCenterBox" << endl;
	_CenterBox = iCenter ;
	return S_OK;
}

HRESULT CAAEVisWireBox::GetCenterBox(CATMathPoint & oCenter) const 
{
    cout << "CAAEVisWireBox::GetCenterBox" << endl;
	oCenter = _CenterBox ;
	return S_OK;
}

