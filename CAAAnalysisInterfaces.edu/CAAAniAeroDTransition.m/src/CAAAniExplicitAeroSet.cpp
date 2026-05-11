#include "CAAAniExplicitAeroSet.h"

// CATAnalysisBase prereq
#include "CATAnalysisExplicitListUsr.h"
#include "CATAnalysisExplicitSet.h"
#include "CATAnalysisExplicitModel.h"
#include "CATAnalysisExplicitTypes.h"
#include "CATString.h"
#include "CATISamExplicit.h"
#include "CATISamAnalysisSet.h"
#include "CAAAniCCTools.h"
#include "CATISpecObject.h"
#include "CATLib.h"            

#include <iostream.h>

CATBeginImplementClass(CAAAniExplicitAeroSet,CacheExtension,CATISamExplicitation,STRUCTURAL_AeroDynamicSet);
CATEndImplementClass(CAAAniExplicitAeroSet);

CATImplementBOA (CATISamExplicitation, CAAAniExplicitAeroSet);

//-----------------------------------------------------------------------------
// CAAAniExplicitAeroSet : constructor
//-----------------------------------------------------------------------------
CAAAniExplicitAeroSet::CAAAniExplicitAeroSet():
CATISamExplicitation()
{
}

//-----------------------------------------------------------------------------
// CAAAniExplicitAeroSet : destructor
//-----------------------------------------------------------------------------
CAAAniExplicitAeroSet::~CAAAniExplicitAeroSet()
{
}

//-----------------------------------------------------------------------------
// Implements CATISamExplicit::Explicit
//-----------------------------------------------------------------------------
HRESULT CAAAniExplicitAeroSet::TranslateToFieldModel(CATISpecObject* iFeatToTranslate, 
                                                  CATISamAnalysisModel* iFEMModel, 
                                                  CATAnalysisExplicitListUsr& iOldExplObjects, 
                                                  CATAnalysisExplicitListUsr& oNewExplObjects)
{

  HRESULT                            HR = S_OK ;
  CATISamExplicit                    *piExplicit = NULL ;
  CATAnalysisExplicitChild           Child;
  CATAnalysisExplicitSet             OldSet,  NewSet ;
  CATAnalysisExplicitList            Children ;
  CATAnalysisExplicitListUsr         ContainingData ;
  CATAnalysisExplicitModel           *ExplicitModel = NULL ;
  CATSamPhysicalType                 PhysicalType;
  CATISamAnalysisSet_var             spSet(iFeatToTranslate);

  if(!iFeatToTranslate) goto error;

// Retrieve CATISamExplicit interface for GetContainingData and UpdateExplicitList methods
  iFeatToTranslate -> QueryInterface (IID_CATISamExplicit,(void**)& piExplicit);
  if (piExplicit == NULL) goto error;

// Retrieve physcal type of the previous version 
  OldSet = *(iOldExplObjects.First()) ;
  if (OldSet == NULL_exp) goto error;
  ExplicitModel = OldSet.GetModel();
  if (ExplicitModel == NULL) goto error;

  OldSet.GetPhysicalType(PhysicalType);

  if (!SUCCEEDED(ContainingData.CreateList(ExplicitModel))) goto error;
  if (!SUCCEEDED(piExplicit -> GetContainingData(iOldExplObjects, ContainingData))) goto error;

  if (!SUCCEEDED(NewSet.CreateSet(ExplicitModel,PhysicalType))) goto error;

  oNewExplObjects += NewSet;

  OldSet.GetChildrenList(Children);
  Child = *(Children.First());
  while ( Child != NULL_exp )
  {
    CATSamDataType DataType = Child.GetType();
    if (DataType == CATSamDataTypeSet || DataType == CATSamDataTypeEntity) NewSet.AddChild(Child);
    Child = *(Children.Next()) ;
  }
  
  if (!SUCCEEDED(piExplicit -> UpdateExplicitList(iOldExplObjects, ContainingData, oNewExplObjects)))  goto error;

  piExplicit -> Release(); piExplicit = NULL;
  if (ContainingData != NULL_exp) ContainingData.Delete() ;

  cout << "Insert here the applicative software you need for updating the feature "<< endl;
// Following method is not necessary. 
// Objective is to show that CharacCollector can be created in the Field model during CATISamExplicitation implementation.
  if (CATGetEnv("CAAAniCreateCCInExplicit"))  CAAAniCCTools::ComputeCC(spSet,NewSet);


  return S_OK;

error:
    if (piExplicit)    piExplicit -> Release(); piExplicit = NULL;
    if (ContainingData != NULL_exp) ContainingData.Delete() ;
  return E_FAIL;
}

