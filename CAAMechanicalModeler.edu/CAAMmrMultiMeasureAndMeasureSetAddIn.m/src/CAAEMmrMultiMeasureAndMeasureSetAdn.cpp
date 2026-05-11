// COPYRIGHT DASSAULT SYSTEMES 2007
//===========================================================================
// CAAEMmrMultiMeasureAndMeasureSetAdn.cpp
// Provide implementation to interface
//      CATIShapeDesignWorkshopAddin
//
//===========================================================================

// Local Framework
#include "CAAEMmrMultiMeasureAndMeasureSetAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h> // needed to manage workshop access
#include "CATCommandHeader.h"  // needed to instanciate the header

// Creates the CAAEMmrMultiMeasureAndMeasureSetAdnHeader command header class
MacDeclareHeader(CAAEMmrMultiMeasureAndMeasureSetAdnHeader);  

// To declare that the class 
// is a DataExtension of (late type) CAAMmrCombinedCurveAddin

CATImplementClass ( CAAEMmrMultiMeasureAndMeasureSetAdn  ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CAAMmrMultiMeasureAndMeasureSetAddin );

// 
// To declare that CAAMmrMultiMeasureAndMeasureSetAdin implements CATIShapeDesignWorkshopAddin, insert 
// the following line in the interface dictionary :
//
// CAAMmrMultiMeasureAndMeasureSetAddin      CATIShapeDesignWorkshopAddin    libCAAMmrMultiMeasureAndMeasureSetAddIn

#include <TIE_CATIShapeDesignWorkshopAddin.h> // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(CAAEMmrMultiMeasureAndMeasureSetAdn);

//-----------------------------------------------------------------------------
// CAAEMmrMultiMeasureAndMeasureSetAdn : constructor
//-----------------------------------------------------------------------------

CAAEMmrMultiMeasureAndMeasureSetAdn::CAAEMmrMultiMeasureAndMeasureSetAdn()
{
    
}

//-----------------------------------------------------------------------------
// CAAEMmrMultiMeasureAndMeasureSetAdn : destructor
//-----------------------------------------------------------------------------

CAAEMmrMultiMeasureAndMeasureSetAdn::~CAAEMmrMultiMeasureAndMeasureSetAdn()
{
    
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void CAAEMmrMultiMeasureAndMeasureSetAdn::CreateCommands()
{
    
    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button
    
    new CAAEMmrMultiMeasureAndMeasureSetAdnHeader( "CAAMmrMeasureSetHdr"  ,
                                         "CAAMmrMultiMeasureAndMeasureSetUI"    ,
                                         "CAAMmrMeasureSetStCmd" ,
                                         (void *)NULL              );

    new CAAEMmrMultiMeasureAndMeasureSetAdnHeader( "CAAMmrMultiMeasureHdr"  ,
                                         "CAAMmrMultiMeasureAndMeasureSetUI"    ,
                                         "CAAMmrMultiMeasureStCmd" ,
                                         (void *)NULL              );
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* CAAEMmrMultiMeasureAndMeasureSetAdn::CreateToolbars()
{
    
    // CAAMmrMeasureSet Toolbar 
    NewAccess        ( CATCmdContainer  , pMeasureSetWkb , CAAMmrMultiMeasureAndMeasureSetTlb );
    
    NewAccess        ( CATCmdStarter    , pMeasureSet    , CAAMmrMeasureSetStr );
    SetAccessCommand ( pMeasureSet      , "CAAMmrMeasureSetHdr" );
    SetAccessChild   ( pMeasureSetWkb   , pMeasureSet  );
    
    // CAAMmrMultiMeasure Toolbar 
    NewAccess        ( CATCmdStarter    , pMultiMeasure ,CAAMmrMultiMeasureStr );
    SetAccessCommand ( pMultiMeasure    , "CAAMmrMultiMeasureHdr" );
    SetAccessNext    ( pMeasureSet      , pMultiMeasure);
    
    AddToolbarView   ( pMeasureSetWkb , -1 , Right ); // Unvisible toolbar 

    return pMeasureSetWkb;
}

