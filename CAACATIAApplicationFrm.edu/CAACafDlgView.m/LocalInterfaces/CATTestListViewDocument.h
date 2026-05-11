// COPYRIGHT Dassault Systemes 2007

#ifndef CATTestListViewDocument_H
#define CATTestListViewDocument_H

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Window of the application which contains alls Dialog's object. 
// 
//=============================================================================
//  Inheritance:
//  ------------
//           CATDlgDocument (Dialog Framework)
//             CATDlgWindow (Dialog Framework)
//               CATDialog (Dialog Framework)
//                 CATCommand (System Framework)
//                   CATEventSubscriber (System Framework)
//                     CATBaseUnknown (System Framework)
//
//=============================================================================

#include "CATDlgDocument.h"
#include "list.h"

class CATTestListViewAppli;
class CATCommand;
class CATNotification;

class CATTestListViewDocument : public CATDlgDocument
{
  public :
    CATTestListViewDocument(CATTestListViewAppli *father, const CATString&, CATDlgStyle style=NULL, const int savevrml = 0);
    virtual ~CATTestListViewDocument();

  private :
    void exit ( CATCommand *, CATNotification *, CATCommandClientData);

    void CreateSampleProto(CATCommand *, CATNotification *, CATCommandClientData data);

    /*
    * These member functions are Dialog callbacks. They are invoked
    * when events occur in the widgets of the dialog window.
    */

    void OnCloseListCB(CATCommand * from, CATNotification *, CATCommandClientData);
    
    /*
    * Callback function invoked on selection in the left-hand side table
    */
    void OnSelectionCB01(CATCommand * from, CATNotification *, CATCommandClientData);

    /*
    * Callback function invoked on selection in the right-hand side table
    */
    void OnSelectionCB02(CATCommand * from, CATNotification *, CATCommandClientData);
    
    /*
    * Callback function invoked on modifying a cell content in the left-hand side table
    */
    void OnForceEditCB(CATCommand * from, CATNotification *, CATCommandClientData);
    void OnForceMaxiCB(CATCommand * from, CATNotification *, CATCommandClientData);

    CATTestListViewAppli *_Appli;
};
#endif
