// -------------------------------------------------------------------
// Copyright Dassault Systemes 2006
//---------------------------------------------------------------------
// Shade Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMFrmSelectorCtx
//---------------------------------------------------------------------
// 
//  Class for contextual Item management 
//    - Extend CATGSMUICmdInfo with management of Edit context (ClearSelection , Edit current feature)
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 06/06/01 > PEY 
//---------------------------------------------------------------------

#include "CATGSMUICmdInfo.h"
#include "CAAGSMFrmCtxMenuInfoUser.h"

// #define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 

// Constructor 
CAAGSMFrmCtxMenuInfoUser::CAAGSMFrmCtxMenuInfoUser (): _info(NULL)
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMFrmCtxMenuInfoUser ) Constructor "  << endl; 
#endif   
    _info = new CATGSMUICmdInfo ();
    _CmdEditMode = 0 ; 
    
}

// Destructor 
CAAGSMFrmCtxMenuInfoUser::~CAAGSMFrmCtxMenuInfoUser () 
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAGSMFrmCtxMenuInfoUser ) Destructor "  << endl; 
#endif   
    _CmdEditMode = 0 ; 
    if (NULL!= _info) {delete _info; _info= NULL;} 
}

// EditMode 
int  CAAGSMFrmCtxMenuInfoUser::GetEditMode ()
{
    return _CmdEditMode ;
}

void CAAGSMFrmCtxMenuInfoUser::SetEditMode (int Edt) 
{ 
    _CmdEditMode = Edt ;
    return;
}

// Cmdinfo 
CATGSMUICmdInfo * CAAGSMFrmCtxMenuInfoUser::GetCmdInfo  () 
{ 
    return _info  ;
}

