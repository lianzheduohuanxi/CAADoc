// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVisModelEventsForObject.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATIModelEvents.h"
TIE_CATIModelEvents(CAAEVisModelEventsForObject);

// To declare that the class is a data extension of CAAVisModelObject
//
CATImplementClass(CAAEVisModelEventsForObject,DataExtension,CATBaseUnknown,CAAVisModelObject);


// 
// To declare that CAAEVisModelEventsForObject implements CATIModelEvents, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelObject CATIModelEvents  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVisModelEventsForObject::CAAEVisModelEventsForObject()
{
  cout << "CAAEVisModelEventsForObject::CAAEVisModelEventsForObject" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVisModelEventsForObject::~CAAEVisModelEventsForObject()
{
  cout << "CAAEVisModelEventsForObject::~CAAEVisModelEventsForObject" << endl;
}

//--------------------------------------------------------------------------------------------
