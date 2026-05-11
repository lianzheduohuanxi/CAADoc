// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationWithMATPComputation :
//
// Sample code for : CAA User Operation connected with 3D Machining Area (sample 6)
//
// Mission         : Customize the Tool Path Computation of the User Operation connected
//                   with a machining area. The tool path created describes the bounding boxes
//                   of the different zones of the machining area.
//                   
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a user operation
//                   3- Select geometry
//                   4- Replay the tool path
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct in the resources\graphic directory of the runtime view.
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationWithMATPComputation.h"
 
// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgActivityParameters.h"
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathComponents.h"
#include "CATIMfgToolPathConstantToolAxis.h"
#include "CATIMfgToolPathFactory.h"
#include "CATIMfgTPSaveData.h"
#include "CATMfgToolPathDefs.h"

// Surface Machining Interfaces
#include "CATISmgMachiningAreaParts.h"
#include "CATISmgMachiningAreaChecks.h"
#include "CATISmgMachiningAreaGuidingCurves.h"

// Mathematics Interfaces
#include "CATMathVector.h"
#include "CATMathBox.h"

// Geometric Objects Interfaces
#include "CATCurve.h"


// Tie the implementation to its interface
CATImplementBOA (CATIMfgComputeToolPathCustom, CAAESmiUserOperationWithMATPComputation);
CATImplementClass( CAAESmiUserOperationWithMATPComputation,
                   CacheExtension,
                   CATIMfgComputeToolPathCustom,
                   CAASmgOperationWithMA );
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationWithMATPComputation::CAAESmiUserOperationWithMATPComputation()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationWithMATPComputation::~CAAESmiUserOperationWithMATPComputation()
{
}
 
//========================================================================
// ComputeToolPath
//========================================================================
HRESULT CAAESmiUserOperationWithMATPComputation::ComputeToolPath (const CATIContainer_var& iContainer, CATIMfgToolPath_var& oTP)
{
	HRESULT RC = S_OK;

	// Check input argument
	if (NULL_var == iContainer) return E_FAIL;

	// Retrieves Activity	
	CATIMfgActivity * pActivity = NULL;
	RC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
	if (SUCCEEDED(RC))
	{
		CATMathBox PartsBBox, ChecksBBox, GuidingCurvesBBox;

		// Gets Machining Area
		CATBaseUnknown_var spBaseFeature = pActivity->GetFeature();	
		if (!!spBaseFeature)
		{
			// Gets geometry from PART of the machining area
			CATISmgMachiningAreaParts * pParts = NULL;
			RC = spBaseFeature->QueryInterface(IID_CATISmgMachiningAreaParts, (void**) &pParts);
			if (SUCCEEDED(RC))
			{
				// Gets geometry of parts
				CATLISTP(CATGeometry) ListOfGeometries;
				RC = pParts->GetGeometricElements(ListOfGeometries);
						
				// Gets the bouding box of the geometry of the part body
				GetBoundingBox(ListOfGeometries,PartsBBox);

				pParts->Release();
				pParts = NULL;
			}
			
			// Gets geometry from CHECK of the machining area
			CATISmgMachiningAreaChecks * pChecks = NULL;
			RC = spBaseFeature->QueryInterface(IID_CATISmgMachiningAreaChecks, (void**) &pChecks);
			if (SUCCEEDED(RC))
			{
				// Gets geometry of checks
				CATLISTP(CATGeometry) ListOfGeometries;
				RC = pChecks->GetGeometricElements(ListOfGeometries);
						
				// Gets the bouding box of the geometry of the checks
				GetBoundingBox(ListOfGeometries,ChecksBBox);

				pChecks->Release();
				pChecks = NULL;
			}
			
			// Gets geometry from LIMITING CURVE of the machining area
			CATISmgMachiningAreaGuidingCurves * pGuidingCurves = NULL;
			RC = spBaseFeature->QueryInterface(IID_CATISmgMachiningAreaGuidingCurves, (void**) &pGuidingCurves);
			if (SUCCEEDED(RC))
			{
				// Gets geometry of Limiting Curves
				CATLISTP(CATCurve) ListOfCurves;
				RC = pGuidingCurves->GetResultingCATCurves(ListOfCurves);

				// Fill a list of CATGeometry from CATCurve
				CATLISTP(CATGeometry) ListOfGeometries;
				int NbCurves = ListOfCurves.Size();
				for (int ic=1;ic<=NbCurves;ic++)
				{
					ListOfGeometries.Append(ListOfCurves[ic]);
				}
					
				// Gets the bouding box of the geometry of the Limiting Curve 
				GetBoundingBox(ListOfGeometries,GuidingCurvesBBox);

				pGuidingCurves->Release();
				pGuidingCurves = NULL;
			}
		}	
		
		// Creates toolpath
		CATIMfgToolPathFactory * pToolPathFactory = NULL;
		RC = iContainer->QueryInterface(IID_CATIMfgToolPathFactory, (void**) &pToolPathFactory);
		if (SUCCEEDED(RC))  
		{    
			// Creation of tool path element
			CATIMfgCompoundTraject_var spCompoundTraject = pToolPathFactory->CreateMfgCompoundTraject();
			if (!!spCompoundTraject)
			{
				// Initialization of tool path from activity (copy of feedrates, spindle, ....)
				CATBaseUnknown_var spBaseActivity = pActivity;
				spCompoundTraject->Init(spBaseActivity);

				// Initialization of tool axis on tool path
				CATMathVector MachToolAxis(0,0,1);
				CATIMfgToolPathConstantToolAxis_var spToolAxis = pToolPathFactory->CreateMfgToolPathConstantToolAxis(MachToolAxis);
				spCompoundTraject->SetToolAxis(spToolAxis);

				// Description of motions
				CATIMfgToolPathComponents * pToolPathComponents = NULL;;
				RC = spCompoundTraject->QueryInterface(IID_CATIMfgToolPathComponents, (void**) &pToolPathComponents);
				if (SUCCEEDED(RC))  
				{
					CATIMfgTPMultipleMotion_var spMultipleMotion = pToolPathFactory->CreateMfgTPMultipleMotion();
					if (!! spMultipleMotion)
					{
						pToolPathComponents->AddElement(spMultipleMotion);

						// Creates the tool path describing the bounding box of the Part Body
						AddTPMotion(spMultipleMotion,PartsBBox);

						// Creates the tool path describing the bounding box of the Check
						AddTPMotion(spMultipleMotion,ChecksBBox);

						// Creates the tool path describing the bounding box of the Guiding Curve
						AddTPMotion(spMultipleMotion,GuidingCurvesBBox);
					}

					// Saves tool path in model
					CATIMfgTPSaveData * pSaveData = NULL;
					RC = pToolPathComponents->QueryInterface(IID_CATIMfgTPSaveData, (void**) &pSaveData);
					if (SUCCEEDED(RC))  
					{
						pSaveData->SaveData();
						pSaveData->Release();
						pSaveData = NULL;
					}

					// Returned TP
					oTP = pToolPathComponents;

					pToolPathComponents->Release();
				}
			}
			pToolPathFactory->Release();
		}
		pActivity->Release();
	}
	return RC;
}

