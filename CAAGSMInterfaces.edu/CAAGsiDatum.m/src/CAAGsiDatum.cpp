

// COPYRIGHT DASSAULT SYSTEMES 2003
//============================================================================================
// Sample code for : Generative Shape Design Interfaces + Convert result in Datum 
// Mission         : - Reuse  parametric nozzle generation (Start from the Part result of CAAGsiNozzle)  
//                   - Scna the mode lo retrieve Sweeps and Lofts 
//                   - Join the  surfaces 
//                   - Convert Join into a Datum surface 
//
// Type		   : Batch program
// Inputs	   : Path for saving the resulting Part (If no argument specified the part is not saved) 
// Outputs         : Return code is 0 if program worked ok, >0 otherwise
//	 
// Illustrates     : o How to retrive an object in part container 
//                   o How to Creat Join 
//                   o How to Convert in a Datum 
//                   o How to Save a Part Document  
//==========================================================================
//  How to execute :
//  
//     CAAGsiDatum Part 
//          with:   Part representing the path of the created part
//    
//  Example:
// 
//   CAAGsiDatum  E:\tmp\CAAGsiNozzle.CATPart E:\tmp\CAAGsiDatum.CATPart 
//
//  Return code:
//  
//   0 successful execution
//   1 bad number of arguments
//   2 problem during document creation
//   3 problem during document deletion 
//   4 problem during Part Save 
//============================================================================================


#include "CAAGsiServices.h"         // To call generic  services

#include "CATBoolean.h"
#include "CATUnicodeString.h"


//ObjectModelerBase Framework
#include "CATSession.h"                // To handle Session   
#include "CATDocument.h"               // To Handle Document
#include "CATSessionServices.h"        // To create session
#include "CATDocumentServices.h"       // To create document
#include "CATBaseUnknown.h"            // Base class for V5 Objects 
#include "CATIDescendants.h"           // To aggregats Features and locate them
#include "LifeCycleObject.h"           // To manage LifeCycle
#include "CATIContainer.h"             // To handle Containers imbeded in document 
#include "CATError.h"                  // To manage errors in CAAGsiUpdateObject()
#include "CATInit.h"                   // To initialize documents


// ObjectModelerBase includes
#include "CATIAlias.h"
#include "CATISpecObject.h"          // To handle Feature 
#include "CATLISTV_CATISpecObject.h" // To handle List of Features

// MecModInterfaces includes
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"

#include "CATIGSMTool.h"
#include "CATIMechanicalTool.h"
#include "CATIDescendants.h"

//Visualization framework 
#include "CATIModelEvents.h"
#include "CATDelete.h"

//Mechanical Modeler 
#include "CATIContainer.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATIMf3DBehavior.h"
#include "CATMfErrUpdate.h"            // To handle Update Exceptions

//Shape Design 
#include "CATIGSMFactory.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATIGSMAssemble.h"     // To insert in the procedural View (Proposed since V5R12)       
#include "CATIGSMProceduralView.h"     // To insert in the procedural View (Proposed since V5R12)       

#include "iostream.h"            


// ---------------------------------------------------------------------------
// ConvertToDatum  
// ---------------------------------------------------------------------------
// This method convert a SpecIn Datum 

HRESULT ConvertToDatum(CATIGSMFactory_var  & ispGsmFact , const CATISpecObject_var & ispSpec)
	{
	HRESULT rc = E_FAIL;
	if ( NULL_var != ispSpec ) {
		
        // Check the feature to convert is not already a Datum 
        CATIMf3DBehavior_var ispBehave(ispSpec);
        if(NULL_var != ispBehave ){
            
            if  ( FAILED( ispBehave -> IsADatum() ) ) { 
                
                CATListValCATISpecObject_var *ListDatum=NULL;
                
                // Convert  Spec in one or more Datum    
                // WARNING : Only available for features which do not have any child
                int iVerif =1 ;
                rc = ispGsmFact->ConvertToDatum(ispSpec, ListDatum,iVerif);
                if (FAILED(rc)) return E_FAIL;  
                
             
                // Delete of Procedural Specification 
                // --> Model event for delete / update visualization 
                CATIModelEvents_var IME(ispSpec);
                if(NULL_var != IME) {
                    CATDelete info(ispSpec->GetImpl());
                    IME->Dispatch(info);
                }
                
                // --> Delete Specification 
                CATISpecObject_var ispFather = ispSpec->GetFather();
                // Specification  is aggretated in the prodecural view   
                if (NULL_var != ispFather) {
                    ispFather->Release();
                    CATIDescendants_var ispDes = ispFather;
                    ispDes->RemoveChild (ispSpec);
                }
                // Specification is not in the prodecural view   
                else {
                    LifeCycleObject_var LCO = ispSpec;
                    LCO -> remove();
                }	
                
                // Datums management   
                CATListValCATISpecObject_var AllDatums;
                if(ListDatum) {
                    AllDatums.Append(*ListDatum);
                    delete ListDatum;ListDatum=NULL;
                }
                
                // Insert in procedural view 
                int i;
                int size = AllDatums.Size();
                 for(i=1;i<=size;i++) {
                    //	rc = CAAGsiObjTool.InsertInProceduralView(AllDatums[i]);
                    CATIGSMProceduralView_var curobj = AllDatums[i];
                    if (NULL_var != curobj ) {
                        rc = curobj->InsertInProceduralView();
                    }
                }
                rc =S_OK;
            } // Datum Test 
        }  // Check Interface CATIMf3DBehavior 
    } // Check Spec valid 
    return rc; 
}

