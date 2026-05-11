// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEMmrCombinedCurveBuild.h"

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrCombinedCurve.h"      // To ask inputs curves and directions 

// GeometricObjects Framework
#include "CATGeoFactory.h"             // To extrude input curves along the input directions
#include "CATLine.h"                   // To query a direction
#include "CATCGMJournalList.h"

// Mathematics Framework
#include "CATMathDirection.h"          // Direction of extrusion
#include "CATMathDef.h"

// MechanicalModeler Framework
#include "CATIMfProcReport.h"          // To manage the procedural report
#include "CATMfBRepDefs.h"             // Useful for the procedural report 
#include "CATMfErrUpdate.h"            // To manage mechanical modeler update error
#include "CATIUpdateError.h"           // To associate an error to a feature
#include "CATIGeometricalElement.h"    // Needed for DeleteScope and GetBodyResult
#include "CATMmrAlgoConfigServices.h"  // Needed to subscribe to repository for AlgorithmConfiguration

// MecModInterfaces Framework
#include "CATIContainerOfDocument.h"   // To retrieve the geometrical factory
#include "CATIMechanicalProperties.h"   //  

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"   // To store the CATBody of the input elements to follow
#include "CATILinkableObject.h"        // To retrieve the result container
#include "CATDocument.h"               // To retrieve the result container
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"            // To query the Combined Curve feature about its inputs

// NewTopologicalObjects Framework
#include "CATBody.h"                   // The Topological result
#include "CATTopData.h"                // Needed to create operators

// System Framework
#include "CATListOfCATUnicodeString.h" // For the list of keys 
#include "CATUnicodeString.h"
#include "CATError.h"
#include "CATBoolean.h"

// TopologicalOperators Framework
#include "CATHybOperator.h"
#include "CATTopPrism.h"               // Needed to extrude curves
#include "CATHybIntersect.h"           // The result of the extruded surfaces's intersection
#include "CATCreateTopIntersect.h"     // Needed to intersect extruded surfaces

// Mathematics Framework
#include "CATSoftwareConfiguration.h"  // Needed to create topological data

#include <iostream.h>

#include "CATDataType.h"

//-----------------------------------------------------------------------------

CATImplementClass ( CAAEMmrCombinedCurveBuild,
                    DataExtension,
                    CATBaseUnknown,
                    CombinedCurve );

//-----------------------------------------------------------------------------
#include "TIE_CATIBuild.h" // needed to tie the implementation to its interface
TIE_CATIBuild( CAAEMmrCombinedCurveBuild);

// 
// To declare that CombinedCurve implements CATIBuild, insert 
// the following line in the interface dictionary:
//
// CombinedCurve  CATIBuild            libCAAMmrCombinedCurve
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
CAAEMmrCombinedCurveBuild::CAAEMmrCombinedCurveBuild():
CATBaseUnknown()
{
    
}

//-----------------------------------------------------------------------------
CAAEMmrCombinedCurveBuild::~CAAEMmrCombinedCurveBuild()
{
    
}

