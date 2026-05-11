//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003+
//=============================================================================

//-------------------------------------------------------------
//               CAAStrRetrieveObjectDataMain                    
//-------------------------------------------------------------

/*********************************************************************
 
 This sample illustrates navigation in an existing product structure
 and retrieve plate and member's data.
     
  - 1. Opens an existing product
  - 2. Retrieves Root Product
  - 3. Retrieves all plates and plate's data under the root
  - 4. Retrieves all members and member's data under the root
  - 5. Close the open document and delete the session
     
 To run this sample, you can use the command:
    mkrun -c "CAAStrRetrieveObjectData input.CATProduct"
 where input.CATProduct is an existing document that contains the 
 structure plate and shape objects.


 Return Errors:
 -------------
  1 - ERROR bad argument number
  2 - ERROR in opening CATProduct
  3 - ERROR in query interface to root product
  4 - ERROR in read structure plate's data
  5 - ERROR in read structure member's data
  6 - ERROR in removing document

***********************************************************************/

//=============================================================================

#include <iostream.h> 

// System Framework
#include "CATLib.h"
#include "CATListOfCATUnicodeString.h"

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"

// ProductStructure Framework 
#include "CATIProduct.h"

// StructureInterfaces Framework
#include "CATIAStrServices.h"
#include "CATIStructureMember.h"
#include "CATIStructurePlate.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// SketcherInterfaces Framework
#include "CATISketch.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// Mathematics Framework
#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATLISTV_CATMathPoint.h"

// GeometricObjects Framework
#include "CATPlane.h"

// CATMatInterfaces Framework
#include "CATIMaterialFeature.h"

HRESULT GetMemberData(CATIProduct_var);
HRESULT GetPlateData(CATIProduct_var);
// ------------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
	HRESULT rc = 0;

	/* -------------------------------- */
	/*  0. Control of arguments number  */       
	/* -------------------------------- */
	 if ( 2 != argc )
	 {
		 cout << "ERROR : bad number of arguments " << argc << endl << flush;
		 return 1;  
	 }

	/* ---------------------------------------- */
	/* 1. Load an existing CATProduct document  */
	/* ---------------------------------------- */
	CATSession* pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",
		                    pSession);
	if (SUCCEEDED(rc))
	  cout << endl << " ## CAAStrRetrieveObjectData.m ## " << endl
		     << endl << " Initialize CATIA Session Succeeded " << endl << flush;

	CATDocument* pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[1],
		                             pDoc);

	if ( FAILED(rc) || (NULL==pDoc)) return 2;
	cout << endl << " product document opened : " 
		   << argv[1] << endl << flush;
	
	/* ---------------------------- */
	/* 2. Retrieves Root Product    */
	/* ---------------------------- */
	
	// Begin navigation through the document => start with the RootProduct.
	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
		                       (void**) &piDocRootsOnDoc);
	if ( FAILED(rc) ) return 3;
	
	// get the root product which is the first element of root elements
	CATListValCATBaseUnknown_var* pRootProducts = 
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	
	if (pRootProducts && pRootProducts->Size())
	{  
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	}
	piDocRootsOnDoc->Release();
	
	// Get CATIProduct handle on the root product.
	CATIProduct *piProductOnRoot = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct,
		                                (void**) &piProductOnRoot);
	if ( FAILED(rc) ) return 3;

	/* --------------------------------------------------- */
	/* 3. Retrieves all the plate object under the root   */
	/* --------------------------------------------------- */
	if (NULL != piProductOnRoot)
	{
		CATListValCATBaseUnknown_var* ListPlate =
			piProductOnRoot->GetAllChildren("CATIStructurePlate");

		if(NULL != ListPlate)
		{		
			int numberOfChildren = ListPlate->Size();
			cout << " Number of plate under the root = " << numberOfChildren << endl << endl << flush;

			/* ---------------------------------------------------------- */
			/*   For each child, get its partNumber, and InstanceName     */
			/* ---------------------------------------------------------- */
			CATIProduct_var spChild = NULL_var;
			for (int i = 1; i <= numberOfChildren; i++)
			{
				spChild = (*ListPlate)[i];
				if (NULL_var != spChild)
				{
					if  ( FAILED(rc) ) return 5;
					cout << " ## Plate child number : " << i << endl << flush;
					rc = GetPlateData( spChild );
					if (!SUCCEEDED(rc)) return 5;
				}
			}
			delete ListPlate;
			ListPlate=NULL;
		}	
	}

	/* --------------------------------------------------- */
	/* 4. Retrieves all the member object under the root   */
	/* --------------------------------------------------- */
	if (NULL != piProductOnRoot)
	{
		CATListValCATBaseUnknown_var* ListMember =
			piProductOnRoot->GetAllChildren("CATIStructureMember");

		piProductOnRoot -> Release();
		piProductOnRoot = NULL;

		if(NULL != ListMember)
		{		
			int numberOfChildren = ListMember->Size();
			cout << " Number of member under the root = " << numberOfChildren << endl << endl << flush;

			/* ---------------------------------------------------------- */
			/*   For each child, get its partNumber, and InstanceName     */
			/* ---------------------------------------------------------- */
			CATIProduct_var spChild = NULL_var;
			for (int i = 1; i <= numberOfChildren; i++)
			{
				spChild = (*ListMember)[i];
				if (NULL_var != spChild)
				{
					if  ( FAILED(rc) ) return 5;
					cout << " ## Member child number : " << i << endl << flush;
					rc = GetMemberData( spChild );
					if (!SUCCEEDED(rc)) return 5;
				}
			}
			delete ListMember;
			ListMember=NULL;
		}	
	}

	/* -------------------------------------------- */
	/*  5. Ends the session                         */
	/* -------------------------------------------- */
	
	// remove opened document
	rc = CATDocumentServices::Remove (*pDoc);
	if (!SUCCEEDED(rc)) return 6;
	
	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	
	rc = ::Delete_Session("CAA2_Sample_Session");
	if (SUCCEEDED(rc))
		cout << " Delete Session Succeeded " << endl << flush;
	
	return rc;
		
};

