
// COPYRIGHT DASSAULT SYSTEMES 2000


//============================================================================================
// Sample code for : Generative Shape Design Interfaces
// Mission         : - Creates a booleean operation on parametric Volume using Part Design Boolean API for volume 
//                       Add, Remove, Intersection 
//                   - Saves the resulting Part 
//
// Type		   : Batch program
// Inputs	   : - Path for the Input Part (.\
//               - Path for saving the resulting Part (If no argument specified the part is not saved) 
// Outputs         : Return code is 0 if program worked ok, >0 otherwise
//	 
// Illustrates     : o How to Create a Part Document
//                   o How to Create a Ordered Geometrical Set 
//                   o How to Create volume standard form feature 
//                   o How to Save a Part Document  
//==========================================================================
//  How to execute :
//  
//     CAAGsiVolumeFormFeatures  
//          with:   Path of the part representing the input required features and path of the resulting part
//    
//  Example:
// 
//   CAAGsiVolumeBooleanOpes  ..\CAAGsiStartVolumeForBoolean.CATPart .\CAAGsiVolumeBooleanGenerated.CATPart  
//
//  Return code:
//  
//   0 successful execution
//   1 bad number of arguments
//   2 problem during document creation
//   3 problem during getting factories 
//   4 problem during Part Save 
//   5 problem during close session 
//============================================================================================
#include "CAAGsiServices.h"         // To call generic services   

#include "CATUnicodeString.h"

// ObjectModelerBase includes
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSession.h"
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATIContainer.h"
#include "CATIAlias.h"


// MecModInterfaces includes
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

// ObjectSpecsModeler includes
#include "CATISpecObject.h"


// Shape Design 
#include "CATLISTV_CATISpecObject.h" // To handle List of Features

#include "CATGSMContextDef.h"

#include "CATIGSMTool.h"              
#include "CATIGSMFactory.h"           
#include "CATIGSMPoint.h"             
#include "CATIGSMCircleCtrRad.h"             
#include "CATIGSMPolyline.h"           
#include "CATIGSMExtrude.h"             
#include "CATIPrtFactory.h"              
#include "CATIPrtBooleanFactory.h"           

// Knowledge 
#include "CATICkeParmFactory.h"     
#include "CATICkeParm.h"            


#include "iostream.h"            


