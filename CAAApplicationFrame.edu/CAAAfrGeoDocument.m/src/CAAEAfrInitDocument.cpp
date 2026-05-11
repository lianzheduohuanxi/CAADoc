// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEAfrInitDocument.h"

// CAASystem.edu Framework
#include "CAAISysCollection.h"

// C++ standrad library 
#include <iostream.h>  

// System framework 
#include "CATErrorDef.h" // for the SUCCEEDED macro
#include "CATInstantiateComponent.h"  

//
//  _______________ Extension of a CAAGeometry Document  _______________
//
// To create TIE Objects
#include "TIE_CATInit.h"              
TIE_CATInit(CAAEAfrInitDocument); 

// To declare that the class is a data extension of (the late type) CAAGeom
// (which is the document suffix), see the CAAEAfrAliasDocument.cpp
//
CATImplementClass(CAAEAfrInitDocument, DataExtension, CATBaseUnknown,CAAGeom);

//  _______________ Dictionary to modify   _____________________________
// 
// To declare that CAAEAfrInitDocument implements  CATIinit  insert 
// the following lines in the interface dictionary:
//
//    CAAGeom CATInit  libCAAAfrGeoDocument
//
// _______________ Constructor - Destructor _____________________________
//

CAAEAfrInitDocument::CAAEAfrInitDocument():_pGeomCont(NULL)
{
  cout << "Constructing CAAEAfrInitDocument"  << endl;
}

CAAEAfrInitDocument::~CAAEAfrInitDocument()
{ 
  cout << "Destructing CAAEAfrInitDocument"  << endl; 
  
  if (  NULL != _pGeomCont )
  {
    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pGeomCont->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      piSysCollection->Empty();

      piSysCollection->Release(); 
      piSysCollection = NULL ;
    }

    _pGeomCont->Release();
    _pGeomCont = NULL ;
  }

}

void CAAEAfrInitDocument::Init(CATBoolean iDestroyExistingData)  
{
   cout << "CAAEAfrInitDocument::Init"  << endl;
   
  // Creation of the container of the document
  // which contains all the objects of the document
   ::CATInstantiateComponent("CAASysGeomCont",IID_CATBaseUnknown,(void**)&_pGeomCont);


}


// GetRootContainer 
// -----------------
// Returns the pointer of the root container, and not the pointer on the asked interface 
//
// 

CATBaseUnknown* CAAEAfrInitDocument::GetRootContainer (const CATIdent InterfaceID)
{
  cout << "CAAEAfrInitDocument::GetRootContainer"  << endl;

  if ( NULL != _pGeomCont )
  {
	 return ( _pGeomCont->QueryInterface(InterfaceID) );                                      
  }
  return _pGeomCont ;

}








