#include "CAAPeoServices.h"

#include "iostream.h"

// CAAOptimizationInterfaces.edu
#include "CAAPeoReturnCodes.h"

// ObjectModelerBase headers
#include "CATSession.h"
#include "CATDocument.h"
#include "CATSessionServices.h" // Create_Session and Delete_Session
#include "CATDocumentServices.h"  // New, SaveAs and Remove document
#include "CATIContainer.h"
#include "LifeCycleObject.h"
#include "CATInit.h" // GetRootContainer

#include "CATIDocRoots.h"
#include "CATISpecObject.h"
#include "CATIPrtContainer.h"

#include "CATIParmPublisher.h" 

CAAPeoServices::CAAPeoServices()
{
    _pDoc = NULL;
    _pSession = NULL;
    _piContainer = NULL;
    _piPrtContainer = NULL;
	_spPart = NULL_var;	
}


CAAPeoServices::CAAPeoServices(CATSession* iSession)
{
    _pDoc = NULL;
    _pSession = iSession;
    _piContainer = NULL;
    _piPrtContainer = NULL;
	_spPart = NULL_var;	
}

CAAPeoServices::~CAAPeoServices()
{
    CAAPeoCloseSession();	
    _pDoc = NULL;
    _pSession = NULL;
    _piContainer = NULL;
    _piPrtContainer = NULL;
	_spPart = NULL_var;	
}

/**
* Creates a part document and returns a pointer to the Root container of this document.
*/
HRESULT CAAPeoServices::CAAPeoCreateInstanceContainer (CATIContainer** opiContainer)
{
    HRESULT rc = E_FAIL;

    if( _piContainer == NULL)
    {
		cerr << "\nCreating document ... ";
        rc = CATDocumentServices::New("Part",_pDoc);

        if (NULL != _pDoc)
			cerr << "OK" << endl << flush;
        else
        {
            cerr << "FAILED" << endl << flush;
            *opiContainer = NULL;
            return rc;
        } 	
        
        /*----------------------------------------------*/
        /* Retrieve the root container of the document. */
        /*----------------------------------------------*/
        
        CATInit *piInitOnDoc = NULL;
        rc = _pDoc -> QueryInterface(IID_CATInit,(void**) &piInitOnDoc);

        if (FAILED(rc)) 
        {
            cerr << "ERROR in QueryInterface on CATInit for doc" << endl << flush;
            *opiContainer = NULL;
            return rc;
        }
 

        const CATIdent idCATIContainer1 = "CATIContainer";
        const CATIdent idCATIContainer2 = "CATIPrtContainer";
        _piPrtContainer = (CATIPrtContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer2);


        /*----------------------------------------------*/
        /* Retrieve the root container of the part. */
        /*----------------------------------------------*/
        _piPrtContainer = (CATIPrtContainer*) piInitOnDoc->GetRootContainer("CATIPrtContainer");	
        if( NULL == _piPrtContainer )
        {
            cout << "ERROR in QueryInterface for CATIPrtContainer" << endl << flush;
            piInitOnDoc -> Release();
	        piInitOnDoc = NULL;
            return rc;          
        }

        _piContainer = (CATIContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer1);
        if( NULL == _piContainer )
        {
            cout << "ERROR in QueryInterface for CATIPrtContainer" << endl << flush;
            piInitOnDoc -> Release();
	        piInitOnDoc = NULL;
          	_piPrtContainer->Release();
            _piPrtContainer = NULL;

            return rc;          
        }
        _spPart =  _piPrtContainer->GetPart();
        if ( NULL_var == _spPart ) 
        {
            cout << "ERROR in QueryInterface for CATIPrtPart" << endl << flush;
            piInitOnDoc -> Release();
	        piInitOnDoc = NULL;
          	_piPrtContainer->Release();
            _piPrtContainer = NULL;
          	_piContainer->Release();
            _piContainer = NULL;

            return rc;
        } 



        piInitOnDoc -> Release();
		piInitOnDoc = NULL;

        if (NULL == _piContainer)
        {
            cerr << "ERROR in GetRootContainer" << endl << flush;
            *opiContainer = NULL;			 
            return rc;
        }        

        *opiContainer = _piContainer;		 
    }
    _piContainer = *opiContainer;
    _piContainer->AddRef();
    
    return rc;
}

