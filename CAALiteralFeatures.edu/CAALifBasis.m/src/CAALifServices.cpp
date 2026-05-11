// COPYRIGHT DASSAULT SYSTEMES  1994 2000


//#include "CAALifInit.h"
#include "CAALifReturnCodes.h"
#include "iostream.h"

// ObjectModelerBase headers
#include "CATSession.h"
#include "CATDocument.h"
#include "CATSessionServices.h" // Create_Session and Delete_Session
#include "CATDocumentServices.h"  // New, SaveAs and Remove document
#include "CATIContainer.h"
#include "LifeCycleObject.h"
#include "CATInit.h" // GetRootContainer

// ObjectSpecsModeler headers
#include "CATISpecAttribute.h"
#include "CATISpecObject.h"

// LiteralFeatures headers
#include "CATICkeParmFactory.h"
#include "CATICkeType.h"
#include "CATICkeParm.h"
#include "CATIParmPublisher.h" // For the definition of the IID. 

// CAALiteralFeatures headers
#include "CAALifServices.h"

// MecModInterfaces
#include "CATIPrtPart.h"
#include "CATIPrtContainer.h"

#if defined(CATIAV5R24)
#pragma message ( "FDKNLMNFLDK%FNKLMLDK%HFNKLD%LK?F" )
#endif

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
//  Usage:
//  ------
// Internal usage.
//  
//=============================================================================
//  Main Methods:
//  ------------
//
//  CAALifCreateStartUpsCatalog:   Creates a new catalog for storing StartUps
//  CAALifCreateStartUps:     Creates the features startups.
//
//=============================================================================
//  Return Errors:
//  -------------
//  CAAInitSessionFailed				- ERROR in creating the session
//	CAALifDeleteSessionFailed		- Unable to delete the session.					
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================

CAALifServices::CAALifServices()
{
	_pDoc = NULL;
	_pSession = NULL;
	_piContainer = NULL;
	_spPart = NULL_var;
}


CAALifServices::CAALifServices(CATSession* iSession)
{
	_pDoc = NULL;
	_pSession = iSession;
	_piContainer = NULL;	
	_spPart = NULL_var;
}

CAALifServices::~CAALifServices()
{
	CAALifCloseSession();	
	_pDoc = NULL;
	_pSession = NULL;
	_piContainer = NULL;	
	_spPart = NULL_var;
}

void CAALifServices::DumpParameter( CATICkeParm_var& iParm, CATUnicodeString& oString)
{
	CATICkeType_var spType = iParm->Type();
	CATUnicodeString parmTypeName = spType->Name();
	CATUnicodeString parmName = iParm->Name();

	CATUnicodeString t1("Parameter : \n");
	CATUnicodeString cr("\n");
	CATUnicodeString name("\tName: ");
	CATUnicodeString typen("\tType Name: ");

	oString.Append(t1);
	oString.Append(parmName);
	oString.Append(cr);
	oString.Append(name);
	oString.Append(parmName);
	oString.Append(cr);
	oString.Append(typen);
	oString.Append(parmTypeName);
	oString.Append(cr);

	return;
}

