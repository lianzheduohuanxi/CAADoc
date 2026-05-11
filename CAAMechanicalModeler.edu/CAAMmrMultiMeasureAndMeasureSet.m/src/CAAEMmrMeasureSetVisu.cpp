// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrMultiMeasureSetVisu.cpp
// Provide implementation to interface
//      CATI3DGeoVisu i.e. CATIVisu for CAAMmrMeasureSet
//======================================================================================
#include "CAAEMmrMeasureSetVisu.h" 

// Visualization Base & Visualization Framework
#include "CATRep.h"
#include "CAT3DBagRep.h"
#include "CATVisManager.h"
#include "CATModelIdentificator.h"

// ObjectSpecsModeler framework
#include "CATIDescendants.h"
#include "CATLISTV_CATISpecObject.h" 

#include <TIE_CATI3DGeoVisu.h>
TIE_CATI3DGeoVisu(CAAEMmrMeasureSetVisu);

CATImplementClass(CAAEMmrMeasureSetVisu, DataExtension, CATExtIVisu, CAAMmrMeasureSet);

// To declare that CAAMmrMeasureSet implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary :
//
// CAAMmrMeasureSet     CATI3DGeoVisu   libCAAMmrMultiMeasureAndMeasureSet


CAAEMmrMeasureSetVisu::CAAEMmrMeasureSetVisu()
{
}

CAAEMmrMeasureSetVisu::~CAAEMmrMeasureSetVisu()
{
}

CATRep *CAAEMmrMeasureSetVisu::BuildRep()
{ 

  // The CAAMmrMeasureSet's Rep is composed of all aggregated Measure's 3DRep.
  CAT3DBagRep * bag = new CAT3DBagRep();
  
  CATIDescendants_var hDescendant = this;
  if(hDescendant != NULL_var)
  {
    CATListValCATISpecObject_var hDescendantsChildren = NULL;
    hDescendant -> GetDirectChildren ("CATI3DGeoVisu", hDescendantsChildren);
  
    int size = hDescendantsChildren.Size();
  
    CATBaseUnknown *g = NULL ;
    CATVisManager *vm = CATVisManager::GetVisManager();

    for(int i = 1; i <= size; i++)
    {
      g = hDescendantsChildren[i];
  
      CATModelIdentificator ident(g);
      CATRep * rep = vm->BuildRep(ident);
      if (NULL != rep)
      {
        bag->AddChild( *((CAT3DRep*)rep) );
      }
    }
  }
  return bag;
 
}
