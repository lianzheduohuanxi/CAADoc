// COPYRIGHT DASSAULT SYSTEMES  2000 
//==========================================================================
//
//	Abstract: This program shows how to Find Equivalent BrepAccess in the copied or reference Feature
//
//            using the CAAMmrBRepScanServices class.
//
//            It is based on the CAAMmrBRepScanServicesRoot Product document. This 
//            document is composed of 2 components:
//            
//            
//                - Root Product
//                     . Comp1 -> CAAMmrBRepScanServices_P1.CATPart
//                     . Comp2 -> CAAMmrBRepScanServices_P2.CATPart
//
//            Comp1: The CAAMmrBRepScanServices_P1 Part document contains the following data
//       
//                - Part
//                     . PartBody  

//
//            Comp2: The CAAMmrBRepScanServices_P2 Part document contains the following data
//       
//                - Part
//                     . PartBody  
//                         . Sketch.1
//                         . Pad.1
//                         . EdgeFillet.1
//                         . Pocket.1
//        
//           The CAAMmrBRepScanServices.CATProduct and its included Part documents are
//           located in the CAAMechanicalModeler.edu/InputData directory.
//
//           What kind of thinks it does: 
//            
//            1/ Copy PartBody of Comp2 into Part of Comp1
//  
//            2/ Get EdgeFillet.1 BrepAccess within Comp2 and search them in Comp1
//       
//
//  Steps :
//    1.   Opens the session
//    2.   Opens the CAAMmrBRepScanServices Product document
//    3.   Retrieves objects useful for the copy
//      3.1 Root product
//      3.2 Comp1, Comp2, the two components of the root product
//      3.3 Objects from Comp1: The Part,  
//      3.4 Objects from Comp2: The Part, PartBody, EdgeFillet.1
//    4.   Copies between two Part Documents
//      4.1   Copy PartBody of Comp2 into Part of Comp1
//    5.   Retrieves BrepAccess with FindDualBRepAccess
//      5.1   Get the BrepAccess From EdgeFillet.1 of Comp2
//      5.2   Get the Dual BrepAccess from the initial BrepAccess in Comp1
//      5.3   Get the BiDual BrepAccess from the Dual BrepAccess in Comp2
//      5.4   Check if the initial BrepAccess are the same than the Bidual's
//      5.5   Release all that is needed
//    6.   Closes all the documents
//    7.   Deletes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAMmrPartCopy InputPath 
//
//   with     InputPath   : $WSROOT/CAAMechanicalModeler.edu/InputData
//
//          
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save 
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATIAlias.h"
#include "CATSession.h"

// Product Structure
#include "CATIProduct.h"

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // To get the MechanicalPart,and element of the OpenBody1
#include "CATLISTV_CATISpecObject.h"
#include "CATLISTV_CATBaseUnknown.h"

// MechanicalModeler
#include "CATMmrInterPartCopy.h"         // To copy mechanical feature
#include "CATMmrBRepScanServices.h"      // To Retrive Brep Element
#include "CATIMfGeometryAccess.h"        // To Retrive Brep Element

// MecModInterfaces Framework
#include "CATIBRepAccess.h"
#include "CATIBodyRequest.h"

// System Framework
#include "CATString.h"
#include "CATBoolean.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// Local Framework
#include "CAAMmrGetGeometry.h"           // To retrieve features
#include "CAAMmrGetPartFromProduct.h"    // To retrieve the Part from a Product 

// C++ Standard Library
#include <iostream.h>  

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

