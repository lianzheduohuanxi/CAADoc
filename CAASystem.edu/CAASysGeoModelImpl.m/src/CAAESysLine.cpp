// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysLine.h"

//C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysLine.h"
TIE_CAAISysLine(CAAESysLine);

// To declare that the class is a data extension of CAASysLine
//
CATImplementClass(CAAESysLine, DataExtension, CATBaseUnknown, CAASysLine);

// 
// To declare that CAAESysLine implements CAAISysLine, insert 
// the following line in the interface dictionary:
//
//    CAASysLine CAAISysLine  libCAASysGeoModelImpl
//
//----------------------------------------------------------------------------

CAAESysLine::CAAESysLine() 
{
  cout << "CAAESysLine::CAAESysLine" << endl;
}

CAAESysLine::~CAAESysLine()
{
  cout << "CAAESysLine::~CAAESysLine" << endl;
}

HRESULT  CAAESysLine::SetStartPoint(const CATMathPoint & iStartPoint) 
{
  _StartPoint = iStartPoint ;
  return S_OK;
}


HRESULT  CAAESysLine::SetEndPoint(const CATMathPoint & iEndPoint) 
{
  _EndPoint = iEndPoint ;
  return S_OK;
}
    
HRESULT CAAESysLine::GetStartPoint(CATMathPoint & oStartPoint) const
{
  oStartPoint = _StartPoint ;
  return S_OK;
}
	

HRESULT  CAAESysLine::GetEndPoint(CATMathPoint & oEndPoint) const
{
  oEndPoint = _EndPoint ;
  return S_OK;
}





