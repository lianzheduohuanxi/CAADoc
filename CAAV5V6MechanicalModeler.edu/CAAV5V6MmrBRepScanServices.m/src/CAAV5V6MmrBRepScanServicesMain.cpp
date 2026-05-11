// COPYRIGHT DASSAULT SYSTEMES  2012
//==========================================================================
//
//	Abstract: This program shows how to Find Equivalent BrepAccess in the copied or reference Feature
//            using the CAAV5V6MmrBRepScanServices class.
//
// Note : CAAV5V6MmrBRepScanServicesMain is the same use case as CAAMmrBRepScanServicesMain. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
////          In V6
//            It is based on an input PLM Product Reference (CAAMmrBRepScanServices,---)
//            
//                - Root Product
//                     . Comp1 -> (CAAMmrBRepScanServices_P1,---)  PLM Rep Ref
//                     . Comp2 -> (CAAMmrBRepScanServices_P2,---)  PLM Rep Ref
//           In V5
//            It is based on the CAAMmrBRepScanServicesRoot Product document. This 
//            document is composed of 2 components:
//                - Root Product
//                     . Comp1 -> CAAMmrBRepScanServices_P1.CATPart
//                     . Comp2 -> CAAMmrBRepScanServices_P2.CATPart
//
//
//            Comp1: CAAMmrBRepScanServices_P1 contains the following data
//       
//                - Part
//                     . PartBody                    
//
//            Comp2: CAAMmrBRepScanServices_P2 contains the following data
//       
//                - Part
//                     . PartBody  
//                         . Sketch.1
//                         . Pad.1
//                         . EdgeFillet.1
//                         . Pocket.1
//
//          For V6:
//           The data is located inside the InputData directory of the CAAV5V6MechanicalModeler.edu fw
//           within the CAAMmrBRepScanServices.3DXML file
//          For V5:
//           The CAAMmrBRepScanServices.CATProduct and its included Part documents are
//           located in the CAAV5V6MechanicalModeler.edu/InputData directory.
//
//           What kind of things it does: 
//            
//            1/ Copy PartBody of Comp2 into Part of Comp1
//            2/ Get EdgeFillet.1 BrepAccess within Comp2 and search them in Comp1
//       
//
//  Steps :
//    1.   Initializes session
//    2.   Opens the input root PLM Product Reference
//    3.   Retrieves objects useful for the copy
//      3.1 Comp1, Comp2, the two Product Instances
//      3.3 Objects from Comp1: The Part
//      3.4 Objects from Comp2: The Part, PartBody, EdgeFillet.1
//    5.   Copy PartBody of Comp2 into Part of Comp1
//    6.   Retrieves BrepAccess with FindDualBRepAccess
//      6.0   Get the result of PartBody of Comp2
//      6.1   Get the BrepAccess From EdgeFillet.1 of Comp2 inside the Result of PartBody
//      6.2   Get the Dual BrepAccess from the initial BrepAccess in Comp1
//      6.3   Get the BiDual BrepAccess from the Dual BrepAccess in Comp2
//      6.4   Check that for each Bidual's face there there is an initial face
//      6.5   Release all that is needed
//    7.   Closes the session
//
//
//==========================================================================
// How to execute :
//
// 
// In V6
// =====
//   mkrun -c "CAAV5V6MmrAxisSystemBRep <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>"                                     
//
//	 where    Repository	: The name of the repository (or provider) 
//			  Server		: The name and port of the server as name:port_number
//			  User			: The user identifier
//            Password		: The user password  
//			  SecurityCtx   : A string representing the security context (Role.Organization.Project)
//							  Choose Role as Designer ( as the use case modifies the PLM Data )
//
// In V5
// =====
//
//   mkrun -c "CAAV5V6MmrBRepScanServices InputPath" 
//
//   with     InputPath   : $WSROOT/CAAV5V6MechanicalModeler.edu/InputData
//
//
// 
//==========================================================================

#include "CATIAV5Level.h"

// ObjectModelerSystem Framework for V6
// ObjectModelerBase Framework for V5
#include "CATIAlias.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// CATMecModLiveUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"

