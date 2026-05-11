// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVisModelSetOfObject.h"

// Visualization Framework
#include "CATMathPointf.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVisModelSetOfObject.h"
TIE_CAAIVisModelSetOfObject(CAAEVisModelSetOfObject);

// To declare that the class is a data extension of CAAVisModelSetOfObject
//
CATImplementClass(CAAEVisModelSetOfObject,DataExtension,CATBaseUnknown,CAAVisModelSetOfObject);

// 
// To declare that CAAEVisModelSetOfObject implements CAAIVisModelSetOfObject, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelSetOfObject CAAIVisModelSetOfObject  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVisModelSetOfObject::CAAEVisModelSetOfObject()
{
  cout << "CAAEVisModelSetOfObject::CAAEVisModelSetOfObject" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVisModelSetOfObject::~CAAEVisModelSetOfObject()
{
  cout << "CAAEVisModelSetOfObject::~CAAEVisModelSetOfObject" << endl;
}

