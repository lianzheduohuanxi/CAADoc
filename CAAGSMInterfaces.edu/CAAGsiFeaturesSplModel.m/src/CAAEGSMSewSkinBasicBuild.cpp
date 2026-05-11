// COPYRIGHT Dassault Systemes 2003
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------//
// CAAEGSMSewSkinBasicBuild.cpp
// Provide implementation to interface
//    CATIBuild
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================
// Object Modeler 
// MINC 
#include "CATUnicodeString.h"

#include "CATIContainer.h" 
#include "CATIPrtContainer.h"
#include "CATISpecObject.h" 

// MechanicalModeler Framework
#include "CATIMfProcReport.h"          // needed to store the procedural report
#include "CATMfBRepDefs.h"             // needed to indicate what the procedural report should follow
#include "CATIMfBRep.h" 
#include "CATMfErrUpdate.h"            // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"           // needed to associate an error to a feature
#include "CATIGeometricalElement.h"


// Topological Operator 
#include "CATGeoFactory.h"
#include "CATSoftwareConfiguration.h"
#include "CATTopData.h" 

#include "CATGSMOrientation.h"


#include "CATCGMJournalList.h"

#include "CATCreateSewSkin.h"
#include "CATTopSewSkin.h"

#include "CATBody.h"


#include "CATIUpdateError.h" 
#include "CAAIGSMSewSkinBasic.h"


#include "CATLISTV_CATBaseUnknown.h"   
#include "CATListOfCATUnicodeString.h" 


#include "CAAEGSMSewSkinBasicBuild.h"
#include "CAAGsiServicesBody.h" 

#define  V5R17_CONFIG_MNGT 
#ifdef V5R17_CONFIG_MNGT 
#include "CATMmrAlgoConfigServices.h" 
#endif  

//#define DEBUG_GSD_CAASAMPLE 
#ifdef DEBUG_GSD_CAASAMPLE 
#include "iostream.h" 
#endif 
CATImplementClass(CAAEGSMSewSkinBasicBuild, CodeExtension, CATBaseUnknown, CAASewSkinBasic );



//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicBuild : constructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicBuild::CAAEGSMSewSkinBasicBuild():
CAAGSMBuildBasic()
{
#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMSewSkinBasicBuild::CAAEGSMSewSkinBasicBuild) Constructor " <<endl ;
#endif 
}

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicBuild : destructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicBuild::~CAAEGSMSewSkinBasicBuild()
{
#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMSewSkinBasicBuild::~CAAEGSMSewSkinBasicBuild) Destructor " <<endl ;
#endif 
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIBuild.h"
TIE_CATIBuild( CAAEGSMSewSkinBasicBuild);


//-----------------------------------------------------------------------------
// Implements CATIBuild::Build
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasicBuild::Build () 
{ 
    
    
    
#ifdef DEBUG_GSD_CAASAMPLE 
     cout << " (CAAEGSMSewSkinBasicBuild::Build) Build Feature  " <<   endl;
#endif     
    //===============================================================================================
    //
    // The build method takes place as follows :
    //
    //     o -1- Removing all possible update error associated with the Sew Skin
    //     o -2- Retrieving the two input surfaces
    //     o -3- Retrieving the two bodies corresponding to the two input surfaces 
    //     o -4- Defining the procedural report
    //     o -5- Sew the Skin 
    //     o -6- Storing the procedural report
    //     o -7- Managing errors
    //
    //===============================================================================================
    
    
    //===============================================================================================
    //
    // -0- Removing all possible update error associated with the Sew Skin
    //
    //===============================================================================================
    
    // Gets a pointer on CATIUpdateError
    CATIUpdateError *piUpdateErrorOnGSMSewSkinBasic = NULL;
    
    HRESULT rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnGSMSewSkinBasic);
    
    if ( FAILED(rc) )
        return E_FAIL;
    
    
    // removes all error associated to the Combined Curve
    piUpdateErrorOnGSMSewSkinBasic->UnsetUpdateError();

    //===============================================================================================
	//
	// -1- Activate/Inactivate 
	//
	//===============================================================================================

	int DeActivationStatus = BuildGeneralizedInactiveResult(); 
	if (DeActivationStatus == 1 ){
		return S_OK; 
	}


    //===============================================================================================
    //
    // -2- Retrieving the two input surfaces
    //
    //===============================================================================================
    
    // Gets pointer on CAAIGSMSewSkinBasic 
    CAAIGSMSewSkinBasic *piGSMSewSkinBasic = NULL;
    
    rc = QueryInterface( IID_CAAIGSMSewSkinBasic , (void**) &piGSMSewSkinBasic );
    
    if ( FAILED(rc) ) 
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();       piUpdateErrorOnGSMSewSkinBasic = NULL ;
        return E_FAIL;
    }
    
    // Retrieves curves and directions
    CATISpecObject_var spiSpecOnSurfaceToSew    ;
    CATISpecObject_var spiSpecOnSurfaceSupport  ;
    
     piGSMSewSkinBasic->GetSurfaceToSew    ( spiSpecOnSurfaceToSew);
