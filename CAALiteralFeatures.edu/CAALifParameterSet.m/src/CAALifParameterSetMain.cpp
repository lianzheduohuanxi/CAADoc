// COPYRIGHT DASSAULT SYSTEMES  1999

//Local: CAALiteralFeatures samples
#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATDocumentServices.h"
#include "CATInit.h"
#include "CATDocument.h"

// LiteralFeatures 
#include "CATICkeParmFactory.h"
#include "CATICkeRelationFactory.h"
#include "CATICkeParm.h"
#include "CATICkeType.h"
#include "CATICkeInst.h"
#include "CATICkeRelation.h"
#include "CATIParmPublisher.h"
#include "CATIVisitor.h"
#include "CATIAlias.h"

// ObjectSpecsModeler
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecObject.h"
#include "CATICatalog.h"

//CAALiteralFeatures.edu
#include "CAALifServices.h"

//LiteralFeatures
#include "CATIVisitor.h"

//Part
#include "CATIPrtPart.h"
#include "CATIPrtContainer.h"
#include "CATIPad.h"

#include "iostream.h" 

CATIContainer* _piContainer;
CATDocument* _pDocument;
CATICkeParmFactory* _piFact;
CATICkeRelationFactory* _piRelFact;

/** @quickReview tvq 2001:06:25 */



/**
*	Load the CATPart and retrieves the root container.
*	iFilename is the absolute filename (total path).
*/
int LoadPart(char* iFilename)
{
    HRESULT rc;
    CATIContainer* piRootContainer = NULL;	
    /*----------------------------------------------*/
    /* Load the document. */
    /*----------------------------------------------*/	
    CATDocument* pDocument = NULL;
    
    boolean ReadOnly = TRUE;
    
    CATUnicodeString filename( iFilename );
    CATDocumentServices::OpenDocument( filename, pDocument, ReadOnly );
    
    if( pDocument == NULL)
    {
        fprintf(stderr,"ERROR: Unable to open document %s\n", iFilename );	
        return -1;	
    }	
    CATInit* piInitOnDoc = NULL;
    rc = pDocument -> QueryInterface(IID_CATInit,
        (void**) &piInitOnDoc);
    if (FAILED(rc)) 
    {
        fprintf(stderr,"ERROR in QueryInterface on CATInit for doc\n");
        return -1;
    }
    
    /*----------------------------------------------*/
    /* Retrieve the root container of the document. */
    /*----------------------------------------------*/
    const CATIdent idCATIContainer = "CATIContainer";
    if( piInitOnDoc != NULL )
    {
        piRootContainer = (CATIContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer);
        piInitOnDoc -> Release();
        piInitOnDoc = NULL;
    }
    if (NULL == piRootContainer)
    {
        fprintf(stderr,"ERROR in GetRootContainer\n");			 
        return -1;
    }		 
    
    CATICkeParmFactory* piFact = NULL;
    rc = piRootContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
        return CAALifParmFactoryError;
    }		
    
    CATICkeRelationFactory* piRelFact = NULL;
    rc = piRootContainer->QueryInterface(IID_CATICkeRelationFactory, (void**) &piRelFact);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
        return CAALifParmFactoryError;
    }		
    
    
    _piContainer = piRootContainer;
    _pDocument = pDocument;
    _piFact = piFact;    
    _piRelFact = piRelFact;
    
    fprintf(stderr,"Container successfully retrieved \n");
    return 0;		
}


void ListParametersUnderPublisher( CATIParmPublisher_var& spPublisher)
{
    if(spPublisher == NULL_var )
        return;
    
    fprintf(stderr," => Parameters under Publisher : \n");
    
    CATLISTV(CATBaseUnknown_var) list;
    CATIVisitor_var aStandardVisitor = _piFact->CreateStandardVisitor(IID_CATICkeParm, &list);

    
    spPublisher->VisitChildren(aStandardVisitor, 1);
    
    //In the end the list is filled with all the CATICkeParm found on the feature and its references.
    int size = list.Size();
    int i = 0;
    for(i=1; i <=size; i++)
    {
        CATICkeParm_var p = list[i];
        fprintf(stderr,"p[%i] parameter name is: %s\n", i, p->Name().CastToCharPtr() );
    }
    
    
    return;
}

