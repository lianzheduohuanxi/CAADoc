// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgBBMessageNotification.h"

// To declare that the class is a component main class  
CATImplementClass(CAADlgBBMessageNotification,Implementation,CATBaseUnknown,CATNull);

//---------------------------------------------------------------------------
CAADlgBBMessageNotification::CAADlgBBMessageNotification(char * iText):_Text(NULL)
{
   if ( NULL != iText )
   {
      _Text = new char [strlen(iText)+1];
      strcpy(_Text,iText);
   }
}

//---------------------------------------------------------------------------
CAADlgBBMessageNotification::~CAADlgBBMessageNotification()
{
	if ( NULL != _Text )
	{
		delete [] _Text ;
		_Text = NULL ;
	}
}

//---------------------------------------------------------------------------
HRESULT CAADlgBBMessageNotification::GetText(char  ** oText )
{
   HRESULT rc = E_FAIL ;

   if ( NULL != oText )
   {
	  if ( NULL != _Text )
	  {
         *oText = new char [strlen(_Text)+1];
         strcpy(*oText,_Text);
      }else 
      {
         *oText = NULL ;
      }

      rc = S_OK ;
   }

   return rc ; 
}

