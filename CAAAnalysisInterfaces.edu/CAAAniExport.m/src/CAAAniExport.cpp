// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//  This Use Case illustrates how to explore a CATAnalysis document in order 
//  to create an exported file. The format of this file is not DASSAULT SYSTEMES 
//  proprietary and could be change at any time. 
//=============================================================================
//
//  Main Methods:
//  ------------
//  MainExport Scan From the CATAnalysis document to the Analysis Sets.
//
//  Input Argument:
//  --------------
//  CATDocument *idocument : Pointer on the current CATAnalysis Document
//  char        *ifile     : Complete path for the ascii file.
//  Return Errors:
//  -------------
//  1 - HRESULT S_OK is every thing is OK E_FAIL Otherwhise.
//
//=============================================================================
#include "CATDocument.h"                    // Management of CATDocument
#include "CATString.h"                      // Management of CATString
#include "CATLib.h"                         // File access

#include "CAAAniExport.h"                   // Local includes of the sample
// Object Modeler and Spec modeler 
# include "CATIContainer.h"                 // For Contenair of document
# include "CATISpecObject.h"                // Spec Object (Name, Type ...)
// Analysis Interfaces Contenair and all feature object 
# include "CATISamAccess.h"                 // Analysis Contenair extraction
# include "CATISamAnalysisContainer.h"      // Analysis Contenair
# include "CATISamAnalysisManager.h"        // Analysis Manager
# include "CATISamAnalysisModel.h"          // CATISamAnalysisModel
# include "CATISamAnalysisCase.h"           // CATISamAnalysisCase
# include "CATISamAnalysisScan.h"           // Scan Analysis Model and cases
# include "CATISamAnalysisSet.h"            // CATISamAnalysisSet
# include "CATISamSolution.h"               // Behavoir Solution for the sets
// Field model interfaces
#include "CATAnalysisExplicitModel.h"      //  Access to the physical types.
#include "CATAnalysisCharacCollector.h"    //  Charac-collector object
//=============================================================================
// Internal method in order to launch the comptation (Update of the model)
//  Input Argument:
//  --------------
//  CATISamAnalysisModel_var ihFEMModel : Handler on the FEMModel to update
//  Return Errors:
//  -------------
//  1 - HRESULT S_OK is every thing is OK E_FAIL Otherwhise.

