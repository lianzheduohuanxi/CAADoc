// COPYRIGHT DASSAULT SYSTEMES 2001

//=============================================================================
//  Abstract of Use Case "CAAEhiNetwork":
//  ---------------------------------------
//
//  This Use Case illustrates how to navigate within electrical harness network  
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Creating the Session and Opening an Existing CATProduct Document.
//      . Retrieving the Root Product of the CATProduct Document.
//  2. Initializing Electrical Environment. 
//  3. Retrievng all Electrical Products under Root Product and Select one Bundle Segment.
//  4. Retrieving Connectors linked to bundle segment. 
//  5. Retrieving Connectors connected to Bundle Segment Connectors. 
//  6. Epilogue.
//      . Removing document from Session.
//      . Closing the Session
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document
//  3 - ERROR in getting root product
//  4 - ERROR in initializing electrical environment 
//  5 - ERROR in searching all products under root product 
//  6 - ERROR in computing list of electrical product in network 
//  7 - ERROR in searching bundle segment to analyze
//  8 - ERROR in searching connectors linked to bundle segment
//  9 - ERROR in searching connectors connected to bundle segment connectors 
//  10- ERROR in removing document  
//  11- ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiNetwork input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the of the document itself.
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

// C++ includes ( only for result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// CAA includes 

// ObjectModelerBase interfaces
#include "CATSessionServices.h"      // managing session
#include "CATDocumentServices.h"     // managing documents in session
#include "CATDocument.h"             // manipulating documents
#include "CATIDocRoots.h"            // browsing root objects in documents

// ProductStructure interfaces 
#include "CATIProduct.h"             // managing products  

// Electrical Harness interfaces
#include "CATIEhiGeoBundle.h"        // browsing geometrical bundles
#include "CATIEhiBundleSegment.h"    // browsing bundle segments
#include "CATIEhiNetwork.h"          // browsing electrical network
#include "CATIEhiNetworkExtremity.h" // browsing electrical network extremities

