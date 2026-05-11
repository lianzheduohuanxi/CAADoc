// COPYRIGHT Dassault Systemes 2002 

//Local Framework
#include "CAAMcaUdfLoftEditCreateCmd.h"
#include "CAAMcaUdfLoftDlg.h"            // Dialog box to display the inputs

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Lock and Unlock
#include "CATDocumentServices.h"         // Open, Remov
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"                 // Document which contains the user feature
                                         // to instantiate

//DialogEngine Framework
#include "CATFeatureImportAgent.h"       // To select a feature
#include "CATDialogTransition.h"         // To set NLS resource to the transition

// Dialog Framework
#include "CATDlgNotify.h"                // The dialog box in case of failure
#include "CATStateActivateNotification.h" // to distinguish begin/resume state in the command activation

//MechanicalCommands Framework
#include "CATIUdfFeatureUser.h"          // To return the type of the u.f.
#include "CATIUdfFeatureInstance.h"      // To modify the u.f.
#include "CATIUdfInstantiate.h"          // To instantiate a new u.f.
#include "CATIUdfFactory.h"              // To retrieve the u.f. to isntantiate

//MecModInterfaces Framework
#include "CATIPrtContainer.h"            // The root container
#include "CATIPrtPart.h"                 // The mechanical Part
#include "CATIGSMTool.h"                 // needed to manage GSM tools
#include "CATIBuildPath.h"

//ObjectSpecsModeler Framework
#include "CATIAlias.h"                   // To retrieve the name of the features

//ApplicationFrame Framework
#include "CATApplicationFrame.h"         // To retrieve the parent dialog boxes
#include "CATFrmEditor.h"                // To unset the repeat command

//System framework
#include "CATGetEnvValue.h"              // To retrieve the path of the 
                                         // user feature reference Part document

//Visualization framework
#include "CATPathElement.h"

//C++ Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAMcaUdfLoftEditCreateCmd);

//-------------------------------------------------------------------------
// Constructor in Edition Mode (0)
CAAMcaUdfLoftEditCreateCmd::CAAMcaUdfLoftEditCreateCmd(CATISpecObject *iObjectToEdit):
CATPrtPanelStateCmd ("CAAMcaUdfLoftEditCreateCmd", CATDlgEngOneShot, CATCommandModeExclusive,0),
_pInputDialogBox(NULL),_pAgentErrorDialogBox(NULL),_pFeatureAgent(NULL),_ErrorKey("NoError"),
_pErrorDialogBox(NULL),_pFirstPoint(NULL),_pSecondPoint(NULL),_pSelectedPath(NULL)
{
    HRESULT rc = E_FAIL ;

    if ( NULL != iObjectToEdit ) 
    {
        rc = InitCommand();

        if ( SUCCEEDED(rc) ) 
        {
           //Check that the feature implements CATIUdfFeatureUser and
           //that its type is CAAUdfLoft
           rc = CheckUserFeatureType(iObjectToEdit);
           if ( SUCCEEDED(rc) )
           {
              CATIUdfFeatureInstance_var spIUdfFeatureInstance = iObjectToEdit ;
              if (NULL_var != spIUdfFeatureInstance) 
              {
                 // Data member of the class CATMMUIStateCommand
                 // This data will be retrieved thanks to the
                 // GiveMyFeature method ( method of the same class)
                 // _Myfeature is a CATISpecObject_var 
                 //
                 _MyFeature = iObjectToEdit ;

                 // Retrieve the inputs          
                 CATBaseUnknown_var spBUknInput ;
                 CATBaseUnknown * pBUknInput = NULL ;
                 CATIAlias_var spAliasInput ;
                 
                 // first Input
                 spIUdfFeatureInstance->GetInput(1,spBUknInput);
 
                 spAliasInput = spBUknInput ;
                 CATUnicodeString FirstName = spAliasInput->GetAlias() ;

                 pBUknInput = (CATBaseUnknown *) spBUknInput ;
                 _pFirstPoint = new CATPathElement(pBUknInput);

                 // second input
                 spIUdfFeatureInstance->GetInput(2,spBUknInput);
  
                 spAliasInput = spBUknInput ;
                 CATUnicodeString SecondName = spAliasInput->GetAlias() ;

                 pBUknInput = (CATBaseUnknown *) spBUknInput ;
                 _pSecondPoint = new CATPathElement(pBUknInput);

                 // Initialize the edit dialog box
                 _pInputDialogBox->InitPointName(FirstName,SecondName);

                 // The end user can click the Ok and Preview buttons
                 _pInputDialogBox->SetOKSensitivity(CATDlgEnable);
                 _pInputDialogBox->SetPREVIEWSensitivity(CATDlgEnable);
                   
              }
           }
        }
    }
    if ( FAILED(rc) )
    {
       _ErrorKey = "InternalError";
    }

}

