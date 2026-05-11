// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Use Case  for   : Mechanical Modeler
//
// Abstract        : It is an use case about the axis systems. It enables to set
//                   an axis system as current and to transform the origin of 
//                   the absolute axis system (0,0,0) in the current axis system. 
//                   The CATIMf3DAxisSystem and CATIMf3DAxisSystemManager 
//                   interfaces are mainly used.
//
// 
// Steps :
//    1-    Checks the arguments
//    2-    Creates the session
//    3-    Opens the Part Document
//    4-    Retrieves the CATFeatCont container, the specification container
//    5-    Retrieves a CATIMf3DAxisSystemManager interface pointer
//    6-    Displays the count of axis systems
//    7-    Retrieves the current axis system
//    8-    Finds the new current axis system in the list
//    9-    Sets the new current axis system
//    10-   Displays the current axis system parameters
//    11-   Transforms the (0,0,0) point in the current axis system .
//    12-   Transforms the (0.0,0.0,1.0) vector in the current axis system 
//    13-   Releases the useless pointer
//    14-   Saves as the Part document
//    15-   Closes the document
//    16-   Deletes the session
// 
//==========================================================================
// How to execute :
//
//   mkrun -c "CAAMmrAxisSystemManagement Filename CurrentAS [OutputPath]"
//
//   with     Filename   : The Part document path containing axis system. You can use  
//                         CAAAxisSystemCreation_Save that you find in:
//                           
//                         Unix : InstallRootDirectory/CAAMechanicalModeler.edu/InputData 
//                         Windows : InstallRootDirectory\CAAMechanicalModeler.edu\InputData 
//
//            CurrentAS  : The name of the axis system to set current. If the string is "AbsoluteAS"
//                         the absolute axis system becomes the current one.
//
//            OutputPath : The output path where the CAAMmrAxisSystemManagement Part document 
//                         will be saved. If this path is empty, the file will be saved in 
//                         the current directory. 
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

// MecModInterfaces Framework
#include "CATIPrtContainer.h"    

