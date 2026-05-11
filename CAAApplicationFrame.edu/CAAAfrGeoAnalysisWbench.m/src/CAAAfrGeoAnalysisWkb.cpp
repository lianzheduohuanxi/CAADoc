// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include <CAAAfrGeoAnalysisWkb.h>

// Declaration of a new Class of Command Header 
#include <CATCommandHeader.h>   
MacDeclareHeader(CAAAfrGeoAnalysisWkbHeader) ;

// ApplicationFrame Framework
#include <CATCreateWorkshop.h> // Need to use macro NewAccess, SetAccessCommand ...

// C++ standard library
#include "iostream.h"

//-------------------------------------------------------------------------
// To create the TIE object
#include <TIE_CATICAAAfrGeometryWksConfiguration.h> 
TIE_CATICAAAfrGeometryWksConfiguration(CAAAfrGeoAnalysisWkb);

// To declare that the class is a component main class 
CATImplementClass(CAAAfrGeoAnalysisWkb, Implementation, CATBaseUnknown, CATNull);

// 
// To declare that CAAAfrGeoAnalysisWkb implements CATICAAAfrGeometryWksConfiguration ,
//  insert the following line in the interface dictionary:
// 
//
//  CAAAfrGeoAnalysisWkb CATICAAAfrGeometryWksConfiguration libCAAAfrGeoAnalysisWbench
//

//------------------------------------------------------------------------

CAAAfrGeoAnalysisWkb::CAAAfrGeoAnalysisWkb()
{
	cout << " construction CAAAfrGeoAnalysisWkb " << endl;
}
CAAAfrGeoAnalysisWkb::~CAAAfrGeoAnalysisWkb()
{
	cout << " Destruction CAAAfrGeoAnalysisWkb " << endl;
}

//-------------------------------------------------------------------------

void CAAAfrGeoAnalysisWkb::CreateCommands()
{
   cout << "CreateCommands CAAAfrGeoAnalysisWkb" << endl ;

   //---------------------------------------------------------------------
   // Instantiation of the headers created by the macro MacDeclareHeader.
   // Commands are always available and are represented by a push button
   //----------------------------------------------------------------------

   new CAAAfrGeoAnalysisWkbHeader("CAAAfrNumericHdr"     , 
                                  "CAADegGeoCommands", 
                                  "CAADegAnalysisNumericCmd",
                                  (void *) NULL);

   new CAAAfrGeoAnalysisWkbHeader("CAAAfrLogicalHdr"     , 
                                  "CAADegGeoCommands", 
                                  "CAADegAnalysisLogCmd",
                                  (void *) NULL);

   new CAAAfrGeoAnalysisWkbHeader("CAAAfrEltTypeHdr"     ,
                                  "CAADegGeoCommands", 
                                  "CAADegAnalysisEltTypeCmd" , 
                                  (void *) NULL);

   new CAAAfrGeoAnalysisWkbHeader("CAAAfrBoundingEltHdr" , 
                                  "CAAAfrGeoCommands", 
                                  "CAAAfrBoundingElementCmd" , 
                                  (void *) NULL);

   new CAAAfrGeoAnalysisWkbHeader("CAAAfrCircleWindowHdr",  
                                 "CAACafUseToolsOptions",
								 "CAACafCircleWindowCmd",  
                                 (void *)NULL);

   new CAAAfrGeoAnalysisWkbHeader("CAAAfrProgressTaskHdr",  
                                 "CAAAfrProgressTask",
								 "CAAAfrProgressTaskSampleCmd",  
                                 (void *)NULL);
}

//-------------------------------------------------------------------------