// Electrical interfaces
#include "CATIEleDocServices.h"      // initializing electrical environement 
#include "CATIElecAttrAccess.h"      // managing electrical attributes 

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
  char *sessionName = "CAA_EhiNetwork_Session";
  CATSession *pSession = NULL;
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
  
  CATDocument *pDoc = NULL;  // pDoc is a pointer to the document 

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
  
  CATIProduct* piRootProduct = NULL; // piRootProduct is a handle to document root product  
  //  
  CATIDocRoots * piDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &piDocRoots);
  if ( FAILED(rc) || (NULL==piDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = piDocRoots->GiveDocRoots();
  piDocRoots->Release();
  piDocRoots=NULL;
  
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
// 3. Retrieving all Electrical Products under Root Product 
//    and Selecting one Bundle Segment 
//--------------------------------------------------------------------
  
  // --- Retrieving all products under root product  
  
  CATListValCATBaseUnknown_var* pListProduct = NULL;
  pListProduct = piRootProduct->GetAllChildren(CATIProduct::ClassName());
  piRootProduct -> Release();
  piRootProduct = NULL ;
  
  int NumberOfProduct = 0;
  if ( (NULL!=pListProduct) && pListProduct->Size() ) 
  {
    NumberOfProduct = pListProduct->Size();	
    cout << "> number of products found : "<< NumberOfProduct << endl << flush;
  }
  else
  {
    cout << "ERROR : no product found in assembly " << endl << flush;
    return 5;
  }
  
  // --- Computing list of Electrical Network Objects from list of products   
    
  CATListValCATBaseUnknown_var* pListNetworkObject = new CATLISTV(CATBaseUnknown_var);
  int NumberOfNetworkObject = 0;
  CATIEhiNetwork * piNetworkObject = NULL;
  int i=0;
  
  for ( i=1; i<= NumberOfProduct; i++ )
  {
    spCBU = (*pListProduct)[i];
    if (NULL_var != spCBU && SUCCEEDED(spCBU->QueryInterface(IID_CATIEhiNetwork,(void**) &piNetworkObject)) && piNetworkObject)
    {
      pListNetworkObject->Append((*pListProduct)[i]);
      piNetworkObject->Release();
      piNetworkObject=NULL;
    }
  }
  
  delete pListProduct;
  pListProduct = NULL;
  
  // < Display objects in standard output >  
  
  if ( NULL!=pListNetworkObject ) 
  {
    NumberOfNetworkObject = pListNetworkObject->Size() ;
    cout << "> number of electrical object in network :"<< NumberOfNetworkObject <<endl << flush;
    
    CATIElecAttrAccess * piElecAttribute = NULL;
    CATUnicodeString ElecType = "unknown";
    CATIProduct* piInstanceProduct = NULL;
    CATUnicodeString InstanceName = "unknown";
    
    for ( i=1; i<= NumberOfNetworkObject; i++ )
    {
      spCBU = (*pListNetworkObject)[i];
      if (NULL_var != spCBU && SUCCEEDED( spCBU->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttribute) ))
      {
        piElecAttribute->GetElecType(ElecType);
        piElecAttribute->Release();
        piElecAttribute=NULL;		
      }
      if (NULL_var != spCBU && SUCCEEDED( spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct) ))
      {
        piInstanceProduct->GetPrdInstanceName(InstanceName);
        piInstanceProduct->Release();
        piInstanceProduct=NULL;		
      }
      
      cout << "   " << InstanceName.ConvertToChar() <<
        " -> type = "<< ElecType.ConvertToChar()     << endl << flush;
      ElecType = "unknown";
      InstanceName = "unknown";
    }
  }
  else
  {
    cout << "ERROR : no object found  " << endl << flush;
    return 6;
  }
  
  // --- Selecting a bundle segment 

  CATIEhiBundleSegment * piBundleSegment = NULL;
  //
  // get first element found in list
  int rank = 1;
  spCBU = (*pListNetworkObject)[rank];
  while ( NULL_var != spCBU && rank<=NumberOfNetworkObject && 
    FAILED(spCBU->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piBundleSegment))
    )
  {
    rank++;
    spCBU = (*pListNetworkObject)[rank];
  }
  
  if ( pListNetworkObject ) delete pListNetworkObject;
  pListNetworkObject=NULL;
  
  if ( NULL!=piBundleSegment )
  {
    cout << "> select bundle segment to analyse " <<endl << flush;
    cout << "   rank in list   :  "<< i << endl << flush;
    CATIProduct_var  spBundleSegmentProduct (piBundleSegment);
    CATUnicodeString InstanceName ;
    if ( NULL_var != spBundleSegmentProduct ) spBundleSegmentProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName .ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : no bundle segment found  " << endl << flush;
    return 7;
  }
  
