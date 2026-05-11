// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEAfrDocumentEdit.h"
#include "CAAAfrCustomWindow.h"

// CAASystem.edu Framework
#include "CAAISysCollection.h"
#include "CAAISysGeomFactory.h" 

// C++ Standrad library
#include <iostream.h>     

// ApplicationFrame Framework 
#include "CATFrmWindow.h"       
#include "CATFrmEditor.h"  

// System Framework
#include "CATString.h"  

// Dialog Framework
#include <CATMsgCatalog.h>       

// ObjectModelBase Framework
#include <CATInit.h>
 
//---------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIDocumentEdit.h"             
TIE_CATIDocumentEdit(CAAEAfrDocumentEdit); 

// To declare that the class is a data extension of (the late type) CAADoc 
// (which is the document suffix)
//
CATImplementClass(CAAEAfrDocumentEdit, DataExtension, CATBaseUnknown, CAADoc);

// 
// To declare that CAAEAfrDocumentEdit implements CATIDocumentEdit, insert 
// the following line in the interface dictionary:
//
//    CAADoc CATIDocumentEdit  libCAAAfrSampleDocument
//
//---------------------------------------------------------------------------------

CAAEAfrDocumentEdit::CAAEAfrDocumentEdit()
{
  cout << "Constructing CAAEAfrDocumentEdit"  << endl;

  // Construction of the UIActivable object, CAASysSampRootObj
  // by a factory implemented by this container
  // 
  CATInit * pCATInit = NULL ;
  HRESULT rc = QueryInterface(IID_CATInit, (void**)&pCATInit);
                                          
  // Construction of the UIActivable object CAASysGeomRootObj
  if ( SUCCEEDED(rc) )
  {		   
    CATBaseUnknown * pContainer = pCATInit->GetRootContainer("CATBaseUnknown") ;

    if ( NULL != pContainer )
    {   
       CATBaseUnknown     * pRootObject     =  NULL ;

       CAAISysGeomFactory * piSysGeomFactory = NULL;                
       rc = pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
       if (SUCCEEDED(rc))
       {
         // Creation on a Root Object by this factory
         piSysGeomFactory->Create(CAAISysGeomFactory::Root, IID_CATBaseUnknown, &pRootObject);
         piSysGeomFactory ->Release() ;
         piSysGeomFactory= NULL  ;
       }

       if ( NULL != pRootObject )
       {
         // Adds the Root Object to the container
         // It's an object of the container 
         //
         CAAISysCollection * pySysCollection = NULL;                
         rc = pContainer->QueryInterface(IID_CAAISysCollection, (void**)&pySysCollection);
         if (SUCCEEDED(rc))
         {
           pySysCollection->AddObject(pRootObject);
           pySysCollection -> Release();
           pySysCollection= NULL ;
         }

         // This Root Object is the object ui activable, so we construct
         // the first road with this object.
         //
         _ActivePath.AddChildElement(pRootObject);

         // Done with pRootObject
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

//---------------------------------------------------------------------------------

CAAEAfrDocumentEdit::~CAAEAfrDocumentEdit()
{ 
  cout << "Destructing CAAEAfrDocumentEdit"  << endl;
  // This destructor should not be explicitly called.
}

//---------------------------------------------------------------------------------

CATFrmWindow * CAAEAfrDocumentEdit::CreateDefaultWindow(CATFrmEditor *iEditor)
{ 
   cout << "CAAEAfrDocumentEdit::CreateDefaultWindow"  << endl;

   // This identifier is used to define the window's resources.
   CATString WindowId = "CustomWindow" ;

   // CAAAfrCustomWindow derives from CATFrmWindow 
   CAAAfrCustomWindow * window = new CAAAfrCustomWindow(WindowId,iEditor);
   window->Build();
   
   // Window Title= The base name + number 
   CATUnicodeString BaseName = CATMsgCatalog::BuildMessage("CAAAfrCustomWindow",
                                        "BaseName",NULL,0,"Customized Window");
   
   window->SetBaseName(BaseName);
  
   // To make it the current window 
   CATFrmLayout *currentLayout = CATFrmLayout::GetCurrentLayout();
   currentLayout->SetCurrentWindow(window);

   return window ;

}

//---------------------------------------------------------------------------------

void CAAEAfrDocumentEdit::Activate()
{ 
	// Empty method
}
void CAAEAfrDocumentEdit::Deactivate()
{ 
	// Empty method
}
//---------------------------------------------------------------------------------

CATPathElement CAAEAfrDocumentEdit::GetActiveObject()
{ 
   cout << " CAAEAfrDocumentEdit::GetActiveObject " << endl ;
   // The first object to ui-actived 
   return _ActivePath ; 
}

//---------------------------------------------------------------------------------

void * CAAEAfrDocumentEdit::MemoryDraw(unsigned short iFormat, int iWidth, int iHeight)
{ 
   cout << "CAAEAfrDocumentEdit::MemoryDraw"<< endl;
   return ( void *) NULL ;
}

//---------------------------------------------------------------------------------


