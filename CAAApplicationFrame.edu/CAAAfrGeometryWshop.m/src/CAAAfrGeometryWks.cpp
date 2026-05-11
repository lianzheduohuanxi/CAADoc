// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAAfrGeometryWks.h"
#include "CATICAAAfrGeometryWksConfiguration.h"
#include "CAAIAfrGeometryWksAddin.h"               

// Creates the CAAAfrGeometryWksHeader command header class
#include <CATCommandHeader.h>
MacDeclareHeader(CAAAfrGeometryWksHeader) ;

// Customized command header class
#include "CAAAfrDumpCommandHeader.h"

// ApplicationFrame Framework
#include <CATCreateWorkshop.h>  // to use NewAccess, NewAccessChild ... macros

// C++ standard library
#include "iostream.h"

//---------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIWorkshop.h> 
TIE_CATIWorkshop(CAAAfrGeometryWks);

// To declare that the class is an implementation
CATImplementClass(CAAAfrGeometryWks, Implementation, CATBaseUnknown, CATNull);

// 
// To declare that CAAAfrGeometryWks implements CATIWorkshop, insert 
// the following line in the interface dictionary:
//
//    CAAAfrGeometryWks CATIWorkshop  libCAAAfrGeometryWks
//
//-----------------------------------------------------------------------------

CAAAfrGeometryWks::CAAAfrGeometryWks()
{
  cout << " Construction CAAAfrGeometryWks " << endl;
}

//-----------------------------------------------------------------------------

CAAAfrGeometryWks::~CAAAfrGeometryWks()
{
  cout << " Destruction CAAAfrGeometryWks " << endl;
}

//-----------------------------------------------------------------------------

