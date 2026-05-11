// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAECafRootProperties.h"

// System Framework
#include "CATString.h"

// other
#include <iostream.h>


//------------------------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CATIRootProperties.h"
TIE_CATIRootProperties(CAAECafRootProperties);

// To declare that the class is a data extension of CAASysGeomRootObj 
//
CATImplementClass(CAAECafRootProperties, DataExtension, CATBaseUnknown, CAASysGeomRootObj);

// 
// To declare that CAAECafRootProperties implements CATIRootProperties, insert 
// this following line in the interface dictionary:
//
//    CAASysGeomRootObj CATIRootProperties  libCATCafRootProperties
//
//------------------------------------------------------------------------------------------
CAAECafRootProperties::CAAECafRootProperties()
{
   cout << " CAAECafRootProperties constructor"<< endl;
}

//------------------------------------------------------------------------------------------
CAAECafRootProperties::~CAAECafRootProperties()
{
   cout << " CAAECafRootProperties destructor"<< endl;
}
//------------------------------------------------------------------------------------------
CATListOfCATString CAAECafRootProperties::GetListOfEditors () 
{
    cout << " CAAECafRootProperties GetListOfEditors"<< endl;

    CATListOfCATString ListOfEditor ;

    ListOfEditor.Append(CATString("CAACafTexturePropertyPageEdt"));
    ListOfEditor.Append(CATString("CAACafColorPropertyPageEdt"));

    return (ListOfEditor);
}
//------------------------------------------------------------------------------------------
void CAAECafRootProperties::GetAssociatedObject() 
{
   cout << " CAAECafRootProperties GetAssociatedObject"<< endl;
}

