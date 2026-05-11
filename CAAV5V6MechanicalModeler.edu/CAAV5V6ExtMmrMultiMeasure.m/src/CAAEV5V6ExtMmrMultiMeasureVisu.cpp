// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrMultiMeasureVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrMultiMeasure
//
// Note :  CAAEV5V6ExtMmrMultiMeasureVisu is the same use case as CAAEMmrMultiMeasureVisu. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//======================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrMultiMeasureVisu.h" 
#include "CAAIV5V6ExtMmrMultiMeasure.h"

// VisualizationFoundation Framework for V6
// VisualizationBase Framework for V5
#include "CAT3DBagRep.h"
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DCustomRep.h"
#include "CATRep.h"

// VisualizationCore Framework for V6
// VisualizationBase Framework for V5
#include "CATGraphicAttributeSet.h"

// GMModelInterfaces Framework
#include "CATBody.h"

// CATMecModUseItf Framework
#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiUseBRep.h"

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathPointf.h"

// KnowledgeInterfaces 
#include "CATICkeParm.h"

// System Framework
#include "CATUnicodeString.h"

// C++ Standard library
#include "iostream.h"


#include <TIE_CATI3DGeoVisu.h>
TIE_CATI3DGeoVisu(CAAEV5V6ExtMmrMultiMeasureVisu);

CATImplementClass(CAAEV5V6ExtMmrMultiMeasureVisu, DataExtension, CATExtIVisu, CAAV5V6ExtMmrMultiMeasure);
// To declare that CAAV5V6ExtMmrMultiMeasure implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary :
//
// CAAV5V6ExtMmrMultiMeasure   CATI3DGeoVisu   libCAAV5V6ExtMmrMultiMeasure

CAAEV5V6ExtMmrMultiMeasureVisu::CAAEV5V6ExtMmrMultiMeasureVisu()
{}

CAAEV5V6ExtMmrMultiMeasureVisu::~CAAEV5V6ExtMmrMultiMeasureVisu()
{}

CATRep *CAAEV5V6ExtMmrMultiMeasureVisu::BuildRep()
{ 
	cout <<" CAAEV5V6ExtMmrMultiMeasureVisu::BuildRep()" << endl;

  CAT3DBagRep  * BagRep = new CAT3DBagRep ();
  CAT3DAnnotationTextGP * pAnnotationText  = NULL;
  CAT3DAnnotationTextGP * pAnnotationText2 = NULL;

  CAAIV5V6ExtMmrMultiMeasure* pMmrMultiMeasure = NULL;

  HRESULT rc = QueryInterface(IID_CAAIV5V6ExtMmrMultiMeasure, (void**) & pMmrMultiMeasure);
  if (SUCCEEDED(rc) && pMmrMultiMeasure != NULL)
  {
    CATBaseUnknown* pInputFeature = NULL;
    rc = pMmrMultiMeasure->GetGeomFeature(pInputFeature);

    if (SUCCEEDED(rc) && pInputFeature != NULL)
    {  
      CATICkeParm_var spLengthParm;
      CATICkeParm_var spAreaParm;
      CATICkeParm_var spVolumeParm;
  
	    pMmrMultiMeasure->GetLengthParameter(spLengthParm); 
	    pMmrMultiMeasure->GetWetAreaParameter(spAreaParm);
	    pMmrMultiMeasure->GetVolumeParameter(spVolumeParm);
    
      if (!!spLengthParm && !!spAreaParm && !!spVolumeParm)
      {
        CATIMmiUseGeometricalElement* pGeomElemOnInputFeature = NULL;
        rc = pInputFeature->QueryInterface(IID_CATIMmiUseGeometricalElement, (void**) & pGeomElemOnInputFeature);
        
        if (FAILED(rc) || pGeomElemOnInputFeature == NULL) // BRepCase or Error on Feature Instance
        {
          // pGeomFeature is a BRep Feature
          CATIMmiUseBRep *pMfBRep = NULL;
          rc = pInputFeature->QueryInterface(IID_CATIMmiUseBRep, (void**) &pMfBRep);
          if (SUCCEEDED(rc) && pMfBRep != NULL) 
          {
            // In BRepCase we choose to retrieve the MasterSupport to define TextBox Params
            CATIMmiMechanicalFeature_var hSupportOfBRep = NULL_var; 
						rc = pMfBRep->GetBRepSupport(hSupportOfBRep);
            if (SUCCEEDED(rc))
              rc = hSupportOfBRep->QueryInterface(IID_CATIMmiUseGeometricalElement, 
							                                    (void**) & pGeomElemOnInputFeature);
            
            pMfBRep->Release();
            pMfBRep = NULL;
          }
          else
            //error on feature
            return BagRep;
        }
        
        if (SUCCEEDED(rc) && pGeomElemOnInputFeature != NULL) //Retrieves Geometrical Element
        {
          CATMathPoint BoundingBoxGravityCenter;
          CATMathPoint LowerPoint;
          CATMathPoint HigherPoint;

          CATUnicodeString StringValue("");

          rc = pGeomElemOnInputFeature->GetGeomCharacteristicPoints(BoundingBoxGravityCenter, LowerPoint, HigherPoint);
          if ((spLengthParm->Value())->AsReal() != NULL)
          {
            StringValue.Append(spLengthParm->RelativeName(this));
            StringValue.Append(" = ");
            StringValue.Append(spLengthParm->Show());
            CATMathPointf CenterPoint(BoundingBoxGravityCenter);
            pAnnotationText = new CAT3DAnnotationTextGP(CenterPoint , StringValue, BASE_CENTER, 0.f,1);
          }
          else
          {
            if ((spAreaParm->Value())->AsReal() != NULL)
            {
              StringValue.Append(spAreaParm->RelativeName(this));
              StringValue.Append(" = ");
              StringValue.Append(spAreaParm->Show());
              CATMathPointf CenterPoint(BoundingBoxGravityCenter);
              pAnnotationText = new CAT3DAnnotationTextGP (CenterPoint , StringValue, TOP_CENTER, 0.f, 1);
            }
            if ((spVolumeParm->Value())->AsReal() != NULL)
            {
              StringValue = (spVolumeParm->RelativeName(this));
              StringValue.Append(" = ");
              StringValue.Append(spVolumeParm->Show());
              CATMathPointf CenterPoint(BoundingBoxGravityCenter);
              pAnnotationText2 = new CAT3DAnnotationTextGP (CenterPoint , StringValue, BOTTOM_CENTER, 0.f, 1);
            }
          }
          pGeomElemOnInputFeature->Release();
          pGeomElemOnInputFeature = NULL;

          CATGraphicAttributeSet textGrAttrs;
          int textColorRed = 113, textColorGreen=0, textColorBlue = 202;
          textGrAttrs.SetColorRGBA(textColorRed, textColorGreen, textColorBlue);
          textGrAttrs.SetColor(TRUECOLOR);

          CAT3DCustomRep* customRep = new CAT3DCustomRep();

          if (customRep && pAnnotationText)
          {
            customRep->AddGP(pAnnotationText, textGrAttrs);
            if (pAnnotationText2 != NULL)
              customRep->AddGP(pAnnotationText2, textGrAttrs);
            
            customRep->SetShowFreeMode(0);
          }
          BagRep->AddChild(*customRep);
        }
      }
      pInputFeature->Release();
      pInputFeature = NULL;
    }
    pMmrMultiMeasure->Release();
    pMmrMultiMeasure = NULL;
  }

  return BagRep;
}

