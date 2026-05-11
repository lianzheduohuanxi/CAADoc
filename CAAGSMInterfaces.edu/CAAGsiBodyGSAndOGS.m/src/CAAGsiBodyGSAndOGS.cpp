
// COPYRIGHT DASSAULT SYSTEMES 2000

//============================================================================================
// Sample code for : Generative Shape Design Interfaces
// Mission         : - Creates a Body/GS or OGS for using Generative Shape Design Feature
//                   - Insert GSD feature in the created set (Volume are insert only in GS and OGS) 
//                   - Perform absorbant feature creation in OGS (Split, Add,Remove)  
//                   - Test settting current feature before Insert  
//                   - Saves the resulting Part 
//
// Type		   : Batch program
// Inputs	   : Path for saving the resulting Part (If no argument specified the part is not saved) 
// Outputs         : Return code is 0 if program worked ok, >0 otherwise
//	 
// Illustrates     : o How to Create a Part Document
//                   o How to Create a GSMTool and set it as current  
//                   o How to Create Points, Lines, Planes, Circles, Sweeps and Lofts
//                   o How to Save a Part Document  
//==========================================================================
//  How to execute :
//  
//     CAAGsiBodyGSAndOGS Part 
//          with:   Part representing the path of the created part
//    
//  Example:
// 
//   CAAGsiBodyGSAndOGS  E:\tmp\CAAGsiBodyGSAndOGS.CATPart 
//
//  Return code:
//  
//   0 successful execution
//   1 bad number of arguments
//   2 problem during document creation
//   3 problem during document deletion 
//   4 problem during Part Save 
//============================================================================================
#include "CAAGsiServices.h"         // To call Creation Services and Init,Save, Close.

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
#include "CATLISTV_CATISpecObject.h" // To handle List of Features

// GSD 
#include "CATGSMContextDef.h"
#include "CATGSMOrientation.h"

#include "CATIGSMFactory.h"            
#include "CATIGSMDirection.h"            
#include "CATIGSMPoint.h"            
#include "CATIGSMPointCoord.h"            
#include "CATIGSMCircleCtrRad.h"         
#include "CATIGSMPolyline.h"           
#include "CATIGSMSpline.h"          
#include "CATIGSMExtrude.h"     
#include "CATIGSMSplit.h"
#include "CATIGSMSweepUnspec.h" 

//Part 
#include "CATIPrtFactory.h"             
#include "CATIPrtBooleanFactory.h"            
#include "CATIPad.h"            

// Knowledge 
#include "CATICkeParm.h"             // To handle GSMTool  
#include "CATICkeParmFactory.h"             // To handle GSMTool  

// 
#include "CATIAlias.h"

//Visualization framework 
#include "CATIModelEvents.h"
#include "CATModify.h"

// IO Traces 
#include "iostream.h"            


#define ContextForBooleanOperationOnVolumeInPartFactory 4 

#define TYPE_GeometricalSet         0  
#define TYPE_OrderedGeometricalSet  1 
#define TYPE_Body                   2 

#define UNDER_Current  0
#define UNDER_Part     1


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

