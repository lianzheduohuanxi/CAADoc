// COPYRIGHT Dassault Systemes 2007
//==============================================================================================
// CAAEnoviaV5SaveCmd.cpp
//
// Creation:  BZQ - 08.29.2007
// Scenario:  Using CAA APIs this Use Case shows how to...
//                  1. load an assembly from the EV5 dB
//                  2. modify this assembly inserting in it file based data
//                  3. define a Vault Mode for the inserted file based data
//                  4. save in EV5 the whole modifications done on the assembly
// Info:  In context of highlight "Automate Access ENOVIA data from CATIA V5", this Use Case is 
//        mainly dedicated to present the way to use new CAA APIs LoadFromPDM() & SetEV5PersistencyMode().
//        
// Prerequisite : Before runing this Use-Case a specific Product Structure have to be created in EV5 database.
//                These are the 5 steps to follow... (from a CATIA V5 connected to an ENOVIA V5 VPM)
//
//                  1. Load and Open any PRC in CV5 (create it if necessary)
//                  2. Insert under PRC: AutoAccessAPI_BranchOne.CATProduct (located into: CAAProductStructureE5i.edu\InputData\StartingPS)
//                                       AutoAccessAPI_BranchTwo.CATProduct (located into: CAAProductStructureE5i.edu\InputData\StartingPS)
//                  3. Chose the "Structure Exposed" vaultMode for each new CATProduct inserted
//                  4. Save the whole assembly in ENOVIA V5 VPM
//
//                This will provide the required Assembly describe at step2 of CAAEnoviaV5SaveCmd::OnOKSelected()
//==============================================================================================

/*
* @quickreview NW2 12:02:24 RollBack the changes of "Added var CV5EV5RecOdt_IR146962_LoadFromPDM to support new ODT CV5EV5RecOdt_IR146962_LoadFromPDM.sh".
* @quickreview NW2 12:02:17 Added var CV5EV5RecOdt_IR146962_LoadFromPDM to support new ODT CV5EV5RecOdt_IR146962_LoadFromPDM.sh
* @quickreview ZUF BBX 09:12:03 - Used "EnoviaV5Save" instead of "LCATrueSave" for "CAACV5AccessEV5DataAPI.sh" ODT 
* @quickreview BZQ 08:03:04 IR 615424 - In ComputeDataPath(), manage working directory to be able to open file-based data
* @quickReview BZQ 08:01:23 MLK-319899 In TraceDocumentname()
* @quickReview BZQ 08:01:23 Modifications necessary to run the Use-Case as an ODT
* @fullReview  BZQ 07:08:29 Creation
*/

#include "CAAEnoviaV5SaveCmd.h"
#include <iostream.h>

#ifdef _WINDOWS_SOURCE
#include <direct.h>
#else
#include <unistd.h>
#endif

// System
#include "CATCreateExternalObject.h"
CATCreateClass(CAAEnoviaV5SaveCmd);
#include "CATLib.h"

// Dialog
#include "CATDlgNotify.h"
#include "CATDlgUtility.h"
#include "CATDialogAgent.h"
#include "CATDialogState.h"

// ApplicationFrame
#include "CATAfrCommandHeaderServices.h"
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"
#include "CATFrmWindow.h"
#include "CATFrmLayout.h"

// ObjectModelerBase
#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATIEditor.h"
#include "CATIDocEnvironment.h"
#include "CATIDocId.h"
#include "CATDocEnvManager.h"
#include "CATIDocRoots.h"
#include "CATDocumentServices.h"

// ProductStructure
#include "CATIProduct.h"

// CATPDMBase
#include "CATPDMInteropServices.h"
#include "CATIPLMIdentificator.h"
#include "CATListOfCATIPLMIdentificator.h"
#include "CATPDMCSServices.h"

// CATPDMBaseInterface
#include "CATIPDMPersistency.h"


