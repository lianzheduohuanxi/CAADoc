//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
// Author :   ZPL
// Creation : January 2008
//=============================================================================
// CAAEV5CommitAndRollback.h
// Date : 10.01.2008
// The Sample CAAEV5CommitAndRollback shows how to use User Exits when 
// "Save in Enovia" Command is executed :
//=============================================================================
/**
* @quickReview VPW BBX 09:01:12 Method ::OnCancel() added for user-exit UEOnCancel for HONDA HL  on R20
*/


#ifndef CAAEV5CommitAndRollback_h
#define CAAEV5CommitAndRollback_h

#include "CATBaseUnknown.h"
#include "CATDocument.h"

class CATIPDMSaveInfo;
class CATIPDMSaveAction;


class CAAEV5CommitAndRollback: public CATBaseUnknown
{
  CATDeclareClass;

  public:
  
    //--------------------------------------------------------------
    // Basic class tools
    //--------------------------------------------------------------
    CAAEV5CommitAndRollback();
    virtual ~CAAEV5CommitAndRollback();

    HRESULT __stdcall BeforeSaveDialog(CATLISTP(CATDocument) * iDocsToSave, 
                                CATIPDMSaveInfo* ipInfo,
                                CATIPDMSaveAction* ipAction);

    HRESULT __stdcall OnOK(CATLISTP(CATDocument)* iDocsToSave, 
                                int onOKNumber, 
                                CATIPDMSaveInfo *ipInfo, 
                                CATIPDMSaveAction *ipAction);


    HRESULT __stdcall BeforeStartingSave(CATLISTP(CATDocument) * iDocsToSave, 
                                CATIPDMSaveInfo* ipInfo,
                                CATIPDMSaveAction* ipAction);

    HRESULT __stdcall OnSaveSucceeded(CATLISTP(CATDocument) * iDocsToSave, 
                                CATIPDMSaveInfo* ipInfo,
                                CATIPDMSaveAction* ipAction);

    HRESULT __stdcall OnSaveFailed(CATLISTP(CATDocument) * iDocsToSave, 
                                CATIPDMSaveInfo* ipInfo,
                                CATIPDMSaveAction* ipAction);

    HRESULT __stdcall BeforeCommit(CATLISTP(CATDocument) * iDocsToSave, 
                                CATIPDMSaveInfo* ipInfo,
                                CATIPDMSaveAction* ipAction);

    HRESULT __stdcall BeforeRollback(CATLISTP(CATDocument) * iDocsToSave, 
                                CATIPDMSaveInfo* ipInfo,
																CATIPDMSaveAction* ipAction);

		// VPW added for HONDA HL on R20
		// Method declared on new interface CATIPDMUEOnCancel
		HRESULT __stdcall OnCancel(CATLISTP(CATDocument) * iDocsToSave, 
			                          CATIPDMSaveInfo* ipInfo,
			                          CATIPDMSaveAction* ipAction);

  private:

   //--------------------------------------------------------------
   // Copy CVonstructor & Operator = declared in private to avoid 
   // default construction and public declaration by the compiler
   //--------------------------------------------------------------
   CAAEV5CommitAndRollback(const CAAEV5CommitAndRollback &);
   CAAEV5CommitAndRollback& operator=(const CAAEV5CommitAndRollback &);

};

#endif


