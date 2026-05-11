// COPYRIGHT Dassault Systemes 2002

// System Framework
#include "CATLISTV_CATBaseUnknown.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// Visualization Framework
#include "CATPathElement.h"

// ObjectModelerBase Framework
#include "CATINavigateObject.h"
#include "CATICutAndPastable.h"

// Local Framework
#include "CAAEPstINFCCPRoot.h"
#include "CAAIPstINFRoot.h"

// Others
#include <iostream.h>
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICutAndPastable.h"
TIE_CATICutAndPastable( CAAEPstINFCCPRoot);


// To declare that the class is a data extension of "CAAPstINFRoot" 
//
CATImplementClass( CAAEPstINFCCPRoot,
                   DataExtension,
                   CATBaseUnknown,
                   CAAPstINFRoot );
 
// To declare that CAAEPstINFCCPRoot implements CATICutAndPastable for the
// CAAIPstINFRoot component, insert the following line in the interface dictionary:
//
//    CAAPstINFRoot   CATICutAndPastable  libCAAINFModeler

//-----------------------------------------------------------------------------
// CAAEPstINFRoot : constructor
//-----------------------------------------------------------------------------
CAAEPstINFCCPRoot::CAAEPstINFCCPRoot():
    ObjectCCP_SPEC()
{
}

//-----------------------------------------------------------------------------
// CAAEPstINFRoot : destructor
//-----------------------------------------------------------------------------
CAAEPstINFCCPRoot::~CAAEPstINFCCPRoot()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATICutAndPastable::BoundaryExtract
//-----------------------------------------------------------------------------
int CAAEPstINFCCPRoot::BoundaryExtract (ListOfVarBaseUnknown &pObjectsAlreadyInBoundary, 
                                        const ListOfVarBaseUnknown *pObjectsToAdd, 
                                        const CATFormat *pAnImposedFormat) const
{
  cout <<"******CAAEPstINFCCPRoot::BoundaryExtract"<<endl;

  // Retrieve a list of the root's children
  int num = 0;
  CAAIPstINFRoot *piRoot = NULL;
  CATBaseUnknown *pRoot = (CATBaseUnknown*) this;
  if (NULL == pRoot) return num;
  HRESULT rc = pRoot -> QueryInterface(IID_CAAIPstINFRoot,
	                                   (void**) &piRoot);
  if (FAILED(rc)) return num;
 
  CATListValCATBaseUnknown_var *pList = NULL;
  rc = piRoot -> GetChildren(&pList);

  piRoot->Release();
  piRoot = NULL;

  if (SUCCEEDED(rc) && pList)
  {
      for (int i=1; i<=pList->Size(); i++)
	  {
          pObjectsAlreadyInBoundary.Append((*pList)[i]);
          num ++;
	  }
  }
  else cout << "Error in GetChildren." << endl;

  delete pList;
  pList = NULL;

  return num;
}

//---------------------------------------------------------------------------------
// Implements CATICutAndPastable::BoundaryRemove
// This method is over-ridden in order to prevent the root node from being deleted.
//---------------------------------------------------------------------------------
int CAAEPstINFCCPRoot::BoundaryRemove (ListOfVarBaseUnknown &pObjectsAlreadyInBoundary, 
                                       const ListOfVarBaseUnknown *pObjectsToRemove, 
                                       const CATFormat *pAnImposedFormat) const
{
  cout <<"******CAAEPstINFCCPRoot::BoundaryRemove"<<endl;
  
  return 0; // prohibit the removal of the root
}

//---------------------------------------------------------------------------------
// Implements CATICutAndPastable::Remove
// This method is over-ridden in order to prevent the root node from being deleted.
//---------------------------------------------------------------------------------
int CAAEPstINFCCPRoot::Remove (ListOfVarBaseUnknown &pObjectToRemove,
							   const CATFormat *pAnImposedFormat)
{
  cout <<"******CAAEPstINFCCPRoot::Remove"<<endl;

  return 0; // prohibit the removal of the root
}

