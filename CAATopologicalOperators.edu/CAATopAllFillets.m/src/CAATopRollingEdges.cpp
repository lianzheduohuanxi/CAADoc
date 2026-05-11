/**
* @quickReview CRE 04:03:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: 
//                   CREATE A FILLET WITH ROLLING EDGES
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Programming     : 1- Retrieve the edges to be filleted
//       steps       2- Specify the rolling edges   
//                   3- Create the fillet with rolling edges 
//                    
//=============================================================================

#include <iostream.h>

// GeometricObjects
#include "CATCGMContainerMngt.h"       // Geometry factory management

// NewTopologicalObjects
#include "CATCell.h"                   // Cell definition
#include "CATVertex.h"                 // Vertex definition
#include "ListPOfCATEdge.h"            // List of edges
#include "CATListOfCATCells.h"         // List of cells
#include "CATBoundedCellsIterator.h"   // To iterate over a range of cells all bounding a
                                       // given cell
 
// TopologicalOperators
#include "CATDynFillet.h"              // Filleting operator 
#include "CATDynFilletRibbon.h"        // One fillet operation
#include "CATDynFilletRadius.h"        // Radius definition

// -------------------------------------------------------------------
int CAATopRollingEdges(CATGeoFactory * iFactory, 
                       CATTopData * iTopData,
                       CATBody * iBody)
{
    
    cout << "Fillet with rolling edges" << endl ;
    int rc = 0;
    if ((NULL==iFactory) ||
        (NULL==iTopData) ||
         NULL==iBody)
    { 
        cout << "Null pointer in CAATopRollingEdges" << endl;
        return (1);
    } 
    else
    {
        // ---------------------------------------------------------
        // 1 - Retrieve the edges to be filleted (the edges 
        //     common to the two cubes).
        //     Methodology:
        //     - Search for the only face which is made up of two domains
        //     - Retrieve all the cells of edge type from the internal domain
        // ---------------------------------------------------------------------------
        //
        // (a) - Retrieve the list of faces 
        // 
        CATLISTP(CATCell) listCells;
        iBody ->GetAllCells(listCells,2 );
        int nbCells=listCells.Size();
        
        CATFace * pFace = NULL;
        CATLISTP(CATCell) listCells1;
        CATLISTP(CATCell) listCells0;  // the vertices
        CATDomain * internalDomain = NULL;
        //
        // (b) - Scan the list of faces and search for the one with two domains 
        // 
        int j = 1;
for (;j<=nbCells;j++)
        {
			CATCell * pLocalCell = listCells[j];
            if (pLocalCell && pLocalCell->GetNbDomains() == 2)
            {
                pFace = (CATFace *)pLocalCell;
                for ( int i=1;i<=pLocalCell->GetNbDomains();i++)
                {
                    // Retrieve the internal domain
                    //
                    CATLocation Location = CATLocationUnknown;
                    CATDomain * piDom = pLocalCell->GetDomain(i,&Location);
                    if (Location == CATLocationInner)
                    {
                        // Set the internal domain
                        internalDomain = piDom;
                        // Retrieve the edges of the internal domain
                        piDom ->GetAllCells(listCells1,1 );
                        // Retrieve the vertices of the internal domain
                        piDom ->GetAllCells(listCells0,0 );  
                        cout << "nbCells1" << listCells1.Size() << endl;
                    }
                }  
            }
        }
        //
        // (c) - Create the list of edges to be filleted
        //
        CATLISTP(CATEdge) listEdges;
        for ( j=1;j<=listCells1.Size();j++)
        {
            listEdges.Append((CATEdge *)listCells1[j]);
        }
        // -----------------------------------------------------------------------
        // 2 - Specify the rolling edges  
        //     Methodology:
        //     - retrieve the list of edges
        //       bounded by each vertex of the internal domain
        //     - gather those which do not belong to the internal domain into a list
        // -----------------------------------------------------------------------
        //
        CATLISTP(CATEdge) listRollingEdges;
        // Scan the list of vertices
        for (j=1;j<=listCells0.Size();j++)
        {
            CATVertex * pVertex = (CATVertex*)listCells0[j];
            if (NULL == pVertex) return (1);
            // For each vertex, create a CATBoundedCellsIterator iterator
            CATBoundedCellsIterator * vertexIterator = 
                pVertex -> CreateBoundedCellsIterator(iBody);
            
            if (vertexIterator)
            {
                CATCell *CurrentCell = NULL;
                // Scan the list of edges bounded by the vertex
                while ( CurrentCell = vertexIterator->Next() )
                    // Add the current edge to the "rolling edge list" 
                    // Put aside the edges from the internal domain
                    if ((internalDomain->Owns(CurrentCell) == 0) && CurrentCell->IsATypeOf(CATEdgeType) )
                    {
                        CATEdge * currentEdge = (CATEdge *)CurrentCell;
                        listRollingEdges.Append(currentEdge);
                    }
                    delete vertexIterator;
            }
        }
        
        // ----------------------------------------------------------------------------
        // 3 -  Create the fillet 
        // -----------------------------------------------------------------------------
        //
        // (a) - Define the radius:
        //           only the first argument is to be specified
        //
        double * ratio= NULL;
        CATDynFilletRadius * pRadius = new CATDynFilletRadius(3.,    // radius value
            NULL,  
            ratio,  
            NULL);  
        if (NULL==pRadius)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        // (b) - Specify on what edges the CATDynFilletRadius is to be applied
        //
        CATLISTP(CATDynFilletRadius) listRadius;		
        listRadius.Append(pRadius);		
        CATDynEdgeFilletRibbon * pRibbon = new 	CATDynEdgeFilletRibbon(listEdges, listRadius,
            CATBody::CATEdgePropagAuto,
            listRollingEdges,   // the rolling edges
            CATDynRolling);
        if (NULL==pRibbon)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        // (c) - Specify that the resulting body contains the created fillets connected to the
        // faces they are relying on.
        //
        pRibbon ->SetSegmentationMode(CATDynTrim);
        //
        // (d) - Create the operator
        //
        CATDynFillet * pFilletOp = CATCreateDynFillet(iFactory,iTopData,iBody);
        if (NULL==pFilletOp)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        //
        // (e) - Append the ribbon
        pFilletOp ->Append(pRibbon);
        
        // (f) - Run the operator
        pFilletOp ->Run(); 
        
        // (g) - Get the resulting body
        CATBody * piFillet1 = NULL;
        piFillet1 = pFilletOp->GetResult();
        
        if (NULL==piFillet1)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        
        // (h) - Delete the operator
        delete pFilletOp;
        pFilletOp = NULL;
        
        if (NULL != pRadius) delete pRadius;
        pRadius = NULL;
        if (NULL != pRibbon) delete pRibbon;
        pRibbon = NULL;
        
        return rc;
    }
}






