// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrCCDataExtensionVisu.cpp
// Provide implementation to interface CATI3DGeoVisu for CAAV5V6ExtMmrCCDataExtension
//
// Note : CAAEV5V6ExtMmrCCDataExtensionVisu is the same use case as CAAEMmrCCDataExtensionVisu. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//======================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrCCDataExtensionVisu.h" 
#include "CAAIV5V6ExtMmrCCDataExtension.h"

// VisualizationBase Framework for V5
// VisualizationFoundation Framework for V6
#include "CAT3DBagRep.h"
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DCustomRep.h"
#include "CATRep.h"

// VisualizationBase Framework for V5
// VisualizationCore Framework for V6
#include "CATGraphicAttributeSet.h"

// Visualization Framework for V5
// VisualizationInterfaces Framework for V6
#include "CATI3DGeoVisu.h"

// CATMecModUseItf Framework
#include "CATIMmiUseGeometricalElement.h"

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathPointf.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// System Framework 
#include "CATUnicodeString.h"

// C++ Standard library
#include "iostream.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

//DataCommonProtocolUse framework
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

#else
//============================================== 
// V5 only
//==============================================

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

#endif


//======================================================================================
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEV5V6ExtMmrCCDataExtensionVisu);

CATImplementClass(CAAEV5V6ExtMmrCCDataExtensionVisu, DataExtension, CATBaseUnknown, CAAV5V6ExtMmrCCDataExtension);
//======================================================================================
CAAEV5V6ExtMmrCCDataExtensionVisu::CAAEV5V6ExtMmrCCDataExtensionVisu()
{}

CAAEV5V6ExtMmrCCDataExtensionVisu::~CAAEV5V6ExtMmrCCDataExtensionVisu()
{}

CATRep *CAAEV5V6ExtMmrCCDataExtensionVisu::BuildRep()
{ 
  cout <<" CAAEV5V6ExtMmrCCDataExtensionVisu::BuildRep" << endl;

  //This impl consists in creating a 3DRepresentation associated with the Extension.
  //As our Extension is like a measure, computing and retrieving the length of its base feature,
  //Let's build a 3DRep with an annotation valuated with the computed legth !

  // 1] Creates a 3DBagRep
  //    All representations built during BuildRep will be aggregated under the 3DBagRep created
  //    At the end of BuildRep, we will return this BagRep, sort of "Representation Set"

  CAT3DBagRep * BagRep = new CAT3DBagRep();
  CAT3DAnnotationTextGP * pAnnotationText = NULL;

  CAAIV5V6ExtMmrCCDataExtension* pCAAMmrCCDataExtension = NULL;
  
  HRESULT rc = QueryInterface(IID_CAAIV5V6ExtMmrCCDataExtension, (void**) & pCAAMmrCCDataExtension);
  if (SUCCEEDED(rc))
  {
    CATBaseUnknown* pBaseFeature = NULL;
    CATICkeParm_var spValuatedParm;

    // 2] Retrieves the Base Feature to known where "stick" the 3DRep
    rc = pCAAMmrCCDataExtension->GetGeomFeature(pBaseFeature);

    // 3] Retrieves the valuated Parm
    rc = pCAAMmrCCDataExtension->GetValuatedParam (spValuatedParm);

    if (pBaseFeature != NULL)
    {
      CATIMmiUseGeometricalElement* pGeometricalElementOnBaseFeature = NULL;
      rc = pBaseFeature->QueryInterface(IID_CATIMmiUseGeometricalElement, (void**) & pGeometricalElementOnBaseFeature);
      if(SUCCEEDED(rc)) //Retrieves Geometrical Element
      {
        // 4 ] Defines the inputs of CAT3DAnnotationTextGP
        CATMathPoint BoundingBoxGravityCenter;
        CATMathPoint LowerPoint;
        CATMathPoint HigherPoint;

        rc = pGeometricalElementOnBaseFeature->GetGeomCharacteristicPoints(BoundingBoxGravityCenter, LowerPoint, HigherPoint);
        
        if (spValuatedParm != NULL_var)
        {
          // 5 ] Defines Value displayed by CAT3DAnnotationTextGP
          CATMathPointf CenterPoint(BoundingBoxGravityCenter);
          const CATUnicodeString StringValue = spValuatedParm->Show();

          // 6 ] Creates the CAT3DAnnotationTextGP
          pAnnotationText = new CAT3DAnnotationTextGP(CenterPoint, StringValue);
        }

        pGeometricalElementOnBaseFeature->Release();
        pGeometricalElementOnBaseFeature=NULL;
      }
      pBaseFeature->Release();
      pBaseFeature = NULL;
    }
    pCAAMmrCCDataExtension -> Release();
    pCAAMmrCCDataExtension = NULL;
  }

  // 7 ] Sets attributes to 3DRep (Colors)
  CATGraphicAttributeSet textGrAttrs;
  int textColorRed=255, textColorGreen=0, textColorBlue=255;
  textGrAttrs.SetColorRGBA(textColorRed, textColorGreen, textColorBlue);
  textGrAttrs.SetColor(TRUECOLOR);
  
  CAT3DCustomRep* customRep = new CAT3DCustomRep();

  if (customRep && pAnnotationText)
    customRep->AddGP(pAnnotationText, textGrAttrs);

  // 8 ] Aggregates 3DRep to CAT3DBagRep
  rc = BagRep->AddChild(*customRep);

  // 9 ] Returns the BagRep.
  return BagRep;
}

int CAAEV5V6ExtMmrCCDataExtensionVisu::ModifyRep (const CATNotification & iInfo)
{
  // Change color on Modifying event
  CATI3DGeoVisu_var h3DVisu = this;

  if (h3DVisu != NULL_var)
  {
	CATBoolean bIsUpToDate=TRUE;

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATIUseEntity * piEntity = NULL;
	HRESULT rc = this->QueryInterface(IID_CATIUseEntity , (void**) &piEntity);
  
	if (SUCCEEDED(rc))
	{
	  rc = DataCommonProtocolServices::IsUpToDate(piEntity, bIsUpToDate);
	
	  piEntity->Release(); 
	  piEntity = NULL;

	}
#else
//============================================== 
// V5 only
//==============================================
	CATISpecObject_var hSOonThis = this;
    
	if (hSOonThis != NULL_var)
       bIsUpToDate = hSOonThis->IsUpToDate();
        
#endif

    if (!bIsUpToDate)
	{  
      CATRep *pRep = h3DVisu->GetRep();
      if (pRep != NULL)
      { 
        list<CATRep> * pListOfChildren = pRep->GetChildren();
        if (pListOfChildren !=NULL && pListOfChildren->length()!= NULL)
            (*pListOfChildren)[0]->SetColor(RED);
        return 1;
      }
	} 
  }

  // Don't forget to continue implementation with default behaviors (CATExtIVisu::ModifyRep(iInfo));
  return CATExtIVisu::ModifyRep(iInfo);
}
