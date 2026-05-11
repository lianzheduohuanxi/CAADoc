// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include <CAAAfrGeoCreationWkb.h>

// Creates the CAAAfrGeoCreationWkbHeader command header class
#include <CATCommandHeader.h>
MacDeclareHeader(CAAAfrGeoCreationWkbHeader) ;

// ApplicationFrame Framework
#include <CATCreateWorkshop.h>    // To use NewAccess .... macros

// C++ standard Library
#include "iostream.h"

//---------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATICAAAfrGeometryWksConfiguration.h> 
TIE_CATICAAAfrGeometryWksConfiguration(CAAAfrGeoCreationWkb);

// To declare that the class is an implementation
//
CATImplementClass(CAAAfrGeoCreationWkb, Implementation, CATBaseUnknown, CATNull);

// 
// To declare that CAAAfrGeoCreationWkb implements CATICAAAfrGeometryWksConfiguration ,
//  insert the following line in the interface dictionary:
// 
//
//  CAAAfrGeoCreationWkb CATICAAAfrGeometryWksConfiguration   libCAAAfrGeoCreationWbench
//
//-------------------------------------------------------------------------

CAAAfrGeoCreationWkb::CAAAfrGeoCreationWkb()
{
   cout << " construction CAAAfrGeoCreationWkb " << endl;
}
CAAAfrGeoCreationWkb::~CAAAfrGeoCreationWkb()
{
   cout << " Destruction CAAAfrGeoCreationWkb " << endl;
}

void CAAAfrGeoCreationWkb::CreateCommands()
{
   cout << "CreateCommands CAAAfrGeoCreationWkb" << endl ;
    
   //---------------------------------------------------------------------
   // Instantiation of the headers created by the macro MacDeclareHeader.
   // Commands are always available and are represented by a push button
   //----------------------------------------------------------------------

   new CAAAfrGeoCreationWkbHeader("CAAAfrCuboidHdr"    ,"CAADegGeoCommands","CAADegCreateBoxCmd",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrSphereHdr"    ,"CommandLib","CommandName",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrTorusHdr"     ,"CommandLib","CommandName",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrCylinder1Hdr"  ,"CAADegGeoCommands","CAADegCreateCylinder1Cmd",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrCylinder2Hdr"  ,"CAADegGeoCommands","CAADegCreateCylinder2Cmd",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrNurbsSurfHdr" ,"CommandLib","CommandName",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrRevolSurfHdr" ,"CommandLib","CommandName",(void *)NULL);
   new CAAAfrGeoCreationWkbHeader("CAAAfrOffsetSurfHdr","CommandLib","CommandName",(void *)NULL);

}

