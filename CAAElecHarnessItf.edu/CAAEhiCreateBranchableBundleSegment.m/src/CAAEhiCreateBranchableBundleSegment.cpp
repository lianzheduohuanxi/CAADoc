
// COPYRIGHT DASSAULT SYSTEMES 2002

//===============================================================================
//  Abstract of Use Case "CAAEhiCreateBranchableBundleSegment":
//  -----------------------------------------------------------
//
//  This Use Case illustrates how to create geometrical bundle and branchable 
//  bundle segment and split and merge a bundle segment . 
//
//===============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      1.1 Checking inputs ( path )
//      1.2 Creating the Session 
//      1.3 Creating new CATProduct Document.
//      1.4 Retrieving the Root Product of the CATProduct Document.
//  2. Initializing Electrical Environment. 
//  3. Creating Geometrical Bundle.  
//  4. Creating a multi branchable bundle segment with three bundle segments
//      4.1 Creating the multi branchable bundle
//      4.2 Creating three bundle segments 
//      4.3 Retrieving the branchables under the multi branchable
//      4.4 Setting attributes on each bundle segment
//      4.5 define bundle segment route 
//      4.6 Computing bundle segments 
//  5. Splitting the first bundle segment on the point created before to obtain two bundle 
//     segments.
//      5.1 Creating Point on first Bundle Segment.
//      5.2 Modifing the attributes of the new bundle segment  
//      5.3 Computing the new bundle segment created.
//  6. Merging the new bundle segment with first bundle segment.
//  7. Epilogue.
//      7.1 releasing pointers
//      7.2 saving documents
//      7.3 removing documents from session
//      7.4 closing session
//
//  Return Errors:
//  -------------
//  1 - ERROR : invalid inputs 
//  2 - ERROR in creating the session
//  3 - ERROR in creating new CATProduct document
//  4 - ERROR in retrieving root product of CATProduct document.
//  5 - ERROR in initializing electrical environment. 
//  6 - ERROR in creating geometrical bundle.
//  7 - ERROR in creating multi branchable
//  8 - ERROR in assigning an instance name to the multi branchable
//  9 - ERROR in creating the second branchable
// 10 - ERROR in creating the third branchable
// 11 - ERROR in retrieving the bundle segments of the multi branchable
// 12 - ERROR in assigning part number on the bundle segments 
// 13 - ERROR in retrieving the branchables of the multi branchable
// 14 - ERROR in assigning part number on the branchables
// 15 - ERROR in setting bundle segment attributes on first bundle segment
// 16 - ERROR in setting bundle segment attributes on second bundle segment
// 17 - ERROR in setting bundle segment attributes on third bundle segment
// 18 - ERROR in defining route of first bundle segment
// 19 - ERROR in defining route of second bundle segment
// 20 - ERROR in defining route of third bundle segment
// 21 - ERROR in computing the first bundle segment
// 22 - ERROR in computing the second bundle segment
// 23 - ERROR in computing the third bundle segment
// 24 - ERROR in creating the point for split of the first bundle segment
// 25 - ERROR in splitting the first bundle segment
// 26 - ERROR in setting bundle segment attributes on the new bundle segment 
// 27 - ERROR in computing the new bundle segment
// 28 - ERROR in merging the first bundle segment with the new bundle segment
// 29 - ERROR in computing the first bundle segment after the merge
// 30 - ERROR in saving the multi branchable document 
// 31 - ERROR in saving the geometrical bundle document 
// 32 - ERROR in removing documents from session 
// 33 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiCreateBranchableBundleSegment PathDir GbnName Bns1Name Bns2Name Bns3Name MultiBnsName" where :
//      . "PathDir" is the entire pathname where to save the new created documents.
//        "GbnName" is the part number of the created geometrical bundle.     
//        "Bns1Name" is the part number of the first bundle segment created. 
//        "Bns2Name" is the part number of the second bundle segment created. 
//        "Bns3Name" is the part number of the third bundle segment created. 
//        "MultiBnsName" is the part number of the multi branchable created
//
//         Geometrical Bundle is saved as GbnName.CATProduct document.      
//         First Bundle Segment is saved as BundleSegment Bns1Name.CATPart document.      
//         Second Bundle Segment is saved as BundleSegment Bns2Name.CATPart document.      
//         Third Bundle Segment is saved as BundleSegment Bns3Name.CATPart document. 
//         Multi branchable is saved as MultiBnsName.CATPart document.      
//
//=====================================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATGSMOrientation.h"
#include "CATIGSMPointOnCurve.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// System interfaces
#include "CATLib.h"                      // managing files
// ObjectModelerBase interfaces
#include "CATSessionServices.h"          // managing session
#include "CATDocumentServices.h"         // managing documents in session
#include "CATDocument.h"                 // manipulating documents
#include "CATIDocRoots.h"                // browsing root objects in documents
#include "CATILinkableObject.h"          // retrieving document for object 
#include "CATISpecObject.h"              // managing feature ( update )
#include "CATIDescendants.h"             // managing part tree
#include "CATIContainer.h"               // managing feature container 


