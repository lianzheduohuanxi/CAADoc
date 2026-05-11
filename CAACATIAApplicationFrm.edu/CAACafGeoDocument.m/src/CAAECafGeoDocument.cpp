// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAECafGeoDocument.h"

// CAASystem.edu Framework
#include "CAAISysGeomFactory.h"
#include "CAAISysCollection.h"

// ApplicationFrame Framework 
#include "CATFrmWindow.h"       
#include "CATFrmEditor.h"       

// CATIAApplicationFrame Framework
#include "CATFrmGraphAnd3DWindow.h"

// System Framework
#include "CATString.h" 

//C++ standard library
#include <iostream.h>  

// ObjectModelBase Framework
#include <CATInit.h>

// Dialog Framework
#include <CATMsgCatalog.h> 

//
//  _______________ Extension of a CAAGeometry Document  _______________
//
// To declare that the class is a data extension of (the late type) CAAGeom
// (which is the document suffix)
//
CATImplementClass(CAAECafGeoDocument, DataExtension, CATBaseUnknown,CAAGeom);

//  _______________ Dictionary to modify   _____________________________
// 
// To declare that CAAECafGeoDocument implements CATIDocumentEdit, 
// insert the following line in the interface dictionary:
//
//    CAAGeom  CATIDocumentEdit  libCAACafGeoDocument
//
// _______________ Constructor - Destructor _____________________________
//

CAAECafGeoDocument::CAAECafGeoDocument()
{
  cout << "Constructing CAAECafGeoDocument"  << endl;

  CATInit * pCATInit = NULL ;
  HRESULT rc = QueryInterface(IID_CATInit, (void**)&pCATInit);
                                          
  // Construction of the UIActivable object CAASysGeomRootObj
  if ( SUCCEEDED(rc) )
  {		   
    CATBaseUnknown * pContainer = pCATInit->GetRootContainer("CATBaseUnknown") ;
    
    if ( NULL != pContainer )
    {
       CATBaseUnknown     * pRootObject      =  NULL ;
       CAAISysGeomFactory * piSysGeomFactory = NULL;                
       rc = pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
       if (SUCCEEDED(rc))
       {
          piSysGeomFactory ->Create(CAAISysGeomFactory::Root, IID_CATBaseUnknown, &pRootObject);
          piSysGeomFactory ->Release() ;
          piSysGeomFactory = NULL ;
       }

       if ( NULL != pRootObject )
       {
          // Adds the root object to the container
         CAAISysCollection * piSysCollection = NULL;                
         rc = pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
         if (SUCCEEDED(rc))
         {
           piSysCollection->AddObject(pRootObject);
           piSysCollection -> Release();
           piSysCollection = NULL ;
         }
         // The first road to the UI activable object 
         _ActivePath.AddChildElement(pRootObject);

         // Done with the root object
         pRootObject->Release() ;
         pRootObject = NULL ;
       }

       pContainer->Release();
       pContainer = NULL ;
    }

    pCATInit->Release();
    pCATInit = NULL ;
  }
           
}

//----------------------------------------------------------------------------------
CAAECafGeoDocument::~CAAECafGeoDocument()
{ 
  cout << "Destructing CAAECafGeoDocument"  << endl;   
}

//
// _______________ CATIDocumentEdit _____________________________
//

// To Create the TIE object
//
#include "TIE_CATIDocumentEdit.h"             
TIE_CATIDocumentEdit(CAAECafGeoDocument); 

//----------------------------------------------------------------------------------
CATFrmWindow * CAAECafGeoDocument::CreateDefaultWindow(CATFrmEditor *iEditor)
{ 
  cout << "CAAECafGeoDocument::CreateDefaultWindow"  << endl;

  // Window to return
  CATFrmGraphAnd3DWindow * pWindow = NULL ;

  // This identifier is used to define the window's resources.
  CATString WindowName = "CATFrmGraphAnd3DWindow" ;

   
  if ( 0 != GetActiveObject().GetSize() )
  {
    // Retrieves the root object to draw 
    CATBaseUnknown_var model = GetActiveObject()[0];

    // CATFrmGraphAnd3DWindow derives from CATFrmWindow
    pWindow = new CATFrmGraphAnd3DWindow(WindowName,model,iEditor);
    
	// Window Title= The base name + number 
    CATUnicodeString BaseName = CATMsgCatalog::BuildMessage("CAACafGeoDocumentWindow",
                                        "BaseName",NULL,0,"Geometry Document");
    pWindow->SetBaseName(BaseName);
    
	// To make it the current window  
    CATFrmLayout *currentLayout = CATFrmLayout::GetCurrentLayout();
    currentLayout->SetCurrentWindow(pWindow);
  }

  return pWindow ;
}

//----------------------------------------------------------------------------------
void CAAECafGeoDocument::Activate()
{ 
	// Empy method
}

//----------------------------------------------------------------------------------
void CAAECafGeoDocument::Deactivate()
{ 
	// Empty method
}

//----------------------------------------------------------------------------------
CATPathElement CAAECafGeoDocument::GetActiveObject()
{ 
  cout << "CAAECafGeoDocument::GetActiveObject()" << endl ;
  return _ActivePath ; 
}

//----------------------------------------------------------------------------------
void * CAAECafGeoDocument::MemoryDraw(unsigned short iFormat, int iWidth, int iHeight)
{ 
  return ( void * ) NULL ;
}

    





