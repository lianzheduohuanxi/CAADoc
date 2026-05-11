// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
//
#include <iostream.h>

#include "CAAPspUtilityMacros.h"

// ObjectModelerBase and System
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATDocumentServices.h"
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATInit.h"
#include "LifeCycleObject.h"
#include "CATObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIDocRoots.h"

// This framework
#include "CAAPspBaseEnv.h"

// CATPlantShipInterfaces
#include "CATIPspLightPart.h"
#include "CATIPspPhysical.h"
#include "CATIPspLogicalLine.h"
#include "CATIPspApplication.h"

// Product Structure
#include "CATIProduct.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspBaseEnv::CAAPspBaseEnv() 
                 :_pDocument (NULL),
                  _pSession (NULL),
                  _pSessionIdent(NULL),
                  _piRootCont (NULL)
{
  cout << "CAAPspBaseEnv::CAAPspBaseEnv()" << endl;
};

//=============================================================================
//  Destructor
//=============================================================================
CAAPspBaseEnv::~CAAPspBaseEnv()
{
  cout << "CAAPspBaseEnv::~CAAPspBaseEnv()" << endl;
  CleanupSession();
  cout << "CAAPspBaseEnv::Done CleanupSession" << endl;
}

//=============================================================================
//  CATProduct Environment
//=============================================================================
void CAAPspBaseEnv::CreateCATProductEnv(const CATUnicodeString &iFileNameToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===   CAAPspBaseEnv::CreateCATProductEnv                 ==="<< endl;
  cout <<"============================================================"<< endl;

  CleanupSession();

  //---------------------------------------------------------------------------
  // Create Session
  //---------------------------------------------------------------------------
  _pSessionIdent = "Session DSA CAAPspBaseEnv CATProduct";
   ::Create_Session (_pSessionIdent, _pSession);
  if (NULL == _pSession)
  {
     cout << "Cannot create session" << endl;
     return;
  }
  cout << "Create_Session successfully" <<endl;  

  //---------------------------------------------------------------------------
  // Load document if any
  //--------------------------------------------------------------------------- 
  CATInit_var spInit = NULL_var;
  if ( iFileNameToBeLoaded.GetLengthInChar() )
  {
     cout << "Loading ... " << iFileNameToBeLoaded << endl;
     if (SUCCEEDED (CATDocumentServices::OpenDocument (iFileNameToBeLoaded,_pDocument)))
     {
        spInit = _pDocument;
        cout << "Loading successfully ..." << endl;
     }
     else
     {
        cout << "*** Loading failed ..." << endl;
     }
  }

  //---------------------------------------------------------------------------
  // Get root container
  //--------------------------------------------------------------------------- 
  if (NULL_var != spInit)
  {
     cout << "Get RootContainer" << endl;
     _piRootCont = (CATIContainer *)spInit->GetRootContainer (CATIContainer::ClassName());
  }
}

//=============================================================================
//  Get Document
//=============================================================================
CATDocument * CAAPspBaseEnv::GetDocument ()
{
  return (_pDocument);
}

//=============================================================================
//  Get Root Container
//=============================================================================
CATIContainer * CAAPspBaseEnv::GetRootContainer ()
{
  return (_piRootCont);
}

//=============================================================================
//  Initialize Piping Design application
//=============================================================================
void CAAPspBaseEnv::ApplicationInit (const CATUnicodeString &iuApplicationContext)
{
  //------------------------------------------------------------------------
  // Create Piping application object and initialize the application
  //------------------------------------------------------------------------
  CATObject *piObj = NULL;
  if (!iuApplicationContext.IsNull())
    piObj = new CATObject(iuApplicationContext);
  if ( NULL != piObj )
  {
     CATIPspApplication *piPspApp = NULL;
     if ( SUCCEEDED(piObj->QueryInterface(IID_CATIPspApplication,(void **)&piPspApp)) && piPspApp )
     {
        if ( NULL != _piRootCont )
        {
           if ( SUCCEEDED(piPspApp->Initialization(_piRootCont)) )
              cout << iuApplicationContext << " application initialized" << endl;
           else
              cout << iuApplicationContext << " application initialization failed" << endl;
        }
        piPspApp->Release();
        piPspApp = NULL;
     }
     piObj->Release();
     piObj = NULL;
  }
}

//=============================================================================
//  Get root product in the document
//=============================================================================
CATIProduct * CAAPspBaseEnv::GetRootProduct ()
{
  CATListValCATBaseUnknown_var* Roots = NULL;
  CATIProduct *opiRootProduct = NULL;

  if ( NULL != _pDocument )
  {
     CATIDocRoots_var spDocRoot (_pDocument);
     if ( NULL_var != spDocRoot )
     {
        Roots = spDocRoot->GiveDocRoots();
        if ( NULL != Roots )
        {
           CATIProduct_var spRootPrd = (*Roots)[1];
           delete Roots;  Roots = NULL;
           if (!!spRootPrd)
             spRootPrd->QueryInterface(IID_CATIProduct, (void**)&opiRootProduct);
        }
     }
  }
  return (opiRootProduct);
}