HRESULT GetPlateData(CATIProduct_var spChild)
{
	HRESULT rc = E_FAIL;
	if (!! spChild)
	{
		CATUnicodeString partNumber = spChild->GetPartNumber();
		CATUnicodeString instanceName (" ");
		rc = spChild->GetPrdInstanceName ( instanceName ) ;
		cout << " has as part number : " << partNumber.ConvertToChar()  << endl << flush;
		cout << " and as instanceName : " << instanceName.ConvertToChar() << endl << endl << flush;

		CATIStructurePlate *piStrPlate = NULL;
		spChild->QueryInterface(IID_CATIStructurePlate, (void**)&piStrPlate);
		if (piStrPlate)
		{
			//----------------------
			// Get Plate's thickness
			//----------------------
			double  Thickness = 0.0;
			rc = piStrPlate->GetThickness(Thickness);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's thickness " << endl << flush;
			}
			else
				cout << " THICKNESS : " << Thickness  << endl << flush;
		
			//----------------------
			// Get Plate's offset
			//----------------------
			double  Offset = 0.0;
			rc = piStrPlate->GetInternalOffset(Offset);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's offset " << endl << flush;
			}
			else
				cout << " OFFSET : " << Offset  << endl << flush;

		
			//----------------------------
			// Get Plate's support
			//----------------------------
			CATISpecObject *pSupport = NULL;
			rc = piStrPlate->GetSupport(&pSupport);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's support " << endl << flush;
			}
			else{
				cout << " Support retrieved " << endl << flush;
			}

			//----------------------------
			// Get Plate's contour
			//----------------------------
			CATISpecObject *pContour = NULL;
			rc = piStrPlate->GetContour(&pContour);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's contour " << endl << flush;
			}
			else if (NULL != pContour)
			{
				//test on the Contour nature
				CATISketch *piSketch = NULL;
				pContour->QueryInterface(IID_CATISketch, (void**)&piSketch);
				if (piSketch)
				{
					cout << " CAAStrRetrieveObjectDataMain : ";
					cout << " Contour is a sketch " << endl << flush;
					piSketch->Release(); piSketch = NULL;
				}
				else{
					cout << " CAAStrRetrieveObjectDataMain : ";
					cout << " Contour is NOT a sketch " << endl << flush;
				}
				pContour->Release(); pContour = NULL;
			}

			//------------------------------
			// Get Plate's Extrusion Vector
			//------------------------------
			CATMathDirection ExtrusionVector;
			rc = piStrPlate->GetExtrusionDirection(ExtrusionVector);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's extrusion vector " << endl << flush;
			}
			else //if ( ExtrusionVector )
			{
				cout << " Extrusion Vector X : " << ExtrusionVector.GetX()  << endl << flush;
				cout << " Extrusion Vector Y : " << ExtrusionVector.GetY()  << endl << flush;
				cout << " Extrusion Vector Z : " << ExtrusionVector.GetZ()  << endl << flush;		
			}


			//-----------------------
			// Get Plate's vertices
			//-----------------------
			CATListValCATMathPoint ListOfVertices;
			rc = piStrPlate->GetListOfVertices(ListOfVertices);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's vertices " << endl << flush;
			}
			else
			{
				int NbOfVertices = ListOfVertices.Size();

				for(int i = 1; i <= NbOfVertices; i++){
					cout << " X Coordinate of Point Nb "<< i <<" : "<< ListOfVertices[i].GetX() << endl << flush;
					cout << " Y Coordinate of Point Nb "<< i <<" : "<< ListOfVertices[i].GetY() << endl << flush;
					cout << " Z Coordinate of Point Nb "<< i <<" : "<< ListOfVertices[i].GetZ() << endl << flush;
				}
			}

			//-----------------------
			// Get Plate's Material
			//-----------------------
			CATIMaterialFeature *oMatFeat = NULL;
			rc = piStrPlate->GetMaterial(&oMatFeat);
			if (FAILED(rc) || NULL == oMatFeat)
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's material " << endl << flush;
			}
			else{
				CATUnicodeString MaterialLabel = oMatFeat -> GetLabel();
				cout << " MATERIAL : " << MaterialLabel.ConvertToChar()  << endl << flush;
			}
			
			if (NULL != oMatFeat)
			{
				oMatFeat->Release(); oMatFeat = NULL;
			}

			//-----------------------------
			// Get List Attribute Names
			//-----------------------------
			CATListValCATUnicodeString *oListOfAttributeNames = NULL;
			rc = piStrPlate->ListAttributeName(&oListOfAttributeNames);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get Plate's list attribute names" << endl << flush;
			}
			else
			{
				if (oListOfAttributeNames)
				{
					int ListSize = oListOfAttributeNames->Size();
					for (int j = 1; j <= ListSize; j++)
					{
						CATUnicodeString uName = (*oListOfAttributeNames)[j];
						cout << " ATTRIBUTE NAME : " << uName.ConvertToChar()  << endl << flush;
					}
				}
			}

			//-----------------------------
			// Get Plate's Attribute Value
			//-----------------------------
			if (oListOfAttributeNames)
			{
				int ListSize = oListOfAttributeNames->Size();
				for (int i = 1; i <= ListSize; i++)
				{
					CATICkeParm *opParm = NULL;
					CATUnicodeString ipName = (*oListOfAttributeNames)[i];
					rc = piStrPlate->GetAttribute(ipName, &opParm);
					if (FAILED(rc))
					{
						cout << " CAAStrRetrieveObjectDataMain : ";
						cout << " Failed to get Plate's attribute " << endl << flush;
					}
					if (NULL != opParm)
					{
						opParm->Release(); opParm = NULL;
					}
				}
				oListOfAttributeNames->RemoveAll();
				delete oListOfAttributeNames;
				oListOfAttributeNames = NULL;
			}

			piStrPlate->Release();
			piStrPlate = NULL;
		}
	}
	return rc;
}