// CATMecModUseItf Framework
#include "CATIMmiUseGeometryAccess.h"
#include "CATLISTV_CATIMmiUseBRepAccess.h"
#include "CATIMmiUseBRepAccess.h"
#include "CATIMmiUseBRep.h"
#include "CATIMmiBRepScanServices.h"
#include "CATMmiUseServicesFactory.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"
#include "CATISpecObject.h"

// Local Framework
#include "CAAV5V6MmrGetGeometry.h"           // To retrieve features
#include "CAAV5V6MmrGetPartFromProduct.h"    // To retrieve the Part from a Product 

// C++ Standard Library
#include <iostream.h>  

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

//CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"
#include "CAAOpenPLMComponent.h"

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// ProductStructureInterfaces
#include "CATIPLMProducts.h"

// CATPLMIntegrationAccess
#include "CATAdpOpenSaveServices.h"

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavInstance.h"

// CATMecModUseItf Framework
#include "CATIMmiUseCreateImport.h"         // To copy mechanical feature
#include "CATMmiUseServicesFactory.h"

#else
//============================================== 
// V5 only
//============================================== 
// ObjectModelerBase Framework
#include "CATSessionServices.h"
#include "CATDocumentServices.h"         // Open, Save 
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATSession.h"

// ProductStructure Framework
#include "CATIProduct.h"

// MechanicalModeler Framework
#include "CATMmrInterPartCopy.h"         // To copy mechanical feature

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

#endif



int main(int iArgc, char *iArgv[])        		    
{

  //---------------------
  // 0- Checks arguments
  //---------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  if ( 9 != iArgc )
	{
		cout << endl;
		cout << "CAAV5V6MmrBRepScanServices <repository> <server> <user> <password> <role> <PLMType> " ;
	    cout<<  "                         <PLM_ExternalID> <V_version> <"<< endl;
		cout << endl;
		return 1;
  }
#else
//============================================== 
// V5 only
//==============================================
  if ( 2 != iArgc ) 
  {
     cout << endl;
     cout << "CAAV5V6MmrBRepScanServices InputPath "<< endl;
     cout << "with : InputPath : $WSROOT/CAAV5V6MechanicalModeler.edu/InputData"<< endl;
     cout << endl;
     return 1;
  }
#endif
  
  cout << "The CAAV5V6MmrBRepScanServices main program begins ...."<< endl << endl;

  //------------------------------------------------------------------
  //1 - Initializes the Session
  //------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

  HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3],iArgv[4], iArgv[5]);
					   
#else
//============================================== 
// V5 only
//==============================================
  char * pSessionName = "CAA_Sample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);
		                         
#endif

  if (FAILED(rc))
	  return 1 ;

  cout <<"   Create Session is OK" << endl;

  //------------------------------------------------------------------
  // 2 -  Opens the input Product  
  //------------------------------------------------------------------
  // 
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

  CATString PLM_Type       = iArgv[6];
  CATUnicodeString PLM_ExternalIDValue = iArgv[7];
  CATUnicodeString V_versionValue = iArgv[8];
  CATIPLMProducts * piPLMProductsOnRoot = NULL;
  CATOmbLifeCycleRootsBag Bag;
 
  rc = CAAOpenPLMComponent(PLM_Type,
			               PLM_ExternalIDValue,
			               V_versionValue,
			               IID_CATIPLMProducts,
			               (void **) &piPLMProductsOnRoot,
				           Bag,
			               TRUE);

  if (FAILED(rc) || (NULL == piPLMProductsOnRoot)) 
    return 1;

  cout << "   " << PLM_ExternalIDValue.ConvertToChar() <<" is opened" << endl;			   
#else
//============================================== 
// V5 only
//==============================================
  CATDocument *pProductDocument = NULL;
  CATString InputData = iArgv[1] ;
  CATString DocumentProductName  = InputData + Slash + "CAAMmrBRepScanServicesRoot.CATProduct";

  rc = CATDocumentServices::OpenDocument(DocumentProductName.ConvertToChar(), pProductDocument);

  if ( FAILED(rc) || ( NULL == pProductDocument) )
     return 1;
  
  cout << "   The "<< DocumentProductName.ConvertToChar() <<" document is opened" << endl ;
