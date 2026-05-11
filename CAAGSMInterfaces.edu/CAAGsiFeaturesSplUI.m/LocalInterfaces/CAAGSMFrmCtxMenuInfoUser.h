#ifndef CAAGSMFrmCtxMenuInfoUser_H
#define CAAGSMFrmCtxMenuInfoUser_H
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
class CATGSMUICmdInfo; 

// Class User Info for Contextual menu creation/definition
// -----------------------------------------------------------------
class CAAGSMFrmCtxMenuInfoUser
{
  public :
      CAAGSMFrmCtxMenuInfoUser ();
      ~CAAGSMFrmCtxMenuInfoUser (); 
      
      int  GetEditMode ();
      void SetEditMode (int Edt) ;
      CATGSMUICmdInfo * GetCmdInfo  () ;
      
  private:
      int _CmdEditMode ;  
      CATGSMUICmdInfo *_info ; 
};
#endif 