HRESULT CAAAniComputeSolution(CATISamAnalysisModel_var ihFEMModel);
//=============================================================================
HRESULT CAAAniExport(CATDocument *idocument,char* ifile)
{
	HRESULT hr   = S_OK;
	FILE*  File = NULL;;
  CATIContainer                *PiSpecContainerOnCont=NULL;
	CATISamAnalysisContainer_var hAnalysisContainer  ;
	CATISamAnalysisManager_var   hAnalysisManager ;
	CATISamAnalysisCase_var      hAnalysisCase ;
	CATISamAnalysisScan_var      hAnalysisScan  ;
	CATISamAnalysisSet_var       hFeatureSet ;
	CATISpecObject_var           hSpecObjectSet ;
	CATAnalysisCharacCollector   **ListCollector =NULL;
	char                         Ligne[512];
	int icase,iset;
//================================================================================
// Find the Main entity inside the feature tree : AnalysisManager
//================================================================================
	CATISamAccess_var  SamAccess (idocument);
	if( !SamAccess) return E_FAIL;
  hr = SamAccess -> GetSpecContainer(PiSpecContainerOnCont) ;
	if ( !SUCCEEDED(hr)) return E_FAIL;
  hAnalysisContainer = PiSpecContainerOnCont ;
  if ( !hAnalysisContainer) return E_FAIL;
	PiSpecContainerOnCont->Release();

  hr = hAnalysisContainer->GetAnalysisManager(hAnalysisManager) ;
	if ( !SUCCEEDED(hr)) return E_FAIL;
//================================================================================
// Initialize the File for output
//================================================================================
	if ((File = fopen  (ifile,"w")) == NULL) return E_FAIL;
//================================================================================
// Loocking to the Field model pointer and retreive some physical type for programming
//================================================================================
  CATAnalysisExplicitModel *ExplicitModel = CATAnalysisExplicitModel::GetDocumentModel(idocument);
//================================================================================
// Generate the File Header
//================================================================================
	sprintf (Ligne,"//  \n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	sprintf (Ligne,"//  Ascii file as sample for Export capability for Analysis document \n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	sprintf (Ligne,"//  \n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
//================================================================================
// Get the different Analysis Model inside the document (AnalysisModels)
//================================================================================
  CATLISTV(CATBaseUnknown_var) oCasesList;
  CATLISTV(CATBaseUnknown_var) AnalysisModels;
  hr = hAnalysisManager->GetAllAnalysisModels(AnalysisModels);
	if (! SUCCEEDED(hr)) return E_FAIL;
  int NbModels = AnalysisModels.Size();
	cout << NbModels <<" model (s) defined "<< endl;
  if (NbModels == 0) 
	{
		cout << " No model defined "<< endl;
		return hr;
	}
//================================================================================
// Take the first Analysis models to launch the computation if needed
//================================================================================
  CATISamAnalysisModel_var FEMModel = AnalysisModels[1];
	hr = CAAAniComputeSolution(FEMModel);
	if (! SUCCEEDED(hr)) return E_FAIL;
//================================================================================
// Take the first Analysis models to look after the Cases list and sets scan
//================================================================================
	hAnalysisScan  = AnalysisModels[1];
//================================================================================
//  Get the analysis interface scan in order to find the sets inside the FEM model
//  The set that can be retreive are MaterialSet,AxisSet,PropertySet
//================================================================================
	CATLISTV(CATBaseUnknown_var) oSetsList = NULL;
	hAnalysisScan  -> GetAllSets(oSetsList);
//================================================================================
//  Retreive from the Analysis Model Name, feature type ...
	hSpecObjectSet = hAnalysisScan;
	CATUnicodeString SetName(hSpecObjectSet->GetName()) ;
	CATUnicodeString SetType(hSpecObjectSet->GetType()) ;
	sprintf (Ligne,"%s %s \n",SetType.ConvertToChar(),SetName.ConvertToChar());
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
//================================================================================
// Dump the information fom the list of set. Extract from each Set its name, feature type
// and the physical type that can be returned.
//================================================================================
	cout << "Number of set: "<<oSetsList.Size() << endl;
	if (oSetsList.Size()) 
	{
		for (iset=1 ; iset <= oSetsList.Size() ; iset ++ )
		{
			sprintf (Ligne,"//  \n");
			fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
			fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	// Take the next set
			hFeatureSet = oSetsList[iset];
	// Extract from the set Name and feture type
			hSpecObjectSet = oSetsList[iset];
			CATUnicodeString SetName(hSpecObjectSet->GetName()) ;
			CATUnicodeString SetType(hSpecObjectSet->GetType()) ;

			sprintf (Ligne,"%s %s \n",SetType.ConvertToChar(),SetName.ConvertToChar());
			fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);

	// Generate the file for the set output
			hr = CAAAniSelectPhysics(File,ExplicitModel,hFeatureSet);
			if (! SUCCEEDED(hr)) return E_FAIL;
		}
	}
// Empty the list for new usage.
	oSetsList.RemoveAll();
//================================================================================
// Look after the list of Cases attached to the Analysis Model
//================================================================================
  hr = FEMModel -> GetAllCases(oCasesList);
	if (! SUCCEEDED(hr)) return E_FAIL;
  int CaseSize = oCasesList.Size();
	cout << CaseSize <<" Case(s) defined "<< endl;
  if (CaseSize == 0) 
	{
		cout << " No Case defined "<< endl;
		return hr;
	}
//================================================================================
// Scan this list of cases
//================================================================================
	for (icase =1 ; icase <= 1 ; icase ++ )
	{
	// Take the next case
		hAnalysisCase = oCasesList[icase];
	// Extract the SolverName defined on the Case
		CATString oSolverName ;
		hr = hAnalysisCase -> GetSolver(oSolverName);
		if (SUCCEEDED(hr)) 
		{
			sprintf (Ligne,"// SolverName: %s \n",oSolverName.CastToCharPtr());
			fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
		} 

		sprintf (Ligne,"//  \n");
		fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
		fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);

	// Extract from the case Name and feature type
		hSpecObjectSet = oCasesList[icase];
		CATUnicodeString SetName(hSpecObjectSet->GetName()) ;
		CATUnicodeString SetType(hSpecObjectSet->GetType()) ;
		sprintf (Ligne,"%s %s \n",SetType.ConvertToChar(),SetName.ConvertToChar());
		fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);

	// Switch on the Analysis Scan interface
		hAnalysisScan  = oCasesList[icase];
		hAnalysisScan ->GetAllSets(oSetsList);
		cout << oSetsList.Size() << endl;
		if ( oSetsList.Size()) 
		{
			for (iset=1 ; iset <= oSetsList.Size() ; iset ++ )
			{
				hFeatureSet    = oSetsList[iset];
				hSpecObjectSet = oSetsList[iset];
				sprintf (Ligne,"//  \n");
				fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
				fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
				CATUnicodeString SetName(hSpecObjectSet->GetName()) ;
				CATUnicodeString SetType(hSpecObjectSet->GetType()) ;
				sprintf (Ligne,"%s %s \n",SetType.ConvertToChar(),SetName.ConvertToChar());
				fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	// Generate the file for the set output
				hr = CAAAniSelectPhysics(File,ExplicitModel,hFeatureSet);
				cout <<" CAAAniSelectPhysics "<< endl;
				if (! SUCCEEDED(hr)) return E_FAIL;
			}
		}
		oSetsList.RemoveAll();
	}
