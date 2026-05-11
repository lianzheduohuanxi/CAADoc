// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationWithMAMacros :
//
// Sample code for : CAA User Operation connected with 3D Machining Area (sample 6)
//
// Mission         : Hide the Macros Tabpage of the edition panel of an user operation connected
//                   with a Machining Area
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a user operation
//                   3- Select the macros tabpage
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct in the resources\graphic directory of the runtime view.
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationWithMAMacros.h"
 
// Tie the implementation to its interface
CATImplementBOA (CATIMfgMacrosTabPage, CAAESmiUserOperationWithMAMacros);
CATImplementClass( CAAESmiUserOperationWithMAMacros,
                   CacheExtension,
                   CATIMfgMacrosTabPage,
                   CAASmgOperationWithMA );
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationWithMAMacros::CAAESmiUserOperationWithMAMacros()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationWithMAMacros::~CAAESmiUserOperationWithMAMacros()
{
}
 
//========================================================================
// IsMacrosTabPageAvailable
//========================================================================
HRESULT CAAESmiUserOperationWithMAMacros::IsMacrosTabPageAvailable( int&  oIsAvailable)
{
    // Hide the Macros TabPage  
    oIsAvailable = 0;
    return S_OK;
}
