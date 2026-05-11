// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVisModelCuboid.h"
#include "CAAIVisModelObject.h"

// System Framework
#include "CATErrorDef.h"

// C++ Standard Library
#include <iostream.h>

//----------------------------------------------------------------------------

// To declare that the class is a component main class which OM derives from
// the CAAVisModelObject component.
CATImplementClass(CAAVisModelCuboid,Implementation,CAAVisModelObject,NULL);

//
//----------------------------------------------------------------------------

CAAVisModelCuboid::CAAVisModelCuboid()
{
   cout << "CAAVisModelCuboid::CAAVisModelCuboid"<< endl;

   CAAIVisModelObject *pICAAIVisModelObject = NULL ;
   HRESULT rc = QueryInterface(IID_CAAIVisModelObject, (void**)&pICAAIVisModelObject);
   if (SUCCEEDED(rc))
   {
        pICAAIVisModelObject->SetType("Cuboid");

        pICAAIVisModelObject->Release();
        pICAAIVisModelObject = NULL ;
   }
}

//----------------------------------------------------------------------------

CAAVisModelCuboid::~CAAVisModelCuboid()
{
   cout << "CAAVisModelCuboid::~CAAVisModelCuboid"<< endl;
}

//----------------------------------------------------------------------------
