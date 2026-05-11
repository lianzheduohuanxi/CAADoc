// COPYRIGHT DASSAULT SYSTEMES 2000
//===========================================================================
// CAAV5V6EMmrSettingsAddIn.cpp
// Provide implementation to interface
//      CATIShapeDesignWorkshopAddin
//
// Note : CAAV5V6EMmrSettingsAddIn is the same use case as CAAEMmrSettingsAddIn. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//===========================================================================

#include "CATIAV5Level.h"

// Local Framework
#include "CAAV5V6EMmrSettingsAddIn.h"

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
 MacDeclareHeader(CAAV5V6EMmrSettingsAddInHeader); 
#endif


// To declare that the class 
// is a DataExtension of (late type) CAAV5V6MmrSettingsAddIn

CATImplementClass(CAAV5V6EMmrSettingsAddIn, DataExtension, CATBaseUnknown, CAAV5V6MmrSettingsAddIn);

// 
// To declare that CAAV5V6MmrSettingsAddIn implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary :
//
// CAAV5V6MmrSettingsAddIn      CATIShapeDesignWorkshopAddin    libCAAV5V6MmrSettingsAddIn

#include <TIE_CATIShapeDesignWorkshopAddin.h> // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(CAAV5V6EMmrSettingsAddIn);

//-----------------------------------------------------------------------------
// CAAV5V6EMmrSettingsAddIn : constructor
//-----------------------------------------------------------------------------

CAAV5V6EMmrSettingsAddIn::CAAV5V6EMmrSettingsAddIn()
{    
}

//-----------------------------------------------------------------------------
// CAAV5V6EMmrSettingsAddIn : destructor
//-----------------------------------------------------------------------------

CAAV5V6EMmrSettingsAddIn::~CAAV5V6EMmrSettingsAddIn()
{
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAV5V6EMmrSettingsAddIn::CreateCommands()
{
    // Instantiation of the Command header 
    // commands are always available and are represented by a push button

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

	CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6MmrUseCreateDatumModeHdr",   
                               "CAAV5V6MmrUseCreateDatumMode",                        
                               "CAAV5V6MmrDatumWindowCmd",                    
   							   (void *)NULL,                                  
							   "CAAV5V6EMmrSettingsAddInHeader",		          
							   CATFrmAvailable);
#else
//============================================== 
// V5 only
//============================================== 
	
	new CAAV5V6EMmrSettingsAddInHeader( "CAAV5V6MmrUseCreateDatumModeHdr"  ,
                                    "CAAV5V6MmrUseCreateDatumMode"    ,
                                    "CAAV5V6MmrDatumWindowCmd" ,
                                     (void *)NULL              );
#endif
}


//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAV5V6EMmrSettingsAddIn::CreateToolbars()
{
    //----------------------
    // CreateDatumMode Toolbar
    //----------------------
    NewAccess        ( CATCmdContainer  , pCreateDatumModeTlb , CAAV5V6MmrUseCreateDatumModeTlb );
   
    NewAccess        ( CATCmdStarter    , pCreateDatumModeT    , CAAV5V6MmrUseCreateDatumModeStr );
    SetAccessCommand ( pCreateDatumModeT    , "CAAV5V6MmrUseCreateDatumModeHdr" );
    SetAccessChild   ( pCreateDatumModeTlb , pCreateDatumModeT  );
    

   //----------------------
   // CreateDatumMode Menubar 
   //----------------------
	NewAccess(CATCmdContainer,pCreateDatumModeMbr,CAAV5V6MmrUseCreateDatumModeMbr);

   //  menu Tools A new command / Locate in Insert Mnu (CATAfrInsertMnu)
   //------------------------------------------------------
   NewAccess(CATCmdContainer,pCreateDatumModeToolsMnu,CATAfrInsertMnu);
   SetAccessChild(pCreateDatumModeMbr,pCreateDatumModeToolsMnu);

   NewAccess(CATCmdSeparator,pCreateDatumModeToolsSep,CAAV5V6MmrUseCreateDatumModeSep);
   SetAccessChild(pCreateDatumModeToolsMnu,pCreateDatumModeToolsSep);

   NewAccess(CATCmdStarter,  pCreateDatumModeM    , CAAV5V6MmrUseCreateDatumModeStr);
   SetAccessCommand ( pCreateDatumModeM    , "CAAV5V6MmrUseCreateDatumModeHdr" );
   SetAccessNext(pCreateDatumModeToolsSep,pCreateDatumModeM);
      
   // Set the menu 
   // pCreateDatumModeTlb: Always the toolbar returned by the method
   // pCreateDatumModeMbr: The container which contains all the menu's containers 
   //
   SetAddinMenu(pCreateDatumModeTlb,pCreateDatumModeMbr);

   //----------------------
   // Visibility 
   //----------------------
         
    AddToolbarView   ( pCreateDatumModeTlb , 1 , Left  ); // Visible toolbar
    
    return pCreateDatumModeTlb;
    
}

