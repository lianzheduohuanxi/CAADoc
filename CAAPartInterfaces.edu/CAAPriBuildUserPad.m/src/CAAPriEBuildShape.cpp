/**
 * @quickReview sqa 04:01:09
 * @quickReview frn 03:06:26
 * @quickReview JDE 03:02:14
 */
// Copyright © 1994-2000 Dassault Systèmes.

// Local Framework
#include "CAAPriEBuildShape.h"

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"   // needed to manage keys
#include "CATILinkableObject.h"        // needed to retrieve the result container
#include "CATDocument.h"               // needed to retrieve the result container

// PartInterfaces Framework
#include "CATIPrtProfile.h"            // needed to manage the profile of the feature
 
// MechanicalModeler Framework
#include "CATIMfProcReport.h"          // needed to manage the procedural report
#include "CATIGeometricalElement.h"	   // needed to delete the scope of the ResultOUT
#include "CATMfBRepDefs.h"             // needed to manage the proc report
#include "CATMfErrUpdate.h"            // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"           // needed to associate an error to a feature

// MecModInterfaces Framework
#include "CATIContainerOfDocument.h"     // needed to retrieve the geometrical factory

// NewTopologicalObjects Framework
#include "CATBody.h"                   // needed to manage the profile and the BodyOUT
#include "CATDomain.h"                 // needed to manage the wire of the profile 
#include "CATWire.h"                   // needed to manage the wire of the profile

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"            // needed to manage the profile
#include "CATISpecAttrAccess.h"				 // needed to access the feature attributes
#include "CATISpecAttrKey.h"				   // needed to access the feature attribute keys

// GeometricObjects Framework			
#include "CATGeoFactory.h"             // needed to create the prism operator
#include "CATCGMJournalList.h"         // needed to manage the topological journal

// TopologicalOperators Framework
#include "CATTopPrism.h"               // needed to create the prism operator
#include "CATTopData.h"                // needed to define the inputs of the 
                                       // topological operators

// Mathematics Framework
#include "CATMathDirection.h"          // needed to define the extrusion direction 
#include "CATMathVector.h"             // needed to define the extrusion direction
#include "CATMathPlane.h"              // needed to define the extrusion direction

// System
#include "CATListOfCATUnicodeString.h" // needed to manage the key list

// Mathematics
#include "CATSoftwareConfiguration.h"  // needed to define the inputs of the 
                                       // topological operators

#include "iostream.h"

//-------------------------------------------------------------------------
// To declare that the class 
// is a DataExtension of (late type) CAAPriUserPad
CATImplementClass(CAAPriEBuildShape, 
                  DataExtension, 
                  CATBaseUnknown, 
                  CAAPriUserPad);

#include "TIE_CATIBuildShape.h"
TIE_CATIBuildShape(CAAPriEBuildShape); // needed to tie the implementation to its interface

