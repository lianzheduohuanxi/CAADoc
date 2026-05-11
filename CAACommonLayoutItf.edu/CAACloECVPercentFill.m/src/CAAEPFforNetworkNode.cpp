// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// CAAEPFforNetworkNode.cpp
// Provide implementation to interface
//
//  Test the program:
//  -------------------
//  Build the use case and try out scenarios by inserting the below 
//  workpackages Hanger / Raceway under the PRC 
//
//  Sample model to test the implementation code: 
//  -------------------
//  This sample uses the following products as workpackages:
//  Hanger Model : MWY1_ECV.CATProduct, 
// 								 LWY1_ECV.CATProduct, 
//								 EQT1_ECV.CATProduct, 
//								 EQT2_ECV.CATProduct, 
//								 ELD1_ECV.CATProduct 
//
//  Raceway model: WKP_Raceway.CATProduct,
//								 WKP_EQT_RWY.CATProduct,
//								 WKP_ELD_RWY.CATProduct 
//
//
//====================================================================
//
#include "CAAEPFforNetworkNode.h"
#include "iostream.h"
#include "CATMathConstant.h"
 
CATImplementClass(CAAEPFforNetworkNode,
                  DataExtension,
                  CATBaseUnknown,
                  CATEcwLightNwkNodeForPercentFill );

//-----------------------------------------------------------------------------
// CAAEPFforNetworkNode : constructor
//-----------------------------------------------------------------------------
CAAEPFforNetworkNode::CAAEPFforNetworkNode():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEPFforNetworkNode : destructor
//-----------------------------------------------------------------------------
CAAEPFforNetworkNode::~CAAEPFforNetworkNode()
{
}
 
// Link the implementation to its interface
// TIE or TIEchain definitions
#include "TIE_CATIEcvPercentFill.h"

TIE_CATIEcvPercentFill( CAAEPFforNetworkNode);

