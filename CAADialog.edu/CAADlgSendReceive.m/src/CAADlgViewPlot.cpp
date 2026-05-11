// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgViewPlot.h"
#include "CAADlgElement.h"

// -----------------------------------------------------------------------------

CAADlgViewPlot::CAADlgViewPlot(): CATCommand(NULL)
{
  printf("The plot view is created.\n");
}

// -----------------------------------------------------------------------------

CAADlgViewPlot::~CAADlgViewPlot() 
{
  printf("The plot view is deleted.\n");
}

// -----------------------------------------------------------------------------

CATNotifPropagationMode CAADlgViewPlot::AnalyseNotification(CATCommand      *iSending, 
                                                            CATNotification *iReceive) 
{
  printf("The plot view analyzes a notification.\n");

  if ( ( NULL == iSending ) || ( NULL == iReceive ) )
      return CATNotifDontTransmitToFather ;

  if ( 1 == iReceive->IsAKindOf("CAADlgAddNotification"))
  {
    CAADlgElement * pElement= NULL;
    pElement = (CAADlgElement *)iSending->SendObject(CAADlgElement::ClassName(), iReceive);

    if ( NULL != pElement) 
    {
      printf("The plot view adds the %s element.\n", pElement->GetElementName());
      pElement->Release();
      pElement = NULL ;
      return(CATNotifDontTransmitToFather);
    } else 
    {
      return(CATNotifTransmitToFather);
    };

  } else if ( 1== iReceive->IsAKindOf("CAADlgRemoveNotification")) 
  {

    CAADlgElement * pElement= NULL ;
    pElement = (CAADlgElement *)iSending->SendObject(CAADlgElement::ClassName(), iReceive);

    if ( NULL != pElement) 
    {
      printf("The plot view removes the %s element.\n", pElement->GetElementName());
      pElement->Release();
      pElement = NULL ;
      return(CATNotifDontTransmitToFather);
    } else
    {
      return(CATNotifTransmitToFather);
    };
  } else 
  {
    return(CATNotifTransmitToFather);
  };
}

// -----------------------------------------------------

void CAADlgViewPlot::WantedFocus() 
{
  printf("The plot view wants the focus.\n");
  RequestStatusChange(CATCommandMsgRequestSharedMode);
}

// ------------------------------------------------

CATStatusChangeRC CAADlgViewPlot::Activate(CATCommand      *iFromClient, 
                                           CATNotification *iNotification)
{
  printf("The plot view gets the focus.\n");
  return(CATStatusChangeRCCompleted);
}

// ---------------------------------------------------

CATStatusChangeRC CAADlgViewPlot::Desactivate(CATCommand      *iFromClient, 
                                              CATNotification *iNotification) 
{
  printf("The plot view looses the focus.\n");
  return(CATStatusChangeRCCompleted);
}
