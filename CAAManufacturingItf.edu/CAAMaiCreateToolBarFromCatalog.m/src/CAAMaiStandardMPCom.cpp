// ========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//========================================================================
//
// Class CAAMaiStandardMPCom2: command for Machining process application 
//
//========================================================================
//
//Dialogue
#include "CAAMaiStandardMPCom.h"

#include "CATLib.h"


#include "CATCreateExternalObject.h"
#include "CATIMfgCatalogServices.h"

#include "CATInstantiateComponent.h"

CATCreateClassArg(CAAMaiStandardMPCom, CATString);

//========================================================================
// Constructeur
//========================================================================

CAAMaiStandardMPCom::CAAMaiStandardMPCom(const CATString * iIdentifier)
: CATCommand("CAAMaiStandardMPCom",CATCommandModeShared)
{  
}

//========================================================================
// Destructeur
//========================================================================

CAAMaiStandardMPCom::~CAAMaiStandardMPCom()
{   
}

//========================================================================
// Activate
//========================================================================
CATStatusChangeRC CAAMaiStandardMPCom::Activate(CATCommand* c, CATNotification* notif)
{
  // ---> Gestion des paths et instantiation
  CATIMfgCatalogServices *piServices=NULL;

  CATString ClassName("CATMfgCatalogServices");
  CATInstantiateComponent (ClassName,CATIMfgCatalogServices::ClassId(),(void**)&piServices);

  if (NULL != piServices)
  {
//  CATUnicodeString PathDocument = "E:\\users\\dcn\\adele\\CXR11_dcn\\intel_a\\startup\\Manufacturing\\Processes\\MP_demo.catalog";
    CATUnicodeString CatalogName = "MP_demo.catalog";
    CATUnicodeString Path;
    HRESULT Res = piServices->BuildMfgStartupMPPath(CatalogName, Path);

    CATUnicodeString PathChapter = "Chapter.1/Drilling Processes";
    CATUnicodeString NomMPRef = "Standard Drilling";
    CATString Keyword = "Standard_Drilling";
    Res = piServices->LaunchMPApplication(Path, PathChapter, NomMPRef, Keyword);

    if (NULL != piServices) piServices->Release();
    piServices = NULL;
  }
  
  RequestDelayedDestruction();
  return (CATStatusChangeRCCompleted);
}
