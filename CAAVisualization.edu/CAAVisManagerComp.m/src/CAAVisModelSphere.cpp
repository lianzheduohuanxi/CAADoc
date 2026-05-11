// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVisModelSphere.h"
#include "CAAIVisModelObject.h"   

// System Framework
#include "CATErrorDef.h" // for the SUCCEDED macro

// Standard C++ library
#include <iostream.h>

//----------------------------------------------------------------------------

// To declare that the class is a component main class which OM derives from
// the CAAVisModelObject component.
CATImplementClass(CAAVisModelSphere,Implementation,CAAVisModelObject,NULL);

//----------------------------------------------------------------------------

CAAVisModelSphere::CAAVisModelSphere ()
{
   cout << "CAAVisModelSphere::CAAVisModelSphere"<< endl;

   CAAIVisModelObject *pICAAIVisOnSphere = NULL ;
   HRESULT rc = QueryInterface(IID_CAAIVisModelObject, (void**)&pICAAIVisOnSphere);
   if (SUCCEEDED(rc))
   {
        pICAAIVisOnSphere->SetType("Sphere");

        pICAAIVisOnSphere->Release();
        pICAAIVisOnSphere = NULL ;
   }
}

//----------------------------------------------------------------------------

CAAVisModelSphere::~CAAVisModelSphere ()
{
   cout << "CAAVisModelSphere::~CAAVisModelSphere"<< endl;
}

