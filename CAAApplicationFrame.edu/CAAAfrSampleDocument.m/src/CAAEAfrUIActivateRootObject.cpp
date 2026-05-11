// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEAfrUIActivateRootObject.h"  

// C++ Standard library 
#include <iostream.h>

//----------------------------------------------------------------------------
// to create the TIE Object
#include "TIE_CATIUIActivate.h"              
TIE_CATIUIActivate(CAAEAfrUIActivateRootObject); 

// this class is a data extension of CAASysSampRootObj. 

CATImplementClass (CAAEAfrUIActivateRootObject,DataExtension, CATBaseUnknown, CAASysSampRootObj);

// 
// To declare that CAAEAfrUIActivateRootObject implements CATIUIActivate, insert 
// the following line in the interface dictionary:
//
//    CAASysSampRootObj CATIUIActivate  libCAAAfrSampleDocument
//
//-----------------------------------------------------------------------------


CAAEAfrUIActivateRootObject::CAAEAfrUIActivateRootObject(): CATExtIUIActivate(), 
                 _WorkshopName("CAAAfrGeometryWks"),
                 _DefaultCommandName("CATAfrSelectHdr")
{
	cout << " construction of CAAEAfrUIActivateRootObject" << endl ;
	// This constructor should not be explicitly called.

    // The default command, CATAfrSelectHdr, is a command of the General Workshop
    // defined in the ApplicationFrame Framework

    // The workshop to lauch is CAAAfrGeometryWks, it's defined in the 
    // local CAAAfrGeometryWshop.m module 
}

//----------------------------------------------------------------------------

CAAEAfrUIActivateRootObject::~CAAEAfrUIActivateRootObject()
{
	cout << "Destruction of CAAEAfrUIActivateRootObject" << endl ;
	// This destructor should not be explicitly called.
}

//----------------------------------------------------------------------------

CATString & CAAEAfrUIActivateRootObject::GetWorkshop()
{
	cout << " CAAEAfrUIActivateRootObject::GetWorkshop " << endl ;

	return  _WorkshopName ;
}

//----------------------------------------------------------------------------
CATString & CAAEAfrUIActivateRootObject::GetDefaultCommand()
{
	cout << " CAAEAfrUIActivateRootObject::GetDefaultCommand " << endl ;

	return  _DefaultCommandName ;
}
//----------------------------------------------------------------------------
