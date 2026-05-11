// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAOmbNavigateObjectRoot.h"

// CAASystem.edu Framework
#include "CAAISysAccess.h"       // Interface to retrieve the object which 
                                 // implements the CAAISysCollection interface
#include "CAAISysCollection.h"   // To retrieve the list of object at the root node

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"   // contains the CATListValCATBaseUnknown_var class def

// System Framework
#include "CATListOfCATUnicodeString.h" // contains the CATListValCATUnicodeString class definition
#include "CATUnicodeString.h"

// CAASystem.edu Framework
#include "CAAISysName.h"               // To retrieve the name of the component

// C++ Standard Library
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject(CAAOmbNavigateObjectRoot);

// Declares that the class is a data extension of CAASysGeomRootObj. 
//
CATImplementClass(CAAOmbNavigateObjectRoot,
				  DataExtension,
				  CATBaseUnknown,
				  CAASysGeomRootObj);
// 
// To declare that CAAOmbNavigateObjectRoot implements the CATINavigateObject 
// interface, insert these following lines in the interface dictionary:
//
//    CAASysGeomRootObj      CATINavigateObject  libCAAOmbGeoNavigate
//
//
//---------------------------------------------------------------------------------------------

CAAOmbNavigateObjectRoot::CAAOmbNavigateObjectRoot()
{
  cout << "CAAOmbNavigateObjectRoot::CAAOmbNavigateObjectRoot" << endl;
}

//---------------------------------------------------------------------------------------------

CAAOmbNavigateObjectRoot::~CAAOmbNavigateObjectRoot()
{
  cout <<"CAAOmbNavigateObjectRoot::~CAAOmbNavigateObjectRoot" << endl;
}

//---------------------------------------------------------------------------------------------

CATListValCATUnicodeString * CAAOmbNavigateObjectRoot::GetIdentificators()
{
  cout << "CAAOmbNavigateObjectRoot::GetIdentificators" << endl;

  CATListOfCATUnicodeString *pIdent = new CATListOfCATUnicodeString;

   // The String displayed in the graph 
  CATUnicodeString Name = "Root" ;

  // Retrieves the name of the component
  //
  CAAISysName * pISysName = NULL ;
  HRESULT rc = QueryInterface(IID_CAAISysName, (void**) & pISysName);
  if ( SUCCEEDED(rc) )
  {
     pISysName->GetName(Name);
     pISysName->Release();
     pISysName = NULL ;
  }

  // String added to the list 
  pIdent -> Append(Name);

  return pIdent;

}

//---------------------------------------------------------------------------------------------

CATListValCATBaseUnknown_var * CAAOmbNavigateObjectRoot::GetChildren()
{
  cout << "CAAOmbNavigateObjectRoot::GetChildren" << endl;

  CATListValCATBaseUnknown_var *pList = NULL ;

  // The interface CAAISysAccess implemented by "this" contains the container object
  // which implements the CAAISysCollection interface from which we can retrieve
  // all objects of the model.
    
  CAAISysAccess  *piSysAccess = NULL  ;
  HRESULT rc = QueryInterface(IID_CAAISysAccess,
	                          (void**)&piSysAccess);
                                               
  if ( SUCCEEDED(rc) )
  {
      // Retrieves the container 
      CATBaseUnknown *pContainer = NULL ;
      piSysAccess -> GetContainer(&pContainer);
      if ( NULL != pContainer) 
      {
          // Retrieves its interface CAAISysCollection pointer
          CAAISysCollection *piSysCollection = NULL ;
          rc = pContainer -> QueryInterface(IID_CAAISysCollection,
			                                (void**)&piSysCollection);
          if ( SUCCEEDED(rc) )
          {
              // The collection contains at least the root object (this), and all
              // objects of the model. 
              int count(0);
              piSysCollection -> GetNumberOfObjects(&count);
              if ( count > 1 )
              {
                 // The collection has at least one object in addition to 
                 // the root object. 

                 // Creation of the list to fill
                 pList = new CATListValCATBaseUnknown_var();

                 // The root object is not a child. It is the node of the tree
                 // so the loop begins at 2. 
                 //
                 for (int i=2; i<=count; i++)
                 {
                    // Retrieves the n-th object in the container
                    CATBaseUnknown * pObject = NULL ;
                    piSysCollection -> GetObject(i, &pObject);

                    if ( NULL != pObject )
                    {
                       // Adds the object in the list 
                       pList -> Append(pObject);
                    
                       // pointer no any longer needed
                       pObject -> Release();
                       pObject = NULL ;
                    }
                 }
              }
              piSysCollection -> Release();
              piSysCollection = NULL ;
          }
          pContainer -> Release();
          pContainer = NULL ;
      }
      piSysAccess -> Release();
      piSysAccess = NULL ;
  }

  return pList;
  
}
//---------------------------------------------------------------------------------------------
