// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniADCharacCollector.cpp
// Provide implementation to interface CATICharacCollector
//
// The Solution will have the Late type AeroDynamicSet
// as defined in the CAAAniCAtalog generator.
// Read the result inside the output file for visualization.
//===================================================================
#include "CAAAniADCharacCollector.h"      // Local Include
#include "CATISamExplicit.h"              // Access to field model from the Feature
#include "CATISamAnalysisSet.h"           // Access to the AnalysisSet Feature
#include "CATISamBasicComponent.h"        // Access to Attribute of AnalysisSet Feature
#include "CATAnalysisExplicitModel.h"     // field model data
#include "CATAnalysisExplicitRulesData.h" // field model data
#include "CATAnalysisExplicitTopology.h"
#include "CATILinkableObject.h"            
#include "CATDocument.h"                  
#include "CATSamDocumentTools.h"

CATImplementClass( CAAAniADCharacCollector,
                   DataExtension,
                   CATECharacCollector,
                   AeroDynamicSet );
 
//=============================================================================
// CAAAniADCharacCollector : constructor
//=============================================================================
CAAAniADCharacCollector::CAAAniADCharacCollector():
    CATECharacCollector()
{
	_Context            = NULL_exp;
	_Model              = NULL;
	_PhysicalTypes      = NULL;
	_Units              = NULL;
	_Positions          = NULL;
	_VersionsT          = NULL;
	_VersionsG          = NULL;
	_NumberOfOccurences = 0;
	_CurrentOccurence   = -1 ;
	_NbPhysicalType     = 0;
  _NbVersionsT        = 0;
  _NbVersionsG        = 0;
  _NbPositions        = 0;
}

