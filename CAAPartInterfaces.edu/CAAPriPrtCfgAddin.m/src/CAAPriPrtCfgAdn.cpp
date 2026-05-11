// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAPriPrtCfgAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    

// Creates the CAAPriPrtCfgHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAPriPrtCfgHeader);  


//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIPrtCfgAddin.h>
TIE_CATIPrtCfgAddin(CAAPriPrtCfgAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAPriPrtCfgAddin
//
CATImplementClass(CAAPriPrtCfgAdn, DataExtension, CATBaseUnknown, CAAPriPrtCfgAddin);

// 
// To declare that CAAPriPrtCfgAddin implements CATIPrtCfgAddin, insert 
// the following line in the interface dictionary:
//
//   CAAPriPrtCfgAddin  CATIPrtCfgAddin libCAAPriPrtCfgAddin
//
//---------------------------------------------------------------------------


CAAPriPrtCfgAdn::CAAPriPrtCfgAdn()
{}

CAAPriPrtCfgAdn::~CAAPriPrtCfgAdn()
{}

void CAAPriPrtCfgAdn::CreateCommands()
{
   //---------------------------------------------------------------------------
   // Instantiation of the header class created by the macro MacDeclareHeader -
   // commands are always available and are represented by a push button
   //---------------------------------------------------------------------------

   new CAAPriPrtCfgHeader("CAAPriEditSketchHdr",
                          "CAAPriCommands",
                          "CAAPriEditSketchCmd",
                              (void *)NULL);
}

CATCmdContainer * CAAPriPrtCfgAdn::CreateToolbars()
{
   // --------------------------
   // CAAPriCfgFrameTlb Toolbar
   // --------------------------- 
   NewAccess(CATCmdContainer,pCAAPriCfgFrameTlb,CAAPriCfgFrameTlb);

      NewAccess(CATCmdStarter,pCAAPriTEditSketchStr,CAAPriTEditSketchStr);
      SetAccessCommand(pCAAPriTEditSketchStr,"CAAPriEditSketchHdr");
      SetAccessChild(pCAAPriCfgFrameTlb,pCAAPriTEditSketchStr);

   //----------------------
    //  Menubar 
    //----------------------
	NewAccess(CATCmdContainer,pCAAPriCfgFrameMbr,pCAAPriCfgFrameMbr);

        //  menu Tools with the new command
       //------------------------------------------------------
       NewAccess(CATCmdContainer,pCAAPriPrtCfgToolsMnu,CATAfrToolsMnu);
       SetAccessChild(pCAAPriCfgFrameMbr,pCAAPriPrtCfgToolsMnu);

         NewAccess(CATCmdSeparator,pCAAPriPrtCfgToolsSep,CAAPriPrtCfgToolsSep);
         SetAccessChild(pCAAPriPrtCfgToolsMnu,pCAAPriPrtCfgToolsSep);

         NewAccess(CATCmdStarter,pCAAPriMEditSketchStr,CAAPriMEditSketchStr);
         SetAccessCommand(pCAAPriMEditSketchStr,"CAAPriEditSketchHdr");
         SetAccessNext(pCAAPriPrtCfgToolsSep,pCAAPriMEditSketchStr);

    // Set the menu 
    // pCAAPriCfgFrameTlb: Always the toolbar returned by the method
    // pCAAPriCfgFrameMbr: The container which contains all the menu's containers 
    //
    SetAddinMenu(pCAAPriCfgFrameTlb,pCAAPriCfgFrameMbr);

   // visible toolbar 
   AddToolbarView(pCAAPriCfgFrameTlb,1,Right); 
		 
   // Pointer of the first toolbar created
   return pCAAPriCfgFrameTlb;
}