int GetParms()
{
    fprintf(stderr, " =========== List all parameters and Parametersets of the loaded part ================== \n");
      
    HRESULT rc = 0;
    
    if( _piContainer == NULL )
        rc = 2;
    else
    {                        
        
        CATIPrtContainer* piPrtContainer = NULL;
        rc = _piContainer->QueryInterface(IID_CATIPrtContainer,
            (void**) &piPrtContainer);
        if (FAILED(rc)) 
        {
            fprintf(stderr, "ERROR in QueryInterface on container for CATIPrtContainer\n" );
            return -1;
        }

		//03/05/02 SOC : mkchecksource
		if(piPrtContainer == NULL)
        {
            fprintf(stderr, "ERROR : piPrtContainer is NULL\n" );
            return -1;
        }        
        
        CATIPrtPart_var myPart = NULL_var;
        myPart = piPrtContainer->GetPart();
        piPrtContainer->Release();
        piPrtContainer = NULL;
        
        if( myPart == NULL_var )
        {
            fprintf(stderr, "Mechanical Part not retreived.\n");
            return -1; 
        }
        
        
        CATIParmPublisher_var root = myPart;
        if( root != NULL_var)
        {
            ListParametersUnderPublisher( root );
            
            CATLISTV(CATBaseUnknown_var) list;
            fprintf(stderr, "\nRetrieving ParameterSets in the open document: \n");
            CATIVisitor_var bStandardVisitor = _piFact->CreateStandardVisitor(IID_CATICkeParameterSet, &list);
            
            root->VisitChildren(bStandardVisitor, 1);
            
            //In the end the list is filled with all the CATICkeParm found on the feature and its references.
            
            int size = list.Size();
            int i;
            for(i=1; i <=size; i++)
            {
                CATICkeParameterSet_var piSet = list[i];
                CATIParmPublisher_var spPub = list[i];
				CATIAlias_var piSetAlias = list[i];

                fprintf(stderr, "ParameterSet Name: %i : %s containing the following parameters.\n",
                    i, piSetAlias->GetAlias().CastToCharPtr() );
                ListParametersUnderPublisher( spPub );
                
            }
        }
        else
            rc = 3;
    }
    
    
    fprintf(stderr, " =========== End of getParmsAndRelations ================== ");
    
    return rc;
}



CATCke::Boolean CAALifAddParameterSet()
{
    
    fprintf(stderr, "\n\n =========== Adding a new parameter set under a pad  ================== \n");    
    
    int rc = 0;
    HRESULT hr = E_FAIL;
    
    if( _piContainer == NULL )
        return 2;
    
    
    CATIPrtContainer* piPrtContainer = NULL;
    hr = _piContainer->QueryInterface(IID_CATIPrtContainer,
        (void**) &piPrtContainer);
    if (FAILED(hr)) 
    {
        cout << "ERROR in QueryInterface on container for CATIPrtContainer" << endl << flush;
        return -1;
    }        
    
    CATIPrtPart_var myPart = NULL_var;
    myPart = piPrtContainer->GetPart();
    piPrtContainer->Release();
    piPrtContainer = NULL;
    
    if( myPart == NULL_var )
    {
        cout << "Mechanical Part not retreived." << endl;
        return -1; 
    }
    
    //Now let's retrieve all the pads.
    CATIParmPublisher_var root = myPart;
    if( root != NULL_var)
    {
        CATLISTV(CATBaseUnknown_var) list;
        CATIVisitor_var aStandardVisitor = _piFact->CreateStandardVisitor(IID_CATIPad, &list);
        
        root->VisitChildren(aStandardVisitor, 1);
        
        //Add a parameter set under all the pads.
        int size = list.Size();
        int i = 0;
        for(i=1; i <=size; i++)
        {
            fprintf(stderr,"Pad retreived. \n");
            CATIPad_var spPad= list[i];
            CATIParmPublisher* piPadPub = NULL;
            rc = spPad->QueryInterface(IID_CATIParmPublisher, (void**) &piPadPub);
            if (FAILED(rc)) 
            {
                cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
                return -1;
            }		
            
            CATICkeParameterSet_var spParamSet1 = _piRelFact->CreateParameterSet("AdditionalParameterSetUnderPad");
            piPadPub->Append( spParamSet1 );
            
            
            CATIParmPublisher* piSetPub = NULL;
            rc = spParamSet1->QueryInterface(IID_CATIParmPublisher, (void**) &piSetPub);
            if (FAILED(rc)) 
            {
                cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
                piPadPub->Release();
                piPadPub = NULL;
                return -1;
            }		
            
            CATICkeParm_var spLength = _piFact->CreateLength ("lengthParamUnderPad",2);
            piSetPub->Append( spLength ); 
            
            piPadPub->Release();
            piPadPub = NULL;
            piSetPub->Release();
            piSetPub = NULL;
        }
    }
    fprintf(stderr, " =========== End of adding a new parameter set under a pad ================== \n\n");
    
    return 1;
}        




int main (int argc, char** argv)
{
    int rc = 0;
    
    CAALifServices services;
    
    // Initialize the session
    rc = services.CAALifInitSession ();
    if( rc != CAALifOk )
        return rc;
    
    char* filename = argv[1];
    
    fprintf(stderr,"filename = %s\n", filename);
    
    LoadPart(filename);
 
    fprintf(stderr," Here is the content of the part after loading. \n\n");
    GetParms();
    
    CAALifAddParameterSet();

    fprintf(stderr," Here is the content of the part after adding a new parameter set under the pad. \n\n");   
    GetParms();
    
    if(_piContainer != NULL)
    {
        _piContainer->Release();	
        _piContainer = NULL;
    }
    if(_piFact != NULL)
    {
        _piFact->Release();
        _piFact = NULL;
    }
    
      if(_piRelFact != NULL)
    {
        _piRelFact->Release();
        _piRelFact = NULL;
    }
    
    // Close the session and environment
    services.CAALifCloseSession();
    
    return rc;
};