//--------------------------------------------------------------------
// 4. Retrieving Connectors linked to bundle segment 
//--------------------------------------------------------------------

  // --- retrieving connectors linked to bundle segment 
  
  CATListValCATBaseUnknown_var* pListConnector = new CATLISTV(CATBaseUnknown_var);
  
  if ( SUCCEEDED(piBundleSegment->QueryInterface(IID_CATIEhiNetwork,(void**) &piNetworkObject)) )
  {
    CATListValCATBaseUnknown_var* pListConnectorPoint = NULL;
    piNetworkObject->ListConnectorPoints(&pListConnectorPoint);
    if ( NULL!=pListConnectorPoint )
    {
      int NumberOfConnectorPoint = pListConnectorPoint->Size();
      CATIEhiNetworkExtremity * piNetworkExtremity = NULL;
      
      for ( i=1; i<=NumberOfConnectorPoint; i++ )
      {
        CATListValCATBaseUnknown_var* pListConnected = NULL;
        spCBU = (*pListConnectorPoint)[i];
        if (NULL_var != spCBU)
          spCBU->QueryInterface(IID_CATIEhiNetworkExtremity,(void**) &piNetworkExtremity);
        if ( NULL != piNetworkExtremity )
        {
          piNetworkExtremity->ListConnectedConnectorPoints(&pListConnected);
          if ( NULL != pListConnected )
          {
            int NumberOfConnected = pListConnected->Size();
            CATBaseUnknown * piConnectedObject=NULL;
            CATIEhiNetworkExtremity * piConnectedExtremity = NULL;
            for ( int j=1; j<=NumberOfConnected; j++ )
            {
              CATBaseUnknown_var spCBUb = (*pListConnected)[j];
              if (NULL_var != spCBUb)
                spCBUb->QueryInterface(IID_CATIEhiNetworkExtremity,(void**) &piConnectedExtremity);
              if ( NULL != piConnectedExtremity )
              {
                piConnectedExtremity->GetElectricalObject(&piConnectedObject);
                piConnectedExtremity->Release();
                piConnectedExtremity=NULL;						  
                if ( NULL != piConnectedObject )
                {
                  CATBaseUnknown_var spObject = piConnectedObject;
                  if ( NULL_var != spObject ) pListConnector->Append(spObject);
                  piConnectedObject->Release();
                  piConnectedObject=NULL;
                }
              }
            }
            delete pListConnected;
            pListConnected=NULL;
          }
          piNetworkExtremity->Release();
          piNetworkExtremity=NULL;
        }
      }
    }
    delete pListConnectorPoint;
    pListConnectorPoint=NULL;
    
  }
  
  //
  if (piNetworkObject) piNetworkObject->Release();
  piNetworkObject=NULL;
   
  // < display connected objects > 
  
  if ( NULL!=pListConnector ) 
  {
    int NumberOfConnectedObject = pListConnector->Size() ;
    cout << "> number of connected object : "<< NumberOfConnectedObject <<endl << flush;
    
    CATIElecAttrAccess * piElecAttribute = NULL;
    CATUnicodeString ElecType = "unknown";
    CATIProduct* piInstanceProduct = NULL;
    CATUnicodeString InstanceName = "unknown";
    
    for ( i=1; i<= NumberOfConnectedObject; i++ )
    {
      spCBU = (*pListConnector)[i];
      if (NULL_var != spCBU)
      {
        if ( SUCCEEDED( spCBU->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttribute) ))
        {
          piElecAttribute->GetElecType(ElecType);
          piElecAttribute->Release();
          piElecAttribute=NULL;		
        }
        if ( SUCCEEDED( spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct) ))
        {
          piInstanceProduct->GetPrdInstanceName(InstanceName);
          piInstanceProduct->Release();
          piInstanceProduct=NULL;		
        }
      }
      
      cout << "   " << InstanceName.ConvertToChar() <<
        " -> type = "<< ElecType.ConvertToChar()     << endl << flush;
      
      
      ElecType = "unknown";
      InstanceName = "unknown";		
    }
  }
  else
  {
    cout << "ERROR : no connected object found  " << endl << flush;
    return 8;
  }
  
  if ( NULL != piBundleSegment ) piBundleSegment->Release();
  piBundleSegment = NULL ;
  
