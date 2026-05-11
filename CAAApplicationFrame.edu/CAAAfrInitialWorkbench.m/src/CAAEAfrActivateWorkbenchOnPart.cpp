// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAAEAfrActivateWorkbenchOnPart.h"

// C++ Standrad Library
#include <iostream.h>

//--------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CATIAfrActivateWorkbench.h"              
TIE_CATIAfrActivateWorkbench(CAAEAfrActivateWorkbenchOnPart); 

// To declare that the class is a data extension of MechanicalPart
CATImplementClass (CAAEAfrActivateWorkbenchOnPart,DataExtension, CATBaseUnknown, MechanicalPart);

// 
// To declare that CAAEAfrActivateWorkbenchOnPart implements CATIAfrActivateWorkbench, 
// insert  the following line in the interface dictionary:
//
//    MechanicalPart  CATIAfrActivateWorkbench  libCAAAfrInitialWorkbench
//
//-----------------------------------------------------------------------------

CAAEAfrActivateWorkbenchOnPart::CAAEAfrActivateWorkbenchOnPart()
                            
{
    cout << " construction of CAAEAfrActivateWorkbenchOnPart" << endl ;

    // Part Design workbench
    _WbName = "PrtCfg" ;
}

//------------------------------------------------------------------------------

CAAEAfrActivateWorkbenchOnPart::~CAAEAfrActivateWorkbenchOnPart()
{
    cout << "Destruction of CAAEAfrActivateWorkbenchOnPart" << endl ;
}

//------------------------------------------------------------------------------

CATString & CAAEAfrActivateWorkbenchOnPart::GetInitialWorkbench()
{
    cout << "CAAEAfrActivateWorkbenchOnPart::GetInitialWorkbench " << endl;
 
    return _WbName;
}

//------------------------------------------------------------------------------

