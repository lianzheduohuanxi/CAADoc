// COPYRIGHT DASSAULT SYSTEMES 2000
//===========================================================================
// CAAEMmrCombinedCurveAdn.cpp
// Provide implementation to interface
//      CATIShapeDesignWorkshopAddin
//
//===========================================================================

// Local Framework
#include "CAAEMmrCombinedCurveAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h> // needed to manage workshop access
#include "CATCommandHeader.h"  // needed to instanciate the header

// Creates the CAAEMmrCombinedCurveAdnHeader command header class
MacDeclareHeader(CAAEMmrCombinedCurveAdnHeader);  

// To declare that the class 
// is a DataExtension of (late type) CAAMmrCombinedCurveAddin

CATImplementClass ( CAAEMmrCombinedCurveAdn  ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CAAMmrCombinedCurveAddin );

// 
// To declare that CAAMmrCombinedCurveAddin implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary :
//
// CAAMmrCombinedCurveAddin      CATIShapeDesignWorkshopAddin    libCAAMmrCombinedCurveAddIn

#include <TIE_CATIShapeDesignWorkshopAddin.h> // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(CAAEMmrCombinedCurveAdn);

//-----------------------------------------------------------------------------
// CAAEMmrCombinedCurveAdn : constructor
//-----------------------------------------------------------------------------

CAAEMmrCombinedCurveAdn::CAAEMmrCombinedCurveAdn()
{
    
}

//-----------------------------------------------------------------------------
// CAAEMmrCombinedCurveAdn : destructor
//-----------------------------------------------------------------------------

CAAEMmrCombinedCurveAdn::~CAAEMmrCombinedCurveAdn()
{
    
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAEMmrCombinedCurveAdn::CreateCommands()
{
    
    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button
    
    new CAAEMmrCombinedCurveAdnHeader( "CAAMmrCombinedCurveHdr"  ,
                                      "CAAMmrCombinedCurveUI"    ,
                                      "CAAMmrCombCrvPanelStCmd" ,
                                      (void *)NULL              );
     // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button
    new CAAEMmrCombinedCurveAdnHeader("CAAMmrCCDataExtensionHdr"   ,
                                      "CAAMmrCCDataExtensionUI"    ,
                                      "CAAMmrCCDataExtensionStCmd" ,
                                      (void *)NULL              );
}


//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAEMmrCombinedCurveAdn::CreateToolbars()
{
    
    // CombinedCurve Toolbar 
    NewAccess        ( CATCmdContainer  , pCombinedCurveWkb , CAAMmrCombinedCurveTlb );
    
    NewAccess        ( CATCmdStarter    , pCombinedCurve    , CAAMmrCombinedCurveStr );
    SetAccessCommand ( pCombinedCurve    , "CAAMmrCombinedCurveHdr" );
    SetAccessChild   ( pCombinedCurveWkb , pCombinedCurve  );
      
    // MmrCCataExtension Toolbar 
    NewAccess        ( CATCmdStarter    , pDataExtension     , CAAMmrCCDataExtensionStr );
    SetAccessCommand ( pDataExtension    , "CAAMmrCCDataExtensionHdr" );
    SetAccessNext    ( pCombinedCurve  , pDataExtension  );
    
    AddToolbarView   ( pCombinedCurveWkb  , -1 , Right ); // Unvisible toolbar 

    return pCombinedCurveWkb;
    
}

