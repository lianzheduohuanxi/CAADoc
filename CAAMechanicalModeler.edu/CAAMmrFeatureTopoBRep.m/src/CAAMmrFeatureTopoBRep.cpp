// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// 
// Mission         : Recolor fillets and planar faces in a Part document
//
//
// Illustrates     : o Document loading in session 
//                   o Access to part within document
//                   o Access to hierarchy of features within part, 
//                     filtering on fillets
//                   o Access to topology associated to features
//                   o Graphical modification of this topology
//                   o Direct access to all topological cells linked to part, 
//                     filtering on planar faces
//                   o Graphical modification of these faces
//                   o "save as" of the modified document
//
//==========================================================================
// How to execute :
//
//   mkrun -c "CAAMmrFeatureTopoBRep  FileNameIn FileNameOut"
//
//   where    FileNameIn  : The complete name of a Part document
//            FileNameOut : The complete name to saveas FileNameIn                         
//
//   ex:
//
//   CAAMmrFeatureTopoBRep $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrPart.CATPart
//                             PartModified.CATPart
//
//   In the current directory, PartModified.CATPart will be created
//
//============================================================================================

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATSessionServices.h"     // To Create,delete a session
#include "CATDocumentServices.h" 
#include "CATInit.h"
#include "CATIContainer.h"
#include "CATSession.h"

// ObjectSpecsModeler Framework
#include "CATIDescendants.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"

// NewTopologicalObjects Framework
#include "CATBody.h"
#include "CATCell.h"

// GeometricObjects Framework
#include "CATGeometry.h"

// MechanicalModeler Framework
#include "CATIPrtContainer.h"
#include "CATIMfGeometryAccess.h"
#include "CATMfBRepDecode.h"
#include "CATIPrtPart.h"
#include "CATIPartRequest.h"
#include "CATIBodyRequest.h"

// MecModInterfaces Framework
#include "CATIBRepAccess.h"
#include "CATIGeometricalElement.h"

// Visualization Framework
#include "CATIVisProperties.h"            // To change faces color
#include "CATVisPropertiesValues.h"

// System Framework
#include "CATBaseUnknown.h"

// 
#include <iostream.h> 

int main(int iArgc,
         char **iArgv) 
                      