#endif

  //------------------------------------------------------------------
  // 3 - Retrieves objects useful for the copies  
  //------------------------------------------------------------------
  // 
  //
  // 3-1 Comp1 & comp2 the two PLM Product Instances
  // 
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  CATUnicodeString comp1Name ="CAAMmrBRepScanServices_P1Inst";
  CATIPLMProducts *piPLMProductOnComp1 = NULL;
  rc = piPLMProductsOnRoot->GetProductByName(comp1Name,piPLMProductOnComp1);
						   
  if (FAILED(rc) || (NULL==piPLMProductOnComp1))
		return 1;
  cout << "   " << comp1Name.ConvertToChar() << " is found" << endl;

  CATIPLMNavInstance_var spNavInstanceOnComp1 = piPLMProductOnComp1;
  piPLMProductOnComp1->Release();
  piPLMProductOnComp1 = NULL;
	
  CATUnicodeString comp2Name ="CAAMmrBRepScanServices_P2Inst" ;
  CATIPLMProducts *piPLMProductOnComp2 = NULL;
  rc = piPLMProductsOnRoot->GetProductByName(comp2Name,piPLMProductOnComp2);
						   
  if (FAILED(rc)|| (NULL==piPLMProductOnComp2) )
		return 1;
  cout << "   " << comp2Name.ConvertToChar() << " is found" << endl;

  CATIPLMNavInstance_var spNavInstanceOnComp2 = piPLMProductOnComp2;
  piPLMProductOnComp2->Release();
  piPLMProductOnComp2 = NULL;
#else
//============================================== 
// V5 only
//==============================================
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
    return 1 ;
  
  cout <<"   The root product has been found" << endl;

  CATListValCATBaseUnknown_var * pListDirectChildren = piProductOnRoot->GetChildren(); 
  if ( (NULL ==pListDirectChildren) || ( pListDirectChildren->Size() !=2) )
    return 1;

  piProductOnRoot->Release();
  piProductOnRoot = NULL ;

  // Comp1 and Comp2
  CATIProduct_var spComp1 = (*pListDirectChildren)[1] ;
  CATIProduct_var spComp2 = (*pListDirectChildren)[2] ;

  if ( (NULL_var == spComp1) || (NULL_var == spComp2) )
    return 1 ;
 
  cout << "   The direct children of the root product has been found" << endl;
  
  delete pListDirectChildren ;
  pListDirectChildren = NULL ;

#endif

  //
  // 3-2 Retrieves objects of CAAMmrBRepScanServices_P2
  //
  cout <<"   Retrieving Objects of CAAMmrBRepScanServices_P2" << endl;

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  // The Part feature
  CATIPartRequest_var spPartRequestOnMechPartOfP2;
  rc = ::CAAV5V6MmrGetPartFromProduct(spNavInstanceOnComp2, spPartRequestOnMechPartOfP2);
  
  if (FAILED(rc) || (NULL_var == spPartRequestOnMechPartOfP2))
     return 1;

  cout << "      The Part feature  of CAAMmrBRepScanServices_P2 has been found" << endl;

  // The PartBody feature
  CATBaseUnknown * pBody = NULL;
  rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnMechPartOfP2, "PartBody", &pBody);
  if (FAILED(rc) || ( NULL == pBody))
     return 1;

  CATBaseUnknown_var spOnBodyOfP2 = pBody;
  pBody->Release();
  pBody = NULL;

  cout << "     The PartBody feature of CAAMmrBRepScanServices_P2 has been found" << endl;

  // The EdgeFillet.1
  CATBaseUnknown * pFil = NULL;
  rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnMechPartOfP2, "EdgeFillet.1", &pFil);
  if (FAILED(rc) || (NULL == pFil))
     return 1;

  CATBaseUnknown_var spOnEdgeFilletOfP2 = pFil;
  pFil->Release();
  pFil = NULL;

  cout << "      The EdgeFillet.1  of P2 has been found" << endl;
