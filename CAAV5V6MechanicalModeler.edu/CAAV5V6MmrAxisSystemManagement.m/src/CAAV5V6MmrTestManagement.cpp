// COPYRIGHT DASSAULT SYSTEMES 2012
//============================================================================================
//
// Mission       : It is an use case about the axis systems. It enables to set
//                   an axis system as current and to transform the origin of 
//                   the absolute axis system (0,0,0) in the current axis system. 
//                   The CATIMf3DAxisSystem and CATIMf3DAxisSystemManager 
//                   interfaces are mainly used.
//
// Note : CAAV5V6MmrTestManagement is the same use case as CAAMmrTestManagement. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
// Steps :
//    1-    Checks the arguments
//    2-    Initializes the session
//    3-    Loads the Representation with the values of the identifiant set attributes 
//    4-    Retrieves CATPrtCont, the specification container
//    5-    Retrieves a CATIMf3DAxisSystemManager interface pointer
//    6-    Displays the count of axis systems
//    7-    Retrieves the current axis system
//    8-    Finds the new current axis system in the list
//    9-    Sets the new current axis system
//    10-   Displays the current axis system parameters
//    11-   Transforms the (0,0,0) point in the current axis system .
//    12-   Transforms the (0.0,0.0,1.0) vector in the current axis system 
//    13-   Releases the useless pointer
//    14-   Saves the Session
//    15-   Closes the Session
// 
//==========================================================================
// How to execute :
//
// In V6
// =====
//	 mkrun -c "CAAV5V6MmrAxisSystemManagement Repository Server UserId Password SecurityCtx PLMRepType PLMExternalIDValue Version CurrentAS"
//
//	 where    Repository	: The name of the repository (or provider) 
//			  Server		: The server as Host:Port_number/RootURI
//			  User			: The user identifier
//            Password		: The user password  
//			  SecurityCtx   : A string representing the security context (Role.Organization.Project)
//							  Choose Role as Designer ( as the use case modifies the PLM Data )
//			  PLMRepType    : A string representing PLM Representation type 
//			  PLMExternalIDValue : the value of the PLM_ExternalID attribute of a PLM representation reference. 
//			  Version       : The value of the V_version attribute of a PLM representation reference. 
//			  CurrentAS     : The name of the axis system to set current.If the string is "AbsoluteAS"
//                            The absolute axis system becomes the current one.	
// 
// In V5
// =====
//
//   mkrun -c "CAAV5V6MmrAxisSystemManagement Filename CurrentAS [OutputPath]"
//
//   with     Filename   : The Part document path containing axis system. You can use  
//                         CAAAxisSystemCreation_Save that you find in:
//                            
//                         InstallRootDirectory\CAAV5V6MechanicalModeler.edu\InputData 
//
//            CurrentAS  : The name of the axis system to set current. If the string is "AbsoluteAS"
//                         the absolute axis system becomes the current one.
//
//            OutputPath : The output path where the CAAMmrAxisSystemManagement Part document 
//                         will be saved. If this path is empty, the file will be saved in 
//                         the current directory. 
//
//============================================================================================

#include "CATIAV5Level.h"

// ObjectModelerSystem Framework
#include "CATIAlias.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"

// MecModInterfaces Framework in V5
// CATMecModUseItf Framework in V6
#include "CATIMf3DAxisSystem.h"         // axis system interface access
#include "CATIMf3DAxisSystemManager.h"  // to list all the axis systems and set a current one

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// System Framework
#include "CATUnicodeString.h"
#include "CATBoolean.h"
#include "CATString.h"

// Local framework
#include "CAAV5V6MmrInitSession.h" 

// C++ Standard library
#include <iostream.h>

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

//CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

//CATPLMIdentificationAccess
#include "CATIPLMComponent.h"                    

//CATPLMIntegrationUse Framework
#include "CATAdpSaver.h"

//CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// CAT3DPhysicalRepInterfaces
#include "CATIPsiRepresentationLoadMode.h"

#else
//============================================== 
// V5 only
//============================================== 
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

