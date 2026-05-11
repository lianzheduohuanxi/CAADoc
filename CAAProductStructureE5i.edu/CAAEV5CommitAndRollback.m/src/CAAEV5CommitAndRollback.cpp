//=============================================================================
// COPYRIGHT Dassault Systemes 2008
// Author : ZPL
//=============================================================================
// Abstract of Use Case "CAAEV5CommitAndRollback":
// --------------------------------------------
// Date : 10.01.2008/ Modified 04.02.2008
// The Sample CAAEV5CommitAndRollback shows how different User-exits are called when "Save in Enovia" Command is executed :
//.1.  Create Product structure as shown in Test Data.
//.2.  Click on "Save in ENOVIA" command.
//.3.  Implementation of BeforeSaveDialog will be called which return’s E_FAIL based on static call counter value (At this step counter value is 0 hence returned E_FAIL and incremented by 1).
//.4.  Due to failure of User-exit BeforeSaveDialog an Error message will be shown in reporter panel.
//.5.  Close the Error Message and again click on "Save in ENOVIA" command.
//.6.  Implementation of BeforeSaveDialog will return S_OK (At this step counter value is 1).
//.7.  Save Panel will be displayed, click on OK.
//.8.  Implementation of OnOK will be called which return’s E_FAIL (At this step counter value is 1 hence returned E_FAIL and incremented by 1).
//.9.  Save process has been interrupted, again click on "Save in ENOVIA" command.
//.10. Implementation of BeforeSaveDialog will return S_OK, click on "OK" from Save Panel.
//.11. Implementation of OnOK will return S_OK.
//.12. Implementation of BeforeStartingSave will be called which return’s E_FAIL (At this step counter value is 2 hence returned E_FAIL and incremented by 1).
//.13. If BeforeStartingSave is failed implementation of OnSaveFailed is called which returns S_OK.
//.14. Save process has been interrupted, again click on "Save in ENOVIA" command.
//.15. Implementation of BeforeStartingSave will return S_OK, click on "OK" from Save Panel. 
//.16. Implementation of OnOK, BeforeStartingSave and OnSaveSucceeded will return S_OK.
//.17. Implementation of BeforeCommit will be called which returns S_OK (At this step counter value is 3 and incremented by 1).
//.18. Created Product structure will be saved to ENOVIA.
//.19. Make some modifications on Part geometries, and click on "Save in Enovia".
//.20. Click on "OK" on Save Panel. All other User-exits will return S_OK except for BeforeCommit which returns E_FAIL at this step.
//.21. Due to failure of User-exit BeforeRollback will be called and then ENOVIA rollback will be called, an Error message will be shown in reporter panel.
//.22. Close the Error Message and again click on "Save in ENOVIA" command.
//.23. At this step all User-exits will return S_OK and hence the modified data will be saved to ENOVIA.
//.24. Click on "Save in ENOVIA" command.
//.25. Click on "Cancel" on Save Panel.Implementation of OnCancel will be called which return’s E_FAIL based on static call counter value (At this step counter value is 3 hence returned E_FAIL and incremented by 1).
//.26. Due to failure of User-exit OnCancel an Error message will be shown in reporter panel.
//.27. Close the Error Message and again click on "Save in ENOVIA" command.
//.28. Click on "Cancel" on Save Panel.
//.29. Implementation of OnCancel will return S_OK.
//=============================================================================
/**
* @quickReview VPW BBX 09:01:12 Method ::OnCancel() added for user-exit UEOnCancel for HONDA HL  on R20
* @quickReview SDM ZPL 08:02:05 Modifications on this Use Case to cover all existing User-exits in CATIPDMUESaveProcess
* @fullreview SDM ZPL 08:08:17 For Added APIs "BeforeCommit", "BeforeRollback" and "GetModificationStatus"
*/
#include "CAAEV5CommitAndRollback.h"

// To Display the Trac
#include <iostream.h>
#include "CATUnicodeString.h"

//For Modification Status
#include "CATIPDMSaveInfo.h"
#include "CATIPDMUESaveProcess.h"

static int CallCounter =0;

CATImplementClass( CAAEV5CommitAndRollback,
                   DataExtension,
                   CATBaseUnknown,
                   CATUEPDMSaveProcess);
 
//-----------------------------------------------------------------------------
// CAAEV5CommitAndRollback : constructor 
//-----------------------------------------------------------------------------
CAAEV5CommitAndRollback::CAAEV5CommitAndRollback():
    CATBaseUnknown()
{
   cout << "CAAEV5CommitAndRollback::CAAEV5CommitAndRollback" << endl;
}

