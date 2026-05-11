/**
* @quickReview AJM 04:02:20
*/

//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators:
//                   CREATE FILLETS 
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Create the geometric factory and software configuration
//                   2- Create a solid cuboid
//                   3- Create another solid cuboid
//                   4- Create a boolean union 
//                   5- Create fillets of different types
//                      (a) - constant radius fillet  
//                      (b) - fillet with rolling edges
//                      (c) - variable radius fillet
//                      (d) - constant chord length fillet
//                      (e) - variable chord length fillet
//                   6- Create 3 skins for tri tangent fillet
//                   7- Create tri tangent fillet
//                   8- Create 2 skins, a spine and a radius law for shape fillet
//                   9- Create shape fillet w/ external radius law
//                   10- Release  the configuration
//                   11- Write the model
//
// How to run it   : CAATopFilletsMain           // to run whithout storing the NCGM file
//                   CAATopFilletsMain  file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Localinterfaces
#include "CAATopConstantFillets.h"
#include "CAATopVariableFillets.h"
#include "CAATopRollingEdges.h"
#include "CAATopTriTangentFillets.h"
#include "CAATopVariableShapeFillets.h"

// Mathematics
#include "CATMathPoint.h"              // mathematical point
#include "CATMathVector.h"              // mathematical vector
#include "CATMathPlane.h"              // mathematical plane
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management
#include "CATSurLimits.h"              // surface limits
#include "CATPlane.h"                    // Plane object

// TopologicalObjects
#include "CATBody.h"                   // body

// TopologicalOperators
#include "CATSolidCuboid.h"            // Box primitive
#include "CATDynBoolean.h"             // Boolean operator
#include "CATTopSkin.h"                // skin operator

// BasicTopologicalOpe
#include "CATTopPointOperator.h"         // To create point bodies
#include "CATTopLineOperator.h"          // To create line bodies   
#include "CATTopSplineOperator.h"        // To create spline bodies


