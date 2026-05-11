// COPYRIGHT DASSAULT SYSTEMES 2012
//============================================================================================
// 
// Mission         : Set and get applicative attributes on a part sub element.
//                   Set and get a color that overloads a part sub element.
//
// Note : CAAV5V6MmrApplicativeAttributes is the same use case as CAAMmrApplicativeAttributes. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
// Steps :        
// 
//    1-    Checks number of arguments
//	  2-    Initialization : create a session, load the part and retrieve the specification container	
//    3-    Retrieves the MechanicalPart 
//    4-    Retrieves BRepAccess of all faces 
//    5-    Retrieving and displaying current faces colors  
//    6-    Setting a new Color on all faces
//    7-    Retrieving colors that just have been set
//    8-    Setting Applicative Attributes
//    9-    Retrieving the applicative attributes we have just set
//    10-   Saves the part
//    11-   Closes the session
//==========================================================================
//How to execute :
//
// In V6
// =====
//	 mkrun -c "CAAV5V6MmrApplicativeAttributes Repository Server UserId Password SecurityCtx Environment PLMExternalIDValue Version"
//
//	 where    Repository	: The name of the repository (or provider) 
//			  Server		: The server as Host:Port_number/RootURI
//			  User			: The user identifier
//            Password		: The user password  
//			  SecurityCtx   : A string representing the security context (Role.Organization.Project).
//							  choose Role as Designer(as use case modifies the PLM Data)
//			  PLM_RepType   : A string representing PLM Representation type  
//			  PLMExternalIDValue : the value of the PLM_ExternalID attribute of the PLM representation reference 
//			  Version       : the attribute value of the same PLM Representtaion Reference 
//
// In V5
// =====
//
//  mkrun -c "CAAV5V6MmrApplicativeAttributes  FileNameIn FileNameOut"
//
//   where    FileNameIn  : The complete name of a Part document
//            FileNameOut : The complete name to saveas FileNameIn             
//
//============================================================================================

// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATListOfInt.h"

// Local framework
#include "CAAV5V6MmrInitSession.h" 

// CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"
#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiUseBRepAccess.h"
#include "CATLISTV_CATIMmiUseBRepAccess.h"
#include "CATIMmiSubElemProperties.h"
#include "CATMmiUseServicesFactory.h" 
#include "CATIMmiUseBRepDecodeServices.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"
#include "CATIPartRequest.h"
#include "CATIBodyRequest.h"

// GMModelInterfaces Framework
#include "CATBody.h"
#include "CATCell.h"
#include "CATListOfCATCells.h"

// KnowledgeInterfaces Framework
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATCkeGlobalFunctions.h"


// Standard C++ library
#include <iostream.h> 


#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 

// CAAPLMClientAdapter.edu
#include "CAAAdpCreateCloseSession.h"

// CAT3DPhysicalRepInterfaces
#include "CATIPsiRepresentationLoadMode.h"

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

// CATPLMIdentificationAccess Framework
#include "CATIPLMComponent.h"            

// CATPLMIntegrationUse Framework
#include "CATAdpSaver.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectModelerBase Framework
#include "CATDocumentServices.h" 
#include "CATSessionServices.h"

#endif


int main(int iArgc,char **iArgv) 
		 
