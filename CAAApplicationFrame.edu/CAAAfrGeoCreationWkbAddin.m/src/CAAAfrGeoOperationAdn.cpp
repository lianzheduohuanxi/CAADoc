// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAAfrGeoOperationAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    

// Creates the CAAAfrGeoOperationAdnHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAAfrGeoOperationAdnHeader);  


//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CAAIAfrGeoCreationWkbAddin.h>
TIE_CAAIAfrGeoCreationWkbAddin(CAAAfrGeoOperationAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAAfrGeoOperationAddin
//
CATImplementClass(CAAAfrGeoOperationAdn, DataExtension, CATBaseUnknown, CAAAfrGeoOperationAddin);

// 
// To declare that CAAAfrGeoOperationAddin implements CAAIAfrGeoCreationWkbAddin, insert 
// the following line in the interface dictionary:
//
//   CAAAfrGeoOperationAddin  CAAIAfrGeoCreationWkbAddin libCAAAfrGeoCreationWkbAddin
//
//---------------------------------------------------------------------------


CAAAfrGeoOperationAdn::CAAAfrGeoOperationAdn()
{}

CAAAfrGeoOperationAdn::~CAAAfrGeoOperationAdn()
{}

void CAAAfrGeoOperationAdn::CreateCommands()
{
   //---------------------------------------------------------------------------
   // Instantiation of the header class created by the macro MacDeclareHeader -
   // commands are always available and are represented by a push button
   //---------------------------------------------------------------------------

   new CAAAfrGeoOperationAdnHeader("CAAAfrUnionHdr"    ,"CommandLib","CommandName",(void *)NULL);
   new CAAAfrGeoOperationAdnHeader("CAAAfrSubstractHdr","CommandLib","CommandName",(void *)NULL);
   new CAAAfrGeoOperationAdnHeader("CAAAfrFilletHdr"   ,"CommandLib","CommandName",(void *)NULL);
}

CATCmdContainer * CAAAfrGeoOperationAdn::CreateToolbars()
{
   // --------------------------
   // CAAAfrOperationTlb Toolbar
   // --------------------------- 
   NewAccess(CATCmdContainer,pCAAAfrOperationTlb,CAAAfrOperationTlb);

      NewAccess(CATCmdStarter,pCAAAfrTUnionStr,CAAAfrTUnionStr);
      SetAccessCommand(pCAAAfrTUnionStr,"CAAAfrUnionHdr");
      SetAccessChild(pCAAAfrOperationTlb,pCAAAfrTUnionStr);

      NewAccess(CATCmdStarter,pCAAAfrTSubstractStr,CAAAfrTSubstractStr);
      SetAccessCommand(pCAAAfrTSubstractStr,"CAAAfrSubstractHdr");
      SetAccessNext(pCAAAfrTUnionStr,pCAAAfrTSubstractStr);

      NewAccess(CATCmdStarter,pCAAAfrTFilletStr,CAAAfrTFilletStr);
      SetAccessCommand(pCAAAfrTFilletStr,"CAAAfrFilletHdr");
      SetAccessNext(pCAAAfrTSubstractStr,pCAAAfrTFilletStr);

    //----------------------
    //  Menubar 
    //----------------------
	NewAccess(CATCmdContainer,pCAAAfrOperationMbr,CAAAfrOperationMbr);

       //  menu Tools with three new command
       //------------------------------------------------------
       NewAccess(CATCmdContainer,pCAAAfrOperationToolsMnu,CATAfrToolsMnu);
       SetAccessChild(pCAAAfrOperationMbr,pCAAAfrOperationToolsMnu);

         NewAccess(CATCmdSeparator,pCAAAfrOperationToolsSep,CAAAfrOperationToolsSep);
         SetAccessChild(pCAAAfrOperationToolsMnu,pCAAAfrOperationToolsSep);

         NewAccess(CATCmdStarter,pCAAAfrMUnionStr,CAAAfrMUnionStr);
         SetAccessCommand(pCAAAfrMUnionStr,"CAAAfrUnionHdr");
         SetAccessNext(pCAAAfrOperationToolsSep,pCAAAfrMUnionStr);

         NewAccess(CATCmdStarter,pCAAAfrMSubstractStr,CAAAfrMSubstractStr);
         SetAccessCommand(pCAAAfrMSubstractStr,"CAAAfrSubstractHdr");
         SetAccessNext(pCAAAfrMUnionStr,pCAAAfrMSubstractStr);

         NewAccess(CATCmdStarter,pCAAAfrMFilletStr,pCAAAfrMFilletStr);
         SetAccessCommand(pCAAAfrMFilletStr,"CAAAfrFilletHdr");
         SetAccessNext(pCAAAfrMSubstractStr,pCAAAfrMFilletStr);

    // Set the menu 
    // pCAAAfrOperationTlb: Always the toolbar returned by the method
    // pCAAAfrOperationMbr: The container which contains all the menu's containers 
    //
    SetAddinMenu(pCAAAfrOperationTlb,pCAAAfrOperationMbr);

   // Invisible toolbar 
   AddToolbarView(pCAAAfrOperationTlb,-1,Right); 
		 
   // Pointer of the first toolbar created
   return pCAAAfrOperationTlb;
}

