// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAMcaUdfAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    

// Creates the CAAMcaUdfLoftCreateHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAMcaUdfLoftCreateHeader);  

// C++ Standard Library
#include <iostream.h>

//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIShapeDesignWorkshopAddin.h>
TIE_CATIShapeDesignWorkshopAddin(CAAMcaUdfAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAMcaUdfAddin
//
CATImplementClass(CAAMcaUdfAdn, DataExtension, CATBaseUnknown, CAAMcaUdfAddin);

// 
// To declare that CAAMcaUdfAddin implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary:
//
//   CAAMcaUdfAddin  CATIShapeDesignWorkshopAddin libCAAMcaUdfAddin
//
//---------------------------------------------------------------------------


CAAMcaUdfAdn::CAAMcaUdfAdn()
{
   cout << "CAAMcaUdfAdn::CAAMcaUdfAdn()" << endl;
}

//---------------------------------------------------------------------------

CAAMcaUdfAdn::~CAAMcaUdfAdn()
{
   cout << "CAAMcaUdfAdn::~CAAMcaUdfAdn()" << endl;
}

//---------------------------------------------------------------------------

void CAAMcaUdfAdn::CreateCommands()
{
   //---------------------------------------------------------------------------
   // Instantiation of the header class created by the macro MacDeclareHeader -
   // commands are always available and are represented by a push button
   //---------------------------------------------------------------------------

   new CAAMcaUdfLoftCreateHeader("CAAMcaUdfLoftCreateHdr",
                                 "CAAMcaUdfEdit",
                                 "CAAMcaUdfLoftEditCreateCmd",               
                                 (void*) NULL);

}

//---------------------------------------------------------------------------

CATCmdContainer * CAAMcaUdfAdn::CreateToolbars()
{
    //----------------------
    //  SDO Toolbar
    //----------------------
    NewAccess(CATCmdContainer,pCAAMcaUdfTlb,CAAMcaUdfTlb);

        NewAccess(CATCmdStarter,pCAAMcaUdfLoftStr,CAAMcaUdfLoftStr);
        SetAccessCommand(pCAAMcaUdfLoftStr,"CAAMcaUdfLoftCreateHdr");
        SetAccessChild(pCAAMcaUdfTlb,pCAAMcaUdfLoftStr);

    // Visible toolbar set in the bottom side of the application window
    AddToolbarView(pCAAMcaUdfTlb,1,Bottom);

		 
    // Pointer of the first toolbar created
    return  pCAAMcaUdfTlb ;
}

