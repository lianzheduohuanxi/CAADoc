// COPYRIGHT DASSAULT SYSTEMES 2012
//============================================================================================
//
// Mission       : It is a use case about the axis systems. It enables to create 
//                 a sketch by using a plane of an axis system.
//                 The CATIMf3DAxisSystem and CATIMf3DAxisSystemFactory 
//                   interfaces are mainly used.
//
// Note : CAAV5V6MmrTestBRep is the same use case as CAAMmrTestBRep. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
// Steps :
//    1-    Checks the arguments
//    2-    Initializes the session 
//    3-    Creates a Part
//    4-    Retrieves the CATPrtCont container, the specification container
//    5-    Retrieves a CATIMf3DAxisSystemFactory interface pointer
//    6-    Creates an axis system 
//    7-    Retrieves the BRep plane and featurizes it
//    8-    Creates the sketch
//    9-    Releases the useless pointers
//    10-   Saves
//    11-   Closes the Session
// 
//
//==========================================================================
// How to execute :
//
// In V6
// =====
//   mkrun -c "CAAV5V6MmrAxisSystemBRep <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>"                                     
//
//	 where    Repository	: The name of the repository (or provider) 
//			  Server		: The name and port of the server as name:port_number
//			  User			: The user identifier
//            Password		: The user password  
//			  SecurityCtx   : A string representing the security context (Role.Organization.Project)
//							  Choose Role as Designer ( as the use case modifies the PLM Data )
//
// In V5
// =====
//
//   mkrun -c "CAAV5V6MmrAxisSystemBRep [Filename]"
//  
//   with   OutputPath : The  Part document with the new sketch.
//                       If this filename is empty, the CAAV5V6MmrAxisSystemBRep file 
//                       will be saved in the current directory.
//                        
//
//===========================================================================================


#include "CATIAV5Level.h"

// KnowledgeInterfaces Framework
#include "CATListValCATICkeParm.h"

// CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"
#include "CATIMmiUseFeaturize.h"
#include "CATIMmiUseMfBRep.h"

// MecModInterfaces in V5
// CATMecModUseItf Framework in V6
#include "CATIMf3DAxisSystem.h"         // axis system interface access
#include "CATIMf3DAxisSystemFactory.h"  // To create an axis system

// CATMecModLiveUseItf
#include "CATIMmiMechanicalFeature.h"

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"

// System Framework
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATErrorMacros.h"

// Standard C++ library
#include <iostream.h>


#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// CAAAdpClientAdapter.edu framework 
#include "CAAAdpCreateCloseSession.h"  

// CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

// CATPLMIntegrationUse Framework
#include "CATAdpSaver.h"     // to save in database

//PLMDictionaryNavServices
#include "CATCkePLMNavPublicServices.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//ProductStructureUseItf  Framework
#include "CATIPrdRepresentationReferenceFactory.h"
#include "CATPrdFactory.h"

// DataCommonProtocolUse Framework
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

// SketcherInterfaces Framework
#include "CATISktUseSketchFactory.h"

// System  Framework
#include "CATLISTP_CATBaseUnknown.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATIAlias.h"
#include "CATSession.h"

// SketcherInterfaces Framework
#include "CATISketchFactory.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// MecModInterfaces Framework
#include "CATIBRepAccess.h"  


#endif

//============================================================================================

int main(int iArgc, char *iArgv[])

{
	//---------------------
	// 1- Check arguments
	//---------------------
	
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	if ( 6 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6MmrAxisSystemBRep <Repository> <Server> <User> <Password> <SecurityCtx> " ;
		return 1;
	}
#else
//============================================== 
// V5 only
//============================================== 
   if ((1 != iArgc) && ( 2 != iArgc) )
   {
      cout << endl;
      cout << "CAAV5V6MmrAxisSystemBRep [Filename]"<< endl;
      cout << "with Filename : The complete file name of the result Part document." << endl;
      cout << "                If the string is empty, the Part document is " << endl;
      cout << "                CAAV5V6MmrAxisSystemBRep.CATPart " << endl;
  
      cout << endl;
      return 1;
  }
#endif
	
	cout << "The CAAV5V6MmrAxisSystemBRep main program begins ...."<< endl << endl;
	
	
	//------------------------------------------------------------------
	//2 - Initialize the session 
	//------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3],iArgv[4], iArgv[5]);			   
	if (FAILED(rc))	
	{
		cout <<"   ERROR creating a session" << endl;
		return 1;  
	}
	
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx="<< iArgv[5] << endl;
	
#else
//============================================== 
// V5 only
//============================================== 
	char * pSessionName = "CAA_CreationSample_Session";
    CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionName,pSession);

    if (FAILED(rc) )
    {
      cout << "ERROR by creating session" << endl ;
      return 1;
    }
