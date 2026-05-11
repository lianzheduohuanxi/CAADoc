// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrMeasureSetVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAV5V6ExtMmrMeasureSet
//
// Note : CAAEV5V6ExtMmrMeasureSetVisu is the same use case as CAAEMmrMeasureSetVisu. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//======================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrMeasureSetVisu.h" 
        
// VisualizationFoundation Framework for V6
// VisualizationBase Framework for V5
#include "CATRep.h"
#include "CAT3DBagRep.h"
#include "CATModelIdentificator.h"

// VisualizationController Framework for V6
// Visualization Framework for V5
#include "CATVisManager.h"

// CATMecModExtendItf Framework
#include "CATIMmiMechanicalSet.h"

// CATMecModLiveUseItf
#include  "CATLISTV_CATIMmiMechanicalFeature.h" 


#include <TIE_CATI3DGeoVisu.h>
TIE_CATI3DGeoVisu(CAAEV5V6ExtMmrMeasureSetVisu);

CATImplementClass(CAAEV5V6ExtMmrMeasureSetVisu, DataExtension, CATExtIVisu, CAAV5V6ExtMmrMeasureSet);

// To declare that CAAV5V6ExtMmrMeasureSet implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary :
//
// CAAV5V6ExtMmrMeasureSet     CATI3DGeoVisu   libCAAV5V6ExtMmrMultiMeasure


CAAEV5V6ExtMmrMeasureSetVisu::CAAEV5V6ExtMmrMeasureSetVisu()
{
}

CAAEV5V6ExtMmrMeasureSetVisu::~CAAEV5V6ExtMmrMeasureSetVisu()
{
}

CATRep *CAAEV5V6ExtMmrMeasureSetVisu::BuildRep()
{ 
  HRESULT rc = S_OK;

  CAT3DBagRep * bag = new CAT3DBagRep();
  
  CATIMmiMechanicalSet_var hMechanicalSet = this;
  if (hMechanicalSet != NULL_var)
  {
    CATListValCATIMmiMechanicalFeature_var FeatureList;
	rc = hMechanicalSet->GetMechanicalFeatures(FeatureList);

	if (SUCCEEDED(rc))
	{
	  int size = FeatureList.Size();

	  CATBaseUnknown *g = NULL;
      CATVisManager *vm = CATVisManager::GetVisManager();

	  for(int i=1; i<=size; i++)
      {
        g = FeatureList[i];
  
        CATModelIdentificator ident(g);
        CATRep * rep = vm->BuildRep(ident);
        if (NULL != rep)
        {
          bag->AddChild( *((CAT3DRep*)rep) );
        }
      }
	}
 }
  
  return bag;
  
}
