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

#ifndef CAAIMaiUserPostProcessorIntegrationExternalPPClient1_H
#define CAAIMaiUserPostProcessorIntegrationExternalPPClient1_H

#include "CATIMfgExternalPPManagement.h"
#include "CAAMaiPostProcessorEnv.h"

//=============================================================================
#ifndef LOCAL_DEFINITION_FOR_IID
extern IID IID_CAAIMaiUserPostProcessorIntegrationExternalPPClient1;
#else
extern "C" const IID IID_CAAIMaiUserPostProcessorIntegrationExternalPPClient1;
#endif

class ExportedByCAAMaiPostProcessorEnv CAAIMaiUserPostProcessorIntegrationExternalPPClient1 : public CATIMfgExternalPPManagement
{
  CATDeclareInterface ;  

  public:

};

CATDeclareHandler (CAAIMaiUserPostProcessorIntegrationExternalPPClient1,CATBaseUnknown) ;
#endif
