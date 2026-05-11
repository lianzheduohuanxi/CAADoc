// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
//  CAAEPFforNetworkArc.cpp
//
//  Provide implementation to interface CATIEcvPercentFill
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
#include "CAAEPFforNetworkArc.h"
#include "iostream.h"
#include "CATMathConstant.h"

 
CATImplementClass(CAAEPFforNetworkArc,
                  DataExtension,
                  CATBaseUnknown,
                  CATEcwLightNwkArcForPercentFill );
 

//-----------------------------------------------------------------------------
// CAAEPFforNetworkArc : constructor
//-----------------------------------------------------------------------------
CAAEPFforNetworkArc::CAAEPFforNetworkArc():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEPFforNetworkArc : destructor
//-----------------------------------------------------------------------------
CAAEPFforNetworkArc::~CAAEPFforNetworkArc()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIEcvPercentFill.h"
TIE_CATIEcvPercentFill( CAAEPFforNetworkArc);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIEcvPercentFill::ComputePercentFillValue
//-----------------------------------------------------------------------------
HRESULT CAAEPFforNetworkArc::ComputePercentFillValue (
							CATEcwLightNwkNodeForPercentFill *  pNwkNode ,
							CATEcwLightNwkArcForPercentFill *  pNwkArc ,
							CATLISTP(CATEcwLightNwkArcForPercentFill)  pListOfCATEcwLightNwkArcForPercentFill ,
							CATEcwLightNwkCableForPercentFill *  pNwkCable ,
							CATLISTP(CATEcwLightNwkCableForPercentFill)  pListOfCATEcwLightNwkCableForPercentFill ,
							int  iRoutingMode ,
							int  iRouteToolsOptionStackCableOption ,
							int  iPFToBeSetOnNode ,
							double &  odComputedPercentFill )
{
	cout<<"-->> CAAEPFforNetworkArc::ComputePercentFillValue:"<<endl;

	CATUnicodeString uType;
	CATUnicodeString uNameOfNode;
	double dNodeArea=0.0;
	double dNodeExistingPFill=0.0;
	double dCurCableOD=0.0;
	CATLISTP(CATEcwLightNwkArcForPercentFill) pListOfCAANwkArc;
	if(pNwkNode)
	{
		pNwkNode->GetNodeData(uNameOfNode, uType, dNodeArea, dNodeExistingPFill, pListOfCAANwkArc);
	}

	if(pNwkCable)
		pNwkCable->GetCableData( dCurCableOD );

	CATListOfDouble iLRoutedCablesDiameter;
	double dTotalCommonCableSize=0.0;

	int iSzOfCables = pListOfCATEcwLightNwkCableForPercentFill.Size();
	for( int iCableFromList=1; iCableFromList<=iSzOfCables; iCableFromList++)
	{
		double dCableOD=0.0;
		CATEcwLightNwkCableForPercentFill *pNwkCableForPFill = 
			pListOfCATEcwLightNwkCableForPercentFill[iCableFromList];

		if(pNwkCableForPFill)
		{
			pNwkCableForPFill->GetCableData( dCableOD ); 
			dTotalCommonCableSize = dTotalCommonCableSize+dCableOD;

			iLRoutedCablesDiameter.Append(dCableOD);
		}
	}

	if(pNwkNode && pNwkArc) // Raceway case
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
		int bPFillToBeSetOnArc = 0;
		double oCustmrImplComputedPrcntFillValForArc=0.0;
		double oCustmrImplComputedPrcntFillValForRwyNode=0.0;

		CATUnicodeString uArcType;
		CATUnicodeString uNameOfArc;
		double dArcArea=0.0;
		double dArcWidth=0.0;
		double dArcExistingPFill=0.0;

		double oCustmrImplComputedPrcntFillValForNode=0;

		if(pNwkArc && !iPFToBeSetOnNode)
		{
			pNwkArc->GetArcData(uNameOfArc, uArcType,
				dArcArea, dArcWidth, dArcExistingPFill);
		} 
		if(pNwkNode && iPFToBeSetOnNode)
		{
			uNameOfArc = uNameOfNode;
			uArcType = uType;
			dArcArea = dNodeArea;
			dArcWidth = 0.0;
			dArcExistingPFill = dNodeExistingPFill;
		}

		if(!iPFToBeSetOnNode)
		{
			double dPercentFill = dArcExistingPFill;
			double dUseArcArea=0.0;

			if((3 == iRoutingMode) || (1 == iRoutingMode))
			{
				if ( dTotalCommonCableSize > 0.0 ) //Compute the percent fill
				{
					if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
					{
						dUseArcArea = dArcArea;
					}
					else //non-stacking
					{
						dUseArcArea = dArcWidth;
					}
					dArcArea = dUseArcArea;

					if ( dArcArea > 0.0 )
						dPercentFill = dTotalCommonCableSize / dArcArea * 100.0;
					else
						dPercentFill = 100.0;
				}
				else
					dPercentFill = 0.0;
			}
			if(2 == iRoutingMode) 
			{
				if ( dTotalCommonCableSize > 0.0 ) //Compute the percent fill
				{
					// in meter square ;subtract the area of the current cable being deleted             
					if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
						dUseArcArea = dArcArea;
					else //non-stacking     
						dUseArcArea = dArcWidth;

					dArcArea = dUseArcArea;

					if ( dArcArea > 0.0 )
					{
						double dTotCommonCableArea = dTotalCommonCableSize;
						if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
							dTotCommonCableArea = dTotCommonCableArea - (CATPI * dCurCableOD * dCurCableOD / 4000000);
						else
							dTotCommonCableArea = dTotCommonCableArea - dCurCableOD;

						dPercentFill = dTotCommonCableArea / dArcArea * 100.0;
					}
					else
						dPercentFill = 100.0;
				}
			}
			if(4 == iRoutingMode)
			{
				if ( dTotalCommonCableSize > 0.0 ) //Compute the percent fill
				{
					if ( iRouteToolsOptionStackCableOption == 1 ) //stacking cable
					{
						dUseArcArea = dArcArea;
					}
					else //non-stacking
					{
						dUseArcArea = dArcWidth;
					}
					dArcArea = dUseArcArea;

					if ( dArcArea > 0.0 )
						dPercentFill = dTotalCommonCableSize / dArcArea * 100.0;
					else
						dPercentFill = 100.0;
				}
			}
			oCustmrImplComputedPrcntFillValForArc = dPercentFill;
			bPFillToBeSetOnArc=1;
		}
		else // i.e. if(iPFToBeSetOnNode)
		{
			// get list of arcs on the node, get their PF, use the MAX PF to be set on the Node
			double dMaxPFfromListOfArcsConnectedToNode = 0.0;
			double dMinPFfromListOfArcsConnectedToNode = 100.0;
			int iSzOfNodeArcs = pListOfCAANwkArc.Size();

			for( int iArcFromList=1; iArcFromList<=iSzOfNodeArcs; iArcFromList++)
			{
				CATEcwLightNwkArcForPercentFill *pNwkArcForPFill_loop = 
					pListOfCAANwkArc[iArcFromList];

				if(pNwkArcForPFill_loop)
				{
					CATUnicodeString uNameOfArc_loop, uArcType_loop;
					double dArcArea_loop = 0.0, dArcWidth_loop = 0.0; 
					double dArcExistingPFill_loop = 0.0;

					pNwkArcForPFill_loop->GetArcData
						( uNameOfArc_loop, uArcType_loop, dArcArea_loop, 
						dArcWidth_loop, dArcExistingPFill_loop);

					if(dMaxPFfromListOfArcsConnectedToNode<dArcExistingPFill_loop)
						dMaxPFfromListOfArcsConnectedToNode = dArcExistingPFill_loop;

					if(dMinPFfromListOfArcsConnectedToNode>dArcExistingPFill_loop)
						dMinPFfromListOfArcsConnectedToNode = dArcExistingPFill_loop;
				}
			} 

			bPFillToBeSetOnArc=0;

			if(2 == iRoutingMode)
			{
				if(dMinPFfromListOfArcsConnectedToNode>dMaxPFfromListOfArcsConnectedToNode)
					dMinPFfromListOfArcsConnectedToNode = dMaxPFfromListOfArcsConnectedToNode;

				oCustmrImplComputedPrcntFillValForRwyNode = dMinPFfromListOfArcsConnectedToNode;
			}
			else
				oCustmrImplComputedPrcntFillValForRwyNode = dMaxPFfromListOfArcsConnectedToNode;
		}
		if(bPFillToBeSetOnArc)    odComputedPercentFill = oCustmrImplComputedPrcntFillValForArc;
		else                      odComputedPercentFill = oCustmrImplComputedPrcntFillValForRwyNode;

	}
	cout<<"<<-- CAAEPFforNetworkArc::ComputePercentFillValue:"<<endl;

	return S_OK;
}