HRESULT GetMemberData(CATIProduct_var spChild)
{
	HRESULT rc = E_FAIL;
	if (!! spChild)
	{
		CATUnicodeString partNumber = spChild->GetPartNumber();
		CATUnicodeString instanceName (" ");
		rc = spChild->GetPrdInstanceName ( instanceName ) ;
		cout << " has as part number : " << partNumber.ConvertToChar()  << endl << flush;
		cout << " and as instanceName : " << instanceName.ConvertToChar() << endl << endl << flush;

		CATIStructureMember *piStrMember = NULL;
		spChild->QueryInterface(IID_CATIStructureMember, (void**)&piStrMember);
		if (piStrMember)
		{
			//-----------------------------
			// Get List Attribute Names
			//-----------------------------
			CATListValCATUnicodeString *oListOfAttributeNames = NULL;
			rc = piStrMember->ListAttributeName(&oListOfAttributeNames);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's list attribute names" << endl << flush;
			}

			//-----------------------------
			// Get Member's Attribute Value
			//-----------------------------
			if (oListOfAttributeNames)
			{
				int ListSize = oListOfAttributeNames->Size();
				for (int i = 1; i <= ListSize; i++)
				{
					CATICkeParm *opParm = NULL;
					CATUnicodeString ipName = (*oListOfAttributeNames)[i];
					rc = piStrMember->GetAttribute(ipName, &opParm);
					if (FAILED(rc))
					{
						cout << " CAAStrRetrieveObjectDataMain : ";
						cout << " Failed to get member's attribute " << endl << flush;
					}
					if (NULL != opParm)
					{
						opParm->Release(); opParm = NULL;
					}
				}
				oListOfAttributeNames->RemoveAll();
				delete oListOfAttributeNames;
				oListOfAttributeNames = NULL;
			}

			//----------------------
			// Get Member's Section
			//----------------------
			CATDocument *oCATDocument = NULL;
			rc = piStrMember->GetSection(oCATDocument);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's section " << endl << flush;
			}
      CATAssert(oCATDocument);
			oCATDocument = NULL;

			//---------------------------
			// Get Member's Section Name
			//---------------------------
			CATUnicodeString oName;
			rc = piStrMember->GetSectionName(oName);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's section name " << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//--------------------------
			// Get Member's Family Name
			//--------------------------
			oName = "";
			rc = piStrMember->GetFamilyName(oName);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's family name " << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//---------------------------
			// Get Member's Catalog Name
			//---------------------------
			oName = "";
			rc = piStrMember->GetCatalogName(oName);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's catalog name " << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//---------------------------
			// Get Member's Profile Type
			//---------------------------
			oName = "";
			rc = piStrMember->GetProfileType(oName);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's profile type " << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//----------------------------
			// Get Member's Start Cutback
			//----------------------------
			CatStrCutbackType oCutbackType;
			CATICkeParm *oCutback = NULL;
			rc = piStrMember->GetStartCutback(oCutbackType, &oCutback);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's start cutback type " << endl << flush;
			}
			if (NULL != oCutback)
			{
				oCutback->Release(); oCutback = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			//--------------------------
			// Get Member's End Cutback
			//--------------------------
			CatStrCutbackType oECutbackType;
			CATICkeParm *oECutback = NULL;
			rc = piStrMember->GetEndCutback(oECutbackType, &oECutback);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's end cutback type " << endl << flush;
			}
			if (NULL != oECutback)
			{
				oECutback->Release(); oECutback = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			//-------------------------------
			// Get Member's Current SetPoint
			//-------------------------------
			CatStrPlacementPoint oSetPoint;
			rc = piStrMember->GetCurrentSetPoint(oSetPoint);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's current set point(CatStrPlacementPoint) " << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//------------------------------
			// GetMember's Current SetPoint
			//------------------------------
			CATUnicodeString uSetPoint;
			rc = piStrMember->GetCurrentSetPoint(uSetPoint);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's current set point(CATUnicodeString)" << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//--------------------
			// Get Member's Angle
			//--------------------
			CATICkeParm *oAngleParm = NULL;
			rc = piStrMember->GetAngle(&oAngleParm);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's angle " << endl << flush;
			}
			if (NULL != oAngleParm)
			{
				oAngleParm->Release(); oAngleParm = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			//---------------------------------
			// Get Member's Section Orientation
			//---------------------------------
			CatStrMaterialOrientation oSectionOrientation;
			rc = piStrMember->GetSectionOrientation(oSectionOrientation);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's section orientation(CatStrMaterialOrientation) " << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//---------------------------------
			// Get Member's Section Orientation
			//---------------------------------
			CATMathVector oU;
			CATMathVector oV;
			rc = piStrMember->GetSectionOrientation(oU, oV);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's section orientation" << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//---------------------------------
			// Get Member's Side Orientation
			//---------------------------------
			CatStrMaterialOrientation oSideOrientation;
			rc = piStrMember->GetSideOrientation(oSideOrientation);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's side orientation" << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//--------------------------------
			// Get Member's Start Coordinates
			//--------------------------------
			CATMathPoint oStartMath;
			rc = piStrMember->GetStartCoord(oStartMath);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's start coordinates" << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//------------------------------
			// Get Member's End Coordinates
			//------------------------------
			CATMathPoint oEndMath;
			rc = piStrMember->GetEndCoord(oEndMath);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's end coordinates" << endl << flush;
			}
      CATAssert(SUCCEEDED(rc));

			//---------------------------
			// Get Member's Start Offset
			//---------------------------
			CATICkeParm *oStartOffset = NULL;
			rc = piStrMember->GetStartOffset(&oStartOffset);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's start offset " << endl << flush;
			}
			if (NULL != oStartOffset)
			{
				oStartOffset->Release(); oStartOffset = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			//-------------------------
			// Get Member's End Offset
			//-------------------------
			CATICkeParm *oEndOffset = NULL;
			rc = piStrMember->GetEndOffset(&oEndOffset);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's end offset " << endl << flush;
			}
			if (NULL != oEndOffset)
			{
				oEndOffset->Release(); oEndOffset = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			//-------------------------
			// Get Member's support
			//-------------------------
			CATISpecObject *oMemSupport = NULL;
			rc = piStrMember->GetMemberSupport(&oMemSupport);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's support " << endl << flush;
			}
			if (NULL != oMemSupport)
			{
				oMemSupport->Release(); oMemSupport = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			//--------------------------
			// Get Member's section axis
			//--------------------------
			CATMathAxis oMemberSectionAxis;
			rc = piStrMember->GetMemberSectionAxis(oMemberSectionAxis);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's section axis " << endl << flush;
			}
			else
			{
				cout << " Get member's section axis OK " << endl << flush;
				CATMathVector oFirstVector;
				oMemberSectionAxis.GetFirstDirection(oFirstVector);
				CATMathVector oSecondVector;
				oMemberSectionAxis.GetSecondDirection(oSecondVector);
				CATMathVector oThirdVector;
				oMemberSectionAxis.GetThirdDirection(oThirdVector);

				cout << " First Direction Vector X : " << oFirstVector.GetX()  << endl << flush;
				cout << " First Direction Vector Y : " << oFirstVector.GetY()  << endl << flush;
				cout << " First Direction Vector Z : " << oFirstVector.GetZ()  << endl << flush;		
				cout << " SecondDirection Vector X : " << oSecondVector.GetX() << endl << flush;
				cout << " SecondDirection Vector Y : " << oSecondVector.GetY() << endl << flush;
				cout << " SecondDirection Vector Z : " << oSecondVector.GetZ() << endl << flush;		
				cout << " Third Direction Vector X : " << oThirdVector.GetX()  << endl << flush;
				cout << " Third Direction Vector Y : " << oThirdVector.GetY()  << endl << flush;
				cout << " Third Direction Vector Z : " << oThirdVector.GetZ()  << endl << flush;		
			}
      CATAssert(SUCCEEDED(rc));

			//-------------------------
			// Get Member's reference
			//-------------------------
			CATISpecObject *oMemReference = NULL;
			rc = piStrMember->GetMemberReference(&oMemReference);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's reference " << endl << flush;
			}
			if (NULL != oMemReference)
			{
				oMemReference->Release(); oMemReference = NULL;
			}

			//-----------------------
			// Get Member's Material
			//-----------------------
			CATIMaterialFeature *oMatFeat = NULL;
			rc = piStrMember->GetMaterial(&oMatFeat);
			if (FAILED(rc))
			{
				cout << " CAAStrRetrieveObjectDataMain : ";
				cout << " Failed to get member's material " << endl << flush;
			}
			if (NULL != oMatFeat)
			{
				oMatFeat->Release(); oMatFeat = NULL;
			}
      CATAssert(SUCCEEDED(rc));

			piStrMember->Release();
			piStrMember = NULL;
		}
	}
	return rc;
}

