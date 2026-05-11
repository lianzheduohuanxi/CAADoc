// COPYRIGHT DASSAULT SYSTEMES 2000
//===========================================================================
// CAAEMmrSettingsAddIn.cpp
// Provide implementation to interface
//      CATIShapeDesignWorkshopAddin
//
//===========================================================================

//#include "iostream.h"

// Local Framework
#include "CAAEMmrSettingsAddIn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h> // needed to manage workshop access
#include "CATCommandHeader.h"  // needed to instanciate the header

// Creates the CAAEMmrSettingsAddInHeader command header class
MacDeclareHeader(CAAEMmrSettingsAddInHeader);  

// To declare that the class 
// is a DataExtension of (late type) CAAMmrSettingsAddIn

CATImplementClass ( CAAEMmrSettingsAddIn  ,DataExtension,CATBaseUnknown,CAAMmrSettingsAddIn);

// 
// To declare that CAAMmrSettingsAddIn implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary :
//
// CAAMmrSettingsAddIn      CATIShapeDesignWorkshopAddin    libCAAMmrSettingsAddIn

#include <TIE_CATIShapeDesignWorkshopAddin.h> // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(CAAEMmrSettingsAddIn);

//-----------------------------------------------------------------------------
// CAAEMmrSettingsAddIn : constructor
//-----------------------------------------------------------------------------

CAAEMmrSettingsAddIn::CAAEMmrSettingsAddIn()
{
     //    cout << "CAAEMmrSettingsAddIn::CAAEMmrSettingsAddIn "<< endl;
    
}

//-----------------------------------------------------------------------------
// CAAEMmrSettingsAddIn : destructor
//-----------------------------------------------------------------------------

CAAEMmrSettingsAddIn::~CAAEMmrSettingsAddIn()
{
    // cout << "CAAEMmrSettingsAddIn::~CAAEMmrSettingsAddIn "<< endl;
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAEMmrSettingsAddIn::CreateCommands()
{
    // cout << "(CAAEMmrSettingsAddIn::CreateCommands)"<< endl;    
    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button
    
    new CAAEMmrSettingsAddInHeader( "CAAMmrUseCreateDatumModeHdr"  ,
                                      "CAAMmrUseCreateDatumMode"    ,
                                      "CAAMmrDatumWindowCmd" ,
                                      (void *)NULL              );
    
}


//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAEMmrSettingsAddIn::CreateToolbars()
{
    
    // cout << "(CAAEMmrSettingsAddIn::CreateToolbars)"<< endl;
    //----------------------
    // CreateDatumMode Toolbar
    //----------------------
    NewAccess        ( CATCmdContainer  , pCreateDatumModeTlb , CAAMmrUseCreateDatumModeTlb );
   
      NewAccess        ( CATCmdStarter    , pCreateDatumModeT    , CAAMmrUseCreateDatumModeStr );
      SetAccessCommand ( pCreateDatumModeT    , "CAAMmrUseCreateDatumModeHdr" );
      SetAccessChild   ( pCreateDatumModeTlb , pCreateDatumModeT  );
    

   //----------------------
   // CreateDatumMode Menubar 
   //----------------------
	NewAccess(CATCmdContainer,pCreateDatumModeMbr,CAAMmrUseCreateDatumModeMbr);

   //  menu Tools A new command / Locate in Insert Mnu (CATAfrInsertMnu)
   //------------------------------------------------------
      NewAccess(CATCmdContainer,pCreateDatumModeToolsMnu,CATAfrInsertMnu);
      SetAccessChild(pCreateDatumModeMbr,pCreateDatumModeToolsMnu);

      NewAccess(CATCmdSeparator,pCreateDatumModeToolsSep,CAAMmrUseCreateDatumModeSep);
      SetAccessChild(pCreateDatumModeToolsMnu,pCreateDatumModeToolsSep);

      NewAccess(CATCmdStarter,  pCreateDatumModeM    , CAAMmrUseCreateDatumModeStr);
      SetAccessCommand ( pCreateDatumModeM    , "CAAMmrUseCreateDatumModeHdr" );
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

