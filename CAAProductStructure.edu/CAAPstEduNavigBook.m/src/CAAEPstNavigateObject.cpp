// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEPstNavigateObject.h"
#include "CAAPstBookExtProvider.h"

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"   // contains the CATListValCATBaseUnknown_var class def
#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATINavigateObject.h"

// ObjectSpecsModeler Framework
#include "CATIClientContainer.h"
#include "CATISpecObject.h"

// ProductStructure Framework
#include "CATINavigateProvider.h"
#include "CATIProviders.h"

// System Framework
#include "CATListOfCATUnicodeString.h" // contains the CATListValCATUnicodeString class definition

// System Framework
#include "CATUnicodeString.h"

// C++ Standard Library
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject(CAAEPstNavigateObject);

// Declares that the class is a data extension of CAAPstSampleCont. 
//
CATImplementClass(CAAEPstNavigateObject,
		  DataExtension,
		  CATBaseUnknown,
		  CAAPstBook);
// 
// To declare that CAAEPstNavigateObject implements the CATINavigateObject 
// interface, insert these following lines in the interface dictionary:
//
//    CAAOsmBook      CATINavigateObject  libCAAPstEduNavigBook
//
//
//---------------------------------------------------------------------------------------------

CAAEPstNavigateObject::CAAEPstNavigateObject()
{
  cout << "CAAEPstNavigateObject::CAAEPstNavigateObject" << endl;
}

//---------------------------------------------------------------------------------------------

CAAEPstNavigateObject::~CAAEPstNavigateObject()
{
  cout <<"CAAEPstNavigateObject::~CAAEPstNavigateObject" << endl;
}

//---------------------------------------------------------------------------------------------

CATListValCATUnicodeString * CAAEPstNavigateObject::GetIdentificators()
{
  cout << "***** CAAOsmBook: CAAEPstNavigateObject::GetIdentificators" << endl;

  CATListOfCATUnicodeString *pIdent = new CATListOfCATUnicodeString;

  CATISpecObject *piSpecObjectOnBook = NULL;
  HRESULT rc = this -> QueryInterface(IID_CATISpecObject,
			                  (void**)&piSpecObjectOnBook);
  if (SUCCEEDED(rc))
  {
	  // Retrieve the applicative container's name
      CATUnicodeString bookId = piSpecObjectOnBook -> GetDisplayName();
      piSpecObjectOnBook -> Release();
	  piSpecObjectOnBook = NULL;

      // String added to the list 
      pIdent -> Append(bookId);
  }

  return pIdent;
}

//---------------------------------------------------------------------------------------------

CATListValCATBaseUnknown_var * CAAEPstNavigateObject::GetChildren()
{
  cout << "***** CAAOsmBook: CAAEPstNavigateObject::GetChildren" << endl;

  CATListValCATBaseUnknown_var *pList = NULL ;
  pList = new CATListValCATBaseUnknown_var();
  
  // Retrieve the list of declared providers

  CATLISTP(CATBaseUnknown) *pListProvider = new CATLISTP(CATBaseUnknown);
  CATLISTP(CATBaseUnknown) *pListChildren = NULL;

  // Retrieve a CATILinkableObject pointer on the CAAOsmBook feature in order
  // to get a CATDocument pointer to the document which contains it.
  CATILinkableObject * piLinkableOnExtFeature = NULL;
  HRESULT rc = this -> QueryInterface (IID_CATILinkableObject,
	                           (void**) &piLinkableOnExtFeature);
  if (!SUCCEEDED(rc)) return pList;

  CATDocument *pDoc = piLinkableOnExtFeature -> GetDocument();
  piLinkableOnExtFeature -> Release();
  piLinkableOnExtFeature = NULL;
  if (NULL == pDoc) return pList;

  // Retrieve a CATIProviders pointer on the document.
  CATIProviders * piProvidersOnDoc = NULL;
  rc = pDoc -> QueryInterface (IID_CATIProviders,
	                           (void**) &piProvidersOnDoc);
  if (!SUCCEEDED(rc)) return pList;

  // Retrieve a list of the providers that have been declared to the document.
  rc = piProvidersOnDoc -> ListProviders (CATINavigateProvider::ClassId(),
	                                      &pListProvider);
  piProvidersOnDoc -> Release();
  piProvidersOnDoc = NULL;

  // For each declared provider, get the CATINavigateProvider interface pointer to
  // execute the GetChildren method and append the list of children returned to the
  // list to be constructed.

  if(SUCCEEDED(rc))
  {
     int size = pListProvider->Size();
	 for (int i=size; i>=1; i--)
	 {
		 // Retrieve a CATINavigateProvider pointer on the provider
		 CATINavigateProvider *piNav = NULL;
		 CATBaseUnknown *pProvider = (*pListProvider)[i];
		 if (NULL == pProvider)
			 break;
		 rc = pProvider -> QueryInterface(IID_CATINavigateProvider,
			                                  (void**) &piNav);
		 if (SUCCEEDED(rc))
		 {
			 pListChildren = new CATLISTP(CATBaseUnknown);
			 // Retrieve the list of the children of the current object 
			 piNav -> GetChildren (this, &pListChildren);
			 if (NULL != pListChildren)
			 	for(int j=1;j<=pListChildren->Size();j++)
				{
				   CATBaseUnknown *pChild = (*pListChildren)[j];
				   if(NULL != pChild)
				   {
				       // Append the child to the list being constructed.
					   CATINavigateObject_var navChild (pChild);
					   if(navChild!=NULL_var)
					      pList->Append(navChild);
					   pChild->Release();
				   }
				}
			 delete pListChildren;
			 pListChildren = NULL;
			 piNav->Release();
		 }
	 }
	 delete pListProvider;
  }
  return pList;
}
		
