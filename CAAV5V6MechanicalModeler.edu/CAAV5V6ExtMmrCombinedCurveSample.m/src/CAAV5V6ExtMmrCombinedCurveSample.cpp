// COPYRIGHT DASSAULT SYSTEMES 2012
//============================================================================================
//
// Abstract of CAAV5V6ExtMmrCombinedCurveSample Use Case :
//
//         Create a Part feature containing a V5V6ExtCombinedCurve. 
//         After its creation, the new Combined curve is updated.  
//
// Note : CAAV5V6ExtMmrCombinedCurveSample is the same use case as CAAMmrCombinedCurveSample. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//    
//  Steps :
//
//     1-   Check input arguments.
//     2-   Create a Session.
//     3-   Create a Part.
//     4-   Retrieve the root container.
//     5-   Retrieve the MechanicalPart feature.
//     6-   Retrieve the main Mechanical Tool feature.
//     7-   Create a geometrical set.
//     8-   Create wireframe geometry
//     9-   Update the mechanical part.
//     10-  Create a V5V6ExtCombinedCurve.
//     11-  Update the combined curve.
//     12-  Analyse the combined curve. 
//     13-  Save the Part.
//     14-  Close the Session. 
//
//==========================================================================
// How to execute :
//
// In V6
// =====
//   mkrun -c "CAAV5V6ExtMmrCombinedCurveSample Repository Server User Password SecurityCtx Environment"
//  
//	 where Repository         : The name of the repository (or provider) 
//		   Server             : The server as Host:Port_number/RootURI
//	   	   User               : The user identifier
//         Password           : The user password  
//  	   SecurityCtx        : a string representing the security context (Role.Organization.Project)
//							                Choose Role as Designer ( as the use case modifies the PLM Data)
//
// In V5
// =====
//
//   CAAV5V6ExtMmrCombinedCurveSample FileName
//
//   where FileName is the name (with or without CATPart extension) of the Part document created 
//
//============================================================================================

#include "CATIAV5Level.h"

//CAAV5V6MechanicalModeler.edu framework 
#include "CAAIV5V6ExtMmrCombCrvFactory.h"
#include "CAAIV5V6ExtMmrCombinedCurve.h"
 
//System Framework
#include "CATLib.h" 
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATBaseUnknown.h"

// KnowledgeInterfaces Framework
#include "CATListValCATICkeParm.h"

//CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h" 
#include "CATIMmiUseBasicInsertion.h"

//CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h" 
#include "CATLISTV_CATIMmiMechanicalFeature.h"

// CATMecModLiveUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIPartRequest.h"

//CATGSMUseItf framework
#include "CATIGSMUseSpline.h"
#include "CATIGSMUseLine.h"
#include "CATIGSMUsePoint.h"
#include "CATIGSMUseFactory.h" 
#include "CATIGSMUseProceduralView.h"

//ObjectModelerSystem framework 
#include "CATIAlias.h"   

// C++ Library
#include "iostream.h"  

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// CAAPLMClientAdapter Framework 
#include "CAAAdpCreateCloseSession.h" 

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//DataCommonProtocolUse Framework
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

// ProductStructureUseItf Framework
#include "CATIPrdRepresentationReferenceFactory.h"
#include "CATPrdFactory.h"

// CATPLMIntegrationAccess Framework
#include "CATAdpDictionaryServices.h"   
#include "CATIAdpEnvironment.h"        

//CATPLMIntegrationUse Framework
#include "CATAdpSaver.h" 

//PLMDictionaryNavServices
#include "CATCkePLMNavPublicServices.h"

//CAT3DPhysicalRepInterfaces Framework 
#include "CATIPsiRepresentationReference.h"

//CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

//CATMecModUseItf framework 
#include "CATIMmiUseSetFactory.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATSession.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// MecModInterfaces Framework
#include "CATIMechanicalRootFactory.h"

#endif