// MechanicalModeler Framework
#include "CATIMf3DAxisSystem.h"         // axis system interface access
#include "CATIMf3DAxisSystemManager.h"  // to list all the axis systems and set a current one
#include "CATListOfCATIMf3DAxisSystem.h"

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathAxis.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

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
  if ((4 != iArgc) && ( 3 != iArgc) )
  {
     cout << endl;
     cout << "CAAMmrAxisSystemManagement Filename CurrentAS [OutputPath]"<< endl;
     cout << "with   Filename : The complete filename of a Part document containing axis systems." <<endl;
     cout << "                  You can use CAAAxisSystemCreation_Save located in:" << endl;
     cout<<  "                  InstallRootDirectory/CAAMechanicalModeler.edu/InputData/ " << endl;
     cout << "       CurrentAS : The name of the axis system to set as current. with 'AbsoluteAS' " <<endl;
     cout << "                    the absolute axis system becomes the current one." << endl;
     cout <<"        OutputPath: Directory to save as the input Part document"<<endl;
     cout << endl;
     return 1;
  }

  cout << "The CAAMmrAxisSystemManagement main program begins ...."<< endl << endl;

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
  //3- Opens the Part document
  //------------------------------------------------------------------
  CATDocument *pModel = NULL;
  CATString DocumentName = iArgv[1] ;
 
  rc = CATDocumentServices::OpenDocument(DocumentName.ConvertToChar(), pModel);

  if (FAILED(rc) )
  {
     cout << "ERROR by opening the document= "<< DocumentName.ConvertToChar() << endl ;
     return 1;
  }else
  {
     cout << "   " << DocumentName.ConvertToChar() << " is open" <<endl << endl;
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
  //5- Retrieves a CATIMf3DAxisSystemManager interface pointer
  //----------------------------------------------------------
  CATIMf3DAxisSystemManager * pIMf3DAxisSystemManagerOnFeatCont = NULL ;
  rc = pIPrtContOnDocument->QueryInterface(IID_CATIMf3DAxisSystemManager,
                                      (void **) & pIMf3DAxisSystemManagerOnFeatCont);
  if ( FAILED(rc) )
  {
     cout <<"Error, CATFeatCont does not implement CATIMf3DAxisSystemManager" << endl;
     return 1;
  }

  pIPrtContOnDocument->Release();
  pIPrtContOnDocument = NULL ;

  //----------------------------------------------------------
  //6- Displays the count of axis systems
  //----------------------------------------------------------

  CATLISTV(CATIMf3DAxisSystem_var) ListAxisSystem ;
  rc = pIMf3DAxisSystemManagerOnFeatCont->GetAxisSystems(ListAxisSystem);
  if ( FAILED(rc) )
  {
      cout <<" GetAxisSystem failed" << endl;
      return 1;
  }

  int nbAS = ListAxisSystem.Size();
  cout <<"   There are " << nbAS << " axis system(s) in the document" << endl;
  for ( int i= 1 ; i <= nbAS  ; i++)
  {
     CATIMf3DAxisSystem_var spMf3DAxisSystemOnAS = ListAxisSystem[i] ;
     if ( NULL_var != spMf3DAxisSystemOnAS )
     {
        CATIAlias_var spAliasOnCurrentAS = spMf3DAxisSystemOnAS ;
        if ( NULL_var != spAliasOnCurrentAS )
        {
            cout<<"      "<< spAliasOnCurrentAS->GetAlias().ConvertToChar() << endl;
        }
     }
  }
  cout << endl;

  //----------------------------------------------------------
  //7- Retrieves the current axis system
  //----------------------------------------------------------
  CATIMf3DAxisSystem_var spMf3DAxisSystemOnCurrentAS ;
  rc = pIMf3DAxisSystemManagerOnFeatCont->GetCurrentAxisSystem(spMf3DAxisSystemOnCurrentAS);
  if ( FAILED(rc) )
  {
      cout <<" GetCurrentAxisSystems failed" << endl;
      return 1;
  }

  CATUnicodeString OldCurrentAxisName ="AbsoluteAS" ;
  if ( NULL_var != spMf3DAxisSystemOnCurrentAS )
  {
      CATIAlias_var spAliasOnCurrentAS = spMf3DAxisSystemOnCurrentAS ;
      if ( NULL_var != spAliasOnCurrentAS )
      {
         OldCurrentAxisName = spAliasOnCurrentAS->GetAlias();
         cout <<"   The current Axis is:" << OldCurrentAxisName.ConvertToChar() << endl;
      }else 
      {
         cout <<" The Axis System should implement CATIAlias" << endl;
         return 1;
      }
  }else cout <<"   There is no current axis system" << endl;

  //----------------------------------------------------------
  //8- Finds the new current axis system in the list
  //----------------------------------------------------------
  CATUnicodeString NewCurrentAxisName = iArgv[2] ;
  CATUnicodeString AbsoluteAS = "AbsoluteAS" ;
  CATBoolean Found = FALSE ;

  if ( (AbsoluteAS != NewCurrentAxisName) && (OldCurrentAxisName != NewCurrentAxisName) )
  {
      int i = 1 ;
      while ( (FALSE == Found) && ( i<= nbAS ))
      {
          CATIMf3DAxisSystem_var spMf3DAxisSystem = ListAxisSystem[i];
          if ( NULL_var != spMf3DAxisSystem )
          {
             CATIAlias_var spAliasOnCurrentAS = spMf3DAxisSystem ;
             if ( NULL_var != spAliasOnCurrentAS )
             {
                if ( NewCurrentAxisName == spAliasOnCurrentAS->GetAlias() )
                {
                    Found = TRUE ;
                    spMf3DAxisSystemOnCurrentAS = spMf3DAxisSystem;
                }
             }
          }
          i++ ;
      }
      if ( FALSE == Found)
      {
         cout << "   The  " << NewCurrentAxisName.ConvertToChar() <<" has not been found" << endl;
         NewCurrentAxisName = OldCurrentAxisName ;
      }
  }

  //----------------------------------------------------------
  //9- Sets the new current axis system 
  //----------------------------------------------------------

  if ( AbsoluteAS == NewCurrentAxisName)
  {
     rc = pIMf3DAxisSystemManagerOnFeatCont->SetCurrentAxisSystem(NULL_var);
     if ( FAILED(rc) )
     {
         cout <<" SetCurrentAxisSystems NULL_var failed" << endl;
         return 1;
     }
  }else if ( TRUE == Found )
  {
     rc = pIMf3DAxisSystemManagerOnFeatCont->SetCurrentAxisSystem(spMf3DAxisSystemOnCurrentAS);
     if ( FAILED(rc) )
     {
         cout <<" SetCurrentAxisSystems NULL_var failed" << endl;
         return 1;
     }
     
  }
  
  cout <<"   The "<< NewCurrentAxisName.ConvertToChar() ; 
  cout << " axis system is the current one" << endl << endl;

  //----------------------------------------------------------
  //10- Displays the current axis system parameters
  //----------------------------------------------------------
  
  if ( AbsoluteAS != NewCurrentAxisName) 
  {
     CATICkeParm_var ListParm[4][3] ;
     spMf3DAxisSystemOnCurrentAS->GetParm(ListParm);
  
     CATUnicodeString Text [] = {"Origin", "X Axis","Y Axis","Z Axis"} ;
     for( int i= 0 ; i <= 3 ; i++)
     {
        CATICkeParm_var AxisX = ListParm[i][0] ;
        CATICkeParm_var AxisY = ListParm[i][1] ;
        CATICkeParm_var AxisZ = ListParm[i][2] ;
        cout <<"      " << Text[i].ConvertToChar() <<"   X= "   << AxisX->Show().ConvertToChar() << ",";
        cout <<"          Y= " << AxisY->Show().ConvertToChar() << ",";
        cout <<"          Z= " << AxisZ->Show().ConvertToChar() <<endl;
     }
  }
  cout << endl;

  //----------------------------------------------------------
  //11- Transforms the (0,0,0) point in the current axis system 
  //----------------------------------------------------------
  if ( AbsoluteAS != NewCurrentAxisName)
  {
     CATMathPoint PointToConvert (.0,.0,.0) ;
     CATMathPoint ConvertedPoint;
     
     rc = pIMf3DAxisSystemManagerOnFeatCont->ConvertPointCoordinates(TRUE,
                                                     PointToConvert,ConvertedPoint);
     if ( FAILED(rc) )
     {
         cout <<" ConvertPointCoordinates  failed" << endl;
         return 1;
     }

     cout <<"   Point Converted: X=" << ConvertedPoint.GetX() ;
     cout <<"   Y=" <<  ConvertedPoint.GetY() ;
     cout <<"   Z=" << ConvertedPoint.GetZ() << endl;
  }
  //----------------------------------------------------------
  //12- Transforms the (0.0,0.0,1.0) vector in the current axis system 
  //----------------------------------------------------------
  if ( AbsoluteAS != NewCurrentAxisName)
  {
 
     CATMathVector VectorToConvert (.0,.0,1.0) ;
     CATMathVector ConvertedVector;
     rc = pIMf3DAxisSystemManagerOnFeatCont->ConvertVectorCoordinates(TRUE,
                                                     VectorToConvert,ConvertedVector);
     if ( FAILED(rc) )
     {
         cout <<" ConvertVectorCoordinates  failed" << endl;
         return 1;
     }
     cout <<"   Vector Converted: X=" << ConvertedVector.GetX() ;
     cout <<"   Y=" <<  ConvertedVector.GetY() ;
     cout <<"   Z=" << ConvertedVector.GetZ() << endl;
  }

  // -----------------------------------------------------------
  // 13- Releases the useless pointers
  // -----------------------------------------------------------
  
  pIMf3DAxisSystemManagerOnFeatCont->Release();
  pIMf3DAxisSystemManagerOnFeatCont = NULL ;

  // -----------------------------------------------------------
  // 14- Saves as the document 
  // -----------------------------------------------------------

  CATString DocumentSaveAsName = "CAAAxisSystemManagement.CATPart" ;
  if ( 4 == iArgc )
  {
     CATString OutputPath = iArgv[3] ;
     DocumentSaveAsName = OutputPath + Slash + DocumentSaveAsName ;
  }

  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pModel,DocumentSaveAsName.ConvertToChar());
  if (S_OK == rc)
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
  //15- Closes the document
  //------------------------------------------------------------------
  rc = CATDocumentServices::Remove (*pModel);
  if ( FAILED(rc) )
  {
      cout <<"Error by closing the Part document" << endl;
      return 1;
  }
  pModel = NULL ;
  
  //------------------------------------------------------------------
  //16- Closes the session
  //------------------------------------------------------------------
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc) )
  {
     cout << "ERROR in delete session" << endl ;
     return 1;
  }

  cout << endl << "The CAAMmrAxisSystemManagement main program ends ...."<< endl << endl;

  return 0;
}