//-----------------------------------------------------------------------------
HRESULT CAAEMmrCombinedCurveBuild::Build ()
{
    cout <<" CAAEMmrCombinedCurveBuild::Build" << endl;

    HRESULT rc = E_FAIL ;

    //========================================================================================
    //
    // The build method takes place as follows :
    //
    // CATTry
    //   o -0- Checking the deactivation status
    //   o -1- Cleaning last update error
    //   o -2- Retrieving data for the procedural report
    //   o  -2-1 Retrieving the two input curves and the two input directions
    //   o  -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
    //   o  -2-3 Retrieving the two bodies corresponding to the two input curves
    //   o -3- Creating the procedural report
    //   o  -3-1 Filling the list of specifications to follow 
    //   o  -3-2 Creating the procedural report
    //   o -4- Running the topological operators 
    //   o  -4-1 Retrieving the geometrical factory
    //   o  -4-2 Retrieving the topological journal
    //   o  -4-3 Retrieving the Algorithm Configuration
    //   o  -4-4 Running the topological operator - extruding curves
    //   o  -4-5 Running the topological operator - computing combined curve
    //   o -5- Storing the procedural report
    //   o -6- Storing the Algorithm Configuration
    //   o -6- Cleaning useless data
    // CATCatch
    //     o -7-1 Managing CATMfErrUpdate Error
    //     o -7-2 Managing other Error's types
    //
    //========================================================================================
    
    // You declare here the pointers :
    //  - used in the CATTry and CATThrow sections, like piUpdateErrorOnThis 
    //  - initialized in the CATTry section, and not released before a 
    //    method which can throw an error. 
    //
    CATIUpdateError          * piUpdateErrorOnThis        = NULL;
    CATIGeometricalElement   * pIGeometricalElementOnThis = NULL ;

    CATTopPrism              * pCurve1Extrude             = NULL;
    CATTopPrism              * pCurve2Extrude             = NULL;
    CATHybOperator           * pIntersect                 = NULL;

    CATBody                  * pCurve1ExtrudeBody         = NULL ;
    CATBody                  * pCurve2ExtrudeBody         = NULL ;

    CATIMfProcReport         * piProcReport               = NULL;
    CATGeoFactory            * piGeomFactory              = NULL;
    CATSoftwareConfiguration * pSoftConfig                = NULL;
    int                      IsConfigToStore              = NULL;

    CATISpecObject           * pSOCombinedCurve           = NULL;
            
    CATTry 
    {

    //========================================================================================
    //
    // -0- Checking the deactivation
    //
    //========================================================================================

        int DeactivateState = 0 ;
        CATIMechanicalProperties *pMechProp = NULL ;
        rc = QueryInterface(IID_CATIMechanicalProperties,(void **) & pMechProp);
        if ( SUCCEEDED(rc) )
        {
            DeactivateState = pMechProp->IsInactive();
          
            pMechProp->Release();
            pMechProp = NULL ;

            if ( 1 == DeactivateState )
            {
               QueryInterface(IID_CATIMfProcReport,(void**) &piProcReport );
               if ( SUCCEEDED(rc) )
               {
                  rc = piProcReport->InactivateResult();
               
                  // if an error is sent by InactivateResult, 
                  // piProcReport is deleted in CATCatch sections

                  piProcReport->Release();
                  piProcReport = NULL ;
               }
            }
        }

    //========================================================================================
    //
    // -1- Cleaning last update error
    //
    //========================================================================================
       if ( DeactivateState == 0 )
       {

          rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnThis);
          if ( SUCCEEDED(rc) )
          {
             piUpdateErrorOnThis->UnsetUpdateError();
          }

          // This step will be useless in R12
          if ( SUCCEEDED(rc) )
          {
             rc = QueryInterface(IID_CATIGeometricalElement,(void**) &pIGeometricalElementOnThis );
             if ( SUCCEEDED(rc) )
             {
                // Deletes the last result - method which can throw an error
                pIGeometricalElementOnThis->DeleteScope() ;

                // Useless pointer
                pIGeometricalElementOnThis->Release();
                pIGeometricalElementOnThis = NULL ;
             }
          }

       //========================================================================================
       //
       // -2- Retrieving Data for the procedural report
       //
       //========================================================================================

          //=====================================================================================
          //
          // -2-1 Retrieving the two input curves and the two input directions
          //
          //=====================================================================================
       
          CATISpecObject    *piSpecOnCurve1     = NULL;
          CATISpecObject    *piSpecOnCurve2     = NULL;
          CATISpecObject    *piSpecOnDirection1 = NULL; 
          CATISpecObject    *piSpecOnDirection2 = NULL; 

          CAAIMmrCombinedCurve *piCombinedCurve = NULL;
          rc = QueryInterface( IID_CAAIMmrCombinedCurve , (void**) &piCombinedCurve );
          if ( SUCCEEDED(rc) )
          {
             // Retrieves curves and directions
             rc = piCombinedCurve->GetCurve    ( 1 , &piSpecOnCurve1     );
             if ( SUCCEEDED(rc) )
                rc = piCombinedCurve->GetDirection( 1 , &piSpecOnDirection1 );
             if ( SUCCEEDED(rc) )
                rc = piCombinedCurve->GetCurve    ( 2 , &piSpecOnCurve2     );
             if ( SUCCEEDED(rc) )
                rc = piCombinedCurve->GetDirection( 2 , &piSpecOnDirection2 );

             piCombinedCurve->Release();
             piCombinedCurve = NULL ;

             if ( FAILED(rc) )
             {
                // One of the inputs is NULL 
                if ( NULL != piSpecOnCurve1 )
                {
                   piSpecOnCurve1->Release();
                   piSpecOnCurve1 = NULL;
                }
                if ( NULL != piSpecOnCurve2 )
                {
                   piSpecOnCurve2->Release();
                   piSpecOnCurve2 = NULL;
                }
                if ( NULL != piSpecOnDirection1 )
                {
                   piSpecOnDirection1->Release();
                   piSpecOnDirection1 = NULL; 
                }
                if ( NULL != piSpecOnDirection2 )
                {
                   piSpecOnDirection2->Release();
                   piSpecOnDirection2 = NULL; 
                }

                // An error is created 
                CATMfErrUpdate *pErrorNoValidInput = new CATMfErrUpdate();
                CATUnicodeString Diagnostic("One of the inputs is wrong.");
                pErrorNoValidInput->SetDiagnostic(1,Diagnostic);

                CATThrow(pErrorNoValidInput);
             }
          }

          //=====================================================================================
          //
          // -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
          //
          //=====================================================================================

          CATMathDirection MathDirection1,MathDirection2 ;

          if ( SUCCEEDED(rc) && (NULL !=piSpecOnDirection1) )
          {
             // Gets a pointer on CATline for first direction
             CATLine *piLine1 = NULL;
    
             rc = piSpecOnDirection1->QueryInterface( IID_CATLine , ( void**) &piLine1 );
    
             if ( SUCCEEDED(rc) )
             {
                // Gets first mathematical direction
                piLine1->GetDirection(MathDirection1);
    
                // releases useless pointer
                piLine1->Release();
                piLine1 = NULL ;
             }
          }

          if ( SUCCEEDED(rc) && (NULL !=piSpecOnDirection2) )
          {
             // Gets a pointer on CATline for second direction
             CATLine *piLine2 = NULL;
    
             rc = piSpecOnDirection2->QueryInterface( IID_CATLine , ( void**) &piLine2 );
    
             if ( SUCCEEDED(rc) )
             {
                piLine2->GetDirection(MathDirection2);
   
                // releases useless pointer
                piLine2->Release();
                piLine2 = NULL ;
             }
          }

          //=====================================================================================
          //
          // -2-3 Retrieving the two bodies corresponding to the two input curves
          //
          //=====================================================================================

          CATBody_var spiBodyOfCurve1,spiBodyOfCurve2 ;

          if ( SUCCEEDED(rc) && (NULL !=piSpecOnCurve1) )
          {
             // gets a pointer on CATIGeometricalElement on the first input curve
             CATIGeometricalElement *piGeometricalElementOnCurve1 = NULL;
             rc = piSpecOnCurve1->QueryInterface ( IID_CATIGeometricalElement , 
                                                (void**) &piGeometricalElementOnCurve1 );
    
             if ( SUCCEEDED(rc) )
             {
                // uses GetBodyResult to retrieve the first body
                spiBodyOfCurve1 = piGeometricalElementOnCurve1->GetBodyResult();
    
                // releases useless pointer on CATIGeometricalElement
                piGeometricalElementOnCurve1->Release();
                piGeometricalElementOnCurve1 = NULL ;
             }
          }

          if ( SUCCEEDED(rc) && (NULL !=piSpecOnCurve2) )
          {
             // gets a pointer on CATIGeometricalElement on the second input curve
             CATIGeometricalElement *piGeometricalElementOnCurve2 = NULL;
             rc = piSpecOnCurve2->QueryInterface ( IID_CATIGeometricalElement , 
                                                   (void**) &piGeometricalElementOnCurve2 );
    
             if ( SUCCEEDED(rc) )
             {
                // uses GetBodyResult to retrieve the second body
                spiBodyOfCurve2 = piGeometricalElementOnCurve2->GetBodyResult();
    
                // releases useless pointer on CATIGeometricalElement
                piGeometricalElementOnCurve2->Release();
                piGeometricalElementOnCurve2 = NULL ;
             }
          }

       //========================================================================================
       //
       // -3- Creating the procedural report
       //     
       //========================================================================================

         //======================================================================================
         // -3-1 Filling the lists of the specifications to follow by the procedural report
         //      
         //======================================================================================

          CATLISTV(CATBaseUnknown_var) ListSpec;
          CATListOfCATUnicodeString    ListKeys;
          if ( SUCCEEDED(rc) )
          {
                ListSpec.Append( piSpecOnCurve1     ); 
                ListKeys.Append( MfKeyNone          );
    
                ListSpec.Append( piSpecOnDirection1 ); 
                ListKeys.Append( MfKeyNone          );
    
                ListSpec.Append( piSpecOnCurve2     ); 
                ListKeys.Append( MfKeyNone          );
    
                ListSpec.Append( piSpecOnDirection2 ); 
                ListKeys.Append( MfKeyNone          );
          }
 
          // No more need of those pointers 
          if ( NULL != piSpecOnCurve1 )
          {
             piSpecOnCurve1->Release();
             piSpecOnCurve1 = NULL;
          }
          if ( NULL != piSpecOnCurve2 )
          {
             piSpecOnCurve2->Release();
             piSpecOnCurve2 = NULL;
          }
          if ( NULL != piSpecOnDirection1 )
          {
             piSpecOnDirection1->Release();
             piSpecOnDirection1 = NULL; 
          }
          if ( NULL != piSpecOnDirection2 )
          {
             piSpecOnDirection2->Release();
             piSpecOnDirection2 = NULL; 
          }

         // Once the pointers are released, Checking that the bodies of the      
         // curve exist
         //
         if ( SUCCEEDED(rc) )
         {
            if ( (NULL_var == spiBodyOfCurve1 ) || ( NULL_var == spiBodyOfCurve2) )
            {
                // An error is created 
                CATMfErrUpdate *pErrorNoValidInput = new CATMfErrUpdate();
                CATUnicodeString Diagnostic("One of the curve has no topology.");
                pErrorNoValidInput->SetDiagnostic(1,Diagnostic);

                CATThrow(pErrorNoValidInput);
            }
         } 

         //======================================================================================
         // -3-2 Creating the procedural report with the list
         //     
         //======================================================================================

          if ( SUCCEEDED(rc) )
          {
             rc = QueryInterface( IID_CATIMfProcReport , (void**) &piProcReport );
             if ( SUCCEEDED(rc) )
             {
                // Creates the procedural report- the result is associated with the
                // feature itself - so BoolOper is 0
                // This method can throw an error
                //
                int BoolOper = 0;
                piProcReport->CreateProcReport(ListSpec,ListKeys,BoolOper); 
             }
          }

       //========================================================================================
       //
       // -4- Running the procedural report
       //
       //========================================================================================
       
          //=====================================================================================
          //
          // -4-1 Retrieving the geometrical factory
          //
          //=====================================================================================

          if ( SUCCEEDED(rc) )
          {
             // Gets a pointer on CATISpecObject.
             CATILinkableObject *piLinkableObjectOnCombinedCurve = NULL;
             rc = QueryInterface( IID_CATILinkableObject, 
                                  (void**)& piLinkableObjectOnCombinedCurve );
          
             if ( SUCCEEDED(rc) )
             {
                // Do not release this pointer
                CATDocument * pDocument = NULL ;
                pDocument = piLinkableObjectOnCombinedCurve->GetDocument();
   
                if ( NULL != pDocument )
                {
                   CATIContainerOfDocument * pIContainerOfDocument = NULL ;
                   rc = pDocument->QueryInterface(IID_CATIContainerOfDocument, 
                                                      (void**)& pIContainerOfDocument );
                   if ( SUCCEEDED(rc) )
                   {
                      CATIContainer * pIContainerOnGeomContainer = NULL ;
                      rc = pIContainerOfDocument->GetResultContainer(pIContainerOnGeomContainer);
                      if ( SUCCEEDED(rc) )
                      {

                         rc = pIContainerOnGeomContainer->QueryInterface( IID_CATGeoFactory , 
                                                                       (void**) &piGeomFactory );
                         pIContainerOnGeomContainer->Release();
                         pIContainerOnGeomContainer = NULL ;
                      }

                      pIContainerOfDocument->Release();
                      pIContainerOfDocument = NULL ;
                   }
                }
                piLinkableObjectOnCombinedCurve->Release();
                piLinkableObjectOnCombinedCurve = NULL ;
             }
          }

          //=====================================================================================
          //
          // -4-2 Retrieving the topological journal which contains the description
          //      of all basic topological operations.
          //
          //=====================================================================================

          CATTopData TopData ;
          if ( SUCCEEDED(rc) && (NULL!=piProcReport) )
          {
             // do not release this pointer
             // This method can throw an error
             CATCGMJournalList *pCGMJournalList = piProcReport->GetCGMJournalList();  
             TopData.SetJournal(pCGMJournalList) ;
             
          //=====================================================================================
          //
          // -4-3 Retrieving the Algorithm Configuration which contains datas used to
          //      version features
          //
          //=====================================================================================
             rc = QueryInterface(IID_CATISpecObject,(void **) & pSOCombinedCurve);
             if(SUCCEEDED(rc)&&pSOCombinedCurve != NULL)
             {
                rc = CATMmrAlgoConfigServices::GetConfiguration(pSOCombinedCurve ,pSoftConfig ,IsConfigToStore);
                if(SUCCEEDED(rc))
                {
		               // SetSoftwareConfig	
		               TopData.SetSoftwareConfiguration(pSoftConfig) ;
		               // release pSoftConfig after the procedural report ending
                }
		         }
          }

          //=====================================================================================
          //
          // -4-4 Running the topological operator extruding the two curves in both senses 
          //      defined by each direction
          //
          //=====================================================================================

          if ( SUCCEEDED(rc) )
          {
             CATLength StartOffset = 1000;
             CATLength EndOffset   = -StartOffset;

             // First topological operator : extrudes the first curve
             // This method can throw an error
             pCurve1Extrude = ::CATCreateTopPrism ( piGeomFactory   ,
					       &TopData ,
					       spiBodyOfCurve1  ,
					       &MathDirection1 ,
					       StartOffset     ,
					       EndOffset);
 
          
          
             if ( NULL != pCurve1Extrude)
             {
                CATLONG32 nbError = 0 ;
                CATError ** pListError = NULL ;
                CATBoolean Check = pCurve1Extrude->CheckOperands(nbError,pListError);
                if ( TRUE == Check )
                {
                   // Runs the first topological operator
                   pCurve1Extrude->Run();
	   
                   // Gets the first resulting extrusion
                   pCurve1ExtrudeBody = pCurve1Extrude->GetResult();
                }
                else
                {               
                    CATThrow(pListError[0]);
                }
             }        
       
             if ( NULL != pCurve1ExtrudeBody )
             {
                //  Second topological operator : extrudes the second curve
                // This method can throw an error
                pCurve2Extrude = ::CATCreateTopPrism ( piGeomFactory   ,
                                               &TopData,
					                            spiBodyOfCurve2  ,
					                            &MathDirection2 ,
					                            StartOffset     ,
					                             EndOffset);
	   
                if ( NULL != pCurve2Extrude)
                {
                    CATLONG32 nbError = 0 ;
                    CATError ** pListError = NULL ;
                    CATBoolean Check = pCurve2Extrude->CheckOperands(nbError,pListError);
                    if ( TRUE == Check )
                    {
                       // Runs the second topological operator
                       pCurve2Extrude->Run();
        
                       // Gets the second resulting extrusion
                       pCurve2ExtrudeBody = pCurve2Extrude->GetResult ();
                    }
                    else
                    {                    
                        CATThrow(pListError[0]);
                    }
                }
             }
          }
 
          //=====================================================================================
          //
          // -4-5 Running the topological operator computing the intersection of 
          //      the two surfaces 
          //      
          //=====================================================================================

          CATBody   *pResultBody = NULL ;

          if ( SUCCEEDED(rc) &&  (NULL!=pCurve2ExtrudeBody) && (NULL!=pCurve1ExtrudeBody) )
          {
             // third topological operator : computes the intersection between two surfaces
             // This method can throw an error
              pIntersect = ::CATCreateTopIntersect ( piGeomFactory      ,
					         &TopData ,
					         pCurve1ExtrudeBody ,
					         pCurve2ExtrudeBody );
   
             if ( NULL != pIntersect )
             {
                 // Runs the topological operator
                 pIntersect->Run();
            
                 // Gets the result of the intersection
                 pResultBody= pIntersect->GetResult ();             
             }
          }

       //========================================================================================
       //
       // -5- Storing the procedural report
       //
       //========================================================================================

          if ( SUCCEEDED(rc) && (NULL!=piProcReport)  )
          {
             if ( NULL != pResultBody )
             {
                // This method can throw an error
                int BoolOper = 0 ; // same as CreateProcReport
                piProcReport->StoreProcReport(pResultBody,NoCopy,BoolOper); 

                //===============================================================================
                //
                // -6- Storing the Algorithm Configuration
                //
                //===============================================================================

                if(IsConfigToStore == 1)
                {
                   CATMmrAlgoConfigServices::StoreConfiguration(pSOCombinedCurve ,pSoftConfig);
                }
             }
             else
             {
                // creates an error if the intersection failed
                CATMfErrUpdate *pErrorNoIntersection = new CATMfErrUpdate();
                CATUnicodeString Diagnostic("The two extruded curves do not intersect.");
                pErrorNoIntersection->SetDiagnostic(1,Diagnostic);

                CATThrow(pErrorNoIntersection);
             }
          }
        
       //========================================================================================   
       //
       // -7- Cleaning Useless Data, the possible solutions are:
       //
       //========================================================================================
       
          // Removes the intermediates bodies from the geometric container
          if ( (NULL !=piGeomFactory) && (NULL != pCurve1ExtrudeBody) )
          {
             piGeomFactory->Remove(pCurve1ExtrudeBody);
             pCurve1ExtrudeBody = NULL ;
          }

          if ( (NULL !=piGeomFactory) && (NULL != pCurve2ExtrudeBody) )
          {
             piGeomFactory->Remove(pCurve2ExtrudeBody);
             pCurve2ExtrudeBody = NULL ;
          }
       
          // Deletes the first topological operator
          if ( NULL != pCurve1Extrude )
          {
              delete pCurve1Extrude;
              pCurve1Extrude = NULL ;
          }
          // Deletes the second topological operator
          if ( NULL != pCurve2Extrude )
          {
             delete pCurve2Extrude;
             pCurve2Extrude = NULL ;
          }
          // Deletes the third topological operator
          if ( NULL != pIntersect )
          {
             delete pIntersect;
             pIntersect = NULL ;
          }
    
          // Releases the update error 
          if(NULL != piUpdateErrorOnThis) 
          {
              piUpdateErrorOnThis->Release();
              piUpdateErrorOnThis = NULL ;
          }

          // Releases the procedural report interface pointer
          if(NULL != piProcReport)  
          {
              piProcReport->Release();
              piProcReport = NULL ;
          }

          // Releases the pointer pSOCombinedCurve
          if(NULL != pSOCombinedCurve)
          {
              pSOCombinedCurve->Release();
              pSOCombinedCurve = NULL;
          }

          // Releases the software configuration
          if (NULL != pSoftConfig)
          {
	          pSoftConfig->Release();
	          pSoftConfig = NULL ;
          }

          // Releases the geometrical factory
          if (NULL != piGeomFactory) 
          {
              piGeomFactory->Release();
              piGeomFactory = NULL ;
          }


       }
    }   

    //========================================================================================
    //
    // -7- Managing errors 
    //
    //========================================================================================
      
    CATCatch ( CATMfErrUpdate , pUpdateError)
    {
        //------------------------------------------------------------------------------
        // Catches CATMfErrUpdate errors
        //------------------------------------------------------------------------------

        // Associates the error with the Combined Curve
        if(NULL != piUpdateErrorOnThis) 
        {
            piUpdateErrorOnThis->SetUpdateError(pUpdateError);

            piUpdateErrorOnThis->Release();
            piUpdateErrorOnThis = NULL ;
        }

        // Releases or deletes the pointer which can be valuated
        // but not released before an error
        //
        if ( NULL != pIGeometricalElementOnThis) 
        {
            pIGeometricalElementOnThis->Release();
            pIGeometricalElementOnThis = NULL ;
        }

        // Deletes the result ( proc report + pResultBody )
        if (NULL != piProcReport)
        {
           piProcReport->DeleteProcReport();
           piProcReport->Release();
           piProcReport = NULL ;
        }

        // Deletes the first topological operator
        if ( NULL != pCurve1Extrude )
        {
           delete pCurve1Extrude;
           pCurve1Extrude = NULL ;
        }
        // Deletes the second topological operator
        if ( NULL != pCurve2Extrude )
        {
           delete pCurve2Extrude;
           pCurve2Extrude = NULL ;
        }
        // Deletes the third topological operator
        if ( NULL != pIntersect )
        {
           delete pIntersect;
           pIntersect = NULL ;
        }

        // Removes the intermediate CATBody
        if ( (NULL !=piGeomFactory) && (NULL != pCurve1ExtrudeBody) )
        {
           piGeomFactory->Remove(pCurve1ExtrudeBody);
           pCurve1ExtrudeBody = NULL ;
        }

        if ( (NULL !=piGeomFactory) && (NULL != pCurve2ExtrudeBody) )
        {
           piGeomFactory->Remove(pCurve2ExtrudeBody);
           pCurve2ExtrudeBody = NULL ;
        }

        // Deletes the pointer on the geometric container
        if(NULL != piGeomFactory) 
        {
           piGeomFactory->Release();
           piGeomFactory = NULL ;
        }

        // Releases the pSOCombinedCurve
        if (NULL!=pSOCombinedCurve)
        {
	       pSOCombinedCurve->Release();
	       pSOCombinedCurve = NULL ;
        }
        
        // Releases the software configuration
        if (NULL!=pSoftConfig)
        {
	       pSoftConfig->Release();
	       pSoftConfig = NULL ;
        }

        

        // Re-dispatches the error.
        // In interactive mode, this errror will be caught by CATPrtUpdateCom that
        // knows how to handle such errors.
        CATRethrow ;
    }
    
    CATCatch ( CATError , pError) 
    {
        //------------------------------------------------------------------------------
        // Catches other CATError errors
        //------------------------------------------------------------------------------

        CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
        pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());

        ::Flush(pError);

        // Associates the error with the Combined Curve
        if(NULL != piUpdateErrorOnThis) 
        {
            piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);

            piUpdateErrorOnThis->Release();
            piUpdateErrorOnThis = NULL ;
        }

        // Releases or Deletes the pointer which can be valuated
        // ant not released due to a throw
        if ( NULL != pIGeometricalElementOnThis) 
        {
            pIGeometricalElementOnThis->Release();
            pIGeometricalElementOnThis = NULL ;
        }

        // Deletes the result ( proc report + pResultBody )
        if (NULL != piProcReport)
        {
           piProcReport->DeleteProcReport();
           piProcReport->Release();
           piProcReport = NULL ;
        }
        
        // Deletes the first topological operator
        if ( NULL != pCurve1Extrude )
        {
           delete pCurve1Extrude;
           pCurve1Extrude = NULL ;
        }
        // Deletes the second topological operator
        if ( NULL != pCurve2Extrude )
        {
           delete pCurve2Extrude;
           pCurve2Extrude = NULL ;
        }
        // Deletes the third topological operator
        if ( NULL != pIntersect )
        {
           delete pIntersect;
           pIntersect = NULL ;
        }
        
        // Removes the intermediate CATBody
        if ( (NULL !=piGeomFactory) && (NULL != pCurve1ExtrudeBody) )
        {
           piGeomFactory->Remove(pCurve1ExtrudeBody);
           pCurve1ExtrudeBody = NULL ;
        }

        if ( (NULL !=piGeomFactory) && (NULL != pCurve2ExtrudeBody) )
        {
           piGeomFactory->Remove(pCurve2ExtrudeBody);
           pCurve2ExtrudeBody = NULL ;
        }

        // Deletes the pointer on the geometric container
        if (NULL != piGeomFactory) 
        {
           piGeomFactory->Release();
           piGeomFactory = NULL ;
        }

        // Releases the pSOCombinedCurve
        if (NULL!=pSOCombinedCurve)
        {
	       pSOCombinedCurve->Release();
	       pSOCombinedCurve = NULL ;
        }
        
        // Releases the software configuration
        if (NULL!=pSoftConfig)
        {
	       pSoftConfig->Release();
	       pSoftConfig = NULL ;
        }

        CATThrow(pErrorToThrow);
    }   
    
    CATEndTry;
    
    return rc ;
}

