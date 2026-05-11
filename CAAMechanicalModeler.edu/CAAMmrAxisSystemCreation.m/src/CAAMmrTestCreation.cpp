// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Use Case  for   : Mechanical Modeler
//
// Abstract        : It is an use case about the axis systems. It explains how to create:
//                     - a standard,
//                     - an axis rotation,
//                     - an euler ,
//                     - an explicit 
//                   axis system with the CATIMf3DAxisSystem and CATIMf3DAxisSystemFactory 
//                   interfaces.
//
//
// Steps :
//    1-    Checks the arguments
//    2-    Creates the session
//    3-    Opens the Part Document
//    4-    Retrieves the CATFeatCont container, the specification container
//    5-    Retrieves the MechanicalPart feature from the Part document
//    6-    Retrieves a CATIMf3DAxisSystemFactory interface pointer
//    7-    Creates a standard axis system (AS_Standard)
//    8-    Creates an axis rotation axis system (AS_AxisRotation)
//    9-    Creates an euler axis system  (AS_EulerAngles)
//    10-   Creates an axis system (AS_AxisStandardOriAxisDir) from the AS_Standard 
//    11-   Creates an explicit axis system (AS_Explicit)
//    12-   Releases the useless pointer
//    13-   Saves as the Part document
//    14-   Closes the document
//    15-   Deletes the session
// 
//==========================================================================
// How to execute :
//
//   mkrun -c "CAAMmrAxisSystemCreation  InputPath [OutputPath]"
//
//   with     InputPath  : The CAAAxisSystemCreation Part document path. You will find it in:
//                           
//                         Unix : InstallRootDirectory/CAAMechanicalModeler.edu/InputData 
//                         Windows : InstallRootDirectory\CAAMechanicalModeler.edu\InputData 
//
//                         Some axis systems are created by using features included in this
//                         Part document.
//
//            OutputPath : The output path where the CAAAxisSystemCreation_Save Part document 
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

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"       // for update

// MecModInterfaces Framework
#include "CATIPrtContainer.h"    

// MechanicalModeler Framework
#include "CATIMf3DAxisSystem.h"         // axis system interface access
#include "CATIMf3DAxisSystemFactory.h"  // to create axis system

// GSMInterfaces Framework
#include "CATIGSMPointCoord.h"          // to modify point coordinates

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathAxis.h"
#include "CATMathConstant.h"  // for CATPI

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// Local Framework
#include "CAAMmrGetGeometry.h"          // To retrieve some features interactively created
#include "CAAMmrRetrieveCornerAndVectorsFromPad.h" // To create Brep features (2 edges) from a Pad

// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"
#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

//============================================================================================

