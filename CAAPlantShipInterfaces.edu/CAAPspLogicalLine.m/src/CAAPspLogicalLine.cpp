// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspLogicalLine - This sample illustrates how to use the following
// interfaces to query a LineID catalog and get a LineID 'from-to' information:
// CATIPspShareData and CATIPspLogicalLine.
//
#include <iostream.h>

// This framework
#include "CAAPspLogicalLine.h"

// CATPlantShipInterfaces
#include "CATIPspLogicalLine.h"
#include "CATIPspShareData.h"
#include "CATIPspResource.h"

//ObjectModelerBase
#include "CATDocument.h"

// System
#include "CATIUnknownList.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspLogicalLine::CAAPspLogicalLine() 
{
  cout << "CAAPspLogicalLine::CAAPspLogicalLine()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspLogicalLine::~CAAPspLogicalLine()
{
  cout << "CAAPspLogicalLine::~CAAPspLogicalLine()" << endl;
}

//=============================================================================
//  Query for logical line information
//=============================================================================
int CAAPspLogicalLine::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspLogicalLine::DoSample                    ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspShareData   *piShareData = NULL;
  CATIPspLogicalLine *piLogLine = NULL;
  CATIPspResource    *piResource = NULL;
  CATIContainer      *piRootCont = NULL;
  CATIUnknownList    *piFromMajorsList = NULL;
  CATIUnknownList    *piFromMinorsList = NULL;
  CATIUnknownList    *piToMajorsList = NULL;
  CATIUnknownList    *piToMinorsList = NULL;
  CATIUnknownList    *piFromConnectionsList = NULL;
  CATIUnknownList    *piToConnectionsList = NULL;

  CATListValCATUnicodeString *pShareDataList = NULL;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    piRootCont = GetRootContainer();
    if (NULL == piRootCont)
    {
       cout << "CAAPspApplication:"
            << "Cannot find root container"
            << endl;
       return E_FAIL;
    }
    else
    {
       //  Find CATIPspShareData interface
       rc = piRootCont->QueryInterface(IID_CATIPspShareData,(void **)&piShareData);
    }  
    
    CATObject *piApplObj = new CATObject("CATPiping");
    if ( NULL != piApplObj )
    {
       //  Find CATIPspResource interface from application object
       rc = piApplObj->QueryInterface(IID_CATIPspResource,(void **)&piResource);
       piApplObj->Release();
       piApplObj = NULL;
    }


    //-------------------------------------------------------------------------
    //  CATIPspShareData methods
    //-------------------------------------------------------------------------
    if ( NULL != piShareData )
    {
       CATUnicodeString ResourceName;
       CATUnicodeString ClassType = "CATPspPipingLine";

       if ( NULL != piResource )
       {
          CATUnicodeString Path;
          rc = piResource->GetLineCatalogPath(ClassType,Path,ResourceName);
          piResource->Release();
          piResource = NULL;
       }

       //----------------------------------------------------------------------
       //  Get a list of logical line IDs from the share data catalog.
       //---------------------------------------------------------------------- 
       if ( ResourceName.GetLengthInChar() > 0 )
       {
          cout << "CAAPspLogicalLine: "
               << "Succeeded in getting resource name for the PipingLine catalog" << endl;
          CATUnicodeString ShareDataType;
          if ( SUCCEEDED(piShareData->List(ResourceName,ShareDataType,&pShareDataList)) )
             cout << "CAAPspLogicalLine: "
                  << "Succeeded in getting a list of Piping Line IDs from the PipingLine catalog" << endl;     
       }
       

       if ( NULL != pShareDataList )
       {
          delete pShareDataList;  pShareDataList = NULL;
       }

       piShareData->Release();
       piShareData = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspLogicalLine methods
    //-------------------------------------------------------------------------
    //  Find a logical line in the document;
    piLogLine = GetALogicalLine();
    if ( NULL != piLogLine )
    {
       //----------------------------------------------------------------------
       //  Get a logical line 'from-to' information.
       //----------------------------------------------------------------------    
       if ( SUCCEEDED(piLogLine->GetFromTo(&piFromMajorsList,&piFromMinorsList,
                              &piToMajorsList,&piToMinorsList,
                              &piFromConnectionsList,&piToConnectionsList)) )
          cout << "CAAPspLogicalLine: "
               << "GetFromTo Succeeded" << endl;

       if ( NULL != piFromMajorsList )
       {
          piFromMajorsList->Release();  piFromMajorsList = NULL;
       }
       if ( NULL != piFromMinorsList )
       {
          piFromMinorsList->Release();  piFromMinorsList = NULL;
       }
       if ( NULL != piToMajorsList )
       {
		      piToMajorsList->Release();  piToMajorsList = NULL;
       }
       if ( NULL != piToMinorsList )
       {
          piToMinorsList->Release();  piToMinorsList = NULL;
       }
       if ( NULL != piFromConnectionsList )
       {
          piFromConnectionsList->Release();  piFromConnectionsList = NULL;
       }
       if ( NULL != piToConnectionsList )
       {
          piToConnectionsList->Release();  piToConnectionsList = NULL;
       }

       piLogLine->Release();
       piLogLine = NULL;
    }
  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piLogLine ) { piLogLine->Release(); piLogLine = NULL; }
    if ( NULL != piShareData ) { piShareData->Release(); piShareData = NULL; }
    if ( NULL != piResource ) { piResource->Release(); piResource = NULL; }
    if ( NULL != piFromMajorsList ) { piFromMajorsList->Release(); piFromMajorsList = NULL; }
    if ( NULL != piFromMinorsList ) { piFromMinorsList->Release(); piFromMinorsList = NULL; }
    if ( NULL != piToMajorsList ) { piToMajorsList->Release(); piToMajorsList = NULL; }
    if ( NULL != piToMinorsList ) { piToMinorsList->Release(); piToMinorsList = NULL; }
    if ( NULL != piFromConnectionsList ) { piFromConnectionsList->Release(); piFromConnectionsList = NULL; }
    if ( NULL != piToConnectionsList ) { piToConnectionsList->Release(); piToConnectionsList = NULL; }
    if ( NULL != pShareDataList )
    {
       delete pShareDataList;  pShareDataList = NULL;
    }
    cout << "CAAPspLogicalLine::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
