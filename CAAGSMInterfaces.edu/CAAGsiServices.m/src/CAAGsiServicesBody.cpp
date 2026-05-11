/**
 * @fullreview PEY 03:01:07
 */
/**
 * @quickreview PEY 03:09:17
 * @quickreview SLA 04:04:13  mkCheckSource
 * @quickreview cev 06:12:08 MINC mkCheckSource
 */

// COPYRIGHT DASSAULT SYSTEMES 2000


// MINC 
#include "CATPathElement.h"

#include "CAAGsiServicesBody.h"


// Frame 
#include "CATFrmEditor.h"

// Part 
#include "CATIPrtPart.h"
#include "CATIContainer.h"
#include "CATIPrtContainer.h"
#include "CATIGeometricalElement.h"
#include "CATIGSMFactory.h"

// OM 
#include "CATISpecObject.h"


// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory
#include "CATGeometry.h"
#include "CATBody.h"                   // Geometry factory
#include "CATTopOperator.h"                   // Geometry factory
#include "CATGeoFactory.h"

#include "CATBody.h"
#include "CATDomain.h"
//System 
#include "CATBaseUnknown.h"


// #define DEBUG_CAASERVICESBODY    
#ifdef DEBUG_CAASERVICESBODY 
#include "iostream.h"
#endif 


//---------------------------------------------------------------------
//   Recuperation du container courant a partir de l'editeur courant
//---------------------------------------------------------------------
ExportedByCAAGsiServices  CATIContainer_var CAAGsiGetCurrentContainer()
{
	CATFrmEditor * editor = CATFrmEditor::GetCurrentEditor();

	// Insertion de l'objet
	if (editor)
	{
		CATPathElement PathAct = editor -> GetUIActiveObject();
		CATIPrtPart_var part = PathAct.SearchObject(CATIPrtPart::ClassName());
		if (!!part)
		{
			part -> Release();
			CATISpecObject_var Spec = part;
			CATIContainer_var cont = Spec -> GetFeatContainer();
			return cont;
		}
	}
	return NULL_var;
}

//-------------------------------------------------------------------
// return the GSMFactory of the container of the feature in input
// addref performed on the factory
//------------------------------------------------------------------
ExportedByCAAGsiServices CATIGSMFactory_var  CAAGsiGetGSMFactory (CATBaseUnknown *ipiFeature ) 
{
  HRESULT rc ; 
  CATIGSMFactory_var spGsmFac ;
  
  CATISpecObject_var spSpec = ipiFeature;
  if (!!spSpec) {
    CATIContainer_var spCont = spSpec->GetFeatContainer();
    if (!!spCont) {
      CATIGSMFactory * result =NULL   ;
      rc  = spCont->QueryInterface (IID_CATIGSMFactory, (void**) &result);
      if ( SUCCEEDED(rc)) {
          spGsmFac  = result;
          result -> Release() ; result = NULL;   
    
      }
    }
  }
  return spGsmFac ;
}



//---------------------------------------------------------------------
//   Retrieves the Geometry factory from Spec
//---------------------------------------------------------------------
ExportedByCAAGsiServices CATGeoFactory_var CAAGsiGetGeoFactory(const CATISpecObject_var& spec)
{
    CATGeoFactory_var spSpecGeo ;
    if (!!spec)
    {
        CATIContainer_var Cont = spec->GetFeatContainer();
        CATIPrtContainer_var PrtCont(Cont);
        if (!!PrtCont)
        {
            CATIContainer_var GeoCont  = PrtCont -> GetGeometricContainer();
            spSpecGeo = GeoCont;
        }
    }
    return spSpecGeo;
}


//---------------------------------------------------------------------
// First Body from spec 
//---------------------------------------------------------------------
ExportedByCAAGsiServices CATBody_var CAAGsiGetFirstBody(const CATISpecObject_var& ipiSpec)
{
  CATBody_var opiBody ;
  CATIGeometricalElement_var spGeoElem = ipiSpec;
  if (!!spGeoElem) {
    opiBody = spGeoElem->GetBodyResult();
  }
  return opiBody ;
}


// -------------------------------------------------------------------
// Dimension of Body 
// -------------------------------------------------------------------
ExportedByCAAGsiServices int CAAGsiGetHigherDimFromBody(const CATBody_var & Body)
{
	int iDimRet = -1;
	CATDomain * Domain;
	if (!!Body)
	{
		int NbDomain = Body -> GetNbDomains();
		for (int ii=1 ; ii<=NbDomain ; ii++)
		{
			Domain = Body -> GetDomain(ii);
			if (Domain)
			{
				int DimDomain = Domain -> GetLowDimension();
				if (DimDomain > iDimRet)
					iDimRet = DimDomain;
			}
		}
	}
	return iDimRet;
}

