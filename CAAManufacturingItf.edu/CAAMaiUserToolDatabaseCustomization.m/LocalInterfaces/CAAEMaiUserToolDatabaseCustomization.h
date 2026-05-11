// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAEMaiUserToolDatabaseCustomization:
//
// Sample code for : Manufacturing Modeler
// Mission         : Customize the Tool Database access
//
// ===================================================================

#ifndef CAAEMaiUserToolDatabaseCustomization_h
#define CAAEMaiUserToolDatabaseCustomization_h

// System Framework
#include "CATBaseUnknown.h"   // for inheritance
#include "CATListOfInt.h"     // for List of Integers
#include "CATListOfDouble.h"  // for List of Doubles
#include "CATListOfCATUnicodeString.h" // for List of CATUnicodeString
#include "CATUnicodeString.h"  // for CATUnicodeString management
#include "CATIDocId.h"    // for CATIDocId management

// Motherinterface of CATIMfgResourceQueryUserDatabase
#include "CATIMfgResourceQuery.h"
#include "CATBaseUnknown.h"

class CAAEMaiUserToolDatabaseCustomization : public CATBaseUnknown
{
  CATDeclareClass;

  public: 
    
	// Constructor and Destructor
	//------------------------------------------------
	CAAEMaiUserToolDatabaseCustomization();
	virtual ~CAAEMaiUserToolDatabaseCustomization();
	
	// This method allows to make connection to the database
	//----------------------------------------------------------------------
	virtual HRESULT InitConnection ();
	
	// This method allows to reset connection to the database
	//----------------------------------------------------------------------
	virtual HRESULT ResetConnection ();
	
	// This method allows to define the names that will be displayed
	// in the Tool Selection panel combo "Look in"
	//----------------------------------------------------------------------
	virtual HRESULT GetNamesToDisplay  (CATListOfCATUnicodeString &oListNames);
	
	// This method allows to initialize the database query
	//----------------------------------------------------------------------
	virtual HRESULT Initialize (const CATUnicodeString &iName, 
								              const CATUnicodeString &iType);


/**
 * Defines the type of resource on which we want to add constraints.
 * Only used for Tool Assembly queries
 * @param iResourceType
 *     The type of resource (MfgTool or MfgInsert).
 * @param iFamily
 *     The family of the resource (MfgEndMillTool, MfgRoundInsert...), defined in 
 *     CATMfgToolConstant & CATMfgInsertConstant
 */
   virtual HRESULT AddSubComponentTypeConstraint (CATIMfgResourceQuery::MfgResourceQueryType  iResourceType,
                                                  const CATUnicodeString                     &iFamily);