//-------------------------------------------------------------------------
// Constructor in Creation Mode (1)
CAAMcaUdfLoftEditCreateCmd::CAAMcaUdfLoftEditCreateCmd():
CATPrtPanelStateCmd ("CAAMcaUdfLoftEditCreateCmd", CATDlgEngOneShot, CATCommandModeExclusive,1),
_pInputDialogBox(NULL),_pAgentErrorDialogBox(NULL),_pFeatureAgent(NULL),_ErrorKey("NoError"),
_pErrorDialogBox(NULL),_pFirstPoint(NULL),_pSecondPoint(NULL),_pSelectedPath(NULL)
{
   HRESULT rc = InitCommand();
   if (FAILED(rc) )
   {
       _ErrorKey = "InternalError";
   }
}

//-------------------------------------------------------------------------

CAAMcaUdfLoftEditCreateCmd::~CAAMcaUdfLoftEditCreateCmd()
{
    if ( NULL != _pInputDialogBox )
    {
        _pInputDialogBox->RequestDelayedDestruction();
        _pInputDialogBox = NULL ;
    }

    if ( NULL != _pErrorDialogBox )
    {
        _pErrorDialogBox->RequestDelayedDestruction();
        _pErrorDialogBox = NULL ;
    }

    if ( NULL != _pAgentErrorDialogBox )
    {
       _pAgentErrorDialogBox->RequestDelayedDestruction();
       _pAgentErrorDialogBox = NULL ;
    }

    if ( NULL != _pFeatureAgent )
    {
       _pFeatureAgent->RequestDelayedDestruction();
       _pFeatureAgent = NULL ;
    }
    
    if ( NULL != _pFirstPoint )
    {
       _pFirstPoint->Release();
       _pFirstPoint = NULL ;
    }
    
    if ( NULL != _pSecondPoint )
    {
       _pSecondPoint->Release();
       _pSecondPoint = NULL ;
    }
    
    if ( NULL != _pSelectedPath )
    {
       _pSelectedPath->Release();
       _pSelectedPath = NULL ;
    }
}

//-------------------------------------------------------------------------

HRESULT  CAAMcaUdfLoftEditCreateCmd::InitCommand()
{
    HRESULT rc = E_FAIL ;

    CATApplicationFrame * pFrame = NULL ;
    pFrame = CATApplicationFrame::GetFrame();
    if ( NULL != pFrame )
    {
        if ( NULL != pFrame->GetMainWindow() )
        {
           _pInputDialogBox = new CAAMcaUdfLoftDlg(pFrame->GetMainWindow());
           _pInputDialogBox->Build();
           _pInputDialogBox->SetOKSensitivity(CATDlgDisable);
           _pInputDialogBox->SetPREVIEWSensitivity(CATDlgDisable);

           rc = S_OK ;
        }
    }  

    return rc ;
   
}

//-------------------------------------------------------------------------

CATDlgDialog*    CAAMcaUdfLoftEditCreateCmd::GiveMyPanel()
{
    return _pInputDialogBox ;
}

//-------------------------------------------------------------------------