//-------------------------------------------------------------------------
// Command Constructor
//-------------------------------------------------------------------------
CAAEnoviaV5SaveCmd::CAAEnoviaV5SaveCmd() :  CATStateCommand("CAAEnoviaV5SaveCmd", CATDlgEngOneShot, CATCommandModeExclusive), 
                                            _pEV5SaveDlgNfy(NULL),
                                            _pCancelNfyAgent(NULL),
                                            _pOKNfyAgent(NULL)
{
  cout << "-->CAAEnoviaV5SaveCmd::CAAEnoviaV5SaveCmd()"  << endl;
  
  // Build the CATDlgNotify
  _pEV5SaveDlgNfy = new CATDlgNotify(CATApplicationFrame::GetFrame()->GetMainWindow(), "CQQEnoviaV5SaveCmd", CATDlgNfyYesNo);

  if (_pEV5SaveDlgNfy != NULL)
  {
    // Hide the CATDlgNotify
    cout << "CAAEnoviaV5SaveCmd() - Notification Dialog Created!" << endl;

    _pEV5SaveDlgNfy->SetText("Do you want to Launch EnoviaV5Save Command?");
    _pEV5SaveDlgNfy->SetVisibility(CATDlgHide);
  }

  cout << "<--CAAEnoviaV5SaveCmd::CAAEnoviaV5SaveCmd()" << endl;
}


//-------------------------------------------------------------------------
// Command Destructor
//-------------------------------------------------------------------------
CAAEnoviaV5SaveCmd::~CAAEnoviaV5SaveCmd()
{
  cout << "-->CAAEnoviaV5SaveCmd::~CAAEnoviaV5SaveCmd()" << endl;

  if (_pEV5SaveDlgNfy != NULL) 
  {
    _pEV5SaveDlgNfy->SetVisibility(CATDlgHide);
    _pEV5SaveDlgNfy->RequestDelayedDestruction(); _pEV5SaveDlgNfy = NULL;

    cout << "~CAAEnoviaV5SaveCmd() - CATDlgNotify Deleted!" << endl;
  }

  if (_pCancelNfyAgent != NULL)
  {
    _pCancelNfyAgent->RequestDelayedDestruction();
    _pCancelNfyAgent = NULL;

    cout << "~CAAEnoviaV5SaveCmd() - Cancel agent Deleted!" << endl;
  }

  if (_pOKNfyAgent != NULL)
  {
    _pOKNfyAgent->RequestDelayedDestruction();
    _pOKNfyAgent = NULL;

    cout << "~CAAEnoviaV5SaveCmd() - OK agent Deleted!" << endl;
  }

  cout << "<--CAAEnoviaV5SaveCmd::~CAAEnoviaV5SaveCmd()" << endl;
}  


//-------------------------------------------------------------------------
// Command life cycle definition
//-------------------------------------------------------------------------
void CAAEnoviaV5SaveCmd::BuildGraph()
{
  cout << "-->CAAEnoviaV5SaveCmd::BuildGraph()" << endl;

   // Create the Dialog States
  CATDialogState * State1 = GetInitialState("StartState_PanelOpen");

  // Create Cancel Dialog Agent
  _pCancelNfyAgent = new CATDialogAgent("CancelNfyAgent");
  _pCancelNfyAgent->AcceptOnNotify(_pEV5SaveDlgNfy,_pEV5SaveDlgNfy->GetNfyNoNotification());
  _pCancelNfyAgent->AcceptOnNotify(_pEV5SaveDlgNfy,_pEV5SaveDlgNfy->GetWindCloseNotification());

  // Create OK Dialog Agent
  _pOKNfyAgent = new CATDialogAgent("OKNfyAgent");
  _pOKNfyAgent->AcceptOnNotify(_pEV5SaveDlgNfy,_pEV5SaveDlgNfy->GetNfyYesNotification());
  
  // Add Agent to State
  State1->AddDialogAgent(_pCancelNfyAgent);
  State1->AddDialogAgent(_pOKNfyAgent);
   
  // Create the Stateshart
  AddTransition(State1,NULL,IsOutputSetCondition(_pOKNfyAgent),Action((ActionMethod)&CAAEnoviaV5SaveCmd::OnOKSelected, NULL, NULL, (void*)NULL));
  AddTransition(State1,NULL,IsOutputSetCondition(_pCancelNfyAgent));

  cout << "<--CAAEnoviaV5SaveCmd::BuildGraph()" << endl;
}


