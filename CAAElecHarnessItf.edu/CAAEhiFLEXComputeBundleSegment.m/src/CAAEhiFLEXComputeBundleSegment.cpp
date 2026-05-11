// COPYRIGHT DASSAULT SYSTEMES 2004

//=================================================================================================================================
//  Abstract of Use Case "CAAEhiFLEXComputeBundleSegment":
//  -----------------------------------------------------
//
//  This Use Case illustrates how to use the FLEX algorithm (in order to test the user implementation of the interface CATIEhiFLEX)
//
//=================================================================================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//		. Setting FLEX algorithm mode
//  2. Initializing Electrical Environment 
//  3. Retrieving all Geometrical Bundle under the Root Product 
//  4. Retrieving all Bundle Segments under the Geometrical Bundle 
//  5. Calculating the shape thanks to the user implementation in FLEX mode 
//  6. Epilogue
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document
//  3 - ERROR in getting root product
//  4 - ERROR in setting the FLEX algo mode
//  5 - ERROR in initializing electrical environment 
//  6 - ERROR in searching geometrical bundle
//  7 - ERROR in retrieving geometrical bundle
//  8 - ERROR in retrieving bundle segment
//  9 - ERROR in retrieving the bundle segment curve 
// 10 - ERROR in imposing the slack value
// 11 - ERROR in the update 
// 12 - ERROR in retrieving the slack value
// 13 - ERROR in retrieving the lminimum bend radius
// 14 - ERROR in Epilogue 
// 15 - ERROR in Epilogue deleting session

//
//  Running the program:
//  -------------------
// To run this program, you can use the command:
//  mkrun -c "CAAEhiFLEXComputeBundleSegment input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the document itself.
//
//
//  You may reference the supplied CATProduct document called "SampleProduct.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAA_EhiFLEXComputeBundleSegment_Sample directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAA_EhiFLEXComputeBundleSegment_Sample 
//  directory. 
//
//================================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents
#include "CATIInstance.h"
#include "CATIValue.h"
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

// Electrical interfaces
#include "CATIEleDocServices.h"    // initializing electrical environement 
#include "CATIElecAttrAccess.h"    // managing electrical attributes 

//System
#include "CATSettingRepository.h"

