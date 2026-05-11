// ========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//========================================================================
// 
// Class CAAMaiStandardMPCom2: command for Machining process application 
//=============================================================================
//
//Dialogue
#include "CAAMaiStandardMPCom2.h"

#include "CATLib.h"

#include <iostream.h>

#include "CATCreateExternalObject.h"
#include "CATIMfgCatalogServices.h"

#include "CATInstantiateComponent.h"

CATCreateClassArg(CAAMaiStandardMPCom2, CATString);

//========================================================================
// Constructeur
//========================================================================

CAAMaiStandardMPCom2::CAAMaiStandardMPCom2(const CATString * iIdentifier)
: CATCommand("CAAMaiStandardMPCom2",CATCommandModeShared)
{  
  cout << " iIdentifier  ="<< &iIdentifier <<endl;
}

//========================================================================
// Destructeur
//========================================================================

CAAMaiStandardMPCom2::~CAAMaiStandardMPCom2()
{   
}

//========================================================================
// Activate
//========================================================================
CATStatusChangeRC CAAMaiStandardMPCom2::Activate(CATCommand* c, CATNotification* notif)
{
  // ---> Gestion des paths et instantiation
  CATIMfgCatalogServices *piServices=NULL;

  CATString ClassName("CATMfgCatalogServices");
  CATInstantiateComponent (ClassName,CATIMfgCatalogServices::ClassId(),(void**)&piServices);

  if (NULL != piServices)
  {
//  CATUnicodeString PathDocument = "E:\\users\\dcn\\adele\\CXR11_dcn\\intel_a\\startup\\Manufacturing\\Processes\\MP_demo.catalog";
    CATUnicodeString CatalogName = "Machining-Processes.catalog";
    CATUnicodeString Path;
    HRESULT Res = piServices->BuildMfgStartupMPPath(CatalogName, Path);

    CATUnicodeString PathChapter = "Machining Process/Milling Processes/2.5 axis";
    CATUnicodeString NomMPRef = "Pocketing MP";
    CATString Keyword = "Pocketing from MP";
    Res = piServices->LaunchMPApplication(Path, PathChapter, NomMPRef, Keyword);

    if (NULL != piServices) piServices->Release();
    piServices = NULL;
  }
  
  RequestDelayedDestruction();
  return (CATStatusChangeRCCompleted);
}
