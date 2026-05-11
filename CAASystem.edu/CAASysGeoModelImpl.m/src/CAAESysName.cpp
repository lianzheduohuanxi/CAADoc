// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysName.h"

//C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAISysName.h"
TIE_CAAISysName(CAAESysName);

// To declare that the class is a data extension of the elements : point, line ....
// 
CATBeginImplementClass(CAAESysName, DataExtension, CATBaseUnknown, CAASysPoint);
CATAddClassExtension(CAASysGeomRootObj);
CATAddClassExtension(CAASysLine);
CATAddClassExtension(CAASysEllipse);
CATAddClassExtension(CAASysPlane);
CATAddClassExtension(CAASysCircle);
CATAddClassExtension(CAASysPolyline);
CATAddClassExtension(CAASysCuboid);
CATAddClassExtension(CAASysCylinder);
CATEndImplementClass(CAAESysName); 

// 
// To declare that elements implement CAAISysName, insert 
// following lines in the interface dictionary:
//
//    CAASysPoint  CAAISysName  libCAASysGeoModelImpl
//    CAASysLine   CAAISysName  libCAASysGeoModelImpl
//    CAASysPlane  CAAISysName  libCAASysGeoModelImpl
//    ....
//-----------------------------------------------------------------------------

CAAESysName::CAAESysName()
{
  cout << "CAAESysName::CAAESysName" << endl;
}

CAAESysName::~CAAESysName()
{
  cout << "CAAESysName::~CAAESysName" << endl;
}

//-----------------------------------------------------------------------------
HRESULT  CAAESysName::SetName(const CATUnicodeString & iName) 
{

  _Name = iName;

  return S_OK;

}
    
//-----------------------------------------------------------------------------
HRESULT CAAESysName::GetName(CATUnicodeString & ioName)
{
  
  ioName = _Name ;
  
  return S_OK;

}
	




