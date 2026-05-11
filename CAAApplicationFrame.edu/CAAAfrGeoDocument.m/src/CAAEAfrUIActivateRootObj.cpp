// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEAfrUIActivateRootObj.h"

// C++ Standrad Library
#include <iostream.h>

//--------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CATIUIActivate.h"              
TIE_CATIUIActivate(CAAEAfrUIActivateRootObj); 

// To declare that the class is a data extension oof CAASysGeomRootObj. 
CATImplementClass (CAAEAfrUIActivateRootObj,DataExtension, CATBaseUnknown, CAASysGeomRootObj);

// 
// To declare that CAAEAfrUIActivateRootObj implements CATIUIActivate, insert 
// the following line in the interface dictionary:
//
//    CAASysGeomRootObj  CATIUIActivate  libCAAAfrGeoDocument
//
//-----------------------------------------------------------------------------

CAAEAfrUIActivateRootObj::CAAEAfrUIActivateRootObj(): 
                   CATExtIUIActivate(),
                   _WorkshopName("CAAAfrGeometryWks"),
				   _DefaultCommandName("CATAfrSelectHdr")
                            
{
    cout << " construction of CAAEAfrUIActivateRootObj" << endl ;
    // The default command, CATAfrSelectHdr, is a command of the General Workshop
    // defined in the ApplicationFrame Framework

    // The workshop to lauch is CAAAfrGeometryWks, it's defined in the 
    // local CAAAfrGeometryWshop.m module 
}

//------------------------------------------------------------------------------

CAAEAfrUIActivateRootObj::~CAAEAfrUIActivateRootObj()
{
    cout << "Destruction of CAAEAfrUIActivateRootObj" << endl ;
}

//------------------------------------------------------------------------------

CATString & CAAEAfrUIActivateRootObj::GetWorkshop()
{
    cout << "CAAEAfrUIActivateRootObj::GetWorkshop " << endl;
   
    return (_WorkshopName) ;

}

//------------------------------------------------------------------------------

CATString & CAAEAfrUIActivateRootObj::GetDefaultCommand()
{
   cout << "CAAEAfrUIActivateRootObj::GetDefaultCommand " << endl;

   return (_DefaultCommandName) ;

}

//------------------------------------------------------------------------------





