#ifndef CAACafSearchCmd_h
#define CAACafSearchCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  State command which creates some queries and displayes a dialog box
//  to choose a criterion and a context and enables the end user to launch the query.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of a Search AI
//     - Use of a CATPanelState
//
//  Usage:
//
//     Select a criterion and a context in the dialog box and then launch the query.
//
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// DialogEngine Framework 
class CATDialogAgent ;        //Dialog agent 

// InteractiveInterfaces Framework 
class CATIIniSearchEngine ;   
class CATIIniSearchContext;
class CATIIniSearchServices;

// Visualization Framework 
class CATPSO ;

// System Framework
#include "CATListOfCATUnicodeString.h" 

// Local Framework
class CAACafSearchDlg ; 


class CAACafSearchCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAACafSearchCmd.CATNls  
  // 

  CmdDeclareResource(CAACafSearchCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAACafSearchCmd();
    virtual ~CAACafSearchCmd();  

    // Activate
    // --------
    // Called when the command selector gives the focus to this command. 
    // Two cases can happen:
    //  -The command starts from the beginning.
    //  -The command restarts at the state that was current when a shared command 
    //   took the focus from it.
    //
    // These two cases can be distinguished thanks to the notification type.
    //
    CATStatusChangeRC Activate   (CATCommand * iCmd,CATNotification * iNotif);

    // Cancel
    // --------
    // Called when the command selector gives the focus to an exclusive command,
    // or if this command completes. In this latter case, the focus is given to 
    // the default command (usually Select). 
    // You should not take care of the command destruction. This is done
    // by the dialog state command engine.
    // 
    // If the end user selects this command again, it is recreated. 
    //
    CATStatusChangeRC Cancel     (CATCommand * iCmd,CATNotification * iNotif);

    // Deactivate
    // ----------
    // Called when the command selector freezes this command to give
    // the focus to a shared command. When the shared command completes, this
    // frozen command will be reactivated from its current state. 
    //  
    CATStatusChangeRC Desactivate(CATCommand * iCmd,CATNotification * iNotif);

    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    //
    //
    virtual void BuildGraph() ;

    // LaunchQuery
    // -----------
    // The query is launched in taken account of the current criterion and
    // the current context. The count of found element is displayed in 
    // a dialog box editor, and the elements are set in the PSO 
    //
    CATBoolean  LaunchQuery (void * iDummy);


    // GetCriteriaText
    // --------------
    // This method is called by the dialog box to retrieve the text of each criterion
    // to display in the combo.
    //
    HRESULT GetCriteriaText(CATListOfCATUnicodeString ** oCriteriaTextList);

  private :

    // Init
    // --------------
    // This method is called in the class constructor. It builds the 
    // search components: the search engine , the services and context components, and
    // calls the CreateCriteria method.
    // 
    void Init();

    // CreateCriteria
    // --------------
    // This method is called by the Init method to build all the criteria. Each
    // criterion is created and deleted just after to have kept its text. Thanks to this text
    // the criteria will be re-created to be launch.
    //
    HRESULT CreateCriteria();



    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafSearchCmd(const CAACafSearchCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafSearchCmd & operator = (const CAACafSearchCmd &iObjectToCopy);

  private :
    // Dialog box to display the criteria and its result
    CAACafSearchDlg                * _pSearchDlg;

    // Dialog agent to be inform that the Launch button has been selected
    CATDialogAgent                 * _daSearchDlg ; 
 
    // Interfaces on the components created in the Init method
    CATIIniSearchEngine            * _pIniSearchEngineOnCurrentEngine ;
    CATIIniSearchContext           * _pIniSearchContextOnCurrentContext ;
    CATIIniSearchServices          * _pIniSearchServices ;
    
    // The list of all the queries created in the CreateQueries method
    CATListOfCATUnicodeString      * _pCriterionTextList ;

    // The result is pre-highlighted 
    CATPSO                         * _pPso ;
};
#endif
