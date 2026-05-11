// COPYRIGHT DASSAULT SYSTEMES 2000
//==============================================================================================
//
// CAAMaiUserToolDatabaseCustomization:
//
// Sample code for : Manufacturing Modeler
// Mission         : Customize the Tool Database access
//
//
// Type            : Interactive functionality
//
// Illustrates     : 1- use of manufacturing interfaces 
//                   2- Customization of tool database access
//
// How to run it   : Set up the run time environment 
//					 In the file CAAManuturingItf.edu.dico, decomment the following line  
//					 CATMfgResourceQuery  CATIMfgResourceQueryUserDatabase   libCAAMaiUserToolDatabaseCustomization
//                   
//                   Launch a CATIA V5 session 
//                   Open the CAAMaiUserToolDatabaseCustomization.CATPart file located in: Windows InstallRootDirectory\CAAManufacturingItf.edu\CNext\resources\graphic\ 
//					 
//					 Start Prismatic Machining Workbench
//                   Invoke the Import/List Tools command for the Tool bar
//					 Select the "My_Tool_Database" value in the "Look In" combo
//
//
//==============================================================================================CATICkeUnit
#include "CAAEMaiUserToolDatabaseCustomization.h"

// Manufacturing Interfaces
#include "CATMfgResourceConstant.h" // for Resources parameter names
#include "CATMfgToolConstant.h"     // for Tools parameter names
#include "CATIDocId.h"						  // for CATIDocId management 

// KnowledgeInterfaces
#include "CATCkeGlobalFunctions.h"
#include "CATICkeUnit.h"
#include "CATICkeMagnitude.h"
#include "CATIParmDictionary.h"

//-----------------------------------------------------------------------------
// Supported Interfaces
//-----------------------------------------------------------------------------
//	In the file CAAManuturingItf.edu.dico, the following line must be available  
//	CATMfgResourceQuery  CATIMfgResourceQueryUserDatabase   libCAAMaiUserToolDatabaseCustomization
#include "TIE_CATIMfgResourceQueryUserDatabase.h"
TIE_CATIMfgResourceQueryUserDatabase(CAAEMaiUserToolDatabaseCustomization);
CATImplementClass(CAAEMaiUserToolDatabaseCustomization,
                  DataExtension,                  
                  CATBaseUnknown,
                  CATMfgResourceQuery);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEMaiUserToolDatabaseCustomization::CAAEMaiUserToolDatabaseCustomization()
:CATBaseUnknown(),
_Type(""),
_Name("")
{
}
//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEMaiUserToolDatabaseCustomization::~CAAEMaiUserToolDatabaseCustomization()
{
	_Type = "";
	_Name = "";
}
//-----------------------------------------------------------------------------
// InitConnection
// This method allows to make connection to the database
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::InitConnection() 
{
	HRESULT Result = S_OK;

	//-----------------------------------------------------------------------------
	// Database Connection
	//-----------------------------------------------------------------------------
	// Call to Database connection Service
	
	return Result;
}
//-----------------------------------------------------------------------------
// ResetConnection
// This method allows to reset connection to the database
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::ResetConnection() 
{
	HRESULT Result = S_OK;

	//-----------------------------------------------------------------------------
	// Reset Database Connection
	//-----------------------------------------------------------------------------
	// Call to Database de-connection Service

	return Result;
}
//-----------------------------------------------------------------------------
// GetNamesToDisplay
// This method allows to define the names that will be displayed
// in the Tool Selection panel combo "Look in"
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::GetNamesToDisplay 
										(CATListOfCATUnicodeString &oListNames)
{
	oListNames.RemoveAll();
	oListNames.Append ("My Tool Database");
	return S_OK;
}
//-----------------------------------------------------------------------------
// Initialize
// This method allows to initialize the database query
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::Initialize (const CATUnicodeString &iName,
														  const CATUnicodeString &iType)
{
	HRESULT Res = S_OK;
	_Name = iName;
	_Type = iType;
	return Res;
}

/**
 * Defines the type of resource on which we want to add constraints.
 * Only used for Tool Assembly queries
 * @param iResourceType
 *     The type of resource (MfgTool or MfgInsert).
 * @param iFamily
 *     The family of the resource (MfgEndMillTool, MfgRoundInsert...), defined in 
 *     CATMfgToolConstant & CATMfgInsertConstant
 */