int UpdateAndDisplayCharacteristics(CATUnicodeString iAxisSystemName,
                          CATIMf3DAxisSystem_var spIAxisSystem,
                          CATAxisSystemIsDirect  iDirect,
                          CATAxisSystemType      iAxisSystemType)
{
  // Changes the axis system name
  CATIAlias * pAliasOnAxisSystem = NULL ;
  HRESULT rc = spIAxisSystem->QueryInterface(IID_CATIAlias,(void **) &pAliasOnAxisSystem);
  if ( FAILED(rc) )
  {
      cout <<"   The  axis system should implement CATIAlias" << endl;
      return 1;
  }
  pAliasOnAxisSystem->SetAlias(iAxisSystemName);
  pAliasOnAxisSystem->Release();
  pAliasOnAxisSystem = NULL ;

  // Updates to take account of the axis system inputs (Origin point, axis direction, axis rotation ref)
  // The update operation is not necessary if the axis system is without feature input.
  //
  CATISpecObject * pSpecObjectOnAxisSystem = NULL ;
  rc = spIAxisSystem->QueryInterface(IID_CATISpecObject,(void **) &pSpecObjectOnAxisSystem);
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

  // Displays the axis system parameters
  CATICkeParm_var ListParm[4][3] ;
  spIAxisSystem->GetParm(ListParm);

  CATUnicodeString Text [] = {"Origin", "X Axis","Y Axis","Z Axis"} ;
  int i = 0;
  for(i=0 ; i <= 3 ; i++)
  {
     CATICkeParm_var AxisX = ListParm[i][0] ;
     CATICkeParm_var AxisY = ListParm[i][1] ;
     CATICkeParm_var AxisZ = ListParm[i][2] ;
     cout <<"      " << Text[i].ConvertToChar() <<"   X= "   << AxisX->Show().ConvertToChar() << ",";
     cout <<"          Y= " << AxisY->Show().ConvertToChar() << ",";
     cout <<"          Z= " << AxisZ->Show().ConvertToChar() <<endl;
  }

  // Displays the axis direction types
  CATUnicodeString DirType [] = {"Same Dir", "Coord","Opposite Dir"} ;
  CATAxisSystemDirectionType SystemAxisType;
  for( i= 0 ; i < 3 ; i++)
  {
     spIAxisSystem->GetAxisType(CATAxisSystemXYZNumber(i+1),SystemAxisType);
     cout <<"      " << Text[i+1].ConvertToChar() <<" is " << DirType[SystemAxisType].ConvertToChar() << endl;
  }

  // Checks the axis system orientation. 
  CATUnicodeString Direct [] ={"Indirect", "Direct","Not Orthogonal"} ;
  CATAxisSystemIsDirect IsDirectAxis ;
  spIAxisSystem->IsDirect(IsDirectAxis);
  if ( iDirect != IsDirectAxis )
  {
      cout <<" Error: The new axis should be" << Direct[iDirect].ConvertToChar()<< endl;
      return 1;
  }else cout <<"      The new axis system is" << Direct[iDirect].ConvertToChar() << endl;

  // Checks the axis system type
  CATUnicodeString ASType [] ={"Standard", "Axis Rotation","Euler Angles"} ;
  CATAxisSystemType AxisSystemType ;
  spIAxisSystem->GetAxisSystemType(AxisSystemType);
  if ( iAxisSystemType != AxisSystemType )
  {
      if ( iAxisSystemType <= 2 )
      {
         cout <<" Error: The new axis should be " << ASType[iAxisSystemType].ConvertToChar() << endl;
      }else cout <<" The new axis should be explicit " << endl;
      return 1;
  }else 
  {
      if ( iAxisSystemType <= 2 )
      {
         cout <<"      The new axis is " << ASType[iAxisSystemType].ConvertToChar() << endl;
      }else cout <<"      The new axis is explicit " << endl;
  }

  return 0 ;
}

//============================================================================================

int main(int iArgc, char *iArgv[])

