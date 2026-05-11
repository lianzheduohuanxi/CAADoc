/**
* @quickReview CRE 04:03:02
*/

//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: 
//                   CREATE A FILLET WITH CONSTANT RADIUS/CHORD
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Programming     : 1- Retrieve the edges to be filleted
//       steps       2- Create the fillet.
//=============================================================================

#include <iostream.h>

// GeometricObjects
#include "CATCGMContainerMngt.h"       // Geometry factory management

// NewTopologicalObjects
#include "CATCell.h"                   // Cell definition
//#include "CATVertex.h"                 // Vertex definition
#include "ListPOfCATEdge.h"            // List of edges
#include "CATListOfCATCells.h"         // List of cells
//#include "CATBoundedCellsIterator.h"   // To iterate over a range of cells all bounding a
                                       // given cell
 
// TopologicalOperators
#include "CATDynFillet.h"              // Filleting operator 
#include "CATDynFilletRibbon.h"        // One fillet operation
#include "CATDynFilletRadius.h"        // Radius definition

// -----------------------------------------------------------------
int CAATopConstantFillets(CATGeoFactory * iFactory, 
                       CATTopData * iTopData,
                       CATBody * iBody,
                       int iRadiusType)
{
    
    cout << "Constant radius fillet" << endl ;
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
        CATDynEdgeFilletRibbon * pRibbon = new 	CATDynEdgeFilletRibbon(listEdges, listRadius);
        if (NULL==pRibbon)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        // (c) -Specify the type of radius: radius type or chordal type
        // In case of radius type the input value to CATDynFilletRadius is taken as radius of the fillet
        // In case of chord type the input value to CATDynFilletRadius is taken as chord length of the fillet
        CATFilletRadiusType filletRadiusType = CATFilletRadiusDefaultType;
        if(1 == iRadiusType)
          filletRadiusType = CATFilletRadiusChordLengthType;

        pRibbon ->SetFilletRadiusType(filletRadiusType);

        // (d) - Specify that the resulting body contains the created fillets connected to the
        // faces they are relying on.
        //
        pRibbon ->SetSegmentationMode(CATDynTrim);
        //
        // (e) - Create the operator
        //
        CATDynFillet * pFilletOp1 = CATCreateDynFillet(iFactory,iTopData,iBody);
        if (NULL==pFilletOp1)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        //
        // (f) - Append the ribbon
        pFilletOp1 ->Append(pRibbon);
        
        // (g) - Run the operator
        pFilletOp1 ->Run(); 
        
        // (h) - Get the resulting body
        CATBody * piFillet1 = NULL;
        piFillet1 = pFilletOp1->GetResult();
        
        if (NULL==piFillet1)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        
        // (i) - Delete the operator
        delete pFilletOp1;
        pFilletOp1 = NULL;
        
        if (NULL != pRadius) delete pRadius;
        pRadius = NULL;
        if (NULL != pRibbon) delete pRibbon;
        pRibbon = NULL;
        
        return rc;
    }
}






