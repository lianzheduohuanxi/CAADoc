// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAACafSearchCmd.h"
#include "CAACafSearchDlg.h" 

//DialogEngine Framework
#include "CATDialogTransition.h"
#include "CATPanelState.h"

//Visualization Framework 
#include "CATSO.h"    
#include "CATPSO.h"

//ApplicationFrame Framework
#include "CATFrmEditor.h"    
#include "CATApplicationFrame.h"    

// InteractiveInterfaces Framework
#include "CATIIniSearchCriterion.h"
#include "CATIIniSearchColorCriterion.h"
#include "CATIIniSearchVisibilityCriterion.h"
#include "CATIIniSearchWeightCriterion.h"
#include "CATIIniSearchDashedCriterion.h"
#include "CATIIniSearchLayerCriterion.h"
#include "CATIIniSearchNameCriterion.h"
#include "CATIIniSearchTypeCriterion.h"
#include "CATIIniSearchDimensionCriterion.h"
#include "CATIIniSearchStringCriterion.h"
#include "CATIIniSearchUserCriterion.h"
#include "CATIIniSearchAndCriterion.h"
#include "CATIIniSearchOrCriterion.h"
#include "CATIIniSearchExceptCriterion.h"
#include "CATIIniSearchServices.h"
#include "CATIIniSearchEngine.h"
#include "CATIIniSearchContext.h"
#include "CATIniSearchEnumeration.h"
#include "CATIniSearchColorCriterionComponent.h"
#include "CATIniSearchVisibilityCriterionComponent.h"
#include "CATIniSearchWeightCriterionComponent.h"
#include "CATIniSearchDashedCriterionComponent.h"
#include "CATIniSearchLayerCriterionComponent.h"
#include "CATIniSearchNameCriterionComponent.h"
#include "CATIniSearchTypeCriterionComponent.h"
#include "CATIniSearchDimensionCriterionComponent.h"
#include "CATIniSearchStringCriterionComponent.h"
#include "CATIniSearchUserCriterionComponent.h"
#include "CATIniSearchAndCriterionComponent.h"
#include "CATIniSearchOrCriterionComponent.h"
#include "CATIniSearchExceptCriterionComponent.h"
#include "CATIniSearchEngineComponent.h"
#include "CATIniSearchContextComponent.h"
#include "CATIniSearchServicesComponent.h"

//KnowledgeInterfaces Framework
#include "CATITypeDictionary.h"
#include "CATIType.h"

// System Framework
#include "CATCreateInstance.h"
#include "CATListOfCATUnicodeString.h"


//others
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAACafSearchCmd);

//----------------------LifeCycle's PART ----------------------------------
CAACafSearchCmd::CAACafSearchCmd():CATStateCommand("CAACafSearchCmdId"),
                        _daSearchDlg(NULL),
                        _pSearchDlg(NULL),
                        _pCriterionTextList (NULL),
                        _pIniSearchEngineOnCurrentEngine(NULL),
                        _pIniSearchContextOnCurrentContext(NULL),
                        _pIniSearchServices(NULL),
                       _pPso (NULL)

                        
{
  cout << "CAACafSearchCmd constructor" << endl ; 

  CATFrmEditor * pEditor = GetEditor();
  if ( NULL !=  pEditor )
  {
      _pPso = pEditor->GetPSO();
  }

  Init();
}

//-----------------------------------------------------------------------

