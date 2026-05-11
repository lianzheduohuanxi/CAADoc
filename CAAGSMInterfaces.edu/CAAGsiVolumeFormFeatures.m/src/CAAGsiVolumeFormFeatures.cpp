
// COPYRIGHT DASSAULT SYSTEMES 2000

//============================================================================================
// Sample code for : Generative Shape Design Interfaces
// Mission         : - Creates a parametric Volume form using Generative Shape Design  and Part Design API 
//                       Volume Extrude, Volume Revol , multiSections Volume, Swept Volume , Thick Surface, Closed Surface 
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
//   CAAGsiVolumeFormFeatures  ..\CAAGsiStartVolume.CATPart .\CAAGsiVolumeFormFeaturesGenerated.CATPart  
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
#include "CATLISTV_CATISpecObject.h" // To handle List of Features

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
#include "CATIGSMTool.h"            

// ObjectSpecsModeler includes
#include "CATISpecObject.h"

// GSD 
#include "CATGSMContextDef.h"

#include "CATIGSMFactory.h"   
#include "CATIGSMDirection.h"               
#include "CATIGSMPoint.h"            
#include "CATIGSMCircleCtrRad.h"          
#include "CATIGSMPolyline.h"         
#include "CATIGSMExtrude.h"            
#include "CATIGSMRevol.h"            
#include "CATIGSMLoft.h"            
#include "CATIGSMSweepUnspec.h"            
#include "CATIGSMProceduralView.h"
          

// Part design 
#include "CATIPrtFactory.h"            
#include "CATIPrtBooleanFactory.h"            
#include "CATPrtEnum.h"            

//Knowledge 
#include "CATICkeParmFactory.h"         
#include "CATICkeParm.h"            


#include "iostream.h"                // To have cout 

#define GEOMETRICAL_SET 0 
#define ORDERED_GEOMETRICAL_SET 1 


// -----------------------------------------------------------------------------
// Local Tools 
// -----------------------------------------------------------------------------