#ifdef DEBUG_GSD_CAASAMPLE 
    cout << " - " << spiSpecOnSurfaceToSew->GetName().ConvertToChar() << endl;
#endif          

     piGSMSewSkinBasic->GetSurfaceSupport  ( spiSpecOnSurfaceSupport);
#ifdef DEBUG_GSD_CAASAMPLE 
    cout << " - " <<  spiSpecOnSurfaceSupport->GetName().ConvertToChar() << endl;
#endif     


    if ( (!spiSpecOnSurfaceToSew ) ||  (!spiSpecOnSurfaceSupport )  ) 
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        piGSMSewSkinBasic->Release();        piGSMSewSkinBasic = NULL ;
        
        return E_FAIL;
    }
    
    
    //===============================================================================================
    //
    // -3- Retrieving the two bodies corresponding to the two input surfaces 
    //
    //===============================================================================================
    
	// Curve Ref 
	// ---------------------------------
    CATBody_var spiBodyOfSurfaceToSew ;
	// gets a pointer on CATIGeometricalElement on the first input curve
    CATIGeometricalElement *piGeometricalElementOnSurfaceToSew= NULL;
    CATIMfBRep *piBRepElementOnSurfaceToSew= NULL;

	if ( SUCCEEDED(spiSpecOnSurfaceToSew->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElementOnSurfaceToSew)) ) {
		// uses GetBodyResult body
		spiBodyOfSurfaceToSew= piGeometricalElementOnSurfaceToSew->GetBodyResult();
		if ( piGeometricalElementOnSurfaceToSew) 
			piGeometricalElementOnSurfaceToSew->Release();    piGeometricalElementOnSurfaceToSew= NULL ;
	}
	else if ( SUCCEEDED(spiSpecOnSurfaceToSew->QueryInterface ( IID_CATIMfBRep  , (void**) &piBRepElementOnSurfaceToSew))  ) {
		// uses GetBody to retrieve  body
		spiBodyOfSurfaceToSew= piBRepElementOnSurfaceToSew->GetBody();
        piBRepElementOnSurfaceToSew->Release();   piBRepElementOnSurfaceToSew= NULL ;
		if (piBRepElementOnSurfaceToSew) 
			piBRepElementOnSurfaceToSew->Release();   piBRepElementOnSurfaceToSew = NULL ;
	
	}
	else {
		// Releases useless pointers.
		piUpdateErrorOnGSMSewSkinBasic->Release();         piUpdateErrorOnGSMSewSkinBasic = NULL ;
		piGSMSewSkinBasic->Release();        piGSMSewSkinBasic = NULL ;
		return E_FAIL;
	}
		// Surface Support 
	// ---------------------------------
    CATBody_var spiBodyOfSurfaceSupport;
    // gets a pointer on CATIGeometricalElement on the second input curve
    CATIGeometricalElement *piGeometricalElementOnSurfaceSupport = NULL;
    CATIMfBRep *piBRepElementOnSurfaceSupport= NULL;
    

	if ( SUCCEEDED(spiSpecOnSurfaceSupport->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElementOnSurfaceSupport)) ) {
		// uses GetBodyResult body
		 spiBodyOfSurfaceSupport= piGeometricalElementOnSurfaceSupport->GetBodyResult();
		if ( piGeometricalElementOnSurfaceSupport) 
			piGeometricalElementOnSurfaceSupport->Release();    piGeometricalElementOnSurfaceSupport= NULL ;
	}
	else if ( SUCCEEDED(spiSpecOnSurfaceSupport->QueryInterface ( IID_CATIMfBRep  , (void**) &piBRepElementOnSurfaceSupport))  ) {
		// uses GetBody to retrieve  body
	     spiBodyOfSurfaceSupport= piBRepElementOnSurfaceSupport->GetBody();
       	if (piBRepElementOnSurfaceSupport) 
			piBRepElementOnSurfaceSupport->Release();   piBRepElementOnSurfaceSupport = NULL ;
	
	}
	else {
		// Releases useless pointers.
		piUpdateErrorOnGSMSewSkinBasic->Release();         piUpdateErrorOnGSMSewSkinBasic = NULL ;
		piGSMSewSkinBasic->Release();        piGSMSewSkinBasic = NULL ;
		return E_FAIL;
	}
    
	// Parameters 
	// ---------------------------------
    