//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(2<iArgc) return (1);
    
    char *pfileName = NULL;
    int  toStore = 0;
    if (2==iArgc) 
    {
        toStore = 1; 
        pfileName = iArgv[1];
    }
    
    //---------------------------------------------------------------------------
    // 1 - Create the factory and software configuration 
    //---------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = CATCreateCGMContainer() ;
    if (NULL == piGeomFactory) return (1);
    
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    
    // -------------------------------------------------------------------------
    // 2 - Create a first solid cuboid
    // -------------------------------------------------------------------------
    //
    CATMathPoint vO1(0, 0., 0.),  vOI1(50., 0., 0), vOJ1(0., 30., 0.),  vOK1(0., 0., 15.);
    //
    // (a) - Create the operator
    //
    CATSolidCuboid *pCuboidOp1 = ::CATCreateSolidCuboid( piGeomFactory, 
        &topdata, 
        vO1, 
        vOI1, 
        vOJ1, 
        vOK1);
    if (NULL==pCuboidOp1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    //
    // (b) - Retrieve the result
    //
    CATBody *piCuboidBody1=NULL;
    piCuboidBody1 = pCuboidOp1->GetResult();
    if (NULL==piCuboidBody1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    //
    // (c) - Delete the operator
    //
    delete pCuboidOp1;
    pCuboidOp1 = NULL;
    
    // -------------------------------------------------------------------------
    // 3 - Create a second solid cuboid
    // -------------------------------------------------------------------------
    //
    CATMathPoint vO2(7, 7., 15.),  vOI2(42., 7., 15), vOJ2(7., 24., 15.),  vOK2(7., 7., 25.);
    //
    // (a) - Create the operator
    //
    CATSolidCuboid *pCuboidOp2 = ::CATCreateSolidCuboid( piGeomFactory, 
        &topdata, 
        vO2, 
        vOI2, 
        vOJ2, 
        vOK2);
    if (NULL==pCuboidOp2)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    //
    // (b) - Retrieve the result
    //
    CATBody *piCuboidBody2=NULL;
    piCuboidBody2 = pCuboidOp2->GetResult();
    if (NULL==piCuboidBody2)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    //
    // (c) - Delete the operator
    //
    delete pCuboidOp2;
    pCuboidOp2 = NULL;
    
    // -------------------------------------------------------------------------
    // 4 - Create a boolean union
    // -------------------------------------------------------------------------
    //
    // (a) - Create the operator
    //
    CATDynBoolean * pBoolOpe =::CATCreateDynBoolean(piGeomFactory, &topdata,CATBoolUnion,
        piCuboidBody1,
        piCuboidBody2);
    if (NULL==pBoolOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    // (b) - Run the operator
    //
    pBoolOpe->Run();
    //
    // (c) - Retrieve the result
    //
    CATBody *piBoolBody=NULL;
    piBoolBody = pBoolOpe->GetResult();
    if (NULL==piBoolBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    //
    // (d) - Delete the operator
    //
    delete pBoolOpe;
    pBoolOpe = NULL;
    
    piGeomFactory->Remove(piCuboidBody1,CATICGMContainer::RemoveDependancies );
    piGeomFactory->Remove(piCuboidBody2,CATICGMContainer::RemoveDependancies );
    // -------------------------------------------------------------------------
    // 5 - Create fillets of different types
    // -------------------------------------------------------------------------
    //
    // (a) - Create a constant radius fillet
    //
    rc = CAATopConstantFillets(piGeomFactory, &topdata, piBoolBody);
    
    // (b) - Create a fillet with rolling edges
    //
    rc = CAATopRollingEdges(piGeomFactory, &topdata, piBoolBody);
    
    // (c) - Create a variable radius fillet
    //
    rc = CAATopVariableFillets(piGeomFactory, &topdata, piBoolBody);

    // (d) - Create a constant chord fillet
    //
    rc = CAATopConstantFillets(piGeomFactory, &topdata, piBoolBody,1);

   // (e) - Create a variable chord fillet
    //
    rc = CAATopVariableFillets(piGeomFactory, &topdata, piBoolBody,1);


    piGeomFactory->Remove(piBoolBody,CATICGMContainer::RemoveDependancies );
      
    // --------------------------------------------------------------------------
    // 6 - Create 3 skins for tri tangent fillet
    //     - define a plane
    //     - define a limits of plane to be used for face
    //     - create a TopSkin operator to create skin
    //     - repeat for remaining 2 skins
    // --------------------------------------------------------------------------

    CATMathPlane iMathPlane1( CATMathPoint(5, 0, -5), CATMathVector( 1, 0, 0), CATMathVector( 0, 1, 0));
    CATPlane *piPlane1 = piGeomFactory->CreatePlane( iMathPlane1);
    
    if( NULL == piPlane1)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    CATSurParam surParamLow1;
    piPlane1->GetParam( CATMathPoint( 2, -3, -5), surParamLow1);
    
    CATSurParam surParamHigh1;
    piPlane1->GetParam( CATMathPoint( 7, 3, -5), surParamHigh1);
    
    CATSurLimits faceLimits1( surParamLow1, surParamHigh1);
    
    CATTopSkin *pSkinOp1 = CATCreateTopSkin( piGeomFactory, &topdata, piPlane1, &faceLimits1);
    if( NULL == pSkinOp1)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    pSkinOp1->Run();
    
    CATBody *piRemoveBody = pSkinOp1->GetResult();
    if (NULL==piRemoveBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    delete pSkinOp1;
    pSkinOp1 = NULL;

    CATMathPlane iMathPlane2( CATMathPoint(), CATMathVector( 0, 0, 1), CATMathVector( 0, -1, 0));
    CATPlane *piPlane2 = piGeomFactory->CreatePlane( iMathPlane2);

    if( NULL == piPlane2)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    CATSurParam surParamLow2;
    piPlane2->GetParam( CATMathPoint( 0, 3, -3), surParamLow2);
    
    CATSurParam surParamHigh2;
    piPlane2->GetParam( CATMathPoint( 0, -3, 3), surParamHigh2);
    
    CATSurLimits faceLimits2( surParamLow2, surParamHigh2);
    
    CATTopSkin *pSkinOp2 = CATCreateTopSkin( piGeomFactory, &topdata, piPlane2, &faceLimits2);
    if( NULL == pSkinOp2)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    pSkinOp2->Run();
    
    CATBody *piLeftBody = pSkinOp2->GetResult();
    if (NULL==piLeftBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    delete pSkinOp2;
    pSkinOp2 = NULL;

    CATMathPlane iMathPlane3( CATMathPoint( 10, 0, 0), CATMathVector( 0, 0, 1), CATMathVector( 0, 1, 0));
    CATPlane *piPlane3 = piGeomFactory->CreatePlane( iMathPlane3);
    
    if( NULL == piPlane3)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    CATSurParam surParamLow3;
    piPlane3->GetParam( CATMathPoint( 10, -3, -3), surParamLow3);
    
    CATSurParam surParamHigh3;
    piPlane3->GetParam( CATMathPoint( 10, 3, 3), surParamHigh3);
    
    CATSurLimits faceLimits3( surParamLow3, surParamHigh3);
    
    CATTopSkin *pSkinOp3 = CATCreateTopSkin( piGeomFactory, &topdata, piPlane3, &faceLimits3);
    if( NULL == pSkinOp3)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    pSkinOp3->Run();
    
    CATBody *piRightBody = pSkinOp3->GetResult();
    if (NULL==piRightBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    delete pSkinOp3;
    pSkinOp3 = NULL;

    // --------------------------------------------------------------------------
    // 7 - Create tri tangent fillet
    // --------------------------------------------------------------------------

    rc = CAATopTriTangentFillets(piGeomFactory, &topdata, piRightBody, piLeftBody, piRemoveBody);

    piGeomFactory->Remove(piRightBody,CATICGMContainer::RemoveDependancies );

    piGeomFactory->Remove(piLeftBody,CATICGMContainer::RemoveDependancies );

    piGeomFactory->Remove(piRemoveBody,CATICGMContainer::RemoveDependancies );

    // --------------------------------------------------------------------------
    // 8 - Create 2 skins for Shape Fillet w/ Ext Radius Law
    //     - define a plane
    //     - define a limits of plane to be used for face
    //     - create a TopSkin operator to create skin (step a)
    //     - repeat for remaining skin (step b)
    //   - Create a wire body for spine (step c)
    //   - Create a constant radius law.(step d)
    // --------------------------------------------------------------------------

    // ---------- (a) First Skin ----------------
    CATMathPlane iMathPlane4(CATMathPoint(0, 0, 0), CATMathVector(0, 0, 1), CATMathVector(1, 0, 0));
    CATPlane *piPlane4 = piGeomFactory->CreatePlane(iMathPlane4);
    
    if (NULL == piPlane4)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    CATSurParam surParamLow4;
    piPlane4->GetParam(CATMathPoint(0, 0, 0), surParamLow4);
    
    CATSurParam surParamHigh4;
    piPlane4->GetParam(CATMathPoint(10, 0, 10), surParamHigh4);
    
    CATSurLimits faceLimits4(surParamLow4, surParamHigh4);

    CATTopSkin *pSkinOp4 = CATCreateTopSkin(piGeomFactory, &topdata, piPlane4, &faceLimits4);
    if (NULL == pSkinOp4)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    pSkinOp4->Run();
    
    CATBody *piRightBodySF = pSkinOp4->GetResult();
    if (NULL==piRightBodySF)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    delete pSkinOp4;
    pSkinOp4 = NULL;

    // ---------- (b) Second Skin ----------------
    CATMathPlane iMathPlane5(CATMathPoint(0, 0, 0), CATMathVector(0, 1, 0), CATMathVector(0, 0, 1));
    CATPlane *piPlane5 = piGeomFactory->CreatePlane(iMathPlane5);
    
    if (NULL == piPlane5)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    CATSurParam surParamLow5;
    piPlane5->GetParam(CATMathPoint(0, 0, 0), surParamLow5);
    
    CATSurParam surParamHigh5;
    piPlane5->GetParam(CATMathPoint(0, 10, 10), surParamHigh5);
    
    CATSurLimits faceLimits5(surParamLow5, surParamHigh5);

    CATTopSkin *pSkinOp5 = CATCreateTopSkin(piGeomFactory, &topdata, piPlane5, &faceLimits5);
    if (NULL == pSkinOp5)
    {
      ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    pSkinOp5->Run();
    
    CATBody *piLeftBodySF = pSkinOp5->GetResult();
    if (NULL==piLeftBodySF)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    delete pSkinOp5;
    pSkinOp5 = NULL;

    // ---------- (c) Wire body for spine ----------------
    const int nbpts = 2;
    CATBody ** aPoints = new CATBody * [nbpts];
    if (NULL==aPoints)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    aPoints[0] = CATCreateTopPointXYZ(piGeomFactory, &topdata, 10., 10., -1.);
    aPoints[1] = CATCreateTopPointXYZ(piGeomFactory, &topdata, 10., 10., 11.);

    if (NULL==aPoints[0] || NULL==aPoints[1])
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Direct creation of a spine body
    CATBody * piSpineBody = ::CATCreateTopLineFromPoints(piGeomFactory,
                                                         &topdata,
                                                         aPoints[0],
                                                         aPoints[1]);
    if (NULL==piSpineBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    for (int i = 0; i < nbpts; i++)
    {
      if (aPoints[i])
        piGeomFactory->Remove(aPoints[i], CATICGMContainer::RemoveDependancies);
    }
    if (aPoints) delete[] aPoints;

    // ---------- (d) Constant law ----------------

    double tmin = 0.0, tmax = 1.0, radius = 2.5;
    CATCompositeLaw * piExtLaw = (CATCompositeLaw*) piGeomFactory->CreateConstantLaw(
                                                                      tmin, tmax,
                                                                      radius);
    if (NULL==piExtLaw)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // --------------------------------------------------------------------------
    // 9 - Create shape fillet with external radius law
    // --------------------------------------------------------------------------

    rc = CAATopVariableShapeFillets(piGeomFactory,
                            &topdata,
                            piRightBodySF,
                            piLeftBodySF,
                            piSpineBody,
                            piExtLaw);

    piGeomFactory->Remove(piRightBodySF, CATICGMContainer::RemoveDependancies);

    piGeomFactory->Remove(piLeftBodySF,  CATICGMContainer::RemoveDependancies);

    piGeomFactory->Remove(piSpineBody,   CATICGMContainer::RemoveDependancies);

    // --------------------------------------------------------------------------
    // 10 - Release  the configuration
    // --------------------------------------------------------------------------
    pConfig->Release();
    
    //---------------------------------------------------------------------------
    // 11- Write the model
    //---------------------------------------------------------------------------
    if(1==toStore)
    {
        cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pfileName, ios::binary ) ;
#else
        ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    //
    // Close the container
    //
    ::CATCloseCGMContainer(piGeomFactory);
    return (rc);
}

