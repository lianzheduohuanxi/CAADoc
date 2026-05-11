// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADegGeoSDOAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    
#include "CATIAfrDialogForAgent.h"

// DialogEngine Framework
#include "CATCommandHeaderWithSDOForAgent.h"

// C++ Standard Library
#include <iostream.h>

//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CAAIAfrGeoCreationWkbAddin.h>
TIE_CAAIAfrGeoCreationWkbAddin(CAADegGeoSDOAdn);

// To declare that the class 
// is a DataExtension of (late type) CAADegGeoAddin
//
CATImplementClass(CAADegGeoSDOAdn, DataExtension, CATBaseUnknown, CAADegGeoSDOAddin);

// 
// To declare that CAADegGeoSDOAddin implements CAAIAfrGeoCreationWkbAddin, insert 
// the following line in the interface dictionary:
//
//   CAADegGeoSDOAddin  CAAIAfrGeoCreationWkbAddin libCAADegSDOAddin
//
//---------------------------------------------------------------------------


CAADegGeoSDOAdn::CAADegGeoSDOAdn()
{
   cout << "CAADegGeoSDOAdn::CAADegGeoSDOAdn()" << endl;
}

//---------------------------------------------------------------------------

CAADegGeoSDOAdn::~CAADegGeoSDOAdn()
{
   cout << "CAADegGeoSDOAdn::~CAADegGeoSDOAdn()" << endl;
}

//---------------------------------------------------------------------------

void CAADegGeoSDOAdn::CreateCommands()
{
   //---------------------------------------------------------------------------
   // Instantiation of the header class created by the macro MacDeclareHeader -
   // commands are always available and are represented by a push button
   //---------------------------------------------------------------------------

   new CATCommandHeaderWithSDOForAgent("CAADegSDOHdr",IID_CATIAfrDialogForAgent);
}

//---------------------------------------------------------------------------

CATCmdContainer * CAADegGeoSDOAdn::CreateToolbars()
{
    //----------------------
    //  SDO Toolbar
    //----------------------
    NewAccess(CATCmdContainer,pCAADegSDOTlb,CAADegSDOTlb);

        NewAccess(CATCmdSeparator,pCAADegFirstSep,CAADegFirstSep);
        SetAccessChild(pCAADegSDOTlb,pCAADegFirstSep);

        NewAccess(CATCmdStarter,pCAADegSDOStr,CAADegSDOStr);
        SetAccessCommand(pCAADegSDOStr,"CAADegSDOHdr");
        SetAccessNext(pCAADegFirstSep,pCAADegSDOStr);

    // Visible toolbar set in the bottom side of the application window
    AddToolbarView(pCAADegSDOTlb,1,Bottom);

		 
    // Pointer of the first toolbar created
    return  pCAADegSDOTlb ;
}

