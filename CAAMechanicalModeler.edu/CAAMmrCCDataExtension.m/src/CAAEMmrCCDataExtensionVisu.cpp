// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrCCDataExtensionVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrCCDataExtension
//======================================================================================

#include "CAAEMmrCCDataExtensionVisu.h" 

#include "CAAIMmrCCDataExtension.h"

//VisualizationBase Fw
#include "CAT3DBagRep.h"
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DCustomRep.h"
#include "CATGraphicAttributeSet.h"
#include "CATRep.h"
#include "CATI3DGeoVisu.h"

//Geometry & Topo
#include "CATBody.h"
#include "CATIGeometricalElement.h"

//Mathematics
#include "CATMathPoint.h"
#include "CATMathPointf.h"

#include "CATICkeParm.h"

#include "CATEventSubscriber.h"
#include "CATModify.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATUnicodeString.h"


#include <TIE_CATI3DGeoVisu.h>
TIE_CATI3DGeoVisu(CAAEMmrCCDataExtensionVisu);

CATImplementClass(CAAEMmrCCDataExtensionVisu, DataExtension, CATBaseUnknown, CAAMmrCCDataExtension);

CAAEMmrCCDataExtensionVisu::CAAEMmrCCDataExtensionVisu()
{
}

CAAEMmrCCDataExtensionVisu::~CAAEMmrCCDataExtensionVisu()
{
}

CATRep *CAAEMmrCCDataExtensionVisu::BuildRep()
{ 
  //This impl consists in creating a 3DRepresentation associated with the Extension.
  //As our Extension is like a measure, computing and retrieving the length of its base feature,
  //Let's build a 3DRep with an annotation valuated with the computed legth !

  // 1] Creates a 3DBagRep
  //    All representations build during BuildRep will be aggregated under the 3DBagRep created
  //    At the end of BuildRep, we will return this BagRep, sort of "Representation Set"

  CAT3DBagRep  * BagRep = new CAT3DBagRep ();
  CAT3DAnnotationTextGP * pAnnotationText = NULL;

  CAAIMmrCCDataExtension* pCAAMmrCCDataExtension = NULL;
  
  HRESULT rc = QueryInterface(IID_CAAIMmrCCDataExtension, (void**) & pCAAMmrCCDataExtension);
  if (SUCCEEDED(rc) && pCAAMmrCCDataExtension != NULL)
  {
    CATISpecObject* pBaseFeature = NULL;
    CATICkeParm_var spValuatedParm;

    // 2] Retrieves the Base Feature to known where "stick" the 3DRep
    pCAAMmrCCDataExtension -> GetGeomFeature (&pBaseFeature);

    // 3] Retrieves the valuated Parm
    pCAAMmrCCDataExtension -> GetValuatedParam (spValuatedParm);

    if(pBaseFeature != NULL)
    {
      CATIGeometricalElement* pGeometricalElementOnBaseFeature = NULL;
      rc = pBaseFeature -> QueryInterface(IID_CATIGeometricalElement, (void**) & pGeometricalElementOnBaseFeature);
      if(SUCCEEDED(rc) && pGeometricalElementOnBaseFeature != NULL) //Retrieves Geometrical Element
      {
        // 4 ] Defines the inputs of CAT3DAnnotationTextGP
        CATMathPoint BoundingBoxGravityCenter;
        CATMathPoint LowerPoint;
        CATMathPoint HigherPoint;

        pGeometricalElementOnBaseFeature -> GetCharacteristicPoints(BoundingBoxGravityCenter, LowerPoint, HigherPoint);
        
        if (!!spValuatedParm)
        {
          // 5 ] Defines Value displayed by CAT3DAnnotationTextGP
          CATMathPointf CenterPoint (BoundingBoxGravityCenter);
          const CATUnicodeString StringValue = spValuatedParm -> Show();
          
          // 6 ] Creates the CAT3DAnnotationTextGP
          pAnnotationText = new CAT3DAnnotationTextGP (CenterPoint , StringValue);
        }
        pGeometricalElementOnBaseFeature -> Release();
        pGeometricalElementOnBaseFeature = NULL;
      }
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

  if( customRep && pAnnotationText)
    customRep->AddGP(pAnnotationText, textGrAttrs);

  // 8 ] Aggregates 3DRep to CAT3DBagRep
  BagRep -> AddChild (*customRep);

  // 9 ] Returns the BagRep.
  return BagRep ;
}

int CAAEMmrCCDataExtensionVisu::ModifyRep ( const CATNotification & iInfo )
{
  // Change color on Modifying event
  CATI3DGeoVisu_var h3DVisu = this;
  CATISpecObject_var hSOonThis = this;
  if(!!h3DVisu && !!hSOonThis)
  {
    if(!hSOonThis->IsUpToDate())
    {
      CATRep *pRep = h3DVisu -> GetRep();
      if(pRep != NULL)
      { 
        list<CATRep> * pListOfChildren = pRep -> GetChildren();
        if(pListOfChildren !=NULL && pListOfChildren -> length()!= NULL)
          (*pListOfChildren)[0] -> SetColor (RED);
        return 1;
      }
    }
  }

  // Don't forget to continue implementation with default behaviors (CATExtIVisu::ModifyRep(iInfo));
  return CATExtIVisu::ModifyRep(iInfo);
}
