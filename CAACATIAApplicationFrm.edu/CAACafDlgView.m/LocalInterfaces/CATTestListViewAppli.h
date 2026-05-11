// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef CATTestListViewAppli_H
#define CATTestListViewAppli_H

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//  This sample illustrates the use of the dialog object CATDlgTableView.
//  A CATDlgTableView is a Multi-List table which allow individual cell edit. 
//  CATDlgTableView is the view part of the MVC paradigm that allow the
//  creation of such multi-lists.
//    
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : mkrun -c CAACafDlgView 
//
//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Application class.
//  This is the main object in the process. It avoids writing a main function.
//  Event loop is managed automatically by deriving from 
//  CATInteractiveApplication. 
//
//  CATTestListViewAppli only creates the main window and subscribes to the 
//  window closing to terminate the application.  
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATInteractiveApplication (Dialog Framework)
//              CATApplication (System Framework)
//
//=============================================================================
//  Main Method:
//  ------------
//
//  BeginApplication: Contains the whole application code.
//
//
//=============================================================================
// CATIAApplicationFrame Framework

#include "CATInteractiveApplication.h" // To derive from

class CATTestListViewDocument;

class CATTestListViewAppli : public CATInteractiveApplication
{
  public :

    /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the BeginApplication method.
    */
    CATTestListViewAppli();
    virtual ~CATTestListViewAppli();
    
    /*
    * Application initialization. 
    * This method instantiates a CAADlgBurgerWindow, calls its build
    * method to initialize it and gives control of it to the
    * main event loop 
    */
    void BeginApplication();

    /*
    * Returns the application return code.
    */
    int  EndApplication();

  protected :
    CATTestListViewDocument *_doc;

  private :
    void DestroyApplication();
    
    /*
    * Copy constructor, not implemented
    * Set as private to prevent from compiler automatic creation as public.
    */
    CATTestListViewAppli(const CATTestListViewAppli &iObjectToCopy);
};
#endif