/**
* Creates a part document and initialize the environement.
*/
HRESULT CAALifServices::CAALifCreateInstanceContainer (CATIContainer** opiContainer)
{
	HRESULT rc = E_FAIL;

	if (opiContainer == NULL || *opiContainer != NULL)
		return E_INVALIDARG;

	*opiContainer = NULL;

	if( _piContainer == NULL)
	{
		rc = CATDocumentServices::New("Part",
			_pDoc);
		if (NULL != _pDoc) cout << "New document created OK" << endl << flush;
		else
		{
			cout << "ERROR in creating New document" << endl << flush;
			return rc;
		}

		/*----------------------------------------------*/
		/* Retrieve the root container of the document. */
		/*----------------------------------------------*/

		CATInit *piInitOnDoc = NULL;
		rc = _pDoc -> QueryInterface(IID_CATInit,
			(void**) &piInitOnDoc);
		if (FAILED(rc) || !piInitOnDoc)
		{
			cout << "ERROR in QueryInterface on CATInit for doc" << endl << flush;
			return rc;
		}

		const CATIdent idCATIContainer = "CATIContainer";
		CATIContainer *piRootContainer = NULL;
		piRootContainer = (CATIContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer);
		if (NULL == piRootContainer)
		{
			cout << "ERROR in GetRootContainer" << endl << flush;
			piInitOnDoc -> Release();
			piInitOnDoc = NULL;
			return rc;
		}

		/*----------------------------------------------*/
		/* Retrieve the root container of the part. */
		/*----------------------------------------------*/
		CATIPrtContainer* piPrtContainer;
		piPrtContainer = (CATIPrtContainer*) piInitOnDoc->GetRootContainer("CATIPrtContainer");	
		if( NULL == piPrtContainer )
		{
			cout << "ERROR in QueryInterface for CATIPrtContainer" << endl << flush;
			piInitOnDoc -> Release();
			piInitOnDoc = NULL;
			piRootContainer->Release();
			piRootContainer = NULL;

			return rc;          
		}
		_spPart =  piPrtContainer->GetPart();
		if ( NULL_var == _spPart ) 
		{
			cout << "ERROR in QueryInterface for CATIPrtPart" << endl << flush;
			piInitOnDoc -> Release();
			piInitOnDoc = NULL;
			piPrtContainer->Release();
			piPrtContainer = NULL;
			piRootContainer->Release();
			piRootContainer = NULL;

			return rc;
		}  
		piPrtContainer->Release();
		piPrtContainer = NULL;
		piInitOnDoc -> Release();
		piInitOnDoc = NULL;

		_piContainer = piRootContainer;
		*opiContainer = _piContainer;	
		if(_piContainer != NULL)    
			_piContainer->AddRef();

	}
	else
	{
		*opiContainer = _piContainer;
		_piContainer->AddRef();
	}

	return rc;
}





/**
* retrieves a startup by its type in the given catalog.
*/
HRESULT CAALifServices::CAALifRetrievePublisherFromCurrentDoc(CATIParmPublisher** opiPublisher)
{
	/*------------------------------------------------*/
	/* Retrieve a publisher from the current document */
	/*------------------------------------------------*/
	HRESULT rc = E_FAIL;
	if( _spPart != NULL_var)
	{
		rc = _spPart -> QueryInterface(IID_CATIParmPublisher, (void**)opiPublisher);
		if (SUCCEEDED(rc))
			cout <<  "Publisher retrieved." << endl << flush;
		else
		{
			cout << "ERROR in retrieving the publisher from the current document." << endl << flush;
			return rc;
		}
	}

	return rc;
}

int CAALifServices::CAALifInitSession ()
{
	/*------------------------------------------------------------------*/
	/* Creates a Session:     																					*/
	/*------------------------------------------------------------------*/	
	char *sessionName = "CAA2_Sample_Session";

	if( _pSession != NULL )
		return CAALifOk;

	HRESULT rc = ::Create_Session(sessionName, 
		_pSession );
	if ((FAILED(rc)) || (NULL == _pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return CAALifInitSessionFailed;
	}
	else
		return CAALifOk;
}

/**
* Closes the session.
*/
int CAALifServices::CAALifCloseSession ()
{
	char *sessionName = "CAA2_Sample_Session";
	HRESULT rc= 0;

	_spPart = NULL_var;

	if (NULL != _pDoc)
	{
		cout << " Removing Document " << endl;
		LifeCycleObject_var spRemove (_pDoc);
		spRemove->remove();	
		_pDoc = NULL;
	}
	if( NULL!= _piContainer )
	{
		cout << " Releasing Container " << endl;	
		_piContainer->Release();
		_piContainer = NULL;
	}
	if(_pSession != NULL)
	{	  
		cout << " Deleting Session " << endl;		  
		rc = ::Delete_Session(sessionName);
		_pSession = NULL;		

		if (FAILED(rc))
		{
			cout << "ERROR in deleting session" << endl << flush;
			return CAALifDeleteSessionFailed;
		}
		else
		{
			cout << " Doc removed and session deleted " << endl;
			_pDoc = NULL;
		}
	}

	return CAALifOk;
}
