// COPYRIGHT DASSAULT SYSTEMES 2012
//================================================================================================================
//
// Mission         : Extracts the list of topological bodies contained in a Part 
//
// Note : CAAV5V6MmrPartBodyRequest is the same use case as CAAMmrPartBodyRequest. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
// Steps :        
// 
//    1-    Checks number of arguments.
//	  2-    Initialization : creates a session, loads the part and retrieves the specification container.		                   
//    3-    Retrieves the MechanicalPart of the representation.  
//    4-    Retrieves the list of geometrical features set using CATIPartRequest.   
//    5-    Closes the session.      
//
//=================================================================================================================
//
//How to execute :
//
// In V6
// =====
//	 mkrun -c "CAAV5V6MmrPatBodyRequest Repository Server UserId Password SecurityCtx PLMRepType PLMExternalID Version"
//
//	 where    Repository	  : The name of the repository (or provider) 
//			  Server		  : The server as Host:Port_number/RootURI
//			  User			  : The user identifier
//            Password		  : The user password  
//			  SecurityCtx     : A string representing the security context (Role.Organization.Project)
//							              Choose Role as Reviewer ( as the use case does not modify the PLM Data)
//			  PLMRepType      : A string representing PLM Representation type
//			  PLMExternalID   : The value of the PLM_ExternalID attribute of a PLM representation reference 
//			  Version         : The value of the V_version attribute of a PLM representation reference 
//   
//
// In V5
// =====
//
//   mkrun -c "CAAV5V6MmrPartBodyRequest  FileName"
//
//   where     Filename   : The complete name of a file which holds a mechanical 
//                          Part document.
//   ex:
//
//   CAAV5V6MmrPartBodyRequest $WSROOT/CAAMechanicalModeler.edu/InputData/CAAV5V6MmrPartBodyRequest.CATPart
//
//============================================================================================

#include "CATIAV5Level.h"

// Local framework
#include "CAAV5V6MmrInitSession.h"  

// CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"
#include "CATIMmiUseGeometricalElement.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// CATMecModLiveUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"

// ObjectModelerSystem Framework for V6
// ObjectModelerBase Framework for V5
#include "CATIAlias.h"

// GeometricObjects Framework
#include "CATICGMObject.h"

// GMModelInterfaces Framework
#include "CATBody.h"

// System includes
#include "CATLib.h" 
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"

// C++ Standard library
#include "iostream.h"  


#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//CATPLMIdentificationAccess Framework
#include "CATIPLMComponent.h"                    

//CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"
#include "CATPLMSessionServices.h"

// CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationLoadMode.h"

#else
//============================================== 
// V5 only
//============================================== 
// ObjectModelerBase Framework
#include "CATSessionServices.h"

#endif



//
// Displays the result of a list of Geometrical Features Sets
//

void PrintGeometricalFeaturesSetsResult(const CATLISTV(CATBaseUnknown_var) &iSet) 
{
  const CATUnicodeString stdContext(""); 

  cout <<" , has " << iSet.Size() << " element(s)" << endl;

  //
  // Processes all the sets
  //
  for (int curSetIdx=1; curSetIdx<=iSet.Size(); curSetIdx++)
  {
    CATBaseUnknown_var CurrentSet = iSet[curSetIdx];
    if ( NULL_var == CurrentSet ) break;

    CATIAlias_var aliasOnCurrentSet = CurrentSet ;
    if ( NULL_var != aliasOnCurrentSet)
    {
      cout << "      " << aliasOnCurrentSet->GetAlias().ConvertToChar() ;
    }

    // 
    // Retrieves the result
    //
    CATLISTV(CATBaseUnknown_var) pListResult;

    CATIBodyRequest *pBodyRequestOnCurrentSet = NULL;
    HRESULT rc = CurrentSet->QueryInterface(IID_CATIBodyRequest, (void**)&pBodyRequestOnCurrentSet);
    if (SUCCEEDED(rc))
    {      
      rc = pBodyRequestOnCurrentSet->GetResults(stdContext, pListResult);
      if (SUCCEEDED(rc))
      {
        int SizeListResult = pListResult.Size() ;
        cout << endl;
        cout <<"         Count of elements in the result list=" << SizeListResult << endl;

        // 
        // Processes each element of the list of results
        //
        for(int curFeatIdx=1; curFeatIdx<=SizeListResult; curFeatIdx++)
        {
          CATBaseUnknown_var CurrentFeat = pListResult[curFeatIdx];
          if (NULL_var == CurrentFeat)
            break;

          CATIAlias_var aliasOnCurFeat =  CurrentFeat ;
          if (NULL_var != aliasOnCurFeat)
            cout << "            " << aliasOnCurFeat->GetAlias().ConvertToChar();

          //
          // Gets the topological results linked to the feature
          //
          CATIMmiUseGeometricalElement *pGeomEltOnCurFeat = 0;
          rc = CurrentFeat->QueryInterface(IID_CATIMmiUseGeometricalElement, (void**)&pGeomEltOnCurFeat);
                                                               
          if (SUCCEEDED(rc))
          {       
            CATBody_var ResultBody;
				    pGeomEltOnCurFeat->GetBodyResult(ResultBody);
        
            if (NULL_var != ResultBody)
            {
              CATICGMObject *pCurTopo = NULL;
              rc=ResultBody->QueryInterface(IID_CATICGMObject,(void**)&pCurTopo);
              if (SUCCEEDED(rc))
              {   
						    unsigned int curResultTag = pCurTopo->GetPersistentTag();
                     
                cout <<", Topological result tag = ";
                cout << curResultTag << endl;
                     
                pCurTopo->Release();
			          pCurTopo = NULL ;
              }
              else 
                cout << "no topology" << endl;
            }

            pGeomEltOnCurFeat->Release();
            pGeomEltOnCurFeat = NULL;
          }
        }
      }
      else
        cout <<" E_FAIL for GetResult" << endl;

      pBodyRequestOnCurrentSet->Release();
      pBodyRequestOnCurrentSet = NULL;
    }
  } // Next curBodyIdx
  cout << endl;
}