CAACafSearchCmd::~CAACafSearchCmd()
{
  cout << "CAACafSearchCmd destructor" << endl ;

  if ( NULL != _daSearchDlg ) 
  {
     _daSearchDlg -> RequestDelayedDestruction() ;
     _daSearchDlg = NULL ;
  }

  if ( NULL != _pSearchDlg ) 
  {
     _pSearchDlg->RequestDelayedDestruction() ;
     _pSearchDlg = NULL ;
  }

  if ( NULL != _pIniSearchEngineOnCurrentEngine ) 
  {
     _pIniSearchEngineOnCurrentEngine->Release() ;
     _pIniSearchEngineOnCurrentEngine = NULL ;
  }

  if ( NULL != _pIniSearchContextOnCurrentContext ) 
  {
     _pIniSearchContextOnCurrentContext->Release() ;
     _pIniSearchContextOnCurrentContext = NULL ;
  }

  if ( NULL != _pIniSearchServices ) 
  {
     _pIniSearchServices->Release() ;
     _pIniSearchServices = NULL ;
  }

  if ( NULL != _pCriterionTextList )
  {
     delete _pCriterionTextList ;
     _pCriterionTextList = NULL ;
  }

  _pPso = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAACafSearchCmd::BuildGraph()
{
  cout << "CAACafSearchCmd BuildGraph" << endl ;
  
  // Retrieves the Dialog Object to create the Dialog box
  CATApplicationFrame * pFrame = NULL ;
  CATDialog * pParent = NULL ;
  pFrame = CATApplicationFrame::GetFrame() ;
  if ( NULL != pFrame )
  {
	   // pParent is the Dialog object dedicated to the current document. 
       //
       pParent = pFrame->GetMainWindow() ;
  }

  if ( NULL != pParent )
  {
     // 1- Creates the dialog box
     // -------------------------
     _pSearchDlg = new CAACafSearchDlg(pParent,this);
     _pSearchDlg->Build();

     // 2- Creates the agent
     // ---------------------

     _daSearchDlg      = new CATDialogAgent("SearchDlgId");

     // Agent behavior :
     // - CATDlgEngRepeat:
     //   After each Launch in the dialog box, the agent is always
     //   usable and the condition method IsLastModifiedAgentCondition 
     //   will be true when the end user reclicks the button.
     // 
     _daSearchDlg->SetBehavior(CATDlgEngRepeat); 
     
     // The agent will be valuated when the end user will click the Launch button
     // The dialog box sends the CAACafLaunchNextQueryNotification event.
     //
     _daSearchDlg->AcceptOnNotify(_pSearchDlg,"CAACafLaunchNextQueryNotification");


     // 3- Creates the State
     // ---------------------

     CATPanelState * stStateLaunch = new CATPanelState (this, "stStateLaunchId", _pSearchDlg);
     SetInitialState(stStateLaunch);
     stStateLaunch->AddDialogAgent(_daSearchDlg);

     // 4-Defines the transitions
     // -------------------------

     CATDialogTransition *pFirstTransition = AddTransition
     (
        stStateLaunch,
        stStateLaunch,
        IsLastModifiedAgentCondition(_daSearchDlg),
        Action((ActionMethod) & CAACafSearchCmd::LaunchQuery)
     );

     // As the state was created explicitely by "new" instead of the 
     // GetInitialState method, it must be released.
     stStateLaunch -> Release();
     stStateLaunch=NULL;

  }
}

//----------------------Action methods's PART -----------------------------

CATBoolean CAACafSearchCmd::LaunchQuery(void *iDummy)
{
  cout << "CAACafSearchCmd::LaunchQuery" << endl ;

  HRESULT rc = E_FAIL ;

  // Removes the last result in PSO
  if ( NULL != _pPso ) 
  {
     _pPso->Empty();
  }

  // Retrieves the current criterion to launch ( a value between 1 and the count of criterion)
  int CriterionIndex = -1 ;
  _pSearchDlg->GetCurrentCriterion(CriterionIndex);

  CATUnicodeString CriterionText = "";
  if ( NULL != _pCriterionTextList )
  {
     if ( (CriterionIndex >= 1) && (CriterionIndex <= _pCriterionTextList->Size()) )
     {
        CriterionText = (*_pCriterionTextList)[CriterionIndex];
     }
  }

  // Retrieves the current context
  CATIIniSearchContext::Scope ContextValue = CATIIniSearchContext::Everywhere ;
  _pSearchDlg->GetCurrentContext(ContextValue);

  // Launches the query 
  if (    ( CriterionIndex >= 1 ) &&
          (NULL != _pIniSearchServices) && 
          (NULL != _pIniSearchContextOnCurrentContext) && 
          (NULL != _pIniSearchEngineOnCurrentEngine) )
  {
     // Creates the criterion from its text
     CATIIniSearchCriterion * pIniSearchCriterion = NULL ;
     rc = _pIniSearchServices->DecodeStringToCriterion(CriterionText,
                                                        FALSE,
                                                        pIniSearchCriterion);
     if ( SUCCEEDED(rc) )
     {
        // Sets the scopes
        rc = _pIniSearchContextOnCurrentContext->SetScope(ContextValue);

        //Launches the query
        if ( SUCCEEDED(rc) )
        { 
           rc = _pIniSearchEngineOnCurrentEngine->SetCriterionAndContext(pIniSearchCriterion,
                                                              _pIniSearchContextOnCurrentContext);
           if ( SUCCEEDED(rc) )
           {
              rc = _pIniSearchEngineOnCurrentEngine->LaunchSearchOnDocument();      
           }
        } 

        pIniSearchCriterion->Release();
        pIniSearchCriterion = NULL ;
     }
  }
  
  // Displays the result 
  if ( SUCCEEDED(rc) )
  {
     CATSO * pListOfFoundObjects = NULL ;
     int nbelt = 0 ;
     _pIniSearchEngineOnCurrentEngine->GetFoundObjects(pListOfFoundObjects);

     if ( NULL != pListOfFoundObjects )
     {
        nbelt = pListOfFoundObjects->GetSize();
        
        // Highlights the found elements
        if ( NULL != _pPso )
        {
           for ( int i= 0 ; i < nbelt ; i++ )
           {
              CATBaseUnknown * pCurrent = (*pListOfFoundObjects)[i] ;
              if ( NULL != pCurrent )
              {
                 _pPso->AddElements(pCurrent);
              }
           }
           _pPso->EndAddElements();
        }
        pListOfFoundObjects->Release();
        pListOfFoundObjects = NULL ;
     }

     // Displays the count of found elements
     CATUnicodeString CountFound ;
     CountFound.BuildFromNum(nbelt);
     
     _pSearchDlg->SetResultQueryEditorText(CountFound) ;

  }else 
  {  _pSearchDlg->SetResultQueryEditorText("The search has failed");
  }
  
  // recycles the agent
  _daSearchDlg->InitializeAcquisition(); 

  return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAACafSearchCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAACafSearchCmd::Activate" << endl;

  if ( NULL != _pSearchDlg )
  {
     _pSearchDlg->SetVisibility(CATDlgShow);
  }

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAACafSearchCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAACafSearchCmd::Desactivate" << endl;

  if ( NULL != _pSearchDlg )
  {
     _pSearchDlg->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAACafSearchCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAACafSearchCmd::Cancel" << endl;

  if ( NULL != _pSearchDlg )
  {
     _pSearchDlg->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}


//-------------------------------------------------------------------------------
HRESULT CAACafSearchCmd::CreateCriteria()
{
   cout <<"        CAACafSearchCmd::CreateCriteria" << endl ;

   HRESULT rc = E_FAIL ;
  
   _pCriterionTextList = new CATListOfCATUnicodeString ;

   // General Search: Color = red ( Color Basic = 25 )
   // ------------------------------------------------
   //
   {
      CATIIniSearchColorCriterion * pIniSearchColorCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchColorCriterionComponent, NULL, 0,
                         IID_CATIIniSearchColorCriterion,
                         (void**)&pIniSearchColorCriterion);

      if ( SUCCEEDED(rc) )
      {
         unsigned int *Color = new unsigned int[3];
         Color[0]=255; Color[1]=0; Color[2]=0;
         CATUnicodeString ColorName;
         // Retrieves the name of the basic color 
         rc = pIniSearchColorCriterion->FindColorNameFromRGBColorCode(Color,ColorName);

         if(SUCCEEDED(rc))
         {
             // The name of the color will be displayed in the text of the criterion
             rc = pIniSearchColorCriterion->SetParameters(Color[0],Color[1],Color[2],
                                   CATIniSearchEnumeration::Equal,
                                   ColorName);
             delete []Color;
         }

         // Retrieves the CATIIniSearchCriterion interface pointer to
         // get and store the text of the criterion
         //
         CATIIniSearchCriterion * pSearchCriterion = NULL ;
         rc = pIniSearchColorCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

         if ( SUCCEEDED(rc) )
         {
             CATUnicodeString Text = "" ;
            pSearchCriterion->GetNLSQuery(Text);
            _pCriterionTextList->Append(Text);

            pSearchCriterion->Release();
            pSearchCriterion = NULL ;
         }
         
         // Releases the useless pointer
         pIniSearchColorCriterion->Release();
         pIniSearchColorCriterion = NULL ;
      }
   }

   // General Search: Color= (253,4,191) and visible elements
   // -------------------------------------------------------
   //
   {
      // Color Criterion
      CATIIniSearchColorCriterion * pIniSearchColorCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchColorCriterionComponent, NULL, 0,
                         IID_CATIIniSearchColorCriterion,
                         (void**)&pIniSearchColorCriterion);

      if ( SUCCEEDED(rc) )
      { 
         unsigned int *Color = new unsigned int[3];
         Color[0]=253; Color[1]=4; Color[2]=191;
 
         if( SUCCEEDED(rc) )
         {
            // The name of the color will be not displayed in the text of the 
            // criterion, only the color components.
            //
            rc = pIniSearchColorCriterion->SetParameters(Color[0],Color[1],Color[2],
                                   CATIniSearchEnumeration::Equal);
                                  

            delete []Color;
         }
      }

      // Visibility Criterion
      CATIIniSearchVisibilityCriterion * pIniSearchVisibilityCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchVisibilityCriterionComponent, NULL, 0,
                         IID_CATIIniSearchVisibilityCriterion,
                         (void**)&pIniSearchVisibilityCriterion);
      
          if(SUCCEEDED(rc))
          {
             rc = pIniSearchVisibilityCriterion->SetParameters(CATIIniSearchVisibilityCriterion::CATShowAttr,
                                                             CATIniSearchEnumeration::Equal);
          }
      }

      // And Criterion
      CATIIniSearchAndCriterion * pIniSearchAndCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchAndCriterionComponent, NULL, 0,
                         IID_CATIIniSearchAndCriterion,
                         (void**)&pIniSearchAndCriterion);
     
          if(SUCCEEDED(rc))
          {
             rc = pIniSearchAndCriterion->SetParameters(pIniSearchVisibilityCriterion,
                                                        pIniSearchColorCriterion);

             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchAndCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                   CATUnicodeString Text = "" ;
                   pSearchCriterion->GetNLSQuery(Text);
                   _pCriterionTextList->Append(Text);

                   pSearchCriterion->Release();
                   pSearchCriterion = NULL ;
                }
             }
          }
      }
             
      // Releases useless pointers
      if ( NULL != pIniSearchAndCriterion )
      {
          pIniSearchAndCriterion->Release();
          pIniSearchAndCriterion = NULL ;
      }
      if ( NULL != pIniSearchVisibilityCriterion )
      {
          pIniSearchVisibilityCriterion->Release();
          pIniSearchVisibilityCriterion = NULL ;
      }
      if ( NULL != pIniSearchColorCriterion )
      {
          pIniSearchColorCriterion->Release();
          pIniSearchColorCriterion = NULL ;
      }

   }

   // General Search: ( linetype = dotted ) and ( linewidth > .1 )
   // ------------------------------------------------------------
   //
   {  
      // Linetype (dashed) Criterion
      CATIIniSearchDashedCriterion * pIniSearchDashedCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchDashedCriterionComponent, NULL, 0,
                         IID_CATIIniSearchDashedCriterion,
                         (void**)&pIniSearchDashedCriterion);

      if ( SUCCEEDED(rc) )
      { 
         // You can retrieve the name of the linetype by using the macro
         // command and by using the Search command
         rc = pIniSearchDashedCriterion->SetParameters("Dotted",
                                   CATIniSearchEnumeration::Equal);
       
      }

      // linewidth (weight) Criterion
      CATIIniSearchWeightCriterion * pIniSearchWeightCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchWeightCriterionComponent, NULL, 0,
                         IID_CATIIniSearchWeightCriterion,
                         (void**)&pIniSearchWeightCriterion);

      if ( SUCCEEDED(rc) )
      { 
         float weight = .1f ;
         rc = pIniSearchWeightCriterion->SetParameters(weight,
                                   CATIniSearchEnumeration::Superior);
       
      }

      // And Criterion
      CATIIniSearchAndCriterion * pIniSearchAndCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchAndCriterionComponent, NULL, 0,
                         IID_CATIIniSearchAndCriterion,
                         (void**)&pIniSearchAndCriterion);
     
          if(SUCCEEDED(rc))
          {
             
             rc = pIniSearchAndCriterion->SetParameters(pIniSearchWeightCriterion,
                                                        pIniSearchDashedCriterion);

             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchAndCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                  CATUnicodeString Text = "" ;
                  pSearchCriterion->GetNLSQuery(Text);
                 _pCriterionTextList->Append(Text);

                 pSearchCriterion->Release();
                 pSearchCriterion = NULL ;
               }
             }
          }
      }

      //Releases useless pointers
      if ( NULL != pIniSearchAndCriterion )
      {
          pIniSearchAndCriterion->Release();
          pIniSearchAndCriterion = NULL ;
      }
      if ( NULL != pIniSearchWeightCriterion )
      {
          pIniSearchWeightCriterion->Release();
          pIniSearchWeightCriterion = NULL ;
      }
      if ( NULL != pIniSearchDashedCriterion )
      {
          pIniSearchDashedCriterion->Release();
          pIniSearchDashedCriterion = NULL ;
      }
   }

   // General Search: ( layer = 2 ) or ( layer = 3 )
   // ----------------------------------------------
   //
   {  
      // Layer Criterion (Second layer)
      CATIIniSearchLayerCriterion * pIniSearchLayer2Criterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchLayerCriterionComponent, NULL, 0,
                         IID_CATIIniSearchLayerCriterion,
                         (void**)&pIniSearchLayer2Criterion);

      if ( SUCCEEDED(rc) )
      { 
         CATUnicodeString LayerIndex ;
         LayerIndex.BuildFromNum(2);
         rc = pIniSearchLayer2Criterion->SetParameters(LayerIndex,
                                   CATIniSearchEnumeration::Equal);
       
      }

      // Layer Criterion (Third layer)
      CATIIniSearchLayerCriterion * pIniSearchLayer3Criterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchLayerCriterionComponent, NULL, 0,
                         IID_CATIIniSearchLayerCriterion,
                         (void**)&pIniSearchLayer3Criterion);

      if ( SUCCEEDED(rc) )
      { 
         CATUnicodeString LayerIndex ;
         LayerIndex.BuildFromNum(3);
         rc = pIniSearchLayer3Criterion->SetParameters(LayerIndex,
                                   CATIniSearchEnumeration::Equal);
       
      }

      // Or Criterion
      CATIIniSearchOrCriterion * pIniSearchOrCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchOrCriterionComponent, NULL, 0,
                         IID_CATIIniSearchOrCriterion,
                         (void**)&pIniSearchOrCriterion);
     
          if(SUCCEEDED(rc))
          {
             
             rc = pIniSearchOrCriterion->SetParameters(pIniSearchLayer2Criterion,
                                                       pIniSearchLayer3Criterion);

             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchOrCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                  CATUnicodeString Text = "" ;
                  pSearchCriterion->GetNLSQuery(Text);
                 _pCriterionTextList->Append(Text);

                 pSearchCriterion->Release();
                 pSearchCriterion = NULL ;
               }
             }
          }
      }

      //Releases useless pointers
      if ( NULL != pIniSearchOrCriterion )
      {
          pIniSearchOrCriterion->Release();
          pIniSearchOrCriterion = NULL ;
      }
      if ( NULL != pIniSearchLayer2Criterion )
      {
          pIniSearchLayer2Criterion->Release();
          pIniSearchLayer2Criterion = NULL ;
      }
      if ( NULL != pIniSearchLayer3Criterion )
      {
          pIniSearchLayer3Criterion->Release();
          pIniSearchLayer3Criterion = NULL ;
      }
   }

   // General Search: ( name = line* ) except ( name = *width* )
   // ----------------------------------------------------------
   // if name = line*Myline -> OK
   // if name = Line*Myline -> OK
   // if name = line*width03 -> OK
   // if name = line*Width03 -> KO
   //
   {
      // Name Criterion (Line*)
      CATIIniSearchNameCriterion * pIniSearchNameLineCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchNameCriterionComponent, NULL, 0,
                         IID_CATIIniSearchNameCriterion,
                         (void**)&pIniSearchNameLineCriterion);

      if ( SUCCEEDED(rc) )
      { 
         CATUnicodeString Name = "" ;
         CATUnicodeString StringToCorrect = "Line*" ;
         _pIniSearchServices->CorrectString(StringToCorrect,Name);

         CATBoolean CaseSensibility = FALSE ;
         rc = pIniSearchNameLineCriterion->SetParameters(Name,CaseSensibility,
                                   CATIniSearchEnumeration::Equal);
       
      }

      // Name Criterion (*Width*)
      CATIIniSearchNameCriterion * pIniSearchNameWidthCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchNameCriterionComponent, NULL, 0,
                         IID_CATIIniSearchNameCriterion,
                         (void**)&pIniSearchNameWidthCriterion);

      if ( SUCCEEDED(rc) )
      {  
         CATUnicodeString Name = "*Width*" ;
         CATBoolean CaseSensibility = TRUE ;
         rc = pIniSearchNameWidthCriterion->SetParameters(Name,CaseSensibility,
                                   CATIniSearchEnumeration::Equal);
       
      }

      // Except Criterion
      CATIIniSearchExceptCriterion * pIniSearchExceptCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchExceptCriterionComponent, NULL, 0,
                         IID_CATIIniSearchExceptCriterion,
                         (void**)&pIniSearchExceptCriterion);
     
          if(SUCCEEDED(rc))
          {
             
             rc = pIniSearchExceptCriterion->SetParameters(pIniSearchNameLineCriterion,
                                                       pIniSearchNameWidthCriterion);

             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchExceptCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                  CATUnicodeString Text = "" ;
                  pSearchCriterion->GetTransFormatQuery(Text);
                 _pCriterionTextList->Append(Text);

                 pSearchCriterion->Release();
                 pSearchCriterion = NULL ;
               }
             }
          }
      }

       //Releases useless pointers
      if ( NULL != pIniSearchExceptCriterion )
      {
          pIniSearchExceptCriterion->Release();
          pIniSearchExceptCriterion = NULL ;
      }
      if ( NULL != pIniSearchNameLineCriterion )
      {
          pIniSearchNameLineCriterion->Release();
          pIniSearchNameLineCriterion = NULL ;
      }
      if ( NULL != pIniSearchNameWidthCriterion )
      {
          pIniSearchNameWidthCriterion->Release();
          pIniSearchNameWidthCriterion = NULL ;
      }
   }


   // Retrieves the type dictionary
   // -----------------------------
   CATITypeDictionary_var pITypeDictionaryOnCurrentDic ;
   pITypeDictionaryOnCurrentDic = CATGlobalFunctions::GetTypeDictionary();

   // Advanced Search: Find all the Hole (in a Part document) whose 
   // Diameter attribute  is >= 10mm
   // -------------------------------------------------------------------
   //
   if ( NULL_var != pITypeDictionaryOnCurrentDic )
   {
      // Type Criterion
      CATIIniSearchTypeCriterion * pIniSearchTypeCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchTypeCriterionComponent, NULL, 0,
                         IID_CATIIniSearchTypeCriterion,
                         (void**)&pIniSearchTypeCriterion);

      if ( SUCCEEDED(rc) )
      { 
         // You retrieve the attribute name and the attribute package in the
         // 
         CATIType_var TypePtr;
         rc = pITypeDictionaryOnCurrentDic->FindTypeInPackage("Hole",
                                                              "PartDesign",
                                                              TypePtr);
         if ( SUCCEEDED(rc) )
         {
            // The last argument (CATPrtSearch) 
            rc = pIniSearchTypeCriterion->SetParameters(TypePtr,
                                   CATIniSearchEnumeration::Equal,"CATPrtSearch");
         }
                                  
      }

      // Dimension Criterion
      CATIIniSearchDimensionCriterion * pIniSearchDimensionCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchDimensionCriterionComponent, NULL, 0,
                         IID_CATIIniSearchDimensionCriterion,
                         (void**)&pIniSearchDimensionCriterion);

      if ( SUCCEEDED(rc) )
      {  
         CATUnicodeString AttributeInternalName = "Diameter" ;
         CATUnicodeString AttributeValue = "10.0mm" ;
         CATUnicodeString AttributeNLSName = "Diameter" ;

         rc = pIniSearchDimensionCriterion->SetParameters(AttributeInternalName, 
                                               AttributeValue,
                                               CATIniSearchEnumeration::SupEqual, 
                                               AttributeNLSName);
      }

      // And Criterion ( mandatory between a type criterion and another criterion )
      CATIIniSearchAndCriterion * pIniSearchAndCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchAndCriterionComponent, NULL, 0,
                         IID_CATIIniSearchAndCriterion,
                         (void**)&pIniSearchAndCriterion);
     
          if(SUCCEEDED(rc))
          {
             // The Type criterion must be the first of the and condition
             rc = pIniSearchAndCriterion->SetParameters(pIniSearchTypeCriterion,
                                                        pIniSearchDimensionCriterion);
                                                       

             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchAndCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                  CATUnicodeString Text = "" ;
                  pSearchCriterion->GetTransFormatQuery(Text);
                 _pCriterionTextList->Append(Text);

                 pSearchCriterion->Release();
                 pSearchCriterion = NULL ;
               }
             }
          }
      }

       //Releases useless pointers
      if ( NULL != pIniSearchAndCriterion )
      {
          pIniSearchAndCriterion->Release();
          pIniSearchAndCriterion = NULL ;
      }
      if ( NULL != pIniSearchDimensionCriterion )
      {
          pIniSearchDimensionCriterion->Release();
          pIniSearchDimensionCriterion = NULL ;
      }
      if ( NULL != pIniSearchTypeCriterion )
      {
          pIniSearchTypeCriterion->Release();
          pIniSearchTypeCriterion = NULL ;
      }
   }

   // Advanced Search: Find all the Product whose PartNumber attribute  
   // begins by the CAAPart string. 
   // ----------------------------------------------------------------------
   //
   if ( NULL_var != pITypeDictionaryOnCurrentDic )
   {
      // Type Criterion
      CATIIniSearchTypeCriterion * pIniSearchTypeCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchTypeCriterionComponent, NULL, 0,
                         IID_CATIIniSearchTypeCriterion,
                         (void**)&pIniSearchTypeCriterion);

      if ( SUCCEEDED(rc) )
      { 
         CATIType_var TypePtr;
         rc = pITypeDictionaryOnCurrentDic->FindTypeInPackage("Product",
                                                              "ProductPackage", 
                                                              TypePtr);
         
         if ( SUCCEEDED(rc) )
         {
            rc = pIniSearchTypeCriterion->SetParameters(TypePtr,
                                   CATIniSearchEnumeration::Equal,"CATProductSearch");  
         }
       
      }

      // String Criterion
      CATIIniSearchStringCriterion * pIniSearchStringCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchStringCriterionComponent, NULL, 0,
                         IID_CATIIniSearchStringCriterion,
                         (void**)&pIniSearchStringCriterion);

      if ( SUCCEEDED(rc) )
      {  
         CATUnicodeString AttributeInternalName = "PartNumber" ;
         CATUnicodeString AttributeNLSName = "Part Number" ;
         CATUnicodeString AttributeValue        = "CAAPart*" ;
         CATBoolean CaseSensibility             = FALSE ;
         rc = pIniSearchStringCriterion->SetParameters(AttributeInternalName, 
                                               AttributeValue,
                                               CaseSensibility ,
                                               CATIniSearchEnumeration::Equal,
                                               AttributeNLSName);  
       
      }

      // And Criterion
      CATIIniSearchAndCriterion * pIniSearchAndCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchAndCriterionComponent, NULL, 0,
                         IID_CATIIniSearchAndCriterion,
                         (void**)&pIniSearchAndCriterion);
     
          if(SUCCEEDED(rc))
          {
             
             rc = pIniSearchAndCriterion->SetParameters(pIniSearchTypeCriterion,
                                                        pIniSearchStringCriterion);
                                                       
             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchAndCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                  CATUnicodeString Text = "" ;
                 pSearchCriterion->GetTransFormatQuery(Text);
                 _pCriterionTextList->Append(Text);

                 pSearchCriterion->Release();
                 pSearchCriterion = NULL ;
               }
             }
          }
      }

       //Releases useless pointers
      if ( NULL != pIniSearchAndCriterion )
      {
          pIniSearchAndCriterion->Release();
          pIniSearchAndCriterion = NULL ;
      }
      if ( NULL != pIniSearchStringCriterion )
      {
          pIniSearchStringCriterion->Release();
          pIniSearchStringCriterion = NULL ;
      }
      if ( NULL != pIniSearchTypeCriterion )
      {
          pIniSearchTypeCriterion->Release();
          pIniSearchTypeCriterion = NULL ;
      }
   }

   // Advanced Search: Find all the Product whose the CAAAttr attribute  
   // (a user attribute) is inferior and equal to .1
   // ------------------------------------------------------------------
   //
   if ( NULL_var != pITypeDictionaryOnCurrentDic )
   {
      // Type Criterion
      CATIIniSearchTypeCriterion * pIniSearchTypeCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchTypeCriterionComponent, NULL, 0,
                         IID_CATIIniSearchTypeCriterion,
                         (void**)&pIniSearchTypeCriterion);

      if ( SUCCEEDED(rc) )
      { 
         CATIType_var TypePtr;
         rc = pITypeDictionaryOnCurrentDic->FindTypeInPackage("Product","ProductPackage", TypePtr);
         
         if ( SUCCEEDED(rc) )
         {
            rc = pIniSearchTypeCriterion->SetParameters(TypePtr,
                                   CATIniSearchEnumeration::Equal,"CATProductSearch");  
         }
       
      }

      // String Criterion
      CATIIniSearchUserCriterion * pIniSearchUserCriterion = NULL ;
      rc = ::CATCreateInstance(CLSID_CATIniSearchUserCriterionComponent, NULL, 0,
                         IID_CATIIniSearchUserCriterion,
                         (void**)&pIniSearchUserCriterion);

      if ( SUCCEEDED(rc) )
      {  
         CATUnicodeString AttributeInternalName = "CAAAttr" ;
         CATUnicodeString AttributeValue = ".1" ;
         rc = pIniSearchUserCriterion->SetParameters(AttributeInternalName, 
                                               AttributeValue,
                                               CATIniSearchEnumeration::InfEqual);  
      
      }

      // And Criterion
      CATIIniSearchAndCriterion * pIniSearchAndCriterion = NULL ;
      if(SUCCEEDED(rc))
      {
          rc = ::CATCreateInstance(CLSID_CATIniSearchAndCriterionComponent, NULL, 0,
                         IID_CATIIniSearchAndCriterion,
                         (void**)&pIniSearchAndCriterion);
     
          if(SUCCEEDED(rc))
          {
             // The Type criterion must be the first of the and condition
             rc = pIniSearchAndCriterion->SetParameters(pIniSearchTypeCriterion,
                                                        pIniSearchUserCriterion );
                                                       

             if(SUCCEEDED(rc))
             {
                CATIIniSearchCriterion * pSearchCriterion = NULL ;
                rc = pIniSearchAndCriterion->QueryInterface(IID_CATIIniSearchCriterion,
                                                  (void**) &pSearchCriterion);

                if ( SUCCEEDED(rc) )
                {
                  CATUnicodeString Text = "" ;
                  pSearchCriterion->GetNLSQuery(Text);
                 _pCriterionTextList->Append(Text);

                 pSearchCriterion->Release();
                 pSearchCriterion = NULL ;
               }
             }
          }
      }

       //Releases useless pointers
      if ( NULL != pIniSearchAndCriterion )
      {
          pIniSearchAndCriterion->Release();
          pIniSearchAndCriterion = NULL ;
      }
      if ( NULL != pIniSearchUserCriterion )
      {
          pIniSearchUserCriterion->Release();
          pIniSearchUserCriterion = NULL ;
      }
      if ( NULL != pIniSearchTypeCriterion )
      {
          pIniSearchTypeCriterion->Release();
          pIniSearchTypeCriterion = NULL ;
      }
   }

   return rc ;
}

