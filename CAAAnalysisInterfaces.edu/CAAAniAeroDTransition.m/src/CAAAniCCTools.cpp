// COPYRIGHT Dassault Systemes 2000
//===================================================================
#include "CAAAniCCTools.h"      // Local Include
#include "CATISamAnalysisSet.h"           // Access to the AnalysisSet Feature
#include "CATISamBasicComponent.h"        // Access to Attribute of AnalysisSet Feature
#include "CATAnalysisExplicitModel.h"     // field model data
#include "CATAnalysisExplicitRulesData.h" // field model data
#include "CATAnalysisExplicitSet.h"
#include "CATSamCharacVersion.h"
#include "CATAnalysisExplicitTypes.h"
#include "CATAnalysisCharacCollector.h"
#include "CATSamCharacVersion.h"
#include "CATSamDimension.h"
#include "CATAnalysisExplicitTopology.h"
//
#include "CATILinkableObject.h"            
#include "CATDocument.h"                  
#include "CATSamDocumentTools.h"

//=============================================================================
// Implements CATICharacCollector::GetCharacCollector
//=============================================================================
HRESULT CAAAniCCTools::ComputeCC(CATISamAnalysisSet_var& ispSet,CATAnalysisExplicitSet & ExpParent)
{
	HRESULT                    hr = S_OK ;
  CATSamCharacVersion        _Versions;
	CATSamPhysicalType         PhysTypeT;
	int                        NbEntities, oMathematicalDimension,oRepeat ;
	char                       *EntityFlags = NULL ;
	void                       *Values , **ValuePointers = NULL ;
	CATSamDimension            *Dimensions = NULL, **DimensionPointers = NULL ;
  CATString   _Units, _Positions ("NODE" );
  CATSamMathType             oMathematicalType;
	CATSamValue                oValueType;
	CATAnalysisCharacCollector *CharacCollector = NULL ;
  CATSamExplicitPtr ExpPtr = NULL;
  const CATAnalysisExplicitTopology*pTopo = NULL;

	if (NULL_var == ispSet || NULL_exp == ExpParent) return E_FAIL ;
  CATAnalysisExplicitModel * _Model = ExpParent.GetModel();
	if (NULL == _Model) return E_FAIL ;

  const CATAnalysisExplicitRulesData *pRulesData = _Model -> GetRulesData();
	if (NULL ==pRulesData) return E_FAIL ;

  pRulesData -> GetPhysicalTypeNumber("TRANSLATIONAL_VELOCITY",PhysTypeT);
  pRulesData -> GetPhysicalTypeMathematicalInfo(PhysTypeT,oMathematicalType,oValueType,oMathematicalDimension,oRepeat);

  _Versions.ValueType     = oValueType ;
  _Versions.MathType      = oMathematicalType ;
  _Versions.MathDimension = oMathematicalDimension ;
  _Versions.RefFrame      = CATSamRefFrameNone ;
  _Versions.Category      = CATSamValueNode ;

  // Don't exist: create a new one:
	CharacCollector = new CATAnalysisCharacCollector;
	CharacCollector -> SetContext(ExpParent,TRUE);
  const char * CharUnit = NULL;

  pRulesData -> GetPhysicalTypeUnit(PhysTypeT,CharUnit);
  _Units = CharUnit;
  CharacCollector -> SetDefinition(PhysTypeT,_Units,_Versions,_Positions,-1);
// one value per node in the modele
  _Model -> GetTopology(pTopo);
	if (pTopo == NULL)  return E_FAIL;
  pTopo -> GetNbNodes(NbEntities);
  pTopo->Release();   pTopo = NULL;
  CharacCollector -> SetNbEntities(NbEntities) ;
	EntityFlags = new char[NbEntities] ;  // array of EntityFlags
	memset(EntityFlags, 1, NbEntities) ;  // set them all == 1
	CharacCollector->SetEntities(EntityFlags) ; // A pointer to the table of tags of the entities.

  // Dimensions of the values
  int nbRepeat[1]={1};
	Dimensions = new CATSamDimension (1, 1, 1, nbRepeat, CATSamValueReal, CATSamMathTypeVector, 3) ;
  CharacCollector -> SetDimensions(1, Dimensions, DimensionPointers) ;
	delete Dimensions ;

// Access to file for values extraction
	float *_Fvalues;
	_Fvalues = new float [3*NbEntities];
	Values = _Fvalues;
	ReadFile(ispSet,EntityFlags,NbEntities	,_Fvalues);

  CharacCollector -> SetValues(3*NbEntities,3*sizeof(float)*NbEntities,Values, ValuePointers) ;
  CharacCollector -> SetStreamable(TRUE);

	delete [] _Fvalues;
  if (EntityFlags) delete [] EntityFlags;
  return S_OK;
}
//=============================================================================================================
void CAAAniCCTools::ReadFile(CATISamAnalysisSet_var& ispSet,char* iName,int iNb	,float *iFvalues)
{
	char buffer [132];
	CATUnicodeString Path="";
	if (NULL_var == ispSet) return;

  CATISamBasicComponent_var spComponent;
  CATBaseUnknown_var        spVarOnDoc;
  ispSet -> GetNamedBasicComponent("ANIFileLink",spComponent);
  if (!! spComponent)
  {
    spComponent -> GetBaseUnknownValue(spVarOnDoc,"ExternDoc");
    if (!!spVarOnDoc)
    {
 		  CATILinkableObject * piLinkable = NULL;
      
      spVarOnDoc -> QueryInterface(IID_CATILinkableObject,(void **)& piLinkable);
      if (piLinkable)
      {
        CATDocument * pDoc = piLinkable -> GetDocument ();

		    if (pDoc) CATSamDocumentTools::GetFileStorage(pDoc,Path);
        piLinkable -> Release(); piLinkable = NULL;
      }
    }
  }
  if (Path.GetLengthInChar() == 0) return;

	FILE * stream = fopen (Path.ConvertToChar(),"r");
	for( int i=0;i<3*iNb;i++)
	{
		iFvalues[i] = 0.f;
	}
	if (stream)
	{
		while (fgets (buffer,132,stream))
		{
			int num;
			double Vx , Vy , Vz;
			sscanf ( buffer ,"%d %lf %lf %lf",&num,&Vx,&Vy,&Vz);
			iFvalues[3*(num-1)  ] = (float) (Vx);
			iFvalues[3*(num-1)+1] = (float) (Vy);
			iFvalues[3*(num-1)+2] = (float) (Vz);
		}
		fclose (stream);
	}
}