// --------------------------------------------------
// Display the command start panel
// Called upon Activation of the Command
// --------------------------------------------------
CATStatusChangeRC CAAEnoviaV5SaveCmd::Activate(CATCommand *iFromClient, CATNotification *iEvtDat)
{
  cout << "-->CAAEnoviaV5SaveCmd::Activate()" << endl;

  if (_pEV5SaveDlgNfy != NULL)
  {
    // Display the CATDlgNotify
    cout << "Activate() - Dialog ready to be displayed!" << endl;

    _pEV5SaveDlgNfy->SetText("Run the HL Automate Access ENOVIA data from CATIA V5 use-case...");
    _pEV5SaveDlgNfy->SetVisibility(CATDlgShow);
  }
  else cout << "Activate() - **Error: Dialog empty!" << endl;

  cout << "<--CAAEnoviaV5SaveCmd::Activate()" << endl;
  return CATStatusChangeRCCompleted;
}


// --------------------------------------------------
// Useless for the moment
// Called upon Desactivation of the Command
// --------------------------------------------------
CATStatusChangeRC CAAEnoviaV5SaveCmd::Desactivate(CATCommand *iFromClient, CATNotification *iEvtDat)
{
  cout << "-->CAAEnoviaV5SaveCmd::Desactivate()" << endl;

	Cancel(iFromClient, iEvtDat);

  cout << "<--CAAEnoviaV5SaveCmd::Desactivate()" << endl;
  return CATStatusChangeRCCompleted;
}


// --------------------------------------------------
// Useless for the moment
// Called upon Cancel of the Command
// --------------------------------------------------
CATStatusChangeRC CAAEnoviaV5SaveCmd::Cancel(CATCommand *iFromClient, CATNotification *iEvtDat)
{
  cout << "-->CAAEnoviaV5SaveCmd::Cancel()" << endl;
  
  // May be useful later...

  cout << "<--CAAEnoviaV5SaveCmd::Cancel()" << endl;	  
  return CATStatusChangeRCCompleted;
}

