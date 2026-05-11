// COPYRIGHT DASSAULT SYSTEMES 2002

//===============================================================================
//  Abstract of Use Case "CAAEhiBundleSegment":
//  ------------------------------------------
//
//  This Use Case illustrates how to create geometrical bundle and bundle segment,
//  and connect bundle segment ( creating bundle segment network ). 
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
//  4. Creating 3 Bundle Segments 
//      4.1 Creating bundle segments 
//      4.2 Setting attributes
//      4.3 define bundle segment route 
//      4.4 Computing bundle segments 
//  5 .Retrieving Bundle Segments extremities.
//  6. Connecting Bundle Segment extremities.  
//  7. Disconnecting Bundle Segment extremities.
//  8. Epilogue.
//      8.1 saving documents
//      8.2 closing session
//
//  Return Errors:
//  -------------
//  1 - ERROR : invalid inputs 
//  2 - ERROR in creating the session
//  3 - ERROR in creating new CATProduct document
//  4 - ERROR in retrieving root product of CATProdut document.
//  5 - ERROR in initializing electrical environment. 
//  6 - ERROR in creating geometrical bundle.
//  7 - ERROR in creating bundle segment.
//  8 - ERROR in assigning constaint point to bundle segment.
//  9 - ERROR in setting bundle segment atttribute.
// 10 - ERROR in managing electrical curve
// 11 - ERROR in computing bundle segment
// 12 - ERROR in retrieving bundle segment extremities.
// 13 - ERROR in saving document  
// 14 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiBundleSegment PathDir GbnName Bns1Name Bns2Name Bns3Name" where :
//      . "PathDir" is the entire pathname where to save the new created documents.
//        "GbnName" is the part number of the created geometrical bundle.     
//        "Bns1Name" is the part number of the first bundle segment.     
//        "Bns2Name" is the part number of the second bundle segment.     
//        "Bns3Name" is the part number of the third bundle segment.     
//
//           Geometrical Bundle is saved as GbnName.CATProduct document.      
//           First Bundle Segment is saved as BundleSegment Bns1Name.CATPart document.      
//           Second Bundle Segment is saved as BundleSegment Bns2Name.CATPart document.      
//           Third Bundle Segment is saved as BundleSegment Bns3Name.CATPart document.      
//
//=============================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
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
#include "CATIEhiBnlSegmentExtremity.h"  // managing bundle segments extremity

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
    CATISpecObject_var (spPoint)->Update(); // conmpute point geometry  
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
HRESULT SetBundleSegmentAttributes ( CATIEhiBundleSegment * piBundleSegment, CATUnicodeString & mode, double & slack,
                                     double & length, double & bend_radius, double & diameter )
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

 // --- build mode = "Slack" : set slack
 if ( mode == "Slack" )
 {
   attribute = "Elec_Di_Slack";
   rc = piElecAttr->Set(attribute,slack);
   if ( FAILED(rc) ) return rc; // set attribute Elec_Di_Slack failed : exit E_FAIL
 }

 // --- build mode = "Length": set length
 if ( mode == "Length" )
 {
   attribute = "Elec_Length";
   rc = piElecAttr->Set(attribute,length);
   if ( FAILED(rc) ) return rc; // set attribute Elec_Length failed : exit E_FAIL
 }

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
  if ( 6 !=argc )
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
  //
  CATUnicodeString  doc_part = ".CATPart";
  CATUnicodeString  doc_product = ".CATProduct";
  CATUnicodeString GbnFile  = GbnPartNum  + doc_product;  // Geometrical Bundle file
  CATUnicodeString Bns1File = Bns1PartNum + doc_part;     // Bundle Segment 1 file
  CATUnicodeString Bns2File = Bns2PartNum + doc_part;     // Bundle Segment 2 file
  CATUnicodeString Bns3File = Bns3PartNum + doc_part;     // Bundle Segment 3 file 

  cout << "> input checked " << endl << flush;
  cout << "   + path : "<< argv[1] << endl << flush;
  cout << "   + geometrical bundle : "<< argv[2] << endl << flush;
  cout << "   + bundle segment 1   : "<< argv[3] << endl << flush;
  cout << "   + bundle segment 2   : "<< argv[4] << endl << flush;
  cout << "   + bundle segment 3   : "<< argv[5] << endl << flush;
  //
  //1.2--- Creating the Session 
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_EhiConnectBns_Session";
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
  if ( FAILED(rc) || (NULL==pGbnDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pGbnDocRoots->GiveDocRoots();
  pGbnDocRoots->Release();
  pGbnDocRoots=NULL;
  
  CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
  if ( pListRootProduct && pListRootProduct->Size() && spCBU)
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
  // 4. Creating 3 Bundle Segments     
  //--------------------------------------------------------------------
  //
  CATIEhiBundleSegment * piBundleSegment1 = NULL;
  CATIEhiBundleSegment * piBundleSegment2 = NULL;
  CATIEhiBundleSegment * piBundleSegment3 = NULL;
  //
  // - 4.1 create bundle segments  
  //       ----------------------       
  //
  //   + create bundle segment 1 
  //         
  rc = piGeoBundle->CreateBundleSegment (& piBundleSegment1  );
  if ( FAILED(rc) || !piBundleSegment1 )
  {
    cout << "ERROR : creating bundle segment 1 failed " << endl << flush;
    return 7;
  }
  else
  {
    cout << "> bundle segment 1 created " << endl << flush;
    //
    //  - set bundle segment part number
    CATIProduct * piProductBns = NULL;
    if ( SUCCEEDED(piBundleSegment1->QueryInterface(IID_CATIProduct,(void**)&piProductBns)) && piProductBns )
    {
      piProductBns->SetPartNumber(Bns1PartNum);
      piProductBns->Release();
      piProductBns=NULL;
    }
  }
  //
  //   + create bundle segment 2 
  //         
  rc = piGeoBundle->CreateBundleSegment (& piBundleSegment2  );
  if ( FAILED(rc) || !piBundleSegment2 )
  {
    cout << "ERROR : creating bundle segment 2 failed " << endl << flush;
    return 7;
  }
  else
  {
    cout << "> bundle segment 2 created " << endl << flush;
    //  - set bundle segment part number
    CATIProduct * piProductBns = NULL;
    if ( SUCCEEDED(piBundleSegment2->QueryInterface(IID_CATIProduct,(void**)&piProductBns)) && piProductBns )
    {
      piProductBns->SetPartNumber(Bns2PartNum);
      piProductBns->Release();
      piProductBns=NULL;
    }
  }
  //
  //   + create bundle segment 3 
  //         
  rc = piGeoBundle->CreateBundleSegment (& piBundleSegment3  );
  if ( FAILED(rc) || !piBundleSegment3 )
  {
    cout << "ERROR : creating bundle segment 3 failed " << endl << flush;
    return 7;
  }
  else
  {
    cout << "> bundle segment 3 created " << endl << flush;
    //  - set bundle segment part number
    CATIProduct * piProductBns = NULL;
    if ( SUCCEEDED(piBundleSegment3->QueryInterface(IID_CATIProduct,(void**)&piProductBns)) && piProductBns )
    {
      piProductBns->SetPartNumber(Bns3PartNum);
      piProductBns->Release();
      piProductBns=NULL;
    }
  }
  //
  // - 4.2 Setting bundle segments attributes  
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
  double diameter, slack, length, bend_radius;
  CATUnicodeString mode;

  //    + set attributes for bundle segment 1
  diameter = 0.008;
  bend_radius=0.018;
  mode="Length";
  length=0.106;
  rc = SetBundleSegmentAttributes ( piBundleSegment1, mode, slack, length, bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to bundle segment 1 failed " << endl << flush;
    return 8;

  }
  else
    cout << "> set attribute to bundle segment 1 " << endl << flush;
  //    + set attributes for bundle segment 2
  diameter = 0.004;
  bend_radius=0.010;
  mode="Slack";
  slack=1.5;
  rc = SetBundleSegmentAttributes ( piBundleSegment2, mode, slack, length, bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to bundle segment 2 failed " << endl << flush;
    return 8;

  }
  else
    cout << "> set attribute to bundle segment 2 " << endl << flush;
  //    + set attributes for bundle segment 3
  diameter = 0.003;
  bend_radius=0.010;
  mode="Slack";
  slack=0.5;
  rc = SetBundleSegmentAttributes ( piBundleSegment3, mode, slack, length, bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to bundle segment 3 failed " << endl << flush;
    return 8;

  }
  else
    cout << "> set attribute to bundle segment 3 " << endl << flush;

  //
  // - 4.3 define bundle segment route  
  //       ---------------------------  
  //   
  //                                     
  //                                o  P2
  //                               /
  //                              /  bundle segment 2
  //           bundle segment 1  /
  //        o------------------o  P0
  //       P1                  | 
  //                           | bundle segment 3
  //                           | 
  //                           o P3


  //   + initialize coordinates for bundle segment constraint points  
  //
  //       - points[3*nb_points] 
  //       - values are given in MKS units
  //
  //   - bundle segment 1 /  extremity 1   : P0 ( 0.   ,0.1   ,0.  )    
  //   - bundle segment 1 /  extremity 2   : P1 ( 0.   ,0.    ,0.  )  
  //   - bundle segment 2 /  extremity 1   : P0 ( 0.   ,0.1   ,0.  )  
  //   - bundle segment 2 /  extremity 2   : P2 (-0.1  ,0.25  ,0.05)  
  //   - bundle segment 3 /  extremity 1   : P0 ( 0.   ,0.1   ,0.  )  
  //   - bundle segment 3 /  extremity 2   : P3 ( 0.2  ,0.15  ,0.05)  
  //
  //
  double points[6];
  int nb_point = 2;
  //   +- P0
  points[0]=0.;
  points[1]=0.1;
  points[2]=0.;
  //
  //  +- define route for bundle segment 1
  //   +- P1
  points[3]=0.;
  points[4]=0.;
  points[5]=0.;
  rc = SetBundleSegmentRoute ( piBundleSegment1, points, nb_point ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : Adding constraint points to bundle segment 1 failed " << endl << flush;
    return 9;

  }
  else
    cout << "> add constraint points to bundle segment 1 " << endl << flush;
  //  +- define route for bundle segment 2
  //   +- P2
  points[3]=-0.1;
  points[4]=0.25;
  points[5]=0.05;
  rc = SetBundleSegmentRoute ( piBundleSegment2, points, nb_point ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : Adding constraint points to bundle segment 2 failed " << endl << flush;
    return 9;

  }
  else
    cout << "> add constraint points to bundle segment 2 " << endl << flush;
  //  +- define route for bundle segment 3
  //   +- P3
  points[3]=0.2;
  points[4]=0.15;
  points[5]=0.05;
  rc = SetBundleSegmentRoute ( piBundleSegment3, points, nb_point ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : Adding constraint points to bundle segment 3 failed " << endl << flush;
    return 9;

  }
  else
    cout << "> add constraint points to bundle segment 3 " << endl << flush;
  //
  //
  // - 4.4 computing bundle segments  
  //       -------------------------  
  //
  //   + compute bundle segment 1 
  //         
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment1 );
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing bundle segment 1 failed " << endl << flush;
    return 11;
  }
  else
    cout << "> bundle segment 1 sucessfully computed " << endl << flush;
  //   + compute bundle segment 2 
  //         
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment2 );
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing bundle segment 2 failed " << endl << flush;
    return 11;
  }
  else
    cout << "> bundle segment 2 sucessfully computed " << endl << flush;
  //   + compute bundle segment 3 
  //         
  rc = piGeoBundle->ComputeBundleSegment ( piBundleSegment3 );
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing bundle segment 3 failed " << endl << flush;
    return 11;
  }
  else
    cout << "> bundle segment 3 sucessfully computed " << endl << flush;
  //
  //--------------------------------------------------------------------
  // 5. Retrieving Bundle Segments extremities.   
  //--------------------------------------------------------------------
  //
  // Retrieving extremities of bundle segment 1 
  //         
  CATIEhiBnlSegmentExtremity * piBnlSegment1_Extremity1=NULL;
  CATIEhiBnlSegmentExtremity * piBnlSegment1_Extremity2=NULL;
  rc = piBundleSegment1->GetExtremities(&piBnlSegment1_Extremity1,&piBnlSegment1_Extremity2);
  if ( FAILED(rc) || !piBnlSegment1_Extremity1 || !piBnlSegment1_Extremity1 )
  {
    cout << "ERROR : retrieving extremity of bundle segment 1 failed " << endl << flush;
    return 12;
  }
  else
    cout << "> extremity of bundle segment 1 sucessfully retrieved " << endl << flush;

  // Retrieving extremities of bundle segment 2 
  //         
  CATIEhiBnlSegmentExtremity * piBnlSegment2_Extremity1=NULL;
  CATIEhiBnlSegmentExtremity * piBnlSegment2_Extremity2=NULL;
  rc = piBundleSegment2->GetExtremities(&piBnlSegment2_Extremity1,&piBnlSegment2_Extremity2);
  if ( FAILED(rc) || !piBnlSegment2_Extremity1 || !piBnlSegment2_Extremity1 )
  {
    cout << "ERROR : retrieving extremity of bundle segment 2 failed " << endl << flush;
    return 12;
  }
  else
    cout << "> extremity of bundle segment 2 sucessfully retrieved " << endl << flush;

  // Retrieving extremities of bundle segment 3 
  //         
  CATIEhiBnlSegmentExtremity * piBnlSegment3_Extremity1=NULL;
  CATIEhiBnlSegmentExtremity * piBnlSegment3_Extremity2=NULL;
  rc = piBundleSegment3->GetExtremities(&piBnlSegment3_Extremity1,&piBnlSegment3_Extremity2);
  if ( FAILED(rc) || !piBnlSegment3_Extremity1 || !piBnlSegment3_Extremity1 )
  {
    cout << "ERROR : retrieving extremity of bundle segment 3 failed " << endl << flush;
    return 12;
  }
  else
    cout << "> extremity of bundle segment 3 sucessfully retrieved " << endl << flush;


  //--------------------------------------------------------------------
  // 6. Connecting Bundle Segment extremities.     
  //--------------------------------------------------------------------
  //
  //     bundle segments are not connected 
  //     ---------------------------------
  //
  //                                      o---------- bundle segment 2
  //                                       
  //     bundle segment 1 -----------o    
  //                                      
  //                                      o---------- bundle segment 3
  //
  //
  //
  // 6.1 connecting BundleSegment1-Extremity1 to BundleSegment2-Extremity1 
  //     -----------------------------------------------------------------
  //
  //
  //
  //                                      o---------- bundle segment 2
  //                                     /  
  //     bundle segment 1 -----------o--C
  //                                      
  //                                      o---------- bundle segment 3
  //
  rc = piBnlSegment1_Extremity1->Connect(piBnlSegment2_Extremity1);
  if ( FAILED(rc) )
  {
    cout << "ERROR : connect BundleSegment1-Extremity1 to BundleSegment2-Extremity1 failed " << endl << flush;
    return 12;
  }
  else
    cout << "> BundleSegment1-Extremity1 connected to BundleSegment2-Extremity1 " << endl << flush;
 
  // 6.2 connecting BundleSegment1-Extremity1 to BundleSegment3-Extremity1 
  //     -----------------------------------------------------------------
  //
  //
  //                                      o---------- bundle segment 2
  //                                     /  
  //     bundle segment 1 -----------o--C
  //                                     \  
  //                                      o---------- bundle segment 3
  //
  rc = piBnlSegment1_Extremity1->Connect(piBnlSegment3_Extremity1);
  if ( FAILED(rc) )
  {
    cout << "ERROR : connect BundleSegment1-Extremity1 to BundleSegment3-Extremity1 failed " << endl << flush;
    return 12;
  }
  else
    cout << "> BundleSegment1-Extremity1 connected to BundleSegment3-Extremity1 " << endl << flush;
 
  //--------------------------------------------------------------------
  // 7. Disconnecting Bundle Segment extremity.     
  //--------------------------------------------------------------------
  //
  // 7.1 disconnecting BundleSegment1-Extremity1  
  //     ------------------------------------
  //
  //
  //                                      o---------- bundle segment 2
  //                                     /  
  //     bundle segment 1 -----------o  C
  //                                     \  
  //                                      o---------- bundle segment 3
  //
  //     bundle segment 2 and bundle segment 3 remain connected 
  //
  rc = piBnlSegment1_Extremity1->Disconnect();
  if ( FAILED(rc) )
  {
    cout << "ERROR : disconnect BundleSegment1-Extremity1 failed " << endl << flush;
    return 13;
  }
  else
    cout << "> BundleSegment1-Extremity1 sucessfully disconnected " << endl << flush;
 
  //--------------------------------------------------------------------
  // 8. Saving documents  
  //--------------------------------------------------------------------
  CATIProduct_var spBnsInstance;     // bundle segment instance product
  CATIProduct_var spBnsReference;    // bundle segment reference product
  CATILinkableObject_var spLinkable; // handle to retrieve document from object
  CATDocument * pBnsPartDoc = NULL;  // bundle segment part document
  
  // --- saving bundle segment 1 CATPart document
  spBnsInstance = piBundleSegment1;
  if ( NULL_var != spBnsInstance  ) spBnsReference = spBnsInstance->GetReferenceProduct();
  if ( NULL_var != spBnsReference ) spLinkable = spBnsReference;    
  if ( NULL_var != spLinkable ) pBnsPartDoc = spLinkable->GetDocument();

  if ( !pBnsPartDoc )
  {
    cout << "ERROR in retrieving bundle segment 1 CATPart document" << endl << flush;
    return 13;
  }
  rc = CATDocumentServices::SaveAs (*pBnsPartDoc , PathOutput+Bns1File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 1 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 1 CATPart document" << endl << flush;
    return 13;
  }


  // --- saving bundle segment 2 CATPart document
  pBnsPartDoc = NULL; 
  spBnsInstance = piBundleSegment2;
  if ( NULL_var != spBnsInstance  ) spBnsReference = spBnsInstance->GetReferenceProduct();
  if ( NULL_var != spBnsReference ) spLinkable = spBnsReference;    
  if ( NULL_var != spLinkable ) pBnsPartDoc = spLinkable->GetDocument();

  if ( ! pBnsPartDoc )
  {
    cout << "ERROR in retrieving bundle segment 2 CATPart document" << endl << flush;
    return 13;
  }
  rc = CATDocumentServices::SaveAs (*pBnsPartDoc , PathOutput+Bns2File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 2 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 2 CATPart document" << endl << flush;
    return 13;
  }

  // --- saving bundle segment 3 CATPart document
  pBnsPartDoc = NULL; 
  spBnsInstance = piBundleSegment3;
  if ( NULL_var != spBnsInstance  ) spBnsReference = spBnsInstance->GetReferenceProduct();
  if ( NULL_var != spBnsReference ) spLinkable = spBnsReference;    
  if ( NULL_var != spLinkable ) pBnsPartDoc = spLinkable->GetDocument();

  if ( ! pBnsPartDoc )
  {
    cout << "ERROR in retrieving bundle segment 3 CATPart document" << endl << flush;
    return 13;
  }
  rc = CATDocumentServices::SaveAs (*pBnsPartDoc , PathOutput+Bns3File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 3 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 3 CATPart document" << endl << flush;
    return 13;
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
    return 13;
  }

  //--------------------------------------------------------------------
  // 9. Epilogue  
  //--------------------------------------------------------------------
  
  // 9.1-- releasing pointers to interface
  //
  piRootProduct->Release(); 
  piEhiFactory->Release();  
  piGeoBundle->Release();  
  piBundleSegment1->Release();  
  piBundleSegment2->Release();  
  piBundleSegment3->Release();  
  piBnlSegment1_Extremity1->Release();
  piBnlSegment1_Extremity2->Release();
  piBnlSegment2_Extremity1->Release();
  piBnlSegment2_Extremity2->Release();
  piBnlSegment3_Extremity1->Release();
  piBnlSegment3_Extremity2->Release();
  // --- always reset pointer value to NULL after release
  piRootProduct=NULL; 
  piEhiFactory=NULL;  
  piGeoBundle=NULL;  
  piBundleSegment1=NULL;  
  piBundleSegment2=NULL;  
  piBundleSegment3=NULL;  
  piBnlSegment1_Extremity1=NULL;
  piBnlSegment1_Extremity2=NULL;
  piBnlSegment2_Extremity1=NULL;
  piBnlSegment2_Extremity2=NULL;
  piBnlSegment3_Extremity1=NULL;
  piBnlSegment3_Extremity2=NULL;
  //
  // 9.2-- removing document from session 
  rc = CATDocumentServices::Remove(*pGbnDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 14;
  }
  // 9.3-- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 14;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
//=========================================================================================================



