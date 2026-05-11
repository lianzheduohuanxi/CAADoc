// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAAPbiUECreate.h
//
// Implement the CATIPDMUECreate interface
//
//===================================================================
//CAA2 Wizard Generation Report
//   EXTENSION: CATUEPDMCreate
//   TIE: CATIPDMUECreate
//End CAA2 Wizard Generation Report
//===================================================================
#ifndef CAAPbiUECreate_H
#define CAAPbiUECreate_H

#include "CATBaseUnknown.h"
class CATDocument;
#include "CATListOfCATUnicodeString.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"

//-----------------------------------------------------------------------

/**
 * Class extending the object "CATUEPDMCreate".
 * <br>
 * It implements the interface:
 *  <ol>
 *  <li>@see CATPDMBase.CATIPDMUECreate
 *  </ol>
 */
class CAAPbiUECreate: public CATBaseUnknown
{
	CATDeclareClass;

public:

	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	CAAPbiUECreate();
	virtual ~CAAPbiUECreate();

	/**
	 * @see CATPDMBase.CATIPDMUECreate#GetProductEnvironment
	 */
	HRESULT GetProductEnvironment(const CATBaseUnknown* iObj,
				      CATUnicodeString& oEnv,
				      CATUnicodeString& oType);

	/**
	 * @see CATPDMBase.CATIPDMUECreate#GetDocumentEnvironment
	 */
	HRESULT GetDocumentEnvironment(const CATDocument* iDoc,
				       CATUnicodeString& oEnv,
				       CATUnicodeString& oTable);

	/**
	 * @see CATPDMBase.CATIPDMUECreate#GetDocumentEnvironment
	 */
	HRESULT GetDocumentEnvironment(const char* Filepath,
				       CATUnicodeString& oEnv,
				       CATUnicodeString& oTable);

	/**
	 * @see CATPDMBase.CATIPDMUECreate#GetProductAttributesValue
	 */
	HRESULT GetProductAttributesValue(const CATBaseUnknown* iObj,
					  const CATUnicodeString& iType,
					  int& oNbAttr,
					  CATListOfCATUnicodeString& oAttrName,
					  CATListOfCATUnicodeString& oAttrType,
					  void**& oAttrValues,
					  CATBoolean& oCreateOrUpdate);

	/**
	 * @see CATPDMBase.CATIPDMUECreate#GetDocumentAttributesValue
	 */
	HRESULT GetDocumentAttributesValue(const CATDocument* iDoc,
					   int& oNbAttr,
					   CATListOfCATUnicodeString& oAttrName,
					   CATListOfCATUnicodeString& oAttrType,
					   void**& oAttrValues,
					   CATBoolean& oCreateOrUpdate);

	/**
	 * @see CATPDMBase.CATIPDMUECreate#GetDocumentAttributesValue
	 */
	HRESULT GetDocumentAttributesValue(const char* Filepath,
					   int& oNbAttr,
					   CATListOfCATUnicodeString& oAttrName,
					   CATListOfCATUnicodeString& oAttrType ,
					   void**& oAttrValues);

	/**
	 * Implements a function from an interface.
	 * @see CATPDMBase.CATIPDMUECreate#GetProductAttributesValue
	 */
	HRESULT GetProductAttributesValue(const char* Filepath,
					  int& oNbAttr,
					  CATListOfCATUnicodeString& oAttrName,
					  CATListOfCATUnicodeString& oAttrType,
					  void**& oAttrValues);


private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	CAAPbiUECreate(CAAPbiUECreate &);
	CAAPbiUECreate& operator=(CAAPbiUECreate&);
	void GetDocNameAndExtension (const CATDocument& iDoc,
				     CATUnicodeString& ioDocName,
				     CATUnicodeString& ioDocExt);
	const char *CopyUStringToChar (CATUnicodeString& istr, int iSize);
	const char *GetEnvironment();
	const char *GetRepository();

	char *_environment;
	char *_repository;

};

//-----------------------------------------------------------------------

#endif