{
  //---------------------
  // 1- Checks arguments
  //---------------------
  if ((3 != iArgc) && ( 2 != iArgc) )
  {
     cout << endl;
     cout << "CAAMmrAxisSystemCreation InputPath [OutputPath]"<< endl;
     cout << "with : InputPath : InstallRootDirectory/CAAMechanicalModeler.edu/InputData"<< endl;
     cout <<"        OutputPath: Directory to save as the Part document"<<endl;
     cout << endl;
     return 1;
  }

  cout << "The CAAMmrAxisSystemCreation main program begins ...."<< endl << endl;

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
  CATString InputData = iArgv[1] ;
  CATString DocumentName =InputData + Slash + "CAAAxisSystemCreation.CATPart";

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
  //5- Retrieves the MechanicalPart feature
  //----------------------------------------------------------
  CATISpecObject_var spSpecObjectOnPart = pIPrtContOnDocument->GetPart();
  if ( NULL_var == spSpecObjectOnPart )
  {
     cout << "The MechanicalPart is NULL"<< endl;
     return 1 ;
  }

  //----------------------------------------------------------
  //6- Retrieves a CATIMf3DAxisSystemFactory interface pointer
  //----------------------------------------------------------
  CATIMf3DAxisSystemFactory * pIMf3DAxisSystemFactoryOnFeatCont = NULL ;
  rc = pIPrtContOnDocument->QueryInterface(IID_CATIMf3DAxisSystemFactory,
                                      (void **) & pIMf3DAxisSystemFactoryOnFeatCont);
  if ( FAILED(rc) )
  {
     cout <<"Error, CATFeatCont does not implement CATIMf3DAxisSystemFactory" << endl;
     return 1;
  }

  pIPrtContOnDocument->Release();
  pIPrtContOnDocument = NULL ;

  // -----------------------------------------------------------
  // 7- Creates a Standard axis system  
  // -----------------------------------------------------------
  CATMathPoint Origin (150.0,.0,.0);
  CATMathVector X (1.0,.0,.0);
  CATMathVector Y (0.0,1.0,.0);

  CATIMf3DAxisSystem_var NewAxisSystemStd ;
  rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(Origin,X,Y,NewAxisSystemStd);
  if ( FAILED(rc) )
  {
     cout <<"Error in Standard CreateAxisSytem creation" << endl;
     return 1;
  }
  cout << endl <<"   Creation of the Standard axis system" << endl;
  
  // Retrieves the Pad 
  //
  CATBaseUnknown * pPad = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnPart,"Pad.1",&pPad);
  if ( FAILED(rc) || ( NULL == pPad) )
  {
     cout << " Pad not found" << endl;
     return 1 ;
  }

  CATBaseUnknown *pVectorX = NULL;
  CATBaseUnknown *pVectorY = NULL;
  rc = ::CAAMmrRetrieveCornerAndVectorsFromPad(pPad,&pVectorX,&pVectorY);
  if ( FAILED(rc) )
  {
      cout <<" Error by retrieving the corner or the three vectors from the pad" << endl;
      return 1;
  }
  
  // The three vectors are BRep feature too.
  // The last vector (on Z axis) is not set, to ensure a direct axis system
  //
  NewAxisSystemStd->SetAxisDirection(CATAxisSystemXNumber, pVectorX);
  NewAxisSystemStd->SetAxisDirection(CATAxisSystemYNumber, pVectorY);
 

  // Updates and Displays axis system characteristics
  int val = UpdateAndDisplayCharacteristics("AS_Standard", NewAxisSystemStd,
                                  CATAxisSystemDirect,
                                  CATAxisSystemStandard);
  if ( 0 != val ) return val ;

  pVectorX->Release(); pVectorX = NULL ;
  pVectorY->Release(); pVectorY = NULL ;

  // -----------------------------------------------------------
  // 8- Creates a Rotation axis system  
  // -----------------------------------------------------------

  CATMathAxis MathAxis ;
  CATIMf3DAxisSystem_var NewAxisSystemRot;
  rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(MathAxis,NewAxisSystemRot);
  if ( FAILED(rc) )
  {
     cout <<"Error in Rotation CreateAxisSytem" << endl;
     return 1;
  }
  cout << endl <<"   Creation of the Rotation axis system" << endl;

  // 8-a Searchs the geometries in the input Part document
  CATBaseUnknown * pPoint5 = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnPart,"Point.5",&pPoint5);
  if ( FAILED(rc) || ( NULL == pPoint5) )
  {
     cout << " Point.5 not found" << endl;
     return 1 ;
  }
  CATBaseUnknown * pLineD1 = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnPart,"D1",&pLineD1);
  if ( FAILED(rc) || (NULL ==pLineD1) )
  {
     cout << " D1 not found" << endl;
     return 1 ;
  }
  CATBaseUnknown * pLineD2 = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnPart,"D2",&pLineD2);
  if ( FAILED(rc) || (NULL ==pLineD2) )
  {
     cout << " D2 not found" << endl;
     return 1 ;
  }

  // Modifies the axis system 
  NewAxisSystemRot->SetOriginPoint(pPoint5);

  // Changes the type of the axis system 
  NewAxisSystemRot->SetAxisSystemType(CATAxisSystemAxisRotation);

  // "Deselect" all the axes to control the axis order
  NewAxisSystemRot->SetAxisType(CATAxisSystemXNumber,CATAxisSystemSameDirection);
  NewAxisSystemRot->SetAxisType(CATAxisSystemYNumber,CATAxisSystemSameDirection);
  NewAxisSystemRot->SetAxisType(CATAxisSystemZNumber,CATAxisSystemSameDirection); 

  // The Y axis is the rotation's axis because it is the first axis
  // The D1 line defined the rotation's axis direction
  //
  NewAxisSystemRot->SetAxisDirection(CATAxisSystemYNumber,pLineD1);

  // The D2 line will be projected in the orthogonal plane to D1.
  // The projected line defines the reference for the rotation. 
  NewAxisSystemRot->SetAxisRotationReference(pLineD2);
  
  // The rotation from the reference's geometry is 90 degrees
  // 
  CATICkeParm_var RotationParm ;
  NewAxisSystemRot->GetAxisRotationParm(RotationParm);
  if ( NULL_var != RotationParm )
  {
     // The valuate method is in MKS 
     RotationParm->Valuate(CATPI/2); // 
  }else 
  {
      cout <<" The axis rotation parameter is NULL" << endl; 
      return 1;
  }

   // Updates and Displays axis system characteristics
  val = UpdateAndDisplayCharacteristics("AS_AxisRotation", NewAxisSystemRot,
                                  CATAxisSystemDirect,
                                  CATAxisSystemAxisRotation);
  if ( 0 != val ) return val ;

  // -----------------------------------------------------------
  // 9- Creates an Euler axis system  
  // -----------------------------------------------------------
  CATMathAxis MathAxisEuler ;
  CATMathPoint OriginEuler (.0,200.0,.0);
  MathAxisEuler.SetOrigin(OriginEuler);

  CATIMf3DAxisSystem_var NewAxisSystemEuler;
  rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(MathAxisEuler,NewAxisSystemEuler);
  if ( FAILED(rc) )
  {
     cout <<"Error in Euler CreateAxisSytem" << endl;
     return 1;
  }
  cout << endl <<"   Creation of the Euler axis system" << endl;

  // Changes the type of the axis system 
  NewAxisSystemEuler->SetAxisSystemType(CATAxisSystemEulerAngles);

  // Modifies the axis system 
  
  CATICkeParm_var EulerAngles[3] ;
  NewAxisSystemEuler->GetEulerAnglesParm(EulerAngles);
  if ( (NULL_var != EulerAngles[0]) && (NULL_var != EulerAngles[1]) &&
       (NULL_var != EulerAngles[2]) )
  {
     // The valuate method is in MKS 
     EulerAngles[0]->Valuate(CATPI/2);  
     EulerAngles[1]->Valuate(CATPI/2);  
     EulerAngles[2]->Valuate(CATPI/2);  
  }else 
  {
      cout <<" At least one euler angle parm is null" << endl; 
      return 1;
  }

  // Updates and Displays axis system characteristics
  val = UpdateAndDisplayCharacteristics("AS_EulerAngles",NewAxisSystemEuler,
                                  CATAxisSystemDirect,
                                  CATAxisSystemEulerAngles);
  if ( 0 != val ) return val ;

  // -----------------------------------------------------------
  // 10- Copy Const  
  // -----------------------------------------------------------

  CATIMf3DAxisSystem_var NewAxisSystemCopyConst;
  rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(NewAxisSystemStd,
                                                           NewAxisSystemCopyConst);
  if ( FAILED(rc) )
  {
     cout <<"Error in Copy Const CreateAxisSytem" << endl;
     return 1;
  }
  cout << endl <<"   Creation of the Copy Const axis system from the first axis system" << endl;

  // The origin of the new axis is at the origin of the three axis directions
  NewAxisSystemCopyConst->SetOriginType(CATAxisSystemPoint);
  NewAxisSystemCopyConst->SetOriginPoint(NULL_var);

  CATAxisSystemPointType SystemPointType ;
  NewAxisSystemCopyConst->GetOriginType(SystemPointType);
  if ( CATAxisSystemPoint != SystemPointType )
  {
      cout <<" NewAxisSystemCopyConst should be CATAxisSystemPoint" << endl;
      return 1;
  }

  // Updates and Displays axis system characteristics
  
  val = UpdateAndDisplayCharacteristics("AS_AxisStandardOriAxisDir", NewAxisSystemCopyConst,
                                  CATAxisSystemDirect,
                                  CATAxisSystemStandard);
  if ( 0 != val ) return val ;

  // -----------------------------------------------------------
  // 11- Explicit Axis System  
  // -----------------------------------------------------------
  CATIMf3DAxisSystem_var NewAxisSystemExplicit;
  CATMathAxis MathAxisExplicit ;
  rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(MathAxisExplicit,
                                                           NewAxisSystemExplicit);
  if ( FAILED(rc) )
  {
     cout <<"Error in Explicit CreateAxisSytem" << endl;
     return 1;
  }
  cout << endl <<"   Creation of the Explicit axis system" << endl;

  CATBaseUnknown * pPoint7 = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnPart,"Point.7",&pPoint7);
  if ( FAILED(rc) || ( NULL == pPoint7) )
  {
     cout << " Point.7 not found" << endl;
     return 1 ;
  }
  
  CATBaseUnknown * pLineD3 = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnPart,"D3",&pLineD3);
  if ( FAILED(rc) || (NULL == pLineD3) )
  {
     cout << " D3 not found" << endl;
     return 1 ;
  }

  // To modify the axis order
  NewAxisSystemExplicit->SetAxisType(CATAxisSystemXNumber,CATAxisSystemSameDirection);
  NewAxisSystemExplicit->SetAxisType(CATAxisSystemYNumber,CATAxisSystemSameDirection);
  NewAxisSystemExplicit->SetAxisType(CATAxisSystemZNumber,CATAxisSystemSameDirection);

  // Modifies the axis system 
  NewAxisSystemExplicit->SetOriginPoint(pPoint7);
  NewAxisSystemExplicit->SetAxisDirection(CATAxisSystemYNumber,pLineD1);
  NewAxisSystemExplicit->SetAxisDirection(CATAxisSystemZNumber,pLineD2);
  NewAxisSystemExplicit->SetAxisDirection(CATAxisSystemXNumber,pLineD3);

  // Updates and Displays axis system characteristics
  val = UpdateAndDisplayCharacteristics("AS_Explicit", NewAxisSystemExplicit,
                                  CATAxisSystemIndirect,
                                  CATAxisSystemStandard);
  if ( 0 != val ) return val ;

  cout <<"      The axis system becomes direct and the origin position is changed" << endl; 

  // Changes the Z direction, the axis system should become direct
  NewAxisSystemExplicit->SetAxisType(CATAxisSystemZNumber,CATAxisSystemOppositeDirection);
 
  // Changes the Origin position
  CATIGSMPointCoord *pGSMPointCoordOnP7 = NULL ;
  rc = pPoint7->QueryInterface(IID_CATIGSMPointCoord,(void **) &pGSMPointCoordOnP7);
  if ( SUCCEEDED(rc) )
  {
     CATICkeParm_var Xnew,Ynew,Znew ;
     pGSMPointCoordOnP7->GetCoordinates(Xnew,Ynew,Znew);
     
     Xnew->Valuate(-0.1); 
     Ynew->Valuate(0.0); 
     Znew->Valuate(0.0);
    
     pGSMPointCoordOnP7->Release();
     pGSMPointCoordOnP7 = NULL ;
  }

  // Updates and Displays axis system characteristics
  val = UpdateAndDisplayCharacteristics("AS_Explicit", NewAxisSystemExplicit,
                                  CATAxisSystemDirect,
                                  CATAxisSystemStandard);
  if ( 0 != val ) return val ;

  cout <<"      The axis system becomes explicit" << endl; 
  NewAxisSystemExplicit->SetAxisSystemType(CATAxisSystemExplicit);

  cout <<"      The Point.7 position changement is without effect on the explicit axis system" << endl;
  pGSMPointCoordOnP7 = NULL ;
  rc = pPoint7->QueryInterface(IID_CATIGSMPointCoord,(void **) &pGSMPointCoordOnP7);
  if ( SUCCEEDED(rc) )
  {
     CATICkeParm_var Xnew,Ynew,Znew ;
     pGSMPointCoordOnP7->GetCoordinates(Xnew,Ynew,Znew);
     
     Xnew->Valuate(-0.2); 
     Ynew->Valuate(0.0); 
     Znew->Valuate(0.0);
    
     pGSMPointCoordOnP7->Release();
     pGSMPointCoordOnP7 = NULL ;
  }

  // Updates and Displays axis system characteristics
  val = UpdateAndDisplayCharacteristics("AS_Explicit", NewAxisSystemExplicit,
                                  CATAxisSystemDirect,
                                  CATAxisSystemExplicit);
  if ( 0 != val ) return val ;

  // The update of the axis system is without effect on the Point.7
  // since the axis system is explicit. So the Point.7 update is
  // necessary
  CATISpecObject * pSpecObjOnP7 = NULL ;
  rc = pPoint7->QueryInterface(IID_CATISpecObject,(void **) &pSpecObjOnP7);
  if ( FAILED(rc) )
  {
      cout <<"   The  axis system should implement CATISpecObject" << endl;
      return 1;
  }

  CATTry
  {
     pSpecObjOnP7->Update();
  }
  CATCatch(CATError,error)
  {
     cout<< error->GetNLSMessage().ConvertToChar() << endl;
     Flush(error);
     return 1 ;
  }
  CATEndTry

  pSpecObjOnP7->Release();
  pSpecObjOnP7 = NULL;

  // -----------------------------------------------------------
  // 12- Releases the useless pointers
  // -----------------------------------------------------------
  pIMf3DAxisSystemFactoryOnFeatCont->Release();
  pIMf3DAxisSystemFactoryOnFeatCont = NULL ;

  pPoint5->Release(); pPoint5 = NULL ;
  pPoint7->Release(); pPoint7 = NULL ;
  pLineD1->Release(); pLineD1 = NULL ;
  pLineD2->Release(); pLineD2 = NULL ;
  pLineD3->Release(); pLineD3 = NULL ;
  pPad->Release();    pPad    = NULL ;

  // -----------------------------------------------------------
  // 13- Saves as the document 
  // -----------------------------------------------------------

  CATString DocumentSaveAsName = "CAAAxisSystemCreation_Save.CATPart" ;
  if ( 3 == iArgc )
  {
     CATString OutputPath = iArgv[2] ;
     DocumentSaveAsName = OutputPath + Slash + DocumentSaveAsName ;
  }

  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pModel,DocumentSaveAsName.ConvertToChar());
  if (S_OK == rc)
  {
     cout << endl;
     cout << "      The Part document is saved in:"<< DocumentSaveAsName.ConvertToChar() << endl ;
  }
  else
  {
     cout << "Error by saving:"<< DocumentSaveAsName.ConvertToChar() << endl;
     return 1;
  }

  //------------------------------------------------------------------
  //14- Closes the document
  //------------------------------------------------------------------
  rc = CATDocumentServices::Remove (*pModel);
  if ( FAILED(rc) )
  {
      cout <<"Error by closing the Part document" << endl;
      return 1;
  }
  pModel = NULL ;
  
  //------------------------------------------------------------------
  //15- Closes the session
  //------------------------------------------------------------------
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc) )
  {
     cout << "ERROR in delete session" << endl ;
     return 1;
  }

  cout << endl << "The CAAMmrAxisSystemCreation main program ends ...."<< endl << endl;

  return 0;
}
