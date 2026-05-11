// COPYRIGHT DASSAULT SYSTEMES 2012
//==================================================================================================
// CAAEV5V6ExtMmrMultiMeasureAdn.cpp
// Provide implementation to interface CATIShapeDesignWorkshopAddin
//
// Note :  CAAEV5V6ExtMmrMultiMeasureAdn is the same use case as CAAEMmrMultiMeasureAndMeasureSetAdn. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//==================================================================================================

#include "CATIAV5Level.h"

// Local Framework
#include "CAAEV5V6ExtMmrMultiMeasureAdn.h"

// AfrFoundation Framework 
#include "CATCreateWorkshop.h" // needed to manage workshop access

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
#include "CATAfrCommandHeader.h"  // needed to instanciate the header

#else
//============================================== 
// V5 only
//==============================================
#include "CATCommandHeader.h"  // needed to instanciate the header

// Creates the CAAEV5V6ExtMmrMultiMeasureAdnHeader command header class
MacDeclareHeader(CAAEV5V6ExtMmrMultiMeasureAdnHeader);  

#endif

// To declare that the class 
// is a DataExtension of (late type) CAAMmrCombinedCurveAddin

CATImplementClass ( CAAEV5V6ExtMmrMultiMeasureAdn  ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CAAV5V6ExtMmrMultiMeasureAddin );

// 
// To declare that CAAV5V6ExtMmrMultiMeasureAdin implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary :
//
// CAAV5V6ExtMmrMultiMeasureAddin      CATIShapeDesignWorkshopAddin    libCAAV5V6ExtMmrMultiMeasureAddIn

#include <TIE_CATIShapeDesignWorkshopAddin.h> // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(CAAEV5V6ExtMmrMultiMeasureAdn);

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureAdn : constructor
//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrMultiMeasureAdn::CAAEV5V6ExtMmrMultiMeasureAdn()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureAdn : destructor
//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrMultiMeasureAdn::~CAAEV5V6ExtMmrMultiMeasureAdn()
{}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAEV5V6ExtMmrMultiMeasureAdn::CreateCommands()
{
    
  // Instantiation of the Command header 
  // commands are always available and are represented by a push button

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6ExtMmrMeasureSetHdr",   
                                                "CAAV5V6ExtMmrMultiMeasureUI",                        
                                                "CAAV5V6ExtMmrMeasureSetStCmd",                    
   							                              (void *)NULL,                                  
							                                "CAAEV5V6ExtMmrMultiMeasureAdnHeader",		          
							                                CATFrmAvailable);

	CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6ExtMmrMultiMeasureHdr",   
                                              "CAAV5V6ExtMmrMultiMeasureUI",                        
                                              "CAAV5V6ExtMmrMultiMeasureStCmd",                    
   							                              (void *)NULL,                                  
							                                "CAAEV5V6ExtMmrMultiMeasureAdnHeader",		          
							                                CATFrmAvailable);
#else 
//============================================== 
// V5 only
//==============================================
	 
    new CAAEV5V6ExtMmrMultiMeasureAdnHeader( "CAAV5V6ExtMmrMultiMeasureHdr"  ,
                                         "CAAV5V6ExtMmrMultiMeasureUI"    ,
                                         "CAAV5V6ExtMmrMultiMeasureStCmd" ,
                                         (void *)NULL              );
	new CAAEV5V6ExtMmrMultiMeasureAdnHeader( "CAAV5V6ExtMmrMeasureSetHdr"  ,
                                         "CAAV5V6ExtMmrMultiMeasureUI"    ,
                                         "CAAV5V6ExtMmrMeasureSetStCmd" ,
                                         (void *)NULL              );
	
#endif
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAEV5V6ExtMmrMultiMeasureAdn::CreateToolbars()
{
    
     // MultiMeasure Toolbar
    NewAccess        ( CATCmdContainer  , pMeasureSetWkb , CAAV5V6ExtMmrMultiMeasureTlb );
    
	// CAAV5V6ExtMmrMeasureSet command
    NewAccess        ( CATCmdStarter    , pMeasureSet    , CAAV5V6ExtMmrMeasureSetStr );
    SetAccessCommand ( pMeasureSet      , "CAAV5V6ExtMmrMeasureSetHdr" );
    SetAccessChild   ( pMeasureSetWkb   , pMeasureSet  );
    
    // CAAV5V6ExtMmrMultiMeasure command
    NewAccess        ( CATCmdStarter    , pMultiMeasure ,CAAV5V6ExtMmrMultiMeasureStr );
    SetAccessCommand ( pMultiMeasure    , "CAAV5V6ExtMmrMultiMeasureHdr" );
    SetAccessNext    ( pMeasureSet      , pMultiMeasure);
    
    AddToolbarView   ( pMeasureSetWkb , -1 , Right ); // Unvisible toolbar 

    return pMeasureSetWkb;
}