//Methods implementation
//-----------------------------------------------------------------------------
// Implements CATIEcvPercentFill::ComputePercentFillValue
//-----------------------------------------------------------------------------
HRESULT CAAEPFforNetworkNode::ComputePercentFillValue ( 
                CATEcwLightNwkNodeForPercentFill         *  pNwkNode ,
							  CATEcwLightNwkArcForPercentFill          *  pNwkArc ,
							  CATLISTP(CATEcwLightNwkArcForPercentFill)   pListOfCATEcwLightNwkArcForPercentFill ,
							  CATEcwLightNwkCableForPercentFill        *  pNwkCable ,
							  CATLISTP(CATEcwLightNwkCableForPercentFill) pListOfCATEcwLightNwkCableForPercentFill ,
							  int                                         iRoutingMode ,
							  int                                         iRouteToolsOptionStackCableOption ,
							  int                                         iPFToBeSetOnNode ,
							  double                                   &  odComputedPercentFill )
{
	HRESULT RC = S_OK;
	cout<<"-->> CAAEPFforNetworkNode::ComputePercentFillValue:"<<endl;

	CATUnicodeString uType_NodeOrArc;
	CATUnicodeString uName_NodeOrArc;
	double           dNodeArea          = 0.0;
	double           dNodeExistingPFill = 0.0;
	CATLISTP(CATEcwLightNwkArcForPercentFill) pListOfCAANwkArc;

	if(pNwkNode) pNwkNode->GetNodeData(uName_NodeOrArc, uType_NodeOrArc, dNodeArea, dNodeExistingPFill, pListOfCAANwkArc);

	// Gather CurrentCable and ExistedRoutedCables related information
	double dCurCableOD           = 0.0;
	double dCurrCableArea        = 0.0;
	double dTotalCommonCableSize = 0.0;
	double dTotalCableArea       = 0.0;
	CATListOfDouble iLRoutedCablesDiameter;

	if(pNwkCable) pNwkCable->GetCableData( dCurCableOD );

	int iSzOfCables = pListOfCATEcwLightNwkCableForPercentFill.Size();
	for(int iCableFromList=1; iCableFromList<=iSzOfCables; iCableFromList++ )
	{
		double dCableOD=0.0;

		CATEcwLightNwkCableForPercentFill *pNwkCableForPFill = 
			pListOfCATEcwLightNwkCableForPercentFill[iCableFromList];

		if(pNwkCableForPFill)
		{
			pNwkCableForPFill->GetCableData( dCableOD );
			dTotalCommonCableSize = dTotalCommonCableSize+dCableOD;
			iLRoutedCablesDiameter.Append(dCableOD);
			if ( dCableOD > 0.0 ) dTotalCableArea = dTotalCableArea + dCableOD;
		}
	}

	if(pNwkNode && !pNwkArc) // Hanger Case
	{
		double dTotalCableArea = 0.0;
		for (int iLCable=1;iLCable<=iLRoutedCablesDiameter.Size(); iLCable++)
		{
			double dCableOD = 0.0;
			dCableOD = iLRoutedCablesDiameter[iLCable];
			if ( dCableOD > 0.0 )
			{
				//For cable penetration, use the area of the cable to compute the percent fill
				double cableArea = dCableOD;
				if ( uType_NodeOrArc.SearchSubString("CATHgrWaterTightCblPn") ==0 || uType_NodeOrArc.SearchSubString("CATHgrNonWaterTightCblPn") ==0)
				{
					cableArea = CATPI * (dCableOD/2) * (dCableOD/2);//the area is in mm square
					if ( uType_NodeOrArc.SearchSubString("CATHgrWaterTightCblPn") ==0 )
					{
						int iBlockWidth = 0;
						// The hardcoded values below are in mm and reflected from 
						// \intel_a\startup\EquipmentAndSystems\Electrical\DesignRules\CableMCTSize.txt
						// Block width is decided on the basis of cable OD
						if(4 < dCableOD && dCableOD < 11.5)
							iBlockWidth = 15;
						else if(11.5 < dCableOD && dCableOD < 16.5)
							iBlockWidth = 20;
						else if(16.5 < dCableOD && dCableOD < 26.5)
							iBlockWidth = 30;
						else if(26.5 < dCableOD && dCableOD < 35.5)
							iBlockWidth = 40;
						else if(35.5 < dCableOD && dCableOD < 55.5)
							iBlockWidth = 60;
						else if(55.5 < dCableOD && dCableOD < 74.5)
							iBlockWidth = 90;
						else if(74.5 < dCableOD && dCableOD < 99.5)
							iBlockWidth = 120;
						cableArea = iBlockWidth * iBlockWidth ; //in mm square
					}
				}
				dTotalCableArea = dTotalCableArea + cableArea;
			}
		}
		double fPercentFill = 0.0;
		double fArea        = dNodeArea;
		if ( fArea > 0.0 ) fPercentFill = (dTotalCableArea * 100) / fArea;

		if( uType_NodeOrArc.SearchSubString("CATHgr") == 0 )
		{
			if ( fArea > 0.0 )
			{
				double totalUsedArea = 0.0;
				dCurrCableArea = dCurCableOD;

				if ( iRoutingMode == 1 ) // pNwkCable is being added to the Node/Arc
					totalUsedArea = dTotalCableArea + dCurrCableArea;
				else if ( iRoutingMode == 2 ) // pNwkCable is being deleted from the Node/Arc
					totalUsedArea = dTotalCableArea - dCurrCableArea;

				if ( totalUsedArea < 0.00000001 ) totalUsedArea = 0.0;

				if ( iRoutingMode == 3 || iRoutingMode == 4 ) // load data or Validate is in progress
					totalUsedArea = dTotalCableArea;

				fPercentFill = totalUsedArea / fArea * 100.0;
			}
			else //the node has zero size
			{
				if ( iRoutingMode == 1 ) // pNwkCable is being added to the Node/Arc
					fPercentFill = 100.0;
				if ( iRoutingMode == 2 ) // pNwkCable is being deleted from the Node/Arc
					fPercentFill = 0.0;
			}
			odComputedPercentFill = fPercentFill;
		}
		if(fPercentFill) 
			odComputedPercentFill = fPercentFill;
		else 
			odComputedPercentFill = dNodeExistingPFill;
	}

	if(pNwkNode && pNwkArc) // Racweway Case for Rwy Node
	{
		if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
		{
			dTotalCommonCableSize=0.0;
			for(int iRCD=1;iRCD<=iLRoutedCablesDiameter.Size();iRCD++)
			{
				double dTmpDia = iLRoutedCablesDiameter[iRCD];
				dTmpDia = dTmpDia * dTmpDia * CATPI / 4000000;
				dTotalCommonCableSize += dTmpDia;
			}
		}

		double  dArcArea          = 0.0;
		double  dArcWidth         = 0.0;
		double  dArcExistingPFill = 0.0;

		if(!iPFToBeSetOnNode)
		{
			pNwkArc->GetArcData(uName_NodeOrArc, uType_NodeOrArc, dArcArea, dArcWidth, dArcExistingPFill);

			double dPercentFill = dArcExistingPFill;
			double dUseArcArea=0.0;

			if ( dTotalCommonCableSize > 0.0 )
			{
				if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
					dUseArcArea = dArcArea; 
				else //non-stacking
					dUseArcArea = dArcWidth; 

				dArcArea = dUseArcArea;

				if ( dArcArea > 0.0 ) 
				{
					if(2 == iRoutingMode) // Cable being deleted
					{
						double dTotCommonCableArea = dTotalCommonCableSize;
						if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
							dTotCommonCableArea = dTotCommonCableArea - (CATPI * dCurCableOD * dCurCableOD / 4000000);
					  else
						 dTotCommonCableArea = dTotCommonCableArea - dCurCableOD;

						dPercentFill = dTotCommonCableArea / dArcArea * 100.0;
					}
					dPercentFill = dTotalCommonCableSize / dArcArea * 100.0; 
				}
				else
					dPercentFill = 100.0;
			}
			else 
			{
				if((1 == iRoutingMode) || (3 == iRoutingMode)) dPercentFill = 0.0;
			}
			odComputedPercentFill = dPercentFill;
		}
		else // i.e. if(iPFToBeSetOnNode)
		{
			// get list of arcs on the node, get their PF, use the MAX PF to be set on the Node
			double dMaxPFfromListOfArcsConnectedToNode = 0.0;
			double dMinPFfromListOfArcsConnectedToNode = 100.0;

			int iSzOfNodeArcs = pListOfCAANwkArc.Size();
			for( int iArcFromList=1; iArcFromList<=iSzOfNodeArcs; iArcFromList++ )
			{
				CATEcwLightNwkArcForPercentFill *pNwkArcForPFill_loop = pListOfCAANwkArc[iArcFromList];
				if(pNwkArcForPFill_loop)
				{
					CATUnicodeString uNameOfArc_loop, uArcType_loop;
					double dArcArea_loop = 0.0, dArcWidth_loop = 0.0; 
					double dArcExistingPFill_loop = 0.0;

					pNwkArcForPFill_loop->GetArcData ( uNameOfArc_loop, uArcType_loop, dArcArea_loop, 
						dArcWidth_loop, dArcExistingPFill_loop );

					if( dMaxPFfromListOfArcsConnectedToNode < dArcExistingPFill_loop )
						dMaxPFfromListOfArcsConnectedToNode = dArcExistingPFill_loop;

					if( dMinPFfromListOfArcsConnectedToNode > dArcExistingPFill_loop )
						dMinPFfromListOfArcsConnectedToNode = dArcExistingPFill_loop;
				}
			} 

			if(2 == iRoutingMode)
			{
				if(dMinPFfromListOfArcsConnectedToNode > dMaxPFfromListOfArcsConnectedToNode)
					dMinPFfromListOfArcsConnectedToNode = dMaxPFfromListOfArcsConnectedToNode;

				odComputedPercentFill = dMinPFfromListOfArcsConnectedToNode;
			}
			else
			{
				odComputedPercentFill = dMaxPFfromListOfArcsConnectedToNode;
			}
		}
	}	
	cout<<"<<-- CAAEPFforNetworkNode::ComputePercentFillValue: is "<< odComputedPercentFill << endl;
	return RC;
}
