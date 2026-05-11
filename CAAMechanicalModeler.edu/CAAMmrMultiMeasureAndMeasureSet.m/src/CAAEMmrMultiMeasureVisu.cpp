// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrMultiMeasureVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrMultiMeasure
//======================================================================================

#include "CAAEMmrMultiMeasureVisu.h" 

#include "CAAIMmrMultiMeasure.h"

//VisualizationBase Fw
#include "CAT3DBagRep.h"
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DCustomRep.h"

//Geometry & Topo
#include "CATBody.h"
#include "CATIGeometricalElement.h"
//BRepcase
#include "CATIMfBRep.h"

//Mathematics
#include "CATMathPoint.h"
#include "CATMathPointf.h"

//KnowledgeInterfaces
#include "CATICkeParm.h"

//VisualizationBase Fw
#include "CATRep.h"
#include "CATGraphicAttributeSet.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"            // To query the Combined Curve feature about its inputs
#include "CATLISTV_CATISpecObject.h"

// Include System
#include "CATUnicodeString.h"

#include "iostream.h"

#include <TIE_CATI3DGeoVisu.h>
TIE_CATI3DGeoVisu(CAAEMmrMultiMeasureVisu);

CATImplementClass(CAAEMmrMultiMeasureVisu, DataExtension, CATExtIVisu, CAAMmrMultiMeasure);
// To declare that CAAMmrMultiMeasure implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary :
//
// CAAMmrMultiMeasure   CATI3DGeoVisu   libCAAMmrMultiMeasureAndMeasureSet

CAAEMmrMultiMeasureVisu::CAAEMmrMultiMeasureVisu()
{
}

CAAEMmrMultiMeasureVisu::~CAAEMmrMultiMeasureVisu()
{
}

CATRep *CAAEMmrMultiMeasureVisu::BuildRep()
{ 
	cout <<" CAAEMmrMultiMeasureVisu::BuildRep()" << endl;

  CAT3DBagRep  * BagRep = new CAT3DBagRep ();
  CAT3DAnnotationTextGP * pAnnotationText  = NULL;
  CAT3DAnnotationTextGP * pAnnotationText2 = NULL;

  CAAIMmrMultiMeasure* pMmrMultiMeasure = NULL;

  HRESULT rc = QueryInterface(IID_CAAIMmrMultiMeasure, (void**) & pMmrMultiMeasure);
  if (SUCCEEDED(rc) && pMmrMultiMeasure != NULL)
  {
    CATISpecObject* pInputFeature = NULL;

    rc = pMmrMultiMeasure -> GetGeomFeature (&pInputFeature);

    if(SUCCEEDED(rc) && pInputFeature != NULL)
    {
      CATICkeParm_var spLengthParm;
      CATICkeParm_var spAreaParm;
      CATICkeParm_var spVolumeParm;
    
	  pMmrMultiMeasure->GetLengthParameter(spLengthParm); 
	  pMmrMultiMeasure->GetWetAreaParameter(spAreaParm);
	  pMmrMultiMeasure->GetVolumeParameter(spVolumeParm);
      
      if(!!spLengthParm && !!spAreaParm && !!spVolumeParm)
      {
        CATIGeometricalElement* pGeometricalElementOnInputFeature = NULL;
        rc = pInputFeature -> QueryInterface(IID_CATIGeometricalElement, (void**) & pGeometricalElementOnInputFeature );
        
        if(FAILED(rc) || pGeometricalElementOnInputFeature == NULL) // BRepCase or Error on Feature Instance
        {
          // pGeomFeature is a BRep Feature
          CATIMfBRep *pMfBRep = NULL;
          rc = pInputFeature -> QueryInterface(IID_CATIMfBRep, (void**) &pMfBRep);
          if ( SUCCEEDED(rc) && pMfBRep != NULL) 
          {
            // In BRepCase we choose to retrieve the MasterSupport to define TextBox Params
            CATISpecObject_var hSupportOfBRep = pMfBRep -> GetMasterSupport();
            
            rc = hSupportOfBRep -> QueryInterface(IID_CATIGeometricalElement, (void**) & pGeometricalElementOnInputFeature );
            
            pMfBRep -> Release();
            pMfBRep = NULL;
          }
          else
            //error on feature
            return BagRep;
        }
        
        if(SUCCEEDED(rc) && pGeometricalElementOnInputFeature != NULL) //Retrieves Geometrical Element
        {
          CATMathPoint BoundingBoxGravityCenter;
          CATMathPoint LowerPoint;
          CATMathPoint HigherPoint;

          CATUnicodeString StringValue("");

          pGeometricalElementOnInputFeature -> GetCharacteristicPoints(BoundingBoxGravityCenter, LowerPoint, HigherPoint);
          if (!!spLengthParm && (spLengthParm -> Value())-> AsReal() != NULL)
          {
            StringValue.Append(spLengthParm -> RelativeName(this));
            StringValue.Append(" = ");
            StringValue.Append(spLengthParm -> Show());
            CATMathPointf CenterPoint (BoundingBoxGravityCenter);
            pAnnotationText = new CAT3DAnnotationTextGP (CenterPoint , StringValue, BASE_CENTER, 0.f,1);
          }
          else
          {
            if (!!spAreaParm && (spAreaParm -> Value())-> AsReal() != NULL)
            {
              StringValue.Append(spAreaParm -> RelativeName(this));
              StringValue.Append(" = ");
              StringValue.Append(spAreaParm -> Show());
              CATMathPointf CenterPoint (BoundingBoxGravityCenter);
              pAnnotationText = new CAT3DAnnotationTextGP (CenterPoint , StringValue, TOP_CENTER, 0.f, 1);
            }
            if (!!spVolumeParm && (spVolumeParm -> Value())-> AsReal() != NULL)
            {
              StringValue = (spVolumeParm -> RelativeName(this));
              StringValue.Append(" = ");
              StringValue.Append(spVolumeParm -> Show());
              CATMathPointf CenterPoint (BoundingBoxGravityCenter);
              pAnnotationText2 = new CAT3DAnnotationTextGP (CenterPoint , StringValue, BOTTOM_CENTER, 0.f, 1);
            }
          }
          pGeometricalElementOnInputFeature -> Release();
          pGeometricalElementOnInputFeature = NULL;

          CATGraphicAttributeSet textGrAttrs;
          int textColorRed = 113, textColorGreen=0, textColorBlue = 202;
          textGrAttrs.SetColorRGBA(textColorRed, textColorGreen, textColorBlue);
          textGrAttrs.SetColor(TRUECOLOR);

          CAT3DCustomRep* customRep = new CAT3DCustomRep();

          if( customRep && pAnnotationText)
          {
            customRep->AddGP(pAnnotationText, textGrAttrs);
            if(pAnnotationText2 != NULL)
              customRep->AddGP(pAnnotationText2, textGrAttrs);
            
            customRep->SetShowFreeMode(0);
          }
          BagRep -> AddChild (*customRep);
        }
      }
      pMmrMultiMeasure -> Release();
      pMmrMultiMeasure = NULL;
    }
 }
  return BagRep ;
}

