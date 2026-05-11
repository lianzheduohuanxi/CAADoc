//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003+
//=============================================================================

//-------------------------------------------------------------
//               CAAStrCreateObjects.m                   
//-------------------------------------------------------------

/*********************************************************************
 
 This sample illustrates the way to create structure objects such as
 plates and members.

 -----
 Steps
 -----

  - 1. Creates a CATProduct document.
  - 2. Retrieves the root product.
  - 3. Creates a flate plate under the root product.
			 - Create an empty plate
			 - Create a sketch containing a rectangle
			 - Set sketch as plate support 
			 - Set thickness
			 - Set offset
			 - Set material
			 - Compute 
  - 4. Creates a curve plate under the root product.
			 - Create an empty plate
			 - Create a sketch containing a curve
			 - Create a surface (extrude of the curve)
			 - Set surface as plate support 
			 - Set thickness
			 - Set offset
			 - Set material
			 - Compute
	- 5. Creates 2 straight members (one has the section flip)under the root product.
			 - Create empty straight member1
			 - Set section
			 - Set start point
			 - Set end point
			 - Set anchor point
			 - Set angle
			 - Set material
			 - Compute
			 	- Create empty straight member2
			 - Set start point
			 - Set anchor point
			 - Set angle
			 - Set material
			 - Compute
			 - Flip section
	- 6. Creates 1 curved member under the root product.
			 - Create an empty member
			 - Create a sketch containing a curve
			 - Set curve as member support
			 - Set anchor point
			 - Set angle
			 - Set material
			 - Compute
  - 7. Save all the open document and delete the session.
 
	--------------
	How to execute 
  --------------

  - To run this sample, you can use the command:
    mkrun -c "CAAStrCreateObjects target.CATProduct section.CATPart structure.CATMaterial"

  - target.CATProduct is the output document that contains the created 
	  structure plate and shape objects.

  - section.CATPart is the section profile that defines the member.

	- structure.CATMaterial is the material catalog defines list of materials.

  First  case  : CAAStrCreateObjects Target.CATProduct InputSectionProfile MaterialCatalog 

			with : InputSectionProfile    Profile path where section document is located and 
																		that profile defines the member.
						 MaterialCatalog        Catalog location that defines list of materials.

  Second case  : CAAStrCreateObjects Target.CATProduct InputSectionProfile

			We retrieves the catalog of materials from PRM 

 -------------
 Return Errors
 -------------
  1 - ERROR bad argument number
  2 - ERROR in creating new CATProduct
  3 - ERROR in query interface to root product
  4 - ERROR in create structure plate
  5 - ERROR in create structure member
  6 - ERROR in saving document

***********************************************************************/
#include <iostream.h>

// ProductStructure Framework
#include "CATIProduct.h"
#include "CATIProductInSession.h"

// ProductStructureInterfaces Framework
#include "CATIAProduct.h"

// ObjectModelerBase Framework
#include "CATObject.h"
#include "CATInit.h"
#include "CATIDocRoots.h"
#include "CATISpecObject.h"
#include "CATDocument.h"
#include "CATSessionServices.h"
#include "CATIContainer.h"
#include "CATDocumentServices.h"

// System Framework
#include "CATLib.h"
#include "CATUnicodeString.h"

// StructureInterfaces Framework
#include "CATIAStrServices.h"
#include "CATIStructureMember.h"
#include "CATIStructurePlate.h"
#include "CATIStructureFactory.h"

// SketcherInterfaces
#include "CATISketchFactory.h"
#include "CATISketch.h"
#include "CATI2DWFFactory.h"
#include "CATI2DPoint.h"
#include "CATI2DLine.h"
#include "CATI2DCurve.h"
#include "CATLISTV_CATI2DPoint.h"

// MechanicalModeler
#include "CATIMechanicalRootFactory.h"

// GSMInterfaces
#include "CATIGSMFactory.h"
#include "CATIGSMExtrude.h"
#include "CATIGSMProceduralView.h"
#include "CATIGSMCircle3Points.h"

// MecModInterfaces
#include "CATIPrtPart.h"
#include "CATIPrtContainer.h"
#include "CATIContainerOfDocument.h"

// CATMathematics Framework
#include "CATMathDirection.h"

// Visualization
#include "CATIVisProperties.h"

// CATMatInterfaces
#include "CATIFamilyFeature.h"
#include "CATILibraryFeature.h"
#include "CATIMaterialFeature.h"
#include "CATIMaterialDocument.h"

// CATPlantShipInterfaces
#include "CATIPspResource.h"
#include "CATIPspApplication.h"

// KnowledgewareInterfaces
#include "CATICkeParmFactory.h"

#include "CATIAProducts.h" 

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

HRESULT CreateSketch(CATISpecObject_var ispSpecPrtPart, CATISketch_var &ospSketch);
HRESULT CreateCurveInSketch(CATISpecObject_var ispSpecPrtPart, CATISketch_var &ospSketch);
HRESULT CreateSurface(CATISpecObject_var ispSpecPrtPart, CATISpecObject_var ispSketch, CATISpecObject_var &ospSurface);