//-----------------------------------------------------------------------------
// CAAEV5CommitAndRollback : destructor
//-----------------------------------------------------------------------------
CAAEV5CommitAndRollback::~CAAEV5CommitAndRollback()
{
   cout << "CAAEV5CommitAndRollback::~CAAEV5CommitAndRollback" << endl;
}
  
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIPDMUESaveProcess.h"
TIE_CATIPDMUESaveProcess(CAAEV5CommitAndRollback);

// VPW R20 HONDA HL
#include "TIE_CATIPDMUEOnCancel.h"
TIE_CATIPDMUEOnCancel(CAAEV5CommitAndRollback);

/**
// * Implements CAAEV5CommitAndRollback::BeforeSaveDialog.
//   BeforeSaveDialog API is called after User Clicks on "Save in Enovia" Command.
//   User can add his required operations which may be reflected to the "Save in Enovia" Panel 
 */
HRESULT __stdcall CAAEV5CommitAndRollback::BeforeSaveDialog(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  cout << "CAAEV5CommitAndRollback::BeforeSaveDialog -> UE for BeforeSaveDialog succeded" << endl;
  if(iDocsToSave && ipInfo)
  {
    int nbDocInSession = iDocsToSave->Size() ;
    //CallCounter ++;
    for ( int i = 1 ; i <= nbDocInSession ; ++i )
    {
      CATDocument * currentDoc = (*iDocsToSave)[i] ;
      if (currentDoc)
      {
        //We have to check for its CATIPDMSaveInfo::ModifStatus
        CATIPDMSaveInfo::ModifStatus oDocStatus = CATIPDMSaveInfo::PDM_NotDefined;
        HRESULT RC = ipInfo->GetModificationStatus(currentDoc, oDocStatus);//CATIPDMSaveInfo::ModifStatus oDocStatus);
        if (SUCCEEDED(RC) && oDocStatus == CATIPDMSaveInfo::PDM_New)
        {
          CATUnicodeString DocName = currentDoc->storageName();
          cout << "CAAEV5CommitAndRollback::BeforeSaveDialog -> Current Document Name is:" << DocName.ConvertToChar()<<"PDM Status of Document is:PDM_New"<<endl;
        }
        else if (SUCCEEDED(RC) && oDocStatus == CATIPDMSaveInfo::PDM_Modified)
        {
          CATUnicodeString DocName = currentDoc->storageName();
          cout << "CAAEV5CommitAndRollback::BeforeSaveDialog -> Current Document Name is:" << DocName.ConvertToChar()<<"PDM Status of Document is:PDM_New"<<endl;
        }
      }
      else cout <<"CAAEV5CommitAndRollback::BeforeSaveDialog -> Current Doc not found"<<endl;
    }
    //return S_OK;
    if(CallCounter == 0)
    {
      CallCounter++;
      cout <<"CAAEV5CommitAndRollback::BeforeSaveDialog -> CallCounter=0 hence return E_FAIL"<<endl;
      return E_FAIL;
    }
    else
    {
      cout <<"CAAEV5CommitAndRollback::BeforeSaveDialog ->  return SUCCESS"<<endl;
      return S_OK;
    }
  }
  else cout <<"CAAEV5CommitAndRollback::BeforeSaveDialog -> List of Doc or SaveInfo is Empty"<<endl;
  return E_FAIL;
}

/**
// * Implements CAAEV5CommitAndRollback::OnOK.
//   OnOK API is called after User Clicks on "OK" from "Save in Enovia" Panel.
//   User can add his required operations which will be called before Save process is started from CV5 
 */
HRESULT __stdcall CAAEV5CommitAndRollback::OnOK(CATLISTP(CATDocument) * iDocsToSave, int onOKNumber, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  //Just a Trace and return S_OK
  cout << "CAAEV5CommitAndRollback::OnOK -> UE for OnOK succeded" << endl;
  if(iDocsToSave && ipInfo)
  {
    if(CallCounter == 1)
    {
      CallCounter++;
      cout <<"CAAEV5CommitAndRollback::OnOK -> CallCounter=1 hence return E_FAIL"<<endl;
      return E_FAIL;
    }
    else
    {
      cout <<"CAAEV5CommitAndRollback::OnOK ->  return SUCCESS"<<endl;
      return S_OK;
    }
  }
  else cout <<"CAAEV5CommitAndRollback::OnOK -> List of Doc or SaveInfo is Empty"<<endl;
  return E_FAIL;
}

/**
// * Implements CAAEV5CommitAndRollback::BeforeStartingSave.
 */