//=============================================================================
//  Get a child object
//=============================================================================
IUnknown * CAAPspBaseEnv::GetChildObject (IUnknown * iObjectTestMethod(const CATBaseUnknown_var &ispObject), 
                                          const CATIProduct *ipiParentProduct)
{
  CATIProduct *piParentProduct = NULL;
  CATListValCATBaseUnknown_var* Children = NULL;
  IUnknown *piChildObject = NULL;

  if (ipiParentProduct)
    ((CATIProduct*)ipiParentProduct)->QueryInterface(IID_CATIProduct, (void**)&piParentProduct);
  else
    piParentProduct = GetRootProduct();
  if ( piParentProduct )
  {
    Children = piParentProduct->GetAllChildren();
    if ( NULL != Children )
    {
       int Size = Children->Size();
       for ( int i = 1; i <= Size; i++ )
       {
          CATBaseUnknown_var spCBU = (*Children)[i];
          if (piChildObject = iObjectTestMethod(spCBU))
            break;
       }
       DeleteObject(Children);
    }
    //ReleaseIUnknown(piParentProduct);
    piParentProduct->Release();
  }
  return (piChildObject);
}

//=============================================================================
//  Get a child object
//=============================================================================
IID IID_GetChildObjectTest;
CATUnicodeString uObjectName_GetChildObjectTest;
IUnknown * GetChildObjectTest(const CATBaseUnknown_var &ispObject)
{
  IUnknown *piChildObject = NULL;
  if (!!ispObject)
  {
    if (uObjectName_GetChildObjectTest.IsNull() || 
        2 == uObjectName_GetChildObjectTest.Compare(GetObjectName(ispObject)))
    {
      ispObject->QueryInterface(IID_GetChildObjectTest, (void**)&piChildObject);
    }
  }
  return piChildObject;
}
IUnknown * CAAPspBaseEnv::GetChildObject (const IID &iIID, 
                                          const CATUnicodeString &iuObjectName, 
                                          const CATIProduct *ipiParentProduct)
{
  IID_GetChildObjectTest = iIID;
  uObjectName_GetChildObjectTest = iuObjectName;
  return GetChildObject(GetChildObjectTest);
}

//=============================================================================
//  Get a physical object in the document
//=============================================================================
IUnknown * GetAPhysicalObjectTest(const CATBaseUnknown_var &ispObject)
{
  IUnknown *piPhysical = NULL;
  if (!!ispObject)
  {
    CATISpecObject_var spSpec = ispObject;
    if ( NULL_var != spSpec )
    {
      // Filter out Equipment and Nozzle objects
      if ( !(spSpec->IsSubTypeOf("CATEqtEquipment")) &&
           !(spSpec->IsSubTypeOf("CATEqtNozzle")) )
        ispObject->QueryInterface(IID_CATIPspPhysical, (void**)&piPhysical);
    }
  }
  return piPhysical;
}
CATIPspPhysical * CAAPspBaseEnv::GetAPhysicalObject (const CATIProduct *ipiParentProduct)
{
  return (CATIPspPhysical*)GetChildObject(GetAPhysicalObjectTest, ipiParentProduct);
}

//=============================================================================
//  Get a physical light object in the document
//=============================================================================
CATIPspLightPart * CAAPspBaseEnv::GetALightObject (const CATIProduct *ipiParentProduct)
{
  return (CATIPspLightPart*)GetChildObject(IID_CATIPspLightPart, "", ipiParentProduct);
}

//=============================================================================
//  Get a bendable pipe object in the document
//=============================================================================
IUnknown * GetABendablePipeObjectTest(const CATBaseUnknown_var &ispObject)
{
  IUnknown *piPhysical = NULL;
  if (!!ispObject)
  {
    CATISpecObject_var spSpec = ispObject;
    if ( NULL_var != spSpec )
    {
      // Filter out Equipment and Nozzle objects
      if (spSpec->IsSubTypeOf("CATPipBendablePipe"))
        ispObject->QueryInterface(IID_CATIPspPhysical, (void**)&piPhysical);
    }
  }
  return piPhysical;
}
CATIPspPhysical * CAAPspBaseEnv::GetABendablePipeObject (const CATIProduct *ipiParentProduct)
{
  return (CATIPspPhysical*)GetChildObject(GetABendablePipeObjectTest, ipiParentProduct);
}

//=============================================================================
//  Get a logical line object in the document
//=============================================================================
CATIPspLogicalLine * CAAPspBaseEnv::GetALogicalLine (const CATIProduct *ipiParentProduct)
{
  return (CATIPspLogicalLine*)GetChildObject(IID_CATIPspLogicalLine, "", ipiParentProduct);
}

/*=============================================================================
//  Save Document
//=============================================================================
void CAAPspBaseEnv::SaveDocument (const CATUnicodeString &iFileName)
{
  if (NULL != _pDocument)
  {
     HRESULT RC = CATDocumentServices::SaveAs ( *_pDocument, iFileName);
     cout << "Document : " << iFileName << " saved !!!" << endl;
  }
  else
  {
     cout << "Document : " << iFileName << " NOT saved !!!" << endl;
     cout << "pointer to document is NULL, perhaps, it has been released !!!"
          <<endl;
  }
}*/

//=============================================================================
//  CleanupSession
//=============================================================================
void CAAPspBaseEnv::CleanupSession ()
{
  cout << "CleanupSession ---" << endl;

  if (NULL != _piRootCont) 
  {
    _piRootCont->Release();
    _piRootCont = NULL;
  }

  if (NULL != _pDocument)
  {
    LifeCycleObject_var spLifeCycle = _pDocument;
    spLifeCycle->remove();
    cout << "document removed !!!!" << endl;
    _pDocument = NULL;
  }

  if (NULL != _pSession)
  {
     ::Delete_Session (_pSessionIdent);
     cout << "Session released !!!!" << endl ;
     _pSession = NULL;
  }

  _pSessionIdent = NULL;
}
