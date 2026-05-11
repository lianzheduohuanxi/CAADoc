// COPYRIGHT DASSAULT SYSTEMES 2012
//============================================================================================
// 
// Mission         : Recolor fillets and planar faces in a 3D Shape Representation 
//
// Note : CAAV5V6MmrFeatureTopoBRep is the same use case as CAAMmrFeatureTopoBRep. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//
// Steps :        
// 
//    1-    Checks number of arguments.
//	  2-    Initialize the session. 		                   
//    3-    Retrieves the MechanicalPart.  
//    4-    Colorizes in green all the fillet features  
//    5-    Colorizes in blue the planar faces of the result associated with the main Part body.   
//    6-    End of session.  
//                   
//
//==========================================================================
//
//How to execute :
//
// In V6
// =====
//	 mkrun -c "CAAV5V6MmrFeatureTopoBRep Repository Server User Password SecurityCtx PLMRepType PLMExternalIDValue Version"
//
//	 where    
//       Repository	        : The name of the repository (or provider) 
//		 Server		        : The server as Host:Port_number/RootURI
//		 User		        : The user identifier
//       Password	        : The user password  
//		 SecurityCtx        : A string representing the security context (Role.Organization.Project
//                          Choose Role as Designer ( as the use case modifies the PLM Data)
//       PLMRepType         : A string representing PLM Representation type 
//		 PLMExternalIDValue : The value of the PLM_ExternalID attribute of a PLM representation reference. 
//		 Version            : The value of the V_version attribute of a PLM representation reference. 
//   
//
// In V5
// =====
//   mkrun -c "CAAV5V6MmrFeatureTopoBRep  FileNameIn FileNameOut"
//
//   where    FileNameIn  : The complete name of a Part document
//            FileNameOut : The complete name to saveas FileNameIn                         
//
//   ex:
//
//   CAAMmrFeatureTopoBRep $WSROOT/CAAV5V6MechanicalModeler.edu/InputData/CAAMmrPart.CATPart
//                             PartModified.CATPart
//
//   In the current directory, PartModified.CATPart will be created
//
//============================================================================================



// System Framework
#include "CATLISTV_CATBaseUnknown.h" 
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"

// GMModelInterfaces
#include "CATBody.h"
#include "CATCell.h"

// GeometricObjects
#include "CATGeometry.h"

// CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"
#include "CATIMmiUseGeometryAccess.h"
#include "CATIMmiUseBRepDecodeServices.h"
#include "CATIMmiUseBRepAccess.h"
#include "CATIMmiUseGeometricalElement.h"
#include "CATMmiUseServicesFactory.h"
#include "CATLISTV_CATIMmiUseBRepAccess.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"
#include "CATIMmiUsePrtPart.h"
#include "CATIMmiUseBodyContent.h"

// CATMecModLiveUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"

// VisualizationInterfaces Framework
#include "CATIVisProperties.h"            // To change faces color
#include "CATVisPropertiesValues.h"

// Local framework
#include "CAAV5V6MmrInitSession.h" 

// C++ Library
#include <iostream.h> 

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
//CATPLMIdentificationAccess Framework
#include "CATIPLMComponent.h"                     // interface valid for all PLM component 

//CATPLMComponentInterfaces
#include "CATIPLMNavRepReference.h"

//CATPLMIntegrationUse Framework
#include "CATAdpSaver.h"

//CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

// CAT3DPhysicalRepInterfaces
#include "CATIPsiRepresentationLoadMode.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATSessionServices.h"     // To Create,delete a session
#include "CATDocumentServices.h" 

#endif

HRESULT GetAllFillet( CATIMmiMechanicalFeature_var ispPartFeature, CATListValCATBaseUnknown_var & ioListResult) ;

int main(int iArgc,
         char **iArgv) 
                      