#else
//============================================== 
// V5 only
//==============================================
 
  // The Part feature
  CATISpecObject_var spSpecObjectOnMechPartOfP2 ;
  rc = ::CAAV5V6MmrGetPartFromProduct( spComp2, spSpecObjectOnMechPartOfP2 );
  
  if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfP2) )
  {    
     return 1 ;
  }
  cout << "      The Part feature  of CAAMmrBRepScanServices_P2 has been found" << endl;

  // The PartBody feature
  CATBaseUnknown * pBody = NULL ;
  rc = ::CAAV5V6MmrGetGeometry( spSpecObjectOnMechPartOfP2, "PartBody", &pBody );
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
  rc = ::CAAV5V6MmrGetGeometry( spSpecObjectOnMechPartOfP2, "EdgeFillet.1", &pFil );
  if ( FAILED(rc) || ( NULL == pFil) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnEdgeFilletOfP2 = pFil ;
  pFil->Release();
  pFil = NULL ;

  cout << "      The EdgeFillet.1  of P2 has been found" << endl;

#endif

  //
  // 3-3 Retrieves objects of CAAMmrBRepScanServices_P1
  //
  cout <<"   Retrieving Objects of CAAV5V6MmrBRepScanServices_P1" << endl;

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  // The Part feature
  CATIPartRequest_var spPartRequestOnMechPartOfP1 ;
  rc = ::CAAV5V6MmrGetPartFromProduct(spNavInstanceOnComp1, spPartRequestOnMechPartOfP1);

  if (FAILED(rc) || (NULL_var == spPartRequestOnMechPartOfP1))
    return 1;
  
#else
//============================================== 
// V5 only
//==============================================
  // The Part feature
  CATISpecObject_var spSpecObjectOnMechPartOfP1  ;
  rc = ::CAAV5V6MmrGetPartFromProduct( spComp1, spSpecObjectOnMechPartOfP1 );

  if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfP1) )   
    return 1;
#endif  

  cout << "      The Part feature  of CAAV5V6MmrBRepScanServices_P1 has been found" << endl;

  //---------------------------------------------------
  // 5- Copy PartBody of P2 into P1
  //---------------------------------------------------

  cout <<"   Copy PartBody of CAAV5V6MmrBRepScanServices_P2 into CAAV5V6MmrBRepScanServices_P1 " << endl;

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  CATIMmiUseCreateImport* pInterPartCopy = NULL; 
  rc = CATMmiUseServicesFactory::CreateMmiUseCreateImport(pInterPartCopy); 
  if (FAILED(rc) || (NULL == pInterPartCopy)) 
    return 1;
 
  CATBaseUnknown_var SourceToCopy = spOnBodyOfP2;
  CATIMmiMechanicalFeature_var Target = spPartRequestOnMechPartOfP1;

  rc = pInterPartCopy->SetObject(SourceToCopy);
  if (FAILED(rc)) 
    return 1;
  
  rc = pInterPartCopy->SetTarget(Target);
  if (FAILED(rc)) 
    return 1;
                                                  
  // Sets the option of copy 
  CATBoolean CopyWithLink = TRUE ;
  pInterPartCopy->SetLinkMode(CopyWithLink); 

  // Executes the copy
  CATIMmiMechanicalFeature_var spResult;
  rc = pInterPartCopy->Run(spResult);
  if (FAILED(rc) || (NULL_var == spResult))
	 return 1;

  cout <<"      Run is ok" << endl;

   //Last copy
  pInterPartCopy->Release();
  pInterPartCopy = NULL;

#else
//============================================== 
// V5 only
//==============================================
  //
  // 4-1  Copy PartBody of P2 into P1
  //
  cout <<"   Copy PartBody of CAAMmrBRepScanServices_P2 into CAAMmrBRepScanServices_P1 " << endl;

  CATMmrInterPartCopy * ptCATMmrInterPartCopy = NULL ;

  CATISpecObject_var SourceToCopy = spOnBodyOfP2 ;
  CATISpecObject_var Target       = spSpecObjectOnMechPartOfP1 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                  
  // Sets the option of copy  
  CATBoolean CopyWithLink = TRUE ;
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
  CATISpecObject_var spResult ;
  rc = ptCATMmrInterPartCopy ->GetResult(spResult);

  if (FAILED(rc) || (NULL_var == spResult))
	 return 1;

