// COPYRIGHT Dassault Systemes 2003
#ifndef CAADlgMoreButtonDlg_H
#define CAADlgMoreButtonDlg_H

// Dialog framework
#include "CATDlgDialog.h"   // To derive from
class  CATDlgFrame ;        // For the private pointer

// System framework
#include "CATUnicodeString.h"
#include "CATBoolean.h"

class CAADlgMoreButtonDlg: public CATDlgDialog
{
  // Declares the CAADlgMoreButtonDlg.CATNls file as the dialog message catalog
  DeclareResource( CAADlgMoreButtonDlg, CATDlgDialog )

  public:

      CAADlgMoreButtonDlg(CATDialog * pParentDlg);
      virtual ~CAADlgMoreButtonDlg();

      void Build ();

 
  private:

      // Method called when the end user clicks the OK or CANCEL button or closes the window
      virtual void CloseWindow (CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);

      // Method called when the end user clicks the More/Less button
      virtual void OnPushButtonMorePushBActivateNotification (CATCommand * iSendingCommand, 
                                                              CATNotification *  iSentNotification, 
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

      CATBoolean             _IsMoreWindowOpen;
      CATDlgFrame     *      _pFrameRightMore;
      CATUnicodeString       _MoreMsg ;
      CATUnicodeString       _LessMsg ;

};

//----------------------------------------------------------------------

#endif