//--------------------------------------------------------------------
// 5. Retrieving Connectors connected to Bundle Segment Connectors 
//--------------------------------------------------------------------
  
  // --- Retrieving connected connectors  
  
  CATListValCATBaseUnknown_var* pListConnectedConnector = new CATLISTV(CATBaseUnknown_var);
  int NumberOfConnectedConnector = 0; 
  
  int NumberOfConnector = pListConnector->Size();
  cout << "> number of connected connector ? "<< endl << flush;

  for ( i=1; i<=NumberOfConnector; i++ )
  {
    cout << "   process connector number "<< i <<endl << flush;

    spCBU = (*pListConnector)[i];
    if (NULL_var != spCBU && SUCCEEDED(spCBU->QueryInterface(IID_CATIEhiNetwork,(void**) &piNetworkObject)) && piNetworkObject)
    {
      // -- retrieving connector points of electrical connector
      CATListValCATBaseUnknown_var* pListConnectorPoint = NULL;
      piNetworkObject->ListConnectorPoints(&pListConnectorPoint);
      
      if ( NULL!=pListConnectorPoint )
      {
        int NumberOfConnectorPoint = pListConnectorPoint->Size();
        CATIEhiNetworkExtremity * piNetworkExtremity = NULL;
        cout << "      number of connector point = "<< NumberOfConnectorPoint <<endl << flush;
        
        for ( int j=1; j<=NumberOfConnectorPoint; j++ )
        {
          cout << "        process connector point "<< j <<endl << flush;
          CATListValCATBaseUnknown_var* pListConnected = NULL;
          CATBaseUnknown_var spCBUb = (*pListConnectorPoint)[j];
          if (NULL_var != spCBUb)
            spCBUb->QueryInterface(IID_CATIEhiNetworkExtremity,(void**) &piNetworkExtremity);
          if ( NULL != piNetworkExtremity )
          {
            piNetworkExtremity->ListConnectedConnectorPoints(&pListConnected);
            if ( NULL != pListConnected )
            {
              int NumberOfConnected = pListConnected->Size();
              cout << "          number of connected connector point "<< NumberOfConnected <<endl << flush;
              CATBaseUnknown * piConnectedObject=NULL;
              CATIEhiNetworkExtremity * piConnectedExtremity = NULL;
              for ( int k=1; k<=NumberOfConnected; k++ )
              {
                 CATBaseUnknown_var spCBUt = (*pListConnected)[k];
                 if (NULL_var != spCBUt)
                   spCBUt->QueryInterface(IID_CATIEhiNetworkExtremity,(void**) &piConnectedExtremity);
                if ( NULL != piConnectedExtremity )
                {
                  piConnectedExtremity->GetElectricalObject(&piConnectedObject);
                  piConnectedExtremity->Release();
                  piConnectedExtremity=NULL;	
                  
                  if ( NULL != piConnectedObject )
                  {
                    CATIElecAttrAccess * piElecAttribute = NULL;
                    CATUnicodeString ElecType = "unknown";
                    CATUnicodeString BundleSegmentType = "ElecBundleSegment";
                    if ( SUCCEEDED( piConnectedObject->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttribute) ))
                    {
                      piElecAttribute->GetElecType(ElecType);
                      
                      if ( ElecType != BundleSegmentType )
                      {
                        CATBaseUnknown_var spObject = piConnectedObject;
                        if ( NULL_var != spObject ) pListConnectedConnector->Append(spObject);												
                      }
                      piElecAttribute->Release();
                      piElecAttribute=NULL;		
                    }
                    piConnectedObject->Release();
                    piConnectedObject=NULL;
                  }
                  
                }
              }
              delete pListConnected;
              pListConnected=NULL;
            }
            else
            {
              cout << "          nothing connected  "<< endl << flush;
            }
            piNetworkExtremity->Release();
            piNetworkExtremity=NULL;
          }
        }
      }
      
      piNetworkObject->Release();
      piNetworkObject=NULL;
      delete pListConnectorPoint;
      pListConnectorPoint=NULL;
      
    }
  }
  
  //
  delete pListConnector;
  pListConnector=NULL;
  
  // < display connected objects > 
  
  if ( NULL!=pListConnectedConnector ) 
  {
    int NumberOfConnectedObject = pListConnectedConnector->Size() ;
    cout << "> number of connected connector : "<< NumberOfConnectedObject <<endl << flush;
    
    CATIElecAttrAccess * piElecAttribute = NULL;
    CATUnicodeString ElecType = "unknown";
    CATIProduct* piInstanceProduct = NULL;
    CATUnicodeString InstanceName = "unknown";
    
    for ( i=1; i<= NumberOfConnectedObject; i++ )
    {
      spCBU = (*pListConnectedConnector)[i];
      if (NULL_var != spCBU)
      {
        if ( SUCCEEDED( spCBU->QueryInterface(IID_CATIElecAttrAccess,(void**) &piElecAttribute) ) && piElecAttribute)
        {
          piElecAttribute->GetElecType(ElecType);
          piElecAttribute->Release();
          piElecAttribute=NULL;		
        }
        if ( SUCCEEDED( spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct) ) && piInstanceProduct)
        {
          piInstanceProduct->GetPrdInstanceName(InstanceName);
          piInstanceProduct->Release();
          piInstanceProduct=NULL;		
        }
      }
      cout << "   " << InstanceName.ConvertToChar() <<
        " -> type = "<< ElecType.ConvertToChar()     << endl << flush;
      
      ElecType = "unknown";
      InstanceName = "unknown";		
    }
  }
  else
  {
    cout << "ERROR : no connected object found  " << endl << flush;
    return 9;
  }
  
  //
  delete pListConnectedConnector;
  pListConnectedConnector=NULL;

//--------------------------------------------------------------------
// 6. Epilogue 
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