{
  // return code
  int rcode = 0;

  //
  // 1- Checks number of arguments
  //
  if( 3!=iArgc )
  {
	  cout <<"CAAMmrFeatureTopoBRep FileNameIn FileNameOut" << endl;
	  cout <<"Where FileNameIn is the complete path of a CATPart document" <<endl;
      cout <<" and FileNameOut, the complete path of the output document" <<endl;
	  cout <<"For FileNameIn, you can use the following Part: " ;
	  cout <<" $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrPart.CATPart"<< endl;
      return 1;
  }

  cout << "The CAAMmrFeatureTopoBRep use case begins" << endl;

  //
  // 2- Creates the session
  //
  char *pSessionName = "Sample session";
  CATSession *pSession = NULL;
  HRESULT rc = Create_Session(pSessionName, pSession) ;
  if( FAILED(rc) )
  {
	  cout << "can not open session" << endl;
	  return 1 ;
  }
  
  //
  // 3- Loads the input document
  //
  CATDocument *pDoc = NULL;
  rc= CATDocumentServices::OpenDocument(iArgv[1], pDoc) ;

  if( FAILED(rc) )
  {
      cout <<"Error in opening the document: " << iArgv[1] << endl ;
	  return 1;
  }
  cout <<"   " << iArgv[1] << " is opened" << endl;

  CATInit *pDocAsInit = NULL;
  rc= pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
  if( FAILED(rc) )
  {
	  cout << "Error, the document does not implement CATInit"<< endl;
	  return 1;
  }
        
  //
  // 4- Gets root container of the document
  //
  CATIPrtContainer *pSpecContainer = NULL ;
  pSpecContainer = (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");

  pDocAsInit->Release();
  pDocAsInit = NULL ;

  if( NULL == pSpecContainer )
  {
      cout <<"Error, the root container is NULL" << endl;
	  return 1;
  }

  //
  // 5- Retrieves the MechanicalPart of the document
  //
  CATIPrtPart_var spPart ( pSpecContainer->GetPart() );
  if ( NULL_var == spPart )
  {
      cout <<"Error, the MechanicalPart is NULL" << endl;
	  return 1;
  }

  pSpecContainer->Release();
  pSpecContainer = NULL ;

  //
  // 6- Colorizes in green all the fillet features
  //

  // 
  // 6-1 Gets the fillet features
  //
  CATLISTV(CATISpecObject_var) filletFeatures;
  CATIDescendants *pPartAsDescendant = NULL;
  rc = spPart->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant) ;
  if( FAILED(rc) )
  {
	  cout <<" The MechanicalPart does not implement CATIDescendant" << endl;
	  return 1;
  }
          
  pPartAsDescendant->GetAllChildren("CATIFillet", filletFeatures);

  for(int currentFillet=1; currentFillet<=filletFeatures.Size(); currentFillet++)
  {
     const CATISpecObject_var& currentfilletFeature = filletFeatures[currentFillet];
     if ( NULL_var != currentfilletFeature )
     {
        //
        // 6-2 Gets the BRep associated with the fillet
        //
        CATIMfGeometryAccess *pFilletAsGeomAccess = NULL;
        if (NULL_var != currentfilletFeature)
           rc= currentfilletFeature->QueryInterface(IID_CATIMfGeometryAccess,
                                                      (void**)&pFilletAsGeomAccess) ;
        else
           rc = E_FAIL;
              
        if ( SUCCEEDED(rc) )
		{
           CATLISTV(CATBaseUnknown_var) filletBReps;
           pFilletAsGeomAccess->GetBReps(filletBReps);

           // 6-3 Colorizes BRep 
           for(int currentBRep=1; currentBRep<=filletBReps.Size(); currentBRep++)
		   {
              CATIVisProperties *pFilletBrepAsGraphics = 0;
              const CATBaseUnknown_var& currentfilletBRep = filletBReps[currentBRep];
              if (NULL_var != currentfilletBRep)
                 rc =  currentfilletBRep->QueryInterface(IID_CATIVisProperties,
                                                              (void**)&pFilletBrepAsGraphics) ;
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
   pPartAsDescendant->Release();
   pPartAsDescendant = NULL ;
          
   //
   // 7- Colorizes in blue the planar faces of the result associated with  
   //    the main Part body

   //
   // 7-1 Retrieves the main body
   //
   CATIPartRequest_var spPartRequest = spPart ;
   if ( NULL_var == spPartRequest )
   {
       cout <<"Error on CATIPartRequest" << endl;
	   return 1;
   }
   CATBaseUnknown_var spMainPartBody ;
   rc = spPartRequest->GetMainBody("",spMainPartBody);
   if ( FAILED(rc) || ( NULL_var == spMainPartBody) )
   {
       cout <<"Error with GetMainBody" << endl;
	   return 1;
   }

   //
   // 7-2 Retrieves the feature holding the result of the main body
   //     It's the first element of the list returned by GetResults
   //
   CATIBodyRequest_var spMainPartBodyBodyRequest = spMainPartBody ;
   if ( NULL_var == spMainPartBodyBodyRequest )
   {
       cout <<"Error with CATIBodyRequest_var on the main Part body" << endl;
	   return 1;
   }

   CATLISTV(CATBaseUnknown_var) ListResult ;
   rc = spMainPartBodyBodyRequest->GetResults("",ListResult);
   if ( FAILED(rc) || (0 == ListResult.Size() ))
   {
       cout <<"Error with GetResults" << endl;
	   return 1;
   }
  
   //
   // 7-3 Retrieves a CATIGeometricalElement pointer on the feature result
   //
   CATIGeometricalElement_var spFeatureResultGeomElem = ListResult[1] ;
   if ( NULL_var == spFeatureResultGeomElem )
   {
	   cout <<"Error, the feature result does not implement CATIGeometricalElement" << endl;
	   return 1;
   }

   //
   // 7-4 Retrieves the CATBody associating with the feature result
   //
   CATBody_var spPartTopoBody = spFeatureResultGeomElem->GetBodyResult();
   if ( NULL_var == spPartTopoBody )
   {
	   cout <<"Error, the body returned by the GetSolid method is NULL" << endl;
	   return 1;
   }

   //
   // 7-5 Gets all two dimensional topo cells representing the Part body
   //
   CATLISTP(CATCell) cells;
   spPartTopoBody->GetAllCells(cells, 2);


   //
   // 7-6 Processes the two dimensional topo cells 
   //
   for(int currentCell=1; currentCell<=cells.Size(); currentCell++)
   {
      CATCell_var pCell ( cells[currentCell] );
      if ( NULL_var != pCell )
      {
         CATGeometry *pGeometry = pCell->GetGeometry();

         if ( (NULL != pGeometry) && (pGeometry->IsATypeOf(CATPlaneType)) )
         {
            CATIBRepAccess_var spBRepAccess ( CATBRepDecode(pCell, spFeatureResultGeomElem) );
            if( NULL_var!=spBRepAccess )
            {
               //
               // 7-7 Colorizes BRep
               //
               CATIVisProperties *pBRepAccessAsGraphics = 0;
               rc= spBRepAccess->QueryInterface(IID_CATIVisProperties,
                                             (void**)&pBRepAccessAsGraphics) ;
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
   // 8- Saves the document
   //
   // @CSC-Filter UNER
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
   // 9- Closes the document
   //
   rc = CATDocumentServices::Remove(*pDoc);
   if (FAILED(rc))
   {
     cout << "Error in closing document" << endl ;
     return 1;
   }
   pDoc = NULL ;

   //
   // 10- Deletes all documents in session	
   //
   rc = Delete_Session(pSessionName);
   if (FAILED(rc))
   {
     cout << "Error in deleting session" << endl ;
     return 1;
   }  
   
   cout << "The CAAMmrFeatureTopoBRep use case is ended" << endl;

   return 0;
}