HRESULT CAAMcaUdfLoftEditCreateCmd::CreateFeature()
{
    cout <<" CAAMcaUdfLoftEditCreateCmd::CreateFeature()" << endl;

    HRESULT rc = E_FAIL ;

    char * pCAAUdfLoftFile = NULL ;
    CATLibStatus result = ::CATGetEnvValue("CAAMcaUdfLoftFile",&pCAAUdfLoftFile);  
    if ( (CATLibError == result) || ( NULL == pCAAUdfLoftFile) )
    {
       _ErrorKey = "EnvVarNotSet";
    }else 
    {
       // Open the document which contains the user feature to instantiate
       CATDocument * pUdfDocument = NULL ;
       CATUnicodeString UdfDocumentName = pCAAUdfLoftFile ;

       free (pCAAUdfLoftFile) ;
       pCAAUdfLoftFile = NULL ;

       HRESULT rc = CATDocumentServices::OpenDocument(UdfDocumentName,pUdfDocument);
 
       if ( SUCCEEDED(rc) )
       {
          // to prevent a destruction 
          ::CATLockDocument(*pUdfDocument);
          
          // Retrieve the user feature to instantiate
          CATIUdfInstantiate * pIUdf = NULL ;
          rc = RetrieveTheUFRef(pUdfDocument, &pIUdf);                                
          if ( SUCCEEDED(rc) )
          {

             // Instantiate it
             rc = InstantiateTheUFRef(pIUdf);
             if (FAILED(rc) )
             {
                _ErrorKey = "InternalError";
             }
             pIUdf->Release();
             pIUdf = NULL ;
          } 
          else _ErrorKey = "UserFeatureReferenceNotFound";
    

          // Close the document AFTER the end of the instantiation
          rc = ::CATUnLockDocument(*pUdfDocument) ;
          pUdfDocument = NULL ;
          if ( FAILED(rc) ) _ErrorKey = "InternalError";

       }else _ErrorKey = "FileNoFound";

    }
   
    return rc ;
}

//-------------------------------------------------------------------------

HRESULT CAAMcaUdfLoftEditCreateCmd::RetrieveTheUFRef(CATDocument * iUFRefDocument, CATIUdfInstantiate ** oIUdf)
{
    HRESULT rc = E_FAIL ;

    if ( NULL == iUFRefDocument ) return rc ;

    CATInit *pInitOnDoc = NULL ;
    rc = iUFRefDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
    if ( SUCCEEDED(rc) )
    {
        CATIPrtContainer * pIPrtCont = NULL ;
        pIPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

        if ( NULL != pIPrtCont )
        {
           CATIUdfFactory *pIUdfFactory = NULL ;
           rc = pIPrtCont->QueryInterface(IID_CATIUdfFactory,(void **) &pIUdfFactory);
           if ( SUCCEEDED(rc) )
           {
              CATListValCATISpecObject_var * pListUserFeature = NULL ;
              pListUserFeature = pIUdfFactory->GetUserFeatureList();

              if ( NULL != pListUserFeature )
              {
                 int i= 1 ;
                 int nb = pListUserFeature->Size();
                 CATBoolean found = FALSE ;

                 rc = E_FAIL ;
                 while ( (i<= nb) && ( FALSE == found ) )
                 {
                    CATISpecObject_var spCurrentUserFeature = (*pListUserFeature)[i] ;
                    if ( NULL_var != spCurrentUserFeature )
                    {
                       rc = CheckUserFeatureType(spCurrentUserFeature);
 
                       if ( SUCCEEDED(rc) )
                       {
                          found = TRUE;
                          rc = spCurrentUserFeature->QueryInterface(IID_CATIUdfInstantiate,
                                                          (void **)oIUdf);
                       }
                    }
                    i++ ;
                 }
                 //SGA le 03/05/2007: MLK 216737
                 delete pListUserFeature;
                 pListUserFeature = NULL;
              }else rc = E_FAIL ;
              
              pIUdfFactory->Release();
              pIUdfFactory = NULL ;
           }
           pIPrtCont->Release();
           pIPrtCont = NULL ;
        }else rc = E_FAIL;

        pInitOnDoc->Release();
        pInitOnDoc = NULL ;
    }
 
    return rc ;
}

//-------------------------------------------------------------------------

HRESULT  CAAMcaUdfLoftEditCreateCmd::CheckUserFeatureType(CATISpecObject * iUserFeature)
{
    HRESULT rc = E_FAIL ;

    CATIUdfFeatureUser_var spIUdfFeatureUser = iUserFeature ;

    if ( (NULL_var != spIUdfFeatureUser) )
    {
       // Test if the type of the feature is CAAUdfLoft 
       CATUnicodeString CAAUdfLoft("CAAUdfLoft");
       CATUnicodeString Type ;          
       spIUdfFeatureUser->GetType(Type);
       if ( CAAUdfLoft == Type )
       {
          rc = S_OK ;
       }
    }

    return rc;
}