//============================================================================================
// Method to create geometry
HRESULT  CreateGeometryForCombinedCurve(const CATIGSMUseFactory_var &spGSMFact,
                                        const CATIMmiMechanicalFeature_var &spGeomSet,
      								    CATBaseUnknown *&piSpline1,
    								    CATBaseUnknown *&piSpline2,
   								        CATBaseUnknown *&piLine1,
                                        CATBaseUnknown *&piLine2);
//============================================================================================

int main(int iargc, char **iargv)
{
  //-----------------------------------------------------------------------------------------------
	// 1- Check input arguments
  //-----------------------------------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	
	if (6 != iargc)
	{
		cout << endl;
		cout << "CAAV5V6ExtMmrCombinedCurveSample <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>" << endl;
		cout << endl;
		return 1;
	}
#else
//============================================== 
// V5 only
//==============================================

    if (2 != iargc)
	{
       cout << endl;
       cout << "CAAV5V6ExtMmrCombinedCurveSample FileName "<< endl;
       cout << "where FileName is the complete name (with or without CATPart extension)" ;
	   cout << " of the Part created by this sample"<< endl;
       cout << endl;
       return 1;
	}
#endif

	cout <<"The CAAV5V6ExtMmrCombinedCurveSample use case begins" << endl;

	//-----------------------------------------------------------------------------------------------
	// 2- Initialize the PLM session
    //-----------------------------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	HRESULT rc = ::CAAAdpCreateSession(iargv[1], iargv[2], iargv[3], iargv[4], iargv[5]);

	if (FAILED(rc)) 
	  return 1;
#else
//============================================== 
// V5 only
//==============================================
	// Creates a session
    char *pSessionName = "SampleSession";
    CATSession *pSession = 0;
    HRESULT rc = SUCCEEDED(Create_Session(pSessionName, pSession));
    if ( FAILED (rc) )
    {
        cout << "ERROR in creating the session" << endl;
        return 1;
    }
#endif

    cout << "Session initialized" << endl;  
    
    //-----------------------------------------------------------------------------------------------
	// 3- Create a Part
    //-----------------------------------------------------------------------------------------------
	
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
		return 1;  
  
    //Create the Representation Reference 
	CATIPsiRepresentationReference *piCreatedRepRef = NULL;
	CATListValCATICkeParm_var EmptyList; 
    rc = pIPLMRepRefFactory->Create3DShape(spRepType, EmptyList, piCreatedRepRef, NULL);

	if (FAILED(rc) || (NULL == piCreatedRepRef ))
    return 1;
	
    cout <<"   The PLM Rep Ref has been created" << endl;

	pIPLMRepRefFactory->Release(); 
    pIPLMRepRefFactory = NULL;
 
	if (FAILED(rc))
	  return 1; 

    // Insert the new component in BAG
 	CATOmbLifeCycleRootsBag Bag;
 	Bag.InsertRoot(piCreatedRepRef);

    cout << "Representation reference created" << endl;

#else
//============================================== 
// V5 only
//==============================================

    // Creates a CATPart
    CATDocument *pDoc= NULL;
    CATDocumentServices::New("CATPart",pDoc);
    if (NULL == pDoc) 
    {
        cout << "ERROR in creating the part" << endl;
        return 1;
    }
    
	cout << "CATPart created" << endl;

#endif

    //-----------------------------------------------------------------------------------------------
	// 4- Retrieve the specification container ( root container) : CATPrtCont
    //-----------------------------------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

	CATIPLMNavRepReference_var spNavRepRef = piCreatedRepRef; 
	if (spNavRepRef == NULL_var)
		return 1;
    
	piCreatedRepRef->Release();
	piCreatedRepRef = NULL;

	CATIMmiPrtContainer * piPrtCont = NULL;
	rc = spNavRepRef->RetrieveApplicativeContainer("CATPrtCont",IID_CATIMmiPrtContainer,(void **)&piPrtCont);

	if (FAILED(rc) || (NULL == piPrtCont))
	  return 1;

	cout << "The Part container has been retrieved"<< endl;
#else
//============================================== 
// V5 only
//==============================================

	// Retrieves a pointer on the CATInit interface
    CATInit *piInitOnDoc = NULL ;
    rc = pDoc->QueryInterface(IID_CATInit,(void**) &piInitOnDoc);

    if (FAILED(rc) )
    {
        cout << "ERROR in initializing the part" << endl;
        return 1; 
    }
    
    // Retrieves the root container
    CATIMmiPrtContainer *piPrtCont = (CATIMmiPrtContainer*) piInitOnDoc->GetRootContainer
                                                      ("CATIMmiPrtContainer");	
    if ( NULL == piPrtCont )
    {
        cout << "ERROR in retrieving the root container" << endl;
        return 1; 
    }
    
    piInitOnDoc->Release();
    piInitOnDoc = NULL ;
#endif

    //-----------------------------------------------------------------------------------------------
	// 5- Retrieve the MechanicalPart feature
    //-----------------------------------------------------------------------------------------------

	CATIMmiMechanicalFeature_var spMechFeatOnPart;  
	rc = piPrtCont->GetMechanicalPart(spMechFeatOnPart);
	
	if (FAILED(rc) || (NULL_var == spMechFeatOnPart))
	  return 1;
    
    //-----------------------------------------------------------------------------------------------
	// 6- Retrieve the main Mechanical Tool feature
    //-----------------------------------------------------------------------------------------------

	CATIPartRequest_var spPartRequest = spMechFeatOnPart;
	if (NULL_var == spPartRequest)
		return 1;

	CATBaseUnknown_var spBUOnMainTool ;
	rc = spPartRequest->GetMainBody("",spBUOnMainTool) ;

	if (FAILED(rc) || (NULL_var == spBUOnMainTool))
		return 1;

    CATIMmiMechanicalFeature_var spMechFeatOnMainTool = spBUOnMainTool;
	if (NULL_var == spMechFeatOnMainTool)
		return 1;

    cout << "main Mechanical Tool feature has been retrieved" << endl;

    //-----------------------------------------------------------------------------------------------
	// 7- Create a geometrical set
    //-----------------------------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

	CATIMmiUseSetFactory_var spRootFactory = piPrtCont;
	if (NULL_var == spRootFactory)
		return 1; 

	CATUnicodeString GSMToolName ="GSMToolForCombinedCurve";
    CATIMmiMechanicalFeature_var spCombinedCurveTool;
	rc = spRootFactory->CreateGeometricalSet(GSMToolName, spMechFeatOnMainTool, spCombinedCurveTool);

#else
//============================================== 
// V5 only
//==============================================

    CATIMechanicalRootFactory_var spRootFactory = piPrtCont;
    if (NULL_var == spRootFactory)
		return 1; 
	   
    CATISpecObject_var spSpecOnMainTool = spMechFeatOnMainTool;
    if (NULL_var == spSpecOnMainTool)
    {
        cout << "ERROR in retrieving main tool" << endl;
        return 1;
    }   

    CATUnicodeString GSMToolName ="GSMToolForCombinedCurve";
    CATISpecObject_var spSpecOnGSMTool ;
    rc = spRootFactory->CreateGeometricalSet(GSMToolName, spSpecOnMainTool, spSpecOnGSMTool);
    CATIMmiMechanicalFeature_var spCombinedCurveTool = spSpecOnGSMTool;

#endif
    
	if (FAILED(rc) || (NULL_var == spCombinedCurveTool)) 
		return 1;

	cout<< "A Geometrical Set has been created" << endl ;

    //-----------------------------------------------------------------------------------------------
	// 8- Create wireframe geometry aggregated by the geometrical feature set
    //-----------------------------------------------------------------------------------------------
	
    // Instantiate the wireframe factory
	CATIGSMUseFactory_var spGSMFactOnPrtCont = piPrtCont;
	if (NULL_var == spGSMFactOnPrtCont)
		return 1; 

    //Create geometry : 2 splines and 2 lines
    CATBaseUnknown *piSpline1=NULL;
    CATBaseUnknown *piSpline2=NULL;
    CATBaseUnknown *piLine1=NULL;
    CATBaseUnknown *piLine2=NULL;

    rc = CreateGeometryForCombinedCurve(spGSMFactOnPrtCont, 
                                      spCombinedCurveTool,
                                      piSpline1, 
                                      piSpline2, 
                                      piLine1, 
                                      piLine2); 

	if (FAILED(rc))
      return 1;

    cout << "2 Splines and 2 Lines created" << endl;
   
    //-----------------------------------------------------------------------------------------------
	// 9- Update the MechanicalPart
    //-----------------------------------------------------------------------------------------------
	//
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATIUseEntity * piPartEntity = NULL;
	rc = spMechFeatOnPart->QueryInterface(IID_CATIUseEntity , (void**) &piPartEntity);
    if (FAILED(rc))
      return 1;

	rc = DataCommonProtocolServices::Update(piPartEntity);
	piPartEntity->Release(); 
	piPartEntity = NULL;

    if (FAILED(rc))
      return 1;
#else
//============================================== 
// V5 only
//==============================================
	 CATISpecObject *piPartEntity = NULL;
	 rc = spMechFeatOnPart->QueryInterface(IID_CATISpecObject , (void**) &piPartEntity);
	 if (FAILED(rc))
      return 1;

	 int PartUpdate = piPartEntity->Update();
	 piPartEntity->Release(); 
	 piPartEntity = NULL;
     
	 if (PartUpdate != 0)
		return 1;
#endif
    
	cout << "Mechanical part updated" << endl;

	//-----------------------------------------------------------------------------------------------
	// 10- Create V5V6ExtCombinedCurve aggregated by the geometrical feature set
    //-----------------------------------------------------------------------------------------------

	CAAIV5V6ExtMmrCombCrvFactory_var spCombinedCurveFactory = piPrtCont;
    if (NULL_var ==  spCombinedCurveFactory)
      return 1;

	piPrtCont->Release(); 
	piPrtCont = NULL;
 
	CAAIV5V6ExtMmrCombinedCurve *piCombinedCurve = NULL;
	rc = spCombinedCurveFactory->CreateCombinedCurve(piSpline1, piLine1, piSpline2, piLine2, piCombinedCurve);

    piSpline1->Release();
    piSpline1 = NULL;

    piSpline2->Release();
    piSpline2 = NULL;
 
    piLine1->Release();
    piLine1 = NULL;
 
    piLine2->Release();
    piLine2 = NULL;
  
	if (FAILED(rc))
	  return 1;
	
  
 	CATIMmiUseBasicInsertion_var hBasicInsertion = piCombinedCurve; 
	rc = hBasicInsertion->InsertInside(spCombinedCurveTool);

	if (FAILED(rc))
	  return 1;

    cout << "V5V6ExtCombinedCurve created" << endl;

    //-----------------------------------------------------------------------------------------------
	// 11- Udpate the Combined Curve
    //-----------------------------------------------------------------------------------------------
	// 
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATIUseEntity * piCombinedCurveEntity = NULL;
	rc = piCombinedCurve->QueryInterface(IID_CATIUseEntity , (void**) &piCombinedCurveEntity);
    if (FAILED(rc))
      return 1;

	rc = DataCommonProtocolServices::Update(piCombinedCurveEntity);
	piCombinedCurveEntity->Release(); 
	piCombinedCurveEntity = NULL;

	if (FAILED(rc))
	  return 9;
#else
//============================================== 
// V5 only
//==============================================
	 CATISpecObject *piCombinedCurveEntity = NULL;
	 rc = piCombinedCurve->QueryInterface(IID_CATISpecObject , (void**) &piCombinedCurveEntity);
	 if (FAILED(rc))
      return 1;

	 int CombinedCurveUpdate = piCombinedCurveEntity->Update();
	 piCombinedCurveEntity->Release(); 
	 piCombinedCurveEntity = NULL;
     
	 if (PartUpdate != 0)
		return 1;
#endif
    
	 cout << "V5V6ExtCombinedCurve instance's update OK " << endl;
     
    //-----------------------------------------------------------------------------------------------
	// 12- Analyse the combined curve
    //-----------------------------------------------------------------------------------------------
	// 
    
	// Retrieves first Curve
	CATBaseUnknown* piCurve1 = NULL ;
	rc = piCombinedCurve->GetCurve(1, piCurve1);

	if (FAILED(rc))
	  return 11;

	// Retrieves the Curve's name
	CATIAlias_var Curve1 = piCurve1;
	if (Curve1 != NULL_var)
	{
	  CATUnicodeString Name1 = Curve1->GetAlias();
	  cout << "     Curve1     : " << Name1.ConvertToChar() << endl;
	}
    
    if (piCurve1)
    {
      piCurve1->Release();
	  piCurve1 = NULL;
    }

	// Retrieves first Direction
	CATBaseUnknown* piDirection1 = NULL ;
	rc = piCombinedCurve->GetDirection(1, piDirection1);

	if (FAILED(rc))
	  return 11;
    
	// Retrieves the Direction's name
	CATIAlias_var Dir1 = piDirection1;
	if (Dir1 != NULL_var)
	{
	  CATUnicodeString Name2 = Dir1->GetAlias();
	  cout << "     Direction1     : " << Name2.ConvertToChar() << endl;
	}

    if (piDirection1)
    {
	  piDirection1->Release();
      piDirection1 = NULL;
    }

	// Retrieves second Curve
	CATBaseUnknown* piCurve2 = NULL ;
	rc = piCombinedCurve->GetCurve(2, piCurve2);

	if (FAILED(rc))
	  return 11;
    
	// Retrieves the Curve's name
	CATIAlias_var Curve2 = piCurve2;
	if (Curve2 != NULL_var)
	{
	  CATUnicodeString Name3 = Curve2->GetAlias();
	  cout << "     Curve2     : " << Name3.ConvertToChar() << endl;
	}

    if (piCurve2)
    {
	  piCurve2->Release() ;
	  piCurve2 = NULL ;
    }

	// Retrieves second Direction
	CATBaseUnknown* piDirection2 = NULL ;
	rc = piCombinedCurve->GetDirection(2, piDirection2);

    if (FAILED(rc))
	  return 11;

	// Retrieve name
	CATIAlias_var Dir2 = piDirection2;
	if (Dir2 != NULL_var)
	{
	  CATUnicodeString Name4 = Dir2->GetAlias();
	  cout << "     Direction2     : " << Name4.ConvertToChar() << endl;
	}

    if (piDirection2)
    {
	  piDirection2->Release() ;
      piDirection2 = NULL ;
    }

    if (piCombinedCurve)
    {
	  piCombinedCurve->Release();
	  piCombinedCurve = NULL ;
    }

    //-----------------------------------------------------------------------------------------------
	// 13- Save the Part
    //-----------------------------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATAdpSaver saver;
    rc = saver.Save();

	if (FAILED(rc))
		return 1;

    // Unload components from session
 	Bag.RemoveAll();

	cout <<"Session saved successfully" << endl;

#else
//============================================== 
// V5 only
//==============================================

	rc = CATDocumentServices::SaveAs (*pDoc,iargv[1]);
	if (S_OK == rc)
	{
       cout << "   The "<< iargv[1] << " document " ;
       cout << " has been saved" << endl ;
	   cout << endl;
	}

#endif
    
    //-----------------------------------------------------------------------------------------------
	// 14- Close the session
    //-----------------------------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc))
		return 1;
#else
//============================================== 
// V5 only
//==============================================
	rc = CATDocumentServices::Remove(*pDoc);
    if ( FAILED(rc) )
    {
       cout << " ERROR in the document closing" << endl ;
       return 1 ;
    }
    pDoc = NULL ;

    rc = ::Delete_Session(pSessionName);
    if (FAILED(rc))
    {
        cout << "ERROR in deleting session" << endl << flush;
        return 19;
    }

#endif

	cout <<"Session closed successfully" << endl;
    
	cout <<"The CAAV5V6ExtMmrCombinedCurveSample use case is ended" << endl;    
    
	return 0;
}

