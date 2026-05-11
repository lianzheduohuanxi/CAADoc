#ifndef CAAMmrDatumWindowCmd_h
#define CAAMmrDatumWindowCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Command allow to demonstrate how to acces to CreateDatum Settings handle in Part/GSD/FreeStyle..
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Command displays a dialog box enabling 

//    1- to get the status of the Setting 
//     Current State field indicates 
//      - NoDatumCreation 
//      - DatumCreationPermanent
//      - DatumCreationTemporary 
//
//    2- to modify the value and to react on this modification 
//      Combo allow to choose a new valkue, once done Apply validate the modification 
//      ==> Then the command reat to the modification event and the CurrentState fielad is updated 
//
//===========================================================================
//  Inheritance:
//  ------------
//           CATDlgDialog (Dialog Framework)    
//              CATDialog   (Dialog Framework)
//                  CATCommand  (System Framework)
//                      CATBaseUnknown (System Framework)
//
//===========================================================================

// Dialog Framework
#include "CATDlgDialog.h"     // Needed to derive from CATDlgDialog

// System Framework
#include "CATEventSubscriber.h" // to receice callback


//Visualization Framework
class CATDlgSelectorList ;
class CATDlgCombo;

class CATFrmEditor;
class CATIMmiPartInfrastructurePreferencesAtt;

class CAAMmrDatumWindowCmd : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAMmrDatumWindowCmd.CATNls 
  //    
  DeclareResource(CAAMmrDatumWindowCmd, CATDlgDialog);
  
  public :
    
    // Constructor
    // -----------
    // Creates the dialog widgets
    //
    CAAMmrDatumWindowCmd();

    virtual ~CAAMmrDatumWindowCmd();  
	
  private : 
 
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMmrDatumWindowCmd(const CAAMmrDatumWindowCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMmrDatumWindowCmd & operator = (const CAAMmrDatumWindowCmd &iObjectToCopy);
    //
    // Close
    // ----------
    // The end user clicks Close.
    // 
    HRESULT Build();
    
    HRESULT InitWindow();
    //
    // Apply 
    // ----------
    // The end user clicks Close.
    // 
    void Apply (CATCommand              *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);


     //
    // Close
    // ----------
    // The end user clicks Close.
    // 
    void Close(CATCommand              *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);

    // EditorClose
    // -----------
    // Enable the destruction of the command when the editor is closed
    // and the command is always active.

    void EditorClose          (CATCallbackEvent  iEvent,
                           void             *iFrom,
                           CATNotification  *iNotification,
                           CATSubscriberData iData,
                           CATCallback       iCallBack );
    void ReceiveDatumModify    (CATCallbackEvent  iEvent,
                           void             *iFrom,
                           CATNotification  *iNotification,
                           CATSubscriberData iData,
                           CATCallback       iCallBack );


  private : 

     // To acces to Interface to CreateDatum component 
     CATIMmiPartInfrastructurePreferencesAtt* _piCATIMmiPartInfrastructurePreferencesAtt;

     // To handle dialog object 
     CATDlgSelectorList    * _pDatumCurrentState ;
     CATDlgCombo           * _pDatumChoice       ;
     
     // To keep Strinfg value for panel fields 
     CATUnicodeString DatumValueMode[3];
     
     // To delete the command when the editor launching it is closed
     CATFrmEditor      * _pEditor ;
};
#endif
