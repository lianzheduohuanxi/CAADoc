// COPYRIGHT Dassault Systemes 2001
#ifndef CAADlgMoreRadioDlg_H
#define CAADlgMoreRadioDlg_H

// Dialog framework
#include "CATDlgDialog.h"   // To derive from

class  CATDlgFrame ; // For the private pointers


class CAADlgMoreRadioDlg: public CATDlgDialog
{
  // Declares the CAADlgMoreRadioDlg.CATNls file as the dialog message catalog
  DeclareResource( CAADlgMoreRadioDlg, CATDlgDialog )

  public:
      
      CAADlgMoreRadioDlg(CATDialog * pParentDlg);
      virtual ~CAADlgMoreRadioDlg();

      void Build ();

  private:

      // Method called when the end user clicks the OK or CANCEL button or closes the window
      virtual void CloseWindow (CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
 
      // Method called when the end user clicks the last radio button 
      virtual void OnRadioButtonDBRadBModifyNotification (CATCommand * iSendingCommand, 
                                                          CATNotification * iSentNotification, 
                                                          CATCommandClientData iUsefulData);

      // Method called when the end user clicks the middle radio button 
      virtual void OnRadioButtonDARadBModifyNotification (CATCommand * iSendingCommand, 
                                                          CATNotification * iSentNotification, 
                                                          CATCommandClientData iUsefulData);

      // Method called when the end user clicks the first radio button
      virtual void OnRadioButtonNDRadBModifyNotification (CATCommand * iSendingCommand, 
                                                          CATNotification * iSentNotification, 
                                                          CATCommandClientData iUsefulData);

      virtual CATStatusChangeRC Activate(
                            CATCommand * iFromClient,
                            CATNotification * iEvtDat);

      virtual CATStatusChangeRC Desactivate(
                            CATCommand * iFromClient,
                            CATNotification * iEvtDat);

      virtual CATStatusChangeRC Cancel(
                            CATCommand * iFromClient,
                            CATNotification * iEvtDat);

 private:

      CATDlgFrame      *      _pFrameDetailA ;
      CATDlgFrame      *      _pFrameDetailB ;

};

//----------------------------------------------------------------------

#endif