//-------------------------------------------------------------------------

HRESULT CAAMcaUdfLoftEditCreateCmd::InstantiateTheUFRef(CATIUdfInstantiate * iIUdf)
{
    HRESULT rc = E_FAIL ;
                  
    if ( NULL == iIUdf ) return rc ;

    // The MechanicalPart in the current document
    CATBaseUnknown * pBkunOnMechanicalPart = NULL ;

    CATIPrtPart_var spIPrtPartOnMechanicalPart = GetPart();
    if ( NULL_var != spIPrtPartOnMechanicalPart )
    {
       CATBaseUnknown_var spBkunOnMechanicalPart = spIPrtPartOnMechanicalPart ; 
       if ( NULL_var !=  spBkunOnMechanicalPart )
       {
          pBkunOnMechanicalPart = (CATBaseUnknown *) spBkunOnMechanicalPart ;
       }
    }
   
    if ( NULL !=  pBkunOnMechanicalPart )
    {
       CATPathElement PathInstantiate(pBkunOnMechanicalPart); 
       CATPathElement * FirstUIactiveObject1 = NULL ;
       CATBaseUnknown_var FirstDest1 = NULL_var ; 

       rc = iIUdf->SetDestinationPath(&PathInstantiate,
                                  FirstUIactiveObject1,
                                  FirstDest1);
 
       if ( SUCCEEDED(rc) )
       {
          rc = iIUdf->Instantiate(NULL_var);

          if ( SUCCEEDED(rc) )
          {
             CATBaseUnknown_var spInstance = NULL_var ;
             spInstance = iIUdf->GetInstantiated(iIUdf);

             if ( NULL_var != spInstance )
             { 
                 rc = iIUdf->EndInstantiate();

                 if ( SUCCEEDED(rc) )
                 {
                    _MyFeature = spInstance ;
                 }
             } else rc = E_FAIL ;
          }

          // In this case, FirstUIactiveObject1 is null 
          if ( NULL != FirstUIactiveObject1 )
          { 
             FirstUIactiveObject1->Release();
             FirstUIactiveObject1 = NULL ;
          }
       }
    } 
            
    return rc ;
}

//-------------------------------------------------------------------------

