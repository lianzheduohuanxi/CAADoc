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



#include "CAAEMaiUserPostProcessorIntegrationExtPPProviders.h"

#include <iostream.h>

#include "CAAIMaiUserPostProcessorIntegrationExternalPPClient1.h"

#include "CATListPV.h"

#include "TIE_CATIMfgExternalPPDefinition.h"

// ---------------------------------------------------------------------------------
CATImplementClass (CAAEMaiUserPostProcessorIntegrationExtPPProviders,CodeExtension,CATBaseUnknown,
		   CATMfgExtPPManagement);
// ---------------------------------------------------------------------------------

TIE_CATIMfgExternalPPDefinition (CAAEMaiUserPostProcessorIntegrationExtPPProviders);

//========================================================================
// Constructor
//========================================================================
CAAEMaiUserPostProcessorIntegrationExtPPProviders::CAAEMaiUserPostProcessorIntegrationExtPPProviders ()
{
}
//========================================================================
// Destructor
//========================================================================
CAAEMaiUserPostProcessorIntegrationExtPPProviders::~CAAEMaiUserPostProcessorIntegrationExtPPProviders ()
{
}
//========================================================================
HRESULT CAAEMaiUserPostProcessorIntegrationExtPPProviders::GetListOfExternalPostProcessorProviders 
                                          (CATListPV& oListOfPostProcessorProviders)
{
  cout << "==> CAAEMaiUserPostProcessorIntegrationExtPPProviders::GetListOfExternalPostProcessorProviders" << endl;
  HRESULT rc = S_OK;
  
  oListOfPostProcessorProviders.RemoveAll ();

  oListOfPostProcessorProviders.Append ((void*) &CAAIMaiUserPostProcessorIntegrationExternalPPClient1::ClassId ());
  
  cout << "<== CAAEMaiUserPostProcessorIntegrationExtPPProviders::GetListOfExternalPostProcessorProviders" << endl;

  return rc;
}
