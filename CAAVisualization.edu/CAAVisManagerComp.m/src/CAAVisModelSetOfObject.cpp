// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVisModelSetOfObject.h"
#include "CAAIVisModelObject.h"

// system Framework
#include "CATErrorDef.h" 

// Standard C++ library
#include <iostream.h>

//----------------------------------------------------------------------------

// To declare that the class is a component main class which OM derives from
// the CAAVisModelObject component.
CATImplementClass(CAAVisModelSetOfObject,Implementation,CAAVisModelObject,NULL);

//----------------------------------------------------------------------------

CAAVisModelSetOfObject::CAAVisModelSetOfObject()
{
   cout << " CAAVisModelSetOfObject::CAAVisModelSetOfObject" << endl;

   CAAIVisModelObject *pICAAIVisModelObject = NULL ;
   HRESULT rc = QueryInterface(IID_CAAIVisModelObject, (void**)&pICAAIVisModelObject);
   if (SUCCEEDED(rc))
   {
        pICAAIVisModelObject->SetType("Set");

        pICAAIVisModelObject->Release();
        pICAAIVisModelObject = NULL ;
   }
   
}

//----------------------------------------------------------------------------

CAAVisModelSetOfObject::~CAAVisModelSetOfObject()
{
   cout << " CAAVisModelSetOfObject::~CAAVisModelSetOfObject" << endl;
}



