// COPYRIGHT DASSAULT SYSTEMES 2002

//===============================================================================
//  Abstract of Use Case "CAAEhiProtection":
//  ------------------------------------------------
//
//  This Use Case illustrates how to analyse different type of protection to find
//  the position her extremity in bundle segment. We illustrate also how find the 
//  position of a support on bundle segment. 
//
//===============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//  2. Initializing Electrical Environment 
//  3. Retrieving all Geometrical Bundle under the Root Product 
//  4. Retrieving all Bundle Segments under the Geometrical Bundle 
//     and analyse it 
//  5. Retrieving bundle segment extremities of bundle segment and checking that we 
//     can retrieve the bundle segment where the extremitie is aggregated
//  6. Retrieving all Supports Linked to Bundle Segment 
//  7. Retrieving the distance of each support with each extremity of the bundle segment
//  8. Retrieving the list of protection linked on each bundle segment.
//  9. For each protection finding his distance with each extremity of bundle segment
// 10. Retrieving the Length of protection.
// 11. Retrieving the geometric representation of the protection.
// 12. Retrieving the curve of protection
// 13. Retrieving the list of bundle segment linked on protection
// 14. Epilogue
// 
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document
//  3 - ERROR in getting root product
//  4 - ERROR in initializing electrical environment 
//  5 - ERROR in searching geometrical bundle
//  6 - ERROR in retrieving geometrical bundle
//  7 - ERROR in retrieving bundle segment
//  8 - ERROR in retrieving bundle segment extremity 
//  9 - ERROR in GetBundleSegment she return a bad bundle segment for first extremity
// 10 - ERROR in GetBundleSegment she return a bad bundle segment for second extremity
// 11 - ERROR in retrieving the support linked with bundle segment
// 12 - ERROR in retrieving the location of support with first bundle segment extremity  
// 13 - ERROR in retrieving the location of support with second bundle segment extremity
// 14 - ERROR in retrieving the protection linked with bundle segment
// 15 - ERROR in retrieving the location of protection with first extremity of bundle segment      
// 16 - ERROR in retrieving the location of protection with second extremity of bundle segment      
// 17 - ERROR in retrieving the Length of protection.     
// 18 - ERROR in retrieving the geometric representation of the protection.    
// 19 - ERROR in retrieving the curve of protection.   
// 20 - ERROR in retrieving the list of bundle segment linked with protection .
// 21 - Epilogue   
// 23 - ERROR - Location of extremities of Protections from first extremity of BNS (in MBB1 and MBB2) are not same.

//
//  Running the program:
//  -------------------
// To run this program, you can use the command:
//  mkrun -c "CAAEhiProtection input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the document itself.
//
//
//  You may reference the supplied CATProduct document called "Product1.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAA_EHIProtectionSample directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAA_EHIProtectionSample 
//  directory. 
//
//================================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents
#include "CATIAlias.h"             // extracting alias

// ProductStructure interfaces 
#include "CATIProduct.h"           // managing products  

// GSM interfaces 
#include "CATIGSMSpline.h"         // managing products  

// Knowledge interfaces 
#include "CATICkeInst.h"           // managing products  

// Electrical Harness interfaces
#include "CATIEhiGeoBundle.h"      // browsing geometrical bundles
#include "CATIEhiBundleSegment.h"  // browsing bundle segments
#include "CATIEhiProtection.h"
#include "CATIEhiBnlSegmentExtremity.h"
#include "CATIEhiMultiBranchable.h" //managing MBB
#include "CATIEhiBranchable.h"  //managing Branchable

// Electrical interfaces
#include "CATIEleDocServices.h"    // initializing electrical environement 
#include "CATIElecAttrAccess.h"    // managing electrical attributes 



