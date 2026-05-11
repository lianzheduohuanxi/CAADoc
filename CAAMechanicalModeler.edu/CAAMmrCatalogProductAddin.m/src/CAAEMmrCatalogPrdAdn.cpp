// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEMmrCatalogPrdAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h> // needed to manage workshop access
#include "CATCommandHeader.h"  // needed to instanciate the header

#include <iostream.h>

// Creates the CAAEMmrCatalogPrdAdnHeader command header class
MacDeclareHeader(CAAEMmrCatalogPrdAdnHeader);  

#include "TIE_CATIPrsConfigurationAddin.h"
TIEchain_CATIPrsConfigurationAddin(CAAEMmrCatalogPrdAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAMmrCatalogPrdAddin

CATImplementClass ( CAAEMmrCatalogPrdAdn  ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CAAMmrCatalogPrdAddin );

// 
// To declare that CAAMmrCatalogPrdAddin implements CATIPrsConfigurationAddin, 
// insert the following line in the interface dictionary :
//
// CAAMmrCatalogPrdAddin      CATIPrsConfigurationAddin    libCAAMmrCatalogProductAddin


//-----------------------------------------------------------------------------
// CAAEMmrCatalogPrdAdn : constructor
//-----------------------------------------------------------------------------

CAAEMmrCatalogPrdAdn::CAAEMmrCatalogPrdAdn()
{
}

//-----------------------------------------------------------------------------
// CAAEMmrCatalogPrdAdn : destructor
//-----------------------------------------------------------------------------

CAAEMmrCatalogPrdAdn::~CAAEMmrCatalogPrdAdn()
{
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAEMmrCatalogPrdAdn::CreateCommands()
{
    
    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button
    
    new CAAEMmrCatalogPrdAdnHeader( "CAAMmrCatalogBrowserHdr"  , 
                                    "CAAMmrCatalogUI"    ,
                                    "CAAMmrBrowserCmd" ,
                                      (void *)NULL              );
    
}


//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAEMmrCatalogPrdAdn::CreateToolbars()
{
   
    // Catalog Toolbar 
    NewAccess        ( CATCmdContainer  , pCAAMmrCatalogPrdTlb , CAAMmrCatalogPrdTlb );
    
    NewAccess        ( CATCmdStarter    , pCAAMmrCatalogPrdStr    , CAAMmrCatalogPrdStr );
    SetAccessCommand ( pCAAMmrCatalogPrdStr , "CAAMmrCatalogBrowserHdr" );
    SetAccessChild   ( pCAAMmrCatalogPrdTlb , pCAAMmrCatalogPrdStr  );
    
    AddToolbarView   ( pCAAMmrCatalogPrdTlb , 1 , Top ); // Visible toolbar
    
    return pCAAMmrCatalogPrdTlb ;
    
}

