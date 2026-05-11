// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================================
//
// CAAAniAeroDynamicTransition.cpp
// Provide implementation to interface CATISamAnalysisTransition
// In this case definition of a new CASE and solution set.

// Provide implementation to CATIAlias for the transition
// This will define athe NLS identifier.
// 
// Last step of customisation is the figure defined in AeroDynamic.CATRsc file
//
// The Solution will have the Late type AeroDynamicSet
// as defined in the CAAAniCatalog generator.
//
// One methode to implement: ExecuteTransition
//
// Input Argument:
// --------------
// CATDocument * iDocument : Current CATAnalysis for data creation
//===================================================================================
#include "CAAAniAeroDynamicTransition.h"                  // Local Include
 
// ObjectModelerBase prereq
#include "CATDocument.h"                                  // Input Argument
#include "CATIContainer.h"                                // retreive the root container

// System prereq
#include "CATString.h"                                    // Management of Strings
#include "CATBaseUnknown.h"                               // CATBaseUnknown Object

// CATAnalysisInterfaces prereq
#include "CATISamAnalysisModelFactory.h"                  // Factory for feature creation
#include "CATISamAccess.h"                                // Get AnalysisContainer
#include "CATISamAnalysisContainer.h"                     // AnalysisContainer
#include "CATISamAnalysisScan.h"                          // Get Set in a case
#include "CATISamAnalysisManager.h"                       // Get Analysis Model
#include "CATISamAnalysisModel.h"                         // CATISamAnalysisModel
#include "CATISamAnalysisCase.h"                          // CATISamAnalysisCase
#include "CATISamAnalysisSet.h"                           // CATISamAnalysisSet
#include "CATISamSolution.h"                              // CATISamSolution

CATImplementClass( CAAAniAeroDynamicTransition,
                   CodeExtension,
                   CATBaseUnknown,
                   AeroDynamic);
 
//-----------------------------------------------------------------------------
// CAAAniAeroDynamicTransition : constructor
//-----------------------------------------------------------------------------
CAAAniAeroDynamicTransition::CAAAniAeroDynamicTransition():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAAniAeroDynamicTransition : destructor
//-----------------------------------------------------------------------------
CAAAniAeroDynamicTransition::~CAAAniAeroDynamicTransition()
{
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATISamAnalysisTransition.h"
TIE_CATISamAnalysisTransition( CAAAniAeroDynamicTransition);

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIAlias.h"
#include "CATOsmSUHandler.h"
TIE_CATIAlias( CAAAniAeroDynamicTransition);
//-----------------------------------------------------------------------------
// Implements CATISamAnalysisTransition::ExecuteTransition
//-----------------------------------------------------------------------------
HRESULT CAAAniAeroDynamicTransition::ExecuteTransition (const CATDocument* iDocument)
{
	HRESULT hr = E_FAIL;
	if(!iDocument) return (hr);
//===================================================================================
// Looking for Analysis Container
	CATISamAccess_var spAccess((CATBaseUnknown*)iDocument);
	CATIContainer* piCont = NULL;
	spAccess->GetSpecContainer(piCont);
	if (NULL == piCont) return (hr);

// Load the Feature Catalog for Startup On the CATIContainer
  CATUnicodeString CataName ("CAAAniCatalog.CATfct");
  CATUnicodeString CataId   ("CAAAniCatalog");
  CATUnicodeString  novelSUType("AeroDynamicSet"); //any dummy SU from CAAAniCatalog.CATfct
  CATOsmSUHandler   novelSUHandler(novelSUType, CataId, CataName);
  if (SUCCEEDED(novelSUHandler.IsValid()))
  {
	CATISpecObject_var dummy;
	novelSUHandler.Instanciate(dummy,piCont,""); 
  }

//===================================================================================
// Looking for CATISamAnalysisContainer Manager's adhesion
	CATISamAnalysisContainer_var spAnalysisCont(piCont);
	if(NULL_var == spAnalysisCont) return (hr);
	CATISamAnalysisManager_var spManager = NULL_var;
	hr = spAnalysisCont->GetAnalysisManager(spManager);
//===================================================================================
// Looking for CATISamAnalysisModelFactory  adhesion for st creation
	CATISamAnalysisModelFactory_var spFactory = piCont;
	piCont -> Release ();
  piCont = NULL;	
//===================================================================================
// Create a new case
	CATUnicodeString caseName("Aero Case");
	CATISamAnalysisCase* piCase = spFactory -> CreateAnalysisCase(caseName);
	if(NULL == piCase) return E_FAIL;
// Attach the Case under the FEM Model
	CATISpecObject* piFEMModel = NULL;
	hr = spManager -> GetCurrentModel(piFEMModel);
	if( NULL == piFEMModel)  return E_FAIL;
	CATISamAnalysisModel_var spAnalysisModel(piFEMModel);

// =================================

	spAnalysisModel->AddCase(piCase);
	piCase->SetWorkingModel(piFEMModel);
	piCase->SetSolver("Aero_Solver");
//===================================================================================
// Creation of  solution
	CATISamAnalysisScan_var spScan(piCase);
	CATISamAnalysisSet* piSet = NULL;
// Creating the solution set
	piSet = spFactory->CreateUserSet("AeroDynamicSet","AERO DYNAMIC Solution Set",piFEMModel);
	if(piSet)
	{
// The created set must be referenced as an output of the AnalysisCase
		hr = spScan->AddSet(piSet,Sam_OUT);
		if (!SUCCEEDED(hr)) return E_FAIL ;
		CATISamSolution_var spSolution(piSet);
		if(NULL_var != spSolution) spSolution->SetCase(piCase);
		piSet->Release();
    piSet = NULL;
	}
	piCase -> Release (); piCase = NULL;
	piFEMModel -> Release (); piFEMModel= NULL;
	return S_OK;
}
//-----------------------------------------------------------------------------
// Implements CATIAlias::SetAlias
//-----------------------------------------------------------------------------
void CAAAniAeroDynamicTransition::SetAlias(const CATUnicodeString&  iName ) 
{
  return;
}
//-----------------------------------------------------------------------------
// Implements CATIAlias::GetAlias
//-----------------------------------------------------------------------------
CATUnicodeString CAAAniAeroDynamicTransition::GetAlias() 
{
  return "Aero Dymanic";
}