//---------------------------------------------------------------------------------------
// Command main function
//
// Role:    Step1 - Retrieve 3 EV5 (asm) Item Instances identificators    => RunObjectService() CAA API
//          Step2 - Load the 3 EV5 (asm) Item Instances                   => LoadFromPDM() CAA API
//
//            PRC
//             |_BranchOneRoot.1
//             |    |_BranchOneASMII.1
//             |_BranchTwoRoot.1
//                  |_BranchThreeRoot.1
//                  |    |_BranchThreeASMII.1
//                  |_BranchTwoASMII.1
//
//          Step3 - Insert a file based "CATProduct" under the 1st EV5 Item Instances loaded (BranchOneASMII.1)
//                  Set the "VolatileExposed" Vault Mode on the inserted "CATProduct" => SetEV5PersistencyMode() CAA API
//            PRC
//             |_BranchOneRoot.1
//             |    |_BranchOneASMII.1
//             |          |_FileBasedProduct.1
//             |                |_FileBasedPart.1
//             |_BranchTwoRoot.1
//                  |_BranchThreeRoot.1
//                  |    |_BranchThreeASMII.1
//                  |_BranchTwoASMII.1
//
//          Step4 - Insert a file based "CATProduct" under the 2nd EV5 Item Instances loaded (BranchOneASMII.1)
//                  Set the "PermanentBlackBox" Vault Mode on the inserted "CATProduct" => SetEV5PersistencyMode() CAA API
//            PRC
//             |_BranchOneRoot.1
//             |    |_BranchOneASMII.1
//             |          |_FileBasedProduct.1
//             |                |_FileBasedPart.1
//             |_BranchTwoRoot.1
//                  |_BranchThreeRoot.1
//                  |    |_BranchThreeASMII.1
//                  |_BranchTwoASMII.1
//                        |_FileBasedProd2.1
//                              |_FileBasedSubProd2Branch01.1
//                              |   |_FileBasedSubProd2Part.1
//                              |   |_FileBasedSubProd2SubBranch01.1
//                              |       |_FileBasedSubProd2SubBranch01Part.1
//                              |_FileBasedSubProd2Branch02.1
//                                  |_FileBasedProd2Branch02Part.1
//
//          Step5 - Open the whole assembly in an editor
//                  Save the assembly calling the EV5Save command
//
// Returns: [FALSE] At least one of the step has failed
//          [TRUE]  Scnario has successfully run through the 4 steps
//---------------------------------------------------------------------------------------
CATBoolean CAAEnoviaV5SaveCmd::OnOKSelected(void *data)
{
	cout << "-->CAAEnoviaV5SaveCmd::OnOKSelected()" << endl;
	HRESULT rc = E_FAIL;

	//*Step1 : Retrieve the PLM-Identificators of 3 EV5 Assembly Item Instances that belong to the same PRC
	//         using CAA API RunObjectService().
	//         (The whole product structure is supposed to have already been created on EV5 database)

	//RunObjectService parameters

	CATLISTV(CATIPLMIdentificator_var) plmIdentificatorList,  // Ouput param: List supposed to be filled with the 3 II CATIPLMIdentificators
		notUsedInputList;      // Input param: Useless in this Use-Case
	CATString   iServName     = "ENOVIA5_AccessEV5Data";      // Input param: Late-Type of the RunObjectServiceCode Implementation
	// Input param: String constitute with the V_ID of the 3 EV5 Item Instances
	const char *ipString      = "Instance;AutoAccessAPI_BranchOneASMII.1;AutoAccessAPI_BranchTwoASMII.1;AutoAccessAPI_BranchThreeASMII.1";
	char       *notUsedString = NULL;                         // Ouput param: Useless in this Use-Case

	// RunObjectService executing
	int nbID = 0;
	rc = CATPDMCSServices::RunObjectService(iServName, notUsedInputList, ipString, plmIdentificatorList, &notUsedString);

	if (SUCCEEDED(rc))
	{
		// Trace the number of the built PLM-Identificators
		nbID = plmIdentificatorList.Size();
		cout << "OnOKSelected - The list returned by RunObjectService() contains " << nbID << " PLMId(s)" << endl;
	}
	else cout << "OnOKSelected - **Error: RunObjectService() has failed!" << endl;


	//*Step2: Load in CV5 session the 3 EV5 Item Instances whose PLM-Identificators have just been retrieved
	//        using CAA API LoadFromPDM().
	if (nbID > 0)
	{
		// LoadFromPDM parameters
		CATLISTP(CATDocument)* pOpenedDocsList = NULL;  // Ouput param: List supposed to be filled with the CATDocuments opened in CV5 session
		//              resulting from Load of the 3 EV5 Item Instances

		// LoadFromPDM executing
		rc = LoadFromPDM(plmIdentificatorList, pOpenedDocsList);

		// Trace the number the Storage Name of the opened CATDocument
		if (SUCCEEDED(rc)) rc = TraceDocumentName(pOpenedDocsList);
		else cout << "OnOKSelected - **Error : LoadFromPDM() has failed!" << endl;


		//*Step3: Insert a file based Product under the loaded instance BranchOneASMII.1
		//        Set VolatileExposed Vault Mode on the Product and its children
		//        using CAA API SetEV5PersistencyMode().
		if (SUCCEEDED(rc))
		{
			// Get the Document hosting the Reference of Instance BranchOneASMII.1
			CATDocument *pBranchOneLeafDoc = (*pOpenedDocsList)[3];

			// Compute the file based document path
			CATUnicodeString docName = "AutoAccessAPI_fbSubAsm.CATProduct", docStorageName;
			rc = ComputeDataPath(docName, 1, docStorageName);

			if (SUCCEEDED(rc))
			{
				// Open in session the file based document
				CATDocument *pfileBasedDoc = NULL;
				rc = CATDocumentServices::Open(docStorageName, pfileBasedDoc);

				if (SUCCEEDED(rc) && pfileBasedDoc)
				{
					// Insert file based document under Instance document
					CATIProduct_var hNewInst;
					rc = InsertDocument(pBranchOneLeafDoc, pfileBasedDoc, hNewInst);

					if (SUCCEEDED(rc))
					{
						// SetEV5PersistencyMode parameters
						CATIPDMPersistency::VaultMode vaultMode = CATIPDMPersistency::VolatileExposed;  // Input param: The Vault Mode
						CATBoolean doPropagation = TRUE;                                                // Input param: Notification flag used to launch propagation of the Vault Mode on children documents

						// SetEV5PersistencyMode executing
						rc = SetEV5PersistencyMode(pfileBasedDoc, vaultMode, doPropagation);

						if (FAILED(rc)) cout << "OnOKSelected - **Error : SetEV5PersistencyMode() failed!" << endl;
					}
					else 
						cout << "OnOKSelected - **Error : Document insertion has failed!" << endl;
				}
				else
				{
					cout << "OnOKSelected - **Error : First insertion failed. Unable to open file based document from !" << docStorageName.ConvertToChar() << endl;
					rc = E_FAIL;
				}
			}
			else
			{
				cout << "OnOKSelected - **Error : Unable to compute the path of the first document!" << endl;
				rc = E_FAIL;
			}
		}


		//*Step4: Insert a file based Product under the loaded instance BranchTwoASMII.1
		//        Set PermanentBlackBox Vault Mode on the Product and its children
		//        using CAA API SetEV5PersistencyMode().
		if (SUCCEEDED(rc))
		{
			// Get the Document hosting the Reference of Instance BranchTwoASMII.1
			CATDocument *pBranchTwoLeafDoc = (*pOpenedDocsList)[5];

			// Compute the file based document path
			CATUnicodeString docName = "AutoAccessAPI_fbSubAsmBB.CATProduct", docStorageName;
			rc = ComputeDataPath(docName, 2, docStorageName);

			if (SUCCEEDED(rc))
			{
				// Open the file based document
				CATDocument *pfileBasedDoc = NULL;
				rc = CATDocumentServices::Open(docStorageName, pfileBasedDoc);

				if (SUCCEEDED(rc) && pfileBasedDoc)
				{
					// Insert file based document under Instance document
					CATIProduct_var hNewInst;
					rc = InsertDocument(pBranchTwoLeafDoc, pfileBasedDoc, hNewInst);

					if (SUCCEEDED(rc))
					{
						// SetEV5PersistencyMode parameters
						CATIPDMPersistency::VaultMode vaultMode = CATIPDMPersistency::PermanentBlackBox;  // Input param: The Vault Mode
						CATBoolean doPropagation = TRUE;                                                  // Input param: Notification flag used to launch propagation of the Vault Mode on children documents

						// SetEV5PersistencyMode executing
						rc = SetEV5PersistencyMode(pfileBasedDoc, vaultMode, doPropagation);

						if (FAILED(rc)) cout << "OnOKSelected - **Error : SetEV5PersistencyMode() failed!" << endl;
					}
					else 
						cout << "OnOKSelected - **Error : Document insertion has failed!" << endl;
				}
				else
				{
					cout << "OnOKSelected - **Error : Second insertion failed. Unable to open file based document from !" << docStorageName.ConvertToChar() << endl;
					rc = E_FAIL;
				}
			}
			else
			{
				cout << "OnOKSelected - **Error : Unable to compute the path of the second file based document!" << docStorageName.ConvertToChar() << endl;
				rc = E_FAIL;
			}
		}


		//*Step5: Edit the whole assembly. (loaded documents + file based inserted documents)
		//        Release the lock put on the root document during the load API execution
		//        Save the whole modified assembly directly calling the EV5Save command.
		if (SUCCEEDED(rc))
		{
			// Edit the root Document of the whole assembly
			// (i.e. the first document of the returned load-list in this specific scenario) 
			CATDocument *pDocToBeEdited = (*pOpenedDocsList)[1];
			if (pDocToBeEdited)
			{
				rc = EditDocument(pDocToBeEdited);

				if (FAILED(rc)) cout << "OnOKSelected - **Error : Unable to edit the assembly!" << endl;

				// Release the root Document (now that it's hold by the editor)
				pDocToBeEdited->ReleaseForLock();

				// Launch the EV5 Save interacive command
				CATCommand * pEV5SaveCmd = NULL;
				//rc = CATAfrStartCommand("LCATrueSave", pEV5SaveCmd);//ZUF commented
				rc = CATAfrStartCommand("EnoviaV5Save", pEV5SaveCmd);
				/* ZUF Commented for : "CAACV5AccessEV5DataAPI.sh" 
				ODT was KO because through this CATAfrStartCommand()VPMNav side SAVE was called for "LCATrueSave" attribute.
				i.e., CATImmDisconnectHeader.LCATrueSave.Title="Save in ENOVIA...";
				But, this ODT was connected through old interop.So, we should call Save of Old interop.
				i.e., CATPrdEnoviaV5CmdHeader.EnoviaV5Save.Help="Save data in ENOVIA V5 VPM Server...";  
				So, here we set "EnoviaV5Save" instead of "LCATrueSave"*/

				// At this point the CAAEnoviaV5SaveCmd command is interrupted by the EnoviaV5Save exclusive command!
				// i.e. After going out of this function, the Cancel method will be executed and our CAAEnoviaV5SaveCmd will end!
			}
			else
			{
				cout << "OnOKSelected - **Error : Root Doc in the load-list is empty!" << endl;
				rc = E_FAIL;
			}

			cout << "OnOKSelected - This will never be displayed!!!" << endl;
		}
	}

	cout << "<--CAAEnoviaV5SaveCmd::OnOKSelected(), RC = " << rc << endl;
	if (SUCCEEDED(rc)) 
		return TRUE;
	else 
		return FALSE;
}


