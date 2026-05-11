// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAPbiUECreate.cpp
// Implement the CATIPDMUECreate interface
//
//===================================================================
#include "CAAPbiUECreate.h"
#include "CATISpecObject.h"
#include "CATDocument.h"
#include "CATIProduct.h"
#include "CATLib.h"
#include "CATGetEnvValue.h"
#include "CAAPbiAttributes.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIPDMUECreate.h"
TIE_CATIPDMUECreate(CAAPbiUECreate);

CATImplementClass(CAAPbiUECreate,
		  DataExtension,
		  CATBaseUnknown,
		  CATUEPDMCreate);
 
//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAPbiUECreate::CAAPbiUECreate():
	CATBaseUnknown()
{
  _environment = NULL;
  _repository = NULL;
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAPbiUECreate::~CAAPbiUECreate()
{
  if (NULL != _environment) 
    {
      free((void *) _environment);
      _environment = NULL;
    }
  if (NULL != _repository) 
    {
      free((void *) _repository);
      _repository = NULL;
    }
}

//-----------------------------------------------------------------------------
// Implements GetProductEnvironment
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetProductEnvironment (const CATBaseUnknown* iObj,
					       CATUnicodeString& oEnv,
					       CATUnicodeString& oType)
{
	oEnv = GetEnvironment();
	return S_OK;
}

//-----------------------------------------------------------------------------
// Implements GetDocumentEnvironment
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetDocumentEnvironment (const CATDocument* iDoc,
						CATUnicodeString& oEnv,
						CATUnicodeString& oTable)
{
	oEnv = GetEnvironment();

	const char *docNomadType = (NULL != iDoc ? iDoc->IsA() : NULL);

	oTable = (NULL != docNomadType && 
		  strcmp(docNomadType, "model") == 0 || 
		  strcmp(docNomadType, "CDMAmodel") == 0 ?
		  "CATIA_MODEL" :
		  "DOCUMENT");

	return S_OK;
}

//-----------------------------------------------------------------------------
// Implements GetDocumentEnvironment
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetDocumentEnvironment (const char* Filepath,
						   CATUnicodeString& oEnv,
						   CATUnicodeString& oTable)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
// Implements GetProductAttributesValue
// Returns the following attributes:
// 	S_PART_NUMBER
//	S_CHG_NUM
//	S_TYPE
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetProductAttributesValue 
	(const CATBaseUnknown* iObj,
	 const CATUnicodeString& iType,
	 int& oNbAttr,
	 CATListOfCATUnicodeString& oAttrName,
	 CATListOfCATUnicodeString& oAttrType,
	 void**& oAttrValues,
	 CATBoolean& oCreateOrUpdate)
{
	if (NULL == iObj)
		return E_FAIL;

	oCreateOrUpdate = TRUE;
	CAAPbiAttributes attrs(oAttrName, oAttrType, oAttrValues, oNbAttr, 3);
	HRESULT ret = attrs.AllocateValues();
	if (FAILED(ret))
	        return ret;

	if (iObj->IsAKindOf("CATDocument")) {

		//
		// S_PART_NUMBER : "Part"+document name
		// S_CHG_NUM     : 0
		// S_TYPE        : document extension
		//
		CATUnicodeString docName;
		CATUnicodeString docExt;
		GetDocNameAndExtension(*(CATDocument*) iObj, docName, docExt);

		CATUnicodeString partNum("Part");
		partNum += docName;
		const char *cPartNum = CopyUStringToChar(partNum, 32);
		if (NULL == cPartNum)
			return E_FAIL;
		attrs.AddAttribute("S_PART_NUMBER", "String", cPartNum);
		
		CATUnicodeString chgNum("0");
		const char *cNum = CopyUStringToChar(chgNum, 0);
		attrs.AddAttribute("S_CHG_NUM", "String", cNum);
		
		const char *cPartType = CopyUStringToChar(docExt, 15);
		if (NULL == cPartType)
			return E_FAIL;
		attrs.AddAttribute("S_TYPE", "String", cPartType);
		
	} else {

		//
		// S_PART_NUMBER : part number
		// S_CHG_NUM     : 0
		// S_TYPE        : part type
		//
		CATUnicodeString partNum;
		CATIProduct_var prod((CATBaseUnknown*)iObj);
		if (NULL_var != prod) {
			partNum = prod->GetPartNumber();	
		} else {
			CATISpecObject_var spec((CATBaseUnknown*)iObj);
			if (NULL_var != spec) {
				partNum = spec->GetDisplayName();
			}
		}
		const char *cPartNum = CopyUStringToChar(partNum, 32);
		if (NULL == cPartNum)
			return E_FAIL;
		attrs.AddAttribute("S_PART_NUMBER", "String", cPartNum);
		
		CATUnicodeString chgNum("0");
		const char *cNum = CopyUStringToChar(chgNum, 0);
		attrs.AddAttribute("S_CHG_NUM", "String", cNum);
		

		CATUnicodeString partType;
		CATISpecObject_var spec((CATBaseUnknown*)iObj);
		if (NULL_var != spec) {
			CATUnicodeString specType= spec->GetType();
			specType = specType.Strip();
			if (specType == "ASMPRODUCT")
				partType = "PART";
			else if (specType == "DATABASEPRODUCT")
				partType = "PART";
			else
				partType = specType;
		}
		const char *cPartType = CopyUStringToChar(partType, 15);
		if (NULL == cPartType)
			return E_FAIL;
		
		attrs.AddAttribute("S_TYPE", "String", cPartType);
	
	}
	
	// attrs.Dump();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Implements GetDocumentAttributesValue
// Returns the following attributes:
// 	S_NAME
// 	S_TYPE_REP
// 	S_FORMAT
// 	C_LAST_REPOSITORY
// 	NOTES
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetDocumentAttributesValue 
	(const CATDocument* iDoc,
	 int& oNbAttr,
	 CATListOfCATUnicodeString& oAttrName,
	 CATListOfCATUnicodeString& oAttrType,
	 void**& oAttrValues,
	 CATBoolean& oCreateOrUpdate)
{
	if (NULL == iDoc)
	  	return E_FAIL;

	oCreateOrUpdate=TRUE;
	CAAPbiAttributes attrs(oAttrName, oAttrType, oAttrValues, oNbAttr, 5);	
	HRESULT ret = attrs.AllocateValues();
	if (FAILED(ret))
	  	return ret;
		
	CATUnicodeString docName;
	CATUnicodeString docExt;
	GetDocNameAndExtension(*iDoc, docName, docExt);
	
  CATUnicodeString begin=docName.SubString(0, 3);
  if (begin != "CAA")
	  docName = "CAA" + docName;
	const char *cDocName = CopyUStringToChar(docName, 12);
	if (NULL == cDocName)
		return E_FAIL;
	attrs.AddAttribute("S_NAME", "String", cDocName);

	const char *cDocType = CopyUStringToChar(docExt, 8);
	if (NULL == cDocType)
		return E_FAIL;
	attrs.AddAttribute("S_TYPE_REP", "String", cDocType);
	
	CATUnicodeString userName("CAA");
	const char *cUserName = CopyUStringToChar(userName, 5);
	if (NULL == cUserName)
		return E_FAIL;
	attrs.AddAttribute("S_FORMAT", "String", cUserName);

	CATUnicodeString repository(GetRepository());
	const char *cRepository = CopyUStringToChar(repository, 0);
	if (NULL == cRepository)
		return E_FAIL;
	attrs.AddAttribute("C_LAST_REPOSITORY", "String", cRepository);

	CATUnicodeString notes("Created with CAA");
	const char *cNotes = CopyUStringToChar(notes, 0);
	if (NULL == cNotes)
		return E_FAIL;
	attrs.AddAttribute("NOTES", "String", cNotes);


	// attrs.Dump();


	return S_OK;
}

//-----------------------------------------------------------------------------
// Implements GetDocumentAttributesValue
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetDocumentAttributesValue
	(const char* iFilepath,
	 int& oNbAttr,
	 CATListOfCATUnicodeString& oAttrName,
	 CATListOfCATUnicodeString& oAttrType,
	 void**& oAttrValues)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
// Implements GetProductAttributesValue
//-----------------------------------------------------------------------------
HRESULT CAAPbiUECreate::GetProductAttributesValue
	(const char* iFilepath, 
	 int& oNbAttr, 
	 CATListOfCATUnicodeString& oAttrName, 
	 CATListOfCATUnicodeString& oAttrType, 
	 void**& oAttrValues)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
// Returns the value of the environment variable "CV5_VPM_ENV"
// or "VPMENV" if it's undefined
//-----------------------------------------------------------------------------
const char *CAAPbiUECreate::GetEnvironment()
{
  if (_environment == NULL)
    {
      if(CATGetEnvValue("CV5_VPM_ENV", &_environment) != CATLibSuccess)
	{
	  _environment=strdup("VPMENV");
	}
    }
  return _environment;
}

//-----------------------------------------------------------------------------
// Returns the VPM repository:
// value of the environment variable "CV5_VPM_REPOSITORY"
// or "DBLFAIX.BIN PATH $HOME/db/" if it's undefined
//-----------------------------------------------------------------------------
const char *CAAPbiUECreate::GetRepository()
{
  if(_repository == NULL)
    {
      if (CATGetEnvValue("CV5_VPM_REPOSITORY", &_repository) != CATLibSuccess)
	{
	   _repository= strdup("DBLFAIX.BIN PATH $HOME/db/");
	 }
    }
  return _repository;
}

//-----------------------------------------------------------------------------
// Split a document path into its name and extension
//-----------------------------------------------------------------------------
void CAAPbiUECreate::GetDocNameAndExtension (const CATDocument& iDoc,
					     CATUnicodeString& ioDocName,
					     CATUnicodeString& ioDocExt)
{
	CATUnicodeString docStorageName = iDoc.StorageName();
	char docDir[CATMaxPathSize];
	char docFileName[CATMaxPathSize];
	CATSplitPath(docStorageName.ConvertToChar(), docDir, docFileName);
	char *dotpos = strrchr(docFileName, '.');
	if (NULL != dotpos) {
		*dotpos = 0;
		ioDocName = docFileName;
		dotpos++;
		ioDocExt = dotpos;
	} else {
		ioDocName = docFileName;
		ioDocExt = "";
	}
}

//-----------------------------------------------------------------------------
// Make a copy of a UnicodeString in char, up to specified length
//-----------------------------------------------------------------------------
const char *CAAPbiUECreate::CopyUStringToChar (CATUnicodeString& iStr, 
					       int iSize)
{
	int len;

	if (0 == iSize) {
		// length is null, copy whole string
		len = iStr.GetLengthInChar();
	} else {
		// only copy up to specified length
		// padding with spaces if necessary
		iStr.Resize(iSize);
		len = iSize;
	}
	char *ptr = new char [len + 1];
	if (NULL == ptr)
		return NULL;
	strcpy(ptr, iStr.ConvertToChar());
	return ptr;
}
