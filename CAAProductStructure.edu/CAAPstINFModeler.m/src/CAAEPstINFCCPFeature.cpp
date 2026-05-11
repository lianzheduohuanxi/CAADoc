// COPYRIGHT Dassault Systemes 2002

// Local Framework
#include "CAAEPstINFCCPFeature.h"
#include "CAAIPstINFRoot.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// ObjectModelerBase Framework
#include "CATICutAndPastable.h"

// Visualization Framework
#include "CATPathElement.h"

// Others
#include <iostream.h>
 
// Tie the implementation to its interface
#include "TIE_CATICutAndPastable.h"
TIE_CATICutAndPastable(CAAEPstINFCCPFeature);

// To declare that the class is a data extension of "CAAPstINFLine", "CAAPstINFPoint" and
// "CAAPstINFWire"
//
CATBeginImplementClass(CAAEPstINFCCPFeature,
   			           DataExtension, 
				       CATBaseUnknown, 
				       CAAPstINFPoint);
CATAddClassExtension(CAAPstINFLine);
CATAddClassExtension(CAAPstINFWire);
CATEndImplementClass(CAAEPstINFCCPFeature); 

// To declare that CAAEPstINFCCPFeature implements CATICutAndPastable for the
// CAAPstINFLine, CAAPstINFPoint and CAAPstINFWire components, insert the following lines
// in the interface dictionary:
//
//    CAAPstINFLine   CATICutAndPastable  libCAAINFModeler
//    CAAPstINFPoint  CATICutAndPastable  libCAAINFModeler
//    CAAPstINFWire   CATICutAndPastable  libCAAINFModeler
//

//-----------------------------------------------------------------------------
// CAAEPstINFCCPFeature : constructor
//-----------------------------------------------------------------------------
CAAEPstINFCCPFeature::CAAEPstINFCCPFeature():
    ObjectCCP_SPEC()
{
}

//-----------------------------------------------------------------------------
// CAAEPstINFCCPFeature : destructor
//-----------------------------------------------------------------------------
CAAEPstINFCCPFeature::~CAAEPstINFCCPFeature()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATICutAndPastable::Update
// This method is called on the paste operation in order to update the root 
// node with the cut or copied object.
//-----------------------------------------------------------------------------
int CAAEPstINFCCPFeature::Update (CATBaseUnknown_Associations &pAssociationOfObjects, 
                                  const CATFormat *pAnImposedFormat , 
                                  ListOfVarBaseUnknown *pToCurObjects)
{
	cout << "*********** CAAEPstINFCCPFeature::Update" << endl;

	//Add this object to the root
    HRESULT rc;
	int num = 0;
	// As long as the list is not null, search for the root node
    if ((NULL != pToCurObjects) && (pToCurObjects->Size())) 
	{
       CATPathElement *pPath = (CATPathElement*)(CATBaseUnknown*)(*pToCurObjects)[1];
       CAAIPstINFRoot *piRoot = NULL;
       if (NULL != pPath)
	   {
          rc = pPath -> Search(IID_CAAIPstINFRoot, (void**) &piRoot);
	   }
       if (SUCCEEDED(rc)) 
	   {
		  // Paste the object under the root
          CATISpecObject *piSpecObjectOnThis = NULL;
		  rc = this -> QueryInterface (IID_CATISpecObject,
			                           (void**) &piSpecObjectOnThis);
		  if (SUCCEEDED(rc))
		  {
			  piRoot -> AddChild (piSpecObjectOnThis);
			  piSpecObjectOnThis -> Release();
		      piSpecObjectOnThis = NULL;
		  }
          
          piRoot->Release();
          piRoot = NULL;

          num = 1;
	   }
	}
  
	// Update
    num = ObjectCCP_SPEC::Update(pAssociationOfObjects,
		                         pAnImposedFormat,
								 pToCurObjects);

    return num;
}