//---------------------------------------------------------------------------------------
// Role:    Open in an editor the assembly of the root document given in input.
//
// Input:   [pToBeEditedDoc]     The Document to edit.
//
// Returns: [E_FAIL]        Unable to create the editor,
//                          Unable to create a window from the editor,
//                          An abnormal erro has happened,
//          [E_INVALIDARG]  The input document is NULL,
//          [S_OK]          Assembly of the root document has been successfully opened.
//---------------------------------------------------------------------------------------
HRESULT CAAEnoviaV5SaveCmd::EditDocument(CATDocument *pToBeEditedDoc)
{
  cout << "-->CAAEnoviaV5SaveCmd::EditDocument()" << endl;
  HRESULT rc = S_OK;

  if (pToBeEditedDoc)
  {
    int nbWind = 0;

    if (CATFrmLayout::GetCurrentLayout()) 
    {
      // Create Editor
      CATFrmEditor* pEditor = NULL;
      CATIEditor_var hPrdEditor(pToBeEditedDoc);
      if (!!hPrdEditor) pEditor = hPrdEditor->GetEditor();

      if (pEditor)  // Editor should now exists
      {
        // Get the nb of window attached to the editor
        pEditor->Init();
        nbWind = pEditor->GetWindowCount();

        if(nbWind == 0) // No window 
        {
          // Create Window
          CATFrmWindow *pWind = pEditor->CreateDefaultWindow();
          nbWind++;
        }

        // Get Document Display Name
        CATUnicodeString toBeEditedDocDisplayName;
        CATIDocEnvironment *pEV5DocEnv = CATDocEnvManager::GetEnvironment("ENOVIA5");

        if (pEV5DocEnv)
        {
          // Get Document Id
          CATIDocId *pToBeEditedDocId = NULL;
          rc = pToBeEditedDoc->GetDocId(&pToBeEditedDocId);

          if (SUCCEEDED(rc) && pToBeEditedDocId)
          {
            // Get Display Name
            rc = pEV5DocEnv->GetDocDisplayName(pToBeEditedDocId, toBeEditedDocDisplayName);
            pToBeEditedDocId->Release();

            // Trace Display name
            cout << "EditDocument - The Display Name of the document to be edited is: " << toBeEditedDocDisplayName.ConvertToChar()<< endl;
          }
          pEV5DocEnv->Release();
        }

        pEditor->SetWindowName(toBeEditedDocDisplayName);
      }
      else
      {
        cout << "EditDocument - **Error: Unable to create Editor from Document!" << endl;
        rc = E_FAIL;
      }
    }
    else
    {
      cout << "EditDocument - **Error: No Layout Instance found!" << endl;
      rc = E_FAIL;
    }
  
    cout << "EditDocument - Number of window attach to editor is: " << nbWind << endl;
    if (nbWind == 0) 
    {
      cout << "EditDocument - **Error: At this point at least one window should have been opened!" << endl;
      rc = E_FAIL;
    }
  }
  else
    rc = E_INVALIDARG;
  
  cout << "<--CAAEnoviaV5SaveCmd::EditDocument(), RC = " << rc << endl;
  return rc;
}