//=========================================================================================================

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
  
  // --- Creating the Session:  

  CATSession *pSession = NULL;
  
  //variable to check location of protection extremities before and aftere rotation
  double LocationFirstExtremityOfProtectionFrmBNSExtr1_MBB1  = 0.0;
  double LocationSecondExtremityOfProtectionFrmBNSExtr1_MBB1 = 0.0;
  double LocationFirstExtremityOfProtectionFrmBNSExtr1_MBB2  = 0.0;
  double LocationSecondExtremityOfProtectionFrmBNSExtr1_MBB2 = 0.0;
  double LocationFirstExtremityOfProtectionFrmBNSExtr2_MBB1  = 0.0;
  double LocationSecondExtremityOfProtectionFrmBNSExtr2_MBB1 = 0.0;
  double LocationFirstExtremityOfProtectionFrmBNSExtr2_MBB2  = 0.0;
  double LocationSecondExtremityOfProtectionFrmBNSExtr2_MBB2 = 0.0;

  char *sessionName = "CAA_EhiProtection_Session";
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 1;
  }
  
  // --- Opening an existing document 
  //     The input parameter to this sample program must contain 
  //     the entire path and name of the document that is to be opened.  
  
  CATDocument *pDoc = NULL; // pDoc is a pointer to the document 
  
  cout << "> open document :"<< argv[1] << endl << flush;
  rc = CATDocumentServices::OpenDocument(argv[1], pDoc);
  if (SUCCEEDED(rc) && (NULL != pDoc))
  {
    cout << "> document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening document" << endl << flush;
    return 2;
  }

  
  
  // --- Retrieving root product of the opened document 
  
  CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product
  
  CATIDocRoots * pDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
  if ( FAILED(rc) || (NULL==pDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pDocRoots->GiveDocRoots();
  pDocRoots->Release();
  pDocRoots=NULL;
  
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
      return 3;
    }
  }
  
  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  
  CATIEleDocServices * piElecDocServices = NULL;
  
  rc = pDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
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
    return 4;
  }
  
  if ( NULL != piElecDocServices )
  {
    piElecDocServices->Release();
    piElecDocServices=NULL;
  }
  
  //--------------------------------------------------------------------
  // 3. Retrieving all geometrical bundles under the root product 
  //    and Selecting one geometrical bundle  
  //--------------------------------------------------------------------
  
  // --- Retrieving all geometric bundles under root product  
  
  CATListValCATBaseUnknown_var* pListGeoBundle = NULL;
  pListGeoBundle = piRootProduct->GetAllChildren(CATIEhiGeoBundle::ClassName());
  piRootProduct -> Release();
  piRootProduct = NULL ;
  
  int NumberOfGeoBundle = 0;
  if ( (NULL!=pListGeoBundle) && pListGeoBundle->Size() ) 
  {
    NumberOfGeoBundle = pListGeoBundle->Size();	
    cout << "> number of geometrical bundle found in assembly : "<< NumberOfGeoBundle << endl << flush;
  }
  else
  {
    cout << "ERROR : no geometrical bundle found in assembly " << endl << flush;
    return 5;
  }
  
  // --- Selecting first geometrical bundle to analyse
  
  CATIEhiGeoBundle * piGeoBundle = NULL;
  spCBU = (*pListGeoBundle)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiGeoBundle,(void**) &piGeoBundle);
  //
  if ( pListGeoBundle ) delete pListGeoBundle;
  pListGeoBundle=NULL;
  //     
  if ( SUCCEEDED(rc) && NULL!= piGeoBundle)
  { 
    cout << "> select geometrical bundle to analyse " <<endl << flush;
    cout << "   rank in list   :  "<< NumberOfGeoBundle << endl << flush;
    CATIProduct_var  spGeoBundleProduct = piGeoBundle ;
    CATUnicodeString InstanceName ;
    if ( NULL_var != spGeoBundleProduct ) spGeoBundleProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName .ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting to geometrical bundle segment failed " << endl << flush;
    return 6;
  }
  
  //--------------------------------------------------------------------
  // 4. Retrieving all bundle segments under the geometrical bundle 
  //    and for each bundle segment retrieving his extremities. 
  //--------------------------------------------------------------------
  
  // --- Retrieving all bundle segment under geometrical bundle
  //
  CATListValCATBaseUnknown_var* pListBundleSegment = NULL;
  rc = piGeoBundle->ListBundleSegments(&pListBundleSegment);
  piGeoBundle->Release();
  piGeoBundle= NULL ;
  //
  if ( SUCCEEDED(rc) && (NULL!=pListBundleSegment) && pListBundleSegment->Size() ) 
  {
    cout << "> number of bundle segment in geometrical bundle :"<< pListBundleSegment->Size() <<endl << flush;
  }
  else
  {
    cout << "ERROR : no bundle segment found under geometric bundle " << endl << flush;
    return 7;
  }
  
  
  // --- selecting each bundle segment in list  find his electrical curve
  //     and the list of his linked support

  CATIEhiBundleSegment * piBundleSegment = NULL;
  int TailleListBundleSegment = pListBundleSegment->Size() ;
  for(int rank =1 ; rank<=TailleListBundleSegment; rank++)
  {
    spCBU = (*pListBundleSegment)[rank];
    if (NULL_var != spCBU)
      rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment);
    
    if ( SUCCEEDED(rc) && (NULL!=piBundleSegment) )
    {
      cout << endl << flush;
      cout << endl << flush;
      cout << "  ******************************** " <<endl << flush;
      cout << "  ******************************** " <<endl << flush;
      cout << "> Select bundle segment to analyse " <<endl << flush;
      cout << "  Rank in list   :  "<< rank << endl << flush;
      cout << "  ******************************** " <<endl << flush;
      cout << "  ******************************** " <<endl << flush;
      cout << endl << flush;
    }
    else
    {
      cout << "ERROR : no bundle segment found under geometric bundle " << endl << flush;
      if ( pListBundleSegment )delete pListBundleSegment;
      pListBundleSegment=NULL;      
      return 7;
    }
    
    //--------------------------------------------------------------------
    // 5. Retrieving extremities of each bundle segment  
    //--------------------------------------------------------------------
    

    CATIEhiBnlSegmentExtremity * pEhiFirstBnsExtremity = NULL;
    CATIEhiBnlSegmentExtremity * pEhiSecondBnsExtremity = NULL;
    
    rc = piBundleSegment -> GetExtremities (  &pEhiFirstBnsExtremity, &pEhiSecondBnsExtremity);
                                   

    if ( SUCCEEDED(rc) && pEhiFirstBnsExtremity && pEhiFirstBnsExtremity)
    {
      cout << "> Bundle segment extremity of current bundle segment are found " << endl << flush;	
    }
    else
    {
      cout << "ERROR : bundle segment extremity not found " << endl << flush;	

      if ( pEhiFirstBnsExtremity )pEhiFirstBnsExtremity->Release();
      pEhiFirstBnsExtremity=NULL;
      if ( pEhiSecondBnsExtremity )pEhiSecondBnsExtremity->Release();
      pEhiSecondBnsExtremity=NULL;
      if ( pListBundleSegment )delete pListBundleSegment;
      pListBundleSegment=NULL;

      return 8;
    }

    // ----------------------------------------------------------------------------
    // For each extremity check that method GetBundleSegment return piBundleSegment
    // ----------------------------------------------------------------------------
   
    CATIEhiBundleSegment * pEhiBundleSegment = NULL;
    
    // ------------------------
    // Case of First Extremity
    // ------------------------
    rc = pEhiFirstBnsExtremity -> GetBundleSegment (pEhiBundleSegment);

    if (SUCCEEDED(rc) )
    {
      cout << endl << flush;
      cout << "> Method GetBundleSegment retrieve the bundle segment where first extremity is aggregated  " << endl << flush;	
        
      
      if ( pEhiBundleSegment ) pEhiBundleSegment->Release();
      pEhiBundleSegment=NULL;
    }
    else
    {
      cout << "ERROR :  Method GetBundleSegment of CATIEhiBnlSegmentExtremity failed or she return a bad bundle segment " << endl << flush ;
      
      if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
      pEhiFirstBnsExtremity=NULL;
      if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
      pEhiSecondBnsExtremity=NULL;
      if ( pEhiBundleSegment ) pEhiBundleSegment->Release();
      pEhiBundleSegment=NULL;

      if ( pListBundleSegment )delete pListBundleSegment;
      pListBundleSegment=NULL;
      return 9;
    }



    // -------------------------
    // Case of second Extremity
    // -------------------------
    rc = pEhiSecondBnsExtremity -> GetBundleSegment (pEhiBundleSegment);

    if (SUCCEEDED(rc))
    {
      cout << "> Method GetBundleSegment retrieve the bundle segment where second extremity is aggregated   " << endl << flush;
      cout << endl << flush;
      if ( pEhiBundleSegment ) pEhiBundleSegment->Release();
      pEhiBundleSegment=NULL;
    }
    else
    {
      cout << "ERROR :  Method GetBundleSegment of CATIEhiBnlSegmentExtremity failed or she return a bad bundle segment " << endl << flush ;
      
      if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
      pEhiFirstBnsExtremity=NULL;
      if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
      pEhiSecondBnsExtremity=NULL;
      if ( pEhiBundleSegment ) pEhiBundleSegment->Release();
      pEhiBundleSegment=NULL;

      if ( pListBundleSegment )delete pListBundleSegment;
      pListBundleSegment=NULL;
      return 10;
    }



    //--------------------------------------------------------------------
    // 6. Retrieving all supports linked to bundle segment  
    //--------------------------------------------------------------------
    
    // --- compute list of support instances
    // --------------------------------------
    cout << "> compute list of supports linked to bundle segment "<< endl << flush;
   
    CATListValCATBaseUnknown_var* pListInstanceSupport = NULL;
    int numberOfSupport = 0;
    
    rc = piBundleSegment->ListLinkedSupports(&pListInstanceSupport);
    
    if ( FAILED(rc) )  
    { 
      cout << "ERROR : ListLinkedSupports method failed " << endl << flush;

      if ( pListBundleSegment )delete pListBundleSegment;
      pListBundleSegment=NULL;
      
      if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
      pEhiFirstBnsExtremity=NULL;

      if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
      pEhiSecondBnsExtremity=NULL;

      return 11;
    }
    if ( (NULL!=pListInstanceSupport) && pListInstanceSupport->Size() ) 
    {
      numberOfSupport=pListInstanceSupport->Size();
      cout << "   number of support instances found : "<< numberOfSupport << endl << flush;
    }
    else
    {
      cout << "WARNING : no support found for this bundle segment " << endl << flush;
    }
    
    // -----------------------------------------------------------------------------------
    // 7 Retrieving the distance of each support with each extremity of the bundle segment
    // -----------------------------------------------------------------------------------


    // < display instance names >
    CATIProduct* piInstanceProduct = NULL;
    CATUnicodeString InstanceName = "unknown";
    int i;
    for ( i =1; i<=numberOfSupport; i++ )
    {
      spCBU = (*pListInstanceSupport)[i];
      if (NULL_var != spCBU)
        rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
      if ( NULL != piInstanceProduct ) piInstanceProduct->GetPrdInstanceName(InstanceName);		
      cout << "The support    "<<i<<" has the instance name :  "<<InstanceName.ConvertToChar()<<endl<< flush;

      // retrieve the location of this support with the first extremity of bundle segment
      // --------------------------------------------------------------------------------
      double LocationSupport_FirstExt = 0.0;
      rc = piBundleSegment->GetLocationSupport(pEhiFirstBnsExtremity, piInstanceProduct,LocationSupport_FirstExt);
      if(SUCCEEDED(rc))
      {
         cout << "The location of support with first bundle segment extremity  is : "<< LocationSupport_FirstExt << endl << flush;

      }
      else
      {
        cout << "   ERROR  : Method GetLocationSupport failed "<<  endl << flush;

        if ( piInstanceProduct ) piInstanceProduct->Release();
        piInstanceProduct = NULL;
        
        if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
        pEhiFirstBnsExtremity=NULL;
        
        if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
        pEhiSecondBnsExtremity=NULL;       
        
        if ( pListBundleSegment )delete pListBundleSegment;
        pListBundleSegment=NULL;
        
        if ( pListInstanceSupport )delete pListInstanceSupport;
        pListInstanceSupport=NULL;
        
        return 12 ;
      }

      // retrieve the location of this support with the second extremity of bundle segment
      // --------------------------------------------------------------------------------
      double LocationSupport_SecondExt = 0.0;
      rc = piBundleSegment->GetLocationSupport(pEhiSecondBnsExtremity, piInstanceProduct,LocationSupport_SecondExt);
      if(SUCCEEDED(rc))
      {
         cout << "The location of support with second bundle segment extremity : "<< LocationSupport_SecondExt << endl << flush;
         cout << endl << flush;

      }
      else
      {
        cout << "   ERROR  : Method GetLocationSupport failed "<<  endl << flush;

        if ( piInstanceProduct ) piInstanceProduct->Release();
        piInstanceProduct = NULL;
        
        if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
        pEhiFirstBnsExtremity=NULL;
        
        if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
        pEhiSecondBnsExtremity=NULL;     
        
        if ( pListBundleSegment )delete pListBundleSegment;
        pListBundleSegment=NULL;
        
        if ( pListInstanceSupport )delete pListInstanceSupport;
        pListInstanceSupport=NULL;
        
        return 13 ;
      }

      if ( NULL != piInstanceProduct ) piInstanceProduct->Release();
      piInstanceProduct = NULL;
    }		
    
    if ( pListInstanceSupport )   delete pListInstanceSupport;
    pListInstanceSupport = NULL;



    // -------------------------------------------------------------------------------
    // 8  For each bundle segment, I retrieve le list of linked protection  
    // -------------------------------------------------------------------------------
     
    CATListValCATBaseUnknown_var * pListOfLinked_PROTECTION = NULL;
    int NumberOfProtection = 0;

    rc = piBundleSegment->ListLinkedProtections( & pListOfLinked_PROTECTION ) ;
    
    if ( FAILED(rc) )  
    { 
    
      cout << "ERROR : ListLinkedProtections method failed " << endl << flush;
      
      if ( pListBundleSegment )delete pListBundleSegment;
      pListBundleSegment=NULL;
      
      if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
      pEhiFirstBnsExtremity=NULL;
      
      if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
      pEhiSecondBnsExtremity=NULL;
      
      return 14;
    }
    if ( (NULL!=pListOfLinked_PROTECTION) && pListOfLinked_PROTECTION->Size() ) 
    {
      NumberOfProtection=pListOfLinked_PROTECTION->Size();
      cout << "Number of protection linked on bundle segment found : "<< NumberOfProtection << endl << flush;
    }
    else
    {
      cout << "WARNING : no protection found for this bundle segment " << endl << flush;
    }

    //get MBB
    CATUnicodeString strMBBAlias;
    if(NULL != piBundleSegment)
    {
      CATIEhiMultiBranchable  *pMultiBranchable = NULL;
      CATIEhiBranchable       *pBranchable      = NULL;

      rc=  piBundleSegment -> GetBranchable(&pBranchable);
      if (SUCCEEDED(rc) && (NULL != pBranchable))
      {
        rc = pBranchable -> GetMultiBranchable(&pMultiBranchable);
        if (SUCCEEDED(rc) && (NULL != pMultiBranchable))
        {
          CATIAlias_var  hMBBAlias(pMultiBranchable);
          if(NULL_var != hMBBAlias)
          {
            strMBBAlias = hMBBAlias->GetAlias(); 
          }
        }
      }
      if(pMultiBranchable)pMultiBranchable->Release();pMultiBranchable = NULL;
      if(pBranchable)pBranchable->Release();pBranchable = NULL;
    }


    // --------------------------------------------------------------------------------
    // 9 For each protection I found his distance with each extremity of bundle segment
    // --------------------------------------------------------------------------------

    int j = 0;
    CATIEhiProtection * pEhiProtection = NULL;
    CATIProduct * pPrdProtection = NULL;
    CATUnicodeString InstanceNameProtection = "unknown";
    
    for(j = 1 ; j<=NumberOfProtection ; j++ )
    {
      spCBU = (*pListOfLinked_PROTECTION)[j];
      if (NULL_var != spCBU)
      {
    
        rc =  spCBU ->QueryInterface(IID_CATIEhiProtection,(void**) & pEhiProtection);
        
        rc =  spCBU ->QueryInterface(IID_CATIProduct,(void**) & pPrdProtection); 
        
        if ( NULL != pPrdProtection ) pPrdProtection->GetPrdInstanceName(InstanceNameProtection);		
        
        cout << "The protection     "<<i<<" are the current instance name :  "<<InstanceNameProtection.ConvertToChar()<<endl<< flush;

        if(pPrdProtection) pPrdProtection->Release();
        pPrdProtection = NULL;
      }
      if(pEhiProtection)
      {
        // Location With First extremity of bundle segment 
        // -----------------------------------------------
        double LocationFirstExtremityOfProtection  = 0.0;
        double LocationSecondExtremityOfProtection = 0.0;
       
        rc = pEhiProtection->GetLocationExtremities(  pEhiFirstBnsExtremity ,
                                                      LocationFirstExtremityOfProtection ,
                                                      LocationSecondExtremityOfProtection);
       
        if(SUCCEEDED(rc))
        {
          cout << "   Location between first extremity of bundle segment and first extremitie of current protection : "<< LocationFirstExtremityOfProtection << endl << flush;
          cout << "   Location between first extremity of bundle segment and second extremitie of current protection : "<< LocationSecondExtremityOfProtection << endl << flush;
          cout << endl << flush;

          if(2 == strMBBAlias.Compare("MBB1"))
          {
            //save the location of extremities         
            LocationFirstExtremityOfProtectionFrmBNSExtr1_MBB1 = LocationFirstExtremityOfProtection;
            LocationSecondExtremityOfProtectionFrmBNSExtr1_MBB1 = LocationSecondExtremityOfProtection;
          }
          else if(2 == strMBBAlias.Compare("MBB2"))
          {
            //save the location of extremities         
            LocationFirstExtremityOfProtectionFrmBNSExtr1_MBB2 = LocationFirstExtremityOfProtection;
            LocationSecondExtremityOfProtectionFrmBNSExtr1_MBB2 = LocationSecondExtremityOfProtection;
          }
        }
        else
        {
           
          cout << "ERROR : CATIEhiProtection::GetLocationExtremities() Failed " << endl << flush;
          
          if(pEhiProtection) pEhiProtection->Release();
          pEhiProtection = NULL;
          
          if ( pListBundleSegment )delete pListBundleSegment;
          pListBundleSegment=NULL;
          
          if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
          pEhiFirstBnsExtremity=NULL;
          
          if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
          pEhiSecondBnsExtremity=NULL;
          
          return 15 ;
        }


        // Location With Second Extremity Of BundleSegment
        // ----------------------------------------------
        rc = pEhiProtection->GetLocationExtremities(  pEhiSecondBnsExtremity ,
                                                      LocationFirstExtremityOfProtection ,
                                                      LocationSecondExtremityOfProtection);
        if(SUCCEEDED(rc))
        {
          cout << "   Location between second extremity of bundle segment and first extremitie of current protection : "<< LocationFirstExtremityOfProtection << endl << flush;
          cout << "   Location between second extremity of bundle segment and second extremitie of current protection : "<< LocationSecondExtremityOfProtection << endl << flush;
          cout << endl << flush;
          if(2 == strMBBAlias.Compare("MBB1"))
          {
            //save the location of extremities         
            LocationFirstExtremityOfProtectionFrmBNSExtr2_MBB1 = LocationFirstExtremityOfProtection;
            LocationSecondExtremityOfProtectionFrmBNSExtr2_MBB1 = LocationSecondExtremityOfProtection;
          }
          else if(2 == strMBBAlias.Compare("MBB2"))
          {
            //save the location of extremities         
            LocationFirstExtremityOfProtectionFrmBNSExtr2_MBB2 = LocationFirstExtremityOfProtection;
            LocationSecondExtremityOfProtectionFrmBNSExtr2_MBB2 = LocationSecondExtremityOfProtection;
          }
        }
        else
        {
           cout << "ERROR : CATIEhiProtection::GetLocationExtremities() Failed " << endl << flush;
           
           if(pEhiProtection) pEhiProtection->Release();
           pEhiProtection = NULL;
           
           if ( pListBundleSegment )delete pListBundleSegment;
           pListBundleSegment=NULL;
           
           if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
           pEhiFirstBnsExtremity=NULL;
           
           if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
           pEhiSecondBnsExtremity=NULL;
           
           return 16 ;
        }
        
        // ---------------------------------------
        // 10 Retrieving the Length of protection
        // ---------------------------------------
        double Length_Protection = 0.0 ;
        
        rc = pEhiProtection ->ComputeLength(Length_Protection);

        if (SUCCEEDED(rc))
        {
           cout << "  The length of protection is  :  "<< Length_Protection << endl << flush;         
        }
        else 
        {
           cout << "ERROR : CATIEhiProtection::ComputeLength() Failed " << endl << flush;

           if(pEhiProtection) pEhiProtection->Release();
           pEhiProtection = NULL;
           
           if ( pListBundleSegment )delete pListBundleSegment;
           pListBundleSegment=NULL;
           
           return 17 ;
        }

        // --------------------------------------------------------------
        //  11 Retrieving the geometric representation of the protection
        // --------------------------------------------------------------
        CATListValCATBaseUnknown_var * pListRepresentation = NULL;

        rc = pEhiProtection -> GetRepresentation (&pListRepresentation );
        
        if ( FAILED(rc) )  
        { 
          cout << "ERROR : The protection representation does not exist " << endl << flush;
          
          if ( pListBundleSegment )delete pListBundleSegment;
          pListBundleSegment=NULL;
          
          if ( pListRepresentation )delete pListRepresentation;
          pListRepresentation=NULL;
          
          if(pEhiProtection) pEhiProtection->Release();
          pEhiProtection = NULL;

          return 18;
        }
        else if ( (NULL!=pListRepresentation) && pListRepresentation->Size() ) 
        {
          cout << "   number of representation found : "<< pListRepresentation->Size() << endl << flush;
          
          if ( pListRepresentation )delete pListRepresentation;
          pListRepresentation=NULL;

        }

        // ------------------------------------- 
        // 12 Retrieving the curve of protection
        // --------------------------------------
       CATBaseUnknown * pCurve = NULL;

       rc = pEhiProtection -> GetCurve (&pCurve );
       
       if(SUCCEEDED(rc) && pCurve)
       {
         cout << "   The curve of protection is found " << endl << flush;
         if(pCurve) pCurve->Release();
         pCurve = NULL;
       }
       else
       {
          cout << "ERROR : The protection curve  not found " << endl << flush;
          
          if ( pListBundleSegment )delete pListBundleSegment;
          pListBundleSegment=NULL;
          
          if(pEhiProtection) pEhiProtection->Release();
          pEhiProtection = NULL;
          
          return 19;          
       }

       // --------------------------------------------------------------
       // 13 Retrieving the list of bundle segment linked on protection
       // --------------------------------------------------------------
       CATListValCATBaseUnknown_var * pListLinkedBundleSegment = NULL;
       int NumberOfLinkedBns = 0;

       rc =  pEhiProtection-> ListBundleSegments (pListLinkedBundleSegment);
       
       if ( FAILED(rc) )  
       { 
         cout << "ERROR : ListBundleSegments method failed " << endl << flush;
         
         if ( pListBundleSegment ) delete pListBundleSegment;
         pListBundleSegment=NULL;
         
         if ( pListLinkedBundleSegment ) delete pListLinkedBundleSegment;
         pListLinkedBundleSegment=NULL;
         
         if(pEhiProtection) pEhiProtection->Release();
         pEhiProtection = NULL;
         
         return 20;
       }
       else if ( (NULL!=pListLinkedBundleSegment) && pListLinkedBundleSegment->Size() ) 
       {
         NumberOfLinkedBns=pListLinkedBundleSegment->Size();
         
         cout << "   number of bundle segment linked with protection : "<< NumberOfLinkedBns << endl << flush;
         cout << endl << flush;
         
         if ( pListLinkedBundleSegment ) delete pListLinkedBundleSegment;
         pListLinkedBundleSegment=NULL;
       }        
      }
    
      if(pEhiProtection) pEhiProtection->Release();
      pEhiProtection = NULL;

    } // end for j

    if(pListOfLinked_PROTECTION) delete pListOfLinked_PROTECTION ;
    pListOfLinked_PROTECTION = NULL;
    
    if ( pEhiFirstBnsExtremity ) pEhiFirstBnsExtremity->Release();
    pEhiFirstBnsExtremity=NULL;
    
    if ( pEhiSecondBnsExtremity ) pEhiSecondBnsExtremity->Release();
    pEhiSecondBnsExtremity=NULL;

    if(piBundleSegment)  piBundleSegment -> Release();
    piBundleSegment = NULL;
    
  } // end for rank


  
  if ( pListBundleSegment )delete pListBundleSegment;
  pListBundleSegment=NULL;
  
  // 
  //--------------------------------------------------------------------
  // 14. Epilogue  
  //--------------------------------------------------------------------
  
  // 14.1-- releasing pointers to interface
  //

  //
  // 14.2-- removing document from session 
  rc = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 21;
  }
  // 14.3-- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 22;
  }

  //check if length of Protection extemities are same  in MBB1 or MBB2
  double tolerance = 0.000001;
  
  double diff1 = LocationFirstExtremityOfProtectionFrmBNSExtr1_MBB1  - 0.0000000;
  double diff2 = LocationSecondExtremityOfProtectionFrmBNSExtr1_MBB1 - 500.0000000;
  double diff3 = LocationFirstExtremityOfProtectionFrmBNSExtr1_MBB2  -  0.0000000;
  double diff4 = LocationSecondExtremityOfProtectionFrmBNSExtr1_MBB2 - 500.0000000;
  double diff5 = LocationFirstExtremityOfProtectionFrmBNSExtr2_MBB1  - 500.0000000;  
  double diff6 = LocationSecondExtremityOfProtectionFrmBNSExtr2_MBB1 - 0.0000000; 
  double diff7 = LocationFirstExtremityOfProtectionFrmBNSExtr2_MBB2  - 500.0000000;
  double diff8 = LocationSecondExtremityOfProtectionFrmBNSExtr2_MBB2 - 0.0000000;

  if( 0 > diff1)
    diff1 = (-1)*diff1;
  if( 0 > diff2)
    diff2 = (-1)*diff2;
  if( 0 > diff3)
    diff3 = (-1)*diff3;
  if( 0 > diff4)
    diff4 = (-1)*diff4;
  if( 0 > diff5)
    diff5 = (-1)*diff5;
  if( 0 > diff6)
    diff6 = (-1)*diff6;
  if( 0 > diff7)
    diff7 = (-1)*diff7;
  if( 0 > diff8)
    diff8 = (-1)*diff8;
  
  if((tolerance < diff1) 
    || (tolerance < diff2 )
    || (tolerance < diff3 )
    || (tolerance < diff4 )
    || (tolerance < diff5 )
    || (tolerance < diff6 )
    || (tolerance < diff7 )
    || (tolerance < diff8 ))
  {
    cout << "Location of extremities of Protections in MBB1 and MBB2 are not same"<< endl << flush;
    return 23;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}















