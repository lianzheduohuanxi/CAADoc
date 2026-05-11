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
#ifndef CAAEMaiUserPostProcessorIntegrationExtPPClient1_H
#define CAAEMaiUserPostProcessorIntegrationExtPPClient1_H

#include "CATBaseUnknown.h"

#include "CATString.h"
#include "CATListOfCATString.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

class CAAEMaiUserPostProcessorIntegrationExtPPClient1 : public CATBaseUnknown
{
public:
  CATDeclareClass;
  
  //Constructor
  CAAEMaiUserPostProcessorIntegrationExtPPClient1 ();

  //Destructor
  virtual ~CAAEMaiUserPostProcessorIntegrationExtPPClient1 ();
  
  // Gives the Post Processor provider name
  // oNLSName : in native language : "My Post Processor Provider"
  // oKeywordName : "MYPPPROVIDER"
  virtual HRESULT GetProviderNames ( CATUnicodeString&        oNLSName     ,
				     CATString&               oKeywordName );

  // Gives the list of PPs managed by the provider
  // oNLSList : in native language
  // oKeywordList : qs keywords
  virtual HRESULT GetListOfPPs     ( CATListOfCATUnicodeString& oNLSList     , 
				     CATListOfCATString&        oKeywordList );
  // Open method to run PP help
  virtual HRESULT RunHelp          ( CATString&                 iPPKeyword );

  // Open method to run PP
  virtual HRESULT RunPP            ( CATListOfCATUnicodeString& iPPParams );

private:
  CAAEMaiUserPostProcessorIntegrationExtPPClient1(const CAAEMaiUserPostProcessorIntegrationExtPPClient1 &iObjectToCopy);
  CAAEMaiUserPostProcessorIntegrationExtPPClient1 &operator =(const CAAEMaiUserPostProcessorIntegrationExtPPClient1 &iCom); 
};
#endif
