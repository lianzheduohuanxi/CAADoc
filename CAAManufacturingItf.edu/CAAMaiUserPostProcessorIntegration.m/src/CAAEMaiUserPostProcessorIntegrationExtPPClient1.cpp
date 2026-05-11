// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAIMaiUserPostProcessorIntegrationExternalPPClient1
//
// Sample code for : NC Manufacturing Review Programmer
// Mission         : Add a new post processor provider into NC Manufacturing Workbench
//
//
// Type            : Interactive functionality
//
// Illustrates     : 1- use of manufacturing interfaces 
//
// How to run it   :  
//					In the file CAAManufacturingItf.dico, decomment the following line  
// CATMfgExtPPManagement  CATIMfgExternalPPDefinition                           libCAAMaiUserPostProcessorIntegration
// CATMfgExtPPManagement  CAAIMaiUserPostProcessorIntegrationExternalPPClient1  libCAAMaiUserPostProcessorIntegration
// CATMfgExtPPManagement  CATICreateInstance                                    libCAAMaiUserPostProcessorIntegration
//
//					Manage Tool + Options + NC Manufacturing + Output
//
//
//=============================================================================

#include "CAAEMaiUserPostProcessorIntegrationExtPPClient1.h"

#include "CATCommandHeader.h"
#include "CATLib.h"
#include <iostream.h>
#include "CATString.h"
#include "CATListOfCATString.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

#include "TIE_CAAIMaiUserPostProcessorIntegrationExternalPPClient1.h"


CATImplementClass (CAAEMaiUserPostProcessorIntegrationExtPPClient1,CodeExtension,CATBaseUnknown,
		   CATMfgExtPPManagement);

TIE_CAAIMaiUserPostProcessorIntegrationExternalPPClient1 (CAAEMaiUserPostProcessorIntegrationExtPPClient1);

//========================================================================
// Constructor
//========================================================================
CAAEMaiUserPostProcessorIntegrationExtPPClient1::CAAEMaiUserPostProcessorIntegrationExtPPClient1()
{
   cout << "<==> CAAEMaiUserPostProcessorIntegrationExtPPClient1::CAAEMaiUserPostProcessorIntegrationExtPPClient1" << endl;
}
//========================================================================
// Destructor
//========================================================================
CAAEMaiUserPostProcessorIntegrationExtPPClient1::~CAAEMaiUserPostProcessorIntegrationExtPPClient1 ()
{
   cout << "<==> CAAEMaiUserPostProcessorIntegrationExtPPClient1::~CAAEMaiUserPostProcessorIntegrationExtPPClient1" << endl;
}
//========================================================================
// GetProviderNames : oNLSName is provider company name (NLS)
//                    oKeywordName is same name (not NLS) 
//========================================================================
HRESULT CAAEMaiUserPostProcessorIntegrationExtPPClient1::GetProviderNames ( CATUnicodeString& oNLSName     ,
					       CATString&        oKeywordName )
{
   cout << "==> CAAEMaiUserPostProcessorIntegrationExtPPClient1::GetProviderNames" << endl;

   HRESULT RC = S_OK;

   oNLSName     = "My Post Processors";
   oKeywordName = "MyPP";
   
   cout << "    Nom NLS: " << oNLSName.ConvertToChar() << endl;
   cout << "    Mot cle: " << oKeywordName << endl;
   cout << "<== CAAEMaiUserPostProcessorIntegrationExtPPClient1::GetProviderNames" << endl;

   return RC;
}
//========================================================================
// GetListOfPPs : list of PPs : NLS
//                list of PPs : keywords 
//========================================================================
HRESULT CAAEMaiUserPostProcessorIntegrationExtPPClient1::GetListOfPPs ( CATListOfCATUnicodeString& oNLSList     ,
					   CATListOfCATString&        oKeywordList )
{
   cout << "==> CAAEMaiUserPostProcessorIntegrationExtPPClient1::GetListOfPPs" << endl;

   HRESULT RC = S_OK;
  
   oNLSList.RemoveAll ();
   oKeywordList.RemoveAll ();

   oNLSList.Append ("My PP 1");
   oNLSList.Append ("My PP 2");

   oKeywordList.Append ("PP1");
   oKeywordList.Append ("PP2");
   
   cout << "<== CAAEMaiUserPostProcessorIntegrationExtPPClient1::GetListOfPPs" << endl;

   return RC;
}
//========================================================================
// RunHelp : iPPKeyword : PP Name : keyword
//========================================================================
HRESULT CAAEMaiUserPostProcessorIntegrationExtPPClient1::RunHelp ( CATString& iPPKeyword )
{
   cout << "==> CAAEMaiUserPostProcessorIntegrationExtPPClient1::RunHelp" << endl;

   HRESULT RC = S_OK;

	// Definition of the path and of the file containing the documentation of the Post-processor
	// which has iPPKeyword as associated keyword
   CATUnicodeString path ("/xx/xxx/xxx") , file ("PP1.html");
   char cFile [256];
   CATMakePath (path.ConvertToChar(),file.ConvertToChar(),cFile);

    // Execute the browser to open the html file
   CATCommandHeader* header = NULL;

   header = CATCommandHeader::GetHeaderFromList ("CATContextualHelpCommand");

   if (NULL != header)
     {
       header -> SetArgument (CATString (cFile));
       header -> StartCommand ();
       header -> SetArgument (CATString (""));
     }

   cout << "<== CAAEMaiUserPostProcessorIntegrationExtPPClient1::RunHelp" << endl;

   return RC;
}
//========================================================================
// RunPP : iPPKeyword : PP Name : keyword
//========================================================================
HRESULT CAAEMaiUserPostProcessorIntegrationExtPPClient1::RunPP ( CATListOfCATUnicodeString& iPPParams )
{
   cout << "==> CAAEMaiUserPostProcessorIntegrationExtPPClient1::RunPP" << endl;
   cout << "    PP Name to run      : " << iPPParams[1].ConvertToChar() << endl;
   cout << "    NC file             : " << iPPParams[2].ConvertToChar() << endl;
   cout << "    ISO file            : " << iPPParams[3].ConvertToChar() << endl;

   HRESULT RC = S_OK;

   // Here has to be written the code for the post-processor submission code, 
   // using the input parameters


   cout << "<== CAAEMaiUserPostProcessorIntegrationExtPPClient1::RunPP" << endl;

   return RC;
}
//========================================================================