#define REPOSITORY_NAME "ElectricalHarnessInstallation"


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
  
  if ( pListRootProduct && pListRootProduct->Size() )
  {  
    CATBaseUnknown_var spItem1=(*pListRootProduct)[1] ;
    rc = spItem1->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
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

  // --- Setting FLEX algorithm mode

	CATSettingRepository * pEhiRepository=NULL;
    pEhiRepository  = CATSettingRepository::GetRepository(REPOSITORY_NAME);
    int choixAlgo = 1;
    if (pEhiRepository) 
	{
	  cout << "> Repository found OK" << endl ;
	  cout << "> The computation willl be made thanks to FLEX algorithm = " << endl ;
      pEhiRepository-> WriteSetting("ChoixAlgo", &choixAlgo);
	}
	else
	{
	  cout << "ERROR : Repository found " << endl << flush;
      return 4;	
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
    return 5;
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
    return 6;
  }
  
  // --- Selecting first geometrical bundle to analyse
  
  CATIEhiGeoBundle * piGeoBundle = NULL;
  CATBaseUnknown_var spGeo1=(*pListGeoBundle)[1];
  rc = spGeo1->QueryInterface(IID_CATIEhiGeoBundle,(void**) &piGeoBundle);
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
    return 7;
  }
  
  //--------------------------------------------------------------------
  // 4. Retrieving all bundle segments under the geometrical bundle 
  //    and for each bundle segment retrieving its curve 
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
    return 8;
  }
  
  
  // --- selecting each bundle segment in list  find his electrical curve
  //     and the list of his linked support

  CATIEhiBundleSegment * piBundleSegment = NULL;
  int TailleListBundleSegment = pListBundleSegment->Size() ;
  for(int rank =1 ; rank<=TailleListBundleSegment; rank++)
  {
    CATBaseUnknown_var spCurrent=(*pListBundleSegment)[rank];
    rc = spCurrent->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment);
    
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
      return 8;
    }

	
	//--------------------------------------------------------------------
    // 5. Calculation of the shape
    // -------------------------------------------------------------------
	CATIInstance *pElecInstance = NULL; 
    if(piBundleSegment&&  SUCCEEDED(piBundleSegment->QueryInterface(CATIInstance::ClassId(),(void**)&pElecInstance)) &&  pElecInstance )
    {
		
		// 5.1 Retrieving Electrical Curve ( Bundle Segment route )  
		//--------------------------------------------------------------------
		
		
		CATIGSMSpline * piSpline = NULL;
		//
		rc = piBundleSegment->GetElecCurve(&piSpline);
		if ( SUCCEEDED(rc) && (NULL!=piSpline) )
		{
			cout << "> electrical curve found " << endl << flush;		
			CATIElecAttrAccess * piElecAttr = NULL;
			rc = piSpline->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttr );
			piSpline->Release();
			piSpline=NULL;
			if (FAILED(rc) || (NULL==piElecAttr)) 
			{
				cout << "ERROR : QueryInterface(IID_CATIElecAttrAccess) FAILED " << endl << flush;	
				return 10;
			}
			
			// We set the Creation Mode to Slack;
			CATUnicodeString attribute,mode;
			mode= "Slack";
			// --- set build mode 
			attribute = "Elec_Creation_Mode";
			rc = piElecAttr->Set(attribute,mode);
			if (FAILED(rc))
			{
				cout << "ERROR : Set Elec_Creation_Mode FAILED" << endl << flush;
				piElecAttr->Release();
				piElecAttr=NULL; 
				return 10;
			}
			
			// --- build mode = "Slack" : get slack and set slack to a different value then back to the initial value to mark the curve as Not Uptodate
			if ( mode == "Slack" )
			{
				cout << "> Mode = Slack " << endl << flush;
				double slack =4.;
				attribute = "Elec_Di_Slack";
				CATICkeInst_var hSlack;
                rc = piElecAttr->Get(attribute,  hSlack);
                double value =-1;
				if (!!hSlack)
                     value= hSlack->AsReal();
				if (FAILED(rc))
				{
					cout << "ERROR : Get Elec_Di_Slack FAILED" << endl << flush;
					piElecAttr->Release();
					piElecAttr=NULL;  
					return 10;
				}
				cout << "> Value of slack= " << value <<endl << flush;
				rc = piElecAttr->Set(attribute,slack);
				if (FAILED(rc))
				{
					cout << "ERROR : Set Elec_Di_Slack FAILED" << endl << flush;
					piElecAttr->Release();
					piElecAttr=NULL;  
					return 10;
				}
				slack=value;
				rc = piElecAttr->Set(attribute,slack);
				if (FAILED(rc))
				{
					cout << "ERROR : Set Elec_Di_Slack FAILED" << endl << flush;
					piElecAttr->Release();
					piElecAttr=NULL;  
					return 10;
				}
			}
			// LRO 07:01:05
			if (piElecAttr)
			{
				piElecAttr->Release();
				piElecAttr=NULL;
			}
		}
		else
		{
			cout << "ERROR : electrical curve not found " << endl << flush;	
			return 9;
		}
		
		
		// 5.2 Update the bundle segment 
		//-------------------------------------------------------------------- 
		
		CATISpecObject_var hSpecBns=piBundleSegment;
		if (NULL_var != hSpecBns)
		{
			hSpecBns->Update();
			cout << "> update of bundle segment done " << endl << flush;
		}
		else
		{
			cout << "ERROR update could not be done " << endl << flush;
			return 11;
		}

		// Retrieve the Slack value
		CATIValue * pValue = pElecInstance -> GetValue("Elec_Di_Slack");
		
		if(pValue)
		{
			CATUnicodeString ShowValueSlack = pValue->Show();      
			cout << "> Value of slack : " << ShowValueSlack.ConvertToChar() << endl;
			pValue->Release();
			pValue = NULL;
		}
		else
		{
			cout << "ERROR : pValue NULL for Elec_Di_Slack" << endl << flush;	
			return 12;
		}
		
		pValue = pElecInstance -> GetValue("Elec_Min_Bend_Radius");
		if(pValue)
		{
			CATUnicodeString ShowValueMinBendRadius = pValue->Show();      
			cout<<"> Min Bend Radius (in m) : "<<ShowValueMinBendRadius.ConvertToChar()<<endl;
			pValue->Release();
			pValue = NULL;
		}
		else
		{
			cout << "ERROR : pValue NULL for Elec_Min_Bend_Radius" << endl << flush;
			return 13;
		}
		
	if(pElecInstance) pElecInstance->Release();
	pElecInstance=NULL;
	}
	
    if(piBundleSegment)  piBundleSegment -> Release();
    piBundleSegment = NULL;
    
  } // end for rank


  
  if ( pListBundleSegment )delete pListBundleSegment;
  pListBundleSegment=NULL;
  
  // 
  //--------------------------------------------------------------------
  // 6. Epilogue  
  //--------------------------------------------------------------------
  
  // 6.1-- releasing pointers to interface
  //

  //
  // 6.2-- removing document from session 
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
  // 6.3-- closing the session
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















