// COPYRIGHT DASSAULT SYSTEMES  2002
// --------------------------------------------------------------------------
//
// ABSTRACT
// Defines all the operations required to start a CATIA batch application:
//   * Create a session
//   * Create a document
//   * Retrieve its root container
//   * Close a session
//
// --------------------------------------------------------------------------
#ifndef __CAAPeoServices_H
#define __CAAPeoServices_H

#include "CAAPeoBasis.h"

// ObjectModelerBase
class CATSession;
class CATDocument;
class CATIContainer;
class CATIPrtContainer;
class CATICatalog;
class CATIParmPublisher;

//System
#include "CATUnicodeString.h"

#include "CATIPrtPart.h"


class ExportedByCAAPeoBasis CAAPeoServices
{

private:

		CATDocument* _pDoc;
		CATSession*	_pSession;
		CATIContainer* _piContainer;
		CATIPrtContainer* _piPrtContainer;
		CATIPrtPart_var _spPart;	
		CATUnicodeString _catalogName;

public:

	CAAPeoServices();

	CAAPeoServices(CATSession* iSession);

	~CAAPeoServices();

	/**
	*Creates a new document CATPart and returns a pointer to the Root container of this document.
	*/
	HRESULT CAAPeoCreateInstanceContainer (CATIContainer** opiContainer);

	/**
	* Opens an existing part document and returns a pointer to the Root container of this document.
	*/
	HRESULT CAAPeoOpenInstanceContainer (const CATUnicodeString& iFilePath, CATIContainer** opiContainer);
	
	/**
	*	Opens a session.
	*/
	HRESULT CAAPeoInitSession();
	
	/**
	* Closes a session.
	* If argument iSavingDocPath is different from "", the document will be saved at the given
	* location.
	*/
	HRESULT CAAPeoCloseSession(const CATUnicodeString& iSavingDocPath = "");

	/**
	* Returns the CATIParmPublisher facet of the current document (created with CAAPeoCreateInstanceContainer).
	*/
	HRESULT CAAPeoRetrievePublisherFromCurrentDoc(CATIParmPublisher** opiPublisher);
};


#endif
