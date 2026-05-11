// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysSampCont.h"

// C++ standard library
#include "iostream.h"

//----------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysSampCont,Implementation,CATBaseUnknown,CATNull);
 
//-----------------------------------------------------------------------


CAASysSampCont::CAASysSampCont()
{
  cout << "CAASysSampCont::CAASysSampCont" << endl;
}

CAASysSampCont::~CAASysSampCont()
{
  cout << "CAASysSampCont::~CAASysSampCont" << endl;
}