{
	//
	// 1- Checks number of arguments
	//
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	if( 9 != iArgc )
	{
		cout <<"CAAMmrFeatureTopoBRep <repository> <server> <user> <password> <SecurityCtx> <PLMRepType> <PLMExternalIDValue> <version>" << endl;
		return 1;
	}
#else
//============================================== 
// V5 only
//==============================================
	if( 3!=iArgc )
    {
	    cout <<"CAAMmrFeatureTopoBRep FileNameIn FileNameOut" << endl;
	    cout <<"Where FileNameIn is the complete path of a CATPart document" <<endl;
        cout <<" and FileNameOut, the complete path of the output document" <<endl;
	    cout <<"For FileNameIn, you can use the following Part: " ;
	    cout <<" $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrPart.CATPart"<< endl;
        return 1;
    }
#endif
	cout << "The CAAMmrFeatureTopoBRep use case begins" << endl;

	//
	// 2 - Initializes the session 
	//
	
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
 
	//-----------------------------------------------------------------------------------
	//    Creates a session with : repository, server, user,password, SecurityCtx
	//    Loads the Representation with the values of the identifiant set attributes
	//    Retrieves the Part Container
	//-----------------------------------------------------------------------------------
	//
	CATString PLM_RepType = iArgv[6];
	CATUnicodeString PLM_ExternalIDValue = iArgv[7];
	CATUnicodeString V_versionValue = iArgv[8];
	CATIMmiPrtContainer * piPartContainer = NULL;
	CATOmbLifeCycleRootsBag Bag;

	HRESULT rc = :: CAAV5V6MmrInitSession(iArgv[1], iArgv[2], iArgv[3],iArgv[4], iArgv[5],
		                              PLM_RepType, PLM_ExternalIDValue, V_versionValue,
		                              Bag, piPartContainer);

	
	if (FAILED(rc) || (NULL == piPartContainer))
		return 1;

	cout << "The Representation has been opened and the Part container has been retrieved"<< endl;

#else
//============================================== 
// V5 only
//==============================================
    //
    //    Creates a session
    //    Loads the Part document
    //    Retrieves the Part Container
    // 
	char *pSessionName = "SampleSession";
    CATIMmiPrtContainer * piPartContainer = NULL;
    CATUnicodeString FileName =  iArgv[1];
    CATDocument *pDoc = NULL;
    HRESULT rc =  CAAV5V6MmrInitSession(pSessionName, FileName, pDoc, piPartContainer) ;

    if (FAILED(rc) || (NULL == piPartContainer))
		return 1;

    cout << "The Part document has been opened and the Part container has been retrieved"<< endl;
 
#endif	

    //
	// 3- Retrieves the MechanicalPart of the reprsentation
	//
	CATIMmiMechanicalFeature_var spMechFeatOnPart;  
    rc = piPartContainer->GetMechanicalPart(spMechFeatOnPart);
	
    if (FAILED(rc) || (NULL_var == spMechFeatOnPart))
	  return 1;
	
	CATIPartRequest_var spPartRequest = spMechFeatOnPart; 

    if (FAILED(rc) || NULL_var == spPartRequest)
	  return 1;

	piPartContainer->Release();
	piPartContainer = NULL ;

	//
	// 4- Colorizes in green all the fillet features
	//
	// 
	// 4-1 Gets the fillet features
	//
	CATListValCATBaseUnknown_var filletFeatures;
    rc = GetAllFillet(spPartRequest,filletFeatures);
    if (FAILED(rc))
      return 1;

	for(int currentFillet=1; currentFillet<=filletFeatures.Size(); currentFillet++)
	{
		CATBaseUnknown_var currentfilletFeature = filletFeatures[currentFillet];
		if ( NULL_var != currentfilletFeature )
		{
			//
			// 4-2 Gets the BRep associated with the fillet
			//
			CATIMmiUseGeometryAccess *pFilletAsGeomAccess = NULL;
			rc= currentfilletFeature->QueryInterface(IID_CATIMmiUseGeometryAccess,(void**)&pFilletAsGeomAccess) ;				 

			if ( SUCCEEDED(rc) )
			{
				CATListValCATIMmiUseBRepAccess_var filletBReps;
				pFilletAsGeomAccess->GetBReps(filletBReps);

				// 4-3 Colorizes BRep 
				for(int currentBRep=1; currentBRep<=filletBReps.Size(); currentBRep++)
				{
					CATIVisProperties *pFilletBrepAsGraphics = 0;
					const CATIMmiUseBRepAccess_var & currentfilletBRep = filletBReps[currentBRep];
					if (NULL_var != currentfilletBRep)
						rc =  currentfilletBRep->QueryInterface(IID_CATIVisProperties,(void**)&pFilletBrepAsGraphics) ;					
					else
						rc = E_FAIL;

					if ( SUCCEEDED(rc) )
					{                
						CATVisPropertiesValues color;
						color.SetColor(0, 255, 0); // green
						pFilletBrepAsGraphics->SetPropertiesAtt(color, CATVPColor, CATVPMesh);

						pFilletBrepAsGraphics->Release();
						pFilletBrepAsGraphics = NULL ;
					}
				}
				pFilletAsGeomAccess->Release();
				pFilletAsGeomAccess = NULL ;
			}
		}
	}
          
	//
	// 5- Colorizes in blue the planar faces of the result associated with  
	//    the main Part body

	//
	// 5-1 Retrieves the main body
	//
	CATBaseUnknown_var spMainPartBody ;
	rc = spPartRequest->GetMainBody("",spMainPartBody);
	if ( FAILED(rc) || ( NULL_var == spMainPartBody) )
		return 1;

	//
	// 5-2 Retrieves the feature holding the result of the main body
	//     It's the first element of the list returned by GetResults
	//
	CATIBodyRequest_var spMainPartBodyBodyRequest = spMainPartBody ;
	if ( NULL_var == spMainPartBodyBodyRequest )
		return 1;

	CATLISTV(CATBaseUnknown_var) ListResult ;
	rc = spMainPartBodyBodyRequest->GetResults("",ListResult);
	if ( FAILED(rc) || (0 == ListResult.Size() ))
		return 1;
  
	//
	// 5-3 Retrieves a CATIMmiUseGeometricalElement pointer on the feature result
	//
	CATIMmiUseGeometricalElement_var spFeatureResultGeomElem = ListResult[1] ;
	if ( NULL_var == spFeatureResultGeomElem )
		return 1;

	//
	// 5-4 Retrieves the CATBody associated with the feature result
	//
	CATBody_var spPartTopoBody ;
	spFeatureResultGeomElem->GetBodyResult(spPartTopoBody);
	if ( NULL_var == spPartTopoBody )
		return 1;

	//
	// 5-5 Gets all two dimensional topo cells representing the Part body
	//
	CATLISTP(CATCell) cells;
	spPartTopoBody->GetAllCells(cells, 2);

	//
	// 5-6 Processes the two dimensional topo cells 
	//
	for(int currentCell=1; currentCell<=cells.Size(); currentCell++)
	{
		CATCell_var pCell ( cells[currentCell] );
		if ( NULL_var != pCell )
		{
			CATGeometry *pGeometry = pCell->GetGeometry();

			if ( (NULL != pGeometry) && (pGeometry->IsATypeOf(CATPlaneType)) )
			{
				CATIMmiUseBRepAccess_var spBRepAccess ; 
				CATIMmiUseBRepDecodeServices_var spBRepDecodeService ;
				CATMmiUseServicesFactory::CreateBRepDecodeServices(spBRepDecodeService); 
                
                spBRepDecodeService->DecodeCellInGeomElt(spBRepAccess,pCell, spFeatureResultGeomElem);
				
				if( NULL_var!=spBRepAccess )
				{
					//
					// 5-7 Colorizes BRep
					//
					CATIVisProperties *pBRepAccessAsGraphics = 0;
					rc= spBRepAccess->QueryInterface(IID_CATIVisProperties,(void**)&pBRepAccessAsGraphics) ;
									 
					if ( SUCCEEDED(rc) )
					{
						CATVisPropertiesValues color;
						color.SetColor(0, 0, 255); // Blue
						pBRepAccessAsGraphics->SetPropertiesAtt(color, CATVPColor, CATVPMesh);
                  
						pBRepAccessAsGraphics->Release();
						pBRepAccessAsGraphics = NULL ;
					}
				}
			}
		}
	}
	//
	// 6- End of session
	//
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

	// Save the session
	CATAdpSaver saver;
    rc = saver.Save();
	
	if (FAILED(rc))
		return 1;

	cout <<"   Session saved successfully" <<endl;
 
	// Unload components from session
    Bag.RemoveAll();

	// Close the session
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc))
		return 1;

	cout <<"   Session closed successfully" << endl;

