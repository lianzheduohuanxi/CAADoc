/**
* @quickReview CRE 03:10:22
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler
// Mission         : Explains how to create a segment sweep with two guide skins( tangency surfaces)
//                   and a spine wire. The created sweep surface is such that the plane of sweep segment is 
//                   normal to spine.
//           
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Main steps        1- Create the sweep operator 
//                   2- Set the desired shell orientations 
//                   3- Set the trim options 
//                   4- Run the operator
//                   5- Get the result bodies
//                   6- Delete the operator     
//
// How to run it   : CAATopSweepSegmentSkinSkin    
//=============================================================================

#include "CAATopSweepSegmentSkinSkin.h"

#include <iostream.h>
#include <iomanip.h>

// Mathematics

// Advanced Mathematics
#include "CATSoftwareConfiguration.h"

// GeometricObjects
#include "CATGeoFactory.h"               // Geometry factory
#include "CATCGMContainerMngt.h"         // Management of the geometry factory

// TopologicalOperators
#include "CATTopSweepSkinSkinSegment.h"

// NewTopologicalObjects
#include "CATBody.h"                     // Body
#include "ListPOfCATBody.h"              // List of bodies

#include "CATCGMJournalList.h"
// Error management
#include "CATError.h"              // errors
#include "CATErrorMacros.h"        // to catch errors 

int CAATopSweepSegmentSkinSkin(CATGeoFactory * iFactory 
                               ,CATTopData * iTopData 
                               ,CATBody * iGuideBody1 
                               ,CATBody * iGuideBody2
                               ,CATBody * iSpineBody 
                               )
{
    //check the input
    if( 0 == iFactory || 0 == iTopData
        || 0 == iGuideBody1 || 0 == iGuideBody2 || 0 == iSpineBody )
    {
        cout << "Bad input for sweep segment skin skin " << endl; 
        return 1;
    }
    
    CATDomain * piDomain = iGuideBody1->GetDomain(1);  
    if( piDomain ? 0 == piDomain->IsATypeOf(CATShellType) : 1 )
    {
        cout << "Bad input for sweep segment skin skin " << endl; 
        return 1;
    }
    
    piDomain = iGuideBody2->GetDomain(1);  
    if( piDomain ? 0 == piDomain->IsATypeOf(CATShellType) : 1 )
    {
        cout << "Bad input for sweep segment skin skin " << endl; 
        return 1;
    }
    
    piDomain = iSpineBody->GetDomain(1);  
    if( piDomain ? 0 == piDomain->IsATypeOf(CATWireType) : 1 )
    {
        cout << "Bad input for sweep segment skin skin " << endl; 
        return 1;
    }
    
    // -----------------------------------------------------------------------------
    // 1- Create the sweep operator 
    // -----------------------------------------------------------------------------
    
    CATTopSweepSkinSkinSegment * SweepTopOp = 
        (CATTopSweepSkinSkinSegment*)CATCreateTopSweepSkinSkinSegment(iFactory, iTopData, iGuideBody1, iGuideBody2, iSpineBody);
    
    if(0 == SweepTopOp )
    {
        cout << "Could not create the CATTopSweepSkinSkinSegment operator " << endl;
        return (1);
    }
    
    // -----------------------------------------------------------------------------
    // 2- Set the desired shell orientations 
    // -----------------------------------------------------------------------------
    int orient1 = -1; //solution desired on opposite side of first shell normal
    int orient2 = 1; //solution desired on same side of second shell normal
    
    SweepTopOp->SetFirstShellOrientation( orient1 );
    SweepTopOp->SetSecondShellOrientation( orient2 );
    
    // -----------------------------------------------------------------------------
    // 3- Set the trim options 
    // -----------------------------------------------------------------------------
    CATDynSegmentationMode trim1 = CATDynTrim; //trim the results with first support
    CATDynSegmentationMode trim2 = CATDynNoTrim; // do not trim the results with second support
    
    SweepTopOp->SetFirstShellModeTrim( trim1 );
    SweepTopOp->SetSecondShellModeTrim( trim2 );
    
    // -----------------------------------------------------------------------------
    // 4- Run the operator
    // -----------------------------------------------------------------------------
    CATTry 
    {  
        SweepTopOp->Run();
        
        
        // -----------------------------------------------------------------------------
        // 5- Get the result bodies
        // -----------------------------------------------------------------------------
        
        SweepTopOp->BeginningResult();
        int firstShellOrient = 0, secondShellOrient = 0, firstCoupledOrient = 0, secondCoupledOrient = 0, index = 0;
        CATSoftwareConfiguration * pConfig = iTopData->GetSoftwareConfiguration();
        
        while (SweepTopOp->NextResult())
        {
            CATCGMJournalList * pTempJournal =  new CATCGMJournalList(pConfig,NULL);//get the journal corresponding to this result
            
            CATBody * pTempBody = SweepTopOp->GetResult(pTempJournal);
            
            //get the signature of the current result
            SweepTopOp->GetResultInformation(firstShellOrient
                ,secondShellOrient
                ,firstCoupledOrient
                ,secondCoupledOrient
                ,index);
            if( pTempJournal )
            {
                delete pTempJournal;
                pTempJournal = 0;
            }
            
        }
    }
    CATCatch(CATError,error)
    {
        cout << error->GetMessageText()<<endl;
        cout << (error->GetNLSMessage()).CastToCharPtr()<<endl;
        return 1;
    }
    
    CATEndTry;
    // -----------------------------------------------------------------------------
    // 6- Delete the operator
    // -----------------------------------------------------------------------------
    
    delete SweepTopOp;
    SweepTopOp = 0;
    
    return 0;
}