void CAAMcaUdfLoftEditCreateCmd::BuildGraph()
{
    cout <<" CAAMcaUdfLoftEditCreateCmd::BuildGraph" << endl;

    // Create the UF in creation mode
    // Keep the current feature to restore
    BeforeBuildGraph();

    if ( CATString("NoError")  != _ErrorKey )
    {  
        // An error is occured during the constructor step or the creation step.
        // A dialog box with a message explained the error type.
        //
        CATApplicationFrame * pFrame = NULL ;
        pFrame = CATApplicationFrame::GetFrame();
        if ( NULL != pFrame )
        {
           if ( NULL != pFrame->GetMainWindow() )
           {
 
              // The CATDlgWndModal style is mandatory. On NT, Notify windows
              // are always modal, not on Unix .
              // The CATDlgNfyOK style is mandatory, on NT it is not necessary
              // but on Unix it is.
              _pErrorDialogBox = new CATDlgNotify(pFrame->GetMainWindow(),
                                                            "Error",
                                              CATDlgNfyError|CATDlgNfyOK| CATDlgWndModal) ;
              //Build the keyword message
              CATUnicodeString ErrorMessage ;
              CATString KeyOfTheErrorMessage = "Error." + _ErrorKey ;

              //Retrieve the NLS text in the NLS file
              ErrorMessage = CATMsgCatalog::BuildMessage("CAAMcaUdfLoftEditCreateCmd",
                                        KeyOfTheErrorMessage,NULL,0,
                                        "Error in the CAAMcaUdfLoftEditCreateCmd command");
              // Set the NLS text
              _pErrorDialogBox->SetText(ErrorMessage);

              _pErrorDialogBox->SetVisibility(CATDlgShow);

              // When the end user clicks on the Ok button, the 
              // command finishes
              CATDialogState *pErrorState = GetInitialState("ErrorStateId");

              _pAgentErrorDialogBox = new CATDialogAgent("PanelError");
              pErrorState->AddDialogAgent(_pAgentErrorDialogBox); 
              
              _pAgentErrorDialogBox->AcceptOnNotify(_pErrorDialogBox,
                                                _pErrorDialogBox->GetNfyOKNotification());
              _pAgentErrorDialogBox->AcceptOnNotify(_pErrorDialogBox,
                                                _pErrorDialogBox->GetWindCloseNotification());

              AddTransition(pErrorState,GetCancelState(),
                            IsOutputSetCondition(_pAgentErrorDialogBox),
                            Action((ActionMethod) &CAAMcaUdfLoftEditCreateCmd::CloseErrorDialogBox));
           }
        }
    }else
    {
        // All is OK, we can choose new inputs for the user feature
        //
        _pInputDialogBox ->SetVisibility(CATDlgShow);
        
        // Display the role of the inputs in the panel
        CATIUdfFeatureInstance_var spIUdfFeatureInstance = GiveMyFeature() ;
        CATUnicodeString Role ;
        spIUdfFeatureInstance->GetInputRole(1,Role);
        _pInputDialogBox->SetRole(1,Role);
        spIUdfFeatureInstance->GetInputRole(2,Role);
        _pInputDialogBox->SetRole(2,Role);

        // This method,from CATMMUIPanelStateCommand, manages the OK, Cancel transitions
        CATDialogState * pInputState = GetInitialPanelState("InputStateId");

        _pFeatureAgent = new CATFeatureImportAgent("PointAgentId");
        _pFeatureAgent->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

        pInputState->AddDialogAgent(_pFeatureAgent);

        CATDialogTransition * pInputTransition = AddTransition(pInputState,pInputState,
                      AndCondition(IsOutputSetCondition(_pFeatureAgent),
                      Condition((ConditionMethod) & CAAMcaUdfLoftEditCreateCmd::CheckInput)),
                      Action((ActionMethod) &CAAMcaUdfLoftEditCreateCmd::SelectPoint));

        pInputTransition->SetResourceID("InputTransitionId");
    }
    
}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::CheckInput( void *UsefulData)
{
    CATBoolean rcode = FALSE;

    cout << "CAAMcaUdfLoftEditCreateCmd::CheckInput" << endl;

    // GetElementValue does not addref the returned pointer
    CATPathElement * pPathElt= _pFeatureAgent->GetValue();
    if ( NULL != pPathElt )
    {
       int i = _pInputDialogBox->GetActiveEditorNumber();

       CATIUdfFeatureInstance_var spFeatInst = GiveMyFeature();

       CATPathElement * pFilterPath = NULL ;
       HRESULT rc = spFeatInst->FilterInput(i,pPathElt,&pFilterPath);

       if ( SUCCEEDED(rc)  && ( NULL != pFilterPath) )
       {
          if (  0 != pFilterPath->GetSize() )
          {
             CATBaseUnknown * pLeaf = NULL ;
             pLeaf = (*pFilterPath)[pFilterPath->GetSize()-1];

             if ( NULL != pLeaf )
             {
                rcode = TRUE ;
 
                _pSelectedPath = pFilterPath ;
                _pSelectedPath->AddRef() ;
             }
          } 
          pFilterPath->Release();
          pFilterPath = NULL ;
       }   
    }

    if ( FALSE == rcode )
    {
       // To select a new feature
       _pFeatureAgent->InitializeAcquisition();
    }

    return rcode;
}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::SelectPoint( void *UsefulData)
{
    cout << "CAAMcaUdfLoftEditCreateCmd::SelectPoint" << endl;

    // _pSelectedPath has been valuated into the CheckInput method
    if ( NULL != _pSelectedPath )
    {
       int i = _pInputDialogBox->GetActiveEditorNumber();
       
       if ( i == 1 ) 
       {
           if ( NULL != _pFirstPoint ) _pFirstPoint->Release();
           _pFirstPoint  = _pSelectedPath ;
       }
       if ( i == 2 ) 
       {
           if ( NULL != _pSecondPoint ) _pSecondPoint->Release();
            _pSecondPoint = _pSelectedPath ;
       }

       CATBaseUnknown * pLeaf = NULL ;
       pLeaf = (*_pSelectedPath)[_pSelectedPath->GetSize()-1];

       if ( NULL != pLeaf )
       {
          CATIAlias * pIAlias = NULL ;
          HRESULT rc = pLeaf->QueryInterface(IID_CATIAlias,(void**)& pIAlias);
          if ( SUCCEEDED(rc) )
          {
             _pInputDialogBox->SetPointName(i,pIAlias->GetAlias());
                  
             pIAlias->Release();
             pIAlias = NULL ;
          }
       }
       // The pointer is kept by _pSecondPoint or _pFirstPoint
       _pSelectedPath = NULL ;
    }

    if ( (NULL != _pFirstPoint ) && ( NULL != _pSecondPoint) )
    {
        _pInputDialogBox->SetOKSensitivity(CATDlgEnable);
        _pInputDialogBox->SetPREVIEWSensitivity(CATDlgEnable);
    }

    // To enable a new selection with the same agent
    _pFeatureAgent->InitializeAcquisition();    

    return TRUE;
}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::OkAction( void *UsefulData)
{
    cout <<"CAAMcaUdfLoftEditCreateCmd::OkAction" << endl;

    CATIUdfFeatureInstance_var spIUdfFeatureInstance = GiveMyFeature() ;
    
    spIUdfFeatureInstance->SetNewInput(1,_pFirstPoint);
    spIUdfFeatureInstance->SetNewInput(2,_pSecondPoint);
    
    // If edition mode, the current feature is the previous current feature
    // In creation mode the current feature stays the same, it means the new UF
    //
    if (0 == GetMode())
    {
       CATBoolean IsInsideOrderedBody = FALSE ;
       IsUFInsideOrderedBody(IsInsideOrderedBody);
       if ( TRUE == IsInsideOrderedBody )
       {
          // method of CATMMUIStateCommand
          SetCurrentFeature(_spSpecObjOnPreviousCurrentFeat);
       }
    }

    // Call the OkAction of the CATPrtPanelStateCmd class,
    // this method will then call the update method
    CATBoolean rc = CATPrtPanelStateCmd::OkAction(UsefulData);

    return rc;
}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::PreviewAction( void *UsefulData)
{
    cout <<"CAAMcaUdfLoftEditCreateCmd::PreviewAction" << endl;
    
    CATIUdfFeatureInstance_var spIUdfFeatureInstance = GiveMyFeature() ;
    
    spIUdfFeatureInstance->SetNewInput(1,_pFirstPoint);
    spIUdfFeatureInstance->SetNewInput(2,_pSecondPoint);

    // Call the PreviewAction of the CATPrtPanelStateCmd class,
    // this method will then call the update method
    CATBoolean rc = CATPrtPanelStateCmd::PreviewAction(UsefulData);

    return rc;
}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::CancelAction( void *UsefulData)
{

    // If edition or creation mode, the current feature is 
    // the old current feature
    //
    CATBoolean IsInsideOrderedBody = FALSE ;
    IsUFInsideOrderedBody(IsInsideOrderedBody);
    if ( TRUE == IsInsideOrderedBody )
    {
       // method of CATMMUIStateCommand
       SetCurrentFeature(_spSpecObjOnPreviousCurrentFeat);
    }

    // Call the CancelAction of the CATPrtPanelStateCmd class
    CATBoolean rc = CATPrtPanelStateCmd::CancelAction(UsefulData);

    return rc;
}
//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::CloseErrorDialogBox( void *UsefulData)
{
    if ( NULL != GetEditor() )
    {
       GetEditor()->UnsetRepeatedCommand();
    }
    return TRUE;
}


