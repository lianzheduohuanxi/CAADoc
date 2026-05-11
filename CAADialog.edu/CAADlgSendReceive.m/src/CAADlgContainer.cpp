// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgContainer.h"

//---------------------------------------------------------------------------

CAADlgContainer::CAADlgContainer(char *iName): CATCommand(NULL) 
{
  // Keep the name of the model
  if ( NULL != iName )
  {
     _pContainerName = new char [strlen(iName)+1];
     strcpy(_pContainerName,iName);
  }else
  {
      _pContainerName = new char [13];
      strcpy(_pContainerName,"DefaultModel");
  }
  printf("The container, %s, is created.\n", _pContainerName );
}

//---------------------------------------------------------------------------

CAADlgContainer::~CAADlgContainer() 
{
  printf("The container, %s, is deleted.\n", _pContainerName );

  if ( NULL != _pContainerName )
  {
     delete [] _pContainerName ;
     _pContainerName = NULL ;
  }
}

//---------------------------------------------------------------------------

char * CAADlgContainer::GetContainerName() 
{
  return(_pContainerName);
}

// -----------------------------------------------------------------------------

CATNotifPropagationMode CAADlgContainer::AnalyseNotification(CATCommand      *iSending, 
                                                             CATNotification *iReceive) 
{
  printf("The container, %s, analyzes a notification.\n",_pContainerName);

  if ( NULL == iReceive ) return CATNotifDontTransmitToFather ;

  if ( 1 == iReceive->IsAKindOf("CAADlgNotifAdd"))
  {
      return(CATNotifTransmitToFather);

  } else if ( 1 == iReceive->IsAKindOf("CAADlgNotifRemove")) 
  {
      return(CATNotifTransmitToFather);

  }else if ( 1 == iReceive->IsAKindOf("CAADlgNotifError")) 
  {
      printf("The container catches an error \n");
      return(CATNotifDontTransmitToFather);

  } else 
  {
    return(CATNotifTransmitToFather);
  };
}
