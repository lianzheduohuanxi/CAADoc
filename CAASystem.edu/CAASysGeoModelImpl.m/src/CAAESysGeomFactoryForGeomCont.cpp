// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysGeomFactoryForGeomCont.h"
#include "CAAISysName.h" // To set a name to the component

//C++ Standard library
#include "iostream.h"

//System framework
#include "CATInstantiateComponent.h"
#include "CATUnicodeString.h"

//--------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysGeomFactory.h"
TIE_CAAISysGeomFactory(CAAESysGeomFactoryForGeomCont);

// To declare that the class is a data extension of CAASysGeomCont
//
CATImplementClass(CAAESysGeomFactoryForGeomCont,DataExtension,CATBaseUnknown,CAASysGeomCont);

// 
// To declare that CAAESysGeomFactoryForGeomCont implements CAAISysGeomFactory, 
// insert these following lines in the interface dictionary:
//
//    CAASysGeomCont     CAAISysGeomFactory  libCAASysGeoModelImpl
//
//--------------------------------------------------------------------

CAAESysGeomFactoryForGeomCont::CAAESysGeomFactoryForGeomCont()
{
  cout << "CAAESysGeomFactoryForGeomCont::CAAESysGeomFactoryForGeomCont" << endl;
}

//--------------------------------------------------------------------

CAAESysGeomFactoryForGeomCont::~CAAESysGeomFactoryForGeomCont()
{
  cout << "CAAESysGeomFactoryForGeomCont::~CAAESysGeomFactoryForGeomCont" << endl;
}

//--------------------------------------------------------------------

HRESULT CAAESysGeomFactoryForGeomCont::Create (const CAAISysGeomFactory::GeomObject iObjectType, 
                                const IID & iIID,          
                                CATBaseUnknown ** oCreatedObj) const
{ 
  // Object creation

  if ( NULL == oCreatedObj ) return E_FAIL;

  HRESULT rc = E_FAIL;
  
  CATUnicodeString Name ;

  switch (iObjectType)
  {
    case CAAISysGeomFactory::Root :
     Name = "CAASysGeomRootObj" ;
     rc = ::CATInstantiateComponent( "CAASysGeomRootObj",  
                                       iIID,
					  				  (void**)oCreatedObj);
     break;      
    case CAAISysGeomFactory::Point : 
     Name = "CAASysPoint" ;
     rc = ::CATInstantiateComponent( "CAASysPoint",  
                                       iIID,
					  				  (void**)oCreatedObj); 
     break;
    case CAAISysGeomFactory::Plane : 
     Name = "CAASysPlane" ;
     rc = ::CATInstantiateComponent( "CAASysPlane",  
                                       iIID,
					  				  (void**)oCreatedObj); 
     break;
    case CAAISysGeomFactory::Line : 
     Name = "CAASysLine" ;
     rc = ::CATInstantiateComponent( "CAASysLine",  
                                       iIID,
					  				  (void**)oCreatedObj); 
     break;
    case CAAISysGeomFactory::Polyline : 
     Name = "CAASysPolyline" ;
     rc = ::CATInstantiateComponent( "CAASysPolyline",  
                                       iIID,
					  				  (void**)oCreatedObj); 
     break;
    case CAAISysGeomFactory::Circle : 
     Name = "CAASysCircle" ;
     rc = ::CATInstantiateComponent( "CAASysCircle",  
                                       iIID,
					  				  (void**)oCreatedObj); 
     break;
    case CAAISysGeomFactory::Ellipse : 
     Name = "CAASysEllipse" ;
     rc = ::CATInstantiateComponent( "CAASysEllipse",  
                                       iIID,
					  				  (void**)oCreatedObj); 
     break;
    case CAAISysGeomFactory::Cuboid : 
     Name = "CAASysCuboid" ;
     rc = ::CATInstantiateComponent( "CAASysCuboid",  
                                       iIID,
					  				  (void**)oCreatedObj);

     break;
    case CAAISysGeomFactory::Cylinder : 
     Name = "CAASysCylinder" ;
     rc = ::CATInstantiateComponent( "CAASysCylinder",  
                                       iIID,
					  				  (void**)oCreatedObj);
     break;
  }

  // A default name is set for the new component
  if ( (NULL != (*oCreatedObj)) &&  SUCCEEDED(rc) )
  {
      CAAISysName * pIName = NULL ;
      rc = (*oCreatedObj)->QueryInterface(IID_CAAISysName, (void**) &pIName);
      if ( SUCCEEDED(rc) )
      {
         pIName->SetName(Name);
 
         pIName->Release();
         pIName = NULL ;
      }
  }

  return rc;

}