//---------------------------------------------------------------------------------------
// Role:    Get & return the Root Reference Product of the document given in input.
//
// Input:   [ipDoc]     The Document
// Output:  [ohRefProd] The Root Reference Product
//
// Returns: [E_FAIL]        Unable to retrieve the root reference product from the document,
//                          An abnormal erro has happened,
//          [E_INVALIDARG]  The input document is NULL,
//          [S_OK]          The Root Reference Product has been successfully retrieved.
//---------------------------------------------------------------------------------------
HRESULT CAAEnoviaV5SaveCmd::GetDocumentRootProdRef(CATDocument *ipDoc, CATIProduct_var &ohRefProd)
{
  cout << "-->CAAEnoviaV5SaveCmd::GetDocumentRootProdRef()" << endl;
  HRESULT rc = S_OK;

  if (ipDoc)
  {
    CATIDocRoots_var hLeafDoc = ipDoc;

    if (!!hLeafDoc)
    {
      CATListValCATBaseUnknown_var * pRootProductsList = hLeafDoc->GiveDocRoots();

      if (pRootProductsList)
      {
        if (pRootProductsList->Size() > 0)  // The list is supposed to contains only one element
        {
          ohRefProd = (*pRootProductsList)[1];
        }
        else
        {
          cout << "GetDocumentRootProdRef - **Error : Unable to retrieve Root Reference form the list!" << endl;
          rc = E_FAIL;
        }

        delete pRootProductsList; pRootProductsList = NULL;
      }
      else
      {
        cout << "GetDocumentRootProdRef - **Error : Unable to retrieve the Document Roots!" << endl;
        rc = E_FAIL;
      }
    }
    else
    {
      rc = E_FAIL;
      cout << "GetDocumentRootProdRef - **Error : Unable to map CATIDocRoots Interface on document!" << endl;
    }
  }
  else
    rc = E_INVALIDARG;

  cout << "<--CAAEnoviaV5SaveCmd::GetDocumentRootProdRef(), RC = " << rc << endl;
  return rc;
}