// ProductStructure interfaces 
#include "CATIProduct.h"                 // managing products  

// Litteral Features interfaces 
#include "CATICkeParm.h"                 // managing litteral features  
#include "CATICkeParmFactory.h"          // creating litteral features  

// Mechanical Modeler interfaces 
#include "CATIPartRequest.h"             // retrieving GSM tool  
#include "CATIPrtContainer.h"            // managing part container 

// GSM interfaces 
#include "CATIGSMSpline.h"               // managing GSM curves  
#include "CATIGSMFactory.h"              // creating GSM objects : point  
#include "CATIGSMPointCoord.h"           // managing points

// Electrical Harness interfaces
#include "CATIEhiFactory.h"              // creating geometrical bundles
#include "CATIEhiGeoBundle.h"            // managing geometrical bundles
#include "CATIEhiBundleSegment.h"        // managing bundle segments
#include "CATIEhiMultiBranchable.h"      // managing multi branchable bundle segments
#include "CATIEhiBranchable.h"           // managing branchable bundle segments

// Electrical interfaces
#include "CATIEleDocServices.h"          // initializing electrical environment 
#include "CATIElecAttrAccess.h"          // electrical attributes management 

//=========================================================================================================
//
// Method : define bundle segment route 
// ------------------------------------
//
//      piBundleSegment : bundle segment instance 
//      point_coord : array of point coordinates
//      nb_point : number of points  ( array dimension is 3*nb_point ) 
//
HRESULT SetBundleSegmentRoute ( CATIEhiBundleSegment * piBundleSegment, double * point_coord,
                                           int & nb_point )
{
 HRESULT rc = E_FAIL;
 //
 if (!piBundleSegment) return rc; // pointer not valuated : exit E_FAIL 
 if ( nb_point < 2 ) return rc;   // number of points < 2 : exit E_FAIL;

 // -- retrieving electrical curve
 CATIGSMSpline * pElecCurve = NULL;
 rc = piBundleSegment->GetElecCurve(& pElecCurve );
 if ( FAILED (rc) || !pElecCurve ) return rc; // electrical curve not found : exit E_FAIL

 // -- retrieving container
 CATIContainer_var spCont;   // the container 
 CATISpecObject_var spObj = pElecCurve;
 if ( NULL_var != spObj ) spCont = spObj->GetFeatContainer();

 // -- retrieving factories : 
 //             -   litteral feature factory
 //             -   GSM factory
 CATICkeParmFactory_var spCKEfacto = spCont;  // litteral feature factory
 CATIGSMFactory_var spGSMfacto = spCont;      // GSM factory
 if ( NULL_var == spCKEfacto || NULL_var == spGSMfacto )
 {
  pElecCurve->Release(); // release pointe
  pElecCurve=NULL;       // reset pointer value to NULL
  return rc;             // cannot retrieve factories : exit E_FAIL
 }

 // -- retrieving GSM Body :
 // 
 CATBaseUnknown_var spGSMBody = NULL_var; // the GMS body 

 CATIPartRequest * pPartAsRequest = NULL;
 CATIPrtContainer_var spPartCont = spCont;
 if ( NULL_var == spPartCont ) return rc;
 CATISpecObject_var spPart = spPartCont->GetPart();
 if ( NULL_var == spPart ) return rc;
 // 
 if( SUCCEEDED(spPart->QueryInterface(IID_CATIPartRequest, (void**)&pPartAsRequest)) )
 {
   
   const CATUnicodeString stdContext(" "); // Sets the context for  bodies lookup 
   
   // retrieve GSM open body
   CATLISTV(CATBaseUnknown_var) surfBodies;  // List of GSM bodies in pPartAsRequest
   pPartAsRequest->GetSurfBodies(stdContext, surfBodies);
   
   // select first body found to create points
   spGSMBody = surfBodies[1];

   pPartAsRequest->Release();
   pPartAsRequest=NULL;
 }
 if ( NULL_var == spGSMBody ) return rc;  // GSM body not found
 CATIDescendants_var spFather = spGSMBody; 
 if ( NULL_var == spFather ) return rc; 

 // -- create and add points to curve
 // 
 CATICkeParm_var X;
 CATICkeParm_var Y; 
 CATICkeParm_var Z;  
 CATIGSMPointCoord_var spPoint;
 //
 for ( int i=1; i<=nb_point; i++ )
 {
   X = spCKEfacto->CreateLength  ( "X", point_coord[  3*(i-1)] );
   Y = spCKEfacto->CreateLength  ( "Y", point_coord[1+3*(i-1)] );
   Z = spCKEfacto->CreateLength  ( "Z", point_coord[2+3*(i-1)] );
   spPoint = spGSMfacto->CreatePoint(X,Y,Z);   
   if ( NULL_var != spPoint ) // --- point created 
   {   
    spFather->Append(spPoint); // add point under GSM body in tree 
    CATISpecObject_var (spPoint)->Update(); // compute point geometry  
    // --- add constraint point to electrical curve
    pElecCurve->Add(spPoint);
   }
   else
   {
   // --- point creation failed
     pElecCurve->Release(); // release pointer
     pElecCurve=NULL;       // reset pointer value to NULL
     return rc;             // GSM point creation failed : exit E_FAIL   
   }
 }
 //
 // -- update curve geometry
 spObj->Update();
 //
 pElecCurve->Release(); // release pointer
 pElecCurve=NULL;       // reset pointer value to NULL
 //
 rc = S_OK;
 //
 return rc; // exit S_OK;
}


