// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Use Case  for   : Mechanical Modeler
// Mission         : Extracts the list of topological bodies contained in a *.CATPart document
//
// Type            : Batch program
// Inputs          : Path to an existing *.CATPart file
// Outputs         : Report on console about bodies found in part
//                 : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Document loading in session 
//                   o Access to part within document
//                   o Access to geometrical features set within part 
//
//==========================================================================
// How to execute :
//
//   mkrun -c "CAAMmrPartBodyRequest  FileName"
//
//   with     Filename   : The complete name of a file which holds a mechanical 
//                          Part document.
//
//   ex:
//
//   CAAMmrPartBodyRequest $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrPartBodyRequest.CATPart
//   
// Return code :
//   0 successful execution
//   1 execution failed
// 
//============================================================================================

// compiler includes
#include <iostream.h>

// System includes
#include "CATLib.h" 
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h" 

// ObjectModelerBase includes
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATIContainer.h"
#include "CATIAlias.h"
#include "CATSession.h"

// ObjectSpecsModeler includes
#include "CATISpecObject.h"
#include "CATIDescendants.h"

// GeometricObjects includes
#include "CATICGMObject.h"
#include "CATBody.h"

// MecModInterfaces includes
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"
#include "CATIGeometricalElement.h"

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
  for(int curSetIdx=1; curSetIdx<=iSet.Size(); curSetIdx++)
  {
      CATBaseUnknown_var CurrentSet = iSet[curSetIdx] ;
      if ( NULL_var == CurrentSet ) break ;

      CATIAlias_var aliasOnCurrentSet = CurrentSet ;
      if ( NULL_var != aliasOnCurrentSet)
      {
            cout << "      " << aliasOnCurrentSet->GetAlias().ConvertToChar() ;
      }
      // 
      // 1- Retrieves the result
      //
      CATLISTV(CATBaseUnknown_var) pListResult;

      CATIBodyRequest *pBodyRequestOnCurrentSet = NULL;
      HRESULT rc = CurrentSet->QueryInterface(IID_CATIBodyRequest, (void**)&pBodyRequestOnCurrentSet);
      if ( SUCCEEDED(rc) )
      {   
	     
         rc = pBodyRequestOnCurrentSet->GetResults(stdContext, pListResult);
         if ( SUCCEEDED(rc) )
         {
            int SizeListResult = pListResult.Size() ;
            cout << endl;
            cout <<"         Count of elements in the result list=" << SizeListResult << endl;

            // 
            // 2- Processes each element of the list of results
            //
            for(int curFeatIdx=1; curFeatIdx<=SizeListResult; curFeatIdx++)
            {
               CATBaseUnknown_var CurrentFeat = pListResult[curFeatIdx] ;
               if ( NULL_var == CurrentFeat ) break ;

                CATIAlias_var aliasOnCurFeat =  CurrentFeat ;
                if ( NULL_var != aliasOnCurFeat)
                {
                   cout << "            " << aliasOnCurFeat->GetAlias().ConvertToChar();
                }

                //
                // Gets the topological results linked to the feature
                //
                CATIGeometricalElement *pGeomEltOnCurFeat = 0;
                rc = CurrentFeat->QueryInterface(IID_CATIGeometricalElement, 
                                                               (void**)&pGeomEltOnCurFeat);
                if( SUCCEEDED(rc) )
                {       
                   CATBody_var ResultBody = pGeomEltOnCurFeat->GetBodyResult();
        
                   if( NULL_var != ResultBody )
                   {
                      CATICGMObject *pCurTopo = NULL ;
                      rc=ResultBody->QueryInterface(IID_CATICGMObject,(void**)&pCurTopo);
                      if( SUCCEEDED(rc) )
                      {            
                         CATULONG32 curResultTag = pCurTopo->GetPersistentTag();
                     
                         cout <<", its topological result is with the following tag : " ;
                         cout << curResultTag << endl;
                     
                         pCurTopo->Release();
			             pCurTopo = NULL ;
                      }else cout << "pas de topo" << endl;
                   }else cout <<" pas de body" << endl;

                   pGeomEltOnCurFeat->Release();
                   pGeomEltOnCurFeat = NULL ;
                }
            }
         }else cout <<" E_FAIL for GetResult" << endl;

         pBodyRequestOnCurrentSet->Release();
         pBodyRequestOnCurrentSet = NULL ;
      }
      else 
      {
          cout <<" pas QI sur CATIBodyRequest" << endl;
      }
  } // Next curBodyIdx
  cout << endl;
}

void PrintGeometricalFeaturesSetsResult2(const CATLISTV(CATISpecObject_var) &iSetSpecObj) 
{
   CATLISTV(CATBaseUnknown_var) iSetBU ;
   for (int i=1; i<=iSetSpecObj.Size(); i++)
   {
      iSetBU.Append(iSetSpecObj[i]);
   }
   PrintGeometricalFeaturesSetsResult(iSetBU);
}

/**
 * Executes the program: reads the argument and looks for topologic results in
 * the corresponding part.
 * ============================================================================
 */