// To declare that UserPad implements CATIBuildShape, insert 
// the following line in the interface dictionary:
//
// CAAPriUserPad  CATIBuildShape  libCAAPriBuildUserPad

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAPriEBuildShape::CAAPriEBuildShape()
{
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAPriEBuildShape::~CAAPriEBuildShape()
{
}

//-------------------------------------------------------------------------
// BuildShape method
//-------------------------------------------------------------------------
int CAAPriEBuildShape::BuildShape()
{
   cout <<" CAAPriEBuildShape::Build" << endl;

    int rcode = 1 ; //OK
    HRESULT rc ;

    //========================================================================================
    //
    // The build method takes place as follows :
    //
    // CATTry
    //
    //     o -1- Cleaning last update error
    //     o -2- Retrieving data for the procedural report
    //     o   -2-1 Retrieving and checking the Profile 
    //     o   -2-2 Retrieving and checking the CATBody accociates with the Profile
    //     o -3- Creating the procedural report
    //     o -4- Running the topological operator 
    //     o   -4-1 Retrieving the geometrical factory
    //     o   -4-2 Retrieving the topological journal
    //     o   -4-3 Running the topological operator 
    //     o -5- Storing the procedural report
    //     o -6- Cleaning useless data
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
  
    CATTopPrism              * pOperatorPrism             = NULL;
    CATIPrtProfile           * pPrtProfile                = NULL;

    CATIMfProcReport         * piProcReport               = NULL;
    CATGeoFactory            * piGeomFactory              = NULL;
    CATSoftwareConfiguration * pSoftConfig                = NULL ;

    CATBody_var                spBodyOnProfile ;

    CATTry
    {

    //==============================================================================================
    //
    // -1- Removing all possible update error associated with the feature
    //
    //==============================================================================================
       
       rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnThis);
       if ( SUCCEEDED(rc) )
       {
          piUpdateErrorOnThis->UnsetUpdateError();
       }

       // This step will be useless in R12
       rc = QueryInterface( IID_CATIGeometricalElement , (void**) &pIGeometricalElementOnThis );
       if ( SUCCEEDED(rc) )
       {   
          // Deletes the last result - method which can throw an error
          pIGeometricalElementOnThis->DeleteScope() ;

          // all is ok - no throw from DeleleScope
          pIGeometricalElementOnThis->Release();
          pIGeometricalElementOnThis = NULL ;
       }

    //==============================================================================================
    //
    // -2- Retrieving Data for the procedural report
    //
    //==============================================================================================
       
       //===========================================================================================
       //
       // -2-1 Retrieving and checking the Profile 
       //      
       //===========================================================================================
       
       CATMathDirection   ExtrusionDirection ;
       CATISpecObject_var spSpecObjectOnProfileElt;

       if ( SUCCEEDED(rc) )
       {
          CATISpecObject  * pSpecObjectOnThis = NULL;
          rc = QueryInterface( IID_CATISpecObject , (void**) &pSpecObjectOnThis );
          if ( SUCCEEDED(rc) )
          {
              // Retrieve the "Profile" Attribute
							CATISpecAttrAccess * piSpecAttrAccessOnThis = NULL; 
							rc = pSpecObjectOnThis->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnThis);
							
              pSpecObjectOnThis->Release();
              pSpecObjectOnThis = NULL ;

							if ( SUCCEEDED(rc) ) 
							{ 
								// Gets a pointer on the Profile attribute key
								CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
								piSpecAttrKeyOnProfile = piSpecAttrAccessOnThis->GetAttrKey("Profile");
								
								if ( NULL != piSpecAttrKeyOnProfile )
								{
									
									CATISpecObject  * pSpecObjectOnProfileAtt = NULL;
									pSpecObjectOnProfileAtt = piSpecAttrAccessOnThis->GetSpecObject(piSpecAttrKeyOnProfile);
									
									piSpecAttrKeyOnProfile->Release();
									piSpecAttrKeyOnProfile = NULL ;

									piSpecAttrAccessOnThis->Release();
									piSpecAttrAccessOnThis = NULL;
									
									if ( NULL != pSpecObjectOnProfileAtt )
									{
                    
                    rc = pSpecObjectOnProfileAtt->QueryInterface( IID_CATIPrtProfile , 
											(void**) &pPrtProfile );
										
                    pSpecObjectOnProfileAtt->Release();
                    pSpecObjectOnProfileAtt = NULL ;
                    
                    if ( SUCCEEDED(rc) )
                    {
											CATMathPlane SketchPlane ;
											rc = pPrtProfile->GetPlane(SketchPlane) ;
											if ( SUCCEEDED(rc) )
											{  
												// Retrieves the normal direction of the sketch plane
												CATMathVector normalDir;
												
												SketchPlane.GetNormal(normalDir);
												ExtrusionDirection = normalDir ;
												
												if ( SUCCEEDED(rc) )
												{
													// Retrieve the elt to follow by the Procedural report
													pPrtProfile->GetElement(1,spSpecObjectOnProfileElt) ;   
													
													if ( NULL_var == spSpecObjectOnProfileElt )
													{
														CATMfErrUpdate *pErrorNoProfile = new CATMfErrUpdate();
														CATUnicodeString Diagnostic("No profile.");
														pErrorNoProfile->SetDiagnostic(1,Diagnostic);
														
														CATThrow(pErrorNoProfile);
													}
												}
											}
                    }
									} 
									else
									{
                    CATMfErrUpdate *pErrorNoProfile = new CATMfErrUpdate();
                    CATUnicodeString Diagnostic("No Profil");
                    pErrorNoProfile->SetDiagnostic(1,Diagnostic);
										
										CATThrow(pErrorNoProfile);
									}
								}
								else 
								{
									piSpecAttrAccessOnThis->Release();
									piSpecAttrAccessOnThis = NULL;

									CATMfErrUpdate *pErrorNoProfile = new CATMfErrUpdate();
									CATUnicodeString Diagnostic("No Attribute Profile.");
									pErrorNoProfile->SetDiagnostic(1,Diagnostic);
									
									CATThrow(pErrorNoProfile);
								}
							}
          }
       }

       //===========================================================================================
       //
       // -2-2 Retrieving and checking the CATBody associated with the Profile
       //
       //===========================================================================================

       if ( SUCCEEDED(rc) && pPrtProfile)
       {
          // Checks if the profile is made with a closed contour
          int nbContour = pPrtProfile->GetContourCount();
          if (nbContour == 1)
          {	
              // retrieve the CATBody associates with the profile
              CATBody_var LocalBody ;
              pPrtProfile->GetBody(0,LocalBody);

              // Check if it is a good profile
              CATDomain * pDomain = LocalBody->GetDomain(1);
              CATWire_var spWireOnDomain(pDomain);
              if (spWireOnDomain != NULL_var)
              {
                 CATBoolean isClosed = spWireOnDomain->IsClosed();
                 if(TRUE != isClosed) 
                 {
                    CATMfErrUpdate *pErrorNotClosedProfile = new CATMfErrUpdate();
                    CATUnicodeString Diagnostic("The associated profile is not closed");
                    pErrorNotClosedProfile->SetDiagnostic(1,Diagnostic);

                    CATThrow(pErrorNotClosedProfile);
                 } else
                 {
                    // This method creates the CATBody associated with the
                    // elt to follow by the procedural report (spSpecObjectOnProfileElt)
                    pPrtProfile->GetBody(1,spBodyOnProfile);

                    if ( NULL_var == spBodyOnProfile )
                    {
                       CATMfErrUpdate *pErrorNoProfileToExtrude = new CATMfErrUpdate();
                       CATUnicodeString Diagnostic("No elt to extrude");
                       pErrorNoProfileToExtrude->SetDiagnostic(1,Diagnostic);
   
                       CATThrow(pErrorNoProfileToExtrude);
                    }
                 }
              }else
              {
                  CATMfErrUpdate *pErrorNoValidProfile = new CATMfErrUpdate();
                  CATUnicodeString Diagnostic("No valid profile");
                  pErrorNoValidProfile->SetDiagnostic(1,Diagnostic);
   
                  CATThrow(pErrorNoValidProfile);
              }
          }else
          {
             CATMfErrUpdate *pErrorNotValidProfile = new CATMfErrUpdate();
             CATUnicodeString Diagnostic("No valid profile");
             pErrorNotValidProfile->SetDiagnostic(1,Diagnostic);

             CATThrow(pErrorNotValidProfile);
          }
       }

       // No more need of this pointers
       if ( NULL != pPrtProfile )
       {
          pPrtProfile ->Release();
          pPrtProfile = NULL ;
       }       

    //==============================================================================================
    //
    // -3- Creating the procedural report
    //     
    //==============================================================================================

      //============================================================================================
      //
      // -3-1 Filling the lists
      //       
      //============================================================================================

       CATLISTV(CATBaseUnknown_var) ListSpec;
       CATListOfCATUnicodeString    ListKeys;
       if ( SUCCEEDED(rc) )
       {
             ListSpec.Append( spSpecObjectOnProfileElt ); 
             ListKeys.Append( MfKeyExtrudedFrom  );
       }
 
      //============================================================================================
      //
      // -3-2 Creating the procedural report with the list
      //       
      //============================================================================================

       if ( SUCCEEDED(rc) )
       {
          rc = QueryInterface( IID_CATIMfProcReport , (void**) &piProcReport );
          if ( SUCCEEDED(rc) )
          {
             // creates the procedural report- the result is associated with the
             // feature itself - so BoolOper is 0
             // The method can throw an error
             int BoolOper = 0;
             piProcReport->CreateProcReport(ListSpec,ListKeys,BoolOper); 
          }
       }

    //==============================================================================================
    //
    // -4- Running the procedural report
    //
    //==============================================================================================
       
       //===========================================================================================
       //
       // -4-1 Retrieving the geometrical factory
       //
       //===========================================================================================

       if ( SUCCEEDED(rc) )
       {
          // Gets a pointer on CATISpecObject.
          CATILinkableObject *piLinkableObjectOnThis = NULL;
          rc = QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObjectOnThis );
          
          if ( SUCCEEDED(rc) )
          {
             // Do not release this pointer
             CATDocument * pDocument = NULL ;
             pDocument = piLinkableObjectOnThis->GetDocument();
   
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
             piLinkableObjectOnThis->Release();
             piLinkableObjectOnThis = NULL ;
          }
       }

       //===========================================================================================
       //
       // -4-2 Retrieving the topological journal which contains the description
       //      of all basic topological operations.
       //
       //===========================================================================================

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

       //===========================================================================================
       //
       // -4-3 Running the topological operator extruding the two curves in both senses 
       //      defined by each direction
       //
       //===========================================================================================
       
       CATBody   *pResultBody = NULL ;

       if ( SUCCEEDED(rc) )
       {
         
          CATLength endOffset = 30.;
          CATLength startOffset = 0.;
    
          pOperatorPrism = CATCreateTopPrism(piGeomFactory,
                                       &TopData,
                                       spBodyOnProfile, 
                                       &ExtrusionDirection, 
                                       startOffset, 
                                       endOffset);

          if ( NULL != pOperatorPrism )
          {
             // The UserPad operation creates matter
             pOperatorPrism->SetOperation(CatBoolUnion);
		
	         CATTopLimitType startLimitType = CatLimOffsetFromProfile;   
             CATTopPropagationType startPropagType = CatPropagSingle;

             // Defines the first limit for the operator
             pOperatorPrism->SetLimit(CatLimStart, 
                             startLimitType,
                             1, 
                             startOffset, 
                             NULL, 
                             CATBody_var(NULL_var), 
                             startPropagType,
                             FALSE);
	
             // Defines the second limit for the operator
             CATTopLimitType endLimitType = CatLimOffsetFromProfile;
             CATTopPropagationType endPropagType = CatPropagSingle;

             pOperatorPrism->SetLimit(CatLimEnd,
                             endLimitType,
                             0, 
                             endOffset, 
                             NULL, 
                             CATBody_var(NULL_var),
                             endPropagType,
                             FALSE);
	
             // Performs the operation
             pOperatorPrism->Run();
	
            // Retrieves the performed body
            pResultBody = pOperatorPrism->GetResult();

          }
       }
 
    //==============================================================================================
    //
    // -5- Storing the procedural report
    //     
    //==============================================================================================
       
       if ( SUCCEEDED(rc) && piProcReport)
       {
          if ( NULL != pResultBody )
          {
              // This method can throw an error
             int BoolOper = 0 ; // same as CreateProcReport
             piProcReport->StoreProcReport(pResultBody,NoCopy,BoolOper); 
          }
          else
          {
             // creates an error if the intersection failed
             CATMfErrUpdate *pErrorBuildShape = new CATMfErrUpdate();
             CATUnicodeString Diagnostic("Error during BuildShape operation");
             pErrorBuildShape->SetDiagnostic(1,Diagnostic);

             CATThrow(pErrorBuildShape);
          }
       }

    //==============================================================================================
    //
    // 6- Cleaning Useless Data
    //
    //==============================================================================================
       
       // Removes the elt to extrude 
       if ( NULL_var != spBodyOnProfile && piGeomFactory)
       {
          piGeomFactory->Remove(spBodyOnProfile);
          spBodyOnProfile = NULL_var ;
       }

       // Releases the topological operator
       if ( NULL != pOperatorPrism )
       {
           delete pOperatorPrism;
           pOperatorPrism = NULL ;
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
       if ( pSoftConfig!= NULL)
       {
	     pSoftConfig->Release();
	     pSoftConfig = NULL ;
       }

       // Releases the geometrical factory
       if(NULL != piGeomFactory) 
       {
           piGeomFactory->Release();
           piGeomFactory = NULL ;
       }

    }
    
    //==============================================================================================
    //
    // -7- Managing errors 
    //
    //==============================================================================================
    
    CATCatch ( CATMfErrUpdate , pUpdateError)
    {
        //------------------------------------------------------------------- 
        // Catches CATMfErrUpdate errors
        //-------------------------------------------------------------------

        // Associates the error with the feature
        if(NULL != piUpdateErrorOnThis) 
        {
            piUpdateErrorOnThis->SetUpdateError(pUpdateError);

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

        // Releases the CATIPrtProfile interface pointer
        if(NULL != pPrtProfile) 
        { 
           pPrtProfile->Release();
           pPrtProfile = NULL ;
        }

        // Removes the elt to extrude 
        if ( NULL_var != spBodyOnProfile && piGeomFactory)
        {
          piGeomFactory->Remove(spBodyOnProfile);
          spBodyOnProfile = NULL_var ;
        }

        // Deletes the first topological operator
        if ( NULL != pOperatorPrism )
        {
            delete pOperatorPrism;
            pOperatorPrism = NULL ;
        }

        // Deletes the pointer on the geometric container
        if(NULL != piGeomFactory) 
        {
            piGeomFactory->Release();
            piGeomFactory = NULL ;
        }

        // Releases the software configuration
        if ( pSoftConfig!= NULL)
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
        //------------------------------------------------------------------ 
        // Catches other CATError errors
        //------------------------------------------------------------------ 

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

        // Removes the elt to extrude 
        if ( NULL_var != spBodyOnProfile && piGeomFactory)
        {
          piGeomFactory->Remove(spBodyOnProfile);
          spBodyOnProfile = NULL_var ;
        }

        // Deletes the topological operator
        if ( NULL != pOperatorPrism )
        {
            delete pOperatorPrism;
            pOperatorPrism = NULL ;
        }

        // Releases the CATIPrtProfile interface pointer
        if(NULL != pPrtProfile) 
        { 
           pPrtProfile->Release();
           pPrtProfile = NULL ;
        }
        // Deletes the pointer on the geometric container
        if(NULL != piGeomFactory) 
        {
            piGeomFactory->Release();
            piGeomFactory = NULL ;
        }

        // Releases the software configuration
        if ( pSoftConfig!= NULL)
        {
	       pSoftConfig->Release();
	       pSoftConfig = NULL ;
        }

        CATThrow(pErrorToThrow);
    }   
    
    CATEndTry;

    if ( FAILED(rc) )
    {
       rcode = 0 ;
    }

   return rcode ;
} 

