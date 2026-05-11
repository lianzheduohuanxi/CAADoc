// COPYRIGHT DASSAULT SYSTEMES 2001

//=============================================================================
//  Abstract of Use Case "CAAEhiGeoBundle":
//  ---------------------------------------
//
//  This Use Case illustrates how retrieve and analyse geometric bundle 
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//  2. Initializing Electrical Environment 
//  3. Retrieving all Geometrical Bundle under the Root Product 
//     and Selecting one to analyse 
//  4. Retrieving all Bundle Segments under the Geometrical Bundle 
//     and Selecting one to analyse 
//  5 .Retrieving Electrical Curve ( Bundle Segment route ) 
//  6. Retrieving all Supports Linked to Bundle Segment 
//  7. Retrieving Electrical Attributes of Bundle Segment
//  8. Epilogue.
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
//  8 - ERROR in retrieving electrical curve
//  9 - ERROR in retrieving supports linked to bundle segment
// 10 - ERROR in retrieving handle to CATIElecAttrAccess for bundle segment
// 11 - ERROR in retrieving handle to CATIElecAttrAccess for bundle segment
// 12 - ERROR in retrieving list bundle segment attributes
// 13 - ERROR in retrieving attribute value  
// 14 - ERROR in removing document  
// 15 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiGeoBundle input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the document itself.
//
//
//  You may reference the supplied CATProduct document called "CAA_EhiSample.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic directory. 
//
//
//=============================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents

// ProductStructure interfaces 
#include "CATIProduct.h"           // managing products  

// GSM interfaces 
#include "CATIGSMSpline.h"         // managing products  

// Knowledge interfaces 
#include "CATICkeInst.h"           // managing products  

// Electrical Harness interfaces
#include "CATIEhiGeoBundle.h"      // browsing geometrical bundles
#include "CATIEhiBundleSegment.h"  // browsing bundle segments

// Electrical interfaces
#include "CATIEleDocServices.h"    // initializing electrical environement 
#include "CATIElecAttrAccess.h"    // managing electrical attributes 