//---------------------------------------------------------------------------------------
// Role:    Display in traces the storage name of each CAtDocument contained in the input
//          list.
//
// Input:   [pDocsList]  List of documents
//
// Returns: [E_FAIL]        At least one document can't be retrieve from the list
//          [E_INVALIDARG]  The input list of document is empty
//          [S_OK]          The complete list has been traced.
//---------------------------------------------------------------------------------------
HRESULT CAAEnoviaV5SaveCmd::TraceDocumentName(CATLISTP(CATDocument)* pDocsList)
{
  cout << "-->CAAEnoviaV5SaveCmd::TraceDocumentName()" << endl;
  HRESULT rc = S_OK;

  if (pDocsList)
  {
    int nbOpenedDoc = pDocsList->Size();
    cout << "TraceDocumentName - The list contains " << nbOpenedDoc << " document(s)" << endl;

    if (nbOpenedDoc > 0)
    {
      for (int i = 1; i <= nbOpenedDoc; i++)
      {
        CATDocument *pCurDoc = (*pDocsList)[i];
        if (pCurDoc) 
        {
          CATUnicodeString docname = pCurDoc->StorageName();
          cout << "Document " << i << ". - " << docname.ConvertToChar() << endl;
          pCurDoc = NULL;
        }
        else 
        {
          cout << "TraceDocumentName - **Error : Unable to retrieve document nb. " << i << " from the list." << endl;
          rc = E_FAIL;
        }
      }
    }
  }
  else rc = E_INVALIDARG;

  cout << "<--CAAEnoviaV5SaveCmd::TraceDocumentName(), RC = " << rc << endl;
  return rc;
}

//---------------------------------------------------------------------------------------
// Role:    Insert a document under another one; i.e. instanciate the root reference
//          product of a document under the root reference product of another one (which
//          is supposed to be an assembly node !). The Instance Product created is returned.
//
// Input:   [ipDocFather]  Document destined to host [ipDocSon] document
//          [ipDocSon]     Document to be inserted under [ipDocFather] document
//
// Returns: [E_FAIL]        Failure encountered while instanciating Son Reference Product under father Reference Product,
//                          Unable to get Reference Product of the Son Document,
//                          Unable to get Reference Product of the Fahter Document,
//          [E_INVALIDARG]  At least one of the input documents is empty
//          [S_OK]          Insertion successfully done.
//---------------------------------------------------------------------------------------
HRESULT CAAEnoviaV5SaveCmd::InsertDocument(CATDocument* ipDocFather, CATDocument* ipDocSon, CATIProduct_var &ohInstProd)
{
  cout << "-->CAAEnoviaV5SaveCmd::InsertDocument()" << endl;
  HRESULT rc = S_OK;

  if (ipDocFather && ipDocSon)
  {
    // Get the Root Reference of the father Document
    CATIProduct_var hFatherDocRootProdRef;
    rc = GetDocumentRootProdRef(ipDocFather, hFatherDocRootProdRef);

    if (SUCCEEDED(rc) && !!hFatherDocRootProdRef)
    {
      // Get the Root Reference of the file son Document
      CATIProduct_var  hSonDocRootProdRef;
      rc = GetDocumentRootProdRef(ipDocSon, hSonDocRootProdRef);

      if (SUCCEEDED(rc) && !!hSonDocRootProdRef)
      {
        // Insert son Reference Product under father Reference Product
        ohInstProd = hFatherDocRootProdRef->AddProduct(hSonDocRootProdRef);

        if (!ohInstProd)
        {
          cout << "InsertDocument - **Error : Unable to instanciate son Reference Product under father Reference Product!" << endl;
          rc = E_FAIL;
        }
      }
      else
      {
        cout << "InsertDocument - **Error : Unable to Get Root product Reference of the son document!" << endl;
        rc = E_FAIL;
      }
    }
    else
    {
      cout << "InsertDocument - **Error : Unable to Get Root product Reference of the father document!" << endl;
      rc = E_FAIL;
    }
  }
  else
    rc = E_INVALIDARG;

  cout << "<--CAAEnoviaV5SaveCmd::InsertDocument(), RC = " << rc << endl;
  return rc;
}


