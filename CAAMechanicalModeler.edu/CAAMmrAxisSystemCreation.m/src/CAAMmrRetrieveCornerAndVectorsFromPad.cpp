// COPYRIGHT DASSAULT SYSTEMES 2001

//============================================================================================
// Use Case  for   : Mechanical Modeler
//
// Abstract        : Global function to retrieve a corner and the three edges coming from
//                   this corner of a Pad. These four cells are featurized. 
//
//                  
// Steps :
//    1-    Checks the arguments
//    2-    Retrieves the MechanicalTool which aggregates the Pad
//    3-    Retrieves the CATBody associated with the MechanicalTool
//    4-    Retrieves the first corner and three edges coming from this corner 
//    5-    Creates the BRep Object
//    6-    Featurizes the BRep Object
//
//============================================================================================

//MecModInterfaces Framework
#include "CATIPrtContainer.h"
#include "CATIBRepAccess.h"
#include "CATIFeaturize.h"

//MechanicalModeler Framework
#include "CATIBodyRequest.h"
#include "CATIGeometricalElement.h"
#include "CATMfBRepDecode.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// NewTopologicalObjects Framework
#include "CATCell.h"
#include "CATBody.h"
#include "CATVertex.h"
#include "CATEdge.h"
#include "CATListOfCATCells.h"

// Local Framework
#include "CAAMmrRetrieveCornerAndVectorsFromPad.h"      // to retrieve a specific element

#include "iostream.h"
#include "CATLISTV_CATBaseUnknown.h" 

// System
#include "CATBaseUnknown.h"
#include "CATBoolean.h"

HRESULT CAAMmrRetrieveCornerAndVectorsFromPad(CATBaseUnknown *  iInputPad, 
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
  CATISpecObject * pSpecObjOnPad = NULL ;
  HRESULT hr = iInputPad->QueryInterface(IID_CATISpecObject,(void**) &pSpecObjOnPad);
  
  if ( SUCCEEDED(hr) )
  {
     CATISpecObject * pFatherPad = NULL ;
     pFatherPad = pSpecObjOnPad->GetFather();

     pSpecObjOnPad->Release();
     pSpecObjOnPad = NULL ;

     if ( pFatherPad != NULL )
     {
         
        CATIBodyRequest * pBodyRequestOnTool = NULL ;
        hr = pFatherPad->QueryInterface(IID_CATIBodyRequest,(void**) &pBodyRequestOnTool);

        pFatherPad->Release();
        pFatherPad = NULL ;

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
           CATIGeometricalElement * pGeomEltOnResult = NULL ;
           hr = FeatureResult->QueryInterface(IID_CATIGeometricalElement,(void**) &pGeomEltOnResult);
           if ( SUCCEEDED(hr) )
           { 
              BodyTool = pGeomEltOnResult->GetBodyResult();

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
                CATIGeometricalElement_var FeatureResultGeomElt = FeatureResult ;
                CATCell_var spEdgeCell = ListEdgeCorner[1] ;
                CATIBRepAccess_var BRepEdge1 = CATBRepDecode(spEdgeCell,FeatureResultGeomElt);
                spEdgeCell = ListEdgeCorner[2] ;
                CATIBRepAccess_var BRepEdge2 = CATBRepDecode(spEdgeCell,FeatureResultGeomElt);

//
// 6- Featurizes the BRep Object
//
                if ( NULL_var != BRepEdge1 )
                {
                   CATIFeaturize_var FCell = BRepEdge1 ;
                   if ( NULL_var != FCell )
                   {
                      CATISpecObject_var MFEdge1Cell = FCell->FeaturizeF();
                      MFEdge1Cell->QueryInterface(IID_CATBaseUnknown,
                                                 (void**) &(*oVectorX));
                   }
                }
               if ( NULL_var != BRepEdge2 )
                {
                   CATIFeaturize_var FCell = BRepEdge2 ;
                   if ( NULL_var != FCell )
                   {
                      CATISpecObject_var MFEdge2Cell = FCell->FeaturizeF();
                      MFEdge2Cell->QueryInterface(IID_CATBaseUnknown,
                                                 (void**) &(*oVectorY));
                   }
                }
            }
        }
     }
 
  }

  if ( (*oVectorX == NULL) || (*oVectorY == NULL) )
  {
      rc = E_FAIL ;
  }else rc = S_OK ;

  return rc ;
}

