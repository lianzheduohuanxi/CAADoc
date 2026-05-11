// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAVisWireBox.h"

// C++ Standard library
#include "iostream.h"


//----------------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAAVisWireBox,Implementation,CATBaseUnknown,CATNull);

//----------------------------------------------------------------------------

CAAVisWireBox::CAAVisWireBox()
{
  cout << "CAAVisWireBox::CAAVisWireBox" << endl;
}

CAAVisWireBox::~CAAVisWireBox()
{
  cout << "CAAVisWireBox::~CAAVisWireBox" << endl;
}

