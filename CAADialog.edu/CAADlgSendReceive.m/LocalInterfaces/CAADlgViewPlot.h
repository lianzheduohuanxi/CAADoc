#ifndef CAADlgViewPlot_H
#define CAADlgViewPlot_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//==============================================================================
//  Abstract of the class:
//  ---------------------
//
//  Command that can be active, that is, that can take the focus.
//
//==============================================================================

// System Framework
#include "CATCommand.h"

class CAADlgViewPlot: public CATCommand 
{
  public:

    CAADlgViewPlot();
    virtual ~CAADlgViewPlot();

    // AnalyseNotification
    // -------------------
    // Redefined from CATCommand
    // Analyzes notifications and, depending on their types, take appropriate
    // actions
    CATNotifPropagationMode AnalyseNotification(CATCommand      *iSending,
                                                CATNotification *iReceive);
    
    // WantedFocus
    // -----------
    // Called when the command wants the focus
    void WantedFocus();

    // Activate 
    // --------
    // Redefined from CATCommand
    // Called when the command gets the focus
    CATStatusChangeRC    Activate(CATCommand      *iFromClient,
                                  CATNotification *iNotification);

    // Desactivate
    // -----------
    // Redefined from CATCommand
    // Called when the command looses the focus
    //
    CATStatusChangeRC Desactivate(CATCommand      *iFromClient,
                                  CATNotification *iNotification);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgViewPlot(const CAADlgViewPlot &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgViewPlot & operator = (const CAADlgViewPlot &iObjectToCopy);
};

#endif
