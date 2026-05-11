// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVisModelCGRObject.h"

// Standard C++ library
#include <iostream.h>


//----------------------------------------------------------------------------

// To declare that the class is a component main class which OM derives from
// the CAAVisModelObject component.
CATImplementClass(CAAVisModelCGRObject,Implementation,CAAVisModelObject,NULL);

//----------------------------------------------------------------------------

CAAVisModelCGRObject::CAAVisModelCGRObject()                         
{
   cout << "CAAVisModelCGRObject::CAAVisModelCGRObject"<< endl;
}

//----------------------------------------------------------------------------

CAAVisModelCGRObject::~CAAVisModelCGRObject()
{
   cout << "CAAVisModelCGRObject::~CAAVisModelCGRObject"<< endl;
}

//----------------------------------------------------------------------------