int main (int argc, char *iArgv[])        
{
	HRESULT rc = 0;
	// --------------------------------------- //
	//  0. Control of arguments number         //
	// --------------------------------------- //
	if ( (4 != argc) && (3 != argc) ){

		cout << "ERROR : bad number of arguments " << argc << endl << flush;
		cout << "How to execute : " << endl << flush;
		cout << "First  case  : CAAStrCreateObjects Target.CATProduct InputSectionProfile MaterialCatalog" << endl << flush;
		cout << "  InputSectionProfile Profile path where section document is located and" << endl << flush;
		cout << "                      that profile defines the member." << endl << flush;
		cout << "  MaterialCatalog     Catalog location that defines list of materials." << endl << flush;
		cout << "Second case  : CAAStrCreateObjects Target.CATProduct InputSectionProfile" << endl << flush;
		cout << "  We retrieves the catalog of materials from PRM" << endl << flush;
		return 1;  
	}

	cout << "-----------------------------------------------"<< endl << endl;
	cout << "The CAAStrCreateObjects main program begins ..."<< endl << endl;
	cout << "-----------------------------------------------"<< endl << endl;

	// ----------------------------------------- //
	//  1. Creation of a new CATProduct document //
	// ----------------------------------------- //
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",
		                  pSession );

	CATUnicodeString TargetFilePath = "";
	CATUnicodeString SectionFilePath = "";
	CATUnicodeString MaterialFilePath = "";

	if (argc >= 1)
 	  TargetFilePath = iArgv[1];

	if (argc >= 2)
    SectionFilePath = iArgv[2];

	if (argc >= 3)
	  MaterialFilePath = iArgv[3];

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Product", pDoc);
	if ( FAILED(rc) || (NULL == pDoc) ){

		cout << "ERROR in creating new CATProduct" << endl << flush;
		return 2;
	}
	cout << endl << "CATProduct Document created " << endl << flush;
	
	// --------------------------------------------------------- //
	//  2. Search for the document's root product (RootProduct)  //
	// --------------------------------------------------------- //
	CATIDocRoots *piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
		                       (void**) &piDocRootsOnDoc);
	if ( FAILED(rc) ){
		cout << "ERROR in query interface to root product" << endl << flush;
		return 3;
	}

	// GetRootContainer from pDoc
	CATInit_var spInit = pDoc;
	CATIContainer *piRootCont = NULL;
	if (!! spInit)
	{
		piRootCont = (CATIContainer *)spInit->GetRootContainer(CATIContainer::ClassName());
	}

	CATListValCATBaseUnknown_var *pRootProducts =	piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	if (NULL != pRootProducts){
		if (pRootProducts->Size())
		{  
			spRootProduct = (*pRootProducts)[1];
			delete pRootProducts;
			pRootProducts = NULL;
		}
	}
	if(piDocRootsOnDoc){
		piDocRootsOnDoc->Release();
		piDocRootsOnDoc=NULL;
	}
	
	if (0 == MaterialFilePath.GetLengthInChar())
	{
    // No material file path was defined. Use PRM to access it.

		CATIPspResource *piResource = NULL;
		CATObject *piObj = new CATObject("CATStructureDesign");
		if ( NULL != piObj )
		{
			// initialize the application PRM
			CATIPspApplication *piApplication = NULL;
			rc = piObj->QueryInterface(IID_CATIPspApplication,(void **)&piApplication);
			if (piApplication)
			{
				piApplication->Initialization(piRootCont);

				piApplication->Release();
				piApplication = NULL;	
			}

			//  Find CATIPspResource interface
			rc = piObj->QueryInterface(IID_CATIPspResource,(void **)&piResource);
			if ( FAILED(rc) ){
				cout << "ERROR in getting CATIPspResource pointer" << endl << flush;
				return 3;
			}

			piObj->Release();
			piObj = NULL;
		}

		if (NULL != piResource)
		{
			// retrieve the Structure Materials Catalog path from PRM
			CATUnicodeString StructureMaterials = "StructureMaterialsCatalog";
			rc = piResource->GetResourcePath(StructureMaterials, MaterialFilePath);
			if ( FAILED(rc) ){
				cout << "ERROR in getting material catalog path" << endl << flush;
				return 3;
			}
			else
				cout << endl << "Retrieving material catalog path from PRM " << endl << flush;

			piResource->Release();
			piResource = NULL;
		}
	}

	if (NULL != piRootCont)
	{
		piRootCont->Release();
		piRootCont = NULL;
  }

	// --------------------------------- //
	// Get material feature from catalog //
	// --------------------------------- //
	CATIMaterialFeature *piMaterialFeature = NULL;
	CATDocument *pMaterialDocument = NULL ;
  rc = CATDocumentServices::OpenDocument(MaterialFilePath, pMaterialDocument);
	if ( FAILED(rc) ){
		cout << "ERROR in opening material catalog" << endl << flush;
		return 3;
	}

	if (pMaterialDocument)
	{
		CATIMaterialDocument *pIMaterialDoc = NULL ;
		rc = pMaterialDocument->QueryInterface(IID_CATIMaterialDocument,(void **) &pIMaterialDoc);
		if ( FAILED(rc) )
		{
			cout << "ERROR no material document"<< endl << endl;
			return 3;
		}
	
		if (pIMaterialDoc)
		{
			CATILibraryFeature  *pILibraryFeature = NULL ;
			rc = pIMaterialDoc->GetMaterialLibrary(&pILibraryFeature);

			if ( FAILED(rc) )
			{
				cout << "ERROR with GetMaterialLibrary method "<< endl;
				return 3;
			}

			if (pILibraryFeature)
			{
			  int NbFamily = pILibraryFeature->GetFamilyCount();

				// Get the first family feature
				CATIFamilyFeature * pIFamilyFeature = NULL ;
				if (NbFamily >= 1)
				  pIFamilyFeature = pILibraryFeature->GetFamily(1);

				if (pIFamilyFeature)
				{
					// Get the first material of the first family feature
					piMaterialFeature = pIFamilyFeature->GetMaterial(1);

					pIFamilyFeature->Release();
					pIFamilyFeature = NULL;
				}
				pILibraryFeature->Release();
				pILibraryFeature = NULL;
			}
			pIMaterialDoc->Release();
			pIMaterialDoc = NULL;
		}
	}

	// Get CATIProduct handle on the root product.
	CATIProduct *piProductOnRoot = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct,
		                               (void**) &piProductOnRoot);
	if ( FAILED(rc) ) return 3;

	// ------------------------------------------- //
	//  1. Creation of a CATPart to store geometry //
	// ------------------------------------------- //
  CATIProduct_var spGeometryPart;

  CATIAProduct  *  oProduct  =  NULL;  
 
  CATBSTR  Name_As_BSTR;  

  CATUnicodeString  NewPartNb;  
  NewPartNb.ConvertToBSTR  (&Name_As_BSTR);  
 
  CATBSTR  TypeDocument_As_BSTR;  
  CATUnicodeString  TypeDocument("Part");  
  TypeDocument.ConvertToBSTR(&TypeDocument_As_BSTR);  
  
  CATIAProducts_var  products  (spRootProduct);  
  HRESULT  hr  =  E_FAIL;  
  if  (!!products)  
    hr=products  ->  AddNewComponent(TypeDocument_As_BSTR,Name_As_BSTR,oProduct);  
  
  CATFreeString(  TypeDocument_As_BSTR  );
  CATFreeString(  Name_As_BSTR  );
  
  if  (  SUCCEEDED(hr)  )    
  {  
    spGeometryPart  =  oProduct;  
       
    CATIProductInSession_var  Newproduct  =  oProduct;  
    if  (!!Newproduct)  
      Newproduct->SetActiveShapeRep("Default");  
  
    oProduct->Release();  
    oProduct  =  NULL;    
  }  
	// --------------------------------------------- //
	// Creates some plate and shape under the root   //
	// --------------------------------------------- //
	if (NULL != piProductOnRoot)
	{
		CATIStructureFactory *piFactory = NULL;
		piProductOnRoot->QueryInterface(IID_CATIStructureFactory, (void**) &piFactory);
		if (piFactory)
		{
	
			// --------------------------------------------------------- //
			//  3. Creates a flate plate															   //
			// --------------------------------------------------------- //
			cout << endl << "CREATE FLATE PLATE STARTING " << endl << flush;

			CATIStructurePlate *pFlatPlate = NULL;

			//Create empty plate
			rc= piFactory->CreatePlate(&pFlatPlate);

			if(SUCCEEDED(rc) && pFlatPlate){

				CATISketch_var spSketch;
				CATIPrtPart_var spPart;
				
				CATIProduct* piProduct = NULL;

				rc = pFlatPlate ->QueryInterface(IID_CATIProduct,(void**) &piProduct);

				if(SUCCEEDED(rc) && piProduct){

					CATILinkableObject_var splinkable;      
					rc = piProduct->GetShapeRep(splinkable, "Default", CATPrd3D, TRUE);
					if (SUCCEEDED(rc))
						spPart = splinkable;

					CATISpecObject_var spSpecPart = spPart;
					//Create a sketch containing a rectangle
					rc = CreateSketch(spSpecPart, spSketch);
		
				}
				else
					cout << "piProduct KO " << endl << flush;

				if(piProduct){
					piProduct->Release();
					piProduct = NULL;
				}
				//Set of imputs
				if(SUCCEEDED(rc) && !!spSketch){

					CATISpecObject* piSketch = NULL;
					rc = spSketch ->QueryInterface(IID_CATISpecObject,(void**) &piSketch);
					if(SUCCEEDED(rc) && piSketch){
						//Before doing anything we update the sketch
						piSketch->Update();
						double Thickness = 0.010;
						double Offset = 0.;
						//Set Support
						pFlatPlate ->SetContour(piSketch);
						//Set Thickness
						pFlatPlate ->SetThickness(Thickness);
						//Set Offset
						pFlatPlate ->SetInternalOffset(Offset);
						//Set Material
						pFlatPlate ->SetMaterial(piMaterialFeature);
						//Compute
						pFlatPlate ->Compute();
					}
					else
							cout << "piSketch KO " << endl << flush;
					if(piSketch){
						piSketch->Release();
						piSketch = NULL;
					}
				}
				else
					cout << "spSketch KO " << endl << flush;
			}
			else
				cout << "pFlatPlate KO " << endl << flush;
			if(pFlatPlate){
				pFlatPlate->Release();
				pFlatPlate = NULL;
			}
			// --------------------------------------------------------- //
			//  3. Creates a flate plate with sketch in an external part //
			// --------------------------------------------------------- //
			cout << endl << "CREATE FLATE PLATE WITH LINK STARTING " << endl << flush;

			CATIStructurePlate *pFlatPlate2 = NULL;

			//Create empty plate
			rc= piFactory->CreatePlate(&pFlatPlate2);

			if(SUCCEEDED(rc) && pFlatPlate2){

				CATISketch_var spSketch;
				CATIPrtPart_var spPart;

				if(spGeometryPart != NULL_var){

					CATILinkableObject_var splinkable;      
					rc = spGeometryPart->GetShapeRep(splinkable, "Default", CATPrd3D, TRUE);
					if (SUCCEEDED(rc))
						spPart = splinkable;

					CATISpecObject_var spSpecPart = spPart;
					//Create a sketch containing a rectangle
					rc = CreateSketch(spSpecPart, spSketch);
		
				}
				else
					cout << "spGeometryPart KO " << endl << flush;

				//Set of imputs
				if(SUCCEEDED(rc) && !!spSketch){

					CATISpecObject* piSketch = NULL;
					rc = spSketch ->QueryInterface(IID_CATISpecObject,(void**) &piSketch);
					if(SUCCEEDED(rc) && piSketch){
						//Before doing anything we update the sketch
						piSketch->Update();
						double Thickness = 0.010;
						double Offset = 0.;
						//Set Support
						pFlatPlate2 ->SetContour(piSketch);
						//Set Thickness
						pFlatPlate2 ->SetThickness(Thickness); 
						//Set Offset
						pFlatPlate2 ->SetInternalOffset(Offset);
						//Set Material
						pFlatPlate2 ->SetMaterial(piMaterialFeature);
						//Compute
						pFlatPlate2 ->Compute();
						//Reverse Direction
						pFlatPlate2 ->ReverseDirection();

					}
					else
							cout << "piSketch KO " << endl << flush;
					if(piSketch){
						piSketch->Release();
						piSketch = NULL;
					}
				}
				else
					cout << "spSketch KO " << endl << flush;
			}
			else
				cout << "pFlatPlate2 KO " << endl << flush;
			if(pFlatPlate2){
				pFlatPlate2->Release();
				pFlatPlate2 = NULL;
			}				
			// --------------------------------------------------------- //
			//  4. Creates a curve plate															   //
			// --------------------------------------------------------- //
			cout << endl << "CREATE CURVED PLATE STARTING " << endl << flush;

			CATIStructurePlate *pCurvePlate = NULL;

			//Create an empty plate
			rc = piFactory->CreatePlate(&pCurvePlate);


			if(SUCCEEDED(rc) && pCurvePlate){
				cout << endl << "CAAStrCreateObjects.m:	pCurvePlate OK " << endl << flush;
				CATISpecObject_var spSurface;
				CATIPrtPart_var spPart;
				
				CATIProduct* piProduct = NULL;

				rc = pCurvePlate ->QueryInterface(IID_CATIProduct,(void**) &piProduct);

				if(SUCCEEDED(rc) && piProduct){
					cout << endl << "piProduct OK " << endl << flush;
					CATILinkableObject_var splinkable;      
					rc = piProduct->GetShapeRep(splinkable, "Default", CATPrd3D, TRUE);
					if (SUCCEEDED(rc))
						spPart = splinkable;

					CATISpecObject_var spSpecPart = spPart;
					CATISketch_var spSketchToExtrude;
					//Create a sketch containing a curve
					CreateCurveInSketch(spSpecPart,spSketchToExtrude);
					CATISpecObject_var spSpecSketchToExtrude = spSketchToExtrude;
					//Create a surface (extrude of the curve)
					rc = CreateSurface(spSpecPart,spSpecSketchToExtrude, spSurface);
				}
				else
					cout << "piProduct KO " << endl << flush;

				if(piProduct){
					piProduct->Release();
					piProduct = NULL;
				}
				//Setting of attributes
				if(SUCCEEDED(rc) && !!spSurface){

					CATISpecObject* piSurface = NULL;
					rc = spSurface ->QueryInterface(IID_CATISpecObject,(void**) &piSurface);
					if(SUCCEEDED(rc) && piSurface){
						//Before doing anything we update the sketch
						piSurface->Update();
						double Thickness = 0.010;
						double Offset = 0.;
						//Set Support
						pCurvePlate ->SetSupport(piSurface);
						//Set Thickness
						pCurvePlate ->SetThickness(Thickness);
						//Set Offset
						pCurvePlate ->SetInternalOffset(Offset);
						//Set Material
						pCurvePlate ->SetMaterial(piMaterialFeature);
						//Compute
						pCurvePlate ->Compute();
					}
					else
						cout << "piSurface KO " << endl << flush;

					if(piSurface){
						piSurface->Release();
						piSurface = NULL;
					}
				}
				else
					cout << "spSurface KO " << endl << flush;
			}
			else
				cout << "pCurvePlate KO " << endl << flush;

			if(pCurvePlate){
				pCurvePlate->Release();
				pCurvePlate = NULL;
			}
			
			if(FAILED(rc)){
				cout << "ERROR in create structure plate"<< endl << endl;
				return 4;
			}
			// --------------------------------------------------------- //
			//  4. Creates a curve plate with link														   //
			// --------------------------------------------------------- //
			cout << endl << "CREATE CURVED PLATE WITH LINK STARTING " << endl << flush;

			CATIStructurePlate *pCurvePlate2 = NULL;

			//Create an empty plate
			rc = piFactory->CreatePlate(&pCurvePlate2);


			if(SUCCEEDED(rc) && pCurvePlate2){
				cout << endl << "CAAStrCreateObjects.m:	pCurvePlate OK " << endl << flush;
				CATISpecObject_var spSurface;
				CATIPrtPart_var spPart;
			

				if(!!spGeometryPart){
					CATILinkableObject_var splinkable;      
					rc = spGeometryPart->GetShapeRep(splinkable, "Default", CATPrd3D, TRUE);
					if (SUCCEEDED(rc))
						spPart = splinkable;

					CATISpecObject_var spSpecPart = spPart;
					CATISketch_var spSketchToExtrude;
					//Create a sketch containing a curve
					CreateCurveInSketch(spSpecPart,spSketchToExtrude);
					CATISpecObject_var spSpecSketchToExtrude = spSketchToExtrude;
					//Create a surface (extrude of the curve)
					rc = CreateSurface(spSpecPart,spSpecSketchToExtrude, spSurface);
				}
				else
					cout << "spGeometryPart KO " << endl << flush;

				//Setting of attributes
				if(SUCCEEDED(rc) && !!spSurface){

					CATISpecObject* piSurface = NULL;
					rc = spSurface ->QueryInterface(IID_CATISpecObject,(void**) &piSurface);
					if(SUCCEEDED(rc) && piSurface){
						//Before doing anything we update the sketch
						piSurface->Update();
						double Thickness = 0.010;
						double Offset = 0.;
						//Set Support
						pCurvePlate2 ->SetSupport(piSurface);
						//Set Thickness
						pCurvePlate2 ->SetThickness(Thickness);
						//Set Offset
						pCurvePlate2 ->SetInternalOffset(Offset);
						//Set Material
						pCurvePlate2 ->SetMaterial(piMaterialFeature);
						//Compute
						pCurvePlate2 ->Compute();
						//ReverseDirection
						pCurvePlate2 ->ReverseDirection();
					}
					else
						cout << "piSurface KO " << endl << flush;

					if(piSurface){
						piSurface->Release();
						piSurface = NULL;
					}
				}
				else
					cout << "spSurface KO " << endl << flush;
			}
			else
				cout << "pCurvePlate2 KO " << endl << flush;

			if(pCurvePlate2){
				pCurvePlate2->Release();
				pCurvePlate2 = NULL;
			}
			
			if(FAILED(rc)){
				cout << "ERROR in create structure plate"<< endl << endl;
				return 4;
			}
			// -------------------------------------------------------------------- //
			//  5. Creates 2 straight members	(the second one has the section flip)													   //
			// -------------------------------------------------------------------- //
			cout << endl << "CAAStrCreateObjects.m:	CREATE STRAIGHT MEMBER STARTING " << endl << flush;
		
			CATDocument *SectionDoc = NULL;
			rc = CATDocumentServices::OpenDocument(SectionFilePath, SectionDoc);
			if(FAILED(rc)){
				cout << "ERROR in open the section profile"<< endl << endl;
				return 5;
			}
			CATUnicodeString AnchorName = "catStrTopLeft";
			double Angle = 0.0;
			CATIStructureMember *piStraightMember1 = NULL;
			CATIStructureMember *piStraightMember2 = NULL;
			CATMathPoint PointStart1(1700.,-400.0,0.0);
			CATMathPoint PointEnd1(100.0,-400.0,0.0);

			CATMathPoint PointStart2(1700.,400.0,0.0);
			CATMathPoint PointEnd2(100.0,400.0,0.0);
			//Create empty straight member1
			rc = piFactory->CreateMember(&piStraightMember1);
			
			if (SUCCEEDED(rc) && piStraightMember1)
			{
				//Set section
				piStraightMember1->SetSection(SectionDoc);
				//Set start point
				piStraightMember1->SetStartCoord(PointStart1);
				//Set end point
				piStraightMember1->SetEndCoord(PointEnd1);
				//Set anchor point
				piStraightMember1->SetCurrentSetPoint(AnchorName);
				//Set Angle
				piStraightMember1->SetAngle(Angle);
				//Set Material
				piStraightMember1->SetMaterial(piMaterialFeature);
				//Compute
				rc = piStraightMember1->Compute();

				if (SUCCEEDED(rc))
					cout << " Create Straight Member ok" << endl << flush;
			}
			else
			{
				cout << " piStraightMember1 ko" << endl << flush;			
			}
			if(piStraightMember1){

				// edit the set point on current member
				CATUnicodeString NewAnchorName = "catStrTopCenter";
				piStraightMember1->SetCurrentSetPoint(NewAnchorName);

				// get current member length
				double Length = 0.;
				piStraightMember1->GetMemberLength(Length);
				cout << " piStraightMember1 Length is " << Length << endl << flush;

				piStraightMember1->Release();
				piStraightMember1 = NULL;
			}

			rc = piFactory->CreateMember(&piStraightMember2);

			if (SUCCEEDED(rc) && piStraightMember2)
			{
				//Set section
				piStraightMember2->SetSection(SectionDoc);
				//Set start point
				piStraightMember2->SetStartCoord(PointStart2);
				//Set end point
				piStraightMember2->SetEndCoord(PointEnd2);
				//Set anchor point
				piStraightMember2->SetCurrentSetPoint(AnchorName);
				//Set Angle
				piStraightMember2->SetAngle(Angle);
				//Set Material
				piStraightMember2->SetMaterial(piMaterialFeature);
				//Compute
				rc = piStraightMember2->Compute();

				if (SUCCEEDED(rc)){
					cout << " Create Straight Member 2 with flip ok" << endl << flush;
					piStraightMember2->Flip();
				}
			}
			else
			{
				cout << " piStraightMember2 ko" << endl << flush;			
			}

			if(piStraightMember2){				
				piStraightMember2->Release();
				piStraightMember2 = NULL;
			}

			// --------------------------------------------------------- //
			//  6. Creates curved members	     												   //
			// --------------------------------------------------------- //
			cout << endl << "CAAStrCreateObjects.m:	CREATE CURVE MEMBER STARTING " << endl << flush;

			CATIStructureMember *piCurvedMember = NULL;

			//Create an empty member
			rc = piFactory->CreateMember(&piCurvedMember);

			if (SUCCEEDED(rc) && piCurvedMember)
			{

				CATISketch_var spSketchMember;
				CATIPrtPart_var spPartMember;
				
				CATIProduct* piProductMember = NULL;

				rc = piCurvedMember ->QueryInterface(IID_CATIProduct,(void**) &piProductMember);

				if(SUCCEEDED(rc) && piProductMember){

					CATILinkableObject_var splinkableMember;      
					rc = piProductMember->GetShapeRep(splinkableMember, "Default", CATPrd3D, TRUE);
					if (SUCCEEDED(rc))
						spPartMember = splinkableMember;

					CATISpecObject_var spSpecPartMember = spPartMember;
					//Create sketch
					rc = CreateCurveInSketch(spSpecPartMember, spSketchMember);

					piProductMember->Release();
					piProductMember = NULL;
		
				}
				else
						cout << "piProductMember KO " << endl << flush;
				
				if(!!spSketchMember){

					CATISpecObject* piSketchMember = NULL;

					rc = spSketchMember ->QueryInterface(IID_CATISpecObject,(void**) &piSketchMember);

					if(piSketchMember){
						cout << "piSketchMember OK " << endl << flush;
						piSketchMember->Update();
						//Set Support
						piCurvedMember->SetMemberSupport(piSketchMember);
						//Set Section
						piCurvedMember->SetSection(SectionDoc);
						//Set Anchor point 
						piCurvedMember->SetCurrentSetPoint(AnchorName);
						//Set Angle
						Angle = 6.2831853/4;
						piCurvedMember->SetAngle(Angle);
						//Set Material
						piCurvedMember->SetMaterial(piMaterialFeature);
						//Compute
						rc = piCurvedMember->Compute();
					}
					else
						cout << "piSketchMember KO " << endl << flush;
					if(piSketchMember)
					{
						piSketchMember->Release();
						piSketchMember = NULL;
					}
				}
				else
						cout << "spSketchMember KO " << endl << flush;
				
			}
			else
			{
				cout << " CreateMember ko" << endl << flush;			
			}

			if(piCurvedMember)
			{
				piCurvedMember->Release();
				piCurvedMember = NULL;
			}
			if(FAILED(rc)){
				cout << "ERROR in create structure member"<< endl << endl;
				return 5;
			}
		}
		else
			cout << "piFactory KO " << endl << flush;

		if(piFactory){
			piFactory->Release();
			piFactory=NULL;
		}

		if (piMaterialFeature){
			piMaterialFeature->Release();
			piMaterialFeature = NULL;
		}

		piProductOnRoot->Release();
		piProductOnRoot=NULL;
	}

	// --------------------------------------------------------- //
	//  7. Save all the open document and delete the session.	   //
	// --------------------------------------------------------- //

	rc = CATDocumentServices::SaveAs(*pDoc,TargetFilePath);
	if(FAILED(rc)){
		cout << "ERROR in saving document"<< endl << endl;
		return 6;
	}
	cout << "-----------------------------------------------"<< endl << endl;
	cout << "The CAAStrCreateObjects main program end ..."<< endl << endl;
	cout << "-----------------------------------------------"<< endl << endl;
	rc = ::Delete_Session("CAA2_Sample_Session");
	return rc;
	
};

