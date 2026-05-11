// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationTPComputation :
//
// Sample code for : CAA Tool Path Management (sample 5)
//
// Mission         : Customize the "CAA Plunge Operation" Tool Path Computation
//                   
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a CAASmg operation
//                   3- Select geometry
//                   4- Replay the tool path
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct and CAAUserMachiningFeatures.CATfct
//                    in the resources\graphic directory of the runtime view.
//
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationTPComputation.h"
#include "CAAISmiUserMachFeature.h"
 
// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgActivityParameters.h"
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathComponents.h"
#include "CATIMfgToolPathConstantToolAxis.h"
#include "CATIMfgToolPathFactory.h"
#include "CATMfgToolPathDefs.h"
#include "CATIMfgTPSaveData.h"

// Mathematics Interfaces
#include "CATMathPoint.h"
#include "CATMathVector.h"

// Geometric Object Interfaces
#include "CATCurve.h"
#include "CATCrvLimits.h"

// Tessellation Interfaces
#include "CATCurveTessellator.h"

// Tie the implementation to its interface
CATImplementBOA (CATIMfgComputeToolPathCustom, CAAESmiUserOperationTPComputation);
CATImplementClass( CAAESmiUserOperationTPComputation,
                   CacheExtension,
                   CATIMfgComputeToolPathCustom,
                   CAASmgOperation );
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationTPComputation::CAAESmiUserOperationTPComputation()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationTPComputation::~CAAESmiUserOperationTPComputation()
{
}
 
//========================================================================
// ComputeToolPath
//========================================================================
HRESULT CAAESmiUserOperationTPComputation::ComputeToolPath (const CATIContainer_var& iContainer, CATIMfgToolPath_var& oTP)
{
	HRESULT RC = S_OK;

	// Check input argument
	if (NULL_var == iContainer) return E_FAIL;

	// Retrieves Activity	
	CATIMfgActivity * pActivity = NULL;
	RC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
	if (SUCCEEDED(RC))
	{
		// Reads Activity Parameters 	
		double Step = 0.;
		double ToolAngle = 0.;
		double ApproachDistance = 0.;
		CATIMfgActivityParameters * pActivityParameters = NULL;
		RC = QueryInterface(IID_CATIMfgActivityParameters, (void**) &pActivityParameters);
		if (SUCCEEDED(RC))
		{
			// Step
			pActivityParameters->GetValue ("CAAStep", Step);

			// ToolAngle
			pActivityParameters->GetValue ("CAAToolAngle", ToolAngle);
						
			// Approach distance
			pActivityParameters->GetValue ("CAAApproachDistance", ApproachDistance);

			pActivityParameters->Release();
			pActivityParameters = NULL;
		}
			
		// Retrieves Machining Feature from Activity
		CATBaseUnknown_var spBaseFeature = pActivity->GetFeature();

		// Retrieves Geometry from Machining Feature
		CATLISTP(CATGeometry) ListOfGeometry;
		CAAISmiUserMachFeature * pUserMachFeature = NULL;
		RC = spBaseFeature->QueryInterface(IID_CAAISmiUserMachFeature, (void**) &pUserMachFeature);
		if (SUCCEEDED(RC))
		{
			pUserMachFeature->GetGuides(ListOfGeometry);
			pUserMachFeature->Release();
			pUserMachFeature = NULL;
		}
	
		// Computes discretized points on Geometry	
		CATLISTV(CATMathPoint) ListOfPoints;
		if (ListOfGeometry.Size() > 0)
		{
			// Only the first one is computed
			CATGeometry * pGeometry = ListOfGeometry[1];
			if (pGeometry && pGeometry->IsATypeOf(CATCurveType))
			{
				CATCurve * pCurve = (CATCurve *) pGeometry;
				RC = TessellateGeometry(pCurve,Step,ListOfPoints);
			}
		}
		else
		{
			pActivity->Release();
			return E_FAIL;
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

						int NbOfPoints = ListOfPoints.Size();
						for (int i=1; i<=NbOfPoints; i++)
						{				
							CATListOfDouble X,Y,Z;
							CATListOfDouble X2,Y2,Z2;

							// Machining Traject							
							X.Append(ListOfPoints[i].GetX() + tan(ToolAngle*CATPI/180.) * ApproachDistance);
							Y.Append(ListOfPoints[i].GetY() + tan(ToolAngle*CATPI/180.) * ApproachDistance);
							Z.Append(ListOfPoints[i].GetZ() + ApproachDistance);

							X.Append(ListOfPoints[i].GetX());
							Y.Append(ListOfPoints[i].GetY());
							Z.Append(ListOfPoints[i].GetZ());

							spMultipleMotion->AddPolyline(TPMachiningTraject,TPMachiningFeedrate,X,Y,Z);
							
							// Linking traject in rapid feedrate
							X2.Append(ListOfPoints[i].GetX());
							Y2.Append(ListOfPoints[i].GetY());
							Z2.Append(ListOfPoints[i].GetZ());

							X2.Append(ListOfPoints[i].GetX());
							Y2.Append(ListOfPoints[i].GetY());
							Z2.Append(ListOfPoints[i].GetZ() + ApproachDistance);
							
							if (i != NbOfPoints)
							{
								X2.Append(ListOfPoints[i+1].GetX() + tan(ToolAngle*CATPI/180.) * ApproachDistance);
								Y2.Append(ListOfPoints[i+1].GetY() + tan(ToolAngle*CATPI/180.) * ApproachDistance);
								Z2.Append(ListOfPoints[i+1].GetZ() + ApproachDistance);
							}
							
							spMultipleMotion->AddPolyline(TPLinkingTraject,TPRapidFeedrate,X2,Y2,Z2);
						}						  
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
// TessellateGeometry
//========================================================================
HRESULT CAAESmiUserOperationTPComputation::TessellateGeometry(CATCurve * const iCurve, const double iStep,
														      CATLISTV(CATMathPoint) & oPointsList)
{	
	HRESULT RC = E_FAIL;	
	if (NULL != iCurve)
	{
		// Creates a tessellation operator
		CATCurveTessellator * pCurveTess = new CATCurveTessellator(1e6);
        if (NULL!=pCurveTess)
        {				  
			RC = S_OK;
			
			// Defines a finite step 
			pCurveTess->SetStep(iStep);   
            
			// Adds the curve to tessellate 
			CATCrvLimits Limits;
            iCurve->GetLimits(Limits);

			pCurveTess->AddCurve(iCurve, Limits);
            pCurveTess -> Run();
              
            // Retrieves the tessellation results
            CATLONG32 NumOfPoints;
            double * aPoints = NULL;
            pCurveTess-> GetCurve (iCurve, NumOfPoints, &aPoints);

            int Index = 0;
		    for (int i=0;i<NumOfPoints;i++)
			{
				CATMathPoint Point(aPoints[Index],aPoints[Index+1],aPoints[Index+2]);
				Index = Index +3;
				oPointsList.Append(Point);
			}
				
			// The deletion of the operator leads to the deletion of aPoints
			delete pCurveTess;
            pCurveTess=NULL;
		} 
	}
	return RC;
}