int main(int    iArgc,   // Number of arguments (1) 
         char **iArgv)   // Path to an existing *.CATPart document
{

  //
  // 1- Check arguments
  //
  if( 2!=iArgc ) 
  {
	  cout <<"CAAMmrPartBodyRequest FileName" << endl;
	  cout <<"Where FileName is the complete path of a Part document" <<endl;
	  cout <<"You can use the following Part: " ;
	  cout <<" $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrPartBodyRequest.CATPart"<< endl;
	  return 1;
  }

  cout <<"The CAAMmrPartBodyRequest use case begins" << endl ;
  
  //
  // 2- Creates a session
  //
  char *pSessionName = "SampleSession";
  CATSession *pSession = 0;
  HRESULT rc = ::Create_Session(pSessionName, pSession) ;
  if ( FAILED(rc) )
  {
      cout <<" Error in creating a session" << endl;
      return 1 ;
  }

  //
  // 3- Loads the document and initializes it
  //
  CATDocument *pDoc = 0;
  rc = CATDocumentServices::OpenDocument(iArgv[1], pDoc) ;
  if ( SUCCEEDED(rc) && ( NULL !=pDoc)  )
  {
       cout <<"   The document " << iArgv[1] << " is opened" << endl ;
  }else
  {
      cout <<" Pb in opening the " << iArgv[1] <<" document" << endl;
      return 1 ;
  }
    
  //
  // 4- Queries on the document to get the root container
  // 

  CATInit *pDocAsInit = NULL ;
  rc = pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit);
  if ( FAILED(rc) )
  {
      cout <<" Error in retrieving a QI on CATInit" << endl;
      return 1 ;
  }
  
  CATIPrtContainer *pSpecContainer = NULL ;
  pSpecContainer = (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");

  if ( NULL == pSpecContainer )
  {
      cout <<" Error in retrieving the Root container" << endl;
      return 1 ;
  }

  pDocAsInit->Release();
  pDocAsInit = NULL ;

  //
  // 5- Retrieves on the root container (CATPrtCont) to get the Part feature
  // 
        
  CATIPrtPart_var spPart = pSpecContainer->GetPart() ;
  if ( NULL_var == spPart )
  {
     cout <<" Error in retrieving the Part feature" << endl;
     return 1 ;
  }

  pSpecContainer->Release();
  pSpecContainer = NULL ;

  //
  // 6- Retrieves the list of geometrical features set using CATIDescendants ...
  //   
  cout <<"Using CATIDescendants" << endl <<endl;
  CATIDescendants *pPartAsDescendants = 0;
  rc = spPart->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendants) ;
  if ( FAILED(rc) )
  {
     cout <<" Error in retrieving a QI on CATIDescendants" << endl;
     return 1 ;
  }
  	  
  // 6-1 Extracts the lists of its Body Features
  CATLISTV(CATISpecObject_var) BodyListDesc;  
  pPartAsDescendants->GetAllChildren("CATIMechanicalTool", BodyListDesc);
  cout <<"   The list of Body Features:" ;
  PrintGeometricalFeaturesSetsResult2(BodyListDesc);

  // 6-2 Extracts the lists of its OGS
  CATLISTV(CATISpecObject_var) OGSList;  
  pPartAsDescendants->GetAllChildren("CATIMmiOrderedGeometricalSet",OGSList);
  cout <<"   The list of Ordered Geometrical Set:"  ;
  PrintGeometricalFeaturesSetsResult2(OGSList);

  // 6-3 Extracts the lists of its GS
  CATLISTV(CATISpecObject_var) GSList;  
  pPartAsDescendants->GetAllChildren("CATIMmiNonOrderedGeometricalSet",GSList);
  cout <<"   The list of Geometrical Set:"  ;
  PrintGeometricalFeaturesSetsResult2(GSList);

  pPartAsDescendants->Release();
  pPartAsDescendants = NULL ;

  //
  // 7- Retrieves the list of geometrical features set using CATIPartRequest ...
  //   
  cout <<"Using CATIPartRequest" << endl <<endl;
  CATIPartRequest *pPartAsRequest = 0;
  rc = spPart->QueryInterface(IID_CATIPartRequest, (void**)&pPartAsRequest) ;
  if ( FAILED(rc) )
  {
     cout <<" Error in retrieving a QI on CATIPartRequest" << endl;
     return 1 ;
  }
  
  const CATUnicodeString stdContext(" "); // Sets the context for topo bodies lookup 
  	  
  // 7-1 Extracts the lists of its Body Features
  CATLISTV(CATBaseUnknown_var) BodyList;  
  pPartAsRequest->GetSolidBodies(stdContext, BodyList);
  cout <<"   The list of Body Features:" ;
  PrintGeometricalFeaturesSetsResult(BodyList);

  // 7-2 Extracts the lists of its surfacic sets
  CATLISTV(CATBaseUnknown_var) SurfacicSetList;  
  pPartAsRequest->GetSurfBodies(stdContext, SurfacicSetList);
  cout <<"   The list of Surfacic Sets:"  ;
  PrintGeometricalFeaturesSetsResult(SurfacicSetList);

  pPartAsRequest->Release();
  pPartAsRequest = NULL ;
          

  //
  // 8- Ends session and drops document
  //
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc) )
  {
     cout << "ERROR in deleting session" << endl ;
     return 1;
  }
    
  cout <<"The CAAMmrPartBodyRequest use case is ended" << endl ;

  return 0;
}