//-------------------------------------------------------------------------------
void CAACafSearchCmd::Init()
{
    cout <<" CAACafSearchCmd::Init" << endl;

    // Creates the component to launch queries
    ::CATCreateInstance(CLSID_CATIniSearchEngineComponent, NULL, 0, 
                                     IID_CATIIniSearchEngine,
                                     (void**)&_pIniSearchEngineOnCurrentEngine);

    // Creates the component to set a context
    ::CATCreateInstance(CLSID_CATIniSearchContextComponent, NULL, 0, 
                                     IID_CATIIniSearchContext,
                        (void**)&_pIniSearchContextOnCurrentContext);

    // Creates the component to use search services
    ::CATCreateInstance(CLSID_CATIniSearchServicesComponent, NULL, 0, 
                                     IID_CATIIniSearchServices,
                                     (void**)&_pIniSearchServices);


    // Creates all the queries 
    CreateCriteria() ;

}

//-------------------------------------------------------------------------

HRESULT CAACafSearchCmd::GetCriteriaText(CATListOfCATUnicodeString ** oQueriesTextList)
{
   HRESULT rc = S_OK;

   if ( (NULL == oQueriesTextList) || (NULL ==_pCriterionTextList)  ) return E_FAIL;

   *oQueriesTextList = new CATListOfCATUnicodeString ;

   CATUnicodeString EmptyText = "";
   CATUnicodeString CurrentText ;
   for ( int i = 1 ; i <= _pCriterionTextList->Size(); i++)
   {
      CurrentText = (*_pCriterionTextList)[i] ;
      
      (*oQueriesTextList)->Append(CurrentText) ;
      
   }

   return rc ;
}