/*
    // gets a pointer on CATIGeometricalElement on the first input curve
    CATIGeometricalElement *piGeometricalElementOnSurfaceToSew = NULL;
    
    rc = spiSpecOnSurfaceToSew->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElementOnSurfaceToSew );
    
    if ( FAILED(rc) ) 
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();         piUpdateErrorOnGSMSewSkinBasic = NULL ;
        piGSMSewSkinBasic->Release();        piGSMSewSkinBasic = NULL ;

        return E_FAIL;
    }
    
    // uses GetBodyResult to retrieve the first body
    CATBody_var spiBodyOfSurfaceToSew = piGeometricalElementOnSurfaceToSew->GetBodyResult();
    
    
    // releases useless pointer on CATIGeometricalElement
    if ( piGeometricalElementOnSurfaceToSew) { 
        piGeometricalElementOnSurfaceToSew->Release();    piGeometricalElementOnSurfaceToSew = NULL ;
    }
    // gets a pointer on CATIGeometricalElement on the second input curve
    CATIGeometricalElement *piGeometricalElementOnSurfaceSupport = NULL;
    
    rc = spiSpecOnSurfaceSupport->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElementOnSurfaceSupport );
    
    if ( FAILED(rc) ) 
    {
        // Releases useless pointers
        piUpdateErrorOnGSMSewSkinBasic->Release();       piUpdateErrorOnGSMSewSkinBasic = NULL ;
        piGSMSewSkinBasic->Release();        piGSMSewSkinBasic = NULL;
        
        return E_FAIL;
    }
    
    // uses GetBodyResult to retrieve the first body
    CATBody_var spiBodyOfSurfaceSupport = piGeometricalElementOnSurfaceSupport->GetBodyResult();
    
    // releases useless pointer on CATIGeometricalElement
    if ( piGeometricalElementOnSurfaceSupport) {
        piGeometricalElementOnSurfaceSupport->Release();    piGeometricalElementOnSurfaceSupport = NULL ;
    } 
    
   */  
    
	//===============================================================================================
    //
    // -4- Defining the procedural report
    //
    //===============================================================================================
    
    // gets a pointer on CATIMfProcReport
    CATIMfProcReport *piProcReport = NULL;
    
    rc = piGSMSewSkinBasic->QueryInterface( IID_CATIMfProcReport , (void**) &piProcReport );
    
    
    
    if ( FAILED(rc) ) 
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();
        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        
        return E_FAIL;
    }
    
    // defines which specifications take part in the creation of the report
    CATLISTV(CATBaseUnknown_var) ListSpec;
    CATListOfCATUnicodeString    ListKeys;
    
    ListSpec.Append( spiSpecOnSurfaceToSew     ); 
    ListKeys.Append( MfKeyNone          );
    
    ListSpec.Append( spiSpecOnSurfaceSupport     ); 
    ListKeys.Append( MfKeyNone          );
    
    // creates the procedural report
    piProcReport->CreateProcReport(ListSpec,ListKeys); 
    
    // Gets a pointer to the topological journal which contains the description 
    // of all basic topological operations.
    CATCGMJournalList *pCGMJournalList = piProcReport->GetCGMJournalList();
    // So far this journal is still empty, it will be filled by the topological operators that use it.
    
    
    //===============================================================================================
    //
    // -5- Sew the Skin 
    //
    //===============================================================================================
    
    // First, finds a geometric factory :
    
    // Gets a pointer on CATISpecObject.
    CATISpecObject *piSpecOnGSMSewSkinBasic = NULL;
    rc = QueryInterface( IID_CATISpecObject , (void**)& piSpecOnGSMSewSkinBasic );
    if ( FAILED(rc) )
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        piProcReport->Release();        piProcReport = NULL ;
        
        return E_FAIL;
    }
    
    // Retrieves the feature container.
    CATIContainer_var spiFeatContainer = piSpecOnGSMSewSkinBasic->GetFeatContainer();
    
    piSpecOnGSMSewSkinBasic->Release();
    piSpecOnGSMSewSkinBasic = NULL ;
    
    if(  NULL_var == spiFeatContainer )
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();
        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        
        piProcReport->Release();
        piProcReport = NULL ;
        
        return E_FAIL;
    }
    
    // Gets a pointer on CATIPrtContainer from the feature container
    CATIPrtContainer *piPartContainer = NULL;
    rc = spiFeatContainer->QueryInterface( IID_CATIPrtContainer , (void**) &piPartContainer );
    if ( FAILED(rc) ) 
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();
        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        
        piProcReport->Release();
        piProcReport = NULL ;
        
        return E_FAIL;
    }
    
    // Retrieves the geometry container from the pointer on CATIPrtContainer
    CATIContainer_var spiGeomContainer = piPartContainer->GetGeometricContainer(); 
    
    // Releases useless pointer
    piPartContainer->Release();
    piPartContainer = NULL ;
    
    // Gets a pointer on CATGeoFactory to extrude the curves.
    CATGeoFactory *piGeomFactory = NULL;
    
    rc = spiGeomContainer->QueryInterface( IID_CATGeoFactory , (void**) &piGeomFactory );
    
    if ( FAILED(rc) ) 
    {
        // Releases useless pointers.
        piUpdateErrorOnGSMSewSkinBasic->Release();
        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        
        piProcReport->Release();
        piProcReport = NULL ;
        
        return E_FAIL;
    }
    
    CATGSMOrientation Orientation = CATGSMSameOrientation;
    if (NULL !=  piGSMSewSkinBasic ) { 
         piGSMSewSkinBasic->GetOrientation(Orientation);
    }

    // ------------------------------------------------------
    // Load the ncgm input file (boundary.ncgm)
    //     and retrieve the input data 
    // ------------------------------------------------------
    //