//========================================================================
// GetBoundingBox
//========================================================================
HRESULT CAAESmiUserOperationWithMATPComputation::GetBoundingBox(
						CATLISTP(CATGeometry) iGeometricElements,
						CATMathBox & oBBox)
{	
	HRESULT RC = S_OK;	
		
	// Infinite bounding box
	double ModelSize = 1e5;
	CATMathBox ModelBox(-ModelSize,ModelSize,-ModelSize,ModelSize,-ModelSize,ModelSize);
	
	// Computes bounding box
	int NbGeometries = iGeometricElements.Size();
	for (int ig=1;ig<=NbGeometries;ig++)
	{
		CATGeometry * pGeometry = iGeometricElements[ig];
		if (pGeometry)
		{
			CATMathBox BoundingBox;
			pGeometry->GetBoundingBox(BoundingBox);

			// We don't add infinite bounding box
			if (ModelBox.IsContaining(BoundingBox))
			{
				oBBox.AddInside(BoundingBox);
			}
		}
	}
	return RC;
}

//========================================================================
// AddTPMotion
//========================================================================
HRESULT CAAESmiUserOperationWithMATPComputation::AddTPMotion(
							const CATIMfgTPMultipleMotion_var & iMultipleMotion,
							const CATMathBox & iBBox )
{	
	HRESULT RC = S_OK;	

	// Test if iBBox is not empty
	if (iBBox.IsEmpty() == FALSE)
	{						
		// Retrieves the extremities of iBBox
		double Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
		iBBox.GetLimits(Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);

        // Inflates the box by adding the value of CAAOffset parameter on each direction	
		CATIMfgActivityParameters * pActivityParameters = NULL;
		RC = QueryInterface(IID_CATIMfgActivityParameters, (void**) &pActivityParameters);
		if (SUCCEEDED(RC))
		{
			double Offset = 0.;
            pActivityParameters->GetValue ("CAAOffset", Offset);
            if (Offset > 0.)
            {
                Xmin = Xmin - Offset;
                Ymin = Ymin - Offset;
                Zmin = Zmin - Offset;
                Xmax = Xmax + Offset;
                Ymax = Ymax + Offset;
                Zmax = Zmax + Offset;
            }

			pActivityParameters->Release();
			pActivityParameters = NULL;
		}


		// Draws the bounding box
		CATListOfDouble X,Y,Z;

		X.Append(Xmin); Y.Append(Ymin); Z.Append(Zmin);
		X.Append(Xmin); Y.Append(Ymax); Z.Append(Zmin);	
		X.Append(Xmax); Y.Append(Ymax); Z.Append(Zmin);
		X.Append(Xmax); Y.Append(Ymin); Z.Append(Zmin);
		X.Append(Xmin); Y.Append(Ymin); Z.Append(Zmin);
						
		X.Append(Xmin); Y.Append(Ymin); Z.Append(Zmax);
		
		X.Append(Xmin); Y.Append(Ymax); Z.Append(Zmax);	
		X.Append(Xmin); Y.Append(Ymax); Z.Append(Zmin);	
		X.Append(Xmin); Y.Append(Ymax); Z.Append(Zmax);	
		
		X.Append(Xmax); Y.Append(Ymax); Z.Append(Zmax);
		X.Append(Xmax); Y.Append(Ymax); Z.Append(Zmin);
		X.Append(Xmax); Y.Append(Ymax); Z.Append(Zmax);

		X.Append(Xmax); Y.Append(Ymin); Z.Append(Zmax);
		X.Append(Xmax); Y.Append(Ymin); Z.Append(Zmin);
		X.Append(Xmax); Y.Append(Ymin); Z.Append(Zmax);

		X.Append(Xmin); Y.Append(Ymin); Z.Append(Zmax);
						 												
		// Adds tool path
		iMultipleMotion->AddPolyline(TPMachiningTraject,TPMachiningFeedrate,X,Y,Z);
	}
	return RC;
}
