// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifServices_h
#define CAALifServices_h

#include "CAALifBasis.h"

// ObjectModelerBase
class CATSession;
class CATDocument;
class CATIContainer;

//ObjectSpecsModeler
class CATISpecObject;

// LiteralFeatures
#include "CATCke.h"
class CATICkeParm_var;
class CATIParmPublisher;

//System
#include "CATUnicodeString.h"

//MecModInterfaces
#include "CATIPrtPart.h"

// ==========================================================================
//
// ABSTRACT
// Defines all the operations required to start a CATIA batch application:
//   * Create a session
//   * Create a document
//   * Retrieve its root container
//   * Close a session
//
// ===========================================================================


class ExportedByCAALifBasis CAALifServices
{

private:

	CATDocument* _pDoc;
	CATSession*	_pSession;
	CATIContainer* _piContainer;
	CATUnicodeString _catalogName;
	CATIPrtPart_var _spPart;
public:

	CAALifServices();

	CAALifServices(CATSession* iSession);

	~CAALifServices();

	/**
	*Creates a new document CATPart and returns a pointer to the Root container of this document.
	*/
	HRESULT CAALifCreateInstanceContainer (CATIContainer** opiContainer);

	/**
	* Returns the CATIParmPublisher facet of the current document (created with CAALifCreateInstanceContainer).
	*/
	HRESULT CAALifRetrievePublisherFromCurrentDoc(CATIParmPublisher** opiPublisher);


	/**
	* Fills the oString CATUnicodeString with some information on the parameter.
	*/
	void DumpParameter( CATICkeParm_var& iParm, CATUnicodeString& oString);


	/**
	*	Opens a session.
	*/
	int CAALifInitSession();

	/**
	* Closes a session.
	*/
	int CAALifCloseSession();

};
#endif








































































