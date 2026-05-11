// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAESysPolyline.h"

// System Framework 
#include "CATCallbackManager.h" // To dispatch notification 

// Mathematics Framework
#include "CATMathPoint.h"

// C++ Standard library
#include "iostream.h"


//----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysPolyline.h"
TIE_CAAISysPolyline(CAAESysPolyline);

// To declare that the class is a data extension of CAASysPolyline
//
CATImplementClass(CAAESysPolyline, DataExtension, CATBaseUnknown, CAASysPolyline);
// 
// To declare that CAAESysPolyline implements CAAISysPolyline, insert 
// the following line in the interface dictionary:
//
//    CAASysPolyline CAAISysPolyline  libCAASysGeoModelImpl
//
//----------------------------------------------------------------------------

CAAESysPolyline::CAAESysPolyline():_pListe(NULL),_IsClosed(0),_PointCount(0)
{
  cout << "CAAESysPolyline::CAAESysPolyline" << endl;
}

CAAESysPolyline::~CAAESysPolyline()
{
  cout << "CAAESysPolyline::~CAAESysPolyline" << endl;
  if ( NULL != _pListe) 
  {
     delete [] _pListe ;
     _pListe = NULL ;
  }
}

HRESULT CAAESysPolyline::GetListPoint(int * oPointCount, CATMathPoint ** oList)
{
  cout << "CAAESysPolyline::GetListPoint" << endl;

  if ( (NULL == oPointCount) || ( NULL == oList) ) 
  {
     return E_FAIL;
  }

  *oList       = _pListe ;
  *oPointCount = _PointCount;

  return S_OK;
}

HRESULT CAAESysPolyline::SetListPoint(const int iPointCount, CATMathPoint *  iList  )
{
  cout << "CAAESysPolyline::SetListPoint" << endl;

  int ok = 0;
 
  if ( iPointCount >= 3 )
  {
    if ( NULL != _pListe) 
    {
       delete [] _pListe ;
       _pListe = NULL ;
    }

    if ( iPointCount > 0 )
    {
       _pListe = new CATMathPoint[iPointCount];

       for (int i=0; i < iPointCount; i++)
       {
         _pListe[i] = iList[i] ;		
       }
    }

    _PointCount = iPointCount ;
    ok = 1 ;
  }

  if ( 1 == ok) 
     return S_OK ;
  else 
     return E_FAIL ;
  
}

HRESULT CAAESysPolyline::GetCloseStatus ( int * oIsClosed )
{
   cout << "CAAESysPolyline::GetCloseStatus" << endl;
   if ( NULL == oIsClosed ) return E_FAIL;
   
   *oIsClosed = _IsClosed ;
  
   return S_OK;
}

HRESULT CAAESysPolyline::SetCloseStatus ( const int iIsClosed )
{
  cout << "CAAESysPolyline::SetCloseStatus" << endl;

  _IsClosed = iIsClosed ;

  return S_OK;
}