HRESULT CAAEMaiUserToolDatabaseCustomization::AddSubComponentTypeConstraint (CATIMfgResourceQuery::MfgResourceQueryType  iResourceType,
                                                                             const CATUnicodeString                &iFamily) {
  return E_FAIL;
}
//-----------------------------------------------------------------------------
// AddNameLikeConstraint
// This method allows to add a constraint on the name of the tool to search
// A like condition will be defined 
// (ex: search tool where name like %ID%)
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::AddNameLikeConstraint (const CATUnicodeString   &iValue,
                                                                     CATIMfgResourceQuery::MfgResourceQueryType iResourceType) 
{
	HRESULT Res = S_OK;

	// Define the type of value in for query constraint (string)
	//----------------------------------------------------------
	int TypeValue= 3;

	// Define the operator and logical link for constraint
	//----------------------------------------------------
	CATListOfInt Operators, LogLinks;

	// Operator 'Like'
	Operators.Append (10);
	
	// Logical link 'Like'
	LogLinks.Append (0);
	
	// Define the values for constraint
	CATListOfInt IntValues;
	CATListOfDouble DblValues;

	CATListOfCATUnicodeString StrValues;
	StrValues.Append (iValue);
	
	// Add the list of constraints
	//----------------------------------------------------
	CATUnicodeString Unit;
	Res = AddConstraints (MfgName, Unit, TypeValue, Operators, 
						  IntValues, DblValues, StrValues, LogLinks);

	return Res;
}
//-----------------------------------------------------------------------------
// AddDiameterBetweenConstraint
// This method allows to add a constraint on the nominal diameter of the tool
// to search. A between condition will be defined 
// (ex: search tool where nominal diameter between 10.0mm and 15.0mm)
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::AddDiameterBetweenConstraint  
											(const double             &iMinValue,
											 const double             &iMaxValue,
									     const CATUnicodeString   &iUnit,
                       CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	
	HRESULT Res=S_OK;
	
	// Define the type of value in for query constraint (double)
	//----------------------------------------------------------
	int TypeValue= 2;
	
	// Define the operator and logical link for constraint
	//----------------------------------------------------
	CATListOfInt Operators, LogLinks;

	// Operator 'Greater or Equal'
	Operators.Append (5);
	// Operator 'Less or Equal'
	Operators.Append (4);

	// Logical links 'And'
	LogLinks.Append (0);
	LogLinks.Append (0);
	
	// Define the values for constraint
	CATListOfInt IntValues;

	CATListOfDouble DblValues;
	DblValues.Append (iMinValue);
	DblValues.Append (iMaxValue);
	
	CATListOfCATUnicodeString StrValues;
		
	// Add the list of constraints
	//----------------------------------------------------
	Res = AddConstraints (MfgNominalDiameter, iUnit, TypeValue, Operators, 
						  IntValues, DblValues, StrValues, LogLinks);

	return Res;
}
//-----------------------------------------------------------------------------
// AddConstraint
// This method allows to add a constraint on the integer type parameters
// on the tool to search. 
// Legal values for iOperator:
// 0:Equal
// 1:Not Equal
// 2:Less
// 3:Greater
// 4:Less or Equal
// 5:Greater Or Equal
// 6:Not Less
// 7:Not Greater
// (ex: search tool where number of flutes = 5)
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::AddConstraint  
								(const CATUnicodeString  &iAttribute, 
								 const int               &iOperator,
								 const int               &iValue,
                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	// Define the type of value in for query constraint (integer)
	//----------------------------------------------------------
	int TypeValue= 1;
	
	// Define the operator and logical link for constraint
	//----------------------------------------------------
	CATListOfInt Operators, LogLinks;
	Operators.Append (iOperator);
	LogLinks.Append (0);
	
	// Define the value for constraint
	//----------------------------------------------------
	CATListOfInt IntValues;
	IntValues.Append (iValue);
	
	CATListOfDouble DblValues;
	CATListOfCATUnicodeString StrValues;
	
	// Add the list of constraints
	//----------------------------------------------------
	CATUnicodeString Unit;
	HRESULT Res = AddConstraints (iAttribute, Unit, TypeValue, Operators, 
								  IntValues, DblValues, StrValues, LogLinks);
	return Res;
}
//-----------------------------------------------------------------------------
// AddConstraint
// This method allows to add a constraint on the double type parameters
// on the tool to search. 
// Legal values for iOperator:
// 0:Equal
// 1:Not Equal
// 2:Less
// 3:Greater
// 4:Less or Equal
// 5:Greater Or Equal
// 6:Not Less
// 7:Not Greater
// (ex: search tool where nominal diameter >= 10.00 mm)
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::AddConstraint  
								(const CATUnicodeString  &iAttribute, 
								 const int               &iOperator,
								 const double            &iValue,
								 const CATUnicodeString  &iUnit,
                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	// Define the type of value in for query constraint (double)
	//----------------------------------------------------------
	int TypeValue= 2;

    // Adapt the value regarding to the unit (here we would like to have mm)
    // -------------------------------------
    double internalValue = iValue;

    if (iUnit != "mm")
    {
        // Length type should be converted to mm
        CATIParmDictionary_var hParmDico = CATCkeGlobalFunctions::GetParmDictionary ();
        if (NULL_var != hParmDico)
        {
            CATICkeUnit_var hCkeUnit = hParmDico->FindUnitFromSymbol(iUnit);
            if (NULL_var != hCkeUnit) 
            {
                // Convert the input value to MKS
                double internalMKSValue = hCkeUnit->Convert(iValue);

                CATICkeMagnitude_var hCkeMagnitude = hCkeUnit->GetMagnitude();
                CATICkeType_var hCkeType = hCkeMagnitude;

                // Conversion is only done on length type
                CATICkeType_var hLengthType = hParmDico->GetLengthType();
                if ( NULL_var != hCkeType && hCkeType->IsaKindOf(hLengthType) )
                {
                    // From MKS to target unit : mm
                    internalValue = internalMKSValue * 1000;
                }
            }
        }
    }
	
	// Define the operator and logical link for constraint
	//----------------------------------------------------
	CATListOfInt Operators, LogLinks;
	Operators.Append (iOperator);
	LogLinks.Append (0);
	
	// Define the value for constraint
	//----------------------------------------------------
	CATListOfInt IntValues;

	CATListOfDouble DblValues;
	DblValues.Append (internalValue);
	
	CATListOfCATUnicodeString StrValues;
	
	// Add the list of constraints
	//----------------------------------------------------
	HRESULT Res = AddConstraints (iAttribute, iUnit, TypeValue, Operators, 
								  IntValues, DblValues, StrValues, LogLinks);

	return Res;
}
//-----------------------------------------------------------------------------
// AddConstraint
// This method allows to add a constraint on the string type parameters
// on the tool to search. 
// Legal values for iOperator:
// 0:Equal
// 10:Like
// (ex: search tool where name == "Identifier")
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::AddConstraint  
								(const CATUnicodeString  &iAttribute, 
								 const int               &iOperator,
								 const CATUnicodeString  &iValue,
                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	// Define the type of value in for query constraint (string)
	//----------------------------------------------------------
	int TypeValue= 3;

	// Define the operator and logical link for constraint
	//----------------------------------------------------
	CATListOfInt Operators, LogLinks;
	Operators.Append (iOperator);
	LogLinks.Append (0);
	
	// Define the value for constraint
	//----------------------------------------------------
	CATListOfInt IntValues;
	CATListOfDouble DblValues;
	CATListOfCATUnicodeString StrValues;
	StrValues.Append (iValue);
	
	// Add the list of constraints
	//----------------------------------------------------
	CATUnicodeString Unit;
	HRESULT Res = AddConstraints (iAttribute, Unit, TypeValue, Operators, 
								  IntValues, DblValues, StrValues, LogLinks);

	return Res;
}
//-----------------------------------------------------------------------------
// AddConstraints
// This method allows to add several constraints 
// on the tool to search. 
// Defines several constraints for query on a specific attribute.
// (ex: search tool where nominal diameter == 10.0mm or nominal diameter == 15.00mm)
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::AddConstraints  
								(const CATUnicodeString            &iAttribute, 
								 const CATUnicodeString            &iUnit,
								 const int                         &iTypeValue,
								 const CATListOfInt                &iOperators,
								 const CATListOfInt                &iIntValues,
								 const CATListOfDouble             &iDblValues,
								 const CATListOfCATUnicodeString   &iStrValues,
								 const CATListOfInt                &iLogLinks,
                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	HRESULT Res=S_OK;

	//------------------------------------------------------------
	// Tests on inputs
	//------------------------------------------------------------
	int nbOpe = iOperators.Size();
	int nbLnk = iLogLinks.Size();
	int nbInt = iIntValues.Size();
	int nbDbl = iDblValues.Size();
	int nbStr = iStrValues.Size();

	if (nbOpe != nbLnk) return E_FAIL;
	
	if (iTypeValue != 0 && iTypeValue != 1 && 
		iTypeValue != 2 && iTypeValue != 3) return E_FAIL;

	if ((iTypeValue == 0 || iTypeValue == 1) &&
		(nbInt != nbOpe  || nbInt!= nbLnk)) return E_FAIL;
	
	if (iTypeValue == 2 &&
		(nbDbl != nbOpe  || nbDbl != nbLnk)) return E_FAIL;
	
	if (iTypeValue == 3 &&
		(nbStr != nbOpe  || nbStr != nbLnk)) return E_FAIL;
	
	//------------------------------------------------------------
	// build the query where clause
	//------------------------------------------------------------
	//_WhereClause =;
	
	return Res;
}
//-----------------------------------------------------------------------------
// Execute
// This method allows to execute the query in database
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::Execute()
{
	HRESULT Res=S_OK;
	
	//----------------------------------------------------------------------
	// Execute query
	//----------------------------------------------------------------------
	// Call to the execute function for database
	
	return Res;
}
//-----------------------------------------------------------------------------
// GetResultSize
// This method allows to read the number of tools matching the query
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::GetResultSize (int &oNbElem,
                                                             CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	HRESULT Res=S_OK;

	//----------------------------------------------------------------------
	// Read the output number of elements (5 for this example)
	//----------------------------------------------------------------------
	oNbElem = 5;

	return Res;
}
//-----------------------------------------------------------------------------
// GetDescription
// This method allows to read the description of a given record in database
// (Hard-coded for this example)
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::GetDescription 
										(const int                  &iNumber, 
										 CATListOfCATUnicodeString  &oAttributes, 
										 CATListOfInt               &oTypeValues, 
										 CATListOfInt               &oNbValues,
										 CATListOfInt               &oIntValues,
										 CATListOfDouble            &oDblValues, 
										 CATListOfCATUnicodeString  &oStrValues,
                     CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	HRESULT Res=S_OK;

	oAttributes.RemoveAll();
	oTypeValues.RemoveAll();
	oNbValues.RemoveAll();
	oIntValues.RemoveAll();
	oDblValues.RemoveAll();
	oStrValues.RemoveAll();

	//-----------------------------------------------------------------------------
	// Read the description of elements in database
	//-----------------------------------------------------------------------------
	// For this example the output is hard-coded for Drill Tool
	
	switch (iNumber)
	{
	case 1:
		oAttributes.Append(MfgName);
		oTypeValues.Append(3);
		oNbValues.Append(1);
		oStrValues.Append("My_Tool_01");
		
		oAttributes.Append(MfgNominalDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(10.0);
		
		oAttributes.Append(MfgCuttingAngle);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(120.0);
		
		oAttributes.Append(MfgCuttingLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(30.0);

		oAttributes.Append(MfgLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(50.0);
		
		oAttributes.Append(MfgOverallLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(100.0);

		oAttributes.Append(MfgBodyDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(10.0);
		
		break;
	case 2:
		oAttributes.Append(MfgName);
		oTypeValues.Append(3);
		oNbValues.Append(1);
		oStrValues.Append("My_Tool_02");
		
		oAttributes.Append(MfgNominalDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(12.0);
		
		oAttributes.Append(MfgCuttingAngle);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(120.0);
		
		oAttributes.Append(MfgCuttingLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(30.0);

		oAttributes.Append(MfgLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(50.0);
		
		oAttributes.Append(MfgOverallLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(100.0);

		oAttributes.Append(MfgBodyDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(12.0);

		break;
	case 3:
		oAttributes.Append(MfgName);
		oTypeValues.Append(3);
		oNbValues.Append(1);
		oStrValues.Append("My_Tool_03");
		
		oAttributes.Append(MfgNominalDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(13.0);
		
		oAttributes.Append(MfgCuttingAngle);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(120.0);
		
		oAttributes.Append(MfgCuttingLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(30.0);

		oAttributes.Append(MfgLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(50.0);
		
		oAttributes.Append(MfgOverallLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(100.0);

		oAttributes.Append(MfgBodyDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(13.0);

		break;
	case 4:
		oAttributes.Append(MfgName);
		oTypeValues.Append(3);
		oNbValues.Append(1);
		oStrValues.Append("My_Tool_04");
		
		oAttributes.Append(MfgNominalDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(14.0);
		
		oAttributes.Append(MfgCuttingAngle);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(120.0);
		
		oAttributes.Append(MfgCuttingLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(30.0);

		oAttributes.Append(MfgLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(50.0);
		
		oAttributes.Append(MfgOverallLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(100.0);

		oAttributes.Append(MfgBodyDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(14.0);

		break;
	case 5:
		oAttributes.Append(MfgName);
		oTypeValues.Append(3);
		oNbValues.Append(1);
		oStrValues.Append("My_Tool_05");
		
		oAttributes.Append(MfgNominalDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(15.0);
		
		oAttributes.Append(MfgCuttingAngle);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(120.0);
		
		oAttributes.Append(MfgCuttingLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(30.0);

		oAttributes.Append(MfgLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(50.0);
		
		oAttributes.Append(MfgOverallLength);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(100.0);

		oAttributes.Append(MfgBodyDiameter);
		oTypeValues.Append(2);
		oNbValues.Append(1);
		oDblValues.Append(15.0);

		break;
	}

	return Res;
}
/**
 * Retrieves the Tool or Insert name defined on the tool assembly, and its index.
 * @param iNumElem
 *    integer representating the index of the tool assembly
 * @param oCompName
 *    The component name
 * @param oCompNumElem
 *    integer representing the index of the tool assembly component,
 *    use GetDescription with same MfgResourceQueryType and this index to get its values
 * @param iResourceType
 *    type of resources to retrieve (MfgTool or MfgInsert)
 */
HRESULT CAAEMaiUserToolDatabaseCustomization::GetComponentNameAndIndex(const int        &iNumElem,
                                                                       CATUnicodeString &oCompName,
                                                                       int              &oCompNumElem,
                                                                       CATIMfgResourceQuery::MfgResourceQueryType iResourceType) {
  return E_FAIL;
}

//-----------------------------------------------------------------------------
// GetRepresentation
// This method allows to read the representaion of a given tool in database
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::GetRepresentation  
							     (const int         &iDescriptionNumber,
								  CATUnicodeString  &oPathName,
                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	HRESULT Res=S_OK;
	oPathName="";
	return Res;
}
//-----------------------------------------------------------------------------
// GetRepresentation
// This method allows to read the representaion of a given tool in database
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::GetRepresentation  
							     (const int         &iDescriptionNumber,
										 CATIDocId  *&oDocId,
										 CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
	HRESULT Res=S_OK;
	oDocId=NULL;
	return Res;
}
//-----------------------------------------------------------------------------
// GetCorrectors
// This method allows to read the correctors of a given tool in database
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::GetCorrectors (const int                 &iElem,
                                                             CATListOfCATUnicodeString &oListPoints,
                                                             CATListOfInt              &oListNumber,
                                                             CATListOfInt              &oListLengthNumber,
                                                             CATListOfInt              &oListRadiusNumber,
                                                             CATListOfDouble           &oListDiameter,
                                                             CATIMfgResourceQuery::MfgResourceQueryType iResourceType)
{
  return E_FAIL;
}

//-----------------------------------------------------------------------------
// InstantiateResourceInDocument
// This method allows to instanciate a resource in the document
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserToolDatabaseCustomization::InstantiateResourceInDocument (const int          &iElem,
                                                                             CATBaseUnknown_var &hBUResources,
                                                                             CATIMfgResourceQuery::MfgResourceQueryType iResourceType,
                                                                             CATDocument *piDoc)
{
  return E_FAIL;
}