CATICkeParm_var 
CreateLength (const CATICkeParmFactory_var spCkeFact, const char* ipNameParam ,const double iValue) 
{
    
    CATICkeParm_var  spParm = NULL_var;
    spParm    = spCkeFact -> CreateLength( ipNameParam,iValue/1000.);
    if (NULL_var == spParm) {
        cout << "ERROR in creating Cke length paramater" << endl << flush;
    }
    return spParm ;
    
    
}
CATICkeParm_var 
CreateAngle (const CATICkeParmFactory_var spCkeFact, const char* ipNameParam ,const double iValue) 
{
    
    CATICkeParm_var  spParm = NULL_var;
    spParm    = spCkeFact -> CreateAngle ( ipNameParam, (iValue/180.)*CATPI);
    if (NULL_var == spParm) {
        cout << "ERROR in creating Cke length paramater" << endl << flush;
    }
    return spParm;
    
}
// -----------------------------------------------------------------------------
// Main 
// Test Create a Volume form 
// -----------------------------------------------------------------------------
int main(int iArgc, 			       // Number of arguments (2)
         char *iArgv[])                 // Paths  Input and Ouput Part 
{
    // Create a parametric Volume form using Generative Shape Design Feature
    int RetCode = 0 ;
    HRESULT rc  = S_OK;
    
    // Checks arguments
    cout << "(CAAGsiVolumeFormFeatures) iArgc = "<< iArgc << endl;
    for (int i=0;i<iArgc;i++) cout << "(CAAGsiVolumeFormFeatures) iArgv =[ "<<i<<" ]= "<< iArgv[i] << endl;
    // if ( 4 <  iArgc) return 1;
    
    char*  pPartNameInput  = NULL;
    pPartNameInput =  iArgv[1];

    char*  pPartNameOutput = NULL;
    if (iArgc > 2  )  { 
        pPartNameOutput =  iArgv[2];
    } 
    
    
    cout << "====================================================================" << endl;
    cout << "=========        Batch : Start Design a Volume   Features ==========" << endl;
    cout << "====================================================================" << endl;
    cout << "(CAAGsiVolumeFormFeatures) Start"  << endl;
    cout << endl;
    
    // ----------------------------------------------------------------------------
    // USE CASE 
    // ----------------------------------------------------------------------------
    int TestCaseError = 0;  
    // --------------------------------------------------------------
    // -1- Init 
    // --------------------------------------------------------------
    

    
    // creates a session
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
    CATIGSMFactory_var spGsmFact; 
    if ( NULL !=piPartContainer ) { 
        CATIPrtFactory * _pPrtFact =NULL; 
        
        rc = piPartContainer -> QueryInterface(IID_CATIPrtFactory ,(void**)&_pPrtFact);
        if (SUCCEEDED(rc) ) {
            spPrtFact =  _pPrtFact;
            if (_pPrtFact) _pPrtFact -> Release(); _pPrtFact = NULL; 
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
    
  
    // Volume Form features 
    //---------------------------------------------------------------
    if (NULL_var != spCont && 
        NULL_var != spGsmFact && 
        NULL_var != spPrtFact ) {


        CATICkeParm_var spCkeLgStart,  spCkeLgEnd ;
        CATICkeParm_var spCkeAngStart, spCkeAngEnd ;

        // -------------------------------------------------------------
        // -1- Init 
        // --------------------------------------------------------------
        CATICkeParmFactory_var spCkeFact = spGsmFact ;
        
        CATListValCATISpecObject_var	spListPlane;
        if(!!spPrtPart)  spListPlane = spPrtPart -> GetReferencePlanes();
        //---------------------------------------------------------------
        // -2- Ordered Geometrical Set Creation 
        //---------------------------------------------------------------
        
        CATLISTV(CATISpecObject_var) ListPoints; 
        CATLISTV(CATISpecObject_var) ListRadius; 
        
        // Create GSM Tool and set this GSMTool as Current Object in order to create all Features
        // in this Open Body    
        cout << "(CAAGsiVolumeFormFeatures) Create OGS " << endl;
        
        int CreationLocation = 1  ;  // Under Part 
        int TypeOfGeometricalSet  =  ORDERED_GEOMETRICAL_SET ;
        
        int iDiag = 0 ;
        CATISpecObject_var spSpecTool  ;
        CATIGSMTool_var spTool  ;
        // int setAsCurrent = 1;
        // spTool = CAAGsiCreateSurfacicFeatureSet(spCont ,"Volume",setAsCurrent,0,TypeOfGeometricalSet);
        rc = CAAGsiCreateGeometricFeatureSets (spCont, "Volume", NULL_var  ,spSpecTool, iDiag ,CreationLocation,TypeOfGeometricalSet) ;
        if (SUCCEEDED(rc) ) { 
            spTool = spSpecTool ; 
        }
        
        // ----------------------------------------------------------------------------
        // 3- Creating  Features 
        // ----------------------------------------------------------------------------
        CATIGSMDirection_var DirRef ;  
        
        // Create Volume Extrude 
        // --------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Create Volume Extrude   " << endl;
        
        CATISpecObject_var SpecSkethToExtrude = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Polyline.1"));
        CATISpecObject_var SpecPlaneRef1 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Plane.15") );
        spCkeLgStart= CreateLength ( spCkeFact,  "Start",   0 );
        spCkeLgEnd  = CreateLength ( spCkeFact,  "End"  , 100.0);
        DirRef =spGsmFact -> CreateDirection ( SpecPlaneRef1); 
        
        CATIGSMExtrude_var  spExtrude1  =  
            spGsmFact -> CreateExtrude ( SpecSkethToExtrude  , DirRef  , spCkeLgStart, spCkeLgEnd, TRUE) ;
        
        //Initialize volume Context
        spExtrude1 -> SetContext(CATGSMVolumeCtxt) ;
        
        // Insert in procedural view and Update
        CATISpecObject_var spSpecExtr1 = spExtrude1 ;
        if (NULL_var != spSpecExtr1) {
            CATIGSMProceduralView_var ispProcView = spSpecExtr1;
            if (NULL_var != ispProcView ) {
                rc = ispProcView ->InsertInProceduralView();
            }
        }
        CAAGsiObjectUpdate(spSpecExtr1) ;
        // Create Volume Revolution 
        // --------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Create Volume revolution   " << endl;
        
        CATISpecObject_var SpecSkethToRevol = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Sketch.2") );
        CATISpecObject_var SpecLineRef1 = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Line.4") );
        
        spCkeAngStart= CreateAngle ( spCkeFact,  "Ang1",   180.0 );
        spCkeAngEnd  = CreateAngle ( spCkeFact,  "Ang2"  , 180.0 );
      
        
        CATIGSMRevol_var  spRevol1  = 
            spGsmFact -> CreateRevol (SpecSkethToRevol,    SpecLineRef1 , spCkeAngStart, spCkeAngEnd ,  FALSE);

        //Initialize volume Context
        spRevol1 -> SetContext(CATGSMVolumeCtxt) ;

        // Insert in procedural view and Update
        CATISpecObject_var spSpecRevol1 = spRevol1 ;
        if (NULL_var != spSpecRevol1 ) {
            CATIGSMProceduralView_var ispProcView = spSpecRevol1 ;
            if (NULL_var != ispProcView ) {
                rc = ispProcView ->InsertInProceduralView();
            }
        }
        CAAGsiObjectUpdate(spSpecRevol1 ) ;
        
        
        // Create Multi Section volume 
        // --------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Create MultiSection Volume " << endl;
        
        CATListValCATISpecObject_var	spListSections;
        CATISpecObject_var SpecSection; 
        SpecSection = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Polyline.2") );spListSections.Append(SpecSection); 
        SpecSection = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Polyline.3") );spListSections.Append(SpecSection); 
        SpecSection = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Polyline.4") );spListSections.Append(SpecSection); 
        
        CATListValCATISpecObject_var	spListGuides;
        CATISpecObject_var SpecGuide; 
        SpecGuide = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Spline.20") );spListGuides.Append(SpecGuide); 
        SpecGuide = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Spline.22") );spListGuides.Append(SpecGuide); 
        SpecGuide = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Spline.23") );spListGuides.Append(SpecGuide);
        SpecGuide = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Spline.21") );spListGuides.Append(SpecGuide);
        
        
        CATIGSMLoft_var  spLoft1  = 
            spGsmFact -> CreateLoft (spListSections,spListGuides);
        
        //Initialize volume Context
        spLoft1  ->  SetContext(CATGSMVolumeCtxt) ; 

        // Insert in procedural view and Update
        CATISpecObject_var spSpecLoft1 = spLoft1 ;
        if (NULL_var != spSpecLoft1 ) {
            CATIGSMProceduralView_var ispProcView = spSpecLoft1 ;
            if (NULL_var != ispProcView ) {
                rc = ispProcView ->InsertInProceduralView();
            }
        }
        CAAGsiObjectUpdate(spSpecLoft1 ) ;
        
        // Create Swept volume 
        // --------------------------------------------------------------
        cout << "(CAAGsiVolumeFormFeatures) Create Swept Volume " << endl;
        
        CATISpecObject_var SpecProfile = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Join.2") );
        CATISpecObject_var SpecGuideSw = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Spline.15") );
        CATISpecObject_var SpecSpine   = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Line.7") );
        
        CATIGSMSweepUnspec_var spExplSweep1  = 
            spGsmFact -> CreateExplicitSweep(SpecGuideSw,SpecProfile,SpecSpine,NULL_var , NULL_var );
        
        //Initialize volume Context
        spExplSweep1 -> SetContext(CATGSMVolumeCtxt) ;
        
        // Insert in procedural view and Update
        CATISpecObject_var spSpecSweep1 = spExplSweep1 ;
        if (NULL_var != spSpecSweep1 ) {
            CATIGSMProceduralView_var ispProcView = spSpecSweep1 ;
            if (NULL_var != ispProcView ) {
                rc = ispProcView ->InsertInProceduralView();
            }
        }
        CAAGsiObjectUpdate(spSpecSweep1 ) ;
        
        // Create Thick Surface 
        // --------------------------------------------------------------
        // Note : PartFactory or PartBooleanFactory automatically insert feature in the procedural view at creation 
        // Thus the InsertProceduralView to call for feature created by Gsd Factory do not have to be done 
        cout << "(CAAGsiVolumeFormFeatures) Create Thick Surface   " << endl;
        
        CATISpecObject_var SpecShape  = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Extrude.5"));
        
        CATPrtOffsetSens iIsensOffset = NormalSide; 
        CATISpecObject_var spThick = 
            spPrtFact -> CreateVolumicOffset (SpecShape, iIsensOffset,0.00, 10.00); 
        
        // Update 
        CAAGsiObjectUpdate(spThick) ;
        
        // Create Close Surface 
        // --------------------------------------------------------------
        // Note : PartFactory or PartBooleanFactory automatically insert feature in the procedural view at creation 
        // Thus the InsertProceduralView to call for feature created by Gsd Factory do not have to be done 
        cout << "(CAAGsiVolumeFormFeatures) Create Close Surface   " << endl;
        CATISpecObject_var SpecShapeToClose  = CAAGsiSearchFeatureFromName(spPrtPart,CATUnicodeString("Revolute.1"));
        
        
        CATISpecObject_var spClose = 
            spPrtFact -> CreateVolumicCloseSurface  (SpecShapeToClose); 
        
        // Update 
        CAAGsiObjectUpdate(spClose) ;
        
        
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
        cout << "(CAAGsiVolumeFormFeatures) Save : "<< pPartNameOutput << endl;
        rc = CATDocumentServices::SaveAs  (*pDoc,pPartNameOutput );
        if (FAILED(rc)) RetCode = 4 ;        
    }
    
    // Close Session
    // ------------------------------------
    cout << "(CAAGsiVolumeFormFeatures) Close session " << endl;
    CATDocumentServices::Remove(*pDoc); 
    if (FAILED(rc)) RetCode = 5 ;        
    
    Delete_Session("SampleSession");
    cout << "(CAAGsiVolumeFormFeatures) End "  << RetCode << endl;
    cout << "====================================================================" << endl;
    cout << "=========        Batch : End Design a Volume               =========" << endl;
    cout << "====================================================================" << endl;
    cout << endl;
    
    return RetCode ;
}