int main (int argc, char * argv[] )
{ 
  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  
  // --- Creating the Session:  A session must always be created in a batch
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_EhiGeoBundle_Session";
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
  
  // --- Selecting last geometrical bundle to analyse
  
  
  CATIEhiGeoBundle * piGeoBundle = NULL;
  spCBU = (*pListGeoBundle)[NumberOfGeoBundle];
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
  //    and Selecting one bundle segment 
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
  
  // --- selecting first bundle segment in list 

  CATIEhiBundleSegment * piBundleSegment = NULL;
  
  int rank = 1;
  spCBU = (*pListBundleSegment)[rank];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment);
  if ( pListBundleSegment )delete pListBundleSegment;
  pListBundleSegment=NULL;
  
  if ( SUCCEEDED(rc) && (NULL!=piBundleSegment) )
  {
    cout << "> select bundle segment to analyse " <<endl << flush;
    cout << "   rank in list   :  "<< rank << endl << flush;
    CATIProduct_var  spBundleSegmentProduct = piBundleSegment;
    CATUnicodeString InstanceName ;
    if ( NULL_var != spBundleSegmentProduct ) spBundleSegmentProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName .ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : no bundle segment found under geometric bundle " << endl << flush;
    return 7;
  }
  
  //--------------------------------------------------------------------
  // 5. Retrieving Electrical Curve ( Bundle Segment route )  
  //--------------------------------------------------------------------
  
  
  CATIGSMSpline * piSpline = NULL;
  //
  rc = piBundleSegment->GetElecCurve(&piSpline);
  if ( SUCCEEDED(rc) && (NULL!=piSpline) )
  {
    cout << "> electrical curve found " << endl << flush;	
    piSpline->Release();
    piSpline=NULL;
  }
  else
  {
    cout << "ERROR : electrical curve not found " << endl << flush;	
    return 8;
  }
  
  
  //--------------------------------------------------------------------
  // 6. Retrieving all supports linked to bundle segment  
  //--------------------------------------------------------------------
  
  // --- compute list of support instances
  cout << "> compute list of supports linked to bundle segment "<< endl << flush;
  CATListValCATBaseUnknown_var* pListInstanceSupport = NULL;
  int numberOfSupport = 0;
  rc = piBundleSegment->ListLinkedSupports(&pListInstanceSupport);
  if ( FAILED(rc) )  
  { 
    cout << "ERROR : ListLinkedSupports method failed " << endl << flush;
    return 9;
  }
  if ( (NULL!=pListInstanceSupport) && pListInstanceSupport->Size() ) 
  {
    numberOfSupport=pListInstanceSupport->Size();
    cout << "   number of support instances found : "<< numberOfSupport << endl << flush;
  }
  else
  {
    cout << "ERROR : no support found " << endl << flush;
    return 9;
  }
  
  // < display instance names >
  CATIProduct* piInstanceProduct = NULL;
  CATUnicodeString InstanceName = "unknown";
  int i;
  for ( i =1; i<=numberOfSupport; i++ )
  {
    spCBU = (*pListInstanceSupport)[i];
    if (NULL_var != spCBU)
      spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
    if ( NULL != piInstanceProduct ) piInstanceProduct->GetPrdInstanceName(InstanceName);		
    cout << "     "<<i<<" instance name :  "<<InstanceName.ConvertToChar()<<endl<< flush;
    if ( NULL != piInstanceProduct ) piInstanceProduct->Release();		
    piInstanceProduct = NULL;
    InstanceName = "unknown";
  }		
  
  cout << "> compute number of support references  "<< endl << flush;
  CATListValCATBaseUnknown_var* pListReferenceSupport = new CATLISTV(CATBaseUnknown_var);
  
  if ( NULL == pListReferenceSupport ) 
  {
    cout << "ERROR : creation of list of reference failed " << endl << flush;
    return 10;
  }
  
  // --- compute list of support references 
  cout << "   get list of reference  "<< endl << flush;
  int numberOfReference = 0;
  for ( i=1; i<=numberOfSupport; i++ )
  {
    spCBU = (*pListInstanceSupport)[i];
    if (NULL_var != spCBU)
      spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
    if ( NULL !=  piInstanceProduct )
    {
      CATIProduct_var spReferenceProduct = piInstanceProduct->GetReferenceProduct();
      if ( NULL_var !=  spReferenceProduct ) pListReferenceSupport->Append(spReferenceProduct);
      piInstanceProduct->Release();
      piInstanceProduct = NULL;
    }
  }
  cout << "   remove duplicated objects in reference list "<< endl << flush;
  pListReferenceSupport->RemoveDuplicates();
  numberOfReference  = pListReferenceSupport->Size();
  cout << "   number of support references found : "<< numberOfReference  << endl << flush;
  
  
  // < display reference part numbers >
  CATIProduct* piReferenceProduct = NULL;
  CATUnicodeString PartNumber = "unknown";
  for ( i =1; i<=numberOfReference; i++ )
  {
    spCBU = (*pListReferenceSupport)[i];
    if (NULL_var != spCBU)
      spCBU->QueryInterface(IID_CATIProduct,(void**) &piReferenceProduct);
    if ( NULL != piReferenceProduct )
    {
      PartNumber=piReferenceProduct->GetPartNumber();
      cout << "     "<<i<<" part number :  "<<PartNumber.ConvertToChar()<<endl<< flush;
      piReferenceProduct->Release();
      piReferenceProduct = NULL;
    }
    PartNumber = "unknown";
  }
  
  
  
  if ( pListInstanceSupport )   delete pListInstanceSupport;
  pListInstanceSupport = NULL;
  if ( pListReferenceSupport ) delete pListReferenceSupport;
  pListReferenceSupport = NULL;
  
  
  //--------------------------------------------------------------------
  // 7. Retrieving electrical attributes of bundle segment 
  //--------------------------------------------------------------------
  
  cout << "> get electrical attributes on bundle segment " << endl << flush;	
  //
  CATIElecAttrAccess * piElecAttribute = NULL;
  piBundleSegment->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttribute);
  if ( NULL != piBundleSegment ) piBundleSegment->Release();
  piBundleSegment = NULL;
  
  if ( FAILED(rc) || (NULL==piElecAttribute) )
  {
    cout << "ERROR : cannot get handle to CATIElecAttrAccess on bundle segment " << endl << flush;
    return 11;
  }
  
  // -- list attributes on object
  cout << "   get list of attributes of bundle segment "<< endl << flush;
  CATListValCATUnicodeString* pAttNameList = NULL; 
  //
  rc = piElecAttribute->ListAttributeNames ( pAttNameList );
  if ( FAILED(rc) )
  {
    cout << "ERROR : ListAttributeNames failed on bundle segment " << endl << flush;
    return 12;
  }
  if (  (NULL!=pAttNameList) && (pAttNameList->Size()) ) 
  {
    int numberOfAttributes=pAttNameList->Size();
    cout << "   number of attributes found : "<< numberOfAttributes <<endl<< flush;
    for ( int i =1; i<=numberOfAttributes; i++ )
    {
      cout << "     "<<i<<"  attribute name :  "<< (*pAttNameList)[i].ConvertToChar()<<endl<< flush;
    }		
  }
  else
  {
    cout << "ERROR : no electrical attribute found on bundle segment " << endl << flush;
    return 12;
  }
  if ( NULL != pAttNameList ) delete pAttNameList;
  pAttNameList=NULL;

  // -- get attribute 
  CATUnicodeString AttributeToRead = "Elec_LengthOUT";
  double  bns_length = 0.;
  CATICkeInst_var spCKEvalue ;
  cout << "   get length of bundle segment ( MKSA unit system ) "<<endl << flush;
  cout << "       . get value (MKSA) of attribute "<< AttributeToRead.ConvertToChar() <<endl << flush;
  rc = piElecAttribute->Get(AttributeToRead,spCKEvalue);
  if ( SUCCEEDED(rc) )
  {
    if ( NULL_var != spCKEvalue ) bns_length = spCKEvalue->AsReal();
    cout << "       . attribute value is : " <<bns_length <<" meters "<< endl << flush;
  }
  else
  {
    cout << "ERROR : CATIElecAttrAccess::Get method failed on bundle segment " << endl << flush;
    return 13;
  }
  
  if ( NULL != piElecAttribute ) piElecAttribute->Release();
  piElecAttribute = NULL;
  
  //--------------------------------------------------------------------
  // 8. Epilogue  
  //--------------------------------------------------------------------
  
  // --- removing document from session 
  rc = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 14;
  }
  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 15;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
