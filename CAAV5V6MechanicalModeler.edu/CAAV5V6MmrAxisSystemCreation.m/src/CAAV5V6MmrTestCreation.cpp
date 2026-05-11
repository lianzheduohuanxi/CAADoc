// COPYRIGHT DASSAULT SYSTEMES 2012
//============================================================================================
//
// Mission        : It is a use case about the axis systems. It explains how to create:
//                     - a standard,
//                     - an axis rotation,
//                     - an euler ,
//                     - an explicit 
//                   axis system with the CATIMf3DAxisSystem and CATIMf3DAxisSystemFactory 
//                   interfaces.
//
// Note : CAAV5V6MmrTestCreation is the same use case as CAAMmrTestCreation. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//
// Steps :
//    1-    Checks the arguments
//    2-    Initializes the session
//    3-    Retrieves the MechanicalPart feature
//    4-    Retrieves a CATIMf3DAxisSystemFactory interface pointer
//    5-    Creates a standard axis system (AS_Standard)
//    6-    Creates an axis rotation axis system (AS_AxisRotation)
//    7-    Creates an euler axis system  (AS_EulerAngles)
//    8-    Creates an axis system (AS_AxisStandardOriAxisDir) from the AS_Standard 
//    9-    Creates an explicit axis system (AS_Explicit)
//    10-   Releases the useless pointers
//    11-   Saves the Session
//    12-   Closes the Session
//    
// 
//==========================================================================
// How to execute :
//
// In V6
// =====
//	 mkrun -c "CAAV5V6MmrAxisSystemCreation Repository Server UserId Password SecurityCtx PLMRepType PLMExternalIDValue Version"
//
//	 where    Repository	: The name of the repository (or provider) 
//			  Server		: The server as Host:Port_number/RootURI
//			  User			: The user identifier
//            Password		: The user password  
//			  SecurityCtx   : A string representing the security context (Role.Organization.Project)
//							  Choose Role as Designer ( as the use case modifies the PLM Data )
//			  PLMrepType    : A string representing PLM Representation type  
//			  PLMExternalIDValue : the value of the PLM_ExternalID attribute of a PLM representation reference. 
//			  Version       : the value of the V_version attribute of a PLM representation reference. 
// 
//
// In V5
// =====
//   mkrun -c "CAAV5V6MmrAxisSystemCreation  InputPath [OutputPath]"
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
//============================================================================================

#include "CATIAV5Level.h"

// ObjectModelerSystem Framework in V6
// ObjectModelerBase Framework in V5
#include "CATIAlias.h"

// CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"

// MecModInterfaces in V5
// CATMecModUseItf Framework in V6
#include "CATIMf3DAxisSystem.h"         
#include "CATIMf3DAxisSystemFactory.h"  

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// MecModInterfaces Framework in V5
// CATMecModLiveUseItf Framework in V6
#include "CATIPartRequest.h"

// CATGSMUseItf Framework
#include "CATIGSMUsePointCoord.h"         

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathAxis.h"
#include "CATMathConstant.h" 

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6MmrGetGeometry.h"          // To retrieve some features interactively created
#include "CAAV5V6MmrRetrieveCornerAndVectorsFromPad.h" // To create Brep features (2 edges) from a Pad

// System Framework
#include "CATString.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// Local framework
#include "CAAV5V6MmrInitSession.h" 

// Standard C++ library
#include <iostream.h>

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// CATPLMIdentificationAccess
#include "CATIPLMComponent.h"                    

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

// CATPLMIntegrationUse Framework
#include "CATAdpSaver.h"

// CAT3DPhysicalRepInterfaces
#include "CATIPsiRepresentationLoadMode.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// DataCommonProtocolUse
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"       // for update

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 

#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

#endif


//============================================================================================

