/**
 * @quickReview GZU 12:04:09 IR-149503:Fou.CATProduct was missing in the documents. Fou.CATProduct is now added.
 */
/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 2004
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Analyze degrees of freedom of a product components in a constraint network
//
// Type            : Batch program
// Inputs          : Product file
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Loading document in session                (1)
//                   o Scanning the components of Root Product    (2)
//                   o Search for a component named :"DoF"        (3)
//                   o Anaylyzing de degrees of freedom of "DoF"  (4)

// Return codes :
//
//  10 - File could not be found or has problem  
//  11 - QI on CATIDocRoots failed
//  12 - Root product could not be found
//
//  20 - No component called DoF was found
//
// use: CAAAsmAnalyzeDegrees xxx.CATProduct
//
//============================================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATLib.h"
#include "CATUnicodeString.h" 
#include "CATLISTV_CATBaseUnknown.h"

// ConstraintModeler Framework
#include "CATIDegreesOfFreedom.h"

// ObjectModelerBase Framework
#include "CATDocumentServices.h"   // to open and close document
#include "CATSessionServices.h"    // to open and close session
#include "CATIDocRoots.h"          // to identify the root of a document
#include "LifeCycleObject.h"       // to delete objects
#include "CATDocument.h"           // to work with documents
#include "CATIAlias.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"
 

// ProductStructure Framework
#include "CATIProduct.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{

  //--------------------------------
  // 1 - Loading document in session
  //--------------------------------

  printf( " Test CAAAnalyzeFreedoms \n" );
  printf( " ======================= \n" );

  // Checking arguments
  if(2 != iArgc)
  { return 10; } // wrong number of arguments
  
  // Opening a session  
  CATSession* pSession = NULL;
  HRESULT rc = Create_Session("Session_ASSEMBLY",pSession);
  printf(  "Session Created\n" );  

  // Opening a document
  CATDocument * pProductDocument = NULL;
  rc = CATDocumentServices::OpenDocument(iArgv[1],pProductDocument);

  if ( FAILED(rc) || (NULL == pProductDocument) )
  {
    printf(  " ERROR: Document not found\n" );
    return 11;
  }
  printf(  "Document opened\n" );
  
  // Searching the root product  
  CATIDocRoots *piDocRootsOnDoc = NULL;
  rc = pProductDocument->QueryInterface(IID_CATIDocRoots, (void**) &piDocRootsOnDoc);
  if ( FAILED(rc) )
  {
    printf(  " ERROR: QI on CATIDocRoots failed\n" );
    return 11;
  }
  CATListValCATBaseUnknown_var *pRootProducts = piDocRootsOnDoc->GiveDocRoots();
  CATIProduct_var spRootProduct = NULL_var;
  if( NULL != pRootProducts )
  {  
    if( 0 != pRootProducts->Size() )
    {
      spRootProduct = (*pRootProducts)[1];
      delete pRootProducts;
      pRootProducts = NULL;
    }  
    piDocRootsOnDoc->Release();
    piDocRootsOnDoc = NULL;
  }
  if (NULL_var == spRootProduct)
  {
    printf(  " ERROR: No root product !!\n" );
    return 12; 
  }
  printf( "Root product found successfully\n" );

  //---------------------------------
  // 2 - Scanbning the Root components
  //---------------------------------------

  CATIProduct_var P_i;
  int Found= 0;
  CATUnicodeString strDoF = "DoF";
  CATListValCATBaseUnknown_var * Components = spRootProduct->GetChildren();
  if( Components!= NULL )
  {
    int NChildren = Components->Size( );
    for( int ch_i = 1 ; ch_i <= NChildren ; ch_i++ )
    {
      P_i = (*Components)[ch_i];
      CATIAlias_var Alias = P_i;
      if( NULL_var != Alias )
      {
        CATUnicodeString Str= Alias->GetAlias();
        if( Str == strDoF)
        { Found=1; break;}
      } 
      
    }
    delete Components;
    Components = NULL;
  }
  if(Found)
  {
//  ---------------------------------------------------------
// 3 - a component 'DoF' was found : analyze of its freedoms
//  ---------------------------------------------------------

	  printf(  "found a component named 'DoF' under root product\n" );
	  int oNbDegreesOfFreedom=0;
	  CATIDegreesOfFreedom_var Degrees = P_i;
	  if(Degrees!=NULL_var)
	  {
		  CATDoFStatusEnum oValidity;
		  HRESULT hr=Degrees->GetNbDegreesOfFreedom(oValidity,oNbDegreesOfFreedom);
		  if(oValidity==DoF_Acceptable)
		  {
			  printf(  "This component 'DoF' could be analyzed and has %d degree(s) of freedom which are (is) :\n", oNbDegreesOfFreedom );
			  for(int i=1;i<=oNbDegreesOfFreedom;i++)
			  {
				  CATDoFTypeEnum oType;
				  double oData[]={0.,0.,0.,0.,0.,0.,0.};
				  HRESULT hr = Degrees->GetDegreesOfFreedom(i,oType,oData);
				  if(oType==DoF_Translation)
				  {
					  printf( "  degree number %d = TRANSLATION \n", i );
					  printf( "        -> vector = %d  %d  %d\n", oData[0], oData[1], oData[2] ); 
				  }
				  else if(oType==DoF_Rotation)
				  {
					  printf( "  degree number %d = ROTATION\n", i );
					  printf( "        -> direction of axis = %d  %d  %d\n", oData[0], oData[1], oData[2] ); 
					  printf( "        -> pole      of axis = %d  %d  %d\n", oData[3], oData[4], oData[5] ); 
				  }
				  else if(oType==DoF_Screw)
				  {
					  printf( "  degree number %d = SCREW ", i );
					  printf( "        -> direction of axis = %d  %d  %d\n", oData[0], oData[1], oData[2] ); 
					  printf( "        -> pole      of axis = %d  %d  %d\n", oData[3], oData[4], oData[5] ); 
					  printf( "        -> pitch of screw    = %d\n", oData[6] ); 
				  }
				  else 
				  {	  printf( "  ERROR in evaluating degree number %d\n", i ); }
			  }
		  }
		  else if(oValidity==DoF_KONotUpdated)
		  {  printf(  " the component 'DoF' could not be analyzed because product is not updated\n" ); }
		  else if(oValidity==DoF_KONoFather || oValidity==DoF_KONotABloc ||oValidity==DoF_KOOther)
		  {	  } 
	  }
	  
	  else
	  { printf(  " ERROR: the component named  'DoF' is not responding to CATIDegreesOfFreedDom interface-\n" ); }
  }  
  else
  {
	  printf(  " ERROR: No component 'DoF' found under the root product\n" );
	  return 20;
  }
  
  
  //-------------
  // - Exiting
  //------------
  
  // closing document
  CATDocumentServices::Remove(*pProductDocument);
  
  // closing session
  Delete_Session("Session_ASSEMBLY");
  printf(  "Session cleaned succesfully\n" );
  printf(  "Normal End\n" );
  printf(  "Return Code = %d", rc );

  return rc;
}
