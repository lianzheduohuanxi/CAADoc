/**
* @quickReview CRE 02:11:08
*/

//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators:
//                   Create a VARIABLE RADIUS/CHORDAL FILLET 
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Main steps      : 1- Specify the radii along the edge to be filleted
//                   2- Fill in the list of radii
//                   3- Create the CATDynEdgeFilletRibbon
//                   4- Create and run the CATDynfillet operator 
//=============================================================================

#include <iostream.h>

// GeometricObjects
#include "CATCGMContainerMngt.h"       // Geometry factory management

// NewTopologicalObjects
#include "CATCell.h"                   // Cell definition
#include "ListPOfCATEdge.h"            // List of edges
#include "CATListOfCATCells.h"         // List of cells
//#include "CATBoundedCellsIterator.h"   // To iterate over a range of cells all bounding a
//                                       given cell
// TopologicalOperators
#include "CATDynFillet.h"              // Filleting operator 
#include "CATDynFilletRibbon.h"        // One fillet operation
#include "CATDynFilletRadius.h"        // Radius definition

// -----------------------------------------------------------------------------
int  CAATopVariableFillets(CATGeoFactory * iFactory,
                           CATTopData * iTopData, 
                           CATBody * iBody,
                           int iRadiusType)
{
    
    cout << "Variable radius fillet" << endl ;
    int rc = 0;
    if ((NULL==iFactory) || (NULL==iTopData) || (NULL==iBody))
    {
        cout << "NUlL handler" << endl;
        return (1);
    } 
    else
    {
        // ---------------------------------------------------------
        // 1 - Create the fillet
        // ---------------------------------------------------------
        //
        // (a) - Specify the radii along listCells[2]
        //  
        CATLISTP(CATCell) listCells;
        iBody ->GetAllCells(listCells,1 );
        
        double ratio0(0.0);
        CATDynFilletRadius * pRadius0 = new CATDynFilletRadius(4.,  // radius value
            listCells[2],  
            &ratio0,  
            NULL);  
        if (NULL==pRadius0)
        {
            ::CATCloseCGMContainer(iFactory); 
            return (1);
        }
        double ratio1(0.25);
        CATDynFilletRadius * pRadius1 = new CATDynFilletRadius(0.2,  // radius value
            listCells[2],  
            &ratio1,  
            NULL);  
        if (NULL==pRadius1)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        double ratio2(0.5);
        CATDynFilletRadius * pRadius2 = new CATDynFilletRadius(6, // radius value
            listCells[2],  
            &ratio2,  
            NULL);  
        if (NULL==pRadius2)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        double ratio3(1);
        CATDynFilletRadius * pRadius3 = new CATDynFilletRadius(0.5, // radius value
            listCells[2],  
            &ratio3,  
            NULL);  
        if (NULL==pRadius3)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        //     
        // (b) - Create the list of radii
        //
        CATLISTP(CATDynFilletRadius) listRadius;		
        listRadius.Append(pRadius0);
        listRadius.Append(pRadius1);
        listRadius.Append(pRadius2);
        listRadius.Append(pRadius3);
         
        // (c) - Create the CATDynEdgeFilletRibbon
        //
        CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(NULL, listRadius);
        if (NULL==pRibbon)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }

        // (d) -Specify the type of radius: radius type or chordal type
        // In case of radius type the input value to CATDynFilletRadius is taken as radius of the fillet
        // In case of chord type the input value to CATDynFilletRadius is taken as chord length of the fillet
        CATFilletRadiusType filletRadiusType = CATFilletRadiusDefaultType;
        if(1 == iRadiusType)
          filletRadiusType = CATFilletRadiusChordLengthType;

        pRibbon ->SetFilletRadiusType(filletRadiusType);

        // (e) - Specify that the resulting body contains the created fillets connected to the
        //       faces they are relying on
        pRibbon->SetSegmentationMode(CATDynTrim);

        // (f) - Create the operator
        //
        CATDynFillet * pFilletOp = CATCreateDynFillet(iFactory,iTopData,iBody);
        if (NULL==pFilletOp)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }
        //
        // (g) - Append the ribbon
        pFilletOp ->Append(pRibbon);
        
        // (h) - Run the operator
        pFilletOp ->Run(); 
        
        // (i) - Get the resulting body
        CATBody * piFillet = NULL;
        piFillet = pFilletOp->GetResult();
        
        if (NULL==piFillet)
        {
            ::CATCloseCGMContainer(iFactory);
            return (1);
        }

        // (j) - Delete the operator
        delete pFilletOp;
        pFilletOp = NULL;
        
        if (NULL != pRadius0) delete pRadius0;
        pRadius0 = NULL;
        if (NULL != pRadius1) delete pRadius1;
        pRadius1 = NULL;
        if (NULL != pRadius2) delete pRadius2;
        pRadius2 = NULL;
        if (NULL != pRadius3) delete pRadius3;
        pRadius3 = NULL;
        if (NULL != pRibbon) delete pRibbon;
        pRibbon = NULL;
        
        return rc;
    }
}






