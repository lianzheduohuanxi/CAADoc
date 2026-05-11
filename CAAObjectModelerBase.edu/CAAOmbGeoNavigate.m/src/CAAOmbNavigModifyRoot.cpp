// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAOmbNavigModifyRoot.h"

// ObjectModelerBase Framework
#include "CATIGraphNode.h"             // SetColor, SetPixelImage      
#include "CATNavigInstance.h"          // Argument type de UpdateElem:  not used

// C++ Standard Library
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATINavigModify.h"
TIE_CATINavigModify(CAAOmbNavigModifyRoot);

// Declares that the class is a data extension of CAASysGeomRootObj_node. 
//
CATImplementClass(CAAOmbNavigModifyRoot,
				  DataExtension,
				  CATBaseUnknown,
				  CAASysGeomRootObj_node);
// 
// To declare that CAAOmbNavigModifyRoot implements the CATINavigModify 
// interface, insert these following lines in the interface dictionary:
//
//    CAASysGeomRootObj_node     CATINavigModify  libCAAOmbGeoNavigate
//
//
//---------------------------------------------------------------------------------------------

CAAOmbNavigModifyRoot::CAAOmbNavigModifyRoot()
{
  cout << "CAAOmbNavigModifyRoot::CAAOmbNavigModifyRoot" << endl;
}

//---------------------------------------------------------------------------------------------

CAAOmbNavigModifyRoot::~CAAOmbNavigModifyRoot()
{
  cout <<"CAAOmbNavigModifyRoot::~CAAOmbNavigModifyRoot" << endl;
}

//---------------------------------------------------------------------------------------------

void CAAOmbNavigModifyRoot::UpdateElem(CATNavigInstance * iInstance)
{
  cout << "CAAOmbNavigModifyRoot::UpdateElem" << endl;

  CATIGraphNode *piGraphNode = NULL  ;
  HRESULT rc = QueryInterface(IID_CATIGraphNode,
	                          (void**)&piGraphNode);
  
  if ( SUCCEEDED(rc) ) 
  {
      // Set the node to green instead of blue (default)
      piGraphNode -> SetColor(50);

	  // Attach an icon to the node
	  CATUnicodeString iconName("CAAOmbIcon2");
	  piGraphNode -> SetPixelImage(iconName);

      piGraphNode -> Release();
      piGraphNode= NULL ;
  }
}

