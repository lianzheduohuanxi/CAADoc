// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Use Case  for   : Mechanical Modeler
//
// Abstract        : It is an use case about the axis systems. It enables to create 
//                   a sketch by using a plane of an axis system.
//                   The CATIMf3DAxisSystem and CATIMf3DAxisSystemFactory 
//                   interfaces are mainly used.
//
//
// Steps :
//    1-    Checks the arguments
//    2-    Creates the session
//    3-    Creates a Part Document
//    4-    Retrieves the CATFeatCont container, the specification container
//    5-    Retrieves a CATIMf3DAxisSystemFactory interface pointer
//    6-    Creates an axis system 
//    7-    Retrieves the BRep plane and featurizes it
//    8-    Creates the sketch
//    9-    Releases the useless pointer
//    10-   Save the Part document
//    11-   Closes the document
//    12-   Deletes the session
// 
//==========================================================================
// How to execute :
//
//   mkrun -c "CAAMmrAxisSystemBRep [Filename]"
//  
//   with   OutputPath : The  Part document with the new sketch.
//                       If this filename is empty, the CAAMmrAxisSystemBRep file 
//                       will be saved in the current directory.
//                        
//
//   
// Return code :
//   0 successful execution
//   1 execution failed
// 
//============================================================================================

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATIAlias.h"
#include "CATSession.h"


// ObjectSpecsModeler
#include "CATISpecObject.h"

// MecModInterfaces Framework
#include "CATIPrtContainer.h"
#include "CATIBRepAccess.h"  
#include "CATIFeaturize.h"   

// MechanicalModeler Framework
#include "CATIMf3DAxisSystem.h"         // axis system interface access
#include "CATIMf3DAxisSystemFactory.h"  // To create an axis system

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathAxis.h"

// SketcherInterfaces Framework
#include "CATISketchFactory.h"

// System Framework
#include "CATUnicodeString.h"
#include "CATBoolean.h"
#include "CATString.h"
#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

//============================================================================================

int main(int iArgc, char *iArgv[])

