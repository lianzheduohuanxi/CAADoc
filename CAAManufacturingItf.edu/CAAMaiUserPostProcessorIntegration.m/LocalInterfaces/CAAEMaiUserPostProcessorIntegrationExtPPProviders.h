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
/* -*-c++-*- */
#ifndef CAAEMaiUserPostProcessorIntegrationExtPPProviders_H
#define CAAEMaiUserPostProcessorIntegrationExtPPProviders_H

#include "CATBaseUnknown.h"

#include "CATListPV.h"

class CAAEMaiUserPostProcessorIntegrationExtPPProviders : public CATBaseUnknown
{
public:
  CATDeclareClass;
  
  // Constructor
  CAAEMaiUserPostProcessorIntegrationExtPPProviders ();

  // Destructor
  virtual ~CAAEMaiUserPostProcessorIntegrationExtPPProviders ();
  
  // Gives the list of Post Processor provides
  // oListOfPostProcessorProviders : list of IID of interfaces of Post Processor providers
  virtual HRESULT GetListOfExternalPostProcessorProviders 
		                         (CATListPV& oListOfPostProcessorProviders);

private:
	// Copy constructor
  CAAEMaiUserPostProcessorIntegrationExtPPProviders(const CAAEMaiUserPostProcessorIntegrationExtPPProviders &iObjectToCopy);
  CAAEMaiUserPostProcessorIntegrationExtPPProviders &operator =(const CAAEMaiUserPostProcessorIntegrationExtPPProviders &iCom); 
};
#endif