/**
 * ===========================================================================
 * Executes the program: reads the argument and looks for topologic results in
 * the corresponding part.
 * ============================================================================
 */

int main(int    iArgc,   
         char **iArgv)   
{
	//
	// 1- Checks arguments
	//
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	if (9 != iArgc) 
	{
		cout <<"CAAV5V6MmrPartBodyRequest <Repository> <Server> <User> <Password> <SecurityCtx> <PLMRepType> <PLMExternalIDValue> <version>"<< endl;
		return 1;
	}
#else
//============================================== 
// V5 only
//============================================== 
	if( 2!=iArgc ) 
    {
	  cout <<"CAAV5V6MmrPartBodyRequest FileName" << endl;
	  cout <<"Where FileName is the complete path of a Part document" <<endl;
	  cout <<"You can use the following Part: " ;
	  cout <<" $WSROOT/CAAMechanicalModeler.edu/InputData/CAAV5V6MmrPartBodyRequest.CATPart"<< endl;
	  return 1;
  }
#endif

	cout <<"The CAAV5V6MmrPartBodyRequest use case begins" << endl ;
  
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	//
    //-----------------------------------------------------------------------------------
	// 2- Creates a session with : repository, server, user,password, SecurityCtx
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
  // 2- Creates a session
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
  // 3- Retrieves the mechanical part 
  //
  CATIMmiMechanicalFeature_var spMechFeatOnPart;  
  rc = piPartContainer->GetMechanicalPart(spMechFeatOnPart);
	
  if (FAILED(rc) || (NULL_var == spMechFeatOnPart))
	return 1;
	
  CATIPartRequest_var spPartRequest = spMechFeatOnPart; 

  if (NULL_var == spPartRequest)
	return 1;

  piPartContainer->Release();
  piPartContainer = NULL;

  //
  // 4- Retrieves the list of geometrical features set using CATIPartRequest 
  //   
  const CATUnicodeString stdContext(" "); // Sets the context for topo bodies lookup 
  	  
  // 4-1 Extracts the lists of its Body Features
  CATLISTV(CATBaseUnknown_var) BodyList;  
  spPartRequest->GetSolidBodies(stdContext, BodyList);
  cout <<"   The list of Body Features:";
  PrintGeometricalFeaturesSetsResult(BodyList);

  // 4-2 Extracts the lists of its Surfacic Feature sets
  CATLISTV(CATBaseUnknown_var) SurfacicSetList;  
  spPartRequest->GetSurfBodies(stdContext, SurfacicSetList);
  cout <<"   The list of Surfacic Sets:"  ;
  PrintGeometricalFeaturesSetsResult(SurfacicSetList);

  //
  // 5- Closes the session 
  //
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
  // Unload components from session
  Bag.RemoveAll();

  rc = CATPLMSessionServices::ClosePLMSession();
 
#else
//============================================== 
// V5 only
//============================================== 
  rc = ::Delete_Session(pSessionName);
 
#endif
	
  if (FAILED(rc) )
	return 1;

  cout <<"   Session closed successfully" <<endl;
    
  cout <<"The CAAV5V6MmrPartBodyRequest use case is ended" << endl ;

  return 0;
}