int main(int iArgc, char *iArgv[])        		    
{

  //---------------------
  // 0- Checks arguments
  //---------------------
  if ( 2 != iArgc ) 
  {
     cout << endl;
     cout << "CAAMmrBRepScanServices InputPath "<< endl;
     cout << "with : InputPath : $WSROOT/CAAMechanicalModeler.edu/InputData"<< endl;
     cout << endl;
     return 1;
  }
  cout << "The CAAMmrBRepScanServices main program begins ...."<< endl << endl;
  
  // The type of copy option 
  CATBoolean CopyWithLink = TRUE ;

  // The copy between documents: with or without PS context
  CATBoolean PSContext = FALSE ;

  //------------------------------------------------------------------
  //1 - Creates Session
  //------------------------------------------------------------------

  char * pSessionName = "CAA_Sample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);
		                          
  if (FAILED(rc) )
  {
      return 1;
  }
  cout <<"   A session is created" << endl;

  //-----------------------------------------
  //2- Opens the CAAMmrPartCopy document 
  //-----------------------------------------

  CATDocument *pProductDocument = NULL;
  CATString InputData = iArgv[1] ;
  CATString DocumentProductName  = InputData + Slash + "CAAMmrBRepScanServicesRoot.CATProduct";

  rc = CATDocumentServices::OpenDocument(DocumentProductName.ConvertToChar(), pProductDocument);
  if ( FAILED(rc) || ( NULL == pProductDocument) )
  {
     return 1;
  }
  
  cout << "   The "<< DocumentProductName.ConvertToChar() <<" document is opened" << endl ;
  
  //------------------------------------------------------
  // 3- Retrieves objects useful for the copies
  //------------------------------------------------------
  //
  // 3-1 The root product
  // 
  CATIProduct * piProductOnRoot = NULL;

  CATIDocRoots * piDocRootsOnDoc = NULL;
  rc = pProductDocument->QueryInterface(IID_CATIDocRoots,(void**) &piDocRootsOnDoc);
                          
  if ( SUCCEEDED(rc) ) 
  {
     // Gets the root product which is the first element of root elements
     CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc->GiveDocRoots();
   
     if ( NULL == pRootProducts )
     {
        return 1 ;
     }

     if (pRootProducts->Size() > 0 )
     {  
        CATBaseUnknown_var spRootProduct = (*pRootProducts)[1];
     
        // Gets CATIProduct handle on the root product.
        if ( NULL_var != spRootProduct )
        {
           rc = spRootProduct->QueryInterface(IID_CATIProduct,(void**) &piProductOnRoot);     
        }

        delete pRootProducts;
        pRootProducts = NULL;
     }
     piDocRootsOnDoc->Release();
     piDocRootsOnDoc = NULL ;
  }

  if ( NULL == piProductOnRoot )
  {
     return 1 ;
  }
  
  cout <<"   The root product has been found" << endl;
  
  //
  // 3-2 The components of the root product
  // 
  CATListValCATBaseUnknown_var * pListDirectChildren = piProductOnRoot->GetChildren(); 
  if ( (NULL ==pListDirectChildren) || ( pListDirectChildren->Size() !=2) )
  {
        return 1 ;
  }

  piProductOnRoot->Release();
  piProductOnRoot = NULL ;

  // Comp1 and Comp2
  CATIProduct_var spComp1 = (*pListDirectChildren)[1] ;
  CATIProduct_var spComp2 = (*pListDirectChildren)[2] ;

  if ( (NULL_var == spComp1) || (NULL_var == spComp2) )
  {
        return 1 ;
  }
  cout << "   The direct children of the root product has been found" << endl;
  
  delete pListDirectChildren ;
  pListDirectChildren = NULL ;

  //
  // 3-3 Retrieves objects of CAAMmrBRepScanServices_P2
  //
  cout <<"   Retrieving Objects of CAAMmrBRepScanServices_P2" << endl;

  // The Part feature
  CATISpecObject_var spSpecObjectOnMechPartOfP2 ;
  rc = ::CAAMmrGetPartFromProduct( spComp2, spSpecObjectOnMechPartOfP2 );
  
  if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfP2) )
  {    
     return 1 ;
  }
  cout << "      The Part feature  of CAAMmrBRepScanServices_P2 has been found" << endl;

  // The PartBody feature
  CATBaseUnknown * pBody = NULL ;
  rc = ::CAAMmrGetGeometry( spSpecObjectOnMechPartOfP2, "PartBody", &pBody );
  if ( FAILED(rc) || ( NULL == pBody) )
  {    
     return 1 ;
  }

  CATBaseUnknown_var spOnBodyOfP2 = pBody ;
  pBody->Release();
  pBody = NULL ;

  cout << "      The PartBody feature of CAAMmrBRepScanServices_P2 has been found" << endl;

  // The EdgeFillet.1
  CATBaseUnknown * pFil = NULL ;
  rc = ::CAAMmrGetGeometry( spSpecObjectOnMechPartOfP2, "EdgeFillet.1", &pFil );
  if ( FAILED(rc) || ( NULL == pFil) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnEdgeFilletOfP2 = pFil ;
  pFil->Release();
  pFil = NULL ;

  cout << "      The EdgeFillet.1  of P2 has been found" << endl;

  //
  // 3-3 Retrieves objects of CAAMmrBRepScanServices_P1
  //
  cout <<"   Retrieving Objects of CAAMmrBRepScanServices_P1" << endl;

  // The Part feature
  CATISpecObject_var spSpecObjectOnMechPartOfP1  ;
  rc = ::CAAMmrGetPartFromProduct( spComp1, spSpecObjectOnMechPartOfP1 );

  if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfP1) )
  {    
    return 1 ;
  }
  cout << "      The Part feature  of CAAMmrBRepScanServices_P1 has been found" << endl;

  //---------------------------------------------------
  // 4- Copies between two Part documents  
  //---------------------------------------------------

  //
  // 4-1  Copy PartBody of P2 into P1
  //
  cout <<"   Copy PartBody of CAAMmrBRepScanServices_P2 into CAAMmrBRepScanServices_P1 " << endl;

  CATMmrInterPartCopy * ptCATMmrInterPartCopy = NULL ;

  CATISpecObject_var SourceToCopy = spOnBodyOfP2 ;
  CATISpecObject_var Target       = spSpecObjectOnMechPartOfP1 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                  
  // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 
  
  // Executes the copy
  CATUnicodeString ErrorMsg ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  CATISpecObject_var Result ;
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }
  }else return 1 ;


  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //---------------------------------------------------
  // 5- Retrieves BrepAccess with FindDualBRepAccess 
  //---------------------------------------------------

   //
  // 5-0  Retrieves the Result of the PartBody
  //
  CATIBodyRequest_var spBodyRequestOnBodyOfP2 = spOnBodyOfP2;
  if ( NULL_var == spBodyRequestOnBodyOfP2 )
  {
	  return 1 ;
  }
  CATLISTV(CATBaseUnknown_var) ListResult ;
  rc = spBodyRequestOnBodyOfP2->GetResults("",ListResult);
  if ( FAILED(rc) || ( 0== ListResult.Size() ) )
  {
     return 1 ;
  }
  // The result for a PartBody is always the first element of the list
  // other elements are sketches
  // see article : Specification/Result Mechanism Applied to Mechanical Features
  //
  CATBaseUnknown_var spResultPartBody2 = ListResult[1];
  if ( NULL_var == spResultPartBody2 )
  {
	  return 1 ;
  }
  CATISpecObject_var spSpecObjResultPartBody2 = spResultPartBody2 ;
  if ( NULL_var == spSpecObjResultPartBody2 )
  {
	  return 1 ;
  }

  cout <<"   The result of PartBody2 has been found " << endl;

  //
  // 5-1  Get the BrepAccess From EdgeFillet.1 of Comp2
  //
  CATIMfGeometryAccess *pGeomAccessOnEdgeFillet = NULL ;
  rc = spOnEdgeFilletOfP2-> QueryInterface(IID_CATIMfGeometryAccess,(void**)&pGeomAccessOnEdgeFillet);
  if ( FAILED(rc) || ( NULL == pGeomAccessOnEdgeFillet) )
  {
     return 1 ;
  }
  cout<<"   Geometrical Feature associated to this Feature Exist"<<endl;

  // Retrieve the BRep (which are Faces for a Edge Fillet) 
  CATLISTV(CATBaseUnknown_var) LBrepAccessOnCATBaseUnknown;
  int n_face = pGeomAccessOnEdgeFillet->GetBReps(LBrepAccessOnCATBaseUnknown);

  pGeomAccessOnEdgeFillet->Release();
  pGeomAccessOnEdgeFillet = NULL;
  if ( 0 == n_face )
  {
       return 1;
  }
  cout<<"   There is (are)" <<n_face <<" face(s) associated with the geometry"<<endl;
  //
  // Transform each CATBaseUnknown in CATIBRepAccess
  //
  CATLISTP(CATIBRepAccess) ListBreps;
  int i_face = 1;
  for( i_face = 1; i_face <= n_face; i_face++)
  {
		CATBaseUnknown * Unk = LBrepAccessOnCATBaseUnknown[i_face];
		if ( NULL != Unk )
		{
		   CATIBRepAccess * Brep = NULL;
           rc = Unk -> QueryInterface(IID_CATIBRepAccess,(void**)&Brep );
           if ( FAILED(rc) || ( NULL == Brep) ) continue;
		   
		   // we are looking for the face inside the Result of PartBody
           CATLISTV(CATBaseUnknown_var) ListTemp;
		   ListTemp = Brep->GetBReps(spSpecObjResultPartBody2);
           for ( int k=1 ; k <= ListTemp.Size(); k++)
		   {
			   CATBaseUnknown_var TempVar = ListTemp[k]  ;
			   if ( NULL_var != TempVar )
			   {
		          CATIBRepAccess * BrepTemp = NULL;
                  TempVar->QueryInterface(IID_CATIBRepAccess,(void**)&BrepTemp );
                  ListBreps.Append(BrepTemp);
			   }
		   }
		   ListTemp.RemoveAll();
           Brep->Release(); Brep = NULL ;
		}
  }
  LBrepAccessOnCATBaseUnknown.RemoveAll();
  n_face = ListBreps.Size() ;
  
  cout<<"   There is(are) "<<n_face<<" face(s) on the EdgeFillet.1 of CAAMmrBRepScanServices_P2"<<endl;

  //
  // 5.2   Get the Dual BrepAccess from the initial BrepAccess in Comp1
  //
  
  CATLISTP(CATIBRepAccess) ListBrepsRef;  // in comp2
  CATLISTP(CATIBRepAccess) ListBrepsDual; // in comp1
  
  for( i_face = 1; i_face <= n_face; i_face++)
  {
	  CATISpecObject *   pFeatRef = NULL ; // unused parameter
	  
	  CATISpecObject * pFeatImp = Result;  // The edgefillet copied in comp1
      CATIBRepAccess * BrepIn   = ListBreps[i_face];  
	  CATIBRepAccess * BrepOut  = NULL;

      rc = CATMmrBRepScanServices::FindDualBRepAccess( pFeatRef, pFeatImp, &BrepIn , &BrepOut ); 
      if ( FAILED(rc) || NULL == BrepOut ) continue;

      ListBrepsRef.Append(BrepIn);BrepIn->AddRef();
      ListBrepsDual.Append(BrepOut);
  }
  n_face = ListBrepsRef.Size();
  if ( 0 == n_face )
  {
      return 1;
  }
 
  cout<<"   There is(are) "<<n_face<<" face(s) of CAAMmrBRepScanServices_P2 Recover in CAAMmrBRepScanServices_P1"<<endl;

  //
  // 5.3   Get the BiDual BrepAccess from the Dual BrepAccess in Comp2
  //
  CATLISTP(CATIBRepAccess) ListBrepsBiDual; // in comp2
  n_face = ListBrepsDual.Size();
  for( i_face = 1; i_face <= n_face; i_face++)
  {
	  CATISpecObject_var FeatRef = spOnBodyOfP2;
	  CATISpecObject *   pFeatRef = (CATISpecObject*) FeatRef ;
	  CATISpecObject *   pFeatImp = Result;        

	  CATIBRepAccess *   BrepIn   = NULL;
	  CATIBRepAccess *   BrepOut  = ListBrepsDual[i_face];
      
      rc = CATMmrBRepScanServices::FindDualBRepAccess( pFeatRef, pFeatImp, &BrepIn , &BrepOut ); 
      if ( FAILED(rc) || NULL == BrepIn ) continue;
      ListBrepsBiDual.Append(BrepIn);
  }
  n_face = ListBrepsBiDual.Size();
  if ( 0 == n_face )
  {
    return 1;
  }
  
  cout<<"   There is(are) "<<n_face<<" face(s)  of CAAMmrBRepScanServices_P1 Recover in CAAMmrBRepScanServices_P2"<<endl;

  //
  // 5.4   Check if each Bidual's face exists in initial 
  //       attention the list of ListBrepsBiDual can be shorter that ListBrepsRef
  //       but all element of ListBrepsBiDual must exist in ListBrepsRef
  //
  for( i_face = 1; i_face <= n_face; i_face++)
  {
    CATIBRepAccess * BrepIn = ListBrepsBiDual[i_face];
    if (NULL == BrepIn) continue;
	CATBoolean Found = FALSE ;
	int j = 1 ;
	while ( (Found==FALSE) && ( j<=ListBrepsRef.Size() ) )
	{
        CATIBRepAccess * BrepOut = ListBrepsRef[j] ;
		if ( BrepIn->IsSame(BrepOut) )
        {
            Found = TRUE ;
		}
		j++ ;
	}
    if ( Found == FALSE )
	{
	   cout<<"Error, One of the Face searched is not Recovered"<<endl;
       return 1;
	}
  }
  cout <<"   All the elements of CAAMmrBRepScanServices_P1 have been found inside CAAMmrBRepScanServices_P2" << endl << endl;

  //
  // 5.5   Release all that is needed
  //
  n_face = ListBreps.Size();
  for( i_face = 1; i_face <= n_face; i_face++)
  {
		CATIBRepAccess * Brep = ListBreps[i_face];
    if (NULL == Brep) continue;
    Brep ->Release();
  }
  ListBreps.RemoveAll();

  n_face = ListBrepsRef.Size();
  for( i_face = 1; i_face <= n_face; i_face++)
  {
		CATIBRepAccess * Brep = ListBrepsRef[i_face];
    if (NULL == Brep) continue;
    Brep ->Release();
  }
  ListBrepsRef.RemoveAll();
  n_face = ListBrepsDual.Size();
  for( i_face = 1; i_face <= n_face; i_face++)
  {
		CATIBRepAccess * Brep = ListBrepsDual[i_face];
    if (NULL == Brep) continue;
    Brep ->Release();
  }
  ListBrepsDual.RemoveAll();

  n_face = ListBrepsBiDual.Size();
  for( i_face = 1; i_face <= n_face; i_face++)
  {
		CATIBRepAccess * Brep = ListBrepsBiDual[i_face];
    if (NULL == Brep) continue;
    Brep ->Release();
  }
  ListBrepsBiDual.RemoveAll();

  cout <<" FindDualBRepAccess OK " << endl;

  //---------------------------------------------------
  // 6- Closes document
  //---------------------------------------------------
 
  // Removes the product, it removes the included Part documents too
  rc = CATDocumentServices::Remove (*pProductDocument);
  if (FAILED(rc)) 
  {
     return 1;
  }
  cout << endl;
  cout << "   The "<< DocumentProductName.ConvertToChar() ;
  cout <<" document and its included files are closed" << endl ;
      
  pProductDocument = NULL ;

  //-------------------
  // 7- Deletes session
  //-------------------

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc)) 
  {
     return 1;
  }  
  cout<<"   The session is deleted"<< endl << endl;

  cout <<"The CAAMmrBRepScanServices main program is ended."<< endl << endl;

  return 0;
}
