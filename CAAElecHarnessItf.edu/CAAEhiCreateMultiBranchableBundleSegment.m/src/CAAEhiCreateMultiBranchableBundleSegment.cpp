// COPYRIGHT DASSAULT SYSTEMES 2003

//===============================================================================
//  Abstract of Use Case "CAAEhiCreateMultiBranchableBundleSegment":
//  ----------------------------------------------------------------
//
//  This Use Case illustrates how to create geometrical bundle and multi
//  branchable bundle segment . 
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
//  4. Creating a multi branchable bundle segment 
//      4.1 Adding two branchables under the muti branchable bundle segment
//      4.2 Retrieving the bundle segments under the multi branchable
//      4.3 Setting attributes on each bundle segment
//      4.4 define bundle segment route of each bundle segment
//      4.5 Computing bundle segments 
//  5. Test some methods on a branchable :
//      5.1 List the branchables under the multi branchable
//      5.2 Get the multi branchable
//      5.3 Get the elec curve 
//      5.4 Retrieving the bundle segments under the branchable
//  6 .Adding a branchable under the multi branchable.
//  7. Removing a branchable of the multi branchable.
//  8. Epilogue.
//      8.1 saving documents
//      8.2 closing session
//
//  Return Errors:
//  -------------
//  1 - ERROR : invalid inputs 
//  2 - ERROR in creating the session
//  3 - ERROR in creating new CATProduct document
//  4 - ERROR in retrieving root product of CATProduct document.
//  5 - ERROR in initializing electrical environment. 
//  6 - ERROR in creating geometrical bundle document
//  7 - ERROR in retrieving root product of geometrical bundle document
//  8 - ERROR in creating geometrical bundle 
//  9 - ERROR in instanciation of geometrical bundle under the root product
// 10 - ERROR in creating multi branchable bundle segment
// 11 - ERROR in adding first branchable under the multi branchable
// 12 - ERROR in adding second branchable under the multi branchable
// 13 - ERROR in retrieving the bundle segments under the multi branchable
// 14 - ERROR in retrieving branchables of the multi branchable
// 15 - ERROR in setting bundle segment attributes on first branchable
// 16 - ERROR in setting bundle segment attributes on second branchable
// 17 - ERROR in setting bundle segment attributes on third branchable
// 18 - ERROR in retrieving elec curve from first branchable
// 19 - ERROR in computing route of first branchable
// 20 - ERROR in retrieving elec curve from second branchable
// 21 - ERROR in computing route of second branchable
// 22 - ERROR in retrieving elec curve from third branchable
// 23 - ERROR in computing route of third branchable
// 24 - ERROR in updating the multi branchable
// 25 - ERROR in retrieving the multi branchable from the branchable
// 26 - ERROR in retrieving elec curve from a branchable
// 27 - ERROR in retrieving bundle segments from the branchable
// 28 - ERROR in removing a branchable from the multi branchable
// 29 - ERROR in retrieving document from the multi branchable
// 30 - ERROR in saving multi branchable document 
// 31 - ERROR in saving multi branchable document  
// 32 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiCreateMultiBranchableBundleSegment PathDir MainName GbnName BnsName" where :
//      . "PathDir" is the entire pathname where to save the new created documents.
//        "MainName" is the part number of the created document. 
//        "GbnName" is the part number of the created geometrical bundle.  
//        "BnsName" is the part number of the created bundle segment.     
//          
//
//==================================================================================================

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
#include "CATIGSMProceduralView.h"       // managing features

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
// Method to set bundle segment attributes
// ---------------------------------------
//
//      piBranchable    : bundle segment instance 
//      mode            : build mode of bundle segment Slack / Length / Bend     
//      slack           : slack value ( in % )
//      length          : length value ( in mm )
//      bend_radius     : minimum bend radius ( in mm )
//      diameter        : diameter ( in mm ) 
//
//
HRESULT SetBranchableAttributes ( CATIEhiBranchable * piBranchable,
								 CATUnicodeString & mode, double & slack, double & length,
								 double & bend_radius, double & diameter )
{
	HRESULT rc = E_FAIL;
	//
	if (!piBranchable) return rc;        // pointer not valuated : exit E_FAIL
	if ( mode != "Slack" && mode != "Length" && mode != "Bend" ) return rc; // invalid mode : exit E_FAIL
	// 
	CATBaseUnknown * pCurve = NULL;
	rc = piBranchable->GetElecCurve(&pCurve);     
	if (FAILED(rc) || (NULL==pCurve)) return E_FAIL;

	//
	CATIElecAttrAccess * piElecAttr = NULL;
	rc = pCurve->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttr );
	pCurve->Release();
	pCurve=NULL;
	if (FAILED(rc) || (NULL==piElecAttr)) return E_FAIL;
	
	//
	CATUnicodeString attribute;
	// --- set build mode 
	attribute = "Elec_Creation_Mode";
	rc = piElecAttr->Set(attribute,mode);
	if (FAILED(rc))
	{
		piElecAttr->Release();
		piElecAttr=NULL; 
		return rc;
	}
	
	// --- build mode = "Slack" : set slack
	if ( mode == "Slack" )
	{
		attribute = "Elec_Di_Slack";
		rc = piElecAttr->Set(attribute,slack);
		if (FAILED(rc))
		{
			piElecAttr->Release();
			piElecAttr=NULL;  
			return rc;
		}
	}
	//
	double val;
	// --- build mode = "Length": set length
	if ( mode == "Length" )
	{
		val = length * 0.001;
		attribute = "Elec_Length";
		rc = piElecAttr->Set(attribute,val);
		if (FAILED(rc))
		{
			piElecAttr->Release();
			piElecAttr=NULL;  
			return rc;
		}
	}
	// --- set bend radius
	attribute = "Elec_Bend_Radius";
	val = bend_radius * 0.001;
	rc = piElecAttr->Set(attribute,val);
	//
	piElecAttr->Release();
	piElecAttr=NULL;
	if (FAILED(rc)) return rc;
	//
	// --- set diameter value
	CATListValCATBaseUnknown_var *  pListOfBns = NULL; 
	rc = piBranchable->ListBundleSegments ( &pListOfBns );
	
	if (SUCCEEDED(rc)) 
	{
		int nb_bns = pListOfBns?pListOfBns->Size():0;
		for ( int i=1; i<=nb_bns; i++ )
		{
      CATBaseUnknown_var spCBU ((*pListOfBns)[i]);
      if (NULL_var != spCBU)
      {		
        rc = spCBU->QueryInterface(IID_CATIElecAttrAccess,(void**)&piElecAttr);
        if (SUCCEEDED(rc) && (NULL!=piElecAttr))
        {
          attribute = "Elec_Diameter";
          val = diameter * 0.001;
          rc = piElecAttr->Set(attribute,val);
          
          piElecAttr->Release();
          piElecAttr=NULL;
          if (FAILED(rc)) break;
        }
      }
		}
	}
	delete pListOfBns;
	pListOfBns=NULL;
	//
	return rc; 
}