//=========================================================================================================
//
// Method : create a point in bundle segment curve. 
// ------------------------------------
//
//      piBundleSegment : bundle segment instance 
//      distance : distance from first extremity
//      spPointOnCurve : the point created on the curve of piBundleSegment 

HRESULT CreatePointOnBundleSegment ( CATIEhiBundleSegment * piBundleSegment, double & distance,CATIGSMPointOnCurve_var & spPointOnCurve)
{
  HRESULT rc(E_FAIL);
  if(!piBundleSegment) return rc;

  CATIGSMSpline * pGSMSpline  = NULL;
  rc = piBundleSegment->GetElecCurve(&pGSMSpline);
  
  // -- retrieving container
  CATIContainer_var spFeatContainer;   // the container 
  CATISpecObject_var spObjectCurve = pGSMSpline;
  if ( NULL_var != spObjectCurve ) spFeatContainer = spObjectCurve->GetFeatContainer();
  
  // -- retrieving factories : 
  //             -   litteral feature factory
  //             -   GSM factory
  CATICkeParmFactory_var spCKEfactory = spFeatContainer;  // litteral feature factory
  CATIGSMFactory_var spGSMfactory = spFeatContainer;      // GSM factory
  if ( NULL_var == spGSMfactory || NULL_var == spCKEfactory )
  {
    if(pGSMSpline) pGSMSpline->Release(); // release pointe
    pGSMSpline=NULL;       // reset pointer value to NULL
    return rc;             // cannot retrieve factories : exit E_FAIL
  }
  CATICkeParm_var spDistance   = spCKEfactory->CreateLength  ( "Distance", 0.5);
  CATIGSMPointOnCurve::DistanceType Type = CATIGSMPointOnCurve::Geodesic;
  CATGSMOrientation Orientation = CATGSMSameOrientation;
  spPointOnCurve = spGSMfactory ->CreatePoint( spObjectCurve, 
                                                                       NULL_var,
                                                                       spDistance,
                                                                       Orientation,
                                                                       Type);
  if(!spPointOnCurve) 
  {
    cout << "> spPointOnCurve not created " << endl << flush;
    return 10; // revoir le numéro a retourner
  }

  
 // -- retrieving GSM Body :
 // 
 CATBaseUnknown_var spGSMBody ; // the GMS body 

 CATIPartRequest * pPartAsRequest = NULL;
 CATIPrtContainer_var spPartCont = spFeatContainer;
 if ( NULL_var == spPartCont ) return rc;
 CATISpecObject_var spPart = spPartCont->GetPart();
 if ( NULL_var == spPart ) return rc;
 // 
 if( SUCCEEDED(spPart->QueryInterface(IID_CATIPartRequest, (void**)&pPartAsRequest)) )
 {
   
   const CATUnicodeString stdContext(" "); // Sets the context for  bodies lookup 
   
   // retrieve GSM open body
   CATLISTV(CATBaseUnknown_var) surfBodies;  // List of GSM bodies in pPartAsRequest
   pPartAsRequest->GetSurfBodies(stdContext, surfBodies);
   
   // select first body found to create points
   spGSMBody = surfBodies[1];

   pPartAsRequest->Release();
   pPartAsRequest=NULL;
 }
 if ( NULL_var == spGSMBody ) return rc;  // GSM body not found
 CATIDescendants_var spFather = spGSMBody; 
 if ( NULL_var == spFather ) return rc; 
 spFather->Append(spPointOnCurve);
 CATISpecObject_var (spPointOnCurve)->Update(); // compute point geometry  

 //
 // -- update curve geometry
 spObjectCurve->Update();

 if(pGSMSpline) pGSMSpline->Release();
 pGSMSpline = NULL;

 return rc;
}




