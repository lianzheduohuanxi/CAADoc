// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniAeroMesher.cpp
// Provide implementation to interface CATIMSHMesher
// Sample of code for managing Analysis data for Aero Dynamic.
// Import of Meshing data inside the CATAnalysis.
//===================================================================
#include "CAAAniAeroMesher.h"               // Local Include

/// AnalysisMeshingModel
#include "CATIMSHMeshPart.h"                // MeshPart Management
#include "CATIMSHMeshManager.h"             // MeshPart Management
#include "CATIMSHMesh.h"                    // Meshing Nodes and element Access

#include "CATILinkableObject.h"            // MeshPart Support Management
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATUnicodeString.h"
#include "CATDocument.h"
#include "CAAIAniAeroImport.h"


CATImplementClass(CAAAniAeroMesher,DataExtension,CATMSHExtIMesher,AeroMeshPart_mesher);

//-----------------------------------------------------------------------------
// CAAAniAeroMesher : constructor
//-----------------------------------------------------------------------------
CAAAniAeroMesher::CAAAniAeroMesher():CATMSHExtIMesher()
{}
//-----------------------------------------------------------------------------
// CAAAniAeroMesher : destructor
//-----------------------------------------------------------------------------
CAAAniAeroMesher::~CAAAniAeroMesher()
{}
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMSHMesher.h"                
TIE_CATIMSHMesher(CAAAniAeroMesher);  

//=====================================================================
int CAAAniAeroMesher::IsATypeOf (CATIMSHMeshPart * iMeshPart,const CATUnicodeString &iType)
{
  if (iType == CATUnicodeString("2D")) return 1 ;
  return 0;
}

//=====================================================================
HRESULT CAAAniAeroMesher::CheckSupport ( CATIMSHMeshPart * MeshPart , int &NbParents , CATIMSHMeshPart ** &ParentMeshParts )
{
  HRESULT hr = S_OK;

  NbParents = 0;
  ParentMeshParts = NULL;

  CATDocument* pBaseDoc  = NULL;
  hr = GetLinkedDoc (MeshPart,pBaseDoc);
  if (!SUCCEEDED(hr)) return E_FAIL;
  if (NULL == pBaseDoc) return E_FAIL;

  return hr;
}

//=====================================================================
HRESULT CAAAniAeroMesher::GetLinkedDoc ( CATIMSHMeshPart * MeshPart,CATDocument* &oDoc)
{
  HRESULT oHR = S_OK;
  oDoc = NULL;

  if (NULL == MeshPart) return E_FAIL;
  
  CATISpecObject * piLink = NULL;
  CATISpecAttrAccess * piMPAc = NULL;
  CATISpecAttrKey * piKey = NULL;
  MeshPart -> QueryInterface(IID_CATISpecAttrAccess,(void **) &piMPAc);
  if (NULL != piMPAc)
  {
    piKey = piMPAc -> GetAttrKey("InputLink");
    if (piKey) {
      piLink = piMPAc -> GetSpecObject(piKey);
      piKey -> Release(); piKey = NULL;
    }
    piMPAc -> Release(); piMPAc = NULL;
  }

  if (piLink)
  {
    CATISpecAttrAccess * piLinkDoc = NULL;
    piLink -> QueryInterface(IID_CATISpecAttrAccess,(void **) &piLinkDoc);
  
    if (piLinkDoc)
    {
      CATILinkableObject * piLinkable = NULL;
      piKey = piLinkDoc -> GetAttrKey("ExternDoc");
      if (piKey) {
        piLinkable = piLinkDoc -> GetExternalObject(piKey,ANYWHERE);
        piKey -> Release(); piKey = NULL;
      }
      if (piLinkable)
      {
        oDoc = piLinkable -> GetDocument();
        piLinkable -> Release();  piLinkable = NULL;
      }
      else 
        oHR = E_FAIL;
        
      piLinkDoc -> Release (); piLinkDoc = NULL;
    }
    piLink -> Release ();  piLink = NULL;
  }
  else 
    oHR = E_FAIL;

  return oHR;
}

//=====================================================================
HRESULT CAAAniAeroMesher::Mesh (CATIMSHMeshPart* MeshPart)
{
  // Check Input Argument
  HRESULT oHR = S_OK;
  if (NULL == MeshPart) return E_FAIL;
  
  // Retrieve document from the Mesh Part
  CATDocument * pBaseDoc  = NULL;
  oHR = GetLinkedDoc (MeshPart,pBaseDoc);

  if (!SUCCEEDED(oHR) || NULL == pBaseDoc) return E_FAIL;

  CATIMSHMeshManager * piManager = MeshPart -> GetMeshManager ();
	if (NULL == piManager) return E_FAIL;
	
  CATIMSHMesh * piMesh = piManager -> GetMesh ();
	if (piManager) piManager -> Release();  piManager = NULL;
	if (NULL == piMesh) return E_FAIL;

  // Start Meshing
  CAAIAniAeroImport_var spAeroImport = pBaseDoc ;
	if ( !spAeroImport) return E_FAIL;
  
  oHR = spAeroImport -> ImportFif (MeshPart,piMesh);
 	if (piMesh)    piMesh -> Release();

  return oHR;
}