// -----------------------------------------------------------------------------
// Main 
// Test Create a Datum form 
// -----------------------------------------------------------------------------

int main(int iArgc, 			// Number of arguments (1)
         char *iArgv[])                 // Path for the created Part 
	{
	
	// Create a parametric Datum form using Generative Shape Design Feature
	int RetCode = 0 ;
	HRESULT rc  = S_OK;
	
	// Checks arguments
	cout << "(CAAGsiDatum) iArgc = "<< iArgc << endl;
	for (int i=0;i<iArgc;i++) cout << "(CAAGsiDatum) iArgv =[ "<<i<<" ]= "<< iArgv[i] << endl;

    char * InputName = iArgv[1]; 
    char * OutputName = NULL ;
    if (iArgc >2 ) OutputName= iArgv[2]; 
    
    cout << "====================================================================" << endl;
    cout << "=========        Batch : Start Design a Datum             =========" << endl;
    cout << "====================================================================" << endl;
    cout << "(CAAGsiDatum) Start"  << endl;
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
    CATSession *pSession = NULL; 
    rc = Create_Session(pSessionName, pSession); 
    if (NULL == pSession ) {
        cout << "(CAAGsiDatum) ERROR: Create_Session" << endl << flush;
        RetCode  = 1 ;
    }
    
    // loads the document and initializes it
    cout <<"The input document " << InputName << " is opened" << endl ;
    CATDocument *pDoc = NULL; 
    rc =CATDocumentServices::OpenDocument(InputName, pDoc) ;
    
    if (NULL == pDoc ) {
        cout << "(CAAGsiDatum) ERROR CATDocumentServices::OpenDocument" << endl << flush;
        RetCode = 2 ;
    }
    
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
    
    //---------------------------------------------------------------
    // -4- Retrieve Features in document 
    //---------------------------------------------------------------
    
    cout <<endl; 
    cout << "(CAAGsiDatum) Shape Design  Factory     " << endl;
    
    // Retrieve the Generative Shape Design Interface and Store it to call
    // services in every 'CreateXXX' method
    CATIGSMFactory_var spGsmFact; 
    if ( NULL !=piPartContainer ) { 
        CATIGSMFactory * _pFact =NULL; 
        
        rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory ,(void**)&_pFact);
        if (SUCCEEDED(rc) ) {
            spGsmFact =  _pFact;
            if (_pFact) _pFact -> Release(); _pFact = NULL; 
        }
        piPartContainer -> Release(); piPartContainer = NULL; 
    }
    
    //---------------------------------------------------------------
    // -4- Search Objects 
    //---------------------------------------------------------------
    cout <<endl; 
    cout << "(CAAGsiDatum) Search in current document   " << endl;
    CATISpecObject_var spSweep1,spSweep2,spLoft1,spLoft2 ; 
    
    int iValidatedInput =1 ; 
    if ( NULL_var != spPrtPart) { 
        CATUnicodeString Sweep1Name ("Sweep.1");
        spSweep1 = CAAGsiSearchFeatureFromName(spPrtPart,Sweep1Name );
        if (NULL_var == spSweep1) { 
            cout << "ERROR: Sweep.1 NotFound " << endl << flush;
            iValidatedInput = 0; 
        }
        CATUnicodeString Sweep2Name ("Sweep.2");
        spSweep2 = CAAGsiSearchFeatureFromName(spPrtPart,Sweep2Name);
        if (NULL_var == spSweep2) { 
            cout << "ERROR: Sweep.2  NotFound " << endl << flush;
            iValidatedInput = 0; 
        }
        CATUnicodeString Loft1Name ("Multi-sections Surface.1");
        spLoft1  = CAAGsiSearchFeatureFromName(spPrtPart,Loft1Name);
        if (NULL_var == spLoft1) { 
            cout << "ERROR: Loft.1  NotFound " << endl << flush;
            iValidatedInput = 0; 
        }
        CATUnicodeString Loft2Name ("Multi-sections Surface.2");
        spLoft2  = CAAGsiSearchFeatureFromName(spPrtPart,Loft2Name);
        if (NULL_var == spLoft2) { 
            cout << "ERROR: Loft.2  NotFound " << endl << flush;
            iValidatedInput = 0; 
        }
    }
    else {
        iValidatedInput= 0; 
    }
    // -5- Create a Datum 
    //---------------------------------------------------------------
    if ( NULL_var != spGsmFact && iValidatedInput ==1 ) {     
        
        // Join 
        // ------------------
        cout <<endl; 
        cout << "(CAAGsiDatum) Creating Assemble" << endl;
        CATLISTV(CATISpecObject_var) aObjectParametersAssemble;
        aObjectParametersAssemble.Append(spSweep1);
        aObjectParametersAssemble.Append(spLoft1);
        aObjectParametersAssemble.Append(spSweep2);
        aObjectParametersAssemble.Append(spLoft2);
        
        // Create feature 
        double MergingDistanceTol = 0.001 ; 
        CATBoolean iCheckConnexity = TRUE ; 
        
        CATICkeParm_var   spParm;
        CATICkeParmFactory_var spCkeFact = spGsmFact ; 
        if (!!spCkeFact) { 
            spParm    = spCkeFact -> CreateLength("MergingDistance",MergingDistanceTol/1000.0);
        }
        CATIGSMAssemble_var spAssemble = spGsmFact -> CreateAssemble(aObjectParametersAssemble,spParm,iCheckConnexity);
        aObjectParametersAssemble.RemoveAll();
        
        // Insert in procedural view 
        // ------------------
        // cout << "(CAAGsiDatum) Insert  in procedural view and update " << endl;
        CATISpecObject_var spSpecTmp = spAssemble;
        
        if (NULL_var != spSpecTmp) { 
            
            // Insert in procedural view 
            CATIGSMProceduralView_var ispProcView  = spSpecTmp;
            if (NULL_var != ispProcView ) {
                rc = ispProcView ->InsertInProceduralView();
            }
            
            // Update 
            CAAGsiObjectUpdate(spSpecTmp);
            // Datum  
            // ------------------
            cout <<endl; 
            cout << "(CAAGsiDatum) Convert to a Datum  " << endl;
            //    rc = CAAGsiObjTool.ConvertToDatum (spAssemble);
            rc = ConvertToDatum (spGsmFact,spAssemble);
            if (FAILED(rc)) {
                RetCode = 102;
                cout << "(CAAGsiDatum) Datum Creation failed " << endl;
            }
        }
        else {
            RetCode = 101; 
            cout << "(CAAGsiDatum) Assemble creation failed   " << endl;
        }
        
        // ----------------------------------------------------------------------------
        // 4- Save dacument 
        // ----------------------------------------------------------------------------
        
        if (NULL != OutputName )      {    
            rc = CATDocumentServices::SaveAs  (*pDoc, OutputName );
            if (SUCCEEDED(rc))   {
                cout <<endl; 
                cout << "(CAAGsiDatum) Save document   " << endl;
                //    rc = CAAGsiObjTooDocument "<< OutputName  << " is saved " << flush;
            }
            else {
                RetCode = 103; 
                cout << "ERROR in saving document" << endl << flush;
            }
        }
        
    } // Input validated 
    else {
        cout << "(CAAGsiDatum) Invalid inputs " << endl;
        RetCode = 4 ; 
    }
    // ----------------------------------------------------------------------------
    // 4- Exit 
    // ----------------------------------------------------------------------------
    
    // Closes the document
    CATDocumentServices::Remove(*pDoc);
    
    // Ends session and drops document	
    Delete_Session("SampleSession");
    
    
    cout << "(CAAGsiDatum) End "  << RetCode << endl;
    cout << "====================================================================" << endl;
    cout << "=========        Batch : End Design a Datum               =========" << endl;
    cout << "====================================================================" << endl;
    cout << endl;
    
    
    return RetCode ;
}




