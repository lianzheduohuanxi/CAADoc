// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysGeomFactoryForSampCont.h"

// System Framework
#include <CATInstantiateComponent.h>

// C++ standard library
#include "iostream.h"

//----------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysGeomFactory.h"
TIE_CAAISysGeomFactory(CAAESysGeomFactoryForSampCont);

// To declare that the class is a data extension of CAASysSampCont
//
CATImplementClass(CAAESysGeomFactoryForSampCont,DataExtension,CATBaseUnknown,CAASysSampCont);
 
// To declare that CAAESysGeomFactoryForSampCont implements CAAISysGeomFactory, 
// insert these following lines in the interface dictionary:
//
//    CAASysSampCont     CAAISysGeomFactory  libCAASysGeoModelImpl
//
//-----------------------------------------------------------------------


CAAESysGeomFactoryForSampCont::CAAESysGeomFactoryForSampCont()
{
  cout << "CAAESysGeomFactoryForSampCont::CAAESysGeomFactoryForSampCont" << endl;
}

CAAESysGeomFactoryForSampCont::~CAAESysGeomFactoryForSampCont()
{
  cout << "CAAESysGeomFactoryForSampCont::~CAAESysGeomFactoryForSampCont" << endl;
}

HRESULT CAAESysGeomFactoryForSampCont::Create (const CAAISysGeomFactory::GeomObject iObjectType,
                     const IID & iIID,          
                     CATBaseUnknown ** oCreatedObj) const
{ 

  if ( NULL == oCreatedObj ) return E_FAIL ;

  HRESULT rc = E_FAIL;
  
  
  switch (iObjectType)
  {
    case CAAISysGeomFactory::Root : 
      rc = ::CATInstantiateComponent( "CAASysSampRootObj",  
                                       iIID,
					  				  (void**)oCreatedObj); 
      break;
    case CAAISysGeomFactory::Plane : 
      rc = ::CATInstantiateComponent( "CAASysPlane",  
                                       iIID,
					  				  (void**)oCreatedObj); 
      break;
    case CAAISysGeomFactory::Point : 
      rc = ::CATInstantiateComponent( "CAASysPoint",  
                                       iIID,
					  				  (void**)oCreatedObj); 
      break;
    case CAAISysGeomFactory::Line : 
      rc = ::CATInstantiateComponent( "CAASysLine",  
                                       iIID,
					  				  (void**)oCreatedObj); 
      break;
    case CAAISysGeomFactory::Polyline : 
      rc = ::CATInstantiateComponent( "CAASysPolyline",  
                                       iIID,
					  				  (void**)oCreatedObj);
      break;
    case CAAISysGeomFactory::Circle : 
      rc = ::CATInstantiateComponent( "CAASysCircle",  
                                       iIID,
					  				  (void**)oCreatedObj); 
      break;
    case CAAISysGeomFactory::Ellipse : 
      rc = ::CATInstantiateComponent( "CAASysEllipse",  
                                       iIID,
					  				  (void**)oCreatedObj); 
	  break;
    case CAAISysGeomFactory::Cuboid : 
      rc = ::CATInstantiateComponent( "CAASysCuboid",  
                                       iIID,
					  				  (void**)oCreatedObj); 
	  break;
    case CAAISysGeomFactory::Cylinder : 
     rc = ::CATInstantiateComponent( "CAASysCylinder",  
                                       iIID,
					  				  (void**)oCreatedObj);
  }

  return rc;
}

