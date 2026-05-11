#include "CAAAniDefinitionSolution.h"
 
#include "CATISamDefineSolution.h"
#include "CATISamAnalysisSet.h"
#include "CATISamSolution.h"
#include "CATISamAnalysisCase.h"
#include "CATString.h"

CATImplementClass(CAAAniDefinitionSolution,CacheExtension,CATISamDefineSolution,AeroDynamicSet);
CATImplementBOA(CATISamDefineSolution,CAAAniDefinitionSolution);
 
//-----------------------------------------------------------------------------
// CAAAniDefinitionSolution : constructor
//-----------------------------------------------------------------------------
CAAAniDefinitionSolution::CAAAniDefinitionSolution():CATISamDefineSolution()
{
}
//-----------------------------------------------------------------------------
// CAAAniDefinitionSolution : destructor
//-----------------------------------------------------------------------------
CAAAniDefinitionSolution::~CAAAniDefinitionSolution()
{
}
//-----------------------------------------------------------------------------
// Implements CATISamDefineSolution::GetSetsForDefinition
//-----------------------------------------------------------------------------
HRESULT CAAAniDefinitionSolution::GetSetsForDefinition (int & oNbDefineSets , 
                                                   CATSamDefineSet * & oDefineSets)
{

  oNbDefineSets = 0;
  oDefineSets = NULL;

/*  oNbDefineSets = 1;
  oDefineSets = new CATSamDefineSet [oNbDefineSets];

  oDefineSets[0]._FeatureType = CATUnicodeString("RestraintSet");
  oDefineSets[0]._Optionnal    = 0; // Mandatory
  oDefineSets[0]._TypeInstance  = 2; // can be referenced (existing set) or created
*/


  return S_OK;
}
//====================================================================================================
//-----------------------------------------------------------------------------
// Implements CATISamDefineSolution::DefineDefaultSensors
//-----------------------------------------------------------------------------
int CAAAniDefinitionSolution::DefineDefaultSensors(const CATBoolean iCreateSensor, const CATISamAnalysisSet* iNewSolution)
{
// Some Aditionnals to do after the feature instantiation
  if (iNewSolution) {
    CATISamSolution_var spSolution((CATBaseUnknown*)iNewSolution);
    if (!! spSolution ) {
      CATISamAnalysisCase* piCase = NULL;
      spSolution -> GetCase(piCase);
      if (piCase){
       piCase -> SetSolver(CATString("AeroSolver"));
       piCase -> Release(); piCase = NULL;
      }
    }
  }

  return (0);
}