#endif

	//------------------------------------------------------------------
	//3- Create a Part
	//------------------------------------------------------------------
	
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
    
	//Retrieve the PLM type 
	CATIType_var spRepType;
    rc = CATCkePLMNavPublicServices::RetrieveKnowledgeType( "3DShape", spRepType );
    if (FAILED(rc))
      return 1;

    cout << "   Retrieved PLM type" << endl;
	
	//Retrieve the interface pointer on the Rep Ref factory
    CATIPrdRepresentationReferenceFactory * pIPLMRepRefFactory = NULL;
    rc = CATPrdFactory::CreatePrdFactory(IID_CATIPrdRepresentationReferenceFactory,(void**) &pIPLMRepRefFactory);
  
	if (FAILED(rc) || ( NULL == pIPLMRepRefFactory))
	{
		cout <<"   ERROR getting Rep Ref factory" << endl;
		return 1;  
	}

    cout <<"   A Pointer to the Representation Reference factory has been found" << endl;

 
    //Create the Representation Reference 
	CATIPsiRepresentationReference * pPsiCreatedRepRef  = NULL;  
	CATListValCATICkeParm_var EmptyList; 
	rc = pIPLMRepRefFactory->Create3DShape(spRepType, EmptyList, pPsiCreatedRepRef, NULL);

	if (FAILED(rc) || (NULL == pPsiCreatedRepRef ))
	{
		cout <<"   ERROR creating the rep ref" << endl;
        return 1;
	}
    cout <<"   The Representation Reference has been created" << endl;

    pIPLMRepRefFactory->Release(); 
    pIPLMRepRefFactory = NULL;
  
	
	
	//Insert component in BAG
    CATOmbLifeCycleRootsBag Bag;
    Bag.InsertRoot(pPsiCreatedRepRef);

#else
//============================================== 
// V5 only
//============================================== 
	CATDocument *pModel= NULL;
    rc = CATDocumentServices::New("CATPart",pModel);

    if (FAILED(rc) )
    {
       cout << "ERROR by creating a Part document= "<< endl ;
       return 1;
    }

#endif

	//------------------------------------------------------------------
	//4- Retrieves CATPrtCont, the specification container piPartContainer
	//------------------------------------------------------------------
    
	CATIMmiPrtContainer * piPartContainer = NULL ;

#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	CATIPLMNavRepReference_var spRepRef = pPsiCreatedRepRef;
    if (spRepRef == NULL_var)
      return 1;
	
	
	rc = spRepRef->RetrieveApplicativeContainer("CATPrtCont",IID_CATIMmiPrtContainer,(void **)&piPartContainer);
	
	if ( FAILED(rc) || (NULL == piPartContainer) )
		return 1 ;
	
	
