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

#include "IUnknown.h"
extern "C" const IID IID_CAAIMaiUserPostProcessorIntegrationExternalPPClient1 = { /* 5a3437a9-3b1b-11d5-be22-0002b33bd3b7 */
    0x5a3437a9, 
    0x3b1b, 
    0x11d5, 
    { 0xbe, 0x22, 0x0, 0x2, 0xb3, 0x3b, 0xd3, 0xb7 }
  };