//==================================================================================================
// End of job  Close the File and end
	if (File) fclose (File);
	File = NULL;
//==================================================================================================
	return hr;
}
//==================================================================================================
HRESULT CAAAniComputeSolution(CATISamAnalysisModel_var FEMModel)
// DUMMY Method In order to launch the computation on site
//==================================================================================================
{
	HRESULT hr   = S_OK;
//================================================================================
// Look after the list of Cases attached to the Analysis Model
//================================================================================
  CATLISTV(CATBaseUnknown_var) oCasesList;
	CATLISTV(CATBaseUnknown_var) oSetsList = NULL;

  hr = FEMModel -> GetAllCases(oCasesList);
	if (! SUCCEEDED(hr)) return E_FAIL;

  int CaseSize = oCasesList.Size();
	cout <<  "In Compute" << CaseSize <<" Case(s) defined "<< endl;
  if (CaseSize == 0) 
	{
		cout << " No Case defined "<< endl;
		return hr;
	}
//================================================================================
// Scan this list of cases
//================================================================================
	for (int icase =1 ; icase <= 1 ; icase ++ )
	{
	// Switch on the Analysis Scan interface for each case
		CATISamAnalysisScan_var hAnalysisScan  = oCasesList[icase];
		if (!hAnalysisScan) return E_FAIL;
		hAnalysisScan ->GetAllSets(oSetsList);
		if ( oSetsList.Size()) 
		{
			for (int iset=1 ; iset <= oSetsList.Size() ; iset ++ )
			{
	// To launch the computation of the solution  if Needed.
				CATISamSolution_var hIsSolution (oSetsList[iset]);
				if (NULL_var != hIsSolution) 
				{
					CATISpecObject_var hSpecObjectSet (oSetsList[iset]);
					if (NULL_var != hSpecObjectSet) hr = hSpecObjectSet -> Update();
					if (! SUCCEEDED(hr)) return E_FAIL;
					cout << " Computation  of "<< (hSpecObjectSet->GetName()).ConvertToChar()<<endl;

				}
			}
		}
	}
	return hr;
}
	
