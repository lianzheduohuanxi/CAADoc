// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgViewScreen.h"
#include "CAADlgElement.h"

// -----------------------------------

CAADlgViewScreen::CAADlgViewScreen(): CATCommand(NULL) 
{
  printf("The screen view is created.\n");
}

// ----------------------------------

CAADlgViewScreen::~CAADlgViewScreen() 
{
  printf("The screen view is deleted.\n");
}

// -------------------------------------------------------------------

CATNotifPropagationMode CAADlgViewScreen::AnalyseNotification(CATCommand *iSending, 
                                                              CATNotification *iReceive) 
{
  printf("The screen view analyzes a notification.\n");
  
  if ( ( NULL == iSending ) || ( NULL == iReceive ) )
      return CATNotifDontTransmitToFather ;

  if ( 1== iReceive->IsAKindOf("CAADlgAddNotification"))
  {
    // Gets information from the iSending command (the model is this case)
    CAADlgElement *pElement= NULL ;
    pElement = (CAADlgElement *)iSending->SendObject(CAADlgElement::ClassName(), iReceive);

    if ( NULL != pElement) 
    {
      printf("The screen view adds the %s element.\n", pElement->GetElementName());
      pElement->Release();
      pElement = NULL ;
      return(CATNotifDontTransmitToFather);
    } else 
    {
      return(CATNotifTransmitToFather);
    }
  } else if ( 1== iReceive->IsAKindOf("CAADlgRemoveNotification")) 
  {
    CAADlgElement *pElement= NULL ;
    pElement = (CAADlgElement *)iSending->SendObject(CAADlgElement::ClassName(), iReceive);

    if ( NULL != pElement) 
    {
      printf("The screen view removes the %s element.\n", pElement->GetElementName());
      pElement->Release();
      pElement = NULL ;
      return(CATNotifDontTransmitToFather);
    } else
    {
      return(CATNotifTransmitToFather);
    }
  } else 
  {
    return(CATNotifTransmitToFather);
  }
}

// -----------------------------------------------------

void CAADlgViewScreen::WantedFocus() 
{
  printf("The screen view wants the focus.\n");
  RequestStatusChange(CATCommandMsgRequestSharedMode);
}

// ------------------------------------------------

CATStatusChangeRC CAADlgViewScreen::Activate(CATCommand      *iFromClient, 
                                             CATNotification *iNotification)
{
  printf("The screen view gets the focus.\n");
  return(CATStatusChangeRCCompleted);
}

// ---------------------------------------------------

CATStatusChangeRC CAADlgViewScreen::Desactivate(CATCommand      *iFromClient, 
                                                CATNotification *iNotification) 
{
  printf("The screen view looses the focus.\n");
  return(CATStatusChangeRCCompleted);
}
