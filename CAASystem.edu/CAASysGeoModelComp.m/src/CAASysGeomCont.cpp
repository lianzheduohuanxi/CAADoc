// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysGeomCont.h"

//others
#include "iostream.h"

//--------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysGeomCont,Implementation,CATBaseUnknown,CATNull);


//--------------------------------------------------------------------

CAASysGeomCont::CAASysGeomCont()
{
  cout << "CAASysGeomCont::CAASysGeomCont" << endl;
}

//--------------------------------------------------------------------

CAASysGeomCont::~CAASysGeomCont()
{
  cout << "CAASysGeomCont::~CAASysGeomCont" << endl;
}


