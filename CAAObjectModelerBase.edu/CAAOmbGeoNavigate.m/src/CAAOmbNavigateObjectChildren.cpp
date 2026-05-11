// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAOmbNavigateObjectChildren.h"

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"   // contains the CATListValCATBaseUnknown_var class def

// System Framework
#include "CATListOfCATUnicodeString.h" // contains the CATListValCATUnicodeString class definition

// CAASystem.edu Framework
#include "CAAISysName.h"               // To retrieve the name of the component

// System Framework
#include "CATUnicodeString.h"

// C++ Standard Library
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject(CAAOmbNavigateObjectChildren);

// Declares that the class is a data extension of children objects: 
//
CATBeginImplementClass(CAAOmbNavigateObjectChildren, DataExtension, CATBaseUnknown, CAASysPoint);
CATAddClassExtension(CAASysLine);
CATAddClassExtension(CAASysEllipse);
CATAddClassExtension(CAASysPlane);
CATAddClassExtension(CAASysCircle);
CATAddClassExtension(CAASysPolyline);
CATAddClassExtension(CAASysCuboid);
CATAddClassExtension(CAASysCylinder);
CATEndImplementClass(CAAOmbNavigateObjectChildren); 

// 
// To declare that CAAOmbNavigateObjectChildren implements the CATINavigateObject 
// interface, insert these following lines in the interface dictionary:
//
//    CAASysPoint        CATINavigateObject  libCAAOmbGeoNavigate
//    CAASysLine         CATINavigateObject  libCAAOmbGeoNavigate
//    ...
//
//---------------------------------------------------------------------------------------------

CAAOmbNavigateObjectChildren::CAAOmbNavigateObjectChildren()
{
  cout << "CAAOmbNavigateObjectChildren::CAAOmbNavigateObjectChildren" << endl;
}

//---------------------------------------------------------------------------------------------

CAAOmbNavigateObjectChildren::~CAAOmbNavigateObjectChildren()
{
  cout <<"CAAOmbNavigateObjectChildren::~CAAOmbNavigateObjectChildren" << endl;
}

//---------------------------------------------------------------------------------------------

CATListValCATUnicodeString * CAAOmbNavigateObjectChildren::GetIdentificators()
{
  cout << "CAAOmbNavigateObjectChildren::GetIdentificators" << endl;

  CATListOfCATUnicodeString *pIdent = new CATListOfCATUnicodeString;
  
  // The String displayed in the graph 
  CATUnicodeString Name = "Children" ;

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

CATListValCATBaseUnknown_var * CAAOmbNavigateObjectChildren::GetChildren()
{
  cout << "CAAOmbNavigateObjectChildren::GetChildren" << endl;

  return NULL;
  
}
//---------------------------------------------------------------------------------------------