//---------------------------------------------------------------------------------------
// Role:    Giving the name of a file based document and the vaultmode in which it 
//          is destined to be saved, this method computes the path that will allow to load
//          the document into the CV5 session.
//
// Input:   [iDocName]            Name of the document 
//                                (DocName.DocExtension)
//          [iDocFuturVaultMode]  Future Vault Mode of the document
//                                (1 : VolatileExposed, 2 : PermanentBlackBox)
//
//  Output: [oDocPath]            Path of the document
//
// Returns: [E_FAIL]        Computation failed,
//          [E_INVALIDARG]  At list one of the input arg is unproper,
//          [S_OK]          The path has been successfully computed.
//---------------------------------------------------------------------------------------
HRESULT CAAEnoviaV5SaveCmd::ComputeDataPath(CATUnicodeString &iDocName, int iDocFuturVaultMode, CATUnicodeString &oDocPath)
{
  cout << "-->CAAEnoviaV5SaveCmd::ComputeDataPath()" << endl;
  HRESULT rc = S_OK;

  if (iDocName.GetLengthInChar() > 0 && (iDocFuturVaultMode == 1 || iDocFuturVaultMode == 2))
  {
    static const char *pInputODT = CATGetEnv("ADL_ODT_IN");

    if (pInputODT) // Specific path computation for ODT Mode (Automatic replay of the CAA Use Case)
    {
      static const char *pSlash = CATGetEnv("ADL_ODT_SLASH");
      static const char *pODTName = CATGetEnv("ODT_LOG_NAME");

      oDocPath = pInputODT;
      oDocPath += pSlash;

      oDocPath += pODTName;
      oDocPath += ".rec";
      oDocPath += pSlash;

      oDocPath += "DATA";
      oDocPath += pSlash;

      if (iDocFuturVaultMode == 1)
        oDocPath += "VolatileExposed";
      else
        oDocPath += "PermanentBlackBox";
      oDocPath += pSlash;
    }
    else   // Path computation for hand replay mode
    {
      // Get the working directory
      char workingPath[255];
      getcwd(workingPath, 255);

      oDocPath = workingPath;
      cout <<"ComputeDataPath() - WorkingPath is set to "<< oDocPath.ConvertToChar() << endl;

#ifdef _WINDOWS_SOURCE
      if (iDocFuturVaultMode == 1)
        oDocPath += "\\CAAProductStructureE5i.edu\\InputData\\VolatileExposed\\";
      else
        oDocPath += "\\CAAProductStructureE5i.edu\\InputData\\PermanentBlackBox\\";
#else
      if (iDocFuturVaultMode == 1)
        oDocPath += "/CAAProductStructureE5i.edu/InputData/VolatileExposed/";
      else
        oDocPath += "/CAAProductStructureE5i.edu/InputData/PermanentBlackBox/";
#endif
    }

    oDocPath += iDocName;
    cout << "ComputeDataPath() - Computed path is: " << oDocPath.ConvertToChar() << endl;

    if (oDocPath.GetLengthInChar() == 0) rc = E_FAIL;
  }
  else 
    rc = E_INVALIDARG;

  cout << "<--CAAEnoviaV5SaveCmd::ComputeDataPath(), RC = " << rc << endl;
  return rc;
}