HRESULT CreateSketch(CATISpecObject_var ispSpecPrtPart, CATISketch_var &ospSketch)
{
	cout << endl << "CreateSketch -->" << endl << flush;
	HRESULT rc = E_FAIL;
	if (!!ispSpecPrtPart){
		
		CATIContainer_var spContainer = ispSpecPrtPart->GetFeatContainer();
		CATIPrtPart_var spPart = ispSpecPrtPart;
		if(!!spContainer && !!spPart){
						
			CATLISTV(CATISpecObject_var) spRefPlanes = spPart->GetReferencePlanes();
			CATISketchFactory_var spSketchFactory = spContainer;
			
			if(!!spSketchFactory){

				ospSketch = spSketchFactory->CreateSketch(spRefPlanes[1]);
				if (NULL_var != ospSketch ){

					ospSketch->OpenEdition();
					CATI2DWFFactory_var sketch2DFactory(ospSketch); // Retrieves the 2D factory to create elements
					CATI2DPoint_var spPt_bottom_left, spPt_bottom_right, spPt_top_right, spPt_top_left;
					CATI2DLine_var spLine1, spLine2, spLine3, spLine4;
					double pt_bottom_left[2]  = {100., -800};
					double pt_bottom_right[2] = {1700., -800};
					double pt_top_right[2]    = {1700., 800};
					double pt_top_left[2]     = {100., 800};
  
					spPt_bottom_left  = sketch2DFactory->CreatePoint(pt_bottom_left);
					spPt_bottom_right = sketch2DFactory->CreatePoint(pt_bottom_right);
					spPt_top_right    = sketch2DFactory->CreatePoint(pt_top_right);
					spPt_top_left     = sketch2DFactory->CreatePoint(pt_top_left);
					spLine1 = sketch2DFactory->CreateLine(pt_bottom_left,pt_bottom_right);
					spLine2 = sketch2DFactory->CreateLine(pt_bottom_right,pt_top_right);
					spLine3 = sketch2DFactory->CreateLine(pt_top_right,pt_top_left);
					spLine4 = sketch2DFactory->CreateLine(pt_top_left,pt_bottom_left);
  
					// connectivity
					CATI2DCurve_var spCurve1 (spLine1);
					CATI2DCurve_var spCurve2 (spLine2);
					CATI2DCurve_var spCurve3 (spLine3);
					CATI2DCurve_var spCurve4 (spLine4);
					spCurve1->SetStartPoint(spPt_bottom_left); 
					spCurve1->SetEndPoint(spPt_bottom_right);
					spCurve2->SetStartPoint(spPt_bottom_right); 
					spCurve2->SetEndPoint(spPt_top_right);
					spCurve3->SetStartPoint(spPt_top_right); 
					spCurve3->SetEndPoint(spPt_top_left);
					spCurve4->SetStartPoint(spPt_top_left); 
					spCurve4->SetEndPoint(spPt_bottom_left);
					ospSketch->CloseEdition();
					rc = S_OK;
				}
				else
					cout << "CreateSketch ospSketch KO " << endl << flush;
			}
			else
				cout << "CreateSketch spSketchFactory KO " << endl << flush;
		}
		else
			cout << "CreateSketch spContainer - spPart KO " << endl << flush;
	}
	else
		cout << "CreateSketch ispSpecPrtPart KO " << endl << flush;
	cout << endl << "CreateSketch <--" << endl << flush;
return rc;
}
HRESULT CreateCurveInSketch(CATISpecObject_var ispSpecPrtPart, CATISketch_var &ospSketch)
{
	cout << endl << "CreateSketchForSurface -->" << endl << flush;
	HRESULT rc = E_FAIL;
	if (!!ispSpecPrtPart){
		
		CATIContainer_var spContainer = ispSpecPrtPart->GetFeatContainer();
		CATIPrtPart_var spPart = ispSpecPrtPart;
		if(!!spContainer && !!spPart){
						
			CATLISTV(CATISpecObject_var) spRefPlanes = spPart->GetReferencePlanes();
			CATISketchFactory_var spSketchFactory = spContainer;
			
			if(!!spSketchFactory){

				ospSketch = spSketchFactory->CreateSketch(spRefPlanes[3]);
				if (NULL_var != ospSketch ){

					ospSketch->OpenEdition();
					CATI2DWFFactory_var sketch2DFactory(ospSketch); // Retrieves the 2D factory to create elements
					CATI2DPoint_var spPt_bottom_left, spPt_bottom_right, spPt_top_center;
					double pt_bottom_left[2]  = {-500., 1700.};
					double pt_bottom_right[2] = {-500., 100.};
					double pt_top_center[2]    = {-400., 900.};

					CATListValCATI2DPoint_var ListOfPoints;
  
					spPt_bottom_left  = sketch2DFactory->CreatePoint(pt_bottom_left);
					ListOfPoints.Append(spPt_bottom_left);
					
					spPt_top_center    = sketch2DFactory->CreatePoint(pt_top_center);
					ListOfPoints.Append(spPt_top_center);
					
					spPt_bottom_right = sketch2DFactory->CreatePoint(pt_bottom_right);
					ListOfPoints.Append(spPt_bottom_right);
					
					sketch2DFactory->CreateSplineCurve(ListOfPoints,0);
					ospSketch->CloseEdition();
					//Hide the sketch
					CATIVisProperties *pVisuSpec = NULL;
					rc = ospSketch->QueryInterface(IID_CATIVisProperties,(void**)&pVisuSpec);
					if( SUCCEEDED(rc) && pVisuSpec)
					{
						CATVisPropertiesValues MyProp ;
						MyProp.SetShowAttr(CATNoShowAttr);
						pVisuSpec -> SetPropertiesAtt(MyProp,CATVPShow,CATVPGlobalType);
						pVisuSpec -> Release();
						pVisuSpec = NULL ;
					}

					rc = S_OK;
				}
				else
					cout << "CreateSketchForSurface ospSketch KO " << endl << flush;
			}
			else
				cout << "CreateSketchForSurface spSketchFactory KO " << endl << flush;
		}
		else
			cout << "CreateSketchForSurface spContainer - spPart KO " << endl << flush;
	}
	else
		cout << "CreateSketchForSurface ispSpecPrtPart KO " << endl << flush;
	cout << endl << "CreateSketchForSurface <--" << endl << flush;
return rc;
}