void CAAAfrGeometryWks::CreateCommands()
{
  cout << "CreateCommands CAAAfrGeometryWks" << endl ;
  // ------------------------------------------------------------------------------
  //  1- Instantiation of the header class created by the macro MacDeclareHeader -
  //     commands are always available and are represented by a push button
  // ------------------------------------------------------------------------------

      // --------------------------
      // 1-a Cases without argument
      // --------------------------
  new CAAAfrGeometryWksHeader("CAAAfrListFormatHdr",
                              "CommandLib", 
                              "CommandName",  
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrQueryExploreHdr", 
                              "CAAAfrGeoCommands", 
                              "CAAAfrQueryExploreCmd",
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrPolylineBy2TrianglesHdr",
                              "CAADegGeoCommands", 
                              "CAADegCreatePolylineBy2TrianglesCmd",    
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrPointHdr",
                              "CAADegGeoCommands", 
                              "CAADegCreatePointCmd",    
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrLineHdr",     
                              "CAADegGeoCommands", 
                              "CAADegCreateLineCmd",     
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrCircleHdr",   
                              "CAADegGeoCommands", 
                              "CAADegCreateCircleCmd", 
                                (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrEllipseHdr",  
                              "CAADegGeoCommands", 
                              "CAADegCreateEllipseCmd",  
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrPlaneHdr",    
                              "CAADegGeoCommands", 
                              "CAADegCreatePlaneCmd",    
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrTriangleHdr", 
                              "CAADegGeoCommands", 
                              "CAADegCreateTriangleCmd", 
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrRectangleHdr",
                              "CAADegGeoCommands", 
                              "CAADegCreateRectangleCmd",
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrPolylineHdr", 
                              "CAADegGeoCommands", 
                              "CAADegCreatePolylineCmd", 
                              (void *) NULL);

  new CAAAfrGeometryWksHeader("CAAAfrComputeHdr",      
                              "CommandLib", 
                              "CommandName",      
                              (void *) NULL);

      // --------------------------
      //  1-b Cases with argument 
      // --------------------------
  new CAAAfrGeometryWksHeader("CAAAfrNormalXHdr",
                              "CAAAfrGeoCommands",
                              "CAAAfrChangeViewNormalCmd",(void *)CATINT32ToPtr(1));

  new CAAAfrGeometryWksHeader("CAAAfrNormalYHdr",
                              "CAAAfrGeoCommands",
                              "CAAAfrChangeViewNormalCmd",(void *)CATINT32ToPtr(2));

  new CAAAfrGeometryWksHeader("CAAAfrNormalZHdr",
                              "CAAAfrGeoCommands",
                              "CAAAfrChangeViewNormalCmd",(void *)CATINT32ToPtr(3));

  //-------------------------------------------------------------------------
  //  2- Instantiation of the header class dedicated to the Dump command -   
  //     The CAAAfrDumpCommandHeader class manages the command availability
  //-------------------------------------------------------------------------
  new CAAAfrDumpCommandHeader("CAAAfrDumpHdr");

}

CATCmdWorkshop * CAAAfrGeometryWks::CreateWorkshop()      
{
   cout << "CreateWorkshop CAAAfrGeometryWks" << endl ;

   //--------------------------------------------------------
   // Definition of the CAAAfrGeometryWks workshop Layout 
   //--------------------------------------------------------
   NewAccess(CATCmdWorkshop,pCAAAfrGeometryWks,CAAAfrGeometryWks);


      //-----------------
      //  Select Toolbar
      //-----------------
      // If you have a Select Toolbar set it always at the beginning
      //
      NewAccess(CATCmdContainer,pCAAAfrSelectTlb,CAAAfrSelectTlb);
      SetAccessChild(pCAAAfrGeometryWks,pCAAAfrSelectTlb);

         NewAccess(CATCmdStarter,pCAAAfrSelectStr,CAAAfrSelectStr);
         SetAccessCommand(pCAAAfrSelectStr,"CATAfrSelectHdr");
         SetAccessChild(pCAAAfrSelectTlb,pCAAAfrSelectStr);

      // Visible (-1 if invisible) toolbar at the right side of the frame
      AddToolbarView(pCAAAfrSelectTlb,1,Right);  

      //------------------------
      //  Basic Elements Toolbar 
      //------------------------
      NewAccess(CATCmdContainer,pCAAAfrBasicElementTlb,CAAAfrBasicElementTlb);
      SetAccessNext(pCAAAfrSelectTlb,pCAAAfrBasicElementTlb);

         NewAccess(CATCmdStarter,pCAAAfrBasicPointStr,CAAAfrBasicPointStr);
         SetAccessCommand(pCAAAfrBasicPointStr,"CAAAfrPointHdr");
         SetAccessChild(pCAAAfrBasicElementTlb,pCAAAfrBasicPointStr);

         NewAccess(CATCmdStarter,pCAAAfrBasicLineStr,CAAAfrBasicLineStr);
         SetAccessCommand(pCAAAfrBasicLineStr,"CAAAfrLineHdr");
         SetAccessNext(pCAAAfrBasicPointStr,pCAAAfrBasicLineStr);

		 NewAccess(CATCmdStarter,pCAAAfrBasicPlaneStr,CAAAfrBasicPlaneStr);
         SetAccessCommand(pCAAAfrBasicPlaneStr,"CAAAfrPlaneHdr");
         SetAccessNext(pCAAAfrBasicLineStr,pCAAAfrBasicPlaneStr);

		 NewAccess(CATCmdSeparator,pCAAAfrBasic1Sep,CAAAfrBasic1Sep);
         SetAccessNext(pCAAAfrBasicPlaneStr,pCAAAfrBasic1Sep);

         NewAccess(CATCmdStarter,pCAAAfrBasicCircleStr,CAAAfrBasicCircleStr);
         SetAccessCommand(pCAAAfrBasicCircleStr,"CAAAfrCircleHdr");
         SetAccessNext(pCAAAfrBasic1Sep,pCAAAfrBasicCircleStr);

         NewAccess(CATCmdStarter,pCAAAfrBasicEllipseStr,CAAAfrBasicEllipseStr);
         SetAccessCommand(pCAAAfrBasicEllipseStr,"CAAAfrEllipseHdr");
         SetAccessNext(pCAAAfrBasicCircleStr,pCAAAfrBasicEllipseStr);

         // ------------------------------
         // Multi-Lines Elements Icone Box  
         // ------------------------------
         NewAccess(CATCmdContainer,pCAAAfrMLinesIcb,CAAAfrMLinesIcb);
         SetAccessNext(pCAAAfrBasicEllipseStr,pCAAAfrMLinesIcb);

            NewAccess(CATCmdStarter,pCAAAfrTRectangleStr,CAAAfrTRectangleStr);
            SetAccessCommand(pCAAAfrTRectangleStr,"CAAAfrRectangleHdr");
            SetAccessChild(pCAAAfrMLinesIcb,pCAAAfrTRectangleStr);

            NewAccess(CATCmdStarter,pCAAAfrTTriangleStr,CAAAfrTTriangleStr);
            SetAccessCommand(pCAAAfrTTriangleStr,"CAAAfrTriangleHdr");
            SetAccessNext(pCAAAfrTRectangleStr,pCAAAfrTTriangleStr);

            NewAccess(CATCmdStarter,pCAAAfrTPolylineStr,CAAAfrTPolylineStr);
            SetAccessCommand(pCAAAfrTPolylineStr,"CAAAfrPolylineHdr");
            SetAccessNext(pCAAAfrTTriangleStr,pCAAAfrTPolylineStr);

            NewAccess(CATCmdStarter,pCAAAfrPolylineBy2TrianglesStr,CAAAfrPolylineBy2TrianglesStr);
            SetAccessCommand(pCAAAfrPolylineBy2TrianglesStr,"CAAAfrPolylineBy2TrianglesHdr");
            SetAccessNext(pCAAAfrTPolylineStr,pCAAAfrPolylineBy2TrianglesStr);

      // Visible (-1 if invisible) toolbar at the right of the frame
      AddToolbarView(pCAAAfrBasicElementTlb,1,Right); 


   //-----------------------------------
   //  Definition of the Menu bar Layout
   //-----------------------------------
   NewAccess(CATCmdContainer,pCAAAfrGeometryMbr,CAAAfrGeometryMbr);

     //--------------------------------------------------
     //  View menu: new items to merge
     //--------------------------------------------------
     // CATAfrView is the identificator of the View menu 
     NewAccess(CATCmdContainer,pCATAfrView,CATAfrView);
     SetAccessChild(pCAAAfrGeometryMbr,pCATAfrView);

        NewAccess(CATCmdContainer,pCAAAfrNormalViewSnu,CAAAfrNormalViewSnu);
        SetAccessChild(pCATAfrView,pCAAAfrNormalViewSnu);

           NewAccess(CATCmdStarter,pCAAAfrNormalXStr,CAAAfrNormalXStr);
           SetAccessCommand(pCAAAfrNormalXStr,"CAAAfrNormalXHdr");
           SetAccessChild(pCAAAfrNormalViewSnu,pCAAAfrNormalXStr);

           NewAccess(CATCmdStarter,pCAAAfrNormalYStr,CAAAfrNormalYStr);
           SetAccessCommand(pCAAAfrNormalYStr,"CAAAfrNormalYHdr");
           SetAccessNext(pCAAAfrNormalXStr,pCAAAfrNormalYStr);

           NewAccess(CATCmdStarter,pCAAAfrNormalZStr,CAAAfrNormalZStr);
           SetAccessCommand(pCAAAfrNormalZStr,"CAAAfrNormalZHdr");
           SetAccessNext(pCAAAfrNormalYStr,pCAAAfrNormalZStr);

     //--------------------------------
     // Insert menu: New items to merge   
     //--------------------------------
     NewAccess(CATCmdContainer,pCATAfrInsertMnu,CATAfrInsertMnu);
     SetAccessNext(pCATAfrView,pCATAfrInsertMnu);

        NewAccess(CATCmdStarter,pCAAAfrInsertPointStr,CAAAfrInsertPointStr);
        SetAccessCommand(pCAAAfrInsertPointStr,"CAAAfrPointHdr");
        SetAccessChild(pCATAfrInsertMnu,pCAAAfrInsertPointStr);

        NewAccess(CATCmdStarter,pCAAAfrInsertLineStr,CAAAfrInsertLineStr);
        SetAccessCommand(pCAAAfrInsertLineStr,"CAAAfrLineHdr");
        SetAccessNext(pCAAAfrInsertPointStr,pCAAAfrInsertLineStr);
		
		NewAccess(CATCmdStarter,pCAAAfrInsertPlaneStr,CAAAfrInsertPlaneStr);
        SetAccessCommand(pCAAAfrInsertPlaneStr,"CAAAfrPlaneHdr");
        SetAccessNext(pCAAAfrInsertLineStr,pCAAAfrInsertPlaneStr);

		NewAccess(CATCmdSeparator,pCAAAfrInsert1Str,CAAAfrInsert1Sep);
        SetAccessNext(pCAAAfrInsertPlaneStr,pCAAAfrInsert1Str);

        NewAccess(CATCmdStarter,pCAAAfrInsertCircleStr,CAAAfrInsertCircleStr);
        SetAccessCommand(pCAAAfrInsertCircleStr,"CAAAfrCircleHdr");
        SetAccessNext(pCAAAfrInsert1Str,pCAAAfrInsertCircleStr);

        NewAccess(CATCmdStarter,pCAAAfrInsertEllipseStr,CAAAfrInsertEllipseStr);
        SetAccessCommand(pCAAAfrInsertEllipseStr,"CAAAfrEllipseHdr");
        SetAccessNext(pCAAAfrInsertCircleStr,pCAAAfrInsertEllipseStr);

        // --------------------
        // Multi-Lines Elements
        // --------------------
        NewAccess(CATCmdContainer,pCAAAfrMLinesSnu,CAAAfrMLinesSnu);
        SetAccessNext(pCAAAfrInsertEllipseStr,pCAAAfrMLinesSnu);

            NewAccess(CATCmdStarter,pCAAAfrMRectangleStr,CAAAfrMRectangleStr);
            SetAccessCommand(pCAAAfrMRectangleStr,"CAAAfrRectangleHdr");
            SetAccessChild(pCAAAfrMLinesSnu,pCAAAfrMRectangleStr);

            NewAccess(CATCmdStarter,pCAAAfrMTriangleStr,CAAAfrMTriangleStr);
            SetAccessCommand(pCAAAfrMTriangleStr,"CAAAfrTriangleHdr");
            SetAccessNext(pCAAAfrMRectangleStr,pCAAAfrMTriangleStr);

            NewAccess(CATCmdStarter,pCAAAfrMPolylineStr,CAAAfrMPolylineStr);
            SetAccessCommand(pCAAAfrMPolylineStr,"CAAAfrPolylineHdr");
            SetAccessNext(pCAAAfrMTriangleStr,pCAAAfrMPolylineStr);

     //------------------------------------------------------
     //   Format menu: a new menu always beetwen Insert and Tools
     //------------------------------------------------------
     NewAccess(CATCmdContainer,pCAAAfrFormatMnu,CAAAfrFormatMnu);
     SetAccessNext(pCATAfrInsertMnu,pCAAAfrFormatMnu);

        NewAccess(CATCmdStarter,pCAAAfrListFormatStr,CAAAfrListFormatStr);
        SetAccessCommand(pCAAAfrListFormatStr,"CAAAfrListFormatHdr");
        SetAccessChild(pCAAAfrFormatMnu,pCAAAfrListFormatStr);

     //-------------------------------
     // Tools menu: New items to merge 
     //-------------------------------
	 // If your workshop doesn't modify the Tools menu 
	 // you must attach the Format menu to the Tools menu 
	 // see the sample of the Explore menu
     //
     // CATAfrToolsMnu is the identificator of the Tools menu 
     NewAccess(CATCmdContainer,pCATAfrToolsMnu,CATAfrToolsMnu);
     SetAccessNext(pCAAAfrFormatMnu,pCATAfrToolsMnu);

        // Dump just before Macro
        NewAccess(CATCmdStarter,pCAAAfrToolsDumpStr,CAAAfrToolsDumpStr);
        SetAccessCommand(pCAAAfrToolsDumpStr,"CAAAfrDumpHdr");
        SetAccessChild(pCATAfrToolsMnu,pCAAAfrToolsDumpStr);
        SetAccessAnchorName(pCAAAfrToolsDumpStr,"CATAfrToolsMacroSnu");   

        // Compute just before IMAGE
        NewAccess(CATCmdStarter,pCAAAfrToolsComputeStr,CAAAfrToolsComputeStr);
        SetAccessCommand(pCAAAfrToolsComputeStr,"CAAAfrComputeHdr");
        SetAccessNext(pCAAAfrToolsDumpStr,pCAAAfrToolsComputeStr);
        SetAccessAnchorName(pCAAAfrToolsComputeStr,"CATAfrToolsImageSnu"); 


      //-----------------------------------------------------
      // Explore menu: a new menu beetween Tools and Windows
      //-----------------------------------------------------
      NewAccess(CATCmdContainer,pCAAAfrExploreMnu,CAAAfrExploreMnu);
      SetAccessNext(pCATAfrToolsMnu,pCAAAfrExploreMnu);

         NewAccess(CATCmdStarter,pCAAAfrQueryExploreStr,CAAAfrQueryExploreStr);
         SetAccessCommand(pCAAAfrQueryExploreStr,"CAAAfrQueryExploreHdr");
         SetAccessChild(pCAAAfrExploreMnu,pCAAAfrQueryExploreStr);

      //-----------------------------------------------------
      // Window menu: to attach Explore menu to the Window menu
	  // else Explore is just before the Help menu
      //-----------------------------------------------------
      // CATAfrWindowMnu is the identificator of the Window menu 
      NewAccess(CATCmdContainer,pCATAfrWindowMnu,CATAfrWindowMnu);
      SetAccessNext(pCAAAfrExploreMnu,pCATAfrWindowMnu);

   // Menu bar to be merged with the General workshop menu bar
   SetWorkshopMenu(pCAAAfrGeometryWks,pCAAAfrGeometryMbr);

   // workshop pointer
   return pCAAAfrGeometryWks;

}

CATClassId CAAAfrGeometryWks::GetWorkbenchInterface()
{
   cout << " GetWorkbenchInterface CAAAfrGeometryWks" << endl ;

   return "CATICAAAfrGeometryWksConfiguration";
}

CATClassId CAAAfrGeometryWks::GetAddinInterface()
{
   cout << " GetAddinInterface CAAAfrGeometryWks" << endl ;

   return "CAAIAfrGeometryWksAddin" ;
}

