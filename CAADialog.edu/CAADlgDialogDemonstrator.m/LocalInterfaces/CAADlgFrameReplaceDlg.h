// COPYRIGHT Dassault Systemes 2003
#ifndef CAADlgFrameReplaceDlg_H
#define CAADlgFrameReplaceDlg_H

// Dialog framework
#include "CATDlgDialog.h"   // To derive from

class  CATDlgFrame ;        // For the private pointer
class  CATDlgCombo ;        // For the private pointer
class  CATDlgSpinner ;      // For the private pointer

// System framework
class CATSettingRepository ; // To manage values


class CAADlgFrameReplaceDlg: public CATDlgDialog
{
  // Declares the CAADlgFrameReplaceDlg.CATNls file as the dialog message catalog
  DeclareResource( CAADlgFrameReplaceDlg, CATDlgDialog )

  public:

      CAADlgFrameReplaceDlg(CATDialog * pParentDlg);
      virtual ~CAADlgFrameReplaceDlg();

      void Build ();

 
  private:

      // Method called when the end user selects in the combo
      virtual void OnComboSelectNotification (CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);

      // Method called when the end user clicks the OK or CANCEL button 
      // or closes the window
      virtual void CloseWindowOK (CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);

      virtual void CloseWindow (CATCommand * iSendingCommand, 
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

     // The list of frames to switch between 
     CATDlgFrame   * _pListFrame[3];
     CATDlgCombo   * _pComboPointType ;
     CATDlgSpinner * _pSpinnerX ;
     CATDlgSpinner * _pSpinnerY ;
     CATDlgSpinner * _pSpinnerZ ;

     // The current choice in the combo
     int           _CurrentSelection ;

     // To keep the values 
     CATSettingRepository * _pSettingFrameReplace ;

};

//----------------------------------------------------------------------

#endif