{
	// return code
	int rcode = 0;
	
    //
	// 1- Checks number of arguments
	//
#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	if( 9 != iArgc )
	{
		cout <<"CAAV5V6MmrApplicativeAttributes <repository> <server> <user> <password> <SecurityCtx> <PLMRepType> <PLMExternalIDValue> <version>" << endl;
		return 1;
	}
#else
//============================================== 
// V5 only
//============================================== 
	if( 3!=iArgc )
    {
      cout <<"CAAV5V6MmrApplicativeAttributes FileNameIn FileNameOut" << endl;
      cout <<"Where FileNameIn is the complete path of a CATPart document" <<endl;
      cout <<" and FileNameOut, the complete path of the output document" <<endl;
      cout <<"For FileNameIn, you can use the following Part: " ;
      cout <<" $WSROOT/CAAMechanicalModeler.edu/InputData/CAAV5V6MmrApplicativeAttributesPart.CATPart"<< endl;
      return 1;
    }
#endif

	cout << "The CAAV5V6MmrApplicativeAttributes use case begins" << endl << endl;

#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
	//
    //-----------------------------------------------------------------------------------
	// 2- Creates a session with : repository, server, user,password, SecurityCtx
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
    // 2- Creates a session
    //    Loads the Part document
    //    Retrieves the Part Container
    //
    char *pSessionName = "SampleSession";
    CATIMmiPrtContainer * piPartContainer = NULL;
	CATDocument *pDoc = NULL;
    HRESULT rc =  CAAV5V6MmrInitSession(pSessionName, iArgv[1], pDoc, piPartContainer) ;
       
    if (FAILED(rc) || (NULL == piPartContainer))
		return 1;

    cout << "The Part document has been opened and the Part container has been retrieved"<< endl;
 
#endif	

	//
	// 3- Retrieves the MechanicalPart 
	//
	CATIMmiMechanicalFeature_var spMechFeatOnPart ;  
	rc = piPartContainer->GetMechanicalPart(spMechFeatOnPart);

	if ( FAILED(rc) || (NULL_var == spMechFeatOnPart))
		return 1 ;

	
	cout <<"   MechanicalPart retrieved" << endl;
	
	piPartContainer->Release();
	piPartContainer = NULL ;
	
	//
	// 4 - Retrieves BRepAccess of all faces
	//
 	
 	//get the main body (PartBody)
	CATIPartRequest_var spPartRequest = spMechFeatOnPart ;
	if ( NULL_var == spPartRequest )
		return 1;
	
 	CATBaseUnknown_var spMainPartBody ;
	rc = spPartRequest->GetMainBody("",spMainPartBody);
	if ( FAILED(rc) || ( NULL_var == spMainPartBody) )
		return 1;
	
	cout <<"   GetMainBody successful" << endl;

	//Retrieves the feature holding the result of the main body
	//It's the first element of the list returned by GetResults
    CATIBodyRequest_var spMainPartBodyRequest = spMainPartBody;
	if ( NULL_var == spMainPartBodyRequest )
		return 1;
	
    CATLISTV(CATBaseUnknown_var) ListResult ;
	rc = spMainPartBodyRequest->GetResults( "", ListResult) ;
	if (!SUCCEEDED(rc) || 0>= ListResult.Size())
		return 1;
	
	cout <<"   GetResults successful" << endl;
    
	CATIMmiUseGeometricalElement_var spFeatureResultGeomElem = ListResult[1];
	if ( NULL_var == spFeatureResultGeomElem )
		return 1;
	
	//retrieves its associated CATBody 
    CATBody_var spBody = NULL_var;
    spFeatureResultGeomElem->GetBodyResult(spBody);
    if ( NULL_var == spBody ) 
      return 1;
                
    //retrieves the faces
    CATLISTV(CATBaseUnknown_var) ListBreps;
    CATLISTP(CATCell) faceList;
    spBody->GetAllCells( faceList, 2 ); 

    // Decode BReps from faces.
    CATIMmiUseBRepDecodeServices_var spBRepDecodeServices;
	CATMmiUseServicesFactory::CreateBRepDecodeServices(spBRepDecodeServices); 
	if (spBRepDecodeServices == NULL_var)
		return 1;

    for (int nFace = 1; nFace <= faceList.Size(); nFace++)
    {
      CATCell_var spCell = faceList[nFace];
      if (NULL_var != spCell) 
      {
        CATIMmiUseBRepAccess_var spBRepAccess = NULL_var;
        spBRepDecodeServices->DecodeCellInBody(spBRepAccess, spCell, spBody);
        if ( NULL_var!=spBRepAccess)
          ListBreps.Append( spBRepAccess );
      }
    }

	int nbfaces = ListBreps.Size();

	// 5- retrieving and displaying current faces colors
	cout<<"   --------------------------"<<endl;
	cout<<"   Retrieving current colors"<<endl;
	CATListOfInt retrieveRed,retrieveGreen,retrieveBlue;
	
    CATIMmiSubElemProperties_var spSubElemProperties ;
    rc =  CATMmiUseServicesFactory::CreateSubElemPropertiesAccess(spSubElemProperties); 

    if (FAILED(rc) || (NULL_var == spSubElemProperties))
      return 1;

	rc = spSubElemProperties->GetColorsOnSubElements(ListBreps, retrieveRed,retrieveGreen,retrieveBlue);
	if (E_FAIL == rc)
		return 1;
	int compt =1;
	for (compt =1; compt<=nbfaces; compt++)
		cout<<"   for the "<<compt<<" face, associated color components are : R "<<retrieveRed[compt]<<" G "<<retrieveGreen[compt]<<" B "<<retrieveBlue[compt]<<endl;
	
	//
	// 6- Setting a new Color on all faces
	//
	
	//we are to color the faces with different color according their position : three by three will have the same color
	cout<<"   --------------------------"<<endl;
	cout<<"   Setting new colors"<<endl;
	
	CATListOfInt newRed,newGreen,newBlue,FailedIndex;
	int x=0;
	for (compt = 1;compt<= nbfaces;compt++)
	{
		x = compt%3;
		int red(0),green(0),blue(0);
		if (1 == x)
			red = 255;
		if (2 == x)
			green = 255;
		if (0 == x)
			blue = 255;
		newRed.Append(red);
		newGreen.Append(green);
		newBlue.Append (blue);
		cout<<"   Setting R "<<red<<" G "<<green<<" B "<<blue<<" on the "<<compt<<" face"<<endl;
	}
	
	rc = spSubElemProperties->SetColorsOnSubElements(ListBreps,newRed,newGreen,newBlue,FailedIndex);
	if (E_FAIL == rc)
		return 1;
	
    cout<<"   Colors successfully set on every faces"<<endl;

	//
	// 7- retrieving colors we have just set
	//
	cout<<"   --------------------------"<<endl;
	cout<<"   Retrieving new colors"<<endl;
	rc = spSubElemProperties->GetColorsOnSubElements( ListBreps, retrieveRed,retrieveGreen,retrieveBlue);
	if (E_FAIL == rc )
		return 1;
	
	for (compt =1;compt<=nbfaces;compt++)
		cout<<"   for the "<<compt<<" face, associated color components are : R "<<retrieveRed[compt]<<" G "<<retrieveGreen[compt]<<" B "<<retrieveBlue[compt]<<endl;
	
	//
	// 8- Setting Applicative Attributes
	//
	
	//
	// 8 - 1 creating new attributes 
	cout<<"   --------------------------"<<endl;
	cout<<"   Creating applicative attributes for different faces"<<endl;
	CATListOfCATUnicodeString **AttrNameListToSet = new CATListOfCATUnicodeString*[nbfaces];
	CATCkeListOfParm *AttrValueListToSet = new CATCkeListOfParm[nbfaces];
	CATICkeParmFactory_var factory = CATCkeGlobalFunctions::GetVolatileFactory();
	for (compt = 1;compt<= nbfaces;compt++)
	{
		cout<<"   Creating ";
		x = compt%3;
		//for each face we create a new list of apllicative attributes
		//an applicative attribute is made of a Name and a value
		if (1 == x)
		{
			AttrNameListToSet [compt-1] = new CATListOfCATUnicodeString (3);
			AttrValueListToSet[compt-1]   = new CATLISTV(CATBaseUnknown_var)(3);
			
			//The first attribute will be the number of the face
			AttrNameListToSet [compt-1]->Append("FACE_NUMBER");
			CATICkeParm_var tempcke1 = factory -> CreateInteger ("FACE_NUMBER",compt);
			AttrValueListToSet[compt-1]->Append(tempcke1);
			
			cout<<"    FACE_NUMBER with value "<<compt; 
			
			//the second will be the color
			AttrNameListToSet [compt-1]->Append("COLOR");
			CATICkeParm_var tempcke2 = factory -> CreateString ("COLOR","Red");
			AttrValueListToSet[compt-1]->Append(tempcke2);
			
			cout<<"    COLOR with value Red";
			
			//the third is x
			AttrNameListToSet [compt-1]->Append("X");
			CATICkeParm_var tempcke3 = factory -> CreateReal ("X",x);
			AttrValueListToSet[compt-1]->Append(tempcke3);
			
			cout<<"    X with value "<<x;
			cout<<"    for face nb "<<compt<<endl;
		}
		else 
			//just to show you you can have different size of list
		{
			AttrNameListToSet [compt-1] = new CATListOfCATUnicodeString (2);
			AttrValueListToSet[compt-1]   = new CATLISTV(CATBaseUnknown_var)(2);
			
			//The first attribute will be the number of the face
			AttrNameListToSet [compt-1]->Append("FACE_NUMBER");
			CATICkeParm_var tempcke1 = factory -> CreateInteger ("FACE_NUMBER",compt);
			AttrValueListToSet[compt-1]->Append(tempcke1);
			
			cout<<"    FACE_NUMBER with value "<<compt; 
			
			//the second will be the color
			AttrNameListToSet [compt-1]->Append("COLOR");
			if (2 == x)
			{
				CATICkeParm_var tempcke2 = factory -> CreateString ("COLOR","Green");
				AttrValueListToSet[compt-1]->Append(tempcke2);
				
				cout<<"    COLOR with value Green";
			}
			if (0 == x)
			{
				CATICkeParm_var tempcke2 = factory -> CreateString ("COLOR","Blue");
				AttrValueListToSet[compt-1]->Append(tempcke2);
				
				cout<<"    COLOR with value Blue";
			}
			
			cout<<"    on face nb "<<compt<<endl;
			
		}
	}
	
	// 8 - 2 Setting the applicative attributes
	cout<<endl<<"   Setting applicative attributes on different faces"<<endl;
	FailedIndex.RemoveAll();
	rc=spSubElemProperties->SetAttributesOnSubElements(ListBreps, AttrNameListToSet,AttrValueListToSet,FailedIndex);
	if (S_FALSE == rc)
	{
		int nberrors = FailedIndex.Size();
		cout<<"Error, setting applicative attriutes on faces fails for faces :";
		for (compt = 1;compt<= FailedIndex.Size(); compt++)
		{
			cout<<"    "<<FailedIndex[compt];
		}
		cout<<endl;
	}
	else
		cout<<"   Applicative attributes successfully set"<<endl;
	
	// 8 - 3 cleaning
	for  (compt=1; compt<=nbfaces;compt++)
	{
		AttrNameListToSet[compt-1]->RemoveAll(); delete AttrNameListToSet[compt-1];  AttrNameListToSet[compt-1] = NULL;
		AttrValueListToSet[compt-1]->RemoveAll();delete AttrValueListToSet[compt-1]; AttrValueListToSet[compt-1] = NULL;
	}
	
	delete [] AttrNameListToSet; AttrNameListToSet = NULL;
	delete [] AttrValueListToSet;AttrValueListToSet = NULL;
	
	//
	// 9 - Retrieving the applicative attributes we have just set
	//
	cout<<"   --------------------------"<<endl;
	cout<<"   Getting applicative attributes on faces"<<endl;
	//
	// 9 - 1 Getting attributes
	CATListOfCATUnicodeString * AttributNameList = new CATListOfCATUnicodeString[nbfaces];
	CATCkeListOfParm  AttrValList = new CATListValCATBaseUnknown_var[nbfaces];
	rc = spSubElemProperties->GetAttributesOnSubElements(ListBreps, AttributNameList, AttrValList );
	if (SUCCEEDED(rc))
	{
		CATListOfCATUnicodeString templiststring;
		CATListValCATBaseUnknown_var tempCke;
		for (compt=1;compt<=nbfaces;compt++)
		{
			//retrieve a list a position k (arrays start at position zero).
			templiststring =  (AttributNameList)[compt-1];
			tempCke = (AttrValList)[compt-1];
			
			int nbAttributes = templiststring.Size();
			int nbValues     = tempCke.Size();
			
			//the list must have the same size! If not, we jump to the next face
			if (nbAttributes != nbValues)
				continue;
			else
				cout<<"   For face "<<compt<<" there is(are) "<<nbAttributes<<" attribute(s) that is(are) : "<<endl;
			for (int i=1;i<=nbAttributes;i++)
				cout<<"       - "<<templiststring[i].ConvertToChar()<<" = "<<((CATICkeParm_var)( tempCke[i] ))->Content().ConvertToChar()<<endl;
			templiststring.RemoveAll();
			tempCke.RemoveAll();
			
		}
	}
	else if (E_FAIL == rc)
		return 1;
	//
	// 9 - 2 Cleaning List:
	for  (int i=0; i < nbfaces;i++)
	{
		AttributNameList[i].RemoveAll();
		AttrValList[i].RemoveAll();
	}
	delete [] AttributNameList;	AttributNameList = NULL;
	delete [] AttrValList;	    AttrValList = NULL;
	
#ifdef CATIAR214	
//============================================== 
// V6 only
//============================================== 
    //
	// 10- Saves the representation
	//
	CATAdpSaver saver;
    rc = saver.Save();

	if (FAILED(rc))
		return 1;
	
	cout << "   Session saved successfully" << endl ;

	//
	// 11- Closes the session	
	//
    
	// First Unload components from session
    Bag.RemoveAll();

	rc = ::CAAAdpCloseSession();
	if (FAILED(rc))
		return 1;
	cout << "   Session closed successfully" << endl ;

#else
//============================================== 
// V5 only
//============================================== 
    //
    // 10- Saves the document
    //
   rc = CATDocumentServices::SaveAs(*pDoc, iArgv[2]);
   if (S_OK == rc)
   {
     cout << "   The "<< iArgv[2] ;
     cout << " document contains the modified Part" << endl ;
   }
   else
   {
     cout << "Error in saving document "<< iArgv[2] << endl;
     return 1;
   }   

   //
   // 11 - Closes the document
   //
   rc = CATDocumentServices::Remove(*pDoc);
   if (FAILED(rc))
   {
     cout << "Error in closing document" << endl ;
     return 1;
   }
   pDoc = NULL ;

   //
   // 12 - Deletes all documents in session	
   //
   rc = Delete_Session(pSessionName);
   if (FAILED(rc))
   {
     cout << "Error in deleting session" << endl ;
     return 1;
   }  
#endif
	
	cout << "The CAAV5V6MmrApplicativeAttributes use case is ended" << endl <<endl;
	
	return 0;

	
}