int main(int iArgc, char *iArgv[])
{

	//---------------------
	// 1- Checks arguments
	//---------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	
	if ((10 != iArgc))
	{
		cout << endl;
		cout << "CAAV5V6MmrAxisSystemManagement <Repository> <Server> <User> <Password> <SecurityCtx> <PLMRepType> <PLMExternalIDValue> <Version> <CurrentAS>"<< endl;
	return 1;
	}

#else
//============================================== 
// V5 only
//==============================================

  if ((4 != iArgc) && ( 3 != iArgc) )
  {
     cout << endl;
     cout << "CAAV5V6MmrAxisSystemManagement Filename CurrentAS [OutputPath]"<< endl;
     cout << "with   Filename : The complete filename of a Part document containing axis systems." <<endl;
     cout << "                  You can use CAAAxisSystemCreation_Save located in:" << endl;
     cout<<  "                  InstallRootDirectory/CAAMechanicalModeler.edu/InputData/ " << endl;
     cout << "       CurrentAS : The name of the axis system to set as current. with 'AbsoluteAS' " <<endl;
     cout << "                    the absolute axis system becomes the current one." << endl;
     cout <<"        OutputPath: Directory to save as the input Part document"<<endl;
     cout << endl;
     return 1;
  }
#endif

  cout << "The CAAV5V6MmrAxisSystemManagement main program begins ...."<< endl << endl;

    //------------------------------------------------------------------
	//2 - Initializes the session 
	//------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

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
    CATDocument *pDoc = NULL;
    CATString DocumentName = iArgv[1] ;
	char * pSessionName = "CAA_CreationSample_Session";
    CATIMmiPrtContainer * piPartContainer = NULL;
    HRESULT rc =  CAAV5V6MmrInitSession(pSessionName, DocumentName.ConvertToChar(), pDoc, piPartContainer) ;
       
    if (FAILED(rc) || (NULL == piPartContainer))
		return 1;

    cout << "The Part document has been opened and the Part container has been retrieved"<< endl;
 
#endif	


	//----------------------------------------------------------
	//5- Retrieve a CATIMf3DAxisSystemManager interface pointer
	//----------------------------------------------------------
	CATIMf3DAxisSystemManager * pIMf3DAxisSystemManagerOnFeatCont = NULL;
	rc = piPartContainer->QueryInterface(IID_CATIMf3DAxisSystemManager,
					     (void **) & pIMf3DAxisSystemManagerOnFeatCont);
	if (FAILED(rc))
		return 1;

	piPartContainer->Release();
	piPartContainer = NULL;

	//----------------------------------------------------------
	//6- Display the count of axis systems
	//----------------------------------------------------------
	CATLISTV(CATIMf3DAxisSystem_var) ListAxisSystem ;
	rc = pIMf3DAxisSystemManagerOnFeatCont->GetAxisSystems(ListAxisSystem);
	if (FAILED(rc))
		return 1;

	int nbAS = ListAxisSystem.Size();
	cout <<"   There are " << nbAS << " axis system(s) in the representation reference" << endl;
	for ( int i= 1 ; i <= nbAS  ; i++)
	{
		CATIMf3DAxisSystem_var spMf3DAxisSystemOnAS = ListAxisSystem[i] ;
		if ( NULL_var != spMf3DAxisSystemOnAS )
		{
			CATIAlias_var spAliasOnCurrentAS = spMf3DAxisSystemOnAS ;
			if (NULL_var != spAliasOnCurrentAS )
				cout<<"      "<< spAliasOnCurrentAS->GetAlias().ConvertToChar() << endl;
		}
	}
	cout << endl;

	//----------------------------------------------------------
	//7- Retrieve the current axis system
	//----------------------------------------------------------
	CATIMf3DAxisSystem_var spMf3DAxisSystemOnCurrentAS ;
	rc = pIMf3DAxisSystemManagerOnFeatCont->GetCurrentAxisSystem(spMf3DAxisSystemOnCurrentAS);
	if (FAILED(rc))
		return 1;

	CATUnicodeString OldCurrentAxisName ="AbsoluteAS";
	if (NULL_var != spMf3DAxisSystemOnCurrentAS)
	{
		CATIAlias_var spAliasOnCurrentAS = spMf3DAxisSystemOnCurrentAS ;
		if (NULL_var != spAliasOnCurrentAS)
		{
			OldCurrentAxisName = spAliasOnCurrentAS->GetAlias();
			cout <<"   The current Axis is:" << OldCurrentAxisName.ConvertToChar() << endl;
		}
		else 
			return 1;
	}
	else 
		cout <<"   There is no current axis system" << endl;

	//----------------------------------------------------------
	//8- Find the new current axis system in the list
	//----------------------------------------------------------
#ifdef CATIAR214
	CATUnicodeString NewCurrentAxisName = iArgv[9];
#else
	CATUnicodeString NewCurrentAxisName = iArgv[2];
#endif
	CATUnicodeString AbsoluteAS = "AbsoluteAS";
	CATBoolean Found = FALSE; 

	if ( (AbsoluteAS != NewCurrentAxisName) && (OldCurrentAxisName != NewCurrentAxisName) )
	{
		int i = 1;
		while ((FALSE == Found) && (i<= nbAS))
		{
			CATIMf3DAxisSystem_var spMf3DAxisSystem = ListAxisSystem[i];
			if (NULL_var != spMf3DAxisSystem)
			{
				CATIAlias_var spAliasOnCurrentAS = spMf3DAxisSystem ;
				if (NULL_var != spAliasOnCurrentAS)
				{
					if (NewCurrentAxisName == spAliasOnCurrentAS->GetAlias())
					{
						Found = TRUE;
						spMf3DAxisSystemOnCurrentAS = spMf3DAxisSystem;
					}
				}
			}
			i++ ;
		}
		if ( FALSE == Found)
			NewCurrentAxisName = OldCurrentAxisName ;
	}

	//----------------------------------------------------------
	//9- Set the new current axis system 
	//----------------------------------------------------------

	if (AbsoluteAS == NewCurrentAxisName)
	{
		rc = pIMf3DAxisSystemManagerOnFeatCont->SetCurrentAxisSystem(NULL_var);
		if ( FAILED(rc) )
			return 1;

	}
	else if (TRUE == Found)
	{
		rc = pIMf3DAxisSystemManagerOnFeatCont->SetCurrentAxisSystem(spMf3DAxisSystemOnCurrentAS);
		if (FAILED(rc))
			return 1;
	}
  
	cout <<"   The "<< NewCurrentAxisName.ConvertToChar() ; 
	cout << " axis system is the current one" << endl << endl;

	//----------------------------------------------------------
	//10- Display the current axis system parameters
	//----------------------------------------------------------
  
	if (AbsoluteAS != NewCurrentAxisName) 
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
	//11- Transform the (0,0,0) point in the current axis system 
	//----------------------------------------------------------
	if ( AbsoluteAS != NewCurrentAxisName)
	{
		CATMathPoint PointToConvert (.0,.0,.0);
		CATMathPoint ConvertedPoint;
     
		rc = pIMf3DAxisSystemManagerOnFeatCont->ConvertPointCoordinates(TRUE,
										PointToConvert,ConvertedPoint);
		if (FAILED(rc))
			return 1;

		cout <<"   Point Converted: X=" << ConvertedPoint.GetX() ;
		cout <<"   Y=" <<  ConvertedPoint.GetY() ;
		cout <<"   Z=" << ConvertedPoint.GetZ() << endl;
	}
	//----------------------------------------------------------
	//12- Transform the (0.0,0.0,1.0) vector in the current axis system 
	//----------------------------------------------------------
	if (AbsoluteAS != NewCurrentAxisName)
	{
		CATMathVector VectorToConvert (.0,.0,1.0);
		CATMathVector ConvertedVector;
		rc = pIMf3DAxisSystemManagerOnFeatCont->ConvertVectorCoordinates(TRUE,
										 VectorToConvert,ConvertedVector);
		if (FAILED(rc))
			return 1;

		cout <<"   Vector Converted: X=" << ConvertedVector.GetX();
		cout <<"   Y=" <<  ConvertedVector.GetY();
		cout <<"   Z=" << ConvertedVector.GetZ() << endl;
	}

	// -----------------------------------------------------------
	// 13- Release the useless pointers
	// -----------------------------------------------------------
  
	pIMf3DAxisSystemManagerOnFeatCont->Release();
	pIMf3DAxisSystemManagerOnFeatCont = NULL;

	// -----------------------------------------------------------
	// 14- End of session
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

	// Unload components from session
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
   CATString DocumentSaveAsName = "CAAAxisSystemManagement.CATPart" ;
   if ( 4 == iArgc )
   {
      CATString OutputPath = iArgv[3] ;
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



	cout << endl << "The CAAV5V6MmrAxisSystemManagement main program ends ...."<< endl << endl;

	return 0;
}