//=========================================================================================================
// Method to set bundle segment attributes
// ---------------------------------------
//
//      piBundleSegment : bundle segment instance 
//      mode            : build mode of bundle segment Slack / Length / Bend     
//      slack           : slack value
//      length          : length value
//      bend_radius     : minimum bend radius
//      diameter        : diameter 
//
//
HRESULT SetBundleSegmentAttributes ( CATIEhiBundleSegment * piBundleSegment, CATUnicodeString & mode,
                                     double & bend_radius, double & diameter )
{
 HRESULT rc = E_FAIL;
 //
 if (!piBundleSegment) return rc;        // pointer not valuated : exit E_FAIL
 if ( mode != "Slack" && mode != "Length" && mode != "Bend" ) return rc; // invalid mode : exit E_FAIL
 // 
 CATIElecAttrAccess * piElecAttr = NULL;
 rc = piBundleSegment->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttr );
 if ( FAILED(rc) || !piElecAttr )  return rc; // Query Interface CATIElecAttrAccess failed : exit E_FAIL
 //
 CATUnicodeString attribute;
 // --- set build mode 
 attribute = "Elec_Creation_Mode";
 rc = piElecAttr->Set(attribute,mode);
 if ( FAILED(rc) ) return rc; // set attribute Elec_Creation_Mode failed : exit E_FAIL

  // --- set bend radius
 attribute = "Elec_Bend_Radius";
 rc = piElecAttr->Set(attribute,bend_radius);
 if ( FAILED(rc) ) return rc; // set attribute Elec_Bend_Radius failed : exit E_FAIL

 // --- set diameter
 attribute = "Elec_Diameter";
 rc = piElecAttr->Set(attribute,diameter);
 if ( FAILED(rc) ) return rc; // set attribute Elec_Diameter failed : exit E_FAIL

 //
 rc = S_OK;
 //
 piElecAttr->Release(); // release pointer
 piElecAttr=NULL;       // reset pointer value to NULL
 //
 return rc; // exit S_OK;
}


