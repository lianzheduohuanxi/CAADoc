// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspConnectivity - This sample illustrates how to use the following
// interfaces to query for part connector and connection information:  
// CATIPspConnector, CATIPspConnectable, CATIPspConnection, CATIPspCntrFlow
//
#include <iostream.h>

// This framework
#include "CAAPspConnectivity.h"

// CATPlantShipInterfaces
#include "CATIPspPhysicalProduct.h"
#include "CATIPspPhysical.h"
#include "CATIPspConnector.h"
#include "CATIPspConnection.h"
#include "CATIPspConnectable.h"
#include "CATIPspCntrFlow.h"

//ObjectModelerBase
#include "CATDocument.h"

// System
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATICStringList.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspConnectivity::CAAPspConnectivity() 
{
  cout << "CAAPspConnectivity::CAAPspConnectivity()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspConnectivity::~CAAPspConnectivity()
{
  cout << "CAAPspConnectivity::~CAAPspConnectivity()" << endl;
}

//=============================================================================
//  List and query connectors, connections, connectables and connector flow
//=============================================================================
int CAAPspConnectivity::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspConnectivity::DoSample               ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspPhysical     *piPhysical = NULL;
  CATIPspConnectable  *piPspConnectable = NULL;
  CATIPspConnection   *piPspConnection = NULL;
  CATIPspConnector    *piPspConnector = NULL;
  CATIPspConnector    *piPspCntr = NULL;
  CATIPspCntrFlow     *piCntrFlow = NULL;
  IUnknown            *piUnknown  = NULL;
  CATIUnknownList     *piUnkListCtnr  = NULL;
  CATIUnknownList     *piUnkListConnections  = NULL;

  CATUnicodeString    CntrName;
    
  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a physical object from the input document
    piPhysical = GetAPhysicalObject();

    if ( NULL != piPhysical )
    {
       //  Find CATIPspConnectable interface
       rc = piPhysical->QueryInterface(IID_CATIPspConnectable,(void**)&piPspConnectable);
       if ( SUCCEEDED(rc)) 
       {
          cout << "CAAPspConnectivity: "
               << "Succeeded in getting CATIPspConnectable interface" << endl;
       }
       piPhysical->Release();
       piPhysical = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspConnectable methods
    //-------------------------------------------------------------------------
    if ( NULL != piPspConnectable )
    {
      int NumOfCtrs = 0;

      //----------------------------------------------------------------------
      //  List connectors
      //----------------------------------------------------------------------    
      if ( SUCCEEDED(piPspConnectable->ListConnectors (NULL,&piUnkListCtnr ))
         && (NULL != piUnkListCtnr )) 
      {
        cout << "Succeeded in  getting a list of connectors" << endl;
    
        //  Get a connector
        unsigned int ListSize = 0;
        if ( SUCCEEDED(piUnkListCtnr->Count(&ListSize)) ) NumOfCtrs = ListSize;
        if ( NumOfCtrs > 0 )
        {
           for ( int i = 0; i < NumOfCtrs; i++ )
           {
              if ( SUCCEEDED(piUnkListCtnr->Item(i,&piUnknown)) && (NULL != piUnknown) )
              {
                 rc = piUnknown->QueryInterface(IID_CATIPspConnector,(void**)&piPspConnector);
                 piUnknown->Release();
                 piUnknown = NULL; 
                 if ( NULL != piPspConnector ) break;
              }
           }
        }
        piUnkListCtnr->Release();  piUnkListCtnr = NULL;
      }

      // Query rest of the CATIPspConnectable functions
      QueryConnectableFunctions(piPspConnectable);

      // Get a connector name and use the name to get a connector pointer
      if ( NULL != piPspConnector )
      {
         if ( SUCCEEDED(piPspConnector->GetName(CntrName)) )
         {
            cout << "Connector name = " << CntrName.ConvertToChar() << endl;
            CATIPspConnector *piCntr = NULL;
            if ( SUCCEEDED(piPspConnectable->GetConnector(CntrName,&piCntr)) )
            {
               cout << "Succeeded in getting a connector pointer" << endl;
               piCntr->Release();
               piCntr = NULL;
            }
         }
      }
    }

    //-------------------------------------------------------------------------
    //  Find CATIPspCntrFlow interface and query CATIPspCntrFlow functions
    //-------------------------------------------------------------------------
    if ( NULL != piPspConnector )
    {
      if ( SUCCEEDED(piPspConnector->QueryInterface(IID_CATIPspCntrFlow,
           (void**)&piCntrFlow)) && piCntrFlow )
      {
        QueryCntrFlowFunctions( piCntrFlow );
        if ( NULL != piCntrFlow )
        { 
          piCntrFlow->Release(); piCntrFlow = NULL;
        }
      }            
    }

    //-------------------------------------------------------------------------
    //  CATIPspConnector methods     
    //-------------------------------------------------------------------------

    if ( NULL != piPspConnector )
    {
      // List Connections
      int NumOfCntns = 0;
      if ( SUCCEEDED( piPspConnector->ListConnections (NULL, &piUnkListConnections )) &&
           (NULL != piUnkListConnections) )          
      {
        // Get a connection 
        unsigned int ListSize = 0;
        if ( SUCCEEDED(piUnkListConnections->Count(&ListSize)) ) NumOfCntns = ListSize;
        if ( NumOfCntns > 0 )
        {
          for ( int i = 0; i < NumOfCntns; i++ )
          {
            if ( SUCCEEDED(piUnkListConnections->Item(i,&piUnknown)) && (NULL != piUnknown) )
            {
              rc = piUnknown->QueryInterface(IID_CATIPspConnection,(void**)&piPspConnection);
              piUnknown->Release();
              piUnknown = NULL; 
              if ( NULL != piPspConnection ) break;
            }
          }
        }
        piUnkListConnections->Release();  piUnkListConnections = NULL;
      }

      // Querying other CATIPspConnector functions
      QueryConnectorFunctions (piPspConnector);

    }

    //-------------------------------------------------------------------------
    //  CATIPspConnection methods
    //-------------------------------------------------------------------------
    if ( NULL != piPspConnection)
    {
       QueryConnectionFunctions (piPspConnection);
    }

    if ( NULL != piPspConnectable ) { piPspConnectable->Release(); piPspConnectable = NULL; }
    if ( NULL != piPspConnector ) { piPspConnector->Release(); piPspConnector = NULL; }
    if ( NULL != piPspConnection ) { piPspConnection->Release(); piPspConnection = NULL; }

  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piPspConnectable ) { piPspConnectable->Release(); piPspConnectable = NULL; }
    if ( NULL != piPspConnection ) { piPspConnection->Release(); piPspConnection = NULL; }
    if ( NULL != piPspConnector ) { piPspConnector->Release(); piPspConnector = NULL; }
    if ( NULL != piPspCntr ) { piPspCntr->Release(); piPspCntr = NULL; }
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    if ( NULL != piUnkListCtnr ) { piUnkListCtnr->Release(); piUnkListCtnr = NULL; }
    if ( NULL != piUnkListConnections ) { piUnkListConnections->Release(); piUnkListConnections = NULL; }
    if ( NULL != piCntrFlow ) { piCntrFlow->Release(); piCntrFlow = NULL; }

    cout << "CAAPspConnectivity::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}


//=============================================================================
//  Set and query CATIPspCntrFlow functions
//=============================================================================

int CAAPspConnectivity::QueryCntrFlowFunctions( CATIPspCntrFlow* piPspCntrFlow)
{
  int RetVal = 0;
  if ( NULL == piPspCntrFlow )
  {
     cout << "Pointer piPspCntrFlow is NULL" << endl;
     return 1;
  }

  CATTry 
  {
    // Query the connector flow capability
    CATPspCntrFlowCapability CntrFlowCapability = CatPspCntrFlowCapability_Undefined;
    if ( SUCCEEDED(piPspCntrFlow->GetFlowCapability(CntrFlowCapability)) )
    {
      switch( CntrFlowCapability )
      {
        case  CatPspCntrFlowCapability_Undefined :
            cout << "Flow Capability is undefined" << endl;
            break;
        case  CatPspCntrFlowCapability_InDirection :
            cout << "Flow Capability is inward direction" << endl;
            break;
        case  CatPspCntrFlowCapability_OutDirection :
            cout << "Flow Capability is Outward Direction" << endl;
            break;
        case  CatPspCntrFlowCapability_InOutDirection :
            cout << "Flow Capability is bi-directional" << endl;
            break;
      }
    }

    // Set the connector flow capability
    CntrFlowCapability = CatPspCntrFlowCapability_InDirection;
    if ( SUCCEEDED(piPspCntrFlow->SetFlowCapability(CntrFlowCapability)) )
       cout << "Succeeded in setting the connector flow capability" << endl;

    // Query the connector flow reality
    CATPspCntrFlowReality CntrFlowReality = CatPspCntrFlowReality_Undefined;
    if ( SUCCEEDED(piPspCntrFlow->GetFlowReality(CntrFlowReality)) )
    {
      switch( CntrFlowCapability )
      {
        case  CatPspCntrFlowReality_Undefined :
          cout << "Flow Reality is undefined" << endl;
          break;
        case  CatPspCntrFlowReality_InDirection :
          cout << "Flow is in inward direction" << endl;
          break;
        case  CatPspCntrFlowReality_OutDirection :
          cout << "Flow is in Outward Direction" << endl;
          break;
        case  CatPspCntrFlowReality_InOutDirection :
          cout << "Flow is bi-directional" << endl;
          break;
      }
    }

    // Set the connector flow reality
    CntrFlowReality = CatPspCntrFlowReality_InDirection;
    if ( SUCCEEDED(piPspCntrFlow->SetFlowReality(CntrFlowReality)) )
       cout << "Succeeded in setting the connector flow reality" << endl;
    
  } // end CATTry
  CATCatch (CATError, error)
  {         
    cout << "CAAPspConnectivity::QueryCntrFlowFunctions *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;                
  return RetVal;
}

//=============================================================================
//  List and query CATIPspConnectable functions
//=============================================================================
int CAAPspConnectivity::QueryConnectableFunctions(CATIPspConnectable* piPspConnectable)
{
  int RetVal = 0;
  if ( NULL == piPspConnectable )
  {
    cout << "Pointer piPspConnectable is NULL" << endl;
    return 1;
  }

  CATICStringList        *pLTypes = NULL;
  CATIPspConnector       *piPspCntr = NULL;
  CATIUnknownList        *pIUListOfOtherCtbl  = NULL;
  CATIUnknownList        *pIUListOfCtr        = NULL;
  CATIUnknownList        *pIUListOfOtherCtr  = NULL;
  
  CATTry 
  {
    //----------------------------------------------------------------------
    //  List valid connector types
    //----------------------------------------------------------------------    
    if ( SUCCEEDED(piPspConnectable->ListValidCntrTypes(&pLTypes)) && pLTypes )
    {
      unsigned int LCStrSize = 0;
      int NumOfCStr = 0;
      if (pLTypes) 
      HRESULT rc = pLTypes->Count (&LCStrSize);
      NumOfCStr = LCStrSize;
      if (NumOfCStr)
      {
        cout << "Number of valid connector types = " << NumOfCStr <<endl;
        char *piCStrMember = NULL;
        for (int iCStr=1; iCStr <= NumOfCStr; iCStr++)
        {
          if ( SUCCEEDED(pLTypes->Item(iCStr-1,&piCStrMember)) &&
               (NULL != piCStrMember) )
          {
            cout <<  iCStr << ") " << piCStrMember << endl;
            delete [] piCStrMember; piCStrMember = NULL;
          }
        }
      }
      if ( NULL != pLTypes )
      {
        pLTypes->Release();
        pLTypes = NULL;
      }
    }
    //----------------------------------------------------------------------
    // Find all the objects connected to this object and the corresponding
    // connectors involved in the connection.
    //----------------------------------------------------------------------
    if ( SUCCEEDED(piPspConnectable->ListConnectables(NULL,&pIUListOfOtherCtbl,&pIUListOfCtr,&pIUListOfOtherCtr)) && 
            pIUListOfOtherCtr && pIUListOfCtr && pIUListOfOtherCtbl )
    {
      unsigned int uiListSizeOtherCtbl = 0;
      unsigned int uiListSizeCtr = 0;
      unsigned int uiListSizeOtherCtr = 0;
      pIUListOfOtherCtbl -> Count(&uiListSizeOtherCtbl);
      pIUListOfCtr -> Count(&uiListSizeCtr);
      pIUListOfOtherCtr -> Count(&uiListSizeOtherCtr);
      cout << "Number of connected objects = " << uiListSizeOtherCtbl << endl;
      cout << "Number of connected connectors on this object = " << uiListSizeCtr << endl;

      if( NULL != pIUListOfOtherCtbl )
      {
        pIUListOfOtherCtbl->Release();
        pIUListOfOtherCtbl = NULL;
      }
      if( NULL != pIUListOfCtr )
      {
        pIUListOfCtr->Release();
        pIUListOfCtr = NULL;
      }
      if( NULL != pIUListOfOtherCtr )
      {
        pIUListOfOtherCtr->Release();
        pIUListOfOtherCtr = NULL;
      }
    }
    else
      cout << "No connected objects found" <<endl;

  } // end CATTry

  CATCatch (CATError, error)
  {    
    if ( NULL != piPspCntr ) { piPspCntr->Release(); piPspCntr = NULL; }    
    if ( NULL != pIUListOfOtherCtbl ) { pIUListOfOtherCtbl->Release(); pIUListOfOtherCtbl = NULL; }
    if ( NULL != pIUListOfCtr ) { pIUListOfCtr->Release(); pIUListOfCtr = NULL; }
    if ( NULL != pIUListOfOtherCtr ) { pIUListOfOtherCtr->Release(); pIUListOfOtherCtr = NULL; }
    if ( NULL != pLTypes ) { pLTypes->Release(); pLTypes = NULL; }

    cout << "CAAPspConnectivity::QueryConnectableFunctions *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;             

  return RetVal;
}

//=============================================================================
//  List and query CATIPspConnector functions
//=============================================================================

int CAAPspConnectivity::QueryConnectorFunctions(CATIPspConnector* piPspConnector )
{
  int RetVal = 0;
  if ( NULL == piPspConnector )
  {
    cout << "Pointer piPspConnector is NULL" << endl;
    return 1;
  }   
  CATIPspConnectable     *piPspConnectable = NULL;

  CATTry 
  {
    // Get the owner of this connector i.e Associated Connectable
    if( SUCCEEDED( piPspConnector->GetAssociatedConnectable ( &piPspConnectable ))
      && ( NULL != piPspConnectable) )
    {       
       cout << "Succeeded in getting associated connectable" << endl;
    }

    if ( NULL != piPspConnectable ) { piPspConnectable->Release(); piPspConnectable = NULL; }

    // Is connector connected
    CATBoolean oBYes = FALSE;
    if( SUCCEEDED( piPspConnector->IsCntrConnected (&oBYes) ) )
    {
      if( oBYes)
      {
        cout << "Connector is connected " << endl;                       
      }
      else
      {
        cout << "Connector is not connected " << endl;                       
      }
    }

    // Getting name of the connector 
    CATUnicodeString uConnectorName;
    if( SUCCEEDED( piPspConnector->GetName (uConnectorName) ))
    {
      cout << "Name of the connector is " << uConnectorName.ConvertToChar() << endl;                       
    }

    // Setting name of the connector 
    uConnectorName = "Connector1";
    if( SUCCEEDED( piPspConnector->SetName (uConnectorName) ))
    {
      cout << "Succeeded in modifying the connector's name" << endl;                       
    }
    
    // Getting connector number 
    int iCtrNumber;
    if( SUCCEEDED( piPspConnector->GetConnectorNumber(iCtrNumber) ))
    {
      cout << "Number of the connector is " << iCtrNumber << endl;                         
    }

  } // end CATTry

  CATCatch (CATError, error)
  {         
    if ( NULL != piPspConnectable ) { piPspConnectable->Release(); piPspConnectable = NULL; }
    cout << "CAAPspConnectivity:QueryConnectorFunctions *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;              
              
  return RetVal;
}

//=============================================================================
//  List and query CATIPspConnection functions
//  Disconnect and connect two connectors
//=============================================================================
int CAAPspConnectivity::QueryConnectionFunctions (CATIPspConnection* piPspConnection)
{
  int RetVal = 0;
  if ( NULL == piPspConnection )
  {
    cout << "Pointer piPspConnection is NULL" << endl;
    return 1;
  }   
  CATIUnknownList   *pIUListOfConnectors    = NULL;
  CATIUnknownList   *pIUListOfConnectables  = NULL;
  IUnknown          *piUnknown = NULL;
  CATIPspConnector  *piCntr1 = NULL;
  CATIPspConnector  *piCntr2 = NULL;
  CATIPspConnection *piConnection = NULL;
  CATUnicodeString  ConnectionType;

  CATTry 
  {
    //-------------------------------------------------------------------------
    // Find all connected objects in this connection
    //-------------------------------------------------------------------------
    if ( SUCCEEDED(piPspConnection->ListConnectables(NULL,&pIUListOfConnectables, &pIUListOfConnectors))
                && pIUListOfConnectables  && pIUListOfConnectors)
    {
      unsigned int uiListSizeCtbl = 0;                
      pIUListOfConnectables -> Count(&uiListSizeCtbl);                
      cout << "Number of connected objects in this connection is " << uiListSizeCtbl << endl;

      if ( NULL != pIUListOfConnectables )
      {
        pIUListOfConnectables->Release();
        pIUListOfConnectables = NULL;
      }

      unsigned int uiListSizeCntr = 0;
      pIUListOfConnectors -> Count(&uiListSizeCntr);
      cout << "Number of connectors included in this connection is " << uiListSizeCntr << endl;

      if ( NULL != pIUListOfConnectors )
      {
        pIUListOfConnectors->Release();
        pIUListOfConnectors = NULL;
      }
    }

    //-------------------------------------------------------------------------
    // Find all the connectors included in this connection
    //-------------------------------------------------------------------------   
    if ( SUCCEEDED(piPspConnection->ListConnectors(NULL,&pIUListOfConnectors))
         && pIUListOfConnectors )
    {
      cout << "Succeded in getting a list of connectors in the connection" << endl;

      unsigned int uiListSizeCntr = 0;                
      pIUListOfConnectors->Count(&uiListSizeCntr);
      if ( uiListSizeCntr == 2 )
      {
         if ( SUCCEEDED(pIUListOfConnectors->Item(0,&piUnknown)) )
         {
            piUnknown->QueryInterface(IID_CATIPspConnector,(void**)&piCntr1);
            piUnknown->Release();
            piUnknown = NULL;
         }
         if ( SUCCEEDED(pIUListOfConnectors->Item(1,&piUnknown)) )
         {
            piUnknown->QueryInterface(IID_CATIPspConnector,(void**)&piCntr2);
            piUnknown->Release();
            piUnknown = NULL;
         }
      }

      //-----------------------------------------------------------------------
      // Disconnect and connect connectors
      //-----------------------------------------------------------------------
      if ( NULL != piCntr1 )
      {
         if ( NULL != piCntr2 )
         {
            if ( SUCCEEDED(piCntr1->Disconnect(piCntr2)) )
            {
              cout << "Succeeded in disconnecting two connectors" << endl;

              // Get a valid connection type for 2 connectors
              if ( SUCCEEDED(piCntr1->GetValidConnection(piCntr2,ConnectionType)) )
                 cout << "Succeeded in getting a valid connection type" << endl;
              
              if ( SUCCEEDED(piCntr1->Connect(ConnectionType,piCntr2,&piConnection)) 
                   && (NULL != piConnection) )
              {
                 cout << "Succeeded in connecting two connectors" << endl;
                 piConnection->Release();
                 piConnection = NULL;
              }
            }
            piCntr2->Release();
            piCntr2 = NULL;
         }
         piCntr1->Release();
         piCntr1 = NULL;
      }
      
      if ( NULL != pIUListOfConnectors )
      {
        pIUListOfConnectors->Release();
        pIUListOfConnectors = NULL;
      }
    }
  } // end CATTry

  CATCatch (CATError, error)
  {     
    if ( NULL != pIUListOfConnectors ) { pIUListOfConnectors->Release(); pIUListOfConnectors = NULL; }
    if ( NULL != pIUListOfConnectables ) { pIUListOfConnectables->Release(); pIUListOfConnectables = NULL; }
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    if ( NULL != piCntr1 ) { piCntr1->Release(); piCntr1 = NULL; }
    if ( NULL != piCntr2 ) { piCntr2->Release(); piCntr2 = NULL; }
    if ( NULL != piConnection ) { piConnection->Release(); piConnection = NULL; }
    cout << "CAAPspConnectivity::QueryConnectionFunctions *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;             

  return RetVal;
}