	// This method allows to add a constraint on the name of the tool to search
	// A like condition will be defined 
	// (ex: search tool where name like %ID%)
	//----------------------------------------------------------------------
	virtual HRESULT AddNameLikeConstraint  (const CATUnicodeString   &iValue,
                                          CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
	// This method allows to add a constraint on the nominal diameter of the tool
	// to search. A between condition will be defined 
	// (ex: search tool where nominal diameter between 10.0mm and 15.0mm)
	//----------------------------------------------------------------------
	virtual HRESULT AddDiameterBetweenConstraint (const double             &iMinValue,
												                        const double             &iMaxValue,
										                            const CATUnicodeString   &iUnit,
                                                CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
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
	//----------------------------------------------------------------------
	virtual HRESULT AddConstraint (const CATUnicodeString   &iAttribute, 
								                 const int                &iOperator,
								                 const int                &iValue,
                                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
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
	//----------------------------------------------------------------------
	virtual HRESULT AddConstraint (const CATUnicodeString   &iAttribute, 
								                 const int                &iOperator,
								                 const double             &iValue,
								                 const CATUnicodeString   &iUnit,
                                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
	// This method allows to add a constraint on the string type parameters
	// on the tool to search. 
	// Legal values for iOperator:
    // 0:Equal
    // 10:Like
	// (ex: search tool where name == "Identifier")
	//----------------------------------------------------------------------
	virtual HRESULT AddConstraint  (const CATUnicodeString   &iAttribute, 
								                  const int                &iOperator,
								                  const CATUnicodeString   &iValue,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
	// This method allows to add several constraints 
	// on the tool to search. 
	// Defines several constraints for query on a specific attribute.
	// (ex: search tool where nominal diameter == 10.0mm or nominal diameter == 15.00mm)
	//----------------------------------------------------------------------
	virtual HRESULT AddConstraints (const CATUnicodeString            &iAttribute, 
									                const CATUnicodeString            &iUnit,
								                  const int                         &iTypeValue,
                                  const CATListOfInt                &iOperators,
                                  const CATListOfInt                &iIntValues,
                                  const CATListOfDouble             &iDblValues,
                                  const CATListOfCATUnicodeString   &iStrValues,
                                  const CATListOfInt                &iLogLinks,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
	// This method allows to execute the query in database
	//----------------------------------------------------------------------
	virtual HRESULT Execute();
	
	// This method allows to read the number of tools matching the query
	//----------------------------------------------------------------------
	virtual HRESULT GetResultSize(int &NbElem,
                                CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
	
	// This method allows to read the description of a given record in database
	//----------------------------------------------------------------------
	virtual HRESULT GetDescription (const int                  &iElem, 
					 			                  CATListOfCATUnicodeString  &oAttributes, 
                                  CATListOfInt               &oTypeValues, 
                                  CATListOfInt               &oNbValues,
                                  CATListOfInt               &oIntValues,
                                  CATListOfDouble            &DblValues, 
                                  CATListOfCATUnicodeString  &StrValues,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);

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
   virtual HRESULT GetComponentNameAndIndex(const int        &iNumElem,
                                            CATUnicodeString &oCompName,
                                            int              &oCompNumElem,
                                            CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);

	// This method allows to read the representaion of a given tool in database
	//-------------------------------------------------------------------------
	virtual HRESULT GetRepresentation  (const int         &iElem,
  								                    CATUnicodeString  &oPathName,
                                      CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);

	// This method allows to read the representaion of a given tool in database
	//-------------------------------------------------------------------------
	virtual HRESULT GetRepresentation  (const int         &iElem,
  								                    CATIDocId         *&oDocId,
																			CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);

/**
 * Retrieves the correctors information.
 * @param iElem
 *     The object number 
 * @param oListPoints       : List of type point as CATUnicodeString (Ex: P1, ..., P9) 
 * @param oListNumber       : List of corrector number as Integer 
 * @param oListLengthNumber : List length Corrector number as Integer 
 * @param oListRadiusNumber : List radius Corrector number as Integer 
 * @param oListDiameter     : List tool diameter for this point as Double 
 */
   virtual HRESULT GetCorrectors (const int                 &iElem,
                                  CATListOfCATUnicodeString &oListPoints,
                                  CATListOfInt              &oListNumber,
                                  CATListOfInt              &oListLengthNumber,
                                  CATListOfInt              &oListRadiusNumber,
                                  CATListOfDouble           &oListDiameter,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);

/**
 * Instanciate the resource in the document.
 * @param iElem
 *     The object number 
 * @param hBUResources
 *     The handler on the created resource
 * @param piDoc
 *     The CATDocument where the resource has to be instantiated
 */
   virtual HRESULT InstantiateResourceInDocument (const int          &iElem,
                                                  CATBaseUnknown_var &hBUResources,
                                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent,
                                                  CATDocument *piDoc = NULL);

  private:
	
	// Copy constructor
	//-------------------------------------------------------------------------
  CAAEMaiUserToolDatabaseCustomization(const CAAEMaiUserToolDatabaseCustomization &iObjectToCopy);
    
	
	CATUnicodeString _Type, _Name;
};

#endif


