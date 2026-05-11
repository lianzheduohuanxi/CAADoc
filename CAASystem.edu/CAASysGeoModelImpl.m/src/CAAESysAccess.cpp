// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysAccess.h"

//C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAISysAccess.h"
TIE_CAAISysAccess(CAAESysAccess);

// To declare that the class is a data extension of the elements : point, line ....
// 
CATBeginImplementClass(CAAESysAccess, DataExtension, CATBaseUnknown, CAASysPoint);
CATAddClassExtension(CAASysSampRootObj);
CATAddClassExtension(CAASysGeomRootObj);
CATAddClassExtension(CAASysLine);
CATAddClassExtension(CAASysEllipse);
CATAddClassExtension(CAASysPlane);
CATAddClassExtension(CAASysCircle);
CATAddClassExtension(CAASysPolyline);
CATAddClassExtension(CAASysCuboid);
CATAddClassExtension(CAASysCylinder);
CATEndImplementClass(CAAESysAccess); 

// 
// To declare that elements implement CAAISysAccess, insert 
// following lines in the interface dictionary:
//
//    CAASysPoint  CAAISysAccess  libCAASysGeoModelImpl
//    CAASysLine   CAAISysAccess  libCAASysGeoModelImpl
//    CAASysPlane  CAAISysAccess  libCAASysGeoModelImpl
//    ....
//-----------------------------------------------------------------------------

CAAESysAccess::CAAESysAccess():_pContainer(NULL)
{
  cout << "CAAESysAccess::CAAESysAccess" << endl;
}

CAAESysAccess::~CAAESysAccess()
{
  cout << "CAAESysAccess::~CAAESysAccess" << endl;
  SetContainer(NULL);

  _pContainer = NULL ;
}

//-----------------------------------------------------------------------------
HRESULT  CAAESysAccess::SetContainer(CATBaseUnknown * iContainer) 
{

  if ( NULL != _pContainer )
  {
    _pContainer->Release();
  }

  _pContainer = iContainer ;

  if ( NULL != _pContainer )
  {	
    _pContainer->AddRef();
  }

  return S_OK;

}
    
//-----------------------------------------------------------------------------
HRESULT CAAESysAccess::GetContainer(CATBaseUnknown  ** oContainer) 
{
  if ( NULL == oContainer) 
  {
     return E_FAIL;
  }

  *oContainer = _pContainer ;

  if ( NULL != _pContainer )
  {
     (*oContainer) -> AddRef();
  }

  return S_OK;

}
	




