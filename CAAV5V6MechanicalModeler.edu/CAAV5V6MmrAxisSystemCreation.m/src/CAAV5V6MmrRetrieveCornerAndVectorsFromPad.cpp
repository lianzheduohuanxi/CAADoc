// COPYRIGHT DASSAULT SYSTEMES 2012

//============================================================================================
//
// Mission        : Global function to retrieve a corner and the three edges coming from
//                  this corner of a Pad. These four cells are featurized. 
//
//  
// Note : CAAV5V6MmrRetrieveCornerAndVectorsFromPad is the V6 migration of CAAMmrCornerAndVectorsFromPad. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.

// Steps :
//    1-    Checks the arguments
//    2-    Retrieves the MechanicalTool which aggregates the Pad
//    3-    Retrieves the CATBody associated with the MechanicalTool
//    4-    Retrieves the first corner and three edges coming from this corner 
//    5-    Creates the BRep Object
//    6-    Featurizes the BRep Object
//
//============================================================================================

#include "CAAV5V6MmrRetrieveCornerAndVectorsFromPad.h" 

// CATMecModUseItf Framework
#include "CATIMmiUseBRepAccess.h"
#include "CATIMmiUseFeaturize.h"
#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiUseBRepDecodeServices.h"
#include "CATMmiUseServicesFactory.h"
#include "CATIMmiUseMfBRep.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// MecModInterfaces Framework in V5
// CATMecModLiveUseIt Framework in V6
#include "CATIBodyRequest.h"

// GMModelInterfaces Framework
#include "CATCell.h"
#include "CATBody.h"
#include "CATVertex.h"
#include "CATEdge.h"
#include "CATListOfCATCells.h"

//System Framework
#include "CATBoolean.h"
#include "iostream.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h" 


HRESULT CAAV5V6MmrRetrieveCornerAndVectorsFromPad(CATBaseUnknown *  iInputPad, 
                                              CATBaseUnknown ** oVectorX,
				                              CATBaseUnknown ** oVectorY)
{
//
// 1- Checks the arguments
//
  if ( NULL == iInputPad ) return E_FAIL ;

  HRESULT rc = S_OK ;

  if ( NULL == oVectorX ) return E_FAIL ;
  if ( NULL == oVectorY ) return E_FAIL ;

  *oVectorX = NULL ;
  *oVectorY = NULL ;

//
// 2- Retrieves the MechanicalTool which aggregates the Pad
//
  CATIMmiMechanicalFeature * pMecModOnPad = NULL ;
  HRESULT hr = iInputPad->QueryInterface(IID_CATIMmiMechanicalFeature,(void**) &pMecModOnPad);
  
  if ( SUCCEEDED(hr) )
  {
     CATIMmiMechanicalFeature_var pFatherPad  ;
     pMecModOnPad->GetMechanicalFather(pFatherPad);

     pMecModOnPad->Release();
     pMecModOnPad = NULL ;

     if ( pFatherPad != NULL_var )
     {
         
        CATIBodyRequest * pBodyRequestOnTool = NULL ;
        hr = pFatherPad->QueryInterface(IID_CATIBodyRequest,(void**) &pBodyRequestOnTool);


        CATBaseUnknown_var FeatureResult ;
        if ( SUCCEEDED(hr) )
        {
             
           CATLISTV(CATBaseUnknown_var) ListR ;
           pBodyRequestOnTool->GetResults("",ListR);
           
           if ( ListR.Size() >= 1 )
           {
              FeatureResult = ListR[1] ;
           }
           pBodyRequestOnTool->Release();
           pBodyRequestOnTool = NULL ;
        }

//
// 3- Retrieves the CATBody associated with the MechanicalTool
//
        CATBody_var BodyTool ;
        if ( NULL_var != FeatureResult )
        {
           CATIMmiUseGeometricalElement * pGeomEltOnResult = NULL ;
           hr = FeatureResult->QueryInterface(IID_CATIMmiUseGeometricalElement,(void**) &pGeomEltOnResult);
           if ( SUCCEEDED(hr) )
           { 
              pGeomEltOnResult->GetBodyResult(BodyTool);

              pGeomEltOnResult->Release();
              pGeomEltOnResult = NULL ;
           }
        }
//
// 4- Retrieves the first corner and three edges coming from this corner 
//
        if ( NULL_var != BodyTool )
        {
            CATLISTP(CATCell) ListVertex ;
            BodyTool->GetAllCells(ListVertex,0) ;
            CATCell * pCornerCell = NULL ;
            CATLISTP(CATCell) ListEdgeCorner;
            if ( ListVertex.Size() >= 1 )
            {
                pCornerCell = ListVertex[1] ;
                
                CATLISTP(CATCell) ListEdge ;
                BodyTool->GetAllCells(ListEdge,1) ;
                CATBoolean found = FALSE;
                int NbEdges = 0 ;
                int i = 1 ;
                CATEdge *pCurrentEdge = NULL ;
                while (( NbEdges != 3) && ( i <= ListEdge.Size()) )
                {
                    pCurrentEdge = (CATEdge*) ListEdge[i] ;
                    if ( NULL != pCurrentEdge )
                    {
                       CATVertex *pStart = NULL ;
                       CATVertex *pEnd   = NULL ;
                       pCurrentEdge->GetVertices(&pStart,&pEnd);
                       if ( (pStart == pCornerCell) || (pEnd == pCornerCell) )
                       {
                          NbEdges ++ ;
                          ListEdgeCorner.Append(pCurrentEdge);
                       }
                    }
                    i++ ;
                }
            }
//
// 5- Creates the BRep objects 
//
            if ( ListEdgeCorner.Size() == 3) 
            {
                CATIMmiUseBRepDecodeServices_var spBRepDecodeServices;
				CATMmiUseServicesFactory::CreateBRepDecodeServices(spBRepDecodeServices);

                CATIMmiUseGeometricalElement_var FeatureResultGeomElt = FeatureResult ;
                CATCell_var spEdgeCell = ListEdgeCorner[1] ;

                CATIMmiUseBRepAccess_var BRepEdge1 ;
				spBRepDecodeServices->DecodeCellInGeomElt(BRepEdge1, spEdgeCell,FeatureResultGeomElt);

                spEdgeCell = ListEdgeCorner[2] ;
                CATIMmiUseBRepAccess_var BRepEdge2 ;
				spBRepDecodeServices->DecodeCellInGeomElt(BRepEdge2,spEdgeCell,FeatureResultGeomElt);

//
// 6- Featurizes the BRep Object
//
                if ( NULL_var != BRepEdge1 )
                {
                   CATIMmiUseFeaturize_var FCell = BRepEdge1 ;
                   if ( NULL_var != FCell )
                   {
                      CATIMmiUseMfBRep_var MFEdge1Cell ;
					  FCell->Featurize(MFEdge1Cell);
                      MFEdge1Cell->QueryInterface(IID_CATBaseUnknown,
                                                 (void**) &(*oVectorX));
                   }
                }
               if ( NULL_var != BRepEdge2 )
                {
                   CATIMmiUseFeaturize_var FCell = BRepEdge2 ;
                   if ( NULL_var != FCell )
                   {
                      CATIMmiUseMfBRep_var MFEdge2Cell ;
					  FCell->Featurize(MFEdge2Cell);
                      MFEdge2Cell->QueryInterface(IID_CATBaseUnknown,
                                                 (void**) &(*oVectorY));
                   }
                }
            }
        }
     }
 
  }

  if ( (*oVectorX == NULL) || (*oVectorY == NULL) )
     rc = E_FAIL ;
  else 
	 rc = S_OK ;

  return rc ;
}