int UpdateAndDisplayCharacteristics(CATUnicodeString iAxisSystemName,
                          CATIMf3DAxisSystem_var spIAxisSystem,
                          CATAxisSystemIsDirect  iDirect,
                          CATAxisSystemType      iAxisSystemType)
{
  // Changes the axis system name
  CATIAlias * pAliasOnAxisSystem = NULL;
  HRESULT rc = spIAxisSystem->QueryInterface(IID_CATIAlias,(void **) &pAliasOnAxisSystem);
  if (FAILED(rc))
		return 1;
  
  pAliasOnAxisSystem->SetAlias(iAxisSystemName);
  pAliasOnAxisSystem->Release();
  pAliasOnAxisSystem = NULL;

  // Update to take account of the axis system inputs (Origin point, axis direction, axis rotation ref)
  // The update operation is not necessary if the axis system is without feature input.
  //
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  CATIUseEntity *pUseEntityOnAxisSystem = NULL;
  rc = spIAxisSystem->QueryInterface(IID_CATIUseEntity , (void**)& pUseEntityOnAxisSystem);
  if (SUCCEEDED(rc))
  {
	  rc = DataCommonProtocolServices::Update(pUseEntityOnAxisSystem);
	  pUseEntityOnAxisSystem->Release();
	  pUseEntityOnAxisSystem = NULL;
  }  
#else
//============================================== 
// V5 only
//==============================================
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
#endif

  // Display the axis system parameters
  CATICkeParm_var ListParm[4][3] ;
  spIAxisSystem->GetParm(ListParm);

  CATUnicodeString Text [] = {"Origin", "X Axis","Y Axis","Z Axis"};
  int i= 0;
  for( i= 0 ; i <= 3 ; i++)
  {
    CATICkeParm_var AxisX = ListParm[i][0];
    CATICkeParm_var AxisY = ListParm[i][1];
    CATICkeParm_var AxisZ = ListParm[i][2];
    cout <<"      " << Text[i].ConvertToChar() <<"   X= "   << AxisX->Show().ConvertToChar() << ",";
    cout <<"          Y= " << AxisY->Show().ConvertToChar() << ",";
    cout <<"          Z= " << AxisZ->Show().ConvertToChar() <<endl;
  }

  // Display the axis direction types
  CATUnicodeString DirType [] = {"Same Dir", "Coord","Opposite Dir"};
  CATAxisSystemDirectionType SystemAxisType;
  for(i= 0 ; i < 3 ; i++)
  {
    spIAxisSystem->GetAxisType(CATAxisSystemXYZNumber(i+1),SystemAxisType);
    cout <<"      " << Text[i+1].ConvertToChar() <<" is " << DirType[SystemAxisType].ConvertToChar() << endl;
  }

  // Check the axis system orientation. 
  CATUnicodeString Direct [] ={"Indirect", "Direct","Not Orthogonal"};
  CATAxisSystemIsDirect IsDirectAxis;
  spIAxisSystem->IsDirect(IsDirectAxis);
  if (iDirect != IsDirectAxis)
  {
	cout <<" bug here " << endl; 
    return 1;
  }
  else 
	cout <<"      The new axis system is" << Direct[iDirect].ConvertToChar() << endl;

  // Check the axis system type
  CATUnicodeString ASType [] ={"Standard", "Axis Rotation","Euler Angles"};
  CATAxisSystemType AxisSystemType;
  spIAxisSystem->GetAxisSystemType(AxisSystemType);
  if (iAxisSystemType != AxisSystemType)
  {
    if (iAxisSystemType <= 2)
      cout <<"   Error: The new axis should be " << ASType[iAxisSystemType].ConvertToChar() << endl;
    else 
			cout <<"   The new axis should be explicit " << endl;
    return 1;
  }
  else 
  {
    if (iAxisSystemType <= 2)
      cout <<"      The new axis is " << ASType[iAxisSystemType].ConvertToChar() << endl;
    else 
	  cout <<"      The new axis is explicit " << endl;
  }

  return 0;
}

//============================================================================================

int main(int iArgc, char *iArgv[])