#define BOOLEAN_OPE_ON_VOLUME 4 

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Main 
// Test Create a Volume form 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int iArgc, 			// Number of arguments (1)
         char *iArgv[])                 // Path for the created Part 
{
    // Create a parametric Volume form using Generative Shape Design Feature
    int RetCode = 0 ;
    HRESULT rc  = S_OK;
    
    // Checks arguments
    cout << "(CAAGsiVolumeForBoolean) iArgc = "<< iArgc << endl;
    for (int i=0;i<iArgc;i++) cout << "(CAAGsiVolumeForBoolean) iArgv =[ "<<i<<" ]= "<< iArgv[i] << endl;
    if ( 3 <  iArgc) return 1;
        // if ( 4 <  iArgc) return 1;
    
    char*  pPartNameInput  = NULL;
    pPartNameInput =  iArgv[1];

    char*  pPartNameOutput = NULL;
    if (iArgc > 2  )  { 
        pPartNameOutput =  iArgv[2];
    } 

    int  pTypeOfTool= 1;
    if (iArgc == 4 )  { 
        pTypeOfTool =atoi (iArgv[3]); 
    } 
    
    
    cout << "====================================================================" << endl;
    cout << "=========        Batch : Start Design a Volume             =========" << endl;
    cout << "====================================================================" << endl;
    cout << "(CAAGsiVolumeForBoolean) Start"  << endl;
    cout << endl;
    
    // ----------------------------------------------------------------------------
    // USE CASE 
    // ----------------------------------------------------------------------------
    // ----------------------------------------------------------------------------
    // USE CASE 
    // ----------------------------------------------------------------------------
    int TestCaseError = 0;  
    // --------------------------------------------------------------
    // -1- Init 
    // --------------------------------------------------------------
    
        char *pSessionName = "SampleSession";
    CATSession *pSession = 0;
    rc = Create_Session(pSessionName, pSession) ; 

    // loads the document and initializes it
    CATDocument *pDoc = 0;
    CATDocumentServices::OpenDocument(pPartNameInput, pDoc) ; 
    if (NULL != pDoc) { 
        cout <<"The input document " << pPartNameInput<< " is opened" << endl ;
    }
    else     {
        cout <<"ERROR : open  document FAILED " << endl ;
        return 1 ;
    }
   

    // PrtContainer 
    //---------------------------------------------------------------
    CATIContainer_var spCont ; 
    CATIPrtContainer *piPartContainer = NULL ; 
    CATIPrtPart_var spPrtPart; 
    
    if ( NULL != pDoc ) { 
        // queries on the document to get the root container
        CATInit *pDocAsInit = NULL; 
        pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit)  ; 
        if ( NULL != pDocAsInit ) {
            
            // Extracts from document a reference to its part in hPartAsRequest
            piPartContainer = 
                (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");
            pDocAsInit->Release();           pDocAsInit = NULL ;
            
            if( NULL != piPartContainer )      {
                CATISpecObject_var spPart = piPartContainer->GetPart() ; 
                spPrtPart = spPart ;
            }                  
        }    
    }
    // Factory 
    //---------------------------------------------------------------
    CATIPrtFactory_var spPrtFact; 
    CATIPrtBooleanFactory_var spBoolPrtFact; 
    CATIGSMFactory_var spGsmFact; 
    if ( NULL !=piPartContainer ) { 
        CATIPrtFactory * _pPrtFact =NULL; 
        
        rc = piPartContainer -> QueryInterface(IID_CATIPrtFactory ,(void**)&_pPrtFact);
        if (SUCCEEDED(rc) ) {
            spPrtFact =  _pPrtFact;
            if (_pPrtFact) _pPrtFact -> Release(); _pPrtFact = NULL; 
        }
        
        CATIPrtBooleanFactory * _pBoolPrtFact =NULL; 
        rc = piPartContainer -> QueryInterface(IID_CATIPrtBooleanFactory ,(void**)&_pBoolPrtFact);
        if (SUCCEEDED(rc) ) {
            spBoolPrtFact =  _pBoolPrtFact;
            if (_pBoolPrtFact) _pBoolPrtFact -> Release(); _pBoolPrtFact = NULL; 
        }
        
        CATIGSMFactory * _pFact =NULL; 
        rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory ,(void**)&_pFact);
        if (SUCCEEDED(rc) ) {
            spGsmFact =  _pFact;
            if (_pFact) _pFact -> Release(); _pFact = NULL; 
        }
        
    }
    spCont = piPartContainer ; 
    if ( NULL !=piPartContainer ) piPartContainer -> Release(); piPartContainer = NULL; 
    
    
    if (NULL_var != spCont && 
        NULL_var != spGsmFact && 
        NULL_var != spBoolPrtFact ) {
        //    -------------------------------------------------------------
        // -1- Init 
        // --------------------------------------------------------------
        CATICkeParmFactory_var spCkeFact = spGsmFact ;
        
        CATListValCATISpecObject_var	spListPlane;
        if(!!spPrtPart)  spListPlane = spPrtPart -> GetReferencePlanes();
        //---------------------------------------------------------------
        // -2- Open Body Creation 
        //---------------------------------------------------------------
        
        CATLISTV(CATISpecObject_var) ListPoints; 
        CATLISTV(CATISpecObject_var) ListRadius; 
        
        // Create GSM Tool and set this GSMTool as Current Object in order to create all Features
        // in this Open Body    
        cout << "(CAAGsiVolumeForBoolean) Create OGS " << endl;
        
        int CreationLocation = 1 ; // Under Part 
        int TypeOfGeometricalSet  =  pTypeOfTool ;
       
        int iDiag = 0 ;
        CATISpecObject_var spSpecTool  ;
        CATIGSMTool_var spTool  ;
        // int setAsCurrent     = 1;
        // spTool = CAAGsiCreateSurfacicFeatureSet(spCont ,"VolumeBoolean",setAsCurrent,CreationLocation,TypeOfGeometricalSet);
        rc = CAAGsiCreateGeometricFeatureSets (spCont, "VolumeBoolean", NULL_var  ,spSpecTool, iDiag ,CreationLocation,TypeOfGeometricalSet) ;
        if (SUCCEEDED(rc) ) { 
            spTool = spSpecTool ; 
        }
        // ----------------------------------------------------------------------------
        // -3- Boolean ooperation on Volumes 
        // ----------------------------------------------------------------------------
        // Note : PartFactory or PartBooleanFactory automatically insert feature in the procedural view at creation 
        // Thus the InsertProceduralView to call for feature created by Gsd Factory do not have to be done 
            
        // Add 
        // ----------------------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Add    " << endl;
        CATISpecObject_var spSpecExtr1 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.10"));
        CATISpecObject_var spSpecExtr2 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.11"));
        
        CATISpecObject_var spSpecAdd = spBoolPrtFact -> CreateAdd ( spSpecExtr1,spSpecExtr2 ,BOOLEAN_OPE_ON_VOLUME ) ;
        CAAGsiObjectUpdate(spSpecAdd) ;
        
        // Remove 
        // ----------------------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Remove     " << endl;
        CATISpecObject_var spSpecExtr3 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.12"));
        CATISpecObject_var spSpecRemove = spBoolPrtFact -> CreateRemove ( spSpecAdd,spSpecExtr3 ,BOOLEAN_OPE_ON_VOLUME ) ;
        CAAGsiObjectUpdate(spSpecRemove) ;

        // Intersection 
        // ----------------------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Intersection  " << endl;
        CATISpecObject_var spSpecExtr4 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.15"));
        CATISpecObject_var spSpecExtr5 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.16"));

        CATISpecObject_var spSpecInt = spBoolPrtFact -> CreateIntersect ( spSpecExtr4,spSpecExtr5 ,BOOLEAN_OPE_ON_VOLUME ) ;
        CAAGsiObjectUpdate(spSpecInt) ;
    
        // Create GSM Tool and set this GSMTool as Current Object in order to create all Features
        // in this Open Body    
        cout << "(CAAGsiVolumeForBoolean) Create OGS " << endl;
        
        spTool = NULL_var ; 
        //  spTool  = CAAGsiCreateSurfacicFeatureSet(spCont ,"VolumeMold",setAsCurrent,CreationLocation,TypeOfGeometricalSet);
        rc = CAAGsiCreateGeometricFeatureSets (spCont, "VolumeMold", NULL_var  ,spSpecTool, iDiag ,CreationLocation,TypeOfGeometricalSet) ;
        if (SUCCEEDED(rc) ) { 
            spTool = spSpecTool ; 
        }
       
       
        // Remove 
        // ----------------------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Intersection  " << endl;
        CATISpecObject_var spSpecBase1 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.17"));
        CATISpecObject_var spSpecBottle = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Revolve.1"));
        CATISpecObject_var spSpecCavity0 = spBoolPrtFact -> CreateRemove ( spSpecBase1, spSpecBottle ,BOOLEAN_OPE_ON_VOLUME ) ;
        CAAGsiObjectUpdate(spSpecCavity0) ;

        CATISpecObject_var spSpecLetters = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Volume Extrude.18"));
        CATISpecObject_var spSpecCavity1 = spBoolPrtFact -> CreateRemove ( spSpecCavity0,spSpecLetters ,BOOLEAN_OPE_ON_VOLUME ) ;
        CAAGsiObjectUpdate(spSpecCavity1) ;

        

    }
    else 
        RetCode = 3 ; 

    // ----------------------------------------------------------------------------
    // 4- Exit 
    // ----------------------------------------------------------------------------
    
    // Save Part 
    // ------------------------------------
    // Saves the modified pad in the second input path
    
    if ( NULL != pPartNameOutput && NULL != pDoc ) {
        cout << "(CAAGsiVolumeForBoolean) Save : "<< pPartNameOutput  << endl;
        rc = CATDocumentServices::SaveAs  (*pDoc,pPartNameOutput);
        if (FAILED(rc)) RetCode = 4 ;        
    }
    
    // Close Session
    // ------------------------------------
    cout << "(CAAGsiVolumeForBoolean) Close session " << endl;
    CATDocumentServices::Remove(*pDoc); 
    if (FAILED(rc)) RetCode = 5 ;        
    
    Delete_Session("SampleSession");
    cout << "(CAAGsiVolumeForBoolean) End "  << RetCode << endl;
    cout << "====================================================================" << endl;
    cout << "=========        Batch : End Design a Volume               =========" << endl;
    cout << "====================================================================" << endl;
    cout << endl;
    
    return RetCode ;
}

