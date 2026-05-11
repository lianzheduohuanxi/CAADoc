// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//  This Use Case illustrates how to explore a CATAnalysis document in order 
//  to create an exported file. The format of this file is not DASSAULT SYSTEMES 
//  proprietary and could be change at any time. 
//=============================================================================
//  Main Methods:
//  CAAAniSelectPhysics Scan the physical information that can be producted by the
//                      analysis set and select some CharacCollector for dumping.
//
//  Input Argument:
//  --------------
//  CATAnalysisExplicitModel  *iExplicitModel : Pointer on the CATAnalysisExplicitModel.
//  CATISamAnalysisSet_var    *ihFeatureSet   : Handler on the CATISamAnalysisSet that manage the mesh.
//
//  Return Errors:
//  -------------
//  1 - HRESULT S_OK is every thing is OK E_FAIL Otherwhise.
//
//=============================================================================
#include "CATString.h"                      // Management of CATString
#include "CAAAniExport.h"                   // Local includes of the sample
// Analysis Interfaces 
# include "CATISamAnalysisSet.h"            // CATISamAnalysisSet
#include "CATISamExplicit.h"               //  Get implementation of Sam Explicit
#include "CATICharacCollector.h"           //  Get implementation of CATICharacCollector
// Field model interfaces
#include "CATAnalysisExplicitModel.h"      //  Access to the physical types.
#include "CATAnalysisCharacCollector.h"    //  Charac-collector object
#include "CATAnalysisExplicitSet.h"        //  Method on CATAnalysisExplicitSet
#include "CATAnalysisExplicitRulesData.h"  //  Method on CATAnalysisExplicitRulesData
//=============================================================================
HRESULT CAAAniSelectPhysics(FILE*  File,CATAnalysisExplicitModel *ExplicitModel,
							CATISamAnalysisSet_var hFeatureSet)
{
	HRESULT hr = S_OK;
	CATUnicodeString           aUnicodeString;
	CATListValCATUnicodeString aListOfString;
	char                         Ligne[512];
  const CATSamPhysicalType    *PhyTypes        = NULL ;
  const CATSamCharacVersion   *oVersions       = NULL;
  const CATString             *oPositions      = NULL;
	const CATString             *Units           = NULL ;
  CATICharacCollector_var     theCollector;
	CATISamExplicit_var         SamExp      ;
	const CATAnalysisCharacCollector  *CharacCollector = NULL;
	const CATAnalysisCharacCollector  *GpePerElementCollector = NULL;
	const CATAnalysisCharacCollector ** ListCollector  = NULL;
	const char*                 oString          = NULL;
	int i,j,k,oNbVersions,oNbPositions,Nbcollect,MaxCollect,ipos=0;
	CATSamPhysicalType          PhyTypSet,PhyTypNumb,PhyTypUser ;
	CATAnalysisExplicitSet      ExpSet;
  CATString   PositionsREF [5] = {"NONE","ELEMENT","NODE","NODE-ELEMENT-FACE-EDGE","NONE-NODE-ELEMENT-NODE_OF_ELEMENT"};

  // Retrieve RulesData
  if (NULL == ExplicitModel)  return E_FAIL;
  const CATAnalysisExplicitRulesData *pRulesData = NULL;
  pRulesData = ExplicitModel->GetRulesData();
  if (NULL == pRulesData)  return E_FAIL;

	int NbPhyTypes = 0;
//=============================================================================
	Nbcollect  = 0;
	MaxCollect = 100;
	CATSamPhysicalType _MESH,_PROPERTIES,_RESTRAINTS,_LOADS,_MASSES,_ELEMENTS,_SENSORS;
	pRulesData -> GetPhysicalTypeNumber("MESH",_MESH);
	pRulesData -> GetPhysicalTypeNumber("PROPERTIES",_PROPERTIES);
	pRulesData -> GetPhysicalTypeNumber("ELEMENTS",_ELEMENTS);
	pRulesData -> GetPhysicalTypeNumber("RESTRAINTS",_RESTRAINTS);
	pRulesData -> GetPhysicalTypeNumber("LOADS",_LOADS);
	pRulesData -> GetPhysicalTypeNumber("MASSES",_MASSES);
	pRulesData -> GetPhysicalTypeNumber("SENSORS",_SENSORS);
	pRulesData -> GetPhysicalTypeNumber("PHYSICAL_TYPE",PhyTypNumb);
	pRulesData -> GetPhysicalTypeNumber("USER_NUMBER",PhyTypUser);
//=============================================================================
// Retreive the CATISamExplicit implementation of the set.
//=============================================================================
	SamExp     = hFeatureSet;
	if (SamExp == NULL_var) return E_NOINTERFACE ;
//=============================================================================
// Extract from CATISamExplicit the Set in the fied model and its physical type
//=============================================================================
	hr = SamExp -> GetExplicitObject(ExpSet);
	if (ExpSet == NULL_exp) return S_OK; // No physical type on this set 
	if (! SUCCEEDED(hr)) return E_FAIL;
	hr = ExpSet.GetPhysicalType(PhyTypSet);
	if (! SUCCEEDED(hr)) return E_FAIL;
	pRulesData -> GetPhysicalTypeName(PhyTypSet,oString);
	cout << "Physical Types of the set "<<PhyTypSet << oString << endl;
	CATString StringTest(oString);
	cout << "strncmp Types of the set "<<StringTest.FindPosition("solution") << endl;
	if (StringTest.FindPosition("solution") > 0) return S_OK; // ipos = 4;

	// Specific export for meshing informations:
	if (PhyTypSet == _MESH)
	{
		CAAAniExportMesh(File,hFeatureSet,ExplicitModel);
		return S_OK;
	}
// If no Physical type is defined the CATICharacCollector will not be implemented
	else if (!PhyTypSet) return S_OK;
	if (PhyTypSet==_SENSORS)  return S_OK;
//=============================================================================
// Ipos will allow to preselect positions inside the PositionsREF array
//=============================================================================
	if (PhyTypSet==_RESTRAINTS) ipos = 2;
	if (PhyTypSet==_LOADS || PhyTypSet==_MASSES) ipos = 3;
  
//=============================================================================
// Retreive the CATICharacCollector implementation of the set.
//=============================================================================
  theCollector = hFeatureSet;
	if (theCollector == NULL_var) return E_NOINTERFACE ;
//=============================================================================
// What are the physical type that can be retreive from a set
//=============================================================================
	hr = theCollector->GetAvailablePhysicalTypes(NbPhyTypes,PhyTypes,Units);
	cout << "NbPhyTypes "<<NbPhyTypes << endl;
	if (NbPhyTypes == 0) 
	{
		sprintf (Ligne,"// Empty Set !  \n");
		fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
		return S_OK;
	}
	if (!SUCCEEDED(hr)) return E_FAIL;
//=============================================================================
// Allocate an array for storing the selected CATAnalysisCharacCollector Objects
//=============================================================================
	CATAnalysisCharacCollector** TempCollector = new CATAnalysisCharacCollector* [MaxCollect];
	ListCollector = (const CATAnalysisCharacCollector**)TempCollector;
//=============================================================================
//  Keep positions in the array ListCollector for specific physical types:
//  ListCollector[0] = List of physical type per gpe or property / Materials ....
//  ListCollector[1] = List of user Number per gpe or property / Materials ....
//  GpePerElementCollector = List of sequential Number of the group per element
//	GpePerElementCollector -> GetValues(Values) Values[element[i]] = Gpe Number
//=============================================================================
	if (!ipos) Nbcollect = 2 ;
	ListCollector[0] = ListCollector[1] = NULL;

    for (i=0 ; i<NbPhyTypes ; i++)
    {
		pRulesData -> GetPhysicalTypeName(PhyTypes[i],oString);
		if (PhyTypes[i]==_ELEMENTS && ipos == 4 ) continue;
		oNbVersions = 0;
		hr = theCollector->GetAvailableVersions(PhyTypes[i],oNbVersions,oVersions);
		if (! SUCCEEDED(hr)) goto error;
		for (j=0 ; j<oNbVersions ; j++)
		{
			oNbPositions = 0;
	        hr = theCollector->GetAvailablePositions(PhyTypes[i],oVersions[j],oNbPositions,oPositions);
			if (!SUCCEEDED(hr)) goto error;
			

			for (k=0 ; k<oNbPositions ; k++)
			{
// Dump the content if needed
				cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<endl;
				cout << "Physical Types "<< oString << " Units:" << *Units <<
				 " Position : " << (const char *) oPositions[k] << endl;
				cout << " Version "<< endl;
				oVersions[j].Dump(&aListOfString,5);
			    for (int il = 1 ; il <= aListOfString.Size() ; il++) 
				{
					aUnicodeString = aListOfString[il] ;
					cout << aUnicodeString.ConvertToChar() << endl;
				}
				aListOfString.RemoveAll();
				CharacCollector = NULL;
// List of physical type per gpe or property / Materials ....
				if (PhyTypes[i] == PhyTypNumb )
				{
					if (ipos) break;
					if ( oPositions[k] == "NONE" && oVersions[j].Category > CATSamValueElement && oVersions[j].Category < CATSamValueSet) 
					{
						hr = theCollector->GetCharacCollector(PhyTypes[i], oVersions[j],oPositions[k],NULL,CharacCollector);
						if (! SUCCEEDED(hr)) goto error;
						ListCollector[0] = CharacCollector;
						cout << "                  Ok pos 0 "<< endl;
//						CharacCollector -> Dump(&aListOfString,2);
//					    for (int il = 1 ; il <= aListOfString.Size() ; il++) 
//						{
//							aUnicodeString = aListOfString[il] ;
//							cout << aUnicodeString.ConvertToChar() << endl;
//						}
//						aListOfString.RemoveAll();
					}
					else break;
				}
// List of user Number per gpe or property / Materials ....
				else if(PhyTypes[i] == PhyTypUser )
				{
					if (ipos) break;
					if (oPositions[k] == "NONE" && oVersions[j].Category > CATSamValueElement && oVersions[j].Category < CATSamValueSet)
					{
						hr = theCollector->GetCharacCollector(PhyTypes[i], oVersions[j],oPositions[k],NULL,CharacCollector);
						if (! SUCCEEDED(hr)) goto error;
						ListCollector[1] = CharacCollector;
						cout << "                  Ok pos 1 "<< endl;
//						CharacCollector -> Dump(&aListOfString,2);
//					    for (int il = 1 ; il <= aListOfString.Size() ; il++) 
//						{
//							aUnicodeString = aListOfString[il] ;
//							cout << aUnicodeString.ConvertToChar() << endl;
//						}
//						aListOfString.RemoveAll();
					}
					else break;
				}
// Number of groupe apply on node / element / face of element / edge of element...
				else if(PhyTypes[i] == PhyTypSet)
				{
					if (oPositions[k] == "NONE") break;

					if (PhyTypSet == _PROPERTIES && oPositions[k] == "ELEMENT"  &&
						oVersions[j].Category == CATSamValueElement &&
					    oVersions[j].ValueType  == CATSamValueInteger)
					{	
						hr = theCollector->GetCharacCollector(PhyTypes[i], 
							oVersions[j],oPositions[k],NULL,CharacCollector);
						if (! SUCCEEDED(hr)) goto error;
						GpePerElementCollector = CharacCollector;
						cout << "                  Ok GpePerElementCollector "<< endl;
//						CharacCollector -> Dump(&aListOfString,2);
//					    for (int il = 1 ; il <= aListOfString.Size() ; il++) 
//						{
//							aUnicodeString = aListOfString[il] ;
//							cout << aUnicodeString.ConvertToChar() << endl;
//						}
//						aListOfString.RemoveAll();

					}
					else break;
				}
				else
				{
					cout << "looking for "<<oPositions[k]<<" in: "<< PositionsREF[ipos] <<" "<<
						PositionsREF[ipos].FindPosition(oPositions[k]) << endl;
					if ( oVersions[j].ValueType < CATSamValuePointer &&
		 				 PositionsREF[ipos].FindPosition(oPositions[k]) > -1)
					{
						if ((ipos > 0 && ipos <= 3 && oVersions[j].Category > CATSamValueElement && oVersions[j].Category < CATSamValueSet) ||
							(ipos && oVersions[j].RefFrame==CATSamRefFrameLocal)) break;
//
						if (ipos == 3 &&  oVersions[j].MathType == CATSamMathTypeScalar &&
							              oVersions[j].RefFrame != CATSamRefFrameNone) break;
						if (ipos == 3 &&  oVersions[j].MathType == CATSamMathTypeVector &&
							              oVersions[j].RefFrame != CATSamRefFrameGlobal) break;
						if (ipos == 4 &&  oVersions[j].RefFrame == CATSamRefFrameLocal) break;

						cout << "Storage at position "<< Nbcollect << endl;
						hr = theCollector->GetCharacCollector(PhyTypes[i], oVersions[j],oPositions[k],NULL,CharacCollector);
						if (! SUCCEEDED(hr)) goto error;
						ListCollector[Nbcollect] = CharacCollector;
//						CharacCollector -> Dump(&aListOfString,2);
//					    for (int il = 1 ; il <= aListOfString.Size() ; il++) 
//						{
//							aUnicodeString = aListOfString[il] ;
//							cout << aUnicodeString.ConvertToChar() << endl;
//						}
//						aListOfString.RemoveAll();
						Nbcollect ++;
					}
					else break;
				}
			}
		}
	}
	if (Nbcollect)
	{
		if (ipos) 
// Generate informations per groupe
			CAAAniDumpByFEentity(File,ExplicitModel,Nbcollect,ListCollector);
		else 
// Generate informations per support (Node/Element)
			CAAAniDumpByGroup(File,ExplicitModel,Nbcollect,ListCollector,GpePerElementCollector);
	}
//=============================================================================
//  Release the required objects.
	if (ListCollector)
	{
    if (GpePerElementCollector) {
      ((CATAnalysisCharacCollector*)GpePerElementCollector) -> RequestDelayedDestruction();
      GpePerElementCollector -> Release();
    }
    for (i=0 ; i<Nbcollect ; i++) {
      if (ListCollector[i]) {
        ((CATAnalysisCharacCollector*)ListCollector[i]) -> RequestDelayedDestruction(); 
        ListCollector[i] -> Release(); 
      }
    }
		delete [] ListCollector ; ListCollector = NULL;
	}
	return S_OK;
//=============================================================================
// In case of errors Release the required objects.
CATSampleError
	( if (ListCollector)
	{
		if (GpePerElementCollector) {
      ((CATAnalysisCharacCollector*)GpePerElementCollector) -> RequestDelayedDestruction();
      GpePerElementCollector -> Release(); 
    }
    for (i=0 ; i<Nbcollect ; i++) {
      if (ListCollector[i]) {
        ((CATAnalysisCharacCollector*)ListCollector[i]) -> RequestDelayedDestruction(); 
        ListCollector[i] -> Release(); 
      }
    }
		delete [] ListCollector ;	ListCollector = NULL;
	}	)
//=============================================================================
}