//=========================================================================================================
// Main - sample 
// 
int main (int argc, char * argv[] )
{ 
  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  //
  // 1.1--- Check inputs
  //
  if ( 7 !=argc )
  {
    cout << " ERROR : number of inputs is invalid : " << argc << endl;
    return 1;
  }

  // --- Check path
  CATDirectory Dir;
  CATLibStatus status = ::CATOpenDirectory (argv[1], &Dir);
      
  if ( CATLibError == status)
  {
     cout << " ERROR : Can't open directory " << argv[1] << endl;
     return 1;
  }
  CATUnicodeString PathOutput ( argv[1] ); // output path 
  //

  // --- initialize part numbers and file names
  CATUnicodeString GbnPartNum  ( argv[2] ); // Part number of Geometrical Bundle
  CATUnicodeString Bns1PartNum ( argv[3] ); // Part number of Bundle Segment 1 
  CATUnicodeString Bns2PartNum ( argv[4] ); // Part number of Bundle Segment 2
  CATUnicodeString Bns3PartNum ( argv[5] ); // Part number of Bundle Segment 3
  CATUnicodeString MultiBnsPartNum ( argv[6] ); // Part number of multi branchable
  //
  CATUnicodeString  doc_part = ".CATPart";
  CATUnicodeString  doc_product = ".CATProduct";
  CATUnicodeString GbnFile  = GbnPartNum  + doc_product;  // Geometrical Bundle file
  CATUnicodeString Bns1File = Bns1PartNum + doc_part;     // Bundle Segment 1 file
  CATUnicodeString Bns2File = Bns2PartNum + doc_part;     // Bundle Segment 2 file
  CATUnicodeString Bns3File = Bns3PartNum + doc_part;     // Bundle Segment 3 file 
  CATUnicodeString MultiBnsFile = MultiBnsPartNum + doc_part;   // Multi branchable file 

  cout << "> input checked " << endl << flush;
  cout << "   + path : "<< argv[1] << endl << flush;
  cout << "   + geometrical bundle : "<< argv[2] << endl << flush;
  cout << "   + bundle segment 1   : "<< argv[3] << endl << flush;
  cout << "   + bundle segment 2   : "<< argv[4] << endl << flush;
  cout << "   + bundle segment 3   : "<< argv[5] << endl << flush;
  cout << "   + multi branchable   : "<< argv[6] << endl << flush;

  //
  // 1.2--- Creating the Session 
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_EhiCreateBranchableBns_Session";
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 2;
  }
  
  // 1.3--- Creating a new CATProduct document :  
  
  CATDocument *pGbnDoc = NULL; // pGbnDoc is a pointer to the CATProduct document 
  

  cout << "> create CATProduct document :"<< GbnFile.ConvertToChar() << endl << flush;
  rc = CATDocumentServices::New("CATProduct", pGbnDoc);
  if (SUCCEEDED(rc) && (NULL != pGbnDoc))
  {
    cout << "> document created " << endl << flush;
  }
  else
  {
    cout << "ERROR in creating CATProduct document" << endl << flush;
    return 3;
  }
  
  // 1.4--- Retrieving root product of the created document 
  
  CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product
  
  CATIDocRoots * pGbnDocRoots = NULL;
  rc = pGbnDoc->QueryInterface(IID_CATIDocRoots,(void**) &pGbnDocRoots);
  if ( FAILED(rc) || (NULL==pGbnDocRoots) ) return 4;
  CATListValCATBaseUnknown_var* pListRootProduct = pGbnDocRoots->GiveDocRoots();
  pGbnDocRoots->Release();
  pGbnDocRoots=NULL;
  
  CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
  if (NULL_var != spCBU && pListRootProduct && pListRootProduct->Size() )
  {  
    rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
    if (pListRootProduct) delete pListRootProduct;
    pListRootProduct = NULL;
    //
    if  (SUCCEEDED(rc) && (NULL != piRootProduct))
      cout << "> root product found in document " << endl << flush;
    else
    {
      cout << "ERROR : Root product not found in document " << endl << flush;
      return 4;
    }
  }
  

  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  
  CATIEleDocServices * piElecDocServices = NULL;
  
  rc = pGbnDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
  if ( SUCCEEDED(rc) && piElecDocServices )
  {
    rc = piElecDocServices->Initialize();
  }
  
  if (SUCCEEDED(rc) )
  {
    cout << "> electrical environment initialized " << endl << flush;
  }
  else
  {
    cout << "ERROR : electrical environment initialization failed " << endl << flush;
    return 5;
  }
  
  if ( NULL != piElecDocServices )
  {
    piElecDocServices->Release();
    piElecDocServices=NULL;
  }


  //--------------------------------------------------------------------
  // 3. Creating the Geometrical Bundle.   
  //--------------------------------------------------------------------

  CATIEhiGeoBundle * piGeoBundle = NULL;  // the geometrical bundle
  //
  CATIEhiFactory * piEhiFactory = NULL;   // the factory
  //
  rc = piRootProduct->QueryInterface(IID_CATIEhiFactory,(void**) &piEhiFactory );
  //     
  if ( FAILED(rc) || !piEhiFactory )
  {
    cout << "ERROR : retrieving Ehi factory failed " << endl << flush;
    return 6;
  }
  
  rc = piEhiFactory->CreateGeometricalBundle(&piGeoBundle);
  if ( FAILED(rc) || !piGeoBundle )
  {
    cout << "ERROR : creating geometrical bundle failed " << endl << flush;
    return 6;
  }
  else
  {
    cout << "> geometrical bundle created " << endl << flush;

    CATIProduct * piProductGbn = NULL;
    if ( SUCCEEDED(piGeoBundle->QueryInterface(IID_CATIProduct,(void**)&piProductGbn)) && piProductGbn )
    {
      piProductGbn->SetPartNumber(GbnPartNum);
      piProductGbn->Release();
      piProductGbn=NULL;
    }
  }


  //--------------------------------------------------------------------
  // 4. Creating 3 Bundle Segments under a multi branchable   
  //--------------------------------------------------------------------
  //

  //
  // - 4.1 create a multi branchable bundle
  //       ---------------------------------  
  //       => a branchable with a bundle segment are created

  CATIEhiMultiBranchable * piMultiBranchable = NULL;
  
  rc = piGeoBundle->CreateMultiBranchable (& piMultiBranchable  );
  if ( FAILED(rc) || !piMultiBranchable )
  {
	  cout << "ERROR : creating multi branchable failed " << endl << flush;
	  return 7;
  }
  else
  {
	  cout << "> multi branchable created " << endl << flush;
	  
	  //  - set multi branchable part number
	  
	  CATIProduct * piMultiBnsProduct = NULL;
	  if ( SUCCEEDED(piMultiBranchable->QueryInterface(IID_CATIProduct,(void**)&piMultiBnsProduct)) && piMultiBnsProduct )
	  {
		  
		  piMultiBnsProduct->SetPartNumber(MultiBnsPartNum);
		  rc = piMultiBnsProduct->SetPrdInstanceName(MultiBnsPartNum);
		  if (FAILED(rc)) return 8;
		  piMultiBnsProduct->Release();
		  piMultiBnsProduct=NULL;
	  }
  }


  //
  // - 4.2 create three bundle segments
  //       ----------------------------  
  // 

  // -- adding a second branchable : a second bundle segment is created

  CATIEhiBranchable* piNewBranchable=NULL;
  rc = piMultiBranchable->AddBranchable(&piNewBranchable);
  if ( FAILED(rc) || (NULL == piNewBranchable) )
  {
	  cout << "ERROR : problem when creating branchable 2 " << endl << flush;
	  return 9;
  } 
  else  
	  cout << ">  branchable 2 created under the multi branchable " << endl << flush;	  
  
  piNewBranchable->Release();
  piNewBranchable=NULL; 

  
  // -- adding a third branchable : a third bundle segment is created

  rc = piMultiBranchable->AddBranchable(&piNewBranchable);
  if ( FAILED(rc) || (NULL == piNewBranchable) )
  {
	  cout << "ERROR : problem when creating branchable 3 " << endl << flush;
	  return 10;
  } 
  else
  {
	  cout << ">  branchable 3 created under the multi branchable " << endl << flush;	  
  }
  
  piNewBranchable->Release();
  piNewBranchable=NULL;
  

  // -- retrieving the three bundle segments under the multi branchable

  CATListValCATBaseUnknown_var* pListBundleSegment = NULL;
  rc = piMultiBranchable->ListBundleSegments(&pListBundleSegment);
  
  //
  if ( SUCCEEDED(rc) && (NULL!=pListBundleSegment) && (3 == pListBundleSegment->Size()) ) 
  {
	  cout << "> number of bundle segment in geometrical bundle :"<< pListBundleSegment->Size() <<endl << flush;
  }
  else
  {
	  cout << "ERROR : problem when retrieving bundle segment under multi branchable " << endl << flush;
	  return 11;
  } 

  if ((NULL_var==(*pListBundleSegment)[1]) || (NULL_var==(*pListBundleSegment)[2])
                                           || (NULL_var==(*pListBundleSegment)[3])) return 11;

  
  CATIEhiBundleSegment * piBundleSegment1 = NULL;
  CATIEhiBundleSegment * piBundleSegment2 = NULL;
  CATIEhiBundleSegment * piBundleSegment3 = NULL;

 
  spCBU = (*pListBundleSegment)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment1);
  if (FAILED(rc) || (NULL == piBundleSegment1)) return 11;

  spCBU = (*pListBundleSegment)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment2);
  if (FAILED(rc) || (NULL == piBundleSegment2)) return 11;

  spCBU = (*pListBundleSegment)[3];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment3);
  if (FAILED(rc) || (NULL == piBundleSegment3)) return 11;


  delete pListBundleSegment;
  pListBundleSegment=NULL;


  //
  //  - set bundle segment part numbers

  CATUnicodeString Elec_Ref_Des("Elec_Ref_Des");
  CATUnicodeString RefDes;
  CATIElecAttrAccess_var spAttrAccess(piBundleSegment1);
  if (NULL_var != spAttrAccess)
  {
	  RefDes = Bns1PartNum;
	  rc = spAttrAccess->Set(Elec_Ref_Des, RefDes );
	  if (FAILED(rc)) return 12;
  } 

  spAttrAccess = piBundleSegment2;
  if (NULL_var != spAttrAccess)
  {
	  RefDes = Bns2PartNum;
	  rc = spAttrAccess->Set(Elec_Ref_Des, RefDes );
	  if (FAILED(rc)) return 12;
  }

  spAttrAccess = piBundleSegment3;
  if (NULL_var != spAttrAccess)
  {
	  RefDes = Bns3PartNum;
	  rc = spAttrAccess->Set(Elec_Ref_Des, RefDes );
	  if (FAILED(rc)) return 12;
  }




  //
  // - 4.3 retrieving the branchables from the multibranchable
  //       ---------------------------------------------------       
  //

  CATListValCATBaseUnknown_var* pListBranchable = NULL;
  rc = piMultiBranchable->ListBranchables(&pListBranchable);
  
  //
  if ( SUCCEEDED(rc) && (NULL!=pListBranchable) && (3 == pListBranchable->Size()) ) 
  {
	  cout << "> number of branchables in multi branchable :"<< pListBranchable->Size() <<endl << flush;
  }
  else
  {
	  cout << "ERROR : problem when retrieving branchables under multi branchable " << endl << flush;
	  return 13;
  } 

  if ((NULL_var==(*pListBranchable)[1]) || (NULL_var==(*pListBranchable)[2]) 
                                        || (NULL_var==(*pListBranchable)[3]) ) return 13;
                                     
  
  CATIEhiBranchable * piBranchable1 = NULL;
  CATIEhiBranchable * piBranchable2 = NULL;
  CATIEhiBranchable * piBranchable3 = NULL;
  

  spCBU = (*pListBranchable)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchable1);
  if (FAILED(rc) || (NULL == piBranchable1)) return 13;

  spCBU = (*pListBranchable)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchable2);
  if (FAILED(rc) || (NULL == piBranchable2)) return 13;

  spCBU = (*pListBranchable)[3];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchable3);
  if (FAILED(rc) || (NULL == piBranchable3)) return 13;


  delete pListBranchable;
  pListBranchable=NULL;


  // set RefDes on the three branchables

  spAttrAccess = piBranchable1;   
  if (NULL_var != spAttrAccess)
  {
	  RefDes ="BundleSegment_1";
	  rc = spAttrAccess->Set(Elec_Ref_Des ,RefDes);
	  if (FAILED(rc)) return 14;
  }

  spAttrAccess = piBranchable2; 
  if (NULL_var != spAttrAccess)
  {
	  RefDes ="BundleSegment_2";
	  rc = spAttrAccess->Set(Elec_Ref_Des ,RefDes);
	  if (FAILED(rc)) return 14;
  }

  spAttrAccess = piBranchable3; 
  if (NULL_var != spAttrAccess)
  {
	  RefDes ="BundleSegment_3";
	  rc = spAttrAccess->Set(Elec_Ref_Des ,RefDes);
	  if (FAILED(rc)) return 14;
  }
  
 
  
  
  //
  // - 4.4 Setting bundle segments attributes  
  //       ----------------------------------  
  //         
  //   + initialize bundle segment attributes
  //        - build mode : "Slack" . "Length" or "Bend"            
  //             - "Slack" mode  : slack  ( percentage of slack added )
  //             - "Length" mode : length ( imposed length of bundle segment )
  //             - "Bend" mode   : no slack ( minimum length is computed ) 
  //        - diameter 
  //        - minimum bend radius
  //
  double diameter, bend_radius;
  CATUnicodeString mode;

  //    + set attributes for bundle segment 1
  diameter = 0.025;
  bend_radius=0.03;
  mode="Slack";
  rc = SetBundleSegmentAttributes ( piBundleSegment1, mode,  bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to bundle segment 1 failed " << endl << flush;
    return 15;

  }
  else
    cout << "> set attribute to bundle segment 1 " << endl << flush;

  //    + set attributes for bundle segment 2
  bend_radius=0.010;
  mode="Slack";
  rc = SetBundleSegmentAttributes ( piBundleSegment2, mode,  bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to bundle segment 2 failed " << endl << flush;
    return 16;

  }
  else
    cout << "> set attribute to bundle segment 2 " << endl << flush;

  //    + set attributes for bundle segment 3
  bend_radius=0.010;
  mode="Slack";

  rc = SetBundleSegmentAttributes ( piBundleSegment3, mode,  bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to bundle segment 3 failed " << endl << flush;
    return 17;

  }
  else
    cout << "> set attribute to bundle segment 3 " << endl << flush;


  //
  // - 4.5 define bundle segment route  
  //       ---------------------------  
  //   + initialize coordinates for bundle segment constraint points  
  //
  //       - points[3*nb_points] 
  //       - values are given in MKS units
  //
  //   - bundle segment 1 /  extremity 1   : P0 ( 0.88   ,-0.27   ,0.47  ) 
  //   - bundle segment 1 /  Second point  : P1 ( 0.47   ,0.125   ,-0.178 ) 
  //   - bundle segment 1 /  extremity 2   : P2 ( 0.   ,0.    ,0.  )  
  //
  //   - bundle segment 2 /  extremity 1   : P0 ( 0.   ,0   ,0.  )  
  //   - bundle segment 2 /  Second point  : P1 ( -0.1807   ,0.04  ,0. ) 
  //   - bundle segment 2 /  extremity 2   : P2 (-0.2  ,0.06  ,0.0) 
  //
  //   - bundle segment 3 /  extremity 1   : P0 (-0.2  ,0.06  ,0.0) 
  //   - bundle segment 3 /  Second point  : P1 ( -0.7807   ,0.09  ,0. ) 
  //   - bundle segment 3 /  extremity 2   : P3 ( -1.2  ,0.5  ,0.0)  
  //
  //
  double points[9];
  int nb_point = 3;

  //   +- P0
  points[0] = 0.88;
  points[1] = -0.27;
  points[2] = 0.47;
  
  //
  //   +- P1
  points[3] = 0.47;
  points[4] = 0.125;
  points[5] = -0.178;
  
  //
  //   +- P2
  points[6] = 0.;
  points[7] = 0.;
  points[8] = 0.;
  


  rc = SetBundleSegmentRoute ( piBundleSegment1, points, nb_point ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : Adding constraint points to bundle segment 1 failed " << endl << flush;
    return 18;
  }  
  else
    cout << "> add constraint points to bundle segment 1 " << endl << flush;

  //  +- define route for bundle segment 2
  //   +- P2
  //   +- P2
  points[0]=0.;
  points[1]=0.;
  points[2]=0.;
  
  //
  //   +- P4
  points[3]=-0.1807;
  points[4]=0.04;
  points[5]=-0.;
  
  //
  //   +- P5
  points[6]=-0.20;
  points[7]=0.06;
  points[8]=0.;
  

  rc = SetBundleSegmentRoute ( piBundleSegment2, points, nb_point ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : Adding constraint points to bundle segment 2 failed " << endl << flush;
    return 19;
  }
  else
    cout << "> add constraint points to bundle segment 2 " << endl << flush;

  //  +- define route for bundle segment 3
  //   +- P3

   points[0]=-0.20;
  points[1]=0.06;
  points[2]=0.;
  
  //
  //   +- P4
  points[3]=-0.7807;
  points[4]=0.09;
  points[5]=0.;
  
  //
  //   +- P5
  points[6]=-1.20;
  points[7]=0.5;
  points[8]=0.;

  rc = SetBundleSegmentRoute ( piBundleSegment3, points, nb_point ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : Adding constraint points to bundle segment 3 failed " << endl << flush;
    return 20;
  }
  else
    cout << "> add constraint points to bundle segment 3 " << endl << flush;


  //
  //
  // - 4.6 computing bundle segments  
  //       -------------------------  
  //
  //   + compute bundle segment 1 
  //         
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment1 );
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing bundle segment 1 failed " << endl << flush;
    return 21;
  }
  else
    cout << "> bundle segment 1 sucessfully computed " << endl << flush;

  //   + compute bundle segment 2 
  //         
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment2 );
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing bundle segment 2 failed " << endl << flush;
    return 22;
  }
  else
    cout << "> bundle segment 2 sucessfully computed " << endl << flush;

  //   + compute bundle segment 3 
  //         
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment3 );
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing bundle segment 3 failed " << endl << flush;
    return 23;
  }
  else
    cout << "> bundle segment 3 sucessfully computed " << endl << flush;



  //------------------------------------------------------
  //  5. Split a bundle segment .
  //------------------------------------------------------

  // - 5.1 Creating a point on the first bundle segment 
  // ---------------------------------------------------

  CATIGSMPointOnCurve_var spGSMPointOnCurve;
  double distance = 0.5;
  rc = CreatePointOnBundleSegment(piBundleSegment1, distance,spGSMPointOnCurve);
  
  if (FAILED(rc) || (NULL_var == spGSMPointOnCurve))
  {
	  cout << "> CreatePointOnBundleSegment has failed " << endl << flush;
	  return 24;
  }
  else	  
	  cout << "> spGSMPointOnCurve sucessfully created " << endl << flush;

  CATIEhiBundleSegment * pElecBundleSegment = NULL;
  rc = piBundleSegment1-> Split(spGSMPointOnCurve, pElecBundleSegment);
  if(FAILED(rc) || !pElecBundleSegment)
  {
      cout << "ERROR : split of bundle segment has failed " << endl << flush;
      return 25;
  }
  
  cout << "> bundle segment sucessfully split in two bundle segments " << endl << flush;
 
  
  // - 5.2 modification of attribute of the new bundle segment.
  // ----------------------------------------------------------
  diameter = 0.02;
  bend_radius=0.03;
  mode="Slack";
  rc = SetBundleSegmentAttributes ( pElecBundleSegment, mode,  bend_radius, diameter );
  if ( FAILED(rc) )
  {
	  cout << "ERROR : setting attributes to bundle segment 1 failed " << endl << flush;
	  return 26;       
  }
  else
	  cout << "> set attribute to bundle segment 1 " << endl << flush;
  
  
  // - 5.3 compute the new bundle segment created by split of first bundle segment
  // -----------------------------------------------------------------------------
  rc = piGeoBundle->ComputeBundleSegment ( pElecBundleSegment );
  if ( FAILED(rc)  )
  {
	  cout << "ERROR : computing bundle segment failed " << endl << flush;
	  return 27;
  }
  else
	  cout << "> bundle segment result of split sucessfully computed " << endl << flush;
  


  //----------------------------------------------------------------------------
  //  6. Merge the pElecBundleSegment in the piBundleSegment1
  //----------------------------------------------------------------------------

  rc = piBundleSegment1->Merge (pElecBundleSegment);
  if(FAILED(rc))
  {
	  cout << "ERROR : Merge pElecBundleSegment with piBundleSegment1 " << endl << flush;
	  return 28;
  }
  
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment1 );
  if ( FAILED(rc)  )
  {
	  cout << "ERROR : computing bundle segment failed " << endl << flush;
	  return 29;
  }
  else
	  cout << "> bundle segment result of merge sucessfully computed " << endl << flush;
  
  
  pElecBundleSegment->Release();
  pElecBundleSegment =  NULL;



  //--------------------------------------------------------------------
  // 7. Epilogue  
  //--------------------------------------------------------------------
  
  // 7.1-- releasing pointers to interface
  //
  piRootProduct->Release(); 
  piEhiFactory->Release();  
  piGeoBundle->Release();  
  piBranchable1->Release(); 
  piBranchable2->Release(); 
  piBranchable3->Release(); 
  piBundleSegment1->Release();  
  piBundleSegment2->Release();  
  piBundleSegment3->Release();  
  
  // --- always reset pointer value to NULL after release
  piRootProduct=NULL; 
  piEhiFactory=NULL;  
  piGeoBundle=NULL;   
  piBranchable1=NULL;  
  piBranchable2=NULL;
  piBranchable3=NULL;  
  piBundleSegment1=NULL;  
  piBundleSegment2=NULL;  
  piBundleSegment3=NULL;  


  //
  // 7.2-- saving the documents 
    
  // --- saving multi branchable CATPart document 
  
  CATIProduct_var spMultiBranchableI = piMultiBranchable;
  piMultiBranchable->Release(); 
  piMultiBranchable=NULL;  
  CATAssert(!!spMultiBranchableI);
  CATIProduct_var spMultiBranchableR = spMultiBranchableI->GetReferenceProduct();
  CATAssert(!!spMultiBranchableR);
  
  CATILinkableObject_var spLinkable=spMultiBranchableR;
  CATAssert(!!spLinkable);
  
  CATDocument * pMultiBnsPartDoc = spLinkable->GetDocument();  
  
  if ( !pMultiBnsPartDoc )
  {
    cout << "ERROR in retrieving multi branchable document" << endl << flush;
    return 30;
  }

  rc = CATDocumentServices::SaveAs (*pMultiBnsPartDoc , PathOutput+MultiBnsFile );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 1 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 1 CATPart document" << endl << flush;
    return 30;
  }


  // --- saving geometrical bundle CATProduct document

  rc = CATDocumentServices::SaveAs (*pGbnDoc , PathOutput+GbnFile );
  if (SUCCEEDED(rc))
  {
    cout << "> geometrical bundle document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving document" << endl << flush;
    return 31;
  }

  //
  // 7.3-- removing documents from session 
  rc = CATDocumentServices::Remove(*pGbnDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 32;
  }

  //
  // 7.4-- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 33;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}







