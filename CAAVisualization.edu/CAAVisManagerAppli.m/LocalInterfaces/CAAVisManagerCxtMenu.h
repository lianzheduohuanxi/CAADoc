#ifndef CAAVisManagerCxtMenu_H
#define CAAVisManagerCxtMenu_H

// COPYRIGHT DASSAULT SYSTEMES 1999


//===========================================================================
// Abstract : 
// ----------
//    
//   
//===========================================================================
//
//  Usage :  
//  -------  
//     
//
//===========================================================================


//Local Framework
#include "CAAVisManagerCmdSelector.h"

// System FrameWork
class CATNotification;
#include "CATCommand.h" // to derive from

//Visualization FrameWork
#include "CATPathElement.h"
class CATViewer ;

// Dialog Framework
#include "CATDlgContextualMenu.h" 


class CAAVisManagerCxtMenu : public CATCommand
{

  // Declares the CAAVisManagerCxtMenu.CATNls file as the dialog 
  // message catalog
  //DeclareResource(CAAVisManagerCxtMenu, CATDlgContextualMenu)
  
  public :

    // Constructs a contextual menu from a command selector, a name, and a path.
    CAAVisManagerCxtMenu(CAAVisManagerCmdSelector *iFather, 
                       const CATString& iName, 
                       CATPathElement *iPath, 
                       CATViewer *iViewer);
  
    virtual ~CAAVisManagerCxtMenu();

    void Build() ;

  private :

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCxtMenu ();
        
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCxtMenu(const CAAVisManagerCxtMenu &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCxtMenu & operator = (const CAAVisManagerCxtMenu &iObjToCopy);

    void OnDeletingCB (CATCommand *iPublishCmd,  
        CATNotification *iNotification, CATCommandClientData iData);

    void OnAddingNewSetCB (CATCommand *iPublishCmd,  
        CATNotification *iNotification, CATCommandClientData iData);

    void OnEditingCB (CATCommand *iPublishCmd,  
        CATNotification *iNotification, CATCommandClientData iData);

    // Method called when an object is selected with the "Delete" menu
    // Thats update the model 
    //
    void DeleteChildren(CATBaseUnknown * iObject) ;

    void EditSet();

  private:  
     
    // the Model Path in the model tree
    CATPathElement _Path;

    // the viewer into which the contextual menu has been triggered
    CATViewer * _pViewer;

    // the father of the viewer into which a contextual menu is triggered
    CATCommand *_pOldFather;
     
    //Contextual Menu
    CATDlgContextualMenu *_pCxtMenu;

     
};

#endif