HRESULT __stdcall CAAEV5CommitAndRollback::BeforeStartingSave(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  //Just a Trace and return S_OK
  cout << "CAAEV5CommitAndRollback::BeforeStartingSave -> UE for BeforeStartingSave succeded" << endl;
  if(CallCounter == 2)
  {
    CallCounter++;
    cout <<"CAAEV5CommitAndRollback::BeforeStartingSave -> CallCounter=2 hence return E_FAIL"<<endl;
    return E_FAIL;
  }
  else
  {
    cout <<"CAAEV5CommitAndRollback::BeforeStartingSave ->  return SUCCESS"<<endl;
    return S_OK;
  }
}

/**
 * Implements CAAEV5CommitAndRollback::OnSaveSucceeded.
 */
HRESULT __stdcall CAAEV5CommitAndRollback::OnSaveSucceeded(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  //Just a Trace and return S_OK
  cout << "CAAEV5CommitAndRollback::OnSaveSucceeded -> UE for OnSaveSucceeded succeded" << endl;
  return S_OK;
}

/**
 * Implements CAAEV5CommitAndRollback::OnSaveFailed.
 */
HRESULT __stdcall CAAEV5CommitAndRollback::OnSaveFailed(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  //Just a Trace and return S_OK
  cout << "CAAEV5CommitAndRollback::OnSaveFailed -> UE for OnSaveFailed succeded" << endl;
  return S_OK;
}

/**
// * Implements CAAEV5CommitAndRollback::BeforeCommit.
//   BeforeCommit API is called after the Save Process has been succeded
//   User can add his Modifications on the DOCs which are finally going to be commited to Vault
//   If BeforeCommit User exits fails:
//      1. Commit will not be called for the session
//      2. Based on Implementation BeforeRollback user Exit will be called
//      3. Rollback will be called on the session 
 */
HRESULT __stdcall CAAEV5CommitAndRollback::BeforeCommit(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  cout << "CAAEV5CommitAndRollback::BeforeCommit -> UE for BeforeCommit succeded" << endl;
  HRESULT RC=S_OK;

  if(iDocsToSave && ipInfo)
  {
    int nbDocInSession = iDocsToSave->Size() ;
    for (int i = 1 ; i <= nbDocInSession ;++i)
    {
      //Lets take out each CATDocument from the List
      CATDocument * currentDoc = (*iDocsToSave)[i];
      if (currentDoc)
      {
        CATIPDMSaveInfo::ModifStatus oDocStatus = CATIPDMSaveInfo::PDM_NotDefined;
        HRESULT RC = ipInfo->GetModificationStatus(currentDoc, oDocStatus);
        if (SUCCEEDED(RC) && oDocStatus == CATIPDMSaveInfo::PDM_NotModified)
        {
          CATUnicodeString DocName = currentDoc->storageName();
          cout << "CAAEV5CommitAndRollback::BeforeCommit -> Current Document Name is:"<<DocName.ConvertToChar()<<" And Status of DOC is PDM_NotModified"<<endl;
        }
      }
      else cout << "CAAEV5CommitAndRollback::BeforeCommit -> Doc not found" << endl;
      //return S_OK;
    }
    if (CallCounter==4)
    {
      CallCounter++;
      cout <<"CAAEV5CommitAndRollback::BeforeCommit -> CallCounter=4 hence return E_FAIL"<<endl;
      return E_FAIL;
    }
    else
    {
      CallCounter++;
      cout <<"CAAEV5CommitAndRollback::BeforeCommit ->  return SUCCESS"<<endl;
      return S_OK;
    }
  }
  else cout <<"CAAEV5CommitAndRollback::BeforeCommit -> List of Doc or SaveInfo is Empty"<<endl;
  return E_FAIL;
}

/**
// * Implements CAAEV5CommitAndRollback::BeforeRollback.
//   BeforeRollback API may be called for following two cases:
//   1. If BeforeCommit User exits fails,
//   2. If ineterop rollback is called,
 */
HRESULT __stdcall CAAEV5CommitAndRollback::BeforeRollback(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
  //Just a Trace and return S_OK
  cout << "CAAEV5CommitAndRollback::BeforeRollback -> UE for BeforeRollback succeded" << endl;
  return S_OK;
}

// VPW added for HONDA HL on R20
// This new method is available with new interface CATIPDMUEOnCancel
HRESULT __stdcall CAAEV5CommitAndRollback::OnCancel(CATLISTP(CATDocument) * iDocsToSave, CATIPDMSaveInfo* ipInfo, CATIPDMSaveAction* ipAction)
{
	if (CallCounter==3)
	{
		CallCounter++;
		cout <<"CAAEV5CommitAndRollback::BeforeCommit -> CallCounter=4 hence return E_FAIL"<<endl;
		return E_FAIL;
	}
	else
	{
		cout << "CAAEV5CommitAndRollback::OnCancel -> UE for OnCancel succeded" << endl;	
		return S_OK;
	}
}