#ifdef V5R17_CONFIG_MNGT 
	CATSoftwareConfiguration * pConfig = NULL;
	int IsConfigToStore = 0; 

	// Configuration Data
	CAAIGSMSewSkinBasic_var spGSMSewSkinBasic = piGSMSewSkinBasic ; 
	CATISpecObject_var spCurrentFeature = spGSMSewSkinBasic; 
	rc = CATMmrAlgoConfigServices::GetConfiguration( spCurrentFeature , pConfig , IsConfigToStore);
#else 
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    // CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
#endif     
    CATTopData * topdata = NULL;
    topdata = new CATTopData(pConfig, pCGMJournalList);
    
    CATTry 
    { 
		// ------------------------------------------------------
		// Creates and run the topological operator
		//     and retrieve the input data 
		// ------------------------------------------------------
        CATTopSewSkin * GSMSewSkinBasicOp = NULL;
        GSMSewSkinBasicOp = (CATTopSewSkin*) CATCreateSewSkin(piGeomFactory,
            topdata,spiBodyOfSurfaceSupport , spiBodyOfSurfaceToSew );
        //

        CATBody * piGSMSewSkinBasicBody = NULL ; 
        if (NULL!=GSMSewSkinBasicOp)
        {
            
			// Retrieves the Orientation and Invert the TopGSMSewSkinBasic if necessary
			if (Orientation == CATGSMInvertOrientation)
			    GSMSewSkinBasicOp->SetSelectionSide(FALSE);

            // Run 
            GSMSewSkinBasicOp->Run();

            // Retrieve Result  body 
            piGSMSewSkinBasicBody = GSMSewSkinBasicOp->GetResult( pCGMJournalList);
#ifdef DEBUG_GSD_CAASAMPLE 
            CATBoolean  Closed  = GSMSewSkinBasicOp-> ResultIsClosed() ;
            cout << " (CAAEGSMSewSkinBasicBuild::Build) Closed ?  = " ;
            if ( Closed)  cout << " TRUE " <<endl ;
            if (!Closed)  cout << " FALSE " <<endl ;
#endif 
            delete GSMSewSkinBasicOp;       GSMSewSkinBasicOp = NULL;
         } 
        
       
        if ( piGSMSewSkinBasicBody != NULL )
        {
        
            CATISpecObject_var     spSpecGSMSewSkinBasic = this ; 
 
            //===============================================================================================
            //
            // -6- Storing the procedural report
            //
            //     The report is built using  : the specifications given when creating it 
            //                                : the topological journal
            //
            //===============================================================================================
            
			piProcReport->StoreProcReport(piGSMSewSkinBasicBody,NoCopy);

#ifdef V5R17_CONFIG_MNGT 
			// Configuration Data
			if (IsConfigToStore ) { 
				rc = CATMmrAlgoConfigServices::StoreConfiguration(spCurrentFeature, pConfig);
			}
#endif  
		}
        else
        {
#ifdef DEBUG_GSD_CAASAMPLE 
        cout << " FAILED to create Swskin "<<endl; 
#endif 

            // creates an error if the intersection failed
            CATMfErrUpdate *pErrorNoIntersection = new CATMfErrUpdate();
            CATUnicodeString Diagnostic("The two surface are not lying on each other.");
            pErrorNoIntersection->SetDiagnostic(1,Diagnostic);
            CATThrow(pErrorNoIntersection);
            
        }
        
    }
    
    
    //===============================================================================================
    //
    // -7- Managing errors
    //
    //===============================================================================================
    
    CATCatch ( CATMfErrUpdate , pUpdateError)
    {
        //------------------------------------------------------------------------------
        // Catches CATMfErrUpdate errors
        //------------------------------------------------------------------------------
#ifdef DEBUG_GSD_CAASAMPLE 
        cout << " === UPDATE ERROR =="<<endl; 
#endif 
        // Builds a new update error.
        CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
        // Add it the diagnostic comming from the error previously caugth.
        pErrorToThrow->SetDiagnostic(1,pUpdateError->GetDiagnostic());
        // Destroys the previous error.
        ::Flush(pUpdateError);
        // Associates the error with the Combined Curve.
        if(NULL != piUpdateErrorOnGSMSewSkinBasic) piUpdateErrorOnGSMSewSkinBasic->SetUpdateError(pErrorToThrow);
        
        
        
        // Releases useless pointers.
        if(NULL != piUpdateErrorOnGSMSewSkinBasic) piUpdateErrorOnGSMSewSkinBasic->Release();
        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        if(NULL != piProcReport) piProcReport->Release();
        piProcReport = NULL ;
        if(NULL != piGeomFactory) piGeomFactory->Release();
        piGeomFactory = NULL ;
        
        // Dispatches the error.
        // In interactive mode, this errror will be caught by CATPrtUpdateCom that
        // knows how to handle such errors.
        CATThrow(pErrorToThrow);
    }
    
    CATCatch ( CATError , pError) 
    {
#ifdef DEBUG_GSD_CAASAMPLE 
        cout << " === ERROR =="<<endl; 
#endif 
        CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
        pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());
        ::Flush(pError);
        if(NULL != piUpdateErrorOnGSMSewSkinBasic) piUpdateErrorOnGSMSewSkinBasic->SetUpdateError(pErrorToThrow);
        
        
        // Releases useless pointers.
        if(NULL != piUpdateErrorOnGSMSewSkinBasic) piUpdateErrorOnGSMSewSkinBasic->Release();
        piUpdateErrorOnGSMSewSkinBasic = NULL ;
        if(NULL != piProcReport) piProcReport->Release();
        piProcReport = NULL ;
        if(NULL != piGeomFactory) piGeomFactory->Release();
        piGeomFactory = NULL ;
        
        CATThrow(pErrorToThrow);
    }   
    
    
    CATEndTry;
    
    if (pConfig!= NULL)   {pConfig->Release(); pConfig = NULL ; } 
    // if (NULL!= pCGMJournalList) {delete pCGMJournalList;pCGMJournalList = NULL;}			
    if (NULL!= topdata) {delete topdata; topdata = NULL;}			

    
    if(NULL != piUpdateErrorOnGSMSewSkinBasic) piUpdateErrorOnGSMSewSkinBasic->Release();
    piUpdateErrorOnGSMSewSkinBasic = NULL ;
    
    if(NULL != piProcReport)  piProcReport->Release();
    piProcReport = NULL ;

    if (NULL != piGSMSewSkinBasic ) { 
		piGSMSewSkinBasic->Release();	piGSMSewSkinBasic = NULL ;
    }
    if(NULL != piGeomFactory) piGeomFactory->Release();
    piGeomFactory = NULL ;
    
#ifdef DEBUG_GSD_CAASAMPLE 
     cout << " (CAAEGSMSewSkinBasicBuild::Build) Exit   " <<   endl;
#endif     
    return S_OK;
}