HRESULT CreateSurface(CATISpecObject_var ispSpecPrtPart, CATISpecObject_var ispSketch, CATISpecObject_var &ospSurface)
{
	cout << endl << "CreateSurface -->" << endl << flush;
	HRESULT rc = E_FAIL;
	if (!!ispSpecPrtPart && !!ispSketch){
		
		CATIPrtContainer_var    spPrtCont = ispSpecPrtPart->GetFeatContainer();
		
		if(!!spPrtCont){

			CATIMechanicalRootFactory_var spMechRoot = spPrtCont;
			CATUnicodeString Name = "Inputs";
			CATISpecObject_var spTool;
			spMechRoot -> CreateGeometricalSet(Name,ispSpecPrtPart,spTool);
			CATIGSMFactory_var spGSMFactory = spPrtCont;
			CATICkeParmFactory_var spCkeParmFactory = spPrtCont;

			if(!!spGSMFactory && !!spCkeParmFactory && !!spTool){

				//first we create the direction of extrusion

				CATISketch_var spSketch = ispSketch;

				if(!!spSketch){

					CATISpecObject_var spPlane = spSketch -> GetSupport();

					CATIGSMDirection_var spDirection =  spGSMFactory -> CreateDirection(spPlane);

					if(!!spDirection){

						CATICkeParm_var Start = spCkeParmFactory -> CreateLength("Start",0.8);
						CATICkeParm_var End = spCkeParmFactory -> CreateLength("End",0.8);

						 
						CATIGSMExtrude_var spExtrude = spGSMFactory -> CreateExtrude(ispSketch,spDirection,Start,End,TRUE);
						ospSurface = spExtrude;
						CATIGSMProceduralView_var spSurfaceGSMV = ospSurface;
						if(!!spSurfaceGSMV){
							spSurfaceGSMV ->InsertInProceduralView(spTool) ;
							rc = S_OK;
						}
						else
							cout << "CreateSurface spSurfaceGSMV KO " << endl << flush;
					}
					else
						cout << "CreateSurface spDirection KO " << endl << flush;
				}
				else
					cout << "CreateSurface spSketch KO " << endl << flush;
			}
			else
				cout << "CreateSurface spGSMFactory KO " << endl << flush;
		}
		else
			cout << "CreateSurface spContainer KO "  << endl << flush;
	}
	else
		cout << "CreateSurface ispSpecPrtPart - ispSketch KO " << endl << flush;

	cout << endl << "CreateSurface <--" << endl << flush;
return rc;
}
