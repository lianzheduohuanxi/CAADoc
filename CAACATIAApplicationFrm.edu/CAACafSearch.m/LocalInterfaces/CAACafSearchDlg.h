#ifndef CAACafSearchDlg_h
#define CAACafSearchDlg_h

// COPYRIGHT DASSAULT SYSTEMES 1999
  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  It is the dialog box associated with the CAACafSearchCmd class. It 
//  displays a list of query and a list of context. 
//
//===========================================================================
// local Framework
class CAACafSearchCmd ;

// Dialog Framework
#include "CATDlgDialog.h"  //Needed to derive from CATDlgDialog

// Dialog Framework
class CATDlgEditor;
class CATDlgPushButton;
class CATDlgCombo;
class CATPSO ;

//InteractiveInterfaces
#include "CATIIniSearchContext.h"

// System Framework
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

class CAACafSearchDlg : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAACafSearchDlg.CATNLS 
  //    
  DeclareResource(CAACafSearchDlg,CATDlgDialog) ;

  public :

    CAACafSearchDlg(CATDialog * iParent, CAACafSearchCmd * iCmd);

    virtual ~CAACafSearchDlg(); 

    // Constructs the Dialog objects
    void Build();

    // SetResultQueryEditorText
    // ------------------------
    // This method modifies the text of the editor which displays
    // the count of element found by the search.
    //
    void SetResultQueryEditorText(CATUnicodeString iText);

    // GetCurrentContext
    // -----------------
    // This method returns the current context selected by the end-user. 
    //
    void GetCurrentContext(CATIIniSearchContext::Scope &oCurrentContext);

    // GetCurrentQuery
    // ---------------
    // This method returns the current criterion selected by the end-user. 
    //
    void GetCurrentCriterion(int & oCurrentCriterion);

  private : 

    //
    // EnterCB 
    // -------
    // A notification is sent to prevent the current state command that
    // the launch button has been clicked.
    //
    void LaunchBtn    (CATCommand          * iPublisher, 
                     CATNotification     * iNotification,
                     CATCommandClientData  iUsefulData);

    
    // ComboSelected 
    // -------------
    // This methods enables to de-highlighted the current elements in the PSO
    // and to reset the contents of the result editor.
    //
    void ComboSelected    (CATCommand          * iPublisher, 
                     CATNotification     * iNotification,
                     CATCommandClientData  iUsefulData);

    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafSearchDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafSearchDlg(const CAACafSearchDlg &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafSearchDlg & operator = (const CAACafSearchDlg &iObjectToCopy);

  private : 

      CATDlgEditor              * _pResultQueryEditor ;
      CATDlgPushButton          * _pLaunchBtn ;
      CATDlgCombo               * _pContextCombo ;
      CATDlgCombo               * _pCriteriaCombo ;

      CATListOfCATUnicodeString * _pCriteriaList ;

      CATPSO                    * _pPso ;
};
#endif