{
  //---------------------
  // 1- Checks arguments
  //---------------------
  if ((1 != iArgc) && ( 2 != iArgc) )
  {
     cout << endl;
     cout << "CAAMmrAxisSystemBRep [Filename]"<< endl;
     cout << "with Filename : The complete file name of the result Part document." << endl;
     cout << "                If the string is empty, the Part document is " << endl;
     cout << "                CAAMmrAxisSystemBRep.CATPart " << endl;
  
     cout << endl;
     return 1;
  }

  cout << "The CAAMmrAxisSystemBRep main program begins ...."<< endl << endl;

  //------------------------------------------------------------------
  //2 - Creates a Session
  //------------------------------------------------------------------
  char * pSessionName = "CAA_CreationSample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);

  if (FAILED(rc) )
  {
      cout << "ERROR by creating session" << endl ;
      return 1;
  }

  //------------------------------------------------------------------
  //3- Creates a Part document
  //------------------------------------------------------------------
  CATDocument *pModel= NULL;
  rc = CATDocumentServices::New("CATPart",pModel);

  if (FAILED(rc) )
  {
     cout << "ERROR by creating a Part document= "<< endl ;
     return 1;
  }

  //------------------------------------------------------------------
  //4- Retrieves CATFeatCont, the specification container
  //------------------------------------------------------------------
  CATInit * pInitOnDoc = NULL ;
  rc = pModel->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
  if ( FAILED(rc) )
  {
     cout << "Error in the CATInit interface"<< endl;
     return 1 ;
  }

  CATIPrtContainer * pIPrtContOnDocument = NULL ;
  pIPrtContOnDocument = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

  if ( NULL == pIPrtContOnDocument )
  {
     cout << "The root container is NULL"<< endl;
     return 1 ;
  }

  // No more need of this interface
  pInitOnDoc->Release();
  pInitOnDoc = NULL ;

  //----------------------------------------------------------
  //5- Retrieves the factory interface pointers
  //----------------------------------------------------------
  CATIMf3DAxisSystemFactory * pIMf3DAxisSystemFactoryOnFeatCont = NULL ;
  rc = pIPrtContOnDocument->QueryInterface(IID_CATIMf3DAxisSystemFactory,
                                      (void **) & pIMf3DAxisSystemFactoryOnFeatCont);
  if ( FAILED(rc) )
  {
     cout <<"Error, CATFeatCont does not implement CATIMf3DAxisSystemFactory" << endl;
     return 1;
  }

  CATISketchFactory * pISketchFactoryOnFeatCont = NULL ;
  rc = pIPrtContOnDocument->QueryInterface(IID_CATISketchFactory,
                                      (void **) & pISketchFactoryOnFeatCont);
  if ( FAILED(rc) )
  {
     cout <<"Error, CATFeatCont does not implement CATISketchFactory" << endl;
     return 1;
  }

  pIPrtContOnDocument->Release();
  pIPrtContOnDocument = NULL ;

  // -----------------------------------------------------------
  // 6- Creates an axis system
  // -----------------------------------------------------------
  CATMathPoint Origin (100.0,.0,.0);
  CATMathVector Xdir (1.0,0.0,.0);
  CATMathVector Ydir (0.0,0.0,1.0);

  CATIMf3DAxisSystem_var NewAxisSystem ;
  rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(Origin,Xdir,Ydir,NewAxisSystem);
  if ( FAILED(rc) )
  {
     cout <<"Error in the Axis System creation" << endl;
     return 1;
  }
  cout << endl <<"   Creation of an axis system" << endl;
  
  CATISpecObject * pSpecObjectOnAxisSystem = NULL ;
  rc = NewAxisSystem->QueryInterface(IID_CATISpecObject,(void **) &pSpecObjectOnAxisSystem);
  if ( FAILED(rc) )
  {
      cout <<"   The  axis system should implement CATISpecObject" << endl;
      return 1;
  }

  CATTry
  {
     pSpecObjectOnAxisSystem->Update();
  }
  CATCatch(CATError,error)
  {
     cout<< error->GetNLSMessage().ConvertToChar() << endl;
     Flush(error);
     return 1 ;
  }
  CATEndTry

  pSpecObjectOnAxisSystem->Release();
  pSpecObjectOnAxisSystem = NULL;

  // -----------------------------------------------------------
  // 7-    Retrieves the BRep plane and featurizes it
  // -----------------------------------------------------------
  CATIBRepAccess_var PlaneBRep ;
  rc = NewAxisSystem->GetPlaneBRepAccess(CATAxisSystemZNumber,PlaneBRep);

  if ( FAILED(rc) )
  {
     cout <<"Error in the Axis System BRep plane access" << endl;
     return 1;
  }

  CATIFeaturize * pIFeaturizeOnPlane = NULL ;
  rc = PlaneBRep->QueryInterface(IID_CATIFeaturize,(void **) &pIFeaturizeOnPlane);
  if ( FAILED(rc) )
  {
     cout <<"Error in the Axis System BRep plane QI CATIFeaturize" << endl;
     return 1;
  }

  CATISpecObject_var MFPlane = pIFeaturizeOnPlane->FeaturizeF();
  if ( NULL_var == MFPlane )
  {
     cout <<"Error in the Axis System BRep featurization" << endl;
     return 1;
  }

  pIFeaturizeOnPlane->Release();
  pIFeaturizeOnPlane = NULL ;

  // -----------------------------------------------------------
  // 8-  Creates the sketch
  // -----------------------------------------------------------

  CATISpecObject_var NewSketch = pISketchFactoryOnFeatCont->CreateSketch(MFPlane);
  if ( NULL_var == NewSketch )
  {
      cout <<"Error in the Sketch creation" << endl;
     return 1;
  }

  // -----------------------------------------------------------
  // 9- Releases the useless pointers
  // -----------------------------------------------------------
  
  pIMf3DAxisSystemFactoryOnFeatCont->Release();
  pIMf3DAxisSystemFactoryOnFeatCont = NULL ;

  pISketchFactoryOnFeatCont->Release();
  pISketchFactoryOnFeatCont = NULL ;

  // -----------------------------------------------------------
  // 10- Saves as the document 
  // -----------------------------------------------------------
  CATString DocumentSaveAsName = "CAAAxisSystemBRep.CATPart" ;
  if ( 2 == iArgc )
  {
     DocumentSaveAsName = iArgv[1] ;
  }
  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pModel,DocumentSaveAsName.ConvertToChar());
  if (SUCCEEDED(rc))
  {
     cout << endl;
     cout << "   The Part document is saved in:"<< DocumentSaveAsName.ConvertToChar() << endl ;
  }
  else
  {
     cout << "Error by saving:"<< DocumentSaveAsName.ConvertToChar() << endl;
     return 1;
  }

  //------------------------------------------------------------------
  //11- Closes the document
  //------------------------------------------------------------------
  rc = CATDocumentServices::Remove (*pModel);
  if ( FAILED(rc) )
  {
      cout <<"Error by closing the Part document" << endl;
      return 1;
  }
  pModel = NULL ;
  
  //------------------------------------------------------------------
  //12- Closes the session
  //------------------------------------------------------------------
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc) )
  {
     cout << "ERROR in delete session" << endl ;
     return 1;
  }

  cout << endl << "The CAAMmrAxisSystemBRep main program ends ...."<< endl << endl;

  return 0;
}