#else
//============================================== 
// V5 only
//============================================== 
	CATInit * pInitOnDoc = NULL ;
    rc = pModel->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
    if ( FAILED(rc) )
    {
       cout << "Error in the CATInit interface"<< endl;
       return 1 ;
    }

    piPartContainer = (CATIMmiPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

    if ( NULL == piPartContainer)
    {
       cout << "The root container is NULL"<< endl;
       return 1 ;
    }

    // No more need of this interface
    pInitOnDoc->Release();
    pInitOnDoc = NULL ;
#endif

	cout << "   The Part container has been retrieved"<< endl;

	//----------------------------------------------------------
	//5- Retrieves the factory interface pointers
	//----------------------------------------------------------
	CATIMf3DAxisSystemFactory * pIMf3DAxisSystemFactoryOnFeatCont = NULL ;
	rc = piPartContainer->QueryInterface(IID_CATIMf3DAxisSystemFactory,
		(void **) & pIMf3DAxisSystemFactoryOnFeatCont);
	if ( FAILED(rc) )
		return 1;

#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	CATISktUseSketchFactory * pISketchFactoryOnFeatCont = NULL ;
	rc = piPartContainer->QueryInterface(IID_CATISktUseSketchFactory,(void **) & pISketchFactoryOnFeatCont);
#else
//============================================== 
// V5 only
//============================================== 
	CATISketchFactory * pISketchFactoryOnFeatCont = NULL ;
    rc = piPartContainer->QueryInterface(IID_CATISketchFactory,(void **) & pISketchFactoryOnFeatCont);
#endif

	if ( FAILED(rc) )
		return 1;
	
	piPartContainer->Release();
	piPartContainer = NULL ;
	
	// -----------------------------------------------------------
	// 6- Creates an axis system
	// -----------------------------------------------------------
	CATMathPoint Origin (100.0,.0,.0);
	CATMathVector Xdir (1.0,0.0,.0);
	CATMathVector Ydir (0.0,0.0,1.0);
	
	CATIMf3DAxisSystem_var NewAxisSystem ;
	rc = pIMf3DAxisSystemFactoryOnFeatCont->CreateAxisSystem(Origin,Xdir,Ydir,NewAxisSystem);
	if ( FAILED(rc) )
		return 1;
	
	cout << endl <<"   Creation of an axis system" << endl;
	
	// update it
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	CATIUseEntity *pUseEntityOnNewAxisSystem= NULL;
    rc = NewAxisSystem->QueryInterface(IID_CATIUseEntity , (void**)& pUseEntityOnNewAxisSystem);
	if ( SUCCEEDED(rc) )
	{
	   rc = DataCommonProtocolServices::Update(pUseEntityOnNewAxisSystem);
	   pUseEntityOnNewAxisSystem->Release(); pUseEntityOnNewAxisSystem = NULL ;
	}  
#else
//============================================== 
// V5 only
//============================================== 
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
#endif
	
	// -----------------------------------------------------------
	// 7-    Retrieves the BRep plane and featurizes it
	// -----------------------------------------------------------


#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	CATBaseUnknown_var spPlaneBRep ;
	rc = NewAxisSystem->RetrievePlaneBRepAccess(CATAxisSystemZNumber,spPlaneBRep);
#else	
//============================================== 
// V5 only
//============================================== 
	CATIBRepAccess_var spPlaneBRep;
    rc = NewAxisSystem->GetPlaneBRepAccess(CATAxisSystemZNumber,spPlaneBRep);
#endif

	if ( FAILED(rc) && (NULL_var != spPlaneBRep) )
		return 1;
	
	cout <<"   Axis System BRep plane access successful" << endl;
	
	CATIMmiUseFeaturize * pIFeaturizeOnPlane = NULL ;
	rc = spPlaneBRep->QueryInterface(IID_CATIMmiUseFeaturize,(void **) &pIFeaturizeOnPlane);
	if ( FAILED(rc) )
		return 1;
	
    CATIMmiUseMfBRep_var MFPlane ;
	pIFeaturizeOnPlane->Featurize(MFPlane);
	if ( NULL_var == MFPlane )
		return 1;
	
	cout <<"   Axis System BRep featurization successful" << endl;
	
	pIFeaturizeOnPlane->Release();
	pIFeaturizeOnPlane = NULL ;
	
	// -----------------------------------------------------------
	// 8-  Creates the sketch
	// -----------------------------------------------------------
	
	CATIMmiMechanicalFeature_var NewSketch = pISketchFactoryOnFeatCont->CreateSketch(MFPlane);
	if ( NULL_var == NewSketch )
		return 1;
	
	cout <<"   Sketch creation successful" << endl;
	
	// -----------------------------------------------------------
	// 9- Releases the useless pointers
	// -----------------------------------------------------------
	
	pIMf3DAxisSystemFactoryOnFeatCont->Release();
	pIMf3DAxisSystemFactoryOnFeatCont = NULL ;
	
	pISketchFactoryOnFeatCont->Release();
	pISketchFactoryOnFeatCont = NULL ;
	
	//---------------------------------------------------------------------
	// 10- Saves 
	//---------------------------------------------------------------------
	
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	CATListPtrCATBaseUnknown pListToSave ;
	pListToSave.Append(pPsiCreatedRepRef);
	CATAdpSaver saver;
    rc = saver.Save(&pListToSave);
	
	if ( FAILED(rc)  )
		return 1;
	
	cout <<"   Save is successful " << endl;

	pPsiCreatedRepRef->Release(); 
    pPsiCreatedRepRef = NULL ;

#else
//============================================== 
// V5 only
//============================================== 
	CATString DocumentSaveAsName = "CAAAxisSystemBRep.CATPart" ;
    if ( 2 == iArgc )
    {
       DocumentSaveAsName = iArgv[1] ;
    }

    rc = CATDocumentServices::SaveAs (*pModel,DocumentSaveAsName.ConvertToChar());
    if (SUCCEEDED(rc))
    {
       cout << endl;
       cout << "   The Part document is saved in:"<< DocumentSaveAsName.ConvertToChar() << endl ;
    }
    else
       return 1;
    
#endif
	
	
	//------------------------------------------------------------------
	// 11- Closes the session
	//------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	// First unload components from session
    Bag.RemoveAll();

	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) )
		return 1;
	cout <<"   Session is closed" << endl;
#else
//============================================== 
// V5 only
//============================================== 
	// Closes the document
	rc = CATDocumentServices::Remove (*pModel);
    if ( FAILED(rc) )
    {
      cout <<"Error by closing the Part document" << endl;
      return 1;
    }
    pModel = NULL ;
  
    //Closes the session
    rc = ::Delete_Session(pSessionName);
    if (FAILED(rc) )
    {
       cout << "ERROR in delete session" << endl ;
       return 1;
    }
#endif

	cout << endl << "The CAAV5V6MmrAxisSystemBRep main program ends ...."<< endl << endl;
	
	return 0;
}