#else
//============================================== 
// V5 only
//==============================================  

   cout << "end of session "<<endl;

   // Save the document
   rc = CATDocumentServices::SaveAs(*pDoc, iArgv[2]);
   if (S_OK == rc)
   {
     cout << "   The "<< iArgv[2] ;
     cout << " document contains the modified Part" << endl ;
   }
   else
   {
     cout << "Error in saving document "<< iArgv[2] << endl;
     return 1;
   }   
 
   //
   // Close the document
   //
   rc = CATDocumentServices::Remove(*pDoc);
   if (FAILED(rc))
   {
     cout << "Error in closing document" << endl ;
     return 1;
   }
    pDoc = NULL ;

   //
   // Delete all documents in session	
   //
   rc = Delete_Session(pSessionName);
   if (FAILED(rc))
   {
     cout << "Error in deleting session" << endl ;
     return 1;
   }     
#endif

   cout << "The CAAMmrFeatureTopoBRep use case is ended" << endl;

   return 0;
}

HRESULT GetAllFillet(CATIMmiMechanicalFeature_var spPartFeature, CATListValCATBaseUnknown_var & ListResults) 
{
	HRESULT rc = E_FAIL;
  
  if (spPartFeature == NULL_var) 
    return E_INVALIDARG ;

  // Retrieve main body (PartBody feature) 
  CATIPartRequest_var spPartReq = spPartFeature;
  CATBaseUnknown_var spMainBody = NULL_var; 
  rc = spPartReq->GetMainBody("",spMainBody);
  
  if (FAILED(rc))
    return E_FAIL;

  if (spMainBody == NULL_var)
    return E_FAIL;

  // Retrieve list of features contained in main body
  CATIMmiUseBodyContent_var spBodyContent = spMainBody;
  CATListValCATBaseUnknown_var listFeat;
  
  if (spBodyContent != NULL_var)
    rc = spBodyContent->GetMechanicalFeatures(listFeat);

  if (FAILED(rc))
    return E_FAIL;

  // Select only fillets from the list
  for (int currentFeat = 1;currentFeat<=listFeat.Size();currentFeat++)
  {
    CATBaseUnknown* pFillet = NULL;
    CATBaseUnknown_var hFeat = listFeat[currentFeat];
    if (!!hFeat)
    {
      // Is the feature a fillet?
      pFillet = hFeat->QueryInterface("CATIPdgUseFillet");
      if (pFillet)
      {
        ListResults.Append(hFeat);
        pFillet->Release();
      }
    }
  }
 
  //
  return rc;

}

