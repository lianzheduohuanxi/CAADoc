// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEVisVisuRootObject.h"

// CAASystem.edu Framework
#include "CAAISysCollection.h"
#include "CAAISysAccess.h"
    
// Visualization Framework 
#include "CAT3DBagRep.h"
#include "CATVisManager.h"

// others
#include <iostream.h>

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuRootObject);

// To declare that the class is a data extension of CAASysGeomRootObj & 
// CAASysSampRootObj
//
CATBeginImplementClass(CAAEVisVisuRootObject,DataExtension,CATBaseUnknown,CAASysGeomRootObj);
CATAddClassExtension(CAASysSampRootObj);
CATEndImplementClass(CAAEVisVisuRootObject);

// 
// To declare that CAAEVisVisuRootObject implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysGeomRootObj  CATI3DGeoVisu  libCAAVisGeoModel
//    CAASysSampRootObj  CATI3DGeoVisu  libCAAVisGeoModel
//
//-----------------------------------------------------------------------------

CAAEVisVisuRootObject::CAAEVisVisuRootObject()
{
  cout << "CAAEVisVisuRootObject::CAAEVisVisuRootObject" << endl;
}

CAAEVisVisuRootObject::~CAAEVisVisuRootObject()
{
  cout << "CAAEVisVisuRootObject::~CAAEVisVisuRootObject" << endl;
}

CATRep * CAAEVisVisuRootObject::BuildRep()
{
  cout << "CAAEVisVisuRootObject::BuildRep" << endl;

  // The rep to return
  CAT3DBagRep * pRepRoot = new CAT3DBagRep();
 
  // With the CAAISysAccess interface we retrieve the container which contains
  // the UIActivable root object and all objects to draw : point
  // line. These elements are created in the workshop ui activated by 
  // the root object.  
  //
  CAAISysAccess * piSysAccess = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
  if (SUCCEEDED(rc))
  {
     // Retrieves the container 
     CATBaseUnknown * piBuknContainer = NULL ;
     rc = piSysAccess->GetContainer(&piBuknContainer);
     if (SUCCEEDED(rc))
     {
        // Retrieves the collection
        CAAISysCollection * piSysCollection = NULL;                
        rc = piBuknContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
        if (SUCCEEDED(rc))
        {
           // Retrieves the count of object in the container
           int Count(0);
           piSysCollection->GetNumberOfObjects(&Count);
           
           // The first object of the list is itself (the root object) 
           int i;
           for (i=2; i<=Count; i++)
           {
              // Retrieves the ieme object
              CATBaseUnknown * pBuknObject = NULL ;
              piSysCollection->GetObject(i, &pBuknObject);

              if ( NULL != pBuknObject )
              {
                 // Computes or retrieves its graphic representation
                 CATVisManager * pVisuManager = CATVisManager::GetVisManager();
                 
                 CATModelIdentificator Ident(pBuknObject);
                 CAT3DRep * pRepChild = (CAT3DRep *) pVisuManager->BuildRep(Ident);
   
                 if ( NULL != pRepChild )
                 {
                       pRepRoot->AddChild(*pRepChild) ;
                 }
                    
                 // Done with the pointer
                 pBuknObject->Release();
                 pBuknObject = NULL ;
              }

           } 
           // Done with the collection pointer
           piSysCollection -> Release();
           piSysCollection = NULL ;
        } 
        // Done with the container pointer
        piBuknContainer -> Release();
        piBuknContainer = NULL ;
     }
     // Done with the access pointer
     piSysAccess ->Release();
     piSysAccess = NULL ;

  }

  return pRepRoot;
}

