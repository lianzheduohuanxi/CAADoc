// COPYRIGHT DASSAULT SYSTEMES  2003
//==========================================================================
//	Abstract: This sample shows how compute graphic representations in
//            batch mode.
//  Steps :
//    1.   Creates the section 
//    2.   Opens the Part document
//    3.   Retrieves the MechanicalPart feature of the Part document
//    4.   Creates a Path with the MechanicalPart feature of the Part document
//    5.   Retrieves the unique CATVisManager instance 
//    6.   Attaches the Path to manage by the CATVisManager
//      6.1 Creates the list of visualization interface 
//      6.2 Creates a default 3D viewpoint (vp)
//      6.3 Attaches the Path to the CATVisManager with the list and the vp    
//    7.   Retrieves the Graphic Representation of the MechanicalPart feature
//    8.   Computes the bounding box  
//    9.   Detachtes VP, root and liste interface 
//   10.   Closes the Part document 
//   11.   Closes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAGviVisuBatch InputPart
//
//   with InputPath: $WSROOT/CAAGeometryVisualization.edu/InputData/CAAVisuBatch.CATPart
//
//          
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

//ObjectModelerBase 
#include "CATSessionServices.h"      // Create_Session and Delete_Session
#include "CATInit.h"                 // To retrieve the root container
#include "CATDocumentServices.h"     // Open
#include "CATDocument.h"

// ObjectSpecModeler
#include "CATISpecObject.h"

// MecModInterfaces
#include "CATIPrtContainer.h"        // The root container of the Part document

// Visualization Framework
#include "CATVisManager.h"           // The object to create the graphic representation (rep)          
#include "CATI3DGeoVisu.h"           // The visualization interface for the reps 
#include "CATPathElement.h"          // To create a path with the object to compute the rep
#include "CAT3DViewpoint.h"          // To create a default viewpoint
#include "CAT3DBoundingSphere.h"     // To retrieve the bounding box associated with the rep

//Mathematics Framework
//#include "CATMathPoint.h"

// System Framework
#include "CATString.h"

// C++ library 
#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif


int main(int iArgc, char *iArgv[])

