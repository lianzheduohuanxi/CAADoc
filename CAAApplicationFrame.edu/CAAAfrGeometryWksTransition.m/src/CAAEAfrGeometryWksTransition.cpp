// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEAfrGeometryWksTransition.h"

// C++ Standrad library
#include "iostream.h"

//-----------------------------------------------------------------------------
// To create the TIE object
#include <TIE_CATIWorkbenchTransition.h> 
TIE_CATIWorkbenchTransition(CAAEAfrGeometryWksTransition);

// To declare that the class is a data extension of (the late type) Geometry_trans
//
CATImplementClass(CAAEAfrGeometryWksTransition, 
				  DataExtension, 
				  CATBaseUnknown, 
				  CAAAfrGeometryWks_trans);

// 
// To declare that CAAEAfrGeometryWksTransition implements 
// CATIWorkbenchTransition insert the following line in the interface
// dictionary:
//
//   CAAAfrGeometryWks_trans CATIWorkbenchTransition  libCATAfrEduWSWBTransition
//
//-----------------------------------------------------------------------------

CAAEAfrGeometryWksTransition::CAAEAfrGeometryWksTransition()
{
   cout << "CAAEAfrGeometryWksTransition constructor" << endl;

   // _newDoc is a data member of the CATExtIWorkbenchTransition class 
   // this value is used in the DoTransition method. It's the name of
   // the document to open when you select a workbench of this workshop 

   _newDoc = "CAAGeometry" ;
}

//-----------------------------------------------------------------------------

CAAEAfrGeometryWksTransition::~CAAEAfrGeometryWksTransition()
{
   cout << "CAAEAfrGeometryWksTransition destructor" << endl;
}

//-----------------------------------------------------------------------------

int CAAEAfrGeometryWksTransition::DoTransition( const CATString & fromWS ,
                                                        const CATString & fromWB ,
                                                        const CATString & toWS   ,
                                                        const CATString & toWB    )
{
    cout << "CAAEAfrGeometryWksTransition::DoTransition" << endl ;
    //                      
    //  Method redefined to have cout
    // 
    cout << "Wshop  from:" << fromWS << " To :" << toWS << endl;
    cout << "Wbench from:" << fromWB << " To :" << toWB << endl;

    int rc = CATExtIWorkbenchTransition::DoTransition(fromWS,fromWB,toWS,toWB) ;

    return rc ;
}







