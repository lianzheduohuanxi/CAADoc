// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Freamework
#include "CAASysSampRootObj.h"

// C++ Standard library
#include "iostream.h"

//-----------------------------------------------------------------------------
// To declare that the class is a component main class 
//
CATImplementClass(CAASysSampRootObj,Implementation,CATBaseUnknown,CATNull);

CAASysSampRootObj::CAASysSampRootObj()
{
  cout << "CAASysSampRootObj::CAASysSampRootObj" << endl;
}

CAASysSampRootObj::~CAASysSampRootObj()
{
  cout << "CAASysSampRootObj::~CAASysSampRootObj" << endl;
}