//-------------------------------------------------------------------------

CATStatusChangeRC CAAMcaUdfLoftEditCreateCmd::Activate (CATCommand * iCmd,
                                                     CATNotification * iNotif)
{
    cout <<" CAAMcaUdfLoftEditCreateCmd::Activate" << endl;

    if ( NULL_var != GiveMyFeature() )
    {
       // Sets the UF as the current feature if it is included
       // in an ordered body.
       //
       CATBoolean IsInsideOrderedBody = FALSE ;
       IsUFInsideOrderedBody(IsInsideOrderedBody);
      
       if ( TRUE == IsInsideOrderedBody )
       {
          // method of CATMMUIStateCommand
          SetCurrentFeature(GiveMyFeature());  
       }
       
    }

    return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------

CATStatusChangeRC CAAMcaUdfLoftEditCreateCmd::Deactivate (CATCommand * iCmd,
                                                     CATNotification * iNotif)
{
    cout <<" CAAMcaUdfLoftEditCreateCmd::Deactivate" << endl;

    // Restores the old current feature
    // only if the UF is inside an ordered body
    //
    CATBoolean IsInsideOrderedBody = FALSE ;
    IsUFInsideOrderedBody(IsInsideOrderedBody);
    if ( TRUE == IsInsideOrderedBody )
    {
       // method of CATMMUIStateCommand
       SetCurrentFeature(_spSpecObjOnPreviousCurrentFeat);      
    }

    return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------
HRESULT CAAMcaUdfLoftEditCreateCmd::IsUFInsideOrderedBody(CATBoolean & oIsInsideOrderedBody )
{

    HRESULT rc = E_FAIL ;

    oIsInsideOrderedBody = FALSE ;
    
    if ( NULL_var != GiveMyFeature() )
    {
       // Retrieve the father of the CC 
       CATISpecObject * pFatherCC = NULL ;
       pFatherCC = GiveMyFeature()->GetFather();
       if ( NULL != pFatherCC )
       {
          // The father must be a GSMTool or an HybridBody
          // CATIGSMTool is implemented by the two kinds of feature
          //
          CATIGSMTool *piGSMToolFatherCC = NULL;
          rc = pFatherCC->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFatherCC);
          if ( SUCCEEDED(rc) )
          {
             // The father can be ordered or not 
             int IsOrdered = -1 ;
             piGSMToolFatherCC->GetType(IsOrdered) ;
             if ( 1 == IsOrdered )
             {
                oIsInsideOrderedBody = TRUE ;
             } 

             piGSMToolFatherCC->Release();
             piGSMToolFatherCC = NULL ;
          }
          pFatherCC->Release();
          pFatherCC = NULL ;
       }
    }

    return rc ;

}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::InitAction (void * iUseful)
{
    cout <<"CAAMcaUdfLoftEditCreateCmd::InitAction" << endl;
    return TRUE ;
}

//-------------------------------------------------------------------------

CATBoolean CAAMcaUdfLoftEditCreateCmd::BeforeBuildGraph ()
{
    cout <<" CAAMcaUdfLoftEditCreateCmd::BeforeBuildGraph " << endl;

    HRESULT rc = E_FAIL;

    //
    // 1- Retrieves the current feature 
    //
    CATISpecObject_var spSpecObjOnLocalPreviousCurrentFeat ;
    spSpecObjOnLocalPreviousCurrentFeat = GetCurrentFeature();

    //
    // 2- Creates the UF if creation mode
    //
    if ( 1 == GetMode() )
    {
       // Creation Mode, the user feature is created in the Activate method
       // to have the undo model in case of cancel     
       CreateFeature();
    }
       
    //
    // 3- If the UF is inside an ordered body, the current feature 
    //    is kept into a data member.
    //
    CATBoolean IsInsideOrderedBody = FALSE ;
    rc = IsUFInsideOrderedBody(IsInsideOrderedBody);
    if ( TRUE == IsInsideOrderedBody )
    {
       // Warning, in case of UF, the Instantiate method modifies the current 
       // feature, so the GetCurrentFeature method is called before 
       // the CreateFeature otherwise the step a is not necessary.
       //
       _spSpecObjOnPreviousCurrentFeat = spSpecObjOnLocalPreviousCurrentFeat ;
    }

    //
    // 4- Manage the current active path object
    //
    if ( (NULL_var != GiveMyFeature()) && (NULL !=GetEditor()) )
    {
       CATIBuildPath *piBuildPath = NULL;
       
       rc = GiveMyFeature()->QueryInterface( IID_CATIBuildPath, 
                                                       (void**) &piBuildPath );
        if ( SUCCEEDED(rc) && (NULL!=piBuildPath) )
        {
            CATPathElement Context = GetEditor()->GetUIActiveObject();
            CATPathElement * pPathElement = NULL ;
            rc = piBuildPath->ExtractPathElement(&Context,&pPathElement);

            if ( NULL != pPathElement )
            {
               SetActiveObject(pPathElement);

               pPathElement->Release();
               pPathElement = NULL ;

            }

            piBuildPath->Release(); 
            piBuildPath = NULL ;       
        }
    }
    
    return TRUE ;
}