CATCmdWorkbench * CAAAfrGeoCreationWkb::CreateWorkbench()      
{
   cout << "CreateWorkshop CAAAfrGeoCreationWkb" << endl ;

   //---------------------------------------------------------
   // Definition of the CAAAfrGeoCreationWkb workbench Layout
   //---------------------------------------------------------
   NewAccess(CATCmdWorkbench,pCAAAfrGeoCreationWkb,CAAAfrGeoCreationWkb);
      
      //------------------
      //  Solid Toolbar 
      //------------------
      NewAccess(CATCmdContainer,pCAAAfrSolidEltTlb,CAAAfrSolidEltTlb);
      SetAccessChild(pCAAAfrGeoCreationWkb, pCAAAfrSolidEltTlb);

         NewAccess(CATCmdStarter,pCAAAfrTSolidEltCuboidStr,CAAAfrTSolidEltCuboidStr);
         SetAccessCommand(pCAAAfrTSolidEltCuboidStr,"CAAAfrCuboidHdr");
         SetAccessChild(pCAAAfrSolidEltTlb,pCAAAfrTSolidEltCuboidStr);

         NewAccess(CATCmdStarter,pCAAAfrTSolidEltSphereStr,CAAAfrTSolidEltSphereStr);
         SetAccessCommand(pCAAAfrTSolidEltSphereStr,"CAAAfrSphereHdr");
         SetAccessNext(pCAAAfrTSolidEltCuboidStr,pCAAAfrTSolidEltSphereStr);

         NewAccess(CATCmdStarter,pCAAAfrTSolidEltTorusStr,CAAAfrTSolidEltTorusStr);
         SetAccessCommand(pCAAAfrTSolidEltTorusStr,"CAAAfrTorusHdr");
         SetAccessNext(pCAAAfrTSolidEltSphereStr,pCAAAfrTSolidEltTorusStr);

         NewAccess(CATCmdStarter,pCAAAfrTSolidEltCylinder1Str,CAAAfrTSolidEltCylinder1Str);
         SetAccessCommand(pCAAAfrTSolidEltCylinder1Str,"CAAAfrCylinder1Hdr");
         SetAccessNext(pCAAAfrTSolidEltTorusStr,pCAAAfrTSolidEltCylinder1Str);
         
		 NewAccess(CATCmdStarter,pCAAAfrTSolidEltCylinder2Str,CAAAfrTSolidEltCylinder2Str);
         SetAccessCommand(pCAAAfrTSolidEltCylinder2Str,"CAAAfrCylinder2Hdr");
         SetAccessNext(pCAAAfrTSolidEltCylinder1Str,pCAAAfrTSolidEltCylinder2Str);

      // Visible toolbar set in the Right side of the application window
      AddToolbarView(pCAAAfrSolidEltTlb,1,Right);

      
      //  Surfacic Toolbar 
      //----------------------
      NewAccess(CATCmdContainer,pCAAAfrSurfacicEltTlb,CAAAfrSurfacicEltTlb);
      SetAccessNext(pCAAAfrSolidEltTlb,pCAAAfrSurfacicEltTlb);

         NewAccess(CATCmdStarter,pCAAAfrTSurfRevolStr,CAAAfrTSurfRevolStr);
         SetAccessCommand(pCAAAfrTSurfRevolStr,"CAAAfrRevolSurfHdr");
         SetAccessChild(pCAAAfrSurfacicEltTlb,pCAAAfrTSurfRevolStr);

         NewAccess(CATCmdStarter,pCAAAfrTSurfNurbsStr,CAAAfrTSurfNurbsStr);
         SetAccessCommand(pCAAAfrTSurfNurbsStr,"CAAAfrNurbsSurfHdr");
         SetAccessNext(pCAAAfrTSurfRevolStr,pCAAAfrTSurfNurbsStr);

         NewAccess(CATCmdStarter,pCAAAfrTSurfOffsetStr,CAAAfrTSurfOffsetStr);
         SetAccessCommand(pCAAAfrTSurfOffsetStr,"CAAAfrOffsetSurfHdr");
         SetAccessNext(pCAAAfrTSurfNurbsStr,pCAAAfrTSurfOffsetStr);

      // Invisible toolbar set in the Right side of the application window
      AddToolbarView(pCAAAfrSurfacicEltTlb,-1,Right);

   //-----------------------------------
   //  Definition of the Menu bar Layout
   //-----------------------------------
   NewAccess(CATCmdContainer,pCAAAfrGeoCreationMbr,CAAAfrGeoCreationMbr);

      //---------------------------------
      //  Insert menu: new items to merge 
      //---------------------------------
      NewAccess(CATCmdContainer,pCATAfrInsertMnu,CATAfrInsertMnu);
      SetAccessChild(pCAAAfrGeoCreationMbr,pCATAfrInsertMnu);

         //----------------------
         //  A separator 
         //----------------------
         NewAccess(CATCmdSeparator,pCAAAfrGeoCreationInsertSep,CAAAfrGeoCreationInsertSep);
         SetAccessChild(pCATAfrInsertMnu,pCAAAfrGeoCreationInsertSep);

         //----------------------
         //  Solid Sub Menu 
         //----------------------
         NewAccess(CATCmdContainer,pCAAAfrSolidEltSnu,CAAAfrSolidEltSnu);
         SetAccessNext(pCAAAfrGeoCreationInsertSep,pCAAAfrSolidEltSnu);

            NewAccess(CATCmdStarter,pCAAAfrMSolidCuboidStr,CAAAfrMSolidCuboidStr);
            SetAccessChild(pCAAAfrSolidEltSnu,pCAAAfrMSolidCuboidStr);
            SetAccessCommand(pCAAAfrMSolidCuboidStr,"CAAAfrCuboidHdr");

            NewAccess(CATCmdStarter,pCAAAfrMSolidSphereStr,CAAAfrMSolidSphereStr);
            SetAccessNext(pCAAAfrMSolidCuboidStr,pCAAAfrMSolidSphereStr);
            SetAccessCommand(pCAAAfrMSolidSphereStr,"CAAAfrSphereHdr");
			    
            NewAccess(CATCmdStarter,pCAAAfrMSolidTorusStr,CAAAfrMSolidTorusStr);
            SetAccessNext(pCAAAfrMSolidSphereStr,pCAAAfrMSolidTorusStr);
            SetAccessCommand(pCAAAfrMSolidTorusStr,"CAAAfrTorusHdr");

            NewAccess(CATCmdStarter,pCAAAfrMSolidCylinder1Str,CAAAfrMSolidCylinder1Str);
            SetAccessNext(pCAAAfrMSolidTorusStr,pCAAAfrMSolidCylinder1Str);
            SetAccessCommand(pCAAAfrMSolidCylinder1Str,"CAAAfrCylinder1Hdr");
            
			NewAccess(CATCmdStarter,pCAAAfrMSolidCylinder2Str,CAAAfrMSolidCylinder2Str);
            SetAccessNext(pCAAAfrMSolidCylinder1Str,pCAAAfrMSolidCylinder2Str);
            SetAccessCommand(pCAAAfrMSolidCylinder2Str,"CAAAfrCylinder2Hdr");

         //----------------------
         //  Surfacic Sub Menu 
         //----------------------
         NewAccess(CATCmdContainer,pCAAAfrSurfacicEltSnu,CAAAfrSurfacicEltSnu) ;
         SetAccessNext(pCAAAfrSolidEltSnu,pCAAAfrSurfacicEltSnu);

            NewAccess(CATCmdStarter,pCAAAfrMSurfRevolStr,CAAAfrMSurfRevolStr);
            SetAccessChild(pCAAAfrSurfacicEltSnu,pCAAAfrMSurfRevolStr);
            SetAccessCommand(pCAAAfrMSurfRevolStr,"CAAAfrRevolSurfHdr");

            NewAccess(CATCmdStarter,pCAAAfrMSurfNurbsStr,CAAAfrMSurfNurbsStr);
            SetAccessNext(pCAAAfrMSurfRevolStr,pCAAAfrMSurfNurbsStr);
            SetAccessCommand(pCAAAfrMSurfNurbsStr,"CAAAfrNurbsSurfHdr");

            NewAccess(CATCmdStarter,pCAAAfrMSurfOffsetStr,CAAAfrMSurfOffsetStr);
            SetAccessNext(pCAAAfrMSurfNurbsStr,pCAAAfrMSurfOffsetStr);
            SetAccessCommand(pCAAAfrMSurfOffsetStr,"CAAAfrOffsetSurfHdr");



   // Menu bar to be merged with the CAAGeometryWks workshop menu bar
   SetWorkbenchMenu(pCAAAfrGeoCreationWkb,pCAAAfrGeoCreationMbr);

   // workbench pointer
   return pCAAAfrGeoCreationWkb ;

}


CATClassId CAAAfrGeoCreationWkb::GetAddinInterface()
{
    cout << " GetAddinInterface CAAAfrGeoCreationWkb" << endl ;

    return "CAAIAfrGeoCreationWkbAddin";
}

void CAAAfrGeoCreationWkb::GetCustomInterfaces(CATListPV * , CATListPV *)
{
   cout << "GetCustomInterfaces CAAAfrGeoCreationWkb" << endl ;
   // Useless
}
