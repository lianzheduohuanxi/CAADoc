
/**
* @fullreview AJM AJD 04:02:06 
*/

//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: 
//                   CREATE A SHAPE FILLET WITH EXTERNAL LAW
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//                   2- Invalid input
//
// Programming     : 1- Retrieve the domain and init faces to be filleted
//       steps       2- Create the fillet.
//=============================================================================

#include <iostream.h>

// GeometricObjects
#include "CATCGMContainerMngt.h"       // Geometry factory management

// NewTopologicalObjects
#include "CATCell.h"                   // Cell definition
#include "CATWire.h"
#include "CATCompositeLaw.h"

#include "ListPOfCATEdge.h"            // List of edges
#include "CATListOfCATCells.h"         // List of cells

// TopologicalOperators
#include "CATDynFillet.h"              // Filleting operator 
#include "CATDynFilletRibbon.h"        // One fillet operation

// -----------------------------------------------------------------
int CAATopVariableShapeFillets(CATGeoFactory * iFactory, 
                       CATTopData * iTopData,
                       CATBody * iRightBody,
                       CATBody * iLeftBody,
                       CATBody * iSpine,
                       CATCompositeLaw * iExtRadiusLaw)
{
    
    cout << "Shape fillet with External Law" << endl ;
    
    if ((NULL==iFactory)    ||
        (NULL==iTopData)    ||
        (NULL==iRightBody)  ||
        (NULL==iLeftBody)   ||
        (NULL==iSpine)      ||
        (NULL==iExtRadiusLaw)
       )
    { 
        cout << "Null pointer in CAATopShapeFillets" << endl;
        return 1;
    } 
    
    // ---------------------------------------------------------
    // 1 - Retrieve the domain and init faces to be filleted 
    //     Methodology:
    //     - Retrieve first domain (should be shell) from each of body
    //     - Retrieve all the cells (faces) from domain to use as Inits
    //     - Repeat for the two rolling support bodies and one spine body
    // ---------------------------------------------------------------------------
    
    CATDomain *pDomain[2] = {0};
    CATLISTP(CATFace) listFaces[2];

    for (int iBody = 0; iBody < 2; ++iBody)
    {

      CATBody *pBody = iRightBody;
      if( 1 == iBody)
        pBody = iLeftBody;

      int nbDomains = pBody->GetNbDomains();
      if( nbDomains < 1)
        return 2;
    
      pDomain[iBody] = pBody->GetDomain( 1);
      if( NULL == pDomain[iBody])
         return 1;
    
      // is it a shell ?
      if( 2 != pDomain[iBody]->GetLowDimension())
        return 2;
    
      CATLISTP(CATCell) listCells;
      pDomain[iBody]->GetAllCells(listCells,2 );
      for( int i=1; i <= listCells.Size(); ++i)
        listFaces[iBody].Append( (CATFace*)listCells[i]);
    }
    
    // ----------------------------------------------------------------------------
    // 2 -  Create the fillet 
    // -----------------------------------------------------------------------------
    //
    // (a) - Set the orientation to take into account for the ribbon computation
    //

    CATOrientation iRightOrientation = CATOrientationPositive;
    CATOrientation iLeftOrientation  = CATOrientationPositive;
    
    //
    // (b) - Constructs a tri-tangent ribbon
    //
    CATDynFaceFaceFilletRibbon * pRibbon = new 	CATDynFaceFaceFilletRibbon( 
                                                            iRightBody, pDomain[0], iRightOrientation, listFaces[0],
                                                            iLeftBody, pDomain[1], iLeftOrientation, listFaces[1],
                                                            iSpine, NULL, iExtRadiusLaw
                                                            );
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
    CATDynFillet * pFilletOp1 = CATCreateDynFillet(iFactory,iTopData,NULL);
    if (NULL==pFilletOp1)
    {
        ::CATCloseCGMContainer(iFactory);
        return (1);
    }
    //
    // (e) - Append the ribbon
    pFilletOp1 ->Append(pRibbon);
    
    // (f) - Run the operator
    pFilletOp1 ->Run(); 
    
    // (g) - Get the resulting body
    CATBody * piFillet1 = pFilletOp1->GetResult();
    
    if (NULL==piFillet1)
    {
        ::CATCloseCGMContainer(iFactory);
        return (1);
    }
    
    // (h) - Delete the operator
    delete pFilletOp1;
    pFilletOp1 = NULL;
    
    delete pRibbon;
    pRibbon = NULL;
    
    return 0;
    
}