{
  //---------------------
  // 0- Checks arguments
  //---------------------

    if ( 2 != iArgc ) 
    {
       cout << endl;
       cout << "CAAGviVisuBatch InputPart "<< endl;
       cout <<" with InputPath: $WSROOT/CAAGeometryVisualization.edu/InputData/CAAVisuBatch.CATPart" <<endl;
       cout << endl;
       return 1;
    }

    cout << "The CAAGviVisuBatch main program begins ...."<< endl << endl;

  //------------------------------------------------------------------
  //1 - Creates Session
  //------------------------------------------------------------------
    
    char * pSessionName = "CAA_CreationSample_Session";
    CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionName,pSession);

    if (FAILED(rc) )
    {
       cout << "ERROR in creating session" << endl ;
       return 1;
    }

  //------------------------------------------------------------------
  //2 - Opens the Part document
  //------------------------------------------------------------------
    
    CATDocument* pPartDocument = NULL;
    CATString DocumentName = iArgv[1] ;
    rc = CATDocumentServices::OpenDocument(DocumentName.ConvertToChar(), pPartDocument);
    if (SUCCEEDED(rc) )
    {
       cout << "The Document: "<< DocumentName.ConvertToChar() <<" is opened" << endl ;
    }
    else
    {
       cout << "ERROR by opening the document= "<< DocumentName.ConvertToChar() << endl ;
       return 1;
    }
    
  //------------------------------------------------------------------
  //3 - Retrieves the MechanicalPart feature of the Part document
  //------------------------------------------------------------------
    
    CATInit * pInitOnDoc = NULL ;
    rc = pPartDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
    if ( FAILED(rc) )
    {
       cout << "Error in the CATInit interface"<< endl;
       return 1 ;
    }
 
    CATIPrtContainer * pISpecContainer= NULL ;
    pISpecContainer = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

    if ( NULL == pISpecContainer )
    {
       cout << "The root container, the specification container, is NULL"<< endl;
       return 1 ;
    }
  
    pInitOnDoc->Release();
    pInitOnDoc = NULL ;

    CATISpecObject_var spSpecObjectOnMechanicalPart = pISpecContainer->GetPart();

    if ( NULL_var == spSpecObjectOnMechanicalPart )
    {
       cout << "The MechanicalPart is NULL_var"<< endl;
       return 1 ;
    }

    pISpecContainer->Release();
    pISpecContainer = NULL ;

  //------------------------------------------------------------------
  //4 - Creates a Path with MechanicalPart feature of the Part document
  //------------------------------------------------------------------
    
    CATPathElement * pRootObjectPath = new CATPathElement(spSpecObjectOnMechanicalPart);

  //------------------------------------------------------------------
  //5 - Retrieves the unique CATVisManager instance 
  //------------------------------------------------------------------

    CATVisManager* pVisManager = CATVisManager::GetVisManager();
    if ( NULL == pVisManager )
    {
        cout <<" ERROR by retrieving the CATVisManager instance" << endl;
        return 1;
    }

  //------------------------------------------------------------------
  //6 - Attaches the Path to manage by the CATVisManager
  //------------------------------------------------------------------
    
    // 6-1 List of CATIVisu interfaces used to display the model 
    list<IID> ListIVisu3d;
    IID * pIIDInf = new IID(IID_CATI3DGeoVisu) ;
    ListIVisu3d.fastadd(pIIDInf);
 
    // 6-2 Creating a default 3D viewpoint
    CAT3DViewpoint * pVP = new CAT3DViewpoint();
    
    // 6-3 Attaching the root to the CATVisManager: The graphic representations
    //     are created.
    //
    rc = pVisManager->AttachTo ( pRootObjectPath, pVP, ListIVisu3d);
    if ( FAILED(rc) )
    {
        cout <<" ERROR in the AttachTo method" << endl;
        return 1;
    }
    
    delete pIIDInf;
    pIIDInf = NULL ;
    ListIVisu3d.empty();

    pRootObjectPath->Release();
    pRootObjectPath = NULL;
        
  //------------------------------------------------------------------
  //7 - Retrieves the Graphic Representation of the MechanicalPart feature
  //------------------------------------------------------------------
    
    CATI3DGeoVisu * pIVisuOnRoot =NULL ;    
    rc = spSpecObjectOnMechanicalPart->QueryInterface(IID_CATI3DGeoVisu,
                                                          (void **) & pIVisuOnRoot);
    if ( SUCCEEDED(rc) )
    {
       // GiveRep is the only one method to retrieve the rep associated with
       // an object. This method does not compute the rep. 
       // Do not release the rep returned by this method
       //
       CATRep * pRep = pIVisuOnRoot->GiveRep();
       if ( NULL != pRep )
       {
          CAT3DRep * p3DRep = (CAT3DRep *) pRep;

   // -------------------------------       
   // 8 - Retrieves the Bounding Box
   // -------------------------------

          CAT3DBoundingSphere pBe = p3DRep->GetBoundingElement();
          float radius = pBe.GetRadius();
          cout <<" The radius of the bounding box = " << radius << endl;
          /*
          CATMathPointf center = pBe.GetCenter();
          CATMathPoint Center ;
          center.GetValue(Center);
          cout <<" The center of the bounding box = " << Center.GetX() ;
          cout <<" " << Center.GetY() ;
          cout <<" " << Center.GetZ() << endl;
          */
       }

       pIVisuOnRoot->Release();
       pIVisuOnRoot = NULL ;

    }else
    {
        cout <<" ERROR to retrieve the CATI3DGeoVisu interface" << endl;
        return 1;
    }

  //------------------------------------------------------------------
  //9 - Detach the VP, the root and the list of interfaces 
  //------------------------------------------------------------------

    rc = pVisManager->DetachFrom(pVP,0) ;
    if ( FAILED(rc) )
    {
        cout <<" ERROR in the DetachFrom method" << endl;
        return 1;
    }

    pVP->Release();
    pVP = NULL ;

  //------------------------------------------------------------------
  //10 - Closes the Part Document 
  //------------------------------------------------------------------

    rc = CATDocumentServices::Remove (*pPartDocument);
    if (SUCCEEDED(rc)) 
    {
       cout << endl << "The Document "<< DocumentName.ConvertToChar() << " is closed OK" << endl ;
    }
    else
    {
       cout << "ERROR in closing document "<< DocumentName.ConvertToChar() << endl ;
       return 1;
    }
    pPartDocument = NULL ;

  //------------------------------------------------------------------
  //11 - Deletes the session 
  //------------------------------------------------------------------

    rc = ::Delete_Session(pSessionName);
    if (FAILED(rc) )
    {
       cout << "ERROR in delete session" << endl ;
       return 1;
    }

    cout << "The CAAGviVisuBatch main program is ended."<< endl << endl;

    return 0;
}

