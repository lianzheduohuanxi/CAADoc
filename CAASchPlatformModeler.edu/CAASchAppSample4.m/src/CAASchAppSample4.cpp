//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2015
//=============================================================================
//
// CAASchAppSample4 - create schematic document from xml document containing Piping/Tubing/HVAC data.
//
#include <iostream.h>

// This framework
#include "CAASchAppSample4.h"

// CATSchPlatformInterfaces
#include "CATISchDocFrmXml.h"

// ObjectModelerBase
#include "CATObject.h"
#include "CATSession.h"
#include "CATSessionServices.h"

//=============================================================================
//  Constructor
//=============================================================================
CAASchAppSample4::CAASchAppSample4() : _pSessionIdent("Session DSA CAASchAppBaseEnv CATProduct"),
	_pSession(NULL), _pObj(NULL), _piSchDoc(NULL)
{
	cout << "CAASchAppSample4::CAASchAppSample4()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAASchAppSample4::~CAASchAppSample4()
{
	cout << "CAASchAppSample4::~CAASchAppSample4()" << endl;
	cout << "CleanupSession ---" << endl;

	if (_piSchDoc)
	{
		_piSchDoc->Release();
		_piSchDoc = NULL;
	}

	if (_pObj)
	{
		_pObj->Release();
		_pObj = NULL;
	}

	if ((NULL != _pSession) && (NULL != _pSessionIdent))
	{
		::Delete_Session(_pSessionIdent);
		_pSession = NULL;
		cout << "Session released !!!!" << endl ;
	}

	_pSessionIdent = NULL;
}

//=============================================================================
//  CreateComponent
//=============================================================================
int CAASchAppSample4::DoSample(CATUnicodeString iFileToBeLoaded, CATUnicodeString iPathToOutputFile)
{
	cout << "====================================" << endl;
	cout << "     CAASchAppSample4::DoSample     " << endl;
	cout << "====================================" << endl;

	HRESULT rc;
	CATTry 
	{
		//---------------------------------------------------------------------------
		// Create Session
		//---------------------------------------------------------------------------
		::Create_Session (_pSessionIdent, _pSession);
		if (NULL == _pSession)
		{
			cout << "Cannot create session" << endl;
			return rc;
		}
		cout << "Create_Session successfully" << endl;

		_pObj = new CATObject("CATPID");//CATTubingDiagram, CATHVACDiagram
		if (NULL != _pObj)
		{
			rc = _pObj->QueryInterface(IID_CATISchDocFrmXml, (void**)&_piSchDoc);
			if (SUCCEEDED(rc) && (NULL != _piSchDoc))
			{
				rc = _piSchDoc->CreateSchematicFromXml(iFileToBeLoaded, iPathToOutputFile);
			}
		}
		else
			return rc;
	} // end CATTry

	CATCatch (CATError, error)
	{
		cout << "CAASchAppSample4::DoSample *** CATRethrow" << endl;
		CATRethrow;
	}	
	CATEndTry;
	return 0;
}