//====================================================================================================
// Method : define bundle segment route 
// ------------------------------------
//
//      pGSMSpline  : curve ( GSMSpline )
//      point_coord : array of point coordinates ( in mm )
//      nb_point    : number of points  ( array dimension is 3*nb_point ) 
//
HRESULT EhiRouteCurve ( CATIGSMSpline* pGSMSpline, int nb_point, double* point_coord )
{
 //
 HRESULT rc = E_FAIL;
 //
 if (!pGSMSpline)    return rc;   // pointer not valuated : exit E_FAIL 
 if ( nb_point < 2 ) return rc;   // number of points < 2 : exit E_FAIL;
 //
 //
 // -- retrieving container
 CATIContainer_var spCont;   // the container 
 CATISpecObject_var spObj = pGSMSpline;
 if ( NULL_var != spObj ) spCont = spObj->GetFeatContainer();
 //
 // -- retrieving factories : 
 //             -   litteral feature factory
 //             -   GSM factory
 CATICkeParmFactory_var spCKEfacto = spCont;  // litteral feature factory
 CATIGSMFactory_var spGSMfacto = spCont;      // GSM factory
 if ( NULL_var == spCKEfacto || NULL_var == spGSMfacto )
 {
  return rc;             // cannot retrieve factories : exit E_FAIL
 }

 // -- create and add points to curve
 // 
 CATICkeParm_var X;
 CATICkeParm_var Y; 
 CATICkeParm_var Z;  
 CATIGSMPointCoord_var spPoint;
 //
 for ( int i=1; i<=nb_point; i++ )
 {
   //
   double unit = 0.001;
   double Px = unit * point_coord[  3*(i-1)] ;
   double Py = unit * point_coord[1+3*(i-1)] ;
   double Pz = unit * point_coord[2+3*(i-1)] ;
   //
   X = spCKEfacto->CreateLength  ( "X", Px );
   Y = spCKEfacto->CreateLength  ( "Y", Py );
   Z = spCKEfacto->CreateLength  ( "Z", Pz );
   //
   spPoint = spGSMfacto->CreatePoint(X,Y,Z);   
   if ( NULL_var != spPoint ) // --- point created 
   {   
    CATIGSMProceduralView_var(spPoint)->InsertInProceduralView();
    CATISpecObject_var (spPoint)->Update(); // compute point geometry  
    // --- add constraint point to electrical curve
    pGSMSpline->Add(spPoint);
   }
 }
 //
 // -- update curve geometry
 spObj->Update();
 //
 rc = S_OK;
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
  if ( 5 !=argc )
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
  CATUnicodeString MainPartNum  ( argv[2] ); // Part number of Geometrical Bundle
  CATUnicodeString GbnPartNum  ( argv[3] ); // Part number of Geometrical Bundle
  CATUnicodeString MultiBns1PartNum ( argv[4] ); // Part number of Multi Branchable 1 

  //
  CATUnicodeString  doc_part = ".CATPart";
  CATUnicodeString  doc_product = ".CATProduct";
  CATUnicodeString MainFile  = MainPartNum  + doc_product;  // Main file
  CATUnicodeString GbnFile  = GbnPartNum  + doc_product;  // Geometrical Bundle file
  CATUnicodeString MultiBns1File = MultiBns1PartNum + doc_part; // Multi Branchable 1 file

  cout << "> input checked " << endl << flush;
  cout << "   + path : "<< argv[1] << endl << flush;
  cout << "   + root product   : "<< argv[2] << endl << flush;
  cout << "   + geometrical bundle : "<< argv[3] << endl << flush;
  cout << "   + bundle segment 1   : "<< argv[4] << endl << flush;

  //
  //1.2--- Creating the Session 
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_EhiCreateMultiBranchableBns_Session";
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
  
  // 1.3--- Creating the main CATProduct document :  
  
  CATDocument *pMainDoc = NULL; // pMainDoc is a pointer to the CATProduct document   

  cout << "> create CATProduct document :"<< MainFile.ConvertToChar() << endl << flush;
  rc = CATDocumentServices::New("CATProduct", pMainDoc);
  if (SUCCEEDED(rc) && (NULL != pMainDoc))
  {
    cout << "> document created " << endl << flush;
  }
  else
  {
    cout << "ERROR in creating main CATProduct document" << endl << flush;
    return 3;
  }
  
  // 1.4--- Retrieving root product of the created document 
  
  CATIProduct* piRootProduct= NULL;// piRootProduct is a handle to document root product
  
  CATIDocRoots * pMainDocRoots = NULL;
  rc = pMainDoc->QueryInterface(IID_CATIDocRoots,(void**) &pMainDocRoots);
  if ( FAILED(rc) || (NULL==pMainDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pMainDocRoots->GiveDocRoots();
  pMainDocRoots->Release();
  pMainDocRoots=NULL;
  
  CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
  if ( pListRootProduct && pListRootProduct->Size() && NULL_var!=spCBU )
  {  
	  rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
	  //
	  if  (SUCCEEDED(rc) && (NULL != piRootProduct))
		  cout << "> root product found in document " << endl << flush;
	  else
	  {
		  cout << "ERROR : Root product not found in document " << endl << flush;
		  return 4;
	  }
  }

  delete pListRootProduct;
  pListRootProduct = NULL;

  if (NULL == piRootProduct) return 4;



  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  
  CATIEleDocServices * piElecDocServices = NULL;
  
  rc = pMainDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
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



  // 2.2--- Creating the GBN CATProduct document :  
  
  CATDocument *pGbnDoc = NULL; // pGbnDoc is a pointer to the CATProduct document  

  cout << "> create CATProduct document :"<< GbnFile.ConvertToChar() << endl << flush;
  rc = CATDocumentServices::New("CATProduct", pGbnDoc);
  if (SUCCEEDED(rc) && (NULL != pGbnDoc))
  {
    cout << "> document created " << endl << flush;
  }
  else
  {
    cout << "ERROR in creating GBN CATProduct document" << endl << flush;
    return 6;
  }
  
  // 2.3--- Retrieving root product of the created document 
  
  CATIProduct* piGbnRootProduct = NULL;// piGbnRootProduct is a handle to document root product
  
  rc = pGbnDoc->QueryInterface(IID_CATIDocRoots,(void**) &pMainDocRoots);
  if ( FAILED(rc) || (NULL==pMainDocRoots) ) return 7;
  pListRootProduct = pMainDocRoots->GiveDocRoots();
  pMainDocRoots->Release();
  pMainDocRoots=NULL;
  
  spCBU = (*pListRootProduct)[1];
  if (pListRootProduct && (pListRootProduct->Size()) && NULL_var != spCBU )
  {  
	  rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piGbnRootProduct );
	  
	  if  (SUCCEEDED(rc) && (NULL != piGbnRootProduct))
		  cout << "> root product found in document " << endl << flush;
	  else
	  {
		  cout << "ERROR : Root product not found in document " << endl << flush;
		  return 7;
	  }
  }
  
  delete pListRootProduct;
  pListRootProduct = NULL;

  if (NULL == piGbnRootProduct) return 7;



  //--------------------------------------------------------------------
  // 3. Creating the Geometrical Bundle.   
  //--------------------------------------------------------------------

  CATIEhiGeoBundle * piGeoBundle = NULL;  // the geometrical bundle
  
  CATIEhiFactory * piEhiFactory = NULL;   // the factory
  
  rc = piGbnRootProduct->QueryInterface(IID_CATIEhiFactory,(void**) &piEhiFactory );
       
  if ( FAILED(rc) || !piEhiFactory )
  {
    cout << "ERROR : retrieving Ehi factory failed " << endl << flush;
    return 8;
  }
  
  rc = piEhiFactory->CreateGeometricalBundle(&piGeoBundle);
  if ( FAILED(rc) || !piGeoBundle )
  {
    cout << "ERROR : creating geometrical bundle failed " << endl << flush;
    return 8;
  }
  else
  {
    cout << "> geometrical bundle created " << endl << flush;

    CATIProduct * piGbnProduct = NULL;
    if ( SUCCEEDED(piGeoBundle->QueryInterface(IID_CATIProduct,(void**)&piGbnProduct)) && piGbnProduct )
    {
      piGbnProduct->SetPartNumber(GbnPartNum);
      piGbnProduct->Release();
      piGbnProduct=NULL;
    }
  }


  //--------------------------------------------------------------------
  // 4. Instanciate the geometrical bundle under the root product
  //--------------------------------------------------------------------
  CATIProduct_var spGBNRoot=piGbnRootProduct;
  CATAssert(!!spGBNRoot);
  
  CATIProduct_var spGBNInstance = piRootProduct->AddProduct(spGBNRoot);   
  if ( NULL_var == spGBNInstance )
  {
    cout << "ERROR : instanciation of gbn under root product failed " << endl << flush;
    return 9;
  }


  //
  //--------------------------------------------------------------------
  // 5. Creating the multi branchable 
  //--------------------------------------------------------------------
  //
  CATIEhiMultiBranchable * piMultiBranchable = NULL;       
  
  rc = piGeoBundle->CreateMultiBranchable (& piMultiBranchable  );

  if ( FAILED(rc) || (NULL == piMultiBranchable))
  {
    cout << "ERROR : creating multi branchable failed " << endl << flush;
    return 10;
  }
  else
  {
	  cout << "> multi branchable created " << endl << flush;
	  
	  //  - set multi branchable part number
	  CATISpecObject * piSpecMultiBns = NULL;
	  if ( SUCCEEDED(piMultiBranchable->QueryInterface(IID_CATISpecObject,(void**)&piSpecMultiBns)) && piSpecMultiBns )
	  {
		  CATIProduct * piMultiBnsProduct = NULL;
		  if ( SUCCEEDED(piMultiBranchable->QueryInterface(IID_CATIProduct,(void**)&piMultiBnsProduct)) && piMultiBnsProduct )
		  {
			  piMultiBnsProduct->SetPartNumber(MultiBns1PartNum);
			  piMultiBnsProduct->Release();
			  piMultiBnsProduct=NULL;
		  }
		  piSpecMultiBns->Release();
		  piSpecMultiBns=NULL;
	  }
  }


  //
  // - 5.1 adding two branchables under the multibranchable
  //       -------------------------------------------------       
  //
  
  // 1- adding second branchable

  CATIEhiBranchable* piNewBranchable=NULL;
  rc = piMultiBranchable->AddBranchable(&piNewBranchable);
  if ( FAILED(rc) || (NULL == piNewBranchable) )
  {
	  cout << "ERROR : problem when creating branchable 2 " << endl << flush;
	  return 11;
  } 
  else
  {
	  cout << ">  branchable 2 created under the multi branchable " << endl << flush;
	  
  }
  
  piNewBranchable->Release();
  piNewBranchable=NULL;


  // 2- adding third branchable
 
  rc = piMultiBranchable->AddBranchable(&piNewBranchable);
  if ( FAILED(rc) || (NULL == piNewBranchable) )
  {
	  cout << "ERROR : problem when creating branchable 3 " << endl << flush;
	  return 12;
  } 
  else
  {
	  cout << ">  branchable 3 created under the multi branchable " << endl << flush;
  }
  
  piNewBranchable->Release();
  piNewBranchable=NULL;
  

  //
  // - 5.2 retrieving the bundle segments from the multibranchable
  //       -------------------------------------------------------       
  //
  
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
	  return 13;
  } 

  if ((NULL_var==(*pListBundleSegment)[1]) || (NULL_var==(*pListBundleSegment)[2])
                                           || (NULL_var==(*pListBundleSegment)[3])) return 13;

  
  CATIEhiBundleSegment * piBundleSegment1 = NULL;
  CATIEhiBundleSegment * piBundleSegment2 = NULL;
  CATIEhiBundleSegment * piBundleSegment3 = NULL;

  spCBU = (*pListBundleSegment)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment1);
  if (FAILED(rc) || (NULL == piBundleSegment1)) return 13;

  spCBU = (*pListBundleSegment)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment2);
  if (FAILED(rc) || (NULL == piBundleSegment2)) return 13;

  spCBU = (*pListBundleSegment)[3];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment3);
  if (FAILED(rc) || (NULL == piBundleSegment3)) return 13;


  delete pListBundleSegment;
  pListBundleSegment=NULL;



  //
  // - 5.3 retrieving the branchables from the multibranchable
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
	  return 14;
  } 

  if ((NULL_var==(*pListBranchable)[1]) || (NULL_var==(*pListBranchable)[2]) 
                                        || (NULL_var==(*pListBranchable)[3]) ) return 14;
                                     
  
  CATIEhiBranchable * piBranchable1 = NULL;
  CATIEhiBranchable * piBranchable2 = NULL;
  CATIEhiBranchable * piBranchable3 = NULL;
  
  spCBU = (*pListBranchable)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchable1);
  if (FAILED(rc) || (NULL == piBranchable1)) return 14;

  spCBU = (*pListBranchable)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchable2);
  if (FAILED(rc) || (NULL == piBranchable2)) return 14;

  spCBU = (*pListBranchable)[3];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchable3);
  if (FAILED(rc) || (NULL == piBranchable3)) return 14;


  delete pListBranchable;
  pListBranchable=NULL;


  // set RefDes on the three branchables

  CATIElecAttrAccess_var hElecAccess;
  CATUnicodeString Elec_Ref_Des("Elec_Ref_Des");
  CATUnicodeString RefDes;

  hElecAccess = piBranchable1;   
  if (NULL_var != hElecAccess)
  {
	  RefDes ="BundleSegment_1";
	  hElecAccess->Set(Elec_Ref_Des ,RefDes);
  }

  hElecAccess = piBranchable2; 
  if (NULL_var != hElecAccess)
  {
	  RefDes ="BundleSegment_2";
	  hElecAccess->Set(Elec_Ref_Des ,RefDes);
  }

  hElecAccess = piBranchable3; 
  if (NULL_var != hElecAccess)
  {
	  RefDes ="BundleSegment_3";
	  hElecAccess->Set(Elec_Ref_Des ,RefDes);
  }
  
  
  //
  // - 5.4 Setting branchables attributes  
  //       ------------------------------  
  //         
  //   + initialize branchable attributes
  //        - build mode : "Slack" . "Length" or "Bend"            
  //             - "Slack" mode  : slack  ( percentage of slack added )
  //             - "Length" mode : length ( imposed length of bundle segment )
  //             - "Bend" mode   : no slack ( minimum length is computed ) 
  //        - diameter 
  //        - minimum bend radius
  //

  //    + set attributes on branchable 1

  CATUnicodeString mode="Slack";

  double slack=2;
  double length=0.;
  double bend_radius=15.;
  double diameter = 3.;

  rc = SetBranchableAttributes ( piBranchable1, mode, slack, length,  bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to branchable 1 failed " << endl << flush;
    return 15;

  }
  else
    cout << "> set attribute to branchable 1 " << endl << flush;

  
  //    + set attributes on branchable 2

  mode="Slack"; 
  slack = 1.5;
  length = 0.;
  bend_radius = 12.;
  diameter = 2.;

  rc = SetBranchableAttributes ( piBranchable2, mode, slack, length, bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to branchable 2 failed " << endl << flush;
    return 16;

  }
  else
    cout << "> set attribute to branchable 2 " << endl << flush;

  
  //    + set attributes on branchable 3
  
  slack = 1;
  length = 0.;
  bend_radius = 25.;
  diameter = 5.;

  rc = SetBranchableAttributes ( piBranchable3, mode, slack, length, bend_radius, diameter );
  if ( FAILED(rc) )
  {
    cout << "ERROR : setting attributes to branchable 3 failed " << endl << flush;
    return 17;

  }
  else
    cout << "> set attribute to branchable 3 " << endl << flush;
 


  //
  // - 5.5 define branchables route  
  //       ------------------------- 
  //   + initialize coordinates for bundle segment constraint points  
  //
  //       - points[3*nb_points] 
  //       - values are given in MKS units
  //
  //   - branchable 1 /  extremity 1   : P1 ( 0. ,   0.  ,0. ) 
  //   - branchable 1 /  extremity 2   : P2 ( 0. , 200.  ,0  )  
  //
  //   - branchable 2 /  extremity 1   : P1 ( 0.   , 0.  , 0.   ) 
  //   - branchable 2 /  second point  : P2 ( 160. , 0.  , 0.   ) 
  //   - branchable 2 /  extremity 2   : P3 ( 300. , 0.  , 50.0 ) 
  //
  //   - branchable 3 /  extremity 1   : P1 ( 0.   ,0.  , 0.   ) 
  //   - branchable 3 /  extremity 2   : P3 ( 0. , -200.  , 40.0 ) 
  //
  //
  
  CATBaseUnknown *   pRoute       = NULL;
  CATIGSMSpline * pGSMSpline = NULL;

  rc = piBranchable1->GetElecCurve(&pRoute);
  if (FAILED(rc) || (NULL == pRoute)) return 18;

  rc = pRoute->QueryInterface(IID_CATIGSMSpline,(void**)&pGSMSpline);
  if (FAILED(rc) || (NULL == pGSMSpline)) return 18;  
  //
  int nb_point = 2;
  double points[9];

  //   +- P1
  points[0]=0.;
  points[1]=0;
  points[2]=0.;
  //
  //   +- P2
  points[3]=0.;
  points[4]=200.;
  points[5]=0.; 

  rc = EhiRouteCurve (pGSMSpline, nb_point, points ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : computing route of first bundle segment failed " << endl << flush;
    return 19;
  }


  pGSMSpline->Release();
  pGSMSpline=NULL;

  pRoute->Release();
  pRoute=NULL;
  

  //  +- define route for branchable 2
  //
      
  rc = piBranchable2->GetElecCurve(&pRoute);
  if (FAILED(rc) || (NULL == pRoute)) return 20;

  rc = pRoute->QueryInterface(IID_CATIGSMSpline,(void**)&pGSMSpline);
  if (FAILED(rc) || (NULL == pGSMSpline)) return 20; 
  
  nb_point = 3;
  //   +- P1
  points[0]=0.;
  points[1]=0.;
  points[2]=0.;
  
  //
  //   +- P2
  points[3]=160.;
  points[4]=0.;
  points[5]=0.;
  
  //
  //   +- P3
  points[6]=300.;
  points[7]=0.;
  points[8]=50.;

  

  rc = EhiRouteCurve ( pGSMSpline, nb_point, points ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : computing route of second bundle segment failed " << endl << flush;
    return 21;
  }
	

  pGSMSpline->Release();
  pGSMSpline=NULL; 

  pRoute->Release();
  pRoute=NULL;
  


  //  +- define route for branchable 3
 
  rc = piBranchable3->GetElecCurve(&pRoute);
  
  if ( FAILED(rc) || (NULL == pRoute)) return 22;

  rc = pRoute->QueryInterface(IID_CATIGSMSpline,(void**)&pGSMSpline);
  if (FAILED(rc) || (NULL == pGSMSpline)) return 22;
  
  nb_point = 2;

  //   +- P1
  points[0]=0.;
  points[1]=0;
  points[2]=0.;
  //
  //   +- P2
  points[3]=0.;
  points[4]=-200.;
  points[5]=40.;
 

  rc = EhiRouteCurve ( pGSMSpline, nb_point, points ); 
  if ( FAILED(rc) )
  {
    cout << "ERROR : computing route of third bundle segment failed " << endl << flush;
    return 23;
  }
 

  pGSMSpline->Release();
  pGSMSpline=NULL;

  pRoute->Release();
  pRoute=NULL;



  //
  //
  // - 5.6 computing multi branchable bundle segment
  //       -----------------------------------------
  // 
  
  rc = piGeoBundle->ComputeMultiBranchable ( piMultiBranchable);
  if ( FAILED(rc)  )
  {
    cout << "ERROR : computing multi branchable failed " << endl << flush;
    return 24;
  }
  else
    cout << "> multi branchable sucessfully computed " << endl << flush;

   

  //--------------------------------------------------------------------
  // 6. Test some methods on a branchable 
  //--------------------------------------------------------------------
  //
  

  //
  // - 6.1 Get the multi branchable of the branchable
  //       ------------------------------------------
  
  CATIEhiMultiBranchable* piMultiBranchableRead=NULL;
  rc = piBranchable1->GetMultiBranchable(&piMultiBranchableRead);
  if (FAILED(rc) || (NULL==piMultiBranchableRead)) return 25;


  //
  // - 6.2 Retrieving the elec curve of the branchable
  //       --------------------------------------------

  CATBaseUnknown* piSplineRead = NULL;
  rc = piBranchable1->GetElecCurve(&piSplineRead);
  if ( SUCCEEDED(rc) && (NULL!=piSplineRead) )
  {
    cout << "> electrical curve found " << endl << flush;	
  }
  else
  {
    cout << "ERROR : electrical curve not found " << endl << flush;	
    return 26;
  }


  //
  // - 6.3 Retrieving the bundle segments of the branchable
  //       ------------------------------------------------

  CATListValCATBaseUnknown_var* pListBNS = NULL;
  rc = piBranchable1->ListBundleSegments(&pListBNS);
  
  //
  if ( SUCCEEDED(rc) && (NULL!=pListBNS) && (1 == pListBNS->Size()) ) 
  {
	  cout << "> number of bundle segment in branchable :"<< pListBNS->Size() <<endl << flush;
  }
  else
  {
	  cout << "ERROR : problem when retrieving bundle segments from branchable " << endl << flush;
	  return 27;
  } 

  delete pListBNS;
  pListBNS=NULL;


  
  //-------------------------------------------------------------------- 
  //  7. Remove a branchable in the multi branchable
  //--------------------------------------------------------------------

  rc = piMultiBranchable->RemoveBranchable(piBranchable2);
 
  if ( FAILED(rc) )
  {
	  cout << "ERROR : problem when removing branchable " << endl << flush;
	  return 28;
  } 
  else
  {
    cout << ">  branchable removed under the multi branchable " << endl << flush;
  }

  

  //--------------------------------------------------------------------
  // 8. Epilogue  
  //--------------------------------------------------------------------
  
  // 8.1-- releasing pointers to interface
  //
  
  piRootProduct->Release(); 
  piGbnRootProduct->Release(); 
  piEhiFactory->Release();  
  piGeoBundle->Release();
  piBranchable1->Release(); 
  piBranchable2->Release();
  piBranchable3->Release();
  piMultiBranchableRead->Release();  
  piBundleSegment1->Release(); 
  piBundleSegment2->Release(); 
  piBundleSegment3->Release(); 
  piSplineRead->Release(); 
  
  // --- always reset pointer value to NULL after release
  piRootProduct=NULL; 
  piGbnRootProduct=NULL; 
  piEhiFactory=NULL;  
  piGeoBundle=NULL;  
  piBranchable1=NULL; 
  piBranchable2=NULL; 
  piBranchable3=NULL;   
  piMultiBranchableRead=NULL;
  piBundleSegment1=NULL; 
  piBundleSegment2=NULL; 
  piBundleSegment3=NULL; 
  piSplineRead=NULL; 


  // 8.2-- saving the documents
  //

  // --- saving multi branchable document
  
  // Retrieving the multi branchable document
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
    return 29;
  }

  rc = CATDocumentServices::SaveAs (*pMultiBnsPartDoc , PathOutput+MultiBns1File );
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

  // --- saving main document
  rc = CATDocumentServices::SaveAs (*pMainDoc , PathOutput+MainFile );
  if (SUCCEEDED(rc))
  {
    cout << "> main document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving document" << endl << flush;
    return 32;
  }


  //
  // 8.3-- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 20;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}