CATCmdWorkbench * CAAAfrGeoAnalysisWkb::CreateWorkbench()      
{
   cout << "CreateWorkbench CAAAfrGeoAnalysisWkb" << endl ;

   //--------------------------------------------------------
   // Definition of the CAAAfrGeoAnalysisWkb workbench Layout 
   //--------------------------------------------------------
   NewAccess(CATCmdWorkbench,pCAAAfrGeoAnalysisWkb,CAAAfrGeoAnalysisWkb);

      //-----------------
      //  Analyse Toolbar  
      //-----------------
      NewAccess(CATCmdContainer,pCAAAfrAnalyzeTlb,CAAAfrAnalyzeTlb);
      SetAccessChild(pCAAAfrGeoAnalysisWkb,pCAAAfrAnalyzeTlb);

         NewAccess(CATCmdStarter,pCAAAfrTAnalyzeNumericStr,CAAAfrTAnalyzeNumericStr);
         SetAccessCommand(pCAAAfrTAnalyzeNumericStr,"CAAAfrNumericHdr");
         SetAccessChild(pCAAAfrAnalyzeTlb,pCAAAfrTAnalyzeNumericStr);

         NewAccess(CATCmdStarter,pCAAAfrTAnalyzeLogicalStr,CAAAfrTAnalyzeLogicalStr);
         SetAccessCommand(pCAAAfrTAnalyzeLogicalStr,"CAAAfrLogicalHdr");
         SetAccessNext(pCAAAfrTAnalyzeNumericStr,pCAAAfrTAnalyzeLogicalStr);

         NewAccess(CATCmdStarter,pCAAAfrTAnalyzeEltTypeStr,CAAAfrTAnalyzeEltTypeStr);
         SetAccessCommand(pCAAAfrTAnalyzeEltTypeStr,"CAAAfrEltTypeHdr");
         SetAccessNext(pCAAAfrTAnalyzeLogicalStr,pCAAAfrTAnalyzeEltTypeStr);

         NewAccess(CATCmdStarter,pCAAAfrTAnalyzeBoundingEltStr,CAAAfrTAnalyzeBoundingEltStr);
         SetAccessCommand(pCAAAfrTAnalyzeBoundingEltStr,"CAAAfrBoundingEltHdr");
         SetAccessNext(pCAAAfrTAnalyzeEltTypeStr,pCAAAfrTAnalyzeBoundingEltStr);

		 NewAccess(CATCmdStarter,pCAAAfrTAnalyzeCircleWindowStr,CAAAfrTAnalyzeCircleWindowStr);
         SetAccessCommand(pCAAAfrTAnalyzeCircleWindowStr,"CAAAfrCircleWindowHdr");
         SetAccessNext(pCAAAfrTAnalyzeBoundingEltStr,pCAAAfrTAnalyzeCircleWindowStr);

         NewAccess(CATCmdStarter,pCAAAfrTProgressTaskStr,CAAAfrTProgressTaskStr);
         SetAccessCommand(pCAAAfrTProgressTaskStr,"CAAAfrProgressTaskHdr");
         SetAccessNext(pCAAAfrTAnalyzeCircleWindowStr,pCAAAfrTProgressTaskStr);

      // Visible toolbar set in the right side of the application window
      AddToolbarView(pCAAAfrAnalyzeTlb,1,Right);

   //-----------------------------------
   //  Definition of the Menu bar Layout
   //-----------------------------------
   NewAccess(CATCmdContainer,pCAAAfrGeoAnalysisMbr,CAAAfrGeoAnalysisMbr);

      //--------------------------------------------
      //  Analyze menu: Between Tools and Window menu
      //--------------------------------------------
      NewAccess(CATCmdContainer,pCAAAfrAnalyzeMnu,CAAAfrAnalyzeMnu);
      SetAccessChild(pCAAAfrGeoAnalysisMbr,pCAAAfrAnalyzeMnu);

          NewAccess(CATCmdStarter,pCAAAfrMAnalyzeNumericStr,CAAAfrMAnalyzeNumericStr);
          SetAccessCommand(pCAAAfrMAnalyzeNumericStr,"CAAAfrNumericHdr");
          SetAccessChild(pCAAAfrAnalyzeMnu,pCAAAfrMAnalyzeNumericStr);

          NewAccess(CATCmdStarter,pCAAAfrMAnalyzeLogicalStr,CAAAfrMAnalyzeLogicalStr);
          SetAccessCommand(pCAAAfrMAnalyzeLogicalStr,"CAAAfrLogicalHdr");
          SetAccessNext(pCAAAfrMAnalyzeNumericStr,pCAAAfrMAnalyzeLogicalStr);

          NewAccess(CATCmdStarter,pCAAAfrMAnalyzeEltTypeStr,CAAAfrMAnalyzeEltTypeStr);
          SetAccessCommand(pCAAAfrMAnalyzeEltTypeStr,"CAAAfrEltTypeHdr");
          SetAccessNext(pCAAAfrMAnalyzeLogicalStr,pCAAAfrMAnalyzeEltTypeStr);

          NewAccess(CATCmdStarter,pCAAAfrMAnalyzeBoundingEltStr,CAAAfrMAnalyzeBoundingEltStr);
          SetAccessCommand(pCAAAfrMAnalyzeBoundingEltStr,"CAAAfrBoundingEltHdr");
          SetAccessNext(pCAAAfrMAnalyzeEltTypeStr,pCAAAfrMAnalyzeBoundingEltStr);

		  NewAccess(CATCmdStarter,pCAAAfrMAnalyzeCircleWindowStr, CAAAfrCircleWindowStr);
          SetAccessCommand(pCAAAfrMAnalyzeCircleWindowStr,"CAAAfrCircleWindowHdr");
          SetAccessNext(pCAAAfrMAnalyzeBoundingEltStr,pCAAAfrMAnalyzeCircleWindowStr);

		  NewAccess(CATCmdStarter,pCAAAfrMProgressTaskStr, CAAAfrMProgressTaskStr);
          SetAccessCommand(pCAAAfrMProgressTaskStr,"CAAAfrProgressTaskHdr");
          SetAccessNext(pCAAAfrMAnalyzeCircleWindowStr,pCAAAfrMProgressTaskStr);
      //--------------------------------------------
      //  Window menu: To attach the previous menu
      //--------------------------------------------
      NewAccess(CATCmdContainer,pCATAfrWindowMnu,CATAfrWindowMnu);
      SetAccessNext(pCAAAfrAnalyzeMnu,pCATAfrWindowMnu);


   // Menu bar to be merged with the CAAGeometryWks workshop menu bar
   SetWorkbenchMenu(pCAAAfrGeoAnalysisWkb,pCAAAfrGeoAnalysisMbr);
   
   
   // workbench pointer
   return pCAAAfrGeoAnalysisWkb ;

}

//-------------------------------------------------------------------------

CATClassId CAAAfrGeoAnalysisWkb::GetAddinInterface()
{
    cout << " GetAddinInterface CAAAfrGeoAnalysisWkb" << endl ;

    // Returns the interface name to implement to add an Addin to this
    // workbench. 
    return "CAAIAfrGeoAnalysisWkbAddin" ;
}

//-------------------------------------------------------------------------

void CAAAfrGeoAnalysisWkb::GetCustomInterfaces(CATListPV * DefaultIIDList, 
                                               CATListPV * CustomIIDList )
{
   // Useless method
   cout << "GetCustomInterfaces CAAAfrGeoAnalysisWkb" << endl ;
}

//-------------------------------------------------------------------------