//=================================================================================================
// Method to create geometry for combinedCurve : 2 splines and 2 lines
//================================================================================================
HRESULT  CreateGeometryForCombinedCurve(const CATIGSMUseFactory_var &spGSMFact,
                                        const CATIMmiMechanicalFeature_var &spGeomSet,
      								                  CATBaseUnknown *&piSpline1,
    								                    CATBaseUnknown *&piSpline2,
   								                      CATBaseUnknown *&piLine1,
                                        CATBaseUnknown *&piLine2)
{
   HRESULT rc= E_FAIL;

    // Create first spline with three points ( first input curve of the Combined Curve )
	double iPrtSpline1Point1[3] ,  iPrtSpline1Point2[3] , iPrtSpline1Point3[3];
	iPrtSpline1Point1[0] = 20.  ;  iPrtSpline1Point2[0] =  5.  ;  iPrtSpline1Point3[0] = -20. ;
	iPrtSpline1Point1[1] =  5.  ;  iPrtSpline1Point2[1] = 30.  ;  iPrtSpline1Point3[1] =   5. ;
	iPrtSpline1Point1[2] = 20.  ;  iPrtSpline1Point2[2] = 30.  ;  iPrtSpline1Point3[2] =  20. ;
     
    // Point1
    CATIGSMUsePoint_var Spline1Point1 = spGSMFact->CreatePoint(iPrtSpline1Point1);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView1OnPoint1 = Spline1Point1;
    if (NULL_var != spProceduralView1OnPoint1)
      rc = spProceduralView1OnPoint1->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;

    // Point2
	CATIGSMUsePoint_var Spline1Point2 = spGSMFact->CreatePoint(iPrtSpline1Point2);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView1OnPoint2 = Spline1Point2;
    if (NULL_var != spProceduralView1OnPoint2)
      rc = spProceduralView1OnPoint2->InsertInProceduralView(spGeomSet);
    else
    rc = E_FAIL;

    if (FAILED(rc))
      return rc;
    
    // Point3
	CATIGSMUsePoint_var Spline1Point3 = spGSMFact->CreatePoint(iPrtSpline1Point3);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView1OnPoint3 = Spline1Point3;
    if (NULL_var != spProceduralView1OnPoint3)
      rc = spProceduralView1OnPoint3->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;

    // Spline1
    CATLISTV(CATIMmiMechanicalFeature_var)ListOfPointsSpline1;
	ListOfPointsSpline1.Append(Spline1Point1);
	ListOfPointsSpline1.Append(Spline1Point2);
	ListOfPointsSpline1.Append(Spline1Point3);
    
	CATIGSMUseSpline_var spSpline1 = spGSMFact->CreateSplinePoints(ListOfPointsSpline1);

    // Append spline in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralViewOnSpline1 = spSpline1;
    if (NULL_var != spProceduralViewOnSpline1)
      rc = spProceduralViewOnSpline1->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;

    cout << "First spline created" << endl;
    
	// Creates second spline with 4 points ( second input curve of the Combined Curve )
    double iPrtSpline2Point1[3] ,  iPrtSpline2Point2[3] , iPrtSpline2Point3[3] , iPrtSpline2Point4[3] ;
	iPrtSpline2Point1[0] = -40. ;  iPrtSpline2Point2[0] = -10.  ;  iPrtSpline2Point3[0] =  25.  ;  iPrtSpline2Point4[0] = 50. ; 
	iPrtSpline2Point1[1] =   0. ;  iPrtSpline2Point2[1] =   0.  ;  iPrtSpline2Point3[1] =   0.  ;  iPrtSpline2Point4[1] =  0. ; 
	iPrtSpline2Point1[2] = 120. ;  iPrtSpline2Point2[2] =  80.  ;  iPrtSpline2Point3[2] = 100.  ;  iPrtSpline2Point4[2] = 50. ; 
     
    // Point1
    CATIGSMUsePoint_var Spline2Point1 = spGSMFact->CreatePoint(iPrtSpline2Point1);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView2OnPoint1 = Spline2Point1;
    if (NULL_var != spProceduralView2OnPoint1)
      rc = spProceduralView2OnPoint1->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;

    // Point2
    CATIGSMUsePoint_var Spline2Point2 = spGSMFact->CreatePoint(iPrtSpline2Point2);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView2OnPoint2 = Spline2Point2;
    if (NULL_var != spProceduralView2OnPoint2)
      rc = spProceduralView2OnPoint2->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;  
  
    // Point3
    CATIGSMUsePoint_var Spline2Point3 = spGSMFact->CreatePoint(iPrtSpline2Point3);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView2OnPoint3 = Spline2Point3;
    if (NULL_var != spProceduralView2OnPoint3)
      rc = spProceduralView2OnPoint3->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL; 

    if (FAILED(rc))
      return rc;  
	
    // Point4
    CATIGSMUsePoint_var Spline2Point4 = spGSMFact->CreatePoint(iPrtSpline2Point4);

    // Append point in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralView2OnPoint4 = Spline2Point4;
    if (NULL_var != spProceduralView2OnPoint4)
      rc = spProceduralView2OnPoint4->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;  

    CATLISTV(CATIMmiMechanicalFeature_var) ListOfPointsSpline2;
	ListOfPointsSpline2.Append(Spline2Point1);
	ListOfPointsSpline2.Append(Spline2Point2);
	ListOfPointsSpline2.Append(Spline2Point3);
	ListOfPointsSpline2.Append(Spline2Point4);
       
    // Spline2
 	CATIGSMUseSpline_var spSpline2 = spGSMFact->CreateSplinePoints(ListOfPointsSpline2);

    // Append spline in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralViewOnSpline2 = spSpline2;
    if (NULL_var != spProceduralViewOnSpline2)
      rc = spProceduralViewOnSpline2->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;

    cout << "Second spline created" << endl;
    
	// Create first and second line ( first and second input directions of the Combined Curve )  
	double iPtrOriginePoint[3] ;
	iPtrOriginePoint[0] = 0. ;
	iPtrOriginePoint[1] = 0. ;
	iPtrOriginePoint[2] = 0. ;
    
	double YVector[3];
	YVector[0] = 0. ;
	YVector[1] = 1. ;
	YVector[2] = 0. ;
    
	double ZVector[3];
	ZVector[0] = 0. ;
	ZVector[1] = 0. ;
	ZVector[2] = 1. ;
     
    // Line1
	CATIGSMUseLine_var spLine1 = spGSMFact->CreateLine(iPtrOriginePoint, ZVector);

    // Append line in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralViewOnLine1 = spLine1;
    if (NULL_var != spProceduralViewOnLine1)
      rc = spProceduralViewOnLine1->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL;

    if (FAILED(rc))
      return rc;  

    // Line2
    CATIGSMUseLine_var spLine2 = spGSMFact->CreateLine(iPtrOriginePoint, YVector);

    // Append line in geometrical feature set
    CATIGSMUseProceduralView_var spProceduralViewOnLine2 = spLine2;
    if (NULL_var != spProceduralViewOnLine2)
      rc = spProceduralViewOnLine2->InsertInProceduralView(spGeomSet);
    else
      rc = E_FAIL; 


    //Cast outputs to CATBaseUnknown
    rc =  spSpline1->QueryInterface(IID_CATBaseUnknown , (void**) &piSpline1);
    if (SUCCEEDED(rc))
    {
      rc =  spSpline2->QueryInterface(IID_CATBaseUnknown , (void**) &piSpline2);
      if (SUCCEEDED(rc))
      {
        rc =  spLine1->QueryInterface(IID_CATBaseUnknown , (void**) &piLine1);
        if (SUCCEEDED(rc))
        rc =  spLine2->QueryInterface(IID_CATBaseUnknown , (void**) &piLine2);
      }
    }
 
    // Set all pointers to NULL if failure
    if (FAILED(rc))
    {
      if (piSpline1)
      {
        piSpline1->Release();
        piSpline1=NULL;
      }
      if (piSpline2)
      {
        piSpline2->Release();
        piSpline2=NULL;
      }
      if (piLine1)
      {
        piLine1->Release();
        piLine1=NULL;
      }
      if (piLine2)
      {
        piLine2->Release();
        piLine2=NULL;
      }
    }

    return rc;
}
