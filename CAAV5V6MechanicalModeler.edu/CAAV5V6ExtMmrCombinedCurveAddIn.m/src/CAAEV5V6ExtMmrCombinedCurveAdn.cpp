// COPYRIGHT DASSAULT SYSTEMES 2012
//===========================================================================
// CAAEV5V6ExtMmrCombinedCurveAdn.cpp
// Provide implementation to interface
//      CATIShapeDesignWorkshopAddin
//
// Note : CAAEV5V6ExtMmrCombinedCurveAdn is the same use case as CAAEMmrCombinedCurveAdn. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//===========================================================================

#include "CATIAV5Level.h"

// Local CAAMechanicalModelerExtend.edu framework  
#include "CAAEV5V6ExtMmrCombinedCurveAdn.h"

// ApplicationFrame Framework in V5
// AfrFoundation Framework in V6  
#include "CATCreateWorkshop.h"    

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// AfrFoundaton Framework
#include "CATAfrCommandHeader.h"  

#else
//============================================== 
// V5 only
//============================================== 

// ApplicationFrame Framework
#include "CATCommandHeader.h"

MacDeclareHeader(CAAEV5V6ExtMmrCombinedCurveAdnHeader);

#endif


// To declare that the class 
// is a DataExtension of (late type) CAAV5V6ExtMmrCombinedCurveAddin

CATImplementClass(CAAEV5V6ExtMmrCombinedCurveAdn, DataExtension, CATBaseUnknown, CAAV5V6ExtMmrCombinedCurveAddin);

// 
// To declare that CAAV5V6ExtMmrCombinedCurveAddin implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary :
//
// CAAV5V6ExtMmrCombinedCurveAddin      CATIShapeDesignWorkshopAddin    libCAAV5V6ExtMmrCombinedCurveAddIn

#include "TIE_CATIShapeDesignWorkshopAddin.h" // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(CAAEV5V6ExtMmrCombinedCurveAdn);

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurveAdn : constructor
//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrCombinedCurveAdn::CAAEV5V6ExtMmrCombinedCurveAdn()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurveAdn : destructor
//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrCombinedCurveAdn::~CAAEV5V6ExtMmrCombinedCurveAdn()
{}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAEV5V6ExtMmrCombinedCurveAdn::CreateCommands()
{   
  // Instantiation of the Command header 
  // commands are always available and are represented by a push button
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6ExtMmrCombinedCurveHdr",   
                                                "CAAV5V6ExtMmrCombinedCurveUI",                        
                                                "CAAV5V6ExtMmrCombCrvPanelStCmd",                    
   							                     (void *)NULL,                                  
							                    "CAAEV5V6ExtMmrCombinedCurveAdnHeader",		          
							                     CATFrmAvailable);

  // Instantiation of the Command header 
  // commands are always available and are represented by a push button
 
	CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6ExtMmrCCDataExtensionHdr",   
                                              "CAAV5V6ExtMmrCCDataExtensionUI",                        
                                              "CAAV5V6ExtMmrCCDataExtensionStCmd",                    
   							                              (void *)NULL,                                  
							                                "CAAEV5V6ExtMmrCombinedCurveAdnHeader",		          
							                                CATFrmAvailable);
#else
//============================================== 
// V5 only
//============================================== 
	
    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button
    
    new CAAEV5V6ExtMmrCombinedCurveAdnHeader( "CAAV5V6ExtMmrCombinedCurveHdr"  ,
                                              "CAAV5V6ExtMmrCombinedCurveUI"    ,
                                              "CAAV5V6ExtMmrCombCrvPanelStCmd" ,
                                              (void *)NULL              );

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    new CAAEV5V6ExtMmrCombinedCurveAdnHeader("CAAV5V6ExtMmrCCDataExtensionHdr"   ,
                                             "CAAV5V6ExtMmrCCDataExtensionUI"    ,
                                             "CAAV5V6ExtMmrCCDataExtensionStCmd" ,
                                             (void *)NULL              );
#endif
}


//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAEV5V6ExtMmrCombinedCurveAdn::CreateToolbars()
{
  // CombinedCurve Toolbar 
  NewAccess        ( CATCmdContainer  , pCombinedCurveWkb , CAAV5V6ExtMmrCombinedCurveTlb );
  NewAccess        ( CATCmdStarter    , pCombinedCurve    , CAAV5V6ExtMmrCombinedCurveStr );
  SetAccessCommand ( pCombinedCurve    , "CAAV5V6ExtMmrCombinedCurveHdr" );
  SetAccessChild   ( pCombinedCurveWkb , pCombinedCurve  );
      
  // MmrCCataExtension Toolbar 
  NewAccess        ( CATCmdStarter    , pDataExtension     , CAAV5V6ExtMmrCCDataExtensionStr );
  SetAccessCommand ( pDataExtension    , "CAAV5V6ExtMmrCCDataExtensionHdr" );
  SetAccessNext    ( pCombinedCurve  , pDataExtension  );
    
  AddToolbarView   ( pCombinedCurveWkb  , -1 , Right ); // Unvisible toolbar 

  return pCombinedCurveWkb;  
}