/**
* Opens an existing part document and returns a pointer to the Root container of this document.
*/
HRESULT CAAPeoServices::CAAPeoOpenInstanceContainer (const CATUnicodeString& iFilePath, CATIContainer** opiContainer)
{
    HRESULT rc = E_FAIL;

    if( _piContainer == NULL)
    {
		cerr << "\nOpening document ... ";
        rc = CATDocumentServices::OpenDocument("Part", _pDoc);

        if (NULL != _pDoc) 
			cerr << "OK" << endl << flush;
        else
        {
            cerr << "FAILED" << endl << flush;
            *opiContainer = NULL;
            return rc;
        } 	
        
        /*----------------------------------------------*/
        /* Retrieve the root container of the document. */
        /*----------------------------------------------*/
        
        CATInit *piInitOnDoc = NULL;
        rc = _pDoc -> QueryInterface(IID_CATInit,
            (void**) &piInitOnDoc);
        if (FAILED(rc)) 
        {
            cerr << "ERROR in QueryInterface on CATInit for doc" << endl << flush;
            *opiContainer = NULL;
            return rc;
        }
        
        const CATIdent idCATIContainer1 = "CATIContainer";
        const CATIdent idCATIContainer2 = "CATIPrtContainer";
        _piContainer = (CATIContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer1);
        if( NULL == _piContainer )
        {
            cout << "ERROR in QueryInterface for CATIPrtContainer" << endl << flush;
            piInitOnDoc -> Release();
	        piInitOnDoc = NULL;
            return rc;          
        }

        _piPrtContainer = (CATIPrtContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer2);
        if( NULL == _piPrtContainer )
        {
            cout << "ERROR in QueryInterface for CATIPrtContainer" << endl << flush;
            piInitOnDoc -> Release();
	        piInitOnDoc = NULL;
          	_piContainer->Release();
            _piContainer = NULL;

            return rc;          
        }

        _spPart =  _piPrtContainer->GetPart();
        if ( NULL_var == _spPart ) 
        {
            cout << "ERROR in QueryInterface for CATIPrtPart" << endl << flush;
            piInitOnDoc -> Release();
	        piInitOnDoc = NULL;
          	_piPrtContainer->Release();
            _piPrtContainer = NULL;
          	_piContainer->Release();
            _piContainer = NULL;

            return rc;
        } 

        piInitOnDoc -> Release();
		piInitOnDoc = NULL;

        if (NULL == _piContainer)
        {
            cerr << "ERROR in GetRootContainer" << endl << flush;
            *opiContainer = NULL;			 
            return rc;
        }        

        *opiContainer = _piContainer;
		_piContainer->AddRef();
    }
    //_piContainer = *opiContainer;

    
    return rc;
}

HRESULT CAAPeoServices::CAAPeoInitSession ()
{
    /*------------------------------------------------------------------*/
    /* Creates a Session:     																					*/
    /*------------------------------------------------------------------*/	
    char *sessionName = "CAA2_Sample_Session";
    
    if( _pSession != NULL )
        return E_FAIL;
    
    HRESULT rc = ::Create_Session(sessionName, 
        _pSession );
    if ((FAILED(rc)) || (NULL == _pSession))
    {
        cerr << "ERROR in creating session" << endl << flush;
        return E_FAIL;
    }

    return S_OK;
}

/**
* Closes the session.
*/
HRESULT CAAPeoServices::CAAPeoCloseSession (const CATUnicodeString& iSavingDocPath)
{
    char *sessionName = "CAA2_Sample_Session";
    HRESULT rc= 0;
    
    if (NULL != _pDoc)
    {
		CATUnicodeString EmptyStr = "";
		if(iSavingDocPath != EmptyStr)
		{
			cerr<< "Saving document as " << iSavingDocPath.ConvertToChar() << "...";
			if( FAILED(CATDocumentServices::SaveAs(*_pDoc,iSavingDocPath)) )
				cerr << "FAILED\n\n";
			else
				cerr << "OK\n\n";
		}

        cerr << " Removing Document " << endl;
        LifeCycleObject_var spRemove (_pDoc);
        spRemove->remove();	
        _pDoc = NULL;
    }
    if( NULL!= _piContainer )
    {
        cerr << " Releasing Container " << endl;	
        _piContainer->Release();
        _piContainer = NULL;
    }
   if( NULL!= _piPrtContainer )
    {
        cerr << " Releasing Prt Container " << endl;	
        _piPrtContainer->Release();
        _piPrtContainer = NULL;
    }
    if(_pSession != NULL)
    {	  
        cerr << " Deleting Session " << endl;		  
        rc = ::Delete_Session(sessionName);
        _pSession = NULL;		
        
        if (FAILED(rc))
        {
            cerr << "ERROR in deleting session" << endl << flush;
            return E_FAIL;
        }
        else
        {
            cerr << " Doc removed and session deleted " << endl;
            _pDoc = NULL;
        }
    }
    
    return S_OK;
}


HRESULT CAAPeoServices::CAAPeoRetrievePublisherFromCurrentDoc(CATIParmPublisher** opiPublisher)
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