#endif
  
  // Displays the result
  CATIAlias_var alias = spResult;

  if (NULL_var != alias)
  {
	  cout <<"      The result of the copy is" ;
	  cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
  }

  cout <<"   Copy PartBody of CAAV5V6MmrBRepScanServices_P2 into CCAAV5V6MmrBRepScanServices_P1 is done " << endl<< endl;

  //---------------------------------------------------
  // 6- Retrieves BrepAccess with FindDualBRepAccess 
  //---------------------------------------------------
  //
  // 6-0  Retrieves the Result of the PartBody
  //
  CATIBodyRequest_var spBodyRequestOnBodyOfP2 = spOnBodyOfP2;
  if (NULL_var == spBodyRequestOnBodyOfP2)
	  return 1;
 
  CATLISTV(CATBaseUnknown_var) ListResult ;
  rc = spBodyRequestOnBodyOfP2->GetResults("",ListResult);
  if (FAILED(rc) || (0==ListResult.Size()))
     return 1;

  // The result for a PartBody is always the first element of the list
  // other elements are sketches
  // see article : Specification/Result Mechanism Applied to Mechanical Features
  //
  CATBaseUnknown_var spResultPartBody2 = ListResult[1];
  if (NULL_var == spResultPartBody2)
	  return 1;

  cout <<"   The result of PartBody2 has been found " << endl;

  //
  // 6-1  Get the BrepAccess From EdgeFillet.1 of Comp2
  //
  CATIMmiUseGeometryAccess_var spGeomAccessOnEdgeFillet = spOnEdgeFilletOfP2;
  if (spGeomAccessOnEdgeFillet == NULL_var)
    return 1;
 
  cout<<"   Geometrical Feature associated to this Feature Exist"<<endl;

  // Retrieve the BRep (which are Faces for a Edge Fillet) 
  CATListValCATIMmiUseBRepAccess_var LBrepAccess;
  rc = spGeomAccessOnEdgeFillet->GetBReps(LBrepAccess);  
  if (FAILED(rc))
    return 1;

  int n_face = LBrepAccess.Size();
  cout<<"   There is (are)" <<n_face <<" face(s) associated with the geometry"<<endl;
 
  //
  // Transform each CATBaseUnknown in CATIBRepAccess
  //
  CATIMmiMechanicalFeature_var spResultPartBody2Feat = spResultPartBody2;
  if (NULL_var == spResultPartBody2Feat)
	  return 1;


  CATListValCATIMmiUseBRepAccess_var ListBreps;
  int i_face=1;
  for (i_face=1; i_face<=n_face; i_face++)
  {
    CATIMmiUseBRepAccess_var Unk = LBrepAccess[i_face];
	if (NULL_var != Unk)
	{
      CATIMmiUseBRep_var spBrep=Unk;
      if (NULL_var == spBrep) 
        continue;
		   
	  // we are looking for the face inside the Result of PartBody
      CATListValCATIMmiUseBRepAccess_var ListTemp;
      rc = spBrep->GetBreps(ListTemp, CATMmrDefaultLimitationType, spResultPartBody2Feat); 
      if (ListTemp.Size())
         ListBreps.Append(ListTemp);
	}
  }
  
  n_face = ListBreps.Size();
  cout<<"   There is(are) "<<n_face<<" face(s) on the EdgeFillet.1 of CAAV5V6MmrBRepScanServices_P2"<<endl;

  //
  // 6.2   Get the Dual BrepAccess from the initial BrepAccess in Comp1
  //
  CATListValCATIMmiUseBRepAccess_var ListBRepsRef;
  CATListValCATIMmiUseBRepAccess_var ListBRepsDual;

  CATIMmiBRepScanServices* piScanServices = NULL;  
  rc = CATMmiUseServicesFactory::CreateMmiBRepScanServices(piScanServices);

  if (FAILED(rc) || piScanServices == NULL)
    return 1;

  for (i_face = 1; i_face <= n_face; i_face++)
  {
    CATIMmiMechanicalFeature_var spFeatRef=NULL_var;//unused parameter
    //spResult = The edgefillet copied in comp1
    CATIMmiUseBRepAccess_var spBRepIn = ListBreps[i_face];  
	CATIMmiUseBRepAccess_var spBRepOut = NULL_var;

    rc = piScanServices->FindDualBRepAccess(spFeatRef, spResult, spBRepIn, spBRepOut);
    if (FAILED(rc) || NULL_var == spBRepOut) 
      continue;

    ListBRepsRef.Append(spBRepIn);
    ListBRepsDual.Append(spBRepOut);
  }

  n_face = ListBRepsRef.Size();
  if (0 == n_face)
    return 1;
 
  cout<<"   There is(are) "<<n_face<<" face(s) of CAAV5V6MmrBRepScanServices_P2 Recover in CAAV5V6MmrBRepScanServices_P1"<<endl;

  //
  // 6.3   Get the BiDual BrepAccess from the Dual BrepAccess in Comp2
  //
  CATListValCATIMmiUseBRepAccess_var ListBRepsBiDual; // in comp2
  n_face = ListBRepsDual.Size();
  for (i_face = 1; i_face <= n_face; i_face++)
  {
	CATIMmiMechanicalFeature_var spFeatRef = spOnBodyOfP2;
    //spResult = The edgefillet copied in comp1
	CATIMmiUseBRepAccess_var spBRepIn = NULL_var;  
	CATIMmiUseBRepAccess_var spBRepOut = ListBRepsDual[i_face];;
    
    rc = piScanServices->FindDualBRepAccess(spFeatRef, spResult, spBRepIn , spBRepOut); 
    if (FAILED(rc) || NULL_var == spBRepIn ) 
      continue;
    ListBRepsBiDual.Append(spBRepIn);
  }
  n_face = ListBRepsBiDual.Size();
  if (0 == n_face)
    return 1;  
  cout<<"   There is(are) "<<n_face<<" face(s)  of CAAV5V6MmrBRepScanServices_P1 Recover in CAAV5V6MmrBRepScanServices_P2"<<endl;

  //
  // 6.4   Check if each Bidual's face exists in initial 
  //       attention the list of ListBrepsBiDual can be shorter that ListBrepsRef
  //       but all element of ListBrepsBiDual must exist in ListBrepsRef
  //
  for (i_face = 1; i_face <= n_face; i_face++)
  {
    CATIMmiUseBRep_var spBRepIn = ListBRepsBiDual[i_face];
    if (NULL_var == spBRepIn) 
      continue;
	CATBoolean Found = FALSE;
	int j=1;
	while ((Found==FALSE) && (j<=ListBRepsRef.Size()))
	{
      CATIMmiUseBRep_var spBRepOut = ListBRepsRef[j];
      CATBoolean IsSame=FALSE;
      rc = spBRepIn->IsSameBRep(spBRepOut, IsSame);
	    if (IsSame)
      Found = TRUE;
	  j++;
	}
    if (Found == FALSE)
	{
	  cout<<"Error, One of the Face searched is not Recovered"<<endl;
      return 1;
	}
  }
  cout <<"   All the elements of CAAV5V6MmrBRepScanServices_P1 have been found inside CAAV5V6MmrBRepScanServices_P2" << endl << endl;

  //
  // 6.5   Release all that is needed
  //
  piScanServices->Release();
  piScanServices = NULL;

  //-------------------
  // 7- Deletes session
  //-------------------
  
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  rc = Bag.RemoveAll();
	if (FAILED(rc))
		return 1;

  rc = ::CAAAdpCloseSession();
  if (FAILED(rc)) 
  {
		return 1;
  }  
  cout<<"   The session is closed"<< endl << endl;
#else
//============================================== 
// V5 only
//==============================================
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
#endif

  cout <<"The CAAV5V6MmrBRepScanServices main program is ended."<< endl << endl;

  return 0;
}