CATISpecObject_var 
CreateDatumPoint  (const CATIGSMFactory_var spGsmFact,  double *coord) 
{
    CATISpecObject_var  Pt = spGsmFact -> CreatePoint ( coord );
    if (NULL_var != Pt ) {
        CAAGsiInsertInProceduralView( Pt , NULL_var ) ; CAAGsiObjectUpdate(Pt) ; 
    }
    else { 
        cout << "ERROR in creating Datum Point " << endl ;
    }
    return Pt ;
    
}
CATISpecObject_var 
CreatePointCoord  (const CATIGSMFactory_var spGsmFact,  double *coord) 
{
    CATICkeParmFactory_var spCkeFact = spGsmFact ;

    CATICkeParm_var X  = CreateLength ( spCkeFact, "X"  , coord[0] ) ;
    CATICkeParm_var Y  = CreateLength ( spCkeFact, "Y"  , coord[1] ) ;
    CATICkeParm_var Z  = CreateLength ( spCkeFact, "Z"  , coord[2] ) ;
   
    CATISpecObject_var  Pt = spGsmFact -> CreatePoint ( X, Y, Z ) ;
    if (NULL_var != Pt ) {
         CAAGsiInsertInProceduralView( Pt , NULL_var ) ; CAAGsiObjectUpdate(Pt) ; 
    }
    else { 
        cout << "ERROR in creating Point Coord  " << endl ;
    }
    return Pt ;
    
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Main 
// Test Create a TstGSAndOGS form 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int iArgc, 			// Number of arguments (1)
         char *iArgv[])                 // Path for the created Part 
{
    // Create a parametric TstGSAndOGS form using Generative Shape Design Feature
    int RetCode = 0 ;
    
    HRESULT rc  = S_OK;
    
    // Checks arguments
    cout << "(CAAGsiBodyGSAndOGS) iArgc = "<< iArgc << endl;
    for (int i=0;i<iArgc;i++) cout << "(CAAGsiBodyGSAndOGS) iArgv =[ "<<i<<" ]= "<< iArgv[i] << endl;
    if ( 3 <  iArgc) return 1;
    
    char*  pPartName = NULL;
    pPartName=  iArgv[1];
    
    
    cout << "====================================================================" << endl;
    cout << "=========        Batch : Start Design a BodyGSAndOGS             =========" << endl;
    cout << "====================================================================" << endl;
    cout << "(CAAGsiBodyGSAndOGS) Start"  << endl;
    
    // ----------------------------------------------------------------------------
    // USE CASE 
    // ----------------------------------------------------------------------------
    int TestCaseError = 0;  
    // --------------------------------------------------------------
    // -1- Init 
    // --------------------------------------------------------------
    
    cout << endl;
    cout << "(CAAGsiBodyGSAndOGS) 1- Create a new document "  << endl;
    // creates a session
    char *pSessionName = "SampleSession";
    CATSession *pSession = NULL; 
    rc = Create_Session(pSessionName, pSession); 
    if (NULL == pSession ) {
        cout << "(CAAGsiBodyGSAndOGS) ERROR: Create_Session" << endl << flush;
        RetCode = 1 ; 
    }
    
    // loads the document and initializes it
    CATDocument *pDoc = NULL; 
    rc = CATDocumentServices::New("CATPart",pDoc);
    
    if (NULL == pDoc ) {
        cout << "(CAAGsiBodyGSAndOGS) ERROR CATDocumentServices::NewDocument" << endl << flush;
        RetCode = 2 ; 
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
    
    
    spCont = piPartContainer ; 
    
    
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
    if ( NULL !=piPartContainer ) piPartContainer -> Release(); piPartContainer = NULL; 
    
    // Create Geometric Features Set 
    //---------------------------------------------------------------
    
    cout << endl;
    cout << "(CAAGsiBodyGSAndOGS) 2- Create a geometrical features set "   << endl;
    
    int Diag = -1 ; 
    int iTypeOfTool ;
        
    CATISpecObject_var spSpecTool ; 
    CATISpecObject_var spParentTool ; 
    CATUnicodeString iName ; 

    // Create Features 
    //---------------------------------------------------------------
    if ( RetCode == 0 ) { 
        // -------------------------------------------------------------
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
        
        cout << endl;
        cout << "(CAAGsiBodyGSAndOGS) 3- Create features "   << endl;
        

        // ======================================================================================================
        // GS 
        // ======================================================================================================
        cout << "(CAAGsiBodyGSAndOGS) Create a GeometricalSet (GS)" <<endl ;

        
        iName="";
        iTypeOfTool  = TYPE_GeometricalSet ; 
        spParentTool = NULL_var ;
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName , spParentTool , spSpecTool , Diag ,  UNDER_Part ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl << flush;
            RetCode = 3 ;   
        }
        spParentTool = spSpecTool ; 
        spSpecTool = NULL_var ; 
    

        //---------------------------------------------------------------
        // 3- Creating  Features 
        // ----------------------------------------------------------------------------
        iName = "PointAndWire"; 
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName , spParentTool , spSpecTool , Diag , UNDER_Current ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl ;
            
        }
        
        // Point and Wires 
        // -------------------------------------------------------------
        cout << "(CAAGsiBodyGSAndOGS) Create points and wires " << endl;
        double pcoord1[3] = {    0.0 ,       0.0 , 200.0 } ; 
        double pcoord2[3] = {    0.0 ,      20.0 , 200.0 } ; 
        double pcoord3[3] = {    0.0 ,      20.0 , 220.0 } ; 
        double pcoord4[3] = {    0.0 ,      40.0 , 220.0 } ; 
        double pcoord5[3] = {    0.0 ,      40.0 , 240.0 } ; 
        double pcoord6[3] = {    0.0 ,      60.0 , 240.0 } ; 
        double pcoord7[3] = {    0.0 ,      60.0 , 260.0 } ; 
        double pcoord8[3] = {    0.0 ,       0.0 , 260.0 } ; 
        double RadPoly    = 20.0 ;
        CATISpecObject_var spCkeRadPoly  = CreateLength ( spCkeFact,  "Radius", RadPoly  );
        
        CATISpecObject_var  Pt ;
        Pt = CreatePointCoord ( spGsmFact, pcoord1 ) ;ListPoints.Append(Pt);   ListRadius.Append(NULL_var);
        Pt = CreatePointCoord ( spGsmFact, pcoord2 ) ;ListPoints.Append(Pt);   ListRadius.Append(spCkeRadPoly);
        Pt = CreatePointCoord ( spGsmFact, pcoord3 ) ;ListPoints.Append(Pt);   ListRadius.Append(NULL_var);
        Pt = CreatePointCoord ( spGsmFact, pcoord4 ) ;ListPoints.Append(Pt);   ListRadius.Append(spCkeRadPoly);
        Pt = CreatePointCoord ( spGsmFact, pcoord5 ) ;ListPoints.Append(Pt);   ListRadius.Append(NULL_var);
        Pt = CreatePointCoord ( spGsmFact, pcoord6 ) ;ListPoints.Append(Pt);   ListRadius.Append(NULL_var);
        Pt = CreatePointCoord ( spGsmFact, pcoord7 ) ;ListPoints.Append(Pt);   ListRadius.Append(NULL_var);
        Pt = CreatePointCoord ( spGsmFact, pcoord8 ) ;ListPoints.Append(Pt);   ListRadius.Append(NULL_var);
        
        CATIGSMPolyline_var  spPolyLine1 =  spGsmFact -> CreatePolyline ( ListPoints , ListRadius, NULL_var ) ;
        CATISpecObject_var spSpecPLine1 = spPolyLine1 ;
        CAAGsiInsertInProceduralView( spSpecPLine1, NULL_var ) ; CAAGsiObjectUpdate(spSpecPLine1) ; 
        spPrtPart -> SetCurrentFeature(spSpecPLine1);
        ListPoints.RemoveAll() ; ListRadius.RemoveAll();
        
        double gcoord1[3] = {    0.0 ,     0.0 , 200.0 } ; 
        double gcoord2[3] = {  100.0 ,    10.0 , 200.0 } ; 
        double gcoord3[3] = {  200.0 ,    40.0 , 200.0 } ; 
        double gcoord4[3] = {  300.0 ,    80.0 , 200.0 } ; 
        Pt = CreatePointCoord ( spGsmFact, gcoord1 ) ;ListPoints.Append(Pt);  
        Pt = CreatePointCoord ( spGsmFact, gcoord2 ) ;ListPoints.Append(Pt);  
        Pt = CreatePointCoord ( spGsmFact, gcoord3 ) ;ListPoints.Append(Pt);  
        Pt = CreatePointCoord ( spGsmFact, gcoord4 ) ;ListPoints.Append(Pt);  
        CATIGSMSpline_var  spSpline1 =  spGsmFact -> CreateSplinePoints ( ListPoints ) ;
        CATISpecObject_var spSpecSpline1 = spSpline1;
        CAAGsiInsertInProceduralView( spSpecSpline1, NULL_var ) ; CAAGsiObjectUpdate(spSpecSpline1) ; 
        spPrtPart -> SetCurrentFeature(spSpecSpline1);
        ListPoints.RemoveAll() ; ListRadius.RemoveAll();
        
        
        cout << "(CAAGsiBodyGSAndOGS) Create a sweep surface" << endl;
        
        iName = "Surface "; 
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName  , spParentTool, spSpecTool , Diag , UNDER_Current ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl ;
            
        }
        
        CATIGSMSweepUnspec_var spExplSweep1  = 
            spGsmFact -> CreateExplicitSweep(spSpecSpline1,spSpecPLine1,NULL_var , NULL_var , NULL_var );
        // spExplSweep1  ->  SetContext(CATGSMVolumeCtxt) ; 
        CATISpecObject_var spSpecExplSweep1  = spExplSweep1 ;
        CAAGsiInsertInProceduralView( spSpecExplSweep1 , NULL_var ) ; 
        rc = CAAGsiObjectUpdate(spSpecExplSweep1) ;
        if (FAILED(rc) ) { 
            cout << "(CAAGsiBodyGSAndOGS) ERROR Creation Sweep " <<endl ;
        }
        spPrtPart -> SetCurrentFeature(spSpecExplSweep1);
        
        
        
        // ======================================================================================================
        // OGS 
        // ======================================================================================================
        cout << "(CAAGsiBodyGSAndOGS) Create an OrderedGeometricalSet (OGS)  " <<endl ;
  
        iName="";
        iTypeOfTool  = TYPE_OrderedGeometricalSet ; 
        spParentTool = NULL_var ;
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName , spParentTool , spSpecTool , Diag ,  UNDER_Part ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl << flush;
            RetCode = 3 ;   
        }
        spParentTool = spSpecTool ; 
        spSpecTool = NULL_var ; 
        
        
        // Closed Wire
        // -------------------------------------------------------------
        iName =  "ClosedWires" ; 
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName , spParentTool , spSpecTool , Diag,   UNDER_Current ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl ;
            
        }
        
        
        // Need to have closed Wires
        cout << "(CAAGsiBodyGSAndOGS) Create closed wires " << endl;
        
        // Create PolyLine 
        // Tips  : Datum construction points are not insert immediately in the ProceduralView 
        // They are going to be automatically Insert on next feature insert and update  
        // Then they are aggregated as "contextual element" under the inserted feature (Here polyline)
        double Poly1coord1[3] = {    0.0 ,    0.0 , 0.0 } ; 
        double Poly1coord2[3] = {  100.0 ,    0.0 , 0.0 } ; 
        double Poly1coord3[3] = {  100.0 ,  100.0 , 0.0 } ; 
        double Poly1coord4[3] = {    0.0 ,  100.0 , 0.0 } ; 
        CATISpecObject_var  Pt1 = spGsmFact -> CreatePoint ( Poly1coord1 ) ;ListPoints.Append(Pt1);  
        CATISpecObject_var  Pt2 = spGsmFact -> CreatePoint ( Poly1coord2 ) ;ListPoints.Append(Pt2); 
        CATISpecObject_var  Pt3 = spGsmFact -> CreatePoint ( Poly1coord3 ) ;ListPoints.Append(Pt3); 
        CATISpecObject_var  Pt4 = spGsmFact -> CreatePoint ( Poly1coord4 ) ;ListPoints.Append(Pt4); 
        
        CATIGSMPolyline_var  spPolyLine =  spGsmFact -> CreatePolyline ( ListPoints , ListRadius, NULL_var ) ;
        spPolyLine -> SetClosure (TRUE) ; 
        CATISpecObject_var spSpecPLine = spPolyLine ;
        CAAGsiInsertInProceduralView( spSpecPLine, NULL_var ) ; CAAGsiObjectUpdate(spSpecPLine) ; 
        spPrtPart -> SetCurrentFeature(spSpecPLine);
        ListPoints.RemoveAll() ; ListRadius.RemoveAll();
        
        // Create Circle 1
        double radius    = 20.0 ;
        
        // Tips  : Datum construction points are not insert immediately in the ProceduralView 
        // They are going to be automatically Insert on next feature insert and update  
        // Then they are aggregated as "contextual element" under the inserted feature (Here Circle )
        double center1[3] = {    0.0 ,    50.0 , 50.0 } ; 
        CATISpecObject_var  Ctr1= spGsmFact -> CreatePoint ( center1 ) ;
        
        CATICkeParm_var spCkeStart, spCkeEnd ;
        spCkeStart= CreateAngle( spCkeFact, "Start", -180.0);
        spCkeEnd  = CreateAngle( spCkeFact, "End"  ,  180.0);
        
        CATICkeParm_var spCkeRad;
        spCkeRad= CreateLength ( spCkeFact,  "Radius", radius );
        
        CATIGSMCircleCtrRad_var  spCircle1 =   spGsmFact -> CreateCircle ( Ctr1,  spListPlane [2] , TRUE, spCkeRad ,spCkeStart,spCkeEnd) ;
        CATISpecObject_var spSpecCircle1  = spCircle1 ;
        CAAGsiInsertInProceduralView( spSpecCircle1 , NULL_var ) ; CAAGsiObjectUpdate(spSpecCircle1 ) ;
        spPrtPart -> SetCurrentFeature(spSpecCircle1);
        
        
        // Create Circle 2
        // Tips  : Datum construction points are not insert immediately in the ProceduralView 
        // They are going to be automatically Insert on next feature insert and update  
        // Then they are aggregated as "contextual element" under the inserted feature (Here Circle )
        double center2[3] = {   50.0 ,    0.0 ,  50.0 } ; 
        CATISpecObject_var  Ctr2= spGsmFact -> CreatePoint ( center2 ) ;
        
        spCkeStart= CreateAngle( spCkeFact, "Start", -180.0);
        spCkeEnd  = CreateAngle( spCkeFact, "End"  ,  180.0);
        
        spCkeRad  = CreateLength ( spCkeFact,  "Radius", radius*2 );
        
        
        CATIGSMCircleCtrRad_var  spCircle2 =   spGsmFact -> CreateCircle ( Ctr2,  spListPlane [3] , TRUE, spCkeRad ,spCkeStart,spCkeEnd) ;
        CATISpecObject_var spSpecCircle2  = spCircle2 ;
        CAAGsiInsertInProceduralView( spSpecCircle2, NULL_var ) ; CAAGsiObjectUpdate(spSpecCircle2 ) ;
        spPrtPart -> SetCurrentFeature(spSpecCircle2);
        
        iName =  "Volumes" ; 
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName , spParentTool , spSpecTool , Diag,   UNDER_Current ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl ;
            
        }
        
        // Surfaces or volumes 
        // -------------------------------------------------------------
        
        //  ---  Volume Features / Only to be insert  in GS or OGS = Surfacic Set 
        CATGSMFeatureContextType GSDCreationContext ;
        
        if ( TYPE_GeometricalSet == iTypeOfTool || TYPE_OrderedGeometricalSet == iTypeOfTool )  { 
            cout << "(CAAGsiBodyGSAndOGS) Create volumes / set is GS or OGS   " << endl;
            // -- Creation of feature in Volume context 
            //  Available Feature GSD Extrude / Revol / MultiSections Surfaces / Sweep
            // Note: Input curves  or profile curves need be closed  (check is done at feature build) 
            GSDCreationContext= CATGSMVolumeCtxt; 
        }
        
        else if (TYPE_Body == iTypeOfTool) {  
            cout << "(CAAGsiBodyGSAndOGS) Create surfaces / set is Body - No volume can be inserted  " << endl;
            // -- Creation of feature in standard Gsd context (Surfacic) 
            GSDCreationContext= CATGSMSurfaceCtxt; 
        }
        
        
        // Extrude 1 
        spCkeStart= CreateLength ( spCkeFact,  "Start",   0 );
        spCkeEnd  = CreateLength ( spCkeFact,  "End"  , 100.0);
        CATIGSMDirection_var Dir1 =spGsmFact -> CreateDirection ( spListPlane[1]); 
        CATIGSMExtrude_var  spExtrude1  =  spGsmFact -> CreateExtrude ( spSpecPLine , Dir1 , spCkeStart, spCkeEnd, TRUE) ;
        spExtrude1  ->  SetContext(GSDCreationContext) ; 
        
        CATISpecObject_var spSpecExtr1  = spExtrude1 ; 
        CAAGsiInsertInProceduralView( spSpecExtr1 , NULL_var ) ;CAAGsiObjectUpdate(spSpecExtr1) ;
        spPrtPart -> SetCurrentFeature(spSpecExtr1);
        
        
        // Extrude 2 
        spCkeStart=CreateLength (  spCkeFact,"Start",  100.0 );
        spCkeEnd  =CreateLength (  spCkeFact,"End"  , 200.0 );
        CATIGSMDirection_var Dir2 =spGsmFact-> CreateDirection ( spListPlane[2]); 
        CATIGSMExtrude_var  spExtrude2  =  spGsmFact -> CreateExtrude ( spSpecCircle1 , Dir2 , spCkeStart, spCkeEnd, TRUE) ;
        spExtrude2  ->  SetContext(GSDCreationContext) ; 
        CATISpecObject_var spSpecExtr2  = spExtrude2 ;
        CAAGsiInsertInProceduralView( spSpecExtr2 , NULL_var ) ; CAAGsiObjectUpdate(spSpecExtr2) ;
        spPrtPart -> SetCurrentFeature(spSpecExtr2);
        
        // Extrude 3 
        spCkeStart=CreateLength (  spCkeFact,"Start",  100.0 );
        spCkeEnd  =CreateLength (  spCkeFact,"End"  , 200.0 );
        CATIGSMDirection_var Dir3 =spGsmFact-> CreateDirection ( spListPlane[3]); 
        CATIGSMExtrude_var  spExtrude3  =  spGsmFact -> CreateExtrude ( spSpecCircle2 , Dir3 , spCkeStart, spCkeEnd, TRUE) ;
        spExtrude3  ->  SetContext(GSDCreationContext) ; 
        CATISpecObject_var spSpecExtr3  = spExtrude3 ;
        CAAGsiInsertInProceduralView( spSpecExtr3 , NULL_var ) ; CAAGsiObjectUpdate(spSpecExtr3) ;
        spPrtPart -> SetCurrentFeature(spSpecExtr3);
        
        
        // Operations 
        // --------------------------------------------------------
        // ---Split / Split on volume allow either Surfacic or Volumic result for Volume feature input 
        
        // Type of Input (Volume or Surfacic) 
        CATGSMFeatureContextType GSDInputFeatureContext ;
        rc = spExtrude2 -> GetContext(GSDInputFeatureContext); 
        
        
        //  Split / Generate volume result if object to split is a volume 
        CATGSMOrientation iorient = CATGSMSameOrientation ;
        CATIGSMSplit_var   spSplit   =  spGsmFact -> CreateSplit  ( spSpecExtr2  , spListPlane [2] ,iorient ) ;
        
        if ( GSDInputFeatureContext == CATGSMVolumeCtxt) { 
            spSplit -> SetVolumeResult(TRUE) ;
        }
        CATISpecObject_var spSpecSplit = spSplit ;
        CAAGsiInsertInProceduralView( spSpecSplit  , NULL_var ) ; CAAGsiObjectUpdate(spSpecSplit ) ;
        spPrtPart -> SetCurrentFeature(spSpecSplit) ;
        
        
        
        // Boolean 
        // -------------------------------------------------------------
        
        // -- Boolean operation on Volume   / Only to be insert  in GS or OGS = Surfacic Set
        if ( TYPE_GeometricalSet == iTypeOfTool || TYPE_OrderedGeometricalSet == iTypeOfTool )  { 
            
            
            // Note : PartFactory or PartBooleanFactory automatically insert feature in the procedural view at creation 
            // Thus the InsertProceduralView to call for feature created by Gsd Factory do not have to e done 
            
            // Add
            CATISpecObject_var spSpecAdd = spBoolPrtFact -> CreateAdd ( spSpecExtr1,spSpecSplit ,ContextForBooleanOperationOnVolumeInPartFactory) ;
            CAAGsiObjectUpdate(spSpecAdd) ;
            spPrtPart -> SetCurrentFeature(spSpecAdd);
            
            // Remove 
            CATISpecObject_var spSpecRemove = spBoolPrtFact -> CreateRemove ( spSpecAdd,spSpecExtr3 ,ContextForBooleanOperationOnVolumeInPartFactory) ;
            CAAGsiObjectUpdate(spSpecRemove) ;
            spPrtPart -> SetCurrentFeature(spSpecRemove);
        }
        // ======================================================================================================
        // Body  
        // ======================================================================================================
        cout << "(CAAGsiBodyGSAndOGS) Create a Body(Hybrid)  (Body)  " <<endl ;

      
        iName="";
        iTypeOfTool  = TYPE_Body ; 
        spParentTool = NULL_var ;
        rc = CAAGsiCreateGeometricFeatureSets (spCont, iName , spParentTool , spSpecTool , Diag ,  UNDER_Part ,  iTypeOfTool);
        if (FAILED(rc))  {
            cout << "(CAAGsiBodyGSAndOGS) ERROR CAAGsiCreateGeometricFeatureSets = " << Diag << endl << flush;
            RetCode = 3 ;   
        }
        spParentTool = spSpecTool ; 
        spSpecTool = NULL_var ; 
        
        
        // Need to have closed Wires
        cout << "(CAAGsiBodyGSAndOGS) Create closed wires " << endl;
        
        // Create PolyLine 
        // Tips  : Datum construction points are not insert immediately in the ProceduralView 
        // They are going to be automatically Insert on next feature insert and update  
        // Then they are aggregated as "contextual element" under the inserted feature (Here polyline)
        double Poly2coord1[3] = {    0.0 ,    0.0 , 100.0 } ; 
        double Poly2coord2[3] = {  100.0 ,    0.0 , 100.0 } ; 
        double Poly2coord3[3] = {  100.0 ,  100.0 , 100.0 } ; 
        double Poly2coord4[3] = {    0.0 ,  100.0 , 100.0 } ; 
        CATISpecObject_var  Poly2Pt1 = spGsmFact -> CreatePoint ( Poly2coord1 ) ;ListPoints.Append(Poly2Pt1);  
        CATISpecObject_var  Poly2Pt2 = spGsmFact -> CreatePoint ( Poly2coord2 ) ;ListPoints.Append(Poly2Pt2); 
        CATISpecObject_var  Poly2Pt3 = spGsmFact -> CreatePoint ( Poly2coord3 ) ;ListPoints.Append(Poly2Pt3); 
        CATISpecObject_var  Poly2Pt4 = spGsmFact -> CreatePoint ( Poly2coord4 ) ;ListPoints.Append(Poly2Pt4); 
        
        CATIGSMPolyline_var  spPolyLineBdy =  spGsmFact -> CreatePolyline ( ListPoints , ListRadius, NULL_var ) ;
        spPolyLineBdy -> SetClosure (TRUE) ; 
        CATISpecObject_var spSpecPLineBdy = spPolyLineBdy ;
        CAAGsiInsertInProceduralView( spSpecPLineBdy, NULL_var ) ; CAAGsiObjectUpdate(spSpecPLineBdy) ; 
        spPrtPart -> SetCurrentFeature(spSpecPLineBdy);
        ListPoints.RemoveAll() ; ListRadius.RemoveAll();
        
        // Pad
        CATISpecObject_var spSpecPad = spPrtFact -> CreatePad ( spSpecPLineBdy ) ;
        CATIPad_var spPad = spSpecPad; 
        spPad -> ModifyEndOffset (50.00) ; 
        CAAGsiObjectUpdate(spSpecPad) ;
        spPrtPart -> SetCurrentFeature(spSpecPad);
        
        
    }
    // ----------------------------------------------------------------------------
    // 4- Exit 
    // ----------------------------------------------------------------------------
    
    // Save Part 
    // ------------------------------------
    // Saves the modified pad in the second input path
    cout << endl;
    cout << "(CAAGsiBodyGSAndOGS) 4- Save document (if required)  "   << endl;
    
    if ( (NULL != pPartName) && (NULL != pDoc) ) {
        cout << "(CAAGsiBodyGSAndOGS) Save : "<< pPartName  << endl;
        rc = CATDocumentServices::SaveAs  (*pDoc,pPartName);
        if (FAILED(rc)) RetCode = 4 ;        
    }
    
    // Close Session
    // ------------------------------------
    cout << endl;
    cout << "(CAAGsiBodyGSAndOGS) 5- Close session " << endl;
    CATDocumentServices::Remove(*pDoc); 
    if (FAILED(rc)) RetCode = 5 ;        
    
    Delete_Session("SampleSession");
    cout << "(CAAGsiBodyGSAndOGS) End "  << RetCode << endl;
    cout << "====================================================================" << endl;
    cout << "=========        Batch : End Design a BodyGSAndOGS               =========" << endl;
    cout << "====================================================================" << endl;
    cout << endl;
    
    return RetCode ;
}

