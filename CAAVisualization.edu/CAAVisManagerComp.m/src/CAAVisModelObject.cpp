// COPYRIGHT DASSAULT SYSTEMES 1999

//Local FrameWork
#include "CAAVisModelObject.h"

// Standard Library
#include <iostream.h>

//-----------------------------------------------------------------------------
// To declare that the class is a component main class 
//

CATImplementClass(CAAVisModelObject,Implementation,CATBaseUnknown,NULL);

//
//----------------------------------------------------------------------------

CAAVisModelObject::CAAVisModelObject()
{
   cout <<"CAAVisModelObject::CAAVisModelObject()"<< endl; 
}

//----------------------------------------------------------------------------

CAAVisModelObject::~CAAVisModelObject()
{
  cout <<"CAAVisModelObject::~CAAVisModelObject()"<< endl; 
}