{

	//------------------------------------------------------------
	// 1- Check arguments
	//------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	if( 9!=iArgc ) 
	{
		cout <<"CAAV5V6MmrAxisSystemCreation <Repository> <Server> <User> <Password> <SecurityCtx> <PLMRepType> <PLMExternalIDValue> <Version>" << endl;
		return 1;
	}
#else
//============================================== 
// V5 only
//==============================================
	if ((3 != iArgc) && ( 2 != iArgc) )
    {
       cout << endl;
       cout << "CAAV5V6MmrAxisSystemCreation InputPath [OutputPath]"<< endl;
       cout << "with : InputPath : InstallRootDirectory/CAAMechanicalModeler.edu/InputData"<< endl;
       cout <<"        OutputPath: Directory to save as the Part document"<<endl;
       cout << endl;
       return 1;
    }
#endif

	cout <<"The CAAV5V6MmrAxisSystemCreation use case begins" << endl;

	//------------------------------------------------------------------
	//2 - Initialize the session 
	//------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	//
    //-----------------------------------------------------------------------------------
	//    Creates a session with : repository, server, user,password, SecurityCtx
	//    Loads the Representation with the values of the identifiant set attributes
	//    Retrieves the Part Container
	//-----------------------------------------------------------------------------------
	//
	CATString PLM_RepType = iArgv[6];
	CATUnicodeString PLM_ExternalIDValue = iArgv[7];
	CATUnicodeString V_versionValue = iArgv[8];
	CATIMmiPrtContainer * piPartContainer = NULL;
	CATOmbLifeCycleRootsBag Bag;

	HRESULT rc = :: CAAV5V6MmrInitSession(iArgv[1], iArgv[2], iArgv[3],iArgv[4], iArgv[5],
		                              PLM_RepType, PLM_ExternalIDValue, V_versionValue,
		                              Bag, piPartContainer);

	
	if (FAILED(rc) || (NULL == piPartContainer))
		return 1;

	cout << "The Representation has been opened and the Part container has been retrieved"<< endl;

#else
//============================================== 
// V5 only
//==============================================
    //
    //    Creates a session
    //    Loads the Part document
    //    Retrieves the Part Container
    //
	char * pSessionName = "CAA_CreationSample_Session";
	CATString InputData = iArgv[1] ;
    CATString DocumentName =InputData + Slash + "CAAAxisSystemCreation.CATPart";
    CATIMmiPrtContainer * piPartContainer = NULL;
	CATDocument *pDoc = NULL;
    HRESULT rc =  CAAV5V6MmrInitSession(pSessionName, DocumentName.ConvertToChar(), pDoc, piPartContainer) ;
       
    if (FAILED(rc) || (NULL == piPartContainer))
		return 1;

    cout << "The Part document has been opened and the Part container has been retrieved"<< endl;
 
#endif	
	

	//----------------------------------------------------------
	//3- Retrieves the MechanicalPart feature
	//----------------------------------------------------------
	CATIMmiMechanicalFeature_var spMechFeatOnPart;  
	rc = piPartContainer->GetMechanicalPart(spMechFeatOnPart);

	if ( FAILED(rc) || (NULL_var == spMechFeatOnPart) )
		return 1;
	
	CATIPartRequest_var spPartRequestOnPart =	spMechFeatOnPart;

	if (NULL_var == spPartRequestOnPart)
		return 1 ;
	cout <<"   Mechanical Part retrieved" << endl;

	//----------------------------------------------------------
	// 4- Retrieves a CATIMf3DAxisSystemFactory interface pointer
	//----------------------------------------------------------
	CATIMf3DAxisSystemFactory * pIMf3DAxisSystemFactoryOnFeatCont = NULL;
	rc = piPartContainer->QueryInterface(IID_CATIMf3DAxisSystemFactory,(void **) & pIMf3DAxisSystemFactoryOnFeatCont);
					     
	if (FAILED(rc))
		return 1;

	piPartContainer->Release();
	piPartContainer = NULL;

	// -----------------------------------------------------------
	// 5- Creates a Standard axis system  
	// -----------------------------------------------------------
	CATMathPoint Origin (150.0,.0,.0);
	CATMathVector X (1.0,.0,.0);
	CATMathVector Y (0.0,1.0,.0);

	CATIMf3DAxisSystem_var NewAxisSystemStd ;
	rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(Origin,X,Y,NewAxisSystemStd);
	if ( FAILED(rc) )
		return 1;
	cout << endl <<"   Creation of the Standard axis system" << endl;
  
	// Retrieve the Pad 
	CATBaseUnknown * pPad = NULL;
	rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnPart,"Pad.1",&pPad);
	if (FAILED(rc) || ( NULL == pPad))
		return 1;

	CATBaseUnknown *pVectorX = NULL;
	CATBaseUnknown *pVectorY = NULL;
	rc = ::CAAV5V6MmrRetrieveCornerAndVectorsFromPad(pPad,&pVectorX,&pVectorY);
	if (FAILED(rc))
		return 1;
  
	// The three vectors are BRep feature too.
	// The last vector (on Z axis) is not set, to ensure a direct axis system
	NewAxisSystemStd->SetAxisDirection(CATAxisSystemXNumber, pVectorX);
	NewAxisSystemStd->SetAxisDirection(CATAxisSystemYNumber, pVectorY);
 
	// Update and Display axis system characteristics
	int val = UpdateAndDisplayCharacteristics("AS_Standard", NewAxisSystemStd,
						  CATAxisSystemDirect,
						  CATAxisSystemStandard);
	if (0 != val) 
		return val;

	pVectorX->Release(); pVectorX = NULL;
	pVectorY->Release(); pVectorY = NULL;

	// -----------------------------------------------------------
	// 6- Creates a Rotation axis system  
	// -----------------------------------------------------------

	CATMathAxis MathAxis;
	CATIMf3DAxisSystem_var NewAxisSystemRot;
	rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(MathAxis,NewAxisSystemRot);
	if ( FAILED(rc) )
		return 1;
	cout << endl <<"   Creation of the Rotation axis system" << endl;

	// Search the geometries in the input Part feature associated with the representation reference
	CATBaseUnknown * pPoint5 = NULL;
	rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnPart,"Point.5",&pPoint5);
	if (FAILED(rc) || ( NULL == pPoint5))
		return 1;

	CATBaseUnknown * pLineD1 = NULL;
	rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnPart,"D1",&pLineD1);
	if (FAILED(rc) || (NULL ==pLineD1))
		return 1;

	CATBaseUnknown * pLineD2 = NULL;
	rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnPart,"D2",&pLineD2);
	if (FAILED(rc) || (NULL ==pLineD2))
		return 1;

	// Modify the axis system 
	NewAxisSystemRot->SetOriginPoint(pPoint5);

	// Change the type of the axis system 
	NewAxisSystemRot->SetAxisSystemType(CATAxisSystemAxisRotation);

	// "Deselect" all the axes to control the axis order
	NewAxisSystemRot->SetAxisType(CATAxisSystemXNumber,CATAxisSystemSameDirection);
	NewAxisSystemRot->SetAxisType(CATAxisSystemYNumber,CATAxisSystemSameDirection);
	NewAxisSystemRot->SetAxisType(CATAxisSystemZNumber,CATAxisSystemSameDirection); 

	// The Y axis is the rotation's axis because it is the first axis
	// The D1 line defined the rotation's axis direction
	NewAxisSystemRot->SetAxisDirection(CATAxisSystemYNumber,pLineD1);

	// The D2 line will be projected in the orthogonal plane to D1.
	// The projected line defines the reference for the rotation. 
	NewAxisSystemRot->SetAxisRotationReference(pLineD2);
  
	// The rotation from the reference's geometry is 90 degrees
	CATICkeParm_var RotationParm ;
	NewAxisSystemRot->GetAxisRotationParm(RotationParm);
	if ( NULL_var != RotationParm )
		// The valuate method is in MKS 
		RotationParm->Valuate(CATPI/2);
	else 
		return 1;

	// Update and Display axis system characteristics
	val = UpdateAndDisplayCharacteristics("AS_AxisRotation", NewAxisSystemRot,
					      CATAxisSystemDirect,
					      CATAxisSystemAxisRotation);
	if (0 != val)
		return val;

	// -----------------------------------------------------------
	// 7- Creates an Euler axis system  
	// -----------------------------------------------------------
	CATMathAxis MathAxisEuler ;
	CATMathPoint OriginEuler (.0,200.0,.0);
	MathAxisEuler.SetOrigin(OriginEuler);

	CATIMf3DAxisSystem_var NewAxisSystemEuler;
	rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(MathAxisEuler,NewAxisSystemEuler);
	if (FAILED(rc))
		return 1;

	cout << endl <<"   Creation of the Euler axis system" << endl;

	// Change the type of the axis system 
	NewAxisSystemEuler->SetAxisSystemType(CATAxisSystemEulerAngles);

	// Modify the axis system 
    CATICkeParm_var EulerAngles[3] ;
	NewAxisSystemEuler->GetEulerAnglesParm(EulerAngles);
	if ((NULL_var != EulerAngles[0]) && (NULL_var != EulerAngles[1]) &&
	    (NULL_var != EulerAngles[2]))
	{
		// The valuate method is in MKS 
		EulerAngles[0]->Valuate(CATPI/2);  
		EulerAngles[1]->Valuate(CATPI/2);  
		EulerAngles[2]->Valuate(CATPI/2);  
	}
	else 
		return 1;

	// Update and Display axis system characteristics
	val = UpdateAndDisplayCharacteristics("AS_EulerAngles",NewAxisSystemEuler,
					      CATAxisSystemDirect,
					      CATAxisSystemEulerAngles);
	if (0 != val)
		return val;

	// -----------------------------------------------------------
	// 8- Creates an axis system (AS_AxisStandardOriAxisDir) from the AS_Standard  
	// -----------------------------------------------------------

	CATIMf3DAxisSystem_var NewAxisSystemCopyConst;
	rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(NewAxisSystemStd,
								 NewAxisSystemCopyConst);
	if (FAILED(rc))
		return 1;

	cout << endl <<"   Creation of the Copy Const axis system from the first axis system" << endl;

	// The origin of the new axis is at the origin of the three axis directions
	NewAxisSystemCopyConst->SetOriginType(CATAxisSystemPoint);
	NewAxisSystemCopyConst->SetOriginPoint(NULL_var);

	CATAxisSystemPointType SystemPointType;
	NewAxisSystemCopyConst->GetOriginType(SystemPointType);
	if (CATAxisSystemPoint != SystemPointType)
		return 1;

	// Update and Display axis system characteristics  
	val = UpdateAndDisplayCharacteristics("AS_AxisStandardOriAxisDir", NewAxisSystemCopyConst,
					      CATAxisSystemDirect,
					      CATAxisSystemStandard);
	if (0 != val)
		return val;

	// -----------------------------------------------------------
	// 9- Create an Explicit Axis System  
	// -----------------------------------------------------------
	CATIMf3DAxisSystem_var NewAxisSystemExplicit;
	CATMathAxis MathAxisExplicit;
	rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(MathAxisExplicit,
								 NewAxisSystemExplicit);
	if (FAILED(rc))
		return 1;

	cout << endl <<"   Creation of the Explicit axis system" << endl;

	CATBaseUnknown * pPoint7 = NULL;
	rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnPart,"Point.7",&pPoint7);
	if ( FAILED(rc) || ( NULL == pPoint7) )
		return 1;
  
	CATBaseUnknown * pLineD3 = NULL;
	rc = ::CAAV5V6MmrGetGeometry(spPartRequestOnPart,"D3",&pLineD3);
	if (FAILED(rc) || (NULL == pLineD3))
		return 1;

	// To modify the axis order
	NewAxisSystemExplicit->SetAxisType(CATAxisSystemXNumber,CATAxisSystemSameDirection);
	NewAxisSystemExplicit->SetAxisType(CATAxisSystemYNumber,CATAxisSystemSameDirection);
	NewAxisSystemExplicit->SetAxisType(CATAxisSystemZNumber,CATAxisSystemSameDirection);

	// Modify the axis system 
	NewAxisSystemExplicit->SetOriginPoint(pPoint7);
	NewAxisSystemExplicit->SetAxisDirection(CATAxisSystemYNumber,pLineD1);
	NewAxisSystemExplicit->SetAxisDirection(CATAxisSystemZNumber,pLineD2);
	NewAxisSystemExplicit->SetAxisDirection(CATAxisSystemXNumber,pLineD3);

	// Update and Displays axis system characteristics
	val = UpdateAndDisplayCharacteristics("AS_Explicit", NewAxisSystemExplicit,
					      CATAxisSystemIndirect,
					      CATAxisSystemStandard);
	if (0 != val)
		return val;

	cout <<"      The axis system becomes direct and the origin position is changed" << endl; 

	// Change the Z direction, the axis system should become direct
	NewAxisSystemExplicit->SetAxisType(CATAxisSystemZNumber,CATAxisSystemOppositeDirection);
 
	// Change the Origin position
	CATIGSMUsePointCoord *pGSMPointCoordOnP7 = NULL ;
	rc = pPoint7->QueryInterface(IID_CATIGSMUsePointCoord,(void **) &pGSMPointCoordOnP7);
	if ( SUCCEEDED(rc) )
	{
		CATICkeParm_var Xnew,Ynew,Znew ;
		pGSMPointCoordOnP7->GetCoordinates(Xnew,Ynew,Znew);
     
		Xnew->Valuate(-0.1); 
		Ynew->Valuate(0.0); 
		Znew->Valuate(0.0);
    
		pGSMPointCoordOnP7->Release();
		pGSMPointCoordOnP7 = NULL;
	}

	// Update and Display axis system characteristics
	val = UpdateAndDisplayCharacteristics("AS_Explicit", NewAxisSystemExplicit,
					      CATAxisSystemDirect,
					      CATAxisSystemStandard);
	if (0 != val)
		return val;

	cout <<"      The axis system becomes explicit" << endl; 
	NewAxisSystemExplicit->SetAxisSystemType(CATAxisSystemExplicit);

	cout <<"      The Point.7 position changement is without effect on the explicit axis system" << endl;
	pGSMPointCoordOnP7 = NULL;
	rc = pPoint7->QueryInterface(IID_CATIGSMUsePointCoord,(void **) &pGSMPointCoordOnP7);
	if (SUCCEEDED(rc))
	{
		CATICkeParm_var Xnew,Ynew,Znew ;
		pGSMPointCoordOnP7->GetCoordinates(Xnew,Ynew,Znew);
     
		Xnew->Valuate(-0.2); 
		Ynew->Valuate(0.0); 
		Znew->Valuate(0.0);
    
		pGSMPointCoordOnP7->Release();
		pGSMPointCoordOnP7 = NULL;
	}

	// Update and Display axis system characteristics
	val = UpdateAndDisplayCharacteristics("AS_Explicit", NewAxisSystemExplicit,
					      CATAxisSystemDirect,
					      CATAxisSystemExplicit);
	if (0 != val)
		return val;

	// The update of the axis system is without effect on the Point.7
	// since the axis system is explicit. So the Point.7 update is
	// necessary
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATIUseEntity *pUseEntityOnP7= NULL;
    rc = pPoint7->QueryInterface(IID_CATIUseEntity , (void**)& pUseEntityOnP7);
	if (SUCCEEDED(rc))
	{
	  rc = DataCommonProtocolServices::Update(pUseEntityOnP7);
	  pUseEntityOnP7->Release(); pUseEntityOnP7 = NULL;
	}  
