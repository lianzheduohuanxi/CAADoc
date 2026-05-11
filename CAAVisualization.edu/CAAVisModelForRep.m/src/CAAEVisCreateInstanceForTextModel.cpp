// COPYRIGHT DASSAULT SYSTEMES  2003

// Local framework
#include "CAAEVisCreateInstanceForTextModel.h"
#include "CAAVisTextModel.h"

// System framework
#include <CATErrorDef.h>

// Standard library
#include <iostream.h>

//-----------------------------------------------------------------------------

// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAEVisCreateInstanceForTextModel);

// To declare that the class is a Code extension of CAAVisTextModel
//
CATImplementClass(CAAEVisCreateInstanceForTextModel, CodeExtension, CATBaseUnknown, CAAVisTextModel);
// 
// To declare that CAAEVisCreateInstanceForTextModel implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAAVisTextModel CATICreateInstance  libCAAVisModelForRep
//
//-----------------------------------------------------------------------------

CAAEVisCreateInstanceForTextModel::CAAEVisCreateInstanceForTextModel()  
{
   cout <<"CAAEVisCreateInstanceForTextModel creation" << endl;
}

CAAEVisCreateInstanceForTextModel::~CAAEVisCreateInstanceForTextModel() 
{
   cout <<"CAAEVisCreateInstanceForTextModel destruction" << endl;
}

//-----------------------------------------------------------------------------

HRESULT __stdcall CAAEVisCreateInstanceForTextModel::CreateInstance(void ** oppv)
{
   cout<<" CAAEVisCreateInstanceForTextModel::CreateInstance" << endl;

   CAAVisTextModel * pt = new CAAVisTextModel();
   if (NULL == pt) return(E_OUTOFMEMORY);
   *oppv = (void *)pt;
   return(S_OK);
}