//=============================================================================
// CAAAniADCharacCollector : destructor
//=============================================================================
CAAAniADCharacCollector::~CAAAniADCharacCollector()
{
	if (_PhysicalTypes) delete [] _PhysicalTypes ;
	if (_Units)         delete [] _Units ;
	if (_Positions)     delete [] _Positions ;
	if (_VersionsT)     delete [] _VersionsT ;
	if (_VersionsG)     delete [] _VersionsG ;
  _Context       = NULL_exp;
	_Model         = NULL;
	_PhysicalTypes = NULL;
	_Units         = NULL;
	_Positions     = NULL;
	_VersionsT     = NULL;
	_VersionsG     = NULL;
	_NumberOfOccurences = 0;
	_CurrentOccurence   = -1 ;
	_NbPhysicalType     = 0;
  _NbVersionsT        = 0;
  _NbVersionsG        = 0;
  _NbPositions        = 0;
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICharacCollector.h"
TIE_CATICharacCollector( CAAAniADCharacCollector);
//=============================================================================
// Implements CATICharacCollector::GetAvailablePhysicalTypes
//=============================================================================
HRESULT CAAAniADCharacCollector::GetAvailablePhysicalTypes (int &  oNumber , 
														  const CATSamPhysicalType* &  oPhysicalTypes , 
														  const CATString* &  oUnits)
{
	oNumber = 0;
	if (!SUCCEEDED(Init())) return E_FAIL ;

	oNumber        = _NbPhysicalType;
	if (_NbPhysicalType) oPhysicalTypes = _PhysicalTypes;
	if (_NbPhysicalType) oUnits         = _Units;
   return S_OK;
}
//=============================================================================
// Implements CATICharacCollector::GetAvailableVersions
//=============================================================================
HRESULT CAAAniADCharacCollector::GetAvailableVersions (const CATSamPhysicalType  iPhysicalType , 
													 int &  oNumber , 
													 const CATSamCharacVersion* &  oVersions)
{
	oNumber = 0;
	if (!SUCCEEDED(Init())) return E_FAIL ;
  if (_NbPhysicalType !=2) return E_FAIL ;

  if (iPhysicalType == _PhysicalTypes[0])
  {
	  oNumber = _NbVersionsT ;
	  if (_NbVersionsT) oVersions = _VersionsT;
  }
  if (iPhysicalType == _PhysicalTypes[1])
  {
	  oNumber = _NbVersionsG ;
	  if (_NbVersionsG) oVersions = _VersionsG;
  }
	return S_OK;

}
//=============================================================================
// Implements CATICharacCollector::GetAvailablePositions
//=============================================================================
HRESULT CAAAniADCharacCollector::GetAvailablePositions (const CATSamPhysicalType  iPhysicalType , 
													  const CATSamCharacVersion &  iVersion ,
													  int &  oNumber , 
													  const CATString* &  oPositions)
{
	oNumber = 0;
	if (!SUCCEEDED(Init())) return E_FAIL ;
	oNumber = _NbPositions ;
	if (_NbPositions) oPositions = _Positions;
	return S_OK;
}
//=============================================================================
// Implements CATICharacCollector::GetNumberOfOccurrences
//=============================================================================
HRESULT CAAAniADCharacCollector::GetNumberOfOccurrences (int &  oNumberOfOccurrences)
{
	oNumberOfOccurrences = 0;
	return S_OK;
}
//=============================================================================
// Implements CATICharacCollector::GetCurrentOccurrence
//=============================================================================
HRESULT CAAAniADCharacCollector::GetCurrentOccurrence (int &  oOccurrenceNumber)
{
	oOccurrenceNumber = -1;
	return S_OK;
}
//=============================================================================
// Implements CATICharacCollector::SetCurrentOccurrence
//=============================================================================
HRESULT CAAAniADCharacCollector::SetCurrentOccurrence (const int  iOccurrenceNumber)
{
  if (iOccurrenceNumber == -1)
    return S_OK; 
  else
    return E_FAIL; 
}
//=============================================================================
// Implements CATICharacCollector::GetCharacCollector
//=============================================================================
HRESULT CAAAniADCharacCollector::GetCharacCollector (const CATSamPhysicalType  iPhysicalType , 
												   const CATSamCharacVersion &  iVersion , 
												   const CATString &  iPosition , 
												   const char*  const  iEntityFlags  ,
												   const CATAnalysisCharacCollector* &  oCharacCollector , 
												   const CATBoolean  iCollectValues,
                           const CATSamPhysicalType iEntiyPhysicalTypeToCollect)
{
	HRESULT                     hr = S_OK ;
	int                         NbEntities; 
	char                        *EntityFlags = NULL ;
	const char                  *CharUnit = NULL;
	void                        *Values , **ValuePointers = NULL ;
	CATSamDimension             *Dimensions = NULL, **DimensionPointers = NULL ;

	CATAnalysisCharacCollector  *CharacCollector = NULL ;
	CATString                    Unit ;
    const CATAnalysisExplicitTopology *pTopo = NULL;
//
	if (!SUCCEEDED(Init())) return E_FAIL ;
	if (NULL == _Model) return E_FAIL ;
  // retrieve RulesData
  const CATAnalysisExplicitRulesData *pRulesData = _Model -> GetRulesData();
	if (NULL ==pRulesData) return E_FAIL ;

// If the Collector already exist's :
	_Context.FindCharacCollector(iPhysicalType,iVersion,iPosition,
		                         _CurrentOccurence,CharacCollector);
	if (CharacCollector) 
	{
// Exist OK Increase its life counter and return it.
		CharacCollector -> AddRef();
		oCharacCollector = CharacCollector;
		return S_OK;
	}
// Don't exist: create a new one:
	CharacCollector = new CATAnalysisCharacCollector;
	CharacCollector -> SetContext(_Context,TRUE);
  pRulesData->GetPhysicalTypeUnit(iPhysicalType, CharUnit) ;
  CharacCollector->SetDefinition(iPhysicalType, CharUnit, iVersion, iPosition, _CurrentOccurence) ;
// one value per node in the modele
  _Model -> GetTopology(pTopo);
	if (pTopo == NULL)  return E_FAIL;
  pTopo -> GetNbNodes(NbEntities);
  pTopo->Release();   pTopo = NULL;
  CharacCollector->SetNbEntities(NbEntities) ;
// Information for all the modele or for a restriction
	if (iEntityFlags == NULL)
	{
		EntityFlags = new char[NbEntities] ;  // array of EntityFlags
		memset(EntityFlags, 1, NbEntities) ;  // set them all == 1
		CharacCollector->SetEntities(EntityFlags) ; // A pointer to the table of tags of the entities.
	}
	else
		CharacCollector->SetEntities(iEntityFlags);

  // Dimensions of the values
  int nbRepeat[1]={1};
	Dimensions = new CATSamDimension (1, 1, 1, nbRepeat, CATSamValueReal, CATSamMathTypeVector, 3) ;
    CharacCollector -> SetDimensions(1, Dimensions, DimensionPointers) ;
	delete Dimensions ;

// Access to file for values extraction
	float *_Fvalues;
	_Fvalues = new float [3*NbEntities];
	Values = _Fvalues;
	ReadFile(EntityFlags,NbEntities	,_Fvalues);

// on multiplie par 2 les valeurs pour la version "NOMINAL"
  if (iVersion.SubType  =="NOMINAL")
  {
    for (int ie=0; ie<3*NbEntities; ie++)
      _Fvalues[ie]=_Fvalues[ie]*2;
  }
  // on multiplie par 3 les valeurs pour la version "GEN1"
  if (iVersion.SubType  =="GEN1")
  {
    for (int ie=0; ie<3*NbEntities; ie++)
      _Fvalues[ie]=_Fvalues[ie]*3;
  }

  CharacCollector -> SetValues(3*NbEntities,3*sizeof(float)*NbEntities,Values, ValuePointers) ;
	delete [] _Fvalues;
  if (EntityFlags) delete [] EntityFlags;
// return the CharacCollector
	CharacCollector -> AddRef();
	oCharacCollector = CharacCollector;
  return S_OK;
}
//=============================================================================
// Implements CATICharacCollector::Update
//=============================================================================
HRESULT CAAAniADCharacCollector::Update (CATBoolean iFullUpdate)
{
	if (_PhysicalTypes) delete [] _PhysicalTypes ;
	if (_Units)         delete [] _Units ;
	if (_Positions)     delete [] _Positions ;
	if (_VersionsT)     delete [] _VersionsT ;
	if (_VersionsG)     delete [] _VersionsG ;
 	_Context       = NULL_exp;
	_Model         = NULL;
	_PhysicalTypes = NULL;
	_Units         = NULL;
	_Positions     = NULL;
	_VersionsT     = NULL;
	_VersionsG     = NULL;
	_NumberOfOccurences =0;
	_CurrentOccurence=  -1 ;
	_NbPhysicalType     =0;
  _NbVersionsT        = 0;
  _NbVersionsG        = 0;
  _NbPositions        = 0;

	return S_OK;
}
//=============================================================================
// Internal method to generate the Data members 
// CATICharacCollector::Init
//=============================================================================
HRESULT CAAAniADCharacCollector::Init()
{
	HRESULT	hr=S_OK;
// This step id Ok if the DataMember _Context is valuated.
	if (_Context != NULL_exp) return hr;
// 
	_NbPhysicalType = 0 ;
  _NbVersionsT    = 0 ;
  _NbVersionsG    = 0 ;
  _NbPositions    = 0 ;
// Initialize the Context with the Explicit Object associated.
	CATISamExplicit*  piExplicit=NULL;
	hr = QueryInterface(IID_CATISamExplicit,(void**)&piExplicit);
	if (piExplicit == NULL) return E_NOINTERFACE ;

	hr= piExplicit->GetExplicitObject(_Context);
	piExplicit-> Release(); 
	piExplicit=NULL;
	if (! SUCCEEDED(hr)) return E_FAIL ;
// Get a protection if the set is not yet in the field model.
	if (_Context == NULL_exp) return hr;
// retrieve the Explcit Model
	_Model = _Context.GetModel();
  if (NULL == _Model) return E_FAIL ;

  // retrieve RulesData
  const CATAnalysisExplicitRulesData *pRulesData = NULL;
  pRulesData = _Model->GetRulesData();
	if (NULL == pRulesData) return E_FAIL ;

// No occurences for this solution
	_CurrentOccurence = -1;
  if (! SUCCEEDED(hr)) return E_FAIL ;
// Allocate the arrays for following array's
	_PhysicalTypes    = new CATSamPhysicalType[2];
	_Units            = new CATString[2];
	_VersionsT        = new CATSamCharacVersion[2];
	_VersionsG        = new CATSamCharacVersion[1];
	_Positions	      = new CATString[1];

// retrieve the CATSamPhysicalType for TRANSLATIONAL_VELOCITY
	CATSamPhysicalType PhysTypeT;
	hr = pRulesData -> GetPhysicalTypeNumber("TRANSLATIONAL_VELOCITY",PhysTypeT);

	_PhysicalTypes[0] = PhysTypeT;
	_Units[0]         = " ";

// retrieve the CATSamPhysicalType for GENERIC_CHARACTERISTIC
	CATSamPhysicalType PhysTypeG;
	hr = pRulesData -> GetPhysicalTypeNumber("GENERIC_CHARACTERISTIC",PhysTypeG);

	_PhysicalTypes[1] = PhysTypeG;
	_Units[1]         = " ";


  CATSamMathType oMathematicalType;
	CATSamValue oValueType;
	int oMathematicalDimension,oRepeat ;
// Initialize the version According to the dictionnary
	hr = pRulesData -> GetPhysicalTypeMathematicalInfo(PhysTypeT,
         oMathematicalType,oValueType,oMathematicalDimension,oRepeat);

    _VersionsT[0].ValueType     = oValueType ;
    _VersionsT[0].MathType      = oMathematicalType ;
    _VersionsT[0].MathDimension = oMathematicalDimension ;
    _VersionsT[0].RefFrame      = CATSamRefFrameNone ;
    _VersionsT[0].Category      = CATSamValueNode ;

    _VersionsT[1].ValueType     = oValueType ;
    _VersionsT[1].MathType      = oMathematicalType ;
    _VersionsT[1].MathDimension = oMathematicalDimension ;
    _VersionsT[1].RefFrame      = CATSamRefFrameNone ;
    _VersionsT[1].Category      = CATSamValueNode ;
    _VersionsT[1].SubType       = "NOMINAL";

// Initialize the version for the GENERIC_CHARACTERISTIC
    _VersionsG[0].ValueType     = _VersionsT[0].ValueType ;
    _VersionsG[0].MathType      = _VersionsT[0].MathType ;
    _VersionsG[0].MathDimension = _VersionsT[0].MathDimension ;
    _VersionsG[0].RefFrame      = _VersionsT[0].RefFrame ;
    _VersionsG[0].Category      = _VersionsT[0].Category ;
    _VersionsG[0].SubType       = "GEN1";

	_Positions[0] = "NODE" ;
	_NbPhysicalType = 2;
  _NbPositions = 1;
  _NbVersionsT = 2;
  _NbVersionsG = 1;
	return S_OK;
}
//=============================================================================
// Internal method to access the file and return the velocity.
// CATICharacCollector::ReadFile
//=============================================================================
void CAAAniADCharacCollector::ReadFile(char* iName,int iNb	,float *iFvalues)
{
	char buffer [132];

  // Open the file
	CATUnicodeString Path="";

// Retrieve the Path from the Analysis Set Object
  CATBaseUnknown_var spVarOnDoc ;
	CATISamAnalysisSet *piAnalysisSet = NULL;
	QueryInterface(IID_CATISamAnalysisSet,(void **)&piAnalysisSet); 
	if (NULL != piAnalysisSet)
	{
    CATISamBasicComponent_var spComponent;
    piAnalysisSet -> GetNamedBasicComponent("ANIFileLink",spComponent);
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
    piAnalysisSet -> Release();  piAnalysisSet = NULL;
	}
   
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