#else
//============================================== 
// V5 only
//==============================================
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
#endif

	// -----------------------------------------------------------
	// 10- Release the useless pointers
	// -----------------------------------------------------------
	pIMf3DAxisSystemFactoryOnFeatCont->Release();
	pIMf3DAxisSystemFactoryOnFeatCont = NULL ;

	pPoint5->Release(); pPoint5 = NULL;
	pPoint7->Release(); pPoint7 = NULL;
	pLineD1->Release(); pLineD1 = NULL;
	pLineD2->Release(); pLineD2 = NULL;
	pLineD3->Release(); pLineD3 = NULL;
	pPad->Release();    pPad    = NULL;

	// -----------------------------------------------------------
	// 11- End of session
	// -----------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	// Save the session
	CATAdpSaver saver;
    rc = saver.Save();
	
	if (FAILED(rc))
		return 1;

	cout <<"   Session saved successfully" << endl;

	// First unload components from session
    Bag.RemoveAll();

	// Close the session
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) )
		return 1;

	cout <<"   Session closed successfully" << endl;

#else
//============================================== 
// V5 only
//==============================================  
   // Save the document
   CATString DocumentSaveAsName = "CAAAxisSystemCreation_Save.CATPart" ;
   if ( 3 == iArgc )
   {
      CATString OutputPath = iArgv[2] ;
      DocumentSaveAsName = OutputPath + Slash + DocumentSaveAsName ;
   }

   rc = CATDocumentServices::SaveAs (*pDoc,DocumentSaveAsName.ConvertToChar());
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

   // Close the document
   rc = CATDocumentServices::Remove (*pDoc);
   if ( FAILED(rc) )
   {
      cout <<"Error by closing the Part document" << endl;
      return 1;
   }
   pDoc = NULL ;
  
   // Delete all documents in session
   rc = ::Delete_Session(pSessionName);
   if (FAILED(rc) )
   {
      cout << "ERROR in delete session" << endl ;
      return 1;
   }

#endif

	cout << endl << "The CAAV5V6MmrAxisSystemCreation main program ends ...."<< endl << endl;

	return 0;
}
