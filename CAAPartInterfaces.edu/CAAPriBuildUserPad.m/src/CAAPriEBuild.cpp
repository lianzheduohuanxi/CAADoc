/**
 * @quickReview frn 03:06:26
 * @quickReview JDE 03:02:14
 */
// Copyright © 1994-2000 Dassault Systèmes.

// Local Framework
#include "CAAPriEBuild.h"

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"     // needed to manage list of bodies
#include "CATILinkableObject.h"          // needed to retrieve the result container
#include "CATDocument.h"                 // needed to retrieve the result container

// PartInterfaces Framework
#include "CATIShapeFeatureBody.h"        // needed to access to the ResultIN/ResultOUT
                                         // of the feature
 
// MechanicalModeler Framework
#include "CATIMfProcReport.h"            // needed to manage the procedural report
#include "CATIGeometricalElement.h"      // needed to delete the scope of the ResultOUT
#include "CATMfBRepDefs.h"               // needed to access to data of the procedural
                                         // report
#include "CATMfErrUpdate.h"              // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"             // needed to associate an error to a feature


// NewTopologicalObjects Framework
#include "CATBody.h"                     // needed to access to the built shape

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // needed to manage ResultIN/ResultOUT 
#include "CATLISTV_CATISpecAttribute.h"  // needed to access to the BodyIN

// GeometricObjects Framework
#include "CATGeoFactory.h"               // needed to create the boolean operation
#include "CATCGMJournalList.h"           // needed to manage the Topological journal

// TopologicalOperators Framework
#include "CATDynBoolean.h"               // needed to perform boolean operation

// MecModInterfaces Framework
#include "CATIBuildShape.h"              // needed to call the built shape operation
#include "CATIContainerOfDocument.h"     // needed to retrieve the geometrical factory

// Mathematics
#include "CATSoftwareConfiguration.h"    // needed to define the inputs of the 
                                         // topological operators
#include "iostream.h"

//-------------------------------------------------------------------------
// To declare that the class 
// is a DataExtension of (late type) CAAPriUserPad
CATImplementClass(CAAPriEBuild, 
                  DataExtension,
                  CATBaseUnknown, 
                  CAAPriUserPad);

#include "TIE_CATIBuild.h" // needed to tie the implementation to its interface
TIE_CATIBuild(CAAPriEBuild);

// To declare that UserPad implements CATIBuild, insert 
// the following line in the interface dictionary:
//
// CAAPriUserPad  CATIBuild  libCAAPriBuildUserPad
//-------------------------------------------------------------------------

CAAPriEBuild::CAAPriEBuild()
{
}

//-------------------------------------------------------------------------

CAAPriEBuild::~CAAPriEBuild()
{
}

//-------------------------------------------------------------------------

HRESULT CAAPriEBuild::Build()
{
   cout <<" CAAPriEBuild::Build" << endl;

   HRESULT rc = E_FAIL ;

    //===============================================================================
    //
    // The build method takes place as follows :
    //
    // CATTry
    //     o -0- Computing the form of the feature
    //     o -1- Cleaning last update error
    //     o -2- Retrieving data for the procedural report
    //     o   -2-1 Retrieving the ResultIn feature
    //     o   -2-2 Retrieving the CATBody associated with this and ResultIn
    //     o -3- Creating the procedural report
    //     o -4- Running the topological operator 
    //     o   -4-1 Retrieving the geometrical factory
    //     o   -4-2 Retrieving the topological journal
    //     o   -4-3 Running the topological operator (union operation)
    //     o -5- Storing the procedural report
    //     o -6- Cleaning useless data
    // CATCatch
    //     o -7-1 Managing CATMfErrUpdate Error
    //     o -7-2 Managing other Error's types
    //
    //===============================================================================
   
    // You declare here the pointers :
    //  - used in the CATTry and CATThrow sections, like piUpdateErrorOnThis 
    //  - initialized in the CATTry section, and not released before a 
    //    method which can throw an error. 
    //
    CATIUpdateError          * piUpdateErrorOnThis             = NULL;
    CATIGeometricalElement   * pIGeometricalElementOnResultOUT = NULL ;

    CATIBuildShape           * piBuildShape                    = NULL;

    CATIMfProcReport         * piProcReport                    = NULL;
    CATGeoFactory            * piGeomFactory                   = NULL;

    CATDynBoolean            * pOperatorBool                   = NULL;

    CATSoftwareConfiguration * pSoftConfig                     = NULL ;

    // Usefull in CATTry and CATCatches sections
    rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnThis);
    if ( FAILED(rc) ) return rc ;

    CATTry
    {
        
    //===============================================================================
    //
    // -0- Creating the form 
    //
    //===============================================================================
       
       rc = QueryInterface(IID_CATIBuildShape,(void**)&piBuildShape);
       if ( SUCCEEDED(rc) )
       {
           // This method can throw an error
           int val = piBuildShape->BuildShape();
           if ( 0 == val )
           {
              rc = E_FAIL ;
           }

           // all is ok 
           piBuildShape->Release();
           piBuildShape = NULL ;
       }

    //================================================================================
    //
    // -1- Removing all possible update error associated with the feature
    //
    //=================================================================================

       if ( SUCCEEDED(rc) )
       {
          piUpdateErrorOnThis->UnsetUpdateError();

          // This step will be useless in R12
          // Delete the last result associated with the ResultOUT feature 
          //
          CATIShapeFeatureBody * pIShapeFeatureBodyOnThis = NULL ;
          rc = QueryInterface( IID_CATIShapeFeatureBody,(void**) &pIShapeFeatureBodyOnThis);
          if ( SUCCEEDED(rc) )
          {
             CATListValCATBaseUnknown_var *pListBodyIn = NULL ;
             pListBodyIn = pIShapeFeatureBodyOnThis->GetBodyIN("CATBody");

             CATISpecObject_var spSpecObjectOnResultOUT ;
             spSpecObjectOnResultOUT = pIShapeFeatureBodyOnThis->GetResultOUT();

             pIShapeFeatureBodyOnThis->Release();
             pIShapeFeatureBodyOnThis = NULL ;

             // It is not the first element of the procedural view
             if  (NULL != pListBodyIn) 
             {
                delete pListBodyIn ;
                pListBodyIn = NULL ;

                rc = spSpecObjectOnResultOUT->QueryInterface( IID_CATIGeometricalElement , 
                                   (void**) &pIGeometricalElementOnResultOUT );
                if ( SUCCEEDED(rc) )
                {
                   // This method can throw an error
                   pIGeometricalElementOnResultOUT->DeleteScope() ;

                   // all is ok - no throw from DeleleScope
                   pIGeometricalElementOnResultOUT->Release();
                   pIGeometricalElementOnResultOUT = NULL ;
                }
             }
          }
       }
          
    //==================================================================================
    //
    // -2- Retrieving Data for the procedural report
    //
    //================================================================================== 
       
       CATIShapeFeatureBody * pIShapeFeatureBodyOnThis = NULL ;
       if ( SUCCEEDED(rc) )
       {
          rc = QueryInterface( IID_CATIShapeFeatureBody,(void**) &pIShapeFeatureBodyOnThis);
       }

       //================================================================================ 
       //
       // -2-1 Retrieving the ResultIn feature     
       //
       //================================================================================ 
       
       CATISpecObject_var  spResultIn ;
       if ( SUCCEEDED(rc) )
       {
             CATListValCATISpecAttribute_var *pListSpecAttribute = NULL ;
             pListSpecAttribute = pIShapeFeatureBodyOnThis->GetBodyINAttributes();
             
             if ( NULL != pListSpecAttribute )
             {
                // The first element of the list is the ResultIN attribute
                CATISpecAttribute_var spSpecAttribute = (*pListSpecAttribute)[1];

                if ( NULL_var != spSpecAttribute )
                {
                   // Retrieve the feature associated with the ResultIN attribute
                   spResultIn = spSpecAttribute->GetSpecObject();
                }

                delete pListSpecAttribute ;
                pListSpecAttribute = NULL ;
             }
       }
       
       //=================================================================================
       //
       // -2-2 Retrieving the two CATBody (this and ResultIn)
       //      
       //=================================================================================
       
       // 2-2-1 CATBody associated with ResultIn feature (can be NULL)
       //
       CATBody_var spCATBodyOnResultIn  ; 
       if ( SUCCEEDED(rc) )
       {
          CATListValCATBaseUnknown_var *pListBodyIn = NULL ;
          pListBodyIn = pIShapeFeatureBodyOnThis->GetBodyIN("CATBody");

          if ( NULL != pListBodyIn )
          {
             // The first element of the list is the CATBody of the ResultIN feature
             spCATBodyOnResultIn = (*pListBodyIn)[1];

             // No more need of this list
             delete pListBodyIn ;
             pListBodyIn = NULL ;
          }
       }

       // 2-2-2 CATBody accociates with this (cannot be NULL)
       //
       CATBody_var  spCATBodyOnThis ;
       if ( SUCCEEDED(rc) )
       {
          // Retrieve the form computed by the BuildShape method
          CATListValCATBaseUnknown_var *pListBody = NULL ;
          pListBody = pIShapeFeatureBodyOnThis->GetShape("CATBody");

          if ( NULL != pListBody )
          {
             spCATBodyOnThis = (*pListBody)[1];

             delete pListBody ;
             pListBody = NULL ;

          }
       }

       // No more need of this pointer
       if ( NULL != pIShapeFeatureBodyOnThis )
       {
           pIShapeFeatureBodyOnThis->Release();
           pIShapeFeatureBodyOnThis = NULL ;
       }

       // 2-2-3 Check that the CATBody corresponding to the shape exits 
       //       
       if ( NULL_var == spCATBodyOnThis )
       {
          CATMfErrUpdate *pErrorNoShape = new CATMfErrUpdate();
          CATUnicodeString Diagnostic("The feature has no shape.");
          pErrorNoShape->SetDiagnostic(1,Diagnostic);

          CATThrow(pErrorNoShape);
       }
     
    //=================================================================================
    //
    // -3- Creating the procedural report
    //
    //=================================================================================

      
       if ( SUCCEEDED(rc) )
       {

      //================================================================================
      //
      // -3-1 Filling the lists
      //     
      //================================================================================ 

          CATLISTV(CATBaseUnknown_var) ListSpec;
          CATListOfCATUnicodeString    ListKeys;

          // Add this to the list
          ListSpec.Append( this ); 
          ListKeys.Append( MfKeyNone );
          

          // if the ResultIN has a body (always excepted for the first element)
          // add the ResultIN to the list 
          if (NULL_var != spCATBodyOnResultIn)
          {
            ListSpec.Append( spResultIn ); 
            ListKeys.Append( MfKeyNone  );
          }

      //================================================================================= 
      //
      // -3-1 Creating the procedural report with the list
      //     
      //=================================================================================
          
          
           rc = QueryInterface( IID_CATIMfProcReport , (void**) &piProcReport );
           if ( SUCCEEDED(rc) )
           {
              // creates the procedural report - the result is associated with the
              // Solid feature not the feature itself - so BoolOper is 1
              // This method can throw an error
              int BoolOper = 1;
              
              piProcReport->CreateProcReport(ListSpec,ListKeys,BoolOper); 
           }

    //===================================================================================
    //
    // -4- Running the procedural report
    //
    //=================================================================================== 
       
       //================================================================================ 
       //
       // -4-1 Retrieving the geometrical factory
       //
       //================================================================================

          if ( SUCCEEDED(rc) )
          {
             // Gets a pointer on CATISpecObject.
             CATILinkableObject *piLinkableObjectOnUserPad = NULL;
             rc = QueryInterface( IID_CATILinkableObject, 
                                     (void**)& piLinkableObjectOnUserPad );
          
             if ( SUCCEEDED(rc) )
             {
                // Do not release this pointer
                CATDocument * pDocument = NULL ;
                pDocument = piLinkableObjectOnUserPad->GetDocument();
   
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
                piLinkableObjectOnUserPad->Release();
                piLinkableObjectOnUserPad = NULL ;
             }
          }

       //================================================================================ 
       //
       // -4-2 Retrieving the topological journal which contains the description
       //      of all basic topological operations.
       //
       //================================================================================ 
       
          CATTopData TopData ;
          if ( SUCCEEDED(rc) && piProcReport)
          {
             // do not release this pointer
             CATCGMJournalList *pCGMJournalList = piProcReport->GetCGMJournalList();  
             TopData.SetJournal(pCGMJournalList) ;

             // release this pointer after the procedural report ending
             pSoftConfig = new CATSoftwareConfiguration();
             TopData.SetSoftwareConfiguration(pSoftConfig) ;
          } 

          //============================================================================== 
          //
          // -4-3 Running the topological operator (union operation)
          //
          //==============================================================================
          CATBody   *pResultBody = NULL ;

          if ( SUCCEEDED(rc) )
          {
            
            //
            // Not the first element
            //
            if (NULL_var != spCATBodyOnResultIn)
            {
              // Creates the boolean operator for an union operation
              // between the shape built by the UserPad feature
              // and the geometry of the previous feature.
              
              CATDynBooleanType internalOperType = CATBoolUnion;
              
              
              pOperatorBool = CATCreateDynBoolean(piGeomFactory,
                                                  &TopData,
                                                  internalOperType,
                                                  spCATBodyOnResultIn,
                                                  spCATBodyOnThis);
              
              if ( NULL != pOperatorBool )
              {
                // Performs the boolean operation
                pOperatorBool->Run();
                
                // Retrieves the result of the boolean operation
                pResultBody = pOperatorBool->GetResult();
              }
            }
            else
            {
               //
               // Build of the ResultOUT body using the cells of the Shape's body.  
               //
               pResultBody = piGeomFactory->CreateBody();
               if ( NULL != pResultBody )
               {
                   CATDomain *Domain = NULL;
                   int NbDomain = spCATBodyOnThis->GetNbDomains();
                
                   for (int i = 1; i <= NbDomain; i++)
                   {
                      Domain = spCATBodyOnThis->GetDomain(i);
                      pResultBody->AddDomain(Domain);
                   }
               }
            }
          }

    //================================================================================= 
    //
    // -5- Storing the procedural report
    //
    //================================================================================= 

          if ( SUCCEEDED(rc) && piProcReport)
          {
             if ( NULL != pResultBody )
             {
                int BoolOper = 1 ; // same as CreateProcReport
                piProcReport->StoreProcReport(pResultBody,Copy, BoolOper); 
             }
             else
             {
                // creates an error if the intersection failed
                CATMfErrUpdate *pErrorNoIntersection = new CATMfErrUpdate();
                CATUnicodeString Diagnostic("Error during boolean operation.");
                pErrorNoIntersection->SetDiagnostic(1,Diagnostic);

                CATThrow(pErrorNoIntersection);
             }
          }
       }

    //==================================================================================
    //
    // 6- Cleaning Useless Data
    //
    //================================================================================== 

       // deletes the  topological operator
       if ( NULL != pOperatorBool )
       {
          delete pOperatorBool;
          pOperatorBool = NULL ;
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

       // Releases the software configuration
       if ( pSoftConfig!= NULL )
       {
	     pSoftConfig->Release();
	     pSoftConfig = NULL ;
       }

       // Releases the geometrical factory
       if( NULL != piGeomFactory ) 
       {
           piGeomFactory->Release();
           piGeomFactory = NULL ;
       }

  }

  CATCatch( CATMfErrUpdate , pUpdateError)
  {
     //------------------------------------------------------------------
     // Catches CATMfErrUpdate errors
     //------------------------------------------------------------------

     // Associates the error with the UserPad.
     if ( NULL != piUpdateErrorOnThis )
     {
        piUpdateErrorOnThis->SetUpdateError(pUpdateError);
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL;
     }
    
     // Releases the CATBuildShape interface pointer
     if ( NULL != piBuildShape )
     {
        piBuildShape->Release() ;
       piBuildShape = NULL ;
     }

     if ( NULL != pIGeometricalElementOnResultOUT )
     {
        pIGeometricalElementOnResultOUT->Release() ;
        pIGeometricalElementOnResultOUT = NULL ;
     }

     // Deletes the result ( proc report + pResultBody )
     if (NULL != piProcReport)
     {
        piProcReport->DeleteProcReport();

        piProcReport->Release();
        piProcReport = NULL ;
     }

     // Releases the software configuration
     if ( pSoftConfig!= NULL)
     {
	    pSoftConfig->Release();
	    pSoftConfig = NULL ;
     }

     // Deletes the topological operator
     if ( NULL != pOperatorBool)
     {
        delete pOperatorBool;
        pOperatorBool = NULL;
     }

     // Releases the geometrical factory
     if(NULL != piGeomFactory) 
     {
        piGeomFactory->Release();
        piGeomFactory = NULL ;
     }

     CATRethrow;

  }
    
  CATCatch ( CATError , pError) 
  {
     //-------------------------------------------------------------------
     // Catches other CATError errors
     //-------------------------------------------------------------------

     CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
     pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());

     ::Flush(pError);

     // Associates the error with the feature
     if(NULL != piUpdateErrorOnThis) 
     {
        piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);

        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
     }

     // Releases the CATBuildShape interface pointer
     if ( NULL != piBuildShape )
     {
        piBuildShape->Release() ;
        piBuildShape = NULL ;
     }

     if ( NULL != pIGeometricalElementOnResultOUT )
     {
        pIGeometricalElementOnResultOUT->Release() ;
        pIGeometricalElementOnResultOUT = NULL ;
     }

     // Deletes the result ( proc report + pResultBody )
     if (NULL != piProcReport)
     {
        piProcReport->DeleteProcReport();

        piProcReport->Release();
        piProcReport = NULL ;
     }

     // Releases the software configuration
     if ( pSoftConfig!= NULL)
     {
	    pSoftConfig->Release();
	    pSoftConfig = NULL ;
     }

     // Deletes the topological operator
     if ( NULL != pOperatorBool)
     {
        delete pOperatorBool;
        pOperatorBool = NULL;
     }

     // Releases the geometrical factory
     if(NULL != piGeomFactory) 
     {
        piGeomFactory->Release();
        piGeomFactory = NULL ;
     }

     CATThrow(pErrorToThrow);
  }  
    
  CATEndTry

  return rc;
}
